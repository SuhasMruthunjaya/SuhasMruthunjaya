library ieee;
use ieee.std_logic_1164.all;

entity blinkLEDs_TB is
end blinkLEDs_TB;

architecture testbench of blinkLEDs_TB is
    -- Component declaration
    component blinkLEDs
        Port (
            LED : out std_logic_vector(3 downto 0);
            CLK : in std_logic;
            RST : in std_logic
        );
    end component;

    -- Signals for testbench
    signal CLK_tb : std_logic := '0'; -- Testbench clock signal
    signal RST_tb : std_logic := '0'; -- Testbench reset signal
    signal LED_tb : std_logic_vector(3 downto 0); -- Testbench LED signal
begin
    -- Instantiate the LED_Blinker module
    DUT: blinkLEDs
    port map (
        LED => LED_tb,
        CLK => CLK_tb,
        RST => RST_tb
    );

    -- Clock generation process
    CLK_gen_process: process
    begin
        while now < 100000 ns loop  -- Run simulation for 1000 ns
            CLK_tb <= not CLK_tb; -- Toggle clock signal
            wait for 5 ns;         -- Clock period of 10 ns (50 MHz)
        end loop;
        wait;
    end process CLK_gen_process;

    -- Stimulus process for reset signal
    stimulus_process: process
    begin
        RST_tb <= '1';  -- Activate reset
        wait for 20 ns; -- Wait for 20 ns
        RST_tb <= '0';  -- Deactivate reset
        wait;
    end process stimulus_process;

end testbench;
