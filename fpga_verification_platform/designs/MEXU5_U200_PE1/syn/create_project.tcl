#
# create_project.tcl: Tcl script for re-creating Vivado project
# 
# requires sourcing the settings.tcl to define the following variables:
# part, PS_DDR, project_name, vivado_dir
# ########################################################################################
global PROJECT_ROOT
set PROJECT_ROOT $env(PROJECT_ROOT)
global PROJECT_DEST 
set PROJECT_DEST $env(PROJECT_DEST)

set ROOT_FOLDER $env(PROJECT_ROOT)
puts $ROOT_FOLDER

set PROJECT_NAME MEXU5_U200_PE1

# Set module_name variable based on the SOM module used here
source $ROOT_FOLDER/designs/$PROJECT_NAME/syn/settings.tcl
set vivado_dir ${PROJECT_NAME}

cd $PROJECT_DEST

# Create project
create_project ${PROJECT_NAME} ${vivado_dir} -part ${part} -f

# Set project directory
set proj_dir [get_property directory [current_project]]

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

set obj [get_filesets sources_1]
if { $obj != {} } {
    set_property IP_REPO_PATHS [subst {{$ROOT_FOLDER/libraries}}] $obj

# Rebuild user ip_repo's index before adding any source files
update_ip_catalog -rebuild
}

# add source and constraints to corresponding fileset
# Misc Sources
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/edge_detect.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/toggle_signal.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/SPI_START_Trigger.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/Custom_MUX.vhd}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/Custom_MUX_tb.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/or_gate.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/Mercury_XU5_gmii2rgmii.edn}]

# I2C
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/I2C/I2C.vhd}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/I2C/I2C_tb.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/I2C/Serializer.vhd}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/I2C/serializer_tb.vhd}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/I2C/slaveEmulator.vhd}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/I2C/slaveEmulator_tb.vhd}]
# DAC SPI
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DAC_SPI/SPI_master.vhd}]
add_files -norecurse -fileset sim_1 [subst {$ROOT_FOLDER/libraries/DAC_SPI/SPI_master_tb.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DAC_SPI/Serializer_SPI.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DAC_SPI/Parallelizer.vhd}]
#DDFS
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DDFS/ddfs.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DDFS/math_utils.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DDFS/phase_acc.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DDFS/sine_wave_LUT.vhd}]
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DDFS/time_base_gen.vhd}]
#PWM_ANALYZER
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/PWM_Analyser/PWM_Analyzer.vhd}]
#DEADTIME_CAPTURE
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/libraries/DeadTime_Capture/DeadTime_Capture.vhd}]
# Project Relevant sources and constraints
add_files -norecurse -fileset sources_1 [subst {$ROOT_FOLDER/designs/$PROJECT_NAME/rtl/Mercury_XU5_PE1.vhd}]
add_files -norecurse -fileset constrs_1 [subst {$ROOT_FOLDER/designs/$PROJECT_NAME/syn/constraints/Mercury_XU5_PE1.tcl}]
add_files -norecurse -fileset constrs_1 [subst {$ROOT_FOLDER/designs/$PROJECT_NAME/syn/constraints/Mercury_XU5_LED_timing.xdc}]
add_files -norecurse -fileset constrs_1 [subst {$ROOT_FOLDER/designs/$PROJECT_NAME/syn/constraints/Mercury_XU5_gmii2rgmii_timing.tcl}]

set_property top Mercury_XU5_PE1 [current_fileset]

# re-create block design
# contains PS settings, IP instances, DDR settings
# ################################################
source $ROOT_FOLDER/designs/$PROJECT_NAME/syn/MEXU5_U200_PE1_bd.tcl
# ################################################

set_property target_constrs_file $ROOT_FOLDER/designs/$PROJECT_NAME/syn/constraints/Mercury_XU5_LED_timing.xdc [current_fileset -constrset]

# handle list of generics at level top
if {[info exists generics]} {
	set list [get_property "generic" $obj]
	lappend list ${generics}
	set_property "generic" ${list} $obj
}

# add the settings.tcl file to synth and implementation tcl.pre
# set proj_dir [get_property DIRECTORY [current_project]]
# set settings_file $proj_dir/../../scripts/settings.tcl
# set norm_settings_file [file normalize $settings_file]
# add_files -fileset utils_1 -norecurse $settings_file
# set_property STEPS.SYNTH_DESIGN.TCL.PRE [ get_files $norm_settings_file -of [get_fileset utils_1] ] [get_runs synth_1]
# set_property STEPS.INIT_DESIGN.TCL.PRE [ get_files $norm_settings_file -of [get_fileset utils_1] ] [get_runs impl_1]

# timing constraints are only relevant for implementation
if {[llength [glob -nocomplain -type f -directory src *_timing.tcl]] != 0} {
    set_property used_in_synthesis false [get_files -filter {NAME =~ *_timing.tcl}]
}
set_property used_in_synthesis false [get_files *.xdc]

puts "INFO: END of [info script]"
