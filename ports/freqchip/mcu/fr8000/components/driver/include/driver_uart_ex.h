/*
  ******************************************************************************
  * @file    driver_uart_ex.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of UART HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_UART_EX_H__
#define __DRIVER_UART_EX_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "driver_system.h"
#include "plf.h"

/** @addtogroup UART_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* DATA/DLL Register */
typedef union
{
    uint32_t DATA;
    uint32_t DLL;
}REG_DATA_DLL_t;

/* IER/DLH Register */
typedef union
{
    struct
    {
        uint32_t ERBFI : 1;
        uint32_t ETBEI : 1;
        uint32_t ELSI  : 1;
        uint32_t EDSSI : 1;
        uint32_t rsv_0 : 3;
        uint32_t PTIME : 1;
        uint32_t rsv_1 : 24;
    }IER;
    
    uint32_t DLH;
}REG_IER_DLH_t;

/* FCR/IID Register */
typedef union
{
    uint32_t FCR;
    uint32_t IID;
}REG_FCR_IID_t;

/* Line control Register */
typedef struct
{
    uint32_t DLS   : 2;
    uint32_t STOP  : 1;
    uint32_t PEN   : 1;
    uint32_t EPS   : 1;
    uint32_t SP    : 1;
    uint32_t BC    : 1;
    uint32_t DLAB  : 1;
    uint32_t rsv_0 : 24;
}REG_LCR_t;

/* MODEM control Register */
typedef struct
{
    uint32_t rsv_0 : 1;
    uint32_t RTS   : 1;
    uint32_t rsv_1 : 3;
    uint32_t AFCE  : 1;
    uint32_t SIRE  : 1;
    uint32_t rsv_2 : 25;
}REG_MCR_t;

/* Status Register */
typedef union
{
    struct
    {
        uint32_t DR    : 1;
        uint32_t OE    : 1;
        uint32_t PE    : 1;
        uint32_t FE    : 1;
        uint32_t BI    : 1;
        uint32_t THRE  : 1;
        uint32_t TEMT  : 1;
        uint32_t RFE   : 1;
        uint32_t rsv_0 : 24;
    }LSR_BIT;

    uint32_t LSR_DWORD;
}REG_LSR_t;

/* MODEM status Register */
typedef struct
{
    uint32_t rsv_0 : 4;
    uint32_t CTS   : 1;
    uint32_t rsv_1 : 27;
}REG_MSR_t;

/* uart status Register */
typedef struct
{
    uint32_t rsv_0 : 1;
    uint32_t TFNF  : 1;
    uint32_t TFE   : 1;
    uint32_t RFNE  : 1;
    uint32_t RFF   : 1;
    uint32_t rsv_1 : 27;
}REG_USR_t;

/* DLF Register */
typedef struct
{
    uint32_t DLF   : 4;
    uint32_t rsv_0 : 28;
}REG_DLF_t;

/* ------------------------------------------------*/
/*                   UART Register                 */
/* ------------------------------------------------*/
typedef struct 
{
    volatile REG_DATA_DLL_t  DATA_DLL;    /* Offset 0x00 */
    volatile REG_IER_DLH_t   IER_DLH;     /* Offset 0x04 */
    volatile REG_FCR_IID_t   FCR_IID;     /* Offset 0x08 */
    volatile REG_LCR_t       LCR;         /* Offset 0x0C */
    volatile REG_MCR_t       MCR;         /* Offset 0x10 */
    volatile REG_LSR_t       LSR;         /* Offset 0x14 */
    volatile REG_MSR_t       MSR;         /* Offset 0x18 */
    volatile uint32_t        rsv_0[24];
    volatile REG_USR_t       USR;         /* Offset 0x7C */
    volatile uint32_t        rsv_1[16];
    volatile REG_DLF_t       DLF;         /* Offset 0xC0 */ 
}struct_UART_t;

#define Uart0    ((struct_UART_t *)UART0_BASE)
#define Uart1    ((struct_UART_t *)UART1_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */



/** @addtogroup UART_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */


/* Uart data length */
typedef enum
{
    UART_DATA_LENGTH_5BIT,    /*!< 5-bit Word Length */
    UART_DATA_LENGTH_6BIT,    /*!< 6-bit Word Length */
    UART_DATA_LENGTH_7BIT,    /*!< 7-bit Word Length */
    UART_DATA_LENGTH_8BIT,    /*!< 8-bit Word Length */
}enum_DataLength_t;

/* Stop bit */
typedef enum
{
    UART_STOPBITS_1,      /*!< UART frame with 1 stop bit      */
    UART_STOPBITS_2,      /*!< UART frame with 2 stop bit      */
}enum_StopBit_t;

/* Parity */
typedef enum
{
    UART_PARITY_NONE,    /*!< No parity   */
    UART_PARITY_ODD,     /*!< Odd parity  */
    UART_PARITY_EVEN,    /*!< Even parity */
    UART_PARITY_0,       /*!< 0 parity    */
    UART_PARITY_1,       /*!< 1 parity    */
}enum_Parity_t;

/* FIFO Enable/Disable */
typedef enum
{
    UART_FIFO_DISABLE,    /*!< FIFO Disable */
    UART_FIFO_ENABLE,     /*!< FIFO Enable  */
}enum_UART_FIFO_t;

/* Line Status index */
typedef enum
{
    STATUS_DR   = 0x01,      /*!< Data Ready              */
    STATUS_OE   = 0x02,      /*!< Over   Err              */
    STATUS_PE   = 0x04,      /*!< Parity Err              */
    STATUS_FE   = 0x08,      /*!< Frame  Err              */
    STATUS_BI   = 0x10,      /*!< Break  ERR              */
    STATUS_THRE = 0x20,      /*!< Tx empty                */
    STATUS_TEMT = 0x40,      /*!< Tx Shift Register empty */
    STATUS_RFE  = 0x80,      /*!< Rx FIFO ERR             */
}enum_UART_LINE_STATUS_t;

/* Interrupt Status index */
typedef enum
{
    INT_INDEX_MODEM   = 0x0,      /*!< modem status interrupt */
    INT_INDEX_NONE    = 0x1,      /*!< NONE                   */
    INT_INDEX_TXE     = 0x2,      /*!< Tx empty interrupt     */
    INT_INDEX_RX      = 0x4,      /*!< Rx Threshold interrupt */
    INT_INDEX_LINE    = 0x6,      /*!< Line status interrupt  */
    INT_INDEX_RX_TOUT = 0xC,      /*!< Rx timeout interrupt   */
}enum_UART_INT_INDEX_t;

/* FCR BIT position */
typedef enum
{
    FCR_FIFOE  = 0x00,
    FCR_RFIFOR = 0x01,
    FCR_XFIFOR = 0x02,
    FCR_DMAM   = 0x03,
    FCR_TET    = 0x04,
    FCR_RT     = 0x06, 
}enum_FCR_t;

/*
 * @brief UART Init Structure definition
 */
typedef struct
{
    uint32_t BaudRate;                  /*!< This parameter configures the UART communication baud rate. */

    uint32_t DataLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                             This parameter can be a value of @ref enum_DataLength_t. */

    uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                             This parameter can be a value of @ref enum_StopBit_t. */

    uint32_t Parity;                    /*!< Specifies the parity mode. 
                                             This parameter can be a value of @ref enum_Parity_t. */

    uint32_t FIFO_Mode;                 /*!< Specifies the FIFO mode. 
                                             This parameter can be a value of @ref enum_UART_FIFO_t. */
}struct_UARTInit_t;

/*
 * @brief  UART handle Structure definition
 */
typedef struct __UART_HandleTypeDef
{
    struct_UART_t           *UARTx;              /*!< UART registers base address        */

    struct_UARTInit_t        Init;               /*!< UART communication parameters      */

    volatile uint32_t        FCR_Shadow;

    volatile void (*TxCpltCallback)(struct __UART_HandleTypeDef *huart);       /* Tx complete Callback */
    volatile void (*RxCpltCallback)(struct __UART_HandleTypeDef *huart);       /* Rx complete Callback */

    volatile uint32_t        u32_TxSize;         /*!< UART Transmit parameters in interrupt  */
    volatile uint32_t        u32_TxCount;
    volatile uint8_t        *p_TxData;
    volatile bool            b_TxBusy;

    volatile uint32_t        u32_RxSize;         /*!< UART Receive parameters in interrupt  */
    volatile uint32_t        u32_RxCount;
    volatile uint8_t        *p_RxData;
    volatile bool            b_RxBusy;
}UART_HandleTypeDef;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* __UART_IS_FIFO_Enable */
/* __UART_FIFO_Enable  */
/* __UART_FIFO_Disable */
/* __UART_TxFIFO_Reset */
/* __UART_RxFIFO_Reset */
/* __UART_RxFIFO_FULL_LEVEL  */
/* __UART_TxFIFO_EMPTY_LEVEL */
#define __UART_IS_FIFO_Enable(__UART__)           (__UART__->FCR_Shadow & 0x01)

#define __UART_FIFO_Enable(__UART__)           do{ __UART__->FCR_Shadow |=  0x01; \
                                                   __UART__->FCR_Shadow |=  0x08; \
                                                   __UART__->UARTx->FCR_IID.FCR = __UART__->FCR_Shadow; }while(0)
#define __UART_FIFO_Disable(__UART__)          do{ __UART__->FCR_Shadow &= ~0x01; \
                                                   __UART__->FCR_Shadow &= ~0x08; \
                                                   __UART__->UARTx->FCR_IID.FCR = __UART__->FCR_Shadow; }while(0)
#define __UART_TxFIFO_Reset(__UART__)             (__UART__->UARTx->FCR_IID.FCR = __UART__->FCR_Shadow | 0x04)
#define __UART_RxFIFO_Reset(__UART__)             (__UART__->UARTx->FCR_IID.FCR = __UART__->FCR_Shadow | 0x02)

/* __LEVEL__ = 0: RxFIFO have 1 byte  */
/* __LEVEL__ = 1: RxFIFO 1/4 full     */
/* __LEVEL__ = 2: RxFIFO 1/2 full     */
/* __LEVEL__ = 3: Need 2 byte to full */
#define __UART_RxFIFO_THRESHOLD(__UART__, __LEVEL__)      do{ __UART__->FCR_Shadow &= ~0xC0;               \
                                                              __UART__->FCR_Shadow |= __LEVEL__ << FCR_RT; \
                                                              __UART__->UARTx->FCR_IID.FCR = __UART__->FCR_Shadow; }while(0)

/* __LEVEL__ = 0: TxFIFO empty       */
/* __LEVEL__ = 1: TxFIFO have 2 byte */
/* __LEVEL__ = 2: TxFIFO 1/4 full    */
/* __LEVEL__ = 3: TxFIFO 1/2 full    */
#define __UART_TxFIFO_THRESHOLD(__UART__, __LEVEL__)      do{ __UART__->FCR_Shadow &= ~0x30;                \
                                                              __UART__->FCR_Shadow |= __LEVEL__ << FCR_TET; \
                                                              __UART__->UARTx->FCR_IID.FCR = __UART__->FCR_Shadow; }while(0)

/* __UART_IS_RxFIFO_FULL  */
/* __UART_IS_RxFIFO_EMPTY */
/* __UART_IS_TxFIFO_FULL  */
/* __UART_IS_TxFIFO_EMPTY */
#define __UART_IS_RxFIFO_FULL(__UARTx__)               (__UARTx__->USR.RFF  == 1)
#define __UART_IS_RxFIFO_EMPTY(__UARTx__)              (__UARTx__->USR.RFNE == 0)
#define __UART_IS_TxFIFO_FULL(__UARTx__)               (__UARTx__->USR.TFNF == 0)
#define __UART_IS_TxFIFO_EMPTY(__UARTx__)              (__UARTx__->USR.TFE  == 1)

/* uart interrupt enable  */
/* uart interrupt disable */
/* uart interrupt get id  */
#define __UART_INT_MODEM_ENABLE(__UARTx__)                  (__UARTx__->IER_DLH.IER.EDSSI = 1)
#define __UART_INT_LINE_STATUS_ENABLE(__UARTx__)            (__UARTx__->IER_DLH.IER.ELSI  = 1)
#define __UART_INT_RX_ENABLE(__UARTx__)                     (__UARTx__->IER_DLH.IER.ERBFI = 1)
/* Tx empty interrupt and fifo enable */
#define __UART_INT_TXE_ENABLE_FE(__UARTx__)               do{__UARTx__->IER_DLH.IER.PTIME = 1; \
                                                             __UARTx__->IER_DLH.IER.ETBEI = 1;}while(0)
/* Tx empty interrupt and fifo disable */
#define __UART_INT_TXE_ENABLE_FD(__UARTx__)               do{__UARTx__->IER_DLH.IER.PTIME = 0; \
                                                             __UARTx__->IER_DLH.IER.ETBEI = 1;}while(0)

#define __UART_INT_MODEM_DISABLE(__UARTx__)                 (__UARTx__->IER_DLH.IER.EDSSI = 0)
#define __UART_INT_LINE_STATUS_DISABLE(__UARTx__)           (__UARTx__->IER_DLH.IER.ELSI  = 0)
#define __UART_INT_RX_DISABLE(__UARTx__)                    (__UARTx__->IER_DLH.IER.ERBFI = 0)
#define __UART_INT_TXE_DISABLE(__UARTx__)                 do{__UARTx__->IER_DLH.IER.PTIME = 0; \
                                                             __UARTx__->IER_DLH.IER.ETBEI = 0;}while(0)

/* Get interrupt ID */
#define __UART_INT_GET_ID(__UARTx__)                        (__UARTx__->FCR_IID.IID & 0xF)


/* __UART_IrDA_ENABLE */
#define __UART_IrDA_ENABLE(__UARTx__)                       (__UARTx__->MCR.SIRE = 1)
#define __UART_IrDA_DISABLE(__UARTx__)                      (__UARTx__->MCR.SIRE = 0)

/* flow control config */
#define __UART_AUTO_FLOW_CONTROL_ENABLE(__UARTx__)        do{__UARTx__->MCR.AFCE = 1; __UARTx__->MCR.RTS  = 1;} while(0)
#define __UART_AUTO_FLOW_CONTROL_DISABLE(__UARTx__)         (__UARTx__->MCR.AFCE = 0)
#define __UART_RTS_ACTIVE(__UARTx__)                        (__UARTx__->MCR.RTS  = 1)
#define __UART_RTS_INACTIVE(__UARTx__)                      (__UARTx__->MCR.RTS  = 0)
#define __UART_IS_CTS_ACTIVE(__UARTx__)                     (__UARTx__->MSR.CTS  == 1)

/* __UART_DLL_DLH_ACCESS_ENABLE */
/* __UART_DLL_DLH_ACCESS_DISABLE */
#define __UART_DLL_DLH_ACCESS_ENABLE(__UARTx__)             (__UARTx__->LCR.DLAB = 1)
#define __UART_DLL_DLH_ACCESS_DISABLE(__UARTx__)            (__UARTx__->LCR.DLAB = 0)

/* __UART_GET_STATUS */
#define __UART_GET_STATUS(__UARTx__)                        (__UARTx__->LSR.LSR_DWORD)


/* Exported functions --------------------------------------------------------*/

/* uart_IRQHandler */
void uart_IRQHandler(UART_HandleTypeDef *huart);

/* uart_init */
void uart_init_ex(UART_HandleTypeDef *huart);

/* uart_transmit */
/* uart_receive */
void uart_transmit(UART_HandleTypeDef *huart, uint8_t *fp_Data, uint32_t fu32_Size);
void uart_receive(UART_HandleTypeDef *huart, uint8_t *fp_Data, uint32_t fu32_Size);

/* uart_transmit_IT */
/* uart_receive_IT */
void uart_transmit_IT(UART_HandleTypeDef *huart, uint8_t *fp_Data, uint32_t fu32_Size);
void uart_receive_IT(UART_HandleTypeDef *huart, uint8_t *fp_Data, uint32_t fu32_Size);

/* uart_transmit_DMA */
/* uart_receive_DMA */
void uart_transmit_DMA(UART_HandleTypeDef *huart);
void uart_receive_DMA(UART_HandleTypeDef *huart);

/* uart_config_baudRate */
void uart_config_baudRate(UART_HandleTypeDef *huart);

#endif
