/*
  ******************************************************************************
  * @file    driver_crc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of CRC module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_CRC_H__
#define __DRIVER_CRC_H__

#include "fr30xx.h"

/** @addtogroup CRC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

#define CRC_START (0x01)
#define CRC_CLEAR (0x08)

typedef struct 
{
    volatile   uint32_t           CRC_CTRL;           /* Offset 0x00 */
    volatile   uint32_t           CRC_STATUS;         /* Offset 0x04 */
    volatile   uint32_t           CRC_FIFO_DATA;      /* Offset 0x08 */
    volatile   uint32_t           CRC_RESULT;         /* Offset 0x0C */
}struct_CRC_t;

#define CRC        ((struct_CRC_t *)CRC_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup CRC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

typedef enum
{
    CRC_INITVALUE_0          = 0x08u,
    CRC_INITVALUE_1          = 0x18u,   
    
    CRC_MULTINOMIAL_16_1021  = 0x02u,
    CRC_MULTINOMIAL_16_8005  = 0x04u,
    CRC_MULTINOMIAL_32       = 0x06u,
      
    CRC_INVERT_EN            = 0x60u,

    CRC_XOR_OUT_EN           = 0x80u,
}enum_CRC_Accumulate;

typedef enum
{
    CRC8                =  (CRC_INITVALUE_0),
    CRC8_ROHC           =  (CRC_INITVALUE_1 | CRC_INVERT_EN),
    CRC16_IBM           =  (CRC_INITVALUE_0 | CRC_MULTINOMIAL_16_8005 | CRC_INVERT_EN),
    CRC16_MAXIM         =  (CRC_INITVALUE_0 | CRC_MULTINOMIAL_16_8005 | CRC_INVERT_EN | CRC_XOR_OUT_EN),
    CRC16_USB           =  (CRC_INITVALUE_1 | CRC_MULTINOMIAL_16_8005 | CRC_INVERT_EN | CRC_XOR_OUT_EN),
    CRC16_MODBUS        =  (CRC_INITVALUE_1 | CRC_MULTINOMIAL_16_8005 | CRC_INVERT_EN),
    CRC16_CCITT         =  (CRC_INITVALUE_0 | CRC_MULTINOMIAL_16_1021 | CRC_INVERT_EN),
    CRC16_CCITT_FALSE   =  (CRC_INITVALUE_1 | CRC_MULTINOMIAL_16_1021),
    CRC16_X25           =  (CRC_INITVALUE_1 | CRC_MULTINOMIAL_16_1021 | CRC_INVERT_EN | CRC_XOR_OUT_EN),
    CRC16_XMODEM        =  (CRC_INITVALUE_0 | CRC_MULTINOMIAL_16_1021),
    CRC32               =  (CRC_INITVALUE_1 | CRC_MULTINOMIAL_32 | CRC_INVERT_EN | CRC_XOR_OUT_EN),
    CRC32_MPEG2         =  (CRC_INITVALUE_1 | CRC_MULTINOMIAL_32),
}enum_CRC_MODE_SEL_t;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/* Initial crc with initial value and mode */
void crc_init(enum_CRC_MODE_SEL_t fe_crc_mode);

/* CRC Calculate */
uint32_t crc_Calculate(uint8_t *fp_Data, uint32_t fu32_size);

#endif
