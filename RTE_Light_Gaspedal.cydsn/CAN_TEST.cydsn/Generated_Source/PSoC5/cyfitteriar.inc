;
; File Name: cyfitteriar.inc
; 
; PSoC Creator  4.4
;
; Description:
; 
;
;-------------------------------------------------------------------------------
; Copyright (c) 2007-2020 Cypress Semiconductor.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;-------------------------------------------------------------------------------

#ifndef INCLUDED_CYFITTERIAR_INC
#define INCLUDED_CYFITTERIAR_INC
    INCLUDE cydeviceiar.inc
    INCLUDE cydeviceiar_trm.inc

/* CAN */
CAN_CanIP__CSR_BUF_SR EQU CYREG_CAN0_CSR_BUF_SR
CAN_CanIP__CSR_CFG EQU CYREG_CAN0_CSR_CFG
CAN_CanIP__CSR_CMD EQU CYREG_CAN0_CSR_CMD
CAN_CanIP__CSR_ERR_SR EQU CYREG_CAN0_CSR_ERR_SR
CAN_CanIP__CSR_INT_EN EQU CYREG_CAN0_CSR_INT_EN
CAN_CanIP__CSR_INT_SR EQU CYREG_CAN0_CSR_INT_SR
CAN_CanIP__PM_ACT_CFG EQU CYREG_PM_ACT_CFG6
CAN_CanIP__PM_ACT_MSK EQU 0x01
CAN_CanIP__PM_STBY_CFG EQU CYREG_PM_STBY_CFG6
CAN_CanIP__PM_STBY_MSK EQU 0x01
CAN_CanIP__RX0_ACR EQU CYREG_CAN0_RX0_ACR
CAN_CanIP__RX0_ACRD EQU CYREG_CAN0_RX0_ACRD
CAN_CanIP__RX0_AMR EQU CYREG_CAN0_RX0_AMR
CAN_CanIP__RX0_AMRD EQU CYREG_CAN0_RX0_AMRD
CAN_CanIP__RX0_CMD EQU CYREG_CAN0_RX0_CMD
CAN_CanIP__RX0_DH EQU CYREG_CAN0_RX0_DH
CAN_CanIP__RX0_DL EQU CYREG_CAN0_RX0_DL
CAN_CanIP__RX0_ID EQU CYREG_CAN0_RX0_ID
CAN_CanIP__RX1_ACR EQU CYREG_CAN0_RX1_ACR
CAN_CanIP__RX1_ACRD EQU CYREG_CAN0_RX1_ACRD
CAN_CanIP__RX1_AMR EQU CYREG_CAN0_RX1_AMR
CAN_CanIP__RX1_AMRD EQU CYREG_CAN0_RX1_AMRD
CAN_CanIP__RX1_CMD EQU CYREG_CAN0_RX1_CMD
CAN_CanIP__RX1_DH EQU CYREG_CAN0_RX1_DH
CAN_CanIP__RX1_DL EQU CYREG_CAN0_RX1_DL
CAN_CanIP__RX1_ID EQU CYREG_CAN0_RX1_ID
CAN_CanIP__RX10_ACR EQU CYREG_CAN0_RX10_ACR
CAN_CanIP__RX10_ACRD EQU CYREG_CAN0_RX10_ACRD
CAN_CanIP__RX10_AMR EQU CYREG_CAN0_RX10_AMR
CAN_CanIP__RX10_AMRD EQU CYREG_CAN0_RX10_AMRD
CAN_CanIP__RX10_CMD EQU CYREG_CAN0_RX10_CMD
CAN_CanIP__RX10_DH EQU CYREG_CAN0_RX10_DH
CAN_CanIP__RX10_DL EQU CYREG_CAN0_RX10_DL
CAN_CanIP__RX10_ID EQU CYREG_CAN0_RX10_ID
CAN_CanIP__RX11_ACR EQU CYREG_CAN0_RX11_ACR
CAN_CanIP__RX11_ACRD EQU CYREG_CAN0_RX11_ACRD
CAN_CanIP__RX11_AMR EQU CYREG_CAN0_RX11_AMR
CAN_CanIP__RX11_AMRD EQU CYREG_CAN0_RX11_AMRD
CAN_CanIP__RX11_CMD EQU CYREG_CAN0_RX11_CMD
CAN_CanIP__RX11_DH EQU CYREG_CAN0_RX11_DH
CAN_CanIP__RX11_DL EQU CYREG_CAN0_RX11_DL
CAN_CanIP__RX11_ID EQU CYREG_CAN0_RX11_ID
CAN_CanIP__RX12_ACR EQU CYREG_CAN0_RX12_ACR
CAN_CanIP__RX12_ACRD EQU CYREG_CAN0_RX12_ACRD
CAN_CanIP__RX12_AMR EQU CYREG_CAN0_RX12_AMR
CAN_CanIP__RX12_AMRD EQU CYREG_CAN0_RX12_AMRD
CAN_CanIP__RX12_CMD EQU CYREG_CAN0_RX12_CMD
CAN_CanIP__RX12_DH EQU CYREG_CAN0_RX12_DH
CAN_CanIP__RX12_DL EQU CYREG_CAN0_RX12_DL
CAN_CanIP__RX12_ID EQU CYREG_CAN0_RX12_ID
CAN_CanIP__RX13_ACR EQU CYREG_CAN0_RX13_ACR
CAN_CanIP__RX13_ACRD EQU CYREG_CAN0_RX13_ACRD
CAN_CanIP__RX13_AMR EQU CYREG_CAN0_RX13_AMR
CAN_CanIP__RX13_AMRD EQU CYREG_CAN0_RX13_AMRD
CAN_CanIP__RX13_CMD EQU CYREG_CAN0_RX13_CMD
CAN_CanIP__RX13_DH EQU CYREG_CAN0_RX13_DH
CAN_CanIP__RX13_DL EQU CYREG_CAN0_RX13_DL
CAN_CanIP__RX13_ID EQU CYREG_CAN0_RX13_ID
CAN_CanIP__RX14_ACR EQU CYREG_CAN0_RX14_ACR
CAN_CanIP__RX14_ACRD EQU CYREG_CAN0_RX14_ACRD
CAN_CanIP__RX14_AMR EQU CYREG_CAN0_RX14_AMR
CAN_CanIP__RX14_AMRD EQU CYREG_CAN0_RX14_AMRD
CAN_CanIP__RX14_CMD EQU CYREG_CAN0_RX14_CMD
CAN_CanIP__RX14_DH EQU CYREG_CAN0_RX14_DH
CAN_CanIP__RX14_DL EQU CYREG_CAN0_RX14_DL
CAN_CanIP__RX14_ID EQU CYREG_CAN0_RX14_ID
CAN_CanIP__RX15_ACR EQU CYREG_CAN0_RX15_ACR
CAN_CanIP__RX15_ACRD EQU CYREG_CAN0_RX15_ACRD
CAN_CanIP__RX15_AMR EQU CYREG_CAN0_RX15_AMR
CAN_CanIP__RX15_AMRD EQU CYREG_CAN0_RX15_AMRD
CAN_CanIP__RX15_CMD EQU CYREG_CAN0_RX15_CMD
CAN_CanIP__RX15_DH EQU CYREG_CAN0_RX15_DH
CAN_CanIP__RX15_DL EQU CYREG_CAN0_RX15_DL
CAN_CanIP__RX15_ID EQU CYREG_CAN0_RX15_ID
CAN_CanIP__RX2_ACR EQU CYREG_CAN0_RX2_ACR
CAN_CanIP__RX2_ACRD EQU CYREG_CAN0_RX2_ACRD
CAN_CanIP__RX2_AMR EQU CYREG_CAN0_RX2_AMR
CAN_CanIP__RX2_AMRD EQU CYREG_CAN0_RX2_AMRD
CAN_CanIP__RX2_CMD EQU CYREG_CAN0_RX2_CMD
CAN_CanIP__RX2_DH EQU CYREG_CAN0_RX2_DH
CAN_CanIP__RX2_DL EQU CYREG_CAN0_RX2_DL
CAN_CanIP__RX2_ID EQU CYREG_CAN0_RX2_ID
CAN_CanIP__RX3_ACR EQU CYREG_CAN0_RX3_ACR
CAN_CanIP__RX3_ACRD EQU CYREG_CAN0_RX3_ACRD
CAN_CanIP__RX3_AMR EQU CYREG_CAN0_RX3_AMR
CAN_CanIP__RX3_AMRD EQU CYREG_CAN0_RX3_AMRD
CAN_CanIP__RX3_CMD EQU CYREG_CAN0_RX3_CMD
CAN_CanIP__RX3_DH EQU CYREG_CAN0_RX3_DH
CAN_CanIP__RX3_DL EQU CYREG_CAN0_RX3_DL
CAN_CanIP__RX3_ID EQU CYREG_CAN0_RX3_ID
CAN_CanIP__RX4_ACR EQU CYREG_CAN0_RX4_ACR
CAN_CanIP__RX4_ACRD EQU CYREG_CAN0_RX4_ACRD
CAN_CanIP__RX4_AMR EQU CYREG_CAN0_RX4_AMR
CAN_CanIP__RX4_AMRD EQU CYREG_CAN0_RX4_AMRD
CAN_CanIP__RX4_CMD EQU CYREG_CAN0_RX4_CMD
CAN_CanIP__RX4_DH EQU CYREG_CAN0_RX4_DH
CAN_CanIP__RX4_DL EQU CYREG_CAN0_RX4_DL
CAN_CanIP__RX4_ID EQU CYREG_CAN0_RX4_ID
CAN_CanIP__RX5_ACR EQU CYREG_CAN0_RX5_ACR
CAN_CanIP__RX5_ACRD EQU CYREG_CAN0_RX5_ACRD
CAN_CanIP__RX5_AMR EQU CYREG_CAN0_RX5_AMR
CAN_CanIP__RX5_AMRD EQU CYREG_CAN0_RX5_AMRD
CAN_CanIP__RX5_CMD EQU CYREG_CAN0_RX5_CMD
CAN_CanIP__RX5_DH EQU CYREG_CAN0_RX5_DH
CAN_CanIP__RX5_DL EQU CYREG_CAN0_RX5_DL
CAN_CanIP__RX5_ID EQU CYREG_CAN0_RX5_ID
CAN_CanIP__RX6_ACR EQU CYREG_CAN0_RX6_ACR
CAN_CanIP__RX6_ACRD EQU CYREG_CAN0_RX6_ACRD
CAN_CanIP__RX6_AMR EQU CYREG_CAN0_RX6_AMR
CAN_CanIP__RX6_AMRD EQU CYREG_CAN0_RX6_AMRD
CAN_CanIP__RX6_CMD EQU CYREG_CAN0_RX6_CMD
CAN_CanIP__RX6_DH EQU CYREG_CAN0_RX6_DH
CAN_CanIP__RX6_DL EQU CYREG_CAN0_RX6_DL
CAN_CanIP__RX6_ID EQU CYREG_CAN0_RX6_ID
CAN_CanIP__RX7_ACR EQU CYREG_CAN0_RX7_ACR
CAN_CanIP__RX7_ACRD EQU CYREG_CAN0_RX7_ACRD
CAN_CanIP__RX7_AMR EQU CYREG_CAN0_RX7_AMR
CAN_CanIP__RX7_AMRD EQU CYREG_CAN0_RX7_AMRD
CAN_CanIP__RX7_CMD EQU CYREG_CAN0_RX7_CMD
CAN_CanIP__RX7_DH EQU CYREG_CAN0_RX7_DH
CAN_CanIP__RX7_DL EQU CYREG_CAN0_RX7_DL
CAN_CanIP__RX7_ID EQU CYREG_CAN0_RX7_ID
CAN_CanIP__RX8_ACR EQU CYREG_CAN0_RX8_ACR
CAN_CanIP__RX8_ACRD EQU CYREG_CAN0_RX8_ACRD
CAN_CanIP__RX8_AMR EQU CYREG_CAN0_RX8_AMR
CAN_CanIP__RX8_AMRD EQU CYREG_CAN0_RX8_AMRD
CAN_CanIP__RX8_CMD EQU CYREG_CAN0_RX8_CMD
CAN_CanIP__RX8_DH EQU CYREG_CAN0_RX8_DH
CAN_CanIP__RX8_DL EQU CYREG_CAN0_RX8_DL
CAN_CanIP__RX8_ID EQU CYREG_CAN0_RX8_ID
CAN_CanIP__RX9_ACR EQU CYREG_CAN0_RX9_ACR
CAN_CanIP__RX9_ACRD EQU CYREG_CAN0_RX9_ACRD
CAN_CanIP__RX9_AMR EQU CYREG_CAN0_RX9_AMR
CAN_CanIP__RX9_AMRD EQU CYREG_CAN0_RX9_AMRD
CAN_CanIP__RX9_CMD EQU CYREG_CAN0_RX9_CMD
CAN_CanIP__RX9_DH EQU CYREG_CAN0_RX9_DH
CAN_CanIP__RX9_DL EQU CYREG_CAN0_RX9_DL
CAN_CanIP__RX9_ID EQU CYREG_CAN0_RX9_ID
CAN_CanIP__TX0_CMD EQU CYREG_CAN0_TX0_CMD
CAN_CanIP__TX0_DH EQU CYREG_CAN0_TX0_DH
CAN_CanIP__TX0_DL EQU CYREG_CAN0_TX0_DL
CAN_CanIP__TX0_ID EQU CYREG_CAN0_TX0_ID
CAN_CanIP__TX1_CMD EQU CYREG_CAN0_TX1_CMD
CAN_CanIP__TX1_DH EQU CYREG_CAN0_TX1_DH
CAN_CanIP__TX1_DL EQU CYREG_CAN0_TX1_DL
CAN_CanIP__TX1_ID EQU CYREG_CAN0_TX1_ID
CAN_CanIP__TX2_CMD EQU CYREG_CAN0_TX2_CMD
CAN_CanIP__TX2_DH EQU CYREG_CAN0_TX2_DH
CAN_CanIP__TX2_DL EQU CYREG_CAN0_TX2_DL
CAN_CanIP__TX2_ID EQU CYREG_CAN0_TX2_ID
CAN_CanIP__TX3_CMD EQU CYREG_CAN0_TX3_CMD
CAN_CanIP__TX3_DH EQU CYREG_CAN0_TX3_DH
CAN_CanIP__TX3_DL EQU CYREG_CAN0_TX3_DL
CAN_CanIP__TX3_ID EQU CYREG_CAN0_TX3_ID
CAN_CanIP__TX4_CMD EQU CYREG_CAN0_TX4_CMD
CAN_CanIP__TX4_DH EQU CYREG_CAN0_TX4_DH
CAN_CanIP__TX4_DL EQU CYREG_CAN0_TX4_DL
CAN_CanIP__TX4_ID EQU CYREG_CAN0_TX4_ID
CAN_CanIP__TX5_CMD EQU CYREG_CAN0_TX5_CMD
CAN_CanIP__TX5_DH EQU CYREG_CAN0_TX5_DH
CAN_CanIP__TX5_DL EQU CYREG_CAN0_TX5_DL
CAN_CanIP__TX5_ID EQU CYREG_CAN0_TX5_ID
CAN_CanIP__TX6_CMD EQU CYREG_CAN0_TX6_CMD
CAN_CanIP__TX6_DH EQU CYREG_CAN0_TX6_DH
CAN_CanIP__TX6_DL EQU CYREG_CAN0_TX6_DL
CAN_CanIP__TX6_ID EQU CYREG_CAN0_TX6_ID
CAN_CanIP__TX7_CMD EQU CYREG_CAN0_TX7_CMD
CAN_CanIP__TX7_DH EQU CYREG_CAN0_TX7_DH
CAN_CanIP__TX7_DL EQU CYREG_CAN0_TX7_DL
CAN_CanIP__TX7_ID EQU CYREG_CAN0_TX7_ID
CAN_isr__INTC_CLR_EN_REG EQU CYREG_NVIC_CLRENA0
CAN_isr__INTC_CLR_PD_REG EQU CYREG_NVIC_CLRPEND0
CAN_isr__INTC_MASK EQU 0x10000
CAN_isr__INTC_NUMBER EQU 16
CAN_isr__INTC_PRIOR_NUM EQU 7
CAN_isr__INTC_PRIOR_REG EQU CYREG_NVIC_PRI_16
CAN_isr__INTC_SET_EN_REG EQU CYREG_NVIC_SETENA0
CAN_isr__INTC_SET_PD_REG EQU CYREG_NVIC_SETPEND0

/* RX_1 */
RX_1__0__INTTYPE EQU CYREG_PICU3_INTTYPE0
RX_1__0__MASK EQU 0x01
RX_1__0__PC EQU CYREG_PRT3_PC0
RX_1__0__PORT EQU 3
RX_1__0__SHIFT EQU 0
RX_1__AG EQU CYREG_PRT3_AG
RX_1__AMUX EQU CYREG_PRT3_AMUX
RX_1__BIE EQU CYREG_PRT3_BIE
RX_1__BIT_MASK EQU CYREG_PRT3_BIT_MASK
RX_1__BYP EQU CYREG_PRT3_BYP
RX_1__CTL EQU CYREG_PRT3_CTL
RX_1__DM0 EQU CYREG_PRT3_DM0
RX_1__DM1 EQU CYREG_PRT3_DM1
RX_1__DM2 EQU CYREG_PRT3_DM2
RX_1__DR EQU CYREG_PRT3_DR
RX_1__INP_DIS EQU CYREG_PRT3_INP_DIS
RX_1__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU3_BASE
RX_1__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
RX_1__LCD_EN EQU CYREG_PRT3_LCD_EN
RX_1__MASK EQU 0x01
RX_1__PORT EQU 3
RX_1__PRT EQU CYREG_PRT3_PRT
RX_1__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
RX_1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
RX_1__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
RX_1__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
RX_1__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
RX_1__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
RX_1__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
RX_1__PS EQU CYREG_PRT3_PS
RX_1__SHIFT EQU 0
RX_1__SLW EQU CYREG_PRT3_SLW

/* TX_1 */
TX_1__0__INTTYPE EQU CYREG_PICU3_INTTYPE1
TX_1__0__MASK EQU 0x02
TX_1__0__PC EQU CYREG_PRT3_PC1
TX_1__0__PORT EQU 3
TX_1__0__SHIFT EQU 1
TX_1__AG EQU CYREG_PRT3_AG
TX_1__AMUX EQU CYREG_PRT3_AMUX
TX_1__BIE EQU CYREG_PRT3_BIE
TX_1__BIT_MASK EQU CYREG_PRT3_BIT_MASK
TX_1__BYP EQU CYREG_PRT3_BYP
TX_1__CTL EQU CYREG_PRT3_CTL
TX_1__DM0 EQU CYREG_PRT3_DM0
TX_1__DM1 EQU CYREG_PRT3_DM1
TX_1__DM2 EQU CYREG_PRT3_DM2
TX_1__DR EQU CYREG_PRT3_DR
TX_1__INP_DIS EQU CYREG_PRT3_INP_DIS
TX_1__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU3_BASE
TX_1__LCD_COM_SEG EQU CYREG_PRT3_LCD_COM_SEG
TX_1__LCD_EN EQU CYREG_PRT3_LCD_EN
TX_1__MASK EQU 0x02
TX_1__PORT EQU 3
TX_1__PRT EQU CYREG_PRT3_PRT
TX_1__PRTDSI__CAPS_SEL EQU CYREG_PRT3_CAPS_SEL
TX_1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT3_DBL_SYNC_IN
TX_1__PRTDSI__OE_SEL0 EQU CYREG_PRT3_OE_SEL0
TX_1__PRTDSI__OE_SEL1 EQU CYREG_PRT3_OE_SEL1
TX_1__PRTDSI__OUT_SEL0 EQU CYREG_PRT3_OUT_SEL0
TX_1__PRTDSI__OUT_SEL1 EQU CYREG_PRT3_OUT_SEL1
TX_1__PRTDSI__SYNC_OUT EQU CYREG_PRT3_SYNC_OUT
TX_1__PS EQU CYREG_PRT3_PS
TX_1__SHIFT EQU 1
TX_1__SLW EQU CYREG_PRT3_SLW

/* LED_RED */
LED_RED__0__INTTYPE EQU CYREG_PICU0_INTTYPE6
LED_RED__0__MASK EQU 0x40
LED_RED__0__PC EQU CYREG_PRT0_PC6
LED_RED__0__PORT EQU 0
LED_RED__0__SHIFT EQU 6
LED_RED__AG EQU CYREG_PRT0_AG
LED_RED__AMUX EQU CYREG_PRT0_AMUX
LED_RED__BIE EQU CYREG_PRT0_BIE
LED_RED__BIT_MASK EQU CYREG_PRT0_BIT_MASK
LED_RED__BYP EQU CYREG_PRT0_BYP
LED_RED__CTL EQU CYREG_PRT0_CTL
LED_RED__DM0 EQU CYREG_PRT0_DM0
LED_RED__DM1 EQU CYREG_PRT0_DM1
LED_RED__DM2 EQU CYREG_PRT0_DM2
LED_RED__DR EQU CYREG_PRT0_DR
LED_RED__INP_DIS EQU CYREG_PRT0_INP_DIS
LED_RED__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU0_BASE
LED_RED__LCD_COM_SEG EQU CYREG_PRT0_LCD_COM_SEG
LED_RED__LCD_EN EQU CYREG_PRT0_LCD_EN
LED_RED__MASK EQU 0x40
LED_RED__PORT EQU 0
LED_RED__PRT EQU CYREG_PRT0_PRT
LED_RED__PRTDSI__CAPS_SEL EQU CYREG_PRT0_CAPS_SEL
LED_RED__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT0_DBL_SYNC_IN
LED_RED__PRTDSI__OE_SEL0 EQU CYREG_PRT0_OE_SEL0
LED_RED__PRTDSI__OE_SEL1 EQU CYREG_PRT0_OE_SEL1
LED_RED__PRTDSI__OUT_SEL0 EQU CYREG_PRT0_OUT_SEL0
LED_RED__PRTDSI__OUT_SEL1 EQU CYREG_PRT0_OUT_SEL1
LED_RED__PRTDSI__SYNC_OUT EQU CYREG_PRT0_SYNC_OUT
LED_RED__PS EQU CYREG_PRT0_PS
LED_RED__SHIFT EQU 6
LED_RED__SLW EQU CYREG_PRT0_SLW

/* DEBUG_RX */
DEBUG_RX__0__INTTYPE EQU CYREG_PICU12_INTTYPE6
DEBUG_RX__0__MASK EQU 0x40
DEBUG_RX__0__PC EQU CYREG_PRT12_PC6
DEBUG_RX__0__PORT EQU 12
DEBUG_RX__0__SHIFT EQU 6
DEBUG_RX__AG EQU CYREG_PRT12_AG
DEBUG_RX__BIE EQU CYREG_PRT12_BIE
DEBUG_RX__BIT_MASK EQU CYREG_PRT12_BIT_MASK
DEBUG_RX__BYP EQU CYREG_PRT12_BYP
DEBUG_RX__DM0 EQU CYREG_PRT12_DM0
DEBUG_RX__DM1 EQU CYREG_PRT12_DM1
DEBUG_RX__DM2 EQU CYREG_PRT12_DM2
DEBUG_RX__DR EQU CYREG_PRT12_DR
DEBUG_RX__INP_DIS EQU CYREG_PRT12_INP_DIS
DEBUG_RX__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
DEBUG_RX__MASK EQU 0x40
DEBUG_RX__PORT EQU 12
DEBUG_RX__PRT EQU CYREG_PRT12_PRT
DEBUG_RX__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
DEBUG_RX__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
DEBUG_RX__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
DEBUG_RX__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
DEBUG_RX__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
DEBUG_RX__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
DEBUG_RX__PS EQU CYREG_PRT12_PS
DEBUG_RX__SHIFT EQU 6
DEBUG_RX__SIO_CFG EQU CYREG_PRT12_SIO_CFG
DEBUG_RX__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
DEBUG_RX__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
DEBUG_RX__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
DEBUG_RX__SLW EQU CYREG_PRT12_SLW

/* DEBUG_TX */
DEBUG_TX__0__INTTYPE EQU CYREG_PICU12_INTTYPE7
DEBUG_TX__0__MASK EQU 0x80
DEBUG_TX__0__PC EQU CYREG_PRT12_PC7
DEBUG_TX__0__PORT EQU 12
DEBUG_TX__0__SHIFT EQU 7
DEBUG_TX__AG EQU CYREG_PRT12_AG
DEBUG_TX__BIE EQU CYREG_PRT12_BIE
DEBUG_TX__BIT_MASK EQU CYREG_PRT12_BIT_MASK
DEBUG_TX__BYP EQU CYREG_PRT12_BYP
DEBUG_TX__DM0 EQU CYREG_PRT12_DM0
DEBUG_TX__DM1 EQU CYREG_PRT12_DM1
DEBUG_TX__DM2 EQU CYREG_PRT12_DM2
DEBUG_TX__DR EQU CYREG_PRT12_DR
DEBUG_TX__INP_DIS EQU CYREG_PRT12_INP_DIS
DEBUG_TX__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU12_BASE
DEBUG_TX__MASK EQU 0x80
DEBUG_TX__PORT EQU 12
DEBUG_TX__PRT EQU CYREG_PRT12_PRT
DEBUG_TX__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
DEBUG_TX__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
DEBUG_TX__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
DEBUG_TX__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
DEBUG_TX__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
DEBUG_TX__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
DEBUG_TX__PS EQU CYREG_PRT12_PS
DEBUG_TX__SHIFT EQU 7
DEBUG_TX__SIO_CFG EQU CYREG_PRT12_SIO_CFG
DEBUG_TX__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
DEBUG_TX__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
DEBUG_TX__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
DEBUG_TX__SLW EQU CYREG_PRT12_SLW

/* UART_LOG */
UART_LOG_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B1_UDB08_09_ACTL
UART_LOG_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG EQU CYREG_B1_UDB08_09_CTL
UART_LOG_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG EQU CYREG_B1_UDB08_09_CTL
UART_LOG_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG EQU CYREG_B1_UDB08_09_CTL
UART_LOG_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG EQU CYREG_B1_UDB08_09_CTL
UART_LOG_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG EQU CYREG_B1_UDB08_09_MSK
UART_LOG_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG EQU CYREG_B1_UDB08_09_MSK
UART_LOG_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG EQU CYREG_B1_UDB08_09_MSK
UART_LOG_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG EQU CYREG_B1_UDB08_09_MSK
UART_LOG_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG EQU CYREG_B1_UDB08_ACTL
UART_LOG_BUART_sRX_RxBitCounter__CONTROL_REG EQU CYREG_B1_UDB08_CTL
UART_LOG_BUART_sRX_RxBitCounter__CONTROL_ST_REG EQU CYREG_B1_UDB08_ST_CTL
UART_LOG_BUART_sRX_RxBitCounter__COUNT_REG EQU CYREG_B1_UDB08_CTL
UART_LOG_BUART_sRX_RxBitCounter__COUNT_ST_REG EQU CYREG_B1_UDB08_ST_CTL
UART_LOG_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG EQU CYREG_B1_UDB08_MSK_ACTL
UART_LOG_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG EQU CYREG_B1_UDB08_MSK_ACTL
UART_LOG_BUART_sRX_RxBitCounter__PERIOD_REG EQU CYREG_B1_UDB08_MSK
UART_LOG_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B1_UDB08_09_ACTL
UART_LOG_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG EQU CYREG_B1_UDB08_09_ST
UART_LOG_BUART_sRX_RxBitCounter_ST__MASK_REG EQU CYREG_B1_UDB08_MSK
UART_LOG_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG EQU CYREG_B1_UDB08_MSK_ACTL
UART_LOG_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG EQU CYREG_B1_UDB08_MSK_ACTL
UART_LOG_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG EQU CYREG_B1_UDB08_ACTL
UART_LOG_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG EQU CYREG_B1_UDB08_ST_CTL
UART_LOG_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG EQU CYREG_B1_UDB08_ST_CTL
UART_LOG_BUART_sRX_RxBitCounter_ST__STATUS_REG EQU CYREG_B1_UDB08_ST
UART_LOG_BUART_sRX_RxShifter_u0__16BIT_A0_REG EQU CYREG_B1_UDB08_09_A0
UART_LOG_BUART_sRX_RxShifter_u0__16BIT_A1_REG EQU CYREG_B1_UDB08_09_A1
UART_LOG_BUART_sRX_RxShifter_u0__16BIT_D0_REG EQU CYREG_B1_UDB08_09_D0
UART_LOG_BUART_sRX_RxShifter_u0__16BIT_D1_REG EQU CYREG_B1_UDB08_09_D1
UART_LOG_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B1_UDB08_09_ACTL
UART_LOG_BUART_sRX_RxShifter_u0__16BIT_F0_REG EQU CYREG_B1_UDB08_09_F0
UART_LOG_BUART_sRX_RxShifter_u0__16BIT_F1_REG EQU CYREG_B1_UDB08_09_F1
UART_LOG_BUART_sRX_RxShifter_u0__A0_A1_REG EQU CYREG_B1_UDB08_A0_A1
UART_LOG_BUART_sRX_RxShifter_u0__A0_REG EQU CYREG_B1_UDB08_A0
UART_LOG_BUART_sRX_RxShifter_u0__A1_REG EQU CYREG_B1_UDB08_A1
UART_LOG_BUART_sRX_RxShifter_u0__D0_D1_REG EQU CYREG_B1_UDB08_D0_D1
UART_LOG_BUART_sRX_RxShifter_u0__D0_REG EQU CYREG_B1_UDB08_D0
UART_LOG_BUART_sRX_RxShifter_u0__D1_REG EQU CYREG_B1_UDB08_D1
UART_LOG_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG EQU CYREG_B1_UDB08_ACTL
UART_LOG_BUART_sRX_RxShifter_u0__F0_F1_REG EQU CYREG_B1_UDB08_F0_F1
UART_LOG_BUART_sRX_RxShifter_u0__F0_REG EQU CYREG_B1_UDB08_F0
UART_LOG_BUART_sRX_RxShifter_u0__F1_REG EQU CYREG_B1_UDB08_F1
UART_LOG_BUART_sRX_RxShifter_u0__MSK_DP_AUX_CTL_REG EQU CYREG_B1_UDB08_MSK_ACTL
UART_LOG_BUART_sRX_RxShifter_u0__PER_DP_AUX_CTL_REG EQU CYREG_B1_UDB08_MSK_ACTL
UART_LOG_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B1_UDB09_10_ACTL
UART_LOG_BUART_sRX_RxSts__16BIT_STATUS_REG EQU CYREG_B1_UDB09_10_ST
UART_LOG_BUART_sRX_RxSts__3__MASK EQU 0x08
UART_LOG_BUART_sRX_RxSts__3__POS EQU 3
UART_LOG_BUART_sRX_RxSts__4__MASK EQU 0x10
UART_LOG_BUART_sRX_RxSts__4__POS EQU 4
UART_LOG_BUART_sRX_RxSts__5__MASK EQU 0x20
UART_LOG_BUART_sRX_RxSts__5__POS EQU 5
UART_LOG_BUART_sRX_RxSts__MASK EQU 0x38
UART_LOG_BUART_sRX_RxSts__MASK_REG EQU CYREG_B1_UDB09_MSK
UART_LOG_BUART_sRX_RxSts__STATUS_AUX_CTL_REG EQU CYREG_B1_UDB09_ACTL
UART_LOG_BUART_sRX_RxSts__STATUS_REG EQU CYREG_B1_UDB09_ST
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG EQU CYREG_B1_UDB10_11_A0
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG EQU CYREG_B1_UDB10_11_A1
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG EQU CYREG_B1_UDB10_11_D0
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG EQU CYREG_B1_UDB10_11_D1
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG EQU CYREG_B1_UDB10_11_ACTL
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG EQU CYREG_B1_UDB10_11_F0
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG EQU CYREG_B1_UDB10_11_F1
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG EQU CYREG_B1_UDB10_A0_A1
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG EQU CYREG_B1_UDB10_A0
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG EQU CYREG_B1_UDB10_A1
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG EQU CYREG_B1_UDB10_D0_D1
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG EQU CYREG_B1_UDB10_D0
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG EQU CYREG_B1_UDB10_D1
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG EQU CYREG_B1_UDB10_ACTL
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG EQU CYREG_B1_UDB10_F0_F1
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG EQU CYREG_B1_UDB10_F0
UART_LOG_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG EQU CYREG_B1_UDB10_F1
UART_LOG_BUART_sTX_TxShifter_u0__A0_A1_REG EQU CYREG_B1_UDB11_A0_A1
UART_LOG_BUART_sTX_TxShifter_u0__A0_REG EQU CYREG_B1_UDB11_A0
UART_LOG_BUART_sTX_TxShifter_u0__A1_REG EQU CYREG_B1_UDB11_A1
UART_LOG_BUART_sTX_TxShifter_u0__D0_D1_REG EQU CYREG_B1_UDB11_D0_D1
UART_LOG_BUART_sTX_TxShifter_u0__D0_REG EQU CYREG_B1_UDB11_D0
UART_LOG_BUART_sTX_TxShifter_u0__D1_REG EQU CYREG_B1_UDB11_D1
UART_LOG_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG EQU CYREG_B1_UDB11_ACTL
UART_LOG_BUART_sTX_TxShifter_u0__F0_F1_REG EQU CYREG_B1_UDB11_F0_F1
UART_LOG_BUART_sTX_TxShifter_u0__F0_REG EQU CYREG_B1_UDB11_F0
UART_LOG_BUART_sTX_TxShifter_u0__F1_REG EQU CYREG_B1_UDB11_F1
UART_LOG_BUART_sTX_TxSts__0__MASK EQU 0x01
UART_LOG_BUART_sTX_TxSts__0__POS EQU 0
UART_LOG_BUART_sTX_TxSts__1__MASK EQU 0x02
UART_LOG_BUART_sTX_TxSts__1__POS EQU 1
UART_LOG_BUART_sTX_TxSts__2__MASK EQU 0x04
UART_LOG_BUART_sTX_TxSts__2__POS EQU 2
UART_LOG_BUART_sTX_TxSts__3__MASK EQU 0x08
UART_LOG_BUART_sTX_TxSts__3__POS EQU 3
UART_LOG_BUART_sTX_TxSts__MASK EQU 0x0F
UART_LOG_BUART_sTX_TxSts__MASK_REG EQU CYREG_B1_UDB11_MSK
UART_LOG_BUART_sTX_TxSts__STATUS_AUX_CTL_REG EQU CYREG_B1_UDB11_ACTL
UART_LOG_BUART_sTX_TxSts__STATUS_REG EQU CYREG_B1_UDB11_ST
UART_LOG_IntClock__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
UART_LOG_IntClock__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
UART_LOG_IntClock__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
UART_LOG_IntClock__CFG2_SRC_SEL_MASK EQU 0x07
UART_LOG_IntClock__INDEX EQU 0x00
UART_LOG_IntClock__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
UART_LOG_IntClock__PM_ACT_MSK EQU 0x01
UART_LOG_IntClock__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
UART_LOG_IntClock__PM_STBY_MSK EQU 0x01

/* LED_GREEN */
LED_GREEN__0__INTTYPE EQU CYREG_PICU0_INTTYPE7
LED_GREEN__0__MASK EQU 0x80
LED_GREEN__0__PC EQU CYREG_PRT0_PC7
LED_GREEN__0__PORT EQU 0
LED_GREEN__0__SHIFT EQU 7
LED_GREEN__AG EQU CYREG_PRT0_AG
LED_GREEN__AMUX EQU CYREG_PRT0_AMUX
LED_GREEN__BIE EQU CYREG_PRT0_BIE
LED_GREEN__BIT_MASK EQU CYREG_PRT0_BIT_MASK
LED_GREEN__BYP EQU CYREG_PRT0_BYP
LED_GREEN__CTL EQU CYREG_PRT0_CTL
LED_GREEN__DM0 EQU CYREG_PRT0_DM0
LED_GREEN__DM1 EQU CYREG_PRT0_DM1
LED_GREEN__DM2 EQU CYREG_PRT0_DM2
LED_GREEN__DR EQU CYREG_PRT0_DR
LED_GREEN__INP_DIS EQU CYREG_PRT0_INP_DIS
LED_GREEN__INTTYPE_BASE EQU CYDEV_PICU_INTTYPE_PICU0_BASE
LED_GREEN__LCD_COM_SEG EQU CYREG_PRT0_LCD_COM_SEG
LED_GREEN__LCD_EN EQU CYREG_PRT0_LCD_EN
LED_GREEN__MASK EQU 0x80
LED_GREEN__PORT EQU 0
LED_GREEN__PRT EQU CYREG_PRT0_PRT
LED_GREEN__PRTDSI__CAPS_SEL EQU CYREG_PRT0_CAPS_SEL
LED_GREEN__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT0_DBL_SYNC_IN
LED_GREEN__PRTDSI__OE_SEL0 EQU CYREG_PRT0_OE_SEL0
LED_GREEN__PRTDSI__OE_SEL1 EQU CYREG_PRT0_OE_SEL1
LED_GREEN__PRTDSI__OUT_SEL0 EQU CYREG_PRT0_OUT_SEL0
LED_GREEN__PRTDSI__OUT_SEL1 EQU CYREG_PRT0_OUT_SEL1
LED_GREEN__PRTDSI__SYNC_OUT EQU CYREG_PRT0_SYNC_OUT
LED_GREEN__PS EQU CYREG_PRT0_PS
LED_GREEN__SHIFT EQU 7
LED_GREEN__SLW EQU CYREG_PRT0_SLW

/* Miscellaneous */
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PSOC4A EQU 26
CYDEV_CHIP_DIE_PSOC5LP EQU 2
CYDEV_CHIP_DIE_PSOC5TM EQU 3
CYDEV_CHIP_DIE_TMA4 EQU 4
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_FM0P EQU 5
CYDEV_CHIP_FAMILY_FM3 EQU 6
CYDEV_CHIP_FAMILY_FM4 EQU 7
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_PSOC6 EQU 4
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E161069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 26
CYDEV_CHIP_MEMBER_4AA EQU 25
CYDEV_CHIP_MEMBER_4AB EQU 30
CYDEV_CHIP_MEMBER_4AC EQU 14
CYDEV_CHIP_MEMBER_4AD EQU 15
CYDEV_CHIP_MEMBER_4AE EQU 16
CYDEV_CHIP_MEMBER_4D EQU 20
CYDEV_CHIP_MEMBER_4E EQU 6
CYDEV_CHIP_MEMBER_4F EQU 27
CYDEV_CHIP_MEMBER_4G EQU 4
CYDEV_CHIP_MEMBER_4H EQU 24
CYDEV_CHIP_MEMBER_4I EQU 32
CYDEV_CHIP_MEMBER_4J EQU 21
CYDEV_CHIP_MEMBER_4K EQU 22
CYDEV_CHIP_MEMBER_4L EQU 31
CYDEV_CHIP_MEMBER_4M EQU 29
CYDEV_CHIP_MEMBER_4N EQU 11
CYDEV_CHIP_MEMBER_4O EQU 8
CYDEV_CHIP_MEMBER_4P EQU 28
CYDEV_CHIP_MEMBER_4Q EQU 17
CYDEV_CHIP_MEMBER_4R EQU 9
CYDEV_CHIP_MEMBER_4S EQU 12
CYDEV_CHIP_MEMBER_4T EQU 10
CYDEV_CHIP_MEMBER_4U EQU 5
CYDEV_CHIP_MEMBER_4V EQU 23
CYDEV_CHIP_MEMBER_4W EQU 13
CYDEV_CHIP_MEMBER_4X EQU 7
CYDEV_CHIP_MEMBER_4Y EQU 18
CYDEV_CHIP_MEMBER_4Z EQU 19
CYDEV_CHIP_MEMBER_5A EQU 3
CYDEV_CHIP_MEMBER_5B EQU 2
CYDEV_CHIP_MEMBER_6A EQU 33
CYDEV_CHIP_MEMBER_FM3 EQU 37
CYDEV_CHIP_MEMBER_FM4 EQU 38
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 EQU 34
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 EQU 35
CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 EQU 36
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5TM_ES1 EQU 1
CYDEV_CHIP_REV_PSOC5TM_PRODUCTION EQU 1
CYDEV_CHIP_REV_TMA4_ES EQU 17
CYDEV_CHIP_REV_TMA4_ES2 EQU 33
CYDEV_CHIP_REV_TMA4_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4AA_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4AB_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4AC_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4AD_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4AE_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4H_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4I_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4J_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4K_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4N_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4O_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4P_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4Q_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4R_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4S_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4T_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4U_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4V_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4W_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4X_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4Y_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4Z_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_6A_ES EQU 17
CYDEV_CHIP_REVISION_6A_NO_UDB EQU 33
CYDEV_CHIP_REVISION_6A_PRODUCTION EQU 33
CYDEV_CHIP_REVISION_FM3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_FM4_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x80
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000000
CYDEV_IS_EXPORTING_CODE EQU 0
CYDEV_IS_IMPORTING_CODE EQU 0
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_STACK_SIZE EQU 0x0800
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3_MV EQU 5000
CYIPBLOCK_ARM_CM3_VERSION EQU 0
CYIPBLOCK_P3_ANAIF_VERSION EQU 0
CYIPBLOCK_P3_CAN_VERSION EQU 0
CYIPBLOCK_P3_CAPSENSE_VERSION EQU 0
CYIPBLOCK_P3_COMP_VERSION EQU 0
CYIPBLOCK_P3_DECIMATOR_VERSION EQU 0
CYIPBLOCK_P3_DFB_VERSION EQU 0
CYIPBLOCK_P3_DMA_VERSION EQU 0
CYIPBLOCK_P3_DRQ_VERSION EQU 0
CYIPBLOCK_P3_DSM_VERSION EQU 0
CYIPBLOCK_P3_EMIF_VERSION EQU 0
CYIPBLOCK_P3_I2C_VERSION EQU 0
CYIPBLOCK_P3_LCD_VERSION EQU 0
CYIPBLOCK_P3_LPF_VERSION EQU 0
CYIPBLOCK_P3_OPAMP_VERSION EQU 0
CYIPBLOCK_P3_PM_VERSION EQU 0
CYIPBLOCK_P3_SCCT_VERSION EQU 0
CYIPBLOCK_P3_TIMER_VERSION EQU 0
CYIPBLOCK_P3_USB_VERSION EQU 0
CYIPBLOCK_P3_VIDAC_VERSION EQU 0
CYIPBLOCK_P3_VREF_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 0
CYIPBLOCK_S8_IRQ_VERSION EQU 0
CYIPBLOCK_S8_SAR_VERSION EQU 0
CYIPBLOCK_S8_SIO_VERSION EQU 0
CYIPBLOCK_S8_UDB_VERSION EQU 0
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERIAR_INC */
