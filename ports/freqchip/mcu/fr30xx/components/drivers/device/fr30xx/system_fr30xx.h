/*
  ******************************************************************************
  * @file    system_fr30xx.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Device Peripheral Access Layer System Headler File.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  * 
  ******************************************************************************
*/
#ifndef __SYSTEM_FR30XX_H__
#define __SYSTEM_FR30XX_H__

#include "fr30xx.h"

/** @addtogroup System_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Soc Clock config Register */
typedef struct
{
    uint32_t SPLL_EN             : 1;
    uint32_t AUPLL_EN            : 1;
    uint32_t SPLL_CLK_DIV2_EN    : 1;
    uint32_t AUPLL_DIV2_EN       : 1;
    uint32_t SOC_CLK_DIV         : 4;
    uint32_t CORE_HSCK_SEL       : 1;
    uint32_t MCU_CLK_SEL         : 1;
    uint32_t rsv_0               : 6;
    uint32_t SOC_FCLK_EN         : 1;
    uint32_t rsv_1               : 15;
}REG_SOCCLK_CTL_t;

/* Bus Clock Divider control0 Register */
typedef struct
{
    uint32_t MCU_CLK_DIV       : 4;
    uint32_t MCU_ST_CLK_DIV    : 4;
    uint32_t APB0_RATIO        : 2;
    uint32_t APB1_RATIO        : 2;
    uint32_t APB2_RATIO        : 2;
    uint32_t rsv_0             : 18;
}REG_BUSCLK_DIV_t;

/* Block Clock select Register */
typedef struct
{
    uint32_t SDIOH0_CLK_SEL    : 2;
    uint32_t rsv_0             : 2;
    uint32_t QSPI0_CLK_SEL     : 2;
    uint32_t QSPI1_CLK_SEL     : 2;
    uint32_t OSPI_CLK_SEL      : 2;
    uint32_t SSIS_CLK_SEL      : 2;
    uint32_t MSPI0_CLK_SEL     : 2;
    uint32_t MSPI1_CLK_SEL     : 2;
    uint32_t USB_CLK_SEL       : 2;
    uint32_t DISPLAY_CLK_SEL   : 2;
    uint32_t GPIO_CLK_SEL      : 1;
    uint32_t UART_CLK_SEL      : 1;
    uint32_t I2C_CLK_SEL       : 1;
    uint32_t rsv_1             : 3;
    uint32_t SSIM_CLK_SEL      : 1;
    uint32_t MCAN_CLK_SEL      : 2;
    uint32_t PWM_CLK_SEL       : 1;  
    uint32_t rsv_2             : 2;        
}REG_BLOCKCLK_SEL_t;

/* Audio Clock select Register */
typedef struct
{
    uint32_t SPDIF_CLK_SEL     : 2;
    uint32_t I2S_CLK_SEL       : 2;
    uint32_t PDM0_CLK_SEL      : 2;
    uint32_t PDM1_CLK_SEL      : 2;
    uint32_t rsv_0             : 3; 
    uint32_t AES_CLK_SEL       : 1;  
    uint32_t CDC_PLL_CLK_SEL   : 1;            
    uint32_t rsv_1             : 19;    
}REG_AUDIOCLK_SEL_t;

/* Block Clock Divider control0 Register */
typedef struct
{
    uint32_t SDIOH0_CLK_DIV    : 4;
    uint32_t rsv_0             : 4;
    uint32_t QSPI0_CLK_DIV     : 4;
    uint32_t QSPI1_CLK_DIV     : 4;
    uint32_t OSPI_CLK_DIV      : 4;
    uint32_t SSIS_CLK_DIV      : 4;
    uint32_t MSPI0_CLK_DIV     : 4;
    uint32_t MSPI1_CLK_DIV     : 4;
}REG_BLOCKCLK_DIV0_t;

/* Block Clock Divider control1 Register */
typedef struct
{
    uint32_t DISPLAY_CLK_DIV   : 2;
    uint32_t rsv_0             : 2;
    uint32_t GPIO_CLK_DIV      : 4;
    uint32_t UART_CLK_DIV      : 2;
    uint32_t rsv_1             : 2;
    uint32_t I2C_CLK_DIV       : 2;
    uint32_t rsv_2             : 14;
    uint32_t SSIM_CLK_DIV      : 2;
    uint32_t rsv_3             : 2;
}REG_BLOCKCLK_DIV1_t;

/* Block Clock Divider control2 Register */
typedef struct
{
    uint32_t rsv_0             : 4;
    uint32_t MCAN_CLK_DIV      : 3;
    uint32_t rsv_1             : 1;    
    uint32_t PWM_CLK_DIV       : 4;
    uint32_t FRSPIM_CLK_DIV    : 4;
    uint32_t rsv_2             : 4;
    uint32_t TIMER01_CLK_DIV   : 4;
    uint32_t TIMER23_CLK_DIV   : 4;
    uint32_t rsv_3             : 4;
}REG_BLOCKCLK_DIV2_t;

/* Audio Clock Divider control Register */
typedef struct
{
    uint32_t SPDIF_CLK_DIV     : 4;
    uint32_t I2S_CLK_DIV       : 4;
    uint32_t PDM0_CLK_DIV      : 4;
    uint32_t PDM1_CLK_DIV      : 4;
    uint32_t rsv_0             : 8;     
    uint32_t AES_CLK_DIV       : 3; 
    uint32_t rsv_1             : 1;     
    uint32_t TIMER45_CLK_DIV   : 4;
}REG_AUDIOCLK_DIV_t;

/* Bus Clock control Enable0 Register */
typedef struct
{
    uint32_t CM33_MAS_CLKEN    : 1;
    uint32_t CODE_BUS_CLKEN    : 1;
    uint32_t SYS_BUS_CLKEN     : 1;
    uint32_t APB_CLKEN         : 1;
    uint32_t APB0_CLKEN        : 1;
    uint32_t APB1_CLKEN        : 1;
    uint32_t APB2_CLKEN        : 1;
    uint32_t CRAM0_CLKEN       : 1;
    uint32_t CRAM1_CLKEN       : 1;
    uint32_t SRAM0_CLKEN       : 1;
    uint32_t SRAM1_CLKEN       : 1;
    uint32_t SRAM2_CLKEN       : 1;
    uint32_t BOOT_ROM_CLKEN    : 1;
    uint32_t rsv_0             : 1;
    uint32_t QSPI0_P_CLKEN     : 1;
    uint32_t QSPI1_P_CLKEN     : 1;
    uint32_t OSPI_P_CLKEN      : 1; 
    uint32_t SRAM3_CLKEN       : 1;     
    uint32_t rsv_1             : 14;  
}REG_CLK_EN0_t;

/* CACHE and DMAC Clock Enable1 Register */
typedef struct
{
    uint32_t PFC_CLKEN    : 1;
    uint32_t AHBC_CLKEN   : 1;
    uint32_t DMAC0_CLKEN  : 1;
    uint32_t DMAC1_CLKEN  : 1;
    uint32_t rsv_0        : 28;
}REG_CLK_EN1_t;

/* SDIO and CAN Clock Enable2 Register */
typedef struct
{
    uint32_t SDIOH0_CLKEN : 1;
    uint32_t rsv_0        : 1;
    uint32_t MCAN0_CLKEN  : 1;
    uint32_t MCAN1_CLKEN  : 1;
    uint32_t MCAN2_CLKEN  : 1;
    uint32_t MCAN3_CLKEN  : 1;
    uint32_t rsv_1        : 26; 
}REG_CLK_EN2_t;

/* TIMER and WDT Clock Enable3 Register */
typedef struct
{
    uint32_t TIMER0_CLKEN  : 1;
    uint32_t TIMER1_CLKEN  : 1;
    uint32_t TIMER2_CLKEN  : 1;
    uint32_t TIMER3_CLKEN  : 1;
    uint32_t WDT_CLKEN     : 1;
    uint32_t rsv_0         : 1;
    uint32_t TIMER4_CLKEN  : 1;
    uint32_t TIMER5_CLKEN  : 1;
    uint32_t rsv_1         : 24;
}REG_CLK_EN3_t;

/* GPIO and PWM Clock Enable4 Register */
typedef struct
{
    uint32_t GPIOA_CLKEN   : 1;
    uint32_t GPIOB_CLKEN   : 1;
    uint32_t GPIOC_CLKEN   : 1;
    uint32_t GPIOD_CLKEN   : 1;
    uint32_t PWM0_CLKEN    : 1;
    uint32_t PWM1_CLKEN    : 1;
    uint32_t GPIOE_CLKEN   : 1;    
    uint32_t rsv_0         : 25;
}REG_CLK_EN4_t;

/* UART and I2C Clock Enable5 Register */
typedef struct
{
    uint32_t UART0_CLKEN  : 1;
    uint32_t UART1_CLKEN  : 1;
    uint32_t UART2_CLKEN  : 1;
    uint32_t UART3_CLKEN  : 1;
    uint32_t UART4_CLKEN  : 1;
    uint32_t UART5_CLKEN  : 1;
    uint32_t I2C0_CLKEN   : 1;
    uint32_t rsv_0        : 1;
    uint32_t I2C1_CLKEN   : 1;
    uint32_t rsv_1        : 1;
    uint32_t I2C2_CLKEN   : 1;  
    uint32_t rsv_2        : 21; 
}REG_CLK_EN5_t;

/* SPI Clock Enable6 Register */
typedef struct
{
    uint32_t SSIM0_CLKEN     : 1;
    uint32_t SSIM1_CLKEN     : 1;    
    uint32_t rsv_0           : 1;
    uint32_t SSIS0_CLKEN     : 1;
    uint32_t SSIS1_CLKEN     : 1;
    uint32_t MSPI0_CLKEN     : 1; 
    uint32_t MSPI1_CLKEN     : 1;  
    uint32_t QSPI0_CLKEN     : 1;
    uint32_t QSPI0_H_CLKEN   : 1;
    uint32_t QSPI1_CLKEN     : 1;
    uint32_t QSPI1_H_CLKEN   : 1;
    uint32_t OSPI_CLKEN      : 1;
    uint32_t OSPI_H_CLKEN    : 1;    
    uint32_t rsv_1           : 19;    
}REG_CLK_EN6_t;

/* HW and ENGINE Clock Enable7 Register */
typedef struct
{
    uint32_t rsv_0         : 7;    
    uint32_t TRNG_CLKEN    : 1;
    uint32_t CRC_CLKEN     : 1;
    uint32_t rsv_1         : 1;
    uint32_t YUV2RGB_CLKEN : 1; 
    uint32_t AES_CLKEN     : 1;     
    uint32_t rsv_2         : 20;
}REG_CLK_EN7_t;

/* AUDIO and DEVICE Clock Enable8 Register */
typedef struct
{
    uint32_t SPDIF_CLKEN       : 1;
    uint32_t I2S0_CLKEN        : 1;
    uint32_t I2S1_CLKEN        : 1;
    uint32_t rsv_0             : 1;
    uint32_t PDM0_CLKEN        : 1;
    uint32_t PDM1_CLKEN        : 1;
    uint32_t rsv_1             : 1;
    uint32_t PSD_DAC_CLKEN     : 1;
    uint32_t rsv_2             : 24;
}REG_CLK_EN8_t;

/* MISC Clock Enable9 Register */
typedef struct
{
    uint32_t USB_CLKEN      : 1;
    uint32_t DISPLAY_CLKEN  : 1;
    uint32_t TICK_CLKEN     : 1;
    uint32_t APP_IPC_CLKEN  : 1;
    uint32_t FRSPIM_CLKEN   : 1;
    uint32_t CALI_CLKEN     : 1;
    uint32_t EFUSE0_CLKEN   : 1;
    uint32_t EFUSE1_CLKEN   : 1;
    uint32_t ADC_CLKEN      : 1;
    uint32_t COUNTER_CLKEN  : 1;
    uint32_t EFUSE2_CLKEN   : 1;
    uint32_t rsv_0          : 21;
}REG_CLK_EN9_t;

/* CPU Bus Register soft reset0 */
typedef struct
{
    uint32_t CM33_MAS_SFT_RST : 1;
    uint32_t MCU_REF_SFT_RST  : 1;
    uint32_t rsv_0            : 1;
    uint32_t APB_SFT_RST      : 1;
    uint32_t APB0_SFT_RST     : 1;
    uint32_t APB1_SFT_RST     : 1;
    uint32_t APB2_SFT_RST     : 1;
    uint32_t SPLL_SFT_RST     : 1;
    uint32_t AUPLL_SFT_RST    : 1;
    uint32_t OSCX2_SFT_RST    : 1;
    uint32_t rsv_1            : 4;
    uint32_t QSPI0_P_SFT_RST  : 1;
    uint32_t QSPI1_P_SFT_RST  : 1;
    uint32_t OSPI_P_SFT_RST   : 1;
    uint32_t rsv_2            : 15;
}REG_RESET0_t;

/* CACHE and _DMAC Register soft reset1 */
typedef struct
{
    uint32_t PFC_SFT_RST    : 1;
    uint32_t AHBC_SFT_RST   : 1;
    uint32_t DMAC0_SFT_RST  : 1;
    uint32_t DMAC1_SFT_RST  : 1;
    uint32_t rsv_0          : 28;
}REG_RESET1_t;

/* SDIO and CAN Register soft reset2 */
typedef struct
{
    uint32_t SDIOH0_SFT_RST : 1;
    uint32_t rsv_0          : 1;
    uint32_t MCAN0_SFT_RST  : 1;
    uint32_t MCAN1_SFT_RST  : 1;
    uint32_t MCAN2_SFT_RST  : 1;
    uint32_t MCAN3_SFT_RST  : 1;
    uint32_t rsv_1          : 26;
}REG_RESET2_t;

/* TINER and WDT Register soft reset3 */
typedef struct
{
    uint32_t TIMER0_SFT_RST  : 1;
    uint32_t TIMER1_SFT_RST  : 1;
    uint32_t TIMER2_SFT_RST  : 1;
    uint32_t TIMER3_SFT_RST  : 1;
    uint32_t WDT_SFT_RST     : 1;
    uint32_t rsv_0           : 1;    
    uint32_t TIMER4_SFT_RST  : 1;
    uint32_t TIMER5_SFT_RST  : 1;
    uint32_t rsv_1           : 24;
}REG_RESET3_t;

/* GPIO and PWM Register soft reset4 */
typedef struct
{
    uint32_t GPIO0_SFT_RST  : 1;
    uint32_t GPIO1_SFT_RST  : 1;
    uint32_t GPIO2_SFT_RST  : 1;
    uint32_t GPIO3_SFT_RST  : 1;
    uint32_t PWM0_SFT_RST   : 1;
    uint32_t PWM1_SFT_RST   : 1;
    uint32_t rsv_0          : 2;
    uint32_t GPIO4_SFT_RST  : 1;    
    uint32_t rsv_1          : 23;
}REG_RESET4_t;

/* UART and I2C Register soft reset5 */
typedef struct
{
    uint32_t UART0_SFT_RST  : 1;
    uint32_t UART1_SFT_RST  : 1;
    uint32_t UART2_SFT_RST  : 1;
    uint32_t UART3_SFT_RST  : 1;
    uint32_t UART4_SFT_RST  : 1;
    uint32_t UART5_SFT_RST  : 1; 
    uint32_t I2C0_SFT_RST   : 1;
    uint32_t rsv_0          : 1; 
    uint32_t I2C1_SFT_RST   : 1; 
    uint32_t rsv_1          : 1; 
    uint32_t I2C2_SFT_RST   : 1;  
    uint32_t rsv_2          : 21;
}REG_RESET5_t;

/* SPI Register soft reset6 */
typedef struct
{
    uint32_t SSIM0_SFT_RST     : 1;
    uint32_t SSIM1_SFT_RST     : 1;
    uint32_t rsv_0             : 1;
    uint32_t SSIS0_SFT_RST     : 1;
    uint32_t SSIS1_SFT_RST     : 1;
    uint32_t MSPI0_SFT_RST     : 1; 
    uint32_t MSPI1_SFT_RST     : 1;
    uint32_t QSPI0_SFT_RST     : 1; 
    uint32_t QSPI0_REF_SFT_RST : 1; 
    uint32_t QSPI1_SFT_RST     : 1; 
    uint32_t QSPI1_REF_SFT_RST : 1;  
    uint32_t OSPI_SFT_RST      : 1;  
    uint32_t OSPI_REF_SFT_RST  : 1;
    uint32_t rsv_1             : 19;
}REG_RESET6_t;

/* HW and ENGINE Register soft reset7 */
typedef struct
{
    uint32_t rsv_0           : 7;    
    uint32_t TRNG_SFT_RST    : 1; 
    uint32_t CRC_SFT_RST     : 1; 
    uint32_t rsv_1           : 1; 
    uint32_t YUV2RGB_SFT_RST : 1;  
    uint32_t AES_SFT_RST     : 1;     
    uint32_t rsv_2           : 20;
}REG_RESET7_t;

/* AUDIO and DEVICE Register soft reset8 */
typedef struct
{
    uint32_t SPDIF_SFT_RST  : 1;
    uint32_t I2S0_SFT_RST   : 1;
    uint32_t I2S1_SFT_RST   : 1;
    uint32_t rsv_0          : 1;
    uint32_t PDM0_SFT_RST   : 1;
    uint32_t PDM1_SFT_RST   : 1;
    uint32_t rsv_1          : 1;
    uint32_t CDC_SFT_RST    : 1;
    uint32_t rsv_2          : 24;
}REG_RESET8_t;

/* MISC Register soft reset9 */
typedef struct
{
    uint32_t USB_SFT_RST      : 1;
    uint32_t DISPLAY_SFT_RST  : 1;
    uint32_t TICK_SFT_RST     : 1;
    uint32_t APP_IPC_SFT_RST  : 1;
    uint32_t FRSPIM_SFT_RST   : 1;
    uint32_t CALI_SFT_RST     : 1; 
    uint32_t EFUSE0_SFT_RST   : 1;
    uint32_t EFUSE1_SFT_RST   : 1; 
    uint32_t ADC_SFT_RST      : 1;  
    uint32_t COUNTER_SFT_RST  : 1; 
    uint32_t EFUSE2_SFT_RST   : 1;    
    uint32_t rsv_0            : 21;
}REG_RESET9_t;

/* DSP Clock Divider control Register */
typedef struct
{
    uint32_t DSP_TIMER_CLK_DIV : 4;
    uint32_t DSP_WDT_CLK_DIV   : 4;
    uint32_t rsv_0             : 24;
}REG_DSPCLK_DIV;

/* DSP Clock Enable Register */
typedef struct
{
    uint32_t DSP_MAS_CLKEN    : 1;
    uint32_t DSP_IBD_CLKEN    : 1;
    uint32_t DSP_OBD_CLKEN    : 1;
    uint32_t DSP_TIMER0_CLKEN : 1;
    uint32_t DSP_TIMER1_CLKEN : 1;
    uint32_t DSP_WDT_CLKEN    : 1;
    uint32_t DSP_IPC_CLKEN    : 1;
    uint32_t rsv_0            : 1;
    uint32_t DSP_APBCLKEN     : 1;
    uint32_t DSP_DAPCLKEN     : 1;
    uint32_t rsv_1            : 22;
}REG_DSPCLK_EN_t;

/* DSP Register soft reset */
typedef struct
{
    uint32_t DSP_MAS_SFT_RST    : 1;
    uint32_t DSP_IPC_SFT_RST    : 1;
    uint32_t DSP_TIMER0_SFT_RST : 1;
    uint32_t DSP_TIMER1_SFT_RST : 1;
    uint32_t DSP_CNTL_SFT_RST   : 1;
    uint32_t DSP_WDT_SFT_RST    : 1;
    uint32_t rsv_0              : 26;
}REG_DSPRESET_t;

/* QSPI PAD config */
typedef struct
{
    volatile uint32_t    QSPI_WakeupEN;
    volatile uint32_t    QSPI_PullEN;
    volatile uint32_t    QSPI_PullSelect;
    volatile uint32_t    QSPI_InputOpenCircuit;
    volatile uint32_t    QSPI_DriveCfg;
    volatile uint32_t    QSPI_FuncMux;
}REG_QSPI_PAD_CFG_t;

/* OSPI PAD config */
typedef struct
{
    volatile uint32_t    OSPI_WakeupEN;
    volatile uint32_t    OSPI_PullEN;
    volatile uint32_t    OSPI_PullSelect;
    volatile uint32_t    OSPI_InputOpenCircuit;
    volatile uint32_t    OSPI_DriveCfg;
    volatile uint32_t    OSPI_FuncMux;
}REG_OSPI_PAD_CFG_t;

/* DSP Controller Register */
typedef struct
{
    uint32_t DSP_RUNSTALL     : 1;
    uint32_t DSP_VEC_SEL      : 1;
    uint32_t DSP_DBGEN        : 1;
    uint32_t DSP_NIDEN        : 1;
    uint32_t DSP_SPIDEN       : 1;   
    uint32_t DSP_SPNIDEN      : 1; 
    uint32_t DSP_DAPSEL_MODE  : 2; 
    uint32_t DSP_WDT_PAUSE    : 1; 
    uint32_t DSP_WDT_SPEED_UP : 1; 
    uint32_t rsv_0            : 6;  
    uint32_t DSP_MEM_OFFSET   : 8;
    uint32_t rsv_1            : 8;     
}REG_DSP_CTL_t;

typedef struct
{
    uint32_t DSP_VEC_TBL : 31;
    uint32_t DSP_VEC_SEL : 1;
}REG_DSPVET_CFG_T;

/* SDIOH MISC Register */
typedef struct
{
    uint32_t SDIOH0_CD_N     : 1;
    uint32_t SDIOH0_WP       : 1;
    uint32_t SDIOH0_DAT_SWAP : 1;
    uint32_t rsv_1           : 29;
}REG_SDIOH_MISC_t;

/* MSPI DATA SWAP Register */
typedef struct
{
    uint32_t MSPI0_DAT_SWAP : 1;
    uint32_t MSPI1_DAT_SWAP : 1;
    uint32_t rsv_0          : 30;
}REG_MSPI_DATA_SWAP_t;

/* USB MISC Register */
typedef struct
{
    uint32_t USB_PHY_ADP_CFG  : 8;
    uint32_t OTG_VBUSVAL      : 1;
    uint32_t OTG_VBUSSES      : 1;
    uint32_t OTG_VBUSLO       : 1;  
    uint32_t OTG_CID          : 1;     
    uint32_t rsv_0            : 20;    
}REG_USB_MISC_t;

/* DMAC0 Endian Configure Register */
typedef struct
{
    uint32_t DMAC0_BIG_ENDIAN_SLV      : 1;
    uint32_t DMAC0_BE_SELECT_BE32_SLV  : 1;
    uint32_t rsv_0                     : 2;
    uint32_t DMAC0_BIG_ENDIAN_M1       : 1;  
    uint32_t DMAC0_BIG_ENDIAN_M2       : 1;     
    uint32_t DMAC0_BIG_ENDIAN_M3       : 1;    
    uint32_t DMAC0_BIG_ENDIAN_M4       : 1;  
    uint32_t DMAC0_BE_SELECT_BE32_M1   : 1;  
    uint32_t DMAC0_BE_SELECT_BE32_M2   : 1;  
    uint32_t DMAC0_BE_SELECT_BE32_M3   : 1;  
    uint32_t DMAC0_BE_SELECT_BE32_M4   : 1;  
    uint32_t DMAC0_LE_SELECT_LLI_M1    : 1;
    uint32_t DMAC0_LE_SELECT_LLI_M2    : 1;
    uint32_t DMAC0_LE_SELECT_LLI_M3    : 1;
    uint32_t DMAC0_LE_SELECT_LLI_M4    : 1;  
    uint32_t rsv_1                     : 16;
}REG_DMAC0_ENDIAN_CFG_t;

/* DMAC1 Endian Configure Register */
typedef struct
{
    uint32_t DMAC1_BIG_ENDIAN_SLV      : 1;
    uint32_t DMAC1_BE_SELECT_BE32_SLV  : 1;
    uint32_t rsv_0                     : 2;
    uint32_t DMAC1_BIG_ENDIAN_M1       : 1;  
    uint32_t DMAC1_BIG_ENDIAN_M2       : 1;     
    uint32_t DMAC1_BIG_ENDIAN_M3       : 1;    
    uint32_t rsv_1                     : 1;    
    uint32_t DMAC1_BE_SELECT_BE32_M1   : 1;  
    uint32_t DMAC1_BE_SELECT_BE32_M2   : 1;  
    uint32_t DMAC1_BE_SELECT_BE32_M3   : 1;  
    uint32_t rsv_2                     : 1;  
    uint32_t DMAC1_LE_SELECT_LLI_M1    : 1;
    uint32_t DMAC1_LE_SELECT_LLI_M2    : 1;
    uint32_t DMAC1_LE_SELECT_LLI_M3    : 1;  
    uint32_t rsv_3                     : 17;
}REG_DMAC1_ENDIAN_CFG_t;

/* Analog Configure3 Register */
typedef struct
{
    uint32_t PLL_M : 16;
    uint32_t PLL_N : 6;
    uint32_t rsv_0 : 10;
}REG_ANALOG_CFG3_t;

/* Audio Tune Configure Register */
typedef struct
{
    uint32_t I2S_TUEN_EN         : 1;
    uint32_t I2S_MODE            : 1; 
    uint32_t PSD_DAC_TUEN_EN     : 1;
    uint32_t PSD_DAC_MODE        : 1;  
    uint32_t SARADC_TUEN_EN      : 1;
    uint32_t SARADC_MODE         : 1; 
    uint32_t PDM0_TUEN_EN        : 1;
    uint32_t PDM0_MODE           : 1; 
    uint32_t PDM1_TUEN_EN        : 1;
    uint32_t PDM1_MODE           : 1; 
    uint32_t SPDIF_TUEN_EN       : 1;
    uint32_t SPDIF_MODE          : 1;
    uint32_t rsv_0               : 20;    
}REG_AUDIOTUNE_CTL_t;


/* -------------------------------------------------*/
/*                 System Registers                 */
/* -------------------------------------------------*/
typedef struct
{
    volatile REG_SOCCLK_CTL_t         ClockCTRL;                       /* Offset 0x00 */
    volatile REG_BUSCLK_DIV_t         BusClockDIV;                     /* Offset 0x04 */ 
    volatile REG_BLOCKCLK_SEL_t       ClockSEL0;                       /* Offset 0x08 */
    volatile REG_AUDIOCLK_SEL_t       ClockSEL1;                       /* Offset 0x0C */
    volatile REG_BLOCKCLK_DIV0_t      BlockClockDIV0;                  /* Offset 0x10 */ 
    volatile REG_BLOCKCLK_DIV1_t      BlockClockDIV1;                  /* Offset 0x14 */ 
    volatile REG_BLOCKCLK_DIV2_t      BlockClockDIV2;                  /* Offset 0x18 */
    volatile REG_AUDIOCLK_DIV_t       AudioClockDIV;                   /* Offset 0x1C */ 
                                                                     
    volatile REG_CLK_EN0_t            ClockEnable0;                    /* Offset 0x20 */
    volatile REG_CLK_EN1_t            ClockEnable1;                    /* Offset 0x24 */
    volatile REG_CLK_EN2_t            ClockEnable2;                    /* Offset 0x28 */
    volatile REG_CLK_EN3_t            ClockEnable3;                    /* Offset 0x2C */
    volatile REG_CLK_EN4_t            ClockEnable4;                    /* Offset 0x30 */ 
    volatile REG_CLK_EN5_t            ClockEnable5;                    /* Offset 0x34 */ 
    volatile REG_CLK_EN6_t            ClockEnable6;                    /* Offset 0x38 */   
    volatile REG_CLK_EN7_t            ClockEnable7;                    /* Offset 0x3C */      
    volatile REG_CLK_EN8_t            ClockEnable8;                    /* Offset 0x40 */  
    volatile REG_CLK_EN9_t            ClockEnable9;                    /* Offset 0x44 */
                                                                     
    volatile REG_RESET0_t             RegReset0;                       /* Offset 0x48 */
    volatile REG_RESET1_t             RegReset1;                       /* Offset 0x4C */    
    volatile REG_RESET2_t             RegReset2;                       /* Offset 0x50 */ 
    volatile REG_RESET3_t             RegReset3;                       /* Offset 0x54 */ 
    volatile REG_RESET4_t             RegReset4;                       /* Offset 0x58 */ 
    volatile REG_RESET5_t             RegReset5;                       /* Offset 0x5C */ 
    volatile REG_RESET6_t             RegReset6;                       /* Offset 0x60 */ 
    volatile REG_RESET7_t             RegReset7;                       /* Offset 0x64 */
    volatile REG_RESET8_t             RegReset8;                       /* Offset 0x68 */ 
    volatile REG_RESET9_t             RegReset9;                       /* Offset 0x6C */
                                                                     
    volatile REG_DSPCLK_DIV           DSPClockDIV;                     /* Offset 0x70 */
    volatile REG_DSPCLK_EN_t          DSPClockEnable;                  /* Offset 0x74 */ 
    volatile REG_DSPRESET_t           DSPRegReset;                     /* Offset 0x78 */     
    volatile uint32_t                 rsv_0[1];                      
         
    volatile uint32_t                 PortA_WakeupEN;                  /* Offset 0x80 */
    volatile uint32_t                 PortB_WakeupEN;                  /* Offset 0x84 */
    volatile uint32_t                 PortC_WakeupEN;                  /* Offset 0x88 */
    volatile uint32_t                 PortD_WakeupEN;                  /* Offset 0x8C */
    volatile uint32_t                 PortE_WakeupEN;                  /* Offset 0x90 */     
    volatile uint32_t                 rsv_1[3];        
         
    volatile uint32_t                 PortA_PullEN;                    /* Offset 0xA0 */
    volatile uint32_t                 PortB_PullEN;                    /* Offset 0xA4 */
    volatile uint32_t                 PortC_PullEN;                    /* Offset 0xA8 */
    volatile uint32_t                 PortD_PullEN;                    /* Offset 0xAC */
    volatile uint32_t                 PortE_PullEN;                    /* Offset 0xB0 */    
    volatile uint32_t                 rsv_2[3];                       
         
    volatile uint32_t                 PortA_PullSelect;                /* Offset 0xC0 */
    volatile uint32_t                 PortB_PullSelect;                /* Offset 0xC4 */
    volatile uint32_t                 PortC_PullSelect;                /* Offset 0xC8 */
    volatile uint32_t                 PortD_PullSelect;                /* Offset 0xCC */
    volatile uint32_t                 PortE_PullSelect;                /* Offset 0xD0 */
    volatile uint32_t                 rsv_3[3];

    volatile uint32_t                 PortA_InputOpenCircuit;          /* Offset 0xE0 */
    volatile uint32_t                 PortB_InputOpenCircuit;          /* Offset 0xE4 */
    volatile uint32_t                 PortC_InputOpenCircuit;          /* Offset 0xE8 */
    volatile uint32_t                 PortD_InputOpenCircuit;          /* Offset 0xEC */
    volatile uint32_t                 PortE_InputOpenCircuit;          /* Offset 0xF0 */  
    volatile uint32_t                 rsv_4[3];                          
                                                                       
    volatile uint32_t                 PortA_DriveCfg;                  /* Offset 0x100 */
    volatile uint32_t                 PortB_DriveCfg;                  /* Offset 0x104 */
    volatile uint32_t                 PortC_DriveCfg;                  /* Offset 0x108 */
    volatile uint32_t                 PortD_DriveCfg;                  /* Offset 0x10C */
    volatile uint32_t                 PortE_DriveCfg;                  /* Offset 0x110 */    
    volatile uint32_t                 rsv_5[3];                        
                                                                       
    volatile uint32_t                 PortA_L_FuncMux;                 /* Offset 0x120 */
    volatile uint32_t                 PortA_H_FuncMux;                 /* Offset 0x124 */
    volatile uint32_t                 PortB_L_FuncMux;                 /* Offset 0x128 */
    volatile uint32_t                 PortB_H_FuncMux;                 /* Offset 0x12C */
    volatile uint32_t                 PortC_L_FuncMux;                 /* Offset 0x130 */
    volatile uint32_t                 PortC_H_FuncMux;                 /* Offset 0x134 */
    volatile uint32_t                 PortD_L_FuncMux;                 /* Offset 0x138 */
    volatile uint32_t                 PortD_H_FuncMux;                 /* Offset 0x13C */
    volatile uint32_t                 PortE_L_FuncMux;                 /* Offset 0x140 */
    volatile uint32_t                 PortE_H_FuncMux;                 /* Offset 0x144 */    
    volatile uint32_t                 rsv_6[6];                        
                                                                       
    volatile uint32_t                 PortA_AF_Status_EN;              /* Offset 0x160 */
    volatile uint32_t                 PortB_AF_Status_EN;              /* Offset 0x164 */
    volatile uint32_t                 PortC_AF_Status_EN;              /* Offset 0x168 */
    volatile uint32_t                 PortD_AF_Status_EN;              /* Offset 0x16C */
    volatile uint32_t                 PortE_AF_Status_EN;              /* Offset 0x170 */    
    volatile uint32_t                 rsv_7[3];                        
                                                                       
    volatile REG_QSPI_PAD_CFG_t       QspiPadConfig;                   /* Offset 0x180 */
    volatile REG_OSPI_PAD_CFG_t       OspiPadConfig;                   /* Offset 0x198 */
    volatile uint32_t                 QspiData;                        /* Offset 0x1B0 */
    volatile uint32_t                 QspiOutEN;                       /* Offset 0x1B4 */
    volatile uint32_t                 OspiData;                        /* Offset 0x1B8 */
    volatile uint32_t                 OspiOutEN;                       /* Offset 0x1BC */
                                                                       
    volatile REG_DSP_CTL_t            DSPCTRL;                         /* Offset 0x1C0 */
    volatile REG_DSPVET_CFG_T         DSPVectorConfig;                 /* Offset 0x1C4 */
    volatile uint32_t                 rsv_8[2];                        
                                                                       
    volatile REG_SDIOH_MISC_t         SDIOH_Misc;                      /* Offset 0x1D0 */
    volatile REG_MSPI_DATA_SWAP_t     MSPI_Swap;                       /* Offset 0x1D4 */
    volatile uint32_t                 MCAN_EXT_TS;                     /* Offset 0x1D8 */
                                                                       
    volatile REG_USB_MISC_t           USB_Misc;                        /* Offset 0x1DC */
    volatile uint32_t                 rsv_9[5];     
    volatile uint32_t                 Ospi_Misc;                       /* Offset 0x1F4 */
    volatile uint32_t                 rsv_10[2];     
     
    volatile REG_DMAC0_ENDIAN_CFG_t   Dmac0EndianConfig;               /* Offset 0x200 */
    volatile REG_DMAC1_ENDIAN_CFG_t   Dmac1EndianConfig;               /* Offset 0x204 */
    volatile uint32_t                 rsv_11[6]; 
    
    volatile uint32_t                 I2S_TuneClock_Gate;              /* Offset 0x220 */  
    volatile uint32_t                 PSD_DAC_TuneClock_Gate;          /* Offset 0x224 */ 
    volatile uint32_t                 SARADC_TuneClock_Gate;           /* Offset 0x228 */ 
    volatile uint32_t                 PDM0_TuneClock_Gate;             /* Offset 0x22C */ 
    volatile uint32_t                 PDM1_TuneClock_Gate;             /* Offset 0x230 */
    volatile uint32_t                 SPDIF_TuneClock_Gate;            /* Offset 0x234 */    
    volatile REG_AUDIOTUNE_CTL_t      AudioTuneCTRL;                   /* Offset 0x238 */ 
    volatile uint32_t                 rsv_12[1];  
    
    volatile uint32_t                 SPLLConfig0;                     /* Offset 0x240 */
    volatile uint32_t                 SPLLConfig1;                     /* Offset 0x244 */
    volatile uint32_t                 SPLLConfig2;                     /* Offset 0x248 */
    volatile REG_ANALOG_CFG3_t        SPLLConfig3;                     /* Offset 0x24C */
    volatile uint32_t                 AUPLLConfig0;                    /* Offset 0x250 */
    volatile uint32_t                 AUPLLConfig1;                    /* Offset 0x254 */
    volatile uint32_t                 AUPLLConfig2;                    /* Offset 0x258 */
    volatile REG_ANALOG_CFG3_t        AUPLLConfig3;                    /* Offset 0x25C */
    volatile uint32_t                 rsv_13;     
    volatile uint32_t                 AUPLLConfig4;                    /* Offset 0x264 */
    volatile uint32_t                 rsv_14[5];
     
    volatile uint32_t                 MISC_IO_Config;                  /* Offset 0x27C */ 
    volatile uint32_t                 MISC_Clock0;                     /* Offset 0x280 */ 
    volatile uint32_t                 MISC_Clock1;                     /* Offset 0x284 */ 
    volatile uint32_t                 MISC_Clock2;                     /* Offset 0x288 */ 
    volatile uint32_t                 MISC_Clock3;                     /* Offset 0x28C */
    volatile uint32_t                 MISC_Clock4;                     /* Offset 0x290 */
    volatile uint32_t                 MISC_Clock5;                     /* Offset 0x294 */ 
    volatile uint32_t                 rsv_15[10];             
     
    volatile uint32_t                 DmacHsCfg[16];                   /* Offset 0x2C0 */

    volatile uint32_t                 PortA_Reference_Status;          /* Offset 0x300 */  
    volatile uint32_t                 PortB_Reference_Status;          /* Offset 0x304 */
    volatile uint32_t                 PortC_Reference_Status;          /* Offset 0x308 */
    volatile uint32_t                 PortD_Reference_Status;          /* Offset 0x30C */  
    volatile uint32_t                 PortE_Reference_Status;          /* Offset 0x310 */   
    volatile uint32_t                 rsv_16[0x0C];
}struct_System_t;

#define SYSTEM                 ((struct_System_t *)SYSTEM_REG_BASE)

#define FREE_COUNTER_VALUE     (*(volatile uint32_t *)(FREE_COUNTER_BASE + 0x04))

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup System_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization Config Section Start ################################ */

/* DMA0/1 request source */
typedef enum
{
    SPIMX8_0_RX,        /* 0 */
    SPIMX8_0_TX,        /* 1 */
    SPIMX8_1_RX,        /* 2 */
    SPIMX8_1_TX,        /* 3 */

    SPIM0_RX,           /* 4 */
    SPIM0_TX,           /* 5 */
    SPIM1_RX,           /* 6 */
    SPIM1_TX,           /* 7 */

    rsv_0,              /* 8 */
    rsv_1,              /* 9 */
    SPISRX,             /* 10 */
    SPISTX,             /* 11 */
    
    SPISX4_RX,          /* 12 */
    SPISX4_TX,          /* 13 */
    UART0_RX,           /* 14 */
    UART0_TX,           /* 15 */

    UART1_RX,           /* 16 */
    UART1_TX,           /* 17 */
    UART2_RX,           /* 18 */
    UART2_TX,           /* 19 */

    UART3_RX,           /* 20 */
    UART3_TX,           /* 21 */
    UART4_RX,           /* 22 */
    UART4_TX,           /* 23 */

    UART5_RX,           /* 24 */
    UART5_TX,           /* 25 */   
    rsv_2,              /* 26 */
    rsv_3,              /* 27 */
    
    rsv_4,              /* 28 */
    rsv_5,              /* 29 */
    SPDIF_TRANS,        /* 30 */
    DISPLAY_TRANS,      /* 31 */

    I2S0_RX_LEFT,       /* 32 */
    I2S0_TX_LEFT,       /* 33 */
    I2S0_RX_RIGTH,      /* 34 */
    I2S0_TX_RIGTH,      /* 35 */

    I2S1_RX_LEFT,       /* 36 */
    I2S1_TX_LEFT,       /* 37 */
    I2S1_RX_RIGTH,      /* 38 */
    I2S1_TX_RIGTH,      /* 39 */
    
    rsv_6,              /* 40 */
    rsv_7,              /* 41 */
    rsv_8,              /* 42 */
    rsv_9,              /* 43 */

    PDM0_RX,            /* 44 */
    PDM1_RX,            /* 45 */
    rsv_10,             /* 46 */
    PSD_DAC_WRITE_LEFT, /* 47 */

    rsv_11,             /* 48 */
    PSD_DAC_WRITE_RIGHT,/* 49 */
    rsv_12,             /* 50 */
    rsv_13,             /* 51 */

    rsv_14,             /* 52 */
    rsv_15,             /* 53 */
    rsv_16,             /* 54 */
    rsv_17,             /* 55 */

    rsv_18,             /* 56 */
    YUV2RGB_IN,         /* 57 */
    YUV2RGB_OUT,        /* 58 */
    SARADC_REQUEST,     /* 59 */
}dmac_request_source_t;

/* DMA0/1 request ID */
typedef enum
{
    /* following ids are used for DMA0 */
    DMA0_REQUEST_ID_1 = 1,
    DMA0_REQUEST_ID_2,
    DMA0_REQUEST_ID_3,
    DMA0_REQUEST_ID_4,
    DMA0_REQUEST_ID_5,
    DMA0_REQUEST_ID_6,
    DMA0_REQUEST_ID_7,
    DMA0_REQUEST_ID_8,
    DMA0_REQUEST_ID_9,
    DMA0_REQUEST_ID_10,
    DMA0_REQUEST_ID_11,
    DMA0_REQUEST_ID_12,
    DMA0_REQUEST_ID_13,
    DMA0_REQUEST_ID_14,
    DMA0_REQUEST_ID_15,
    /* following ids are used for DMA1 */
    DMA1_REQUEST_ID_1 = 17,
    DMA1_REQUEST_ID_2,
    DMA1_REQUEST_ID_3,
    DMA1_REQUEST_ID_4,
    DMA1_REQUEST_ID_5,
    DMA1_REQUEST_ID_6,
    DMA1_REQUEST_ID_7,
    DMA1_REQUEST_ID_8,
    DMA1_REQUEST_ID_9,
    DMA1_REQUEST_ID_10,
    DMA1_REQUEST_ID_11,
    DMA1_REQUEST_ID_12,
    DMA1_REQUEST_ID_13,
    DMA1_REQUEST_ID_14,
    DMA1_REQUEST_ID_15,
}dmac_request_id_t;

/* DMA0/1 request ID */
typedef enum
{
    PER_CLK_UARTx,           // Uart0/Uart1/Uart2/Uart3/Uart4/Uart5
    PER_CLK_GPIOx,           // GPIOA/GPIOB/GPIOC/GPIOD/GPIOE
    PER_CLK_I2Cx,            // I2C0/I2C1/I2C2/I2C3/I2C4/I2C5
    PER_CLK_I2Sx,
    PER_CLK_TIMER01,         // Timer0/Timer1
    PER_CLK_TIMER23,         // Timer2/Timer3
    PER_CLK_TIMER45,    
    PER_CLK_SPIMx,           
    PER_CLK_SPIS,
    PER_CLK_SPIMX8_0,
    PER_CLK_SPIMX8_1,
    PER_CLK_PWM,  
    PER_CLK_PDM0,
    PER_CLK_PDM1,
    PER_CLK_DISPLAY,
    PER_CLK_QSPI0,
    PER_CLK_QSPI1,
    PER_CLK_OSPI,  
    PER_CLK_SDIOH0,
    PER_CLK_CANx,            // CAN0/CAN1/CAN2/CAN3
    PER_CLK_SPDIF, 
}per_clock_index_t;

/* xip flash clock source selection */
typedef enum
{
    XIP_CLK_SEL_COREH,
    XIP_CLK_SEL_SPLL,
    XIP_CLK_SEL_AUPLL,
}xip_clk_src_t;

#define PLL_POWER_DISABLE         (0)
#define PLL_POWER_ENABLE          (1)

/* MCU_CLOCK_SELECT */
#define MCU_CLK_SEL_CORE_HSCLK    (0)
#define MCU_CLK_SEL_SPLL_CLK      (1)

#define CORE_HSCLK_SEL_HES        (0)    /* CORE_HSCLK source select HES(External High Speed oscillator) */
#define CORE_HSCLK_SEL_HIS        (1)    /* CORE_HSCLK source select HIS(Internal High Speed oscillator) */

#define SYSTEM_PREVENT_SLEEP_TYPE_DISABLE       0x00000001
#define SYSTEM_PREVENT_SLEEP_TYPE_CALIBRATION   0x00000002
#define SYSTEM_PREVENT_SLEEP_TYPE_DSP           0x00000004
#define SYSTEM_PREVENT_SLEEP_TYPE_HCI_RX        0x00000008
#define SYSTEM_PREVENT_SLEEP_TYPE_HCI_TX        0x00000010
#define SYSTEM_PREVENT_SLEEP_SCO_ONGOING        0x00000020
#define SYSTEM_PREVENT_SLEEP_A2DP_ONGOING       0x00000040
#define SYSTEM_PREVENT_SLEEP_DISPLAY_ONGOING    0x00000080

/**
  * @brief  system clock config.
  */
typedef struct
{
    uint32_t CORE_HSCLK_Source;
}System_CORE_HSCLKConfig_t;

/**
  * @brief  PLL config.
  */
typedef struct
{
    uint32_t PowerEn;
    uint32_t PLL_N;
    uint32_t PLL_M;
}System_SPLLConfig_t;

/**
  * @brief  PLL config.
  */
typedef struct
{
    uint32_t PowerEn;
    uint32_t PLL_N;
    uint16_t PLL_K;
    uint16_t PLL_D;
}System_AUPLLConfig_t;

/**
  * @brief  system clock config.
  */
typedef struct
{
    System_CORE_HSCLKConfig_t    CORE_HSCLK_CFG;
    System_SPLLConfig_t          SPLL_CFG;
    System_AUPLLConfig_t         AUPLL_CFG;

    uint32_t MCU_Clock_Source;    /* This parameter can be a value of @ref MCU_CLOCK_SELECT. */

    uint32_t SOC_DIV;     /* This parameter can be a value 1 ~ 16 */
    uint32_t MCU_DIV;     /* This parameter can be a value 1 ~ 16 */

    uint32_t APB0_DIV;    /* This parameter can be a value 1 ~ 4 */
    uint32_t APB1_DIV;    /* This parameter can be a value 1 ~ 4 */
    uint32_t APB2_DIV;    /* This parameter can be a value 1 ~ 4 */
}System_ClkConfig_t;

/**
  * @brief  system XIP flash config.
  */
typedef struct
{
    xip_clk_src_t           CLK_SRC_SEL;
    enum flash_rd_type_t    RD_TYPE;
    enum flash_wr_type_t    WR_TYPE;
    enum qspi_baud_rate_t   DIV_SEL;
}System_XIPConfig_t;

/* ################################ Initialization Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* ======================================================================================================= */
/* =============================== SOC Clock Select Enable/Disable ======================================= */
/* ======================================================================================================= */
#define __SYSTEM_MCU_CLK_SELECT_COREH()                (SYSTEM->ClockCTRL.MCU_CLK_SEL = 0)
#define __SYSTEM_MCU_CLK_SELECT_SPLL()                 (SYSTEM->ClockCTRL.MCU_CLK_SEL = 1)

#define __SYSTEM_CORE_HIGH_CLK_SELECT_OSC()            (SYSTEM->ClockCTRL.CORE_HSCK_SEL = 0)
#define __SYSTEM_CORE_HIGH_CLK_SELECT_RC()             (SYSTEM->ClockCTRL.CORE_HSCK_SEL = 1)

#define __SYSTEM_SOC_CLK_DIV(__CLKDIV__)               (SYSTEM->ClockCTRL.SOC_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_SPLL_CLK_ENABLE()                     (SYSTEM->ClockCTRL.SPLL_EN  = 1)
#define __SYSTEM_APLL_CLK_ENABLE()                     (SYSTEM->ClockCTRL.AUPLL_EN = 1)

#define __SYSTEM_SPLL_CLK_DIV2_ENABLE()                (SYSTEM->ClockCTRL.SPLL_CLK_DIV2_EN = 1)
#define __SYSTEM_APLL_CLK_DIV2_ENABLE()                (SYSTEM->ClockCTRL.AUPLL_DIV2_EN    = 1)

#define __SYSTEM_SOC_FCLK_ENABLE()                     (SYSTEM->ClockCTRL.SOC_FCLK_EN = 1)

/* ======================================================================================================= */
/* =============================== Bus Clock Select Enable/Disable/Reset ================================= */
/* ======================================================================================================= */
#define __SYSTEM_APB0_CLK_RATIO(__RATIO__)             (SYSTEM->BusClockDIV.APB0_RATIO  = __RATIO__ - 1)
#define __SYSTEM_APB1_CLK_RATIO(__RATIO__)             (SYSTEM->BusClockDIV.APB1_RATIO  = __RATIO__ - 1)
#define __SYSTEM_APB2_CLK_RATIO(__RATIO__)             (SYSTEM->BusClockDIV.APB2_RATIO  = __RATIO__ - 1)
#define __SYSTEM_MCU_CLK_DIV(__CLKDIV__)               (SYSTEM->BusClockDIV.MCU_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_BOOT_ROM_CLK_ENABLE()                 (SYSTEM->ClockEnable0.BOOT_ROM_CLKEN= 1)
#define __SYSTEM_SRAM0_CLK_ENABLE()                    (SYSTEM->ClockEnable0.SRAM0_CLKEN = 1)
#define __SYSTEM_SRAM1_CLK_ENABLE()                    (SYSTEM->ClockEnable0.SRAM1_CLKEN = 1)
#define __SYSTEM_SRAM2_CLK_ENABLE()                    (SYSTEM->ClockEnable0.SRAM2_CLKEN = 1)
#define __SYSTEM_CRAM0_CLK_ENABLE()                    (SYSTEM->ClockEnable0.CRAM0_CLKEN = 1)
#define __SYSTEM_CRAM1_CLK_ENABLE()                    (SYSTEM->ClockEnable0.CRAM1_CLKEN = 1)
#define __SYSTEM_APB0_CLK_ENABLE()                     (SYSTEM->ClockEnable0.APB0_CLKEN = 1)
#define __SYSTEM_APB1_CLK_ENABLE()                     (SYSTEM->ClockEnable0.APB1_CLKEN = 1)
#define __SYSTEM_APB2_CLK_ENABLE()                     (SYSTEM->ClockEnable0.APB2_CLKEN = 1)
#define __SYSTEM_APB_CLK_ENABLE()                      (SYSTEM->ClockEnable0.APB_CLKEN  = 1)
#define __SYSTEM_BUS_CLK_ENABLE()                      (SYSTEM->ClockEnable0.SYS_BUS_CLKEN = 1)
#define __SYSTEM_CODE_BUS_CLK_ENABLE()                 (SYSTEM->ClockEnable0.CODE_BUS_CLKEN = 1)
#define __SYSTEM_CPU_MAS_CLK_ENABLE()                  (SYSTEM->ClockEnable0.CM33_MAS_CLKEN = 1)

#define __SYSTEM_LIBRARY_ROM_CLK_DISABLE()             (SYSTEM->ClockEnable0.LIB_ROM_CLKEN = 0)
#define __SYSTEM_SRAM0_CLK_DISABLE()                   (SYSTEM->ClockEnable0.SRAM0_CLKEN = 0)
#define __SYSTEM_SRAM1_CLK_DISABLE()                   (SYSTEM->ClockEnable0.SRAM1_CLKEN = 0)
#define __SYSTEM_SRAM2_CLK_DISABLE()                   (SYSTEM->ClockEnable0.SRAM2_CLKEN = 0)
#define __SYSTEM_CRAM0_CLK_DISABLE()                   (SYSTEM->ClockEnable0.CRAM0_CLKEN = 0)
#define __SYSTEM_CRAM1_CLK_DISABLE()                   (SYSTEM->ClockEnable0.CRAM1_CLKEN = 0)
#define __SYSTEM_APB0_CLK_DISABLE()                    (SYSTEM->ClockEnable0.APB0_CLKEN = 0)
#define __SYSTEM_APB1_CLK_DISABLE()                    (SYSTEM->ClockEnable0.APB1_CLKEN = 0)
#define __SYSTEM_APB2_CLK_DISABLE()                    (SYSTEM->ClockEnable0.APB2_CLKEN = 0)
#define __SYSTEM_APB_CLK_DISABLE()                     (SYSTEM->ClockEnable0.APB_CLKEN  = 0)
#define __SYSTEM_BUS_CLK_DISABLE()                     (SYSTEM->ClockEnable0.SYS_BUS_CLKEN = 0)
#define __SYSTEM_CODE_BUS_CLK_DISABLE()                (SYSTEM->ClockEnable0.CODE_BUS_CLKEN = 0)
#define __SYSTEM_CM33_MAS_CLK_DISABLE()                (SYSTEM->ClockEnable0.CM33_MAS_CLKEN = 0)

#define __SYSTEM_APB0_RESET()                          (SYSTEM->RegReset0.APB0_SFT_RST = 1)
#define __SYSTEM_APB1_RESET()                          (SYSTEM->RegReset0.APB1_SFT_RST = 1)
#define __SYSTEM_APB2_RESET()                          (SYSTEM->RegReset0.APB2_SFT_RST = 1)
#define __SYSTEM_APB_RESET()                           (SYSTEM->RegReset0.APB_SFT_RST  = 1)
#define __SYSTEM_APB0_RESET()                          (SYSTEM->RegReset0.APB0_SFT_RST = 1)
#define __SYSTEM_CM33_MAS_RESET()                      (SYSTEM->RegReset0.CM33_MAS_SFT_RST = 1)

/* ======================================================================================================= */
/* =============================== COUNTER Clock Enable/Disable/Reset ==================================== */
/* ======================================================================================================= */
#define __SYSTEM_FREE_COUNTER_CLK_ENABLE()             (SYSTEM->ClockEnable9.COUNTER_CLKEN = 1)
#define __SYSTEM_FREE_COUNTER_CLK_DISABLE()            (SYSTEM->ClockEnable9.COUNTER_CLKEN = 0)

#define __SYSTEM_COUNTER_RESET()                       (SYSTEM->RegReset9.COUNTER_SFT_RST  = 1)


/* ======================================================================================================= */
/* =============================== AHBC Clock Enable/Disable/Reset ======================================= */
/* ======================================================================================================= */
#define __SYSTEM_AHBC_CLK_ENABLE()                    (SYSTEM->ClockEnable1.AHBC_CLKEN = 1)
#define __SYSTEM_AHBC_CLK_DISABLE()                   (SYSTEM->ClockEnable1.AHBC_CLKEN = 0)

#define __SYSTEM_AHBC_RESET()                         (SYSTEM->RegReset1.AHBC_SFT_RST  = 1)
  
/* ======================================================================================================= */
/* =============================== PFC Clock Enable/Disable/Reset ======================================== */
/* ======================================================================================================= */
#define __SYSTEM_PFC_CLK_ENABLE()                     (SYSTEM->ClockEnable1.PFC_CLKEN = 1)
#define __SYSTEM_PFC_CLK_DISABLE()                    (SYSTEM->ClockEnable1.PFC_CLKEN = 0)

#define __SYSTEM_PFC_RESET()                          (SYSTEM->RegReset1.PFC_SFT_RST  = 1)

/* ======================================================================================================= */
/* =============================== CRC Clock Enable/Disable/Reset ======================================== */
/* ======================================================================================================= */
#define __SYSTEM_CRC_CLK_ENABLE()                     (SYSTEM->ClockEnable7.CRC_CLKEN = 1)
#define __SYSTEM_CRC_CLK_DISABLE()                    (SYSTEM->ClockEnable7.CRC_CLKEN = 0)

#define __SYSTEM_CRC_RESET()                          (SYSTEM->RegReset7.CRC_SFT_RST  = 1)

/* ======================================================================================================= */
/* =============================== TRNG Clock Enable/Disable ============================================= */
/* ======================================================================================================= */
#define __SYSTEM_TRNG_CLK_ENABLE()                      (SYSTEM->ClockEnable7.TRNG_CLKEN = 1)
#define __SYSTEM_TRNG_CLK_DISABLE()                     (SYSTEM->ClockEnable7.TRNG_CLKEN = 0)

#define __SYSTEM_TRNG_RESET()                           (SYSTEM->RegReset7.TRNG_SFT_RST  = 1)

/* ======================================================================================================= */
/* =============================== AES Clock Select/Enable/Disable ======================================= */
/* ======================================================================================================= */
#define __SYSTEM_AES_CLK_SELECT_COREH()                 (SYSTEM->ClockSEL1.AES_CLK_SEL = 0)
#define __SYSTEM_AES_CLK_SELECT_SPLL()                  (SYSTEM->ClockSEL0.MCAN_CLK_SEL = 1)

#define __SYSTEM_AES_CLK_ENABLE()                       (SYSTEM->ClockEnable7.AES_CLKEN = 1)
#define __SYSTEM_AES_CLK_DISABLE()                      (SYSTEM->ClockEnable7.AES_CLKEN = 0)

#define __SYSTEM_AES_RESET()                            (SYSTEM->RegReset7.AES_SFT_RST  = 1)

/* ======================================================================================================= */
/* =============================== ADC Clock Enable/Disable ============================================== */
/* ======================================================================================================= */
#define __SYSTEM_ADC_CLK_ENABLE()                       (SYSTEM->ClockEnable9.ADC_CLKEN = 1)
#define __SYSTEM_ADC_CLK_DISABLE()                      (SYSTEM->ClockEnable9.ADC_CLKEN = 0)

#define __SYSTEM_ADC_RESET()                            (SYSTEM->RegReset9.ADC_SFT_RST  = 1)

/* ======================================================================================================= */
/* =============================== CALI Clock Enable/Disable ============================================= */
/* ======================================================================================================= */
#define __SYSTEM_CALI_CLK_ENABLE()                      (SYSTEM->ClockEnable9.CALI_CLKEN = 1)
#define __SYSTEM_CALI_CLK_DISABLE()                     (SYSTEM->ClockEnable9.CALI_CLKEN = 0)

#define __SYSTEM_CALI_RESET()                           (SYSTEM->RegReset9.CALI_SFT_RST  = 1)

/* ======================================================================================================= */
/* =============================== APP_IPC Clock Enable/Disable ========================================== */
/* ======================================================================================================= */
#define __SYSTEM_APP_IPC_CLK_ENABLE()                   (SYSTEM->ClockEnable9.APP_IPC_CLKEN = 1)
#define __SYSTEM_APP_IPC_CLK_DISABLE()                  (SYSTEM->ClockEnable9.APP_IPC_CLKEN = 0)

#define __SYSTEM_APP_IPC_RESET()                        (SYSTEM->RegReset9.APP_IPC_SFT_RST  = 1)

/* ======================================================================================================= */
/* =============================== TICK Clock Enable/Disable ============================================= */
/* ======================================================================================================= */
#define __SYSTEM_TICK_CLK_DIV(__CLKDIV__)               (SYSTEM->BusClockDIV.MCU_ST_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_TICK_CLK_ENABLE()                      (SYSTEM->ClockEnable9.TICK_CLKEN = 1)
#define __SYSTEM_TICK_CLK_DISABLE()                     (SYSTEM->ClockEnable9.TICK_CLKEN = 0)

#define __SYSTEM_TICK_RESET()                           (SYSTEM->RegReset9.TICK_SFT_RST  = 1)

/* ======================================================================================================= */
/* =============================== CAN Clock Select/Enable/Disable/Reset ================================= */
/* ======================================================================================================= */
#define __SYSTEM_MCAN_CLK_SELECT_COREH()                (SYSTEM->ClockSEL0.MCAN_CLK_SEL = 0)
#define __SYSTEM_MCAN_CLK_SELECT_SPLL()                 (SYSTEM->ClockSEL0.MCAN_CLK_SEL = 1)
#define __SYSTEM_MCAN_CLK_SELECT_AUPLL()                (SYSTEM->ClockSEL0.MCAN_CLK_SEL = 2)
#define __SYSTEM_MCAN_CLK_SELECT_D48M()                 (SYSTEM->ClockSEL0.MCAN_CLK_SEL = 3)

#define __SYSTEM_MCAN_CLK_DIV(__CLKDIV__)               (SYSTEM->BlockClockDIV2.MCAN_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_MCAN0_CLK_ENABLE()                     (SYSTEM->ClockEnable2.MCAN0_CLKEN = 1)
#define __SYSTEM_MCAN1_CLK_ENABLE()                     (SYSTEM->ClockEnable2.MCAN1_CLKEN = 1)
#define __SYSTEM_MCAN2_CLK_ENABLE()                     (SYSTEM->ClockEnable2.MCAN2_CLKEN = 1)
#define __SYSTEM_MCAN3_CLK_ENABLE()                     (SYSTEM->ClockEnable2.MCAN3_CLKEN = 1)

#define __SYSTEM_MCAN0_CLK_DISABLE()                    (SYSTEM->ClockEnable2.MCAN0_CLKEN = 0)
#define __SYSTEM_MCAN1_CLK_DISABLE()                    (SYSTEM->ClockEnable2.MCAN1_CLKEN = 0)
#define __SYSTEM_MCAN2_CLK_DISABLE()                    (SYSTEM->ClockEnable2.MCAN2_CLKEN = 0)
#define __SYSTEM_MCAN3_CLK_DISABLE()                    (SYSTEM->ClockEnable2.MCAN3_CLKEN = 0)

#define __SYSTEM_MCAN0_RESET()                          (SYSTEM->RegReset2.MCAN0_SFT_RST = 1)
#define __SYSTEM_MCAN1_RESET()                          (SYSTEM->RegReset2.MCAN1_SFT_RST = 1)
#define __SYSTEM_MCAN2_RESET()                          (SYSTEM->RegReset2.MCAN2_SFT_RST = 1)
#define __SYSTEM_MCAN3_RESET()                          (SYSTEM->RegReset2.MCAN3_SFT_RST = 1)

/* ======================================================================================================= */
/* =============================== SDIO Clock Select/Enable/Disable/Reset ================================ */
/* ======================================================================================================= */
#define __SYSTEM_SDIOH0_CLK_SELECT_COREH()              (SYSTEM->ClockSEL0.SDIOH0_CLK_SEL = 0)
#define __SYSTEM_SDIOH0_CLK_SELECT_SPLL()               (SYSTEM->ClockSEL0.SDIOH0_CLK_SEL = 1)
#define __SYSTEM_SDIOH0_CLK_SELECT_AUPLL()              (SYSTEM->ClockSEL0.SDIOH0_CLK_SEL = 2)
#define __SYSTEM_SDIOH0_CLK_SELECT_D48M()               (SYSTEM->ClockSEL0.SDIOH0_CLK_SEL = 3)

#define __SYSTEM_SDIOH0_CLK_DIV(__CLKDIV__)             (SYSTEM->BlockClockDIV0.SDIOH0_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_SDIOH0_CLK_ENABLE()                    (SYSTEM->ClockEnable2.SDIOH0_CLKEN = 1)
#define __SYSTEM_SDIOH0_CLK_DISABLE()                   (SYSTEM->ClockEnable2.SDIOH0_CLKEN = 0)

#define __SYSTEM_SDIOH0_RESET()                         (SYSTEM->RegReset2.SDIOH0_SFT_RST = 1)

#define __SYSTEM_SDIOH0_DAT_SWAP_ENABLE()               (SYSTEM->SDIOH_Misc.SDIOH0_DAT_SWAP = 1)
#define __SYSTEM_SDIOH0_DAT_SWAP_DISABLE()              (SYSTEM->SDIOH_Misc.SDIOH0_DAT_SWAP = 0)

/* ======================================================================================================= */
/* =============================== Timer Clock Select/Enable/Disable/Reset =============================== */
/* ======================================================================================================= */
#define __SYSTEM_TIMER0_CLK_ENABLE()                    (SYSTEM->ClockEnable3.TIMER0_CLKEN = 1)
#define __SYSTEM_TIMER1_CLK_ENABLE()                    (SYSTEM->ClockEnable3.TIMER1_CLKEN = 1)
#define __SYSTEM_TIMER2_CLK_ENABLE()                    (SYSTEM->ClockEnable3.TIMER2_CLKEN = 1)
#define __SYSTEM_TIMER3_CLK_ENABLE()                    (SYSTEM->ClockEnable3.TIMER3_CLKEN = 1)
#define __SYSTEM_TIMER4_CLK_ENABLE()                    (SYSTEM->ClockEnable3.TIMER4_CLKEN = 1)
#define __SYSTEM_TIMER5_CLK_ENABLE()                    (SYSTEM->ClockEnable3.TIMER5_CLKEN = 1)

#define __SYSTEM_TIMER0_CLK_DISABLE()                   (SYSTEM->ClockEnable3.TIMER0_CLKEN = 0)
#define __SYSTEM_TIMER1_CLK_DISABLE()                   (SYSTEM->ClockEnable3.TIMER1_CLKEN = 0)
#define __SYSTEM_TIMER2_CLK_DISABLE()                   (SYSTEM->ClockEnable3.TIMER2_CLKEN = 0)
#define __SYSTEM_TIMER3_CLK_DISABLE()                   (SYSTEM->ClockEnable3.TIMER3_CLKEN = 0)
#define __SYSTEM_TIMER4_CLK_DISABLE()                   (SYSTEM->ClockEnable3.TIMER4_CLKEN = 0)
#define __SYSTEM_TIMER5_CLK_DISABLE()                   (SYSTEM->ClockEnable3.TIMER5_CLKEN = 0)

#define __SYSTEM_TIMER01_CLK_DIV(__CLKDIV__)            (SYSTEM->BlockClockDIV2.TIMER01_CLK_DIV = __CLKDIV__ - 1)
#define __SYSTEM_TIMER23_CLK_DIV(__CLKDIV__)            (SYSTEM->BlockClockDIV2.TIMER23_CLK_DIV = __CLKDIV__ - 1)
#define __SYSTEM_TIMER45_CLK_DIV(__CLKDIV__)            (SYSTEM->AudioClockDIV.TIMER45_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_TIMER0_RESET()                         (SYSTEM->RegReset3.TIMER0_SFT_RST = 1)
#define __SYSTEM_TIMER1_RESET()                         (SYSTEM->RegReset3.TIMER1_SFT_RST = 1)
#define __SYSTEM_TIMER2_RESET()                         (SYSTEM->RegReset3.TIMER2_SFT_RST = 1)
#define __SYSTEM_TIMER3_RESET()                         (SYSTEM->RegReset3.TIMER3_SFT_RST = 1)
#define __SYSTEM_TIMER4_RESET()                         (SYSTEM->RegReset3.TIMER4_SFT_RST = 1)
#define __SYSTEM_TIMER5_RESET()                         (SYSTEM->RegReset3.TIMER5_SFT_RST = 1)

/* ======================================================================================================= */
/* ================================ WDT Clock Select/Enable/Disable/Reset ================================ */
/* ======================================================================================================= */
#define __SYSTEM_WDT_CLK_ENABLE()                       (SYSTEM->ClockEnable3.WDT_CLKEN = 1)
#define __SYSTEM_WDT_CLK_DISABLE()                      (SYSTEM->ClockEnable3.WDT_CLKEN = 0)
#define __SYSTEM_WDT_CLK_DIV(__CLKDIV__)                (SYSTEM->BlockClockDIV2.WDT_CLK_DIV = __CLKDIV__ - 1)
#define __SYSTEM_WDT_RESET()                            (SYSTEM->RegReset3.WDT_SFT_RST = 1)

/* ===================================================================================================== */
/* =============================== QPSI and OSPI Clock Select/Enable/Disable/Reset ===================== */
/* ===================================================================================================== */
#define __SYSTEM_QSPI0_CLK_SELECT_COREH()               (SYSTEM->ClockSEL0.QSPI0_CLK_SEL = 0)
#define __SYSTEM_QSPI0_CLK_SELECT_SPLL()                (SYSTEM->ClockSEL0.QSPI0_CLK_SEL = 1)
#define __SYSTEM_QSPI0_CLK_SELECT_AUPLL()               (SYSTEM->ClockSEL0.QSPI0_CLK_SEL = 2)
#define __SYSTEM_QSPI0_CLK_SELECT_D48M()                (SYSTEM->ClockSEL0.QSPI0_CLK_SEL = 3)

#define __SYSTEM_QSPI1_CLK_SELECT_COREH()               (SYSTEM->ClockSEL0.QSPI1_CLK_SEL = 0)
#define __SYSTEM_QSPI1_CLK_SELECT_SPLL()                (SYSTEM->ClockSEL0.QSPI1_CLK_SEL = 1)
#define __SYSTEM_QSPI1_CLK_SELECT_AUPLL()               (SYSTEM->ClockSEL0.QSPI1_CLK_SEL = 2)
#define __SYSTEM_QSPI1_CLK_SELECT_D48M()                (SYSTEM->ClockSEL0.QSPI1_CLK_SEL = 3)

#define __SYSTEM_OSPI_CLK_SELECT_COREH()                (SYSTEM->ClockSEL0.OSPI_CLK_SEL = 0)
#define __SYSTEM_OSPI_CLK_SELECT_SPLL()                 (SYSTEM->ClockSEL0.OSPI_CLK_SEL = 1)
#define __SYSTEM_OSPI_CLK_SELECT_AUPLL()                (SYSTEM->ClockSEL0.OSPI_CLK_SEL = 2)
#define __SYSTEM_OSPI_CLK_SELECT_D48M()                 (SYSTEM->ClockSEL0.OSPI_CLK_SEL = 3)

#define __SYSTEM_QSPI0_CLK_DIV(__CLKDIV__)              (SYSTEM->BlockClockDIV0.QSPI0_CLK_DIV = __CLKDIV__ - 1)
#define __SYSTEM_QSPI1_CLK_DIV(__CLKDIV__)              (SYSTEM->BlockClockDIV0.QSPI1_CLK_DIV = __CLKDIV__ - 1)
#define __SYSTEM_OSPI_CLK_DIV(__CLKDIV__)               (SYSTEM->BlockClockDIV0.OSPI_CLK_DIV = __CLKDIV__ - 1)
 
#define __SYSTEM_QSPI0_CLK_ENABLE()                     do{ SYSTEM->ClockEnable0.QSPI0_P_CLKEN  = 1; \
                                                            SYSTEM->ClockEnable6.QSPI0_CLKEN    = 1; \
                                                            SYSTEM->ClockEnable6.QSPI0_H_CLKEN  = 1;}while(0)

#define __SYSTEM_QSPI1_CLK_ENABLE()                     do{ SYSTEM->ClockEnable0.QSPI1_P_CLKEN  = 1; \
                                                            SYSTEM->ClockEnable6.QSPI1_CLKEN    = 1; \
                                                            SYSTEM->ClockEnable6.QSPI1_H_CLKEN  = 1;}while(0)

#define __SYSTEM_OSPI_CLK_ENABLE()                      do{ SYSTEM->ClockEnable0.OSPI_P_CLKEN  = 1; \
                                                            SYSTEM->ClockEnable6.OSPI_CLKEN    = 1; \
                                                            SYSTEM->ClockEnable6.OSPI_H_CLKEN  = 1;}while(0)

#define __SYSTEM_QSPI0_CLK_DISABLE()                    do{ SYSTEM->ClockEnable0.QSPI0_P_CLKEN = 0; \
                                                            SYSTEM->ClockEnable6.QSPI0_CLKEN   = 0; \
                                                            SYSTEM->ClockEnable6.QSPI0_H_CLKEN = 0;}while(0)

#define __SYSTEM_QSPI1_CLK_DISABLE()                    do{ SYSTEM->ClockEnable0.QSPI1_P_CLKEN  = 0; \
                                                            SYSTEM->ClockEnable6.QSPI1_CLKEN    = 0; \
                                                            SYSTEM->ClockEnable6.QSPI1_H_CLKEN  = 0;}while(0)

#define __SYSTEM_OSPI_CLK_DISABLE()                     do{ SYSTEM->ClockEnable0.OSPI_P_CLKEN  = 0; \
                                                            SYSTEM->ClockEnable6.OSPI_CLKEN    = 0; \
                                                            SYSTEM->ClockEnable6.OSPI_H_CLKEN  = 0;}while(0)
                                          
#define __SYSTEM_QSPI0_RESET()                          do{ SYSTEM->RegReset0.QSPI0_P_SFT_RST   = 1; \
                                                            SYSTEM->RegReset6.QSPI0_SFT_RST     = 1; \
                                                            SYSTEM->RegReset6.QSPI0_REF_SFT_RST = 1;}while(0)

#define __SYSTEM_QSPI1_RESET()                          do{ SYSTEM->RegReset0.QSPI1_P_SFT_RST   = 1; \
                                                            SYSTEM->RegReset6.QSPI1_SFT_RST     = 1; \
                                                            SYSTEM->RegReset6.QSPI1_REF_SFT_RST = 1;}while(0)

#define __SYSTEM_OSPI_RESET()                           do{ SYSTEM->RegReset0.OSPI_P_SFT_RST   = 1; \
                                                            SYSTEM->RegReset6.OSPI_SFT_RST     = 1; \
                                                            SYSTEM->RegReset6.OSPI_REF_SFT_RST = 1;}while(0)

/* ======================================================================================================= */
/* =============================== YUV2RGB Clock Enable/Disable/Reset ==================================== */
/* ======================================================================================================= */
#define __SYSTEM_YUV2RGB_CLK_ENABLE()                   (SYSTEM->ClockEnable7.YUV2RGB_CLKEN = 1)
#define __SYSTEM_YUV2RGB_CLK_DISABLE()                  (SYSTEM->ClockEnable7.YUV2RGB_CLKEN = 0)

#define __SYSTEM_YUV2RGB_RESET()                        (SYSTEM->RegReset7.YUV2RGB_SFT_RST = 1)

/* ===================================================================================================== */
/* =============================== I2C Clock Select/Enable/Disable/Reset =============================== */
/* ===================================================================================================== */
#define __SYSTEM_I2C_CLK_SELECT_COREH()                 (SYSTEM->ClockSEL0.I2C_CLK_SEL = 0)
#define __SYSTEM_I2C_CLK_SELECT_SPLL()                  (SYSTEM->ClockSEL0.I2C_CLK_SEL = 1)
 
#define __SYSTEM_I2C_CLK_DIV(__CLKDIV__)                (SYSTEM->BlockClockDIV1.I2C_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_I2C0_CLK_ENABLE()                      (SYSTEM->ClockEnable5.I2C0_CLKEN = 1)
#define __SYSTEM_I2C1_CLK_ENABLE()                      (SYSTEM->ClockEnable5.I2C1_CLKEN = 1)
#define __SYSTEM_I2C2_CLK_ENABLE()                      (SYSTEM->ClockEnable5.I2C2_CLKEN = 1)
#define __SYSTEM_I2C3_CLK_ENABLE()                      (SYSTEM->ClockEnable5.I2C3_CLKEN = 1)
                                                
#define __SYSTEM_I2C0_CLK_DISABLE()                     (SYSTEM->ClockEnable5.I2C0_CLKEN = 0)
#define __SYSTEM_I2C1_CLK_DISABLE()                     (SYSTEM->ClockEnable5.I2C1_CLKEN = 0)
#define __SYSTEM_I2C2_CLK_DISABLE()                     (SYSTEM->ClockEnable5.I2C2_CLKEN = 0)
#define __SYSTEM_I2C3_CLK_DISABLE()                     (SYSTEM->ClockEnable5.I2C3_CLKEN = 0)
                                                
#define __SYSTEM_I2C0_RESET()                           (SYSTEM->RegReset5.I2C0_SFT_RST = 1)
#define __SYSTEM_I2C1_RESET()                           (SYSTEM->RegReset5.I2C1_SFT_RST = 1)
#define __SYSTEM_I2C2_RESET()                           (SYSTEM->RegReset5.I2C2_SFT_RST = 1)
#define __SYSTEM_I2C3_RESET()                           (SYSTEM->RegReset5.I2C3_SFT_RST = 1)

/* ===================================================================================================== */
/* =============================== SPI Clock Select/Enable/Disable/Reset =============================== */
/* ===================================================================================================== */
#define __SYSTEM_SPI_SLAVE_CLK_SELECT_COREH()           (SYSTEM->ClockSEL0.SSIS_CLK_SEL = 0)
#define __SYSTEM_SPI_SLAVE_CLK_SELECT_SPLL()            (SYSTEM->ClockSEL0.SSIS_CLK_SEL = 1)
#define __SYSTEM_SPI_SLAVE_CLK_SELECT_AUPLL()           (SYSTEM->ClockSEL0.SSIS_CLK_SEL = 2)   
#define __SYSTEM_SPI_SLAVE_CLK_SELECT_D48M()            (SYSTEM->ClockSEL0.SSIS_CLK_SEL = 3)   
                                                
#define __SYSTEM_SPI_MASTER0_X8_CLK_SELECT_COREH()      (SYSTEM->ClockSEL0.MSPI0_CLK_SEL = 0)
#define __SYSTEM_SPI_MASTER0_X8_CLK_SELECT_SPLL()       (SYSTEM->ClockSEL0.MSPI0_CLK_SEL = 1)
#define __SYSTEM_SPI_MASTER0_X8_CLK_SELECT_AUPLL()      (SYSTEM->ClockSEL0.MSPI0_CLK_SEL = 2)
#define __SYSTEM_SPI_MASTER0_X8_CLK_SELECT_D48M()       (SYSTEM->ClockSEL0.MSPI0_CLK_SEL = 3)
                                                    
#define __SYSTEM_SPI_MASTER1_X8_CLK_SELECT_COREH()      (SYSTEM->ClockSEL0.MSPI1_CLK_SEL = 0)
#define __SYSTEM_SPI_MASTER1_X8_CLK_SELECT_SPLL()       (SYSTEM->ClockSEL0.MSPI1_CLK_SEL = 1)
#define __SYSTEM_SPI_MASTER1_X8_CLK_SELECT_AUPLL()      (SYSTEM->ClockSEL0.MSPI1_CLK_SEL = 2) 
#define __SYSTEM_SPI_MASTER1_X8_CLK_SELECT_D48M()       (SYSTEM->ClockSEL0.MSPI1_CLK_SEL = 3)      

#define __SYSTEM_SPI_MASTER_CLK_SELECT_COREH()          (SYSTEM->ClockSEL0.SSIM_CLK_SEL = 0)
#define __SYSTEM_SPI_MASTER_CLK_SELECT_SPLL()           (SYSTEM->ClockSEL0.SSIM_CLK_SEL = 1)

#define __SYSTEM_SPI_SLAVE_CLK_DIV(__CLKDIV__)          (SYSTEM->BlockClockDIV0.SSIS_CLK_DIV  = __CLKDIV__ - 1)
#define __SYSTEM_SPI_MASTER0_X8_CLK_DIV(__CLKDIV__)     (SYSTEM->BlockClockDIV0.MSPI0_CLK_DIV = __CLKDIV__ - 1)
#define __SYSTEM_SPI_MASTER1_X8_CLK_DIV(__CLKDIV__)     (SYSTEM->BlockClockDIV0.MSPI1_CLK_DIV = __CLKDIV__ - 1)
#define __SYSTEM_SPI_MASTER_CLK_DIV(__CLKDIV__)         (SYSTEM->BlockClockDIV1.SSIM_CLK_DIV  = __CLKDIV__ - 1)
                                                
#define __SYSTEM_SPI_SLAVE0_CLK_ENABLE()                (SYSTEM->ClockEnable6.SSIS0_CLKEN = 1)
#define __SYSTEM_SPI_SLAVE1_CLK_ENABLE()                (SYSTEM->ClockEnable6.SSIS1_CLKEN = 1)

#define __SYSTEM_SPI_MASTER0_X8_CLK_ENABLE()            (SYSTEM->ClockEnable6.MSPI0_CLKEN = 1)
#define __SYSTEM_SPI_MASTER1_X8_CLK_ENABLE()            (SYSTEM->ClockEnable6.MSPI1_CLKEN = 1)
  
#define __SYSTEM_SPI_MASTER0_CLK_ENABLE()               (SYSTEM->ClockEnable6.SSIM0_CLKEN = 1)
#define __SYSTEM_SPI_MASTER1_CLK_ENABLE()               (SYSTEM->ClockEnable6.SSIM1_CLKEN = 1)
 
#define __SYSTEM_SPI_SLAVE0_CLK_DISABLE()               (SYSTEM->ClockEnable6.SSIS0_CLKEN = 0)
#define __SYSTEM_SPI_SLAVE1_CLK_DISABLE()               (SYSTEM->ClockEnable6.SSIS1_CLKEN = 0)

#define __SYSTEM_SPI_MASTER0_X8_CLK_DISABLE()           (SYSTEM->ClockEnable6.MSPI0_CLKEN = 0)
#define __SYSTEM_SPI_MASTER1_X8_CLK_DISABLE()           (SYSTEM->ClockEnable6.MSPI1_CLKEN = 0)

#define __SYSTEM_SPI_MASTER0_CLK_DISABLE()              (SYSTEM->ClockEnable6.SSIM0_CLKEN = 0)
#define __SYSTEM_SPI_MASTER1_CLK_DISABLE()              (SYSTEM->ClockEnable6.SSIM1_CLKEN = 0)

#define __SYSTEM_SPI_SLAVE0_RESET()                     (SYSTEM->RegReset6.SSIS0_SFT_RST = 1)
#define __SYSTEM_SPI_SLAVE1_RESET()                     (SYSTEM->RegReset6.SSIS1_SFT_RST = 1)

#define __SYSTEM_SPI_MASTER0_X8_RESET()                 (SYSTEM->RegReset6.MSPI0_SFT_RST = 1)
#define __SYSTEM_SPI_MASTER1_X8_RESET()                 (SYSTEM->RegReset6.MSPI1_SFT_RST = 1)

#define __SYSTEM_SPI_MASTER0_RESET()                    (SYSTEM->RegReset6.SSIM0_SFT_RST = 1)
#define __SYSTEM_SPI_MASTER1_RESET()                    (SYSTEM->RegReset6.SSIM1_SFT_RST = 1)

/* ====================================================================================================== */
/* =============================== Uart Clock Select/Enable/Disable/Reset =============================== */
/* ====================================================================================================== */
                                                        
#define __SYSTEM_UART_CLK_SELECT_COREH()                (SYSTEM->ClockSEL0.UART_CLK_SEL = 0)
#define __SYSTEM_UART_CLK_SELECT_SPLL()                 (SYSTEM->ClockSEL0.UART_CLK_SEL = 1)
 
#define __SYSTEM_UART_CLK_DIV(__CLKDIV__)               (SYSTEM->BlockClockDIV1.UART_CLK_DIV = __CLKDIV__ - 1)
                                                             
#define __SYSTEM_UART0_CLK_ENABLE()                     (SYSTEM->ClockEnable5.UART0_CLKEN = 1)
#define __SYSTEM_UART1_CLK_ENABLE()                     (SYSTEM->ClockEnable5.UART1_CLKEN = 1)
#define __SYSTEM_UART2_CLK_ENABLE()                     (SYSTEM->ClockEnable5.UART2_CLKEN = 1)
#define __SYSTEM_UART3_CLK_ENABLE()                     (SYSTEM->ClockEnable5.UART3_CLKEN = 1)
#define __SYSTEM_UART4_CLK_ENABLE()                     (SYSTEM->ClockEnable5.UART4_CLKEN = 1)
#define __SYSTEM_UART5_CLK_ENABLE()                     (SYSTEM->ClockEnable5.UART5_CLKEN = 1)
 
#define __SYSTEM_UART0_CLK_DISABLE()                    (SYSTEM->ClockEnable5.UART0_CLKEN = 0)
#define __SYSTEM_UART1_CLK_DISABLE()                    (SYSTEM->ClockEnable5.UART1_CLKEN = 0)
#define __SYSTEM_UART2_CLK_DISABLE()                    (SYSTEM->ClockEnable5.UART2_CLKEN = 0)
#define __SYSTEM_UART3_CLK_DISABLE()                    (SYSTEM->ClockEnable5.UART3_CLKEN = 0)
#define __SYSTEM_UART4_CLK_DISABLE()                    (SYSTEM->ClockEnable5.UART4_CLKEN = 0)
#define __SYSTEM_UART5_CLK_DISABLE()                    (SYSTEM->ClockEnable5.UART5_CLKEN = 0)
 
#define __SYSTEM_UART0_RESET()                          (SYSTEM->RegReset5.UART0_SFT_RST = 1)
#define __SYSTEM_UART1_RESET()                          (SYSTEM->RegReset5.UART1_SFT_RST = 1)
#define __SYSTEM_UART2_RESET()                          (SYSTEM->RegReset5.UART2_SFT_RST = 1)
#define __SYSTEM_UART3_RESET()                          (SYSTEM->RegReset5.UART3_SFT_RST = 1)
#define __SYSTEM_UART4_RESET()                          (SYSTEM->RegReset5.UART4_SFT_RST = 1)
#define __SYSTEM_UART5_RESET()                          (SYSTEM->RegReset5.UART5_SFT_RST = 1)

/* ====================================================================================================== */
/* =============================== GPIO Clock Select/Enable/Disable/Reset ================================*/
/* ====================================================================================================== */
#define __SYSTEM_GPIO_CLK_SELECT_COREH()                (SYSTEM->ClockSEL0.GPIO_CLK_SEL = 0)
#define __SYSTEM_GPIO_CLK_SELECT_SPLL()                 (SYSTEM->ClockSEL0.GPIO_CLK_SEL = 1)

#define __SYSTEM_GPIO_CLK_DIV(__CLKDIV__)               (SYSTEM->BlockClockDIV1.GPIO_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_GPIOA_CLK_ENABLE()                     (SYSTEM->ClockEnable4.GPIOA_CLKEN = 1)
#define __SYSTEM_GPIOB_CLK_ENABLE()                     (SYSTEM->ClockEnable4.GPIOB_CLKEN = 1)
#define __SYSTEM_GPIOC_CLK_ENABLE()                     (SYSTEM->ClockEnable4.GPIOC_CLKEN = 1)
#define __SYSTEM_GPIOD_CLK_ENABLE()                     (SYSTEM->ClockEnable4.GPIOD_CLKEN = 1)
#define __SYSTEM_GPIOE_CLK_ENABLE()                     (SYSTEM->ClockEnable4.GPIOE_CLKEN = 1)

#define __SYSTEM_GPIOA_CLK_DISABLE()                    (SYSTEM->ClockEnable4.GPIOA_CLKEN = 0)
#define __SYSTEM_GPIOB_CLK_DISABLE()                    (SYSTEM->ClockEnable4.GPIOB_CLKEN = 0)
#define __SYSTEM_GPIOC_CLK_DISABLE()                    (SYSTEM->ClockEnable4.GPIOC_CLKEN = 0)
#define __SYSTEM_GPIOD_CLK_DISABLE()                    (SYSTEM->ClockEnable4.GPIOD_CLKEN = 0)
#define __SYSTEM_GPIOE_CLK_DISABLE()                    (SYSTEM->ClockEnable4.GPIOE_CLKEN = 0)

#define __SYSTEM_GPIOA_RESET()                          (SYSTEM->RegReset4.GPIO0_SFT_RST = 1)
#define __SYSTEM_GPIOB_RESET()                          (SYSTEM->RegReset4.GPIO1_SFT_RST = 1)
#define __SYSTEM_GPIOC_RESET()                          (SYSTEM->RegReset4.GPIO2_SFT_RST = 1)
#define __SYSTEM_GPIOD_RESET()                          (SYSTEM->RegReset4.GPIO3_SFT_RST = 1)
#define __SYSTEM_GPIOE_RESET()                          (SYSTEM->RegReset4.GPIO4_SFT_RST = 1)

#define __SYSTEM_GPIOA_INPUT_OPEN_CIRCUIT_ENABLE(__PIN__)          (SYSTEM->PortA_InputOpenCircuit &= ~(__PIN__))
#define __SYSTEM_GPIOB_INPUT_OPEN_CIRCUIT_ENABLE(__PIN__)          (SYSTEM->PortB_InputOpenCircuit &= ~(__PIN__))
#define __SYSTEM_GPIOC_INPUT_OPEN_CIRCUIT_ENABLE(__PIN__)          (SYSTEM->PortC_InputOpenCircuit &= ~(__PIN__))
#define __SYSTEM_GPIOD_INPUT_OPEN_CIRCUIT_ENABLE(__PIN__)          (SYSTEM->PortD_InputOpenCircuit &= ~(__PIN__))
#define __SYSTEM_GPIOE_INPUT_OPEN_CIRCUIT_ENABLE(__PIN__)          (SYSTEM->PortE_InputOpenCircuit &= ~(__PIN__))

#define __SYSTEM_GPIOA_INPUT_OPEN_CIRCUIT_DISABLE(__PIN__)         (SYSTEM->PortA_InputOpenCircuit |= (__PIN__))
#define __SYSTEM_GPIOB_INPUT_OPEN_CIRCUIT_DISABLE(__PIN__)         (SYSTEM->PortB_InputOpenCircuit |= (__PIN__))
#define __SYSTEM_GPIOC_INPUT_OPEN_CIRCUIT_DISABLE(__PIN__)         (SYSTEM->PortC_InputOpenCircuit |= (__PIN__))
#define __SYSTEM_GPIOD_INPUT_OPEN_CIRCUIT_DISABLE(__PIN__)         (SYSTEM->PortD_InputOpenCircuit |= (__PIN__))
#define __SYSTEM_GPIOE_INPUT_OPEN_CIRCUIT_DISABLE(__PIN__)         (SYSTEM->PortE_InputOpenCircuit |= (__PIN__))

/* ======================================================================================================== */
/* =============================== PWM Clock Select/Enable/Disable/Reset ================================== */
/* ======================================================================================================== */

#define __SYSTEM_PWM_CLK_SELECT_COREH()                 (SYSTEM->ClockSEL0.PWM_CLK_SEL = 0)
#define __SYSTEM_PWM_CLK_SELECT_SPLL()                  (SYSTEM->ClockSEL0.PWM_CLK_SEL = 1)

#define __SYSTEM_PWM_CLK_DIV(__CLKDIV__)                (SYSTEM->BlockClockDIV2.PWM_CLK_DIV = __CLKDIV__ - 1) 
 
#define __SYSTEM_PWM0_CLK_ENABLE()                      (SYSTEM->ClockEnable4.PWM0_CLKEN = 1)
#define __SYSTEM_PWM1_CLK_ENABLE()                      (SYSTEM->ClockEnable4.PWM1_CLKEN = 1)
#define __SYSTEM_PWM0_CLK_DISABLE()                     (SYSTEM->ClockEnable4.PWM0_CLKEN = 0)
#define __SYSTEM_PWM1_CLK_DISABLE()                     (SYSTEM->ClockEnable4.PWM1_CLKEN = 0)
 
#define __SYSTEM_PWM0_RESET()                           (SYSTEM->RegReset4.PWM0_SFT_RST = 1)
#define __SYSTEM_PWM1_RESET()                           (SYSTEM->RegReset4.PWM1_SFT_RST = 1)

/* ======================================================================================================= */
/* =============================== I2S Clock Select/Enable/Disable/Reset ================================= */
/* ======================================================================================================= */
//Further modifications needed:
#define __SYSTEM_I2S_CLK_SELECT_COREH()                 (SYSTEM->ClockSEL1.I2S_CLK_SEL = 0)
#define __SYSTEM_I2S_CLK_SELECT_SPLL()                  (SYSTEM->ClockSEL1.I2S_CLK_SEL = 1)
#define __SYSTEM_I2S_CLK_SELECT_AUPLL()                 (SYSTEM->ClockSEL1.I2S_CLK_SEL = 2)
#define __SYSTEM_I2S_CLK_SELECT_EXTERNAL()              (SYSTEM->ClockSEL1.I2S_CLK_SEL = 3)
 
#define __SYSTEM_I2S_CLK_DIV(__CLKDIV__)                (SYSTEM->AudioClockDIV.I2S_CLK_DIV = __CLKDIV__ - 1)
                                                             
#define __SYSTEM_I2S0_CLK_ENABLE()                      (SYSTEM->ClockEnable8.I2S0_CLKEN = 1) 
#define __SYSTEM_I2S1_CLK_ENABLE()                      (SYSTEM->ClockEnable8.I2S1_CLKEN = 1)
#define __SYSTEM_I2S2_CLK_ENABLE()                      (SYSTEM->ClockEnable8.I2S2_CLKEN = 1)
 
#define __SYSTEM_I2S0_CLK_DISABLE()                     (SYSTEM->ClockEnable8.I2S0_CLKEN = 0) 
#define __SYSTEM_I2S1_CLK_DISABLE()                     (SYSTEM->ClockEnable8.I2S1_CLKEN = 0)
#define __SYSTEM_I2S2_CLK_DISABLE()                     (SYSTEM->ClockEnable8.I2S2_CLKEN = 0)
 
#define __SYSTEM_I2S0_RESET()                           (SYSTEM->RegReset8.I2S0_SFT_RST = 1)
#define __SYSTEM_I2S1_RESET()                           (SYSTEM->RegReset8.I2S1_SFT_RST = 1)
#define __SYSTEM_I2S2_RESET()                           (SYSTEM->RegReset8.I2S2_SFT_RST = 1)

/* ======================================================================================================= */
/* =============================== PSD DAC Clock Select/Enable/Disable/Reset ============================= */
/* ======================================================================================================= */
//Further modifications needed:
#define __SYSTEM_PSD_DAC_CLK_SELECT_SPLL()                (SYSTEM->ClockSEL1.CDC_PLL_CLK_SEL = 0)
#define __SYSTEM_PSD_DAC_CLK_SELECT_AUPLL()               (SYSTEM->ClockSEL1.CDC_PLL_CLK_SEL = 1)

#define __SYSTEM_PSD_DAC_CLK_ENABLE()                     (SYSTEM->ClockEnable8.PSD_DAC_CLKEN = 1)
#define __SYSTEM_PSD_DAC_CLK_DISABLE()                    (SYSTEM->ClockEnable8.PSD_DAC_CLKEN = 0)

/* ======================================================================================================= */
/* =============================== SPDIF Clock Select/Enable/Disable/Reset ======================== ====== */
/* ======================================================================================================= */
//Further modifications needed:
#define __SYSTEM_SPDIF_CLK_SELECT_COREH()               (SYSTEM->ClockSEL1.SPDIF_CLK_SEL = 0)
#define __SYSTEM_SPDIF_CLK_SELECT_SPLL()                (SYSTEM->ClockSEL1.SPDIF_CLK_SEL = 1)
#define __SYSTEM_SPDIF_CLK_SELECT_AUPLL()               (SYSTEM->ClockSEL1.SPDIF_CLK_SEL = 2)
#define __SYSTEM_SPDIF_CLK_SELECT_D48M()                (SYSTEM->ClockSEL1.SPDIF_CLK_SEL = 3)

#define __SYSTEM_SPDIF_CLK_DIV(__CLKDIV__)              (SYSTEM->AudioClockDIV.SPDIF_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_SPDIF_CLK_ENABLE()                     (SYSTEM->ClockEnable8.SPDIF_CLKEN = 1)
#define __SYSTEM_SPDIF_CLK_DISABLE()                    (SYSTEM->ClockEnable8.SPDIF_CLKEN = 0)

#define __SYSTEM_SPDIF_RESET()                          (SYSTEM->RegReset8.SPDIF_SFT_RST = 1)

/* ======================================================================================================= */
/* =============================== EFUSE Clock Enable/Disable/Reset ====================================== */
/* ======================================================================================================= */
#define __SYSTEM_EFUSE_CLK_DIV(__CLKDIV__)              (SYSTEM->BlockClockDIV2.EFUSE_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_EFUSE0_CLK_ENABLE()                    (SYSTEM->ClockEnable9.EFUSE0_CLKEN = 1)
#define __SYSTEM_EFUSE1_CLK_ENABLE()                    (SYSTEM->ClockEnable9.EFUSE1_CLKEN = 1)
#define __SYSTEM_EFUSE0_CLK_DISABLE()                   (SYSTEM->ClockEnable9.EFUSE0_CLKEN = 0)
#define __SYSTEM_EFUSE1_CLK_DISABLE()                   (SYSTEM->ClockEnable9.EFUSE1_CLKEN = 0)

#define __SYSTEM_EFUSE0_RESET()                         (SYSTEM->RegReset9.EFUSE0_SFT_RST = 1)
#define __SYSTEM_EFUSE1_RESET()                         (SYSTEM->RegReset9.EFUSE1_SFT_RST = 1)

/* ======================================================================================================= */
/* =============================== FRSPIM Clock Enable/Disable/Reset ===================================== */
/* ======================================================================================================= */
#define __SYSTEM_FRSPIM_CLK_DIV(__CLKDIV__)             (SYSTEM->BlockClockDIV2.FRSPIM_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_FRSPIM__CLK_ENABLE()                   (SYSTEM->ClockEnable9.FRSPIM_CLKEN = 1)
#define __SYSTEM_FRSPIM__CLK_DISABLE()                  (SYSTEM->ClockEnable9.FRSPIM_CLKEN = 0)

#define __SYSTEM_FRSPIM_RESET()                         (SYSTEM->RegReset9.FRSPIM_SFT_RST = 1)

/* ====================================================================================================== */
/* =============================== PDM Clock Select/Enable/Disable/Reset ================================ */
/* ====================================================================================================== */
//Further modifications needed:
#define __SYSTEM_PDM0_CLK_SELECT_COREH()                (SYSTEM->ClockSEL1.PDM0_CLK_SEL = 0)
#define __SYSTEM_PDM0_CLK_SELECT_AUPLL()                (SYSTEM->ClockSEL1.PDM0_CLK_SEL = 1)
#define __SYSTEM_PDM0_CLK_SELECT_EXTERNAL()             (SYSTEM->ClockSEL1.PDM0_CLK_SEL = 2)
#define __SYSTEM_PDM0_CLK_SELECT_D48M()                 (SYSTEM->ClockSEL1.PDM0_CLK_SEL = 3)

#define __SYSTEM_PDM1_CLK_SELECT_COREH()                (SYSTEM->ClockSEL1.PDM1_CLK_SEL = 0)
#define __SYSTEM_PDM1_CLK_SELECT_AUPLL()                (SYSTEM->ClockSEL1.PDM1_CLK_SEL = 1)
#define __SYSTEM_PDM1_CLK_SELECT_EXTERNAL()             (SYSTEM->ClockSEL1.PDM1_CLK_SEL = 2)
#define __SYSTEM_PDM1_CLK_SELECT_D48M()                 (SYSTEM->ClockSEL1.PDM1_CLK_SEL = 3)

#define __SYSTEM_PDM0_CLK_DIV(__CLKDIV__)               (SYSTEM->AudioClockDIV.PDM0_CLK_DIV = __CLKDIV__ - 1)
#define __SYSTEM_PDM1_CLK_DIV(__CLKDIV__)               (SYSTEM->AudioClockDIV.PDM1_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_PDM0_CLK_ENABLE()                      (SYSTEM->ClockEnable8.PDM0_CLKEN = 1)
#define __SYSTEM_PDM1_CLK_ENABLE()                      (SYSTEM->ClockEnable8.PDM1_CLKEN = 1)

#define __SYSTEM_PDM0_CLK_DISABLE()                     (SYSTEM->ClockEnable8.PDM0_CLKEN = 0)
#define __SYSTEM_PDM1_CLK_DISABLE()                     (SYSTEM->ClockEnable8.PDM1_CLKEN = 0)

#define __SYSTEM_PDM0_RESET()                           (SYSTEM->RegReset8.PDM0_SFT_RST = 1)
#define __SYSTEM_PDM1_RESET()                           (SYSTEM->RegReset8.PDM1_SFT_RST = 1)

/* ====================================================================================================== */
/* =============================== DMA Clock Enable/Disable/Reset ======================================= */
/* ====================================================================================================== */
#define __SYSTEM_DMA0_CLK_ENABLE()                      (SYSTEM->ClockEnable1.DMAC0_CLKEN = 1)
#define __SYSTEM_DMA1_CLK_ENABLE()                      (SYSTEM->ClockEnable1.DMAC1_CLKEN = 1)

#define __SYSTEM_DMA0_CLK_DISABLE()                     (SYSTEM->ClockEnable1.DMAC0_CLKEN = 0)
#define __SYSTEM_DMA1_CLK_DISABLE()                     (SYSTEM->ClockEnable1.DMAC1_CLKEN = 0)

#define __SYSTEM_DMA0_RESET()                           (SYSTEM->RegReset1.DMAC0_SFT_RST = 1)
#define __SYSTEM_DMA1_RESET()                           (SYSTEM->RegReset1.DMAC1_SFT_RST = 1)

/* ====================================================================================================== */
/* =============================== USB Clock Enable/Disable/Reset ======================================= */
/* ====================================================================================================== */

#define __SYSTEM_USB_CLK_ENABLE()                       (SYSTEM->ClockEnable9.USB_CLKEN = 1)
#define __SYSTEM_USB_CLK_DISABLE()                      (SYSTEM->ClockEnable9.USB_CLKEN = 0)

#define __SYSTEM_USB_RESET()                            (SYSTEM->RegReset9.USB_SFT_RST = 1)

/* ====================================================================================================== */
/* =============================== DISPLAY Select/Clock Enable/Disable/Reset =========================== */
/* ====================================================================================================== */
//Further modifications needed:
#define __SYSTEM_DISPLAY_CLK_SELECT_COREH()             (SYSTEM->ClockSEL0.DISPLAY_CLK_SEL = 0)
#define __SYSTEM_DISPLAY_CLK_SELECT_SPLL()              (SYSTEM->ClockSEL0.DISPLAY_CLK_SEL = 1)
#define __SYSTEM_DISPLAY_CLK_SELECT_AUPLL()             (SYSTEM->ClockSEL0.DISPLAY_CLK_SEL = 2)
#define __SYSTEM_DISPLAY_CLK_SELECT_D48M()              (SYSTEM->ClockSEL0.DISPLAY_CLK_SEL = 3)

#define __SYSTEM_DISPLAY_CLK_DIV(__CLKDIV__)            (SYSTEM->BlockClockDIV1.DISPLAY_CLK_DIV = __CLKDIV__ - 1)

#define __SYSTEM_DISPLAY_CLK_ENABLE()                   (SYSTEM->ClockEnable9.DISPLAY_CLKEN = 1)

#define __SYSTEM_DISPLAY_CLK_DISABLE()                  (SYSTEM->ClockEnable9.DISPLAY_CLKEN = 0)

#define __SYSTEM_DISPLAY_RESET()                        (SYSTEM->RegReset9.DISPLAY_SFT_RST = 1)

/* ====================================================================================================== */
/* =============================== SYSTEM MISC config  ================================================== */
/* ====================================================================================================== */
#define SYSTEM_QSPI0_PAD0    (0x01)
#define SYSTEM_QSPI0_PAD1    (0x02)
#define SYSTEM_QSPI0_PAD2    (0x04)
#define SYSTEM_QSPI0_PAD3    (0x08)
#define SYSTEM_QSPI0_PAD4    (0x10)
#define SYSTEM_QSPI0_PAD5    (0x20)
#define SYSTEM_QSPI0_PAD6    (0x40)
#define SYSTEM_QSPI0_PAD7    (0x80)
#define SYSTEM_QSPI0_PAD8    (0x100)
#define SYSTEM_QSPI0_PAD9    (0x200)

#define __SYSTEM_QSPI_INPUT_OPEN_CIRCUIT_ENABLE(__PIN__)          (SYSTEM->QspiPadConfig.QSPI_InputOpenCircuit &= ~(__PIN__))
#define __SYSTEM_QSPI_INPUT_OPEN_CIRCUIT_DISABLE(__PIN__)         (SYSTEM->QspiPadConfig.QSPI_InputOpenCircuit |= (__PIN__))

#define __SYSTEM_QSPI0_PAD0_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x3)
#define __SYSTEM_QSPI0_PAD1_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0xC)
#define __SYSTEM_QSPI0_PAD2_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x30)
#define __SYSTEM_QSPI0_PAD3_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0xC0)

#define __SYSTEM_QSPI0_PAD4_USED_IO2()          (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x100)
#define __SYSTEM_QSPI0_PAD4_USED_IO3()          (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x200)
#define __SYSTEM_QSPI0_PAD4_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x300)

#define __SYSTEM_QSPI0_PAD5_USED_IO3()          (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x400)
#define __SYSTEM_QSPI0_PAD5_USED_IO2()          (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x800)
#define __SYSTEM_QSPI0_PAD5_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0xC00)

#define __SYSTEM_QSPI0_PAD6_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x3000)
#define __SYSTEM_QSPI0_PAD7_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0xC000)

#define __SYSTEM_QSPI0_PAD8_USED_IO2()          (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x10000)
#define __SYSTEM_QSPI0_PAD8_USED_IO3()          (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x20000)
#define __SYSTEM_QSPI0_PAD8_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x30000)

#define __SYSTEM_QSPI0_PAD9_USED_IO3()          (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x40000)
#define __SYSTEM_QSPI0_PAD9_USED_IO2()          (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0x80000)
#define __SYSTEM_QSPI0_PAD9_USED_REGIO()        (SYSTEM->QspiPadConfig.QSPI_FuncMux |= 0xC0000)

#define __SYSTEM_QSPI0_PAD_PULL_ENABLE(__PAD__)                   (SYSTEM->QspiPadConfig.QSPI_PullEN |= (__PAD__))
#define __SYSTEM_QSPI0_PAD_PULL_DISABLE(__PAD__)                  (SYSTEM->QspiPadConfig.QSPI_PullEN &= ~(__PAD__))
                                                                  
#define __SYSTEM_QSPI0_PAD_PULL_SEL_UP(__PAD__)                   (SYSTEM->QspiPadConfig.QSPI_PullSelect |= (__PAD__))
#define __SYSTEM_QSPI0_PAD_PULL_SEL_DOWN(__PAD__)                 (SYSTEM->QspiPadConfig.QSPI_PullSelect &= ~(__PAD__))
                                                                  
#define __SYSTEM_QSPI0_PAD_INPUT_ENABLE(__PAD__)                  (SYSTEM->QspiPadConfig.QSPI_InputOpenCircuit |= (__PAD__))
                                                                  
#define __SYSTEM_FR3066DQC_QSPI0_IO2_IO3_CONFIG()                 do { __SYSTEM_QSPI0_PAD4_USED_REGIO();   \
                                                                       __SYSTEM_QSPI0_PAD5_USED_IO3();   \
                                                                       __SYSTEM_QSPI0_PAD6_USED_REGIO(); \
                                                                       __SYSTEM_QSPI0_PAD7_USED_REGIO(); \
                                                                       __SYSTEM_QSPI0_PAD8_USED_IO2(); \
                                                                       __SYSTEM_QSPI0_PAD_PULL_DISABLE(SYSTEM_QSPI0_PAD0|SYSTEM_QSPI0_PAD1|SYSTEM_QSPI0_PAD2|SYSTEM_QSPI0_PAD3|SYSTEM_QSPI0_PAD5|SYSTEM_QSPI0_PAD8); \
                                                                       __SYSTEM_QSPI0_PAD_INPUT_ENABLE(SYSTEM_QSPI0_PAD2|SYSTEM_QSPI0_PAD5|SYSTEM_QSPI0_PAD8); \
                                                                  } while(0)
                                                                  
#define __SYSTEM_MISC_CLK_ENABLE()                                do { SYSTEM->MISC_Clock0 = 0xFFFFFFFF; \
                                                                       SYSTEM->MISC_Clock1 = 0xFFFFFFFF; \
                                                                       SYSTEM->MISC_Clock2 = 0xFFFFFFFF; \
                                                                       SYSTEM->MISC_Clock3 = 0xFFFFFFFF; \
                                                                       SYSTEM->MISC_Clock4 = 0xFFFFFFFF; \
                                                                       SYSTEM->MISC_Clock5 = 0xFFFFFFFF; \
                                                                  } while(0)

/* Enable input of SWD(PB10, PB11), UART(PB4, PB5), Flash IO0 and IO1 */                                                                  
#define __SYSTEM_MISC_IO_CONFIG()                                 do { SYSTEM->PortB_InputOpenCircuit |= 0xC30; \
                                                                       SYSTEM->QspiPadConfig.QSPI_InputOpenCircuit |= 0x00C; \
                                                                       SYSTEM->MISC_IO_Config = 0x7F; \
                                                                       SYSTEM->PortA_WakeupEN = 0; \
                                                                       SYSTEM->PortB_WakeupEN = 0; \
                                                                       SYSTEM->PortC_WakeupEN = 0; \
                                                                       SYSTEM->PortD_WakeupEN = 0; \
                                                                       SYSTEM->PortE_WakeupEN = 0; \
                                                                       SYSTEM->QspiPadConfig.QSPI_WakeupEN = 0; \
                                                                       SYSTEM->OspiPadConfig.OSPI_WakeupEN = 0; \
                                                                  } while(0)

#define SYSTEM_OSPI_PAD0     (0x0001)
#define SYSTEM_OSPI_PAD1     (0x0002)
#define SYSTEM_OSPI_PAD2     (0x0004)
#define SYSTEM_OSPI_PAD3     (0x0008)
#define SYSTEM_OSPI_PAD4     (0x0010)
#define SYSTEM_OSPI_PAD5     (0x0020)
#define SYSTEM_OSPI_PAD6     (0x0040)
#define SYSTEM_OSPI_PAD7     (0x0080)
#define SYSTEM_OSPI_PAD8     (0x0100)
#define SYSTEM_OSPI_PAD9     (0x0200)
#define SYSTEM_OSPI_PAD10    (0x0400)
#define SYSTEM_OSPI_PAD11    (0x0800)
#define SYSTEM_OSPI_PAD12    (0x1000)
#define SYSTEM_OSPI_PAD13    (0x2000)

#define __SYSTEM_OSPI_INPUT_OPEN_CIRCUIT_ENABLE(__PIN__)          (SYSTEM->OspiPadConfig.OSPI_InputOpenCircuit &= ~(__PIN__))
#define __SYSTEM_OSPI_INPUT_OPEN_CIRCUIT_DISABLE(__PIN__)         (SYSTEM->OspiPadConfig.OSPI_InputOpenCircuit |= (__PIN__))

/* ====================================================================================================== */
/* =============================== SYSTEM Audio Tune Config  ============================================ */
/* ====================================================================================================== */

#define __SYSTEM_I2S_TUNE_ENABLE()                                (SYSTEM->AudioTuneCTRL.I2S_TUEN_EN = 1)
#define __SYSTEM_I2S_TUNE_DISABLE()                               (SYSTEM->AudioTuneCTRL.I2S_TUEN_EN = 0) 
#define __SYSTEM_PSD_DAC_TUNE_ENABLE()                            (SYSTEM->AudioTuneCTRL.PSD_DAC_TUEN_EN = 1)
#define __SYSTEM_PSD_DAC_TUNE_DISABLE()                           (SYSTEM->AudioTuneCTRL.PSD_DAC_TUEN_EN = 0)
#define __SYSTEM_PDM0_TUNE_ENABLE()                               (SYSTEM->AudioTuneCTRL.PDM0_TUEN_EN = 1)
#define __SYSTEM_PDM0_TUNE_DISABLE()                              (SYSTEM->AudioTuneCTRL.PDM0_TUEN_EN = 0)
#define __SYSTEM_PDM1_TUNE_ENABLE()                               (SYSTEM->AudioTuneCTRL.PDM1_TUEN_EN = 1)
#define __SYSTEM_PDM1_TUNE_DISABLE()                              (SYSTEM->AudioTuneCTRL.PDM1_TUEN_EN = 0)
#define __SYSTEM_SPDIF_TUNE_ENABLE()                              (SYSTEM->AudioTuneCTRL.SPDIF_TUEN_EN = 1)
#define __SYSTEM_SPDIF_TUNE_DISABLE()                             (SYSTEM->AudioTuneCTRL.SPDIF_TUEN_EN = 0)

#define __SYSTEM_I2S_TUNE_SELECT_MODE0()                          (SYSTEM->AudioTuneCTRL.I2S_MODE = 0)
#define __SYSTEM_I2S_TUNE_SELECT_MODE1()                          (SYSTEM->AudioTuneCTRL.I2S_MODE = 1) 
#define __SYSTEM_PSD_DAC_TUNE_SELECT_MODE0()                      (SYSTEM->AudioTuneCTRL.PSD_DAC_MODE = 0)
#define __SYSTEM_PSD_DAC_TUNE_SELECT_MODE1()                      (SYSTEM->AudioTuneCTRL.PSD_DAC_MODE = 1)
#define __SYSTEM_PDM0_TUNE_SELECT_MODE0()                         (SYSTEM->AudioTuneCTRL.PDM0_MODE = 0)
#define __SYSTEM_PDM0_TUNE_SELECT_MODE1()                         (SYSTEM->AudioTuneCTRL.PDM0_MODE = 1)
#define __SYSTEM_PDM1_TUNE_SELECT_MODE0()                         (SYSTEM->AudioTuneCTRL.PDM1_MODE = 0)
#define __SYSTEM_PDM1_TUNE_SELECT_MODE1()                         (SYSTEM->AudioTuneCTRL.PDM1_MODE = 1)
#define __SYSTEM_SPDIF_TUNE_SELECT_MODE0()                        (SYSTEM->AudioTuneCTRL.SPDIF_MODE = 0)
#define __SYSTEM_SPDIF_TUNE_SELECT_MODE1()                        (SYSTEM->AudioTuneCTRL.SPDIF_MODE = 1)

#define __SYSTEM_I2S_TUNE_CLK_GATE(__P0__, __P1__)                (SYSTEM->I2S_TuneClock_Gate = (((__P1__-1)<<16)|(__P0__-1))) 
#define __SYSTEM_PSD_DAC_TUNE_CLK_GATE(__P0__, __P1__)            (SYSTEM->PSD_DAC_TuneClock_Gate = (((__P1__-1)<<16)|(__P0__-1))) 
#define __SYSTEM_PDM0_TUNE_CLK_GATE(__P0__, __P1__)               (SYSTEM->PDM0_TuneClock_Gate = (((__P1__-1)<<16)|(__P0__-1))) 
#define __SYSTEM_PDM1_TUNE_CLK_GATE(__P0__, __P1__)               (SYSTEM->PDM1_TuneClock_Gate = (((__P1__-1)<<16)|(__P0__-1))) 
#define __SYSTEM_SPDIF_TUNE_CLK_GATE(__P0__, __P1__)              (SYSTEM->SPDIF_TuneClock_Gate = (((__P1__-1)<<16)|(__P0__-1))) 
                                                                  

/* ====================================================================================================== */
/* ===============================   GLOBAL interrupt controller    ===================================== */
/* ====================================================================================================== */
typedef unsigned int CPU_SR;

/** @brief Enable interrupts globally in the system.
 * This macro must be used when the initialization phase is over and the interrupts
 * can start being handled by the system.
 */
void GLOBAL_INT_START(void);

/** @brief Disable interrupts globally in the system.
 * This macro must be used when the system wants to disable all the interrupt
 * it could handle.
 */
void GLOBAL_INT_STOP(void);

/** @brief Disable interrupts globally in the system.
 * This macro must be used in conjunction with the @ref GLOBAL_INT_RESTORE macro since this
 * last one will close the brace that the current macro opens.  This means that both
 * macros must be located at the same scope level.
 */

uint32_t CPU_SR_Save(uint32_t);
#define GLOBAL_INT_DISABLE()    do {    \
                                    CPU_SR cpu_sr;  \
                                    cpu_sr = CPU_SR_Save(0x20);
#define GLOBAL_INT_DISABLE_V2()   CPU_SR_Save(0x20)

/** @brief Restore interrupts from the previous global disable.
 * @sa GLOBAL_INT_DISABLE
 */
void CPU_SR_Restore(uint32_t reg);
#define GLOBAL_INT_RESTORE()    CPU_SR_Restore(cpu_sr); \
                                    } while(0)
#define GLOBAL_INT_RESTORE_V2(sr) CPU_SR_Restore(sr);

#define WFI()                   __ASM("wfi")

#ifdef __ICCARM__
#define __RAM_CODE              __ramfunc
#else
#define __RAM_CODE              __attribute__((section("ram_code")))
#endif

/* Exported functions --------------------------------------------------------*/

/* Write/Read pmu register, unit byte */
#define pmu_reg_write(addr, data)      ool_write(addr, data)
#define pmu_reg_read(addr)             ool_read(addr)
/* Write/Read pmu register, unit half word */
#define pmu_reg_write16(addr, data)    ool_write16(addr, data)
#define pmu_reg_read16(addr)           ool_read16(addr)
/* Write/Read pmu register, unit word */
#define pmu_reg_write32(addr, data)    ool_write32(addr, data)
#define pmu_reg_read32(addr)           ool_read32(addr)


/* SystemInit */
void SystemInit(void);

/* System_CORE_HSCLK_config */
/* System_SPLL_config */
/* System_AUPLL_config */
/* System_MCU_clock_Config */
void System_CORE_HSCLK_config(System_CORE_HSCLKConfig_t *COREHConfig);
int System_SPLL_config(System_SPLLConfig_t *PLLConfig, uint32_t fu32_timeout);
int System_AUPLL_config(System_AUPLLConfig_t *PLLConfig, uint32_t fu32_timeout);
void System_MCU_clock_Config(System_ClkConfig_t *ClkConfig);

/* Get system Core/DSP/SPLLCLK/AUPLLCLK/CORE_HSCLK clock. unit HZ */
uint32_t system_get_CoreClock(void);
uint32_t system_get_DSPClock(void);
uint32_t system_get_CORE_HSCLK(void);
uint32_t system_get_SPLLCLK(void);
uint32_t system_get_AUPLLCLK(void);
uint32_t system_get_LPRCCLK(void);
void system_set_LPRCCLK(uint32_t);
/* System_get_peripheral_clock */
uint32_t system_get_peripheral_clock(per_clock_index_t peripheral);

void system_dmac_request_id_config(dmac_request_source_t fe_source, dmac_request_id_t fe_id);

void system_xip_flash_init(System_XIPConfig_t *cfg, bool wake_up);

void system_delay_us(uint32_t fu32_delay);

void system_cache_enable(bool invalid_ram);
void system_cache_disable(void);

void system_prevent_sleep_set(uint32_t type);
void system_prevent_sleep_clear(uint32_t type);
uint32_t system_prevent_sleep_get(void);

void system_get_unique_ID(uint8_t *buffer, uint8_t *length);

#endif  // __SYSTEM_FR30XX_H__
