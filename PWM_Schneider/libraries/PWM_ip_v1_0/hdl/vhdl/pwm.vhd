----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 13.02.2023 16:44:11
-- Design Name: 
-- Module Name: pwm - rtl
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

LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity pwm is
port (  clk             : in std_logic;
        clk_enable      : in std_logic;
        reset           : in std_logic;
        Enable          : in std_logic;
        Deadtime        : in std_logic_vector (15 downto 0);
        Frequency       : in std_logic_vector (31 downto 0);
        Duty_U          : in std_logic_vector (15 downto 0);
        Duty_V          : in std_logic_vector (15 downto 0);
        Duty_W          : in std_logic_vector (15 downto 0);   
        ce_out          : out std_logic; 
        PWM_Trig        : out std_logic;            
        PWM_UH          : out std_logic;
        PWM_UL          : out std_logic;
        PWM_VH          : out std_logic;
        PWM_VL          : out std_logic;
        PWM_WH          : out std_logic;
        PWM_WL          : out std_logic;
        PWM_CntDir      : out std_logic;   
        PWM_Freq        : out std_logic_vector(31 downto 0)            
      );  
end pwm;

architecture rtl of pwm is

component pwm_carrier is
port (  clk             : in std_logic;
        rst             : in std_logic;
        frequency       : in std_logic_vector (31 downto 0);
        updn            : out std_logic;
        cnt_f           : out std_logic_vector (31 downto 0)              
    );
end component;    

component duty_cycle is
    port (  clk             : in std_logic;
            rst             : in std_logic;
            cnt_f           : in std_logic_vector(15 downto 0);
            duty            : in std_logic_vector(15 downto 0);
            PWM_OUT         : out std_logic
          );
end component;          

component dead_time is
    port ( rst      : in    std_logic;
           clk      : in    std_logic;
           pwm_in   : in    std_logic;
           pwm_out  : out   std_logic;
           tdead    : in    std_logic_vector(15 downto 0)         -- dynamic dead time setting -> number of clock cycles 
          );
end component;

component edge_detect is
    port (
            rst     : in      std_logic;                        -- edge detector reset unput
            clk     : in      std_logic;                        -- clock 
            inp     : in      std_logic;                        -- input signal
            r_edge  : out     std_logic;                        -- rising edge detect output
            f_edge  : out     std_logic                      -- falling edge detect output
         );
end component;  
   
signal cnt_f_16         : std_logic_vector(15 downto 0) := (others => '0');
signal cnt_f_32         : std_logic_vector(31 downto 0) := (others => '0');
signal t_redge          : std_logic;
signal t_fedge          : std_logic;
signal clock            : std_logic; 
signal clock_tmp        : std_logic; 
signal updown           : std_logic;
signal duty_ut          : std_logic_vector(15 downto 0) := (others => '0'); 
signal duty_vt          : std_logic_vector(15 downto 0) := (others => '0');
signal duty_wt          : std_logic_vector(15 downto 0) := (others => '0');  
signal PWM_OUT_U        : std_logic := '0';
signal not_PWM_OUT_U    : std_logic := '0';
signal PWM_OUT_V        : std_logic := '0';
signal not_PWM_OUT_V    : std_logic := '0';
signal PWM_OUT_W        : std_logic := '0';
signal not_PWM_OUT_W    : std_logic := '0';
signal PWM_UT_buf       : std_logic_vector (1 downto 0);
signal PWM_VT_buf       : std_logic_vector (1 downto 0);
signal PWM_WT_buf       : std_logic_vector (1 downto 0);

begin
    CD: clock_divider port map(clk => clk, reset => reset, clock_out => clock_tmp);
    clock <= clock_tmp when clk_enable = '1' else '0';
    ce_out <= clk_enable;
    PWM_Freq <= Frequency;
    
    PWM_C: pwm_carrier port map (rst => reset, clk => clock, updn => updown, frequency  => Frequency, cnt_f => cnt_f_32);
        
    D_U: duty_cycle port map (rst => reset, clk => clock, cnt_f => cnt_f_16, duty => duty_ut, PWM_OUT => PWM_OUT_U);    
    D_V: duty_cycle port map (rst => reset, clk => clock, cnt_f => cnt_f_16, duty => duty_vt, PWM_OUT => PWM_OUT_V); 
    D_W: duty_cycle port map (rst => reset, clk => clock, cnt_f => cnt_f_16, duty => duty_wt, PWM_OUT => PWM_OUT_W); 
             
    cnt_f_16 <= cnt_f_32(31 downto 16);
    PWM_CntDir <= updown;
    
    DT: process(updown, reset)
    begin
        if reset = '0' then
            duty_ut <= (others => '0');
            duty_vt <= (others => '0');
            duty_wt <= (others => '0');
        elsif rising_edge(updown) then
            duty_ut <= Duty_U;
            duty_vt <= Duty_V;
            duty_wt <= Duty_W;
        end if;
        if reset = '0' then
            duty_ut <= (others => '0');
            duty_vt <= (others => '0');
            duty_wt <= (others => '0');
        elsif falling_edge(updown) then
            duty_ut <= Duty_U;
            duty_vt <= Duty_V;
            duty_wt <= Duty_W;
        end if;            
    end process;    
      
    Ted: edge_detect port map( rst => reset, clk => clock, inp => updown, r_edge => t_redge, f_edge => t_fedge);
    
    PWM_Trig <= t_redge OR t_fedge;
    
    not_PWM_OUT_U <= not PWM_OUT_U;
    not_PWM_OUT_V <= not PWM_OUT_V;
    not_PWM_OUT_W <= not PWM_OUT_W;
    
    Uhs: dead_time port map( pwm_in => PWM_OUT_U, pwm_out => PWM_UT_buf(0), clk => clock, rst => reset, tdead => Deadtime ); 
    Uls: dead_time port map( pwm_in => not_PWM_OUT_U, pwm_out => PWM_UT_buf(1), clk => clock, rst => reset, tdead => Deadtime ); 
    
    Vhs: dead_time port map( pwm_in => PWM_OUT_V, pwm_out => PWM_VT_buf(0), clk => clock, rst => reset, tdead => Deadtime ); 
    Vls: dead_time port map( pwm_in => not_PWM_OUT_V, pwm_out => PWM_VT_buf(1), clk => clock, rst => reset, tdead => Deadtime ); 
    
    Whs: dead_time port map( pwm_in => PWM_OUT_W, pwm_out => PWM_WT_buf(0), clk => clock, rst => reset, tdead => Deadtime ); 
    Wls: dead_time port map( pwm_in => not_PWM_OUT_W, pwm_out => PWM_WT_buf(1), clk => clock, rst => reset, tdead => Deadtime );
    
    PWM_UH <= PWM_UT_buf(0) when Enable = '1' else '0'; 
    PWM_UL <= PWM_UT_buf(1) when Enable = '1' else '0';     
    PWM_VH <= PWM_VT_buf(0) when Enable = '1' else '0'; 
    PWM_VL <= PWM_VT_buf(1) when Enable = '1' else '0';   
    PWM_WH <= PWM_WT_buf(0) when Enable = '1' else '0'; 
    PWM_WL <= PWM_WT_buf(1) when Enable = '1' else '0';           
end rtl;
