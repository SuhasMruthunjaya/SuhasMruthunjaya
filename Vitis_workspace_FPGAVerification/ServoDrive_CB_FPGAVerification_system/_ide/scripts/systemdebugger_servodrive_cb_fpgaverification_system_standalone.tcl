# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\Work\Vitis_workspace_FPGAVerification\ServoDrive_CB_FPGAVerification_system\_ide\scripts\systemdebugger_servodrive_cb_fpgaverification_system_standalone.tcl
# 
# 
# Usage with xsct:
# In an external shell use the below command and launch symbol server.
# symbol_server.bat -S -s tcp::1534
# To debug using xsct, launch xsct and run below command
# source D:\Work\Vitis_workspace_FPGAVerification\ServoDrive_CB_FPGAVerification_system\_ide\scripts\systemdebugger_servodrive_cb_fpgaverification_system_standalone.tcl
# 
connect -path [list tcp::1534 tcp:localhost:3122]
source C:/Xilinx/Vitis/2023.1/scripts/vitis/util/zynqmp_utils.tcl
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -nocase -filter {name =~"APU*"}
reset_apu
targets -set -nocase -filter {name =~"RPU*"}
clear_rpu_reset
enable_split_mode
targets -set -filter {jtag_cable_name =~ "Enclustra GmbH Module Link enclustraA" && level==0 && jtag_device_ctx=="jsn-Module Link-enclustraA-04721093-0"}
fpga -file D:/Work/Vitis_workspace_FPGAVerification/ServoDrive_CB_FPGAVerification/_ide/bitstream/Mercury_XU5_PE1.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/Work/Vitis_workspace_FPGAVerification/Mercury_XU5_PE1/export/Mercury_XU5_PE1/hw/Mercury_XU5_PE1.xsa -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/Work/Vitis_workspace_FPGAVerification/ServoDrive_CB_FPGAVerification/_ide/psinit/psu_init.tcl
psu_init
source C:/Xilinx/Vitis/2023.1/scripts/vitis/util/fsbl.tcl
catch {XFsbl_DdrEccInit}
after 1000
psu_ps_pl_isolation_removal
after 1000
psu_ps_pl_reset_config
catch {psu_protection}
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow D:/Work/Vitis_workspace_FPGAVerification/ServoDrive_CB_FPGAVerification/Debug/ServoDrive_CB_FPGAVerification.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A53*#0"}
con
