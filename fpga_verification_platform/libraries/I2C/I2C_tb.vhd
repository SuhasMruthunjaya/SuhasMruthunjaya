----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 02/20/2025 09:10:43 AM
-- Design Name: 
-- Module Name: I2C_tb - Behavioral
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

entity I2C_tb is
--  Port ( );
end I2C_tb;

architecture Behavioral of I2C_tb is

    component I2C is 
    Port ( 
    clk : in std_logic;
    rst_n : in std_logic;
    start_read_trigger : in std_logic;
    start_write_trigger : in std_logic;
    slave_address: in std_logic_vector (6 downto 0);
    reg_address: in std_logic_vector (15 downto 0);
    regSel : in std_logic;
    data : in std_logic_vector( 7 downto 0);
    stop_trigger : in std_logic;
    SCL_in_internal : in std_logic;
    SCL_out_internal : out std_logic;
    SCL_tristate : out std_logic;
    --SDA : inout std_logic;
    SDA_out_internal : out std_logic;
    SDA_in_internal : in std_logic;
    SDA_tristate : out std_logic;
    debug_port : out std_logic_vector( 15 downto 0)
    );
    end component;
    
    component slaveEmulator is
    Port(
    clk : in std_logic;
    rst_n : in std_logic;
    SCL_in : in std_logic;
    SDA_out : out std_logic;
    start_read_trigger : in std_logic;
    start_write_trigger : in std_logic;
    stop_trigger : in std_logic;
    debug_port : in std_logic_vector( 15 downto 0) := (others => '0')    
    );
    end component;
        
    signal clk_tb : std_logic := '1';
    signal rst_n_tb : std_logic := '0';
    signal start_read_trigger_tb : std_logic := '0';
    signal start_write_trigger_tb : std_logic := '0';
    signal slave_address_tb : std_logic_vector (6 downto 0) := (others => '0');
    signal reg_address_tb : std_logic_vector (15 downto 0) := (others => '0');
    --signal ack_tb: std_logic := '0';
    signal data_tb : std_logic_vector (7 downto 0) := (others => '0');
    signal stop_trigger_tb : std_logic := '0';
    signal regSel_tb : std_logic := '0';
    signal SCL_in_internal_tb : std_logic := 'Z';
    signal SCL_out_internal_tb : std_logic := 'Z';
    signal SCL_tristate_tb : std_logic := '0';
    signal SDA : std_logic;
    signal SDA_out_internal_tb : std_logic := 'Z';
    signal SDA_in_internal_tb : std_logic := 'Z';
    signal SDA_tristate_tb : std_logic := '0';
    signal debug_port_tb   : std_logic_vector(15 downto 0) := (others => '0');
    
    
begin

    clk_tb <= not clk_tb after 5ns;
    rst_n_tb <= '0' , '1' after 10ns;
    
    dut : I2C
    port map(
        clk => clk_tb,
        rst_n => rst_n_tb,
        start_read_trigger => start_read_trigger_tb,
        start_write_trigger => start_write_trigger_tb,
        slave_address => slave_address_tb,
        reg_address => reg_address_tb,
        regSel => regSel_tb,
        data => data_tb,
        stop_trigger => stop_trigger_tb,
        SCL_in_internal => SCL_in_internal_tb,
        SCL_out_internal => SCL_out_internal_tb,
        SCL_tristate => SCL_tristate_tb,
        --SDA : inout std_logic;
        SDA_out_internal => SDA_out_internal_tb,
        SDA_in_internal => SDA_in_internal_tb,
        SDA_tristate => SDA_tristate_tb,
        debug_port => debug_port_tb
        );
       
    uut : slaveEmulator
    port map(
         clk => clk_tb,
         rst_n => rst_n_tb,
         SCL_in => SCL_out_internal_tb,
         SDA_out => SDA_in_internal_tb,
        start_read_trigger => start_read_trigger_tb,
        start_write_trigger => start_write_trigger_tb,
        stop_trigger => stop_trigger_tb,
        debug_port => debug_port_tb         
        );
 
        SDA <= SDA_out_internal_tb when SDA_tristate_tb = '0' else 'Z';
        SDA_in_internal_tb <= SDA_out_internal_tb when SDA_tristate_tb = '0' else SDA; 
     
        
        --start_write_trigger_tb <= '1' after 16384ns;
        start_read_trigger_tb <= '1' after 200000ns, '0' after 200020ns;
        start_write_trigger_tb <= '1' after 40ns, '0' after 80ns;
        slave_address_tb <= "1010111";
        reg_address_tb <= x"A000";
        data_tb <= "10001000";
        stop_trigger_tb <= '1' after 149000ns , '0' after 149020ns;
        --start_read_trigger_tb <= '1' after 151300ns, '0' after 151320ns;
        --SDA_tb <= '1' after 46600ns, '0' after 49100ns, 'Z' after 68840ns;
        regSel_tb <= '1';
        
       -- start_read_trigger_tb <= '0' after 80ns;
        --SDA_tb <= '0' after 21380ns;
        
--    stimulus_stateMachine : process(slave_address_tb)
--    begin
--        slave_address_tb <= 0x5A after 50ns;
--    end process;

end Behavioral;
