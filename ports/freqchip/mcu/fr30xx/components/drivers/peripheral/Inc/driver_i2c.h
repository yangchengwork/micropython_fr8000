/*
  ******************************************************************************
  * @file    driver_i2c.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of I2C HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_I2C_H__
#define __DRIVER_I2C_H__

#include "fr30xx.h"

/** @addtogroup I2C_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* I2C control Register */
typedef struct
{
    uint32_t MASTER_MODE               : 1;
    uint32_t SPEED                     : 2;
    uint32_t ADDR_SLAVE_10BIT          : 1;
    uint32_t rsv_0                     : 1;
    uint32_t RESTART_EN                : 1;
    uint32_t SLAVE_DISABLE             : 1;
    uint32_t STOP_DET_IF_ADDR_ESSED    : 1;
    uint32_t TX_EMPTY_CTRL             : 1;
    uint32_t RX_FIFO_FULL_HLD_CTRL     : 1;
    uint32_t STOP_DET_IF_MASTER_ACTIVE : 1;
    uint32_t BUS_DETEC_FEATURE_CTRL    : 1;
    uint32_t rsv_1                     : 20;
}REG_I2C_CTRL_t;

/* target address Register */
typedef struct
{
    uint32_t TAR               : 10;
    uint32_t rsv_0             : 1;
    uint32_t SPECIAL           : 1;
    uint32_t ADDR_MASTER_10BIT : 1;
    uint32_t DEVICE_ID         : 1;
    uint32_t rsv_1             : 18;
}REG_TAR_t;

/* DATA CMD Register */
typedef struct
{
    uint32_t DAT             : 8;
    uint32_t CMD             : 1;
    uint32_t STOP            : 1;
    uint32_t RESTART         : 1;
    uint32_t FIRST_DATA_BYTE : 1;
    uint32_t rsv_0           : 20;
}REG_DATA_CMD_t;

/* enable Register */
typedef struct
{
    uint32_t ENABLE             : 1;
    uint32_t ABORT              : 1;
    uint32_t TX_CMD_BLOCK       : 1;
    uint32_t SDA_STUCK_RECOVERY : 1;
    uint32_t rsv_0              : 28;
}REG_ENABLE_t;

/* Status Register */
typedef struct
{
    uint32_t ACTIVITY                : 1;
    uint32_t TFNF                    : 1;
    uint32_t TFE                     : 1;
    uint32_t RFNE                    : 1;
    uint32_t RFF                     : 1;
    uint32_t MST_ACTIVITY            : 1;
    uint32_t SLV_ACTIVITY            : 1;
    uint32_t MST_HOLD_TX_FIFO_EMPTY  : 1;
    uint32_t MST_HOLD_RX_FIFO_FULL   : 1;
    uint32_t SLV_HOLD_TX_FIFO_EMPTY  : 1;
    uint32_t SLV_HOLD_RX_FIFO_FULL   : 1;
    uint32_t SDA_STUCK_NOT_RECOVERED : 1;
    uint32_t rsv_0                   : 20;
}REG_STATUS_t;

/* SDA hold Register */
typedef struct
{
    uint32_t SDA_TX_HOLD : 16;
    uint32_t SDA_RX_HOLD : 8;
    uint32_t rsv_0       : 8;
}REG_SDA_HOLD_t;

/* TX ABRT SOURCE Register */
typedef union
{
    struct 
    {
        uint32_t ABRT_7ADDR_NOACK          : 1;
        uint32_t ABRT_10ADDR1_NOACK        : 1;
        uint32_t ABRT_10ADDR2_NOACK        : 1;
        uint32_t ABRT_TXDATA_NOACK         : 1;
        uint32_t rsv_0                     : 2;
        uint32_t ABRT_SBYTE_ACKDET         : 1;
        uint32_t rsv_1                     : 1;
        uint32_t ABRT_HS_NORSTRT           : 1;
        uint32_t rsv_2                     : 1;
        uint32_t ABRT_10B_RD_NORSTRT       : 1;
        uint32_t ABRT_MASTER_DIS           : 1;
        uint32_t ARB_LOST                  : 1;
        uint32_t ABRT_SLVFLUSH_TXFIFO      : 1;
        uint32_t ABRT_SLV_ARBLOST          : 1;
        uint32_t ABRT_SLVRD_INTX           : 1;
        uint32_t ABRT_USER_ABRT            : 1;
        uint32_t ABRT_SDA_STUCK_AT_LOW     : 1;
        uint32_t rsv_3                     : 1;
        uint32_t ABRT_DEVICE_SLVADDR_NOACK : 1;
        uint32_t ABRT_DEVICE_WRITE         : 1;
        uint32_t rsv_4                     : 2;
        uint32_t TX_FLUSH_CNT              : 9;
    }TX_ABRT_SOURCE_BIT;

    uint32_t TX_ABRT_SOURCE_DWORD;

}REG_TX_ABRT_SOURCE_t;

/* DMA control Register */
typedef struct
{
    uint32_t RDMAE : 1;
    uint32_t TDMAE : 1;
    uint32_t rsv_0 : 30;
}REG_DMA_CR_t;

/* -----------------------------------------------*/
/*                   I2C Register                 */
/* -----------------------------------------------*/
typedef struct 
{
    volatile REG_I2C_CTRL_t        CTRL;                     /* Offset 0x00 */
    volatile REG_TAR_t             TAR;                      /* Offset 0x04 */
    volatile uint32_t              SAR;                      /* Offset 0x08 */
    volatile uint32_t              HS_MADDR;                 /* Offset 0x0C */
    volatile uint32_t              DATA_CMD;                 /* Offset 0x10 */
    volatile uint32_t              rsv_0[2];  
    volatile uint32_t              FS_SCL_HCNT;              /* Offset 0x1C */
    volatile uint32_t              FS_SCL_LCNT;              /* Offset 0x20 */
    volatile uint32_t              rsv_1[2];     
    volatile uint32_t              INT_STAT;                 /* Offest 0x2C */
    volatile uint32_t              INT_MASK;                 /* Offest 0x30 */
    volatile uint32_t              RAW_INT_STAT;             /* Offest 0x34 */
    volatile uint32_t              RX_TL;                    /* Offest 0x38 */
    volatile uint32_t              TX_TL;                    /* Offest 0x3C */
    volatile uint32_t              CLR_INTR;                 /* Offest 0x40 */
    volatile uint32_t              CLR_RX_UNDER;             /* Offest 0x44 */
    volatile uint32_t              CLR_RX_OVER;              /* Offest 0x48 */
    volatile uint32_t              CLR_TX_OVER;              /* Offest 0x4C */
    volatile uint32_t              CLR_RD_REQ;               /* Offest 0x50 */
    volatile uint32_t              CLR_TX_ABRT;              /* Offest 0x54 */
    volatile uint32_t              CLR_RX_DONE;              /* Offest 0x58 */
    volatile uint32_t              CLR_ACTIVITY;             /* Offest 0x5C */
    volatile uint32_t              CLR_STOP_DET;             /* Offest 0x60 */
    volatile uint32_t              CLR_START_DET;            /* Offest 0x64 */
    volatile uint32_t              rsv_2;
    volatile REG_ENABLE_t          ENABLE;                   /* Offest 0x6C */
    volatile REG_STATUS_t          STATUS;                   /* Offest 0x70 */
    volatile uint32_t              TXFLR;                    /* Offest 0x74 */
    volatile uint32_t              RXFLR;                    /* Offest 0x78 */
    volatile REG_SDA_HOLD_t        SDA_HOLD;                 /* Offest 0x7C */
    volatile REG_TX_ABRT_SOURCE_t  TX_ABRT_SOURCE;           /* Offest 0x80 */       
    volatile uint32_t              SLV_DATA_NACK;            /* Offest 0x84 */  
    volatile uint32_t              rsv_3[3];
    volatile uint32_t              SDA_SETUP;                /* Offest 0x94 */
    volatile uint32_t              rsv_4[2];
    volatile uint32_t              FS_SPKLEN;                /* Offest 0xA0 */
    volatile uint32_t              rsv_5;    
    volatile uint32_t              CLR_RESTART_DET;          /* Offest 0xA8 */
    volatile uint32_t              SCL_STUCK_LOW_TIMEOUT;    /* Offest 0xAC */
    volatile uint32_t              SDA_STUCK_LOW_TIMEOUT;    /* Offest 0xB0 */
    volatile uint32_t              CLR_SCL_STUCK_DET;        /* Offest 0xB4 */
}struct_I2C_t;

#define I2C0    ((struct_I2C_t *)I2C0_BASE)
#define I2C1    ((struct_I2C_t *)I2C1_BASE)
#define I2C2    ((struct_I2C_t *)I2C2_BASE)
/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup I2C_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

/* interrupt index */
typedef enum
{
    INT_RX_UNDER         = 0x00000001,
    INT_RX_OVER          = 0x00000002,
    INT_RX_FULL          = 0x00000004,
    INT_TX_OVER          = 0x00000008,
    INT_TX_EMPTY         = 0x00000010,
    INT_RD_REQ           = 0x00000020,
    INT_TX_ABRT          = 0x00000040,
    INT_RX_DONE          = 0x00000080,
    INT_ACTIVITY         = 0x00000100,
    INT_STOP_DET         = 0x00000200,
    INT_START_DET        = 0x00000400,
    INT_RESTART_DET      = 0x00001000,
    INT_MASTER_ON_HOLD   = 0x00002000,
    INT_SCL_STUCK_AT_LOW = 0x00004000,
}enum_INT_Index_t;

/* interrupt index */
typedef enum
{
    CMD_WRITE   = 0x0000,
    CMD_READ    = 0x0100,
    CMD_STOP    = 0x0200,
    CMD_RESTART = 0x0400,
}enum_CMD_t;

/* I2C Mode */
typedef enum
{
    I2C_MODE_MASTER_7BIT  = 0x01,
    I2C_MODE_MASTER_10BIT = 0x11,
    I2C_MODE_SLAVE_7BIT   = 0x00,
    I2C_MODE_SLAVE_10BIT  = 0x10,

    I2C_MASK_MASTER = 0x01,
    I2C_MASK_10BIT  = 0x10,
}enum_I2C_MODE_t;


/*
 * @brief I2C Init Structure definition
 */
typedef struct
{
    uint32_t  I2C_Mode;               /* This parameter can be a value of @ref enum_I2C_MODE_t */

    uint32_t  SCL_HCNT;               /* This parameter can be a 16-bit value. The minimum limit is 6 */
    uint32_t  SCL_LCNT;               /* SCL high/low level hold time. The minimum limit is 8 */

    uint32_t  Slave_Address;          /* This parameter can be a 7-bit or 10-bit address */
}struct_I2CInit_t;


/*
 * @brief  I2C handle Structure definition
 */
typedef struct
{
    struct_I2C_t           *I2Cx;               /*!< I2C registers base address        */

    struct_I2CInit_t        Init;               /*!< I2C communication parameters      */

    volatile uint32_t       u32_TxSize;         /*!< I2C Transmit parameters in interrupt  */
    volatile uint32_t       u32_TxCount;
    volatile uint8_t       *p_TxData;
    volatile bool           b_TxBusy;

    volatile uint32_t       u32_RxSize;         /*!< I2C Receive parameters in interrupt  */
    volatile uint32_t       u32_RxCount;
    volatile uint8_t       *p_RxData;
    volatile bool           b_RxBusy;
}I2C_HandleTypeDef;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

#define __I2C_ENABLE(__I2Cx__)                          (__I2Cx__->ENABLE.ENABLE = 1)
#define __I2C_DISABLE(__I2Cx__)                         (__I2Cx__->ENABLE.ENABLE = 0)

/* master transfe abort */
#define __I2C_MASTER_TRAN_ABORT(__I2Cx__)               (__I2Cx__->ENABLE.ABORT = 1)

/* master Block/start the transmission */
#define __I2C_MASTER_BLOCK_TRAN(__I2Cx__)               (__I2Cx__->ENABLE.TX_CMD_BLOCK = 1)
#define __I2C_MASTER_START_TRAN(__I2Cx__)               (__I2Cx__->ENABLE.TX_CMD_BLOCK = 0)

/* get the number of valid data in RxFIFO/TxFIFO */
#define __I2C_GET_TxFIFO_VALID_NUM(__I2Cx__)            (__I2Cx__->TXFLR)
#define __I2C_GET_RxFIFO_VALID_NUM(__I2Cx__)            (__I2Cx__->RXFLR)

/* Get Tx abort source */
#define __I2C_GET_TX_ABRT_SOURCE(__I2Cx__)              (__I2Cx__->TX_ABRT_SOURCE.TX_ABRT_SOURCE_DWORD)
#define __I2C_IS_TX_ABRT(__I2Cx__)                      (__I2Cx__->RAW_INT_STAT & INT_TX_ABRT)

/* get I2C Status */
#define __I2C_IS_BUSY(__I2Cx__)                         (__I2Cx__->STATUS.ACTIVITY)
#define __I2C_IS_MASTER_BUSY(__I2Cx__)                  (__I2Cx__->STATUS.MST_ACTIVITY)
#define __I2C_IS_SLAVE_BUSY(__I2Cx__)                   (__I2Cx__->STATUS.SLV_ACTIVITY)
#define __I2C_IS_TxFIFO_FULL(__I2Cx__)                  (__I2Cx__->STATUS.TFNF == 0)
#define __I2C_IS_TxFIFO_EMPTY(__I2Cx__)                 (__I2Cx__->STATUS.TFE)
#define __I2C_IS_RxFIFO_FULL(__I2Cx__)                  (__I2Cx__->STATUS.RFF)
#define __I2C_IS_RxFIFO_EMPTY(__I2Cx__)                 (__I2Cx__->STATUS.RFNE == 0)
#define __I2C_IS_MST_HOLD_TX_FIFO_EMPTY(__I2Cx__)       (__I2Cx__->STATUS.MST_HOLD_TX_FIFO_EMPTY)
#define __I2C_IS_MST_HOLD_RX_FIFO_FULL(__I2Cx__)        (__I2Cx__->STATUS.MST_HOLD_RX_FIFO_FULL)
#define __I2C_IS_SLV_HOLD_TX_FIFO_EMPTY(__I2Cx__)       (__I2Cx__->STATUS.SLV_HOLD_TX_FIFO_EMPTY)
#define __I2C_IS_SLV_HOLD_RX_FIFO_FULL(__I2Cx__)        (__I2Cx__->STATUS.SLV_HOLD_RX_FIFO_FULL)
#define __I2C_IS_SDA_STUCK_NOT_RECOVERED(__I2Cx__)      (__I2Cx__->STATUS.SDA_STUCK_NOT_RECOVERED)

/* RxFIFO/TxFIFO Threshold level */
#define __I2C_RxFIFO_THRESHOLD_LEVEL(__I2Cx__, __LEVEL__)    (__I2Cx__->RX_TL = __LEVEL__)
#define __I2C_TxFIFO_THRESHOLD_LEVEL(__I2Cx__, __LEVEL__)    (__I2Cx__->TX_TL = __LEVEL__)

/* SCL High/Low count,  */
#define __I2C_SCL_HIGH_COUNT(__I2Cx__, __COUNT__)            (__I2Cx__->FS_SCL_HCNT = __COUNT__)
#define __I2C_SCL_LOW_COUNT(__I2Cx__, __COUNT__)             (__I2Cx__->FS_SCL_LCNT = __COUNT__)
#define __I2C_SDA_HOLD(__I2Cx__, __COUNT__)                  (__I2Cx__->SDA_HOLD.SDA_TX_HOLD = __COUNT__)
#define __I2C_SDA_SETUP(__I2Cx__, __COUNT__)                 (__I2Cx__->SDA_SETUP = __COUNT__)

/* Slave send ACK/NACK */
#define __I2C_SLAVE_SEND_NACK(__I2Cx__)                      (__I2Cx__->SLV_DATA_NACK = 1)
#define __I2C_SLAVE_SEND_ACK(__I2Cx__)                       (__I2Cx__->SLV_DATA_NACK = 0)

/* Exported functions ---------------------------------------------------------*/

/* i2c_IRQHandler */
void i2c_IRQHandler(I2C_HandleTypeDef *hi2c);

/* i2c_init */
void i2c_init(I2C_HandleTypeDef *hi2c);

/* Master transmit/receive */
bool i2c_master_transmit(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_master_receive(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_master_transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_master_receive_IT(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_slave_transmit(I2C_HandleTypeDef *hi2c, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_slave_receive(I2C_HandleTypeDef *hi2c, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_slave_transmit_IT(I2C_HandleTypeDef *hi2c, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_slave_receive_IT(I2C_HandleTypeDef *hi2c, uint8_t *fp_Data, uint32_t fu32_Size);

/* memory write/read */
bool i2c_memory_write(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress, uint16_t fu16_MemAddress, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_memory_read(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress, uint16_t fu16_MemAddress, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_memory_is_busy(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress);

/* interrupt function */
void i2c_int_enable(I2C_HandleTypeDef *hi2c, enum_INT_Index_t fe_INT_Index);
void i2c_int_disable(I2C_HandleTypeDef *hi2c, enum_INT_Index_t fe_INT_Index);
bool i2c_is_int_enable(I2C_HandleTypeDef *hi2c, enum_INT_Index_t fe_INT_Index);
bool i2c_get_int_status(I2C_HandleTypeDef *hi2c, enum_INT_Index_t fe_INT_Index);
void i2c_clear_int_status(I2C_HandleTypeDef *hi2c, enum_INT_Index_t fe_INT_Index);

/* sensor write/read */
bool i2c_sensor_write(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress, uint32_t fu32_RegAddress, uint8_t fu8_AddressLength, uint8_t *fp_Data, uint32_t fu32_Size);
bool i2c_sensor_read(I2C_HandleTypeDef *hi2c, uint16_t fu16_DevAddress, uint32_t fu32_RegAddress, uint8_t fu8_AddressLength, uint8_t *fp_Data, uint32_t fu32_Size);
#endif
