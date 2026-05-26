----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379) 
-- 
-- Create Date: 02/24/2025 11:09:35 AM
-- Design Name: 
-- Module Name: serializer_tb - Behavioral
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

entity serializer_tb is
--  Port ( );
end serializer_tb;

architecture Behavioral of serializer_tb is
    signal clk : std_logic := '0';
    signal rst_n : std_logic := '1';
    signal input_sig : std_logic_vector(6 downto 0) := "1010101";
    signal output_sig : std_logic;
    signal done : std_logic;

    constant clk_period : time := 10 ns;
begin
     -- Instantiate the Serializer
    uut: entity work.Serializer
        port map (
            clk => clk,
            rst_n => rst_n,
            input_sig => input_sig,
            output_sig => output_sig,
            done => done
        );

    -- Clock generation
    clk_process : process
    begin
        while true loop
            clk <= '0';
            wait for clk_period/2;
            clk <= '1';
            wait for clk_period/2;
        end loop;
    end process;

    -- Stimulus process
    stim_process: process
    begin
        -- Reset the design
        rst_n <= '1';
        wait for 20 ns;
        rst_n <= '0';
        
        -- Wait for serialization
        wait for 100 ns;

        -- Finish simulation
        assert false report "End of simulation" severity note;
        wait;
    end process;

end Behavioral;
