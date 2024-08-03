/*
  ******************************************************************************
  * @file    driver_i2s.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of I2S HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_I2S_H__
#define __DRIVER_I2S_H__

#include "fr30xx.h"

/** @addtogroup I2S_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* I2S control 0 Register */
typedef struct
{
    uint32_t MSTSLV      : 1;
    uint32_t LR_WD_EN    : 1;
    uint32_t INTEN       : 1;
    uint32_t LR_WD_SWAP  : 1;
    uint32_t RXFF_R_EN   : 1;
    uint32_t RXFF_L_EN   : 1;
    uint32_t TXFF_R_EN   : 1;
    uint32_t TXFF_L_EN   : 1;
    uint32_t RXFF_R_CLR  : 1;
    uint32_t RXFF_L_CLR  : 1;
    uint32_t TXFF_R_CLR  : 1;
    uint32_t TXFF_L_CLR  : 1;      
    uint32_t rsv_0       : 4;
    uint32_t SBC_ACCESS  : 1;
    uint32_t rsv_1       : 15;
}REG_I2S_CTRL0_t;

/* frame divder Register */
typedef struct
{
    uint32_t BCLKDIV   : 16;    
    uint32_t FRMDIV    : 16;    
}REG_FRM_DIV_t;

/* I2S control 1 Register */
typedef struct
{
    uint32_t I2S_EN            : 1;
    uint32_t I2S_FRMINV        : 1;
    uint32_t I2S_BCLKINV       : 1;
    uint32_t I2S_LP            : 1;
    uint32_t I2S_HLSEL         : 1;
    uint32_t A2DP_SYNC_DISABLE : 1;
    uint32_t rsv_0             : 1;
    uint32_t I2S_NORMAL        : 1;
    uint32_t I2S_ADJUST        : 1;
    uint32_t I2S_LSB1ST        : 1;
    uint32_t rsv_1             : 2;
    uint32_t I2S_DATA_LENGTH   : 3;
    uint32_t rsv_2             : 1;
    uint32_t I2SFBOFF          : 16;
}REG_I2S_CTRL1_t;

/* FIFO config right Register */
typedef struct
{
    uint32_t TXFF_AEMPTY : 8;
    uint32_t TXFF_AFULL  : 8;
    uint32_t RXFF_AEMPTY : 8;
    uint32_t RXFF_AFULL  : 8;
}REG_FIFO_CFG_t;

/* DMA config Register */
typedef struct
{
    uint32_t DMACR_L_TX : 1;
    uint32_t DMACR_R_TX : 1;
    uint32_t DMACR_L_RX : 1;
    uint32_t DMACR_R_RX : 1;
    uint32_t rsv_0      : 4; 
    uint32_t DMARDLR    : 5;
    uint32_t rsv_1      : 3;    
    uint32_t DMATDLR    : 5;
    uint32_t rsv_2      : 11;
}REG_I2S_DMA_CFG_t;

/* PCM general Register */
typedef struct
{
    uint32_t PCM_EN          : 1;
    uint32_t PCM_LRSWAP      : 1;
    uint32_t PCM_BYTESWAP    : 1;
    uint32_t PCM_PLL_EN      : 1;
    uint32_t PCM_MONO_STEREO : 1;
    uint32_t PCM_MONO_LR_SEL : 1;
    uint32_t PCM_LOOPBACK    : 1;
    uint32_t PCM_CLKINV      : 1; 
    uint32_t PCM_SLVBFMST    : 1; 
    uint32_t PCM_SET_FRAME   : 1; 
    uint32_t rsv_0           : 22;
}REG_PCM_GENCTRL_t;

/* PCM PHY CTRL Register */
typedef struct
{
    uint32_t PCM_FSYNCSHP     : 3;
    uint32_t rsv_0            : 1;
    uint32_t PCM_DOUTCFG      : 2;
    uint32_t rsv_1            : 2;
    uint32_t PCM_LRCHPOL      : 1;
    uint32_t PCM_IOM          : 1;
    uint32_t PCM_LSB1ST       : 1;
    uint32_t rsv_2            : 1; 
    uint32_t PCM_SAMPSZ       : 1; 
    uint32_t PCM_SAMPTYPE     : 1; 
    uint32_t rsv_3            : 2;
    uint32_t PCM_SLOTNB       : 3;
    uint32_t rsv_4            : 1;
    uint32_t PCM_FIRSTACTSLOT : 2;
    uint32_t rsv_5            : 10;
}REG_PCM_PHYCTRL_t;

/* PCM PHY CTRL Register */
typedef struct
{
    uint32_t PCM_LSAMPPAD : 16;
    uint32_t PCM_RSAMPPAD : 16;
}REG_PCM_PADDING_t;

/* PCM MUTE Register */
typedef struct
{
    uint32_t PCM_MUTE_PATT : 16;
    uint32_t rsv_0         : 15;
    uint32_t PCM_MUTE_EN   : 1;
}REG_PCM_MUTE_t;

/* -----------------------------------------------*/
/*                   I2S Register                 */
/* -----------------------------------------------*/
typedef struct 
{
    volatile REG_I2S_CTRL0_t      CTRL0;            /* Offset 0x00 */
    volatile REG_FRM_DIV_t        FrmDiv;           /* Offset 0x04 */
    volatile REG_I2S_CTRL1_t      CTRL1;            /* Offset 0x08 */
    volatile uint32_t             DATA_L;           /* Offset 0x0C */
    volatile uint32_t             DATA_R;           /* Offset 0x10 */
    volatile uint32_t             INT_STATUS;       /* Offset 0x14 */
    volatile uint32_t             INT_STATUS_EN;    /* Offset 0x18 */
    volatile REG_FIFO_CFG_t       FIFO_CFG_L;       /* Offset 0x1C */
    volatile REG_FIFO_CFG_t       FIFO_CFG_R;       /* Offset 0x20 */
    volatile REG_I2S_DMA_CFG_t    DMA_CFG;          /* Offset 0x24 */
    volatile REG_PCM_GENCTRL_t    PCM_GENCTRL;      /* Offset 0x28 */
    volatile REG_PCM_PHYCTRL_t    PCM_RHYCTRL;      /* Offset 0x2C */
    volatile REG_PCM_PADDING_t    PCM_PADDING;      /* Offset 0x30 */
    volatile REG_PCM_MUTE_t       PCM_MUTE;         /* Offset 0x34 */
}struct_I2S_t;

#define I2S0    ((struct_I2S_t *)I2S0_BASE)
#define I2S1    ((struct_I2S_t *)I2S1_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup I2S_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

#define I2S_FIFO_DEPTH                (32)
#define I2S_FIFO_HALF_DEPTH           (I2S_FIFO_DEPTH >> 1)

/* FIFO Status start */
#define    I2S_RX_FIFOS_FULL          (0x00001)
#define    I2S_RX_FIFOS_HALF_FULL     (0x00002)
#define    I2S_RX_FIFOS_EMPTY         (0x00004)
#define    I2S_RX_L_FIFO_FULL         (0x00008)
#define    I2S_RX_L_FIFO_HALF_FULL    (0x00010)
#define    I2S_RX_L_FIFO_EMPTY        (0x00020)
#define    I2S_RX_R_FIFO_FULL         (0x00040)
#define    I2S_RX_R_FIFO_HALF_FULL    (0x00080)
#define    I2S_RX_R_FIFO_EMPTY        (0x00100)
#define    I2S_TX_FIFOS_FULL          (0x00200)
#define    I2S_TX_FIFOS_ALMOST_EMPTY  (0x00400)
#define    I2S_TX_FIFOS_EMPTY         (0x00800)
#define    I2S_TX_L_FIFO_FULL         (0x01000)
#define    I2S_TX_L_FIFO_ALMOST_EMPTY (0x02000)
#define    I2S_TX_L_FIFO_EMPTY        (0x04000)
#define    I2S_TX_R_FIFO_FULL         (0x08000)
#define    I2S_TX_R_FIFO_ALMOST_EMPTY (0x10000)
#define    I2S_TX_R_FIFO_EMPTY        (0x20000)
#define    I2S_ALL_FIFO_STATUS        (0x3FFFF)
/* FIFO Status end */

/* I2S Mode */
typedef enum
{
    I2S_MODE_MASTER,
    I2S_MODE_SLAVE,
}enum_I2S_Mode_t;

/* I2S Standard */
typedef enum
{
    I2S_STANDARD_PHILIPS,
    I2S_STANDARD_MSB,
    I2S_STANDARD_LSB,
    I2S_STANDARD_PCM,
}enum_I2S_Standard_t;

/* I2S Data Format */
typedef enum
{
    I2S_DATA_FORMAT_8BIT,
    I2S_DATA_FORMAT_16BIT,
    I2S_DATA_FORMAT_20BIT,
    I2S_DATA_FORMAT_24BIT,
    I2S_DATA_FORMAT_32BIT,
}enum_I2S_DataFormat_t;

/*
 * @brief I2S Init Structure definition
 */
typedef struct
{
    uint32_t Mode;                      /*!< Specifies the I2S operating mode.
                                             This parameter can be a value of @ref enum_I2S_Mode_t */

    uint32_t Standard;                  /*!< Specifies the communication standard.
                                             This parameter can be a value of @ref enum_I2S_Standard_t */

    uint32_t DataFormat;                /*!< Specifies the data format.
                                             This parameter can be a value of @ref enum_I2S_DataFormat_t */
    
    uint32_t BCLKDIV;                   /*!< Specifies the clock dividor used to generate bclk.
                                             This parameter can be a even value of between 0x000 ~ 0xFFF. */
    
    uint32_t ChannelLength;             /*!< Specifies the channel length.
                                             This parameter can be a even value of between 0x000 ~ 0xFFF. */

    uint32_t AudioFreq;                 /*!< Specifies the frequency selected for the I2S communication.
                                             This parameter can be a value of @ref I2S_Audio_Frequency */   

}struct_I2SInit_t;

/*
 * @brief PCM Init Structure definition
 */
typedef struct
{
    
}struct_PCMInit_t;

/*
 * @brief  I2S handle Structure definition
 */
typedef struct __I2S_HandleTypeDef
{
    struct_I2S_t           *I2Sx;               /*!< I2S registers base address        */

    struct_I2SInit_t        Init;               /*!< I2S communication parameters      */

    struct_PCMInit_t        PCM_Init;           /*!< PCM communication parameters      */
    
    volatile bool           b_TxBusy;
    void (*TxIntCallback)(struct __I2S_HandleTypeDef *hi2s);       /*!< Tx Interrupt Callback */

    volatile bool           b_RxBusy;
    void (*RxIntCallback)(struct __I2S_HandleTypeDef *hi2s);       /*!< Rx Interrupt Callback */

}I2S_HandleTypeDef;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* I2s and PCM Enable/Disable */
#define __I2S_ENABLE(__I2Sx__)                                   (__I2Sx__->CTRL1.I2S_EN = 1)
#define __I2S_DISABLE(__I2Sx__)                                  (__I2Sx__->CTRL1.I2S_EN = 0)

#define __I2S_PCM_ENABLE(__I2Sx__)                               do{ __I2Sx__->PCM_GENCTRL.PCM_PLL_EN = 1; \
                                                                     __I2Sx__->PCM_GENCTRL.PCM_EN     = 1;}while(0)

#define __I2S_PCM_DISABLE(__I2Sx__)                              do{ __I2Sx__->PCM_GENCTRL.PCM_PLL_EN = 0; \
                                                                     __I2Sx__->PCM_GENCTRL.PCM_EN     = 0;}while(0)

/* RxFIFO/TxFIFO clear */
#define __I2S_TxFIFO_CLR(__I2Sx__)                               do{ __I2Sx__->CTRL0.TXFF_R_CLR = 1; \
                                                                     __I2Sx__->CTRL0.TXFF_L_CLR = 1;}while(0)
                                                                 
#define __I2S_RxFIFO_CLR(__I2Sx__)                               do{ __I2Sx__->CTRL0.RXFF_R_CLR = 1; \
                                                                     __I2Sx__->CTRL0.RXFF_L_CLR = 1;}while(0)
                                                                 
/* TxFIFO/RxFIFO enable */                                       
#define __I2S_TxFIFO_EN(__I2Sx__)                                do{ __I2Sx__->CTRL0.TXFF_L_EN = 1; \
                                                                     __I2Sx__->CTRL0.TXFF_R_EN = 1; }while(0)

#define __I2S_RxFIFO_EN(__I2Sx__)                                do{ __I2Sx__->CTRL0.RXFF_L_EN = 1; \
                                                                     __I2Sx__->CTRL0.RXFF_R_EN = 1;}while(0) 

/* TxFIFO Data from sbcdecode or cpu*/
#define __I2S_TXFIFO_SOURCE_SBC_DECODE(__I2Sx__)                 (__I2Sx__->CTRL0.SBC_ACCESS = 1)
#define __I2S_TXFIFO_SOURCE_CPU(__I2Sx__)                        (__I2Sx__->CTRL0.SBC_ACCESS = 0)

/* enable channels Operate Simultaneously*/              
#define __I2S_LR_WD_ENABLE(__I2Sx__)                             (__I2Sx__->CTRL0.LR_WD_EN = 1)
#define __I2S_LR_WD_DISABLE(__I2Sx__)                            (__I2Sx__->CTRL0.LR_WD_EN = 0)
                                                              
#define __I2S_WD_SWAP_HIGH16SIZE_RIGHT(__I2Sx__)                 (__I2Sx__->CTRL0.LR_WD_SWAP = 1)   
#define __I2S_WD_SWAP_HIGH16SIZE_LEFT(__I2Sx__)                  (__I2Sx__->CTRL0.LR_WD_SWAP = 0)
                                                              
/* Status interrupt enable and disable */                     
#define __I2S_INT_ENABLE(__I2Sx__, __STATUS__)                   do{ __I2Sx__->CTRL0.INTEN = 1; \
                                                                     __I2Sx__->INT_STATUS_EN |= __STATUS__;}while(0)
                                                                
#define __I2S_INT_DISABLE(__I2Sx__, __STATUS__)                  do{ __I2Sx__->CTRL0.INTEN = 0; \
                                                                     __I2Sx__->INT_STATUS_EN &= ~__STATUS__;}while(0)

#define __I2S_INT_IS_ENANLE(__I2Sx__, __STATUS__)                (__I2Sx__->INT_STATUS_EN & __STATUS__)
                                                                  
 /* Get interrupt status */                                                                 
#define __I2S_GET_INT_STATUS(__I2Sx__)                           (__I2Sx__->INT_STATUS)

/* Left/Right Rxfifo txfifo full/empty level */
#define __I2S_L_RxFIFO_FULL_LEVEL(__I2Sx__, __LEVEL__)           (__I2Sx__->FIFO_CFG_L.RXFF_AFULL  = __LEVEL__)
#define __I2S_L_RxFIFO_EMPTY_LEVEL(__I2Sx__, __LEVEL__)          (__I2Sx__->FIFO_CFG_L.RXFF_AEMPTY = __LEVEL__)
#define __I2S_L_TxFIFO_FULL_LEVEL(__I2Sx__, __LEVEL__)           (__I2Sx__->FIFO_CFG_L.TXFF_AFULL  = __LEVEL__)
#define __I2S_L_TxFIFO_EMPTY_LEVEL(__I2Sx__, __LEVEL__)          (__I2Sx__->FIFO_CFG_L.TXFF_AEMPTY = __LEVEL__)

#define __I2S_R_RxFIFO_FULL_LEVEL(__I2Sx__, __LEVEL__)           (__I2Sx__->FIFO_CFG_R.RXFF_AFULL  = __LEVEL__)
#define __I2S_R_RxFIFO_EMPTY_LEVEL(__I2Sx__, __LEVEL__)          (__I2Sx__->FIFO_CFG_R.RXFF_AEMPTY = __LEVEL__)
#define __I2S_R_TxFIFO_FULL_LEVEL(__I2Sx__, __LEVEL__)           (__I2Sx__->FIFO_CFG_R.TXFF_AFULL  = __LEVEL__)
#define __I2S_R_TxFIFO_EMPTY_LEVEL(__I2Sx__, __LEVEL__)          (__I2Sx__->FIFO_CFG_R.TXFF_AEMPTY = __LEVEL__)

/* BCLK Inverted Output */
#define __I2S_BCLK_INV_ENABLE(__I2Sx__)                          (__I2Sx__->CTRL1.I2S_BCLKINV = 1)
#define __I2S_BCLK_INV_DISABLE(__I2Sx__)                         (__I2Sx__->CTRL1.I2S_BCLKINV = 0)

/* Frame Inverted Output */
#define __I2S_FRAME_INV_ENABLE(__I2Sx__)                         (__I2Sx__->CTRL1.I2S_FRMINV = 1)
#define __I2S_FRAME_INV_DISABLE(__I2Sx__)                        (__I2Sx__->CTRL1.I2S_FRMINV = 0)

/* PCMCLK Inverted Output */                                 
#define __I2S_PCMCLK_INV_ENABLE(__I2Sx__)                        (__I2Sx__->PCM_GENCTRL.PCM_CLKINV = 1) 
#define __I2S_PCMCLK_INV_DISABLE(__I2Sx__)                       (__I2Sx__->PCM_GENCTRL.PCM_CLKINV = 0) 

/* PCM SLOTS SET */
#define __I2S_PCM_SLOTS_SET(__I2Sx__, __LEVEL__)                 (__I2Sx__->PCM_RHYCTRL.PCM_SLOTNB = __LEVEL__) 
#define __I2S_PCM_FIRSTSLOTS_SET(__I2Sx__, __CONFIGURE__)        (__I2Sx__->PCM_RHYCTRL.PCM_FIRSTACTSLOT = __CONFIGURE__) 

/* PCM SAMPLE SIZE SELECT */
#define __I2S_PCM_SAMPLESIZE_8BIT(__I2Sx__)                      (__I2Sx__->PCM_RHYCTRL.PCM_SAMPSZ = 0)
#define __I2S_PCM_SAMPLESIZE_16BIT(__I2Sx__)                     (__I2Sx__->PCM_RHYCTRL.PCM_SAMPSZ = 1)

/* DMA Request Level */
#define __I2S_TX_DMA_EMPTY_LEVEL(__I2Sx__, __LEVEL__)            (__I2Sx__->DMA_CFG.DMATDLR = __LEVEL__)
#define __I2S_RX_DMA_EMPTY_LEVEL(__I2Sx__, __LEVEL__)            (__I2Sx__->DMA_CFG.DMARDLR = __LEVEL__)

/* Exported functions --------------------------------------------------------*/

/* i2s_init */
void i2s_init(I2S_HandleTypeDef *hi2s);
/* i2s_init */
void i2s_deinit(I2S_HandleTypeDef *hi2s);
/* i2s_transmit_IT */
bool i2s_transmit_IT(I2S_HandleTypeDef *hi2s);
/* i2s_receive_IT */
bool i2s_receive_IT(I2S_HandleTypeDef *hi2s);
/* i2s_IRQHandler */
void i2s_IRQHandler(I2S_HandleTypeDef *hi2s);
/* i2s_read_data */
uint32_t i2s_read_data(I2S_HandleTypeDef *hi2s, uint32_t *buffer, uint32_t samples);
/* i2s_send_data */
uint32_t i2s_send_data(I2S_HandleTypeDef *hi2s, uint32_t *buffer, uint32_t samples);
/* i2s_transmit_DMA */
void i2s_transmit_DMA(I2S_HandleTypeDef *hi2s);
/* i2s_receive_DMA */
void i2s_receive_DMA(I2S_HandleTypeDef *hi2s);
#endif
