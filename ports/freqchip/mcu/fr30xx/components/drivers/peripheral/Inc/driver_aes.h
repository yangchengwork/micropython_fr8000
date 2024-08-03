/*
  ******************************************************************************
  * @file    driver_aes.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of aes module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_AES_H__
#define __DRIVER_AES_H__

#include "fr30xx.h"

/** @addtogroup AES_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Control Register for AES */
typedef struct
{
    uint32_t STU_MODE      : 3;
    uint32_t CALC_MODE     : 2;
    uint32_t KEY_MODE      : 2;
    uint32_t RSV           : 25;    
} REG_AES_CTRL_t;

/* Interrupt Control Register for AES */
typedef struct
{
    uint32_t INTEN       : 1;
    uint32_t INTCLR      : 1;
    uint32_t RSV         : 30;
} REG_AES_INT_CTRL;

/* Interrupt configuration Register for AES */
typedef struct
{
    uint32_t CALC_INTEN            : 1;
    uint32_t BYTE_LEN_ERR_INTEN    : 1;
    uint32_t RSV                   : 30;
} REG_AES_INT_CFG;

/* FIFO configuration Register for AES */
typedef struct
{
    uint32_t WFIFO_ALMOST_EMPTY_LEVEL : 6;
    uint32_t RFIFO_ALMOST_FULL_LEVEL  : 6;
    uint32_t RSV                      : 20;
} REG_AES_FIFO_CFG;

typedef struct 
{
    volatile REG_AES_CTRL_t            AES_CTRL;           /* Offset 0x00 */
    volatile uint32_t                  DATA_CONSTR;        /* Offset 0x04 */
    volatile REG_AES_INT_CTRL          INT_CTRL;           /* Offset 0x08 */
    volatile REG_AES_INT_CFG           INT_CFG;            /* Offset 0x0C */
    volatile REG_AES_FIFO_CFG          FIFO_CFG;           /* Offset 0x10 */   
    volatile uint32_t                  KEY_7;              /* Offset 0x14 */ 
    volatile uint32_t                  KEY_6;              /* Offset 0x18 */ 
    volatile uint32_t                  KEY_5;              /* Offset 0x1C */ 
    volatile uint32_t                  KEY_4;              /* Offset 0x20 */ 
    volatile uint32_t                  KEY_3;              /* Offset 0x24 */ 
    volatile uint32_t                  KEY_2;              /* Offset 0x28 */   
    volatile uint32_t                  KEY_1;              /* Offset 0x2C */  
    volatile uint32_t                  KEY_0;              /* Offset 0x30 */   
    volatile uint32_t                  IV_3;               /* Offset 0x34 */
    volatile uint32_t                  IV_2;               /* Offset 0x38 */
    volatile uint32_t                  IV_1;               /* Offset 0x3C */
    volatile uint32_t                  IV_0;               /* Offset 0x40 */   
    volatile uint32_t                  rsv0[3];
    volatile uint32_t                  STATUS0;            /* Offset 0x50 */ 
    volatile uint32_t                  STATUS1;            /* Offset 0x54 */
    volatile uint32_t                  rsv1[40];   
    volatile uint32_t                  FIFO_DATA;          /* Offset 0xF8 */      
    volatile uint32_t                  Command;            /* Offset 0xFC */    
}struct_SEC_AES_t;

#define SEC_AES    ((struct_SEC_AES_t *)(AES_BASE))
/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup AES_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

typedef enum
{
    AES_CALC_DONE              = 0x01,
    AES_BYTE_LEN_ERR           = 0x02,
    AES_KEY_GEN_DONE           = 0x04,  
}enum_AES_FLAG_STATUS_t;

typedef enum
{
    AES_TX_FIFO_EMPTY          = 0x01,
    AES_TX_FIFO_FULL           = 0x02,
    AES_TX_FIFO_ALMOST_EMPTY   = 0x04,  
    AES_RX_FIFO_EMPTY          = 0x10, 
    AES_RX_FIFO_FULL           = 0x20,     
    AES_RX_FIFO_ALMOST_FULL    = 0x40, 
}enum_AES_FIFO_STATUS_t;

typedef enum
{
    AES_128,
    AES_192,
    AES_256,
}enum_AES_KEY_MODE_t;

typedef enum
{
    AES_DISABLE,    
    AES_ENCRYPT,
    AES_DECRYPE,
}enum_AES_CALC_MODE_t;

typedef enum
{
    AES_ECB,
    AES_CBC,
    AES_CFB,
    AES_OFB,
    AES_CTR,
    AES_PCBC,
}enum_AES_STU_MODE_t;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define SRESET   0x00
#define KEY_RDY  0x01
#define STATE_FLAG_CLR  0x02
/* get aes status */
#define __AES_IS_FIFO_STATUS(__STATUS__)          (SEC_AES->STATUS1 & __STATUS__)
#define __AES_IS_FLAG_STATUS(__STATUS__)          (SEC_AES->STATUS0 & __STATUS__)                                                 

/* Exported functions --------------------------------------------------------*/

/* AES config */
void aes_config(enum_AES_KEY_MODE_t fe_Key_Mode, enum_AES_STU_MODE_t fe_Stu_Mode);

/* AES set key/iv */
void aes_set_encrypt_key(uint8_t *key);
void aes_set_encrypt_iv(uint8_t *iv);

/* AES encrypt/decrypt */
void aes_encrypt(uint8_t *fp_Data_In, uint32_t fu32_Size, uint8_t *fp_Data_Out);
void aes_decrypt(uint8_t *fp_Data_In, uint32_t fu32_Size, uint8_t *fp_Data_Out);

#endif
