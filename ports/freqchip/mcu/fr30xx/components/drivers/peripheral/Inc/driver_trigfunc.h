/*
  ******************************************************************************
  * @file    driver_trigfunc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of trigfunc module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_TRIGFUNC_H__
#define __DRIVER_TRIGFUNC_H__

#include "fr30xx.h"

/** @addtogroup TRIGFUNC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

#define TRIGFUNC_INTRCR (0x01)

typedef struct 
{
    volatile uint32_t       TRIGFUNC_CTRL;                 /* Offset 0x00 */
    volatile uint32_t       TRIGFUNC_INTR;                 /* Offset 0x04 */
    volatile uint32_t       TRIGFUNC_ARG1_IN;              /* Offset 0x08 */
    volatile uint32_t       TRIGFUNC_ARG2_IN;              /* Offset 0x0c */
    volatile uint32_t       TRIGFUNC_RESULT1_OUT;          /* Offset 0x10 */
    volatile uint32_t       TRIGFUNC_RESULT2_OUT;          /* Offset 0x14*/
    volatile uint32_t       TRIGFUNC_STATUS;               /* Offset 0x18 */
}struct_TRIGFUNC_t;

#define TRIGFUNC              ((struct_TRIGFUNC_t *)TRI_FUNC_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup TRIGFUNC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization_Config Section Start ################################ */

typedef enum 
{
    TRIG_CAL_SIN_AND_COS     = 0x0u,
    TRIG_CAL_TAN             = 0x1u,
    TRIG_CAL_ARCTAN_X_Y      = 0x2u,
    TRIG_CAL_ARCTAN_X        = 0x3u,
}enum_TRIGFUNC_MODE_SEL_t ;

typedef enum 
{
    BYTE_1      = 0x000u,
    BYTE_2      = 0x100u,
    BYTE_3      = 0x200u,
    BYTE_ALL    = 0x300u,
}enum_NBYTE_SEL_t;

/* ################################ Initialization?Config Section END ################################## */
/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/

#define QUANTIZATION_PARAMETER                    (double)((0x10000) / 2)

#define __TRIGFUNC_CAL_IS_DONE_STATUS()           (TRIGFUNC->TRIGFUNC_STATUS)
#define __TRIGFUNC_IS_MODE()                      (TRIGFUNC->TRIGFUNC_CTRL)
#define __TRIGFUNC_CAL_IS_INT_STATUS()            (TRIGFUNC->TRIGFUNC_INTR & 0x100)

/* Exported functions ---------------------------------------------------------*/

/* trigfunc_sin */
/* trigfunc_cos */
/* trigfunc_tan */
/* trigfunc_atan */
double trigfunc_sin(double fe_argin);
double trigfunc_cos(double fe_argin);
double trigfunc_tan(double fe_argin);
double trigfunc_atan(double fe_argin);

#endif
