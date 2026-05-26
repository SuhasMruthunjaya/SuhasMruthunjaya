----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya  
-- 
-- Create Date: 04/03/2025 01:55:05 PM
-- Design Name: 
-- Module Name: SPI_master_tb - Behavioral
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

entity SPI_master_tb is
--  Port ( );
end SPI_master_tb;

architecture Behavioral of SPI_master_tb is

    component SPI_master is 
     generic (
            N_databits       : integer := 24
          );
         
     Port ( 
         clk                    : in  std_logic;
         rst_n                  : in  std_logic;
         MOSI                   : out std_logic;
         MISO                   : in  std_logic;
         SCLK                   : out std_logic;
         divider                : in  std_logic_vector(7 downto 0);
         cpol                   : in  std_logic;
         CS_n                   : out std_logic;
         start_trigger          : in  std_logic;
         data_out               : out std_logic_vector(N_databits-1 downto 0);
         data_in                : in  std_logic_vector(N_databits-1 downto 0);
         
         -- for debugging purposes
         debug_port             : out std_logic_vector( 3 downto 0) := (others => '0') 
        );
    end component;
    
    
    signal clk_tb                   :  std_logic                       := '1';                                      
    signal rst_n_tb                 :  std_logic                       := '0';                                      
    signal MOSI_tb                  :  std_logic                       := 'Z';                                      
    signal MISO_tb                  :  std_logic                       := 'Z';                                      
    signal SCLK_tb                  :  std_logic                       := '0';                                      
    signal CS_n_tb                  :  std_logic                       := '1';                                      
    signal data_out_tb              :  std_logic_vector(23 downto 0)   := (others => '0');        
    signal data_in_tb               :  std_logic_vector(23 downto 0)   := (others => '0');
    signal start_trigger_tb         :  std_logic                       := '0';                                        
    signal start_write_trigger_tb   :  std_logic                       := '0';
    signal divider_tb               :  std_logic_vector(7 downto 0)    := (others => '0');
    signal cpol_tb                  :  std_logic                       := '0';
    signal debug_port_tb            :  std_logic_vector( 3 downto 0)   := (others => '0');

begin

    clk_tb   <= not clk_tb after 7.8125ns;
    rst_n_tb <= '0' , '1' after 15.625ns;
    --cs_n_tb  <= '0' after 60ns, '1' after 480ns;
    start_trigger_tb <= '1' after 80ns, '0' after 100ns, '1' after 1796.990ns, '0' after 1816.990ns;
    data_in_tb  <= '0' & "000" & "1000" & x"FFFF";
    divider_tb <= x"01";
    cpol_tb <= '0';
    MISO_tb <= '0' after 10ns, '1' after 421.902ns, '0' after 484.406ns, '1' after 859.430ns, '0' after 984.438ns, '1' after 1046.942ns, '0' after 1109.446ns, '1' after 1296.958ns, '0' after 1359.462ns, '1' after 1421.966ns, '0' after 1484.470ns, '1' after 1546.974ns, '0' after 1671.982ns, '1' after 2765.802ns, '0' after 2828.306ns;
    
    dut : SPI_master
        generic map (
            N_databits => 24
        )
        port map (
            clk                        =>   clk_tb,   
            rst_n                      =>   rst_n_tb,
            MOSI                       =>   MOSI_tb,
            MISO                       =>   MISO_tb,
            SCLK                       =>   SCLK_tb,
            divider                    =>   divider_tb,
            cpol                       =>   cpol_tb,
            CS_n                       =>   CS_n_tb,
            start_trigger              =>   start_trigger_tb,
            data_out                   =>   data_out_tb,
            data_in                    =>   data_in_tb,
            debug_port                 =>   debug_port_tb
        );    
            
end Behavioral;
