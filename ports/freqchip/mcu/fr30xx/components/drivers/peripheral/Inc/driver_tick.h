/*
  ******************************************************************************
  * @file    driver_tick.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of System Tick HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_TICK_H__
#define __DRIVER_TICK_H__

#include "fr30xx.h"

/** @addtogroup Tick_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Tick Control Register */
typedef struct
{
    uint32_t SMP        : 1;
    uint32_t UPD        : 1;
    uint32_t CMP_EN     : 1;
    uint32_t RST        : 1;
    uint32_t rsv_0      : 28;
}REG_TickControl_t;

/* Tick Sleep Control Register */
typedef struct
{
    uint32_t SLP_ON         : 1;
    uint32_t SLP_CORR_EN    : 1;
    uint32_t DELTA          : 1;
    uint32_t rsv_0          : 29;
}REG_TickSleepControl_t;

/* Tick Interrupt Register */
typedef union
{
    uint32_t Word;
    struct {
        uint32_t SLP    : 1;
        uint32_t TGT    : 1;
        uint32_t rsv_0  : 30;
    }Bits;
}REG_TickInt_t;

typedef struct 
{
    volatile REG_TickControl_t          CTL;        /* Offset 0x00 */
    volatile REG_TickSleepControl_t     SLP_CTL;    /* Offset 0x04 */
    volatile uint32_t                   CLK_SMP;    /* Offset 0x08 */
    volatile uint32_t                   FINE_SMP;   /* Offset 0x0C */
    volatile uint32_t                   CLK_CORR;   /* Offset 0x10 */
    volatile uint32_t                   FINE_CORR;  /* Offset 0x14 */
    volatile uint32_t                   CLK_TGT;    /* Offset 0x18 */
    volatile uint32_t                   FINE_TGT;   /* Offset 0x1C */
    volatile uint32_t                   CLK_UPD;    /* Offset 0x20 */
    volatile REG_TickInt_t              INT_CTL;    /* Offset 0x24 */
    volatile REG_TickInt_t              INT_STA;    /* Offset 0x28 */
    volatile REG_TickInt_t              INT_RAW;    /* Offset 0x2C */
}struct_Tick_t;

#define Tick    ((struct_Tick_t *)(SYSTEM_TIMER_BASE))

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup Tick_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

/* Tick Interrupt Type */
typedef enum  
{
    TICK_INT_TYPE_SLP = (1<<0),
    TICK_INT_TYPE_TGT = (1<<1),
}enum_TickIntType_t;

/*
 * @brief  Tick handle Structure definition
 */
typedef struct
{
    void (*TickTargetCallback)(void);       /*!< Tick reach target Callback */
    void (*TickSleepCallback)(void);        /*!< wake up frome sleep Callback */
}TICK_HandleTypeDef;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
#define TICK_FINE_VALUE_MAX                 (1000)

/* Exported functions --------------------------------------------------------*/

void tick_IRQHandler(TICK_HandleTypeDef *handle);

void tick_init(TICK_HandleTypeDef *handle);

void tick_get(uint32_t *clk, uint32_t *fine);
void tick_set_target(uint32_t clk, uint32_t fine);
void tick_set_target_IT(uint32_t clk, uint32_t fine);
void tick_start_corr(uint32_t clk, uint32_t fine);

#endif
