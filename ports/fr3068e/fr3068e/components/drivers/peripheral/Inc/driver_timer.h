/*
  ******************************************************************************
  * @file    driver_timer.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of TImer HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_TIMER_H__
#define __DRIVER_TIMER_H__

#include "fr30xx.h"

/** @addtogroup Timer_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Timer Control Register */
typedef struct
{
    uint32_t ENABLE   : 1;
    uint32_t MODE     : 1;
    uint32_t INT_MASK : 1;
    uint32_t rsv_0    : 29;
}REG_Control_t;


/* -------------------------------------------------*/
/*                   Timer Register                 */
/* -------------------------------------------------*/
typedef struct 
{
    volatile uint32_t         LoadCount;        /* Offset 0x00 */
    volatile uint32_t         CurrentValue;     /* Offset 0x04 */
    volatile REG_Control_t    Control;          /* Offset 0x08 */
    volatile uint32_t         IntClear;         /* Offset 0x0C */
    volatile uint32_t         IntStatus;        /* Offset 0x10 */
}struct_Timer_t;

#define Timer0    ((struct_Timer_t *)(TIM0_BASE))
#define Timer1    ((struct_Timer_t *)(TIM1_BASE))
#define Timer2    ((struct_Timer_t *)(TIM2_BASE))
#define Timer3    ((struct_Timer_t *)(TIM3_BASE))
#define Timer4    ((struct_Timer_t *)(TIM4_BASE))
#define Timer5    ((struct_Timer_t *)(TIM5_BASE))

#define DSP_Timer0    ((struct_Timer_t *)(DSP_TIM0_BASE))
#define DSP_Timer1    ((struct_Timer_t *)(DSP_TIM1_BASE))

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/* timer_init */
void timer_init(struct_Timer_t *TIMERx, uint32_t fu32_LoadCount);

/* timer_int_enable */
/* timer_int_disable */
/* timer_int_clear */
/* timer_int_status */
void timer_int_enable(struct_Timer_t *TIMERx);
void timer_int_disable(struct_Timer_t *TIMERx);
void timer_int_clear(struct_Timer_t *TIMERx);
bool timer_int_status(struct_Timer_t *TIMERx);

/* timer_start */
/* timer_stop */
void timer_start(struct_Timer_t *TIMERx);
void timer_stop(struct_Timer_t *TIMERx);

/* timer_get_CurrentCount */
uint32_t timer_get_CurrentCount(struct_Timer_t *TIMERx);

#endif
