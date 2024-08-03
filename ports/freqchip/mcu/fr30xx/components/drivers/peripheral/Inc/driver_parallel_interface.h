/*
  ******************************************************************************
  * @file    driver_parallel_interface.H
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of parallel_interface HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_PARALLEL_INTERFACE_H__
#define __DRIVER_PARALLEL_INTERFACE_H__

#include "fr30xx.h"

/** @addtogroup Parallel_Interface_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* parallel interface config */
typedef struct 
{
    uint32_t DC_POLARITY : 1;
    uint32_t CS_POLARITY : 1;
    uint32_t MODE        : 1;
    uint32_t PARA_WIDTH  : 1;
    uint32_t rsv_0       : 28;
}REG_INTERFACE_CFG_t;

/* Write/Read clock Config */
typedef struct 
{
    uint32_t WRITE_CLK_CFG : 3;
    uint32_t rsv_0         : 1;
    uint32_t READ_CLK_CFG  : 4;
    uint32_t WR_L_LEN      : 3;
    uint32_t rsv_1         : 1; 
    uint32_t WR_H_LEN      : 3;
    uint32_t rsv_2         : 17;
}REG_WR_CLK_t;

/* Data transmission Configuration */
typedef struct 
{
    uint32_t DATA_TRANS_SEQ_0 : 2;
    uint32_t DATA_TRANS_SEQ_1 : 2;
    uint32_t DATA_TRANS_SEQ_2 : 2;
    uint32_t DATA_TRANS_SEQ_3 : 2;
    uint32_t rsv_1            :24;
}REG_DATA_CFG_t;

/* DMA Configuration */
typedef struct 
{
    uint32_t DMA_TX_LEVEL : 5;
    uint32_t DMA_ENABLE   : 1;
    uint32_t rsv_0        : 26;
}REG_DMA_t;

/* -------------------------------------------*/
/*           parallel Register                */
/* -------------------------------------------*/
typedef struct 
{
    volatile REG_INTERFACE_CFG_t    INTF_CFG;        /* offset 0x00 */
    volatile uint32_t               CSX;             /* offset 0x04 */
    volatile REG_WR_CLK_t           CRM;             /* offset 0x08 */    
    volatile uint32_t               BUS_STATUS;      /* offset 0x0C */ 
    volatile uint32_t               CFG;             /* offset 0x10 */ 
    volatile uint32_t               DATA_WR_LEN;     /* offset 0x14 */  
    volatile REG_DATA_CFG_t         DATA_CFG;        /* offset 0x18 */   
    volatile uint32_t               TX_FIFO;         /* offset 0x1C */  
    volatile uint32_t               RD_REQ;          /* offset 0x20 */ 
    volatile uint32_t               DAT_RD;          /* offset 0x24 */ 
    volatile uint32_t               TXFF_AEMP_LV;    /* offset 0x28 */    
    volatile uint32_t               TXFF_CLR;        /* offset 0x2C */
    volatile uint32_t               INT_CONTROL;     /* offset 0x30 */  
    volatile uint32_t               INT_STATUS;      /* offset 0x34 */     
    volatile REG_DMA_t              DMA;             /* offset 0x38 */      
}struct_Parallel_t;

#define PARALLEL0              ((struct_Parallel_t *)PARALLEL_BASE)

/* ################################ Register Section END ################################ */
/**
  * @}
  */



/** @addtogroup Parallel_Interface_Initialization_Config_Section
  * @{            
  */
/* ################################ Initialization_Config Section Start ################################ */

/** @defgroup PARALLEL_FIFO PARALLEL FIFO 
  * @{
  */
#define PARALLEL_FIFO_DEPTH      32
/**
  * @}
  */
/* mode select */
typedef enum
{
    MODE_8080,
    MODE_6800,
}enum_Parallel_MODE_t;

/* data bus width */
typedef enum
{
    DATA_BUS_8_BIT,
    DATA_BUS_16_BIT,
}enum_DATA_BUS_t;

/* read clock division */
typedef enum
{
    RDCLK_DIV_1,
    RDCLK_DIV_2,
    RDCLK_DIV_3,
    RDCLK_DIV_4,
    RDCLK_DIV_6,
    RDCLK_DIV_8,
    RDCLK_DIV_16,
    RDCLK_DIV_32,
    RDCLK_DIV_64,
}enum_RDCLK_DIV_t;

/* write clock division */
typedef enum
{
    WDCLK_DIV_1,
    WDCLK_DIV_2,
    WDCLK_DIV_3,
    WDCLK_DIV_4,
    WDCLK_DIV_6,
    WDCLK_DIV_8,
}enum_WDCLK_DIV_t;

/* interrupt index */
typedef enum
{
    INT_TXFIFO_FULL     = 0x00000001,
    INT_TXFIFO_EMPTY    = 0x00000002, 
    INT_TXFIFO_LEVEMPT  = 0x00000004,
}enum_INT_t;

/**
  * @brief  parallel Initialization Structure definition
  */
typedef struct 
{
    uint32_t ParallelMode;              /* This parameter can be a value of @ref enum_Parallel_MODE_t */

    uint32_t DataBusSelect;             /* This parameter can be a value of @ref enum_DATA_BUS_t */

    uint32_t ReadClock;                 /* This parameter can be a value of @ref enum_RDCLK_DIV_t */

    uint32_t WriteClock;                /* This parameter can be a value of @ref enum_WDCLK_DIV_t */
}str_ParallelInit_t;

/**
 * @brief  parallel handle Structure definition
 */
typedef struct
{
    struct_Parallel_t    *PARALLELx;          /*!< PARALLEL registers base address        */
    
    str_ParallelInit_t    Init;               /*!< PARALLEL communication parameters      */
}PARALLEL_HandTypeDef;

/* ################################ Initialization_Config Section END ################################ */
/**
  * @}
  */

 /* Exported macro ------------------------------------------------------------*/

/* Parallel tx fifo level */                                                             /* fu8_level: 0 ~ 31 */
#define __PARALLEL_TX_FIFO_ALMOST_EMPTY_LEVEL(__PARALLELx__, __LEVEL__)                  (__PARALLELx__->TXFF_AEMP_LV = __LEVEL__)

/* Parallel tx fifo reset */
/* Parallel tx fifo release */
#define __PARALLEL_TX_FIFO_RESET(__PARALLELx__)                                          (__PARALLELx__->TXFF_CLR = 0x07)
#define __PARALLEL_TX_FIFO_RELEASE(__PARALLELx__)                                        (__PARALLELx__->TXFF_CLR = 0x00)

/* Parallel writer CMD */
#define __PARALLEL_WR_CMD(__PARALLELx__ , __CMD__)                                       (__PARALLELx__->CFG = __CMD__)                                                                            
#define __PARALLEL_WR_PARAM(__PARALLELx__ , __DATA__)                                    (__PARALLELx__->CFG = 0x10000 | __DATA__)

/* Parallel get interrupt status */
#define __PARALLEL_INT_STATUS(__PARALLELx__)                                             (__PARALLELx__->INT_STATUS)                                                                                     
/* Parallel interrupt Status enable/disable */        
#define __PARALLEL_INT_STATUS_ENABLE(__PARALLELx__, __STATUS__)                          (__PARALLELx__->INT_CONTROL |=  (__STATUS__))                        
#define __PARALLEL_INT_STATUS_DISABLE(__PARALLELx__, __STATUS__)                         (__PARALLELx__->INT_CONTROL &= ~(__STATUS__))  
#define __PARALLEL_INT_STATUS_ALL_ENABLE(__PARALLELx__, __STATUS__)                      (__PARALLELx__->INT_CONTROL = 0x0F)                                                                                         
#define __PARALLEL_INT_STATUS_ALL_DISABLE(__PARALLELx__, __STATUS__)                     (__PARALLELx__->INT_CONTROL = 0x00)   
                                                                                       
/* Parallel bus status */      
#define __PARALLEL_IS_BUS_BUSY(__PARALLELx__)                                            (__PARALLELx__->BUS_STATUS)
/* Parallel bus status */      
#define __PARALLEL_RD_REQ(__PARALLELx__)                                                 (__PARALLELx__->RD_REQ = 0x1)
                                                                    
/* Parallel_dma_requset_level */                                                         /* fu8_level: 0 ~ 31 */
#define __PARALLEL_DMA_TX_LEVEL(__PARALLELx__, __LEVEL__)                                (__PARALLELx__->DMA.DMA_TX_LEVEL = __LEVEL__)
/* Parallel_dma ENABLE and DISABLE */
#define __PARALLEL_DMA_ENABLE(__PARALLELx__)                                             (__PARALLELx__->DMA.DMA_ENABLE = 1)   
#define __PARALLEL_DMA_DISABLE(__PARALLELx__)                                            (__PARALLELx__->DMA.DMA_ENABLE = 0) 

/* Parallel_cs_set */
/* Parallel_cs_release */
#define __PARALLEL_CS_SET(__PARALLELx__)                                                 (__PARALLELx__->CSX = 0)
#define __PARALLEL_CS_RELEASE(__PARALLELx__)                                             (__PARALLELx__->CSX = 1)

/* Parallel_set_bus_8bit */
/* Parallel_set_bus_16bit */
#define __PARALLEL_SET_BUS_8BIT(__PARALLELx__)                                           (__PARALLELx__->INTF_CFG.PARA_WIDTH = DATA_BUS_8_BIT)  
#define __PARALLEL_SET_BUS_16BIT(__PARALLELx__)                                          (__PARALLELx__->INTF_CFG.PARA_WIDTH = DATA_BUS_16_BIT)                     

/* Parallel_wrclk_div */
/* Parallel_rdclk_div */
#define __PARALLEL_WRCLK_DIV(__PARALLELx__, __WDCLK_DIV__)                               (__PARALLELx__->CRM.WRITE_CLK_CFG = __WDCLK_DIV__)
#define __PARALLEL_RDCLK_DIV(__PARALLELx__, __RDCLK_DIV__)                               (__PARALLELx__->CRM.READ_CLK_CFG  = __RDCLK_DIV__)

/* Parallel_wrclk_HighLength */
/* Parallel_wrclk_LowLength  */
#define __PARALLEL_WRCLK_HIGHLENGTH(__PARALLELx__, __LENGTH__)                           (__PARALLELx__->CRM.WR_H_LEN = __LENGTH__)         
#define __PARALLEL_WRCLK_LOWLENGTH(__PARALLELx__, __LENGTH__)                            (__PARALLELx__->CRM.WR_L_LEN = __LENGTH__)  

/* Parallel_CS_Polarity */                                                               /* fb_Polarity: 1: high active */
/* Parallel_DC_Polarity */                                                               /*              0: low  active */
#define __PARALLEL_CS_POLARITY(__PARALLELx__, __POLARITY__)                              (__PARALLELx__->INTF_CFG.CS_POLARITY = __POLARITY__)  
#define __PARALLEL_DC_POLARITY(__PARALLELx__, __FB_POLARITY__)                           (__PARALLELx__->INTF_CFG.DC_POLARITY = __POLARITY__)

/* __PARALLEL_Set_WR_LEN */ 
#define __PARALLEL_SET_WR_LEN(__PARALLELx__, __LEVEL__)                                  (__PARALLELx__->DATA_WR_LEN = __LEVEL__)                             


/* Exported functions ---------------------------------------------------------------*/

/* parallel_init */
void parallel_init(PARALLEL_HandTypeDef *hparallel);

/* Parallel_write_cmd */
/* Parallel_write_param */
/* Parallel_write_data */
void Parallel_write_cmd(PARALLEL_HandTypeDef *hparallel, uint8_t fp8_CMD);
void Parallel_write_param(PARALLEL_HandTypeDef *hparallel, uint16_t fu16_Data);
void Parallel_write_data(PARALLEL_HandTypeDef *hparallel, uint32_t *fp32_WriteBuffer, uint32_t fu32_WriteNum);

/* Parallel_read_data_8bit */
/* Parallel_read_data_16bit */
void Parallel_read_data_8bit(PARALLEL_HandTypeDef *hparallel, uint8_t fu8_Param, uint8_t *fp8_ReadBuffer, uint32_t fu32_ReadNum);
void Parallel_read_data_16bit(PARALLEL_HandTypeDef *hparallel, uint8_t fu8_Param, uint16_t *fp16_ReadBuffer, uint32_t fu32_ReadNum);

#endif
