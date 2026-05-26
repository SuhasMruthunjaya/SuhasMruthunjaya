----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 05/14/2025 02:28:46 PM
-- Design Name: 
-- Module Name: time_base_gen - RTL
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
use IEEE.numeric_std.ALL;
use work.math_utils.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity time_base_gen is
 generic(
            parameter : in integer := 187
        );
 Port ( 
        clk :           in std_logic;
        rst_n :         in std_logic;
        q_out :         out std_logic;
        ddfs_start :    in std_logic
       );
end time_base_gen;

architecture RTL of time_base_gen is    
    
    constant bitwidth : natural := clog2(parameter);
    signal time_base : unsigned(bitwidth-1 downto 0) := (others => '0');   
    
begin
    
    q_out <= '1' when time_base = parameter - 1 else '0';
    
    time_base_counter : process(clk, rst_n)
    begin
        if rising_edge(clk) then
            if rst_n = '0' then
                time_base <= (others => '0');
            else
                if ddfs_start = '1' then
                    if time_base = parameter - 1 then
                        time_base <= (others => '0');
                    else
                        time_base <= time_base + "1";
                    end if;
                end if;
            end if;
        end if;       
    end process time_base_counter;
    
end RTL;
