/*
  ******************************************************************************
  * @file    driver_sha.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of sha module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SHA_H__
#define __DRIVER_SHA_H__

#include "fr30xx.h"

/** @addtogroup SHA_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/*SHA CTRL REG  0x00*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t MODE                   : 3;//001->SHA-1;010->SHA-256;011->SHA-224;100->SHA-512;101->SHA-384;110->SHA-512/256;111->SHA-512/224
        uint32_t INIT_EN                : 1;//set this bit to encode thhe messgae with the initial value of A-H(A-E when mask= 010)
        uint32_t ISR_EN                 : 1;//interrupt enable
        uint32_t ENDIAN_MODE            : 1;//message endian mode 0->big endian 1->little endian
        uint32_t CALCULATE              : 1;//cpu write this bit to enable calculate.read this bit to verify whether the encoding is complete
        uint32_t RSV                    : 25;
    } Bits;
} REG_SHA_CTRL_t;

/*SHA INT STATE REG  0x04*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INT_DONE               : 1;//this bit is set by SHA finishing encoding the message and writing the digest to the base address
        uint32_t INT_ERROR              : 1;//this bit is set by SHA select error mode
        uint32_t RSV                    : 30;
    } Bits; 
} REG_SHA_INT_STATE_t;

/* ----------------------------------------------*/
/*                 SHA Registers                 */
/* ----------------------------------------------*/
typedef struct 
{
    volatile REG_SHA_CTRL_t                         SHA_CTRL;             /* Offset 0x00 */
    volatile REG_SHA_INT_STATE_t                    SHA_INT_STATE;        /* Offset 0x04 */
    volatile uint32_t                               HASH_VAL_L[8];        /* Offset 0x08 - 0x24*/
    volatile uint32_t                               HASH_VAL_H[8];        /* Offset 0x28 - 0x44*/
    volatile uint32_t                               DATA_1[16];               /* Offset 0x48 -0x84 */
    volatile uint32_t                               DATA_2[16];               /* Offset 0x88-0xb4*/
}struct_SEC_SHA_t;

#define SEC_SHA_OFFSET        0x1000
#define SEC_SHA              ((struct_SEC_SHA_t *)(SEC_BASE + SEC_SHA_OFFSET))

/* ################################ Register Section END ################################ */
/**
  * @}
  */

/** @addtogroup ADC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization, Config Section Start ################################ */
typedef enum{
    SHA_1          = 1,
    SHA_256        = 2,
    SHA_224        = 3,
    SHA_512        = 4,
    SHA_384        = 5,
    SHA_512_OR_256 = 6,
    SHA_512_OR_224 = 7
}enum_sha_mode_t;

typedef enum{
    SHA_BIG_ENDIAN    = 0,
    SHA_LITTLE_ENDIAN = 1
}enum_sha_endian_t;

#define SHA_256_BLOCK_SIZE                  (64)
#define SHA_512_BLOCK_SIZE                  (128)

/* ################################ Initialization, Config Section END ################################ */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define __SHA_GET_INT_DONE_FALG()           (SEC_SHA->SHA_INT_STATE.Bits.INT_DONE)
#define __SHA_INT_ERROR()                   (SEC_SHA->SHA_INT_STATE.Bits.INT_ERROR == 1)


/* Exported functions --------------------------------------------------------*/

/* sha init */
void sha_init(uint8_t Mode);
/* sha updata */
void sha_update(uint8_t *fp8_Data, uint32_t fu32_Size);
/* sha_final */
void sha_final(uint8_t *DataOut);

#endif
