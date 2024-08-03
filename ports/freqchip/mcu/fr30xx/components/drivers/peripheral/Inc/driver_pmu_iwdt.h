/*
  ******************************************************************************
  * @file    driver_pmu_iwdt.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of PMU IWDT HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_PMU_IWDT_H__
#define __DRIVER_PMU_IWDT_H__

#include "fr30xx.h"

/** @addtogroup IWDT_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization/config Section Start ################################ */

enum IWDT_INT_t 
{
    WDT_INT_ENABLE  = 0x08,
    WDT_INT_DISABLE = 0x00,
};

/**
  * @brief  iwdt Initialization Structure definition
  */
typedef struct 
{
    uint32_t iwdt_Count;         /* The watchdog initializes the count value.
                                    An interrupt can be generated when the count value is reached.
                                    This parameter can be a 32-bit Size.  */

    uint16_t iwdt_Timeout;       /* The watchdog Timeout reset count value.
                                    When the count value is reached, the timeout counter is starting. 
                                    Timeout triggers the system reset.
                                    Attention: Timeout Set to 0 the system will not reset.
                                    This parameter can be a 16-bit Size */
    
    uint32_t iwdt_int_Enable;    /* This parameter can be a value of @ref IWDT_INT_t */
}iwdt_Init_t;

/* ################################ Initialization/config Section END ################################## */
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/* iwdt_init */
void iwdt_init(iwdt_Init_t Init);

/* iwdt_Enable */
/* iwdt_Disable */
void iwdt_Enable(void);
void iwdt_Disable(void);

/* iwdt_Refresh */
void iwdt_Refresh(void);

/* iwdt_Interrupt_Enable */
/* iwdt_Interrupt_Disable */
void iwdt_Interrupt_Enable(void);
void iwdt_Interrupt_Disable(void);

/* iwdt_Set_Count */
void iwdt_Set_Count(uint32_t iwdtCount);

/* iwdt_Set_Timeout */
void iwdt_Set_Timeout(uint16_t iwdtTimeout);

#endif


