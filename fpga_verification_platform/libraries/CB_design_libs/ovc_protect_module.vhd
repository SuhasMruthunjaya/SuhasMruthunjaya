----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 13.09.2023 14:49:57
-- Design Name: 
-- Module Name: ovc_protect_module - rtl
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------
LIBRARY ieee;                                                                                                                         
USE ieee.std_logic_1164.all;                                                                                                          
USE ieee.std_logic_arith.all;                                                                                                         
USE ieee.std_logic_unsigned.all;                                                                                                      
USE ieee.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ovc_protect_module is
    port 
        ( 
            clk             : in std_logic;
            reset_n         : in std_logic;
            ovc_low_limit   : in std_logic_vector(11 downto 0);
            ovc_high_limit  : in std_logic_vector(11 downto 0);
            current_offset  : in std_logic_vector(11 downto 0);
            ovc_time        : in std_logic_vector(11 downto 0);
            sc_off          : in std_logic;
            trigger_ovc     : in std_logic;
            current_raw_adc : in std_logic_vector(35 downto 0);
            status          : out std_logic_vector(5 downto 0);     -- [0:1] -> U, [2:3] -> V, [4:5] -> W (overcurrent and short-circuit)
            ovc_event       : out std_logic;
            ovc_release     : in std_logic
        );
end ovc_protect_module;

architecture rtl of ovc_protect_module is
-- fsm type
type   fsm_ovc_state is(ready, wait_current, get_current, overcurrent, short_circuit);
signal state_reg, state_next: fsm_ovc_state;
-- internal signals
signal ovc_low_limit_intern     : std_logic_vector(11 downto 0) := x"650";  -- 65A -> 65A*0.002Ohm*10 V/V ~ 1.302V  (ADC input) -> 1.302V/3.3V*2^12  = 1616 LSBs -> 650 hex
signal ovc_high_limit_intern    : std_logic_vector(11 downto 0) := x"7CE";  -- 80.5A -> 10A*0.002Ohm*10 V/V ~ 1.61V  (ADC input) -> 1.61V/3.3V*2^12  = 1998 LSBs -> 7CE hex
signal current_offset_intern    : std_logic_vector(11 downto 0) := x"800";  -- ADC offset, initially set to 0x800, but has to be set by FW
signal ovc_error_u              : std_logic := '0';                         -- overcurrent error
signal ovc_error_v              : std_logic := '0';                         -- overcurrent error
signal ovc_error_w              : std_logic := '0';                         -- overcurrent error
signal sc_error_u               : std_logic := '0';                         -- short circuit error
signal sc_error_v               : std_logic := '0';                         -- short circuit error
signal sc_error_w               : std_logic := '0';                         -- short circuit error
signal ovc_counter_u            : std_logic_vector(11 downto 0) := (others => '0');
signal ovc_counter_v            : std_logic_vector(11 downto 0) := (others => '0');
signal ovc_counter_w            : std_logic_vector(11 downto 0) := (others => '0');
signal compare                  : std_logic := '0';
signal ovc_timer                : std_logic_vector(11 downto 0) := x"280";  -- 10us OVC time

begin

ovc_low_limit_intern  <= x"650" when ovc_low_limit = x"000" else ovc_low_limit;
ovc_high_limit_intern <= x"7CE" when ovc_high_limit = x"000" else ovc_high_limit;
current_offset_intern <= x"800" when current_offset = x"000" else current_offset;
ovc_timer <= x"280" when ovc_time = x"000" else ovc_time;

-- current compare process
meas_current_proc: process(clk, reset_n, compare)
begin
    if rising_edge(clk) then
        if reset_n = '0' then
            status <= "000000";
            ovc_error_u <= '0';
            ovc_error_v <= '0';
            ovc_error_w <= '0';
            sc_error_u <= '0';
            sc_error_v <= '0';
            sc_error_w <= '0'; 
        elsif compare = '1' then
            -- Phase U    
            if current_raw_adc(11 downto 0) <= (current_offset_intern - ovc_low_limit_intern)  and 
               current_raw_adc(11 downto 0) >= (current_offset_intern - ovc_high_limit_intern) then
                status(0) <= '1';
                ovc_error_u <= '1';
            elsif current_raw_adc(11 downto 0) >= (current_offset_intern + ovc_low_limit_intern)  and 
               current_raw_adc(11 downto 0) <= (current_offset_intern + ovc_high_limit_intern) then
                status(0) <= '1';
                ovc_error_u <= '1';
            elsif current_raw_adc(11 downto 0) <= (current_offset_intern - ovc_high_limit_intern) or 
               current_raw_adc(11 downto 0) >= (current_offset_intern + ovc_high_limit_intern) then      
                status(1) <= '1';
                sc_error_u <= '1';   
            else
                status(0) <= '0';
                status(1) <= '0';
                ovc_error_u <= '0';
                sc_error_u <= '0';     
            end if;   
             -- Phase V    
            if current_raw_adc(23 downto 12) <= (current_offset_intern - ovc_low_limit_intern)  and 
               current_raw_adc(23 downto 12) >= (current_offset_intern - ovc_high_limit_intern) then
                status(2) <= '1';
                ovc_error_v <= '1';
            elsif current_raw_adc(23 downto 12) >= (current_offset_intern + ovc_low_limit_intern)  and 
               current_raw_adc(23 downto 12) <= (current_offset_intern + ovc_high_limit_intern) then
                status(2) <= '1';
                ovc_error_v <= '1';
            elsif current_raw_adc(23 downto 12) <= (current_offset_intern - ovc_high_limit_intern) or 
               current_raw_adc(23 downto 12) >= (current_offset_intern + ovc_high_limit_intern) then      
                status(3) <= '1';
                sc_error_v <= '1';  
            else
                status(2) <= '0';
                status(3) <= '0';
                ovc_error_v <= '0';
                sc_error_v <= '0';      
            end if;                                                             
             -- Phase W    
            if current_raw_adc(35 downto 24) <= (current_offset_intern - ovc_low_limit_intern)  and 
               current_raw_adc(35 downto 24) >= (current_offset_intern - ovc_high_limit_intern) then
                status(4) <= '1';
                ovc_error_w <= '1';
            elsif current_raw_adc(35 downto 24) >= (current_offset_intern + ovc_low_limit_intern)  and 
               current_raw_adc(35 downto 24) <= (current_offset_intern + ovc_high_limit_intern) then
                status(4) <= '1';
                ovc_error_w <= '1';
            elsif current_raw_adc(35 downto 24) <= (current_offset_intern - ovc_high_limit_intern) or 
               current_raw_adc(35 downto 24) >= (current_offset_intern + ovc_high_limit_intern) then      
                status(5) <= '1';
                sc_error_w <= '1'; 
            else
                status(4) <= '0';
                status(5) <= '0';
                ovc_error_w <= '0';
                sc_error_w <= '0';                   
            end if;
        else
            status <= "000000";
            ovc_error_u <= '0';
            ovc_error_v <= '0';
            ovc_error_w <= '0';
            sc_error_u <= '0';
            sc_error_v <= '0';
            sc_error_w <= '0';        
        end if;        
    end if;
end process;

-- overcurrent counter for phase U generation process
ovc_counter_u_proc: process(clk, reset_n, ovc_error_u)
begin
    if (rising_edge(clk)) then
        if (reset_n = '0') then
            ovc_counter_u <= (others => '0');
        elsif ovc_error_u = '1' then
            ovc_counter_u <= ovc_counter_u + 1;
        else 
            ovc_counter_u <= (others => '0');    
        end if;
    end if;
end process;

-- overcurrent counter for phase V generation process
ovc_counter_v_proc: process(clk, reset_n, ovc_error_v)
begin
    if (rising_edge(clk)) then
        if (reset_n = '0') then
            ovc_counter_v <= (others => '0');
        elsif ovc_error_v = '1' then
            ovc_counter_v <= ovc_counter_v + 1;
        else 
            ovc_counter_v <= (others => '0');    
        end if;
    end if;
end process;

-- overcurrent counter for phase W generation process
ovc_counter_w_proc: process(clk, reset_n, ovc_error_w)
begin
    if (rising_edge(clk)) then
        if (reset_n = '0') then
            ovc_counter_w <= (others => '0');
        elsif ovc_error_w = '1' then
            ovc_counter_w <= ovc_counter_w + 1;
        else 
            ovc_counter_w <= (others => '0');    
        end if;
    end if;
end process;

-- beginning of the FSM - first process FSM generation 
fsm_sync_proc: process(clk, reset_n)
begin
    if (rising_edge(clk)) then
        if (reset_n = '0') then
            state_reg <= ready;
        else
            state_reg <= state_next;
        end if;
    end if;
end process; 

-- next state generation process
next_state_decode: process(state_reg, reset_n, ovc_error_u, ovc_error_v, ovc_error_w, sc_error_u, sc_error_v, sc_error_w, ovc_counter_u, ovc_counter_v, ovc_counter_w, ovc_release, sc_off)
begin
    state_next <= state_reg;
    case(state_reg) is
        when ready =>
            if reset_n = '1' then
                state_next <= get_current;
            else
                state_next <= ready;
            end if;  
        when wait_current =>
            if trigger_ovc = '1' then
                state_next <= get_current;
            else
                state_next <= wait_current;
            end if;             
        when get_current =>
            if ovc_error_u = '1' or ovc_error_v = '1' or ovc_error_w = '1' then
                state_next <= overcurrent;
            elsif sc_off = '1' and (sc_error_u = '1' or sc_error_v = '1' or sc_error_w = '1') then
                state_next <= short_circuit;
            else
                state_next <= get_current;   
            end if;
        when overcurrent => 
            -- 10us for overcurrent x"280"
            if ovc_counter_u >= ovc_timer or ovc_counter_v >= ovc_timer or ovc_counter_w >= ovc_timer then
                state_next <= short_circuit;
            elsif sc_off = '1' and (sc_error_u = '1' or sc_error_v = '1' or sc_error_w = '1') then 
                state_next <= short_circuit;
            elsif ovc_error_u = '0' and ovc_error_v = '0' and ovc_error_w = '0' and sc_error_u = '0' and sc_error_v = '0' and sc_error_w = '0' then
                state_next <= get_current;     
            else
                state_next <= overcurrent;    
            end if;
        when short_circuit =>
            if ovc_release = '1' then
                state_next <= get_current;
            else
                state_next <= short_circuit;
            end if;
        when others => null;
    end case;   
end process;                          

-- FSM output generation process
output_generation_proc: process(state_reg)
begin
    ovc_event <= '0';
    compare <= '0';
    case state_reg is
        when ready =>
            ovc_event <= '0';
            compare <= '0';
        when wait_current =>
            ovc_event <= '0';
            compare <= '0';
        when get_current =>
            compare <= '1';
            ovc_event <= '0';
        when overcurrent =>
            compare <= '1';
            ovc_event <= '0';
        when short_circuit =>
            compare <= '1';
            ovc_event <= '1';
        when others => null;
    end case;  
end process;                                   

end rtl;
