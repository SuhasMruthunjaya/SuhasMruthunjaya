----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.09.2023 13:33:35
-- Design Name: 
-- Module Name: pwm_off - rtl
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
USE ieee.std_logic_misc.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity pwm_off is
    generic (
        ERROR_AH            : integer range 1 to 8 := 4;
        ERROR_AL            : integer range 1 to 8 := 1;
        PWM_WIDTH           : integer range 1 to 8 := 6 
    );
    port ( 
        clk_i               : in  std_logic;
        reset_n_i           : in  std_logic;
        error_i             : in  std_logic_vector(ERROR_AH-1 downto 0);  -- Active High Errors: Overcurrent Error, R5 Error Core 0, R5 Error Core 1
        error_n_i           : in  std_logic_vector(ERROR_AL-1 downto 0);  -- Active Low Errors: ITrip (GATE_FLT) Error                 
        pwm_i               : in  std_logic_vector(PWM_WIDTH-1 downto 0); -- All PWM input signals combined
        pwm_o               : out std_logic_vector(PWM_WIDTH-1 downto 0)  -- All PWM output signals to IO ports
    );
end pwm_off;

architecture rtl of pwm_off is

component OBUFT is
port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC
);
end component OBUFT;

signal error_comb               : std_logic := '0'; 
signal error_comb_n             : std_logic := '1'; 
signal error_result             : std_logic := '0'; 

begin

-- purpose: OR combination of active high errors
-- inputs:  clk_i, reset_n_i, error_i
-- outputs: error_comb
comb_ah_errors_proc: process(clk_i, reset_n_i)
begin
    if rising_edge(clk_i) then
        if reset_n_i = '0' then
            error_comb <= '0';
        else
            error_comb <= or_reduce(error_i);    
        end if;
    end if;      
end process;

-- purpose: OR combination of active low errors
-- inputs:  clk_i, reset_n_i, error_i
-- outputs: error_comb_n
comb_al_errors_proc: process(clk_i, reset_n_i)
begin
    if rising_edge(clk_i) then
        if reset_n_i = '0' then
            error_comb_n <= '0';
        else
            error_comb_n <= and_reduce(error_n_i);    
        end if;
    end if;      
end process;
 
-- purpose: main combination of active low and high errors
-- inputs:  clk_i, reset_n_i, error_comb, error_comb_n
-- outputs: error_result 
main_proc: process(clk_i, reset_n_i, error_comb, error_comb_n)
begin
    if rising_edge(clk_i) then
        if reset_n_i = '0' then 
            error_result <= '1';
        elsif error_comb = '1' or error_comb_n = '0' then   
            error_result <= '1'; 
        else                
            error_result <= '0'; 
        end if;
    end if;        
end process;

-- purpose: generate needed Tristate Output Buffer instances
-- inputs:  pwm_i, error_result
-- outputs: pwm_o
generate_obuft_inst: for i in 0 to PWM_WIDTH-1 generate
    pwm_uvw_buf: component OBUFT
    port map (
        I => pwm_i(i),
        O => pwm_o(i),
        T => error_result
    );      
end generate;  

end rtl;
