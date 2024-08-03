/*
  ******************************************************************************
  * @file    driver_can.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of CAN HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_CAN_H__
#define __DRIVER_CAN_H__

#include "fr30xx.h"

/** @addtogroup CAN miscellaneous config
  * @{
  */
/* ################################ Misc Section Start ################################ */

/*
 * rx dedicated buffer nums
 *
 * The default number is 64. (unmodifiable)
 */
#define CAN_RX_DEDICATED_BUFFER_NUMS    (64)    /* Fixed 64 */


/*
 * Global Filter Config
 *
 * Unmatched standard ID handling selection.
 * 1: reject
 * 2: accept and store to fifo0
 * 3: accept and store to fifo1
 * 
 * Unmatched extended ID handling selection.
 * 1: reject
 * 2: accept and store to fifo0
 * 3: accept and store to fifo1
 */
#define CAN_UNMATCHED_STANDARD_ID_HANDLING    (1)    // 1: reject
#define CAN_UNMATCHED_EXTENDED_ID_HANDLING    (1)    // 1: reject


/*
 * Rx FIFO0/FIFO1 mode selection
 *
 * 1: blocking mode.
 * 2: overwrite mode.
 */
#define CAN_RX_FIFO0_MODE_SELECTION    (1)    // 1: blocking mode.
#define CAN_RX_FIFO1_MODE_SELECTION    (1)    // 1: blocking mode.


/*
 * Rx FIFO0/FIFO1 almost full threshold
 *
 * 0: almost full disable.
 * 1 ~ 64: almost full level.
 */
#define CAN_RX_FIFO0_ALMOST_FULL_THRESHOLD    (0)    // 0: disable.
#define CAN_RX_FIFO1_ALMOST_FULL_THRESHOLD    (0)    // 0: disable.


/*
 * Tx event function 
 *
 *  Uncomment to used Tx event function 
 */
// #define CAN_TX_EVENT_FUNCTION_EXIST

#ifdef CAN_TX_EVENT_FUNCTION_EXIST
    #define CAN_TX_EVENT_ALMOST_FULL_THRESHOLD    (0)    // 0: disable.
#endif


/*
 * Tx FIFO/Queue mode 
 *
 * Tx operation mode selection
 * 
 * 1: Tx FIFO operation
 * 2: Tx Queue operation
 */
#define CAN_TX_OPERATION_MODE_SELECTION    (2)



/* ################################ Misc Section END ################################## */
/**
  * @}
  */



/** @addtogroup CAN_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Data Bit Timing Prescaler Register */
typedef struct
{
    uint32_t  DSJW   : 4;    /* Data (Re)Synchronization Jump Width   */
    uint32_t  DTSEG2 : 4;    /* Data time segment after sample point  */
    uint32_t  DTSEG1 : 5;    /* Data time segment before sample point */
    uint32_t  rsv_0  : 3;
    uint32_t  DBRP   : 5;    /* Data Bit Rate Prescaler */
    uint32_t  rsv_1  : 2;
    uint32_t  TDC    : 1;    /* Transmitter Delay Compensation */
    uint32_t  rsv_2  : 8;
}REG_Timing_t;

/* Test Register */
typedef struct
{
    uint32_t  rsv_0    : 4;
    uint32_t  LBCK     : 1;    /* Loop Back Mode */
    uint32_t  TX       : 2;
    uint32_t  RX       : 1;
    uint32_t  MEM_STOP : 1;
    uint32_t  rsv_1    : 23;
}REG_Tset_t;

/* RAM Watchdog Register */
typedef struct
{
    uint32_t  WDC   : 8;    /* Watchdog Configuration */
    uint32_t  WDV   : 8;    /* Watchdog Value */
    uint32_t  rsv_0 : 16;
}REG_RAMWatchdog_t;

/* CC Control Register */
typedef struct
{
    uint32_t  INIT  : 1;    /* Initialization */
    uint32_t  CCE   : 1;    /* Configuration Change */
    uint32_t  ASM   : 1;    /* Restricted Operation Mode */
    uint32_t  CSA   : 1;    /* Clock Stop Acknowledge */
    uint32_t  CSR   : 1;    /* Clock Stop Request */
    uint32_t  MON   : 1;    /* Bus Monitoring Mode */
    uint32_t  DAR   : 1;    /* Automatic Retransmission */
    uint32_t  TEST  : 1;    /* Test Mode */
    uint32_t  FDOE  : 1;    /* FD Operation Enable */
    uint32_t  BRSE  : 1;    /* Bit Rate Switch Enable */
    uint32_t  rsv_1 : 2;    
    uint32_t  PXHD  : 1;    /* Protocol Exception Handling Disable */
    uint32_t  EFBI  : 1;    /* Edge Filtering during Bus Integration */
    uint32_t  TXP   : 1;    /* Transmit Pause */
    uint32_t  NISO  : 1;    /* CAN FD ISO Operation */
    uint32_t  rsv_2 : 16;   
}REG_CCCtrl_t;

/* Nominal Bit Timing Prescaler Register */
typedef struct
{
    uint32_t  NTSEG2 : 7;    /* Nominal Time segment after sample point */
    uint32_t  rsv_0  : 1;
    uint32_t  NTSEG1 : 8;    /* Nominal Time segment before sample point */
    uint32_t  NBRP   : 9;    /* Nominal Bit Rate Prescaler */
    uint32_t  NSJW   : 7;    /* Nominal (Re)Synchronization Jump Width */
}REG_NominalTiming_t;

/* Timestamp Counter Configuration */
typedef struct
{
    uint32_t  TSS   : 2;    /* Timestamp Select */
    uint32_t  rsv_0 : 14;
    uint32_t  TCP   : 8;    /* Timestamp Counter Prescaler */
    uint32_t  rsv_1 : 8;
}REG_TimestampConfig_t;

/* Timestamp Counter Configuration */
typedef struct
{
    uint32_t  ETOC  : 1;    /* Enable Timeout Counter */
    uint32_t  TOS   : 2;    /* Timeout Select */
    uint32_t  rsv_0 : 13;
    uint32_t  TOP   : 16;   /* Timeout Period */
}REG_TimeoutConfig_t;

/* Timestamp Counter Configuration */
typedef struct
{
    uint32_t  TEC   : 8;    /* Transmit Error Counter */
    uint32_t  REC   : 7;    /* Receive Error Counter */
    uint32_t  RP    : 1;    /* Receive Error Passive */
    uint32_t  CEL   : 8;    /* CAN Error Logging */
    uint32_t  rsv_0 : 8;
}REG_ErrorCounter_t;

/* Protocol Status */
typedef union
{
    volatile uint32_t BusProtocolStatus;
    struct
    {
        uint32_t  LEC    : 3;
        uint32_t  ACT    : 2;
        uint32_t  EP     : 1;
        uint32_t  EW     : 1;
        uint32_t  BO     : 1;
        uint32_t  DLEC   : 3;
        uint32_t  RESI   : 1;
        uint32_t  RBRS   : 1;
        uint32_t  RFDF   : 1;
        uint32_t  PXE    : 1;
        uint32_t  rsv_0  : 1;
        uint32_t  TDCV   : 7;
        uint32_t  rsv_1  : 9;
    } Bits;
}REG_ProtocolStatus_t;

/* Transmitter Delay Compensation */
typedef struct
{
    uint32_t  TDCF  : 7;    /* Transmitter Delay Compensation Filter Window Length */
    uint32_t  rsv_0 : 1;
    uint32_t  TDCO  : 7;    /* Transmitter Delay Compensation Offset */
    uint32_t  rsv_1 : 17;
}REG_TxDelayCompensation_t;

/* Global Filter Configuration */
typedef struct
{
    uint32_t  RRFE  : 1;    /* Reject Remote Frames Extended */
    uint32_t  RRFS  : 1;    /* Reject Remote Frames Standard */
    uint32_t  ANFE  : 2;    /* Accept Non-matching Frames Extended */
    uint32_t  ANFS  : 2;    /* Accept Non-matching Frames Standard */
    uint32_t  rsv_0 : 26;
}REG_GlobalFilterCfg_t;

/* Standard ID Filter Configuration */
typedef struct
{
    uint32_t  FLSSA : 16;    /* Filter List Standard Start Address */
    uint32_t  LSS   : 8;     /* List Size Standard */
    uint32_t  rsv_0 : 8;
}REG_StandardIDFilterCfg_t;

/* Extended ID Filter Configuration */
typedef struct
{
    uint32_t  FLESA : 16;    /* Filter List Extended Start Address */
    uint32_t  LSE   : 8;     /* List Size Extended */
    uint32_t  rsv_0 : 8;
}REG_ExtendedIDFilterCfg_t;

/* High Priority Message Status */
typedef struct
{
    uint32_t  BIDX  : 6;    /* Buffer Index */
    uint32_t  MSI   : 2;    /* Message Storage Indicator */
    uint32_t  FIDX  : 7;    /* Filter Index */
    uint32_t  FLST  : 1;    /* Filter List */
    uint32_t  rsv_0 : 16;
}REG_HighPriorityMSGStatus_t;

/* Rx FIFO Configuration */
typedef struct
{
    uint32_t  FxSA  : 16;    /* Rx FIFO 0/1 Start Address */
    uint32_t  FxS   : 7;     /* Number of Rx FIFO 0/1 elements */
    uint32_t  rsv_0 : 1; 
    uint32_t  FxWM  : 7;     /* Rx FIFO 0/1 Watermark */
    uint32_t  FxOM  : 1;     /* FIFO 0/1 Operation Mode */
}REG_RxFIFOConfig_t;

/* Rx FIFO 0/1 Status */
typedef struct
{
    uint32_t  FxFL  : 7;    /* Rx FIFO 0/1 Fill Level */
    uint32_t  rsv_0 : 1;
    uint32_t  FxGI  : 6;    /* Rx FIFO 0/1 Get Index */
    uint32_t  rsv_1 : 2;
    uint32_t  F0PI  : 6;    /* Rx FIFO 0/1 Put Index */
    uint32_t  rsv_2 : 2;
    uint32_t  FxF   : 1;    /* Rx FIFO 0/1 Full */
    uint32_t  RFxL  : 1;    /* Rx FIFO 0/1 Message Lost */
    uint32_t  rsv_3 : 6;
}REG_RxFIFOStatus_t;

/* Tx Buffer Configuration */
typedef struct
{
    uint32_t  TBSA  : 16;    /* Tx Buffers Start Address */
    uint32_t  NDTB  : 6;     /* Number of Dedicated Transmit Buffers */
    uint32_t  rsv_0 : 2; 
    uint32_t  TFQS  : 6;     /* Transmit FIFO/Queue Size */
    uint32_t  TFQM  : 1;     /* Tx FIFO/Queue Mode */
    uint32_t  rsv_1 : 1;
}REG_TxBufferConfig_t;

/* Rx Buffer / FIFO Element Size Configuration */
typedef struct
{
    uint32_t  F0DS  : 3;    /* Rx FIFO 0 Data Field Size */
    uint32_t  rsv_0 : 1;
    uint32_t  F1DS  : 3;    /* Rx FIFO 1 Data Field Size */
    uint32_t  rsv_1 : 1;
    uint32_t  RBDS  : 3;    /* Rx Buffer Data Field Size */
    uint32_t  rsv_2 : 21;
}REG_RxBufferElementCfg_t;

/* Tx FIFO/Queue Status */
typedef struct
{
    uint32_t  TFFL  : 6;    /* Tx FIFO Free Level */
    uint32_t  rsv_0 : 2;
    uint32_t  TFGI  : 5;    /* Tx FIFO Get Index */
    uint32_t  rsv_1 : 3;
    uint32_t  TFQPI : 5;    /* Tx FIFO/Queue Put Index */
    uint32_t  TFQF  : 1;    /* Tx FIFO/Queue Full */
    uint32_t  rsv_2 : 10;
}REG_TxQueueStatus_t;

/* Tx Event FIFO Configuration */
typedef struct
{
    uint32_t  EFSA  : 16;    /* Event FIFO Start Address */
    uint32_t  EFS   : 6;     /* Event FIFO Size */
    uint32_t  rsv_0 : 2; 
    uint32_t  EFWM  : 6;     /* Event FIFO Watermark */
    uint32_t  rsv_1 : 2;
}REG_TxEventFIFOConfig_t;

/* Tx FIFO/Queue Status */
typedef struct
{
    uint32_t  EFFL  : 6;    /* Event FIFO Fill Level */
    uint32_t  rsv_0 : 2;    
    uint32_t  EFGI  : 5;    /* Event FIFO Get Index */
    uint32_t  rsv_1 : 3;
    uint32_t  EFPI  : 5;    /* Event FIFO Put Index */
    uint32_t  rsv_2 : 3;
    uint32_t  EFF   : 1;    /* Event FIFO Full */
    uint32_t  TEFL  : 1;    /* Tx Event FIFO Element Lost */
    uint32_t  rsv_3 : 6;
}REG_TxEventFIFOStatus_t;

/* -------------------------------------------------*/
/*                   CAN Register                   */
/* -------------------------------------------------*/
typedef struct 
{
    volatile uint32_t                  CoreRelease;                /* Offset 0x00 */
    volatile uint32_t                  Endian;                     /* Offset 0x04 */
    volatile uint32_t                  Customer;                   /* Offset 0x08 */
    volatile REG_Timing_t              DataTiming;                 /* Offset 0x0C */
    volatile REG_Tset_t                Test;                       /* Offset 0x10 */
    volatile REG_RAMWatchdog_t         RAMWatchdog;                /* Offset 0x14 */
    volatile REG_CCCtrl_t              CCCtrl;                     /* Offset 0x18 */
    volatile REG_NominalTiming_t       NominalTiming;              /* Offset 0x1C */
    volatile REG_TimestampConfig_t     TimestampConfig;            /* Offset 0x20 */
    volatile uint32_t                  TimestampCounter;           /* Offset 0x24 */
    volatile REG_TimeoutConfig_t       TimeoutConfig;              /* Offset 0x28 */
    volatile uint32_t                  TimeoutCounter;             /* Offset 0x2C */
    volatile uint32_t                  rsv_0[4];
    volatile REG_ErrorCounter_t        ErrorCounter;               /* Offset 0x40 */
    volatile REG_ProtocolStatus_t      ProtocolStatus;             /* Offset 0x44 */
    volatile REG_TxDelayCompensation_t TxDelayCompensation;        /* Offset 0x48 */
    volatile uint32_t                  rsv_1;
    volatile uint32_t                  IntStatus;                  /* Offset 0x50 */
    volatile uint32_t                  IntEnable;                  /* Offset 0x54 */
    volatile uint32_t                  IntLineSelect;              /* Offset 0x58 */
    volatile uint32_t                  IntLineEnbale;              /* Offset 0x5C */
    volatile uint32_t                  rsv_2[8];
    volatile REG_GlobalFilterCfg_t     GlobalFilterCfg;            /* Offset 0x80 */
    volatile REG_StandardIDFilterCfg_t StandardIDFilterCfg;        /* Offset 0x84 */
    volatile REG_ExtendedIDFilterCfg_t ExtendedIDFilterCfg;        /* Offset 0x88 */
    volatile uint32_t                  rsv_3;
    volatile uint32_t                  ExtendedIDMask;             /* Offset 0x90 */
    volatile uint32_t                  HighPriorityMSGStatus;      /* Offset 0x94 */
    volatile uint32_t                  NewData1;                   /* Offset 0x98 */
    volatile uint32_t                  NewData2;                   /* Offset 0x9C */
    volatile REG_RxFIFOConfig_t        RxFIFO0Config;              /* Offset 0xA0 */
    volatile REG_RxFIFOStatus_t        RxFIFO0Status;              /* Offset 0xA4 */
    volatile uint32_t                  RxFIFO0Ack;                 /* Offset 0xA8 */
    volatile uint32_t                  RxBufferConfig;             /* Offset 0xAC */
    volatile REG_RxFIFOConfig_t        RxFIFO1Config;              /* Offset 0xB0 */
    volatile REG_RxFIFOStatus_t        RxFIFO1Status;              /* Offset 0xB4 */
    volatile uint32_t                  RxFIFO1Ack;                 /* Offset 0xB8 */
    volatile REG_RxBufferElementCfg_t  RxBufferElementCfg;         /* Offset 0xBC */
    volatile REG_TxBufferConfig_t      TxBufferConfig;             /* Offset 0xC0 */
    volatile REG_TxQueueStatus_t       TxQueueStatus;              /* Offset 0xC4 */
    volatile uint32_t                  TxBufferElementCfg;         /* Offset 0xC8 */
    volatile uint32_t                  TxBufferReqPending;         /* Offset 0xCC */
    volatile uint32_t                  TxBufferAddReq;             /* Offset 0xD0 */
    volatile uint32_t                  TxBufferCancellationReq;    /* Offset 0xD4 */
    volatile uint32_t                  TxOccurred;                 /* Offset 0xD8 */
    volatile uint32_t                  TxBufferCancellationEnd;    /* Offset 0xDC */
    volatile uint32_t                  TxOccurredIntEn;            /* Offset 0xE0 */
    volatile uint32_t                  TxCancellationEndIntEn;     /* Offset 0xE4 */
    volatile uint32_t                  rsv_4[2];
    volatile REG_TxEventFIFOConfig_t   TxEventFIFOConfig;          /* Offset 0xF0 */
    volatile REG_TxEventFIFOStatus_t   TxEventFIFOStatus;          /* Offset 0xF4 */
    volatile uint32_t                  TxEventFIFOAck;             /* Offset 0xF8 */ 
    volatile uint32_t                  rsv_5;
    volatile uint32_t                  MessageRamAddr;             /* Offset 0x100 */
}struct_CAN_t; 

#define CAN0    ((struct_CAN_t *)CAN0_BASE)
#define CAN1    ((struct_CAN_t *)CAN1_BASE)
#define CAN2    ((struct_CAN_t *)CAN2_BASE)
#define CAN3    ((struct_CAN_t *)CAN3_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */



/** @addtogroup CAN_Message_Ram_Section
  * @{
  */
/* ############################## Message Ram Section Start ############################### */

/* Standard Message ID Filter Element */
typedef struct 
{
    volatile uint32_t SFID2 : 11;
    volatile uint32_t rsv_0 : 5;
    volatile uint32_t SFID1 : 11;
    volatile uint32_t SFEC  : 3;
    volatile uint32_t SFT   : 2;
}struct_StdFilterElement_t;

/* extended Message ID Filter Element */
typedef struct 
{
    volatile uint32_t EFID1 : 29;
    volatile uint32_t EFEC  : 3;
    volatile uint32_t EFID2 : 29;
    volatile uint32_t rsv_0 : 1;
    volatile uint32_t EFT   : 2;
}struct_ExtFilterElement_t;


/* Tx Frame Config */
typedef struct 
{
    uint32_t ID    : 29;    /* Identifier */
    uint32_t RTR   : 1;     /* Remote Transmission Request */
    uint32_t XTD   : 1;     /* Extended Identifier */
    uint32_t ESI   : 1;     /* Error State Indicator (Used in CAN_FD) */
    uint32_t rsv_0 : 16;
    uint32_t DLC   : 4;     /* Data Length Code */
    uint32_t BRS   : 1;     /* Bit Rat Switching (Used in CAN_FD) */
    uint32_t FDF   : 1;     /* FD Format (Used in CAN_FD) */
    uint32_t rsv_1 : 1;
    uint32_t EFC   : 1;     /* Event FIFO Control */
    uint32_t MM    : 8;     /* Message Marker */
}struct_TxFrameConfig_t;

/* CAN Tx Buffer Element */
typedef struct 
{
    volatile struct_TxFrameConfig_t FrameCFG;
    volatile uint8_t  Data[];
}struct_CanTxElement_t;


/* Rx Frame Config */
typedef struct 
{
    uint32_t ID    : 29;    /* Identifier */
    uint32_t RTR   : 1;     /* Remote Transmission Request */
    uint32_t XTD   : 1;     /* Extended Identifier */
    uint32_t ESI   : 1;     /* Error State Indicator */
    uint32_t RXTS  : 16;    /* Rx Timestamp */
    uint32_t DLC   : 4;     /* Data Length Code */
    uint32_t BRS   : 1;     /* Bit Rate Switch */
    uint32_t FDF   : 1;     /* FD Format */
    uint32_t rsv_0 : 2;
    uint32_t FIDX  : 7;     /* Filter Index */
    uint32_t ANMF  : 1;     /* Accepted Non-matching Frame */
}struct_RxFrameConfig_t;

/* CAN Rx Buffer Element */
typedef struct 
{
    volatile struct_RxFrameConfig_t FrameCFG;
    volatile uint8_t  Data[];
}struct_CanRxElement_t;

/* #################################### Message Ram Section END ######################################### */
/**
  * @}
  */



/** @addtogroup CAN_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

/* error code */
#define CAN_ERR_TXFIFO_FULL                          (-1)
#define CAN_ERR_TXBUFFER_IN_USE                      (-2)
#define CAN_ERR_STANDARD_ID_FILTER_NUMS_OVERFLOW     (-3)
#define CAN_ERR_EXTENDEN_ID_FILTER_NUMS_OVERFLOW     (-4)
#define CAN_ERR_TXBUFFER_NUMS_OVERFLOW               (-5)
#define CAN_ERR_RX_FIFO0_NUMS_OVERFLOW               (-6)
#define CAN_ERR_RX_FIFO1_NUMS_OVERFLOW               (-7)
#define CAN_ERR_DATA_BUFFER_OVERSIZE                 (-8)

/* interrupt status mask */
typedef enum
{
    INT_CAN_NO_ERR = 0,
    
    INT_RxFIFO0_NEW_MESSAGE                = 0x00000001,
    INT_RxFIFO0_WATERMARK_REACHED          = 0x00000002,
    INT_RxFIFO0_FULL                       = 0x00000004,
    INT_RxFIFO0_MESSAGE_LOST               = 0x00000008,
    INT_RxFIFO1_NEW_MESSAGE                = 0x00000010,
    INT_RxFIFO1_WATERMARK_REACHED          = 0x00000020,
    INT_RxFIFO1_FULL                       = 0x00000040,
    INT_RxFIFO1_MESSAGE_LOST               = 0x00000080,
    INT_HIGH_PRIORITY_MESSAGE              = 0x00000100,
    INT_TRANSMISSION_COMPLETED             = 0x00000200,
    INT_TRANSMISSION_CANCELLATION_FINISHED = 0x00000400,
    INT_TxFIFO_EMPTY                       = 0x00000800,
    INT_TxEVENT_NEW_ENTRY                  = 0x00001000,
    INT_TxEVENT_WATERMARK_REACHED          = 0x00002000,
    INT_TxEVENT_FULL                       = 0x00004000,
    INT_TxEVENT_ELEMENT_LOST               = 0x00008000,
    INT_TIMESTAMP_WRAPAROUND               = 0x00010000,
    INT_MESSAGE_RAM_ACCESS_FAILURE         = 0x00020000,
    INT_TIMEOUT_OCCURRED                   = 0x00040000,
    INT_MESSAGE_STORED_TO_RX_BUFFER        = 0x00080000,
    INT_BIT_ERROR_CORRECTED                = 0x00100000,
    INT_BIT_ERROR_UNCORRECTED              = 0x00200000,
    INT_ERROR_LOG_OVERFLOW                 = 0x00400000,
    INT_ERROR_PASSIVE                      = 0x00800000,
    INT_WARNING_STATUS                     = 0x01000000,
    INT_BUS_OFF_STATUS                     = 0x02000000,
    INT_WATCHDOG_INTERRUPT                 = 0x04000000,
    INT_PROTOCOL_ERROR                     = 0x08000000,
    INT_PROTOCOL_ERROR_FD                  = 0x10000000,
    INT_ACCESS_RESERVED_ADDRESS            = 0x20000000,
}enum_CAN_INT_Status_t;

/* CAN interrupt line */
typedef enum
{
    CAN_INT_LINE0,
    CAN_INT_LINE1,
}enum_CAN_INT_LINEx_t;

/* CAN frame mode */
typedef enum
{
    CAN_CLASSICAL_FRAME,
    CAN_FD_FRAME,
}enum_CAN_FrameMode_t;

/* CAN frame mode */
typedef enum
{
    CAN_FD_DLC9_DATA_LENGTH_12BYTE  = 9,
    CAN_FD_DLC10_DATA_LENGTH_16BYTE = 10,
    CAN_FD_DLC11_DATA_LENGTH_20BYTE = 11,
    CAN_FD_DLC12_DATA_LENGTH_24BYTE = 12,
    CAN_FD_DLC13_DATA_LENGTH_32BYTE = 13,
    CAN_FD_DLC14_DATA_LENGTH_48BYTE = 14,
    CAN_FD_DLC15_DATA_LENGTH_64BYTE = 15,
}enum_CAN_FD_DLC_t;

/* CAN function enable/disable */
typedef enum
{
    CAN_FUNC_DISABLE,
    CAN_FUNC_ENABLE,
}enum_CAN_FUNC_t;

/* CAN Identifier Type */
typedef enum
{
    CAN_ID_STANDARD,
    CAN_ID_EXTENDED,
}enum_IdType_t;

/* CAN frame Type */
typedef enum
{
    CAN_DATA_FRAME,
    CAN_REMOTE_FRAM,
}enum_FrameType_t;

/* CAN FD mode Data buffer size */
typedef enum
{
    CAN_DATA_BUFFER_SIZE_8_BYTE,
    CAN_DATA_BUFFER_SIZE_12_BYTE,
    CAN_DATA_BUFFER_SIZE_16_BYTE,
    CAN_DATA_BUFFER_SIZE_20_BYTE,
    CAN_DATA_BUFFER_SIZE_24_BYTE,
    CAN_DATA_BUFFER_SIZE_32_BYTE,
    CAN_DATA_BUFFER_SIZE_48_BYTE,
    CAN_DATA_BUFFER_SIZE_64_BYTE,
}enum_CAN_DataSize_t;

/* CAN Filter Type */
typedef enum
{
    CAN_FILTER_RANGE_FILTER      = 0,    /* Range filter from SFID1 to SFID2 (SFID2 ¡Ý SFID1) */
    CAN_FILTER_SINGLE_ID_FILTER  = 1,    /* Single ID filter */
    CAN_FILTER_DUAL_ID_FILTER    = 1,    /* Dual ID filter   */
    CAN_FILTER_CLASSIC_FILTER    = 2,    /* filter and mask */

    CAN_FILTER_DISABLE = 3,
}enum_CAN_FilterType_t;

/* CAN Filter Process Mode */
typedef enum
{
    FILTER_PROCESS_DISABLE,
    
    FILTER_PROCESS_STORE_IN_RxFIFO0,
    FILTER_PROCESS_STORE_IN_RxFIFO1,
    FILTER_PROCESS_REJECT,
    FILTER_PROCESS_SET_PRIORITY,
    FILTER_PROCESS_SET_PRIORITY_AND_STORE_IN_RxFIFO0,
    FILTER_PROCESS_SET_PRIORITY_AND_STORE_IN_RxFIFO1,
    FILTER_PROCESS_STORE_IN_RxBUFFER,
}enum_CAN_FilterProcessMode_t;

/* CAN interrupt line */
typedef enum
{
   CAN_INTERNAL_LOOP_BACK_TEST_MODE,
   CAN_EXTERNAL_LOOP_BACK_TEST_MODE,
}enum_CAN_TestMode_t;

/* CAN timeout select */
typedef enum
{
   CAN_CONTINUOUS_OPERATION,
   CAN_TIMEOUT_CONTROLLED_BY_TX_EVENT_FIFO,
   CAN_TIMEOUT_CONTROLLED_BY_RX_FIFO_0,
   CAN_TIMEOUT_CONTROLLED_BY_RX_FIFO_1,
}enum_CAN_Timeout_select_t;

/**
  * @brief  CAN init structure definition
  */
typedef struct
{
    /* -------------------------------------------- */
    /* IN class CAN mode, Nominal Bit Timing config */
    /* -------------------------------------------- */
    uint32_t Prescaler;                  /*!< Specifies the Bit Rate Prescaler.
                                              This parameter must be a number between Min_Data = 1 and Max_Data = 256. */
                                              
    uint32_t SyncJumpWidth;              /*!< Specifies the Synchronization Jump Width.
                                              This parameter can be a number between Min_Data = 0 and Max_Data = 127. */
                                              
    uint32_t TimeSeg1;                   /*!< Specifies the number of time quanta in Bit Segment 1.
                                              This parameter can be a number between Min_Data = 0 and Max_Data = 255. */
                                              
    uint32_t TimeSeg2;                   /*!< Specifies the number of time quanta in Bit Segment 2.
                                              This parameter can be a number between Min_Data = 0 and Max_Data = 127. */

    /* -------------------------------------------- */
    /* IN CAN FD mode, Data Bit Timing config       */
    /* -------------------------------------------- */
    uint32_t DataBit_RateSwitch;         /*!< Specifies the Data Bit Rate Switch enabel/disable.
                                              This parameter can be set to CAN_FUNC_ENABLE or CAN_FUNC_DISABLE. */

    /* if set DataBit_RateSwitch = CAN_FUNC_DISABLE, The following parameters do not need to be configured   */

    uint32_t DataBit_Prescaler;          /*!< Specifies the Data Bit Rate Prescaler.
                                              This parameter must be a number between Min_Data = 1 and Max_Data = 32. */

    uint32_t DataBit_SyncJumpWidth;      /*!< Specifies the Data Bit Synchronization Jump Width.
                                              This parameter can be a number between Min_Data = 0 and Max_Data = 15. */
                                              
    uint32_t DataBit_TimeSeg1;           /*!< Specifies the Data Bit number of time quanta in Bit Segment 1.
                                              This parameter can be a number between Min_Data = 0 and Max_Data = 31. */
                                              
    uint32_t DataBit_TimeSeg2;           /*!< Specifies the Data Bit number of time quanta in Bit Segment 2.
                                              This parameter can be a number between Min_Data = 0 and Max_Data = 15. */
}struct_CANInit_t;

/**
  * @brief  Message RAM cnonfig structure definition
  */
typedef struct
{
    uint32_t StartAddress;               /*!< Specifies the message ram address. */

    uint32_t StandardIDFilterNums;       /*!< Specifies the number of standard message ID filter element.
                                              This parameter must be a number 0 ~ 128. */

    uint32_t ExtendedIDFilterNums;       /*!< Specifies the number of extended message ID filter element.
                                              This parameter must be a number 0 ~ 64. */

    uint32_t TxFIFOQueueNums;            /*!< Specifies the number of Tx fifo/queue element.
                                              This parameter must be a number 0 ~ 32. */
    uint32_t TxDedicatedBufferNums;      /*!< Specifies the number of Tx dedicated buffer element.
                                              This parameter must be a number 0 ~ 32. */

                                         /* The tx buffer has four combination modes :
                                            1. only use tx fifo. 
                                            2. only use tx queue. 
                                            3. mixed tx dedicated buffers / Tx fifo.
                                            4. mixed tx dedicated buffers / Tx queue. */
                                         /* attention: the sum of TxFIFOQueueNums and TxDedicatedBufferNums 
                                            cannot be greater than 32. */

    uint32_t RxFIFO0Nums;                /*!< Specifies the number of Rx FIFO0 element.
                                              This parameter must be a number 0 ~ 64. */
    uint32_t RxFIFO1Nums;                /*!< Specifies the number of Rx FIFO1 element.
                                              This parameter must be a number 0 ~ 64. */
#ifdef CAN_TX_EVENT_FUNCTION_EXIST
    uint32_t TxEventNums;                /*!< Specifies the number of Tx Event element.
                                              This parameter must be a number 0 ~ 32. */
#endif
    uint32_t DataBufferSize;             /*!< Specifies the CAN data buffer size.
                                              This parameter can be a value of @ref enum_CAN_DataSize_t.
                                              Note: Only use classic mode, the buffer defaults set 8 Byte. */
}struct_RAMConfig_t;

/**
  * @brief Classics CAN Tx message header structure definition
  */
typedef struct
{
    uint32_t  IdType;           /*!< Specifies the type of identifier for the message.
                                     This parameter can be a value of @ref enum_IdType_t */

    uint32_t  Identifier;       /*!< Specifies the standard identifier or extended identifier.
                                     Use standard identifier this parameter must be a value between Min_Data = 0 and Max_Data = 0x7FF.
                                     Use extended identifier this parameter must be a value between Min_Data = 0 and Max_Data = 0x1FFFFFFF. */

    uint8_t   FrameType;        /*!< Specifies the type of frame for the message.
                                     This parameter can be a value of @ref enum_FrameType_t */

    uint8_t   FormatMode;       /*!< Specifies the mode of frame for the message. 
                                     CAN_CLASSICAL_FRAME = Frame transmitted in Classic CAN format.
                                     CAN_FD_FRAME        = Frame transmitted in CAN FD format. */

    uint8_t   DLC;              /*!< Specifies the length of data for the message.
                                     0 ~ 8  = CAN + CAN FD: transmit frame has 0-8 data bytes. 
                                     9 ~ 15 = CAN: transmit frame has 8 data bytes.
                                     9 ~ 15 = CAN FD: transmit frame has 12/16/20/24/32/48/64 data bytes. */
    
    uint8_t   BitRateSwitch;    /*!< Bit Rate Switch enable/disable. BitRateSwitch = 1 or BitRateSwitch = 0*/
}struct_CANTxHeaderDef_t;

/**
  * @brief CAN Rx message header structure definition
  */
typedef struct
{
    uint32_t  IdType;           /*!< Specifies the type of identifier for the message.
                                     This parameter can be a value of @ref enum_IdType_t */

    uint32_t  Identifier;       /*!< Specifies the standard identifier or extended identifier.
                                     Use standard identifier this parameter must be a value between 0 ~ 0x7FF.
                                     Use extended identifier this parameter must be a value between 0 ~ 0x1FFFFFFF. */

    uint8_t   FrameType;        /*!< Specifies the type of frame for the message.
                                     This parameter can be a value of @ref enum_FrameType_t */

    uint8_t   FormatMode;       /*!< Specifies the mode of frame for the message. 
                                     CAN_CLASSICAL_FRAME = Frame transmitted in Classic CAN format.
                                     CAN_FD_FRAME        = Frame transmitted in CAN FD format. */
    
    uint8_t   DLC;              /*!< Specifies the length of data for the message.
                                     This parameter must be a number between Min_Data = 0 and Max_Data = 8. */

    uint8_t   BitRateSwitch;    /*!< Bit Rate Switch enable/disable. BitRateSwitch = 1 or BitRateSwitch = 0*/
    
    uint16_t  Timestamp;        /*!< Specifies the timestamp counter value captured on start of frame reception.
                                     This parameter must be a number between  0 ~ 0xFFFF. */

    uint8_t   FilterMatchIndex; /*!< Specifies the index of matching acceptance filter element.
                                     matching standard identifier this parameter must be a value 0 ~ 127.
                                     matching extended identifier this parameter must be a value 0 ~ 63. */
}struct_CANRxHeaderDef_t;

/**
  * @brief filter config
  */
typedef struct
{
    uint32_t FilterType;       /*!< Specifies the type of filter mode.
                                    This parameter can be a value of @ref enum_CAN_FilterType_t */
    
    uint32_t ProcessMode;      /*!< Specifies the type of filter process mode.
                                    This parameter can be a value of @ref enum_CAN_FilterProcessMode_t */
    
    uint32_t FilterID_1;       /* Specifies the Filter ID 1 */
    uint32_t FilterID_2;       /* Specifies the Filter ID 2 
                                  Use standard identifier this parameter must be a value between 0x000 ~ 0x7FF.
                                  Use extended identifier this parameter must be a value between 0x000 ~ 0x1FFFFFFF.
                                  Note: if FilterType select STD_FILTER_SINGLE_FILTER, user must set StdFilterID_1 = StdFilterID_2 */

    uint32_t RxBufferIndex;    /* Specifies the index of RxBuffer, if ProcessMode select FILTER_PROCESS_STORE_IN_RxBUFFER.
                                  this parameter must be a value between Min_Data = 0 and Max_Data = 63 */
}struct_FilterCfg_t;

/*
 * @brief  CAN handle Structure definition
 */
typedef struct __CAN_HandleTypeDef
{
    struct_CAN_t           *CANx;              /*!< CAN registers base address     */

    struct_CANInit_t        Init;              /*!< CAN communication parameters   */

    struct_RAMConfig_t      RAMConfig;         /*!< CAN message RAM cnonfig        */

    void (*RxFIFO0_New_Message_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*RxFIFO0_Watermark_Reached_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*RxFIFO0_Full_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*RxFIFO0_Message_Lost_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*RxFIFO1_New_Message_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*RxFIFO1_Watermark_Reached_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*RxFIFO1_Full_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*RxFIFO1_Message_Lost_Callback)(struct __CAN_HandleTypeDef *hcan);

    void (*Receive_High_Priority_Message_Callback)(struct __CAN_HandleTypeDef *hcan);

    void (*Transmission_Completed_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Transmission_Cancellation_Finished_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*TxFIFO_Empty_Callback)(struct __CAN_HandleTypeDef *hcan);

#ifdef CAN_TX_EVENT_FUNCTION_EXIST
    void (*TxEventFIFO_New_Entry_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*TxEventFIFO_Watermark_Reached_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*TxEventFIFO_Full_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*TxEventFIFO_Lost_Callback)(struct __CAN_HandleTypeDef *hcan);
#endif

    void (*Message_Ram_Access_Failure_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Timeout_Occurred_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Message_Stored_To_RxBuffer_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Bit_Error_Corrected_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Bit_Error_Uncorrected_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Error_Log_Overflow_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Error_Passive_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Warning_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Bus_Off_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*RAM_WDT_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Protocol_Error_Callback)(struct __CAN_HandleTypeDef *hcan);
    void (*Protocol_Error_FD_Callback)(struct __CAN_HandleTypeDef *hcan);

    uint32_t                ElementSize;       /*!< Tx/Rx FIFO element size */
    
    uint32_t                RxBufferUsed_L;    /*!< Rx Buffer used status, Low  32 */
    uint32_t                RxBufferUsed_H;    /*!< Rx Buffer used status, High 32 */
}CAN_HandleTypeDef;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

#define __CAN_SET_MESSAGE_RAM_START_ADDR(__CANx__, __ADDR__)            (__CANx__->MessageRamAddr = __ADDR__)
#define __CAN_GET_MESSAGE_RAM_START_ADDR(__CANx__)                      (__CANx__->MessageRamAddr)

/* get core release versions */
#define __CAN_GET_CORE_RELEASE_VERSION(__CANx__)                        (__CANx__->CoreRelease)
/* Endianness Test Value 0x87654321 */
#define __CAN_GET_ENDIAN(__CANx__)                                      (__CANx__->Endian)
/* write/read customer register */
#define __CAN_WRITE_CUSTOMER_REGISTER(__CANx__, __DATA__)               (__CANx__->Customer = __DATA__)
#define __CAN_READ_CUSTOMER_REGISTER(__CANx__)                          (__CANx__->Customer)

/* ----------------------*/
/*      Data Timing      */
/* ----------------------*/
/* Transmitter Delay Compensation enabled */
/* Transmitter Delay Compensation disabled */
#define __CAN_TRANSMITTER_DELAY_COMPENSATION_ENABLE(__CANx__)              (__CANx__->DataTiming.TDC = 1)
#define __CAN_TRANSMITTER_DELAY_COMPENSATION_DISABLE(__CANx__)             (__CANx__->DataTiming.TDC = 0)

/* Set Data Rate Prescaler */
/* Set Data PhaseSeg1 */
/* Set Data PhaseSeg2 */
/* Set Data Synchronization width */
#define __CAN_SET_DATA_BIT_RATE_PRESCALER(__CANx__, __PRESCALER__)         (__CANx__->DataTiming.DBRP   = __PRESCALER__ - 1)
#define __CAN_SET_DATA_BIT_TIME_SEG_1(__CANx__, __VALUE__)                 (__CANx__->DataTiming.DTSEG1 = __VALUE__)
#define __CAN_SET_DATA_BIT_TIME_SEG_2(__CANx__, __VALUE__)                 (__CANx__->DataTiming.DTSEG2 = __VALUE__)
#define __CAN_SET_DATA_BIT_SYNC_WIDTH(__CANx__, __VALUE__)                 (__CANx__->DataTiming.DSJW   = __VALUE__)

/* ----------------------*/
/*         Test          */
/* ----------------------*/
#define __CAN_TEST_MODE_LOOP_BACK_MODE_ENABLE(__CANx__)                    (__CANx__->Test.LBCK = 1)
#define __CAN_TEST_MODE_LOOP_BACK_MODE_DISABLE(__CANx__)                   (__CANx__->Test.LBCK = 0)
#define __CAN_TEST_MODE_SET_TX_DOMINANT(__CANx__)                          (__CANx__->Test.TX = 2)
#define __CAN_TEST_MODE_SET_TX_RECESSIVE(__CANx__)                         (__CANx__->Test.TX = 3)
#define __CAN_TEST_MODE_GET_RX_STATUS(__CANx__)                            (__CANx__->Test.RX)

/* ----------------------*/
/*      RAM Watchdog     */
/* ----------------------*/
#define __CAM_SET_RAM_WATCHDOG_INITIAL_VALUE(__CANx__, __VALUE__)          (__CANx__->RAMWatchdog.WDC = __VALUE__)
#define __CAM_GET_RAM_WATCHDOG_VALUE(__CANx__)                             (__CANx__->RAMWatchdog.WDV)

/* ----------------------*/
/*       CC Control      */
/* ----------------------*/
/* Initialization Start/Stop */
/* Configuration Change Enable/Disable */
#define __CAN_INIT_START(__CANx__)                                         (__CANx__->CCCtrl.INIT = 1)
#define __CAN_INIT_STOP(__CANx__)                                          (__CANx__->CCCtrl.INIT = 0)
#define __CAN_CHANGE_ENABLE(__CANx__)                                      (__CANx__->CCCtrl.CCE = 1)
#define __CAN_CHANGE_DISABLE(__CANx__)                                     (__CANx__->CCCtrl.CCE = 0)
/* Restricted Operation Mode Enable/Disable */
#define __CAN_RESTRICTED_OPERATION_ENABLE(__CANx__)                        (__CANx__->CCCtrl.ASM = 1)
#define __CAN_RESTRICTED_OPERATION_DISABLE(__CANx__)                       (__CANx__->CCCtrl.ASM = 0)
/* Get clock stop status */
/* Set clock stop request */
#define __CAN_GET_CLK_STOP_STATUS(__CANx__)                                (__CANx__->CCCtrl.CSA)
#define __CAN_SET_CLK_STOP_REQUEST(__CANx__)                               (__CANx__->CCCtrl.CSR = 1)
/* Bus Monitoring Mode Enable/Disable */
#define __CAN_BUS_MONITOR_MODE_ENABLE(__CANx__)                            (__CANx__->CCCtrl.MON = 1)
#define __CAN_BUS_MONITOR_MODE_DISABLE(__CANx__)                           (__CANx__->CCCtrl.MON = 0)
/* Automatic Retransmission Enable/Disable */
#define __CAN_AUTOMATIC_RETRANSMISSION_ENABLE(__CANx__)                    (__CANx__->CCCtrl.DAR = 0)
#define __CAN_AUTOMATIC_RETRANSMISSION_DISABLE(__CANx__)                   (__CANx__->CCCtrl.DAR = 1)
/* Test mode enable/disable */
#define __CAN_TEST_MODE_ENABLE(__CANx__)                                   (__CANx__->CCCtrl.TEST = 1)
#define __CAN_TEST_MODE_DISABLE(__CANx__)                                  (__CANx__->CCCtrl.TEST = 0)
/* classics CAN/CAN_FD */
#define __CAN_FD_MODE_DISABLE(__CANx__)                                    (__CANx__->CCCtrl.FDOE = 0)
#define __CAN_FD_MODE_ENABLE(__CANx__)                                     (__CANx__->CCCtrl.FDOE = 1)
/* data bit rate switch enable/disable */
#define __CAN_BIT_RATE_SWITCH_ENABLE(__CANx__)                             (__CANx__->CCCtrl.BRSE = 1)
#define __CAN_BIT_RATE_SWITCH_DISABLE(__CANx__)                            (__CANx__->CCCtrl.BRSE = 0)
/* protocol exception handling enable/disable */
#define __CAN_PROTOCOL_EXCEPTION_HANDLING_ENABLE(__CANx__)                 (__CANx__->CCCtrl.PXHD = 1)
#define __CAN_PROTOCOL_EXCEPTION_HANDLING_DISABLE(__CANx__)                (__CANx__->CCCtrl.PXHD = 0)
/* Edge Filtering during Bus Integration */
#define __CAN_EDGE_FILTER_ENABLE(__CANx__)                                 (__CANx__->CCCtrl.EFBI = 1)
#define __CAN_EDGE_FILTER_DISABLE(__CANx__)                                (__CANx__->CCCtrl.EFBI = 0)
/* Transmit Pause */
#define __CAN_TRANSMIT_PAUSE_ENABLE(__CANx__)                              (__CANx__->CCCtrl.TXP = 1)
#define __CAN_TRANSMIT_PAUSE_DISABLE(__CANx__)                             (__CANx__->CCCtrl.TXP = 0)
/* CAN FD frame format */
#define __CAN_FD_FRAME_FORMAT_ISO11898_1(__CANx__)                         (__CANx__->CCCtrl.NISO = 0)
#define __CAN_FD_FRAME_FORMAT_BOSCH_CAN_FD_SPECV1(__CANx__)                (__CANx__->CCCtrl.NISO = 1)

/* ----------------------*/
/*         Timing        */
/* ----------------------*/
/* Set Nominal Rate Prescaler */
/* Set Nominal PhaseSeg1 */
/* Set Nominal PhaseSeg2 */
/* Set Nominal Synchronization width */
#define __CAN_SET_NOMINAL_RATE_PRESCALER(__CANx__, __PRESCALER__)             (__CANx__->NominalTiming.NBRP   = __PRESCALER__ - 1)
#define __CAN_SET_NOMINAL_TIME_SEG_1(__CANx__, __VALUE__)                     (__CANx__->NominalTiming.NTSEG1 = __VALUE__)
#define __CAN_SET_NOMINAL_TIME_SEG_2(__CANx__, __VALUE__)                     (__CANx__->NominalTiming.NTSEG2 = __VALUE__)
#define __CAN_SET_NOMINAL_SYNC_WIDTH(__CANx__, __VALUE__)                     (__CANx__->NominalTiming.NSJW   = __VALUE__)

/* ----------------------*/
/*       Timestamp       */
/* ----------------------*/
/* Set Timestamp select */
/* Set Timestamp prescaler */
/* Get Timestamp Counter */
#define __CAN_SET_TIMESTAMP_SELECT_BYPASS(__CANx__)                        (__CANx__->TimestampConfig.TSS = 0)
#define __CAN_SET_TIMESTAMP_SELECT_INTERNAL(__CANx__)                      (__CANx__->TimestampConfig.TSS = 1)
#define __CAN_SET_TIMESTAMP_SELECT_EXTERNAL(__CANx__)                      (__CANx__->TimestampConfig.TSS = 2)
#define __CAN_SET_TIMESTAMP_PRESCALER(__CANx__, __PRESCALER__)             (__CANx__->TimestampConfig.TCP = __PRESCALER__ - 1)
#define __CAN_SET_TIMESTAMP(__CANx__)                                      (__CANx__->TimestampCounter = 0)
#define __CAN_GET_TIMESTAMP(__CANx__)                                      (__CANx__->TimestampCounter)

/* ----------------------*/
/*    Timeout Counter    */
/* ----------------------*/
/* Timeout Counter enable/disable */
/* Timeout Counter mode select */
/* Timeout Counter get value */
#define __CAN_TIMEOUT_COUNTER_ENABLE(__CANx__)                             (__CANx__->TimeoutConfig.ETOC = 1)
#define __CAN_TIMEOUT_COUNTER_DISABLE(__CANx__)                            (__CANx__->TimeoutConfig.ETOC = 0)
#define __CAN_TIMEOUT_COUNTER_MODE_CONTINUOUS(__CANx__)                    (__CANx__->TimeoutConfig.TOS = 0)
#define __CAN_TIMEOUT_COUNTER_MODE_TX_EVENT_FIFO(__CANx__)                 (__CANx__->TimeoutConfig.TOS = 1)
#define __CAN_TIMEOUT_COUNTER_MODE_RX_FIFO0(__CANx__)                      (__CANx__->TimeoutConfig.TOS = 2)
#define __CAN_TIMEOUT_COUNTER_MODE_RX_FIFO1(__CANx__)                      (__CANx__->TimeoutConfig.TOS = 3)
#define __CAN_TIMEOUT_COUNTER_SET_MODE(__CANx__, __MODE__)                 (__CANx__->TimeoutConfig.TOS = __MODE__)
#define __CAN_TIMEOUT_COUNTER_GET_MODE(__CANx__)                           (__CANx__->TimeoutConfig.TOS)
#define __CAN_TIMEOUT_COUNTER_INITIAL_VALUE(__CANx__, __VALUE__)           (__CANx__->TimeoutConfig.TOP = __VALUE__)
#define __CAN_GET_TIMEOUT_COUNTER(__CANx__)                                (__CANx__->TimeoutCounter)

/* ----------------------*/
/*     Error Counter     */
/* ----------------------*/
#define __CAN_GET_TRANSMIT_ERROR_COUNTER(__CANx__)                         (__CANx__->ErrorCounter.TEC)
#define __CAN_GET_RECEIVE_ERROR_COUNTER(__CANx__)                          (__CANx__->ErrorCounter.REC)
#define __CAN_GET_CAN_ERROR_LOGGING(__CANx__)                              (__CANx__->ErrorCounter.CEL)

/* ----------------------*/
/*    Protocol Status    */
/* ----------------------*/
/* Get Protocol Status */
#define __CAN_GET_PROTOCOL_STATUS(__CANx__)                                (__CANx__->ProtocolStatus.BusProtocolStatus)
#define __CAN_GET_COMMUNICATION_STATE(__CANx__)                            (__CANx__->ProtocolStatus.Bits.ACT)

/* ------------------------------ */
/* Transmitter Delay Compensation */
/* ------------------------------ */
#define __CAN_GET_TRANSMITTER_DELAY_COMPENSATION(__CANx__, __VALUE__)                          (__CANx__->ProtocolStatus.TDCV)
#define __CAN_SET_TRANSMITTER_DELAY_COMPENSATION_OFFSET(__CANx__, __OFFSET__)                  (__CANx__->TxDelayCompensation.TDCO = __OFFSET__)
#define __CAN_SET_TRANSMITTER_DELAY_COMPENSATION_FILTER_WINDOW_LENGTH(__CANx__, __LENGTH__)    (__CANx__->TxDelayCompensation.TDCF = __LENGTH__)

/* ----------------------*/
/*       Interrupt       */
/* ----------------------*/
/* Interrupt status Enable/clear */
#define __CAN_INT_SELECT_LINE0(__CANx__, __INT__)                          (__CANx__->IntLineSelect &= ~(__INT__))
#define __CAN_INT_SELECT_LINE1(__CANx__, __INT__)                          (__CANx__->IntLineSelect |=  (__INT__))
#define __CAN_INT_LINE_ENABLE(__CANx__)                                    (__CANx__->IntLineEnbale = 0x3)
#define __CAN_INT_ENABLE(__CANx__, __INT__)                                (__CANx__->IntEnable |=  (__INT__))
#define __CAN_INT_DISABLE(__CANx__, __INT__)                               (__CANx__->IntEnable &= ~(__INT__))
#define __CAN_INT_CLEAR(__CANx__, __INT__)                                 (__CANx__->IntStatus |=  (__INT__))
#define __CAN_INT_GET_STATUS(__CANx__)                                     (__CANx__->IntStatus)

/* ----------------------*/
/*      Global Filter    */
/* ----------------------*/
/* Accept remote frames with 29-bit extended IDs */
/* Reject all remote frames with 29-bit extended IDs */
#define __CAN_EXTENDED_ACCEPT_REMOTE_FRAME(__CANx__)                       (__CANx__->GlobalFilterCfg.RRFE = 0)
#define __CAN_EXTENDED_REJECT_REMOTE_FRAME(__CANx__)                       (__CANx__->GlobalFilterCfg.RRFE = 1)
/* Accept remote frames with 11-bit standard IDs */
/* Reject all remote frames with 11-bit standard IDs */
#define __CAN_STANDARD_ACCEPT_REMOTE_FRAME(__CANx__)                       (__CANx__->GlobalFilterCfg.RRFS = 0)
#define __CAN_STANDARD_REJECT_REMOTE_FRAME(__CANx__)                       (__CANx__->GlobalFilterCfg.RRFS = 1)
/* Reject Non-matching data frames with 29-bit extended IDs */
/* Accept Non-matching data frames with 29-bit extended IDs to Rx FIFO 0 */
/* Accept Non-matching data frames with 29-bit extended IDs to Rx FIFO 1 */
#define __CAN_EXTENDED_REJECT_UNMATCHED_FRAME(__CANx__)                    (__CANx__->GlobalFilterCfg.ANFE = 2)
#define __CAN_EXTENDED_ACCEPT_UNMATCHED_FRAME_TO_FIFO0(__CANx__)           (__CANx__->GlobalFilterCfg.ANFE = 0)
#define __CAN_EXTENDED_ACCEPT_UNMATCHED_FRAME_TO_FIFO1(__CANx__)           (__CANx__->GlobalFilterCfg.ANFE = 1)
/* Reject Non-matching data frames with 11-bit standard IDs */
/* Accept Non-matching Frames Standard to Rx FIFO 0 */
/* Accept Non-matching Frames Standard to Rx FIFO 1 */
#define __CAN_STANDARD_REJECT_UNMATCHED_FRAME(__CANx__)                    (__CANx__->GlobalFilterCfg.ANFS = 2)
#define __CAN_STANDARD_ACCEPT_UNMATCHED_FRAME_TO_FIFO0(__CANx__)           (__CANx__->GlobalFilterCfg.ANFS = 0)
#define __CAN_STANDARD_ACCEPT_UNMATCHED_FRAME_TO_FIFO1(__CANx__)           (__CANx__->GlobalFilterCfg.ANFS = 1)

/* ----------------------*/
/*     Standard Filter   */
/* ----------------------*/
/* Set Standard ID Filter List Start Address */
/* Get Standard ID Filter List Start Address */
#define __CAN_SET_STANDARD_ID_FILTER_LIST_START_ADDRESS(__CANx__, __ADDR__)    (__CANx__->StandardIDFilterCfg.FLSSA = __ADDR__)
#define __CAN_GET_STANDARD_ID_FILTER_LIST_START_ADDRESS(__CANx__)              (__CANx__->StandardIDFilterCfg.FLSSA)
/* Set Standard ID Filter List Size */
#define __CAN_SET_STANDARD_ID_FILTER_LIST_NUMS(__CANx__, __SIZE__)             (__CANx__->StandardIDFilterCfg.LSS = __SIZE__)

/* ----------------------*/
/*     Extended Filter   */
/* ----------------------*/
/* Set Extended ID Filter List Start Address */
/* Get Extended ID Filter List Start Address */
#define __CAN_SET_EXTENDED_ID_FILTER_LIST_START_ADDRESS(__CANx__, __ADDR__)    (__CANx__->ExtendedIDFilterCfg.FLESA = __ADDR__)
#define __CAN_GET_EXTENDED_ID_FILTER_LIST_START_ADDRESS(__CANx__)              (__CANx__->ExtendedIDFilterCfg.FLESA)
/* Set Extended ID Filter List numbers */
#define __CAN_SET_EXTENDED_ID_FILTER_LIST_NUMS(__CANx__, __SIZE__)             (__CANx__->ExtendedIDFilterCfg.LSE = __SIZE__)
/* Set Extended ID Filter Mask */
#define __CAN_SET_EXTENDED_ID_MASK(__CANx__, __MASK__)                         (__CANx__->ExtendedIDMask = __MASK__)

/* Get high priority message status */
#define __CAN_GET_HIGH_PRIORITY_MESSAGE_STATUS(__CANx__)                       (__CANx__->HighPriorityMSGStatus)

/* ----------------------*/
/*        NewData        */
/* ----------------------*/
#define  __CAN_CLEAR_NEWDATA1_FLAGS(__CANx__, __MASK__)                        (__CANx__->NewData1 = __MASK__)
#define  __CAN_CLEAR_NEWDATA2_FLAGS(__CANx__, __MASK__)                        (__CANx__->NewData2 = __MASK__)

/* ----------------------*/
/*    RxFIFO0/1 Config   */
/* ----------------------*/
/* Set Rx FIFO 0/1 Start Address */
/* Get Rx FIFO 0/1 Start Address */
#define __CAN_SET_Rx_FIFO0_START_ADDRESS(__CANx__, __ADDR__)                   (__CANx__->RxFIFO0Config.FxSA = __ADDR__)
#define __CAN_SET_Rx_FIFO1_START_ADDRESS(__CANx__, __ADDR__)                   (__CANx__->RxFIFO1Config.FxSA = __ADDR__)
#define __CAN_GET_Rx_FIFO0_START_ADDRESS(__CANx__)                             (__CANx__->RxFIFO0Config.FxSA)
#define __CAN_GET_Rx_FIFO1_START_ADDRESS(__CANx__)                             (__CANx__->RxFIFO1Config.FxSA)

/* Set Rx FIFO 0/1 numbers */
#define __CAN_SET_Rx_FIFO0_NUMS(__CANx__, __SIZE__)                            (__CANx__->RxFIFO0Config.FxS = __SIZE__)
#define __CAN_SET_Rx_FIFO1_NUMS(__CANx__, __SIZE__)                            (__CANx__->RxFIFO1Config.FxS = __SIZE__)
/* Set Rx FIFO 0/1 threshold */
#define __CAN_SET_RX_FIFO0_THRESHOLD(__CANx__, __THRESHOLD__)                  (__CANx__->RxFIFO0Config.FxWM = __THRESHOLD__)
#define __CAN_SET_RX_FIFO1_THRESHOLD(__CANx__, __THRESHOLD__)                  (__CANx__->RxFIFO1Config.FxWM = __THRESHOLD__)

/* Set Rx FIFO 0/1 Operation Mode */
#define __CAN_SET_Rx_FIFO0_BLOCKING_MODE(__CANx__)                             (__CANx__->RxFIFO0Config.FxOM = 0)
#define __CAN_SET_Rx_FIFO0_OVERWRITE_MODE(__CANx__)                            (__CANx__->RxFIFO0Config.FxOM = 1)
#define __CAN_SET_Rx_FIFO1_BLOCKING_MODE(__CANx__)                             (__CANx__->RxFIFO1Config.FxOM = 0)
#define __CAN_SET_Rx_FIFO1_OVERWRITE_MODE(__CANx__)                            (__CANx__->RxFIFO1Config.FxOM = 1)
/* Set Rx FIFO 0/1 Acknowledge */
#define __CAN_SET_Rx_FIFO0_ACKNOWLEDGE(__CANx__, __INDEX__)                    (__CANx__->RxFIFO0Ack = __INDEX__)
#define __CAN_SET_Rx_FIFO1_ACKNOWLEDGE(__CANx__, __INDEX__)                    (__CANx__->RxFIFO1Ack = __INDEX__)

/* Set Rx FIFO 0/1, Rx Buffer element size */
#define __CAN_SET_Rx_FIFO0_ELEMENT_SIZE(__CANx__, __SIZE__)                    (__CANx__->RxBufferElementCfg.F0DS = __SIZE__)
#define __CAN_SET_Rx_FIFO1_ELEMENT_SIZE(__CANx__, __SIZE__)                    (__CANx__->RxBufferElementCfg.F1DS = __SIZE__)
#define __CAN_SET_Rx_BUFFER_ELEMENT_SIZE(__CANx__, __SIZE__)                   (__CANx__->RxBufferElementCfg.RBDS = __SIZE__)

/* ----------------------*/
/*    RxBuffer Config    */
/* ----------------------*/
/* Set Rx Buffer Start Address */
/* Get Rx Buffer Start Address */
#define __CAN_SET_Rx_BUFFER_START_ADDRESS(__CANx__, __ADDR__)                  (__CANx__->RxBufferConfig = __ADDR__)
#define __CAN_GET_Rx_BUFFER_START_ADDRESS(__CANx__)                            (__CANx__->RxBufferConfig)

/* ----------------------*/
/*    RxFIFO0/1 Status   */
/* ----------------------*/
/* Get Rx FIFO 0/1 Fill Level */
#define __CAN_GET_Rx_FIFO0_FILL_LEVEL(__CANx__)                                (__CANx__->RxFIFO0Status.FxFL)
#define __CAN_GET_Rx_FIFO1_FILL_LEVEL(__CANx__)                                (__CANx__->RxFIFO1Status.FxFL)
/* Get Rx FIFO 0/1 Put Index */
#define __CAN_GET_Rx_FIFO0_PUT_INDEX(__CANx__)                                 (__CANx__->RxFIFO0Status.FxPI)
#define __CAN_GET_Rx_FIFO1_PUT_INDEX(__CANx__)                                 (__CANx__->RxFIFO1Status.FxPI)
/* Get Rx FIFO 0/1 Get Index */
#define __CAN_GET_Rx_FIFO0_GET_INDEX(__CANx__)                                 (__CANx__->RxFIFO0Status.FxGI)
#define __CAN_GET_Rx_FIFO1_GET_INDEX(__CANx__)                                 (__CANx__->RxFIFO1Status.FxGI)
/* Is Rx FIFO 0/1 Full */
#define __CAN_IS_Rx_FIFO0_FULL(__CANx__)                                       (__CANx__->RxFIFO0Status.FxF == 1)
#define __CAN_IS_Rx_FIFO1_FULL(__CANx__)                                       (__CANx__->RxFIFO1Status.FxF == 1)
/* Is Rx FIFO 0/1 Message Lost */
#define __CAN_IS_Rx_FIFO0_MESSAGE_LOST(__CANx__)                               (__CANx__->RxFIFO0Status.RFxL == 1)
#define __CAN_IS_Rx_FIFO1_MESSAGE_LOST(__CANx__)                               (__CANx__->RxFIFO1Status.RFxL == 1)

/* ----------------------*/
/*    TxBuffer Config    */
/* ----------------------*/
/* Tx FIFO/Queue Mode */
#define __CAN_SET_Tx_FIFO_OPERATION(__CANx__)                              (__CANx__->TxBufferConfig.TFQM = 0)
#define __CAN_SET_Tx_QUEUE_OPERATION(__CANx__)                             (__CANx__->TxBufferConfig.TFQM = 1)
/* Tx FIFO/Queue Size */
/* Tx Buffer Size */
#define __CAN_SET_Tx_FIFO_QUEUE_NUMS(__CANx__, __SIZE__)                   (__CANx__->TxBufferConfig.TFQS = __SIZE__)
#define __CAN_SET_Tx_BUFFER_NUMS(__CANx__, __SIZE__)                       (__CANx__->TxBufferConfig.NDTB = __SIZE__)
/* Tx Buffers Start Address */
#define __CAN_SET_Tx_BUFFER_START_ADDRESS(__CANx__, __ADDR__)              (__CANx__->TxBufferConfig.TBSA = __ADDR__)
#define __CAN_GET_Tx_BUFFER_START_ADDRESS(__CANx__)                        (__CANx__->TxBufferConfig.TBSA)

/* ----------------------*/
/*    TxBuffer Status    */
/* ----------------------*/
/* Is Tx FIFO/Queue Full */
#define __CAN_IS_TxFIFO_QUEUE_FULL(__CANx__)                               (__CANx__->TxQueueStatus.TFQF == 1)
/* Get Tx FIFO/Queue Put/GET Index */
#define __CAN_GET_TxFIFO_QUEUE_PUT_INDEX(__CANx__)                         (__CANx__->TxQueueStatus.TFQPI)
#define __CAN_GET_TxFIFO_QUEUE_GET_INDEX(__CANx__)                         (__CANx__->TxQueueStatus.TFGI)
/* Get Tx FIFO free level */
#define __CAN_GET_TxFIFO_FREE_LEVEL(__CANx__)                              (__CANx__->TxQueueStatus.TFFL)

/* -----------------------*/
/*  TxBuffer Element Size */
/* -----------------------*/
/* Set Tx Buffer Element Size */
#define __CAN_SET_Tx_BUFFER_ELEMENT_SIZE(__CANx__, __SIZE__)               (__CANx__->TxBufferElementCfg = __SIZE__)


/* Get Tx Request Pending */
#define __CAN_GET_Tx_REQUEST_PENDING(__CANx__)                             (__CANx__->TxBufferReqPending)
/* Tx Buffer Add Request */
#define __CAN_ADD_Tx_REQUEST(__CANx__, __INDEX__)                          (__CANx__->TxBufferAddReq = __INDEX__)
/* Tx Buffer Cancellation Request */
#define __CAN_CANCELLATION_Tx_REQUEST(__CANx__, __INDEX__)                 (__CANx__->TxBufferCancellationReq = __INDEX__)
/* Get Tx Buffer Cancellation Finished */
#define __CAN_GET_CANCELLATION_Tx_REQUEST_END(__CANx__)                    (__CANx__->TxBufferCancellationEnd)
/* Get Tx Buffer Transmission Occurred */
#define __CAN_GET_Tx_OCCURRED(__CANx__)                                    (__CANx__->TxOccurred)
/* Tx Buffer Transmission Occurred interrupt enable/disable */
#define __CAN_Tx_OCCURRED_INT_ENABLE(__CANx__, __INDEX__)                  (__CANx__->TxOccurredIntEn |= (__INDEX__))
#define __CAN_Tx_OCCURRED_INT_DISABLE(__CANx__, __INDEX__)                 (__CANx__->TxOccurredIntEn &= ~(__INDEX__))
/* Tx Buffer Cancellation Finished interrupt enable/disable */
#define __CAN_Tx_CANCELLATION_END_INT_ENABLE(__CANx__, __INDEX__)          (__CANx__->TxCancellationEndIntEn |= (__INDEX__))
#define __CAN_Tx_CANCELLATION_END_INT_DISABLE(__CANx__, __INDEX__)         (__CANx__->TxCancellationEndIntEn &= ~(__INDEX__))

/* ----------------------*/
/*    Tx Event Config    */
/* ----------------------*/
/* Set Tx EVENT Address */
/* Get Tx EVENT Address */
#define __CAN_SET_Tx_EVENT_START_ADDRESS(__CANx__, __ADDR__)               (__CANx__->TxEventFIFOConfig.EFSA = __ADDR__)
#define __CAN_GET_Tx_EVENT_START_ADDRESS(__CANx__)                         (__CANx__->TxEventFIFOConfig.EFSA)
/* Set Tx EVENT numbers */
#define __CAN_SET_Tx_EVENT_NUMS(__CANx__, __SIZE__)                        (__CANx__->TxEventFIFOConfig.EFS = __SIZE__)
/* Set Tx EVENT threshold */
#define __CAN_SET_TX_EVENT_THRESHOLD(__CANx__, __THRESHOLD__)              (__CANx__->TxEventFIFOConfig.EFWM = __THRESHOLD__)

/* ----------------------*/
/*    Tx Event Status    */
/* ----------------------*/
/* Get Tx Event Fill Level */
#define __CAN_GET_Tx_EVENT_FILL_LEVEL(__CANx__)                            (__CANx__->TxEventFIFOStatus.EFFL)
/* Get Tx Event Put Index */
#define __CAN_GET_Tx_EVENT_PUT_INDEX(__CANx__)                             (__CANx__->TxEventFIFOStatus.EFPI)
/* Get Tx Event Get Index */
#define __CAN_GET_Tx_EVENT_GET_INDEX(__CANx__)                             (__CANx__->TxEventFIFOStatus.EFGI)
/* Is Tx Event Full */
#define __CAN_IS_Tx_EVENT_FULL(__CANx__)                                   (__CANx__->TxEventFIFOStatus.EFF == 1)
/* Is Tx Event Message Lost */
#define __CAN_IS_Tx_EVENT_MESSAGE_LOST(__CANx__)                           (__CANx__->TxEventFIFOStatus.TEFL == 1)

/* Set Tx Event Acknowledge */
#define __CAN_SET_Tx_EVENT_ACKNOWLEDGE(__CANx__, __INDEX__)                (__CANx__->TxEventFIFOAck = __INDEX__)

/* Exported functions --------------------------------------------------------*/

/* can_IRQHandler */
void can_IRQHandler(CAN_HandleTypeDef *hcan);

/* can_init */
void can_init(CAN_HandleTypeDef *hcan);
/* can_message_ram_init */
uint32_t can_message_ram_init(CAN_HandleTypeDef *hcan);

/* can_ram_watch_dog_config */
/* can_get_ram_watch_dog_value */
void can_ram_watch_dog_config(CAN_HandleTypeDef *hcan, uint8_t fu8_InitValue);
uint8_t can_get_ram_watch_dog_value(CAN_HandleTypeDef *hcan);

/* can_timestamp_prescaler_config */
/* can_timestamp_counter_reset */
/* can_get_timestamp_counter */
void can_timestamp_prescaler_config(CAN_HandleTypeDef *hcan, uint16_t fu16_prescaler);
void can_timestamp_counter_reset(CAN_HandleTypeDef *hcan);
uint16_t can_get_timestamp_counter(CAN_HandleTypeDef *hcan);

/* can_get_transmit_error_counter */
/* can_get_receive_error_counter */
uint8_t can_get_transmit_error_counter(CAN_HandleTypeDef *hcan);
uint8_t can_get_receive_error_counter(CAN_HandleTypeDef *hcan);

/* can_add_tx_message */
/* can_add_tx_message_to_txbuffer */
/* can_abort_tx_message */
/* can_is_tx_message_pending */
int32_t can_add_tx_message(CAN_HandleTypeDef *hcan, struct_CANTxHeaderDef_t fstr_TxHeader, uint8_t *Data);
int32_t can_add_tx_message_to_txbuffer(CAN_HandleTypeDef *hcan, uint32_t fu32_TxBufferIndex, struct_CANTxHeaderDef_t fstr_TxHeader, uint8_t *Data);
void can_abort_tx_message(CAN_HandleTypeDef *hcan, uint32_t fu32_PutIndex);
bool can_is_tx_message_pending(CAN_HandleTypeDef *hcan, uint32_t fu32_PutIndex);

/* can_add_standard_filter */
/* can_add_extended_filter */
/* can_remove_extended_filter */
/* can_remove_standard_filter */
void can_add_standard_filter(CAN_HandleTypeDef *hcan, struct_FilterCfg_t fstr_FilterCfg, uint32_t fu32_Index);
void can_add_extended_filter(CAN_HandleTypeDef *hcan, struct_FilterCfg_t fstr_FilterCfg, uint32_t fu32_Index);
void can_remove_extended_filter(CAN_HandleTypeDef *hcan, uint32_t fu32_Index);
void can_remove_standard_filter(CAN_HandleTypeDef *hcan, uint32_t fu32_Index);

/* can_get_rxbuffer_message */
/* can_get_rxfifo0_message */
/* can_get_rxfifo1_message */
void can_get_rxbuffer_message(CAN_HandleTypeDef *hcan, uint32_t fu32_RxBufferIndex, struct_CANRxHeaderDef_t *RxHeader, uint8_t *Data);
uint32_t can_get_rxfifo0_message(CAN_HandleTypeDef *hcan, struct_CANRxHeaderDef_t *RxHeader, uint8_t *Data);
uint32_t can_get_rxfifo1_message(CAN_HandleTypeDef *hcan, struct_CANRxHeaderDef_t *RxHeader, uint8_t *Data);

/* can_get_rxfifo0_fill_level */
/* can_get_rxfifo1_fill_level */
uint32_t can_get_rxfifo0_fill_level(CAN_HandleTypeDef *hcan);
uint32_t can_get_rxfifo1_fill_level(CAN_HandleTypeDef *hcan);

/* can_get_rxbuffer_0_31_status */
/* can_get_rxbuffer_32_64_status */
uint32_t can_get_rxbuffer_0_31_status(CAN_HandleTypeDef *hcan);
uint32_t can_get_rxbuffer_32_63_status(CAN_HandleTypeDef *hcan);

/* can_int_select_line */
/* can_int_enable */
/* can_int_disable */
/* can_get_int_status */
/* can_clear_int_status */
void can_int_select_line(CAN_HandleTypeDef *hcan, uint32_t fu32_INT_Index, enum_CAN_INT_LINEx_t fe_line);
void can_int_enable(CAN_HandleTypeDef *hcan, uint32_t fu32_INT_Index);
void can_int_disable(CAN_HandleTypeDef *hcan, uint32_t fu32_INT_Index);
uint32_t can_get_int_status(CAN_HandleTypeDef *hcan);
void can_clear_int_status(CAN_HandleTypeDef *hcan, uint32_t fu32_INT_Index);

/* can_enter_test_mode */
/* can_quit_test_mode */
void can_enter_test_mode(CAN_HandleTypeDef *hcan, enum_CAN_TestMode_t fe_TestMode);
void can_quit_test_mode(CAN_HandleTypeDef *hcan);
/* can_enter_bus_monitoring_mode */
/* can_quit_bus_monitoring_mode */
void can_enter_bus_monitoring_mode(CAN_HandleTypeDef *hcan);
void can_quit_bus_monitoring_mode(CAN_HandleTypeDef *hcan);
/* can_enter_restricted_operation_mode */
/* can_quit_restricted_operation_mode */
void can_enter_restricted_operation_mode(CAN_HandleTypeDef *hcan);
void can_quit_restricted_operation_mode(CAN_HandleTypeDef *hcan);

/* transmitter delay compensation enable */
/* transmitter delay compensation disable */
void can_fd_transmitter_delay_compensation_enable(CAN_HandleTypeDef *hcan, uint16_t fu16_TDCF, uint16_t fu32_TDCO);
void can_fd_transmitter_delay_compensation_disable(CAN_HandleTypeDef *hcan);

/* can fd frame format according to ISO11898-1 */
/* can fd frame format according to Bosch CAN FD Specification V1.0 */
void can_fd_frame_format_according_to_ISO11898_1(CAN_HandleTypeDef *hcan);
void can_fd_frame_format_according_to_Bosch(CAN_HandleTypeDef *hcan);

/* can_timeout_counter_config */
/* can_timeout_counter_enable */
/* can_timeout_counter_disable */
/* can_timeout_counter_restart */
void can_timeout_counter_config(CAN_HandleTypeDef *hcan, uint16_t fu16_InitValue, enum_CAN_Timeout_select_t fe_TOSelect);
void can_timeout_counter_enable(CAN_HandleTypeDef *hcan);
void can_timeout_counter_disable(CAN_HandleTypeDef *hcan);
void can_timeout_counter_restart(CAN_HandleTypeDef *hcan);

#endif
