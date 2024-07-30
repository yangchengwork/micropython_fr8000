/*
  ******************************************************************************
  * @file    driver_pmu_iwdt.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   pmu iwdt module driver.
  *          This file provides firmware functions to manage the 
  *          PMU Independent watchdog (IWDT) peripheral
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "fr30xx.h"

/*********************************************************************
 * @fn      iwdt_init
 *
 * @brief   init the Watchdog. 
 */
void iwdt_init(iwdt_Init_t Init)
{
    /* enable pmu wdt clock */
    ool_write(PMU_REG_CLK_EN, ool_read(PMU_REG_CLK_EN) | PMU_WDT_CLK_EN_BIT);

    /* Set iwdt_Count and iwdt_Timeout */
    iwdt_Set_Count(Init.iwdt_Count);
    iwdt_Set_Timeout(Init.iwdt_Timeout);
    
    /* Set iwdt control */
    ool_write(PMU_REG_WDT_CTRL, Init.iwdt_int_Enable | PMU_WDT_RST_CHIP_BIT);

    /* iwdt interrupt enable */
    if (Init.iwdt_int_Enable) 
    {
        pmu_enable_isr(PMU_WDT_INT_MSK_BIT);
    }
    else
    {
        pmu_disable_isr(PMU_WDT_INT_MSK_BIT);
    }
}

/*********************************************************************
 * @fn      iwdt_Enable
 *
 * @brief   Watchdog count Enable.
 */
void iwdt_Enable(void)
{
    /* enable iwdt count */
    ool_write(PMU_REG_WDT_CTRL, ool_read(PMU_REG_WDT_CTRL) | PMU_WDT_EN_BIT);
}

/*********************************************************************
 * @fn      iwdt_Disable
 *
 * @brief   Watchdog count Disable.
 */
void iwdt_Disable(void)
{
    /* disable iwdt count */
    ool_write(PMU_REG_WDT_CTRL, ool_read(PMU_REG_WDT_CTRL) & ~PMU_WDT_EN_BIT);
}

/*********************************************************************
 * @fn      iwdt_Refresh
 *
 * @brief   Refresh the Watchdog. 
 */
void iwdt_Refresh(void)
{
    ool_write(PMU_REG_WDT_CTRL, ool_read(PMU_REG_WDT_CTRL) | PMU_WDT_CLR_BIT);
}

/*********************************************************************
 * @fn      iwdt_Interrupt_Enable
 *
 * @brief   Watchdog Interrupt Enable.
 */
void iwdt_Interrupt_Enable(void)
{
    /* enable iwdt interrupt */
    ool_write(PMU_REG_WDT_CTRL, ool_read(PMU_REG_WDT_CTRL) | PMU_WDT_IRQ_EN_BIT);
}

/*********************************************************************
 * @fn      iwdt_Interrupt_Disable
 *
 * @brief   Watchdog Interrupt Disable.
 */
void iwdt_Interrupt_Disable(void)
{
    /* enable iwdt interrupt */
    ool_write(PMU_REG_WDT_CTRL, ool_read(PMU_REG_WDT_CTRL) & ~PMU_WDT_IRQ_EN_BIT);
}

/*********************************************************************
 * @fn      iwdt_Set_Count
 *
 * @brief   Set watchdog count. 
 *
 * @param   iwdtCount: watchdog count (0x00000000 ~ 0xFFFFFFFF).
 */
void iwdt_Set_Count(uint32_t iwdtCount)
{
    /* set iwdt Count value */
    ool_write32(PMU_REG_WDT_LEN_0, iwdtCount);
}

/*********************************************************************
 * @fn      iwdt_Set_Timeout
 *
 * @brief   Set watchdog Timeout. Timeout trigger the system reset.
 *          Attention: Timeout Set to 0 the system will not reset.
 *
 * @param   WdtCount: watchdog Timeout value (0x0000 ~ 0xFFFF).
 */
void iwdt_Set_Timeout(uint16_t iwdtTimeout)
{
    /* set iwdt timeout value */
    ool_write16(PMU_REG_WDT_TOUT_COUNTER_0, iwdtTimeout);
}

