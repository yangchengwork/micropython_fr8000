/*
  ******************************************************************************
  * @file    driver_sbc_enc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of SBC ENC module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SBC_ENC_H__
#define __DRIVER_SBC_ENC_H__

#include "fr30xx.h"

#define SBCE_INFIFO_DEEPTH      256
#define SBCE_OUTFIFO_DEEPTH     128


/** @addtogroup SBC_ENC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */
/* SBC ENC CTRL REGISTER 0x00*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t ENC_EN                      : 1;//sbc encoder enable
        uint32_t ENC_LR_SWAP                 : 1;//swap encoder left and rignt channel enable
        uint32_t ENC_INL_FLOW_CTRL           : 1;//bypass in left fifo status
        uint32_t ENC_INR_FLOW_CTRL           : 1;//bypass in right fifo status
        uint32_t ENC_RESET                   : 1;//encoder reset
        uint32_t ENC_OUT_FIFO_RESET          : 1;//encoder outfifo reset
        uint32_t ENC_INL_FIFO_RESET          : 1;//encoder left infifo reset
        uint32_t ENC_INR_FIFO_RESET          : 1;//encoder right infifo reset
        uint32_t IN_DMA_EN                   : 1;//infifo dma enable
        uint32_t OUT_DMA_EN                  : 1;//outfifo dma enable
        uint32_t INL_FIFO_EN                 : 1;//infifo status select left fifo
        uint32_t INR_FIFO_EN                 : 1;//infifo status select right fifo
        uint32_t RSV                         : 20;
    } Bits;
} REG_SBCE_CTRL_t;

/* SBC ENC CONFIG REGISTER 0x04*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t SMP_FRQ                      : 2;//sbc encoder sample frequncy 00->16KHz, 01->32KHz, 10->44.1KHz, 11->48KHz
        uint32_t BLK_LEN                      : 2;//block length 00->4 01->8 10->12 11->16
        uint32_t RSV1                         : 1;
        uint32_t CH_MODE                      : 1;//0->mono 1->dual
        uint32_t RSV2                         : 26;
    } Bits;
} REG_SBCE_CFG_t;

/* SBC ENC IN FIFO REG REGISTER 0x08*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t ENC_FFL                            : 16;//left channel input data
        uint32_t ENC_FFR                            : 16;//right channel input data
    } Bits;
} REG_SBCE_INFIFO_REG_t;

/* SBC ENC OUT FIFO REG REGISTER 0x0C*/


/* SBC ENC INT EN REGISTER 0x10*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t OUTFF_FULL_INT_EN                            : 1;//output fifo full interrupt enbale
        uint32_t OUTFF_EMPTY_INT_EN                           : 1;//output fifo empty interrupt enbale
        uint32_t OUTFF_ALFULL_INT_EN                          : 1;//output fifo almost full interrupt enbale
        uint32_t RSV1                                         : 1;
        uint32_t INLFF_FULL_INT_EN                            : 1;//input left fifo full interrupt enbale
        uint32_t INLFF_EMPTY_INT_EN                           : 1;//input left fifo empty interrupt enbale
        uint32_t INLFF_ALEMPTY_INT_EN                         : 1;//input left fifo almost empty interrupt enbale
        uint32_t RSV2                                         : 1;
        uint32_t INRFF_FULL_INT_EN                            : 1;//input right fifo full interrupt enbale
        uint32_t INRFF_EMPTY_INT_EN                           : 1;//input right fifo empty interrupt enbale
        uint32_t INRFF_ALEMPTY_INT_EN                         : 1;//input right fifo amlost empty interrupt enbale
        uint32_t RSV3                                         : 21; 
    } Bits;
} REG_SBCE_INTEN_REG_t;

/* SBC ENC INT STATUS REGISTER 0x14*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t OUTFF_FULL_INT_STS                          : 1;//output fifo full interrupt status
        uint32_t OUTFF_EMPTY_INT_STS                         : 1;//output fifo empty interrupt status
        uint32_t OUTFF_ALFULL_INT_STS                        : 1;//output fifo almost full interrupt status
        uint32_t RSV1                                        : 1;
        uint32_t INLFF_FULL_INT_STS                          : 1;//input left fifo full interrupt status
        uint32_t INLFF_EMPTY_INT_STS                         : 1;//input left fifo empty interrupt status
        uint32_t INLFF_ALEMPTY_INT_STS                       : 1;//input left fifo almost empty interrupt status
        uint32_t RSV2                                        : 1;    
        uint32_t INRFF_FULL_INT_STS                          : 1;//input right fifo full interrupt status
        uint32_t INRFF_EMPTY_INT_STS                         : 1;//input right fifo empty interrupt status
        uint32_t INRFF_ALEMPTY_INT_STS                       : 1;//input right fifo almost empty interrupt status
        uint32_t RSV3                                        : 21;     
    } Bits;
} REG_SBCE_INTS_REG_t;


/* SBC ENC FIFO STATE REGISTER 0x18 */
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t OUTFIFO_FULL                     : 1;//outfifo full flag
        uint32_t OUTFIFO_EMPTY                    : 1;//outfifo empty flag
        uint32_t OUTFIFO_ALFULL                   : 1;//outfifo almost empty flag
        uint32_t RSV1                             : 1;
        uint32_t INLFIFO_FULL                     : 1;//inlfifo full flag
        uint32_t INLFIFO_EMPTY                    : 1;//inlfifo empty flag
        uint32_t INLFIFO_ALEMPTY                  : 1;//inlfifo almost full flag
        uint32_t RSV2                             : 1;
        uint32_t INRFIFO_FULL                     : 1;//inrfifo full flag
        uint32_t INRFIFO_EMPTY                    : 1;//inrfifo empty flag
        uint32_t INRFIFO_ALEMPTY                  : 1;//inrfifo almost full flag
        uint32_t RSV                              : 21;
    } Bits;
} REG_SBCE_FIFO_STATE_t;

/* SBC ENC FIFO INWDS 0x1C*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t ENC_INLFFWDS_CNT             : 9;//input left fifo words count
        uint32_t RSV1                         : 7;
        uint32_t ENC_INRFFWDS_CNT             : 9;//input right fifo words count
        uint32_t RSV2                         : 7;
    } Bits;
} REG_SBCE_FIFO_INWDS_t;

/* SBC ENC FIFO OUTWDS 0x20*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t ENC_OUTFFWDS_CNT               : 8;//output fifo words pointer
        uint32_t RSV1                           : 24;
    } Bits;
} REG_SBCE_FIFO_OUTWDS_t;

/*SBC ENC INPUT FIFO LEVEL 0x24*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INLFIFO_ALEMPTY_LEVEL                : 8;//output left fifo words pointer
        uint32_t RSV1                                 : 8;
        uint32_t INRFIFO_ALEMPTY_LEVEL                : 8;//output left fifo words pointer
        uint32_t RSV2                                 : 8;
    } Bits;
} REG_SBCE_INFIFO_LEVEL_t;

/*SBC ENC OUTPUT FIFO LEVEL 0x28*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t OUTFIFO_ALFULL_LEVEL                : 8;//output fifo almost full level
        uint32_t RSV                                 : 24;
    } Bits;
} REG_SBCE_OUTFIFO_LEVEL_t;


typedef struct 
{
    volatile REG_SBCE_CTRL_t           SBCE_CTRL;                /* Offset 0x00 */
    volatile REG_SBCE_CFG_t            SBCE_CFG;                 /* Offset 0x04 */
    volatile REG_SBCE_INFIFO_REG_t     SBCE_INFIFO;              /* Offset 0x08 */
    volatile uint32_t                  SBCE_OUTFIFO;             /* Offset 0x0C */
    volatile REG_SBCE_INTEN_REG_t      SBCE_INTEN;               /* Offset 0x10 */
    volatile REG_SBCE_INTS_REG_t       SBCE_INTS;                /* Offset 0x14 */
    volatile REG_SBCE_FIFO_STATE_t     SBCE_FIFO_STATE;          /* Offset 0x18 */
    volatile REG_SBCE_FIFO_INWDS_t     SBCE_FIFO_INWDS;          /* Offset 0x1C */
    volatile REG_SBCE_FIFO_OUTWDS_t    SBCE_FIFO_OUTWDS;         /* Offset 0x20 */
    volatile REG_SBCE_INFIFO_LEVEL_t   SBCE_INFIFO_LVL;          /* Offset 0x24 */    
    volatile REG_SBCE_OUTFIFO_LEVEL_t  SBCE_OUTFF_LVL;           /* Offset 0x28 */        
}struct_SBCE_t;

#define SBC_ENC   ((struct_SBCE_t *)SBC_ENC_BASE)

typedef enum{
    SBCE_MONO = 0,
    SBCE_STEREO = 1,
}enum_pcm_channel_mode_t ;

typedef enum{
    BLOCK_4  = 0,
    BLOCK_8  = 1,
    BLOCK_12 = 2,
    BLOCK_16 = 3,
}enum_pcm_block_length_t ;

typedef enum{
    SP_16KHz   = 0,
    SP_32KHz   = 1,
    SP_44_1KHz = 2,
    SP_48KHz   = 3,
}enum_pcm_sample_freq_t ;

typedef struct{
    uint32_t input_dma_en;
    uint32_t output_dma_en;
    uint32_t inlfifo_dma_en;
    uint32_t inrfifo_dma_en;
}struct_SBCE_DMA_cfg_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t inlfifo_alempty_lvl   : 8;
        uint32_t inrfifo_alempty_lvl   : 8;
        uint32_t outlfifo_alfull_lvl   : 8;
        uint32_t output_dma_en         : 1;
        uint32_t input_dma_en          : 1;
        uint32_t sample_freq           : 2;
        uint32_t ch_mode               : 1;
        uint32_t blk_len               : 2;
        uint32_t RSV                   : 1;
    }Bits;
}struct_SBCENC_Init_t;

typedef struct{
    uint32_t outfifo_full_int_en;
    uint32_t outfifo_empty_int_en;
    uint32_t outfifo_alfull_int_en;
    uint32_t inlff_full_int_en;
    uint32_t inlff_empty_int_en;
    uint32_t inlff_alempty_int_en;
    uint32_t inrff_full_int_en;
    uint32_t inrff_empty_int_en;
    uint32_t inrff_alempty_int_en;
}struct_SBCE_ISR_cfg_t;

typedef struct __SBC_ENC_HandleTypeDef
{
    struct_SBCENC_Init_t SbcEncInit;
    uint16_t *OrignlData;
    uint32_t gDataInIndex;
    uint8_t *EncodedData;
    uint32_t gDataOutIndex;
    uint32_t OrignlDataSize;
    void (*Callback)(struct __SBC_ENC_HandleTypeDef *hSbcEnc);                /*!< SBC encode finish Callback */
}SBC_ENC_HandleTypeDef ;

typedef enum 
{
    OUTFF_FULL_INT      = (1 << 0),
    OUTFF_EMPTY_INT     = (1 << 1),
    OUTFF_ALFULL_INT    = (1 << 2),
    INLF_FULL_INT       = (1 << 4),
    INLF_EMPTY_INT      = (1 << 5),
    INLF_ALEMPTY_INT    = (1 << 6),
    INRF_FULL_INT       = (1 << 8),
    INRF_EMPTY_INT      = (1 << 9),
    INRF_ALEMPTY_INT    = (1 << 10),
}enum_sbce_isr_status_t ;

#define __SBCE_OUTFIFO_IS_FULL()            (SBC_ENC->SBCE_FIFO_STATE.Bits.OUTFIFO_FULL == 1)
#define __SBCE_OUTFIFO_IS_EMPTY()           (SBC_ENC->SBCE_FIFO_STATE.Bits.OUTFIFO_EMPTY == 1)
#define __SBCE_OUTFIFO_IS_ALFULL()          (SBC_ENC->SBCE_FIFO_STATE.Bits.OUTFIFO_ALFULL == 1)
#define __SBCE_INLFIFO_IS_FULL()            (SBC_ENC->SBCE_FIFO_STATE.Bits.INLFIFO_FULL == 1)
#define __SBCE_INLFIFO_IS_EMPTY()           (SBC_ENC->SBCE_FIFO_STATE.Bits.INLFIFO_EMPTY == 1)
#define __SBCE_INLFIFO_IS_ALEMPTY()         (SBC_ENC->SBCE_FIFO_STATE.Bits.INLFIFO_ALEMPTY == 1)
#define __SBCE_INRFIFO_IS_FULL()            (SBC_ENC->SBCE_FIFO_STATE.Bits.INRFIFO_FULL == 1)
#define __SBCE_INRFIFO_IS_EMPTY()           (SBC_ENC->SBCE_FIFO_STATE.Bits.INRFIFO_EMPTY == 1)
#define __SBCE_INRFIFO_IS_ALEMPTY()         (SBC_ENC->SBCE_FIFO_STATE.Bits.INRFIFO_ALEMPTY == 1)

#define __SBCE_GET_ISR_STS()                (SBC_ENC->SBCE_INTS.Word)
#define __SBCE_GET_OUT_RESULT_WORD()        (SBC_ENC->SBCE_OUTFIFO)

#define __SBCE_INLFF_EMPTY_INT_DISABLE()    (SBC_ENC->SBCE_INTEN.Bits.INLFF_EMPTY_INT_EN  = 0)

void sbc_enc_init(SBC_ENC_HandleTypeDef *hSbcEnc);
void sbc_encoder_enc_IT(SBC_ENC_HandleTypeDef *hSbcEnc, uint16_t *fp_Data_In, uint32_t fu32_size, uint8_t *fp_Data_Out);
void sbcenc_IRQHandler(SBC_ENC_HandleTypeDef *hSbcEnc);

#endif
