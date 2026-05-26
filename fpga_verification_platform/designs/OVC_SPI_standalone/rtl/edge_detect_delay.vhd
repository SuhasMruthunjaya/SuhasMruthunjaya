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

entity edge_detect_delay is
    port ( 
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic);                       -- falling edge detect output
end edge_detect_delay;

architecture rtl of edge_detect_delay is
   signal ff1 :std_logic := '0';                                -- first Flip-Flop
   signal ff2 :std_logic;                                       -- second Flip-Flop
   signal ff3 :std_logic;                                       -- third Flip-Flop
   signal ff4 :std_logic;                                       -- fourth Flip-Flop

begin
    p_edge_detect: process(clk,rst)   
    begin
        if rising_edge(clk) then    
            if rst='0' then
                ff1 <= '0';
                ff2 <= '0';
             else
                ff1 <= inp;                                         
                ff2 <= ff1;
				ff3 <= ff2;
				ff4 <= ff3;
            end if;
        end if;    
    end process;
    
    r_edge <= ff3 and (not ff4);                                -- rising edge detect pulse 
    f_edge <= ff3 nor (not ff4);                                -- falling edge detect pulse
 
end rtl;
