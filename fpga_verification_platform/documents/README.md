Steps to successfully build the project in Vitis:



1. After importing the files from the app folder into the src directory in Vitis, right-click on the application and select C/C++ Build Settings.
2. In C/C++ Build → Settings, add the necessary directories to the Include paths.
3. Add the following directories: ComputeLibrary, Include, PrivateInclude, Source, Include/dsp, and ComputeLibrary/Include, then click Apply.
4. Under ARM v8 gcc compiler → Symbols, add DISABLEFLOAT16 to the Defined symbols (-D) list and click Apply.
5. Under ARM v6 gcc linker → Libraries, add m to the Libraries (-l) list and click Apply.
6. Under Miscellaneous, add -u\_printf\_float in Other options (-XLinker \[option]) and click Apply.



Additionally, update the BSP (Board Support Package) settings:



1. In the Explorer, open platform.spr.
2. Under Board Support Package for standalone\_psu\_cortexa53\_0, select Modify BSP Settings.
3. Check xilffs and click OK.
