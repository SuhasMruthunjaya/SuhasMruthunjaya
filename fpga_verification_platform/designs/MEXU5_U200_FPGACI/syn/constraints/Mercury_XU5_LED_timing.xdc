
set_false_path -from [get_clocks clk_pl_1] -to [get_ports LED1_N_PL]
set_false_path -from [get_clocks clk_pl_1] -to [get_ports LED2_N_PL]
set_false_path -from [get_clocks clk_pl_1] -to [get_ports LED3_N_PL]

####################################################################################
# Constraints from file : 'Mercury_XU5_auto_cc_1_clocks.xdc'
####################################################################################

#connect_debug_port u_ila_1/probe0 [get_nets [list {Mercury_XU5_i/SPI_master_0/U0/SCLK_active_ed/FSM_onehot_current_state_reg[3]}]]

#set_property MARK_DEBUG false [get_nets {Mercury_XU5_i/SPI_master_0/U0/current_state[0]}]
#set_property MARK_DEBUG false [get_nets {Mercury_XU5_i/SPI_master_0/U0/current_state[1]}]

#set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
#set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
#set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
#connect_debug_port dbg_hub/clk [get_nets clk]

# create clocks
# main FPGA diffeferntial clk 100MHz
create_clock -period 10.000 -name clk100_diff [get_ports CLK100_PL_P]
set_input_jitter [get_clocks -of_objects [get_ports CLK100_PL_P]] 0.100
# main FPGA single-ended clock 100MHz
create_generated_clock -name clk100 -source [get_ports CLK100_PL_P] -multiply_by 1 -add -master_clock [get_clocks clk100_diff] [get_pins {*/util_ds_buf_1/IBUF_OUT[0]}]
# main design and AXi clock 192MHz
create_generated_clock -name clk_main_192M -source [get_pins */clk_wiz_2/inst/mmcme4_adv_inst/CLKIN1] -master_clock [get_clocks clk100] [get_pins */clk_wiz_2/inst/mmcme4_adv_inst/CLKOUT0]
# main design clock 100MHz
create_generated_clock -name clk_main_100M -source [get_pins */clk_wiz_2/inst/mmcme4_adv_inst/CLKIN1] -master_clock [get_clocks clk100] [get_pins */clk_wiz_2/inst/mmcme4_adv_inst/CLKOUT1]
# I2C clock
create_generated_clock -name scl_internal -source [get_pins */clk_wiz_2/inst/mmcme4_adv_inst/CLKOUT1] -multiply_by 1 -divide_by 100 -add -master_clock [get_clocks clk_main_100M] [get_pins */I2C_0/U0/SCL_ed/f_edge]
# SPI SCLK
create_generated_clock -name sclk_internal -source [get_pins */clk_wiz_2/inst/mmcme4_adv_inst/CLKOUT0] -multiply_by 1 -divide_by 6 -add -master_clock [get_clocks clk_main_192M] [get_pins */SPI_master_0/U0/SCLK_sig_reg/Q]

set_max_delay -datapath_only -from [get_clocks sclk_internal] -to [get_clocks clk_main_192M] 15.000
set_max_delay -datapath_only -from [get_clocks clk_main_192M] -to [get_clocks sclk_internal] 15.000