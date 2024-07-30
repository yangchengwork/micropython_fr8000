/*
  ******************************************************************************
  * @file    driver_pdm.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of pdm HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_PDM_H__
#define __DRIVER_PDM_H__

#include "fr30xx.h"

#include <math.h>

/** @addtogroup PDM_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* PDM config register */
typedef struct 
{
    uint32_t EN             : 1;
    uint32_t CLK_EN         : 1;
    uint32_t RST            : 1;
    uint32_t DAT_INV        : 1;
    uint32_t CLK_INV        : 1;
    uint32_t USB_MODE       : 1;
    uint32_t SAMPLE_RATE    : 4;
    uint32_t OSR_MODE       : 2;
    uint32_t MONO           : 1;
    uint32_t CH_SEL         : 1;
    uint32_t LR_SWAP        : 1;
    uint32_t HPF_EN         : 1;
    uint32_t DATA_SRC       : 1;
    uint32_t rsv_0          : 15;
}REG_PDMConfig_t;

/* PDM FIFO Reset Register */
typedef union{
    struct {
        uint32_t PUSH_RST       : 1;
        uint32_t POP_RST        : 1;
        uint32_t RST            : 1;
        uint32_t rsv            : 29;
    } s;
    uint32_t rst;
}REG_PDMFFReset_t;

/* PDM interrupt Register */
typedef struct{
    uint32_t FF_FULL        : 1;
    uint32_t FF_AFULL       : 1;
    uint32_t FF_EMPTY       : 1;
    uint32_t rsv            : 29;
}REG_PDMFFInt_t;

/* PDM interrupt Register */
typedef struct{
    uint32_t TRIG_LVL       : 6;
    uint32_t EN             : 1;
    uint32_t rsv            : 25;
}REG_PDMDMA_t;


/* -----------------------------------------------*/
/*                   PDM Register                 */
/* -----------------------------------------------*/
typedef struct 
{
    volatile REG_PDMConfig_t     Config;               /* Offset 0x00 */
    volatile uint32_t            FF_AFLL_LVL;          /* Offset 0x04 */
    volatile REG_PDMFFReset_t    FF_RST;               /* Offset 0x08 */
    volatile REG_PDMFFInt_t      INT_EN;               /* Offset 0x0C */
    volatile REG_PDMFFInt_t      INT_STA;              /* Offset 0x10 */
    volatile REG_PDMFFInt_t      INT_RAW_STA;          /* Offset 0x14 */
    volatile uint32_t            VOL_L;                /* Offset 0x18 */
    volatile uint32_t            VOL_R;                /* Offset 0x1C */
    volatile uint32_t            rsv1;                 /* Offset 0x20 */
    volatile uint32_t            DATA;                 /* Offset 0x24 */
    volatile REG_PDMDMA_t        DMA_CFG;              /* Offset 0x28 */
}struct_PDM_t;

#define PDM0       ((struct_PDM_t *)PDM0_BASE)
#define PDM1       ((struct_PDM_t *)PDM1_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup PDM_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization Config Section Start ################################ */

/* PDM Sample Rate */
typedef enum  
{
    PDM_SAMPLE_RATE_8000      = 0x00,
    PDM_SAMPLE_RATE_12000     = 0x01,
    PDM_SAMPLE_RATE_16000     = 0x02,
    PDM_SAMPLE_RATE_24000     = 0x03,
    PDM_SAMPLE_RATE_32000     = 0x04,
    PDM_SAMPLE_RATE_48000     = 0x05,
    PDM_SAMPLE_RATE_96000     = 0x06,
    PDM_SAMPLE_RATE_192000    = 0x07,
    PDM_SAMPLE_RATE_8012      = 0x08,
    PDM_SAMPLE_RATE_11025     = 0x09,
    PDM_SAMPLE_RATE_22050     = 0x0A,
    PDM_SAMPLE_RATE_44100     = 0x0B,
    PDM_SAMPLE_RATE_88200     = 0x0C,
    PDM_SAMPLE_RATE_176400    = 0x0D,
    PDM_SAMPLE_RATE_44_1K_SET = 0x08,
}enum_PDM_SampleRate_t;

/* PDM Clock Mode Selection */
typedef enum{
    PDM_CLOCK_MODE_NORMAL,      /* clock from AUPLL2 */
    PDM_CLOCK_MODE_USB,         /* clock is 24MHz */
}enum_PDM_ClockMode_t;

/* PDM Over Sample Mode */
typedef enum{
    PDM_OSM_0,      // oversampling low level support to all SampleRate.
    PDM_OSM_1,      // oversampling middle level support up to 96K.
    PDM_OSM_2,      // oversampling high level support up to 48K.
}enum_PDM_OverSampleMode_t;

/* PDM Channel Selection in Mono mode */
typedef enum{
    PDM_MONO_LEFT,      /* Mono selcet left */
    PDM_MONO_RIGHT,     /* Mono selcet right */
    PDM_STEREO,         /* stereo */
}enum_PDM_ChannelMode_t;

/* PDM Volume */
typedef enum{
    PDM_VOL_0,
    PDM_VOL_1,
    PDM_VOL_2,
    PDM_VOL_3,
    PDM_VOL_4,
    PDM_VOL_5,
    PDM_VOL_6,
    PDM_VOL_7,
    PDM_VOL_8,
    PDM_VOL_9,
    PDM_VOL_10,
    PDM_VOL_11,
    PDM_VOL_12,
    PDM_VOL_13,
    PDM_VOL_14,
    PDM_VOL_15,
    PDM_VOL_MAX
}enum_PDM_Volume_t;

/*
 * @brief PDM Init Structure definition
 */
typedef struct
{
    uint8_t SampleRate;             /* This parameter can be a value of @ref enum_PDM_SampleRate_t */

    uint8_t OverSampleMode;         /* This parameter can be a value of @ref enum_PDM_OverSampleMode_t */

    uint8_t ChannelMode;            /* This parameter can be a value of @ref enum_PDM_ChannelMode_t */

    int8_t  Volume;                 /* This parameter can be a value with dB as unit */

    uint8_t FIFO_FullThreshold;     /* This parameter can be a  5 bit value */
}struct_PDMInit_t;

/*
 * @brief  PDM handle Structure definition
 */
typedef struct __PDM_HandleTypeDef
{
    struct_PDM_t            *PDMx;               /*!< PDM registers base address           */

    struct_PDMInit_t         Init;               /*!< PDM communication parameters         */

    void (*RxCallback)(struct __PDM_HandleTypeDef *hpdm);

    bool                     b_RxBusy;
    void                    *p_RxData;
}PDM_HandleTypeDef;

/* ################################ Initialization Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define PDM_FIFO_DEPTH      64
#define PDM_FIFO_H_FULL     (PDM_FIFO_DEPTH / 2)
#define PDM_VOL_dB(x)       (uint32_t)(pow(10.0, (x)/20.0) * 0x2000)

/* PDM enable/disable */
#define __PDM_ENABLE(__PDMx__)                           (__PDMx__->Config.EN = 1)
#define __PDM_DISABLE(__PDMx__)                          (__PDMx__->Config.EN = 0)
/* PDM clock enable/disable */
#define __PDM_CLK_ENABLE(__PDMx__)                       (__PDMx__->Config.CLK_EN = 1)
#define __PDM_CLK_DISABLE(__PDMx__)                      (__PDMx__->Config.CLK_EN = 0)
/* PDM L/R SWAP enable/disable */
#define __PDM_SWAP_ENABLE(__PDMx__)                      (__PDMx__->Config.LR_SWAP = 1)
#define __PDM_SWAP_DISABLE(__PDMx__)                     (__PDMx__->Config.LR_SWAP = 0)
/* PDM stereo/mono mode */
#define __PDM_SET_STEREO_MODE(__PDMx__)                  (__PDMx__->Config.MONO = 0)
#define __PDM_SET_MONO_MODE(__PDMx__)                    (__PDMx__->Config.MONO = 1)
/* PDM mono mode select channel */
#define __PDM_MONO_MODE_SELECT_LEFT_CHANNEL(__PDMx__)    (__PDMx__->Config.CH_SEL = 0)
#define __PDM_MONO_MODE_SELECT_RIGHT_CHANNEL(__PDMx__)   (__PDMx__->Config.CH_SEL = 1)
/* PDM oversampling level */
#define __PDM_SET_OVERSAMPLING_LEVEL(__PDMx__)           (__PDMx__->Config.OSR_MODE = 1)
/* PDM sampling rate */
#define __PDM_SET_SAMPLING_RATE(__PDMx__)                (__PDMx__->Config.OSR_MODE = 1)
/* PDM clock mode. 0: from AUPLL. 1: from 24M */
#define __PDM_CLK_MODE(__PDMx__, __MODE__)               (__PDMx__->Config.USB_MODE = __MODE__)
/* PDM Sampling clock inversion enable/disable */
#define __PDM_CLK_INV_ENABLE(__PDMx__)                   (__PDMx__->Config.CLK_INV = 1)
#define __PDM_CLK_INV_DISABLE(__PDMx__)                  (__PDMx__->Config.CLK_INV = 0)
/* PDM Sampling data inversion enable/disable */
#define __PDM_DATA_INV_ENABLE(__PDMx__)                  (__PDMx__->Config.DAT_INV = 1)
#define __PDM_DATA_INV_DISABLE(__PDMx__)                 (__PDMx__->Config.DAT_INV = 0)
/* PDM software reset */
#define __PDM_SOFTWARE_RESET(__PDMx__)                 do{__PDMx__->Config.RST = 1; \
                                                          __PDMx__->Config.RST = 0;}while(0)
/* PDM data source select saradc */
#define __PDM_DATA_SOURCE_SELECT_SARADC(__PDMx__)        (__PDMx__->Config.DATA_SRC = 1)
                                                          
/* PDM almost full threshold value level */
#define __PDM_SET_ALFULL_THRESHOLD(__PDMx__, __LEVEL__)  (__PDMx__->FF_AFLL_LVL = __LEVEL__)

/* PDM volume config */
#define __PDM_SET_VOLUME_LEFT(__PDMx__, __VOL__)         (__PDMx__->VOL_L = __VOL__)
#define __PDM_SET_VOLUME_RIGHT(__PDMx__, __VOL__)        (__PDMx__->VOL_R = __VOL__)

/* PDM FIFO interrupt enable/disable */
#define __PDM_FIFO_FULL_INT_ENABLE(__PDMx__)             (__PDMx__->INT_EN.FF_FULL = 1)
#define __PDM_FIFO_EMPTY_INT_ENABLE(__PDMx__)            (__PDMx__->INT_EN.FF_EMPTY = 1)
#define __PDM_FIFO_ALMOST_FULL_INT_ENABLE(__PDMx__)      (__PDMx__->INT_EN.FF_AFULL = 1)

#define __PDM_FIFO_FULL_INT_DISABLE(__PDMx__)            (__PDMx__->INT_EN.FF_FULL = 0)
#define __PDM_FIFO_EMPTY_INT_DISABLE(__PDMx__)           (__PDMx__->INT_EN.FF_EMPTY = 0)
#define __PDM_FIFO_ALMOST_FULL_INT_DISABLE(__PDMx__)     (__PDMx__->INT_EN.FF_AFULL = 0)

/* PDM FIFO status */
#define __PDM_IS_FIFO_FULL(__PDMx__)                     (__PDMx__->INT_RAW_STA.FF_FULL)
#define __PDM_IS_FIFO_EMPTY(__PDMx__)                    (__PDMx__->INT_RAW_STA.FF_EMPTY)
#define __PDM_IS_FIFO_ALMOST_FULL(__PDMx__)              (__PDMx__->INT_RAW_STA.FF_AFULL)

#define __PDM_GET_INT_STS_FIFO_FULL(__PDMx__)            (__PDMx__->INT_STA.FF_FULL)
#define __PDM_GET_INT_STS_FIFO_EMPTY(__PDMx__)           (__PDMx__->INT_STA.FF_EMPTY)
#define __PDM_GET_INT_STS_FIFO_ALMOST_FULL(__PDMx__)     (__PDMx__->INT_STA.FF_AFULL)

/* PDM FIFO Reset */
#define __PDM_FIFO_RESET(__PDMx__)                       (__PDMx__->FF_RST.rst = 0x07)

/* PDM read fifo */
#define __PDM_READ_FIFO(__PDMx__)                        (__PDMx__->DATA)

/* PDM DAM config */
#define __PDM_DMA_ENABLE(__PDMx__)                       (__PDMx__->DMA_CFG.EN = 1)
#define __PDM_DMA_DISABLE(__PDMx__)                      (__PDMx__->DMA_CFG.EN = 0)
#define __PDM_DMA_THRESHOLD(__PDMx__, __LEVEL__)         (__PDMx__->DMA_CFG.TRIG_LVL = __LEVEL__)

/* Exported functions --------------------------------------------------------*/

void pdm_IRQHandler(PDM_HandleTypeDef *hpdm);

/* pdm_init */
void pdm_init(PDM_HandleTypeDef *hpdm);

/* pdm_start/stio */
void pdm_start(PDM_HandleTypeDef *hpdm);
void pdm_stop(PDM_HandleTypeDef *hpdm);

/* pdm_start_IT  */
void pdm_start_IT(PDM_HandleTypeDef *hpdm, void *fp_Data);

/* pdm_vol_set */
void pdm_vol_set(PDM_HandleTypeDef *hpdm, int8_t vol);

/* pdm_read_data */
void pdm_read_data(PDM_HandleTypeDef *hpdm, void *fp_Data);

#endif
