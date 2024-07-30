/*
  ******************************************************************************
  * @file    driver_pwm.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of PWM HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_PWM_H__
#define __DRIVER_PWM_H__

#include "fr30xx.h"

/** @addtogroup PWM_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* PWM Output ctrl register */
typedef struct 
{
    uint32_t OutputEN    : 16;
    uint32_t Output_ctrl : 16;
}REG_PWMOutput_t;

/* Posedge、Negedeg register */
typedef struct 
{
    uint32_t Posedge;
    uint32_t Negedeg;
}REG_PWMedge_t;

/* capture control register */
typedef struct 
{
    uint32_t Capture_Mode : 8;
    uint32_t Capture_EN   : 8;
    uint32_t rsv_0        : 16;
}REG_CaptureCtrl_t;

/* PWM Update control register */
typedef struct 
{
    uint32_t PWM_Update : 16;
    uint32_t PWM_Status : 16;
}REG_PWMUpdate_t;

/* Prescale、Period register */
typedef struct 
{
    uint32_t Prescale;
    uint32_t Period;
}REG_PWMFrequency_t;

/* -----------------------------------------------*/
/*                   PWM Register                 */
/* -----------------------------------------------*/
typedef struct 
{
    volatile uint32_t           rsv_0;
    volatile REG_PWMOutput_t    OutputEN;           /* Offset 0x04 */
    volatile uint32_t           ChannelEN;          /* Offset 0x08 */
    volatile uint32_t           rsv_1;
    volatile REG_PWMedge_t      Edge[16];           /* Offset 0x10 ~ 0x8C */
    volatile uint32_t           OutputSelect;       /* Offset 0x90 */
    volatile uint32_t           CapturePrescale;    /* Offset 0x94 */
    volatile uint32_t           CaptureStatus;      /* Offset 0x98 */
    volatile uint32_t           CaptureINTEN;       /* Offset 0x9C */
    volatile REG_CaptureCtrl_t  CaptureCtrl;        /* Offset 0xA0 */
    volatile uint32_t           CaptureValue[8];    /* Offset 0xA4 ~ 0xE0 */
    volatile uint32_t           rsv_2[8];
    volatile REG_PWMUpdate_t    Update;             /* Offset 0xE4 */
    volatile uint32_t           rsv_3[2];
    volatile uint32_t           OutputValue;        /* Offset 0xF0 */
    volatile uint32_t           rsv_4;
    volatile uint32_t           InverterEN;         /* Offset 0xF8 */
    volatile uint32_t           CNT_EN;             /* Offset 0xFC */
    volatile REG_PWMFrequency_t Frequency[16];      /* Offset 0x100 ~ 0x17C */
}struct_PWM_t;

#define PWM0       ((struct_PWM_t *)PWM0_BASE)
#define PWM1       ((struct_PWM_t *)PWM1_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup PWM_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization、Config Section Start ################################ */

/* PWM Channel */
typedef enum
{
    PWM_CHANNEL_0  = 0x0001,
    PWM_CHANNEL_1  = 0x0002,
    PWM_CHANNEL_2  = 0x0004,
    PWM_CHANNEL_3  = 0x0008,
    PWM_CHANNEL_4  = 0x0010,
    PWM_CHANNEL_5  = 0x0020,
    PWM_CHANNEL_6  = 0x0040,
    PWM_CHANNEL_7  = 0x0080,
    PWM_CHANNEL_8  = 0x0100,
    PWM_CHANNEL_9  = 0x0200, 
    PWM_CHANNEL_10 = 0x0400,
    PWM_CHANNEL_11 = 0x0800,
    PWM_CHANNEL_12 = 0x1000,
    PWM_CHANNEL_13 = 0x2000,
    PWM_CHANNEL_14 = 0x4000,
    PWM_CHANNEL_15 = 0x8000,
}enum_PWMChannel_t;

/* Inverter Enable */
typedef enum
{
    Inverter_Enable,     /* output Inverter enable  */
    Inverter_Disable,    /* output Inverter disable */
}enum_InverterEN_t;

/* Capture_Prescale */
typedef enum
{
    CAPTURE_DIV_1,
    CAPTURE_DIV_2,
    CAPTURE_DIV_4,
    CAPTURE_DIV_8,
    CAPTURE_DIV_16,
    CAPTURE_DIV_32,
    CAPTURE_DIV_64,
    CAPTURE_DIV_128,
    CAPTURE_DIV_256,
    CAPTURE_DIV_512,
    CAPTURE_DIV_1024,
    CAPTURE_DIV_2048,
}enum_CapturePrescale_t;

/* Capture Mode */
typedef enum
{
    MODE_LOOP,      /* Loop    trigger */
    MODE_SINGLE,    /* Single  trigger */
}enum_CaptureMode_t;

/*
 * @brief  PWM mode config parameter
 */
typedef struct 
{
    uint16_t Prescale;      /* Clock = APB_Clock / Prescale */
    uint16_t Period;        /* Period = Clock * PWM_Period  */

    uint16_t Posedge;       /* The position of the rising  edge in the period */
    uint16_t Negedge;       /* The position of the falling edge in the period */
}struct_PWM_Config_t;

/*
 * @brief  PWM complementary config parameter
 */
typedef struct 
{
    uint16_t Prescale;         /* Clock = APB_Clock / Prescale */
    uint16_t Period;           /* Period = Clock * PWM_Period  */

    uint16_t DutyCycle;        /* Low level hold time in one period */
    
    uint16_t MianDeadTime;     /* Mian Channel dead-time */
    uint16_t CompDeadTime;     /* complementary Channel dead-time */
}struct_PWM_Complementary_Config_t;

/*
 * @brief  Capture mode config parameter
 */
typedef struct 
{
    uint32_t CapturePrescale;    /* This parameter can be a value of @ref enum_CapturePrescale_t */
    uint32_t CaptureMode;        /* This parameter can be a value of @ref enum_CaptureMode_t */
}struct_Capture_Config_t;


/* ################################ Initialization、Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* PWM mode. output inverter Enable/Disable */
#define __PWM_INVERTER_ENABLE(__PWMx__, __CHANNEL__)                   (__PWMx__->InverterEN |=  (__CHANNEL__))
#define __PWM_INVERTER_DISABLE(__PWMx__, __CHANNEL__)                  (__PWMx__->InverterEN &= ~(__CHANNEL__))

/* Capture mode. Capture interrupt Enable/Disable/Clear */
#define __PWM_CAPTURE_INT_ENABLE(__PWMx__, __CHANNEL__)                (__PWMx__->CaptureINTEN  |=  (__CHANNEL__))
#define __PWM_CAPTURE_INT_DISABLE(__PWMx__, __CHANNEL__)               (__PWMx__->CaptureINTEN  &= ~(__CHANNEL__))
#define __PWM_CAPTURE_INT_CLEAR(__PWMx__, __CHANNEL__)                 (__PWMx__->CaptureStatus |=  (__CHANNEL__))


/* Exported functions --------------------------------------------------------*/

/*------------------------------------------------------------*/
/*------------------     PWM Mode functions ------------------*/
/*------------------ PWM_DAC Mode functions ------------------*/
/*------------------------------------------------------------*/
/* pwm_config */
void pwm_config(struct_PWM_t *PWMx, uint16_t fu16_channel, struct_PWM_Config_t fstr_Config);

/* pwm_complementary_config */
bool pwm_complementary_config(struct_PWM_t *PWMx, uint16_t fu16_MainChannel, uint16_t ComplementaryChannel, struct_PWM_Complementary_Config_t fstr_Config);

/* pwm_output_enable/disable */
void pwm_output_enable(struct_PWM_t *PWMx, uint16_t fu16_channel);
void pwm_output_disable(struct_PWM_t *PWMx, uint16_t fu16_channel);

/* pwm_output_status */
bool pwm_output_status(struct_PWM_t *PWMx, enum_PWMChannel_t fe_channel);

/* pwm_output_updata */
void pwm_output_updata(struct_PWM_t *PWMx, uint16_t fu16_channel);

/*------------------------------------------------------------*/
/*------------------ Capture Mode functions ------------------*/
/*------------------------------------------------------------*/
/* pwm_capture_config */
void pwm_capture_config(struct_PWM_t *PWMx, uint16_t fu16_channel, struct_Capture_Config_t fstr_Config);

/* capture_enable/disable */
void pwm_capture_enable(struct_PWM_t *PWMx, uint16_t fu16_channel);
void pwm_capture_disable(struct_PWM_t *PWMx, uint16_t fu16_channel);

/* pwm_capture_status */
bool pwm_capture_status(struct_PWM_t *PWMx, enum_PWMChannel_t fe_channel);

/* pwm_capture_status_clear */
void pwm_capture_status_clear(struct_PWM_t *PWMx, enum_PWMChannel_t fe_channel);

/* pwm_capture_value */
uint32_t pwm_capture_value(struct_PWM_t *PWMx, enum_PWMChannel_t fe_channel);

#endif
