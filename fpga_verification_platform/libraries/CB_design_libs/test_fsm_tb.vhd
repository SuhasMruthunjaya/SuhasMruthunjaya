----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06/17/2025 01:30:05 PM
-- Design Name: 
-- Module Name: test_fsm_tb - Behavioral
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


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity test_fsm_tb is
--  Port ( );
end test_fsm_tb;

architecture Behavioral of test_fsm_tb is

    component uart is
        generic (
            CLK_FREQ:    integer    := 125_000_000;
            BAUD_RATE:   integer    := 115_200;
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
    
    component test_data_fsm is
    generic(
        N_BYTES_COMMAND     : integer := 8;                     -- Number of Bytes for input command
        N_BYTES_SEND        : integer := 2                      -- Number of Bytes for send data
    );
    port(
        clk_125M_i          : in  std_logic;
        clk_64M_i           : in  std_logic;
        rst_n_i             : in  std_logic;    
        test_mode_active_i  : in  std_logic;
        -------- INPUTS -------- 
        -- UART 
        uart_rx_busy_i      : in  std_logic;                    -- UART Receive in progress
        uart_rx_error_i     : in  std_logic;                    -- UART start, parity, or stop bit error detected
        uart_rx_data_i      : in  std_logic_vector(7 downto 0); -- UART Received Byte
        uart_tx_busy_i      : in  std_logic;                    -- UART Transmit in progress
        -- Phase Current 
        phx_data_ready_a1_i : in  std_logic;                    -- trigger_current_processing, ADC SPI transmission done Axis 1
        phu_adc_a1_i        : in  std_logic_vector(11 downto 0);-- Phase Current value Axis 1 Phase U   
        phv_adc_a1_i        : in  std_logic_vector(11 downto 0);-- Phase Current value Axis 1 Phase V  
        phw_adc_a1_i        : in  std_logic_vector(11 downto 0);-- Phase Current value Axis 1 Phase W    
        phx_data_ready_a2_i : in  std_logic;                    -- trigger_current_processing, ADC SPI transmission done Axis 2
        phu_adc_a2_i        : in  std_logic_vector(11 downto 0);-- Phase Current value Axis 2 Phase U    
        phv_adc_a2_i        : in  std_logic_vector(11 downto 0);-- Phase Current value Axis 2 Phase V  
        phw_adc_a2_i        : in  std_logic_vector(11 downto 0);-- Phase Current value Axis 2 Phase W  
        -- OVC Module
        ovc_status_a1_i     : in  std_logic_vector(5 downto 0); -- Overcurrent Protection Status Bits Axis 1
        ovc_event_a1_i      : in  std_logic;                    -- Overcurrent Error Detection Axis 1
        ovc_status_a2_i     : in  std_logic_vector(5 downto 0); -- Overcurrent Protection Status Bits Axis 2        
        ovc_event_a2_i      : in  std_logic;                    -- Overcurrent Error Detection Axis 2
        -- FIFO
        fifo_full_i         : in  std_logic;                    -- Indication that fifo is filled 
        fifo_empty_i        : in  std_logic;                    -- Indication that fifo is empty
        fifo_data_out_i     : in  std_logic_vector(7 downto 0); -- FIFO data to read 
        -------- OUTPUTS -------- 
        -- FIFO
        fifo_wr_en_o        : out std_logic;                    -- Trigger Pulse to initiate FIFO write
        fifo_data_in_o      : out std_logic_vector(15 downto 0);-- FIFO data to write
        fifo_rd_en_o        : out std_logic;                    -- Trigger Pulse to initiate FIFO read
        -- UART
        uart_tx_trigger_o   : out std_logic;                    -- Trigger Pulse to initiate UART Transmission
        uart_tx_data_o      : out std_logic_vector(7 downto 0)  -- UART Transmit Byte                
    );
    end component;
    
    signal clk_125M_tb     : std_logic := '0';
    signal clk_64M_tb      : std_logic := '0';
    signal reset_n         : std_logic := '0';
    
    constant c_clkFreq    : integer := 64000000;                    --Freq in Hz
    constant c_clkPeriod  : time := (1000000000 ns/c_clkFreq);      --Clock Period
    constant c_clkHalfPer : time := (c_clkPeriod /2);               --Clock Half Period
    constant trigger_Freq : integer := 1000000;                     --Freq in Hz
    constant trigger_Period  : time := (1000000000 ns/trigger_Freq);--Clock Period
    constant trigger_HalfPer : time := (trigger_Period /2);         --Clock Half Period
    
    constant CLK_FREQ:  integer := 125_000_000;
    constant BAUD_RATE: integer := 115_200;
    constant OS_RATE:   integer := 16;
    constant D_WIDTH:   integer := 8;
    constant PARITY:    integer := 0;
    constant PARITY_EO: std_logic := '0';
    
    signal tx_ena:      std_logic := '0';
    signal tx_data:     std_logic_vector (D_WIDTH - 1 downto 0);
    signal rx:          std_logic;
    signal rx_busy:     std_logic;
    signal rx_error:    std_logic;
    signal rx_data:     std_logic_vector (D_WIDTH - 1 downto 0);
    signal tx_busy:     std_logic;
    signal tx:          std_logic;
    
    signal tx_ena_s:      std_logic := '0';
    signal tx_data_s:     std_logic_vector (D_WIDTH - 1 downto 0);
    signal rx_busy_s:     std_logic;
    signal rx_error_s:    std_logic;
    signal rx_data_s:     std_logic_vector (D_WIDTH - 1 downto 0);
    signal tx_busy_s:     std_logic;
    
    signal message:     string(1 to 8) := "ovc_u_a1";
    signal message_change   : std_logic := '0';
    signal xmt_char:    character;
    signal rcv_char:    character;
    
    signal test_mode_active_tb : std_logic := '1';
    
    signal trigger_current_processing   : std_logic := '0';
    signal current_adc_spi              : std_logic_vector(35 downto 0) := x"800800800"; 
    
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

reset:process
begin
    wait until rising_edge(clk_125M_tb);
    reset_n <= '1';
    wait;
end process;

clock64M:process
begin	
    clk_64M_tb <= '0';
    wait for c_clkHalfPer;
    clk_64M_tb <= '1';
    wait for c_clkHalfPer;
end process;

clock125M:process
begin
    wait for 4 ns;
    clk_125M_tb <= not clk_125M_tb;
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

DUT_UART_inst: uart 
        generic map (
            CLK_FREQ  => CLK_FREQ,
            BAUD_RATE => BAUD_RATE,
            OS_RATE   => OS_RATE,
            D_WIDTH   => D_WIDTH,
            PARITY    => PARITY,
            PARITy_EO => PARITY_EO
        )
        port map (
            clk      => clk_125M_tb,
            reset_n  => reset_n,
            tx_ena   => tx_ena,
            tx_data  => tx_data,
            rx       => rx,
            rx_busy  => rx_busy,
            rx_error => rx_error,
            rx_data  => rx_data,
            tx_busy  => tx_busy,
            tx       => tx
        );
        
STIMULI_UART_inst: uart 
        generic map (
            CLK_FREQ  => CLK_FREQ,
            BAUD_RATE => BAUD_RATE,
            OS_RATE   => OS_RATE,
            D_WIDTH   => D_WIDTH,
            PARITY    => PARITY,
            PARITy_EO => PARITY_EO
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

DUT_TEST_FSM_inst: test_data_fsm
    generic map(
        N_BYTES_COMMAND     => 8,
        N_BYTES_SEND        => 2
    )
    port map(
        clk_125M_i          => clk_125M_tb,
        clk_64M_i           => clk_64M_tb,
        rst_n_i             => reset_n,   
        test_mode_active_i  => '1',
        -------- INPUTS -------- 
        -- UART 
        uart_rx_busy_i      => rx_busy,
        uart_rx_error_i     => rx_error,
        uart_rx_data_i      => rx_data,
        uart_tx_busy_i      => tx_busy,
        -- Phase Current 
        phx_data_ready_a1_i => trigger_current_processing,
        phu_adc_a1_i        => current_adc_spi(11 downto 0),   
        phv_adc_a1_i        => current_adc_spi(23 downto 12),
        phw_adc_a1_i        => current_adc_spi(35 downto 24),
        phx_data_ready_a2_i => trigger_current_processing,
        phu_adc_a2_i        => x"800",    
        phv_adc_a2_i        => x"800",  
        phw_adc_a2_i        => x"800",   
        -- OVC Module
        ovc_status_a1_i     => b"000000",
        ovc_event_a1_i      => '0',
        ovc_status_a2_i     => b"000000",       
        ovc_event_a2_i      => '0',
        -- FIFO
        fifo_full_i         => '0',
        fifo_empty_i        => '0',
        fifo_data_out_i     => x"00",
        -------- OUTPUTS -------- 
        fifo_wr_en_o        => open,
        fifo_data_in_o      => open,
        fifo_rd_en_o        => open,
        -- UART
        uart_tx_trigger_o   => tx_ena,
        uart_tx_data_o      => tx_data                
    );
    
STIMULI_COMMAND:
    process
    begin
        message <= "ovc_u_a1";
        message_change <= '1';
        wait for 100us;
        message_change <= '0';
        wait for 900us;
        message <= "phv_s_a1";
        message_change <= '1';
        wait for 100us;
        message_change <= '0';
        wait for 900us;
        message <= "phw_s_a1";
        message_change <= '1';
        wait for 100us;
        message_change <= '0';
        wait for 900us;
    end process;        

STIMULI_TX: 
    process
    begin
        wait until message_change = '1';
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
