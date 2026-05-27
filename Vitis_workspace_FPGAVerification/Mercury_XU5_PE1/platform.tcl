# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct D:\Work\Vitis_workspace_FPGAVerification\Mercury_XU5_PE1\platform.tcl
# 
# OR launch xsct and run below command.
# source D:\Work\Vitis_workspace_FPGAVerification\Mercury_XU5_PE1\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Mercury_XU5_PE1}\
-hw {D:\Work\New folder\MEXU5_U200_PE1\Mercury_XU5_PE1.xsa}\
-arch {64-bit} -fsbl-target {psu_cortexa53_0} -out {D:/Work/Vitis_workspace_FPGAVerification}

platform write
domain create -name {standalone_psu_cortexa53_0} -display-name {standalone_psu_cortexa53_0} -os {standalone} -proc {psu_cortexa53_0} -runtime {cpp} -arch {64-bit} -support-app {hello_world}
platform generate -domains 
platform active {Mercury_XU5_PE1}
domain active {zynqmp_fsbl}
domain active {zynqmp_pmufw}
domain active {standalone_psu_cortexa53_0}
platform generate -quick
platform generate
platform generate -domains 
domain active {zynqmp_fsbl}
bsp reload
bsp reload
domain active {standalone_psu_cortexa53_0}
bsp reload
bsp setlib -name xilffs -ver 5.0
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynqmp_pmufw}
bsp reload
bsp setlib -name xilffs -ver 5.0
bsp write
bsp reload
catch {bsp regenerate}
platform generate -domains standalone_psu_cortexa53_0,zynqmp_pmufw 
platform clean
platform generate
platform config -updatehw {D:/Work/New folder/MEXU5_U200_PE1/Mercury_XU5_PE1.xsa}
platform generate -domains 
platform active {Mercury_XU5_PE1}
platform config -updatehw {D:/Work/New folder/MEXU5_U200_PE1/Mercury_XU5_PE1.xsa}
platform generate -domains 
platform config -updatehw {D:/Work/New folder/MEXU5_U200_PE1/Mercury_XU5_PE1.xsa}
platform generate -domains 
platform config -updatehw {D:/Work/New folder/MEXU5_U200_PE1/Mercury_XU5_PE1.xsa}
platform generate -domains 
platform config -updatehw {D:/Work/New folder/MEXU5_U200_PE1/Mercury_XU5_PE1.xsa}
platform generate -domains 
platform config -updatehw {D:/Work/New folder/MEXU5_U200_PE1/Mercury_XU5_PE1.xsa}
platform generate -domains 
platform config -updatehw {D:/Work/New folder/MEXU5_U200_PE1/Mercury_XU5_PE1.xsa}
platform generate -domains 
platform generate
platform active {Mercury_XU5_PE1}
domain active {zynqmp_fsbl}
domain active {standalone_psu_cortexa53_0}
domain active {zynqmp_pmufw}
bsp reload
bsp reload
bsp reload
domain active {zynqmp_fsbl}
bsp reload
domain active {standalone_psu_cortexa53_0}
bsp reload
domain active {zynqmp_pmufw}
bsp reload
domain active {zynqmp_fsbl}
bsp reload
domain active {zynqmp_pmufw}
bsp reload
platform active {Mercury_XU5_PE1}
platform config -updatehw {C:/Users/sesa807379/Downloads/MEXU5_U200_FPGACI.xsa}
platform generate
platform active {Mercury_XU5_PE1}
domain active {standalone_psu_cortexa53_0}
bsp reload
bsp reload
platform generate -domains 
bsp reload
bsp reload
platform active {Mercury_XU5_PE1}
domain active {zynqmp_pmufw}
bsp reload
bsp reload
bsp reload
