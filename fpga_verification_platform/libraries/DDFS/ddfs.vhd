----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 05/15/2025 11:58:14 AM
-- Design Name: 
-- Module Name: ddfs - rtl
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

entity ddfs is
  Port (
         clk :   in std_logic;
         rst_n : in std_logic;
         q :     out std_logic_vector( 15 downto 0);
         start : in std_logic;
         trigger_pulse : out std_logic
       );
end ddfs;

architecture rtl of ddfs is
        component time_base_gen 
        generic (
            parameter : in integer := 196
         );
        port ( 
            clk :           in std_logic;
            rst_n :         in std_logic;
            q_out :         out std_logic;
            ddfs_start :    in std_logic
        );
        end component;
        
        component phase_acc
        Port ( 
         clk :          in std_logic;
         rst_n :        in std_logic;
         enable :       in std_logic;
         ftw :          in std_logic_vector(15 downto 0);
         q :            out std_logic_vector( 9 downto 0)
         );
        end component;
        
        component sine_wave_lut
        Port (
        address : in  std_logic_vector(9 downto 0);
        q       : out std_logic_vector(15 downto 0)
        );
        end component;
        
        signal enable : std_logic := '0';
        signal lut_address : std_logic_vector(9 downto 0) := (others => '0');
begin
    
    time_base_inst : time_base_gen generic map ( parameter => 187) port map ( clk => clk, rst_n => rst_n, q_out => enable, ddfs_start => start);
    phase_acc_inst : phase_acc port map ( clk => clk , rst_n => rst_n, enable => enable, ftw => "0000000000000001", q => lut_address);
    sine_wave_inst : sine_wave_lut port map ( address => lut_address, q => q);
    
    trigger_pulse <= enable;
    

end rtl;
