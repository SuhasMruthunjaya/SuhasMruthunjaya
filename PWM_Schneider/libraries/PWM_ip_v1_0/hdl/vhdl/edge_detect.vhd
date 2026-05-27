----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 18.11.2022 15:31:42
-- Design Name: 
-- Module Name: edge_detect - rtl
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

entity edge_detect is
    port ( 
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic);                       -- falling edge detect output
end edge_detect;

architecture rtl of edge_detect is
   signal ff1 :std_logic := '0';                                -- first Flip-Flop
   signal ff2 :std_logic;                                       -- second Flip-Flop

begin
    p_edge_detect: process(clk,rst)   
    begin
        if rst='0' then
            ff1 <= '0';
            ff2 <= '0';
         elsif rising_edge(clk) then
            ff1 <= inp;                                         
            ff2 <= ff1;
        end if;
    end process;
    
    r_edge <= ff1 and (not ff2);                                -- rising edge detect pulse 
    f_edge <= ff1 nor (not ff2);                                -- falling edge detect pulse
 
end rtl;
