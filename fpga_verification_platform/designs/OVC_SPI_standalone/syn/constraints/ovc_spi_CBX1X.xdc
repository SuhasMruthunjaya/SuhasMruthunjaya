####### Phase Current Measurement #######
set_property -dict {PACKAGE_PIN AA13 IOSTANDARD LVCMOS33} [get_ports PHX_CS_N_A1]
set_property -dict {PACKAGE_PIN AD11 IOSTANDARD LVCMOS33} [get_ports PHX_SCLK_A1]
set_property -dict {PACKAGE_PIN AB11 IOSTANDARD LVCMOS33} [get_ports PHX_RSCLK_A1]
set_property -dict {PACKAGE_PIN AD15 IOSTANDARD LVCMOS33} [get_ports PHU_SDO_A1]
set_property -dict {PACKAGE_PIN AG14 IOSTANDARD LVCMOS33} [get_ports PHV_SDO_A1]
set_property -dict {PACKAGE_PIN AD14 IOSTANDARD LVCMOS33} [get_ports PHW_SDO_A1]
####### Inverter Interface #######
set_property -dict {PACKAGE_PIN AD12 IOSTANDARD LVCMOS33} [get_ports GATE_UT_A1]
set_property -dict {PACKAGE_PIN AC12 IOSTANDARD LVCMOS33} [get_ports GATE_UB_A1]
set_property -dict {PACKAGE_PIN AE10 IOSTANDARD LVCMOS33} [get_ports GATE_VT_A1]
set_property -dict {PACKAGE_PIN AF11 IOSTANDARD LVCMOS33} [get_ports GATE_VB_A1]
set_property -dict {PACKAGE_PIN AF10 IOSTANDARD LVCMOS33} [get_ports GATE_WT_A1]
set_property -dict {PACKAGE_PIN AG11 IOSTANDARD LVCMOS33} [get_ports GATE_WB_A1]
set_property PACKAGE_PIN W13 [get_ports GATE_FLT_A1]
set_property IOSTANDARD LVCMOS33 [get_ports GATE_FLT_A1]
####### LEDs #######
set_property -dict {PACKAGE_PIN AE14 IOSTANDARD LVCMOS33} [get_ports LED4_GR]
set_property -dict {PACKAGE_PIN AE15 IOSTANDARD LVCMOS33} [get_ports LED4_RD]
####### PL UART Interface #######
set_property -dict {PACKAGE_PIN AA11 IOSTANDARD LVCMOS33} [get_ports UART2_TX]
set_property -dict {PACKAGE_PIN AA10 IOSTANDARD LVCMOS33} [get_ports UART2_RX]
###################### Debug Interface ######################
####### LVDS Debug Pins #######
#set_property -dict {PACKAGE_PIN AF7 IOSTANDARD LVCMOS18 SLEW FAST} [get_ports DEBUG0_LVDS_P]
#set_property -dict {PACKAGE_PIN AF6 IOSTANDARD LVCMOS18 SLEW FAST} [get_ports DEBUG0_LVDS_N]
#set_property -dict {PACKAGE_PIN AG9 IOSTANDARD LVCMOS18 SLEW FAST} [get_ports DEBUG1_LVDS_P]
#set_property -dict {PACKAGE_PIN AH9 IOSTANDARD LVCMOS18 SLEW FAST} [get_ports DEBUG1_LVDS_N]
#set_property -dict {PACKAGE_PIN AH8 IOSTANDARD LVCMOS18 SLEW FAST} [get_ports DEBUG2_LVDS_P]
#set_property -dict {PACKAGE_PIN AH7 IOSTANDARD LVCMOS18 SLEW FAST} [get_ports DEBUG2_LVDS_N]
#set_property -dict {PACKAGE_PIN AF8 IOSTANDARD LVCMOS18 SLEW FAST} [get_ports DEBUG3_LVDS_P]
#set_property -dict {PACKAGE_PIN AG8 IOSTANDARD LVCMOS18 SLEW FAST} [get_ports DEBUG3_LVDS_N]
# create clocks
create_clock -period 62.500 -name spi_rclk_a1 -waveform {0.000 31.250} [get_ports PHX_RSCLK_A1]
set_input_jitter [get_clocks -of_objects [get_ports PHX_RSCLK_A1]] 0.100
#create_clock -period 62.500 -name spi_rclk_a2 -waveform {0.000 31.250} [get_ports PHX_RSCLK_A2]
#set_input_jitter [get_clocks -of_objects [get_ports PHX_RSCLK_A2]] 0.100
# pwm carrier 64MHz
create_generated_clock -name pwm_carrier_clk -source [get_pins OVC_SPI_i/clk_wiz_0/inst/mmcme4_adv_inst/CLKIN1] -master_clock [get_clocks clk_pl_0] [get_pins OVC_SPI_i/clk_wiz_0/inst/mmcme4_adv_inst/CLKOUT0]
create_generated_clock -name spi_sclk_a1 -source [get_pins OVC_SPI_i/clk_wiz_0/clk_out1] -divide_by 4 -add -master_clock pwm_carrier_clk [get_pins OVC_SPI_i/SPI_module_A1/sclk]
create_generated_clock -name spi_rclk_a1 -source [get_pins OVC_SPI_i/clk_wiz_0/clk_out1] -divide_by 4 -add -master_clock pwm_carrier_clk [get_pins OVC_SPI_i/SPI_module_A1/U0/pl_rclk_rising_reg/Q]
create_generated_clock -name clk_125M -source [get_pins OVC_SPI_i/clk_wiz_0/inst/mmcme4_adv_inst/CLKIN1] -master_clock [get_clocks clk_pl_0] [get_pins OVC_SPI_i/clk_wiz_0/inst/mmcme4_adv_inst/CLKOUT1]
create_generated_clock -name test_clk -source [get_pins OVC_SPI_i/clk_wiz_0/inst/mmcme4_adv_inst/CLKOUT1] -multiply_by 1 -add -master_clock [get_clocks clk_125M] [get_pins {OVC_SPI_i/util_ds_buf_1/BUFGCE_O[0]}]

set_max_delay -datapath_only -from [get_clocks clk_pl_0] -to [get_clocks pwm_carrier_clk] 15.000
set_max_delay -datapath_only -from [get_clocks pwm_carrier_clk] -to [get_clocks clk_pl_0] 15.000
set_max_delay -datapath_only -from [get_clocks spi_sclk_a1] -to [get_clocks pwm_carrier_clk] 15.000
set_max_delay -datapath_only -from [get_clocks pwm_carrier_clk] -to [get_clocks spi_sclk_a1] 15.000
set_max_delay -datapath_only -from [get_clocks test_clk] -to [get_clocks pwm_carrier_clk] 15.000
set_max_delay -datapath_only -from [get_clocks pwm_carrier_clk] -to [get_clocks test_clk] 15.000
set_max_delay -datapath_only -from [get_clocks clk_125M] -to [get_clocks pwm_carrier_clk] 15.000
set_max_delay -datapath_only -from [get_clocks pwm_carrier_clk] -to [get_clocks clk_125M] 15.000

# SPI driver for Current Sense
set_clock_groups -asynchronous -group [get_clocks -of_objects [get_pins OVC_SPI_i/clk_wiz_0/inst/mmcme4_adv_inst/CLKOUT0]] -group [get_clocks spi_rclk_a1]

# SPI driver for Current Sense
####### IO Delays #######
set_input_delay -clock [get_clocks spi_rclk_a1] -min 1.000 [get_ports PHX_RSCLK_A1]
set_input_delay -clock [get_clocks spi_rclk_a1] -max 3.000 [get_ports PHX_RSCLK_A1]

set_input_delay -clock [get_clocks spi_rclk_a1] -min 1.000 [get_ports PHU_SDO_A1]
set_input_delay -clock [get_clocks spi_rclk_a1] -max 3.000 [get_ports PHU_SDO_A1]
set_input_delay -clock [get_clocks spi_rclk_a1] -min 1.000 [get_ports PHV_SDO_A1]
set_input_delay -clock [get_clocks spi_rclk_a1] -max 3.000 [get_ports PHV_SDO_A1]
set_input_delay -clock [get_clocks spi_rclk_a1] -min 1.000 [get_ports PHW_SDO_A1]
set_input_delay -clock [get_clocks spi_rclk_a1] -max 3.000 [get_ports PHW_SDO_A1]

set_output_delay -clock [get_clocks spi_sclk_a1] -min 1.000 [get_ports PHX_SCLK_A1]
set_output_delay -clock [get_clocks spi_sclk_a1] -max 3.000 [get_ports PHX_SCLK_A1]
set_output_delay -clock [get_clocks spi_sclk_a1] -min 1.000 [get_ports PHX_CS_N_A1]
set_output_delay -clock [get_clocks spi_sclk_a1] -max 3.000 [get_ports PHX_CS_N_A1]

#set_output_delay -clock [get_clocks test_clk] -min 1.000 [get_ports UART2_TX]
#set_output_delay -clock [get_clocks test_clk] -max 3.000 [get_ports UART2_TX]

#set_input_delay -clock [get_clocks test_clk] -min 1.000 [get_ports UART2_RX]
#set_input_delay -clock [get_clocks test_clk] -max 3.000 [get_ports UART2_RX]

# PWM Output Signals input and output delays
set_output_delay -clock [get_clocks pwm_carrier_clk] -min 1.000 [get_ports GATE_VB_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -max 3.000 [get_ports GATE_VB_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -min 1.000 [get_ports GATE_WB_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -max 3.000 [get_ports GATE_WB_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -min 1.000 [get_ports GATE_VT_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -max 3.000 [get_ports GATE_VT_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -min 1.000 [get_ports GATE_WT_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -max 3.000 [get_ports GATE_WT_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -min 1.000 [get_ports GATE_UB_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -max 3.000 [get_ports GATE_UB_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -min 1.000 [get_ports GATE_UT_A1]
set_output_delay -clock [get_clocks pwm_carrier_clk] -max 3.000 [get_ports GATE_UT_A1]

