----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379) 
-- 
-- Create Date: 02/25/2025 01:04:22 PM
-- Design Name: 
-- Module Name: slaveEmulator_tb - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity slaveEmulator_tb is
--  Port ( );
end slaveEmulator_tb;

architecture Behavioral of slaveEmulator_tb is

    component slaveEmulator is
        port(
            clk : in std_logic;
            rst_n : in std_logic;
            SCL_in : in std_logic;
            SDA_out : inout std_logic
            );
      end component;
      
      signal clk_tb : std_logic := '0';
      signal rst_n_tb : std_logic := '0';
      signal SCL_in_tb : std_logic := '0';
      signal SDA_out_tb : std_logic := '1';
      signal count_tb : integer := 0;

begin
    
    clk_tb <= not clk_tb after 5ns;
    rst_n_tb <= '1' , '0' after 10ns;
    SDA_out_tb <= 'Z' after 10ns;
    
    dut : slaveEmulator
    port map (
              clk  => clk_tb,
              rst_n => rst_n_tb,
              SCL_in => SCL_in_tb,
              SDA_out => SDA_out_tb
             );
    
    
    scl_stimulus : process(clk_tb, rst_n_tb)
    begin
    if rst_n_tb = '1' then
        count_tb <= 0;
        SCL_in_tb <= '1';
        --SDA_signal <= '1';
    elsif rising_edge(clk_tb) then
            if count_tb < 249 then
                count_tb <= count_tb + 1;
            else
                count_tb <= 0;  -- Reset count after 250 cycles
            end if;

            -- Toggle SCL_signal based on the count
            if count_tb < 125 then
                SCL_in_tb <= '1';  -- First 125 cycles ON
            else
                SCL_in_tb <= '0';  -- Next 125 cycles OFF
            end if;
        end if;
    end process;

end Behavioral;
