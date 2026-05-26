----------------------------------------------------------------------------------
-- Company:  Schneider Electric - Marktheidenfeld                
-- Engineer:  Suhas Bangalore Mruthunjaya (SESA807379)
-- 
-- Create Date: 02/19/2025 03:03:08 PM
-- Design Name: 
-- Module Name: I2C - rtl
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity I2C is
  Port ( 
    clk : in std_logic;
    rst_n : in std_logic;
    start_read_trigger : in std_logic;
    start_write_trigger : in std_logic;
    slave_address: in std_logic_vector (6 downto 0);
    reg_address: in std_logic_vector (15 downto 0);
    regSel : in std_logic;
    data : in std_logic_vector( 7 downto 0);
    stop_trigger : in std_logic;
    --SCL : out std_logic;
    SCL_in_internal : in std_logic := 'Z';
    SCL_out_internal : out std_logic := 'Z';
    SCL_tristate : out std_logic := '0';
    --SDA : inout std_logic;
    SDA_out_internal : out std_logic := 'Z';
    SDA_in_internal : in std_logic := 'Z';
    SDA_tristate : out std_logic := '0';
    
    -- only for debugging purposes
    debug_port : out std_logic_vector( 15 downto 0) := (others => '0')
    );
end I2C;

architecture rtl of I2C is


    component edge_detect is
    port (
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic                      -- falling edge detect output
         );
    end component;
    
    component Serializer is
    generic (DATA_WIDTH : integer);
    Port ( 
           clk : in std_logic;
           rst_n : in std_logic;
           start : in std_logic;
           input_sig : in std_logic_vector(DATA_WIDTH -1 downto 0);
           output_sig : out std_logic;
           done : out std_logic
         );
    end component;
    
    component IOBUF is
    port (
      I : in STD_LOGIC;
      O : out STD_LOGIC;
      T : in STD_LOGIC;
      IO : inout STD_LOGIC
    );
  end component IOBUF;
    
    signal count : integer := 0;
    signal hd_counter : integer := 0;
    signal hd_count_start : std_logic := '0';
    signal hd_count_done : std_logic := '0';
    signal SCL_signal : std_logic := '1';
    signal SCL_start_signal : std_logic := '0';
    signal SDA_signal : std_logic := 'Z';
    signal SDA_signal_drive_low : std_logic := '0';
    signal start_State : std_logic := '0';
    signal idle_State : std_logic := '0';
    signal transmitSlaveAddress_State : std_logic := '0';
    signal transmitSlaveAddress_Finished : std_logic := '0';
    signal readWrite_State : std_logic := '0';
    signal readWriteData_State : std_logic := '0';
    --signal readWriteBit_Finished : std_logic := '0';
    signal acknowledgement_State : std_logic := '0';
    signal registerAcknowledgement_State : std_logic := '0';
    signal dataAcknowledgement_State : std_logic := '0';
    signal serializer_start : std_logic := '0';
    signal serializer_out : std_logic := '0';
    signal serializer_done : std_logic := '0';
    signal readOp_slave_serializer_start : std_logic := '0';
    signal readOp_slave_serializer_out : std_logic := '0';
    signal readOp_slave_serializer_done : std_logic := '0';
    signal reg_lowByte_serializer_start : std_logic := '0';
    signal reg_lowByte_serializer_out : std_logic := '0';
    signal reg_lowByte_serializer_done : std_logic := '0';
    signal reg_highByte_serializer_start : std_logic := '0';
    signal reg_highByte_serializer_out : std_logic := '0';
    signal reg_highByte_serializer_done : std_logic := '0';
    signal data_serializer_start : std_logic := '0';
    signal data_serializer_out : std_logic := '0';
    signal data_serializer_done : std_logic := '0';
    signal transmitRegisterAddress_lowByte_State : std_logic := '0';
    signal transmitRegisterAddress_highByte_State : std_logic := '0';
    signal transmitRegisterAddress_Finished : std_logic := '0';
    signal readWriteData_Finished : std_logic := '0';
    signal readData_Finished : std_logic := '0';
    signal transmitData_Finished : std_logic := '0';
    type state_type is (st1_idle, st2_start, st3_transmitSlaveAddress, st4_readWrite, st5_transmitRegisterAddress_lowByte, st6_readWriteData, 
                        st7_stop, acknowledgement, registerAcknowledgement_lowByte, st5_transmitRegisterAddress_highByte, registerAcknowledgement_highByte,
                        dataAcknowledgement);
    signal current_state, next_state : state_type;
    type readOp_state_type is (st1_readOp_idle, st2_readOp_start, st3_readOp_transmitSlaveAddress, st4_readOP_readWrite, readOp_acknowledgement, st5_readOp_readData, st6_readOp_stop); 
    signal readOp_current_state, readOp_next_state : readOp_state_type;
    signal redge_sda : std_logic := '0';
    signal fedge_sda : std_logic := '0';
    signal redge_scl : std_logic := '0';
    signal fedge_scl : std_logic := '0';
    signal redge_read_trigger : std_logic := '0';
    signal fedge_read_trigger : std_logic := '0';
    signal redge_write_trigger : std_logic := '0';
    signal fedge_write_trigger : std_logic := '0';
    signal stop_State: std_logic := '0';
    signal read_trigger : std_logic := '0';
    signal start_read_operation : std_logic := '0';
    signal write_trigger : std_logic := '0';
    signal stop_trigger_sig : std_logic := '0';
    signal redge_stop_trigger : std_logic := '0';
    signal fedge_stop_trigger : std_logic := '0';
    signal count_fscl : integer := 0;
    signal reg_address_lowByte : std_logic_vector(7 downto 0) := (others => '0');
    signal reg_address_highByte : std_logic_vector(7 downto 0) := (others => '0');
    signal readOp_idle_State : std_logic := '0';
    signal readOp_start_State : std_logic := '0';
    signal readOp_transmitSlaveAddress_State : std_logic := '0';
    signal readOp_readWrite_State : std_logic := '0';
    signal readOp_acknowledgement_State : std_logic := '0';
    signal readOp_readData_State : std_logic := '0';
    signal readOp_stop_State : std_logic := '0';
      
        
begin
    
SCL_out_internal <= SCL_signal;
reg_address_lowByte <= reg_address(7 downto 0);
reg_address_highByte <= reg_address(15 downto 8);
debug_port <= std_logic_vector(to_unsigned(state_type'pos(current_state),16));


SCL_ed : edge_detect port map( rst => rst_n, clk => clk, inp => SCL_signal, r_edge => redge_scl, f_edge => fedge_scl);
read_trigger_ed : edge_detect port map( rst => rst_n, clk => clk, inp => start_read_trigger, r_edge => redge_read_trigger,
                  f_edge => fedge_read_trigger);
write_trigger_ed : edge_detect port map (rst => rst_n, clk => clk, inp => start_write_trigger, r_edge => redge_write_trigger,
                  f_edge => fedge_write_trigger);
stop_trigger_ed : edge_detect port map (rst => rst_n, clk => clk, inp => stop_trigger, r_edge => redge_stop_trigger,
                  f_edge => fedge_stop_trigger);
serializer_inst : Serializer generic map (DATA_WIDTH => 7) port map( clk => fedge_scl, rst_n => rst_n, 
                    start => serializer_start, input_sig => slave_address, output_sig => serializer_out, done => serializer_done);
readOp_slave_serializer_inst : Serializer generic map (DATA_WIDTH => 7) port map( clk => fedge_scl, rst_n => rst_n, 
                    start => readOp_slave_serializer_start, input_sig => slave_address, output_sig => readOp_slave_serializer_out, done => readOp_slave_serializer_done);                    
register_serializer_lowByte_inst : Serializer generic map (DATA_WIDTH => 8) port map( clk => fedge_scl, 
                   rst_n => rst_n, start => reg_lowByte_serializer_start, input_sig => reg_address_lowByte, output_sig => reg_lowByte_serializer_out, 
                   done => reg_lowByte_serializer_done);
register_serializer_highByte_inst : Serializer generic map (DATA_WIDTH => 8) port map( clk => fedge_scl, 
                   rst_n => rst_n, start => reg_highByte_serializer_start, input_sig => reg_address_highByte, output_sig => reg_highByte_serializer_out, 
                   done => reg_highByte_serializer_done);
data_serializer_inst : Serializer generic map (DATA_WIDTH => 8) port map( clk => fedge_scl, rst_n => rst_n, 
                   start => data_serializer_start, input_sig => data, output_sig => data_serializer_out, done => data_serializer_done);


capture_read_trigger : process(clk, rst_n)
begin
    if rst_n = '0' then
        read_trigger <= '0';
    elsif rising_edge(clk) then
        if redge_read_trigger = '1' then
            read_trigger <= '1';
        end if;
        if  stop_State = '1' then
            read_trigger <= '0';
        end if;
    end if;
end process capture_read_trigger;


capture_write_trigger : process(clk, rst_n)
begin
    if rst_n = '0' then
        write_trigger <= '0';
    elsif rising_edge(clk) then
        if redge_write_trigger = '1' then
            write_trigger <= '1';
        end if;
        if  stop_State = '1' then
            write_trigger <= '0';
        end if;
    end if;
end process capture_write_trigger;

capture_stop_trigger : process(clk, rst_n)
begin
    if rst_n = '0' then
        stop_trigger_sig <= '0';
    elsif rising_edge(clk) then
        if redge_stop_trigger = '1' then
            stop_trigger_sig <= '1';
        end if;
        if idle_State = '1' then 
            stop_trigger_sig <= '0';
        end if;
    end if;
end process capture_stop_trigger;

    
scl_stimulus : process(clk, rst_n)
begin
    if rst_n = '0' then
        count <= 0;
        SCL_signal <= '1';
        --SDA_signal <= '1';
    elsif rising_edge(clk) then
        if read_trigger = '1' or write_trigger = '1' then
            if count < 249 then
                count <= count + 1;
            else
                count <= 0;  -- Reset count after 250 cycles
            end if;

            -- Toggle SCL_signal based on the count
            if count < 125 then
                SCL_signal <= '1';  -- First 125 cycles ON
            else
                SCL_signal <= '0';  -- Next 125 cycles OFF
            end if;
        else
            SCL_signal <= '1';
            count <= 0;
        end if;
    end if;
end process scl_stimulus;


readOp_state_transition: process (clk, rst_n)
begin
    if rst_n = '0' then
        readOp_current_state <= st1_readOp_idle;
    elsif rising_edge(clk) then
        readOp_current_state <= readOp_next_state;
    end if;
end process readOp_state_transition;


state_transition : process (clk, rst_n)
begin 
    if rst_n = '0' then
        current_state <= st1_idle;
    elsif rising_edge(clk) then
        current_state <= next_state;
    end if;
end process state_transition;

readOp_next_state_decode : process(readOp_current_state, start_read_operation,SCL_signal, SDA_in_internal, transmitSlaveAddress_Finished,
                           fedge_scl, readData_Finished)
begin
    
    readOp_next_state <= readOp_current_state;
    
    case readOp_current_state is
        when st1_readOp_idle =>
            if start_read_operation = '1' then
                readOp_next_state <= st2_readOp_start;
            else
                readOp_next_state <= st1_readOp_idle;
            end if;
        when st2_readOp_start =>
           if SCL_signal = '1' and SDA_in_internal = '0' then
              readOp_next_state <= st3_readOp_transmitSlaveAddress;
           else
              readOp_next_state <= st2_readOp_start;
           end if;
        when st3_readOp_transmitSlaveAddress => 
            if transmitSlaveAddress_Finished = '1' then
                if fedge_scl = '1' then 
                    readOp_next_state <= st4_readOp_readWrite;
                else 
                    readOp_next_state <= st3_readOp_transmitSlaveAddress;
                end if;
            end if;
        when st4_readOp_readWrite => 
            if fedge_scl = '1' then
                readOp_next_state <= readOp_acknowledgement;
            else 
                readOp_next_state <= st4_readOp_readWrite;
            end if;
        when readOp_acknowledgement =>
             if fedge_scl = '1' then
                if  SDA_in_internal = '0' then
                    readOp_next_state <= st5_readOp_readData;
                else
                    readOp_next_state <= st6_readOp_stop;
                end if;
           else
                readOp_next_state <= readOp_acknowledgement;     
           end if;
        when st5_readOp_readData =>
             if readData_Finished = '1' then
                if fedge_scl = '1' then
                    readOp_next_state <= st6_readOp_stop;
                    --readWriteData_Finished <= '0';
                else 
                    readOp_next_state <= st5_readOp_readData;
                end if;
           end if;
       when st6_readOp_stop =>
            if fedge_scl = '1' then
                readOp_next_state <= st1_readOp_idle;
            else
                readOp_next_state <= st6_readOp_stop;   
            end if;
      when others => 
            readOp_next_state <= st1_readOp_idle;
                 
    end case;
    
end process readOp_next_state_decode;


next_state_decode : process(current_state, SCL_signal, SDA_in_internal, fedge_scl, redge_scl, transmitRegisterAddress_Finished, regSel,
                    start_read_trigger, start_write_trigger, read_trigger, write_trigger, transmitSlaveAddress_Finished, stop_trigger)
begin

    next_state <= current_state;

    case current_state is  
        when st1_idle =>
            if start_read_trigger = '1' or start_write_trigger = '1' then
                next_state <= st2_start;
            else 
                next_state <= st1_idle;
            end if;
        when st2_start =>
            if  SCL_signal = '1' and SDA_in_internal = '0' then
                next_state <= st3_transmitSlaveAddress;
            else 
                next_state <= st2_start;
            end if;
        when st3_transmitSlaveAddress => 
            if transmitSlaveAddress_Finished = '1' then
                if fedge_scl = '1' then 
                    next_state <= st4_readWrite;
                else 
                    next_state <= st3_transmitSlaveAddress;
                end if;
            end if;
        when st4_readWrite => 
            if fedge_scl = '1' then
                next_state <= acknowledgement;
            else 
                next_state <= st4_readWrite;
            end if;
        when acknowledgement =>
            if fedge_scl = '1' then
                if  SDA_in_internal = '0' then
                    if regSel = '0' then
                        next_state <= st5_transmitRegisterAddress_lowByte;
                    elsif regSel = '1' then
                        next_state <= st5_transmitRegisterAddress_highByte;
                    end if;
                else
                    next_state <= st7_stop;
                end if;
           else
                next_state <= acknowledgement;     
           end if;
        when st5_transmitRegisterAddress_lowByte => 
            if transmitRegisterAddress_Finished = '1' then
                if fedge_scl = '1' then 
                    next_state <= registerAcknowledgement_lowByte;
                else 
                    next_state <= st5_transmitRegisterAddress_lowByte;
                end if;
            end if;
        when registerAcknowledgement_lowByte =>
            if fedge_scl = '1' then
                if  SDA_in_internal = '0' then
                    next_state <= st6_readWriteData;
                else
                    next_state <= st7_stop;
                end if;
           else
                next_state <= registerAcknowledgement_lowByte;     
           end if;
       when st5_transmitRegisterAddress_highByte => 
            if transmitRegisterAddress_Finished = '1' then
                if fedge_scl = '1' then 
                    next_state <= registerAcknowledgement_highByte;
                else 
                    next_state <= st5_transmitRegisterAddress_highByte;
                end if;
            end if;
       when registerAcknowledgement_highByte =>
            if fedge_scl = '1' then
                if  SDA_in_internal = '0' then
                    next_state <= st5_transmitRegisterAddress_lowByte;
                else
                    next_state <= st7_stop;
                end if;
           else
                next_state <= registerAcknowledgement_highByte;     
           end if;
        when st6_readWriteData => 
            if readWriteData_Finished = '1' then
                if fedge_scl = '1' then
                    next_state <= dataAcknowledgement;
                else 
                    next_state <= st6_readWriteData;
                end if;
           end if;
        when dataAcknowledgement =>  
            if fedge_scl = '1' then
                if SDA_in_internal = '0' then
                    next_state <= st7_stop;
                end if;
            else 
                    next_state <= dataAcknowledgement;
            end if;   
         
        when st7_stop => 
           if stop_trigger_sig = '1' then
--            if fedge_scl = '1' then 
               next_state <= st1_idle;
            else 
               next_state <= st7_stop; 
--            end if;
           end if;
       
       when others =>
            next_state <= st1_idle;
            
                             
    end case;
end process next_state_decode;

readOp_output_decode : process(readOp_current_state)
begin
    readOp_idle_State                       <= '0';
    readOp_start_State                      <= '0';
    readOp_transmitSlaveAddress_State       <= '0';
    readOp_readWrite_State                  <= '0';
    readOp_acknowledgement_State            <= '0';
    readOp_readData_State                   <= '0';
    readOp_stop_State                       <= '0';
    readOp_slave_serializer_start           <= '0';
    
    case readOp_current_state is
        when st1_readOp_idle =>
            readOp_idle_State <= '1';
        when st2_readOp_start =>
            readOp_start_State <= '1';
        when st3_readOp_transmitSlaveAddress =>
            readOp_transmitSlaveAddress_State <= '1';
            readOp_slave_serializer_start <= '1';
        when st4_readOp_readWrite =>
            readOp_readWrite_State <= '1';
        when readOp_acknowledgement =>
            readOp_acknowledgement_State <= '1';
        when st5_readOp_readData =>
            readOp_readData_State <= '1';
        when st6_readOp_stop =>
            readOp_stop_State <= '1';
        when others =>
            null;               
    end case;


end process readOp_output_decode;

output_decode : process(current_state)
begin
    
    idle_State                             <=  '0';
    start_State                            <=  '0';
    serializer_start                       <=  '0';
    transmitSlaveAddress_State             <=  '0';
    readWrite_State                        <=  '0';
    acknowledgement_State                  <=  '0';
    reg_lowByte_serializer_start           <=  '0';
    reg_highByte_serializer_start          <=  '0';
    registerAcknowledgement_State          <=  '0';
    transmitRegisterAddress_lowByte_State  <=  '0';
    data_serializer_start                  <=  '0';
    transmitRegisterAddress_highByte_State <=  '0';
    readWriteData_State                    <=  '0';
    dataAcknowledgement_State              <=  '0';
    stop_State                             <=  '0';
    
    case current_state is  
        when st1_idle =>
            idle_State <= '1';
            
        when st2_start =>
            idle_State <= '0';
            start_State <= '1';
         
            
        when st3_transmitSlaveAddress => 
            start_State <= '0';
            serializer_start <= '1';
            transmitSlaveAddress_State <= '1';
            
        when st4_readWrite => 
            transmitSlaveAddress_State <= '0';
            readWrite_State <= '1';
        
        when acknowledgement =>
            readWrite_State <= '0';
            acknowledgement_State <= '1';
            if regSel = '0' then
                reg_lowByte_serializer_start <= '1';            -- why it takes one SCL to update ?
            elsif regSel = '1' then
                reg_highByte_serializer_start <= '1';
            end if;                  
            
        when st5_transmitRegisterAddress_lowByte => 
            if regSel = '0' then
                acknowledgement_State <= '0';
            elsif regSel = '1' then
                registerAcknowledgement_State <= '0';
            end if;
            reg_lowByte_serializer_start <= '1';
            transmitRegisterAddress_lowByte_State <= '1';
           
          
        when registerAcknowledgement_lowByte => 
            transmitRegisterAddress_lowByte_State <= '0';
            registerAcknowledgement_State <= '1';
            data_serializer_start <= '1';
            
            
       when st5_transmitRegisterAddress_highByte =>
            reg_highByte_serializer_start <= '1';
            transmitRegisterAddress_highByte_State <= '1';
            acknowledgement_State <= '0';
            
            
        when registerAcknowledgement_highByte => 
            transmitRegisterAddress_highByte_State <= '0';
            registerAcknowledgement_State <= '1';
            reg_lowByte_serializer_start <= '1';
                       
        when st6_readWriteData =>
            registerAcknowledgement_State <= '0';
            readWriteData_State <= '1';
            data_serializer_start <= '1';
       
        when dataAcknowledgement => 
            readWriteData_State <= '0';
            dataAcknowledgement_State <= '1';
        
                      
        when st7_stop => 
            dataAcknowledgement_State <= '0';
            stop_State <= '1';
            
       when others =>
            null;                            
    end case;
end process output_decode;

hd_counter_start: process(clk)
begin
    if rst_n = '0' then
        hd_count_start <= '0';
    elsif rising_edge(clk) then
        if fedge_scl = '1' then
            hd_count_start <= '1';
        elsif hd_count_done = '1' then
            hd_count_start <= '0';          
        end if;
    end if;    
end process hd_counter_start;

holdtime_counter : process(clk)
begin
    if rst_n = '0' then
        hd_counter <= 0;
        hd_count_done <= '0';
    elsif rising_edge(clk) then
        if hd_count_start = '1' then
            if hd_counter < 25 then
                hd_counter <= hd_counter + 1;
             else 
                hd_count_done <= '1';
            end if;
        else 
            hd_counter <= 0; 
            hd_count_done <= '0';   
        end if;
    end if;
end process holdtime_counter;


sda_stimulus : process(clk)
begin
    if rst_n = '0' then
        SDA_out_internal <= '1';
        SDA_tristate <= '0';
    elsif rising_edge(clk) then
       if start_State = '1' then
            SDA_out_internal <= '0';
            SDA_tristate <= '0';
       elsif transmitSlaveAddress_State = '1' then
            if hd_count_done = '1' then
                SDA_out_internal <= serializer_out;
                SDA_tristate <= '0';
            end if;
            if  serializer_done = '1' then
                transmitSlaveAddress_Finished <= '1';
            end if;          
       elsif readWrite_State = '1' then
            if hd_count_done = '1' then
                SDA_out_internal <= '0';
                SDA_tristate <= '0';
            end if;    
       elsif acknowledgement_State = '1' then
            if hd_count_done = '1' then
                transmitSlaveAddress_Finished <= '0';
                SDA_out_internal <= 'Z';
                SDA_tristate <= '1';
            end if;
       elsif transmitRegisterAddress_lowByte_State = '1' then
            if hd_count_done = '1' then
                SDA_out_internal <= reg_lowByte_serializer_out;
                SDA_tristate <= '0';
            end if;
            if  reg_lowByte_serializer_done = '1' then
                transmitRegisterAddress_Finished <= '1';
            end if;
       elsif registerAcknowledgement_State = '1' then
            if hd_count_done = '1' then
                SDA_out_internal <= 'Z';
                SDA_tristate <= '1';
                transmitRegisterAddress_Finished <= '0';
            end if;
       elsif transmitRegisterAddress_highByte_State = '1' then
            if hd_count_done = '1' then
                SDA_out_internal <= reg_highByte_serializer_out;
                SDA_tristate <= '0';
            end if;
            if  reg_highByte_serializer_done = '1' then
                transmitRegisterAddress_Finished <= '1';
            end if;
       elsif readWriteData_State = '1' then
            if write_trigger = '1' then
                if hd_count_done = '1' then
                    SDA_out_internal <= data_serializer_out;
                    SDA_tristate <= '0';
                end if;
                if data_serializer_done = '1' then
                    readWriteData_Finished <= '1';
                end if;
            elsif read_trigger = '1' then
            
           -- Read Operation States Handled Here ...
                  start_read_operation <= '1';
                  if readOp_idle_State = '1' then
                        SDA_out_internal <= '1';
                        SDA_tristate <= '0';
                  elsif readOp_start_State = '1' then
                        if redge_scl = '1' then
                            SDA_out_internal <= '0';
                            SDA_tristate <= '0';
                        end if;
                  elsif readOp_transmitSlaveAddress_State = '1' then
                        if hd_count_done = '1' then
                            SDA_out_internal <= readOp_slave_serializer_out;
                            SDA_tristate <= '0';
                        end if;
                        if  readOp_slave_serializer_done = '1' then
                            transmitSlaveAddress_Finished <= '1';
                        end if;
                  elsif readOp_readWrite_State = '1' then
                        if hd_count_done = '1' then
                            SDA_out_internal <= '1';
                            SDA_tristate <= '0';
                        end if;
                  elsif readOp_acknowledgement_State = '1' then
                        if hd_count_done = '1' then
                            transmitSlaveAddress_Finished <= '0';
                            SDA_out_internal <= 'Z';
                            SDA_tristate <= '1';
                        end if;
                  elsif readOp_readData_State = '1' then
                        SDA_out_internal <= 'Z';
                        SDA_tristate <= '1';
                        if fedge_scl = '1' then
                            count_fscl <= count_fscl + 1;
                            if count_fscl = 7 then
                                start_read_operation <= '0';
                                readData_Finished <= '1';
                                readWriteData_Finished <= '1';
                                count_fscl <= 0;
                            end if;
                        end if;
                  elsif readOp_stop_State = '1' then
                        start_read_operation <= '0';
                  
                  end if;

            end if;
       elsif dataAcknowledgement_State = '1' then
            readWriteData_Finished <= '0';
            if read_trigger = '1' then
               if hd_count_done = '1' then
                    SDA_out_internal <= '0';
                    SDA_tristate <= '0';
               end if;
            elsif write_trigger = '1' then
                if hd_count_done = '1' then
                    SDA_out_internal <= 'Z';
                    SDA_tristate <= '1';
                end if;
            end if;
       elsif stop_State = '1' then
--            if redge_scl = '1' then
               if hd_count_done = '1' then
                    SDA_out_internal <= '1';
                    SDA_tristate <= '0';
               end if;             
--            end if;                            
       end if;
   
    end if;
end process sda_stimulus;


end rtl;
