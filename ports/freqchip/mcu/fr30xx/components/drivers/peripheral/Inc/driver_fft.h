/*
  ******************************************************************************
  * @file    driver_fft.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of FFT module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_FFT_H__
#define __DRIVER_FFT_H__

#include "fr30xx.h"

/** @addtogroup FFT_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/*FFT CTRL REG  0x00*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t NP_SEL   : 2;    // fft sample number point select
        uint32_t MODE_SEL : 1;    // fft calculate mode select
        uint32_t RSV      : 29;
    } Bits;
} REG_FFT_CTRL_t;

/*FFT DMA CONFIG REG  0x04*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t DMACR       : 2;    //dma clear
        uint32_t RSV1        : 6;
        uint32_t DMA_OUT_THR : 8;    //dma_out_req start threshold
        uint32_t DMA_IN_THR  : 8;    //dma_in_req  start threshold
        uint32_t RSV         : 8;
    } Bits;
} REG_FFT_DMA_t;

/*FFT INTERRUPT CLEAR REG  0x08*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t INT_EN     : 1;    //FFT interrupt enable 
        uint32_t RSV1       : 7;
        uint32_t INT_STATUS : 1;    //FFT interrupt status
        uint32_t RSV2       : 22;
    } Bits;
} REG_FFT_ISRCR_t;

/*FFT SOFT RESET REG 0x0c*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t NRST             : 1;    //FFT soft reset
        uint32_t RSV              : 31;
    } Bits;
} REG_FFT_SOFTRST_t;

/*FFT STATUS REG  0x14*/
typedef volatile union
{
    volatile uint32_t Word;
    struct
    {
        uint32_t IDLE             : 1;    // FFT status is idle
        uint32_t CAL_DONE         : 1;    // FFT calculate done
        uint32_t RSV              : 30;
    } Bits;
} REG_FFT_STATUS_t;

/* -----------------------------------------------*/
/*                  FFT Registers                 */
/* -----------------------------------------------*/
typedef struct 
{
    volatile REG_FFT_CTRL_t     FFT_CTRL;                 /* Offset 0x00 */
    volatile REG_FFT_DMA_t      FFT_DMA;                  /* Offset 0x04 */
    volatile REG_FFT_ISRCR_t    FFT_ISRCR;                /* Offset 0x08 */
    volatile REG_FFT_SOFTRST_t  FFT_SOFTRST_IIRFLT;       /* Offset 0x0C */
    volatile uint32_t           rsv1;                     /* Offset 0x10 */
    volatile REG_FFT_STATUS_t   FFT_STATUS;               /* Offset 0x14 */
    volatile uint32_t           rsv2[26];                 /* Offser 0x18 ~ 0x7c*/
    volatile uint32_t           FFT_ACCESSRAM;            /* Offset 0x80 */
}struct_FFT_t;

#define FFT              ((struct_FFT_t *)FFT_BASE)

/* ################################ Register Section END ################################ */
/**
  * @}
  */

/** @addtogroup FFT_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization Config Section Start ################################ */
typedef enum 
{
    FFT_128 = 0,
    FFT_256 = 1,
    FFT_512 = 2,
}FFT_Samples_t ;

typedef enum 
{
    FFT_CAL_MODE  = 0,    /* FFT calculate */
    IFFT_CAL_MODE = 1,    /* FFT inverse calculation */
}FFT_Cal_Mode_t ;

typedef struct 
{
    uint32_t    FFT_Samples;                 /*!< Specifies the number of Sample.
                                                  This parameter can be a value of @ref fft_samples_t. */

    uint32_t    FFT_Cal_Mode;                /*!< Specifies the FFT calculate mode.
                                                  This parameter can be a value of @ref FFT_Cal_Mode_t. */
}struct_FFT_Init_t;

typedef struct
{
    struct_FFT_Init_t    FFT_Init;

    uint32_t BlockCNT;
    uint32_t BlockSize;
    uint32_t DataIndex;
    uint32_t DataOutIndex;
    uint32_t *DataIn;
    uint32_t *DataOut;
    bool     FFT_Busy;
}FFT_HandleTypeDef;

/* ################################ Initialization/Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* FFT reset */
#define __FFT_RESET_ENABLE()                           (FFT->FFT_SOFTRST_IIRFLT.Bits.NRST = 0)
#define __FFT_RESET_DISABLE()                          (FFT->FFT_SOFTRST_IIRFLT.Bits.NRST = 1)

/* FFT int enable/disable/clear */
#define __FFT_INT_ENALE()                              (FFT->FFT_ISRCR.Bits.INT_EN = 1)
#define __FFT_INT_DISALE()                             (FFT->FFT_ISRCR.Bits.INT_EN = 0)
#define __FFT_INT_STATUS_CLEAR()                       (FFT->FFT_ISRCR.Bits.INT_STATUS = 0)

/* FFT calculate id done */
#define __FFT_CAL_IS_DONE()                            (FFT->FFT_STATUS.Bits.CAL_DONE == 1)
/* FFT is dile */
#define __FFT_IS_IDLE()                                (FFT->FFT_STATUS.Bits.IDLE == 1)

/* FFT DMA config */
#define __FFT_DMA_ENABLE()                             (FFT->FFT_DMA.Bits.DMACR = 3)
#define __FFT_DMA_IN_THR(__THR__)                      (FFT->FFT_DMA.Bits.DMA_IN_THR  = __THR__)
#define __FFT_DMA_OUT_THR(__THR__)                     (FFT->FFT_DMA.Bits.DMA_OUT_THR = __THR__)

/* Exported functions --------------------------------------------------------*/

/* Initialize the fft module */
void fft_init(FFT_HandleTypeDef *hfft);
/* FFt start */
void fft_start(FFT_HandleTypeDef *hfft, uint32_t *fp_Data_In, uint32_t *fp_Data_Out, uint32_t fu32_BlockCNT);
/* FFT start with isr */
int fft_start_IT(FFT_HandleTypeDef *hfft, uint32_t *fp_Data_In, uint32_t *fp_Data_Out, uint32_t fu32_BlockCNT);
/* FFT interrupt handler */
void fft_IRQHandler(FFT_HandleTypeDef *hfft);

#endif
