/*
  ******************************************************************************
  * @file    usb_core.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file for usb_core.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __USB_CORE_H__
#define __USB_CORE_H__

#include "fr30xx.h"

/* Control Register for USB */
#define USB_OTG_CTRL_CID         (0x800)
#define USB_OTG_CTRL_VBUS_CFG    (0x700)
#define USB_OTG_CTRL_ADP         (0x009)

#define USB_OTG_CTRL_DEVICE_CFG    (USB_OTG_CTRL_CID | USB_OTG_CTRL_VBUS_CFG | USB_OTG_CTRL_ADP)
#define USB_OTG_CTRL_HOST_CFG      (USB_OTG_CTRL_VBUS_CFG | USB_OTG_CTRL_ADP)

#define USB_OTG_CTRL_BASE    (0xE00501DC)

#define USB_OTG_CTRL        *(volatile uint32_t *)USB_OTG_CTRL_BASE

/** @addtogroup USB_Registers_Section
  * @{
  */
/* ################################ Register bit define Start ################################ */

/* Power in device */
#define USB_POWER_RESUME                 (0x04)
#define USB_POWER_EN_SUSPEND             (0x01)

/* Power in host */
#define USB_HOST_POWER_RESET             (0x08)
#define USB_HOST_POWER_RESUME            (0x04)
#define USB_HOST_POWER_SUSPEND           (0x02)

/* usb signal interrupt */
#define USB_INT_STATUS_VBUS_ERROR        (0x80)
#define USB_INT_STATUS_SESSREQ           (0x40)
#define USB_INT_STATUS_DISCON            (0x20)
#define USB_INT_STATUS_CONN              (0x10)
#define USB_INT_STATUS_SOF               (0x08)
#define USB_INT_STATUS_RESET             (0x04)
#define USB_INT_STATUS_RESUME            (0x02)
#define USB_INT_STATUS_SUSPEND           (0x01)

/* CSR01 in device */
#define USB_CSR01_SVCSETUPEND            (0x80)
#define USB_CSR01_SVCRXPKTRDY            (0x40)
#define USB_CSR01_SENDSTALL              (0x20)
#define USB_CSR01_SETUPEND               (0x10)
#define USB_CSR01_DATAEND                (0x08)
#define USB_CSR01_SENTSTALL              (0x04)
#define USB_CSR01_TXPKTRDY               (0x02)
#define USB_CSR01_RXPKTRDY               (0x01)
/* CSR01 in host */
#define USB_HOST_CSR01_NAK_TIMEOUT       (0x80)
#define USB_HOST_CSR01_STATUS_PKT        (0x40)
#define USB_HOST_CSR01_REQ_PKT           (0x20)
#define USB_HOST_CSR01_ERROR             (0x10)
#define USB_HOST_CSR01_SETUP_PKT         (0x08)
#define USB_HOST_CSR01_RXSTALL           (0x04)
#define USB_HOST_CSR01_TXPKTRDY          (0x02)
#define USB_HOST_CSR01_RXPKTRDY          (0x01)

/* TXCSR1 in device */
#define USB_TXCSR1_CLRDATATOG            (0x40)
#define USB_TXCSR1_SENTSTALL             (0x20)
#define USB_TXCSR1_SENDSTALL             (0x10)
#define USB_TXCSR1_FLUSHFIFO             (0x08)
#define USB_TXCSR1_UNDERRUN              (0x04)
#define USB_TXCSR1_FIFO_NOTEMPTY         (0x02)
#define USB_TXCSR1_TXPKTRDY              (0x01)

/* TXCSR1 in host */
#define USB_HOST_TXCSR1_NAK_TIMEOUT      (0x80)
#define USB_HOST_TXCSR1_CLRDATATOG       (0x40)
#define USB_HOST_TXCSR1_RXSTALL          (0x20)
#define USB_HOST_TXCSR1_FLUSHFIFO        (0x08)
#define USB_HOST_TXCSR1_ERROR            (0x04)
#define USB_HOST_TXCSR1_FIFO_NOTEMPTY    (0x02)
#define USB_HOST_TXCSR1_TXPKTRDY         (0x01)

#define USB_TXCSR2_AUTO_SET              (0x80)
#define USB_TXCSR2_ISO                   (0x40)
#define USB_TXCSR2_MODE                  (0x20)
#define USB_TXCSR2_DMA_ENABLE            (0x10)
#define USB_TXCSR2_FRC_DATA_TOG          (0x08)
#define USB_TXCSR2_DMA_MODE              (0x04)

/* RXCSR1 in device */
#define USB_RXCSR1_CLRDATATOG            (0x80)
#define USB_RXCSR1_SENTSTALL             (0x40)
#define USB_RXCSR1_SENDSTALL             (0x20)
#define USB_RXCSR1_FLUSHFIFO             (0x10)
#define USB_RXCSR1_DATAERROR             (0x08)
#define USB_RXCSR1_OVERRUN               (0x04)
#define USB_RXCSR1_FIFO_FULL             (0x02)
#define USB_RXCSR1_RXPKTRDY              (0x01)

/* RXCSR1 in host */
#define USB_HOST_RXCSR1_CLRDATATOG       (0x80)
#define USB_HOST_RXCSR1_RXSTALL          (0x40)
#define USB_HOST_RXCSR1_REQPKT           (0x20)
#define USB_HOST_RXCSR1_FLUSHFIFO        (0x10)
#define USB_HOST_RXCSR1_NAK_TIMEOUT      (0x08)
#define USB_HOST_RXCSR1_ERROR            (0x04)
#define USB_HOST_RXCSR1_FIFO_FULL        (0x02)
#define USB_HOST_RXCSR1_RXPKTRDY         (0x01)

#define USB_RXCSR2_AUTO_CLEAR            (0x80)
#define USB_RXCSR2_DEVICE_ISO            (0x40)
#define USB_RXCSR2_HOST_AUTO_REQ         (0x40)
#define USB_RXCSR2_DMA_ENABLE            (0x20)
#define USB_RXCSR2_DMA_MODE              (0x10)

#define USB_HOST_TXTYPE_PROTOCOL_POS            (0x04)
#define USB_HOST_TXTYPE_PROTOCOL_MSK            (0x30)
#define USB_HOST_TXTYPE_TARGET_ENDP_NUM_POS     (0x00)
#define USB_HOST_TXTYPE_TARGET_ENDP_NUM_MSK     (0x0F)

#define USB_HOST_RXTYPE_PROTOCOL_POS            (0x04)
#define USB_HOST_RXTYPE_PROTOCOL_MSK            (0x30)
#define USB_HOST_RXTYPE_TARGET_ENDP_NUM_POS     (0x00)
#define USB_HOST_RXTYPE_TARGET_ENDP_NUM_MSK     (0x0F)

/* ################################ Register bit define END ################################ */
/**
  * @}
  */
  
typedef enum
{
    ENDPOINT_0,
    ENDPOINT_1,
    ENDPOINT_2,
    ENDPOINT_3,
    ENDPOINT_4,
    ENDPOINT_5,
    ENDPOINT_6,
    ENDPOINT_7,
}enum_Endpoint_t;

typedef enum
{
    HOST_ENDP_TYPE_NONE,
    HOST_ENDP_TYPE_ISO,
    HOST_ENDP_TYPE_BULK,
    HOST_ENDP_TYPE_INT,
}enum_HostEndpointType_t;

/** @addtogroup USB_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* -------------------------------------------*/
/*            Common USB registers            */
/* -------------------------------------------*/
typedef struct 
{
    volatile uint8_t FAddr;         // offset 0x00
    volatile uint8_t Power;         // offset 0x01
    volatile uint8_t IntrTx1;       // offset 0x02
    volatile uint8_t IntrTx2;       // offset 0x03
    volatile uint8_t IntrRx1;       // offset 0x04
    volatile uint8_t IntrRx2;       // offset 0x05
    volatile uint8_t IntrUSB;       // offset 0x06
    volatile uint8_t IntrTx1E;      // offset 0x07
    volatile uint8_t IntrTx2E;      // offset 0x08
    volatile uint8_t IntrRx1E;      // offset 0x09
    volatile uint8_t IntrRx2E;      // offset 0x0A
    volatile uint8_t IntrUSBE;      // offset 0x0B
    volatile uint8_t Frame1;        // offset 0x0C
    volatile uint8_t Frame2;        // offset 0x0D
    volatile uint8_t Index;         // offset 0x0E
    volatile uint8_t DevCtl;        // offset 0x0F
    volatile uint8_t rsv_0[80];     // offset 0x10~0x5F    
    volatile uint8_t SetRxTog1;     // offset 0x60
    volatile uint8_t rsv_1;         // offset 0x61 
    volatile uint8_t SetTxTog1;     // offset 0x62
    volatile uint8_t rsv_2;         // offset 0x63 
    volatile uint8_t GetRxTog1;     // offset 0x64
    volatile uint8_t rsv_3;         // offset 0x65      
    volatile uint8_t GetTxTog1;     // offset 0x66
    volatile uint8_t rsv_4;         // offset 0x67         
}usb_common_t;                                                          

/* ------------------------------------------------*/
/*      Control Status registers for endpoint0     */
/* ------------------------------------------------*/
typedef struct 
{
    volatile uint8_t rsv_0;         // offset 0x10
    volatile uint8_t CSR01;         // offset 0x11
    volatile uint8_t CSR02;         // offset 0x12
    volatile uint8_t rsv_1[3];      // offset 0x13 ~ 0x15
    volatile uint8_t Count0;        // offset 0x16
    volatile uint8_t rsv_2[2];      // offset 0x17 ~ 0x18
    volatile uint8_t NAKLimit0;     // offset 0x19
    volatile uint8_t rsv_3[6];      // offset 0x1A ~ 0x1F
    volatile uint8_t FIFO;          // offset 0x20
}usb_endpoint0_t;

/* -----------------------------------------------------*/
/*      Control Status registers for endpoint1 ~ 10     */
/* -----------------------------------------------------*/
typedef struct 
{
    volatile uint8_t TxMaxP;         // offset 0x10
    volatile uint8_t TxCSR1;         // offset 0x11
    volatile uint8_t TxCSR2;         // offset 0x12
    volatile uint8_t RxMaxP;         // offset 0x13
    volatile uint8_t RxCSR1;         // offset 0x14
    volatile uint8_t RxCSR2;         // offset 0x15
    volatile uint8_t RxCount1;       // offset 0x16
    volatile uint8_t RxCount2;       // offset 0x17
    volatile uint8_t TxType;         // offset 0x18 (Used in HostMode)
    volatile uint8_t TxInterval;     // offset 0x19 (Used in HostMode)
    volatile uint8_t RxType;         // offset 0x1A (Used in HostMode)
    volatile uint8_t RxInterval;     // offset 0x1B (Used in HostMode)
    volatile uint8_t TxFIFO1;        // offset 0x1C
    volatile uint8_t TxFIFO2;        // offset 0x1D
    volatile uint8_t RxFIFO1;        // offset 0x1E
    volatile uint8_t RxFIFO2;        // offset 0x1F
    volatile uint8_t FIFO[44];       // offset 0x20
}usb_endpoints_t;

#define USB_OTG_ENDPOINT_BASE    (0x10010010)   /* USB_OTG_BASE + 0x10 */

#define USB           ((volatile usb_common_t *)USB_OTG_BASE)
#define USB_POINT0    ((volatile usb_endpoint0_t *)USB_OTG_ENDPOINT_BASE)
#define USB_POINTS    ((volatile usb_endpoints_t *)USB_OTG_ENDPOINT_BASE)

/* ################################ Register Section END ################################ */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/* usb_device_init */
void usb_device_init(void);
void usb_host_init(void);

/* usb_selecet_endpoint */
void usb_selecet_endpoint(enum_Endpoint_t Endpoint);

/* usb_get_endpoint */
uint8_t usb_get_endpoint(void);

/* usb_set_address */
void usb_set_address(uint8_t address);

/* usb_get_frame */
uint32_t usb_get_frame(void);

/* usb_RxSyncEndpoint_enable */
/* usb_TxSyncEndpoint_enable */
void usb_RxSyncEndpoint_enable(void);
void usb_TxSyncEndpoint_enable(void);

/* usb_SingleInt_Enable */
/* usb_SingleInt_Disable */
void usb_SingleInt_Enable(uint8_t fu8_Signal);
void usb_SingleInt_Disable(uint8_t fu8_Signal);

/* usb_TxInt_Enable/usb_TxInt_Disable */
/* usb_RxInt_Enable/usb_RxInt_Disable */
void usb_TxInt_Enable(enum_Endpoint_t Endpoint);
void usb_TxInt_Disable(enum_Endpoint_t Endpoint);
void usb_RxInt_Enable(enum_Endpoint_t Endpoint);
void usb_RxInt_Disable(enum_Endpoint_t Endpoint);

/* usb_endpoint_Txfifo_config */
/* usb_endpoint_Rxfifo_config */
void usb_endpoint_Txfifo_config(uint32_t StartAddress, uint32_t MaxPacket);
void usb_endpoint_Rxfifo_config(uint32_t StartAddress, uint32_t MaxPacket);

/* usb_TxMaxP_set */
/* usb_RxMaxP_set */
void usb_TxMaxP_set(uint32_t MaxPacket);
void usb_RxMaxP_set(uint32_t MaxPacket);

/* usb_Host_TxEndpointType */
/* usb_Host_RxEndpointType */
void usb_Host_TxEndpointType(enum_HostEndpointType_t fe_Type);
void usb_Host_RxEndpointType(enum_HostEndpointType_t fe_Type);
/* usb_Host_TxTargetEndpoint */
/* usb_Host_RxTargetEndpoint */
void usb_Host_TxTargetEndpoint(uint8_t fu8_TargetEndpointNum);
void usb_Host_RxTargetEndpoint(uint8_t fu8_TargetEndpointNum);
/* usb_Host_TxPollingInterval */
/* usb_Host_RxPollingInterval */
/* usb_Host_TxNAKLimit */
/* usb_Host_RxNAKLimit */
void usb_Host_TxPollingInterval(uint8_t fu8_TxInterval);
void usb_Host_TxNAKLimit(uint8_t fu8_TxNAKLimit);
void usb_Host_RxPollingInterval(uint8_t fu8_RxInterval);
void usb_Host_RxNAKLimit(uint8_t fu8_RxNAKLimit);

/* usb_write_fifo */
/* usb_read_fifo  */
void usb_write_fifo(enum_Endpoint_t Endpoint, uint8_t *Buffer, uint32_t Size);
void usb_read_fifo(enum_Endpoint_t Endpoint, uint8_t *Buffer, uint32_t Size);

/* Exported inline functions --------------------------------------------------------*/

/* usb_get_USBStatus */
static inline uint8_t usb_get_USBStatus(void)
{
    return USB->IntrUSB;
}

/* usb_get_TxStatus */
/* usb_get_RxStatus */
static inline uint8_t usb_get_TxStatus(void)
{
    return USB->IntrTx1;
}
static inline uint8_t usb_get_RxStatus(void)
{
    return USB->IntrRx1;
}

/* ------------------------------------ */
/* ---------- Pwoer function ---------- */
/* ------------------------------------ */ 

/* ---------- Device ---------- */
static inline void usb_ResumeSignalStart(void)
{
    /* Device generate Resume signaling on the bus. */
    USB->Power |= USB_POWER_RESUME;
}
static inline void usb_ResumeSignalStop(void)
{
    USB->Power &= ~USB_POWER_RESUME;
}

static inline void usb_SuspendDetectEn(void)
{
    /* Device Detec Suspend signal on the bus. */
    USB->Power |= USB_POWER_EN_SUSPEND;
}

/* ---------- Host ---------- */
/* usb_Host_ResetSignalStart  */
/* usb_Host_ResetSignalStop   */
/* usb_Host_ResumeSignalStart */
/* usb_Host_ResumeSignalStop  */
/* usb_Host_EntrySuspendMode  */
/* usb_Host_ExitSuspendMode   */
static inline void usb_Host_ResetSignalStart(void)
{
    /*  Host generate Reset signaling on the bus. */
    USB->Power |= USB_HOST_POWER_RESET;
}
static inline void usb_Host_ResetSignalStop(void)
{
    USB->Power &= ~USB_HOST_POWER_RESET;
}

static inline void usb_Host_ResumeSignalStart(void)
{
    /* Host generate Resume signaling on the bus. */
    USB->Power |= USB_HOST_POWER_RESUME;
}
static inline void usb_Host_ResumeSignalStop(void)
{
    USB->Power &= ~USB_HOST_POWER_RESUME;
}

static inline void usb_Host_EntrySuspendMode(void)
{
    USB->Power |= USB_HOST_POWER_SUSPEND;
}
static inline void usb_Host_ExitSuspendMode(void)
{
    USB->Power &= ~USB_HOST_POWER_SUSPEND;
}

/* ---------------------------------------- */
/* ---------- Endpoint0 function ---------- */
/* ---------------------------------------- */ 
/* usb_get_Endpoint0_RxCount   */
/* usb_get_Endpoint0_FlushFIFO */
static inline uint8_t usb_Endpoint0_get_RxCount(void)
{
    return USB_POINT0->Count0;
}

static inline void usb_Endpoint0_FlushFIFO(void)
{
    USB_POINT0->CSR02 = 1;
}

/* ---------- Device ---------- */
/* usb_Endpoint0_SendStall    */
/* usb_Endpoint0_DataEnd      */
/* usb_Endpoint0_SET_TxPktRdy */
/* usb_Endpoint0_GET_TxPktRdy */
/* usb_Endpoint0_GET_RxPktRdy */
static inline void usb_Endpoint0_SendStall(void)
{
    USB_POINT0->CSR01 |= USB_CSR01_SENDSTALL;
}

static inline void usb_Endpoint0_DataEnd(void)
{
    USB_POINT0->CSR01 |= USB_CSR01_DATAEND;
}

static inline void usb_Endpoint0_SET_TxPktRdy(void)
{
    USB_POINT0->CSR01 |= USB_CSR01_TXPKTRDY;
}

static inline bool usb_Endpoint0_GET_TxPktRdy(void)
{
    return (USB_POINT0->CSR01 & USB_CSR01_TXPKTRDY) ? true : false;
}

static inline bool usb_Endpoint0_GET_RxPktRdy(void)
{
    return (USB_POINT0->CSR01 & USB_CSR01_RXPKTRDY) ? true : false;
}

/* ---------- Host ---------- */
/* usb_Host_Endpoint0_SET_ReqPkt             */
/* usb_Host_Endpoint0_SET_ReqPkt_StatusPkt   */
/* usb_Host_Endpoint0_SET_TxPktRdy           */
/* usb_Host_Endpoint0_SET_TxPktRdy_StatusPkt */
/* usb_Host_Endpoint0_SET_TxPktRdy_SetupPkt  */
/* usb_Host_Endpoint0_Clr_SetupPkt           */
/* usb_Host_Endpoint0_Clr_StatusPkt          */
/* usb_Host_Endpoint0_Clr_ReqPkt             */
/* usb_Host_Endpoint0_GET_TxPktRdy           */
/* usb_Host_Endpoint0_GET_RxPktRdy           */
/* usb_Host_Endpoint0_GET_NAKtimeout         */
/* usb_Host_Endpoint0_Clr_NAKtimeout         */
/* usb_Host_Endpoint0_GET_ERROR              */
/* usb_Host_Endpoint0_NAKlimit               */
static inline void usb_Host_Endpoint0_SET_ReqPkt(void)
{
    USB_POINT0->CSR01 |= USB_HOST_CSR01_REQ_PKT;
}
static inline void usb_Host_Endpoint0_SET_ReqPkt_StatusPkt(void)
{
    USB_POINT0->CSR01 |= (USB_HOST_CSR01_REQ_PKT | USB_HOST_CSR01_STATUS_PKT);
}

static inline void usb_Host_Endpoint0_SET_TxPktRdy(void)
{
    USB_POINT0->CSR01 |= USB_HOST_CSR01_TXPKTRDY;
}
static inline void usb_Host_Endpoint0_SET_TxPktRdy_SetupPkt(void)
{
    USB_POINT0->CSR01 |= (USB_HOST_CSR01_TXPKTRDY | USB_HOST_CSR01_SETUP_PKT);
}
static inline void usb_Host_Endpoint0_SET_TxPktRdy_StatusPkt(void)
{
    USB_POINT0->CSR01 |= (USB_HOST_CSR01_TXPKTRDY | USB_HOST_CSR01_STATUS_PKT);
}

static inline void usb_Host_Endpoint0_Clr_SetupPkt(void)
{
    USB_POINT0->CSR01 &= ~USB_HOST_CSR01_SETUP_PKT;
}
static inline void usb_Host_Endpoint0_Clr_StatusPkt(void)
{
    USB_POINT0->CSR01 &= ~USB_HOST_CSR01_STATUS_PKT;
}
static inline void usb_Host_Endpoint0_Clr_ReqPkt(void)
{
    USB_POINT0->CSR01 &= ~USB_HOST_CSR01_REQ_PKT;
}

static inline bool usb_Host_Endpoint0_GET_TxPktRdy(void)
{
    return (USB_POINT0->CSR01 & USB_HOST_CSR01_TXPKTRDY) ? true : false;
}

static inline bool usb_Host_Endpoint0_GET_RxPktRdy(void)
{
    return (USB_POINT0->CSR01 & USB_HOST_CSR01_RXPKTRDY) ? true : false;
}

static inline bool usb_Host_Endpoint0_GET_NAKtimeout(void)
{
    return (USB_POINT0->CSR01 & USB_HOST_CSR01_NAK_TIMEOUT) ? true : false;
}
static inline void usb_Host_Endpoint0_Clr_NAKtimeout(void)
{
    USB_POINT0->CSR01 &= ~USB_HOST_CSR01_NAK_TIMEOUT;
}

static inline bool usb_Host_Endpoint0_GET_ERROR(void)
{
    return (USB_POINT0->CSR01 & USB_HOST_CSR01_ERROR) ? true : false;
}

static inline void usb_Host_Endpoint0_Clr_ERROR(void)
{
    USB_POINT0->CSR01 &= ~USB_HOST_CSR01_ERROR;
}

static inline void usb_Host_Endpoint0_NAKlimit(uint8_t fu8_NAKlimit)
{
    USB_POINT0->NAKLimit0 = fu8_NAKlimit;
}

/* ---------------------------------------- */
/* ------- other Endpoints function ------- */
/* ---------------------------------------- */ 

/* usb_Endpoints_get_RxCount  */
static inline uint8_t usb_Endpoints_get_RxCount(void)
{
    return USB_POINTS->RxCount1;
}
/* usb_Endpoints_get_RxCount_16bit  */
static inline uint16_t usb_Endpoints_get_RxCount_16bit(void)
{
    return (uint16_t)USB_POINTS->RxCount2 << 8 | (uint16_t)USB_POINTS->RxCount1;
}

/* ---------- Device ---------- */
/* usb_Endpoints_GET_RxPktRdy */
/* usb_Endpoints_SET_TxPktRdy */
/* usb_Endpoints_GET_TxPktRdy */
/* usb_Endpoints_FlushRxFIFO  */
/* usb_Endpoints_FlushTxFIFO  */

static inline bool usb_Endpoints_GET_RxPktRdy(void)
{
    return (USB_POINTS->RxCSR1 & USB_RXCSR1_RXPKTRDY) ? true : false;
}

static inline void usb_Endpoints_SET_TxPktRdy(void)
{
    USB_POINTS->TxCSR1 |= USB_TXCSR1_TXPKTRDY;
}

static inline bool usb_Endpoints_GET_TxPktRdy(void)
{
    return (USB_POINTS->TxCSR1 & USB_TXCSR1_TXPKTRDY) ? true : false;
}

static inline void usb_Endpoints_FlushRxFIFO(void)
{
    USB_POINTS->RxCSR1 |= USB_RXCSR1_FLUSHFIFO;
}

static inline void usb_Endpoints_FlushTxFIFO(void)
{
    USB_POINTS->TxCSR1 |= USB_TXCSR1_FLUSHFIFO;
}

/* ---------- Host ---------- */
/* usb_Host_Endpoints_SET_RxReqPkt */
/* usb_Host_Endpoints_Clr_RxReqPkt */
/* usb_Host_Endpoints_GET_RxPktRdy */
/* usb_Host_Endpoints_SET_TxPktRdy */
/* usb_Host_Endpoints_GET_TxPktRdy */
/* usb_Host_Endpoints_FlushRxFIFO */
/* usb_Host_Endpoints_FlushTxFIFO */
/* usb_Host_Endpoints_GET_Tx_NAKtimeout */
/* usb_Host_Endpoints_Clr_Tx_NAKtimeout */
/* usb_Host_Endpoints_GET_Tx_STALL */
/* usb_Host_Endpoints_Clr_Tx_STALL */
/* usb_Host_Endpoints_GET_Tx_ERROR */
/* usb_Host_Endpoints_Clr_Tx_ERROR */
/* usb_Host_Endpoints_GET_Rx_NAKtimeout */
/* usb_Host_Endpoints_Clr_Rx_NAKtimeout */
/* usb_Host_Endpoints_GET_Rx_STALL */
/* usb_Host_Endpoints_Clr_Rx_STALL */
/* usb_Host_Endpoints_GET_Rx_ERROR */
/* usb_Host_Endpoints_Clr_Rx_ERROR */
static inline void usb_Host_Endpoints_SET_RxReqPkt(void)
{
    USB_POINTS->RxCSR1 |= USB_HOST_RXCSR1_REQPKT;
}
static inline void usb_Host_Endpoints_Clr_RxReqPkt(void)
{
    USB_POINTS->RxCSR1 &= ~USB_HOST_RXCSR1_REQPKT;
}

static inline bool usb_Host_Endpoints_GET_RxPktRdy(void)
{
    return (USB_POINTS->RxCSR1 & USB_HOST_RXCSR1_RXPKTRDY) ? true : false;
}

static inline void usb_Host_Endpoints_SET_TxPktRdy(void)
{
    USB_POINTS->TxCSR1 |= USB_HOST_TXCSR1_TXPKTRDY;
}

static inline bool usb_Host_Endpoints_GET_TxPktRdy(void)
{
    return (USB_POINTS->TxCSR1 & USB_HOST_TXCSR1_TXPKTRDY) ? true : false;
}

static inline void usb_Host_Endpoints_FlushRxFIFO(void)
{
    USB_POINTS->RxCSR1 |= USB_HOST_RXCSR1_FLUSHFIFO;
}

static inline void usb_Host_Endpoints_FlushTxFIFO(void)
{
    USB_POINTS->TxCSR1 |= USB_HOST_TXCSR1_FLUSHFIFO;
}

static inline bool usb_Host_Endpoints_GET_Tx_NAKtimeout(void)
{
    return (USB_POINTS->TxCSR1 & USB_HOST_TXCSR1_NAK_TIMEOUT) ? true : false;
}
static inline void usb_Host_Endpoints_Clr_Tx_NAKtimeout(void)
{
    USB_POINTS->TxCSR1 &= ~USB_HOST_TXCSR1_NAK_TIMEOUT;
}

static inline bool usb_Host_Endpoints_GET_Tx_STALL(void)
{
    return (USB_POINTS->TxCSR1 & USB_HOST_TXCSR1_RXSTALL) ? true : false;
}
static inline void usb_Host_Endpoints_Clr_Tx_STALL(void)
{
    USB_POINTS->TxCSR1 &= ~USB_HOST_TXCSR1_RXSTALL;
}

static inline bool usb_Host_Endpoints_GET_Tx_ERROR(void)
{
    return (USB_POINTS->TxCSR1 & USB_HOST_TXCSR1_ERROR) ? true : false;
}
static inline void usb_Host_Endpoints_Clr_Tx_ERROR(void)
{
    USB_POINTS->TxCSR1 &= ~USB_HOST_TXCSR1_ERROR;
}

static inline bool usb_Host_Endpoints_GET_Rx_NAKtimeout(void)
{
    return (USB_POINTS->RxCSR1 & USB_HOST_RXCSR1_NAK_TIMEOUT) ? true : false;
}
static inline void usb_Host_Endpoints_Clr_Rx_NAKtimeout(void)
{
    USB_POINTS->RxCSR1 &= ~USB_HOST_RXCSR1_NAK_TIMEOUT;
}

static inline bool usb_Host_Endpoints_GET_Rx_STALL(void)
{
    return (USB_POINTS->RxCSR1 & USB_HOST_RXCSR1_RXSTALL) ? true : false;
}
static inline void usb_Host_Endpoints_Clr_Rx_STALL(void)
{
    USB_POINTS->RxCSR1 &= ~USB_HOST_RXCSR1_RXSTALL;
}

static inline bool usb_Host_Endpoints_GET_Rx_ERROR(void)
{
    return (USB_POINTS->RxCSR1 & USB_HOST_RXCSR1_ERROR) ? true : false;
}
static inline void usb_Host_Endpoints_Clr_Rx_ERROR(void)
{
    USB_POINTS->RxCSR1 &= ~USB_HOST_RXCSR1_ERROR;
}

/* ------------------------------------ */
/* ----------- MISC function ---------- */
/* ------------------------------------ */ 
static inline void usb_Set_Rx_Tog(uint8_t value)
{
    USB->SetRxTog1 = value;
}

static inline void usb_Set_Tx_Tog(uint8_t value)
{
    USB->SetTxTog1 = value;
}

static inline uint8_t usb_Get_Rx_Tog(void)
{
    return USB->GetRxTog1;
}

static inline uint8_t usb_Get_Tx_Tog(void)
{
    return USB->GetTxTog1;
}

#endif

/* ======================================================================================================= */
/* =============================== USB driver version management ========================================= */
/* ======================================================================================================= */

/*
   Driver name          Version          Data             Description
   -------------------------------------------------------------------------------------------------------
   usb_core             1.0.0            2024/1/9         First edition      
   -------------------------------------------------------------------------------------------------------
   usb_host             1.0.0            2024/1/9         First edition
   -------------------------------------------------------------------------------------------------------     
   usb_dev              1.0.0            2024/1/9         First edition
   ------------------------------------------------------------------------------------------------------- 
   usbh_mass_storage    1.0.0            2024/1/9         First edition     
   -------------------------------------------------------------------------------------------------------   
   usb_mass_storage     1.0.0            2024/1/9         First edition
   -------------------------------------------------------------------------------------------------------      
   usb_audio            1.0.0            2024/1/9         First edition
   -------------------------------------------------------------------------------------------------------
   usb_cdc              1.0.0            2024/1/9         First edition
   -------------------------------------------------------------------------------------------------------
   usb_hid              1.0.0            2024/1/9         First edition
   -------------------------------------------------------------------------------------------------------
   usb_winusb           1.0.0            2024/1/9         First edition
   -------------------------------------------------------------------------------------------------------
   usb_wireless         1.0.0            2024/1/9         First edition
*/
