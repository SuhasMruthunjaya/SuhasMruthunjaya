# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\SESA630813\work-2\4EV_HandsOn_platt\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\SESA630813\work-2\4EV_HandsOn_platt\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {4EV_HandsOn_platt}\
-hw {C:\Schneider\ScriptingPath\enclustra\4EV-Hands-On\Block_4EV_HandsOn.xsa}\
-proc {psu_cortexa53_0} -os {standalone} -arch {64-bit} -fsbl-target {psu_cortexa53_0} -out {C:/Users/SESA630813/work-2}

platform write
platform generate -domains 
platform active {4EV_HandsOn_platt}
bsp reload
platform generate
platform config -updatehw {C:/Schneider/ScriptingPath/enclustra/4EV-Hands-On/Block_4EV_wrapper.xsa}
platform generate -domains 
platform generate -domains 
platform config -updatehw {C:/Schneider/ScriptingPath/enclustra/4EV-Hands-On/Block_4EV_HandsOn.xsa}
platform generate -domains 
platform config -updatehw {C:/Schneider/ScriptingPath/enclustra/4EV-Hands-On/Block_4EV_HandsOn.xsa}
platform generate -domains 
platform config -updatehw {C:/Schneider/ScriptingPath/enclustra/4EV-Hands-On/Block_4EV_HandsOn.xsa}
platform generate -domains 
platform config -updatehw {C:/Schneider/ScriptingPath/enclustra/4EV-Hands-On/Block_4EV_HandsOn.xsa}
platform generate -domains 
platform config -updatehw {C:/Schneider/ScriptingPath/enclustra/4EV-Hands-On/Block_4EV_wrapper.xsa}
