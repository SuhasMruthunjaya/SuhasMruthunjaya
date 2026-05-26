----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 05/22/2025 01:55:33 PM
-- Design Name: 
-- Module Name: Custom_SPI_START_Trigger - rtl
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

entity SPI_START_Trigger is
  generic (
            Num_of_cycles : integer := 187
             
           );
  Port ( 
         clk        : in std_logic;
         rst_n      : in std_logic;
         start      : in std_logic;
         enable     : out std_logic     
        );
end SPI_START_Trigger;

architecture rtl of SPI_START_Trigger is
       signal count : integer := 0;
begin
    
    enable <= '1' when count = Num_of_cycles - 1 else '0';
    
    counter : process(clk, rst_n)
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                 count <= 0;
            elsif start = '1' then
                 if count < Num_of_cycles then
                    count <= count + 1;
                 else
                    count <= 0;
                 end if;   
            end if;
        end if;
         
    end process counter;

end rtl;
