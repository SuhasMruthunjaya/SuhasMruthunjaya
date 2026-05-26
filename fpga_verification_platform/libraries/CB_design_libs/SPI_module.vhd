LIBRARY ieee;                                                                                                                         
USE ieee.std_logic_1164.all;                                                                                                          
USE ieee.std_logic_arith.all;                                                                                                         
USE ieee.std_logic_unsigned.all;                                                                                                      
USE ieee.numeric_std.ALL;                                                                                                             
                                                                                                                                      
entity SPI_module is                                                                                                                  
  generic(                                                                                                                            
    d_width : integer := 14                                                     --! data bus width
    );                                                                                 
  port(  
    -- inputs                                                                                                                             
    clk                        : in     std_logic;                             --! system clock                                                         
    reset_n                    : in     std_logic;                             --! asynchronous reset                                                   
    trigger_current_sensor     : in     std_logic;                             --! initiate transaction                                                                                             
    current_sense_en_i         : in     std_logic;
    p_save                     : in     std_logic;                             --! Power Save signal for ADC supply     
    clk_div                    : in     std_logic_vector(13 DOWNTO 0);         --! system clock cycles per 1/2 period of sclk                                                                
    miso_0                     : in     std_logic;                             --! master in, slave out - line 0, Phase U
    miso_1                     : in     std_logic;                             --! master in, slave out - line 1, Phase V                                        
    miso_2                     : in     std_logic;                             --! master in, slave out - line 2, Phase W                                       
    pl_rclk                    : in     std_logic;                             --! return clock - data collected on this clock                          
    -- outputs                                                                                                                                  
    sclk                       : out    std_logic;                             --! spi clock                                                            
    cs_n                       : out    std_logic;                             --! chip select - active low                                                                                         
    wd_error_o                 : out    std_logic;
    trigger_current_processing : out    std_logic;                             --! puls which triggers when transaction ends                                                          
    current_adc_uvw_0          : out    std_logic_vector(35 downto 0)          --! 36bit register - collects data which comes from all three MISO lines                                     
);        
                                                                                            
end SPI_module;                                                                                                                       

architecture rtl of SPI_module is  

type fsm_spi_state is (reset, ready, execute_cal, execute, delay_cal, delay_0, delay_1);  --! state machine data type                              
signal state_reg, state_next     : fsm_spi_state;          --! current state
                                                                                                                                                                  
signal clk_ratio                      : integer;                                              --! current clk_div                                                                 
signal count                          : integer;                                              --! counter to trigger sclk from system clock                                       
signal clk_div_s                      : integer;                                                                                                                
signal clk_toggles                    : integer range 0 to d_width*2 + 1;                     --! count spi clock toggles  
signal clk_toggles_cal                : integer range 0 to (d_width+2)*2 + 1;                 --! count spi clock toggles for calibration                                      
signal assert_data                    : std_logic := '0';                                     --! '1' is tx sclk toggle, '0' is rx sclk toggle                                               
signal rx_buffer_0_next               : std_logic_vector(d_width-1 DOWNTO 0):= "00" & x"800";  --! receive data buffer 0 registered value                                                            
signal rx_buffer_1_next               : std_logic_vector(d_width-1 DOWNTO 0):= "00" & x"800";  --! receive data buffer 1 registered value                                                            
signal rx_buffer_2_next               : std_logic_vector(d_width-1 DOWNTO 0):= "00" & x"800";  --! receive data buffer 2 registered value                                                                                                                                                                           
signal sclk_intern_0                  : std_logic := '0';                                                                                                                                  
signal enable_s                       : std_logic := '0';                                       --! enable_s = '1' set busy signal to '1' and it is active until word is transfered 
signal spi_counter                    : std_logic_vector(3 downto 0) :=(others => '0');  --! spi counter, used for counting the collected data          

signal cpol, cpha                     : std_logic := '0';   

signal pl_rclk_rising                 : std_logic;                                       --! synchronized pl_rclk signal 
signal pl_rclk_prev                   : std_logic;                                       --! signal used for pl_rclk synchronization
signal reset_enable,spi_counter_reset : std_logic;                                       --! enable register reset signal and spi counter reset signal 

signal miso_0_s, miso_1_s, miso_2_s   : std_logic := '0';                                --! synchronized miso data signals
signal miso_0_s0, miso_1_s1, miso_2_s2: std_logic := '0';
                                                                                             
signal assert_data_n                  : std_logic := '0';
signal pl_rclk_s, pl_rclk_s1          : std_logic := '0';
signal pl_rclk_falling                : std_logic := '0';
signal pl_rclk_falling_en             : std_logic := '0';
signal current_sense_en               : std_logic := '0';
signal min_count_ready                : std_logic_vector(2 downto 0) := (others => '0');
signal min_count_ready_cnt            : std_logic := '0';
signal reset_enable_rising            : std_logic := '0';
signal reset_enable_prev              : std_logic := '0';
		                                                    
signal p_save_i                       : std_logic := '0';
signal p_save_i_prev                  : std_logic := '0';
signal p_save_rising                  : std_logic := '0';
signal reset_p_save_rising            : std_logic := '0';  
signal p_save_falling                 : std_logic := '0';
signal reset_p_save_falling           : std_logic := '0'; 
signal cal_cnt                        : std_logic_vector(3 downto 0) := (others => '0');
signal cal_cnt_en                     : std_logic := '0';
signal sclk_cal_en                    : std_logic := '0';

		                                                                                                                                                          
begin   
   
clk_div_s     <= conv_integer(clk_div); 

--! register which captures current sense enable
p_save_capture: process(clk, reset_n) 
begin
    if rising_edge(clk) then  
        if (reset_n = '0') then
            p_save_i <= '0';
        else        
            p_save_i <= p_save;
        end if;
    end if;
end process;

--! register which captures trigger current sensor next logic
p_save_edge_detect: process(clk, p_save_i) 
begin
    if rising_edge(clk) then
        if (p_save_i = '1' and p_save_i_prev = '0') then
            p_save_rising <= '1';
        elsif (reset_p_save_rising = '1') then
            p_save_rising <= '0';
        end if; 
        p_save_i_prev <=  p_save_i;
        if (p_save_i = '0' and p_save_i_prev = '1') then
            p_save_falling <= '1';
        elsif (reset_p_save_falling = '1') then
            p_save_falling <= '0';
        end if;        
    end if;    
end process;

--! MISO data double stage synchronizer
miso_proc: process(clk) is
begin
    if (rising_edge(clk)) then
        if(reset_n = '0') then
            miso_0_s  <= '0';
            miso_1_s  <= '0';
            miso_2_s  <= '0';
            miso_0_s0 <= '0';
            miso_1_s1 <= '0';
            miso_2_s2 <= '0';
        else
            miso_0_s  <= miso_0;
            miso_1_s  <= miso_1;
            miso_2_s  <= miso_2;
            miso_0_s0 <= miso_0_s;
            miso_1_s1 <= miso_1_s;
            miso_2_s2 <= miso_2_s;
        end if;
    end if;
end process;

--! Wright current data into output register
write_current_data: process(clk, spi_counter) is
begin   
    if rising_edge(clk) then  
        if (reset_n = '0') then
            current_adc_uvw_0           <= x"800800800";
            trigger_current_processing  <= '0';
        elsif (spi_counter = "1110") then
            current_adc_uvw_0           <= rx_buffer_2_next(11 downto 0)&rx_buffer_1_next(11 downto 0)&rx_buffer_0_next(11 downto 0);
            trigger_current_processing  <= '1';
        else
            trigger_current_processing  <= '0';   
        end if;
    end if;    
end process; 

--! Miso capture on RCLK
miso_pl_rclk: process(clk, reset_n)
begin			
    if (rising_edge(clk)) then
        if (reset_n = '0') then
          rx_buffer_0_next <= "00" & x"800";
          rx_buffer_1_next <= "00" & x"800";
          rx_buffer_2_next <= "00" & x"800";
        else
            if (pl_rclk_falling_en = '1' and current_sense_en = '1' and spi_counter >= "0010") then
                rx_buffer_0_next <= rx_buffer_0_next(d_width-2 downto 0) & miso_0_s0;
                rx_buffer_1_next <= rx_buffer_1_next(d_width-2 downto 0) & miso_1_s1;
                rx_buffer_2_next <= rx_buffer_2_next(d_width-2 downto 0) & miso_2_s2;
            end if; 
        end if;
    end if;
end process;

--! pl_rclk double stage synchronization
pl_rclk_sync: process(clk)
begin
    if (rising_edge(clk)) then
        if (reset_n = '0') then
            pl_rclk_s       <= '0';
            pl_rclk_rising  <= '0';
        else
            pl_rclk_s       <= pl_rclk;
            pl_rclk_rising  <= pl_rclk_s;
        end if;
     end if;
end process;   
  
--! register which captures current sense enable
current_sense_capture: process(clk, reset_n) 
begin
    if rising_edge(clk) then  
        if (reset_n = '0') then
            current_sense_en <= '0';
        else        
            current_sense_en <= current_sense_en_i;
        end if;
    end if;
end process;

--! register which captures trigger current sensor next logic
enable_capture: process(clk, trigger_current_sensor, reset_enable_rising, current_sense_en) 
begin
    if rising_edge(clk) then
        if (trigger_current_sensor = '1' and current_sense_en = '1') then
            enable_s <= '1';
        elsif (reset_enable_rising = '1') then
            enable_s <= '0';
        end if; 
    end if;    
end process;


--! Reset for the enable_s signal
rising_edge_detection_reset_enable: process(clk) 
begin
    if (rising_edge(clk)) then
       if (reset_enable = '1' and reset_enable_prev = '0') then
            reset_enable_rising <= '1';
       else
            reset_enable_rising <= '0';
       end if;
       reset_enable_prev <= reset_enable;
   end if;
end process;

--Return clock rising edge detector - need for the transition states inside the FSM  Marcels code
falling_edge_detection: process(clk) 
begin
    if (rising_edge(clk)) then
       if (pl_rclk_rising = '0' and pl_rclk_prev = '1') then
            pl_rclk_falling <= '1';
       else
            pl_rclk_falling <= '0';
       end if;
       pl_rclk_prev         <= pl_rclk_rising;
       pl_rclk_falling_en   <= pl_rclk_falling;
   end if;
end process;                                                                                                                                                      

--! SPI clock counter - counts 14 bits of input serial data. Also indication for FSM that transaction is completed
spi_clock_counter: process(clk, reset_n, trigger_current_sensor) 
begin
    if (rising_edge(clk)) then
        if (reset_n = '0') then
            spi_counter <=(others => '0');
        elsif trigger_current_sensor = '1' or (spi_counter = "1110") then
            spi_counter <= (others => '0');    
        elsif (pl_rclk_falling = '1' and current_sense_en = '1') then
            spi_counter <= spi_counter + 1 ;
        end if; 
    end if;
end process;
		
--! Counter for Minimum Clock Cycles in Ready State
min_count_proc: process(clk, min_count_ready_cnt)
begin
    if (rising_edge(clk)) then
        if (min_count_ready_cnt = '1' and min_count_ready < "111") then
            min_count_ready <= min_count_ready + 1;
        elsif (min_count_ready_cnt = '0') then
            min_count_ready <= (others => '0');
        end if;
    end if; 
end process;     

--! Counter for calibration End
cal_count_proc: process(clk, cal_cnt_en)
begin
    if (rising_edge(clk)) then
        if (cal_cnt_en = '1') then
            cal_cnt <= cal_cnt + 1;
        else
            cal_cnt <= (others => '0');
        end if;
    end if; 
end process;          		
    
--! Beginning of the FSM - first process FSM generation 
sync_proc: process(clk)
begin
  if (rising_edge(clk)) then
     if (reset_n = '0') then
        state_reg <= reset;
     else
        state_reg <= state_next;
     end if;
  end if;
end process;
   
--! Next state generation process
next_state_decode: process(state_reg, enable_s, min_count_ready, clk_toggles, clk_toggles_cal, cal_cnt, current_sense_en, p_save_rising, p_save_falling)
begin
  case (state_reg) is
    when reset =>
        if p_save_rising = '1' then
            state_next <= execute_cal;    
        else 
            state_next <= reset;
        end if;  
    when execute_cal =>
        if clk_toggles_cal = (d_width+2)*2 then
           state_next <= delay_cal;
        else
           state_next <= execute_cal;
        end if;        
    when delay_cal =>
        if cal_cnt = "1111" then
            state_next <= ready;
        else 
            state_next <= delay_cal;
        end if;        
    when ready =>
        if enable_s = '1' and min_count_ready = "111" then
           state_next <= execute;
        elsif p_save_falling = '1' and min_count_ready = "111" then
           state_next <= reset;   
        else
           state_next <= ready;
        end if;
    when execute =>
        if clk_toggles = d_width*2 then
           state_next <= delay_0;
        else
           state_next <= execute;
        end if;
    when delay_0 =>
        state_next <= delay_1;
    when delay_1 =>
        state_next <= ready;
    when others =>
        state_next <= reset;
    end case;
end process;

--! FSM output generation process
output_generation_proc: process(state_reg, min_count_ready, clk_toggles, cal_cnt)
begin
    case (state_reg) is
         when reset =>
            cs_n                        <= '1';
            assert_data                 <= not cpha;          
            reset_enable                <= '1';
            if (min_count_ready < "101") then
                min_count_ready_cnt     <= '1';  
            else
                min_count_ready_cnt     <= '0';
            end if;  
            cal_cnt_en                  <= '0';  
            reset_p_save_rising         <= '0'; 
            reset_p_save_falling        <= '0';  
            sclk_cal_en                 <= '0';           
         when execute_cal =>
            cs_n                        <= '0';
            assert_data                 <= not cpha;          
            reset_enable                <= '1';  
            min_count_ready_cnt         <= '0';
            cal_cnt_en                  <= '0';  
            reset_p_save_rising         <= '0';  
            reset_p_save_falling        <= '0'; 
            sclk_cal_en                 <= '1';
         when delay_cal =>
            if (cal_cnt < "0010") then
                cs_n                    <= '0';
            else
                cs_n                    <= '1'; 
            end if;
            assert_data                 <= not cpha;          
            reset_enable                <= '1';  
            min_count_ready_cnt         <= '0';
            cal_cnt_en                  <= '1';  
            reset_p_save_rising         <= '1';  
            reset_p_save_falling        <= '1';   
            sclk_cal_en                 <= '0';             
         when ready =>
            cs_n                        <= '1';
            assert_data                 <= not cpha;           
            reset_enable                <= '0';
            min_count_ready_cnt         <= '1'; 
            cal_cnt_en                  <= '0';  
            reset_p_save_rising         <= '0';  
            reset_p_save_falling        <= '0'; 
            sclk_cal_en                 <= '0';           
         when execute =>
            cs_n                        <= '0';
            assert_data                 <= '0';
            if clk_toggles >= 27 then
                reset_enable            <= '1';
            else
                reset_enable            <= '0'; 
            end if;       
            min_count_ready_cnt         <= '1';
            cal_cnt_en                  <= '0';  
            reset_p_save_rising         <= '0'; 
            reset_p_save_falling        <= '0';  
            sclk_cal_en                 <= '0';           
         when delay_0 =>
            cs_n                        <= '1';
            assert_data                 <= '0';
            reset_enable                <= '0';
            min_count_ready_cnt         <= '0'; 
            cal_cnt_en                  <= '0';  
            reset_p_save_rising         <= '0';  
            reset_p_save_falling        <= '0'; 
            sclk_cal_en                 <= '0';          
         when delay_1 =>
            cs_n                        <= '1';
            assert_data                 <= '0';
            reset_enable                <= '0';
            min_count_ready_cnt         <= '1'; 
            cal_cnt_en                  <= '0';  
            reset_p_save_rising         <= '0'; 
            reset_p_save_falling        <= '0';   
            sclk_cal_en                 <= '0';        
         when others =>
            cs_n                        <= '1';
            assert_data                 <= '0';
            reset_enable                <= '0';
            min_count_ready_cnt         <= '1'; 
            cal_cnt_en                  <= '0';  
            reset_p_save_rising         <= '0'; 
            reset_p_save_falling        <= '0'; 
            sclk_cal_en                 <= '0';           
    end case;
end process;

sclk_generation_block: process(clk) 
begin
    if (rising_edge(clk)) then
        if (reset_n = '0') then
            sclk_intern_0       <= '0';
        elsif enable_s = '1' and min_count_ready >= "110" and sclk_cal_en = '0' then          -- normal SPI transmission
            if (count = clk_ratio) then
                count           <= 1; 
                assert_data_n   <= not assert_data; 
                if (clk_toggles < (d_width*2)) then 
                  sclk_intern_0 <= not sclk_intern_0;                   --toggle spi clock
                  clk_toggles   <= clk_toggles + 1;
               else
                   sclk_intern_0 <= '0';
                   clk_toggles   <= (d_width*2);
               end if;
            else 
                count       <= count+1;
            end if; 
        elsif sclk_cal_en = '1' then                                            -- calibration phase
            if (count = clk_ratio) then
                count           <= 1; 
                assert_data_n   <= not assert_data; 
                if (clk_toggles_cal < ((d_width+2)*2)) then 
                  sclk_intern_0     <= not sclk_intern_0;               --toggle spi clock
                  clk_toggles_cal   <= clk_toggles_cal + 1;
               else
                   sclk_intern_0    <= '0';
                   clk_toggles_cal  <= ((d_width+2)*2);
               end if;
            else 
                count       <= count+1;
            end if;                              
        else
            sclk_intern_0   <= '0';
            clk_toggles     <= 0; 
            clk_toggles_cal <= 0;
            if(clk_div_s = 0) then
                clk_ratio   <= 1;
                count       <= 1;
            else
                clk_ratio <= clk_div_s;
                count     <= clk_div_s;
            end if;              
        end if; 
     end if;
end process; 
    
sclk <= sclk_intern_0;
wd_error_o <= '0';
  
end rtl;
