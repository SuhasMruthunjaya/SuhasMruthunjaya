----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 07/15/2025 01:08:47 PM
-- Design Name: 
-- Module Name: test_data_fsm_tb - Behavioral
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
use ieee.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity test_data_fsm_tb is
--  Port ( );
end test_data_fsm_tb;

architecture Behavioral of test_data_fsm_tb is

    component uart is
        generic (
            CLK_FREQ:    integer    := 125_000_000;
            BAUD_RATE:   integer    := 921_600;
            OS_RATE:     integer    := 16;       -- oversample rate
            D_WIDTH:     integer    := 8;
            PARITY:      integer    := 0;
            parity_eo:   std_logic  := '0'
        ); 
        port (
            clk:        in   std_logic;
            reset_n:    in   std_logic;
            tx_ena:     in   std_logic;
            tx_data:    in   std_logic_vector(D_WIDTH - 1 downto 0); 
            rx:         in   std_logic;
            rx_busy:    out  std_logic;
            rx_error:   out  std_logic;
            rx_data:    out  std_logic_vector(D_WIDTH - 1 downto 0);
            tx_busy:    out  std_logic;
            tx:         out  std_logic
        );
    end component;
    
    component test_data_fsm_sim_wrapper is
      port (
        clk_in : in STD_LOGIC;
        clk_125M : out STD_LOGIC_VECTOR(0 downto 0);
        clk_64M : out STD_LOGIC;
        pwm_uvw_top : out STD_LOGIC_VECTOR(2 downto 0);
        pwm_uvw_bot : out STD_LOGIC_VECTOR(2 downto 0);
        phu_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 );
        phv_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 );
        phw_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 );
        phx_data_ready_a1 : in STD_LOGIC;
        test_mode_active : in STD_LOGIC;
        ovc_release_a1 : in STD_LOGIC;
        ovc_event_a1   :out STD_LOGIC;
        ovc_status_a1   :out STD_LOGIC_VECTOR(5 downto 0);
        pl_uart_rx : in STD_LOGIC;
        pl_uart_tx : out STD_LOGIC;
        rst_n_in : in STD_LOGIC
      );
    end component;
    
    signal main_clk_125M_tb     : std_logic := '0';
    signal clk_125M_tb          : std_logic := '0';
    signal clk_64M_tb           : std_logic := '0';
    signal reset_n         : std_logic := '0';
    
    constant c_clkFreq    : integer := 64000000;                    --Freq in Hz
    constant c_clkPeriod  : time := (1000000000 ns/c_clkFreq);      --Clock Period
    constant c_clkHalfPer : time := (c_clkPeriod /2);               --Clock Half Period
    constant trigger_Freq : integer := 1000000;                     --Freq in Hz
    constant trigger_Period  : time := (1000000000 ns/trigger_Freq);--Clock Period
    constant trigger_HalfPer : time := (trigger_Period /2);         --Clock Half Period
    
    constant CLK_FREQ:  integer := 125_000_000;
    constant BAUD_RATE: integer := 921_600;
    constant OS_RATE:   integer := 16;
    constant D_WIDTH:   integer := 8;
    constant PARITY:    integer := 0;
    constant PARITY_EO: std_logic := '0';
    
    signal rx:          std_logic;
    signal tx:          std_logic;
    
    signal tx_ena_s:      std_logic := '0';
    signal tx_data_s:     std_logic_vector (D_WIDTH - 1 downto 0);
    signal rx_busy_s:     std_logic;
    signal rx_error_s:    std_logic;
    signal rx_data_s:     std_logic_vector (D_WIDTH - 1 downto 0);
    signal tx_busy_s:     std_logic;
    
    signal message:     string(1 to 8) := "phv_s_a1";
    signal message_change   : std_logic := '0';
    signal xmt_char:    character;
    signal rcv_char:    character;
    
    signal test_mode_active_tb : std_logic := '1';
    
    signal trigger_current_processing   : std_logic := '0';
    signal current_adc_spi              : std_logic_vector(35 downto 0) := x"800800800"; 
    signal ovc_release_a1               : std_logic := '0';
    signal ovc_event_a1                 : std_logic := '0';
    
    signal ovc_status_a1                : std_logic_vector(5 downto 0) := (others => '0');
    
    signal pwm_uvw_top_tb :  STD_LOGIC_VECTOR(2 downto 0);
    signal pwm_uvw_bot_tb :  STD_LOGIC_VECTOR(2 downto 0);
    
    type current_type is array(29 downto 0) of std_logic_vector(11 downto 0);
    signal current_U      : current_type := (x"F68", x"ee0" ,x"e58" ,x"dd0" ,x"d48" ,x"cc0", x"c38", x"bb0",x"b28",
                                             x"aa0", x"a18", x"990", x"908", x"880", x"7f8", x"770", x"6e8", x"660",x"5d8", x"550",
                                             x"4c8", x"440", x"3b8",x"330", x"2a8", x"220", x"198", x"110", x"088", x"000");
    signal current_V      : current_type := (x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"104", x"2ff",
                                             x"a64", x"a64", x"a64", x"9ff", x"9d1", x"dd1", x"feb", x"efb", x"a55", x"a55",
                                             x"a55", x"a55", x"a55", x"a55", x"a55", x"a55", x"dd1", x"9ff", x"9d1", x"800");
    signal current_W      : current_type := (x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"800", x"800",
                                             x"dd1", x"dd1", x"104", x"104", x"2ff", x"2ff", x"2ff", x"2ff", x"bbb", x"aaa",
                                             x"104", x"22f", x"9ff", x"aa5", x"aa5", x"feb", x"dd1", x"dd1", x"a55", x"800");

begin

reset:process
begin
    wait until rising_edge(clk_125M_tb);
    reset_n <= '1';
    wait;
end process;

clock125M:process
begin
    wait for 4 ns;
    main_clk_125M_tb <= not main_clk_125M_tb;
end process;

-- Current Sense trigger generator
trigg_proc: process
begin	
    trigger_current_processing <= '0';
    wait for trigger_Period;
    wait until rising_edge(clk_64M_tb);
    trigger_current_processing <= '1';
    wait until rising_edge(clk_64M_tb);
    trigger_current_processing <= '0';
end process;

-- adc value generator
adc_proc: process
begin	
    current_l: for k in 0 to current_U'length-1 loop
        wait until rising_edge(trigger_current_processing);
        current_adc_spi(11 downto 0) <= current_U(k);
        current_adc_spi(23 downto 12) <= current_V(k);
        current_adc_spi(35 downto 24) <= current_W(k);
    end loop current_l;    
end process;

---- OVC release generator
--ovc_release_proc: process(clk_64M_tb)
--begin
--    if rising_edge(clk_64M_tb) then
--        if (ovc_event_a1 = '1' and ovc_status_a1 = "000000") then
--            ovc_release_a1 <= '1';
--        else
--            ovc_release_a1 <= '0';
--        end if;
--    end if;
--end process;


DUT_FSM: test_data_fsm_sim_wrapper
      port map(
        clk_in              => main_clk_125M_tb,
        clk_125M(0)         => clk_125M_tb,
        clk_64M             => clk_64M_tb,
        test_mode_active    => '1',
        pwm_uvw_top         => pwm_uvw_top_tb,
        pwm_uvw_bot         => pwm_uvw_bot_tb,
        phu_adc_a1          => current_adc_spi(11 downto 0),
        phv_adc_a1          => current_adc_spi(23 downto 12),
        phw_adc_a1          => current_adc_spi(35 downto 24),
        phx_data_ready_a1   => trigger_current_processing,
        ovc_release_a1      => ovc_release_a1,
        ovc_event_a1        => ovc_event_a1,
        ovc_status_a1       => ovc_status_a1,
        pl_uart_rx          => rx,
        pl_uart_tx          => tx,
        rst_n_in            => reset_n
      );

STIMULI_UART_inst: uart 
        generic map (
            CLK_FREQ  => CLK_FREQ,
            BAUD_RATE => BAUD_RATE,
            OS_RATE   => OS_RATE,
            D_WIDTH   => D_WIDTH,
            PARITY    => PARITY,
            PARITY_EO => PARITY_EO
        )
        port map (
            clk      => clk_125M_tb,
            reset_n  => reset_n,
            tx_ena   => tx_ena_s,
            tx_data  => tx_data_s,
            rx       => tx,
            rx_busy  => rx_busy_s,
            rx_error => rx_error_s,
            rx_data  => rx_data_s,
            tx_busy  => tx_busy_s,
            tx       => rx
        );
        
STIMULI_COMMAND:
    process
    begin
        message <= "ovc_u_a1";
        wait for 80us;
        message <= "phv_s_a1";
        wait for 100us;
        wait for 900us;
        message <= "phw_s_a1";
        wait for 100us;
        wait for 900us;
    end process;        

STIMULI_TX_command: 
    process
    begin
        for i in 1 to message'length loop
            wait until tx_busy_s = '0';
            wait until rising_edge (clk_125M_tb);
            tx_data_s <= 
                std_logic_vector (
                    to_unsigned(character'pos(message(i)), tx_data_s'length)
                );
            xmt_char <= message(i);
            tx_ena_s <= '1';
            wait until rising_edge (clk_125M_tb);
            tx_ena_s <= '0';
        end loop;  
        wait for 30 us;
        for i in 1 to message'length loop
            wait until tx_busy_s = '0';
            wait until rising_edge (clk_125M_tb);
            tx_data_s <= 
                std_logic_vector (
                    to_unsigned(character'pos(message(i)), tx_data_s'length)
                );
            xmt_char <= message(i);
            tx_ena_s <= '1';
            wait until rising_edge (clk_125M_tb);
            tx_ena_s <= '0';
        end loop;  
    end process;  
STIMULI_RX:
    process
    begin
        wait until rx_busy_s = '1';
        for i in 1 to message'length loop
            wait until rx_busy_s = '0';
            wait until rising_edge (clk_125M_tb);
            rcv_char <= character'val (to_integer(unsigned(rx_data_s)));
        end loop; 
    end process;

end Behavioral;

