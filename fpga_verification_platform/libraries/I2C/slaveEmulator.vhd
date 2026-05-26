----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/25/2025 12:42:15 PM
-- Design Name: 
-- Module Name: slaveEmulator - rtl
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
use IEEE.Numeric_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity slaveEmulator is
  Port ( 
            clk : in std_logic;
            rst_n : in std_logic;
            SCL_in : in std_logic;
            SDA_out : out std_logic;
            start_read_trigger : in std_logic;
            start_write_trigger : in std_logic;
            stop_trigger : in std_logic;
            
            debug_port : in std_logic_vector( 15 downto 0) := (others => '0')
         );
end slaveEmulator;

architecture rtl of slaveEmulator is
    
    signal count : integer := 0;
    signal redge_scl: std_logic := '0';
    signal fedge_scl: std_logic := '0';
    signal temp : std_logic := '0';
    signal hd_counter : integer := 0;
    signal hd_count_start : integer := 0;
    signal hd_count_done : integer := 0;
    signal SDA_write_slaveEmulator : std_logic := '0';
    signal redge_read_trigger : std_logic := '0';
    signal fedge_read_trigger : std_logic := '0';
    signal redge_write_trigger : std_logic := '0';
    signal fedge_write_trigger : std_logic := '0';
    signal redge_stop_trigger : std_logic := '0';
    signal fedge_stop_trigger : std_logic := '0';
    signal read_trigger : std_logic := '0';
    signal stop_trigger_sig : std_logic := '0';    
    signal write_trigger : std_logic := '0';
    signal debug_port_integer : integer := 0;
     
    component edge_detect is
    port (
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic                      -- falling edge detect output
         );
    end component;
    
begin

SCL_ed : edge_detect port map( rst => rst_n, clk => clk, inp => SCL_in, r_edge => redge_scl, f_edge => fedge_scl); 
read_trigger_ed : edge_detect port map( rst => rst_n, clk => clk, inp => start_read_trigger, r_edge => redge_read_trigger,
                  f_edge => fedge_read_trigger);
write_trigger_ed : edge_detect port map (rst => rst_n, clk => clk, inp => start_write_trigger, r_edge => redge_write_trigger,
                  f_edge => fedge_write_trigger);
stop_trigger_ed : edge_detect port map (rst => rst_n, clk => clk, inp => stop_trigger, r_edge => redge_stop_trigger,
                  f_edge => fedge_stop_trigger);
                  
debug_port_integer <= to_integer(unsigned(debug_port));                

capture_read_trigger : process(clk, rst_n)
begin
    if rst_n = '0' then
        read_trigger <= '0';
    elsif rising_edge(clk) then
        if redge_read_trigger = '1' then
            read_trigger <= '1';
        end if;
        if debug_port_integer = 6 then
            read_trigger <= '0';
        end if;
    end if;
end process capture_read_trigger;


capture_write_trigger : process(clk, rst_n)
begin
    if rst_n = '0' then
        write_trigger <= '0';
    elsif rising_edge(clk) then
        if redge_write_trigger = '1' then
            write_trigger <= '1';
        end if;
        if  debug_port_integer = 6 then
            write_trigger <= '0';
        end if;
    end if;
end process capture_write_trigger;

capture_stop_trigger : process(clk, rst_n)
begin
    if rst_n = '0' then
        stop_trigger_sig <= '0';
    elsif rising_edge(clk) then
        if redge_stop_trigger = '1' then
            stop_trigger_sig <= '1';
        end if;
        if read_trigger = '1' or write_trigger = '1' then 
            stop_trigger_sig <= '0';
        end if;
    end if;
end process capture_stop_trigger;

   
stim: process (clk, rst_n)
    begin
        if (rst_n = '0') then
            SDA_write_slaveEmulator <= '0';
        elsif rising_edge(clk) then
            if read_trigger = '1' or write_trigger = '1' then
                temp <= fedge_scl;
                if temp = '1' then
                    count <= count + 1;
                    if count = 8 then
                        count <= 0;
                        SDA_write_slaveEmulator <= '1';
                    else 
                        SDA_write_slaveEmulator <= '0';
                    end if;
                end if;
            elsif stop_trigger_sig = '1' or debug_port_integer = 6 then
                SDA_write_slaveEmulator <= '0';
                count <= 0;
            end if;
        end if;
    end process;
    
holdtime_counter : process(clk)
begin
    if rst_n = '0' then
        hd_counter <= 0;
        hd_count_done <= 0;
    elsif rising_edge(clk) then
        if hd_count_start = 1 then
            if hd_counter < 23 then
                hd_counter <= hd_counter + 1;
                hd_count_done <= 0;
            else 
                hd_counter <= 0;
                hd_count_done <= 1;
            end if;
        end if;
    end if;
end process;


SDA_write : process(clk, rst_n)
    begin 
        if (rst_n = '0') then 
            SDA_out <= 'Z';
            hd_count_start <= 0;
        elsif rising_edge(clk) then
            if SDA_write_slaveEmulator = '1' then
                 hd_count_start <= 1;
                 if hd_count_done = 1 then
                    SDA_out <= '0';
                    hd_count_start <= 0;
                 end if;
            else 
                SDA_out <= 'Z';
            end if;
       end if;
     end process;
         
            

end rtl;
