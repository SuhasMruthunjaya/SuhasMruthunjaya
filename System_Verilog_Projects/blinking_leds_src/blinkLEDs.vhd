library ieee;
use ieee.std_logic_1164.all;

-- Entity declaration
entity blinkLEDs is
    Port (
        LED : out std_logic_vector(3 downto 0); -- Output ports for LEDs
        CLK : in std_logic;                      -- Clock input
        RST : in std_logic                      -- Reset input
    );
end blinkLEDs;

-- Architecture body
architecture Behavioral of blinkLEDs is
    signal counter : integer range 0 to 500 := 0;  -- Counter to control blinking speed
    signal LED_state : std_logic_vector(3 downto 0) := "0000"; -- Initial LED state
begin

    -- Process to control LED blinking
    LED_blink_process: process(CLK, RST)
    begin
        if RST = '1' then  -- Reset condition
            counter <= 0;
            LED_state <= "0000";
        elsif rising_edge(CLK) then  -- Clock edge detection
            if counter = 500 then -- Change LED state every 50000000 clock cycles
                counter <= 0;
                LED_state <= not LED_state; -- Toggle LEDs
            else
                counter <= counter + 1;  -- Increment counter
            end if;
        end if;
    end process LED_blink_process;

    -- Assign LED outputs
    LED <= LED_state;

end Behavioral;
