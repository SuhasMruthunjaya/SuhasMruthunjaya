--Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
--Date        : Wed Sep 20 10:26:22 2023
--Host        : WTDELVSE201964L running 64-bit major release  (build 9200)
--Command     : generate_target OVC_SPI_wrapper.bd
--Design      : OVC_SPI_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library work;

entity OVC_SPI_wrapper is
  port (
    -- Inverter Interface 
    GATE_UT_A1   : out std_logic;
    GATE_UB_A1   : out std_logic;
    GATE_VT_A1   : out std_logic;
    GATE_VB_A1   : out std_logic;
    GATE_WT_A1   : out std_logic;
    GATE_WB_A1   : out std_logic;
    GATE_FLT_A1  : in  std_logic;
    
    -- Phase Current Measurememt
    PHX_CS_N_A1  : out std_logic;     
    PHX_SCLK_A1  : out std_logic;     
    PHX_RSCLK_A1 : in  std_logic;     
    PHU_SDO_A1   : in  std_logic;     
    PHV_SDO_A1   : in  std_logic;     
    PHW_SDO_A1   : in  std_logic;     
    --PHX_GPIO_A1  : out std_logic;
    
    -- PL UART Interface
    UART2_TX   : out   std_logic;
    UART2_RX   : in    std_logic;
    
    LED4_GR      : inout std_logic;
    LED4_RD      : inout std_logic
    
    
  );
end OVC_SPI_wrapper;

architecture STRUCTURE of OVC_SPI_wrapper is
  
    signal axi_clk          : std_logic;
    signal Rst_N            : std_logic;
    signal LedCount         : unsigned(26 downto 0);
    signal GPIO_EMIO_tri_i  : std_logic_vector(31 downto 0);
    signal GPIO_EMIO_tri_o  : std_logic_vector(31 downto 0);
    signal GPIO_EMIO_tri_t  : std_logic_vector(31 downto 0);
    signal p_save_emio      : std_logic; 
  
begin

  
OVC_SPI_i: entity work.OVC_SPI
     port map (
      SDI0_PC1          => PHU_SDO_A1,
      SDI1_PC1          => PHV_SDO_A1,
      SDI2_PC1          => PHW_SDO_A1,
      RSCLK_PC1         => PHX_RSCLK_A1,
      SCLK_PC1          => PHX_SCLK_A1,
      CS_PC1            => PHX_CS_N_A1,
      GATE_FLT_A1       => GATE_FLT_A1,
      GATE_UVW_13(3)    => GATE_UT_A1,
      GATE_UVW_13(4)    => GATE_VT_A1,
      GATE_UVW_13(5)    => GATE_WT_A1,
      GATE_UVW_13(0)    => GATE_UB_A1,
      GATE_UVW_13(1)    => GATE_VB_A1,
      GATE_UVW_13(2)    => GATE_WB_A1,
      pl_uart0_rx       => UART2_RX,
      pl_uart0_tx       => UART2_TX,  
      P_SAVE_EMIO       => p_save_emio,    
      GPIO_EMIO_tri_i   => GPIO_EMIO_tri_i,
      GPIO_EMIO_tri_o   => GPIO_EMIO_tri_o,
      GPIO_EMIO_tri_t   => GPIO_EMIO_tri_t, 
      axi_clk           => axi_clk,
      Rst_N             => Rst_N
    );
    
    -- P_SAVE Output from PS
    p_save_emio <= GPIO_EMIO_tri_o(14);

      -- PS/PL indication 
    process (axi_clk)
    begin
        if rising_edge (axi_clk) then
            if Rst_N = '0' then
                LedCount <= (others => '0');
            else
                LedCount <= LedCount + 1;
            end if;
        end if;
    end process;
    LED4_GR <= '0' when LedCount(LedCount'high) = '0' else 'Z';
    LED4_RD <= '1' when LedCount(LedCount'high) = '0' else 'Z';
    
end STRUCTURE;
