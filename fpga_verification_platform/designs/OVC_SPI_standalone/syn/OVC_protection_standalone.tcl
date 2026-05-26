# requires sourcing the settings.tcl to define the following variables:
# module (2CG or 4EV), PS_DDR, project_name, vivado_dir
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
set project_name OVC_protection_module

set vivado_dir ${project_name} 

set part xczu4cg-sfvc784-1-i 

 # Create project
 cd $PROJECT_DEST
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

# Rebuild user ip_repo's index before adding any source files
# add source and constraints to corresponding fileset
# Set IP repository paths
set obj [get_filesets sources_1]
if { $obj != {} } {
	set_property IP_REPO_PATHS [subst {$ROOT_FOLDER/libraries/OVC_PROTECT_IP_1_0}] $obj

# Rebuild user ip_repo's index before adding any source files
update_ip_catalog -rebuild
}

add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/ovc_protect_module.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/pwm_off.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/designs/OVC_SPI_standalone/rtl/ovc_protect_wrapper.v}]

add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/designs/OVC_SPI_standalone/rtl_tb/tb_ovc_protect_module.vhd}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/designs/OVC_SPI_standalone/rtl_tb/ovc_protect_ip_tb.sv}]

# re-create block design
# ################################################
# CHANGE DESIGN NAME HERE
set design_name ovc_protect

create_bd_design $design_name

# Create interface ports

  # Create ports
  set aclk [ create_bd_port -dir I -type clk aclk ]
  set aresetn [ create_bd_port -dir I -type rst aresetn ]
  set ovc_clk [ create_bd_port -dir I ovc_clk ]
  set ovc_reset_n [ create_bd_port -dir I ovc_reset_n ]
  set trigger_ovc [ create_bd_port -dir I trigger_ovc ]
  set current_raw_adc [ create_bd_port -dir I -from 35 -to 0 current_raw_adc ]
  set ovc_release [ create_bd_port -dir I ovc_release ]
  set ovc_status [ create_bd_port -dir O -from 5 -to 0 ovc_status ]
  set ovc_event [ create_bd_port -dir O ovc_event ]

  # Create instance: OVC_PROTECT_IP_0, and set properties
  set OVC_PROTECT_IP_0 [ create_bd_cell -type ip -vlnv se.com:user:OVC_PROTECT_IP:1.0 OVC_PROTECT_IP_0 ]

  # Create instance: axi_ovc_protect, and set properties
  set axi_ovc_protect [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vip:1.1 axi_ovc_protect ]
  set_property -dict [list \
    CONFIG.ADDR_WIDTH {32} \
    CONFIG.ARUSER_WIDTH {0} \
    CONFIG.AWUSER_WIDTH {0} \
    CONFIG.BUSER_WIDTH {0} \
    CONFIG.DATA_WIDTH {32} \
    CONFIG.HAS_BRESP {1} \
    CONFIG.HAS_BURST {1} \
    CONFIG.HAS_CACHE {1} \
    CONFIG.HAS_LOCK {1} \
    CONFIG.HAS_PROT {1} \
    CONFIG.HAS_QOS {1} \
    CONFIG.HAS_REGION {1} \
    CONFIG.HAS_RRESP {1} \
    CONFIG.HAS_WSTRB {1} \
    CONFIG.ID_WIDTH {0} \
    CONFIG.INTERFACE_MODE {MASTER} \
    CONFIG.PROTOCOL {AXI4} \
    CONFIG.READ_WRITE_MODE {READ_WRITE} \
    CONFIG.RUSER_WIDTH {0} \
    CONFIG.SUPPORTS_NARROW {1} \
    CONFIG.WUSER_WIDTH {0} \
  ] $axi_ovc_protect


  # Create instance: axi_interconnect_0, and set properties
  set axi_interconnect_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.1 axi_interconnect_0 ]
  set_property CONFIG.NUM_MI {1} $axi_interconnect_0


  # Create interface connections
  connect_bd_intf_net -intf_net axi_interconnect_0_M00_AXI [get_bd_intf_pins axi_interconnect_0/M00_AXI] [get_bd_intf_pins OVC_PROTECT_IP_0/S_AXI_LITE]
  connect_bd_intf_net -intf_net axi_ovc_protect_M_AXI [get_bd_intf_pins axi_ovc_protect/M_AXI] [get_bd_intf_pins axi_interconnect_0/S00_AXI]

  # Create port connections
  connect_bd_net -net OVC_PROTECT_IP_0_ovc_event_o [get_bd_pins OVC_PROTECT_IP_0/ovc_event_o] [get_bd_ports ovc_event]
  connect_bd_net -net OVC_PROTECT_IP_0_ovc_status_o [get_bd_pins OVC_PROTECT_IP_0/ovc_status_o] [get_bd_ports ovc_status]
  connect_bd_net -net aclk_0_1 [get_bd_ports aclk] [get_bd_pins axi_ovc_protect/aclk] [get_bd_pins OVC_PROTECT_IP_0/s_axi_lite_aclk] [get_bd_pins axi_interconnect_0/ACLK] [get_bd_pins axi_interconnect_0/S00_ACLK] [get_bd_pins axi_interconnect_0/M00_ACLK]
  connect_bd_net -net aresetn_0_1 [get_bd_ports aresetn] [get_bd_pins axi_ovc_protect/aresetn] [get_bd_pins OVC_PROTECT_IP_0/s_axi_lite_aresetn] [get_bd_pins axi_interconnect_0/S00_ARESETN] [get_bd_pins axi_interconnect_0/M00_ARESETN] [get_bd_pins axi_interconnect_0/ARESETN]
  connect_bd_net -net current_raw_adc_i_0_1 [get_bd_ports current_raw_adc] [get_bd_pins OVC_PROTECT_IP_0/current_raw_adc_i]
  connect_bd_net -net ovc_clk_i_0_1 [get_bd_ports ovc_clk] [get_bd_pins OVC_PROTECT_IP_0/ovc_clk_i]
  connect_bd_net -net ovc_release_i_0_1 [get_bd_ports ovc_release] [get_bd_pins OVC_PROTECT_IP_0/ovc_release_i]
  connect_bd_net -net ovc_reset_n_i_0_1 [get_bd_ports ovc_reset_n] [get_bd_pins OVC_PROTECT_IP_0/ovc_reset_n_i]
  connect_bd_net -net trigger_ovc_i_0_1 [get_bd_ports trigger_ovc] [get_bd_pins OVC_PROTECT_IP_0/trigger_ovc_i]

  # Create address segments
  assign_bd_address -offset 0x44A00000 -range 0x00010000 -target_address_space [get_bd_addr_spaces axi_ovc_protect/Master_AXI] [get_bd_addr_segs OVC_PROTECT_IP_0/S_AXI_LITE/S_AXI_LITE_reg] -force

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