----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 05/28/2025 12:50:20 PM
-- Design Name: 
-- Module Name: toggle_signal - Behavioral
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

entity toggle_signal is
    Port( 
        clk_in     : in  std_logic;
        rst_n   : in  std_logic;
        toggle_out : out std_logic;
        start_sig  : in std_logic
    );
end toggle_signal;

architecture rtl of toggle_signal is

signal toggle_out_int   : std_logic := '0';

begin

process (clk_in, rst_n)
begin
    if rising_edge(clk_in) then
        if rst_n = '0' then
            toggle_out_int <= '0';
        elsif start_sig = '1' then
            toggle_out_int <= not toggle_out_int;
        end if;      
     end if;      
end process;

toggle_out <= toggle_out_int;

end rtl;
