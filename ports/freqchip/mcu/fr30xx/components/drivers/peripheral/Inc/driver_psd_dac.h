/*
  ******************************************************************************
  * @file    driver_psd_dac.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of PWM Sigma-Delta DAC module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_PWM_SIGMA_DELTA_DAC_H__
#define __DRIVER_PWM_SIGMA_DELTA_DAC_H__

#include "fr30xx.h"

/** @addtogroup PSD_DAC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Master Clock Output Configuration Register */
typedef struct
{
    uint32_t MCLK_DIV      : 10;
    uint32_t MCLK_DIV_TYPE : 1;
    uint32_t MCLK_SRC      : 2;
    uint32_t MCLK_OUT_EN   : 1;
    uint32_t rsv           : 18;
}REG_PSD_MCLKCfg_t;

/* DAC Configure Register */
typedef struct
{
    uint32_t USB_MODE           : 1;
    uint32_t SAMPLE_RATE        : 4;
    uint32_t OVER_SAMPLE_MODE   : 2;
    uint32_t MONO_EN            : 1;
    uint32_t MONO_SELECT        : 1;
    uint32_t SWAP_EN            : 1;
    uint32_t DAC_CLK_SRC        : 2;
    uint32_t DAC_DATA_SRC       : 1;
    uint32_t LEFT_MIX_EN        : 1;
    uint32_t RIGHT_MIX_EN       : 1;
    uint32_t PWM_CLK_INV_EN     : 1;
    uint32_t rsv                : 16;
}REG_PSD_DACCfg_t;

/* DAC Volume Configure Register */
typedef struct
{
    uint32_t LEFT_VOLUME  : 16;
    uint32_t RIGHT_VOLUME : 16;
}REG_PSD_DacVol_t;

/* I2S TX Control Register */
typedef struct
{
    uint32_t FORMAT     : 2;
    uint32_t DCI_WL     : 2;
    uint32_t LR_POL     : 1;
    uint32_t LR_SWAP    : 1;
    uint32_t CHANNEL_CP : 1;
    uint32_t IBCLK_INV  : 1;
    uint32_t OBCLK_INV  : 1;
    uint32_t I2S_MODE   : 1;
    uint32_t BCLK_SRC   : 2;
    uint32_t rsv        : 20;
}REG_PSD_I2STxCtrl_t;

/* I2S TX Clock Control Register */
typedef struct
{
    uint32_t BCLK_DIV   : 16;
    uint32_t LRCLK_DIV  : 16;
}REG_PSD_I2STxClkCtrl_t;

/* DAC FIFO Control Register */
typedef struct 
{
    uint32_t DACFF_BITWD_L    : 2;
    uint32_t DACFF_BITWD_R    : 2;
    uint32_t DACFF_OP_MODE_EN : 1;
    uint32_t rsv              : 27;
}REG_PSD_DACFIFOCtrl_t;

/* DAC FIFO Threshold Configure Register */
typedef struct
{
    uint32_t DAC_FIFO_Threshold_Left  : 6;
    uint32_t DAC_FIFO_Threshold_Right : 6;
    uint32_t rsv                      : 20;
}REG_PSD_DACFIFOThd_t;

/* DAC FIFO Threshold Configure Register */
typedef struct
{
    uint32_t DAC_DMA_Threshold_Left  : 6;
    uint32_t DAC_DMA_Threshold_Right : 6;
    uint32_t rsv                     : 20;
}REG_PSD_DACDMAThd_t;

/* ------------------------------------------------*/
/*                 PSD_DAC Register                */
/* ------------------------------------------------*/
typedef struct 
{
    /* DAC Control Registers */
    volatile uint32_t                ClockEnable;        /* offset 0x00 */
    volatile uint32_t                SoftReset;          /* offset 0x04 */
    volatile uint32_t                rsv_0;              /* offset 0x08 */
    volatile uint32_t                ModeEnable;         /* offset 0x0C */
    volatile uint32_t                AudioPLLPreDiv;     /* offset 0x10 */
    volatile REG_PSD_MCLKCfg_t       MCLKCfg;            /* offset 0x14 */
    volatile REG_PSD_DACCfg_t        DACCfg;             /* offset 0x18 */
    volatile uint32_t                rsv_1;              /* offset 0x1C */
    volatile uint32_t                MuteCtrl;           /* offset 0x20 */
    volatile REG_PSD_DacVol_t        Volume;             /* offset 0x24 */
    volatile uint32_t                GainCompensate;     /* offset 0x28 */
    volatile uint32_t                rsv_2;              /* offset 0x2C */

    /* I2S Control Registers */
    volatile REG_PSD_I2STxCtrl_t     I2STxCtrl;          /* offset 0x30 */
    volatile REG_PSD_I2STxClkCtrl_t  I2STxClkCtrl;       /* offset 0x34 */

    /* DAC FIFO Control Registers */
    volatile REG_PSD_DACFIFOCtrl_t   DACFIFOCtrl;        /* offset 0x38 */
    volatile REG_PSD_DACFIFOThd_t    DACFIFOThd;         /* offset 0x3C */
    volatile uint32_t                DACDataL;           /* offset 0x40 */
    volatile uint32_t                DACDataR;           /* offset 0x44 */

    /* DAC DMA Control Registers */
    volatile uint32_t                DACDmaEn;           /* offset 0x48 */
    volatile REG_PSD_DACDMAThd_t     DACDmaThd;          /* offset 0x4C */

    /* DAC interrupt Registers */
    volatile uint32_t                DACIntEn;           /* offset 0x50 */
    volatile uint32_t                DACIntRawStatus;    /* offset 0x54 */
    volatile uint32_t                DACIntStatus;       /* offset 0x58 */
}struct_PSD_DAC_t;

#define PSD_DAC       ((struct_PSD_DAC_t *)PSD_DAC_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup PSD_DAC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization Config Section Start ################################ */


/* PSD DAC FIFO interrupt status */
typedef enum
{
    PSD_DAC_INT_DACFF_L_FULL   = (1<<0),
    PSD_DAC_INT_DACFF_R_FULL   = (1<<1),
    PSD_DAC_INT_DACFF_L_EMPTY  = (1<<2),
    PSD_DAC_INT_DACFF_R_EMPTY  = (1<<3),
    PSD_DAC_INT_DACFF_L_AEMPTY = (1<<4),
    PSD_DAC_INT_DACFF_R_AEMPTY = (1<<5),
}enum_PSD_DAC_INT_Status_t;

/* PSD DAC data source select */
typedef enum
{
    PSD_DAC_DATA_SOURCE_DACFIFO,       ///* PSD_DAC data source from DAC FIFO */
    PSD_DAC_DATA_SOURCE_I2SRX,         ///* PSD_DAC data source from I2S Rx */
}enum_PSD_DAC_DataSrc_t;

/* PSD DAC Clock source */
typedef enum
{
    PSD_DAC_CLOCK_SOURCE_24M_MODE = 0,
    PSD_DAC_CLOCK_SOURCE_AUPLL    = 1,
    PSD_DAC_CLOCK_SOURCE_EXTERN   = 2,
}enum_PSD_DAC_Clcok_Src_t;

/* PSD DAC Sample Rate */
typedef enum
{
    PSD_DAC_SAMPLE_RATE_8000,
    PSD_DAC_SAMPLE_RATE_12000,
    PSD_DAC_SAMPLE_RATE_16000,
    PSD_DAC_SAMPLE_RATE_24000,
    PSD_DAC_SAMPLE_RATE_32000,
    PSD_DAC_SAMPLE_RATE_48000,
    PSD_DAC_SAMPLE_RATE_96000,
    PSD_DAC_SAMPLE_RATE_192000,
    PSD_DAC_SAMPLE_RATE_11025,
    PSD_DAC_SAMPLE_RATE_22050,
    PSD_DAC_SAMPLE_RATE_44100,
    PSD_DAC_SAMPLE_RATE_88200,
    PSD_DAC_SAMPLE_RATE_176400,
}enum_PSD_DAC_SampleRate_t;

/* PSD DAC oversampling level */
typedef enum
{
    PSD_DAC_OVERSAMPLING_LOW,         // oversampling low level support to all SampleRate.
    PSD_DAC_OVERSAMPLING_MIDDLE,      // oversampling middle level support up to 96K.
    PSD_DAC_OVERSAMPLING_HIGH,        // oversampling high level support up to 48K.
}enum_PSD_DAC_Oversampling_level_t;

/* DAC FIFO Data Format */
typedef enum
{
    PSD_DAC_FIFO_FORMAT_8BIT,
    PSD_DAC_FIFO_FORMAT_16BIT,
    PSD_DAC_FIFO_FORMAT_20BIT,
    PSD_DAC_FIFO_FORMAT_24BIT,
}enum_PSD_DAC_DacFIFO_Format_t;

/* MCLK config */
typedef enum
{
    MCLK_SOURCE_24M_MODE  = 0,
    MCLK_SOURCE_AUPLL     = 1,
    MCLK_SOURCE_EXTERN    = 2,

    MCLK_DIV_TYPE_INTEGER = 0,
    MCLK_DIV_TYPE_FLOAT   = 1,
}enum_PSD_DAC_MCLK_Config_t;

/* BCLK config */
typedef enum
{
    BCLK_SOURCE_24M_MODE  = 0,
    BCLK_SOURCE_AUPLL     = 1,
    BCLK_SOURCE_EXTERN    = 2,
}enum_PSD_DAC_BCLK_Config_t;

/* channel select */
typedef enum
{
    PSD_DAC_CH_L  = 1,
    PSD_DAC_CH_R  = 2,
    PSD_DAC_CH_LR = 3,
}enum_PSD_DAC_Channel_t;

/* Codec I2S config */
typedef enum
{
    PSD_DAC_I2S_MODE_SLAVE  = 0,
    PSD_DAC_I2S_MODE_MASTER = 1,

    PSD_DAC_I2S_STANDARD_LSB     = 0,
    PSD_DAC_I2S_STANDARD_MSB     = 1,
    PSD_DAC_I2S_STANDARD_PHILIPS = 2,

    PSD_DAC_I2S_DATA_FORMAT_16BIT = 0,
    PSD_DAC_I2S_DATA_FORMAT_20BIT = 1,
    PSD_DAC_I2S_DATA_FORMAT_24BIT = 2,

    PSD_DAC_I2S_CHANNEL_COPY_DISABLE = 0,
    PSD_DAC_I2S_CHANNEL_COPY_ENABLE  = 1,
}enum_PSD_DAC_I2S_Config_t;

/* PSD DAC function enable/disable select */
typedef enum
{
    PSD_DAC_FUNC_DISABLE,     /*!< function disable */
    PSD_DAC_FUNC_ENABLE,      /*!< function enable  */
}enum_PSD_DAC_func_en_t;

/* DAC data */
typedef union 
{
    volatile void      *p_data;
    volatile uint8_t   *p_u8;
    volatile uint16_t  *p_u16;
    volatile uint32_t  *p_u32;
}union_PSD_DACData_t;

/*
 * @brief PSD DAC Init Structure definition
 */
typedef struct
{
    uint32_t DataSrc;               /*!< Specifies the data source.
                                         This parameter can be a value of @ref enum_PSD_DAC_DataSrc_t */

    uint32_t Right_mix;             /*!< Specifies the right channel mix enable.
                                         This parameter can be a value of @ref enum_PSD_DAC_func_en_t */
    uint32_t Left_mix;              /*!< Specifies the left channel mix enable.
                                         This parameter can be a value of @ref enum_PSD_DAC_func_en_t */

    uint32_t MonoEn;                /*!< Specifies the play mode, Stereo or mono.
                                         This parameter can be a value of @ref enum_PSD_DAC_func_en_t */

    uint32_t ClockSource;               /*!< Specifies the DAC Clcok Source.
                                                 This parameter can be a value of @ref enum_PSD_DAC_Clcok_Src_t. */

    uint32_t SampleRate;                /*!< Specifies the DAC Sample Rate.
                                                 This parameter can be a value of @ref enum_PSD_DAC_SampleRate_t. */

    uint32_t Oversampling_Level;        /*!< Specifies the DAC Oversampling level.
                                                 This parameter can be a value of @ref enum_PSD_DAC_Oversampling_level_t. */

        /* ----------------------------------------------------------------------------- */
        /* Set the following parameters when DataSrc select PSD_DAC_DATA_SOURCE_DACFIFO. */
        /* ----------------------------------------------------------------------------- */
        uint32_t DAC_DataFormat;                /*!< Specifies the ADC FIFO Data Format.
                                                    This parameter can be a value of @ref enum_PSD_DAC_DacFIFO_Format_t. */

        uint32_t DAC_FIFOCombine;               /*!< Specifies the DAC FIFO operation mode.
                                                    This parameter can be a value of @ref enum_PSD_DAC_func_en_t */
                                                    /// note: when use 8bit/16bit data Format, data can be merged into the left channel.
                                                    /// use 20bit/24bit data Format, Combine func invalid.
        
        uint32_t DAC_FIFOThreshold;             /* !< Specifies the DAC FIFO almost empty threshold.
                                                    This parameter can be a value 1 ~ 63 */

        /* ----------------------------------------------------------------------------- */
        /* Set the following parameters when DataSrc select PSD_DAC_DATA_SOURCE_I2SRX.   */
        /* ----------------------------------------------------------------------------- */
        uint32_t I2S_Mode;                  /*!< Specifies the I2S operating mode.
                                                This parameter can be a value of @ref enum_PSD_DAC_I2S_Config_t */

        uint32_t I2S_Standard;              /*!< Specifies the communication standard.
                                                This parameter can be a value of @ref enum_PSD_DAC_I2S_Config_t */

        uint32_t I2S_DataFormat;            /*!< Specifies the I2S data format.
                                                This parameter can be a value of @ref enum_PSD_DAC_I2S_Config_t */

        uint32_t I2S_ChannelCopy;           /*!< Specifies the I2S Channel Copy Enable.(Left Data copy to right)
                                                This parameter can be a value of @ref enum_PSD_DAC_I2S_Config_t */

            /* ============================================================================= */
            /* Set the following parameters when I2S_Mode select PSD_DAC_I2S_MODE_MASTER.    */
            /* ============================================================================= */
            uint32_t BCLK_Source;           /*!< Specifies the BCLK source select.
                                                This parameter can be a value of @ref enum_PSD_DAC_BCLK_Config_t. */

            uint32_t BCLK_DIV;              /*!< Specifies the MCLK DIV.
                                                This parameter can be a 16-bit value. */
                                                /// note: BCLK = BCLK Source clock/ BCLK_DIV.

            uint32_t LRCLK_DIV;             /*!< Specifies the LRCLK DIV.
                                                This parameter can be a 16-bit value. */
                                                /// note: LRCLK = BCLK / LRCLK_DIV.
}struct_PSD_DACInit_t;

/*
 * @brief I2S MCLK parameter config
 */
typedef struct
{
    uint32_t MCLK_Source;        /*!< Specifies the MCLK source select.
                                      This parameter can be a value of @ref enum_PSD_DAC_MCLK_Config_t. */

    uint32_t MCLK_DIV_Type;      /*!< Specifies the MCLK DIV mode select.
                                      This parameter can be a value of @ref enum_PSD_DAC_MCLK_Config_t. */

                                /// note: select MCLK_DIV_MODE_INTEGER. MCLK = MCLK_Source / (MCLK_DIV + 1)
                                ///       select MCLK_DIV_MODE_FLOAT.   MCLK = MCLK_Source / ((MCLK_DIV + 1) / 2)

    uint32_t MCLK_DIV;           /*!< Specifies the MCLK DIV.
                                      This parameter can be a 10-bit value. */
}struct_PSD_DAC_MCLKConfig_t;

/*
 * @brief  PSD_DAC handle Structure definition
 */
typedef struct __PSD_DAC_HandleTypeDef
{
    struct_PSD_DACInit_t    Init;               /*!< PSD DAC communication parameters      */

    void (*DAC_FIFO_LeftEmpty_Callback)(struct __PSD_DAC_HandleTypeDef *hpsd);
    void (*DAC_FIFO_RightEmpty_Callback)(struct __PSD_DAC_HandleTypeDef *hpsd);
    void (*DAC_FIFO_LeftAlmostEmpty_Callback)(struct __PSD_DAC_HandleTypeDef *hpsd);
    void (*DAC_FIFO_RightAlmostEmpty_Callback)(struct __PSD_DAC_HandleTypeDef *hpsd);
}PSD_DAC_HandleTypeDef;

/* ################################ Initialization Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* PSD DAC clock enable/disable */
#define __PSD_DAC_I2S_CLOCK_ENABLE()                        (PSD_DAC->ClockEnable |= 0x02)
#define __PSD_DAC_I2S_CLOCK_DISABLE()                       (PSD_DAC->ClockEnable &= 0xFD)
#define __PSD_DAC_DAC_CLOCK_ENABLE()                        (PSD_DAC->ClockEnable |= 0x01)
#define __PSD_DAC_DAC_CLOCK_DISABLE()                       (PSD_DAC->ClockEnable &= 0xFE)
/* PSD DAC mode enable/disable */
#define __PSD_DAC_I2S_ENABLE()                              (PSD_DAC->ModeEnable |= 0x02)
#define __PSD_DAC_I2S_DISABLE()                             (PSD_DAC->ModeEnable &= 0xFD)
#define __PSD_DAC_DAC_ENABLE()                              (PSD_DAC->ModeEnable |= 0x01)
#define __PSD_DAC_DAC_DISABLE()                             (PSD_DAC->ModeEnable &= 0xFE)

/* PSD DAC reset */
#define __PSD_DAC_DAC_RESET()                             do{PSD_DAC->SoftReset = 0x01; \
                                                             while(PSD_DAC->SoftReset);} while(0)
#define __PSD_DAC_I2S_RESET()                             do{PSD_DAC->SoftReset = 0x02; \
                                                             while(PSD_DAC->SoftReset);} while(0)
#define __PSD_DAC_DAC_FIFO_RESET()                        do{PSD_DAC->SoftReset = 0x1C; \
                                                             while(PSD_DAC->SoftReset);} while(0)
#define __PSD_DAC_RESET()                                 do{PSD_DAC->SoftReset = 0x1F; \
                                                             while(PSD_DAC->SoftReset);} while(0)

/* Set audio pll divider */
#define __PSD_DAC_SET_AUPLL_DIV(__DIV__)                    (PSD_DAC->AudioPLLPreDiv = __DIV__)

/* MCLK out config */
#define __PSD_DAC_MCLK_ENABLE()                             (PSD_DAC->MCLKCfg.MCLK_OUT_EN = 1)
#define __PSD_DAC_MCLK_DISABLE()                            (PSD_DAC->MCLKCfg.MCLK_OUT_EN = 0)
#define __PSD_DAC_MCLK_SOURCE_SELECT(__SELECT__)            (PSD_DAC->MCLKCfg.MCLK_SRC = __SELECT__)
#define __PSD_DAC_MCLK_DIV_TYPE(__TYPE__)                   (PSD_DAC->MCLKCfg.MCLK_DIV_TYPE = __TYPE__)
#define __PSD_DAC_MCLK_DIV(__DIV__)                         (PSD_DAC->MCLKCfg.MCLK_DIV = __DIV__)

/* PSD DAC config */
#define __PSD_DAC_USB_MODE_ENABLE()                         (PSD_DAC->DACCfg.USB_MODE = 1)
#define __PSD_DAC_NORMAL_MODE_ENABLE()                      (PSD_DAC->DACCfg.USB_MODE = 0)
#define __PSD_DAC_SAMPLING_RATE(__RATE__)                   (PSD_DAC->DACCfg.SAMPLE_RATE = __RATE__)
#define __PSD_DAC_OVERSAMPLING_RATE_MODE(__MODE__)          (PSD_DAC->DACCfg.OVER_SAMPLE_MODE = __MODE__)
#define __PSD_DAC_MONO_ENABLE()                             (PSD_DAC->DACCfg.MONO_EN = 1)
#define __PSD_DAC_STEREO_ENABLE()                           (PSD_DAC->DACCfg.MONO_EN = 0)
#define __PSD_DAC_MONO_SELECT(__CH__)                       (PSD_DAC->DACCfg.MONO_SELECT = __CH__)
#define __PSD_DAC_SWAP_ENABLE()                             (PSD_DAC->DACCfg.SWAP_EN = 1)
#define __PSD_DAC_SWAP_DISABLE()                            (PSD_DAC->DACCfg.SWAP_EN = 0)
#define __PSD_DAC_CLOCK_SRC(__SRC__)                        (PSD_DAC->DACCfg.DAC_CLK_SRC = __SRC__)
#define __PSD_DAC_DATA_SRC(__SRC__)                         (PSD_DAC->DACCfg.DAC_DATA_SRC = __SRC__)

#define __PSD_DAC_LEFT_CHANNEL_MIX_ENABLE()                 (PSD_DAC->DACCfg.LEFT_MIX_EN  = 1)
#define __PSD_DAC_LEFT_CHANNEL_MIX_DISABLE()                (PSD_DAC->DACCfg.LEFT_MIX_EN  = 0)
#define __PSD_DAC_LEFT_CHANNEL_MIX_CONFIG(__CFG__)          (PSD_DAC->DACCfg.LEFT_MIX_EN  = __CFG__)
#define __PSD_DAC_RIGHT_CHANNEL_MIX_ENABLE()                (PSD_DAC->DACCfg.RIGHT_MIX_EN = 1)
#define __PSD_DAC_RIGHT_CHANNEL_MIX_DISABLE()               (PSD_DAC->DACCfg.RIGHT_MIX_EN = 0)
#define __PSD_DAC_RIGHT_CHANNEL_MIX_CONFIG(__CFG__)         (PSD_DAC->DACCfg.RIGHT_MIX_EN = __CFG__)

#define __PSD_DAC_PWMCLK_INVERT_ENABLE()                    (PSD_DAC->DACCfg.PWM_CLK_INV_EN = 1)
#define __PSD_DAC_PWMCLK_INVERT_DISABLE()                   (PSD_DAC->DACCfg.PWM_CLK_INV_EN = 0)

/* mute */
#define __PSD_DAC_MUTE_CTRL(__CTRL__)                       (PSD_DAC->MuteCtrl = __CTRL__)
#define __PSD_DAC_MUTE_ENABLE()                             (PSD_DAC->MuteCtrl = 0x03)
#define __PSD_DAC_MUTE_DISABLE()                            (PSD_DAC->MuteCtrl = 0x00)
/* set volume */
#define __PSD_DAC_SET_RIGHT_VOLUME(__VOL__)                 (PSD_DAC->Volume.RIGHT_VOLUME = __VOL__)
#define __PSD_DAC_SET_LEFT_VOLUME(__VOL__)                  (PSD_DAC->Volume.LEFT_VOLUME = __VOL__)
/* gain compensate */
#define __PSD_DAC_SET_GAIN_COMPENSATE(__GAIN__)             (PSD_DAC->GainCompensate = __GAIN__)

/* PSD I2S config */
#define __PSD_DAC_I2S_FORAMT(__FORMAT__)                    (PSD_DAC->I2STxCtrl.FORMAT = __FORMAT__)
#define __PSD_DAC_I2S_DATA_WIDTH(__WIDTH__)                 (PSD_DAC->I2STxCtrl.DCI_WL = __WIDTH__)
#define __PSD_DAC_I2S_LRCLK_INVERT_ENABLE()                 (PSD_DAC->I2STxCtrl.LR_POL = 1)
#define __PSD_DAC_I2S_LRCLK_INVERT_DISABLE()                (PSD_DAC->I2STxCtrl.LR_POL = 0)
#define __PSD_DAC_I2S_SWAP_ENABLE()                         (PSD_DAC->I2STxCtrl.LR_SWAP = 1)
#define __PSD_DAC_I2S_SWAP_DISABLE()                        (PSD_DAC->I2STxCtrl.LR_SWAP = 0)
#define __PSD_DAC_I2S_CHANNEL_COPY_ENABLE()                 (PSD_DAC->I2STxCtrl.CHANNEL_CP = 1)
#define __PSD_DAC_I2S_CHANNEL_COPY_DISABLE()                (PSD_DAC->I2STxCtrl.CHANNEL_CP = 0)
#define __PSD_DAC_I2S_CHANNEL_COPY_CONFIG(__CFG__)          (PSD_DAC->I2STxCtrl.CHANNEL_CP = __CFG__)
#define __PSD_DAC_I2S_INTERNAL_MCLK_INV_ENABLE()            (PSD_DAC->I2STxCtrl.IBCLK_INV = 1)
#define __PSD_DAC_I2S_INTERNAL_MCLK_INV_DISABLE()           (PSD_DAC->I2STxCtrl.IBCLK_INV = 0)
#define __PSD_DAC_I2S_OUT_MCLK_INV_ENABLE()                 (PSD_DAC->I2STxCtrl.OBCLK_INV = 1)
#define __PSD_DAC_I2S_OUT_MCLK_INV_DISABLE()                (PSD_DAC->I2STxCtrl.OBCLK_INV = 0)
#define __PSD_DAC_I2S_MASTER_MODE()                         (PSD_DAC->I2STxCtrl.I2S_MODE = 1)
#define __PSD_DAC_I2S_SLAVE_MODE()                          (PSD_DAC->I2STxCtrl.I2S_MODE = 0)
#define __PSD_DAC_I2S_MODE_CONFIG(__CFG__)                  (PSD_DAC->I2STxCtrl.I2S_MODE = __CFG__)
#define __PSD_DAC_I2S_BCLK_SRC(__SRC__)                     (PSD_DAC->I2STxCtrl.BCLK_SRC = __SRC__)

#define __PSD_DAC_I2S_BCLK_DIV(__DIV__)                     (PSD_DAC->I2STxClkCtrl.BCLK_DIV  = __DIV__)
#define __PSD_DAC_I2S_LRCLK_DIV(__DIV__)                    (PSD_DAC->I2STxClkCtrl.LRCLK_DIV = __DIV__)

/* FIFO config */
#define __PSD_DAC_FIFO_SET_BITWD_LEFT(__WIDTH__)            (PSD_DAC->DACFIFOCtrl.DACFF_BITWD_L = __WIDTH__)
#define __PSD_DAC_FIFO_SET_BITWD_RIGHT(__WIDTH__)           (PSD_DAC->DACFIFOCtrl.DACFF_BITWD_R = __WIDTH__)
#define __PSD_DAC_FIFO_GET_BITWD_LEFT()                     (PSD_DAC->DACFIFOCtrl.DACFF_BITWD_L)
#define __PSD_DAC_FIFO_GET_BITWD_RIGHT()                    (PSD_DAC->DACFIFOCtrl.DACFF_BITWD_R)

#define __PSD_DAC_FIFO_OP_MODE(__MODE__)                    (PSD_DAC->DACFIFOCtrl.DACFF_OP_MODE_EN = __MODE__)

#define __PSD_DAC_FIFO_EMPTY_THRESHOLD_LEFT(__THRE__)       (PSD_DAC->DACFIFOThd.DAC_FIFO_Threshold_Left  = __THRE__)
#define __PSD_DAC_FIFO_EMPTY_THRESHOLD_RIGHT(__THRE__)      (PSD_DAC->DACFIFOThd.DAC_FIFO_Threshold_Right = __THRE__)

/* write fifo */
#define __PSD_DAC_WRITE_FIFO_DATA_LEFT(__DATA__)            (PSD_DAC->DACDataL = __DATA__)
#define __PSD_DAC_WRITE_FIFO_DATA_RIGHT(__DATA__)           (PSD_DAC->DACDataR = __DATA__)

/* DMA control */
#define __PSD_DAC_DMA_ENABLE()                              (PSD_DAC->DACDmaEn = 0x03)
#define __PSD_DAC_DMA_DISABLE()                             (PSD_DAC->DACDmaEn = 0x00)
#define __PSD_DAC_DMA_THRESHOLD_LEFT(__THRE__)              (PSD_DAC->DACDmaThd.DAC_DMA_Threshold_Left  = __THRE__)
#define __PSD_DAC_DMA_THRESHOLD_RIGHT(__THRE__)             (PSD_DAC->DACDmaThd.DAC_DMA_Threshold_Right = __THRE__)

/* interrupt status enable */
#define __PSD_DAC_STATUS_ENABLE(__STATUS__)                 (PSD_DAC->DACIntEn |= (__STATUS__))
#define __PSD_DAC_STATUS_DISABLE(__STATUS__)                (PSD_DAC->DACIntEn &= ~(__STATUS__))
#define __PSD_DAC_GET_INT_STATUS(__STATUS__)                (PSD_DAC->DACIntStatus)
#define __PSD_DAC_GET_INT_RAW_STATUS(__STATUS__)            (PSD_DAC->DACIntRawStatus)

/* get fifo status */
#define __PSD_DAC_IS_FIFO_FULL_LEFT()                       (PSD_DAC->DACIntRawStatus & PSD_DAC_INT_DACFF_L_FULL)
#define __PSD_DAC_IS_FIFO_FULL_RIGHT()                      (PSD_DAC->DACIntRawStatus & PSD_DAC_INT_DACFF_R_FULL)
#define __PSD_DAC_IS_FIFO_EMPTY_LEFT()                      (PSD_DAC->DACIntRawStatus & PSD_DAC_INT_DACFF_L_EMPTY)
#define __PSD_DAC_IS_FIFO_EMPTY_RIGHT()                     (PSD_DAC->DACIntRawStatus & PSD_DAC_INT_DACFF_R_EMPTY)
#define __PSD_DAC_IS_FIFO_ALMOST_EMPTY_LEFT()               (PSD_DAC->DACIntRawStatus & PSD_DAC_INT_DACFF_L_AEMPTY)
#define __PSD_DAC_IS_FIFO_ALMOST_EMPTY_RIGHT()              (PSD_DAC->DACIntRawStatus & PSD_DAC_INT_DACFF_R_AEMPTY)

/* Exported functions ---------------------------------------------------------*/

/* psd_dac_init */
void psd_dac_init(PSD_DAC_HandleTypeDef *hpsd);

/* psd_dac_mute_contrl */
void psd_dac_mute_contrl(enum_PSD_DAC_Channel_t fe_Channel);

/* set volume */
void psd_dac_set_volume(enum_PSD_DAC_Channel_t fe_Channel, uint16_t fu16_Volume);
/* set dac fifo threshold */
void psd_dac_set_dac_fifothreshold(uint16_t fu16_thr);
/* set sampling rate */
void psd_dac_set_samplerate(enum_PSD_DAC_SampleRate_t fe_rate);
/* set Data bit width */
void psd_dac_set_dataformat(enum_PSD_DAC_DacFIFO_Format_t fe_format);
/* psd_dac_set_gain_compensate */
void psd_dac_set_gain_compensate(uint16_t fu16_comp);

/* i2s mclk config/output enable/output disable */
void psd_dac_i2s_mclk_config(struct_PSD_DAC_MCLKConfig_t *sConfig);
void psd_dac_i2s_mclk_out_enable(void);
void psd_dac_i2s_mclk_out_disable(void);

/* interrupt enable/disable */
/* interrupt status/raw status */
void psd_dac_int_enable(enum_PSD_DAC_INT_Status_t fe_Int_Status);
void psd_dac_int_disable(enum_PSD_DAC_INT_Status_t fe_Int_Status);
uint32_t psd_dac_int_get_status(void);
uint32_t psd_dac_int_get_raw_status(void);

/* write dac FIFO */
void psd_dac_write_dac_fifo_left(void *fp_data, uint32_t fu32_length);
void psd_dac_write_dac_fifo_right(void *fp_data, uint32_t fu32_length);
void psd_dac_write_dac_fifo_left_right(void *fp_data, uint32_t fu32_length);
bool psd_dac_write_dac_fifo_Combine(void *fp_data, uint32_t fu32_length);

#endif  // __DRIVER_PWM_SIGMA_DELTA_DAC_H__
