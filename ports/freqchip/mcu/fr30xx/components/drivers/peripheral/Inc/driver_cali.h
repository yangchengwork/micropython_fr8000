/*
  ******************************************************************************
  * @file    driver_cali.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of Calibration HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_CALI_H__
#define __DRIVER_CALI_H__

#include "fr30xx.h"

/** @addtogroup CALI_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Control Register */
typedef struct
{
    uint32_t EN         : 1;
    uint32_t UP_MODE    : 1;
    uint32_t rsv_0      : 30;
}REG_CALI_CTRL_t;

/* ------------------------------------------------*/
/*                   UART Register                 */
/* ------------------------------------------------*/
typedef struct 
{
    volatile REG_CALI_CTRL_t    CTRL;    /* Offset 0x00 */
    volatile uint32_t           DONE;    /* Offset 0x04 */
    volatile uint32_t           INT_EN;  /* Offset 0x08 */  
    volatile uint32_t           INT_STA; /* Offset 0x0C */ 
    volatile uint32_t           LEN;     /* Offset 0x10 */  
    volatile uint32_t           RESULT;  /* Offset 0x14 */  
}struct_CALI_t;

#define CALI        ((struct_CALI_t *)CALIB_BASE)
/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup CALI_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization Config Section Start ################################ */

/* FCR BIT position */
typedef enum
{
    CALI_UP_MODE_KEEP   = 0x00,     /*!< return the oldest unread data */
    CALI_UP_MODE_NORMAL = 0x01,     /*!< return the latest calibration result */
}enum_CALI_UP_MODE_t;

/*
 * @brief  Calibration handle Structure definition
 */
typedef struct __Cali_HandleTypeDef
{
    enum_CALI_UP_MODE_t         mode;                           /*!< Calibration result fetch mode */
    uint16_t                    rc_cnt;                         /*!< how many RC cycles used to calibrate */

    void (*DoneCallback)(struct __Cali_HandleTypeDef *hcali,    /*!< Calibration Done Callback */
                                uint32_t result);
}CALI_HandleTypeDef;

/* ################################ InitializationbConfig Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* __CALI_ENABLE */
/* __CALI_DISABLE */
#define __CALI_ENABLE()             (CALI->CTRL.EN = 0x01)
#define __CALI_DISABLE()            (CALI->CTRL.EN = 0x00)

/* __CALI_UP_MODE_SET */
#define __CALI_UP_MODE_SET(m)       (CALI->CTRL.UP_MODE = m)

/* __CALI_INT_ENABLE */
/* __CALI_INT_DISABLE */
#define __CALI_INT_ENABLE()         (CALI->INT_EN = 0x01)
#define __CALI_INT_DISABLE()        (CALI->INT_EN = 0x00)

/* __CALI_INT_CLR */
#define __CALI_INT_CLR()            (CALI->INT_STA = 0x01)

/* __CALI_IS_DONE */
#define __CALI_IS_DONE()            (CALI->DONE == 0x01)

/* __CALI_CNT_SET */
#define __CALI_CNT_SET(v)           (CALI->LEN = v)

/* __CALI_RESULT_GET */
#define __CALI_RESULT_GET()         (CALI->RESULT)

/* Exported functions --------------------------------------------------------*/

/* cali_IRQHandler */
void cali_IRQHandler(CALI_HandleTypeDef *hcali);

/* cali_init */
void cali_init(CALI_HandleTypeDef *hcali);

/* cali_start */
uint32_t cali_start(CALI_HandleTypeDef *hcali);
/* cali_start_IT */
void cali_start_IT(CALI_HandleTypeDef *hcali);

/* cali_stop */
void cali_stop(CALI_HandleTypeDef *hcali);

/* cali_calc_rc_freq */
uint32_t cali_calc_rc_freq(CALI_HandleTypeDef *hcali, uint32_t result);

#endif  // __DRIVER_CALI_H__
