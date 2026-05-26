----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379) 
-- 
-- Create Date: 09/17/2025 10:34:43 AM
-- Design Name: 
-- Module Name: DeadTime_Capture - rtl
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
    --use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity DeadTime_Capture is
Port ( clk              : in std_logic;
       rst_n            : in std_logic;
       pwm_high         : in std_logic;
       pwm_low          : in std_logic;
       pwm_deadTime     : out std_logic_vector(31 downto 0)
                
         --debug purpose
       --watchdog_active_out    : out std_logic 
       
     );
end DeadTime_Capture;

architecture rtl of DeadTime_Capture is

    component edge_detect is
    port (
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic                         -- falling edge detect output
         );
    end component;
    
    signal redge_pwm_high       : std_logic := '0';
    signal fedge_pwm_high       : std_logic := '0';
    signal redge_pwm_low        : std_logic := '0';
    signal fedge_pwm_low        : std_logic := '0';
    signal free_counter         : unsigned (15 downto 0) := (others => '0');
    signal pwm_high_deadtime    : unsigned (15 downto 0) := (others => '0');
    signal pwm_low_deadtime     : unsigned (15 downto 0) := (others => '0');
    signal pwm_high_sync_0      : std_logic;
    signal pwm_high_sync_1      : std_logic;
    signal pwm_high_sync        : std_logic;
    signal pwm_low_sync_0       : std_logic;
    signal pwm_low_sync_1       : std_logic;
    signal pwm_low_sync         : std_logic;
    constant WATCHDOG_LIMIT : unsigned (16 downto 0) := TO_UNSIGNED(96000, 17);  
    signal watchdog_active : std_logic := '0';           

begin
    
   pwm_high_ed : edge_detect port map( rst => rst_n, clk => clk, inp => pwm_high_sync, r_edge => redge_pwm_high, f_edge => fedge_pwm_high);
   pwm_low_ed  : edge_detect port map( rst => rst_n, clk => clk, inp => pwm_low_sync, r_edge => redge_pwm_low, f_edge => fedge_pwm_low);
   
   pwm_deadTime <= std_logic_vector(pwm_low_deadtime) & std_logic_vector(pwm_high_deadtime) when watchdog_active = '0' else (others => '0'); 
   
   --watchdog_active_out <= watchdog_active;    
   
    pwm_high_sync_pro : process(clk, rst_n)
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                pwm_high_sync_0 <= '0';
                pwm_high_sync_1 <= '0';
                pwm_high_sync   <= '0';
            else
                pwm_high_sync_0 <= pwm_high;
                pwm_high_sync_1 <= pwm_high_sync_0;
                pwm_high_sync   <= pwm_high_sync_1;
            end if;
        end if;
    end process pwm_high_sync_pro;
   

    pwm_low_sync_pro : process(clk, rst_n)
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                pwm_low_sync_0 <= '0';
                pwm_low_sync_1 <= '0';
                pwm_low_sync   <= '0';
            else
                pwm_low_sync_0 <= pwm_low;
                pwm_low_sync_1 <= pwm_low_sync_0;
                pwm_low_sync   <= pwm_low_sync_1;
            end if;
        end if;
    end process pwm_low_sync_pro;
    
    
    free_counter_pro : process(clk, rst_n)
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                free_counter <= (others => '0');
            else
                free_counter <= free_counter + 1;
            end if;
        end if;
    end process free_counter_pro;
    
    deadtime_highLow_counter_pro : process(clk, rst_n)
        variable risingEdge_pwm_low_value : unsigned (15 downto 0) := (others => '0');
        variable fallingEdge_pwm_high_value : unsigned (15 downto 0) := (others => '0');
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                risingEdge_pwm_low_value   := (others => '0');
                fallingEdge_pwm_high_value  := (others => '0');
            else
                if fedge_pwm_high = '1' then
                    fallingEdge_pwm_high_value := free_counter;
                elsif redge_pwm_low = '1' then
                    risingEdge_pwm_low_value := free_counter;
                    pwm_high_deadtime <= risingEdge_pwm_low_value - fallingEdge_pwm_high_value;                   
                end if;
            end if;
        end if;
    end process deadtime_highLow_counter_pro; 
    

    deadtime_Lowhigh_counter_pro : process(clk, rst_n)
        variable risingEdge_pwm_high_value : unsigned (15 downto 0) := (others => '0');
        variable fallingEdge_pwm_low_value : unsigned (15 downto 0) := (others => '0');
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                risingEdge_pwm_high_value   := (others => '0');
                fallingEdge_pwm_low_value  := (others => '0');
            else
                if fedge_pwm_low = '1' then
                    fallingEdge_pwm_low_value := free_counter;
                elsif redge_pwm_high = '1' then
                    risingEdge_pwm_high_value := free_counter;
                    pwm_low_deadtime <= risingEdge_pwm_high_value - fallingEdge_pwm_low_value;                   
                end if;
            end if;
        end if;
    end process deadtime_Lowhigh_counter_pro; 
    
    watchdog_pro : process(clk,rst_n)       
        variable watchdog_counter : unsigned (16 downto 0) := (others => '0');        
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                watchdog_counter := (others => '0');
                watchdog_active <= '0';
            else
                if ((redge_pwm_high = '1') or (redge_pwm_low = '1')) then
                    watchdog_counter := (others => '0');
                    watchdog_active <= '0';
                elsif watchdog_counter < WATCHDOG_LIMIT then
                    watchdog_counter := watchdog_counter + 1;
                    watchdog_active <= '0';
                else
                     watchdog_counter := WATCHDOG_LIMIT;
                     watchdog_active <= '1';
                end if;                
            end if;
        end if;
    end process watchdog_pro;


end rtl;
