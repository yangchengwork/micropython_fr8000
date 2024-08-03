#ifndef _PLF_H
#define _PLF_H

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
    /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn           = -14,    /*!< 2 Non Maskable Interrupt                           */
    HardFault_IRQn                = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                   */
    SVCall_IRQn                   = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                     */
    PendSV_IRQn                   = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                     */
    SysTick_IRQn                  = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                 */

    /******  CMSDK Specific Interrupt Numbers *******************************************************/
    BLE_IRQn                      = 0,
    DMA_IRQn                      = 1,
    TIMER0_IRQn                   = 2,
    TIMER1_IRQn                   = 3,
    I2C0_IRQn                     = 4,
    I2C1_IRQn                     = 5,
    SPIM0_IRQn                    = 6,
    SPIM1_IRQn                    = 7,
    SPIS_IRQn                     = 8,
    UART0_IRQn                    = 9,
    UART1_IRQn                    = 10,
    PDM_IRQn                      = 11,
    TRNG_IRQn                     = 12,
    ADC_IRQn                      = 13,
    GPIO_IRQn                     = 14,
    PMU_IRQn                      = 15,
    FC_IRQn                       = 16,
    QSPI_IRQn                     = 17,
    PWM_IRQn                      = 18,
    USBMCU_IRQn                   = 19,
    LCD_IRQn                      = 21,
    I2S_IRQn                      = 23,
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __MPU_PRESENT             0         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */
#define __NVIC_PRIO_GRP_CONFIG    4         /*!< Priority Group configuration                     */

#include "core_cm3.h"
#include "jump_table.h"

/*
 * ==========================================================================
 * -----------  Device Specific Peripheral Section   ------------------------
 * ==========================================================================
 */

#define QSPI0_DAC_ADDRESS   0x10000000
#define QSPI1_DAC_ADDRESS   0x22000000

#define DMA_BASE            0x20020000
#define OTG_BASE            0x20040000

#define SYSTEM_REG_BASE     0x50000000
#define TIMER0_BASE         0x50010000
#define TIMER1_BASE         0x50010020
#define FRSPIM_BASE         0x50020000
#define MODEM_BASE          0x50024000
#define EFUSE_BASE          0x50028000
#define FRSPIM8_BASE        0x5002c000

#define SSIM0_BASE          0x50030000
#define SSIM1_BASE          0x50034000
#define SSIS_BASE           0x50038000
#define I2C0_BASE           0x50040000
#define I2C1_BASE           0x50048000
#define UART0_BASE          0x50050000
#define UART1_BASE          0x50058000
#define GPIO_BASE           0x50060000
#define GPIOAB_BASE         0x50060000
#define GPIOCD_BASE         0x50064000
#define EXTI_BASE           0x50068000
#define I2S_BASE            0x50070000
#define PWM_BASE            0x50080000
#define SAR_ADC_BASE        0x50090000
#define PDM_BASE            0x500A0000
#define CACHE_BASE          0x500B0000
#define QSPI_APB_BASE       0x500B8000
#define QSPI0_APB_BASE      0x500F0000

#define TRNG_BASE           0x500C0000
#define LCD_BASE            0x500D0000

#define TUBE_BASE           0x500F8888
#define APB2SPI_BASE        0x50010000

typedef unsigned int CPU_SR;

void GLOBAL_INT_START(void);
void GLOBAL_INT_STOP(void);;

unsigned int CPU_SR_Save(unsigned char);
#define GLOBAL_INT_DISABLE()    CPU_SR cpu_sr;  {cpu_sr = CPU_SR_Save(0x20);}

void CPU_SR_Restore(CPU_SR reg);
#define GLOBAL_INT_RESTORE()    CPU_SR_Restore(cpu_sr)

void platform_reset(uint32_t error);

/*********************************************************************
 * @fn      get_SDK_compile_date_time
 *
 * @brief   get the SDK compile date time.
 * 
 * @param   date: pointer to the compile date.
 * @param   time: pointer to the compile time.
 */
void get_SDK_compile_date_time(char **date, char **time);

#endif  // _PLF_H


