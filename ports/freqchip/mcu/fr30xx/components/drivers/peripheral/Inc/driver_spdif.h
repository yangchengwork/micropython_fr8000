/*
  ******************************************************************************
  * @file    driver_spdif.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of SPDIF module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SPDIF_H__
#define __DRIVER_SPDIF_H__

#include "fr30xx.h"

/** @addtogroup SPDIF_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* SPDIF CTRL REG */
typedef struct
{
    uint32_t TSAMPLERATE    : 8;
    uint32_t SFR_RESET      : 1;
    uint32_t SPDIF_ENABLE   : 1;
    uint32_t FIFO_RESET     : 1;
    uint32_t CLK_ENABLE     : 1;
    uint32_t TR_MODE        : 1;
    uint32_t PARITY_CHECK   : 1;
    uint32_t PARITYGEN      : 1;
    uint32_t VALIDITY_CHECK : 1;
    uint32_t CHANNEL_MODE   : 1;
    uint32_t DUPLICATE      : 1;
    uint32_t SETPREAMBLE    : 1;
    uint32_t DATA_WIDTH     : 2;
    uint32_t INT_STS_EN     : 11;
}REG_SPDIF_CTRL_t;

/* SPDIF INT_STS REG */
typedef struct
{
    uint32_t RSAMPLERATE    : 8;
    uint32_t PREAMBLEDEL    : 4;
    uint32_t rsv_0          : 9;
    uint32_t INT_STS        : 11;
}REG_SPDIF_INT_STS_t;

/* SPDIF FIFO CTRL REG */
typedef struct
{
    uint32_t ALEMPTY_THRESHOLD    : 7;
    uint32_t rsv_0                : 1;
    uint32_t ALFULL_THRESHOLD     : 7;
    uint32_t rsv_1                : 1;
    uint32_t PARITY_INT_TYPE      : 1;
    uint32_t UNDERR_INT_TYPE      : 1;
    uint32_t OVERR_INT_TYPE       : 1;
    uint32_t FF_EMPTY_INT_TYPE    : 1;
    uint32_t FF_ALEMPTY_INT_TYPE  : 1;
    uint32_t FF_FULL_INT_TYPE     : 1;
    uint32_t FF_ALFULL_INT_TYPE   : 1;
    uint32_t SYNCERR_INT_TYPE     : 1;
    uint32_t LOCK_INT_TYPE        : 1;
    uint32_t BLOCK_BEGIN_INT_TYPE : 1;
    uint32_t rsv_2                : 6;
}REG_SPDIF_FIFO_CTRL_t;

/* SPDIF INT_STS REG */
typedef struct
{
    uint32_t FIFO_LEVEL    : 8;
    uint32_t rsv_0         : 13;
    uint32_t RAW_STS       : 11;
}REG_SPDIF_RAW_STS_t;

typedef struct 
{
    volatile REG_SPDIF_CTRL_t           SPDIF_CTRL;                 /* Offset 0x00 */
    volatile REG_SPDIF_INT_STS_t        SPDIF_INT_STS;              /* Offset 0x04 */
    volatile REG_SPDIF_FIFO_CTRL_t      SPDIF_FIFO_CTRL;            /* Offset 0x08 */
    volatile REG_SPDIF_RAW_STS_t        SPDIF_RAW_STS;              /* Offset 0x0C */
    volatile uint32_t                   SPDIF_FIFO_DATA;            /* Offset 0x10 */
}struct_SPDIF_t;

#define SPDIF      ((struct_SPDIF_t *)SPDIF_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup SPDIF_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization_Config Section Start ################################ */

#define SPDIF_FIFO_DEPTH    (128)

/* SPDIF Sample Rate */
typedef enum
{
    SPDIF_SAMPLE_RATE_8000,
    SPDIF_SAMPLE_RATE_12000,
    SPDIF_SAMPLE_RATE_16000,
    SPDIF_SAMPLE_RATE_24000,
    SPDIF_SAMPLE_RATE_32000,
    SPDIF_SAMPLE_RATE_48000,
    SPDIF_SAMPLE_RATE_96000,
    SPDIF_SAMPLE_RATE_192000,
    SPDIF_SAMPLE_RATE_11025,
    SPDIF_SAMPLE_RATE_22050,
    SPDIF_SAMPLE_RATE_44100,
    SPDIF_SAMPLE_RATE_88200,
    SPDIF_SAMPLE_RATE_176400,
}enum_SPDIF_SampleRate_t;

/* Interrupt Status */
typedef enum
{
    SPDIF_INT_PARITY  = 1 << 0,
    SPDIF_INT_UNDERR  = 1 << 1,
    SPDIF_INT_OVERR   = 1 << 2,
    SPDIF_INT_EMPTY   = 1 << 3,
    SPDIF_INT_ALEMPTY = 1 << 4,
    SPDIF_INT_FULL    = 1 << 5,
    SPDIF_INT_ALFULL  = 1 << 6,
    SPDIF_INT_SYNCERR = 1 << 7,
    SPDIF_INT_LOCK    = 1 << 8,
    SPDIF_INT_BEGIN   = 1 << 9,
    SPDIF_INT_MASK    = 1 << 10,
}enum_SPDIF_INT_Index_t;

/* SPDIF work mode */
typedef enum
{
    SPDIF_RX_MODE,      /*!< Rx work mode */
    SPDIF_TX_MODE,      /*!< Tx work mode */
}enum_SPDIF_WorkMode_t;

/* SPDIF work mode */
typedef enum
{
    SPDIF_DATA_WIDTH_24BIT,
    SPDIF_DATA_WIDTH_20BIT,
    SPDIF_DATA_WIDTH_16BIT,
}enum_SPDIF_DataWidth_t;

/* SPDIF function enable/disable select */
typedef enum
{
    SPDIF_FUNC_DISABLE,     /*!< function disable */
    SPDIF_FUNC_ENABLE,      /*!< function enable  */
}enum_SPDIF_func_en_t;

/*
 * @brief SPDIF Init Structure definition
 */
typedef struct 
{
    uint32_t WorkMode;                /*!< Specifies the SPDIF work mode.
                                           This parameter can be a value of @ref enum_SPDIF_WorkMode_t */

    uint32_t MonoEn;                  /*!< Specifies the play mode, Stereo or mono.
                                           This parameter can be a value of @ref enum_SPDIF_func_en_t */

    uint32_t DataWidth;               /*!< Specifies the data width.
                                           This parameter can be a value of @ref enum_SPDIF_DataWidth_t */

    uint32_t TxSampleRate;            /*!< Specifies the Send sample rate.
                                           This parameter can be a value of @ref enum_SPDIF_SampleRate_t */

    uint32_t Tx_ALEmpty_Threshold;    /*!< Specifies the FIFO almost EMPTY threshold, in Tx mode.
                                           This parameter The value can be a value 0 ~ 0x7F*/ 

    uint32_t Rx_ALFull_Threshold;     /*!< Specifies the FIFO almost FULL threshold, in Rx mode.
                                           This parameter The value can be a value 0 ~ 0x7F*/
}struct_SPDIF_Init_t;

/*
 * @brief  SPDIF handle Structure definition
 */
typedef struct __SPDIF_HandleTypeDef
{
    struct_SPDIF_Init_t     Init;                              /*!< SPDIF communication parameters */

    void (*TxALEmptyCallback)(struct __SPDIF_HandleTypeDef *hspdif);    /*!< tx almost empty Callback */
    void (*RxALFullCallback)(struct __SPDIF_HandleTypeDef *hspdif);     /*!< rx almost full  Callback */

    union {
        volatile void      *p_data;
        volatile uint16_t  *p_u16;
        volatile uint32_t  *p_u32;
    } u_Data;
}SPDIF_HandleTypeDef;

/* ################################ Initialization_Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* TX samplerate divider */
#define __SPDIF_SET_TX_SAMPLERATE_DIV(__DIV__)               (SPDIF->SPDIF_CTRL.TSAMPLERATE = (__DIV__))
/* Software reset */
#define __SPDIF_SFR_RESET()                                  (SPDIF->SPDIF_CTRL.SFR_RESET = 0)
/* SPDIF Enable Diable */
#define __SPDIF_ENABLE()                                     (SPDIF->SPDIF_CTRL.SPDIF_ENABLE = 1)
#define __SPDIF_DISABLE()                                    (SPDIF->SPDIF_CTRL.SPDIF_ENABLE = 0)
#define __SPDIF_CLOCK_ENABLE()                               (SPDIF->SPDIF_CTRL.CLK_ENABLE = 0)
#define __SPDIF_CLOCK_DISABLE()                              (SPDIF->SPDIF_CTRL.CLK_ENABLE = 1)
/* FIFO reset */
#define __SPDIF_FIFO_RESET()                                 (SPDIF->SPDIF_CTRL.FIFO_RESET = 0)
/* parity checK */
#define __SPDIF_PARITY_CHECK_ENABLE()                        (SPDIF->SPDIF_CTRL.PARITY_CHECK = 1)
#define __SPDIF_PARITY_CHECK_DISABLE()                       (SPDIF->SPDIF_CTRL.PARITY_CHECK = 0)
/* tx work mode/rx work mode */
#define __SPDIF_WORK_MODE(__MODE__)                          (SPDIF->SPDIF_CTRL.TR_MODE = __MODE__)
/* auto/manual mode */
#define __SPDIF_PARITY_AUTO_MODE()                           (SPDIF->SPDIF_CTRL.PARITYGEN = 1)
#define __SPDIF_PARITY_MANUAL_MODE()                         (SPDIF->SPDIF_CTRL.PARITYGEN = 0)
/* valid bit check enable/disable */
#define __SPDIF_VALID_BIT_CHECK_ENABLE()                     (SPDIF->SPDIF_CTRL.VALIDITY_CHECK = 1)
#define __SPDIF_VALID_BIT_CHECK_DISABLE()                    (SPDIF->SPDIF_CTRL.VALIDITY_CHECK = 0)
/* mono/stereo */
#define __SPDIF_CHANNEL_MODE(__MODE__)                       (SPDIF->SPDIF_CTRL.CHANNEL_MODE = __MODE__)
/* mono mode, right channel copy enable/disable */
#define __SPDIF_MONO_RIGHT_COPY_ENABLE()                     (SPDIF->SPDIF_CTRL.DUPLICATE = 1)
#define __SPDIF_MONO_RIGHT_COPY_DISABLE()                    (SPDIF->SPDIF_CTRL.DUPLICATE = 0)
/* SETPREAMBLE operation mode */
#define __SPDIF_SETPREAMBLE_OPERATION_MODE(__MODE__)         (SPDIF->SPDIF_CTRL.SETPREAMBLE = __MODE__)
/* data width config */
#define __SPDIF_DATA_WIDTH_CONFIG(__CFG__)                   (SPDIF->SPDIF_CTRL.DATA_WIDTH = __CFG__)

/* interrupt enable/disable */
#define __SPDIF_INT_ENABLE(__INT__)                          (SPDIF->SPDIF_CTRL.INT_STS_EN |= (__INT__))
#define __SPDIF_INT_DISABLE(__INT__)                         (SPDIF->SPDIF_CTRL.INT_STS_EN &= ~(__INT__))

/* Get Interrupt Status */
#define __SPDIF_GET_INT_STATUS()                             (SPDIF->SPDIF_INT_STS.INT_STS)
/* Get RX samplerate divider */
#define __SPDIF_GET_RX_SAMPLERATE_DIV()                      (SPDIF->SPDIF_INT_STS.RSAMPLERATE)

/* tx almost empty threshold */
#define __SPDIF_TXALMOST_EMPTY_THRESHOLD_CONFIG(__CFG__)     (SPDIF->SPDIF_FIFO_CTRL.ALEMPTY_THRESHOLD = __CFG__)
/* rx almost full threshold */
#define __SPDIF_RXALMOST_FULL_THRESHOLD_CONFIG(__CFG__)      (SPDIF->SPDIF_FIFO_CTRL.ALFULL_THRESHOLD = __CFG__)

/* get fifo level */
#define __SPDIF_GET_FIFO_LEVEL()                             (SPDIF->SPDIF_RAW_STS.FIFO_LEVEL)
/* get raw status */
#define __SPDIF_GET_RAW_STS()                                (SPDIF->SPDIF_RAW_STS.RAW_STS)

/* write/read fifo */
#define __SPDIF_WRITE_FIFO(__DATA__)                         (SPDIF->SPDIF_FIFO_DATA = __DATA__)
#define __SPDIF_READ_FIFO()                                  (SPDIF->SPDIF_FIFO_DATA)


/* Exported functions -------------------------------------------------------------------------*/

void SPDIF_IRQHandler(SPDIF_HandleTypeDef *hspdif);

/* spdif_init */
void spdif_init(SPDIF_HandleTypeDef *hspdif);

/* spdif_transmit_IT/spdif_receive_IT */
void spdif_transmit_IT(SPDIF_HandleTypeDef *hspdif, void *fp_Data);
void spdif_receive_IT(SPDIF_HandleTypeDef *hspdif, void *fp_Data);

/* spdif_send_data/spdif_read_data */
void spdif_send_data(SPDIF_HandleTypeDef *hspdif, void *fp_Data, uint32_t fu32_length);
void spdif_read_data(SPDIF_HandleTypeDef *hspdif, void *fp_Data, uint32_t fu32_length);

#endif
