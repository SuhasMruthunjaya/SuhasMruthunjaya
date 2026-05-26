LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_arith.all;
USE ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use std.standard.all;

entity spi_module_tb is 
generic(
    d_width: integer  := 14
);
end spi_module_tb;

architecture Behavioral of spi_module_tb is
    component SPI_module
        port(
            clk                        : IN     STD_LOGIC;                             --system clock                                                         
            reset_n                    : IN     STD_LOGIC;                             --asynchronous reset                                                   
            trigger_current_sensor     : IN     STD_LOGIC;                             --initiate transaction
                                                                                       --
            current_sense_en_i         : IN     STD_LOGIC;
            p_save                     : IN     STD_LOGIC;            
            clk_div                    : IN     STD_LOGIC_VECTOR(13 DOWNTO 0);         --system clock cycles per 1/2 period of sclk                                                                
            miso_0                     : IN     STD_LOGIC;                             --master in, slave out - line 0                                        
            miso_1                     : IN     STD_LOGIC;                             --master in, slave out - line 1                                        
            miso_2                     : IN     STD_LOGIC;                             --master in, slave out - line 2                                        
            pl_rclk                    : IN     STD_LOGIC;                             --return clock - data collected on this clock                          
            
            -- outputs                                                                                                                                  
            sclk                       : OUT    STD_LOGIC;                             --spi clock                                                            
            cs_n                       : OUT    STD_LOGIC;                             --chip select - active low                                                                                         
            wd_error_o                 : out    std_logic;
            trigger_current_processing : OUT    STD_LOGIC;                             --puls which triggers when transaction ends                            
                              
            current_adc_uvw_0          : OUT    STD_LOGIC_VECTOR(35 downto 0)         --36bit register - collects data which comes from all three MISO lines 
            );
    end component;
   
   constant CLK_PERIOD: time := 15.625 ns;
   constant TEST_CLK_PERIOD: time := 1 ns;
   
   signal clk, test_clk : std_logic := '0';
   signal reset_n : std_logic := '0';
   signal pl_rclk : std_logic := '0';
   signal trigger_current_sensor, cont : std_logic := '0';
   signal sclk, miso_0, miso_1, miso_2 : std_logic := '0';
   signal cs_n: std_logic := '1';
   signal clk_div : std_logic_vector(13 downto 0) := (others => '0');
   signal i : integer range 0 to 13;
   signal test : integer := 0;
   signal rand_num_0 : std_logic_vector(11 downto 0) :=(others => '0');
   signal rand_num_1 : std_logic_vector(11 downto 0) :=(others => '0');
   signal rand_num_2 : std_logic_vector(11 downto 0) :=(others => '0');
   signal miso_data_0, miso_data_1, miso_data_2 : std_logic_vector(13 downto 0) :=(others => '0');
   signal trigger_current_processing : std_logic := '0';
   signal current_adc_uvw_0 : std_logic_vector(35 downto 0) := (others => '0');
   signal test_signal: std_logic;
   constant delay_stages : integer := 40;
    signal shift_reg : std_logic_vector(delay_stages - 1 downto 0) := (others => '0');
    signal sense_en : std_logic:= '0';
    signal wd_error : std_logic;
    signal p_save_tb : std_logic := '0';
   
    begin
        clk <= not clk after CLK_PERIOD/2;
        reset_n <= '0', '1' after 800 ns;
        test_clk <= not test_clk after TEST_CLK_PERIOD/2;
        
        DUT: SPI_module
                port map(
                    clk => clk,
                    reset_n => reset_n,
                    
                    --inputs
                    trigger_current_sensor => trigger_current_sensor,
                    current_sense_en_i     => sense_en,
                    p_save                 => p_save_tb,
                    clk_div => clk_div,
                    miso_0 => miso_0,
                    miso_1 => miso_1,
                    miso_2 => miso_2,
                    pl_rclk => pl_rclk,

                    --outputs
                    cs_n => cs_n,
                    sclk => sclk,
                    current_adc_uvw_0 => current_adc_uvw_0,
                    wd_error_o => wd_error,
                    trigger_current_processing => trigger_current_processing                              
                );
                
            process(test_clk, reset_n) 
                begin
                    if(reset_n = '0') then
                        shift_reg <= (others => '0');
                        pl_rclk <= '0';
                    elsif(rising_edge(test_clk)) then
                        shift_reg <= shift_reg(delay_stages - 2 downto 0) & sclk;
                        pl_rclk <= shift_reg(delay_stages - 1);
                    end if;
            end process;     
            
            data_in_process: process
  
            begin   
               clk_div <= "00000000000010";
               
               rand_num_0 <= "101010101010"; --setting random value
               rand_num_1 <= "001100110011";
               rand_num_2 <= "000100000000";
               wait for 10 ns;
               miso_data_0 <= "00"&rand_num_0; -- concatenating random value with 0
               miso_data_1 <= "00"&rand_num_1; -- concatenating random value with 0
               miso_data_2 <= "00"&rand_num_2; -- concatenating random value with 0
               --wait for 100 ns;
               
               --wait for 100 ns;
               wait until reset_n = '1';
               p_save_tb <= '1';
               
               wait for 2000ns;
               p_save_tb <= '0';
               wait for 30ns;
               p_save_tb <= '1';               
               
               wait for 2000ns;
               sense_en <= '1';
                
                wait until rising_edge(pl_rclk);
                miso_0 <= '0';--miso_data_0(13);
                miso_1 <= '0';--miso_data_1(13);
                miso_2 <= '0';--miso_data_2(13);
                for i in 12 downto 0 loop
                wait until falling_edge(pl_rclk);
                wait for 30ns;
                miso_0 <= '0';--miso_data_0(i);
                miso_1 <= '0';--miso_data_1(i);
                miso_2 <= '0';--miso_data_2(i);
               end loop;
               
               wait until trigger_current_processing = '1';
               
--            --starting the data transmission / cpol = 0 and cpha = 0 - Data sampled on the rising edge
--            -- and shifted out on the falling edge
----               wait for 1000 ns;
              wait for 10 ns;
               
               rand_num_0 <= "110100011000"; -- set different random value
               rand_num_1 <= "111000111000";
               rand_num_2 <= "000000000010";
               
               wait for 10 ns;
               
               miso_data_0 <= "00"&rand_num_0; -- concatenating random value with 0
               miso_data_1 <= "00"&rand_num_1; -- concatenating random value with 0
               miso_data_2 <= "00"&rand_num_2; -- concatenating random value with 0
                
                wait until rising_edge(pl_rclk);
                miso_0 <= miso_data_0(13);
                miso_1 <= miso_data_1(13);
                miso_2 <= miso_data_2(13); 
                for i in 12 downto 0 loop 
                wait until falling_edge(pl_rclk);
                wait for 30ns;
                miso_0 <= miso_data_0(i);
                miso_1 <= miso_data_1(i);
                miso_2 <= miso_data_2(i);
               end loop;               
               
               wait until trigger_current_processing = '1';
                wait for 50 ns;
               
               rand_num_0 <= "111000110010"; -- set different random value
               rand_num_1 <= "000101001110";
               rand_num_2 <= "000000000011";
               
               wait for 10 ns;
               
               miso_data_0 <= "00"&rand_num_0; -- concatenating random value with 0
               miso_data_1 <= "00"&rand_num_1; -- concatenating random value with 0
               miso_data_2 <= "00"&rand_num_2; -- concatenating random value with 0
               
                wait until rising_edge(pl_rclk);
                miso_0 <= miso_data_0(13);
                miso_1 <= miso_data_1(13);
                miso_2 <= miso_data_2(13); 
                for i in 12 downto 0 loop
                wait until falling_edge(pl_rclk);
                wait for 30ns;
                miso_0 <= miso_data_0(i);
                miso_1 <= miso_data_1(i);
                miso_2 <= miso_data_2(i);
               end loop;
               
               wait until trigger_current_processing = '1';
               wait for 50 ns;
               
               rand_num_0 <= "101010101010"; -- set different random value
               rand_num_1 <= "111111111111";
               rand_num_2 <= "000000000100";
               
               wait for 10 ns;
               
               miso_data_0 <= "00"&rand_num_0; -- concatenating random value with 0
               miso_data_1 <= "00"&rand_num_1; -- concatenating random value with 0
               miso_data_2 <= "00"&rand_num_2; -- concatenating random value with 0
               
                wait until rising_edge(pl_rclk);
                miso_0 <= miso_data_0(13);
                miso_1 <= miso_data_1(13);
                miso_2 <= miso_data_2(13); 
                for i in 12 downto 0 loop
                wait until falling_edge(pl_rclk);
                wait for 30ns;
                miso_0 <= miso_data_0(i);
                miso_1 <= miso_data_1(i);
                miso_2 <= miso_data_2(i);
               end loop;
               
               wait until trigger_current_processing = '1';
               wait for 50 ns;
               
               rand_num_0 <= "000000000000"; -- set different random value
               rand_num_1 <= "101010100111";
               rand_num_2 <= "000000000101";
               
               wait for 10 ns;
               
               miso_data_0 <= "00"&rand_num_0; -- concatenating random value with 0
               miso_data_1 <= "00"&rand_num_1; -- concatenating random value with 0
               miso_data_2 <= "00"&rand_num_2; -- concatenating random value with 0
               
                
                wait until rising_edge(pl_rclk);
                miso_0 <= miso_data_0(13);
                miso_1 <= miso_data_1(13);
                miso_2 <= miso_data_2(13); 
                for i in 12 downto 0 loop
                wait until falling_edge(pl_rclk);
                wait for 30ns;
                miso_0 <= miso_data_0(i);
                miso_1 <= miso_data_1(i);
                miso_2 <= miso_data_2(i);
               end loop;               
               
               wait until trigger_current_processing = '1';
               wait for 50 ns;
               
               rand_num_0 <= "000000000000"; -- set different random value
               rand_num_1 <= "000000000000";
               rand_num_2 <= "000000000000";
               
               wait for 10 ns;
               
               miso_data_0 <= "00"&rand_num_0; -- concatenating random value with 0
               miso_data_1 <= "00"&rand_num_1; -- concatenating random value with 0
               miso_data_2 <= "00"&rand_num_2; -- concatenating random value with 0
               
                
                wait until rising_edge(pl_rclk);
                miso_0 <= miso_data_0(13);
                miso_1 <= miso_data_1(13);
                miso_2 <= miso_data_2(13); 
                for i in 12 downto 0 loop
                wait until falling_edge(pl_rclk);
                wait for 30ns;
                miso_0 <= miso_data_0(i);
                miso_1 <= miso_data_1(i);
                miso_2 <= miso_data_2(i);
               end loop;
               
               wait for 2000ns;
               p_save_tb <= '0';
               sense_en  <= '0';
               wait for 30ns;
               p_save_tb <= '1';
               wait for 3000ns;
               sense_en <= '1';
           
               wait for 5000ns;
            end process;

           trig_sense: process is
           begin  -- process trig_sense
             wait until rising_edge(clk);   
             trigger_current_sensor <= '1'; -- enabling the SPI - data can be transmitted 
              wait for CLK_PERIOD;
             trigger_current_sensor <='0';
              wait for 63*CLK_PERIOD;
             
           end process trig_sense;
   
    
 end Behavioral;  
