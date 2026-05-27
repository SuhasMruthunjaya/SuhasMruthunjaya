----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.02.2023 11:29:11
-- Design Name: 
-- Module Name: pwm_carrier - rtl
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

entity pwm_carrier is
port (  clk             : in std_logic;
        rst             : in std_logic;
        frequency       : in std_logic_vector (31 downto 0);
        updn            : out std_logic;
        cnt_f           : out std_logic_vector (31 downto 0)              
    );
end pwm_carrier;

architecture rtl of pwm_carrier is
signal freq         : unsigned(31 downto 0) := (others => '0');
signal cnt          : unsigned(31 downto 0) := (others => '0');
signal updown       : std_logic := '0';

begin
    CNT_P : process(clk, rst)
    begin
        if rst = '1' then
            cnt <= (others => '0');
            updown <= '0'; 
        elsif rising_edge(clk) then
            case updown is
            when '0' => 
                cnt <= cnt + freq; 
                if cnt = 0 then
                    freq <= unsigned(frequency);
                end if;                                 
                if cnt >= (2147483647 - freq) then
                    updown <= '1';
                end if;                
            when '1' =>
                cnt <= cnt - freq; 
                if cnt <= freq then
                    updown <= '0';
                    freq <= unsigned(frequency);
                end if;                  
             when others =>   
                cnt <= (others => '0');
                updown <= '0';                                               
            end case;  
        end if;
     end process CNT_P;
     updn <= updown;
     cnt_f <= std_logic_vector(cnt);    
end rtl;
