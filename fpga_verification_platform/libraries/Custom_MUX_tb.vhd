----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
--
-- Create Date: 06/24/2025 03:00:00 PM
-- Design Name:
-- Module Name: Custom_MUX_tb - Behavioral
-- Project Name: Custom_MUX Testbench
-- Target Devices:
-- Tool Versions:
-- Description: Testbench for the Custom_MUX VHDL module.
--
-- Dependencies: Custom_MUX.vhd
--
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
----------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL; -- Required for integer types if used elsewhere, good practice.

entity Custom_MUX_tb is
end Custom_MUX_tb;

architecture behavioral of Custom_MUX_tb is

    -- Component Declaration for the Unit Under Test (UUT)
    component Custom_MUX is
        Port (
            clk                     : in std_logic;
            rst_n                   : in std_logic;
            sel                     : in std_logic;
            spi_ph_address          : in std_logic_vector(7 downto 0);
            ddfs_data               : in std_logic_vector(15 downto 0);
            spi_data                : out std_logic_vector(23 downto 0);
            spi_continous_start     : out std_logic;
            start_op                : in std_logic;
            spi_cpol                : out std_logic;
            spi_divider             : out std_logic_vector(7 downto 0);
            spi_intermittent_start  : out std_logic
        );
    end component;

    -- Input Signals for the UUT
    signal clk_i                    : std_logic := '0';
    signal rst_n_i                  : std_logic := '0'; -- Start in reset
    signal sel_i                    : std_logic := '0';
    signal spi_ph_address_i         : std_logic_vector(7 downto 0)  := (others => '0');
    signal ddfs_data_i              : std_logic_vector(15 downto 0) := (others => '0');
    signal start_op_i               : std_logic := '0';

    -- Output Signals from the UUT
    signal spi_data_o               : std_logic_vector(23 downto 0);
    signal spi_continous_start_o    : std_logic;
    signal spi_cpol_o               : std_logic;
    signal spi_divider_o            : std_logic_vector(7 downto 0);
    signal spi_intermittent_start_o : std_logic;

    -- Clock period constant (e.g., 100 MHz clock -> 10 ns period)
    constant CLK_PERIOD : time := 5.2083333ns;

begin

    -- Instantiate the Unit Under Test (UUT)
    uut: Custom_MUX
        port map (
            clk                     => clk_i,
            rst_n                   => rst_n_i,
            sel                     => sel_i,
            spi_ph_address          => spi_ph_address_i,
            ddfs_data               => ddfs_data_i,
            spi_data                => spi_data_o,
            spi_continous_start     => spi_continous_start_o,
            start_op                => start_op_i,
            spi_cpol                => spi_cpol_o,
            spi_divider             => spi_divider_o,
            spi_intermittent_start  => spi_intermittent_start_o
        );

    -- Clock Generation Process
    clk_gen: process
    begin
        loop
            clk_i <= '0';
            wait for CLK_PERIOD / 2;
            clk_i <= '1';
            wait for CLK_PERIOD / 2;
        end loop;
    end process clk_gen;

    -- Stimulus Process
    stim_proc: process
    begin
        report "--- Testbench Started ---" severity note;

        -- 1. Initial Reset Sequence
        report "Applying Reset..." severity note;
        rst_n_i <= '0';           -- Assert reset
        start_op_i <= '0';
        sel_i <= '0';
        spi_ph_address_i <= X"08";
        ddfs_data_i <= (others => '0');
        wait for CLK_PERIOD * 5;  -- Hold reset for a few clock cycles
        rst_n_i <= '1';           -- De-assert reset
        report "Reset De-asserted. FSM should be in st1_idle." severity note;
        wait for CLK_PERIOD * 2;

        -- 2. Test FSM Transition to st2_config_reg_update and spi_intermittent_start pulse
        report "Triggering FSM to st2_config_reg_update (start_op = '1'). Expect single pulse on spi_intermittent_start_o." severity note;
        start_op_i <= '1';
        wait for CLK_PERIOD;
--        start_op_i <= '0';        -- De-assert start_op after one cycle to avoid re-triggering immediately
--        wait for CLK_PERIOD;
        -- Check if spi_intermittent_start_o pulsed (it should have been high for 1 clock cycle)
        report "spi_intermittent_start_o should have pulsed: " & std_logic'image(spi_intermittent_start_o) severity note;
--        report "spi_data_o during st2_config_reg_update: " & to_string(spi_data_o) severity note;

        -- 3. Wait for write_reg_done to go high (after 192 clock cycles as per Num_of_cycles in SPI_START_Trigger)
        report "Waiting for write_reg_done (approx. 192 cycles later)..." severity note;
        wait until spi_data_o = X"0401FF"; -- Wait for the SPI data to change to next state (st3_gain_reg_update)
        -- The write_reg_done signal in the DUT is internal, so we observe its effect on state transition.
        -- In a real testbench, if write_reg_done was an output, we'd check it directly.
        -- For this test, we verify the state transition by spi_data_o's value.
--        report "FSM should now be in st3_gain_reg_update. spi_data_o: " & to_string(spi_data_o) severity note;
        wait for CLK_PERIOD * 5;
--        sel_i <= '1';
--        -- 4. Test sel = '1' path (DAC write)
--        report "Setting sel_i = '1'. Expect spi_data_o to be spi_ph_address_i & ddfs_data_i." severity note;
--        sel_i <= '1';
--        spi_ph_address_i <= X"AA";
--        ddfs_data_i <= X"1234";
--        wait for CLK_PERIOD * 2;
----        report "spi_data_o (sel='1'): " & to_string(spi_data_o) severity note;
--        -- Expected: X"AA1234"

--        -- 5. Test spi_continous_start with sel = '1'
--        -- spi_continous_start is driven by SPI_START_Trigger which gets 'start' from 'sel'.
--        -- So when sel='1', spi_continous_start should eventually go high after 187 cycles from SPI_START_Trigger
--        report "sel_i is '1'. Monitoring spi_continous_start_o. It should pulse after ~187 cycles." severity note;
--        wait for CLK_PERIOD * 200; -- Wait for enough cycles for SPI_START_Trigger to activate
--        report "spi_continous_start_o after sel='1' for a while: " & std_logic'image(spi_continous_start_o) severity note;


--        -- 6. Return to idle and re-trigger
--        report "Returning to idle and re-triggering for another pulse check." severity note;
--        sel_i <= '0';
--        start_op_i <= '0';
--        wait for CLK_PERIOD * 10;
--        start_op_i <= '1';
--        wait for CLK_PERIOD;
--        start_op_i <= '0';
--        wait for CLK_PERIOD;
--        report "spi_intermittent_start_o should have pulsed again: " & std_logic'image(spi_intermittent_start_o) severity note;


        report "--- Testbench Finished ---" severity note;
        wait; -- End of simulation
    end process stim_proc;

end behavioral;
