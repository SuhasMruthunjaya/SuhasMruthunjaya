----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 05/21/2025 01:13:10 PM
-- Design Name: 
-- Module Name: Custom_MUX - RTL
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


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Custom_MUX is
  Port (
        clk                        : in std_logic;
        rst_n                      : in std_logic;
        sel                        : in std_logic;
        spi_ph_address             : in std_logic_vector(7 downto 0);
        ddfs_data                  : in std_logic_vector(15 downto 0);
        spi_data                   : out std_logic_vector(23 downto 0);
        spi_continous_start        : out std_logic;
        start_op                   : in std_logic;
        spi_cpol                   : out std_logic;
        spi_divider                : out std_logic_vector(7 downto 0);
        spi_intermittent_start     : out std_logic;
        static_data                : in std_logic_vector(15 downto 0);
        
        ddfs_start                 : out std_logic;
        lut_trigger                : in std_logic;
        
        -- debug port
        debug_custom_MUX_STATE     : out std_logic_vector( 3 downto 0) := (others => '0')       
 );
end Custom_MUX;

architecture RTL of Custom_MUX is
    
    component SPI_START_Trigger 
        generic (
            Num_of_cycles : integer := 192
            );
        Port ( 
         clk        : in std_logic;
         rst_n      : in std_logic;
         start      : in std_logic;
         enable     : out std_logic     
        );
    end component;
    
    component edge_detect is
    port (
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic                      -- falling edge detect output
         );
    end component;
    
    type state_type is (st1_idle, st2_config_reg_update, ack_config_reg, st3_gain_reg_update, ack_gain_reg, read_status_reg, st4_dac_write);
    signal current_state, next_state : state_type;
    signal write_reg_done : std_logic := '0';
    
    signal spi_intermittent_start_signal : std_logic := '0';
    signal one_microsec_counter          : integer   := 0;
    signal count_start                   : std_logic := '0';
    signal trigger_pulse                 : std_logic := '0';
    
    signal redge_start_op                : std_logic := '0';
    signal fedge_start_op                : std_logic :='0';
    
    -- FSM STATE INTERNAL SIGNALS -- 
    signal idle_state : std_logic := '0';
    signal config_reg_update_state : std_logic := '0';
    signal gain_reg_update_state : std_logic := '0';
    signal dac_write_state : std_logic := '0';
    signal ack_config_reg_state : std_logic := '0';
    signal ack_gain_reg_state : std_logic := '0';
    signal read_status_reg_state : std_logic := '0';
    signal spi_data_int :  std_logic_vector(23 downto 0);
    signal ddfs_start_int : std_logic := '0';
    signal continous_start_trigger_active  : std_logic := '0';
        

begin

SPI_start_trigger_inst : SPI_START_Trigger generic map (Num_of_cycles => 187) port map ( clk => clk, rst_n => rst_n,
                         start => continous_start_trigger_active , enable => spi_continous_start);
                         
start_op_edge_detect   : edge_detect port map( rst => rst_n, clk => clk, inp => start_op, r_edge => redge_start_op,
                        f_edge => fedge_start_op);    
                                                    
                        
debug_custom_MUX_STATE <= std_logic_vector(to_unsigned(state_type'pos(current_state),4));                                                                                            

spi_intermittent_start <= spi_intermittent_start_signal;
spi_cpol               <= '0';
spi_divider            <= X"03"; 
ddfs_start             <= ddfs_start_int;        
        
spi_data_update :process(clk, rst_n)
begin
    if rising_edge(clk) then
        if rst_n = '0' then
            spi_data_int <= (others => '0');
            ddfs_start_int <= '0';
            continous_start_trigger_active <= '0';
        else
            if config_reg_update_state = '1' then
                spi_data_int <= X"030100";
            elsif ack_config_reg_state = '1' then
                spi_data_int <= X"130000";
            elsif gain_reg_update_state = '1' then
                spi_data_int <= X"0401FF";
            elsif ack_gain_reg_state = '1' then
                spi_data_int <= X"140000";
            elsif read_status_reg_state = '1' then
                spi_data_int <= X"170000";
            elsif dac_write_state = '1' then
                if sel = '0' then
                    ddfs_start_int <= '0';
                    spi_data_int <= spi_ph_address & static_data;
                    continous_start_trigger_active <= '0';
                else
                    continous_start_trigger_active <= '1';
                    ddfs_start_int <= '1';
                    spi_data_int <= spi_ph_address & ddfs_data;
                end if;
            else
                spi_data_int <= (others => '0');
            end if;
        end if;
    end if;
end process spi_data_update;


spi_data_register_pro : process (clk, rst_n)
begin
    if rising_edge(clk) then
        if rst_n = '0' then
            spi_data <= (others => '0'); -- Reset to a known state
        else
            -- Update spi_data only when we are in a state that actively drives it
            if current_state = st2_config_reg_update or
               current_state = ack_config_reg or
               current_state = st3_gain_reg_update or
               current_state = ack_gain_reg or
               current_state = read_status_reg or
               current_state = st4_dac_write then
                spi_data <= spi_data_int;
            -- ELSE, it implicitly holds its value (since there's no other assignment in this branch).
            -- This is the desired "hold until changed" behavior without latches.
            end if;
        end if;
    end if;
end process spi_data_register_pro;

-- Process to generate a single-cycle pulse when entering st2_config_reg_update
single_cycle_pulse: process (clk, rst_n)
begin
    if rising_edge(clk) then
        if rst_n = '0' then
            trigger_pulse <= '0';
        else
            if current_state = st1_idle and next_state = st2_config_reg_update then
                trigger_pulse <= '1';
            elsif current_state = st2_config_reg_update and next_state = ack_config_reg then
                trigger_pulse <= '1';
            elsif current_state = ack_config_reg and next_state = st3_gain_reg_update then
                trigger_pulse <= '1';
            elsif current_state = st3_gain_reg_update and next_state = ack_gain_reg then
                trigger_pulse <= '1';
            elsif current_state = ack_gain_reg and next_state = read_status_reg then
                trigger_pulse <= '1';
            elsif current_state = read_status_reg and next_state = st4_dac_write then
                trigger_pulse <= '1';
            else
                trigger_pulse <= '0';
            end if;
        end if;
    end if;
end process single_cycle_pulse;

state_transition : process (clk, rst_n)
begin
    if rising_edge(clk) then    
        if rst_n = '0' then
            current_state <= st1_idle;
        else
            current_state <= next_state;
        end if;
    end if;    
end process state_transition;

next_state_decode : process (current_state, start_op, write_reg_done, redge_start_op)
begin
    
    next_state <= current_state;
    
    case current_state is
        when st1_idle =>
            if redge_start_op = '1' then
                next_state <= st2_config_reg_update;
            else
                next_state <= st1_idle;
            end if;
       
        when st2_config_reg_update =>
            if write_reg_done = '1' then
                next_state <= ack_config_reg; 
            else
                next_state <= st2_config_reg_update;
            end if;
            
        when ack_config_reg =>
            if write_reg_done = '1' then
                next_state <= st3_gain_reg_update; 
            else
                next_state <= ack_config_reg;
            end if;     
                    
        when st3_gain_reg_update =>
             if write_reg_done = '1' then
                next_state <= ack_gain_reg;
             else
                next_state <= st3_gain_reg_update;
             end if;
             
        when ack_gain_reg =>
            if write_reg_done = '1' then
                next_state <= read_status_reg; 
            else
                next_state <= ack_gain_reg;
            end if; 
 
         when read_status_reg =>
            if write_reg_done = '1' then
                next_state <= st4_dac_write; 
            else
                next_state <= read_status_reg;
            end if;                         
                                     
        when st4_dac_write =>
             if sel = '0' then
                if write_reg_done = '1' then
                    next_state <= st1_idle;
                else
                    next_state <= st4_dac_write;
                end if;
             else
                if lut_trigger = '1' then
                    next_state <= st4_dac_write;
                end if;
             end if;
                        
        when others =>  
            next_state <= st1_idle;                
    end case;   

end process next_state_decode;


output_decode : process (current_state, trigger_pulse)
begin
    
    idle_state <= '0';
    config_reg_update_state <= '0';
    spi_intermittent_start_signal <= '0';
    count_start <= '0';
    gain_reg_update_state <= '0';
    dac_write_state   <= '0';
    ack_config_reg_state    <= '0';
    ack_gain_reg_state  <= '0';
    read_status_reg_state <= '0';
    
    case current_state is
        when st1_idle =>
            idle_state                      <= '1';
        when st2_config_reg_update =>
            spi_intermittent_start_signal   <= trigger_pulse;
            config_reg_update_state         <= '1';
            count_start                     <= '1';
        when ack_config_reg =>
            ack_config_reg_state           <= '1'; 
            spi_intermittent_start_signal  <= trigger_pulse;
            count_start                    <= '1';           
        when st3_gain_reg_update =>
            gain_reg_update_state           <= '1';
            spi_intermittent_start_signal   <= trigger_pulse;
            count_start                     <= '1';
        when ack_gain_reg =>
            ack_gain_reg_state           <= '1'; 
            spi_intermittent_start_signal  <= trigger_pulse;
            count_start                    <= '1';     
        when read_status_reg =>
            read_status_reg_state           <= '1'; 
            spi_intermittent_start_signal  <= trigger_pulse;
            count_start                    <= '1';                                      
        when st4_dac_write =>
            dac_write_state                 <= '1';
            count_start                     <= '1';
            spi_intermittent_start_signal   <= trigger_pulse;
        when others =>
            null;
    end case;

end process output_decode;

one_microsec_counter_pro : process (clk, rst_n)
begin
    if rising_edge(clk) then
        if rst_n = '0' then
            one_microsec_counter <= 0;
            write_reg_done  <= '0';
        else
            if count_start = '1' then
                one_microsec_counter <= one_microsec_counter + 1;
            end if;
            if one_microsec_counter = 187 then
                one_microsec_counter <= 0;
                write_reg_done <= '1';
            else
                write_reg_done <= '0';    
            end if;
        end if;
    end if;
end process one_microsec_counter_pro;
    
end RTL;
