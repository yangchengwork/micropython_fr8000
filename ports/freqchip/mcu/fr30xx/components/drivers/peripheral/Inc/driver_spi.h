/*
  ******************************************************************************
  * @file    driver_spi.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of SPI HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SPI_H__
#define __DRIVER_SPI_H__

#include "fr30xx.h"

/** @addtogroup SPI_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Control Register 0 */
typedef struct
{
    uint32_t rsv_0       : 4;
    uint32_t FRF         : 2;
    uint32_t SCPH        : 1;
    uint32_t SCPOL       : 1;
    uint32_t TMOD        : 2;
    uint32_t SLV_OE      : 1;
    uint32_t rsv_1       : 1;
    uint32_t CFS         : 4;
    uint32_t DFS_32      : 5;
    uint32_t SPI_FRF     : 2;
    uint32_t rsv_2       : 1;
    uint32_t SSTE        : 1;
    uint32_t rsv_3       : 7; 
}REG_Control0_t;

/* Control Register 1 */
typedef struct
{
    uint32_t NDF     : 16;
    uint32_t rsv_0   : 16;
}REG_Control1_t;

/* Microwire Control Register */
typedef struct
{
    uint32_t MWMOD : 1;
    uint32_t DMM   : 1;
    uint32_t MHS   : 1;
    uint32_t rsv_0 : 29;
}REG_MWCR_t;

/* Status Register */
typedef union
{
    volatile struct
    {
        uint32_t BUSY  : 1;
        uint32_t TFNF  : 1;
        uint32_t TFE   : 1;
        uint32_t RFNE  : 1;
        uint32_t RFF   : 1;
        uint32_t TXE   : 1;
        uint32_t DCOL  : 1;
        uint32_t rsv_0 : 25;
    }SR_BIT;

    uint32_t SR_DWORD;
}REG_SR_t;

/* Interrupt Mask Register */
typedef struct
{
    uint32_t TXEIM : 1;
    uint32_t TXOIM : 1;
    uint32_t RXUIM : 1;
    uint32_t RXOIM : 1;
    uint32_t RXFIM : 1;
    uint32_t MSTIM : 1;
    uint32_t rsv_0 : 26;
}REG_IMR_t;

/* Interrupt Status Register */
typedef union
{
    struct
    {
        uint32_t TXEIS : 1;
        uint32_t TXOIS : 1;
        uint32_t RXUIS : 1;
        uint32_t RXOIS : 1;
        uint32_t RXFIS : 1;
        uint32_t MSTIS : 1;
        uint32_t rsv_0 : 26;
    }ISR_BIT;

    uint32_t ISR_DWORD;
}REG_ISR_t;

/* Raw Interrupt Status Register */
typedef union
{
    struct
    {
        uint32_t TXEIR : 1;
        uint32_t TXOIR : 1;
        uint32_t RXUIR : 1;
        uint32_t RXOIR : 1;
        uint32_t RXFIR : 1;
        uint32_t MSTIR : 1;
        uint32_t rsv_0 : 26;
    }RISR_BIT;

    uint32_t RISR_DWORD;
}REG_RISR_t;

/* DMA Control Register */
typedef struct
{
    uint32_t RDMAE : 1;
    uint32_t TDMAE : 1;
    uint32_t rsv_0 : 30;
}REG_DMACR_t;

/* Control Register 2 */
typedef struct
{
    uint32_t TRANS_TYPE         : 2;
    uint32_t ADDR_L             : 4;
    uint32_t rsv_0              : 2;
    uint32_t INST_L             : 2;
    uint32_t DUAL_DEVICE_ACCESS : 1;
    uint32_t WAIT_CYCLES        : 5;
    uint32_t DDR_EN             : 1;
    uint32_t rsv_1              : 3;    
    uint32_t TX_ENDIAN          : 2;
    uint32_t RX_ENDIAN          : 2;
    uint32_t rsv_2              : 4;
    uint32_t SPI_CLOCK_FIX      : 1; 
    uint32_t SPI_RX_NO_INST_ADD : 1;
    uint32_t SLV_DUAL_MODE      : 1;
    uint32_t SLV_QUAD_MODE      : 1;   
}REG_Control2_t;

/* Flow Control Register */
typedef struct
{
    uint32_t RX_FLOW_LR  : 7;
    uint32_t rsv_0       : 1;
    uint32_t RX_FLOW_EN  : 1;    
    uint32_t rsv_1       : 7;
    uint32_t TX_FLOW_LR  : 7;
    uint32_t rsv_2       : 1;
    uint32_t TX_FLOW_EN  : 1;
    uint32_t rsv_3       : 7;
}
REG_Flow_Control_t;

/* -----------------------------------------------*/
/*                   SPI Register                 */
/* -----------------------------------------------*/
typedef struct 
{
    volatile REG_Control0_t       CTRL0;           /* Offset 0x00 */
    volatile REG_Control1_t       CTRL1;           /* Offset 0x04 */
    volatile uint32_t             SSI_EN;          /* Offset 0x08 */
    volatile REG_MWCR_t           MWCR;            /* Offset 0x0C */
    volatile uint32_t             SER;             /* Offset 0x10 */
    volatile uint32_t             BAUDR;           /* Offset 0x14 */
    volatile uint32_t             TXFTLR;          /* Offset 0x18 */
    volatile uint32_t             RXFTLR;          /* Offset 0x1C */
    volatile uint32_t             TXFLR;           /* Offset 0x20 */
    volatile uint32_t             RXFLR;           /* Offset 0x24 */
    volatile REG_SR_t             SR;              /* Offset 0x28 */
    volatile REG_IMR_t            IMR;             /* Offset 0x2C */
    volatile REG_ISR_t            ISR;             /* Offset 0x30 */
    volatile REG_RISR_t           RISR;            /* Offset 0x34 */
    volatile uint32_t             TXOICR;          /* Offset 0x38 */
    volatile uint32_t             RXOICR;          /* Offset 0x3C */
    volatile uint32_t             RXUICR;          /* Offset 0x40 */
    volatile uint32_t             MSTICR;          /* Offset 0x44 */
    volatile uint32_t             ICR;             /* Offset 0x48 */
    volatile REG_DMACR_t          DMACR;           /* Offset 0x4C */
    volatile uint32_t             DMATDLR;         /* Offset 0x50 */
    volatile uint32_t             DMARDLR;         /* Offset 0x54 */
    volatile uint32_t             rsv_0[2];
    volatile uint32_t             DR;              /* Offset 0x60 */
    volatile uint32_t             rsv_1[35];
    volatile uint32_t             RX_SAMPLE_DLY;   /* Offset 0xF0 */
    volatile REG_Control2_t       CTRL2;           /* Offset 0xF4 */
    volatile uint32_t             TED;             /* Offset 0xF8 */
    volatile REG_Flow_Control_t   FLOW_CTRL;       /* Offset 0xFC */
}struct_SPI_t;

#define SPIM0       ((struct_SPI_t *)SPIM0_BASE)
#define SPIM1       ((struct_SPI_t *)SPIM1_BASE)

#define SPIS0       ((struct_SPI_t *)SPIS0_BASE)
#define SPIS1       ((struct_SPI_t *)SPIS1_BASE)

#define SPIMX8_0    ((struct_SPI_t *)SPIMX8_0_BASE)
#define SPIMX8_1    ((struct_SPI_t *)SPIMX8_1_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */



/** @addtogroup SPI_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization、Config Section Start ################################ */

/* SPI Frame Size */
typedef enum  
{
    SPI_FRAME_SIZE_4BIT = 3,
    SPI_FRAME_SIZE_5BIT,
    SPI_FRAME_SIZE_6BIT,
    SPI_FRAME_SIZE_7BIT,
    SPI_FRAME_SIZE_8BIT,
    SPI_FRAME_SIZE_9BIT,
    SPI_FRAME_SIZE_10BIT,
    SPI_FRAME_SIZE_11BIT,
    SPI_FRAME_SIZE_12BIT,  
    SPI_FRAME_SIZE_13BIT,  
    SPI_FRAME_SIZE_14BIT,  
    SPI_FRAME_SIZE_15BIT,  
    SPI_FRAME_SIZE_16BIT,  
    SPI_FRAME_SIZE_17BIT,  
    SPI_FRAME_SIZE_18BIT,  
    SPI_FRAME_SIZE_19BIT,  
    SPI_FRAME_SIZE_20BIT,  
    SPI_FRAME_SIZE_21BIT,  
    SPI_FRAME_SIZE_22BIT,  
    SPI_FRAME_SIZE_23BIT,  
    SPI_FRAME_SIZE_24BIT,  
    SPI_FRAME_SIZE_25BIT,  
    SPI_FRAME_SIZE_26BIT,
    SPI_FRAME_SIZE_27BIT,
    SPI_FRAME_SIZE_28BIT,
    SPI_FRAME_SIZE_29BIT,
    SPI_FRAME_SIZE_30BIT,
    SPI_FRAME_SIZE_31BIT,
    SPI_FRAME_SIZE_32BIT,
}enum_FrameSize_t;

/* work mode */
typedef enum  
{
    SPI_WORK_MODE_0,    /* Idle: Low ; sample: first  edge */
    SPI_WORK_MODE_1,    /* Idle: Low ; sample: second edge */
    SPI_WORK_MODE_2,    /* Idle: High; sample: first  edge */
    SPI_WORK_MODE_3,    /* Idle: High; sample: second edge */
}enum_Work_Mode_t;

/* Instruct Length */
typedef enum  
{
    INST_0BIT,     /* none  Instruct */
    INST_4BIT,     /* 4bit  Instruct */
    INST_8BIT,     /* 8bit  Instruct */
    INST_16BIT,    /* 16bit Instruct */
}enum_InstructLength_t;

/* Address Length */
typedef enum  
{
    ADDR_0BIT,      /* none  Address */
    ADDR_4BIT,      /* 4bit  Address */
    ADDR_8BIT,      /* 8bit  Address */
    ADDR_12BIT,     /* 12bit Address */
    ADDR_16BIT,     /* 16bit Address */
    ADDR_20BIT,     /* 20bit Address */
    ADDR_24BIT,     /* 24bit Address */
    ADDR_28BIT,     /* 28bit Address */
    ADDR_32BIT,     /* 32bit Address */
}enum_AddressLength_t;

/* Transfer Type */
typedef enum  
{
    INST_ADDR_X1,       /* Instruct and Address use X1 mode */
    INST_1X_ADDR_XX,    /* Instruct usb 1X mode, Address use X2/X4 mode */
    INST_ADDR_XX,       /* Instruct and Address use X2/X4 mode */
}enum_TransferType_t;

/* 2X2/3X Select */
typedef enum  
{
    Wire_X2 = 1,    /* X2 mode */
    Wire_X4,        /* X4 mode */
    Wire_X8,        /* X8 mode */
}enum_Wire_X2X4_t;

/* Wire type */
typedef enum  
{
    Wire_Read,     /* Wire_Reade */
    Wire_Write,    /* Wire_Write */
}enum_Wire_Type_t;

/* TX-RX endian */
typedef enum{
    TX_RX_Endian_4321,  /* keep origin trans sequence */
    TX_RX_Endian_2143,  /* TX: MCU writes 0x12345678 to DR, then SPI-core shifts the data as 0x56781234 */
                        /* RX: input from SPI-bus is 0x12-0x34-0x56-0x78, MCU reads from DR is:
                                    32-bits frame size: 0x56781234
                                    16-bits frame size: 0x12340000, 0x56780000
                                    8-bits frame size: 0x00120000, 0x00340000, 0x00560000, 0x00780000 */
    TX_RX_Endian_1234,  /* TX: MCU writes 0x12345678 to DR, then SPI-core shifts the data as 0x78563412 */
                        /* RX: input from SPI-bus is 0x12-0x34-0x56-0x78, MCU reads from DR is:
                                    32-bits frame size: 0x78563412
                                    16-bits frame size: 0x34120000, 0x78560000
                                    8-bits frame size: 0x12000000, 0x34000000, 0x56000000, 0x78000000 */
} enum_TX_RX_Endian_t;

/*
 * @brief SPI Init Structure definition
 */
typedef struct
{
    uint32_t  Work_Mode;                /* This parameter can be a value of @ref SPI_WORK_MODE */

    uint32_t  Frame_Size;               /* This parameter can be a value of @ref enum_FrameSize_t */
    
    uint32_t  BaudRate_Prescaler;       /* This parameter can be a value 2 ~ 65534 */
    
    uint32_t  TxFIFOEmpty_Threshold;    /* This parameter can be a value 0 ~ 64 */

    uint32_t  RxFIFOFull_Threshold;     /* This parameter can be a value 1 ~ 64 */
}struct_SPIInit_t;

/*
 * @brief SPI Multiple wire transfer parameter
 */
typedef struct 
{    
    uint32_t Wire_X2X4X8;               /* This parameter can be a value of @ref enum_Wire_X2X4_t */
    
    uint32_t ReceiveWaitCycles;         /* This parameter can be a 5bit value */

    uint32_t InstructLength;            /* This parameter can be a value of @ref enum_InstructLength_t */
    uint16_t Instruct;                  /* This parameter can be a 16bit value */

    uint32_t AddressLength;             /* This parameter can be a value of @ref enum_AddressLength_t */
    uint32_t Address;                   /* This parameter can be a 32bit value */

    uint32_t TransferType;              /* This parameter can be a value of @ref enum_TransferType_t */
    
}struct_MultipleWire_t;

/*
 * @brief  SPI handle Structure definition
 */
typedef struct __SPI_HandleTypeDef
{
    struct_SPI_t            *SPIx;               /*!< SPI registers base address           */

    struct_SPIInit_t         Init;               /*!< SPI communication parameters         */

    struct_MultipleWire_t    MultWireParam;      /*!< SPI Multiple wire transfer parameter */
                                                 /*!< Used for multi-line transmission     */

    void (*TxCpltCallback)(struct __SPI_HandleTypeDef *hspi);       /*!< Tx complete Callback */
    void (*RxCpltCallback)(struct __SPI_HandleTypeDef *hspi);       /*!< Rx complete Callback */
    
    volatile uint32_t       u32_TxSize;          /*!< SPI Transmit parameters in interrupt  */
    volatile uint32_t       u32_TxCount;
    union {
        volatile void      *p_data;
        volatile uint8_t   *p_u8;
        volatile uint16_t  *p_u16;
        volatile uint32_t  *p_u32;
    } u_TxData;
    volatile bool           b_TxBusy;

    volatile uint32_t       u32_RxSize;          /*!< SPI Receive parameters in interrupt  */
    volatile uint32_t       u32_RxCount;
    union {
        volatile void      *p_data;
        volatile uint8_t   *p_u8;
        volatile uint16_t  *p_u16;
        volatile uint32_t  *p_u32;
    } u_RxData;
    volatile bool           b_RxBusy;
}SPI_HandleTypeDef;

/* ################################ Initialization、Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* SPI DDR Enable/Disable/Div */
#define __SPI_DDR_ENABLE(__SPIx__)                           (__SPIx__->CTRL2.DDR_EN = 1)
#define __SPI_DDR_DISABLE(__SPIx__)                          (__SPIx__->CTRL2.DDR_EN = 0)

#define __SPI_DDR_DRIVE_DIV(__SPIx__, __DIV__)               (__SPIx__->TED = __DIV__)


/* SPI Enable/Disable */
#define __SPI_ENABLE(__SPIx__)                               (__SPIx__->SSI_EN = 1)
#define __SPI_DISABLE(__SPIx__)                              (__SPIx__->SSI_EN = 0)

/* SPI Enable/Disable */
#define __SPI_CS_SET(__SPIx__)                               (__SPIx__->SER = 1)
#define __SPI_CS_RELEASE(__SPIx__)                           (__SPIx__->SER = 0)

/* Master Standard、Dual、Quad、Octal mode */
#define __SPI_SET_MODE_X1(__SPIx__)                          (__SPIx__->CTRL0.SPI_FRF = 0)
#define __SPI_SET_MODE_X2(__SPIx__)                          (__SPIx__->CTRL0.SPI_FRF = 1)
#define __SPI_SET_MODE_X4(__SPIx__)                          (__SPIx__->CTRL0.SPI_FRF = 2)
#define __SPI_SET_MODE_X8(__SPIx__)                          (__SPIx__->CTRL0.SPI_FRF = 3)
#define __SPI_SET_MODE_X2X4X8(__SPIx__, __WIDTH__)           (__SPIx__->CTRL0.SPI_FRF = __WIDTH__)

/* Slave Standard、Dual、Quad、Octal mode */
#define __SPI_SLAVE_SET_MODE_X1(__SPIx__)                    do{ __SPIx__->CTRL2.SLV_DUAL_MODE = 0; \
                                                                 __SPIx__->CTRL2.SLV_QUAD_MODE = 0;}while(0) 
#define __SPI_SLAVE_SET_MODE_X2(__SPIx__)                    do{ __SPIx__->CTRL2.SLV_DUAL_MODE = 1; \
                                                                 __SPIx__->CTRL2.SLV_QUAD_MODE = 0;}while(0) 
#define __SPI_SLAVE_SET_MODE_X4(__SPIx__)                    do{ __SPIx__->CTRL2.SLV_DUAL_MODE = 0; \
                                                                 __SPIx__->CTRL2.SLV_QUAD_MODE = 1;}while(0) 
/* SPI Slave output Enable */
#define __SPI_SLAVE_OUTPUT_ENABLE(__SPIx__)                  (__SPIx__->CTRL0.SLV_OE = 1)
#define __SPI_SLAVE_OUTPUT_DISABLE(__SPIx__)                 (__SPIx__->CTRL0.SLV_OE = 0)

/* Transfer mode */
#define __SPI_TMODE_RxTx(__SPIx__)                           (__SPIx__->CTRL0.TMOD = 0)
#define __SPI_TMODE_Tx_ONLY(__SPIx__)                        (__SPIx__->CTRL0.TMOD = 1)
#define __SPI_TMODE_Rx_ONLY(__SPIx__)                        (__SPIx__->CTRL0.TMOD = 2)
#define __SPI_TMODE_FLASH_READ(__SPIx__)                     (__SPIx__->CTRL0.TMOD = 3)

/* Data Frame Size */
#define __SPI_DATA_FRAME_SIZE(__SPIx__, __SIZE__)            (__SPIx__->CTRL0.DFS_32 = __SIZE__)
#define __SPI_DATA_FRAME_SIZE_GET(__SPIx__)                  (__SPIx__->CTRL0.DFS_32)

/* Receive data size */
#define __SPI_RECEIVE_SIZE(__SPIx__, __SIZE__)               (__SPIx__->CTRL1.NDF = __SIZE__)

/* RxFIFO_FULL_THRESHOLD */
/* TxFIFO_EMPTY_THRESHOLD */
#define __SPI_RxFIFO_FULL_THRESHOLD(__SPIx__, __THRESHOLD__)     (__SPIx__->RXFTLR = __THRESHOLD__)
#define __SPI_TxFIFO_EMPTY_THRESHOLD(__SPIx__, __THRESHOLD__)    (__SPIx__->TXFTLR = __THRESHOLD__)

/* Get Rx/Tx FIFO current level */
#define __SPI_GET_RxFIFO_LEVEL(__SPIx__)                     (__SPIx__->RXFLR)
#define __SPI_GET_TxFIFO_LEVEL(__SPIx__)                     (__SPIx__->TXFLR)

/* DMA Enable/Disable, level */
#define __SPI_DMA_RX_ENABLE(__SPIx__)                        (__SPIx__->DMACR.RDMAE = 1)
#define __SPI_DMA_TX_ENABLE(__SPIx__)                        (__SPIx__->DMACR.TDMAE = 1)
#define __SPI_DMA_RX_DISABLE(__SPIx__)                       (__SPIx__->DMACR.RDMAE = 0)
#define __SPI_DMA_TX_DISABLE(__SPIx__)                       (__SPIx__->DMACR.TDMAE = 0)
#define __SPI_DMA_RX_LEVEL(__SPIx__, __LEVEL__)              (__SPIx__->DMARDLR = __LEVEL__)
#define __SPI_DMA_TX_LEVEL(__SPIx__, __LEVEL__)              (__SPIx__->DMATDLR = __LEVEL__)

/* SPI busy status */
#define __SPI_IS_BUSY(__SPIx__)                              (__SPIx__->SR.SR_BIT.BUSY)

/* Tx/Rx FIFO status */
#define __SPI_IS_RxFIFO_EMPTY(__SPIx__)                      (__SPIx__->SR.SR_BIT.RFNE == 0)
#define __SPI_IS_RxFIFO_NOT_EMPTY(__SPIx__)                  (__SPIx__->SR.SR_BIT.RFNE == 1)
#define __SPI_IS_RxFIFO_FULL(__SPIx__)                       (__SPIx__->SR.SR_BIT.RFF  == 1)
#define __SPI_IS_TxFIFO_EMPTY(__SPIx__)                      (__SPIx__->SR.SR_BIT.TFE  == 1)
#define __SPI_IS_TxFIFO_FULL(__SPIx__)                       (__SPIx__->SR.SR_BIT.TFNF == 0)

/* Tx/Rx FIFO interrupt */
#define __SPI_TxFIFO_EMPTY_INT_ENABLE(__SPIx__)              (__SPIx__->IMR.TXEIM = 1)
#define __SPI_RxFIFO_FULL_INT_ENABLE(__SPIx__)               (__SPIx__->IMR.RXFIM = 1)

#define __SPI_TxFIFO_EMPTY_INT_DISABLE(__SPIx__)             (__SPIx__->IMR.TXEIM = 0)
#define __SPI_RxFIFO_FULL_INT_DISABLE(__SPIx__)              (__SPIx__->IMR.RXFIM = 0)

#define __SPI_TxFIFO_EMPTY_INT_STATUS(__SPIx__)              (__SPIx__->ISR.ISR_BIT.TXEIS)
#define __SPI_RxFIFO_FULL_INT_STATUS(__SPIx__)               (__SPIx__->ISR.ISR_BIT.RXFIS)

/* __SPI_RX_SAMPLE_DLY */
#define __SPI_RX_SAMPLE_DLY(__SPIx__, __DELAY__)             (__SPIx__->RX_SAMPLE_DLY = __DELAY__)

/* SPI Master CS Toggle Enable */
#define __SPI_CS_TOGGLE_ENABLE(__SPIx__)                     (__SPIx__->CTRL0.SSTE = 1)
#define __SPI_CS_TOGGLE_DISABLE(__SPIx__)                    (__SPIx__->CTRL0.SSTE = 0)

/* SPI TX endian setting */
#define __SPI_TX_ENDIAN_SET(__SPIx__, v)                     (__SPIx__->CTRL2.TX_ENDIAN = v)
/* SPI RX endian setting */
#define __SPI_RX_ENDIAN_SET(__SPIx__, v)                     (__SPIx__->CTRL2.RX_ENDIAN = v)

/*-----------------------------------------------------------------------------------*/
/* Master Exported functions --------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/

/* spi_IRQHandler */
void spi_master_IRQHandler(SPI_HandleTypeDef *hspi);

/* spi_master_init */
void spi_master_init(SPI_HandleTypeDef *hspi);

/* Master Standard mode Transmit/Receive */
/* blocking、Interrupt、DMA mode  */
void spi_master_transmit_X1(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);
void spi_master_transmit_X1_IT(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);
void spi_master_transmit_X1_DMA(SPI_HandleTypeDef *hspi);

void spi_master_receive_X1(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);

void spi_master_readflash_X1(SPI_HandleTypeDef *hspi, uint16_t *fp_CMD_ADDR, uint32_t fu32_CMDLegnth, uint8_t *fp_Data, uint16_t fu16_Size);
void spi_master_readflash_X1_IT(SPI_HandleTypeDef *hspi, uint8_t *fp_CMD_ADDR, uint32_t fu32_CMDLegnth, uint8_t *fp_Data, uint16_t fu16_Size);
void spi_master_readflash_X1_DMA(SPI_HandleTypeDef *hspi, uint8_t *fp_CMD_ADDR, uint32_t fu32_CMDLegnth, uint16_t fu16_Size);

/* Master Dual、Quad mode Transmit/Receive */
/* blocking、Interrupt、DMA mode */
void spi_master_transmit_X2X4X8(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);
void spi_master_transmit_X2X4X8_IT(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);
void spi_master_transmit_X2X4X8_DMA(SPI_HandleTypeDef *hspi);

void spi_master_receive_X2X4X8(SPI_HandleTypeDef *hspi, void *fp_Data, uint16_t fu16_Size);
void spi_master_receive_X2X4X8_IT(SPI_HandleTypeDef *hspi, void *fp_Data, uint16_t fu16_Size);
void spi_master_receive_X2X4X8_DMA(SPI_HandleTypeDef *hspi, uint16_t fu16_Size);

/* spi_master_MultWireConfig */
/* spi_slave_MultWireConfig */
void spi_master_MultWireConfig(SPI_HandleTypeDef *hspi, enum_Wire_Type_t fe_type);
void spi_slave_MultWireConfig(SPI_HandleTypeDef *hspi, enum_Wire_Type_t fe_type);

/*-----------------------------------------------------------------------------------*/
/* Slave Exported functions ---------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/

/* spi_slave_IRQHandler */
void spi_slave_IRQHandler(SPI_HandleTypeDef *hspi);

/* spi_slave_init */
void spi_slave_init(SPI_HandleTypeDef *hspi);

/* Slave Standard mode Transmit/Receive */
/* blocking、Interrupt、DMA mode  */
void spi_slave_transmit(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);
void spi_slave_transmit_IT(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);
void spi_slave_transmit_DMA(SPI_HandleTypeDef *hspi);

void spi_slave_receive(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);
void spi_slave_receive_IT(SPI_HandleTypeDef *hspi, void *fp_Data, uint32_t fu32_Size);
void spi_slave_receive_DMA(SPI_HandleTypeDef *hspi);

#endif
