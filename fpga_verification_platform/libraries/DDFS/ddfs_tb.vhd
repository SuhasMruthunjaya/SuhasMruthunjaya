----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/15/2025 01:45:48 PM
-- Design Name: 
-- Module Name: ddfs_tb - behavourial
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

entity ddfs_tb is
--  Port ( );
end ddfs_tb;

architecture Behavourial of ddfs_tb is

     component ddfs is
            Port (
                clk :   in std_logic;
                rst_n : in std_logic;
                q :     out std_logic_vector( 15 downto 0)
            ); 
     end component;
     
     signal clk_tb : std_logic := '0';
     signal rst_n_tb : std_logic := '0';
     signal q_tb : std_logic_vector(15 downto 0) := (others => '0');

begin
    
    dut : ddfs
            port map ( clk => clk_tb, rst_n => rst_n_tb, q => q_tb );
            
    clk_tb   <= not clk_tb after 10ns;
    rst_n_tb <= '0' , '1' after  20ns;
    
  
end Behavourial;
