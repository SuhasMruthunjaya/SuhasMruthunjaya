
set_false_path -from [get_clocks clk_pl_1] -to [get_ports LED1_N_PL]
set_false_path -from [get_clocks clk_pl_1] -to [get_ports LED2_N_PL]
set_false_path -from [get_clocks clk_pl_1] -to [get_ports LED3_N_PL]

####################################################################################
# Constraints from file : 'Mercury_XU5_auto_cc_1_clocks.xdc'
####################################################################################

create_generated_clock -name pwm_clk -source [get_pins Mercury_XU5_i/clk_wiz_1/inst/mmcme4_adv_inst/CLKIN1] -master_clock [get_clocks Mercury_XU5_i/clk_wiz_1/inst/clk_in1] [get_pins Mercury_XU5_i/clk_wiz_1/inst/mmcme4_adv_inst/CLKOUT0]
set_max_delay -datapath_only -from [get_clocks clk_pl_2] -to [get_clocks pwm_clk] 20.000
set_max_delay -datapath_only -from [get_clocks pwm_clk] -to [get_clocks clk_pl_2] 20.000


#connect_debug_port u_ila_1/probe0 [get_nets [list {Mercury_XU5_i/SPI_master_0/U0/SCLK_active_ed/FSM_onehot_current_state_reg[3]}]]

#set_property MARK_DEBUG false [get_nets {Mercury_XU5_i/SPI_master_0/U0/current_state[0]}]
#set_property MARK_DEBUG false [get_nets {Mercury_XU5_i/SPI_master_0/U0/current_state[1]}]

#set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
#set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
#set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
#connect_debug_port dbg_hub/clk [get_nets clk]
