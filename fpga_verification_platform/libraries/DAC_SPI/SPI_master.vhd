----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 04/03/2025 10:02:47 AM
-- Design Name: 
-- Module Name: SPI_master - rtl
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
use IEEE.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity SPI_master is
  generic (
            N_databits       : integer := 24 
  );
  Port ( 
         clk                    : in  std_logic;
         rst_n                  : in  std_logic;
         MOSI                   : out std_logic;
         MISO                   : in  std_logic;
         SCLK                   : out std_logic;
         divider                : in  std_logic_vector(7 downto 0);
         cpol                   : in  std_logic;
         CS_n                   : out std_logic;
         start_trigger          : in  std_logic;
         data_out               : out std_logic_vector(N_databits-1 downto 0);
         data_in                : in  std_logic_vector(N_databits-1 downto 0);
         
         -- for debugging purposes
         debug_port             : out std_logic_vector( 3 downto 0) := (others => '0')
         --debug_port_sclk_active_status : out std_logic 
  );
end SPI_master;

architecture rtl of SPI_master is

    component edge_detect is
    port (
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic                      -- falling edge detect output
         );
    end component;
        
    component Serializer_SPI is
    generic (DATA_WIDTH : integer := 24);
    Port ( 
           clk : in std_logic;
           rst_n : in std_logic;
           start : in std_logic;
           input_sig : in std_logic_vector(DATA_WIDTH -1 downto 0);
           output_sig : out std_logic
         );
    end component;
    
    
    component Parallelizer is
      GENERIC (DATA_WIDTH : integer := 24); -- Generic parameter for the input signal
      Port (
                  clk       : IN std_logic;
                  rst_n     : IN std_logic;
                  data_in   : IN std_logic;
                  data_out  : OUT std_logic_vector(DATA_WIDTH-1 downto 0);
                  start     : IN std_logic
          );
    end component;

   signal SCLK_sig                                      : std_logic := '0';
   signal SCLK_active                                   : std_logic := '0';
   signal count                                         : integer := 0;
   signal MOSI_sig                                      : std_logic := 'Z';
   type   state_type is (st1_idle, st2_start, st3_transmitData, st4_end);
   signal current_state, next_state                     : state_type;
   signal chipSelectSig                                 : std_logic := '1';
   attribute fsm_encoding                               : string;
   attribute fsm_encoding of current_state, next_state  : signal is "sequential";
   signal redge_cs                                      : std_logic := '0';
   signal fedge_cs                                      : std_logic := '0';
   signal cs_down_trigger                               : std_logic := '0';
   signal redge_trigger                                 : std_logic := '0';
   signal fedge_trigger                                 : std_logic := '0';
--   signal redge_write_trigger                           : std_logic := '0';
--   signal fedge_write_trigger                           : std_logic := '0';   
   signal detect_trigger                                  : std_logic := '0';
--   signal write_trigger                                 : std_logic := '0';
   signal idleState                                     : std_logic := '0';
   signal startState                                    : std_logic := '0';
   signal redge_sclk                                    : std_logic := '0';
   signal fedge_sclk                                    : std_logic := '0';
   signal redge_sclk_active                             : std_logic := '0';
   signal fedge_sclk_active                             : std_logic := '0';   
   signal data_word                                     : std_logic_vector(23 downto 0) := (others => '0');                     
   signal transmitData_Finished                         : std_logic := '0';
   signal transmitDataState                             : std_logic := '0';
   signal endState                                      : std_logic := '0';
   signal data_serializer_start                         : std_logic := '0';
   signal data_serializer_out                           : std_logic := '0';
   signal delay_start                                   : std_logic := '0';
   signal data_length                                   : Integer := 0;
   signal sclk_count                                    : Integer := 0;
   signal delay_count                                   : Integer := 0;
   signal ref_count                                     : Integer := 0;
   signal data_parallelizer_start                       : std_logic := '0';
   signal data_parallelizer_out                         : std_logic_vector(23 downto 0) := (others => '0');
   
begin

  SCLK <= SCLK_sig;
  --MOSI <= MOSI_sig;
  CS_n <= chipSelectSig;
  data_word <= data_in;
  MOSI <= data_serializer_out when SCLK_active = '1' else cpol;
  data_length <= data_word'LENGTH;
  --data_out <= data_parallelizer_out when SCLK_active = '0';
  debug_port <= std_logic_vector(to_unsigned(state_type'pos(current_state),4));
  --debug_port_sclk_active_status <= SCLK_active;
  
  CS_ed             : edge_detect port map( rst => rst_n, clk => clk, inp => chipSelectSig, r_edge => redge_cs, f_edge => fedge_cs);
  start_trigger_ed   : edge_detect port map( rst => rst_n, clk => clk, inp => start_trigger, r_edge => redge_trigger,
                        f_edge => fedge_trigger);
--  write_trigger_ed  : edge_detect port map (rst => rst_n, clk => clk, inp => start_write_trigger, r_edge => redge_write_trigger,
--                  f_edge => fedge_write_trigger);
  SCLK_ed           : edge_detect port map( rst => rst_n, clk => clk, inp => SCLK_sig, r_edge => redge_sclk, f_edge => fedge_sclk);
  SCLK_active_ed    : edge_detect port map( rst => rst_n, clk => clk, inp => SCLK_active, r_edge => redge_sclk_active, f_edge => fedge_sclk_active);
  data_word_serializer_inst : Serializer_SPI generic map (DATA_WIDTH => 24) port map( clk => SCLK_Sig, rst_n => rst_n, 
                            start => data_serializer_start, input_sig => data_word, output_sig => data_serializer_out);
  mosi_parallelizer_inst :  Parallelizer generic map( DATA_WIDTH => 24) port map ( clk => SCLK_Sig, rst_n => rst_n,
                            start => data_parallelizer_start, data_in => MISO, data_out => data_parallelizer_out);                           
                                              
 
  capture_trigger : process(clk, rst_n)
  begin
      if rst_n = '0' then
          detect_trigger <= '0';
      elsif rising_edge(clk) then
          if redge_trigger = '1' then
              detect_trigger <= '1';
          end if;
          if  redge_cs = '1' then
              detect_trigger <= '0';
          end if;
      end if;
  end process capture_trigger;
   
  capture_CS_trigger : process(clk, rst_n)
  begin
      if rising_edge(clk) then
          if rst_n = '0' then
              cs_down_trigger <= '0';
          else
              if fedge_cs = '1' then
                  cs_down_trigger <= '1';
              end if;
              if  redge_cs = '1' then
                  cs_down_trigger <= '0';
              end if;
          end if;
      end if;
  end process capture_CS_trigger;
    
  sclk_counter : process (clk, rst_n)
  begin
     if rising_edge(clk) then
        if rst_n = '0' then
            sclk_count <= 0;
        else
            if redge_sclk = '1' then
                sclk_count <= sclk_count + 1;
            end if;
            if cs_down_trigger = '0' then
                sclk_count <= 0;
            end if;         
       end if;
    end if;                
  end process sclk_counter;
   
  sclk_stimulus : process(clk, rst_n)
  begin
      if rising_edge(clk) then
          if rst_n = '0' then
              count <= 0;
              SCLK_sig <= cpol;
              SCLK_active <= '0';
              ref_count  <= 0;
          elsif cs_down_trigger = '1' then
              if sclk_count < data_length then
                if divider = x"1" then
                   SCLK_sig <= not SCLK_sig;
                   SCLK_active <= '1';
                   ref_count <= 0;              -- reset ref_count while active
                else
                    if count = to_integer(unsigned(divider)) - 1 then
                        count <= 0;
                        SCLK_sig <= not SCLK_sig;
                        SCLK_active <= '1'; -- SCLK is active
                        ref_count <= 0; -- Reset ref_count while SCLK is active
                    else
                        count <= count + 1;
                    end if;
                end if;
              else
                  SCLK_sig <= cpol;
                  if ref_count < 1 then
                      ref_count <= ref_count + 1;
                      SCLK_active <= '1'; -- Keep SCLK_active high for 1 ref clock cycles
                  else
                      SCLK_active <= '0'; -- SCLK is inactive
                  end if;
              end if;
          else
              -- cs not active
              SCLK_sig <= cpol;
              count <= 0;
              SCLK_active <= '0';
              ref_count <= 0;
          end if;
      end if;
  end process sclk_stimulus;

    
  state_transition : process (clk, rst_n)
  begin
       if rising_edge(clk) then
            if rst_n = '0' then
                current_state <= st1_idle;
            else
                current_state <= next_state;
            end if;
       end if;
  end process state_transition;
  
  next_state_decode : process (current_state, fedge_cs, cs_down_trigger, SCLK_active, fedge_sclk_active, start_trigger, chipSelectSig)
  begin
        
       next_state <= current_state;
       
       case current_state is
           when st1_idle => 
                 if start_trigger = '1' then
                    next_state <= st2_start;
                 else 
                    next_state <= st1_idle;
                end if;
           when st2_start =>
                if cs_down_trigger = '1' then
                    next_state <= st3_transmitData;
                else
                    next_state <= st2_start;
                end if;
          when st3_transmitData =>
                if fedge_sclk_active = '1' then
                    next_state <= st4_end;
                else
                    next_state <= st3_transmitData;
                end if;
          when st4_end =>
                if chipSelectSig = '1' then
                    next_state <= st1_idle;
                else
                    next_state <= st4_end;
                end if;
          when others =>
                next_state <= st1_idle;
                 
       end case; 
                   
  end process next_state_decode;
  
  
  output_decode : process (current_state)
  begin
        
        idleState <= '0';
        startState <= '0';
        transmitDataState <= '0';
        endState <= '0';
        data_serializer_start <= '0';
        data_parallelizer_start <= '0';
         
        case current_state is
            when st1_idle => 
                 idleState <= '1';                 
            when st2_start =>
                 startState <= '1';                 
            when st3_transmitData =>
                 transmitDataState <= '1';
                 data_serializer_start <= '1';
                 data_parallelizer_start <= '1';
            when st4_end =>                                   
                 endState <= '1';
            when others =>
                  null;                        
        end case;
  
  end process output_decode;
 
  chip_select : process (clk)
  begin
        if rising_edge(clk) then
            if rst_n = '0' then
                chipSelectSig <= '1';
                delay_start <= '0';
             elsif startState = '1' then
                chipSelectSig <= '0';
             elsif endState = '1' then
--                delay_start <= '1';
--                if delay_count = 2 then
                    chipSelectSig <= '1';
--                    delay_start <= '0';
--                end if;
             end if;   
        end if;
  end process chip_select;
  
  
  MOSI_update : process (clk, rst_n)
  begin
        if rst_n = '0' then
            MOSI_sig <= 'Z';
        elsif rising_edge(clk) then
                 if transmitDataState = '1' then
                        if  fedge_sclk_active = '1' then
                            transmitData_Finished <= '1';
                        else
                            transmitData_Finished <= '0';
                        end if;                  
                 end if;
        end if;         
      
  end process MOSI_update; 
  
    
  data_out_update : process (clk)
  begin
        if falling_edge(clk) then
            if SCLK_active = '0' then
                data_out <= data_parallelizer_out;
            end if;
        end if;
  end process data_out_update;
  
                                                                                                                                                                                  
end rtl;
