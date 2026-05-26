--Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
--Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2023.1 (lin64) Build 3865809 Sun May  7 15:04:56 MDT 2023
--Date        : Tue Jul 15 13:06:32 2025
--Host        : LIABDIT18041 running 64-bit Ubuntu 18.04.6 LTS
--Command     : generate_target test_data_fsm_sim_wrapper.bd
--Design      : test_data_fsm_sim_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity test_data_fsm_sim_wrapper is
  port (
    clk_in : in STD_LOGIC;
    clk_125M : out STD_LOGIC_VECTOR(0 downto 0);
    clk_64M : out STD_LOGIC;
    pwm_uvw_top : out STD_LOGIC_VECTOR(2 downto 0);
    pwm_uvw_bot : out STD_LOGIC_VECTOR(2 downto 0);
    phu_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 );
    phv_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 );
    phw_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 );
    phx_data_ready_a1 : in STD_LOGIC;
    ovc_release_a1      :in STD_LOGIC;
    ovc_event_a1        :out STD_LOGIC;
    ovc_status_a1   :out STD_LOGIC_VECTOR(5 downto 0);
    test_mode_active : in STD_LOGIC;
    pl_uart_rx : in STD_LOGIC;
    pl_uart_tx : out STD_LOGIC;
    rst_n_in : in STD_LOGIC
  );
end test_data_fsm_sim_wrapper;

architecture STRUCTURE of test_data_fsm_sim_wrapper is
  component test_data_fsm_sim is
  port (
    pl_uart_tx : out STD_LOGIC;
    pl_uart_rx : in STD_LOGIC;
    clk_in : in STD_LOGIC;
    clk_125M : out STD_LOGIC_VECTOR(0 downto 0);
    clk_64M : out STD_LOGIC;
    rst_n_in : in STD_LOGIC;
    test_mode_active : in STD_LOGIC;
    pwm_uvw_top : out STD_LOGIC_VECTOR(2 downto 0);
    pwm_uvw_bot : out STD_LOGIC_VECTOR(2 downto 0);
    phx_data_ready_a1 : in STD_LOGIC;
    ovc_release_a1      :in STD_LOGIC;
    ovc_event_a1        :out STD_LOGIC;
    ovc_status_a1   :out STD_LOGIC_VECTOR(5 downto 0);
    phu_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 );
    phv_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 );
    phw_adc_a1 : in STD_LOGIC_VECTOR ( 11 downto 0 )
  );
  end component test_data_fsm_sim;
begin
test_data_fsm_sim_i: component test_data_fsm_sim
     port map (
      clk_in => clk_in,
      clk_125M => clk_125M,
      clk_64M => clk_64M,
      test_mode_active => test_mode_active,
      phu_adc_a1(11 downto 0) => phu_adc_a1(11 downto 0),
      phv_adc_a1(11 downto 0) => phv_adc_a1(11 downto 0),
      phw_adc_a1(11 downto 0) => phw_adc_a1(11 downto 0),
      phx_data_ready_a1 => phx_data_ready_a1,
      ovc_release_a1 => ovc_release_a1,
      ovc_event_a1 => ovc_event_a1,
      ovc_status_a1 => ovc_status_a1,
      pl_uart_rx => pl_uart_rx,
      pl_uart_tx => pl_uart_tx,
      rst_n_in => rst_n_in
    );
end STRUCTURE;
