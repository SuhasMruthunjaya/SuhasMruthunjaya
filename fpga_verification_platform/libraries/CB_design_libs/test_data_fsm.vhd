----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06/11/2025 01:22:36 PM
-- Design Name: 
-- Module Name: test_data_fsm - rtl
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

library work;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity test_data_fsm is
    generic(
        N_BYTES_COMMAND     : integer := 8;                     -- Number of Bytes for input command
        N_BYTES_SEND        : integer := 2;                     -- Number of Bytes for send data
        N_BYTES_FIFO        : integer := 4096                   -- Number of Bytes for FIFO transmission
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
        -- PWM Module
        pwm_enable_a1_o     : out std_logic;                    -- PWM IP enable output Axis 1
        pwm_freq_a1_o       : out std_logic_vector(12 downto 0);-- PWM IP period compare value -> pwm frequency Axis 1
        pwm_duty_a1_o       : out std_logic_vector(38 downto 0);-- PWM IP duty compare value -> pwm duty cycle Axis 1
        pwm_enable_a2_o     : out std_logic;                    -- PWM IP enable output Axis 2
        pwm_freq_a2_o       : out std_logic_vector(12 downto 0);-- PWM IP period compare value -> pwm frequency Axis 2
        pwm_duty_a2_o       : out std_logic_vector(38 downto 0);-- PWM IP duty compare value -> pwm duty cycle Axis 2
        -- OVC Module
        ovc_release_a1_o    : out std_logic;
        ovc_release_a2_o    : out std_logic;
        -- FIFO
        fifo_wr_en_o        : out std_logic;                    -- Trigger Pulse to initiate FIFO write
        fifo_data_in_o      : out std_logic_vector(15 downto 0);-- FIFO data to write
        fifo_rd_en_o        : out std_logic;                    -- Trigger Pulse to initiate FIFO read
        -- UART
        uart_tx_trigger_o   : out std_logic;                    -- Trigger Pulse to initiate UART Transmission for static test
        uart_tx_data_o      : out std_logic_vector(7 downto 0)  -- UART Transmit Byte for static test
  
    );
end test_data_fsm;

architecture rtl of test_data_fsm is
    
------------------------------------------------------------------------------
--  Component Declaration
------------------------------------------------------------------------------    
    component edge_detect is
      Port (    rst     : in      std_logic;       
                clk     : in      std_logic;       
                inp     : in      std_logic;       -- input signal
                r_edge  : out     std_logic;       -- rising edge detect output
                f_edge  : out     std_logic);      -- falling edge detect output
    end component;
    
    component xpm_cdc_array_single is
        generic (
            DEST_SYNC_FF   : integer range 2 to 10; -- DECIMAL; range: 2-10
            INIT_SYNC_FF   : std_logic;             -- DECIMAL; 0=disable simulation init values, 1=enable simulation init values
            SIM_ASSERT_CHK : std_logic;             -- DECIMAL; 0=disable simulation messages, 1=enable simulation messages
            SRC_INPUT_REG  : std_logic;             -- DECIMAL; 0=do not register input, 1=register input
            WIDTH          : integer range 1 to 1024-- DECIMAL; range: 1-1024
        );
        port (
            dest_out : out std_logic_vector(WIDTH-1 downto 0);   -- WIDTH-bit output: src_in synchronized to the destination clock domain.
            dest_clk : in  std_logic;                            -- 1-bit input: Clock signal for the destination clock domain.
            src_clk  : in  std_logic;                            -- 1-bit input: optional; required when SRC_INPUT_REG = 1
            src_in   : in  std_logic_vector(WIDTH-1 downto 0)    -- WIDTH-bit input: Input single-bit array to be synchronized to destination clock domain. 
        );
    end component;
    
    component xpm_cdc_pulse is
        generic(
            DEST_SYNC_FF    : integer range 2 to 10; -- DECIMAL; range: 2-10
            INIT_SYNC_FF    : std_logic;             -- DECIMAL; 0=disable simulation init values, 1=enable simulation init values
            REG_OUTPUT      : std_logic;             -- DECIMAL; 0=disable registered output, 1=enable registered output
            RST_USED        : std_logic;             -- DECIMAL; 0=no reset, 1=implement reset
            SIM_ASSERT_CHK  : std_logic              -- DECIMAL; 0=disable simulation messages, 1=enable simulation messages
        );
        port(
           dest_pulse   : out std_logic;     -- 1-bit output: Outputs a pulse the size of one dest_clk period 
           dest_clk     : in  std_logic;     -- 1-bit input: Destination clock.
           dest_rst     : in  std_logic;     -- 1-bit input: optional; required when RST_USED = 1
           src_clk      : in  std_logic;     -- 1-bit input: Source clock.
           src_pulse    : in  std_logic;     -- 1-bit input: Rising edge of this signal initiates a pulse transfer to the destination clock domain.
           src_rst      : in  std_logic      -- 1-bit input: optional; required when RST_USED = 1
        );
    end component;
    
    component xpm_cdc_handshake is
        generic(
            DEST_EXT_HSK   : natural range 0 to 1;      -- DECIMAL; 0=internal handshake, 1=external handshake
            DEST_SYNC_FF   : natural range 2 to 10;     -- DECIMAL; range: 2-10
            INIT_SYNC_FF   : natural range 0 to 1;      -- DECIMAL; 0=disable simulation init values, 1=enable simulation init values
            SIM_ASSERT_CHK : natural range 0 to 1;      -- DECIMAL; 0=disable simulation messages, 1=enable simulation messages
            SRC_SYNC_FF    : natural range 2 to 10;     -- DECIMAL; range: 2-10
            WIDTH          : natural range 1 to 1024    -- DECIMAL; range: 1-1024
        );
        port(
           dest_out : out std_logic_vector(WIDTH-1 downto 0);   -- WIDTH-bit output: src_in synchronized to the destination clock domain.
           dest_req : out std_logic;                            -- this signal asserts for one clock period when dest_out bus is valid
           src_rcv  : out std_logic;                            -- Acknowledgement from destination logic that src_in has been received
           dest_ack : in  std_logic;                            -- optional; required when DEST_EXT_HSK = 1
           dest_clk : in  std_logic;                            -- Destination clock.
           src_clk  : in  std_logic;                            -- Source clock.
           src_in   : in  std_logic_vector(WIDTH-1 downto 0);   -- WIDTH-bit input: Input single-bit array to be synchronized to destination clock domain.
           src_send : in  std_logic                             -- signal for src_in bus to be synchronized to the destination clock domain
        );
    end component;    
    
    type test_state_type is (idle, rx_command, rx_pwm_f, rx_pwm_d, rx_delay, test_exec_phx_s, test_exec_phx_d, test_exec_ovc, tx_send, tx_phx_send_d);
    signal test_current_state, test_next_state : test_state_type := idle;
    
    signal receive_command      : std_logic := '0';
    signal uart_transmit        : std_logic := '0';
    signal uart_transmit_s      : std_logic := '0';
    signal uart_transmit_d      : std_logic := '0';
    signal transmit_toggle      : std_logic := '0';
    signal phx_s_start          : std_logic := '0';
    signal phx_s_end            : std_logic := '0';
    signal phx_d_start          : std_logic := '0';
    signal phx_d_end            : std_logic := '0';
    signal ovc_start            : std_logic := '0';
    signal ovc_end              : std_logic := '0';
    signal receive_pwm_f        : std_logic := '0';
    signal receive_pwm_d        : std_logic := '0';
    signal pwm_period_compare   : std_logic_vector(15 downto 0) := X"07d0";          -- 16kHz default value (125MHz domain)
    signal pwm_uvw_compare      : std_logic_vector(39 downto 0) := x"0FA07D03E8";    -- 50% all phases default value (125MHz domain)
    signal pwm_period_compare_sync : std_logic_vector(15 downto 0) := X"07d0";       -- 16kHz default value (64MHz domain)  
    signal pwm_f_sync_ready     : std_logic := '0';                                  -- pwm period compare value can be written to PWM IP  
    signal pwm_uvw_compare_sync : std_logic_vector(39 downto 0) := x"0FA07D03E8";    -- 50% all phases default value (64MHz domain) 
    signal pwm_d_sync_ready     : std_logic := '0';                                  -- pwm uvw compare value can be written to PWM IP      
    
    signal uart_rx_busy_falling : std_logic := '0';
    signal receive_pwm_f_falling: std_logic := '0';
    signal receive_pwm_f_stretched : std_logic := '0';
    signal receive_pwm_d_falling: std_logic := '0';
    signal receive_pwm_d_stretched : std_logic := '0';
    signal stretch_cnt_f        : natural range 4 downto 0 := 0;
    signal stretch_cnt_d        : natural range 4 downto 0 := 0;
    signal tx_en_rising         : std_logic := '0';
    signal tx_en_falling        : std_logic := '0';
    signal tx_busy_falling      : std_logic := '0';
    signal uart_transmit_s_rising : std_logic := '0';
    signal uart_transmit_d_rising : std_logic := '0';
    signal tx_trigger_s         : std_logic := '0';
    signal tx_trigger_d         : std_logic := '0';
    signal tx_trigger_d_delay   : std_logic := '0';
    signal tx_trigger_send      : std_logic := '0';
    signal rx_byte_cnt          : integer range 0 to N_BYTES_COMMAND := 0;
    signal tx_byte_cnt          : integer range 0 to N_BYTES_FIFO    := 0;
    signal fifo_wr_toggle       : std_logic := '0';
    signal fifo_wr_rising       : std_logic := '0';
    signal fifo_wr_falling      : std_logic := '0';
    signal fifo_data_buf        : std_logic_vector(8*N_BYTES_SEND   -1 downto 0) := (others=>'0');
    signal test_command         : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := (others=>'0');
    signal transmit_data        : std_logic_vector(7                   downto 0) := (others=>'0');
    signal transmit_data_s      : std_logic_vector(8*N_BYTES_SEND   -1 downto 0) := (others=>'0');
    constant phu_s_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"7068755F735F6131"; -- phu_s_a1 -> static test on Phase U Axis 1
    constant phv_s_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"7068765F735F6131"; -- phv_s_a1 -> static test on Phase V Axis 1
    constant phw_s_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"7068775F735F6131"; -- phw_s_a1 -> static test on Phase W Axis 1
    constant phu_d_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"7068755F645F6131"; -- phu_d_a1 -> dynamic test on Phase U Axis 1
    constant phv_d_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"7068765F645F6131"; -- phv_d_a1 -> dynamic test on Phase V Axis 1
    constant phw_d_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"7068775F645F6131"; -- phw_d_a1 -> dynamic test on Phase W Axis 1
    constant ovc_u_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"6F76635F755F6131"; -- ovc_u_a1 -> OVC test on Phase U Axis 1
    constant ovc_v_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"6F76635F765F6131"; -- ovc_u_a1 -> OVC test on Phase V Axis 1
    constant ovc_w_a1           : std_logic_vector(8*N_BYTES_COMMAND-1 downto 0) := x"6F76635F775F6131"; -- ovc_v_a1 -> OVC test on Phase W Axis 1
    
    signal phx_data_ready_a1_sync   : std_logic;
    signal phu_sdo_a1_sync          : std_logic_vector(11 downto 0) := (others=>'0');
    signal phv_sdo_a1_sync          : std_logic_vector(11 downto 0) := (others=>'0');
    signal phw_sdo_a1_sync          : std_logic_vector(11 downto 0) := (others=>'0');
    
    signal ovc_event_a1_sync        : std_logic := '0';
    signal ovc_status_a1_sync       : std_logic_vector(5 downto 0) := (others=>'0');
    
    signal watchdog_cnt             : natural range 0 to 16777215 := 0;   -- 24-bit counter for watchdog of the states -> 50ms wait

begin

    uart_rx_busy_ed_inst: edge_detect port map( rst => rst_n_i, clk => clk_125M_i, inp => uart_rx_busy_i, r_edge => open, f_edge => uart_rx_busy_falling);
    receive_pwm_f_ed_inst: edge_detect port map( rst => rst_n_i, clk => clk_125M_i, inp => receive_pwm_f, r_edge => open, f_edge => receive_pwm_f_falling);
    receive_pwm_d_ed_inst: edge_detect port map( rst => rst_n_i, clk => clk_125M_i, inp => receive_pwm_d, r_edge => open, f_edge => receive_pwm_d_falling);
    
	-- receive pulse stretching for 3 clk cycles of 125MHz to synchronize to 64MHz
    pulse_stretcher : process(clk_125M_i)
    begin
        if (rising_edge(clk_125M_i)) then
            if (receive_pwm_f_falling = '1') then
                stretch_cnt_f <= 3;
            end if;
            if (stretch_cnt_f > 0) then
                stretch_cnt_f <= stretch_cnt_f - 1;
                receive_pwm_f_stretched <= '1';
            else
                receive_pwm_f_stretched <= '0';    
            end if;
            if (receive_pwm_d_falling = '1') then
                stretch_cnt_d <= 3;
            end if;
            if (stretch_cnt_d > 0) then
                stretch_cnt_d <= stretch_cnt_d - 1;
                receive_pwm_d_stretched <= '1';
            else
                receive_pwm_d_stretched <= '0';    
            end if;            
        end if;
    end process;     
    ----------------------------------------------------------------------------- 
    -- Data Synchronization                                      --
    -----------------------------------------------------------------------------  
    xpm_cdc_handsh_sync_pwm_f: xpm_cdc_handshake
        generic map(
            DEST_EXT_HSK    => 0,
            DEST_SYNC_FF    => 4,
            INIT_SYNC_FF    => 1,
            SIM_ASSERT_CHK  => 0,
            SRC_SYNC_FF     => 2,
            WIDTH           => 16    
        )
        port map(
            dest_out    => pwm_period_compare_sync,
            dest_req    => pwm_f_sync_ready,
            src_rcv     => open,
            dest_ack    => '0',
            dest_clk    => clk_64M_i,
            src_clk     => clk_125M_i,
            src_in      => pwm_period_compare,
            src_send    => receive_pwm_f_stretched
        );
        
    xpm_cdc_handsh_sync_pwm_d: xpm_cdc_handshake
        generic map(
            DEST_EXT_HSK    => 0,
            DEST_SYNC_FF    => 4,
            INIT_SYNC_FF    => 1,
            SIM_ASSERT_CHK  => 0,
            SRC_SYNC_FF     => 2,
            WIDTH           => 40    
        )
        port map(
            dest_out    => pwm_uvw_compare_sync,
            dest_req    => pwm_d_sync_ready,
            src_rcv     => open,
            dest_ack    => '0',
            dest_clk    => clk_64M_i,
            src_clk     => clk_125M_i,
            src_in      => pwm_uvw_compare,
            src_send    => receive_pwm_d_stretched
        );
    
    xpm_cdc_puls_phx_data_ready: xpm_cdc_pulse
        generic map(
            DEST_SYNC_FF    => 2,
            INIT_SYNC_FF    => '1',
            REG_OUTPUT      => '0',
            RST_USED        => '0',
            SIM_ASSERT_CHK  => '0'
        )
        port map(
            dest_pulse  => phx_data_ready_a1_sync,
            dest_clk    => clk_125M_i,
            dest_rst    => '1',
            src_clk     => clk_64M_i,
            src_pulse   => phx_data_ready_a1_i,
            src_rst     => '1'
        );
        
    xpm_cdc_array_sync_phu_a1: xpm_cdc_array_single
        generic map(
            DEST_SYNC_FF    => 2,
            INIT_SYNC_FF    => '1',
            SIM_ASSERT_CHK  => '0',
            SRC_INPUT_REG   => '0',
            WIDTH           => 12    
        )
        port map(
            dest_out    => phu_sdo_a1_sync,
            dest_clk    => clk_125M_i,
            src_clk     => clk_64M_i,
            src_in      => phu_adc_a1_i
        );
    
    xpm_cdc_array_sync_phv_a1: xpm_cdc_array_single
        generic map(
            DEST_SYNC_FF    => 2,
            INIT_SYNC_FF    => '1',
            SIM_ASSERT_CHK  => '0',
            SRC_INPUT_REG   => '0',
            WIDTH           => 12    
        )
        port map(
            dest_out    => phv_sdo_a1_sync,
            dest_clk    => clk_125M_i,
            src_clk     => clk_64M_i,
            src_in      => phv_adc_a1_i
        );
        
    xpm_cdc_array_sync_phw_a1: xpm_cdc_array_single
        generic map(
            DEST_SYNC_FF    => 2,
            INIT_SYNC_FF    => '1',
            SIM_ASSERT_CHK  => '0',
            SRC_INPUT_REG   => '0',
            WIDTH           => 12    
        )
        port map(
            dest_out    => phw_sdo_a1_sync,
            dest_clk    => clk_125M_i,
            src_clk     => clk_64M_i,
            src_in      => phw_adc_a1_i
        );
    
    xpm_cdc_puls_ovc_event_a1: xpm_cdc_array_single
        generic map(
            DEST_SYNC_FF    => 2,
            INIT_SYNC_FF    => '1',
            SIM_ASSERT_CHK  => '0',
            SRC_INPUT_REG   => '0',
            WIDTH           => 1    
        )
        port map(
            dest_out(0) => ovc_event_a1_sync,
            dest_clk    => clk_125M_i,
            src_clk     => clk_64M_i,
            src_in(0)   => ovc_event_a1_i
        );  
        
    xpm_cdc_array_sync_ovc_status_a1: xpm_cdc_array_single
        generic map(
            DEST_SYNC_FF    => 2,
            INIT_SYNC_FF    => '1',
            SIM_ASSERT_CHK  => '0',
            SRC_INPUT_REG   => '0',
            WIDTH           => 6    
        )
        port map(
            dest_out    => ovc_status_a1_sync,
            dest_clk    => clk_125M_i,
            src_clk     => clk_64M_i,
            src_in      => ovc_status_a1_i
        );            
    
    -----------------------------------------------------------------------------    
    -- END DATA SYNCHRONIZATION                                                --
    -----------------------------------------------------------------------------  
     ----------------------------------------------------------------------------- 
    -- Write PWM values to outputs                                              --
    ----------------------------------------------------------------------------- 
    period_compare_proc: process(clk_64M_i, rst_n_i)
    begin
        if rising_edge(clk_64M_i) then
            if rst_n_i = '0' then
                pwm_freq_a1_o   <= b"0011111010000"; -- 0x07D0 default value 16kHz
            elsif pwm_f_sync_ready = '1' then
                pwm_freq_a1_o   <= pwm_period_compare_sync(12 downto 0);
            end if;        
        end if;
    end process;  
    
    uvw_compare_proc: process(clk_64M_i, rst_n_i)
    begin
        if rising_edge(clk_64M_i) then
            if rst_n_i = '0' then
                pwm_duty_a1_o   <= b"000111110100000011111010000001111101000"; -- 0x0FA07D03E8  default value 50%
                pwm_enable_a1_o <= '0';
            elsif pwm_d_sync_ready = '1' then
                pwm_duty_a1_o   <= pwm_uvw_compare_sync(38 downto 0);
                pwm_enable_a1_o <= '1';
            end if;        
        end if;
    end process; 
        -----------------------------------------------------------------------------    
    -- END write PWM values                                                 --
    -----------------------------------------------------------------------------    
     ----------------------------------------------------------------------------- 
    -- OVC Release process                                                      --
    -----------------------------------------------------------------------------  
    ovc_release_proc: process(clk_64M_i, rst_n_i)
    begin
        if rising_edge(clk_64M_i) then
            if rst_n_i = '0' then
                ovc_release_a1_o <= '0';
            elsif (ovc_event_a1_i = '1' and ovc_status_a1_i = "000000") then
                ovc_release_a1_o <= '1';
            else 
                ovc_release_a1_o <= '0';        
            end if;    
         end if;
    end process;    
    
    -----------------------------------------------------------------------------    
    -- END OVC Release                                                 --
    -----------------------------------------------------------------------------     
           
    ----------------------------------------------------------------------------- 
    -- UART DATA CAPTURE                                                       --
    -----------------------------------------------------------------------------  
    -- receive test command, receive pwm period compare, receive pwm duty cycle compare
    uart_rx_data_proc: process(clk_125M_i, rst_n_i)
    begin
        if rising_edge(clk_125M_i) then
            if rst_n_i = '0' then
                test_command       <= (others=>'0');
                pwm_period_compare <= (others=>'0');
                pwm_uvw_compare    <= (others=>'0');
                rx_byte_cnt  <= 0;
            elsif receive_command = '1' then   
                if uart_rx_busy_falling = '1' then
                    test_command(test_command'HIGH-rx_byte_cnt*8 downto test_command'HIGH-rx_byte_cnt*8-7) <= uart_rx_data_i;
                    rx_byte_cnt <= rx_byte_cnt + 1; 
                end if;
                if rx_byte_cnt = N_BYTES_COMMAND then
                    rx_byte_cnt <= 0;
                end if;       
            elsif receive_pwm_f = '1' then   
                if uart_rx_busy_falling = '1' then
                    pwm_period_compare(pwm_period_compare'HIGH-rx_byte_cnt*8 downto pwm_period_compare'HIGH-rx_byte_cnt*8-7) <= uart_rx_data_i;
                    rx_byte_cnt <= rx_byte_cnt + 1; 
                end if; 
            elsif receive_pwm_d = '1' then   
                if uart_rx_busy_falling = '1' then
                    pwm_uvw_compare(pwm_uvw_compare'HIGH-rx_byte_cnt*8 downto pwm_uvw_compare'HIGH-rx_byte_cnt*8-7) <= uart_rx_data_i;
                    rx_byte_cnt <= rx_byte_cnt + 1; 
                end if; 
            else 
                rx_byte_cnt <= 0;        
            end if;    
         end if;
    end process;     
    -----------------------------------------------------------------------------    
    -- END UART DATA CAPTURE                                                   --
    -----------------------------------------------------------------------------        

    ----------------------------------------------------------------------------- 
    -- UART DATA SEND TEST                                                     --
    -----------------------------------------------------------------------------   
    uart_tx_en_inst: edge_detect port map( rst => rst_n_i, clk => clk_125M_i, inp => transmit_toggle, r_edge => tx_en_rising, f_edge => tx_en_falling);
    uart_tx_trigger_o <= tx_en_rising or tx_en_falling;
    uart_tx_busy_inst: edge_detect port map( rst => rst_n_i, clk => clk_125M_i, inp => uart_tx_busy_i, r_edge => open, f_edge => tx_busy_falling);
    uart_transmit_s_inst: edge_detect port map( rst => rst_n_i, clk => clk_125M_i, inp => uart_transmit_s, r_edge => uart_transmit_s_rising, f_edge => open);
    uart_transmit_d_inst: edge_detect port map( rst => rst_n_i, clk => clk_125M_i, inp => uart_transmit_d, r_edge => uart_transmit_d_rising, f_edge => open);
    
    tx_trigger_s <= (uart_transmit_s_rising or tx_busy_falling) and uart_transmit_s;
    tx_trigger_d <= (uart_transmit_d_rising or tx_busy_falling) and uart_transmit_d;
    fifo_rd_en_o <= tx_trigger_d;
    
    -- UART Transmit Data 
    uart_tx_data_proc: process(clk_125M_i, rst_n_i)
    begin
        if rising_edge(clk_125M_i) then
            if rst_n_i = '0' then
                uart_tx_data_o <= (others=>'0');
                tx_byte_cnt  <= 0;
            elsif uart_transmit_s = '1' or uart_transmit_d = '1' then   
                if uart_tx_busy_i = '0' and tx_trigger_send = '1' then
                    uart_tx_data_o <= transmit_data;
                    tx_byte_cnt <= tx_byte_cnt + 1; 
                    transmit_toggle <= not transmit_toggle;
                end if;
            else 
                tx_byte_cnt <= 0;        
            end if;    
         end if;
    end process; 
    
    -- tx_trigger_d delay
    fifo_rd_en_delay_proc: process(clk_125M_i, rst_n_i)
    begin
        if rising_edge(clk_125M_i) then
            if rst_n_i = '0' then
                tx_trigger_d_delay <= '0';
            elsif tx_trigger_d = '1' then
                tx_trigger_d_delay <= '1';
            else 
                tx_trigger_d_delay <= '0';
            end if;
        end if;
    end process;                            
    
    -- Data allocation
    uart_tx_static_data_proc: process(clk_125M_i, rst_n_i)
    begin
        if rising_edge(clk_125M_i) then
            if rst_n_i = '0' then
                transmit_data   <= (others=>'0');
                tx_trigger_send <= '0';
            elsif uart_tx_busy_i = '0' and tx_trigger_s = '1' then   
                transmit_data   <= transmit_data_s(transmit_data_s'HIGH-tx_byte_cnt*8 downto transmit_data_s'HIGH-tx_byte_cnt*8-7);   
                tx_trigger_send <= '1';
            elsif uart_tx_busy_i = '0' and tx_trigger_d_delay = '1' then  
                transmit_data   <= fifo_data_out_i;   
                tx_trigger_send <= '1';      
            else
                tx_trigger_send <= '0';    
            end if;    
         end if;
    end process; 

    -----------------------------------------------------------------------------    
    -- END UART DATA SEND TEST                                          --
    -----------------------------------------------------------------------------       
    
    -----------------------------------------------------------------------------    
    -- STATIC TESTS: Capture Data to UART Register                --
    -----------------------------------------------------------------------------       

    test_exec_static_proc: process(clk_125M_i, rst_n_i)
    begin
        if rising_edge(clk_125M_i) then
            if rst_n_i = '0' then
                phx_s_end      <= '0';
                ovc_end        <= '0';
                transmit_data_s<= (others=>'0');
            elsif phx_s_start = '1' then
                if phx_data_ready_a1_sync = '1' then
                    case test_command is  
                        when phu_s_a1 =>
                            transmit_data_s(7 downto 0)   <= phu_sdo_a1_sync(7 downto 0);
                            transmit_data_s(11 downto 8)  <= phu_sdo_a1_sync(11 downto 8);
                            phx_s_end                     <= '1';
                        when phv_s_a1 =>
                            transmit_data_s(7 downto 0)   <= phv_sdo_a1_sync(7 downto 0);
                            transmit_data_s(11 downto 8)  <= phv_sdo_a1_sync(11 downto 8);
                            phx_s_end                     <= '1';
                        when phw_s_a1 =>
                            transmit_data_s(7 downto 0)   <= phw_sdo_a1_sync(7 downto 0);
                            transmit_data_s(11 downto 8)  <= phw_sdo_a1_sync(11 downto 8);  
                            phx_s_end                     <= '1';
                        when others => NULL;
                    end case; 
                end if;  
            elsif ovc_start = '1' then
                if phx_data_ready_a1_sync = '1' then
                    transmit_data_s(5 downto 0)   <= ovc_status_a1_sync;
                    transmit_data_s(7 downto 6)   <= (others=>'0');
                    transmit_data_s(8)            <= ovc_event_a1_sync;
                    transmit_data_s(15 downto 9)  <= (others=>'0');
                    ovc_end                       <= '1';
                end if;           
            else
                phx_s_end <= '0';    
                ovc_end   <= '0'; 
            end if;
        end if;
    end process;       

    -----------------------------------------------------------------------------    
    -- END STATIC TEST                                                         --
    -----------------------------------------------------------------------------   
    
    -----------------------------------------------------------------------------    
    -- DYNAMIC TEST: Capture Phase Current Data 4096 samples to FIFO           --
    -----------------------------------------------------------------------------    
    fifo_wr_en_inst: edge_detect port map( rst => rst_n_i, clk => clk_125M_i, inp => fifo_wr_toggle, r_edge => fifo_wr_rising, f_edge => fifo_wr_falling);
    fifo_wr_en_o <= fifo_wr_rising or fifo_wr_falling;
    
    test_exec_dynamic_proc: process(clk_125M_i, rst_n_i)
    begin
        if rising_edge(clk_125M_i) then
            if rst_n_i = '0' then
                phx_d_end      <= '0';
                fifo_data_in_o <= (others=>'0');
            elsif phx_d_start = '1' then
                if phx_data_ready_a1_sync = '1' then
                    case test_command is  
                        when phu_d_a1 =>
                            fifo_data_in_o(7 downto 0)  <= phu_sdo_a1_sync(7 downto 0);    
                            fifo_data_in_o(11 downto 8) <= phu_sdo_a1_sync(11 downto 8);    
                            fifo_wr_toggle              <= not fifo_wr_toggle;     
                        when phv_d_a1 =>
                            fifo_data_in_o(7 downto 0)  <= phv_sdo_a1_sync(7 downto 0);    
                            fifo_data_in_o(11 downto 8) <= phv_sdo_a1_sync(11 downto 8);  
                            fifo_wr_toggle              <= not fifo_wr_toggle;
                        when phw_d_a1 =>
                            fifo_data_in_o(7 downto 0)  <= phw_sdo_a1_sync(7 downto 0);    
                            fifo_data_in_o(11 downto 8) <= phw_sdo_a1_sync(11 downto 8);  
                            fifo_wr_toggle              <= not fifo_wr_toggle;
                        when others => NULL;
                    end case; 
                end if;    
            end if;
        end if;
    end process;            
   
    -----------------------------------------------------------------------------    
    -- END DYNAMIC TEST                                                        --
    -----------------------------------------------------------------------------   
    
    -- watchdog counter 
    watchdog_cnt_proc: process(clk_125M_i)
    begin 
        if rising_edge(clk_125M_i) then
            if rst_n_i = '0' then
                watchdog_cnt <= 0;
            elsif receive_command = '1' or phx_s_start = '1' or uart_transmit_s = '1' or uart_transmit_d = '1' then
                watchdog_cnt <= watchdog_cnt + 1;
            else 
                watchdog_cnt <= 0;        
            end if;
         end if;
     end process;       
                         
------------------------------------------------------------------------------
--  Main Test Statmachine 
------------------------------------------------------------------------------

    -- Test State machine Input
    test_state_proc: process(clk_125M_i)
    begin
        if rising_edge(clk_125M_i) then
            test_current_state <= test_next_state;
        end if;    
    end process;
    
    test_fsm_input_proc: process(test_current_state, uart_rx_busy_i, rx_byte_cnt, phx_s_end, ovc_end, tx_byte_cnt, fifo_full_i, fifo_empty_i, watchdog_cnt)
    begin
        test_next_state <= test_current_state;
        case test_current_state is
            when idle =>    
                if uart_rx_busy_i = '1' then
                    test_next_state <= rx_command;
                else
                    test_next_state <= idle;
                end if;        
            when rx_command =>
                -- phase current static test check
                if rx_byte_cnt = N_BYTES_COMMAND 
                and test_command(8*N_BYTES_COMMAND-1 downto 6*N_BYTES_COMMAND) = x"7068" 
                and test_command(4*N_BYTES_COMMAND-1 downto 3*N_BYTES_COMMAND) = x"73" then
                    test_next_state <= test_exec_phx_s;
                -- phase current dynamic test check    
                elsif rx_byte_cnt = N_BYTES_COMMAND
                and test_command(8*N_BYTES_COMMAND-1 downto 6*N_BYTES_COMMAND) = x"7068" 
                and test_command(4*N_BYTES_COMMAND-1 downto 3*N_BYTES_COMMAND) = x"64" then
                    test_next_state <= test_exec_phx_d;  
                -- overcurrent detection test check    
                elsif rx_byte_cnt = N_BYTES_COMMAND   
                and test_command(8*N_BYTES_COMMAND-1 downto 5*N_BYTES_COMMAND) = x"6F7663" then          
                    test_next_state <= test_exec_ovc; 
                -- pwm period or duty cycle compare value    
                elsif rx_byte_cnt = N_BYTES_COMMAND   
                and (test_command(8*N_BYTES_COMMAND-1 downto 3*N_BYTES_COMMAND) = x"70776D5F66" 
                or  test_command(8*N_BYTES_COMMAND-1 downto 3*N_BYTES_COMMAND) = x"70776D5F64") then          
                    test_next_state <= rx_delay;                                
                elsif watchdog_cnt = 1000000 then
                    test_next_state <= idle;        
                else
                    test_next_state <= rx_command;
                end if;   
            when rx_delay =>
                -- pwm period compare value
                if test_command(8*N_BYTES_COMMAND-1 downto 3*N_BYTES_COMMAND) = x"70776D5F66" then          
                    test_next_state <= rx_pwm_f;  
                -- pwm duty cycle compare value    
                elsif test_command(8*N_BYTES_COMMAND-1 downto 3*N_BYTES_COMMAND) = x"70776D5F64" then          
                    test_next_state <= rx_pwm_d; 
                elsif watchdog_cnt = 1000000 then
                    test_next_state <= idle;
                else
                    test_next_state <= rx_delay;   
                end if;                
            when rx_pwm_f =>
                -- receive PWM period compare value
                if rx_byte_cnt = 2 then    
                    test_next_state <= idle;  
                else
                    test_next_state <= rx_pwm_f;   
                end if;
            when rx_pwm_d =>
                -- receive PWM duty cycle compare value
                if rx_byte_cnt = 5 then    
                    test_next_state <= idle;  
                else
                    test_next_state <= rx_pwm_d;   
                end if;                                                                              
            when test_exec_phx_s =>
                if phx_s_end = '1' then
                    test_next_state <= tx_send;
                elsif watchdog_cnt = 1000000 then
                    test_next_state <= idle;  
                else
                    test_next_state <= test_exec_phx_s;
                end if;
            when test_exec_phx_d =>
                if fifo_full_i = '1' then
                    test_next_state <= tx_phx_send_d;
                elsif watchdog_cnt = 6250000 then
                    test_next_state <= idle;  
                else
                    test_next_state <= test_exec_phx_d;
                end if;   
            when test_exec_ovc =>
                if ovc_end = '1' then
                    test_next_state <= tx_send;
                elsif watchdog_cnt = 1000000 then
                    test_next_state <= idle;  
                else
                    test_next_state <= test_exec_ovc;
                end if;                                 
            when tx_send =>                   
                if tx_byte_cnt = N_BYTES_SEND then
                    test_next_state <= idle; 
                elsif watchdog_cnt = 1000000 then
                    test_next_state <= idle;    
                else
                    test_next_state <= tx_send;  
                end if;         
            when tx_phx_send_d =>                   
                if tx_byte_cnt = N_BYTES_FIFO then
                    test_next_state <= idle; 
                elsif watchdog_cnt = 12500000 then
                    test_next_state <= idle;    
                else
                    test_next_state <= tx_phx_send_d;  
                end if;                     
            when others =>
                test_next_state <= idle;
        end case;                 
    end process;
    
    test_fsm_output_proc: process(test_current_state)
    begin
        phx_s_start     <= '0';  
        phx_d_start     <= '0';
        ovc_start       <= '0';
        receive_command <= '0'; 
        receive_pwm_f   <= '0';
        receive_pwm_d   <= '0';
        uart_transmit_s <= '0';
        uart_transmit_d <= '0';
        case test_current_state is
            when idle => NULL;
            
            when rx_command =>
                receive_command <= '1';
                
            when rx_pwm_f =>
                receive_pwm_f <= '1';   
                
            when rx_pwm_d =>
                receive_pwm_d <= '1';                  
                
            when test_exec_phx_s =>   
                phx_s_start <= '1';
                
            when test_exec_phx_d =>
                phx_d_start <= '1';    
                
            when test_exec_ovc =>
                ovc_start <= '1';    
                    
            when tx_send =>   
                uart_transmit_s <= '1';
                
            when tx_phx_send_d =>   
                uart_transmit_d <= '1';
                    
            when others => NULL;
        end case;        
    end process;
    
end rtl;
