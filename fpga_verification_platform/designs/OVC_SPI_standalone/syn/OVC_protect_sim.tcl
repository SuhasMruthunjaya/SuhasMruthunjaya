# ########################################################################################
global PROJECT_ROOT
set PROJECT_ROOT $env(PROJECT_ROOT)
global PROJECT_DEST 
set PROJECT_DEST $env(PROJECT_DEST)
global MATLAB_ROOT
set MATLAB_ROOT $env(MATLAB_ROOT)

puts PROJECT_ROOT=$PROJECT_ROOT
puts PROJECT_DEST=$PROJECT_DEST
puts MATLAB_ROOT=$MATLAB_ROOT

set ROOT_FOLDER $env(PROJECT_ROOT)
puts $ROOT_FOLDER

set project_name HB_PWM_IP_sim

set vivado_dir ${project_name} 

set module XU5
set family zynqmp
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

# Create 'sim_1' fileset (if not found)
if {[string equal [get_filesets -quiet sim_1] ""]} {
  create_fileset -simset sim_1
}


# add source and constraints to corresponding fileset
# Set IP repository paths
set obj [get_filesets sources_1]
if { $obj != {} } {
	set_property IP_REPO_PATHS [subst {$ROOT_FOLDER/libraries/HB_PWM_IP_1_0}] $obj

# Rebuild user ip_repo's index before adding any source files
update_ip_catalog -rebuild
}

add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/designs/HB_PWM_standalone/rtl/hb_pwm_ip_sim_wrapper.v}]
add_files -norecurse -fileset sim_1     [subst {$ROOT_FOLDER/designs/HB_PWM_standalone/rtl_tb/hb_pwm_ip_tb.sv}]
add_files -norecurse -fileset sim_1     [subst {$ROOT_FOLDER/designs/HB_PWM_standalone/sim/hb_pwm_ip_tb_behav.wcfg}]

# Set 'sources_1' fileset properties
set obj [get_filesets sources_1]
set_property -name "top" -value "./$ROOT_FOLDER/designs/HB_PWM_standalone/rtl/hb_pwm_ip_sim_wrapper.v" -objects $obj

# Set 'sim_1' fileset properties
set obj [get_filesets sources_1]
set_property -name "top" -value "hb_pwm_ip_sim_wrapper" -objects $obj
set_property -name "top_lib" -value "xil_defaultlib" -objects $obj

# Set 'sim_1' fileset file properties for local files
set file "hb_pwm_ip_tb.sv"
set file_obj [get_files -of_objects [get_filesets sim_1] [list "*$file"]]
set_property -name "file_type" -value "SystemVerilog" -objects $file_obj

# Set 'sim_1' fileset properties
set obj [get_filesets sim_1]
set_property -name "top" -value "hb_pwm_ip_tb" -objects $obj
set_property -name "top_lib" -value "xil_defaultlib" -objects $obj

# re-create block design
# ################################################
# CHANGE DESIGN NAME HERE
set design_name hb_pwm_ip_sim

create_bd_design $design_name

# Create ports
  set HB_CTL_A1 [ create_bd_port -dir O HB_CTL_A1 ]
  set HB_CTL_A2 [ create_bd_port -dir O HB_CTL_A2 ]
  set aclk [ create_bd_port -dir I -type clk -freq_hz 125000000 aclk ]
  set aresetn [ create_bd_port -dir I -type rst aresetn ]
  set rtc_8kHz_sync [ create_bd_port -dir I rtc_8kHz_sync ]

  # Create instance: axi_hb_control, and set properties
  set axi_hb_control [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vip:1.1 axi_hb_control ]
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
  ] $axi_hb_control


  # Create instance: axi_hb_control_axi_periph, and set properties
  set axi_hb_control_axi_periph [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_hb_control_axi_periph ]
  set_property CONFIG.NUM_MI {1} $axi_hb_control_axi_periph


  # Create instance: HB_PWM_IP_0, and set properties
  set HB_PWM_IP_0 [ create_bd_cell -type ip -vlnv se.com:user:HB_PWM_IP:1.0 HB_PWM_IP_0 ]

  # Create interface connections
  connect_bd_intf_net -intf_net axi_hb_control_M_AXI [get_bd_intf_pins axi_hb_control/M_AXI] [get_bd_intf_pins axi_hb_control_axi_periph/S00_AXI]
  connect_bd_intf_net -intf_net axi_hb_control_axi_periph_M00_AXI [get_bd_intf_pins axi_hb_control_axi_periph/M00_AXI] [get_bd_intf_pins HB_PWM_IP_0/S_AXI_LITE]

  # Create port connections
  connect_bd_net -net HB_PWM_IP_0_hb_pwm_out_a1 [get_bd_pins HB_PWM_IP_0/hb_pwm_out_a1] [get_bd_ports HB_CTL_A1]
  connect_bd_net -net HB_PWM_IP_0_hb_pwm_out_a2 [get_bd_pins HB_PWM_IP_0/hb_pwm_out_a2] [get_bd_ports HB_CTL_A2]
  connect_bd_net -net aclk_1 [get_bd_ports aclk] [get_bd_pins axi_hb_control/aclk] [get_bd_pins axi_hb_control_axi_periph/ACLK] [get_bd_pins axi_hb_control_axi_periph/S00_ACLK] [get_bd_pins axi_hb_control_axi_periph/M00_ACLK] [get_bd_pins HB_PWM_IP_0/s_axi_lite_aclk]
  connect_bd_net -net aresetn_1 [get_bd_ports aresetn] [get_bd_pins axi_hb_control/aresetn] [get_bd_pins axi_hb_control_axi_periph/S00_ARESETN] [get_bd_pins axi_hb_control_axi_periph/M00_ARESETN] [get_bd_pins axi_hb_control_axi_periph/ARESETN] [get_bd_pins HB_PWM_IP_0/s_axi_lite_aresetn]
  connect_bd_net -net rtc_8kHz_sync_1 [get_bd_ports rtc_8kHz_sync] [get_bd_pins HB_PWM_IP_0/rtc_8kHz_sync_i]

  # Create address segments
  assign_bd_address -offset 0x44A00000 -range 0x00000080 -target_address_space [get_bd_addr_spaces axi_hb_control/Master_AXI] [get_bd_addr_segs HB_PWM_IP_0/S_AXI_LITE/S_AXI_LITE_reg] -force

	validate_bd_design
	save_bd_design
	close_bd_design $design_name 

# ################################################
# handle list of generics at level top
if {[info exists generics]} {
	set list [get_property "generic" $obj]
	lappend list ${generics}
	set_property "generic" ${list} $obj
}

puts "INFO: END of [info script]"
