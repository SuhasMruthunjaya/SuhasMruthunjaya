# requires sourcing the settings.tcl to define the following variables:
# module (2CG or 4EV), PS_DDR, project_name, vivado_dir
# ########################################################################################
global PROJECT_ROOT
set PROJECT_ROOT $env(PROJECT_ROOT)
global PROJECT_DEST 
set PROJECT_DEST $env(PROJECT_DEST)
#global MATLAB_ROOT
#set MATLAB_ROOT $env(MATLAB_ROOT)
global CB_BOARD_REV
set BOARD_REVISION $env(CB_BOARD_REV)

puts PROJECT_ROOT=$PROJECT_ROOT
puts PROJECT_DEST=$PROJECT_DEST
#puts MATLAB_ROOT=$MATLAB_ROOT
puts BOARD_REVISION=$BOARD_REVISION

set ROOT_FOLDER $env(PROJECT_ROOT)
puts $ROOT_FOLDER

#global MATLAB_ROOT_FOLDER
#if { [info exists MATLAB_ROOT] } {
#	set MATLAB_FOLDER $MATLAB_ROOT
#} else {
#        puts "Warning: MATLAB_ROOT Environment must be set"
#	set MATLAB_FOLDER "./S4F_Matlab"
#}

# add source and constraints to corresponding fileset
# Set IP repository paths
set obj [get_filesets sources_1]
if { $obj != {} } {
	set_property IP_REPO_PATHS [subst {$PROJECT_ROOT/libraries}] $obj

# Rebuild user ip_repo's index before adding any source files
update_ip_catalog -rebuild
}

set project_name OVC_SPI_standalone

set vivado_dir ${project_name} 

set part xczu4cg-sfvc784-1-i

cd $PROJECT_DEST

 # Create project
create_project ${project_name} ${vivado_dir} -part ${part} -force

# Set project directory
set proj_dir [get_property DIRECTORY [current_project]]

# Set project properties
set_property "default_lib"        "xil_defaultlib" [current_project]
set_property "part"               "${part}"        [current_project]
set_property "simulator_language" "Mixed"          [current_project]
set_property "target_language"    "VHDL"           [current_project]

# Create filesets (if not found)
if {[string equal [get_filesets -quiet sources_1] ""]} {
    create_fileset -srcset sources_1
}
if {[string equal [get_filesets -quiet constrs_1] ""]} {
    create_fileset -srcset constrs_1
}
if {[string equal [get_filesets -quiet constrs_1] ""]} {
    create_fileset -simset sim_1
}
# add source and constraints to corresponding fileset
# Set IP repository paths
set obj [get_filesets sources_1]
if { $obj != {} } {
	set_property IP_REPO_PATHS [subst {{$ROOT_FOLDER/libraries/CB_design_libs} {$ROOT_FOLDER/libraries}}] $obj

# Rebuild user ip_repo's index before adding any source files
update_ip_catalog -rebuild
}
# Rebuild user ip_repo's index before adding any source files
update_ip_catalog -rebuild

add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/CB_design_libs/SPI_module.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/edge_detect.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/CB_design_libs/ovc_protect_module.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/CB_design_libs/pwm_off.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/toggle_signal.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/uart.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/CB_design_libs/test_data_fsm.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/CB_design_libs/test_data_fsm_sim_wrapper.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/designs/OVC_SPI_standalone/rtl/edge_detect_delay.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/designs/OVC_SPI_standalone/rtl/OVC_SPI_wrapper.vhd}]

add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/designs/OVC_SPI_standalone/rtl_tb/spi_module_tb.vhd}]
#add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/CB_design_libs/test_fsm_tb.vhd}]
#add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/CB_design_libs/test_data_fsm_tb.vhd}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/CB_design_libs/test_data_fsm_tb.sv}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/designs/OVC_SPI_standalone/sim/test_fsm_tb_behav.wcfg}]

set_property top test_data_fsm_tb [get_filesets sim_1]
set_property top_lib xil_defaultlib [get_filesets sim_1]
update_compile_order -fileset sim_1

# Settings File based on BOARD_REVISION
if { $BOARD_REVISION == "CBX1X"} {
    source $ROOT_FOLDER/designs/$project_name/syn/CBX1X_U003_MERGED_settings.tcl
}     

if { $BOARD_REVISION == "CBX4X"} {
    source $ROOT_FOLDER/designs/$project_name/syn/CBX4X_U003_MERGED_settings.tcl
} 

# re-create block design
# ################################################
create_bd_design OVC_SPI
# ################################################
 # Create interface ports
  set GPIO_EMIO [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gpio_rtl:1.0 GPIO_EMIO ]


  # Create ports
  set GATE_UVW_13 [ create_bd_port -dir O -from 5 -to 0 GATE_UVW_13 ]
  set CS_PC1 [ create_bd_port -dir O CS_PC1 ]
  set SDI0_PC1 [ create_bd_port -dir I SDI0_PC1 ]
  set SDI1_PC1 [ create_bd_port -dir I -type data SDI1_PC1 ]
  set SDI2_PC1 [ create_bd_port -dir I -type data SDI2_PC1 ]
  set RSCLK_PC1 [ create_bd_port -dir I RSCLK_PC1 ]
  set SCLK_PC1 [ create_bd_port -dir O SCLK_PC1 ]
  set GATE_FLT_A1 [ create_bd_port -dir I GATE_FLT_A1 ]
  set Rst_N [ create_bd_port -dir O -type rst Rst_N ]
  set axi_clk [ create_bd_port -dir O -type clk axi_clk ]
  set pl_uart0_tx [ create_bd_port -dir O pl_uart0_tx ]
  set pl_uart0_rx [ create_bd_port -dir I pl_uart0_rx ]
  set P_SAVE_EMIO [ create_bd_port -dir I P_SAVE_EMIO ]

  # Create instance: clk_wiz_0, and set properties
  set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_wiz_0 ]
  set_property -dict [list \
    CONFIG.CLKIN1_JITTER_PS {80.0} \
    CONFIG.CLKOUT1_DRIVES {Buffer} \
    CONFIG.CLKOUT1_JITTER {136.480} \
    CONFIG.CLKOUT1_PHASE_ERROR {96.948} \
    CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {64.00} \
    CONFIG.CLKOUT2_DRIVES {Buffer} \
    CONFIG.CLKOUT2_JITTER {119.348} \
    CONFIG.CLKOUT2_PHASE_ERROR {96.948} \
    CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {125.00} \
    CONFIG.CLKOUT2_USED {true} \
    CONFIG.CLKOUT3_DRIVES {Buffer} \
    CONFIG.CLKOUT3_JITTER {99.263} \
    CONFIG.CLKOUT3_PHASE_ERROR {96.948} \
    CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {100.000} \
    CONFIG.CLKOUT3_USED {false} \
    CONFIG.CLKOUT4_DRIVES {Buffer} \
    CONFIG.CLKOUT4_JITTER {99.263} \
    CONFIG.CLKOUT4_PHASE_ERROR {96.948} \
    CONFIG.CLKOUT4_REQUESTED_OUT_FREQ {100.000} \
    CONFIG.CLKOUT4_USED {false} \
    CONFIG.CLKOUT5_DRIVES {Buffer} \
    CONFIG.CLKOUT6_DRIVES {Buffer} \
    CONFIG.CLKOUT7_DRIVES {Buffer} \
    CONFIG.FEEDBACK_SOURCE {FDBK_AUTO} \
    CONFIG.MMCM_CLKFBOUT_MULT_F {8.000} \
    CONFIG.MMCM_CLKIN1_PERIOD {8.000} \
    CONFIG.MMCM_CLKIN2_PERIOD {10.0} \
    CONFIG.MMCM_CLKOUT0_DIVIDE_F {15.625} \
    CONFIG.MMCM_CLKOUT1_DIVIDE {8} \
    CONFIG.MMCM_CLKOUT2_DIVIDE {1} \
    CONFIG.MMCM_CLKOUT3_DIVIDE {1} \
    CONFIG.MMCM_DIVCLK_DIVIDE {1} \
    CONFIG.NUM_OUT_CLKS {2} \
    CONFIG.OPTIMIZE_CLOCKING_STRUCTURE_EN {true} \
    CONFIG.PRIM_IN_FREQ {125.000} \
    CONFIG.PRIM_SOURCE {No_buffer} \
    CONFIG.RESET_PORT {resetn} \
    CONFIG.RESET_TYPE {ACTIVE_LOW} \
    CONFIG.SECONDARY_SOURCE {Single_ended_clock_capable_pin} \
    CONFIG.USE_PHASE_ALIGNMENT {true} \
  ] $clk_wiz_0


  # Create instance: edge_detect_delay_0, and set properties
  set block_name edge_detect_delay
  set block_cell_name edge_detect_delay_0
  if { [catch {set edge_detect_delay_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $edge_detect_delay_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: util_vector_logic_0, and set properties
  set util_vector_logic_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_0 ]
  set_property -dict [list \
    CONFIG.C_OPERATION {xor} \
    CONFIG.C_SIZE {1} \
  ] $util_vector_logic_0


  # Create instance: util_vector_logic_1, and set properties
  set util_vector_logic_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_1 ]
  set_property CONFIG.C_SIZE {1} $util_vector_logic_1


  # Create instance: vio_A1, and set properties
  set vio_A1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_A1 ]
  set_property -dict [list \
    CONFIG.C_NUM_PROBE_IN {2} \
    CONFIG.C_NUM_PROBE_OUT {12} \
    CONFIG.C_PROBE_OUT10_WIDTH {2} \
    CONFIG.C_PROBE_OUT11_INIT_VAL {0x1} \
    CONFIG.C_PROBE_OUT11_WIDTH {1} \
    CONFIG.C_PROBE_OUT12_INIT_VAL {0x0} \
    CONFIG.C_PROBE_OUT12_WIDTH {1} \
    CONFIG.C_PROBE_OUT14_INIT_VAL {0x1} \
    CONFIG.C_PROBE_OUT1_INIT_VAL {0x0002} \
    CONFIG.C_PROBE_OUT1_WIDTH {14} \
    CONFIG.C_PROBE_OUT3_INIT_VAL {0x0} \
    CONFIG.C_PROBE_OUT3_WIDTH {1} \
    CONFIG.C_PROBE_OUT4_INIT_VAL {0x0} \
    CONFIG.C_PROBE_OUT4_WIDTH {1} \
    CONFIG.C_PROBE_OUT5_INIT_VAL {0x07D0} \
    CONFIG.C_PROBE_OUT5_WIDTH {13} \
    CONFIG.C_PROBE_OUT6_INIT_VAL {0x0FA07D03E8} \
    CONFIG.C_PROBE_OUT6_WIDTH {39} \
    CONFIG.C_PROBE_OUT7_INIT_VAL {0x40} \
    CONFIG.C_PROBE_OUT7_WIDTH {7} \
  ] $vio_A1


  # Create instance: xlconstant_1, and set properties
  set xlconstant_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_1 ]
  set_property CONFIG.CONST_VAL {0} $xlconstant_1


  # Create instance: PWM_ip_0, and set properties
  set PWM_ip_0 [ create_bd_cell -type ip -vlnv schneider-electric.com:ip:PWM_ip:1.0 PWM_ip_0 ]

  # Create instance: ps8_axi_periph, and set properties
  set ps8_axi_periph [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 ps8_axi_periph ]
  set_property CONFIG.NUM_MI {2} $ps8_axi_periph


  # Create instance: rst_ps8_125M, and set properties
  set rst_ps8_125M [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 rst_ps8_125M ]

  # Create instance: pwm_off_0, and set properties
  set block_name pwm_off
  set block_cell_name pwm_off_0
  if { [catch {set pwm_off_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $pwm_off_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  set_property CONFIG.ERROR_AH {3} $pwm_off_0
  
  # Create instance: ila_0, and set properties
  set ila_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_0 ]
  set_property -dict [list \
    CONFIG.C_DATA_DEPTH {65536} \
    CONFIG.C_EN_STRG_QUAL {1} \
    CONFIG.C_MONITOR_TYPE {Native} \
    CONFIG.C_NUM_OF_PROBES {15} \
  ] $ila_0


  # Create instance: xlslice_0, and set properties
  set xlslice_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_0 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {11} \
    CONFIG.DIN_WIDTH {36} \
  ] $xlslice_0


  # Create instance: xlslice_1, and set properties
  set xlslice_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_1 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {23} \
    CONFIG.DIN_TO {12} \
    CONFIG.DIN_WIDTH {36} \
  ] $xlslice_1


  # Create instance: xlslice_2, and set properties
  set xlslice_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_2 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {35} \
    CONFIG.DIN_TO {24} \
    CONFIG.DIN_WIDTH {36} \
  ] $xlslice_2


  # Create instance: toggle_signal_0, and set properties
  set block_name toggle_signal
  set block_cell_name toggle_signal_0
  if { [catch {set toggle_signal_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $toggle_signal_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: SPI_module_A1, and set properties
  set block_name SPI_module
  set block_cell_name SPI_module_A1
  if { [catch {set SPI_module_A1 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $SPI_module_A1 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: uart_0, and set properties
  set block_name uart
  set block_cell_name uart_0
  if { [catch {set uart_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $uart_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
    set_property -dict [list \
    CONFIG.baud_rate {921600} \
    CONFIG.clk_freq {125000000} \
    CONFIG.parity {0} \
  ] $uart_0


  # Create instance: util_ds_buf_1, and set properties
  set util_ds_buf_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_ds_buf:2.2 util_ds_buf_1 ]
  set_property CONFIG.C_BUF_TYPE {BUFGCE} $util_ds_buf_1


  # Create instance: edge_detect_0, and set properties
  set block_name edge_detect
  set block_cell_name edge_detect_0
  if { [catch {set edge_detect_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $edge_detect_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: OVC_PROTECT_IP_0, and set properties
  set OVC_PROTECT_IP_0 [ create_bd_cell -type ip -vlnv schneider-electric.com:user:OVC_PROTECT_IP:1.0 OVC_PROTECT_IP_0 ]

  # Create instance: fifo_generator_0, and set properties
  set fifo_generator_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:fifo_generator:13.2 fifo_generator_0 ]
  set_property -dict [list \
    CONFIG.Input_Data_Width {16} \
    CONFIG.Input_Depth {2048} \
    CONFIG.Output_Data_Width {8} \
    CONFIG.Performance_Options {Standard_FIFO} \
    CONFIG.Programmable_Full_Type {No_Programmable_Full_Threshold} \
    CONFIG.asymmetric_port_width {true} \
  ] $fifo_generator_0


  # Create instance: util_vector_logic_2, and set properties
  set util_vector_logic_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_2 ]
  set_property -dict [list \
    CONFIG.C_OPERATION {not} \
    CONFIG.C_SIZE {1} \
  ] $util_vector_logic_2


  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property -dict [list \
    CONFIG.IN0_WIDTH {3} \
    CONFIG.IN1_WIDTH {3} \
  ] $xlconcat_0


  # Create instance: axi_gpio_0, and set properties
  set axi_gpio_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio:2.0 axi_gpio_0 ]
  set_property -dict [list \
    CONFIG.C_ALL_OUTPUTS {1} \
    CONFIG.C_ALL_OUTPUTS_2 {1} \
    CONFIG.C_DOUT_DEFAULT_2 {0x00000001} \
    CONFIG.C_GPIO2_WIDTH {1} \
    CONFIG.C_GPIO_WIDTH {3} \
    CONFIG.C_IS_DUAL {1} \
  ] $axi_gpio_0


  # Create instance: xlslice_3, and set properties
  set xlslice_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_3 ]
  set_property CONFIG.DIN_WIDTH {3} $xlslice_3


  # Create instance: xlslice_4, and set properties
  set xlslice_4 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_4 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {1} \
    CONFIG.DIN_TO {1} \
    CONFIG.DIN_WIDTH {3} \
  ] $xlslice_4


  # Create instance: xlslice_5, and set properties
  set xlslice_5 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_5 ]
  set_property -dict [list \
    CONFIG.DIN_FROM {2} \
    CONFIG.DIN_TO {2} \
    CONFIG.DIN_WIDTH {3} \
  ] $xlslice_5
  
  
  # Create instance: test_data_fsm_0, and set properties
  set block_name test_data_fsm
  set block_cell_name test_data_fsm_0
  if { [catch {set test_data_fsm_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $test_data_fsm_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
   
  # Create instance: xlconcat_1, and set properties
  set xlconcat_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_1 ]
  set_property -dict [list \
    CONFIG.IN0_WIDTH {2} \
    CONFIG.IN1_WIDTH {1} \
  ] $xlconcat_1
   
    if { $BOARD_REVISION == "CBX1X"} {
        source $ROOT_FOLDER/designs/$project_name/syn/CBX1X_U003_MERGED_zynqmp.tcl
    }     

    if { $BOARD_REVISION == "CBX4X"} {
        source $ROOT_FOLDER/designs/$project_name/syn/CBX4X_U003_MERGED_zynqmp.tcl
    } 
  
  
  # Create interface connections
  connect_bd_intf_net -intf_net ps8_axi_periph_M00_AXI [get_bd_intf_pins ps8_axi_periph/M00_AXI] [get_bd_intf_pins OVC_PROTECT_IP_0/S_AXI_LITE]
  connect_bd_intf_net -intf_net ps8_axi_periph_M01_AXI [get_bd_intf_pins ps8_axi_periph/M01_AXI] [get_bd_intf_pins axi_gpio_0/S_AXI]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_GPIO_0 [get_bd_intf_ports GPIO_EMIO] [get_bd_intf_pins zynq_ultra_ps_e/GPIO_0]
  connect_bd_intf_net -intf_net zynq_ultra_ps_e_M_AXI_HPM0_LPD [get_bd_intf_pins zynq_ultra_ps_e/M_AXI_HPM0_LPD] [get_bd_intf_pins ps8_axi_periph/S00_AXI]

  # Create port connections
  connect_bd_net -net GATE_FLT_A1 [get_bd_ports GATE_FLT_A1] [get_bd_pins ila_0/probe6] [get_bd_pins pwm_off_0/error_n_i]
  connect_bd_net -net OVC_PROTECT_IP_0_ovc_event_o [get_bd_pins OVC_PROTECT_IP_0/ovc_event_o] [get_bd_pins vio_A1/probe_in0] [get_bd_pins ila_0/probe5] [get_bd_pins xlconcat_1/In1] [get_bd_pins test_data_fsm_0/ovc_event_a1_i]
  connect_bd_net -net OVC_PROTECT_IP_0_ovc_status_o [get_bd_pins OVC_PROTECT_IP_0/ovc_status_o] [get_bd_pins vio_A1/probe_in1] [get_bd_pins ila_0/probe4] [get_bd_pins test_data_fsm_0/ovc_status_a1_i]
  connect_bd_net -net P_SAVE_EMIO_1 [get_bd_ports P_SAVE_EMIO] [get_bd_pins SPI_module_A1/p_save] [get_bd_pins ila_0/probe10]
  connect_bd_net -net SPI_module_0_cs_n [get_bd_pins SPI_module_A1/cs_n] [get_bd_ports CS_PC1]
  connect_bd_net -net SPI_module_0_sclk [get_bd_pins SPI_module_A1/sclk] [get_bd_ports SCLK_PC1]
  connect_bd_net -net SPI_module_0_trans_end [get_bd_pins SPI_module_A1/trigger_current_processing] [get_bd_pins edge_detect_delay_0/inp] [get_bd_pins ila_0/probe0] [get_bd_pins OVC_PROTECT_IP_0/trigger_ovc_i] [get_bd_pins toggle_signal_0/start_sig] [get_bd_pins test_data_fsm_0/phx_data_ready_a1_i]
  connect_bd_net -net SPI_module_A1_current_adc_uvw_0 [get_bd_pins SPI_module_A1/current_adc_uvw_0] [get_bd_pins xlslice_2/Din] [get_bd_pins xlslice_1/Din] [get_bd_pins xlslice_0/Din] [get_bd_pins OVC_PROTECT_IP_0/current_raw_adc_i]
  connect_bd_net -net axi_gpio_0_gpio_io_o [get_bd_pins axi_gpio_0/gpio_io_o] [get_bd_pins xlslice_3/Din] [get_bd_pins xlslice_4/Din] [get_bd_pins xlslice_5/Din]
  connect_bd_net -net clk_wiz_0_clk_out1 [get_bd_pins clk_wiz_0/clk_out1] [get_bd_pins edge_detect_delay_0/clk] [get_bd_pins vio_A1/clk] [get_bd_pins PWM_ip_0/IPCORE_CLK] [get_bd_pins ila_0/clk] [get_bd_pins SPI_module_A1/clk] [get_bd_pins edge_detect_0/clk] [get_bd_pins OVC_PROTECT_IP_0/ovc_clk_i] [get_bd_pins pwm_off_0/clk_i] [get_bd_pins toggle_signal_0/clk_in] [get_bd_pins test_data_fsm_0/clk_64M_i]
  connect_bd_net -net clk_wiz_0_clk_out2 [get_bd_pins clk_wiz_0/clk_out2] [get_bd_pins util_ds_buf_1/BUFGCE_I]
  connect_bd_net -net clk_wiz_0_locked [get_bd_pins clk_wiz_0/locked] [get_bd_pins edge_detect_delay_0/rst] [get_bd_pins PWM_ip_0/IPCORE_RESETN] [get_bd_pins SPI_module_A1/reset_n] [get_bd_pins uart_0/reset_n] [get_bd_pins edge_detect_0/rst] [get_bd_pins OVC_PROTECT_IP_0/ovc_reset_n_i] [get_bd_pins util_vector_logic_2/Op1] [get_bd_pins pwm_off_0/reset_n_i] [get_bd_pins toggle_signal_0/rst_n] [get_bd_pins test_data_fsm_0/rst_n_i]
  connect_bd_net -net current_raw_U_A1 [get_bd_pins xlslice_0/Dout] [get_bd_pins ila_0/probe1] [get_bd_pins test_data_fsm_0/phu_adc_a1_i]
  connect_bd_net -net current_raw_V_A1 [get_bd_pins xlslice_1/Dout] [get_bd_pins ila_0/probe2] [get_bd_pins test_data_fsm_0/phv_adc_a1_i]
  connect_bd_net -net current_raw_W_A1 [get_bd_pins xlslice_2/Dout] [get_bd_pins ila_0/probe3] [get_bd_pins test_data_fsm_0/phw_adc_a1_i]
  connect_bd_net -net current_sense_en [get_bd_pins xlslice_3/Dout] [get_bd_pins SPI_module_A1/current_sense_en_i] [get_bd_pins ila_0/probe11]
  connect_bd_net -net edge_detect_0_r_edge [get_bd_pins edge_detect_0/r_edge] [get_bd_pins util_vector_logic_0/Op2]
  connect_bd_net -net edge_detect_delay_0_r_edge [get_bd_pins edge_detect_delay_0/r_edge] [get_bd_pins util_vector_logic_1/Op1]
  connect_bd_net -net fifo_generator_0_dout [get_bd_pins fifo_generator_0/dout] [get_bd_pins test_data_fsm_0/fifo_data_out_i]
  connect_bd_net -net fifo_generator_0_empty [get_bd_pins fifo_generator_0/empty] [get_bd_pins test_data_fsm_0/fifo_empty_i]
  connect_bd_net -net fifo_generator_0_full [get_bd_pins fifo_generator_0/full] [get_bd_pins test_data_fsm_0/fifo_full_i]
  connect_bd_net -net miso_0_1 [get_bd_ports SDI0_PC1] [get_bd_pins SPI_module_A1/miso_0]
  connect_bd_net -net miso_1_1 [get_bd_ports SDI1_PC1] [get_bd_pins SPI_module_A1/miso_1]
  connect_bd_net -net miso_2_1 [get_bd_ports SDI2_PC1] [get_bd_pins SPI_module_A1/miso_2]
  connect_bd_net -net pl_rclk_0_1 [get_bd_ports RSCLK_PC1] [get_bd_pins SPI_module_A1/pl_rclk]
  connect_bd_net -net pwm_dead_time [get_bd_pins vio_A1/probe_out7] [get_bd_pins PWM_ip_0/dead_time]
  connect_bd_net -net pwm_off_0_pwm_uvw_high_out [get_bd_pins pwm_off_0/pwm_o] [get_bd_ports GATE_UVW_13]
  connect_bd_net -net pwm_uvw_high [get_bd_pins PWM_ip_0/pwm_uvw_high_0] [get_bd_pins ila_0/probe7] [get_bd_pins xlconcat_0/In1]
  connect_bd_net -net pwm_uvw_low [get_bd_pins PWM_ip_0/pwm_uvw_low_0] [get_bd_pins ila_0/probe8] [get_bd_pins xlconcat_0/In0]
  connect_bd_net -net r5_errors [get_bd_pins vio_A1/probe_out10] [get_bd_pins xlconcat_1/In0]
  connect_bd_net -net rst_ps8_125M_peripheral_aresetn [get_bd_pins rst_ps8_125M/peripheral_aresetn] [get_bd_pins ps8_axi_periph/S00_ARESETN] [get_bd_pins ps8_axi_periph/M00_ARESETN] [get_bd_pins ps8_axi_periph/ARESETN] [get_bd_pins clk_wiz_0/resetn] [get_bd_pins OVC_PROTECT_IP_0/s_axi_lite_aresetn] [get_bd_pins ps8_axi_periph/M01_ARESETN] [get_bd_pins axi_gpio_0/s_axi_aresetn]
  connect_bd_net -net rx_0_1 [get_bd_ports pl_uart0_rx] [get_bd_pins uart_0/rx]
  connect_bd_net -net spi_clk_div [get_bd_pins vio_A1/probe_out1] [get_bd_pins SPI_module_A1/clk_div]
  connect_bd_net -net test_data_fsm_0_fifo_data_in [get_bd_pins test_data_fsm_0/fifo_data_in_o] [get_bd_pins fifo_generator_0/din]
  connect_bd_net -net test_data_fsm_0_fifo_rd_en [get_bd_pins test_data_fsm_0/fifo_rd_en_o] [get_bd_pins fifo_generator_0/rd_en]
  connect_bd_net -net test_data_fsm_0_fifo_wr_en [get_bd_pins test_data_fsm_0/fifo_wr_en_o] [get_bd_pins fifo_generator_0/wr_en]
  connect_bd_net -net test_data_fsm_0_ovc_release_a1_o [get_bd_pins test_data_fsm_0/ovc_release_a1_o] [get_bd_pins OVC_PROTECT_IP_0/ovc_release_i] [get_bd_pins ila_0/probe14]
  connect_bd_net -net test_data_fsm_0_pwm_duty_a1_o [get_bd_pins test_data_fsm_0/pwm_duty_a1_o] [get_bd_pins PWM_ip_0/pwm_compare_uvw_0]
  connect_bd_net -net test_data_fsm_0_pwm_enable_a1_o [get_bd_pins test_data_fsm_0/pwm_enable_a1_o] [get_bd_pins PWM_ip_0/enable]
  connect_bd_net -net test_data_fsm_0_pwm_freq_a1_o [get_bd_pins test_data_fsm_0/pwm_freq_a1_o] [get_bd_pins PWM_ip_0/period_compare]
  connect_bd_net -net test_data_fsm_0_uart_tx_data_o [get_bd_pins test_data_fsm_0/uart_tx_data_o] [get_bd_pins uart_0/tx_data]
  connect_bd_net -net test_data_fsm_0_uart_tx_trigger_o [get_bd_pins test_data_fsm_0/uart_tx_trigger_o] [get_bd_pins uart_0/tx_ena]
  connect_bd_net -net test_mode_active [get_bd_pins axi_gpio_0/gpio2_io_o] [get_bd_pins util_ds_buf_1/BUFGCE_CE] [get_bd_pins test_data_fsm_0/test_mode_active_i]
  connect_bd_net -net trans_end_toggle_out [get_bd_pins toggle_signal_0/toggle_out] [get_bd_pins ila_0/probe9]
  connect_bd_net -net trigger_current_sense_continuous [get_bd_pins xlslice_4/Dout] [get_bd_pins util_vector_logic_1/Op2] [get_bd_pins ila_0/probe12]
  connect_bd_net -net trigger_current_sensor [get_bd_pins xlslice_5/Dout] [get_bd_pins edge_detect_0/inp] [get_bd_pins ila_0/probe13]
  connect_bd_net -net uart_0_rx_busy [get_bd_pins uart_0/rx_busy] [get_bd_pins test_data_fsm_0/uart_rx_busy_i]
  connect_bd_net -net uart_0_rx_data [get_bd_pins uart_0/rx_data] [get_bd_pins test_data_fsm_0/uart_rx_data_i]
  connect_bd_net -net uart_0_rx_error [get_bd_pins uart_0/rx_error] [get_bd_pins test_data_fsm_0/uart_rx_error_i]
  connect_bd_net -net uart_0_tx [get_bd_pins uart_0/tx] [get_bd_ports pl_uart0_tx]
  connect_bd_net -net uart_0_tx_busy [get_bd_pins uart_0/tx_busy] [get_bd_pins test_data_fsm_0/uart_tx_busy_i]
  connect_bd_net -net util_ds_buf_1_BUFGCE_O [get_bd_pins util_ds_buf_1/BUFGCE_O] [get_bd_pins uart_0/clk] [get_bd_pins fifo_generator_0/clk] [get_bd_pins test_data_fsm_0/clk_125M_i]
  connect_bd_net -net util_vector_logic_0_Res [get_bd_pins util_vector_logic_0/Res] [get_bd_pins SPI_module_A1/trigger_current_sensor]
  connect_bd_net -net util_vector_logic_1_Res [get_bd_pins util_vector_logic_1/Res] [get_bd_pins util_vector_logic_0/Op1]
  connect_bd_net -net util_vector_logic_2_Res [get_bd_pins util_vector_logic_2/Res] [get_bd_pins fifo_generator_0/srst]
  connect_bd_net -net xlconcat_0_dout [get_bd_pins xlconcat_0/dout] [get_bd_pins pwm_off_0/pwm_i]
  connect_bd_net -net xlconcat_1_dout [get_bd_pins xlconcat_1/dout] [get_bd_pins pwm_off_0/error_i]
  connect_bd_net -net xlconstant_1_dout [get_bd_pins xlconstant_1/dout] [get_bd_pins PWM_ip_0/pwm_select_dead_time_calc]
  connect_bd_net -net zynq_ultra_ps_e_pl_clk0 [get_bd_pins zynq_ultra_ps_e/pl_clk0] [get_bd_pins ps8_axi_periph/ACLK] [get_bd_pins zynq_ultra_ps_e/maxihpm0_lpd_aclk] [get_bd_pins ps8_axi_periph/S00_ACLK] [get_bd_pins rst_ps8_125M/slowest_sync_clk] [get_bd_pins ps8_axi_periph/M00_ACLK] [get_bd_pins clk_wiz_0/clk_in1] [get_bd_ports axi_clk] [get_bd_pins OVC_PROTECT_IP_0/s_axi_lite_aclk] [get_bd_pins ps8_axi_periph/M01_ACLK] [get_bd_pins axi_gpio_0/s_axi_aclk]
  connect_bd_net -net zynq_ultra_ps_e_pl_resetn0 [get_bd_pins zynq_ultra_ps_e/pl_resetn0] [get_bd_pins rst_ps8_125M/ext_reset_in] [get_bd_ports Rst_N]

  # Create address segments
  assign_bd_address -offset 0x80030000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e/Data] [get_bd_addr_segs OVC_PROTECT_IP_0/S_AXI_LITE/S_AXI_LITE_reg] -force
  assign_bd_address -offset 0x80000000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e/Data] [get_bd_addr_segs axi_gpio_0/S_AXI/Reg] -force

  # Set Top module of the design
  set_property top OVC_SPI_wrapper [current_fileset]
      if { $BOARD_REVISION == "CBX1X"} {
        set_property target_constrs_file $ROOT_FOLDER/designs/$project_name/syn/constraints/ovc_spi_CBX1X.xdc [current_fileset -constrset]
    }     

    if { $BOARD_REVISION == "CBX4X"} {
        set_property target_constrs_file $ROOT_FOLDER/designs/$project_name/syn/constraints/ovc_spi_CBX4X.xdc [current_fileset -constrset]
    } 
  
  update_compile_order -fileset sources_1
  
  save_bd_design
  validate_bd_design
  save_bd_design
  close_bd_design OVC_SPI
  
 
  create_bd_design test_data_fsm_sim

 # Create interface ports

  # Create ports
  set pl_uart_tx [ create_bd_port -dir O pl_uart_tx ]
  set pl_uart_rx [ create_bd_port -dir I pl_uart_rx ]
  set clk_in [ create_bd_port -dir I -type clk -freq_hz 125000000 clk_in ]
  set rst_n_in [ create_bd_port -dir I -type rst rst_n_in ]
  set phx_data_ready_a1 [ create_bd_port -dir I phx_data_ready_a1 ]
  set phu_adc_a1 [ create_bd_port -dir I -from 11 -to 0 phu_adc_a1 ]
  set phv_adc_a1 [ create_bd_port -dir I -from 11 -to 0 phv_adc_a1 ]
  set phw_adc_a1 [ create_bd_port -dir I -from 11 -to 0 phw_adc_a1 ]
  set clk_64M [ create_bd_port -dir O -type clk clk_64M ]
  set clk_125M [ create_bd_port -dir O -from 0 -to 0 -type clk clk_125M ]
  set test_mode_active [ create_bd_port -dir I test_mode_active ]
  set ovc_release_a1 [ create_bd_port -dir I ovc_release_a1 ]
  set ovc_event_a1 [ create_bd_port -dir O ovc_event_a1 ]
  set ovc_status_a1 [ create_bd_port -dir O -from 5 -to 0 ovc_status_a1 ]
  set pwm_uvw_top [ create_bd_port -dir O -from 2 -to 0 pwm_uvw_top ]
  set pwm_uvw_bot [ create_bd_port -dir O -from 2 -to 0 pwm_uvw_bot ]

  # Create instance: clk_wiz_0, and set properties
  set clk_wiz_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_wiz_0 ]
  set_property -dict [list \
    CONFIG.CLKIN1_JITTER_PS {80.0} \
    CONFIG.CLKOUT1_DRIVES {Buffer} \
    CONFIG.CLKOUT1_JITTER {136.480} \
    CONFIG.CLKOUT1_PHASE_ERROR {96.948} \
    CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {64.00} \
    CONFIG.CLKOUT2_DRIVES {Buffer} \
    CONFIG.CLKOUT2_JITTER {119.348} \
    CONFIG.CLKOUT2_PHASE_ERROR {96.948} \
    CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {125.00} \
    CONFIG.CLKOUT2_USED {true} \
    CONFIG.CLKOUT3_DRIVES {Buffer} \
    CONFIG.CLKOUT3_JITTER {99.263} \
    CONFIG.CLKOUT3_PHASE_ERROR {96.948} \
    CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {100.000} \
    CONFIG.CLKOUT3_USED {false} \
    CONFIG.CLKOUT4_DRIVES {Buffer} \
    CONFIG.CLKOUT4_JITTER {99.263} \
    CONFIG.CLKOUT4_PHASE_ERROR {96.948} \
    CONFIG.CLKOUT4_REQUESTED_OUT_FREQ {100.000} \
    CONFIG.CLKOUT4_USED {false} \
    CONFIG.CLKOUT5_DRIVES {Buffer} \
    CONFIG.CLKOUT6_DRIVES {Buffer} \
    CONFIG.CLKOUT7_DRIVES {Buffer} \
    CONFIG.FEEDBACK_SOURCE {FDBK_AUTO} \
    CONFIG.MMCM_CLKFBOUT_MULT_F {8.000} \
    CONFIG.MMCM_CLKIN1_PERIOD {8.000} \
    CONFIG.MMCM_CLKIN2_PERIOD {10.0} \
    CONFIG.MMCM_CLKOUT0_DIVIDE_F {15.625} \
    CONFIG.MMCM_CLKOUT1_DIVIDE {8} \
    CONFIG.MMCM_CLKOUT2_DIVIDE {1} \
    CONFIG.MMCM_CLKOUT3_DIVIDE {1} \
    CONFIG.MMCM_DIVCLK_DIVIDE {1} \
    CONFIG.NUM_OUT_CLKS {2} \
    CONFIG.OPTIMIZE_CLOCKING_STRUCTURE_EN {true} \
    CONFIG.PRIM_IN_FREQ {125.000} \
    CONFIG.PRIM_SOURCE {No_buffer} \
    CONFIG.RESET_PORT {resetn} \
    CONFIG.RESET_TYPE {ACTIVE_LOW} \
    CONFIG.SECONDARY_SOURCE {Single_ended_clock_capable_pin} \
    CONFIG.USE_PHASE_ALIGNMENT {true} \
  ] $clk_wiz_0


  # Create instance: fifo_generator_0, and set properties
  set fifo_generator_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:fifo_generator:13.2 fifo_generator_0 ]
  set_property -dict [list \
    CONFIG.Input_Data_Width {16} \
    CONFIG.Input_Depth {2048} \
    CONFIG.Output_Data_Width {8} \
    CONFIG.Performance_Options {Standard_FIFO} \
    CONFIG.Programmable_Full_Type {No_Programmable_Full_Threshold} \
    CONFIG.asymmetric_port_width {true} \
  ] $fifo_generator_0


  # Create instance: uart_0, and set properties
  set block_name uart
  set block_cell_name uart_0
  if { [catch {set uart_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $uart_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
    set_property -dict [list \
    CONFIG.baud_rate {921600} \
    CONFIG.clk_freq {125000000} \
    CONFIG.parity {0} \
  ] $uart_0


  # Create instance: util_ds_buf_1, and set properties
  set util_ds_buf_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_ds_buf:2.2 util_ds_buf_1 ]
  set_property CONFIG.C_BUF_TYPE {BUFGCE} $util_ds_buf_1


  # Create instance: util_vector_logic_2, and set properties
  set util_vector_logic_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:util_vector_logic:2.0 util_vector_logic_2 ]
  set_property -dict [list \
    CONFIG.C_OPERATION {not} \
    CONFIG.C_SIZE {1} \
  ] $util_vector_logic_2


  # Create instance: OVC_PROTECT_IP_0, and set properties
  set OVC_PROTECT_IP_0 [ create_bd_cell -type ip -vlnv schneider-electric.com:user:OVC_PROTECT_IP:1.0 OVC_PROTECT_IP_0 ]

  # Create instance: xlconcat_0, and set properties
  set xlconcat_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:2.1 xlconcat_0 ]
  set_property -dict [list \
    CONFIG.IN0_WIDTH {12} \
    CONFIG.IN1_WIDTH {12} \
    CONFIG.IN2_WIDTH {12} \
    CONFIG.NUM_PORTS {3} \
  ] $xlconcat_0


  # Create instance: axi_vip_0, and set properties
  set axi_vip_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vip:1.1 axi_vip_0 ]
  set_property -dict [list \
    CONFIG.ADDR_WIDTH {32} \
    CONFIG.DATA_WIDTH {32} \
    CONFIG.HAS_BRESP {1} \
    CONFIG.HAS_PROT {1} \
    CONFIG.HAS_RRESP {1} \
    CONFIG.HAS_WSTRB {1} \
    CONFIG.INTERFACE_MODE {MASTER} \
    CONFIG.PROTOCOL {AXI4LITE} \
    CONFIG.READ_WRITE_MODE {READ_WRITE} \
  ] $axi_vip_0


  # Create instance: PWM_ip_0, and set properties
  set PWM_ip_0 [ create_bd_cell -type ip -vlnv schneider-electric.com:ip:PWM_ip:1.0 PWM_ip_0 ]

  # Create instance: xlconstant_0, and set properties
  set xlconstant_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_0 ]
  set_property -dict [list \
    CONFIG.CONST_VAL {64} \
    CONFIG.CONST_WIDTH {7} \
  ] $xlconstant_0


  # Create instance: xlconstant_1, and set properties
  set xlconstant_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.1 xlconstant_1 ]
  set_property CONFIG.CONST_VAL {0} $xlconstant_1


  # Create instance: test_data_fsm_0, and set properties
  set block_name test_data_fsm
  set block_cell_name test_data_fsm_0
  if { [catch {set test_data_fsm_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $test_data_fsm_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create interface connections
  connect_bd_intf_net -intf_net axi_vip_0_M_AXI [get_bd_intf_pins OVC_PROTECT_IP_0/S_AXI_LITE] [get_bd_intf_pins axi_vip_0/M_AXI]

  # Create port connections
  connect_bd_net -net OVC_PROTECT_IP_0_ovc_event_o [get_bd_pins OVC_PROTECT_IP_0/ovc_event_o] [get_bd_ports ovc_event_a1] [get_bd_pins test_data_fsm_0/ovc_event_a1_i]
  connect_bd_net -net OVC_PROTECT_IP_0_ovc_status_o [get_bd_pins OVC_PROTECT_IP_0/ovc_status_o] [get_bd_ports ovc_status_a1] [get_bd_pins test_data_fsm_0/ovc_status_a1_i]
  connect_bd_net -net PWM_ip_0_pwm_uvw_high_0 [get_bd_pins PWM_ip_0/pwm_uvw_high_0] [get_bd_ports pwm_uvw_top]
  connect_bd_net -net PWM_ip_0_pwm_uvw_low_0 [get_bd_pins PWM_ip_0/pwm_uvw_low_0] [get_bd_ports pwm_uvw_bot]
  connect_bd_net -net clk_in1_0_1 [get_bd_ports clk_in] [get_bd_pins clk_wiz_0/clk_in1] [get_bd_pins OVC_PROTECT_IP_0/s_axi_lite_aclk] [get_bd_pins axi_vip_0/aclk]
  connect_bd_net -net clk_wiz_0_clk_out1 [get_bd_pins clk_wiz_0/clk_out1] [get_bd_ports clk_64M] [get_bd_pins OVC_PROTECT_IP_0/ovc_clk_i] [get_bd_pins PWM_ip_0/IPCORE_CLK] [get_bd_pins test_data_fsm_0/clk_64M_i]
  connect_bd_net -net clk_wiz_0_clk_out2 [get_bd_pins clk_wiz_0/clk_out2] [get_bd_pins util_ds_buf_1/BUFGCE_I]
  connect_bd_net -net clk_wiz_0_locked [get_bd_pins clk_wiz_0/locked] [get_bd_pins uart_0/reset_n] [get_bd_pins util_vector_logic_2/Op1] [get_bd_pins OVC_PROTECT_IP_0/ovc_reset_n_i] [get_bd_pins PWM_ip_0/IPCORE_RESETN] [get_bd_pins test_data_fsm_0/rst_n_i]
  connect_bd_net -net fifo_generator_0_dout [get_bd_pins fifo_generator_0/dout] [get_bd_pins test_data_fsm_0/fifo_data_out_i]
  connect_bd_net -net fifo_generator_0_empty [get_bd_pins fifo_generator_0/empty] [get_bd_pins test_data_fsm_0/fifo_empty_i]
  connect_bd_net -net fifo_generator_0_full [get_bd_pins fifo_generator_0/full] [get_bd_pins test_data_fsm_0/fifo_full_i]
  connect_bd_net -net fpga_test_mode_set [get_bd_ports test_mode_active] [get_bd_pins util_ds_buf_1/BUFGCE_CE] [get_bd_pins test_data_fsm_0/test_mode_active_i]
  connect_bd_net -net phu_adc_a1_i_0_1 [get_bd_ports phu_adc_a1] [get_bd_pins xlconcat_0/In0] [get_bd_pins test_data_fsm_0/phu_adc_a1_i]
  connect_bd_net -net phv_adc_a1_i_0_1 [get_bd_ports phv_adc_a1] [get_bd_pins xlconcat_0/In1] [get_bd_pins test_data_fsm_0/phv_adc_a1_i]
  connect_bd_net -net phw_adc_a1_i_0_1 [get_bd_ports phw_adc_a1] [get_bd_pins xlconcat_0/In2] [get_bd_pins test_data_fsm_0/phw_adc_a1_i]
  connect_bd_net -net phx_data_ready_a1_i_0_1 [get_bd_ports phx_data_ready_a1] [get_bd_pins OVC_PROTECT_IP_0/trigger_ovc_i] [get_bd_pins test_data_fsm_0/phx_data_ready_a1_i]
  connect_bd_net -net resetn_0_1 [get_bd_ports rst_n_in] [get_bd_pins clk_wiz_0/resetn] [get_bd_pins OVC_PROTECT_IP_0/s_axi_lite_aresetn] [get_bd_pins axi_vip_0/aresetn]
  connect_bd_net -net rx_0_1 [get_bd_ports pl_uart_rx] [get_bd_pins uart_0/rx]
  connect_bd_net -net test_data_fsm_0_fifo_data_in [get_bd_pins test_data_fsm_0/fifo_data_in_o] [get_bd_pins fifo_generator_0/din]
  connect_bd_net -net test_data_fsm_0_fifo_rd_en [get_bd_pins test_data_fsm_0/fifo_rd_en_o] [get_bd_pins fifo_generator_0/rd_en]
  connect_bd_net -net test_data_fsm_0_fifo_wr_en [get_bd_pins test_data_fsm_0/fifo_wr_en_o] [get_bd_pins fifo_generator_0/wr_en]
  connect_bd_net -net test_data_fsm_0_ovc_release_a1_o [get_bd_pins test_data_fsm_0/ovc_release_a1_o] [get_bd_pins OVC_PROTECT_IP_0/ovc_release_i]
  connect_bd_net -net test_data_fsm_0_pwm_duty_a1_o [get_bd_pins test_data_fsm_0/pwm_duty_a1_o] [get_bd_pins PWM_ip_0/pwm_compare_uvw_0]
  connect_bd_net -net test_data_fsm_0_pwm_enable_a1_o [get_bd_pins test_data_fsm_0/pwm_enable_a1_o] [get_bd_pins PWM_ip_0/enable]
  connect_bd_net -net test_data_fsm_0_pwm_freq_a1_o [get_bd_pins test_data_fsm_0/pwm_freq_a1_o] [get_bd_pins PWM_ip_0/period_compare]
  connect_bd_net -net test_data_fsm_0_uart_tx_data_o [get_bd_pins test_data_fsm_0/uart_tx_data_o] [get_bd_pins uart_0/tx_data]
  connect_bd_net -net test_data_fsm_0_uart_tx_trigger_o [get_bd_pins test_data_fsm_0/uart_tx_trigger_o] [get_bd_pins uart_0/tx_ena]
  connect_bd_net -net uart_0_rx_busy [get_bd_pins uart_0/rx_busy] [get_bd_pins test_data_fsm_0/uart_rx_busy_i]
  connect_bd_net -net uart_0_rx_data [get_bd_pins uart_0/rx_data] [get_bd_pins test_data_fsm_0/uart_rx_data_i]
  connect_bd_net -net uart_0_rx_error [get_bd_pins uart_0/rx_error] [get_bd_pins test_data_fsm_0/uart_rx_error_i]
  connect_bd_net -net uart_0_tx [get_bd_pins uart_0/tx] [get_bd_ports pl_uart_tx]
  connect_bd_net -net uart_0_tx_busy [get_bd_pins uart_0/tx_busy] [get_bd_pins test_data_fsm_0/uart_tx_busy_i]
  connect_bd_net -net util_ds_buf_1_BUFGCE_O [get_bd_pins util_ds_buf_1/BUFGCE_O] [get_bd_pins uart_0/clk] [get_bd_pins fifo_generator_0/clk] [get_bd_ports clk_125M] [get_bd_pins test_data_fsm_0/clk_125M_i]
  connect_bd_net -net util_vector_logic_2_Res [get_bd_pins util_vector_logic_2/Res] [get_bd_pins fifo_generator_0/srst]
  connect_bd_net -net xlconcat_0_dout [get_bd_pins xlconcat_0/dout] [get_bd_pins OVC_PROTECT_IP_0/current_raw_adc_i]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins xlconstant_0/dout] [get_bd_pins PWM_ip_0/dead_time]
  connect_bd_net -net xlconstant_1_dout [get_bd_pins xlconstant_1/dout] [get_bd_pins PWM_ip_0/pwm_select_dead_time_calc]

  # Create address segments



 save_bd_design
  validate_bd_design
  save_bd_design
  close_bd_design test_data_fsm_sim 

