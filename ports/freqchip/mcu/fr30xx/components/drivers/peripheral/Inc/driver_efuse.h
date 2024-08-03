/*
  ******************************************************************************
  * @file    driver_efuse.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of eFuse HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_EFUSE_H__
#define __DRIVER_EFUSE_H__

#include "fr30xx.h"

/** @addtogroup eFuse_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Control Register */
/* bit2: Done       */
/* bit1: Read/Write */
/* bit0: GO         */
#define EFUSE_SISO_READ_MODE     (0x01)
#define EFUSE_SISO_WRITE_MODE    (0x03)
#define EFUSE_SISO_CHECK_DONE    (0x04)

/* ------------------------------------------------*/
/*               eFuse SISO Register               */
/* ------------------------------------------------*/
typedef struct 
{
    volatile uint32_t        eFuse_Ctrl;      /* Offset 0x00 */
    volatile uint32_t        eFuse_Timing;    /* Offset 0x04 */
    volatile uint32_t        eFuse_Data0;     /* Offset 0x08 */
    volatile uint32_t        eFuse_Data1;     /* Offset 0x0C */
    volatile uint32_t        eFuse_Data2;     /* Offset 0x10 */
}struct_eFuse_SISO_t;

#define EFUSE_SISO    ((struct_eFuse_SISO_t *)EFUSE_SISO_BASE)


/* Control Register */
/* bit4: Done       */
/* bit3: Read       */
/* bit2: Write      */
/* bit1: AVDDEN     */
/* bit0: GO         */
#define EFUSE_PIPO_CHECK_DONE    (0x10)
#define EFUSE_PIPO_READ_MODE     (0x08)
#define EFUSE_PIPO_WRITE_MODE    (0x04)
#define EFUSE_PIPO_AVDDEN        (0x02)
#define EFUSE_PIPO_GO            (0x01)

/* ------------------------------------------------*/
/*               eFuse PIPO Register               */
/* ------------------------------------------------*/
typedef struct 
{
    volatile uint32_t        eFuse_Ctrl;      /* Offset 0x00 */
    volatile uint32_t        eFuse_Length;    /* Offset 0x04 */
    volatile uint32_t        eFuse_Addr;      /* Offset 0x08 */
    volatile uint32_t        eFuse_WData;     /* Offset 0x0C */
    volatile uint32_t        eFuse_RData;     /* Offset 0x10 */
}struct_eFuse_PIPO_t;

#define EFUSE_PIPO0    ((struct_eFuse_PIPO_t *)EFUSE_PIPO0_BASE)
#define EFUSE_PIPO1    ((struct_eFuse_PIPO_t *)EFUSE_PIPO1_BASE)


/* ################################ Register Section END ################################## */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* eFuse_siso_read */
/* eFuse_siso_write */
void eFuse_siso_read(uint32_t *fp_Data);
void eFuse_siso_write(uint32_t *fp_Data);
void eFuse_pipo_read(struct_eFuse_PIPO_t *hpipo, uint8_t fu8_Addr, uint8_t *fp_Data);
void eFuse_pipo_write(struct_eFuse_PIPO_t *hpipo, uint8_t fu8_Addr, uint8_t fu8_Data);

#endif
