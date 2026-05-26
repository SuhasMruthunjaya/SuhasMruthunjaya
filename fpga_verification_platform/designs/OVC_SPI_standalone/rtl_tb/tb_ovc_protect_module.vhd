----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 18.09.2023 13:04:03
-- Design Name: 
-- Module Name: tb_ovc_protect_module - Behavioral
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
USE ieee.std_logic_arith.all;                                                                                                         
USE ieee.std_logic_unsigned.all;                                                                                                      
USE ieee.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity tb_ovc_protect_module is
--  Port ( );
end tb_ovc_protect_module;

architecture Behavioral of tb_ovc_protect_module is

component ovc_protect_module is
    port 
        ( 
            clk             : in std_logic;
            reset_n         : in std_logic;
            ovc_low_limit   : in std_logic_vector(11 downto 0);
            ovc_high_limit  : in std_logic_vector(11 downto 0);
            current_offset  : in std_logic_vector(11 downto 0);
            ovc_time        : in std_logic_vector(11 downto 0);
            sc_off          : in std_logic;
            trigger_ovc     : in std_logic;
            current_raw_adc : in std_logic_vector(35 downto 0);
            status          : out std_logic_vector(5 downto 0);     -- [0:1] -> U, [2:3] -> V, [4:5] -> W (overcurrent and short-circuit)
            ovc_event       : out std_logic;
            ovc_release     : in std_logic
        );
end component;

component pwm_off is
    port ( 
        clk                 : in  std_logic;
        reset_n             : in  std_logic;
        error_1             : in  std_logic;
        error_2             : in  std_logic;
        error_3             : in  std_logic;
        error_4             : in  std_logic;
		error_5				: in  std_logic;
        pwm_uvw_high_in     : in  std_logic_vector(2 downto 0);
        pwm_uvw_low_in      : in  std_logic_vector(2 downto 0);
        pwm_uvw_high_out    : out std_logic_vector(2 downto 0);
        pwm_uvw_low_out     : out std_logic_vector(2 downto 0)
    );   
end component;     

-- Signals Declarations --------------------------------------------------------
signal clk                  : std_logic := '0';
signal rst                  : std_logic := '0';
signal trigger_ovc_tb       : std_logic := '0';   
signal trigger_ovc_tb_sync  : std_logic := '0';
signal current_adc_spi      : std_logic_vector(35 downto 0) := x"800800800";  
signal current_adc_spi_i    : std_logic_vector(35 downto 0) := (others => '0');   
signal ovc_low_limit_p      : std_logic_vector(11 downto 0) := x"dd1"; 
signal ovc_low_limit_n      : std_logic_vector(11 downto 0) := x"22f"; 
signal ovc_high_limit_p     : std_logic_vector(11 downto 0) := x"efb"; 
signal ovc_high_limit_n     : std_logic_vector(11 downto 0) := x"105"; 
signal ovc_high_limit_tb    : std_logic_vector(11 downto 0) := x"6fb"; 
signal ovc_time_tb          : std_logic_vector(11 downto 0) := x"280"; 
signal sc_off_tb            : std_logic := '0';

-- pwm signals
signal task_overflow_current_control_A  : std_logic := '0';
signal watchdog_error_core0             : std_logic := '0';
signal watchdog_error_core1             : std_logic := '0';
signal pwm_uvw_high                     : std_logic_vector(2 downto 0) := (others => '0');
signal pwm_uvw_low                      : std_logic_vector(2 downto 0) := (others => '0');
signal GATE_UVW_1                       : std_logic_vector(2 downto 0) := (others => '0');
signal GATE_UVW_2                       : std_logic_vector(2 downto 0) := (others => '0');

signal status_tb        : std_logic_vector(5 downto 0) := (others => '0');
signal ovc_event_tb     : std_logic := '0';   
signal ovc_release_tb   : std_logic := '0';  
--------------------------------------------------------------------------------
-- Constants Declaration
--------------------------------------------------------------------------------
-- Clock
constant c_clkFreq    : integer := 64000000;                    --Freq in Hz
constant c_clkPeriod  : time := (1000000000 ns/c_clkFreq);      --Clock Period
constant c_clkHalfPer : time := (c_clkPeriod /2);               --Clock Half Period
constant trigger_Freq : integer := 1000000;                     --Freq in Hz
constant trigger_Period  : time := (1000000000 ns/trigger_Freq);--Clock Period
constant trigger_HalfPer : time := (trigger_Period /2);         --Clock Half Period
constant c_PWMFreq    : integer := 16000;                       --PWM Frequency 
constant c_sync_period: time := (1000000000 ns /c_PWMFreq);     --synchronization period for PWM

type current_type is array(29 downto 0) of std_logic_vector(11 downto 0);
signal current_U      : current_type := (x"104", x"f98" ,x"f98" ,x"f98" ,x"f98" ,x"f98", x"f98", x"f98",x"f98",
                                         x"f98", x"f98", x"efb", x"dff", x"a64", x"a64", x"a64", x"a64", x"9ff",x"9d1", x"dd1",
                                         x"dd1", x"dd1", x"dd1",x"dd1", x"dd1", x"a64", x"a64", x"9ff", x"9d1", x"800");
signal current_V      : current_type := (x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"104", x"2ff",
                                         x"a64", x"a64", x"a64", x"9ff", x"9d1", x"dd1", x"feb", x"efb", x"a55", x"a55",
                                         x"a55", x"a55", x"a55", x"a55", x"a55", x"a55", x"dd1", x"9ff", x"9d1", x"800");
signal current_W      : current_type := (x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"800",
                                         x"dd1", x"dd1", x"104", x"104", x"2ff", x"2ff", x"2ff", x"2ff", x"bbb", x"aaa",
                                         x"104", x"22f", x"9ff", x"aa5", x"aa5", x"feb", x"dd1", x"dd1", x"a55", x"800");

begin

ovc_module_i: ovc_protect_module
port map (
    clk             => clk,
    reset_n         => rst,
    ovc_low_limit   => x"650",
    ovc_high_limit  => x"7CE",
    current_offset  => x"800",
    ovc_time        => ovc_time_tb,
    sc_off          => sc_off_tb,
    trigger_ovc     => trigger_ovc_tb_sync,
    current_raw_adc => current_adc_spi,
    status          => status_tb,
    ovc_event       => ovc_event_tb,
    ovc_release     => ovc_release_tb
);    

pwm_off_i: pwm_off
port map (
    clk                 => clk,
    reset_n             => rst,  
    error_1             => ovc_event_tb,
    error_2             => watchdog_error_core0,
    error_3             => watchdog_error_core1,
    error_4             => task_overflow_current_control_A,
	error_5				=> '0',
    pwm_uvw_high_in     => pwm_uvw_high,
    pwm_uvw_low_in      => pwm_uvw_low,
    pwm_uvw_high_out    => GATE_UVW_1,
    pwm_uvw_low_out     => GATE_UVW_2
);  

-- trigger generator
trigg_proc: process
begin	
    trigger_ovc_tb <= '0';
    wait for trigger_HalfPer;
    trigger_ovc_tb <= '1';
    wait for c_clkPeriod;
    trigger_ovc_tb <= '0';
    wait for trigger_HalfPer;
end process;

trigger_ovc_tb_sync <= trigger_ovc_tb after c_clkPeriod;

-- adc value generator
adc_proc: process
begin	
    current_l: for k in 0 to current_U'length-1 loop
        wait until rising_edge(trigger_ovc_tb);
        current_adc_spi(11 downto 0) <= current_U(k);
        current_adc_spi(23 downto 12) <= current_V(k);
        current_adc_spi(35 downto 24) <= current_W(k);
    end loop current_l;    
end process;

-- event and release process
r5_proc: process
begin
    wait until rising_edge(trigger_ovc_tb_sync);
    if ovc_event_tb ='1' and current_adc_spi(11 downto 0) <= ovc_low_limit_p and
       current_adc_spi(11 downto 0) >= ovc_low_limit_n and
       current_adc_spi(23 downto 12) <= ovc_low_limit_p and
       current_adc_spi(23 downto 12) >= ovc_low_limit_n and
       current_adc_spi(35 downto 24) <= ovc_low_limit_p and
       current_adc_spi(35 downto 24) >= ovc_low_limit_n and
       status_tb = "000000" then
        ovc_release_tb <= '1';
    else
        ovc_release_tb <= '0';
    end if;              
       
end process;
--------------------------------------------------------------------------------
-- clock
--------------------------------------------------------------------------------
clock:process
begin	
    clk <= '0';
    wait for c_clkHalfPer;
    clk <= '1';
    wait for c_clkHalfPer;
end process;

--------------------------------------------------------------------------------
-- pwm generator
--------------------------------------------------------------------------------
process
begin
    pwm_uvw_high <= "111";
    pwm_uvw_low  <= "000";
    wait for (c_sync_period/2);
    pwm_uvw_high <= "000";
    pwm_uvw_low  <= "111";
    wait for (c_sync_period/2);
end process;

rst <= '1';
sc_off_tb <= '1';

error_proc: process
begin
    wait for 55us;
    watchdog_error_core0 <= '1';
    wait for 5us; 
    watchdog_error_core0 <= '0';
    wait for 25us;
    watchdog_error_core1 <= '1';
    wait for 5us; 
    watchdog_error_core1 <= '0';
    wait for 10us;
    task_overflow_current_control_A <= '1';
    wait for 5us; 
    task_overflow_current_control_A <= '0';    
end process;


end Behavioral;
