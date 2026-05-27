----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 13.02.2023 16:06:13
-- Design Name: 
-- Module Name: duty_cycle - rtl
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
use ieee.numeric_std.all;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity duty_cycle is
port (  clk             : in std_logic;
        rst             : in std_logic;
        cnt_f           : in std_logic_vector(15 downto 0);
        duty            : in std_logic_vector(15 downto 0);
        PWM_OUT         : out std_logic
      );
end duty_cycle;

architecture rtl of duty_cycle is
begin
    DT : process(clk, rst)
    begin
        if rst = '1' then
            PWM_OUT <= '0';
        elsif clk'EVENT AND clk = '1' then
            if duty = X"8000" then
                PWM_OUT <= '1'; 
            else    
                if cnt_f < duty  then  
                    PWM_OUT <= '1';
                else 
                    PWM_OUT <= '0';      
                end if;                     
            end if;                             
        end if;    
    end process DT;     
end rtl;
