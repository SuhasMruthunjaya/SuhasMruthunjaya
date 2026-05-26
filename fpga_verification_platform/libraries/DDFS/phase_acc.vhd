----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379) 
-- 
-- Create Date: 05/15/2025 11:27:26 AM
-- Design Name: 
-- Module Name: phase_acc - rtl
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

entity phase_acc is
  Port ( clk :          in std_logic;
         rst_n :        in std_logic;
         enable :       in std_logic;
         ftw :          in std_logic_vector(15 downto 0);
         q :            out std_logic_vector( 9 downto 0)
       );
end phase_acc;

architecture rtl of phase_acc is
      signal q_reg : unsigned (15 downto 0) := (others => '0');      
begin

    q <= std_logic_vector(q_reg( 9 downto 0));
    
    phase_acc_stimulus : process(clk) 
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                q_reg <= (others => '0');
            elsif enable = '1' then
                q_reg <= q_reg + unsigned(ftw);
            end if;
        end if;
    end process phase_acc_stimulus;

end rtl;
