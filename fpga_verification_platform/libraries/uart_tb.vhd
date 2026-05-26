library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity uart_tb is -- https://forum.digikey.com/t/uart-vhdl/12670
end entity;

architecture testbench of uart_tb is   
    component uart is
        generic (
            CLK_FREQ:    integer    := 50_000_000;
            BAUD_RATE:   integer    := 19_200;
            OS_RATE:     integer    := 16;       -- oversample rate
            D_WIDTH:     integer    := 8;
            PARITY:      integer    := 1;
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
    
    constant CLK_FREQ:  integer := 50_000_000;
    constant BAUD_RATE: integer := 19_200;
    constant OS_RATE:   integer := 16;
    constant D_WIDTH:   integer := 8;
    constant PARITY:    integer := 1;
    constant PARITY_EO: std_logic := '0';
    
    signal clk:         std_logic := '0';
    signal reset_n:     std_logic := '1';
    signal tx_ena:      std_logic := '0';
    signal tx_data:     std_logic_vector (D_WIDTH - 1 downto 0);
    signal rx:          std_logic;
    signal rx_busy:     std_logic;
    signal rx_error:    std_logic;
    signal rx_data:     std_logic_vector (D_WIDTH - 1 downto 0);
    signal tx_busy:     std_logic;
    signal tx:          std_logic;
    
    constant message:   string := "Scott Larson's VHDL UART at Digikey TechForum";
    signal xmt_char:    character;
    signal rcv_char:    character;
begin
    
DUT:
    uart 
        generic map (
            CLK_FREQ => CLK_FREQ,
            BAUD_RATE => BAUD_RATE,
            OS_RATE => OS_RATE,
            D_WIDTH => D_WIDTH,
            PARITY => PARITY,
            PARITy_EO => PARITY_EO
        )
        port map (
            clk => clk,
            reset_n => reset_n,
            tx_ena => tx_ena,
            tx_data => tx_data,
            rx => rx,
            rx_busy => rx_busy,
            rx_error => rx_error,
            rx_data => rx_data,
            tx_busy => tx_busy,
            tx => tx
        );
CLOCK:
    process
    begin
        wait for 10 ns;
        clk <= not clk;
        if now > 28.75 ms then
            wait;
        end if;
    end process;

RESET:
    process
    begin
        wait for 4 ns;
        reset_n <= '0';
        wait for 80 ns;
        reset_n <= '1';
        wait;
    end process;
STIMULI_TX: 
    process
    begin
        wait until rising_edge(reset_n);
        for i in 1 to message'length loop
            wait until tx_busy = '0';
            wait until rising_edge (clk);
            tx_data <= 
                std_logic_vector (
                    to_unsigned(character'pos(message(i)), tx_data'length)
                );
            xmt_char <= message(i);
            tx_ena <= '1';
            wait until rising_edge (clk);
            tx_ena <= '0';
        end loop;
        wait;
    end process;
STIMULI_RX:
    process
    begin
        wait until rising_edge (reset_n);
        wait until rx_busy = '1';
        for i in 1 to message'length loop
            wait until rx_busy = '0';
            wait until rising_edge (clk);
            rcv_char <= character'val (to_integer(unsigned(rx_data)));
        end loop;
    end process;
LOOP_BACK:
    rx <= tx;
end architecture;
    
