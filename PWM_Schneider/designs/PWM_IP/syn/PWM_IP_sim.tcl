# ########################################################################################
global VIVADO_ROOT_FOLDER
if { [info exists VIVADO_ROOT_FOLDER] } {
	set ROOT_FOLDER $VIVADO_ROOT_FOLDER
} else {
	set ROOT_FOLDER "./PWM_Schneider"
}

set project_name PWM_IP_sim

set vivado_dir ${project_name} 

set module XU5
set family zynqmp
set part xczu4ev-sfvc784-1-i

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
	set_property IP_REPO_PATHS [subst {$ROOT_FOLDER/libraries/PWM_ip_v1_0}] $obj

# Rebuild user ip_repo's index before adding any source files
update_ip_catalog -rebuild
}

add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/designs/PWM_IP/rtl/pwm_ip_sim_DUT.v}]
add_files -norecurse -fileset sim_1     [subst {$ROOT_FOLDER/designs/PWM_IP/rtl_tb/pwm_ip_tb.sv}]
add_files -norecurse -fileset sim_1     [subst {$ROOT_FOLDER/designs/PWM_IP/sim/sine_ph0.mem}]
add_files -norecurse -fileset sim_1     [subst {$ROOT_FOLDER/designs/PWM_IP/sim/sine_ph1.mem}]
add_files -norecurse -fileset sim_1     [subst {$ROOT_FOLDER/designs/PWM_IP/sim/sine_ph2.mem}]

# Set 'sources_1' fileset properties
set obj [get_filesets sources_1]
set_property -name "top" -value "./$ROOT_FOLDER/designs/PWM_IP/rtl/pwm_ip_sim_DUT.v" -objects $obj

# Set 'sim_1' fileset file properties for local files
set file "pwm_ip_tb.sv"
set file_obj [get_files -of_objects [get_filesets sim_1] [list "*$file"]]
set_property -name "file_type" -value "SystemVerilog" -objects $file_obj

set file "sine_ph0.mem"
set file_obj [get_files -of_objects [get_filesets sim_1] [list "*$file"]]
set_property -name "file_type" -value "Memory File" -objects $file_obj

set file "sine_ph1.mem"
set file_obj [get_files -of_objects [get_filesets sim_1] [list "*$file"]]
set_property -name "file_type" -value "Memory File" -objects $file_obj

set file "sine_ph2.mem"
set file_obj [get_files -of_objects [get_filesets sim_1] [list "*$file"]]
set_property -name "file_type" -value "Memory File" -objects $file_obj

# Set 'sim_1' fileset properties
set obj [get_filesets sim_1]
set_property -name "top" -value "pwm_ip_tb" -objects $obj
set_property -name "top_lib" -value "xil_defaultlib" -objects $obj

# re-create block design
# ################################################
# CHANGE DESIGN NAME HERE
set design_name pwm_ip_sim

create_bd_design $design_name

	# Create ports
	set PWM_Trig_0 [ create_bd_port -dir O PWM_Trig_0 ]
	set PWM_U_0 [ create_bd_port -dir O -from 1 -to 0 PWM_U_0 ]
	set PWM_V_0 [ create_bd_port -dir O -from 1 -to 0 PWM_V_0 ]
	set PWM_W_0 [ create_bd_port -dir O -from 1 -to 0 PWM_W_0 ]
	set aclk [ create_bd_port -dir I -type clk -freq_hz 300000000 aclk ]
	set areset [ create_bd_port -dir I -type rst areset ]
	
	# Create instance: PWM_ip_DUT_0, and set properties
	set PWM_ip_DUT_0 [ create_bd_cell -type ip -vlnv schneider-electric.com:ip:PWM_ip:1.0 PWM_ip_DUT_0 ]	
		
	# Create instance: axi_pwm_control, and set properties
	create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vip:1.1 axi_pwm_control 
	set_property -dict [ list \
			CONFIG.ADDR_WIDTH {32} \
			CONFIG.ARUSER_WIDTH {0} \
			CONFIG.AWUSER_WIDTH {0} \
			CONFIG.BUSER_WIDTH {0} \
			CONFIG.DATA_WIDTH {32} \
			CONFIG.HAS_BRESP {1} \
			CONFIG.HAS_BURST {0} \
			CONFIG.HAS_CACHE {0} \
			CONFIG.HAS_LOCK {0} \
			CONFIG.HAS_PROT {1} \
			CONFIG.HAS_QOS {0} \
			CONFIG.HAS_REGION {0} \
			CONFIG.HAS_RRESP {1} \
			CONFIG.HAS_WSTRB {1} \
			CONFIG.ID_WIDTH {0} \
			CONFIG.INTERFACE_MODE {MASTER} \
			CONFIG.PROTOCOL {AXI4LITE} \
			CONFIG.READ_WRITE_MODE {READ_WRITE} \
			CONFIG.RUSER_BITS_PER_BYTE {0} \
			CONFIG.RUSER_WIDTH {0} \
			CONFIG.SUPPORTS_NARROW {0} \
			CONFIG.WUSER_BITS_PER_BYTE {0} \
			CONFIG.WUSER_WIDTH {0} \
	] [get_bd_cells axi_pwm_control]
	
	# Create instance: axi_vip_0, and set properties
	create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vip:1.1 axi_vip_0 	
	
	# Create instance: clk_gen, and set properties
	create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_gen 
	set_property -dict [ list \
			CONFIG.CLKOUT1_DRIVES {Buffer} \
			CONFIG.CLKOUT1_JITTER {116.415} \
			CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {50.000} \
			CONFIG.CLKOUT2_DRIVES {Buffer} \
			CONFIG.CLKOUT3_DRIVES {Buffer} \
			CONFIG.CLKOUT4_DRIVES {Buffer} \
			CONFIG.CLKOUT5_DRIVES {Buffer} \
			CONFIG.CLKOUT6_DRIVES {Buffer} \
			CONFIG.CLKOUT7_DRIVES {Buffer} \
			CONFIG.MMCM_CLKOUT0_DIVIDE_F {24.000} \
			CONFIG.OPTIMIZE_CLOCKING_STRUCTURE_EN {true} \
			CONFIG.RESET_PORT {resetn} \
			CONFIG.RESET_TYPE {ACTIVE_LOW} \
			CONFIG.SECONDARY_SOURCE {Single_ended_clock_capable_pin} \
			CONFIG.USE_PHASE_ALIGNMENT {true} \
	] [get_bd_cells clk_gen]
	
	# Create interface connections
	connect_bd_intf_net -intf_net axi_vip_0_M_AXI [get_bd_intf_pins PWM_ip_DUT_0/AXI4_Lite] [get_bd_intf_pins axi_vip_0/M_AXI]
	connect_bd_intf_net -intf_net axi_vip_1_M_AXI [get_bd_intf_pins axi_pwm_control/M_AXI] [get_bd_intf_pins axi_vip_0/S_AXI]	
	
	# Create port connections
	connect_bd_net -net PWM_ip_0_PWM_Trig [get_bd_ports PWM_Trig_0] [get_bd_pins PWM_ip_DUT_0/PWM_Trig]
	connect_bd_net -net PWM_ip_0_PWM_U [get_bd_ports PWM_U_0] [get_bd_pins PWM_ip_DUT_0/PWM_U]
	connect_bd_net -net PWM_ip_0_PWM_V [get_bd_ports PWM_V_0] [get_bd_pins PWM_ip_DUT_0/PWM_V]
	connect_bd_net -net PWM_ip_0_PWM_W [get_bd_ports PWM_W_0] [get_bd_pins PWM_ip_DUT_0/PWM_W]
	connect_bd_net -net aclk_1 [get_bd_ports aclk] [get_bd_pins PWM_ip_DUT_0/AXI4_Lite_ACLK] [get_bd_pins axi_pwm_control/aclk] \
		[get_bd_pins axi_vip_0/aclk] [get_bd_pins clk_gen/clk_in1]
	connect_bd_net -net areset_1 [get_bd_ports areset] [get_bd_pins PWM_ip_DUT_0/AXI4_Lite_ARESETN] [get_bd_pins axi_pwm_control/aresetn] \
		[get_bd_pins axi_vip_0/aresetn] [get_bd_pins clk_gen/resetn]
	connect_bd_net -net clk_wiz_0_clk_out1 [get_bd_pins PWM_ip_DUT_0/IPCORE_CLK] [get_bd_pins clk_gen/clk_out1]
	connect_bd_net -net clk_wiz_0_locked [get_bd_pins PWM_ip_DUT_0/IPCORE_RESETN] [get_bd_pins clk_gen/locked]	
	
	# Create address segments
	assign_bd_address -offset 0x44A00000 -range 0x00010000 -target_address_space [get_bd_addr_spaces axi_pwm_control/Master_AXI] [get_bd_addr_segs PWM_ip_DUT_0/AXI4_Lite/reg0] -force
	
	set_property top pwm_ip_sim [current_fileset]
	update_compile_order -fileset sources_1
	
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
