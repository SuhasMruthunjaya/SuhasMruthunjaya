----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 09/11/2025 09:59:29 AM
-- Design Name: 
-- Module Name: PWM_Analyzer - RTL
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
--use IEEE.std_logic_arith.ALL;
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity PWM_Analyzer is
  Port ( clk                : in std_logic; 
         rst_n              : in std_logic;
         PWM_in             : in std_logic;
         PWM_count          : out unsigned(15 downto 0);
         dutycycle_count    : out unsigned(15 downto 0)
         
         --debug purpose
         --watchdog_active_out    : out std_logic 
       );
end PWM_Analyzer;

architecture RTL of PWM_Analyzer is

    component edge_detect is
    port (
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic                         -- falling edge detect output
         );
    end component;
    
    signal redge_pwm                        : std_logic := '0';
    signal fedge_pwm                        : std_logic := '0';
    signal counter_pwm                      : unsigned (15 downto 0) := (others => '0');
    signal counter_dutyCycle                : unsigned (15 downto 0) := (others => '0');
    signal free_counter                     : unsigned (15 downto 0) := (others => '0');
    signal armed                            : std_logic;
    
    signal PWM_sync_0 : std_logic := '0';
    signal PWM_sync_1 : std_logic := '0';
    signal PWM_sync   : std_logic := '0';
    constant WATCHDOG_LIMIT : unsigned (16 downto 0) := TO_UNSIGNED(96000, 17);
    signal watchdog_active : std_logic := '0'; 
          

begin

    pwm_ed : edge_detect port map( rst => rst_n, clk => clk, inp => PWM_sync, r_edge => redge_pwm, f_edge => fedge_pwm);
    
    
    PWM_count           <= counter_pwm when watchdog_active = '0' else  (others => '0');
    dutycycle_count     <= counter_dutyCycle when watchdog_active = '0' else (others => '0');
    
    --watchdog_active_out <= watchdog_active;    
    
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
    
    
    watchdog_pro : process(clk,rst_n)       
        variable watchdog_counter : unsigned (16 downto 0) := (others => '0');        
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                watchdog_counter := (others => '0');
                watchdog_active <= '0';
            else
                if ((redge_pwm = '1') or (fedge_pwm = '1')) then
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
       
    
    pwm_counter_pro : process(clk,rst_n)
        variable current_free_counter_value : unsigned(15 downto 0) := (others => '0');
        variable prev_free_counter_value: unsigned(15 downto 0) := (others => '0');
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                counter_pwm                 <= (others => '0');
                prev_free_counter_value     := (others => '0');
                current_free_counter_value  := (others => '0');
                armed                       <= '0'; 
            else
                if redge_pwm = '1' then
                    if armed = '0' then
                        prev_free_counter_value := free_counter;
                        armed <= '1' ;
                    else
                        current_free_counter_value  := free_counter;
                        counter_pwm <= current_free_counter_value - prev_free_counter_value;
                        prev_free_counter_value := current_free_counter_value;
                    end if;
                end if;
            end if;
        end if;
    end process pwm_counter_pro;
    
    
    dutyCycle_counter_pro : process(clk, rst_n)
        variable risingEdge_counter_value : unsigned (15 downto 0) := (others => '0');
        variable fallingEdge_counter_value : unsigned (15 downto 0) := (others => '0');
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                risingEdge_counter_value   := (others => '0');
                fallingEdge_counter_value  := (others => '0');
            else
                if redge_pwm = '1' then
                    risingEdge_counter_value := free_counter;
                elsif fedge_pwm = '1' then
                    fallingEdge_counter_value := free_counter;
                    counter_dutyCycle <= fallingEdge_counter_value - risingEdge_counter_value;                   
                end if;
            end if;
        end if;
    end process dutyCycle_counter_pro; 
        
    sync_pro : process(clk, rst_n)
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                PWM_sync_0 <= '0';
                PWM_sync_1 <= '0';
                PWM_sync   <= '0';
            else
                PWM_sync_0 <= PWM_in;
                PWM_sync_1 <= PWM_sync_0;
                PWM_sync   <= PWM_sync_1;
            end if;
        end if;
    end process sync_pro;

end RTL;
