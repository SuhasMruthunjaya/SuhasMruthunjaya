@echo off
setlocal enabledelayedexpansion

:: Check where Xilinx installation is located
if exist "C:\Xilinx\Vivado\2023.1" (
	set XILINX_PATH=C:\Xilinx
	goto XilinxPathOK
)
if exist "D:\Xilinx\Vivado\2023.1" (
	set XILINX_PATH=D:\Xilinx
	goto XilinxPathOK
)
echo ERROR: Not able to locate Xilinx installation
echo press ENTER to close
goto END_ERROR

:: Xilinx installation found, procceed
:XilinxPathOK
echo found Xilinx installation at %XILINX_PATH%

cd %PROJECT_ROOT%

set PROJECT_NAME=MEXU5_U200_PE1

call %XILINX_PATH%\Vivado\2023.1\bin\vivado.bat -mode tcl -tempDir $PROJECT_DEST/.Xil -journal $PROJECT_DEST/vivado.jou -log $PROJECT_DEST/vivado.log -source %PROJECT_ROOT%\designs\%PROJECT_NAME%\syn\create_project.tcl

:END_ERROR
TITLE ERROR
if !DOWAIT! == 1 pause
exit

:END
TITLE Finished
echo Finished
if !DOWAIT! == 1 pause