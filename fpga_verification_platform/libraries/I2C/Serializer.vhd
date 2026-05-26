----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 02/21/2025 04:41:51 PM
-- Design Name: 
-- Module Name: Synchronizer - rtl
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

entity Serializer is
  generic (
        DATA_WIDTH : integer := 7 -- Generic parameter for the input signal
        );
  Port ( 
         clk : in std_logic;
         rst_n : in std_logic;
         start : in std_logic;
         input_sig : in std_logic_vector(DATA_WIDTH-1  downto 0);
         output_sig : out std_logic;
         done : out std_logic
         );
end Serializer;

architecture rtl of Serializer is

signal count : integer := 0;

begin

process(clk, rst_n)
begin
    if rst_n = '0' then
        output_sig <= '0';
        done <= '0';
        count <= 0;
    elsif rising_edge(clk) then
--        output_sig <= input_sig(6 - count);
--        count <= count + 1;
--        if count >= 6 then
--            count <= 0;
--            done <= '1';
--        end if;
      if start = '1' then
        if count < DATA_WIDTH then
            output_sig <= input_sig(DATA_WIDTH-1 - count);
            count <= count + 1;
            if count = DATA_WIDTH - 1 then
                done <= '1';  -- Signal done after all bits are serialized
            else 
                done <= '0';
            end if;
        end if;
      elsif start = '0' then
        output_sig <= '0';
        done <= '0';
        count <= 0;
      end if;              
    end if;
end process;


end rtl;
