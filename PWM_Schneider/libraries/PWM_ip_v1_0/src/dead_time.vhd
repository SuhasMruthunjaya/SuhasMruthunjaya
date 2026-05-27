----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 17.11.2022 08:37:43
-- Design Name: 
-- Module Name: dead_time - Behavioral
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


LIBRARY ieee;
USE ieee.std_logic_1164.all;
use IEEE.NUMERIC_STD.ALL;


-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity dead_time is
    Port ( rst      : in    std_logic;
           clk      : in    std_logic;
           pwm_in   : in    std_logic;
           pwm_out  : out   std_logic;
           tdead    : in    std_logic_vector(15 downto 0)         -- dynamic dead time setting -> number of clock cycles 
          );
end dead_time;

architecture rtl of dead_time is
   
   component edge_detect is
      Port (    rst     : in      std_logic;       
                clk     : in      std_logic;       
                inp     : in      std_logic;       -- input signal
                r_edge  : out     std_logic;       -- rising edge detect output
                f_edge  : out     std_logic);      -- falling edge detect output
   end component;
   
   signal delay     : unsigned (15 downto 0) := X"0000";
   signal redge     : std_logic;
   signal fedge     : std_logic;
   signal td        : unsigned (15 downto 0) := X"0000";
      
begin
   ed: edge_detect PORT MAP( rst => rst, clk => clk, inp => pwm_in, r_edge => redge, f_edge => fedge);
   p_deat_time: process(rst,clk)
   begin
      if rst='1' then
            pwm_out <= '0';
            delay <= X"0000";  
      elsif rising_edge(clk) then
        if fedge='1' then                           -- falling edge        
            pwm_out <= '0';                         -- immediatelly switcht output to low
            delay <= X"0000";                       -- reset delay counter
        elsif pwm_in='1' then                       -- PWM input high?
            if (delay <= td) then                   -- counter overflow?
                delay <= delay + 1;                 -- NO: wait for delay
            else                          
                pwm_out  <= '1';                    -- YES: switch output to high
            end if;     
        end if;
      end if;
   end process;
   
   p_dt: process(tdead)
   begin
      if unsigned(tdead) < X"000A" then
        td <= X"000A";
      else
        td <= unsigned(tdead);  
      end if;
   end process;
end rtl;