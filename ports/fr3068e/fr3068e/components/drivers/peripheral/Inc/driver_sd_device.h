/*
  ******************************************************************************
  * @file    driver_sd_device.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of SD device HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SD_DEVICE_H__
#define __DRIVER_SD_DEVICE_H__

#include "fr30xx.h"

/** @addtogroup SD_device_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Capability0 Register */
typedef struct
{
    uint32_t ProgramDone           : 1;
    uint32_t rsv_0                 : 1;
    uint32_t CardInitDone          : 1;
    uint32_t AddressOutRange       : 1;
    uint32_t AddressMisalign       : 1;
    uint32_t RpmbDisable           : 1;
    uint32_t EraseParam            : 1;
    uint32_t CardECCFailed         : 1;
    uint32_t CCError               : 1;
    uint32_t Error                 : 1;
    uint32_t MMC_IRQ_Trigger       : 1;
    uint32_t CMDDataOutputEdge     : 1;
    uint32_t CMD32_CMD33_Enable    : 1;
    uint32_t BootSequenceSupport   : 1;
    uint32_t SwitchError           : 1;
    uint32_t SendBootACK           : 1;
    uint32_t WP_Violation          : 1;
    uint32_t WP_Erase_Skip         : 1;
    uint32_t CID_CSD_Overwrite     : 1;
    uint32_t AKE_Seq_Error         : 1;
    uint32_t Card_ECC_Disabled     : 1;
    uint32_t StreamThresholdSize   : 3;
    uint32_t PermanentWriteProtect : 1;
    uint32_t TemporaryWriteProtect : 1;
    uint32_t WPCommandsEnabled     : 1;
    uint32_t ALLOW_AKE             : 1;
    uint32_t SECURED_MODE          : 1;
    uint32_t AKE_SEQ_OK            : 1;
    uint32_t ASSD_Disable          : 1;
    uint32_t BootDataReady         : 1;
}REG_SDDevice_Control_t;

/* Command Register */
typedef struct
{
    uint32_t Application           : 1;
    uint32_t BlockSize             : 12;
    uint32_t CommandIndex          : 6;
    uint32_t CurrentBusWidth       : 2;
    uint32_t CurrentSpeed          : 3;
    uint32_t CardState             : 4;
    uint32_t EraseSequence         : 1;
    uint32_t rsv_0                 : 3;
}REG_SDDevice_Command_t;

/* Password Length Register */
typedef struct
{
    uint32_t PWDS_LEN         : 8;
    uint32_t LockUnlockEnable : 1;
    uint32_t rsv_0            : 23;
}REG_PasswordLength_t;

/* -------------------------------------------------*/
/*                SD Device Register                */
/* -------------------------------------------------*/
typedef struct 
{
    volatile REG_SDDevice_Control_t    Control;                 /* Offset 0x00 */
    volatile REG_SDDevice_Command_t    Command;                 /* Offset 0x04 */
    volatile uint32_t                  Argument;                /* Offset 0x08 */
    volatile uint32_t                  BlockCount;              /* Offset 0x0C */
    volatile uint32_t                  DMA1Address;             /* Offset 0x10 */
    volatile uint32_t                  DMA1Control;             /* Offset 0x14 */
    volatile uint32_t                  DMA2Address;             /* Offset 0x18 */
    volatile uint32_t                  DMA2Control;             /* Offset 0x1C */
    volatile uint32_t                  EraseWriteBlockStart;    /* Offset 0x20 */
    volatile uint32_t                  EraseWriteblockEnd;      /* Offset 0x24 */
    volatile REG_PasswordLength_t      PasswordLength;          /* Offset 0x28 */
    volatile uint32_t                  SecureBlockCount;        /* Offset 0x2C */
    volatile uint32_t                  rsv_0[3];
    volatile uint32_t                  IntStatus;               /* Offset 0x3C */
    volatile uint32_t                  IntStatusEn;             /* Offset 0x40 */
    volatile uint32_t                  IntSignalEn;             /* Offset 0x44 */
    volatile uint32_t                  CardAddress;             /* Offset 0x48 */
    volatile uint32_t                  CardData;                /* Offset 0x4C */
    volatile uint32_t                  IOREADY;                 /* Offset 0x50 */
    volatile uint32_t                  Function1Control;        /* Offset 0x54 */
    volatile uint32_t                  Function2Control;        /* Offset 0x58 */
    volatile uint32_t                  SDIOCCCRControl;         /* Offset 0x5C */
    volatile uint32_t                  SDIOFBRxControl[8];      /* Offset 0x60 ~ 0x7C */
    volatile uint32_t                  CardSize;                /* Offset 0x80 */
    volatile uint32_t                  CardOCR;                 /* Offset 0x84 */
    volatile uint32_t                  Control2;                /* Offset 0x88 */
    volatile uint32_t                  rsv_1;                   
    volatile uint32_t                  Function3Control;        /* Offset 0x90 */
    volatile uint32_t                  Function4Control;        /* Offset 0x94 */
    volatile uint32_t                  Function5Control;        /* Offset 0x98 */
    volatile uint32_t                  IntStatus2;              /* Offset 0x9C */
    volatile uint32_t                  IntStatusEn2;            /* Offset 0xA0 */
    volatile uint32_t                  IntSignal2;              /* Offset 0xA4 */
    volatile uint32_t                  Password_127_96;         /* Offset 0xA8 */
    volatile uint32_t                  Password_95_64;          /* Offset 0xAC */
    volatile uint32_t                  Password_63_32;          /* Offset 0xB0 */
    volatile uint32_t                  Passowrd_31_0;           /* Offset 0xB4 */
    volatile uint32_t                  ADMAErrorStatus;         /* Offset 0xB8 */
    volatile uint32_t                  RCA;                     /* Offset 0xBC */
    volatile uint32_t                  Debug[7];                /* Offset 0xC0 ~ 0xD8 */
    volatile uint32_t                  AHBMasterBurstSize;      /* Offset 0xDC */
    volatile uint32_t                  Argument2;               /* Offset 0xE0 */
}struct_SD_Device_t; 

#define SD_DEVICE    ((struct_SD_Device_t *)SDIOD0_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */



/** @addtogroup SD_device_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

/* SD device interrupt status mask */
typedef enum
{
    INT_TRANSFER_COMP     = 0x00000001,
    INT_DMA1              = 0x00000002,
    INT_SLEEP_AWAKE       = 0x00000004,
    INT_WRITE_START       = 0x00000008,
    INT_READ_START        = 0x00000010,
    INT_PASSWORD_SET      = 0x00000020,
    INT_PASSWORD_RESET    = 0x00000040,
    INT_LOCK_CARD         = 0x00000080,
    INT_UNLOCK_CARD       = 0x00000100,
    INT_FORCE_ERASE       = 0x00000200,
    INT_ERASE             = 0x00000400,
    INT_CMD11             = 0x00000800,
    INT_CMD0_CMD52        = 0x00001000,
    INT_CMD6_CHECK        = 0x00002000,
    INT_CMD6_SWITCH       = 0x00004000,
    INT_PROGRAM_CSD       = 0x00008000,
    INT_ACMD23            = 0x00010000,
    INT_CMD20             = 0x00020000,
                         /* 0x00040000 */
    INT_CMD4              = 0x00080000,
    INT_BOOT_START        = 0x00100000,
    INT_FUNCTION1_RESET   = 0x00200000,
    INT_FUNCTION2_RESET   = 0x00400000,
    INT_CMD11_CLK_STOP    = 0x00800000,
    INT_CMD11_CLK_START   = 0x01000000,
    INT_PROGRAM_START     = 0x02000000,
    INT_CMD40             = 0x04000000,
    INT_CMD_R1b           = 0x08000000,
    INT_FUNCTIONX_ERROR   = 0x10000000,
    INT_FUNCTIONX_ABORT   = 0x20000000,
    INT_LRST              = 0x40000000,
    INT_BOOT_COMPLETE     = 0x80000000,
}enum_SD_Device_Status_t;


/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* ----------------------*/
/*     Control control   */
/* ----------------------*/

/* Program Done */
#define __SD_D_SET_PROGRAM_DONE(__SDx__)                            (__SDx__->Control.ProgramDone = 1)
/* Card Init Done */
#define __SD_D_CARD_INIT_DONE(__SDx__)                              (__SDx__->Control.CardInitDone = 1)
/* Address Out of Range */
#define __SD_D_ADDR_OUT_RANGE(__SDx__)                              (__SDx__->Control.AddressOutRange = 1)
/* Address Misalign */
#define __SD_D_ADDR_MISALIGN(__SDx__)                               (__SDx__->Control.AddressMisalign = 1)
/* Command and Data Output at the falling edge */
/* Command and Data Output at the Rising edge */
#define __SD_D_FALLING_EDGE_OUTPUT(__SDx__)                         (__SDx__->Control.CMDDataOutputEdge = 0)
#define __SD_D_RISING_EDGE_OUTPUT(__SDx__)                          (__SDx__->Control.CMDDataOutputEdge = 1)
/* support/nonsupport CMD32 CMD33 */
#define __SD_D_CMD32_CMD33_ENABLE(__SDx__)                          (__SDx__->Control.CMD32_CMD33_Enable = 0)
#define __SD_D_CMD32_CMD33_DISABLE(__SDx__)                         (__SDx__->Control.CMD32_CMD33_Enable = 1)
/* Stream Threshold Size */
#define __SD_D_SET_STREAM_THRESHOLD_SIZE(__SDx__, __SIZE__)         (__SDx__->Control.StreamThresholdSize = __SIZE__)

/* Set card address */
/* Set card data */
#define __SD_D_SET_CARD_ADDR(__SDx__, __ADDR__)                     (__SDx__->CardAddress = __ADDR__)
#define __SD_D_SET_CARD_DATA(__SDx__, __DATA__)                     (__SDx__->CardData = __DATA__)

/* get interrupt status */
#define __SD_D_GET_INT_STATUS(__SDx__)                              (__SDx__->IntStatus)
/* clear interrupt status */
#define __SD_D_CLR_INT_STATUS(__SDx__, __STATUS__)                  (__SDx__->IntStatus |= __STATUS__)
/* interrupt Status enable/disable */
#define __SD_D_INT_STATUS_ENABLE(__SDx__, __STATUS__)               (__SDx__->IntStatusEn |=  (__STATUS__))
#define __SD_D_INT_STATUS_DISABLE(__SDx__, __STATUS__)              (__SDx__->IntStatusEn &= ~(__STATUS__))
#define __SD_D_INT_STATUS_ALL_ENABLE(__SDx__)                       (__SDx__->IntStatusEn = 0xFFFFFFFF)
#define __SD_D_INT_STATUS_ALL_DISABLE(__SDx__)                      (__SDx__->IntStatusEn = 0x00000000)
/* interrupt Signal enable/disable */
#define __SD_D_INT_ENABLE(__SDx__, __STATUS__)                      (__SDx__->IntSignalEn |=  (__STATUS__))
#define __SD_D_INT_DISABLE(__SDx__, __STATUS__)                     (__SDx__->IntSignalEn &= ~(__STATUS__))


/* Exported functions --------------------------------------------------------*/



#endif
