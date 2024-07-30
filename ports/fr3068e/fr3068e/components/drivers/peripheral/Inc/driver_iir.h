/*
  ******************************************************************************
  * @file    driver_iir.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of IIR module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_IIR_H__
#define __DRIVER_IIR_H__

#include "fr30xx.h"

/** @addtogroup IIR_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* IIR CTRL */
typedef struct
{
    uint32_t N_DIV             : 7;
    uint32_t rsv_0             : 1;
    uint32_t ORDER_SEL         : 2;
    uint32_t rsv_1             : 6;
    uint32_t NODE_SEL          : 2;
    uint32_t rsv_2             : 6;
    uint32_t NBYTE_SEL         : 2;
    uint32_t ESV4              : 6;
} REG_IIR_CTRL_t;


/* IIR THR FIFO */
typedef struct
{
    uint32_t THR_TX_FIFO       : 6;
    uint32_t rsv_0             : 10;
    uint32_t THR_RX_FIFO       : 6;
    uint32_t rsv_1             : 10;
} REG_IIR_THR_FIFO_t;

typedef struct 
{
    volatile uint32_t             IIR_COEF[20];              /* Offser 0x00-0x4c*/
    volatile REG_IIR_CTRL_t       IIR_CTRL;                  /* Offset 0x50*/
    volatile REG_IIR_THR_FIFO_t   IIR_THR_FIFO;              /* Offset 0x54*/
    volatile uint32_t             rsv_0;
    volatile uint32_t             rsv_1;
    volatile uint32_t             IIR_SOFTRST;               /* Offset 0x60*/
    volatile uint32_t             rsv_2[5];
    volatile uint32_t             IIR_STATUS;                /* Offset 0x78*/
    volatile uint32_t             rsv_3; 
    volatile uint32_t             IIR_FIFO;                  /* Offset 0x80*/       
}struct_IIR_t;

#define IIR_FILTER                     ((struct_IIR_t *)IIR_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup IIR_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization_Config Section Start ################################ */

/* FIFO Status */
typedef enum
{
    TX_FIFO_FULL     = 0x01, 
    TX_FIFO_EMPTY    = 0x02,
    TX_FIFO_AL_EMPTY = 0x04,
    RX_FIFO_FULL     = 0x08, 
    RX_FIFO_EMPTY    = 0x10, 
    RX_FIFO_AL_FULL  = 0x20,
}enum_IIR_INT_Index_t;

/* Nbytes Select */
typedef enum{
    IIR_BYTE_1,
    IIR_BYTE_2,
    IIR_BYTE_3,
    IIR_BYTE_ALL,
}enum_Nbytes_sel_t;

/* Node Select */
typedef enum{
    THE_FIRST_STAGE_OUTPUT,
    THE_SENCOND_STAGE_OUTPUT,
    THE_THIRD_STAGE_OUTPUT,
    THE_FOURTH_STAGE_OUTPUT,
}enum_Node_Sel_t;

/* Order Select */
typedef enum{
    ORDER_2,
    ORDER_4,
    ORDER_6,
    ORDER_8,
}enum_Order_Sel_t;

typedef struct
{
    uint32_t IIRCoef[20];         /*!< Specifies the internal Feedback coefficient.
                                       This parameter The value can be a value 0~0xFFFFFF*/ 
                                 
    uint8_t N_Div;               /*!< Specifies the internal read/write tx and rx FIFO is relative The frequency division factor of the system clock.
                                       This parameter The value should be greater than 2*(order_sel + 1)*5 */ 
                                 
    uint8_t Order_Sel;           /*!< Specifies the internal Filter order configuration.
                                       This parameter can be a value of @ref enum_Order_Sel_t */ 
                                 
    uint8_t Node_Sel;            /*!< Specifies the internal Filter order configuration.
                                       This parameter can be a value of @ref enum_Node_Sel_t */ 
                                 
    uint8_t Nbytes_Sel;          /*!< Specifies the internal Filter order configuration.
                                       This parameter can be a value of @ref enum_Nbytes_sel_t */ 

}IIR_InitTypeDef;

/* ################################ Initialization_Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* RxFIFO/TxFIFO Threshold level */
#define __IIR_RxFIFO_THRESHOLD_LEVEL(__LEVEL__)                  (IIR_FILTER->IIR_THR_FIFO.THR_RX_FIFO = __LEVEL__)
#define __IIR_TxFIFO_THRESHOLD_LEVEL(__LEVEL__)                  (IIR_FILTER->IIR_THR_FIFO.THR_TX_FIFO = __LEVEL__)

/* SOFTRST Set and Clear */
#define __IIR_SOFTRST_SET()                                      (IIR_FILTER->IIR_SOFTRST = 0)
#define __IIR_SOFTRST_CLEAR()                                    (IIR_FILTER->IIR_SOFTRST = 1)

/* Get FIFO status */                                                                 
#define __IIR_GET_FIFO_STATUS(__STATUS__)                        (IIR_FILTER->IIR_STATUS & __STATUS__)

/* Exported functions ---------------------------------------------------------*/
/* iir_init */
void iir_init(IIR_InitTypeDef *hiir);
/* iir_filter_start */
void iir_filter_start(uint32_t *fp_Data_In, uint32_t *fp_Data_Out, uint32_t fu32_Size);

#endif
