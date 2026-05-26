# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\SESA630813\work-2\4EV_HandsOn_app_system\_ide\scripts\debugger_4ev_handson_app-default.tcl
# 
# 
# Usage with xsct:
# In an external shell use the below command and launch symbol server.
# symbol_server.bat -S -s tcp::1534
# To debug using xsct, launch xsct and run below command
# source C:\Users\SESA630813\work-2\4EV_HandsOn_app_system\_ide\scripts\debugger_4ev_handson_app-default.tcl
# 
connect -path [list tcp::1534 tcp:127.0.0.1:3121]
source C:/Xilinx3/Vitis/2021.2/scripts/vitis/util/zynqmp_utils.tcl
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -nocase -filter {name =~"RPU*"}
clear_rpu_reset
targets -set -filter {jtag_cable_name =~ "Platform Cable USB II 13724327082d01" && level==0 && jtag_device_ctx=="jsn-DLC10-13724327082d01-5ba00477-0"}
fpga -file C:/Users/SESA630813/work-2/4EV_HandsOn_platt/hw/Block_4EV_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/SESA630813/work-2/4EV_HandsOn_platt/hw/Block_4EV_wrapper.xsa -mem-ranges [list {0x80000000 0xbfffffff} {0x400000000 0x5ffffffff} {0x1000000000 0x7fffffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/SESA630813/work-2/4EV_HandsOn_platt/hw/psu_init.tcl
psu_init
after 1000
psu_ps_pl_isolation_removal
after 1000
psu_ps_pl_reset_config
catch {psu_protection}
targets -set -nocase -filter {name =~ "*A53*#0"}
rst -processor
dow C:/Users/SESA630813/work-2/4EV_HandsOn_app/Debug/4EV_HandsOn_app.elf
configparams force-mem-access 0
bpadd -addr &main
