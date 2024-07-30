/*
  ******************************************************************************
  * @file    driver_trng.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of TRNG HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_TRNG_H__
#define __DRIVER_TRNG_H__

#include "fr30xx.h"

/** @addtogroup TRNG_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* ------------------------------------------------*/
/*                   TRNG Register                 */
/* ------------------------------------------------*/
typedef struct 
{
    volatile uint32_t                 rsv_0[64];         /* Offset 0x000 ~ 0x0FC */
    volatile uint32_t                 TRNG_IMR;            /* Offset 0x100 */
    volatile uint32_t                 TRNG_ISR;            /* Offset 0x104 */
    volatile uint32_t                 TRNG_ICR;            /* Offset 0x108 */
    volatile uint32_t                 TRNG_Config;         /* Offset 0x10C */
    volatile uint32_t                 TRNG_Valid;          /* Offset 0x110 */
    volatile uint32_t                 TRNG_Data[6];        /* Offset 0x114 ~ 0x128 */
    volatile uint32_t                 TRNG_SrcEN;          /* Offset 0x12C */
    volatile uint32_t                 TRNG_SAMPLE_CNT1;    /* Offset 0x130 */
    volatile uint32_t                 TRNG_AUTOCORR;       /* Offset 0x134 */
    volatile uint32_t                 TRNG_DebugControl;   /* Offset 0x138 */
    volatile uint32_t                 rsv_1;               /* Offset 0x13C */
    volatile uint32_t                 TRNG_Reset;          /* Offset 0x140 */
    volatile uint32_t                 rsv_2[29];           /* Offset 0x144 ~ 0x1B4 */
    volatile uint32_t                 TRNG_Busy;           /* Offset 0x1B8 */
    volatile uint32_t                 TRNG_ResetBit;       /* Offset 0x1BC */
    volatile uint32_t                 rsv_3[8];            /* Offset 0x1C0 ~ 0x1DC */
    volatile uint32_t                 TRNG_BIST_CNTR0;     /* Offset 0x1E0 */
    volatile uint32_t                 TRNG_BIST_CNTR1;     /* Offset 0x1E4 */
    volatile uint32_t                 TRNG_BIST_CNTR2;     /* Offset 0x1E8 */
}struct_TRNG_t;

#define TRNG    ((struct_TRNG_t *)TRNG_BASE)
/* ################################ Register Section END ################################## */
/**
  * @}
  */



/** @addtogroup TRNG_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

#define TRNG_STATUS_EHR_VALID       (0x01)
#define TRNG_STATUS_AUTOCORR_ERR    (0x02)
#define TRNG_STATUS_CRNGT_ERR       (0x04)
#define TRNG_STATUS_VN_ERR          (0x08)

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/

/* trng_init */
void trng_init(void);

/* trng_read_rand_num */
void trng_read_rand_num(uint8_t *fp_buffer, uint8_t length);

#endif
