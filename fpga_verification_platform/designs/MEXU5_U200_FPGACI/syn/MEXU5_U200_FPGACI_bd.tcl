# ----------------------------------------------------------------------------------
# Copyright (c) 2022 by Enclustra GmbH, Switzerland.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this hardware, software, firmware, and associated documentation files (the
# "Product"), to deal in the Product without restriction, including without
# limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Product, and to permit persons to whom the
# Product is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Product.
#
# THE PRODUCT IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# PRODUCT OR THE USE OR OTHER DEALINGS IN THE PRODUCT.
# ----------------------------------------------------------------------------------

create_bd_design $module

###################### Enclustra Design ################################
create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e zynq_ultra_ps_e
set_property -dict [ list \
  CONFIG.PSU_BANK_0_IO_STANDARD {LVCMOS18} \
  CONFIG.PSU_BANK_1_IO_STANDARD {LVCMOS18} \
  CONFIG.PSU_BANK_2_IO_STANDARD {LVCMOS18} \
  CONFIG.PSU_BANK_3_IO_STANDARD {LVCMOS18} \
] [get_bd_cells zynq_ultra_ps_e]
set_property -dict [ list \
  CONFIG.PSU__SD1__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU__SD1__SLOT_TYPE {SD 2.0} \
  CONFIG.PSU__SD1__PERIPHERAL__IO {MIO 46 .. 51} \
  CONFIG.PSU__SD1__GRP_CD__ENABLE {1} \
  CONFIG.PSU__I2C0__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU__I2C0__PERIPHERAL__IO {MIO 10 .. 11} \
  CONFIG.PSU__UART0__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU__UART0__PERIPHERAL__IO {MIO 38 .. 39} \
  CONFIG.PSU__UART1__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU__UART1__PERIPHERAL__IO {EMIO} \
  CONFIG.PSU__TTC0__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU__FPGA_PL1_ENABLE {1} \
  CONFIG.PSU__CRL_APB__PL1_REF_CTRL__FREQMHZ {50} \
  CONFIG.PSU__FPGA_PL2_ENABLE {1} \
  CONFIG.PSU__CRL_APB__PL2_REF_CTRL__FREQMHZ {100} \
  CONFIG.PSU__GPIO0_MIO__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU__GPIO1_MIO__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU__GPIO2_MIO__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU_MIO_12_PULLUPDOWN {disable} \
  CONFIG.PSU__USE__M_AXI_GP1 {1} \
] [get_bd_cells zynq_ultra_ps_e]

if { $PS_DDR_TYPE == "PS_D10H"} {
  set_property -dict [ list \
    CONFIG.PSU__DDRC__SPEED_BIN {DDR4_2400T} \
    CONFIG.PSU__DDRC__CWL {12} \
    CONFIG.PSU__DDRC__DEVICE_CAPACITY {4096 MBits} \
    CONFIG.PSU__DDRC__DRAM_WIDTH {16 Bits} \
    CONFIG.PSU__DDRC__ROW_ADDR_COUNT {15} \
    CONFIG.PSU__DDRC__BG_ADDR_COUNT {1} \
    CONFIG.PSU__DDRC__ECC {Disabled} \
    CONFIG.PSU__DDRC__PARITY_ENABLE {1} \
    CONFIG.PSU__DDRC__BUS_WIDTH {32 Bit} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_DDR_TYPE == "PS_D11E"} {
  set_property -dict [ list \
    CONFIG.PSU__DDRC__SPEED_BIN {DDR4_2400T} \
    CONFIG.PSU__DDRC__CWL {12} \
    CONFIG.PSU__DDRC__DEVICE_CAPACITY {4096 MBits} \
    CONFIG.PSU__DDRC__DRAM_WIDTH {16 Bits} \
    CONFIG.PSU__DDRC__ROW_ADDR_COUNT {15} \
    CONFIG.PSU__DDRC__BG_ADDR_COUNT {1} \
    CONFIG.PSU__DDRC__ECC {Enabled} \
    CONFIG.PSU__DDRC__PARITY_ENABLE {1} \
    CONFIG.PSU__DDRC__BUS_WIDTH {64 Bit} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_DDR_TYPE == "PS_D12E"} {
  set_property -dict [ list \
    CONFIG.PSU__DDRC__SPEED_BIN {DDR4_2400T} \
    CONFIG.PSU__DDRC__CWL {12} \
    CONFIG.PSU__DDRC__DEVICE_CAPACITY {8192 MBits} \
    CONFIG.PSU__DDRC__DRAM_WIDTH {16 Bits} \
    CONFIG.PSU__DDRC__ROW_ADDR_COUNT {16} \
    CONFIG.PSU__DDRC__BG_ADDR_COUNT {1} \
    CONFIG.PSU__DDRC__ECC {Enabled} \
    CONFIG.PSU__DDRC__PARITY_ENABLE {1} \
    CONFIG.PSU__DDRC__BUS_WIDTH {64 Bit} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_DDR_TYPE == "PS_D12"} {
  set_property -dict [ list \
    CONFIG.PSU__DDRC__SPEED_BIN {DDR4_2400T} \
    CONFIG.PSU__DDRC__CWL {12} \
    CONFIG.PSU__DDRC__DEVICE_CAPACITY {8192 MBits} \
    CONFIG.PSU__DDRC__DRAM_WIDTH {16 Bits} \
    CONFIG.PSU__DDRC__ROW_ADDR_COUNT {16} \
    CONFIG.PSU__DDRC__BG_ADDR_COUNT {1} \
    CONFIG.PSU__DDRC__ECC {Disabled} \
    CONFIG.PSU__DDRC__PARITY_ENABLE {1} \
    CONFIG.PSU__DDRC__BUS_WIDTH {64 Bit} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_DDR_TYPE == "PS_D13E"} {
  set_property -dict [ list \
    CONFIG.PSU__DDRC__SPEED_BIN {DDR4_2400T} \
    CONFIG.PSU__DDRC__CWL {12} \
    CONFIG.PSU__DDRC__DEVICE_CAPACITY {16384 MBits} \
    CONFIG.PSU__DDRC__DRAM_WIDTH {16 Bits} \
    CONFIG.PSU__DDRC__ROW_ADDR_COUNT {17} \
    CONFIG.PSU__DDRC__BG_ADDR_COUNT {1} \
    CONFIG.PSU__DDRC__ECC {Enabled} \
    CONFIG.PSU__DDRC__PARITY_ENABLE {1} \
    CONFIG.PSU__DDRC__BUS_WIDTH {64 Bit} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PL_ETH == "PL_ETH"} {
  set_property -dict [ list \
    CONFIG.PSU__ENET1__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__ENET1__PERIPHERAL__IO {EMIO} \
    CONFIG.PSU__ENET1__GRP_MDIO__ENABLE {1} \
    CONFIG.PSU__ENET1__GRP_MDIO__IO {EMIO} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_ETH == "PS_ETH"} {
  set_property -dict [ list \
    CONFIG.PSU__ENET0__GRP_MDIO__ENABLE {1} \
    CONFIG.PSU__ENET0__PERIPHERAL__ENABLE {1} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_USB0 == "PS_USB0"} {
  set_property -dict [ list \
    CONFIG.PSU__USB0__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__USB0__REF_CLK_SEL {Ref Clk2} \
    CONFIG.PSU__USB0__REF_CLK_FREQ {100} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_USB1 == "PS_USB1"} {
  set_property -dict [ list \
    CONFIG.PSU__USB1__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__USB1__REF_CLK_SEL {Ref Clk2} \
    CONFIG.PSU__USB1__REF_CLK_FREQ {100} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_EMMC == "PS_EMMC"} {
  set_property -dict [ list \
    CONFIG.PSU__SD0__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__SD0__SLOT_TYPE {eMMC} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PS_QSPI == "PS_QSPI"} {
  set_property -dict [ list \
    CONFIG.PSU__QSPI__PERIPHERAL__ENABLE {1} \
    CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__FREQMHZ {200} \
    CONFIG.PSU__CRL_APB__QSPI_REF_CTRL__SRCSEL {RPLL} \
    CONFIG.PSU__QSPI__GRP_FBCLK__ENABLE {1} \
    CONFIG.PSU__QSPI__PERIPHERAL__DATA_MODE {x4} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

create_bd_cell -type ip -vlnv xilinx.com:ip:system_management_wiz system_management_wiz
set_property -dict [ list \
  CONFIG.TEMPERATURE_ALARM_OT_TRIGGER {85} \
  CONFIG.CHANNEL_ENABLE_VP_VN {false} \
] [get_bd_cells system_management_wiz]
set_property -dict [ list \
  CONFIG.PSU_MIO_13_PULLUPDOWN {disable} \
  CONFIG.PSU_MIO_14_PULLUPDOWN {disable} \
  CONFIG.PSU_MIO_15_PULLUPDOWN {disable} \
  CONFIG.PSU_MIO_16_PULLUPDOWN {disable} \
  CONFIG.PSU_MIO_17_PULLUPDOWN {disable} \
  CONFIG.PSU_MIO_18_PULLUPDOWN {disable} \
  CONFIG.PSU_MIO_19_PULLUPDOWN {disable} \
  CONFIG.PSU_MIO_20_PULLUPDOWN {disable} \
  CONFIG.PSU_MIO_21_PULLUPDOWN {disable} \
  CONFIG.PSU__SD0__PERIPHERAL__IO {MIO 13 .. 22} \
  CONFIG.PSU__SD0__DATA_TRANSFER_MODE {8Bit} \
] [get_bd_cells zynq_ultra_ps_e]
set_property -dict [ list \
  CONFIG.PSU__I2C1__PERIPHERAL__ENABLE {1} \
  CONFIG.PSU__I2C1__PERIPHERAL__IO {EMIO} \
] [get_bd_cells zynq_ultra_ps_e]

create_bd_cell -type ip -vlnv xilinx.com:ip:axi_gpio led
set_property -dict [ list \
  CONFIG.C_GPIO_WIDTH {2} \
  CONFIG.C_ALL_OUTPUTS {1} \
  CONFIG.C_DOUT_DEFAULT {0x00000003} \
] [get_bd_cells led]

if { $PL_DDR == "PL_DDR"} {
  create_bd_cell -type ip -vlnv xilinx.com:ip:ddr4 ddr4
}

if { $PL_DDR == "PL_DDR"} {
  set_property -dict [ list \
    CONFIG.PSU__USE__M_AXI_GP0 {1} \
  ] [get_bd_cells zynq_ultra_ps_e]
}

if { $PL_DDR == "No_PL_DDR"} {
  create_bd_cell -type ip -vlnv xilinx.com:ip:util_ds_buf util_ds_buf_0
  set_property -dict [ list \
    CONFIG.C_BUF_TYPE {OBUFDS} \
  ] [get_bd_cells util_ds_buf_0]
}

if { $PL_DDR == "No_PL_DDR"} {
  create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant xlconstant_0
}

if { $PL_DDR_TYPE == "512MB_1066MHz"} {
  set_property -dict [ list \
    CONFIG.C0.DDR4_TimePeriod {938} \
    CONFIG.C0.DDR4_InputClockPeriod {10006} \
    CONFIG.C0.DDR4_MemoryPart {MT40A256M16GE-083E} \
    CONFIG.C0.DDR4_DataWidth {16} \
    CONFIG.C0.DDR4_CasLatency {16} \
    CONFIG.C0.DDR4_CasWriteLatency {11} \
  ] [get_bd_cells ddr4]
}

if { $PL_DDR_TYPE == "512MB_1200MHz"} {
  set_property -dict [ list \
    CONFIG.C0.DDR4_TimePeriod {833} \
    CONFIG.C0.DDR4_InputClockPeriod {9996} \
    CONFIG.C0.DDR4_MemoryPart {MT40A256M16GE-083E} \
    CONFIG.C0.DDR4_DataWidth {16} \
    CONFIG.C0.DDR4_CasLatency {17} \
    CONFIG.C0.DDR4_CasWriteLatency {12} \
  ] [get_bd_cells ddr4]
}

if { $PL_DDR_TYPE == "1GB_1066MHz"} {
  set_property -dict [ list \
    CONFIG.C0.DDR4_TimePeriod {938} \
    CONFIG.C0.DDR4_InputClockPeriod {10006} \
    CONFIG.C0.DDR4_MemoryPart {MT40A512M16HA-083E} \
    CONFIG.C0.DDR4_DataWidth {16} \
    CONFIG.C0.DDR4_CasLatency {16} \
    CONFIG.C0.DDR4_CasWriteLatency {11} \
  ] [get_bd_cells ddr4]
}

if { $PL_DDR_TYPE == "1GB_1200MHz"} {
  set_property -dict [ list \
    CONFIG.C0.DDR4_TimePeriod {833} \
    CONFIG.C0.DDR4_InputClockPeriod {9996} \
    CONFIG.C0.DDR4_MemoryPart {MT40A512M16HA-083E} \
    CONFIG.C0.DDR4_DataWidth {16} \
    CONFIG.C0.DDR4_CasLatency {17} \
    CONFIG.C0.DDR4_CasWriteLatency {12} \
  ] [get_bd_cells ddr4]
}

if { $PL_DDR_TYPE == "2GB_1200MHz"} {
  set_property -dict [ list \
    CONFIG.C0.DDR4_TimePeriod {833} \
    CONFIG.C0.DDR4_InputClockPeriod {9996} \
    CONFIG.C0.DDR4_MemoryPart {MT40A1G16WBU-083E} \
    CONFIG.C0.DDR4_CasLatency {16} \
    CONFIG.C0.DDR4_CasWriteLatency {12} \
    CONFIG.C0.BANK_GROUP_WIDTH {2} \
    CONFIG.C0.DDR4_DataWidth {16} \
    CONFIG.C0.DDR4_isCustom {true} \
    CONFIG.C0.DDR4_AxiAddressWidth {31} \
    CONFIG.C0.DDR4_AxiDataWidth {128} \
  ] [get_bd_cells ddr4]
}

if { $PL_DDR == "PL_DDR" } {
create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect axi_interconnect_0
set_property -dict [ list \
  CONFIG.NUM_MI {1} \
  CONFIG.NUM_SI {1} \
] [get_bd_cells axi_interconnect_0]
}

if { $PL_ETH == "PL_ETH"} {
  create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz clk_wiz_0
  set_property -dict [ list \
    CONFIG.CLKIN1_JITTER_PS {200.0} \
    CONFIG.CLKOUT1_JITTER {129.582} \
    CONFIG.CLKOUT1_PHASE_ERROR {150.623} \
    CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {125.000} \
    CONFIG.CLKOUT2_JITTER {129.583} \
    CONFIG.CLKOUT2_PHASE_ERROR {150.623} \
    CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {125.000} \
    CONFIG.CLKOUT2_REQUESTED_PHASE {90} \
    CONFIG.CLKOUT2_USED {true} \
    CONFIG.CLKOUT3_JITTER {181.251} \
    CONFIG.CLKOUT3_PHASE_ERROR {150.623} \
    CONFIG.CLKOUT3_REQUESTED_OUT_FREQ {100.000} \
    CONFIG.CLKOUT3_USED {true} \
    CONFIG.CLKOUT4_JITTER {241.956} \
    CONFIG.CLKOUT4_PHASE_ERROR {150.623} \
    CONFIG.CLKOUT4_REQUESTED_OUT_FREQ {100.000} \
    CONFIG.CLKOUT4_USED {true} \
    CONFIG.MMCM_CLKFBOUT_MULT_F {25.000} \
    CONFIG.MMCM_CLKIN1_PERIOD {20.000} \
    CONFIG.MMCM_CLKIN2_PERIOD {10.0} \
    CONFIG.MMCM_CLKOUT0_DIVIDE_F {10.0} \
    CONFIG.MMCM_CLKOUT1_DIVIDE {10} \
    CONFIG.MMCM_CLKOUT1_PHASE {90} \
    CONFIG.MMCM_CLKOUT2_DIVIDE {50} \
    CONFIG.MMCM_CLKOUT3_DIVIDE {125} \
    CONFIG.MMCM_DIVCLK_DIVIDE {1} \
    CONFIG.NUM_OUT_CLKS {4} \
    CONFIG.OVERRIDE_MMCM {true} \
    CONFIG.PRIM_IN_FREQ {49.9995} \
    CONFIG.PRIM_SOURCE {Global_buffer} \
    CONFIG.RESET_PORT {resetn} \
    CONFIG.RESET_TYPE {ACTIVE_LOW} \
    CONFIG.USE_LOCKED {true} \
  ] [get_bd_cells clk_wiz_0]
}

connect_bd_net [get_bd_pins zynq_ultra_ps_e/maxihpm0_lpd_aclk] [get_bd_pins zynq_ultra_ps_e/pl_clk0]
create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 ps_sys_rst
connect_bd_net [get_bd_pins ps_sys_rst/slowest_sync_clk] [get_bd_pins zynq_ultra_ps_e/pl_clk0]
set IIC [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:iic_rtl:1.0 IIC ]
connect_bd_intf_net [get_bd_intf_ports IIC] [get_bd_intf_pins zynq_ultra_ps_e/IIC_1]

set C0_SYS_CLK [ create_bd_intf_port -mode Slave -vlnv xilinx.com:interface:diff_clock_rtl:1.0 C0_SYS_CLK ]

if { $PL_DDR == "PL_DDR"} {
  set_property generic BG_WIDTH=1 [current_fileset]
  connect_bd_intf_net [get_bd_intf_ports C0_SYS_CLK] [get_bd_intf_pins ddr4/C0_SYS_CLK]
  set C0_DDR4 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddr4_rtl:1.0 C0_DDR4 ]
  connect_bd_intf_net [get_bd_intf_ports C0_DDR4] [get_bd_intf_pins ddr4/C0_DDR4]
  create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 ddr4_sys_rst
  if {[catch { connect_bd_net [get_bd_pins zynq_ultra_ps_e/maxihpm0_fpd_aclk] [get_bd_pins ddr4/c0_ddr4_ui_clk] } errmsg]} { puts [string map {ERROR DEBUG} $errmsg] }
  connect_bd_net [get_bd_pins ddr4_sys_rst/ext_reset_in] [get_bd_pins zynq_ultra_ps_e/pl_resetn0]
  connect_bd_net [get_bd_pins ddr4_sys_rst/slowest_sync_clk] [get_bd_pins ddr4/c0_ddr4_ui_clk]
  connect_bd_net [get_bd_pins ddr4_sys_rst/peripheral_aresetn] [get_bd_pins ddr4/c0_ddr4_aresetn]
  connect_bd_net [get_bd_pins ddr4_sys_rst/peripheral_reset] [get_bd_pins ddr4/sys_rst]
}

if { $PL_DDR == "No_PL_DDR"} {
  set_property generic BG_WIDTH=1 [current_fileset]
  set C0_DDR4_ACT_N [ create_bd_port -dir O C0_DDR4_ACT_N ]
  set C0_DDR4_adr [ create_bd_port -dir O -from 16 -to 0 C0_DDR4_adr ]
  set C0_DDR4_ba [ create_bd_port -dir O -from 1 -to 0 C0_DDR4_ba ]
  set C0_DDR4_bg [ create_bd_port -dir O -from 0 -to 0 C0_DDR4_bg ]
  set C0_DDR4_ck_c [ create_bd_port -dir O -from 0 -to 0 C0_DDR4_ck_c ]
  set C0_DDR4_ck_t [ create_bd_port -dir O -from 0 -to 0 C0_DDR4_ck_t ]
  set C0_DDR4_cke [ create_bd_port -dir O -from 0 -to 0 C0_DDR4_cke ]
  set C0_DDR4_cs_n [ create_bd_port -dir O -from 0 -to 0 C0_DDR4_cs_n ]
  set C0_DDR4_dm_n [ create_bd_port -dir IO -from 1 -to 0 C0_DDR4_dm_n ]
  set C0_DDR4_dq [ create_bd_port -dir IO -from 15 -to 0 C0_DDR4_dq ]
  set C0_DDR4_dqs_c [ create_bd_port -dir IO -from 1 -to 0 C0_DDR4_dqs_c ]
  set C0_DDR4_dqs_t [ create_bd_port -dir IO -from 1 -to 0 C0_DDR4_dqs_t ]
  set C0_DDR4_odt [ create_bd_port -dir O -from 0 -to 0 C0_DDR4_odt ]
  set C0_DDR4_reset_n [ create_bd_port -dir O C0_DDR4_reset_n ]
  connect_bd_net -net util_ds_buf_1_OBUF_DS_N [get_bd_ports C0_DDR4_ck_c] [get_bd_pins util_ds_buf_0/OBUF_DS_N]
  connect_bd_net -net util_ds_buf_1_OBUF_DS_P [get_bd_ports C0_DDR4_ck_t] [get_bd_pins util_ds_buf_0/OBUF_DS_P]
  connect_bd_net -net xlconstant_0_dout [get_bd_pins util_ds_buf_0/OBUF_IN] [get_bd_pins xlconstant_0/dout]
}

if { $PL_DDR_TYPE == "2GB_1200MHz"} {
  set_property generic BG_WIDTH=2 [current_fileset]
}
if { $PL_DDR == "PL_DDR"} {
    connect_bd_intf_net -boundary_type upper [get_bd_intf_pins axi_interconnect_0/S00_AXI] [get_bd_intf_pins zynq_ultra_ps_e/M_AXI_HPM0_FPD]
    connect_bd_intf_net -boundary_type upper [get_bd_intf_pins axi_interconnect_0/M00_AXI] [get_bd_intf_pins ddr4/C0_DDR4_S_AXI]
    connect_bd_net [get_bd_pins axi_interconnect_0/ACLK] [get_bd_pins axi_interconnect_0/S00_ACLK] -boundary_type upper
    connect_bd_net [get_bd_pins axi_interconnect_0/S00_ACLK] [get_bd_pins axi_interconnect_0/M00_ACLK] -boundary_type upper
    connect_bd_net [get_bd_pins axi_interconnect_0/ARESETN] [get_bd_pins axi_interconnect_0/S00_ARESETN] -boundary_type upper
    connect_bd_net [get_bd_pins axi_interconnect_0/S00_ARESETN] [get_bd_pins axi_interconnect_0/M00_ARESETN] -boundary_type upper
    connect_bd_net [get_bd_pins axi_interconnect_0/ACLK] [get_bd_pins ddr4/c0_ddr4_ui_clk]
    connect_bd_net -net ARESETN_1 [get_bd_pins ddr4_sys_rst/interconnect_aresetn] [get_bd_pins axi_interconnect_0/ARESETN] [get_bd_pins axi_interconnect_0/S00_ARESETN] [get_bd_pins axi_interconnect_0/M00_ARESETN]
}

if { $PL_ETH == "PL_ETH"} {
  set GMII [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:gmii_rtl:1.0 GMII ]
  set MDIO [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:mdio_rtl:1.0 MDIO ]
  connect_bd_intf_net [get_bd_intf_ports GMII] [get_bd_intf_pins zynq_ultra_ps_e/GMII_ENET1]
  connect_bd_intf_net [get_bd_intf_ports MDIO] [get_bd_intf_pins zynq_ultra_ps_e/MDIO_ENET1]
  set ETH_CLK125 [ create_bd_port -dir O -type clk ETH_CLK125 ]
  set ETH_CLK125_90 [ create_bd_port -dir O -type clk ETH_CLK125_90 ]
  set ETH_CLK25 [ create_bd_port -dir O -type clk ETH_CLK25 ]
  set ETH_CLK10 [ create_bd_port -dir O -type clk ETH_CLK10 ]
  set ETH_resetn [ create_bd_port -dir O ETH_resetn ]
  connect_bd_net -net ETH_CLK125 [get_bd_ports ETH_CLK125] [get_bd_pins clk_wiz_0/clk_out1]
  connect_bd_net -net CLK_ETH125_90 [get_bd_ports ETH_CLK125_90] [get_bd_pins clk_wiz_0/clk_out2]
  connect_bd_net -net CLK_ETH25 [get_bd_ports ETH_CLK25] [get_bd_pins clk_wiz_0/clk_out3]
  connect_bd_net -net CLK_ETH10 [get_bd_ports ETH_CLK10] [get_bd_pins clk_wiz_0/clk_out4]
  connect_bd_net -net clk_wiz_0_locked [get_bd_ports ETH_resetn] [get_bd_pins clk_wiz_0/locked]
  connect_bd_net [get_bd_pins clk_wiz_0/resetn] [get_bd_pins zynq_ultra_ps_e/pl_resetn0]
  connect_bd_net [get_bd_pins clk_wiz_0/clk_in1] [get_bd_pins zynq_ultra_ps_e/pl_clk1]
}

if { $PL_ETH == "No_PL_ETH"} {
  set ETH_CLK10 [ create_bd_port -dir O ETH_CLK10]
  set ETH_CLK125 [ create_bd_port -dir O ETH_CLK125 ]
  set ETH_CLK125_90 [ create_bd_port -dir O ETH_CLK125_90 ]
  set ETH_CLK25 [ create_bd_port -dir O ETH_CLK25 ]
  set ETH_resetn [ create_bd_port -dir O ETH_resetn ]
  set GMII_col [ create_bd_port -dir I GMII_col ]
  set GMII_crs [ create_bd_port -dir I GMII_crs ]
  set GMII_rx_clk [ create_bd_port -dir I GMII_rx_clk ]
  set GMII_rx_dv [ create_bd_port -dir I GMII_rx_dv ]
  set GMII_rx_er [ create_bd_port -dir I GMII_rx_er ]
  set GMII_rxd [ create_bd_port -dir I -from 7 -to 0 GMII_rxd ]
  set GMII_speed_mode [ create_bd_port -dir O -from 2 -to 0 GMII_speed_mode ]
  set GMII_tx_clk [ create_bd_port -dir I GMII_tx_clk ]
  set GMII_tx_en [ create_bd_port -dir O GMII_tx_en ]
  set GMII_tx_er [ create_bd_port -dir O GMII_tx_er ]
  set GMII_txd [ create_bd_port -dir O -from 7 -to 0 GMII_txd ]
  set MDIO_mdc [ create_bd_port -dir O MDIO_mdc ]
  set MDIO_mdio_i [ create_bd_port -dir I MDIO_mdio_i ]
  set MDIO_mdio_o [ create_bd_port -dir O MDIO_mdio_o ]
  set MDIO_mdio_t [ create_bd_port -dir O MDIO_mdio_t ]
}

create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect smartconnect_00
set_property -dict [list CONFIG.NUM_MI {2} CONFIG.NUM_CLKS {1} CONFIG.NUM_SI {1}] [get_bd_cells smartconnect_00]
connect_bd_intf_net [get_bd_intf_pins zynq_ultra_ps_e/M_AXI_HPM0_LPD] [get_bd_intf_pins smartconnect_00/S00_AXI]
connect_bd_net [get_bd_pins zynq_ultra_ps_e/pl_clk0] [get_bd_pins smartconnect_00/aclk]
connect_bd_net [get_bd_pins ps_sys_rst/interconnect_aresetn] [get_bd_pins smartconnect_00/aresetn]
connect_bd_intf_net [get_bd_intf_pins smartconnect_00/M00_AXI ] [get_bd_intf_pins system_management_wiz/S_AXI_LITE]
connect_bd_intf_net [get_bd_intf_pins smartconnect_00/M01_AXI ] [get_bd_intf_pins led/S_AXI]

connect_bd_net [get_bd_pins ps_sys_rst/peripheral_aresetn] [get_bd_pins system_management_wiz/s_axi_aresetn]
connect_bd_net [get_bd_pins zynq_ultra_ps_e/pl_clk0] [get_bd_pins system_management_wiz/s_axi_aclk]
connect_bd_net [get_bd_pins ps_sys_rst/peripheral_aresetn] [get_bd_pins led/s_axi_aresetn]
connect_bd_net [get_bd_pins zynq_ultra_ps_e/pl_clk0] [get_bd_pins led/s_axi_aclk]

set Clk100 [ create_bd_port -dir O -type clk Clk100]
connect_bd_net [get_bd_ports Clk100] [get_bd_pins zynq_ultra_ps_e/pl_clk0]
set Clk50 [ create_bd_port -dir O -type clk Clk50]
connect_bd_net [get_bd_ports Clk50] [get_bd_pins zynq_ultra_ps_e/pl_clk1]
set Rst_N [ create_bd_port -dir O -type rst Rst_N]
connect_bd_net [get_bd_ports Rst_N] [get_bd_pins zynq_ultra_ps_e/pl_resetn0]
set LED_N_PL [ create_bd_port -dir O -from 1 -to 0 LED_N_PL]
connect_bd_net [get_bd_ports LED_N_PL] [get_bd_pins led/gpio_io_o]

##################### End Enclustra Design ####################################

############################## User Design - FPGA CI/CD Platform ########################################
# Create Interface Ports
set UART1 [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:uart_rtl:1.0 UART1 ]

# Create Ports
set SCL_out_internal [ create_bd_port -dir O SCL_out_internal ]
set SDA_out_internal [ create_bd_port -dir O SDA_out_internal ]
set SDA_tristate [ create_bd_port -dir O SDA_tristate ]
set SDA_in_internal [ create_bd_port -dir I SDA_in_internal ]
set SCL_tristate [ create_bd_port -dir O SCL_tristate ]
set SCL_in_internal [ create_bd_port -dir I SCL_in_internal ]
set SPI_MISO [ create_bd_port -dir I SPI_MISO ]
set SPI_MOSI [ create_bd_port -dir O SPI_MOSI ]
set SPI_SCLK [ create_bd_port -dir O SPI_SCLK ]
set SPI_CS [ create_bd_port -dir O SPI_CS ]
set CB_PWM_UH_A1 [ create_bd_port -dir I CB_PWM_UH_A1 ]
set CB_PWM_UL_A1 [ create_bd_port -dir I CB_PWM_UL_A1 ]
set CB_PWM_VH_A1 [ create_bd_port -dir I CB_PWM_VH_A1 ]
set CB_PWM_VL_A1 [ create_bd_port -dir I CB_PWM_VL_A1 ]
set CB_PWM_WH_A1 [ create_bd_port -dir I CB_PWM_WH_A1 ]
set CB_PWM_WL_A1 [ create_bd_port -dir I CB_PWM_WL_A1 ]

create_bd_cell -type ip -vlnv xilinx.com:ip:util_ds_buf util_ds_buf_1

create_bd_cell -type ip -vlnv xilinx.com:ip:smartconnect:1.0 smartconnect_0
set_property -dict [list CONFIG.NUM_MI {2} CONFIG.NUM_CLKS {1} CONFIG.NUM_SI {1}] [get_bd_cells smartconnect_0]

create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 rst_ps8_299M
  
create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:6.0 clk_wiz_2 
  set_property -dict [list \
    CONFIG.CLKIN2_JITTER_PS {100.0} \
    CONFIG.CLKOUT1_DRIVES {BUFGCE} \
    CONFIG.CLKOUT1_JITTER {102.845} \
    CONFIG.CLKOUT1_PHASE_ERROR {87.180} \
    CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {192} \
    CONFIG.CLKOUT2_DRIVES {BUFGCE} \
    CONFIG.CLKOUT2_JITTER {115.831} \
    CONFIG.CLKOUT2_PHASE_ERROR {87.180} \
    CONFIG.CLKOUT2_USED {true} \
    CONFIG.CLKOUT3_DRIVES {BUFGCE} \
    CONFIG.CLKOUT4_DRIVES {BUFGCE} \
    CONFIG.CLKOUT5_DRIVES {BUFGCE} \
    CONFIG.CLKOUT6_DRIVES {BUFGCE} \
    CONFIG.CLKOUT7_DRIVES {BUFGCE} \
    CONFIG.FEEDBACK_SOURCE {FDBK_AUTO} \
    CONFIG.MMCM_BANDWIDTH {OPTIMIZED} \
    CONFIG.MMCM_CLKFBOUT_MULT_F {12.000} \
    CONFIG.MMCM_CLKIN2_PERIOD {10.000} \
    CONFIG.MMCM_CLKOUT0_DIVIDE_F {6.250} \
    CONFIG.MMCM_CLKOUT1_DIVIDE {12} \
    CONFIG.MMCM_COMPENSATION {AUTO} \
    CONFIG.NUM_OUT_CLKS {2} \
    CONFIG.PRIMITIVE {MMCM} \
    CONFIG.PRIM_IN_FREQ {100.000} \
    CONFIG.PRIM_SOURCE {No_buffer} \
    CONFIG.RESET_PORT {resetn} \
    CONFIG.RESET_TYPE {ACTIVE_LOW} \
    CONFIG.SECONDARY_SOURCE {Single_ended_clock_capable_pin} \
    CONFIG.USE_INCLK_SWITCHOVER {false} \
    CONFIG.USE_PHASE_ALIGNMENT {true} \
    CONFIG.USE_RESET {false} \
    CONFIG.USE_SAFE_CLOCK_STARTUP {true} \
  ] [get_bd_cells clk_wiz_2]
  
create_bd_cell -type module -reference or_gate or_gate_0 
create_bd_cell -type module -reference ddfs ddfs_0
create_bd_cell -type module -reference toggle_signal debug_toggle_signal_0
create_bd_cell -type module -reference SPI_master SPI_master_0
create_bd_cell -type module -reference edge_detect edge_detect_0
create_bd_cell -type module -reference edge_detect edge_detect_1
create_bd_cell -type module -reference edge_detect edge_detect_2
create_bd_cell -type module -reference edge_detect edge_detect_3
create_bd_cell -type module -reference edge_detect edge_detect_4
create_bd_cell -type module -reference Custom_MUX Custom_MUX_0 
create_bd_cell -type module -reference PWM_Analyzer PWM_Analyzer_0
create_bd_cell -type module -reference PWM_Analyzer PWM_Analyzer_1
create_bd_cell -type module -reference PWM_Analyzer PWM_Analyzer_2
create_bd_cell -type module -reference PWM_Analyzer PWM_Analyzer_3
create_bd_cell -type module -reference PWM_Analyzer PWM_Analyzer_4
create_bd_cell -type module -reference PWM_Analyzer PWM_Analyzer_5
create_bd_cell -type module -reference DeadTime_Capture DeadTime_Capture_0
create_bd_cell -type module -reference DeadTime_Capture DeadTime_Capture_1
create_bd_cell -type module -reference DeadTime_Capture DeadTime_Capture_2
 

create_bd_cell -type ip -vlnv schneider-electric.com:user:CurrentSense_AXI:1.0 CurrentSense_AXI_0
create_bd_cell -type ip -vlnv schneider-electric.com:user:PWMCapture_AXI:1.0 PWMCapture_AXI_0

create_bd_cell -type module -reference I2C I2C_0

# Debugging
create_bd_cell -type ip -vlnv xilinx.com:ip:vio:3.0 vio_0 
  set_property -dict [list \
    CONFIG.C_NUM_PROBE_IN {0} \
    CONFIG.C_NUM_PROBE_OUT {7} \
    CONFIG.C_PROBE_OUT2_INIT_VAL {1011001} \
    CONFIG.C_PROBE_OUT2_WIDTH {7} \
    CONFIG.C_PROBE_OUT3_INIT_VAL {1010000010100101} \
    CONFIG.C_PROBE_OUT3_WIDTH {16} \
    CONFIG.C_PROBE_OUT5_INIT_VAL {10001000} \
    CONFIG.C_PROBE_OUT5_WIDTH {8} \
  ] [get_bd_cells vio_0]
      
create_bd_cell -type ip -vlnv xilinx.com:ip:system_ila:1.1 system_ila_2 
  set_property -dict [list \
    CONFIG.C_DATA_DEPTH {32768} \
    CONFIG.C_EN_STRG_QUAL {1} \
    CONFIG.C_MON_TYPE {NATIVE} \
    CONFIG.C_NUM_OF_PROBES {18} \
    CONFIG.C_PROBE10_WIDTH {4} \
    CONFIG.C_PROBE1_WIDTH {24} \
    CONFIG.C_PROBE5_WIDTH {24} \
    CONFIG.C_PROBE6_WIDTH {4} \
	CONFIG.C_PROBE11_WIDTH {16} \
    CONFIG.C_PROBE_WIDTH_PROPAGATION {MANUAL} \
  ] [get_bd_cells system_ila_2]  

# Create interface connections
# connect_bd_intf_net -intf_net axi_interconnect_1_M00_AXI [get_bd_intf_pins axi_interconnect_1/M00_AXI] [get_bd_intf_pins CurrentSense_AXI_0/S00_AXI]
connect_bd_intf_net -intf_net smartconnect_0_M00_AXI [get_bd_intf_pins smartconnect_0/M00_AXI] [get_bd_intf_pins CurrentSense_AXI_0/S00_AXI] 
connect_bd_intf_net -intf_net smartconnect_0_M01_AXI [get_bd_intf_pins smartconnect_0/M01_AXI] [get_bd_intf_pins PWMCapture_AXI_0/S00_AXI]
# connect_bd_intf_net -intf_net zynq_ultra_ps_e_M_AXI_HPM1_FPD [get_bd_intf_pins zynq_ultra_ps_e/M_AXI_HPM1_FPD] [get_bd_intf_pins axi_interconnect_1/S00_AXI]
connect_bd_intf_net -intf_net zynq_ultra_ps_e_M_AXI_HPM1_FPD [get_bd_intf_pins zynq_ultra_ps_e/M_AXI_HPM1_FPD] [get_bd_intf_pins smartconnect_0/S00_AXI]
connect_bd_intf_net -intf_net zynq_ultra_ps_e_UART_1 [get_bd_intf_ports UART1] [get_bd_intf_pins zynq_ultra_ps_e/UART_1]
connect_bd_intf_net [get_bd_intf_ports C0_SYS_CLK] [get_bd_intf_pins util_ds_buf_1/CLK_IN_D]

# Create port connections
connect_bd_net -net CurrentSense_AXI_0_dac_ph_address [get_bd_pins CurrentSense_AXI_0/dac_ph_address] [get_bd_pins Custom_MUX_0/spi_ph_address]
connect_bd_net -net CurrentSense_AXI_0_sel [get_bd_pins CurrentSense_AXI_0/sel] [get_bd_pins Custom_MUX_0/sel]
connect_bd_net -net CurrentSense_AXI_0_static_data [get_bd_pins CurrentSense_AXI_0/static_data] [get_bd_pins Custom_MUX_0/static_data]
connect_bd_net -net Custom_MUX_0_debug_custom_MUX_STATE [get_bd_pins Custom_MUX_0/debug_custom_MUX_STATE] [get_bd_pins system_ila_2/probe10]
connect_bd_net -net Custom_MUX_0_spi_continous_start [get_bd_pins Custom_MUX_0/spi_continous_start] [get_bd_pins edge_detect_4/inp]
connect_bd_net -net Custom_MUX_0_spi_cpol [get_bd_pins Custom_MUX_0/spi_cpol] [get_bd_pins SPI_master_0/cpol]
connect_bd_net -net Custom_MUX_0_spi_divider [get_bd_pins Custom_MUX_0/spi_divider] [get_bd_pins SPI_master_0/divider]
connect_bd_net -net Custom_MUX_0_spi_intermittent_start [get_bd_pins Custom_MUX_0/spi_intermittent_start] [get_bd_pins edge_detect_3/inp]
connect_bd_net -net Custom_MUX_0_ddfs_start [get_bd_pins Custom_MUX_0/ddfs_start] [get_bd_pins ddfs_0/start]
connect_bd_net -net I2C_0_SCL_out_internal [get_bd_pins I2C_0/SCL_out_internal] [get_bd_ports SCL_out_internal]
connect_bd_net -net I2C_0_SCL_tristate [get_bd_pins I2C_0/SCL_tristate] [get_bd_ports SCL_tristate]
connect_bd_net -net I2C_0_SDA_out_internal [get_bd_pins I2C_0/SDA_out_internal] [get_bd_ports SDA_out_internal]
connect_bd_net -net I2C_0_SDA_tristate [get_bd_pins I2C_0/SDA_tristate] [get_bd_ports SDA_tristate]
connect_bd_net -net MISO_0_1 [get_bd_ports SPI_MISO] [get_bd_pins system_ila_2/probe0] [get_bd_pins SPI_master_0/MISO]  
connect_bd_net -net SCL_in_internal_0_1 [get_bd_ports SCL_in_internal] [get_bd_pins I2C_0/SCL_in_internal]
connect_bd_net -net SDA_in_internal_0_1 [get_bd_ports SDA_in_internal] [get_bd_pins I2C_0/SDA_in_internal]
connect_bd_net -net SPI_data_in [get_bd_pins Custom_MUX_0/spi_data] [get_bd_pins system_ila_2/probe1] [get_bd_pins SPI_master_0/data_in]
connect_bd_net -net SPI_master_0_CS_n [get_bd_pins SPI_master_0/CS_n] [get_bd_ports SPI_CS] [get_bd_pins system_ila_2/probe4]
connect_bd_net -net SPI_master_0_MOSI [get_bd_pins SPI_master_0/MOSI] [get_bd_ports SPI_MOSI] [get_bd_pins system_ila_2/probe2]
connect_bd_net -net SPI_master_0_SCLK [get_bd_pins SPI_master_0/SCLK] [get_bd_ports SPI_SCLK] [get_bd_pins system_ila_2/probe3]
connect_bd_net -net SPI_master_0_data_out [get_bd_pins SPI_master_0/data_out] [get_bd_pins system_ila_2/probe5]
connect_bd_net -net SPI_master_0_debug_port [get_bd_pins SPI_master_0/debug_port] [get_bd_pins system_ila_2/probe6]
connect_bd_net -net SPI_start_signal [get_bd_pins or_gate_0/outputY] [get_bd_pins system_ila_2/probe7] [get_bd_pins debug_toggle_signal_0/start_sig] [get_bd_pins SPI_master_0/start_trigger]
connect_bd_net -net clk_wiz_2_clk_out1 [get_bd_pins clk_wiz_2/clk_out1] [get_bd_pins system_ila_2/clk] [get_bd_pins ddfs_0/clk] [get_bd_pins SPI_master_0/clk] [get_bd_pins edge_detect_3/clk] [get_bd_pins edge_detect_4/clk] [get_bd_pins CurrentSense_AXI_0/s00_axi_aclk] [get_bd_pins Custom_MUX_0/clk] [get_bd_pins zynq_ultra_ps_e/maxihpm1_fpd_aclk] [get_bd_pins smartconnect_0/aclk] [get_bd_pins debug_toggle_signal_0/clk_in] [get_bd_pins PWM_Analyzer_0/clk] [get_bd_pins PWM_Analyzer_1/clk] [get_bd_pins PWM_Analyzer_2/clk] [get_bd_pins PWM_Analyzer_3/clk] [get_bd_pins PWM_Analyzer_4/clk] [get_bd_pins PWM_Analyzer_5/clk] [get_bd_pins DeadTime_Capture_0/clk] [get_bd_pins DeadTime_Capture_1/clk] [get_bd_pins DeadTime_Capture_2/clk] [get_bd_pins PWMCapture_AXI_0/s00_axi_aclk] 
connect_bd_net -net clk_wiz_2_locked [get_bd_pins clk_wiz_2/locked] [get_bd_pins ddfs_0/rst_n] [get_bd_pins debug_toggle_signal_0/rst_n] [get_bd_pins SPI_master_0/rst_n] [get_bd_pins edge_detect_3/rst] [get_bd_pins edge_detect_4/rst] [get_bd_pins CurrentSense_AXI_0/s00_axi_aresetn] [get_bd_pins Custom_MUX_0/rst_n] [get_bd_pins smartconnect_0/aresetn] [get_bd_pins PWM_Analyzer_0/rst_n] [get_bd_pins PWM_Analyzer_1/rst_n] [get_bd_pins PWM_Analyzer_2/rst_n] [get_bd_pins PWM_Analyzer_3/rst_n] [get_bd_pins PWM_Analyzer_4/rst_n] [get_bd_pins PWM_Analyzer_5/rst_n] [get_bd_pins DeadTime_Capture_0/rst_n] [get_bd_pins DeadTime_Capture_1/rst_n] [get_bd_pins DeadTime_Capture_2/rst_n]  
connect_bd_net -net ddfs_0_q [get_bd_pins ddfs_0/q] [get_bd_pins Custom_MUX_0/ddfs_data] [get_bd_pins system_ila_2/probe11] [get_bd_pins PWMCapture_AXI_0/s00_axi_aresetn]
connect_bd_net -net ddfs_0_trigger_pulse [get_bd_pins ddfs_0/trigger_pulse] [get_bd_pins Custom_MUX_0/lut_trigger]
connect_bd_net -net CB_PWM_UH_A1_0 [get_bd_ports CB_PWM_UH_A1] [get_bd_pins PWM_Analyzer_0/PWM_in] [get_bd_pins system_ila_2/probe12] [get_bd_pins DeadTime_Capture_0/pwm_high]
connect_bd_net -net CB_PWM_UL_A1_0 [get_bd_ports CB_PWM_UL_A1] [get_bd_pins PWM_Analyzer_1/PWM_in] [get_bd_pins system_ila_2/probe13] [get_bd_pins DeadTime_Capture_0/pwm_low]
connect_bd_net -net CB_PWM_VH_A1_0 [get_bd_ports CB_PWM_VH_A1] [get_bd_pins PWM_Analyzer_2/PWM_in] [get_bd_pins system_ila_2/probe14] [get_bd_pins DeadTime_Capture_1/pwm_high]
connect_bd_net -net CB_PWM_VL_A1_0 [get_bd_ports CB_PWM_VL_A1] [get_bd_pins PWM_Analyzer_3/PWM_in] [get_bd_pins system_ila_2/probe15] [get_bd_pins DeadTime_Capture_1/pwm_low]
connect_bd_net -net CB_PWM_WH_A1_0 [get_bd_ports CB_PWM_WH_A1] [get_bd_pins PWM_Analyzer_4/PWM_in] [get_bd_pins system_ila_2/probe16] [get_bd_pins DeadTime_Capture_2/pwm_high]
connect_bd_net -net CB_PWM_WL_A1_0 [get_bd_ports CB_PWM_WL_A1] [get_bd_pins PWM_Analyzer_5/PWM_in] [get_bd_pins system_ila_2/probe17] [get_bd_pins DeadTime_Capture_2/pwm_low]
connect_bd_net -net PWM_Analyzer_0_PWM_count [get_bd_pins PWM_Analyzer_0/PWM_count] [get_bd_pins PWMCapture_AXI_0/phase_UH_freq]
connect_bd_net -net PWM_Analyzer_0_dutyCycle_count [get_bd_pins PWM_Analyzer_0/dutycycle_count] [get_bd_pins PWMCapture_AXI_0/phase_UH_dutyCycle]
connect_bd_net -net PWM_Analyzer_1_PWM_count [get_bd_pins PWM_Analyzer_1/PWM_count] [get_bd_pins PWMCapture_AXI_0/phase_UL_freq]
connect_bd_net -net PWM_Analyzer_1_dutyCycle_count [get_bd_pins PWM_Analyzer_1/dutycycle_count] [get_bd_pins PWMCapture_AXI_0/phase_UL_dutyCycle]
connect_bd_net -net PWM_Analyzer_2_PWM_count [get_bd_pins PWM_Analyzer_2/PWM_count] [get_bd_pins PWMCapture_AXI_0/phase_VH_freq]
connect_bd_net -net PWM_Analyzer_2_dutyCycle_count [get_bd_pins PWM_Analyzer_2/dutycycle_count] [get_bd_pins PWMCapture_AXI_0/phase_VH_dutyCycle]
connect_bd_net -net PWM_Analyzer_3_PWM_count [get_bd_pins PWM_Analyzer_3/PWM_count] [get_bd_pins PWMCapture_AXI_0/phase_VL_freq]
connect_bd_net -net PWM_Analyzer_3_dutyCycle_count [get_bd_pins PWM_Analyzer_3/dutycycle_count] [get_bd_pins PWMCapture_AXI_0/phase_VL_dutyCycle]
connect_bd_net -net PWM_Analyzer_4_PWM_count [get_bd_pins PWM_Analyzer_4/PWM_count] [get_bd_pins PWMCapture_AXI_0/phase_WH_freq]
connect_bd_net -net PWM_Analyzer_4_dutyCycle_count [get_bd_pins PWM_Analyzer_4/dutycycle_count] [get_bd_pins PWMCapture_AXI_0/phase_WH_dutyCycle]
connect_bd_net -net PWM_Analyzer_5_PWM_count [get_bd_pins PWM_Analyzer_5/PWM_count] [get_bd_pins PWMCapture_AXI_0/phase_WL_freq]
connect_bd_net -net PWM_Analyzer_5_dutyCycle_count [get_bd_pins PWM_Analyzer_5/dutycycle_count] [get_bd_pins PWMCapture_AXI_0/phase_WL_dutyCycle]
connect_bd_net -net DeadTime_Capture_0_deadTime [get_bd_pins DeadTime_Capture_0/pwm_deadTime] [get_bd_pins PWMCapture_AXI_0/phase_U_deadtime]
connect_bd_net -net DeadTime_Capture_1_deadTime [get_bd_pins DeadTime_Capture_1/pwm_deadTime] [get_bd_pins PWMCapture_AXI_0/phase_V_deadtime]
connect_bd_net -net DeadTime_Capture_2_deadTime [get_bd_pins DeadTime_Capture_2/pwm_deadTime] [get_bd_pins PWMCapture_AXI_0/phase_W_deadtime]
connect_bd_net -net edge_detect_0_r_edge [get_bd_pins edge_detect_0/r_edge] [get_bd_pins I2C_0/start_read_trigger]
connect_bd_net -net edge_detect_1_r_edge [get_bd_pins edge_detect_1/r_edge] [get_bd_pins I2C_0/start_write_trigger]
connect_bd_net -net edge_detect_2_r_edge [get_bd_pins edge_detect_2/r_edge] [get_bd_pins I2C_0/stop_trigger]
connect_bd_net -net edge_detect_3_r_edge [get_bd_pins edge_detect_3/r_edge] [get_bd_pins or_gate_0/inputA]
connect_bd_net -net edge_detect_4_r_edge [get_bd_pins edge_detect_4/r_edge] [get_bd_pins or_gate_0/inputB]  
connect_bd_net -net start_op_signal [get_bd_pins CurrentSense_AXI_0/start_op] [get_bd_pins system_ila_2/probe9] [get_bd_pins Custom_MUX_0/start_op]
connect_bd_net -net toggle_signal [get_bd_pins debug_toggle_signal_0/toggle_out] [get_bd_pins system_ila_2/probe8]
connect_bd_net -net vio_0_probe_out0 [get_bd_pins vio_0/probe_out0] [get_bd_pins edge_detect_0/inp]
connect_bd_net -net vio_0_probe_out1 [get_bd_pins vio_0/probe_out1] [get_bd_pins edge_detect_1/inp]
connect_bd_net -net vio_0_probe_out2 [get_bd_pins vio_0/probe_out2] [get_bd_pins I2C_0/slave_address]
connect_bd_net -net vio_0_probe_out3 [get_bd_pins vio_0/probe_out3] [get_bd_pins I2C_0/reg_address]
connect_bd_net -net vio_0_probe_out4 [get_bd_pins vio_0/probe_out4] [get_bd_pins I2C_0/regSel]
connect_bd_net -net vio_0_probe_out5 [get_bd_pins vio_0/probe_out5] [get_bd_pins I2C_0/data]
connect_bd_net -net vio_0_probe_out6 [get_bd_pins vio_0/probe_out6] [get_bd_pins edge_detect_2/inp]
connect_bd_net -net clk100_pl_ext [get_bd_pins util_ds_buf_1/IBUF_OUT] [get_bd_pins clk_wiz_2/clk_in1]
connect_bd_net -net clk100_pl_int [get_bd_pins clk_wiz_2/clk_out2] [get_bd_pins rst_ps8_299M/slowest_sync_clk] [get_bd_pins vio_0/clk] [get_bd_pins edge_detect_0/clk] [get_bd_pins edge_detect_1/clk] [get_bd_pins edge_detect_2/clk] [get_bd_pins I2C_0/clk]
connect_bd_net -net rst_ps8_299M_peripheral_aresetn [get_bd_pins rst_ps8_299M/peripheral_aresetn] [get_bd_pins clk_wiz_2/resetn] [get_bd_pins edge_detect_0/rst] [get_bd_pins edge_detect_1/rst] [get_bd_pins edge_detect_2/rst] [get_bd_pins I2C_0/rst_n]
connect_bd_net -net zynq_ultra_ps_e_pl_resetn0 [get_bd_pins zynq_ultra_ps_e/pl_resetn0] [get_bd_pins ps_sys_rst/ext_reset_in] [get_bd_pins ddr4_sys_rst/ext_reset_in] [get_bd_pins clk_wiz_0/resetn] [get_bd_ports Rst_N] [get_bd_pins rst_ps8_299M/ext_reset_in]

# Create address segments
assign_bd_address -offset 0xB0000000 -range 0x00010000 -target_address_space [get_bd_addr_spaces zynq_ultra_ps_e/Data] [get_bd_addr_segs CurrentSense_AXI_0/S00_AXI/S00_AXI_reg] -force

assign_bd_address
save_bd_design
validate_bd_design
save_bd_design
