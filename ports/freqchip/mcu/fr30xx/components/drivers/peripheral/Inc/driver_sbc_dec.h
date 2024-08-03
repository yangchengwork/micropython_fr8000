/*
  ******************************************************************************
  * @file    driver_sbc_dec.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of SBC DEC module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SBC_DEC_H__
#define __DRIVER_SBC_DEC_H__

#include "fr30xx.h"

#define SBCD_INFIFO_DEEPTH      128
#define SBCD_OUTLFIFO_DEEPTH    256
#define SBCD_OUTRFIFO_DEEPTH    256


/** @addtogroup SBC_CODEC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */
/* SBC DEC CTRL REGISTER 0x00*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t DEC_EN                      : 1;//sbc decoder enable
        uint32_t DEC_LR_SWAP                 : 1;//swap decoder left and rignt channel enable
        uint32_t DEC_OUTL_FLOW_CTRL          : 1;//whether use the left outfifo almost full status to control whether to read the infifo
        uint32_t DEC_OUTR_FLOW_CTRL          : 1;//whether use the right outfifo almost full status to control whether to read the infifo
        uint32_t DEC_RESET                   : 1;//decoder reset
        uint32_t DEC_IN_FIFO_RESET           : 1;//decoder infifo reset
        uint32_t DEC_OUTL_FIFO_RESET         : 1;//decoder left outfifo reset
        uint32_t DEC_OUTR_FIFO_RESET         : 1;//decoder right outfifo reset
        uint32_t IN_DMA_EN                   : 1;//infifo dma enable
        uint32_t OUT_DMA_EN                  : 1;//outfifo dma enable
        uint32_t OUTL_FIFO_EN                : 1;//outfifo status select left fifo
        uint32_t OUTR_FIFO_EN                : 1;//outfifo status select right fifo
        uint32_t RSV                         : 20;
    } Bits;
} REG_SBCD_CTRL_t;


/* SBC DEC IN FIFO REG REGISTER 0x04*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t SBC_IN                            : 8;//sbc encoded data in
        uint32_t RSV                               : 24;
    } Bits;
} REG_SBCD_INFIFO_REG_t;

/* SBC DEC OUT FIFO REG REGISTER 0x08*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t PCM_RIGHT_DATA                            : 16;//sbc encoded data in
        uint32_t PCM_LEFT_DATA                             : 16;
    } Bits;
} REG_SBCD_OUTFIFO_REG_t;

/* SBC DEC INT EN REGISTER 0x0C*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INFF_FULL_INT_EN                            : 1;//input fifo full interrupt enbale
        uint32_t INFF_EMPTY_INT_EN                           : 1;//input fifo empty interrupt enbale
        uint32_t INFF_ALEMPTY_INT_EN                         : 1;//input fifo almost empty interrupt enbale
        uint32_t RSV1                                        : 1;
        uint32_t OUTLFF_FULL_INT_EN                          : 1;//output left fifo full interrupt enbale
        uint32_t OUTLFF_EMPTY_INT_EN                         : 1;//output left fifo empty interrupt enbale
        uint32_t OUTLFF_ALFULL_INT_EN                        : 1;//output left fifo almost full interrupt enbale
        uint32_t RSV2                                        : 1;
        uint32_t OUTRFF_FULL_INT_EN                          : 1;//output right fifo full interrupt enbale
        uint32_t OUTRFF_EMPTY_INT_EN                         : 1;//output right fifo empty interrupt enbale
        uint32_t OUTRFF_ALFULL_INT_EN                        : 1;//output right fifo amlost full interrupt enbale
        uint32_t RSV3                                        : 1;
        uint32_t CRC_ERR_INT_EN                              : 1;//crc error flag interrupt enable
        uint32_t RSV4                                        : 19;   
    } Bits;
} REG_SBCD_INTEN_REG_t;

/* SBC DEC INT STATUS REGISTER 0x10*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INFF_FULL_INT_STS                          : 1;//input fifo full interrupt status
        uint32_t INFF_EMPTY_INT_STS                         : 1;//input fifo empty interrupt status
        uint32_t INFF_ALEMPTY_INT_STS                       : 1;//input fifo almost empty interrupt status
        uint32_t RSV1                                       : 1;
        uint32_t OUTLFF_FULL_INT_STS                        : 1;//output left fifo full interrupt status
        uint32_t OUTLFF_EMPTY_INT_STS                       : 1;//output left fifo empty interrupt status
        uint32_t OUTLFF_ALFULL_INT_STS                      : 1;//output left fifo almost full interrupt status 
        uint32_t RSV2                                       : 1;    
        uint32_t OUTRFF_FULL_INT_STS                        : 1;//output right fifo full interrupt status
        uint32_t OUTRFF_EMPTY_INT_STS                       : 1;//output right fifo empty interrupt status
        uint32_t OUTRFF_ALFULL_INT_STS                      : 1;//output right fifo almost full interrupt status
        uint32_t RSV3                                       : 1;    
        uint32_t CRC_ERR_INT_STS                            : 1;//crc interrupt status ,write 1 to cleat this bit      
        uint32_t RSV4                                       : 19;       
    } Bits;
} REG_SBCD_INTS_REG_t;


/* SBC DEC FIFO STATE REGISTER 0x14 */
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INFIFO_FULL                     : 1;//infifo full flag
        uint32_t INFIFO_EMPTY                    : 1;//infifo empty flag
        uint32_t INFIFO_ALEMPTY                  : 1;//infifo almost empty flag
        uint32_t RSV1                            : 1;
        uint32_t OUTLFIFO_FULL                   : 1;//outlfifo full flag
        uint32_t OUTLFIFO_EMPTY                  : 1;//outlfifo empty flag
        uint32_t OUTLFIFO_ALFULL                 : 1;//outlfifo almost full flag
        uint32_t RSV2                            : 1;
        uint32_t OUTRFIFO_FULL                   : 1;//outrfifo full flag
        uint32_t OUTRFIFO_EMPTY                  : 1;//outrfifo empty flag
        uint32_t OUTRFIFO_ALFULL                 : 1;//outrfifo almost full flag
        uint32_t RSV                             : 21;
    } Bits;
} REG_SBCD_FIFO_STATE_t;

/* SBC DEC FIFO INWDS 0x18*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INFIFO_WC             : 8;//input fifo words count
        uint32_t RSV                   : 24;//
    } Bits;
} REG_SBCD_FIFO_INWDS_t;

/* SBC DEC FIFO OUTWDS 0x1C*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t OUTLFIFO_WC               : 8;//output left fifo words pointer
        uint32_t RSV1                      : 8;
        uint32_t OUTRFIFO_WC               : 8;//output right fifo words pointer
        uint32_t RSV2                      : 8;
    } Bits;
} REG_SBCD_FIFO_OUTWDS_t;

/*SBC FIFO LEVEL 0x20*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INFIFO_ALEMPTY_LEVEL                : 7;//output left fifo words pointer
        uint32_t RSV1                                : 1;
        uint32_t OUTLFIFO_ALFULL_LEVEL               : 8;//output right fifo words pointer
        uint32_t OUTRFIFO_ALFULL_LEVEL               : 8;//output right fifo words pointer
        uint32_t RSV2                                : 8;
    } Bits;
} REG_SBCD_FIFO_LEVEL_t;


typedef struct 
{
    volatile REG_SBCD_CTRL_t           SBCD_CTRL;                /* Offset 0x00 */
    volatile REG_SBCD_INFIFO_REG_t     SBCD_INFIFO;              /* Offset 0x04 */
    volatile REG_SBCD_OUTFIFO_REG_t    SBCD_OUTFIFO;             /* Offset 0x08 */
    volatile REG_SBCD_INTEN_REG_t      SBCD_INTEN;               /* Offset 0x0C */
    volatile REG_SBCD_INTS_REG_t       SBCD_INTS;                /* Offset 0x10 */
    volatile REG_SBCD_FIFO_STATE_t     SBCD_FIFO_STATE;          /* Offset 0x14 */
    volatile REG_SBCD_FIFO_INWDS_t     SBCD_FIFO_INWDS;          /* Offset 0x18 */
    volatile REG_SBCD_FIFO_OUTWDS_t    SBCD_FIFO_OUTWDS;         /* Offset 0x1C */
    volatile REG_SBCD_FIFO_LEVEL_t     SBCD_FIFO_LEVEL;          /* Offset 0x20 */    
}struct_SBCD_t;

#define SBC_DEC   ((struct_SBCD_t *)SBC_DEC_BASE)

typedef enum{
    SBCD_MONO = 0,
    SBCD_STEREO,
}enum_Ch_Mode_t ;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t infifo_alempty_lvl         : 7;
        uint32_t outlfifo_alfull_lvl        : 8;
        uint32_t outrlfifo_alfull_lvl       : 8;
        uint32_t input_dma_en               : 1;
        uint32_t output_dma_en              : 1;
        uint32_t outlfifo_en                : 1;
        uint32_t outrfifo_en                : 1;
        uint32_t ch_mode                    : 1;
        uint32_t RSV                        : 4;
    }Bits;
}struct_SBCDec_Init_t;


typedef struct __SBC_DEC_HandleTypeDef
{
    struct_SBCDec_Init_t sbc_init;
    uint8_t *EncodeData;
    uint32_t DataSize;
    uint16_t *OrignData;
    uint32_t InputIndex;
    uint32_t OutIndex;
    
    void (*Callback)(struct __SBC_DEC_HandleTypeDef *hSbcDec);                /*!< SBC decode finish Callback */
}SBC_DEC_HandleTypeDef;

typedef enum 
{
    INFF_FULL_INT      = (1 << 0),
    INFF_EMPTY_INT     = (1 << 1),
    INFF_ALEMPTY_INT   = (1 << 2),
    OUTLF_FULL_INT     = (1 << 4),
    OUTLF_EMPTY_INT    = (1 << 5),
    OUTLF_ALFULL_INT   = (1 << 6),
    OUTRF_FULL_INT     = (1 << 8),
    OUTRF_EMPTY_INT    = (1 << 9),
    OUTRF_ALFULL_INT   = (1 << 10),
    CRC_ERR_INT        = (1 << 12),
}enum_isr_status_t ;

typedef struct{
    uint8_t frequency;
    uint8_t block_mode;
    uint8_t block_len;
    uint8_t channels;
    uint8_t bit_pool;
    enum {
        MONO            = 0,
        DUAL_CHANNEL    = 1,
        STEREO          = 2,
        JOINT_STEREO    = 3
    } mode;
    enum {
        LOUDNESS    = 0,
        SNR         = 1
    } allocation;
    uint8_t subband_mode;
    uint8_t subbands;
}struct_frame_info_t;

#define __SBCD_INFIFO_IS_FULL()            (SBC_DEC->SBCD_FIFO_STATE.Bits.INFIFO_FULL == 1)
#define __SBCD_INFIFO_IS_EMPTY()           (SBC_DEC->SBCD_FIFO_STATE.Bits.INFIFO_EMPTY == 1)
#define __SBCD_INFIFO_IS_ALEMPTY()         (SBC_DEC->SBCD_FIFO_STATE.Bits.INFIFO_ALEMPTY == 1)
#define __SBCD_OUTLFIFO_IS_FULL()          (SBC_DEC->SBCD_FIFO_STATE.Bits.OUTLFIFO_FULL == 1)
#define __SBCD_OUTLFIFO_IS_EMPTY()         (SBC_DEC->SBCD_FIFO_STATE.Bits.OUTLFIFO_EMPTY == 1)
#define __SBCD_OUTLFIFO_IS_ALFULL()        (SBC_DEC->SBCD_FIFO_STATE.Bits.OUTLFIFO_ALFULL == 1)
#define __SBCD_OUTRFIFO_IS_FULL()          (SBC_DEC->SBCD_FIFO_STATE.Bits.OUTRFIFO_FULL == 1)
#define __SBCD_OUTRFIFO_IS_EMPTY()         (SBC_DEC->SBCD_FIFO_STATE.Bits.OUTRFIFO_EMPTY == 1)
#define __SBCD_OUTRFIFO_IS_ALFULL()        (SBC_DEC->SBCD_FIFO_STATE.Bits.OUTRFIFO_ALFULL == 1)

#define __SBCD_GET_ISR_STS()               (SBC_DEC->SBCD_INTS.Word)

#define __SBCD_INFIFO_EMPTY_DISABLE()      (SBC_DEC->SBCD_INTEN.Bits.INFF_EMPTY_INT_EN = 0)

/* sbc decoder initialize */
void sbc_dec_init(SBC_DEC_HandleTypeDef *hSbcDec);
/* sbc decoder get packed frame info */
int sbc_dec_get_packed_frame_info(uint8_t *data, struct_frame_info_t frame_info);
/* sbc decoder handle function in sbc decoder isr */
void sbcdec_IRQHandler(SBC_DEC_HandleTypeDef *hSbcDec);
/* sbc decoder play data with isr */
void sbc_dec_playdata_IT(SBC_DEC_HandleTypeDef *hSbcDec, uint8_t *fp_Data, uint32_t fu32_Size, uint16_t *fp_Data_Out);

#endif
