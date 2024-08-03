/*
  ******************************************************************************
  * @file    driver_blend.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of BLEND module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_BLEND_H__
#define __DRIVER_BLEND_H__

#include "fr30xx.h"

/** @addtogroup BLEND_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/*BLEND CTRL REG  0x00*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t BLEND_EN              : 1;
        uint32_t RGB0_FF_RST           : 1;
        uint32_t RGB1_FF_RST           : 1;
        uint32_t MASK_FF_RST           : 1;
        uint32_t ORGB_FF_RST           : 1;       
        uint32_t RSV                   : 27;
    } Bits;
} REG_BLEND_CTRL_t;

/*BLEND CONFIG REG  0x04*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t BLEND_MODE                 : 2;
        uint32_t RGB0_FORMAT                : 2;
        uint32_t RGB1_FORMAT                : 2;
        uint32_t ORGB_FORMAT                : 2;
        uint32_t ORGB_MODE                  : 1;
        uint32_t RGB0_CAL_EN                : 1;
        uint32_t RGB1_CAL_EN                : 1;       
        uint32_t MASK_CAL_EN                : 1;
        uint32_t R_MUL_TC_EN                : 1;
        uint32_t G_MUL_TC_EN                : 1;
        uint32_t B_MUL_TC_EN                : 1;
        uint32_t A_MUL_TC_EN                : 1;
        uint32_t ORGB_565_R_TC_EN           : 1;
        uint32_t ORGB_565_G_TC_EN           : 1;
        uint32_t ORGB_565_B_TC_EN           : 1;
        uint32_t ORGB_332_R_TC_EN           : 1;
        uint32_t ORGB_332_G_TC_EN           : 1;
        uint32_t ORGB_332_B_TC_EN           : 1;
        uint32_t RSV                        : 10;
    } Bits;
} REG_BLEND_CFG_t;


/*BLEND PIXEL REG  0x08*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t PIXEL_ALPHA        : 8;
        uint32_t PIXEL_DATA         : 24;
    } Bits;
} REG_BLEND_PIXEL_t;

/*BLEND SRC ALPHA REG  0x0C*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t SRC_ALPHA        : 8;
        uint32_t RSV              : 24;
    } Bits;
} REG_BLEND_SRC_ALPHA_t;

/*BLEND DMAC REG  0x10*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t RGB0_DMA_EN        : 1;
        uint32_t RGB1_DMA_EN        : 1;
        uint32_t MASK_DMA_EN        : 1;
        uint32_t ORGB_DMA_EN        : 1;
        uint32_t RSV                : 28;
    } Bits;
} REG_BLEND_DMAC_t;

/*BLEND INFIFO0 THRESHOLD CONTROL REG  0x14*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t RGB0_ALEMPTY_THR        : 5;
        uint32_t RSV                     : 3;
        uint32_t RGB0_ALFULL_THR         : 5;
        uint32_t RSV2                    : 3;
        uint32_t RGB0_DMA_THR            : 5;  
        uint32_t RSV3                    : 11;
    } Bits;
} REG_BLEND_INFIFO0_THR_CTL_t;

/*BLEND INFIFO1 THRESHOLD CONTROL REG  0x18*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t RGB1_ALEMPTY_THR        : 5;
        uint32_t RSV                     : 3;
        uint32_t RGB1_ALFULL_THR         : 5;
        uint32_t RSV2                    : 3;
        uint32_t RGB1_DMA_THR            : 5; 
        uint32_t RSV3                    : 11;
    } Bits;
} REG_BLEND_INFIFO1_THR_CTL_t;

/*BLEND INFIFOMASK THRESHOLD CONTROL REG  0x1C*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t MASK_ALEMPTY_THR        : 5;
        uint32_t RSV                     : 3;
        uint32_t MASK_ALFULL_THR         : 5;
        uint32_t RSV2                    : 3;
        uint32_t MASK_DMA_THR            : 5; 
        uint32_t RSV3                    : 11;
    } Bits;
} REG_BLEND_INFIFOMASK_THR_CTL_t;

/*BLEND OUTFIFO THRESHOLD CONTROL REG  0x20*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t ORGB_ALEMPTY_THR       : 5;
        uint32_t RSV1                   : 3;
        uint32_t ORGB_ALFULL_THR        : 5;
        uint32_t RSV2                   : 3;
        uint32_t ORGB_DMA_THR           : 5; 
        uint32_t RSV3                   : 3;
        uint32_t ORGB_FLOW_THR          : 5;
        uint32_t RSV4                   : 3;
    } Bits;
} REG_BLEND_OUTFIFO_THR_CTL_t;

/*BLEND INTERRUPT CONTROL REG  0x24*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t RGB0_EMPTY_INT_EN        : 1;
        uint32_t RGB0_ALEMPTY_INT_EN      : 1;
        uint32_t RGB0_FULL_INT_EN         : 1;
        uint32_t RGB0_ALFULL_INT_EN       : 1;
        uint32_t RSV1                     : 4;
        uint32_t RGB1_EMPTY_INT_EN        : 1;
        uint32_t RGB1_ALEMPTY_INT_EN      : 1;
        uint32_t RGB1_FULL_INT_EN         : 1;
        uint32_t RGB1_ALFULL_INT_EN       : 1;
        uint32_t RSV2                     : 4;
        uint32_t MASK_EMPTY_INT_EN        : 1;
        uint32_t MASK_ALEMPTY_INT_EN      : 1;  
        uint32_t MASK_FULL_INT_EN         : 1;
        uint32_t MASK_ALFULL_INT_EN       : 1;      
        uint32_t RSV3                     : 4;
        uint32_t ORGB_EMPTY_INT_EN        : 1;
        uint32_t ORGB_ALEMPTY_INT_EN      : 1; 
        uint32_t ORGB_FULL_INT_EN         : 1;
        uint32_t ORGB_ALFULL_INT_EN       : 1;
        uint32_t RSV4                     : 4;       
    } Bits;
} REG_BLEND_ISR_CTL_t;

/*BLEND INTERRUPT STATUS REG  0x28*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t RGB0_EMPTY_INT_STS        : 1;
        uint32_t RGB0_ALEMPTY_INT_STS      : 1;
        uint32_t RGB0_FULL_INT_STS         : 1;
        uint32_t RGB0_ALFULL_INT_STS       : 1;
        uint32_t RSV1                      : 4;
        uint32_t RGB1_EMPTY_INT_STS        : 1;
        uint32_t RGB1_ALEMPTY_INT_STS      : 1;
        uint32_t RGB1_FULL_INT_STS         : 1;
        uint32_t RGB1_ALFULL_INT_STS       : 1;
        uint32_t RSV2                      : 4;
        uint32_t MASK_EMPTY_INT_STS        : 1;
        uint32_t MASK_ALEMPTY_INT_STS      : 1;  
        uint32_t MASK_FULL_INT_STS         : 1;
        uint32_t MASK_ALFULL_INT_STS       : 1;     
        uint32_t RSV3                      : 4;
        uint32_t ORGB_EMPTY_INT_STS        : 1;
        uint32_t ORGB_ALEMPTY_INT_STS      : 1;
        uint32_t ORGB_FULL_INT_STS         : 1;
        uint32_t ORGB_ALFULL_INT_STS       : 1;  
        uint32_t RSV4                      : 4;       
} Bits;
} REG_BLEND_ISR_STATUS_t;

/*BLEND FIFO STATUS REG  0x2c*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t RGB0_EMPTY               : 1;
        uint32_t RGB0_ALEMPTY             : 1;
        uint32_t RGB0_FULL                : 1;
        uint32_t RGB0_ALFULL              : 1;     
        uint32_t RSV1                     : 4;       
        uint32_t RGB1_EMPTY               : 1;
        uint32_t RGB1_ALEMPTY             : 1;
        uint32_t RGB1_FULL                : 1;
        uint32_t RGB1_ALFULL              : 1;
        uint32_t RSV2                     : 4;
        uint32_t MASK_EMPTY               : 1;
        uint32_t MASK_ALEMPTY             : 1;
        uint32_t MASK_FULL                : 1;
        uint32_t MASK_ALFULL              : 1;        
        uint32_t RSV3                     : 4;
        uint32_t ORGB_EMPTY               : 1;
        uint32_t ORGB_ALEMPTY             : 1;
        uint32_t ORGB_FULL                : 1;
        uint32_t ORGB_ALFULL              : 1;
        uint32_t RSV4                     : 4;       
    } Bits;
} REG_BLEND_FIFO_STATUS_t;


/*BLEND FIFO COUNT REG  0x38*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t RGB0_FF_COUNT               : 6;
        uint32_t RSV1                        : 2;
        uint32_t RGB1_FF_COUNT               : 6;
        uint32_t RSV2                        : 2;
        uint32_t MASK_FF_COUNT               : 6;
        uint32_t RSV3                        : 2;   
        uint32_t ORGB_FF_COUNT               : 6;       
        uint32_t RSV                         : 2;       
    } Bits; 
} REG_BLEND_FIFO_COUNT_t;

/*BLEND PIXEL_THR REG  0x3C*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t O565_B_THR                  : 3;
        uint32_t O565_G_THR                  : 2;      
        uint32_t O565_R_THR                  : 3;
        uint32_t RSV2                        : 8;  
        uint32_t O332_B_THR                  : 6;
        uint32_t O332_G_THR                  : 5;
        uint32_t O332_R_THR                  : 5;             
    } Bits; 
} REG_BLEND_PIXEL_THR_t;

typedef struct 
{
    REG_BLEND_CTRL_t                 CTRL;                /* Offset 0x00 */
    REG_BLEND_CFG_t                  CONFIG;              /* Offset 0x04 */
    REG_BLEND_PIXEL_t                PIXEL;               /* Offset 0x08*/
    REG_BLEND_SRC_ALPHA_t            SRC_ALPHA;           /* Offset 0x0c */
    REG_BLEND_DMAC_t                 DMAC;                /* Offset 0x10 */
    REG_BLEND_INFIFO0_THR_CTL_t      INFIFO0_THR_CTL;     /* Offset 0x14 */
    REG_BLEND_INFIFO1_THR_CTL_t      INFIFO1_THR_CTL;     /* Offset 0x18 */
    REG_BLEND_INFIFOMASK_THR_CTL_t   INFIFOMASK_THR_CTL;   /* Offset 0x1C */
    REG_BLEND_OUTFIFO_THR_CTL_t      OUTFIFO_THR_CTL;     /* Offset 0x20 */
    REG_BLEND_ISR_CTL_t              ISR_CTL;             /* Offset 0x24 */
    REG_BLEND_ISR_STATUS_t           ISR_STATUS;          /* Offset 0x28 */
    REG_BLEND_FIFO_STATUS_t          FIFO_STATUS;         /* Offset 0x2C */
    uint32_t                         RGB0_DATA;           /* Offset 0x30 */
    uint32_t                         RGB1_DATA;           /* Offset 0x34 */
    REG_BLEND_FIFO_COUNT_t           FIFO_COUNT;          /* Offset 0x38 */
    REG_BLEND_PIXEL_THR_t            PIXEL_THR;           /* Offset 0x3c */
}struct_BLEND_t;

typedef struct
{
    uint32_t     MASK_DATA;/* Offset 0x00 */
    uint32_t     ORGB_DATA;/* Offset 0x04 */
}struct_BLEND_AHB1_t;

#define BLEND_AHB0               ((volatile struct_BLEND_t *)BLEND_AHB0_BASE)
#define BLEND_AHB1               ((volatile struct_BLEND_AHB1_t *)BLEND_AHB1_BASE)


#define BLEND_RGB0_EMPTY_INT_STS         (1<<0)
#define BLEND_RGB0_ALEMPTY_INT_STS       (1<<1)
#define BLEND_RGB1_EMPTY_INT_STS         (1<<8)
#define BLEND_RGB1_ALEMPTY_INT_STS       (1<<9)
#define BLEND_MASK_EMPTY_INT_STS         (1<<16)
#define BLEND_MASK_ALEMPTY_INT_STS       (1<<17)
#define BLEND_ORGB_FULL_INT_STS          (1<<26)
#define BLEND_ORGB_ALFULL_INT_STS        (1<<27)


typedef enum{
    BLEND_RGB_TYPE_888 = 0,
    BLEND_RGB_TYPE_565 = 1,
}enum_RGB_TYPE_t;


typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INRGB0_FORMAT           : 2;
        uint32_t INRGB1_FORMAT           : 2;       
        uint32_t OUTRGB_FORMAT           : 2;       
        uint32_t SRC_IS_PURE             : 1;
        uint32_t SRC_ALPHA               : 8;
        uint32_t BLEND_MODE              : 2;
        uint32_t DMA_IN_EN               : 1;
        uint32_t DMA_OUT_EN              : 1;
        uint32_t ISR_EN                  : 1;
        uint32_t MASK_CAL_EN             : 1;
        uint32_t RSV                     : 11;       
    } Bits;
}struct_init_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t ALEMPTY_THR             : 6;
        uint32_t DMA_THR                 : 6;
        uint32_t RSV                     : 20;       
    } Bits;
}struct_INFIFO_THR_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t ALFULL_THR              : 6;  
        uint32_t DMA_THR                 : 6;
        uint32_t RSV                     : 20;       
    } Bits;
}struct_OUTFIFO_THR_t;

typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t PIXEL                   : 24;  
        uint32_t RSV                     : 8;       
    } Bits;
}struct_PURE_t;

typedef struct __BLEND_HandleTypeDef
{
    struct_init_t   BlendInit;
    
    struct_PURE_t   Pure;
    
    struct_INFIFO_THR_t Infifo0Thr;
    
    struct_INFIFO_THR_t Infifo1Thr;
    
    struct_INFIFO_THR_t InfifoMaskThr;
    
    struct_OUTFIFO_THR_t OutfifoThr;
    
    uint32_t *SrcRgb;   /*!< BLEND parameters in interrupt  */
    uint32_t SrcSize;
    uint32_t *BackRgb;
    uint32_t BackSize;
    uint32_t *MaskRgb;
    uint32_t MaskSize;
    uint32_t *OutRgb;
    uint32_t OutSize;
    uint8_t  gMaskRem;
    uint32_t PixelCount;
    
    uint32_t SrcInIndex;  /*!< BLEND RGB data index in handle  */
    uint32_t BackInIndex;    
    uint32_t MaskInIndex;
    uint32_t DataOutIndex;
    
    void (*Callback)(struct __BLEND_HandleTypeDef *hblend);         /*!< BLEND RGB out finish Callback */

}BLEND_HandleTypeDef;

typedef struct{
    uint8_t *SrcRgb;
    uint8_t *BackRgb;
    uint8_t *MaskRgb;
    uint8_t *OutRgb;
    uint32_t PixelCount;
}BLEND_DataParam_t;



#define __BLEND_INT_RGB0_FIFO_EMPTY_ENABLE()     (BLEND_AHB0->ISR_CTL.Bits.RGB0_EMPTY_INT_EN = 1)
#define __BLEND_INT_RGB1_FIFO_EMPTY_ENABLE()     (BLEND_AHB0->ISR_CTL.Bits.RGB1_EMPTY_INT_EN = 1)
#define __BLEND_INT_MASK_FIFO_EMPTY_ENABLE()     (BLEND_AHB0->ISR_CTL.Bits.MASK_EMPTY_INT_EN = 1)
#define __BLEND_INT_ORGB_FIFO_ALFULL_ENABLE()    (BLEND_AHB0->ISR_CTL.Bits.ORGB_ALFULL_INT_EN = 1) 

#define __BLEND_INT_RGB0_FIFO_EMPTY_DISABLE()     (BLEND_AHB0->ISR_CTL.Bits.RGB0_EMPTY_INT_EN = 0)
#define __BLEND_INT_RGB1_FIFO_EMPTY_DISABLE()     (BLEND_AHB0->ISR_CTL.Bits.RGB1_EMPTY_INT_EN = 0)
#define __BLEND_INT_MASK_FIFO_EMPTY_DISABLE()     (BLEND_AHB0->ISR_CTL.Bits.MASK_EMPTY_INT_EN = 0)
#define __BLEND_INT_ORGB_FIFO_ALFULL_DISABLE()    (BLEND_AHB0->ISR_CTL.Bits.ORGB_ALFULL_INT_EN = 0) 

#define __RGB0_FIFO_IS_EMPTY()            (BLEND_AHB0->FIFO_STATUS.Bits.RGB0_EMPTY == 1)
#define __RGB0_FIFO_IS_ALEMPTY()          (BLEND_AHB0->FIFO_STATUS.Bits.RGB0_ALEMPTY == 1)
#define __RGB0_FIFO_IS_FULL()             (BLEND_AHB0->FIFO_STATUS.Bits.RGB0_FULL == 1)
#define __RGB0_FIFO_IS_ALFULL()           (BLEND_AHB0->FIFO_STATUS.Bits.RGB0_ALFULL == 1)
#define __RGB1_FIFO_IS_EMPTY()            (BLEND_AHB0->FIFO_STATUS.Bits.RGB1_EMPTY == 1)
#define __RGB1_FIFO_IS_ALEMPTY()          (BLEND_AHB0->FIFO_STATUS.Bits.RGB1_ALEMPTY == 1)/*set almost empty to do*/
#define __RGB1_FIFO_IS_FULL()             (BLEND_AHB0->FIFO_STATUS.Bits.RGB1_FULL == 1)
#define __RGB1_FIFO_IS_ALFULL()           (BLEND_AHB0->FIFO_STATUS.Bits.RGB1_ALFULL == 1)
#define __MASK_FIFO_IS_EMPTY()            (BLEND_AHB0->FIFO_STATUS.Bits.MASK_EMPTY == 1)
#define __MASK_FIFO_IS_ALEMPTY()          (BLEND_AHB0->FIFO_STATUS.Bits.MASK_ALEMPTY == 1)
#define __MASK_FIFO_IS_FULL()             (BLEND_AHB0->FIFO_STATUS.Bits.MASK_FULL == 1)
#define __MASK_FIFO_IS_ALFULL()           (BLEND_AHB0->FIFO_STATUS.Bits.MASK_ALFULL == 1)
#define __ORGB_FIFO_IS_FULL()             (BLEND_AHB0->FIFO_STATUS.Bits.ORGB_FULL == 1)
#define __ORGB_FIFO_IS_ALFULL()           (BLEND_AHB0->FIFO_STATUS.Bits.ORGB_ALFULL == 1)
#define __ORGB_FIFO_IS_EMPTY()            (BLEND_AHB0->FIFO_STATUS.Bits.ORGB_EMPTY == 1)
#define __ORGB_FIFO_IS_ALEMPTY()          (BLEND_AHB0->FIFO_STATUS.Bits.ORGB_ALEMPTY == 1)
#define __ORGB_FIFO_IS_HALF_FULL()        (BLEND_AHB0->FIFO_STATUS.Bits.ORGB_HALF_FULL == 1)

/* Initialize the blend module */
void blend_init(BLEND_HandleTypeDef *hblend);
/* Start blend to mix pixel without isr */
void blend_start(BLEND_HandleTypeDef *hblend, BLEND_DataParam_t DataParam);
/* Start blend to mix pixel with isr */
void blend_start_IT(BLEND_HandleTypeDef *hblend, BLEND_DataParam_t DataParam);
/* Blend module handle function in the blend isr */
void blend_IRQHandler(BLEND_HandleTypeDef *hblend);

#endif
