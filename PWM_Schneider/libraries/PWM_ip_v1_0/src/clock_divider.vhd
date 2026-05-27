----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.02.2023 12:09:54
-- Design Name: 
-- Module Name: clock_divider - rtl
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
USE IEEE.numeric_std.ALL;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity clock_divider is
    port (  clk         : in std_logic;
            reset       : in std_logic;
            clock_out   : out std_logic
          );
end clock_divider;

architecture rtl of clock_divider is
signal count: unsigned(2 downto 0) := "001";
signal tmp : std_logic := '0';

begin
    process(clk,reset)
        begin
        if(reset='1') then
            count <= "001";
            tmp <= '0';
        elsif rising_edge(clk) then
            count <= count + 1;
            if (count = 6) then
                tmp <= NOT tmp;
                count <= "001";
            end if;
        end if;
         if(reset='1') then
            count <= "001";
            tmp <= '0';
        elsif falling_edge(clk) then
            count <= count + 1;
            if (count = 6) then
                tmp <= NOT tmp;
                count <= "001";
            end if;
        end if;
        clock_out <= tmp;
    end process;

end rtl;
