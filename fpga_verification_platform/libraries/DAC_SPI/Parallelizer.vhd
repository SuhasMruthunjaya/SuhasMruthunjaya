----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 04/17/2025 01:21:21 PM
-- Design Name: 
-- Module Name: Parallelizer - rtl
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

entity Parallelizer is
  GENERIC (
                  DATA_WIDTH : integer := 7 -- Generic parameter for the input signal
          );
  Port (
                  clk       : IN std_logic;
                  rst_n     : IN std_logic;
                  data_in   : IN std_logic;
                  data_out  : OUT std_logic_vector(DATA_WIDTH-1 downto 0);
                  start     : IN std_logic
       );
end Parallelizer;

architecture rtl of Parallelizer is
      
      signal count      : integer := 0;
      signal int_sig    : std_logic_vector(DATA_WIDTH-1 downto 0) := (others =>'0');
      
begin

  data_out <= int_sig;

  parallelizer : process(clk,rst_n) 
  begin        
       if rising_edge(clk) then
            if rst_n = '0' then
                --data_out <= (others => '0');
                int_sig  <= (others => '0');
            else
                if start = '1' then
                     if count < DATA_WIDTH then
                        int_sig(DATA_WIDTH-1 - count) <= data_in;
                        count <= count + 1;
                        if count = DATA_WIDTH - 1 then
                            count <= 0;
                        end if;
                    end if;
                elsif start = '0' then
                     count <= 0;
                     int_sig <= (others => '0');
                end if;
            end if;
       end if;   
  end process parallelizer;

end rtl;
