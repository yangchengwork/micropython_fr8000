/*
  ******************************************************************************
  * @file    fr30xx.h
  * @author  FreqChip Firmware Team
  * @brief   CMSIS fr30xx Device Peripheral Access Layer Header File.
  *
  *          This file contains:
  *           - Data structures and the address mapping for all peripherals
  *           - Configuration of the Processor and Core Peripherals
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __FR30XX_H__
#define __FR30XX_H__

#ifdef __cplusplus
extern "C"
{
#endif

//#define CHIP_SEL_FR3066DQC_V1
//#define CHIP_SEL_FR3068EC_V1
#define CHIP_SEL_FR3066DQC_V2
//#define CHIP_SEL_FR3068EC_V2

#if (defined(CHIP_SEL_FR3066DQC_V1) \
        + defined(CHIP_SEL_FR3068EC_V1) \
        + defined(CHIP_SEL_FR3066DQC_V2) \
        + defined(CHIP_SEL_FR3068EC_V2) \
        != 1)
#error "only one chip should be selected!"
#endif

#ifdef CHIP_SEL_FR3066DQC_V2
#undef CHIP_SEL_FR3066DQC_V2
#define CHIP_SEL_FR3066DQC_V1
#define CHIP_UPDATE 
#endif

#ifdef CHIP_SEL_FR3068EC_V2
#undef CHIP_SEL_FR3068EC_V2
#define CHIP_SEL_FR3068EC_V1
#define CHIP_UPDATE 
#endif

/** @group Peripheral_interrupt_number_definition
  * @{
  */
#if defined(__ARMCC_VERSION) || defined(__GNUC__) || defined(__ICCARM__)
typedef enum IRQn
{
    /******  Cortex-M33 Processor Exceptions Numbers ************************************************/
    NonMaskableInt_IRQn           = -14,    /*!< 2 Non Maskable Interrupt                           */
    HardFault_IRQn                = -13,    /*!< 3 Cortex-M33 Hard Fault Interrupt                  */
    SVCall_IRQn                   = -5,     /*!< 11 Cortex-M33 SV Call Interrupt                    */
    PendSV_IRQn                   = -2,     /*!< 14 Cortex-M33 Pend SV Interrupt                    */
    SysTick_IRQn                  = -1,     /*!< 15 Cortex-M33 System Tick Interrupt                */
	
    /******  CMSDK Specific Interrupt Numbers *******************************************************/
    TIMER0_IRQn                     = 0,     /*!<   */
    TIMER1_IRQn                     = 1,     /*!<   */
    TIMER2_IRQn                     = 2,     /*!<   */
    TIMER3_IRQn                     = 3,     /*!<   */
    DMA0_IRQn                       = 4,
    DMA1_IRQn                       = 5,     /*!<   */
    SDIOH0_IRQn                     = 6,     /*!<   */
    IPC_MCU_IRQn                    = 8,     /*!<   */
    USBOTG_IRQn                     = 9,     /*!<   */
    GPIOA_IRQn                      = 16,    /*!<   */
    GPIOB_IRQn                      = 17,    /*!<   */
    GPIOC_IRQn                      = 18,    /*!<   */
    GPIOD_IRQn                      = 19,    /*!<   */
    UART0_IRQn                      = 20,    /*!<   */
    UART1_IRQn                      = 21,    /*!<   */
    UART2_IRQn                      = 22,    /*!<   */
    UART3_IRQn                      = 23,    /*!<   */
    UART4_IRQn                      = 24,
    UART5_IRQn                      = 25,
    I2C0_IRQn                       = 26,
    I2C1_IRQn                       = 28,
    I2C2_IRQn                       = 30,
    SPIM0_IRQn                      = 32,
    SPIM1_IRQn                      = 33,
    SPIS0_IRQn                      = 35,
    SPIS1_IRQn                      = 36,
    SPIMX8_0_IRQn                   = 37,
    SPIMX8_1_IRQn                   = 38,
    I2S0_IRQn                       = 39,
    I2S1_IRQn                       = 40,
    PDM0_IRQn                       = 42,
    PDM1_IRQn                       = 43,
    SARADC_IRQn                     = 45,
    PSD_DAC_IRQn                    = 46,
    SPDIF_IRQn                      = 47,
    DISPLAY_IRQn                    = 51,
    WDT_IRQn                        = 52,
    CALI_IRQn                       = 53,
    TRNG_IRQn                       = 54,
    TICK_IRQn                       = 55,
    DSP_TIMER0_IRQn                 = 60,
    DSP_TIMER1_IRQn                 = 61,
    DSP_WDT_IRQn                    = 62,
    IPC_DSP_IRQn                    = 63,
    YUV2RGB_IRQn                    = 64,
    PMU_IRQn                        = 65,
    PMU_LVD_IRQn                    = 66,
    PMU_ACOK_IRQn                   = 67,
    PMU_WDT_IRQn                    = 68,
    GPIOE_IRQn                      = 69,
    CAN0_Line0_IRQn                 = 70,
    CAN0_Line1_IRQn                 = 71,
    CAN1_Line0_IRQn                 = 72,
    CAN1_Line1_IRQn                 = 73,
    CAN2_Line0_IRQn                 = 74,
    CAN2_Line1_IRQn                 = 75,
    CAN3_Line0_IRQn                 = 76,
    CAN3_Line1_IRQn                 = 77,
    PWM0_IRQn                       = 79,
    PWM1_IRQn                       = 80,
    TIMER4_IRQn                     = 81,
    TIMER5_IRQn                     = 82,
}IRQn_Type;
#endif  // __ARMCC_VERSION

#ifdef __XTENSA__
typedef enum IRQn
{
    DSP_IPC_IRQn                    = 7,
}IRQn_Type;
#endif  // __XTENSA__
/**
  * @}
  */

#if defined(__ARMCC_VERSION) || defined(__GNUC__) || defined(__ICCARM__)
/**
  * @brief Configuration of the Processor and Core Peripherals
  */
#define __CM33_REV                0x0003U   /*!< Core revision r0p4                               */
#define __SAUREGION_PRESENT       0         /*!< SAU regions present                              */
#define __MPU_PRESENT             1         /*!< MPU present                                      */
#define __VTOR_PRESENT            1         /*!< VTOR present                                     */
#define __FPU_PRESENT             1         /*!< FPU present or not                               */
#define __DSP_PRESENT             1         /*!< DSP present or not                               */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */



#include "core_cm33.h"
#if __SAUREGION_PRESENT == 1
#include "arm_cmse.h"
#endif
#endif  // defined(__ARMCC_VERSION) || defined(__GNUC__) || defined(__ICCARM__)

#ifdef __XTENSA__
#define __WEAK              __attribute__((weak))
#define __STATIC_INLINE     __attribute__((always_inline))
#endif  // __XTENSA__

/** @group Peripheral_memory_map
  * @{
  */
#define FLASH_DAC_BASE       (0x08000000)  

#define DMAC0_BASE           (0x10000000)
#define USB_OTG_BASE         (0x10010000)
#define APB_BASE             (0x10100000)
#define CRC_BASE             (0x10130000)
#define EFUSE_SISO_BASE      (0x10140000)
#define EFUSE_PIPO0_BASE     (0x10150000)
#define EFUSE_PIPO1_BASE     (0x101C0000)
#define SYSTEM_TIMER_BASE    (0x10160000)
#define FREE_COUNTER_BASE    (0x10170000)
#define CAN0_BASE            (0x10180000)
#define CAN1_BASE            (0x10190000)
#define CAN2_BASE            (0x101A0000)
#define CAN3_BASE            (0x101B0000)
#define AES_BASE             (0x502B0000)

#define DSP_FLASH_DAC_BASE   (0x28000000)

#define PSRAM_DAC_BASE       (0x38000000)
#define SDIOH0_BASE          (0x40000000)
#define DMAC1_BASE           (0x40020000)

#define GPIOA_BASE           (0x50000000)
#define GPIOB_BASE           (0x50008000)
#define UART0_BASE           (0x50010000)
#define UART1_BASE           (0x50018000)
#define I2C0_BASE            (0x50020000)
#define SPIM0_BASE           (0x50030000)
#define SPIS0_BASE           (0x50040000)
#define PWM0_BASE            (0x50050000)
#define I2S0_BASE            (0x50060000)
#define PDM0_BASE            (0x50070000)
#define AHBC_CACHE_BASE      (0x500B0000)
#define PSRAM_OSPI_BASE      (0x500B8000)
#define SPIMX8_0_BASE        (0x500C0000)
#define DISPLAY_BASE         (0x500D0000)
#define SARADC_BASE          (0x500E0000)

#define GPIOC_BASE           (0x50100000)       
#define GPIOD_BASE           (0x50108000)
#define UART2_BASE           (0x50110000)
#define UART3_BASE           (0x50118000)
#define I2C1_BASE            (0x50120000)
#define SPIM1_BASE           (0x50130000)
#define SPIS1_BASE           (0x50140000)
#define PWM1_BASE            (0x50150000)
#define I2S1_BASE            (0x50160000)
#define PDM1_BASE            (0x50170000)
#define SPDIF_BASE           (0x50180000)
#define PSD_DAC_BASE         (0x50190000)
#define SPIMX8_1_BASE        (0x501C0000)

#define GPIOE_BASE           (0x50200000)
#define UART4_BASE           (0x50210000)
#define UART5_BASE           (0x50218000)
#define I2C2_BASE            (0x50220000)
#define DSP_TIM0_BASE        (0x50240000)
#define DSP_TIM1_BASE        (0x50240014)
#define DSP_WDT_BASE         (0x50250000)
#define DSP_IPC_BASE         (0x50280000)
#define DSP_QSPI_BASE        (0x50290000)
#define YUV2RGB_BASE         (0x502A0000)

#define SYSTEM_REG_BASE      (0xE0050000)
#define TIM0_BASE            (0xE0060000)
#define TIM1_BASE            (0xE0060014)
#define TIM2_BASE            (0xE0068000)
#define TIM3_BASE            (0xE0068014)
#define TIM4_BASE            (0xE006C000)
#define TIM5_BASE            (0xE006C014)
#define WDT_BASE             (0xE0070000)
#define FRSPIM_BASE          (0xE0080000)
#define IPC_BASE             (0xE0090000)
#define CALIB_BASE           (0xE00A0000)
#define FLASH_CACHE_BASE     (0xE00B0000)
#define FLASH_QSPI_BASE      (0xE00C0000)
#define TRNG_BASE            (0xE00D0000)
#define ADC_BASE             (0xE00E0000)


/**
  * @}
  */

/* ########################## Oscillator Values adaptation ####################*/
/**
  * @brief Adjust the value of External High Speed oscillator (HSE) used in your application.
  *        This value is used by the system clock calculation.
  */
#define HSE_VALUE    24000000U /*!< Value of the External oscillator in Hz */

/**
  * @brief Internal High Speed oscillator (HSI) value.
  *        This value is used by the system clock calculation.
  */
#define HSI_VALUE    24000000U /*!< Value of the Internal oscillator in Hz */

/* Peripheral drive */
#include "driver_common.h"
/* System driver    */
#include "system_fr30xx.h"
/* trim relative */
#include "trim_fr30xx.h"

#ifdef __cplusplus
}
#endif

#endif  // __FR30XX_H__
