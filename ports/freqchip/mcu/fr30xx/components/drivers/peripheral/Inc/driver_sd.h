/*
  ******************************************************************************
  * @file    driver_sd.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of SD HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SD_H__
#define __DRIVER_SD_H__

#include "fr30xx.h"

/** @addtogroup SD_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Transfer Block control Register */
typedef struct
{
    uint32_t BlockSize      : 12;
    uint32_t HostSDMABuffer : 3;
    uint32_t rsv_0          : 1;
    uint32_t BlockCount     : 16;
}REG_TransferBlock_t;

/* Transfer mode Register */
typedef struct
{
    uint16_t DMAEnable              : 1;
    uint16_t BlockCountEnable       : 1;
    uint16_t AutoCMDEnable          : 2;
    uint16_t DataDirection          : 1;
    uint16_t MultiBlockEnable       : 1;
    uint16_t rsv_0                  : 5;
    uint16_t StreamModeEnable       : 1;
    uint16_t SPIModeEnable          : 1;
    uint16_t BootAckEnable          : 1;
    uint16_t AlternateBootOperation : 1;
    uint16_t BootOperation          : 1;
}REG_TransferConfig_t;

/* Transfer Block control Register */
typedef struct
{
    uint32_t CMDInhibit          : 1;
    uint32_t DATInhibit          : 1;
    uint32_t DATLineActive       : 1; 
    uint32_t Re_TuningRequset    : 1;
    uint32_t rsv_0               : 4;
    uint32_t WriteTransferActive : 1;
    uint32_t ReadTransferActive  : 1;
    uint32_t BufferWriteEnable   : 1;
    uint32_t BUfferReadEnable    : 1;
    uint32_t rsv_1               : 4;
    uint32_t CradInserted        : 1;
    uint32_t CradStateStable     : 1;
    uint32_t CredDetctPin        : 1;
    uint32_t WriteProtectPin     : 1;
    uint32_t DATLineSignal       : 4;
    uint32_t CMDLineSignal       : 1;
    uint32_t rsv_2               : 7;
}REG_PresentState_t;

/* control 0 Register */
typedef struct
{
    /* host control 1 */
    uint32_t LEDControl                : 1;
    uint32_t DataTransferWidth         : 1;
    uint32_t HighSpeedEnable           : 1;
    uint32_t DMASelect                 : 2;
    uint32_t ExtendDataTransferWidth   : 1;
    uint32_t CardDetectTestLevel       : 1;
    uint32_t CardDetectSignalSelection : 1;
    /* Power control */
    uint32_t SDBusPower         : 1;
    uint32_t SDBusVoltageSelect : 3;
    uint32_t SMIH_OD_PP         : 1;
    uint32_t SMIH_RST_N         : 1;
    uint32_t rsv_0              : 2;
    /* Block gap control */
    uint32_t StopRequest     : 1;
    uint32_t ContinueRequest : 1;
    uint32_t ReadWaitControl : 1;
    uint32_t BlockGapInt     : 1;
    uint32_t rsv_1           : 4;
    /* wakeup control */
    uint32_t WEE_CardInterrupt   : 1;    /* WEE: Wakeup Event Enable */
    uint32_t WEE_SDCardInsertion : 1;
    uint32_t WEE_SDCardRemoval   : 1;
    uint32_t rsv_2               : 5;
}REG_SD_Control0_t;

/* control 1 Register */
typedef struct
{
    /* clock control */
    uint32_t InternalClockEnable   : 1;
    uint32_t InternalClockStable   : 1;
    uint32_t SDClockEnable         : 1;
    uint32_t rsv_0                 : 2;
    uint32_t ClockGeneratorSelect  : 1;
    uint32_t SDCLKFrequencySelect1 : 2;
    uint32_t SDCLKFrequencySelect0 : 8;
    /* timeout control */
    uint32_t DATTimeoutValue       : 4;
    uint32_t rsv_1                 : 4;
    /* Software reset */
    uint32_t ResetAll              : 1;
    uint32_t ResetCMDLine          : 1;
    uint32_t ResetDATLine          : 1;
    uint32_t rsv_2                 : 5;
}REG_SD_Control1_t;

/* control 2 Register */
typedef struct
{
    /* Auto CMD Error status */
    uint32_t AutoCMD12NotExecuted             : 1;
    uint32_t AutoCMDTimeoutError              : 1;
    uint32_t AutoCMDCRCError                  : 1;
    uint32_t AutoCMDEndBitError               : 1;
    uint32_t AUtoCMDIndexError                : 1;
    uint32_t rsv_0                            : 2;
    uint32_t CommandNotIssuedByAutoCMD12Error : 1;
    uint32_t rsv_1                            : 8;
    /* host control 2 */
    uint32_t UHSModeSelect                    : 3;
    uint32_t Signal1_8Enable                  : 1;
    uint32_t DriverStrengthSelect             : 2;
    uint32_t ExcuteTuning                     : 1;
    uint32_t SamplingClockSelect              : 1;
    uint32_t rsv_2                            : 6;
    uint32_t AsynchronousInterruptEnable      : 1;
    uint32_t SDCLK_IO_Operation               : 1;
}REG_SD_Control2_t;

/* Capability0 Register */
typedef struct
{
    uint32_t SDR50_Support      : 1;
    uint32_t SDR104_Support     : 1;
    uint32_t DDR50_Support      : 1;
    uint32_t rsv_0              : 1;
    uint32_t DriverTypeASupport : 1;
    uint32_t DriverTypeCSupport : 1;
    uint32_t DriverTypeDSupport : 1;
    uint32_t rsv_1              : 1;
    uint32_t ReTuningTimerCount : 4;
    uint32_t rsv_2              : 1;
    uint32_t SDR50_UseTuning    : 1;
    uint32_t ReTuningMode       : 2;
    uint32_t ClockMultiplier    : 8;
    uint32_t rsv_3              : 8;
}REG_Capability0_t;

/* ------------------------------------------------*/
/*                    SD Register                  */
/* ------------------------------------------------*/
typedef struct 
{
    volatile uint32_t             Argument2;          /* Offset 0x00 */
    volatile REG_TransferBlock_t  Block;              /* Offset 0x04 */
    volatile uint32_t             Argument1;          /* Offset 0x08 */
    volatile REG_TransferConfig_t TransferConfig;     /* Offset 0x0C */
    volatile uint16_t             Command;            /* Offset 0x0E */
    volatile uint32_t             Response0;          /* Offset 0x10 */
    volatile uint32_t             Response1;          /* Offset 0x14 */
    volatile uint32_t             Response2;          /* Offset 0x18 */
    volatile uint32_t             Response3;          /* Offset 0x1C */
    volatile uint32_t             BufferData;         /* Offset 0x20 */
    volatile uint32_t             PresentState;       /* Offset 0x24 */
    volatile REG_SD_Control0_t    Control0;           /* Offset 0x28 */
    volatile REG_SD_Control1_t    Control1;           /* Offset 0x2C */
    volatile uint32_t             StatusInt;          /* Offset 0x30 */
    volatile uint32_t             StatusIntEN;        /* Offset 0x34 */
    volatile uint32_t             SignalIntEN;        /* Offset 0x38 */
    volatile REG_SD_Control2_t    Control2;           /* Offset 0x3C */
    volatile uint32_t             Capability0;        /* Offset 0x40 */
    volatile uint32_t             Capability1;        /* Offset 0x44 */
    volatile uint32_t             MaxCurrent0;        /* Offset 0x48 */
    volatile uint32_t             MaxCurrent1;        /* Offset 0x4C */
    volatile uint32_t             ForceError;         /* Offset 0x50 */
    volatile uint32_t             AMDAError;          /* Offset 0x54 */
    volatile uint32_t             ADMA_Address0;      /* Offset 0x58 */
    volatile uint32_t             ADMA_Address1;      /* Offset 0x5C */
    volatile uint32_t             PresetValue0;       /* Offset 0x60 */
    volatile uint32_t             PresetValue1;       /* Offset 0x64 */
    volatile uint32_t             PresetValue2;       /* Offset 0x68 */
    volatile uint32_t             PresetValue3;       /* Offset 0x6C */
    volatile uint32_t             rsv_0[28];    
    volatile uint32_t             ShareBusCtl;        /* Offset 0xE0 */
    volatile uint32_t             rsv_1[2];
    volatile uint32_t             BurstSize;          /* Offset 0xEC */
    volatile uint32_t             rsv_2[1];
    volatile uint32_t             ManualSampling;     /* Offset 0xF4 */
    volatile uint32_t             ConsecutiveSampling;/* Offset 0xF8 */
    volatile uint32_t             SoltIntStatus;      /* Offset 0xFC */
}struct_SD_t; 

#define SDIO0    ((struct_SD_t *)SDIOH0_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */



/** @addtogroup SD_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

/* SD Bus Voltage Select */
typedef enum
{
    VOLTAGE_3_3 = 7,
    VOLTAGE_3_0 = 6,
    VOLTAGE_1_8 = 5,
}enum_Voltage_Select_t;

/* command response type */
typedef enum
{
    CMD_TYPE_ABORT   = 0xC0,
    CMD_TYPE_RESUME  = 0x80,
    CMD_TYPE_SUSPEND = 0x40,
    CMD_TYPE_NORMAL  = 0,

    DATA_PRESENT    = 0x20,
    NO_DATA_PRESENT = 0,

    RES_NO          = 0,
    RES_R2          = 0x09,
    RES_R3_R4       = 0x02,
    RES_R1_R5_R6_R7 = 0x1A,
    RES_R1b_R5b     = 0x1B,
}enum_CmdRes_Type_t;

/* present state mask */
typedef enum
{
    PreState_CMD_LINE_MASK          = 0x00000001,
    PreState_DAT_LINE_MASK          = 0x00000002,
    PreState_DAT_LINE_ACTIVE_MASK   = 0x00000004,
    PreState_RE_TUNING_REQUEST_MASK = 0x00000008,
    PreState_WRITE_TRANDSFER_MASK   = 0x00000100,
    PreState_READ_TRANDSFER_MASK    = 0x00000200,
    PreState_BUFFER_WRITE_EN_MASK   = 0x00000400,
    PreState_BUFFER_READ_EN_MASK    = 0x00000800,
    PreState_CARD_INSERTED_MASK     = 0x00010000,
    PreState_CARD_STABLE_MASK       = 0x00020000,
    PreState_WRITE_PROTECT_MASK     = 0x00080000,
    PreState_DAT0_SIGNAL_MASK       = 0x00100000,
    PreState_DAT1_SIGNAL_MASK       = 0x00200000,
    PreState_DAT2_SIGNAL_MASK       = 0x00400000,
    PreState_DAT3_SIGNAL_MASK       = 0x00800000,
    PreState_CMD_SIGNAL_MASK        = 0x01000000,
}enum_PresentState_t;

/* interrupt status mask */
typedef enum
{
    INT_CMD_COMPLETE       = 0x00000001,
    INT_TRANSFER_COMPLETE  = 0x00000002,
    INT_BLOCK_GAP_EVENT    = 0x00000004,
    INT_DMA_INT            = 0x00000008,
    INT_BUFFER_WRITE_READY = 0x00000010,
    INT_BUFFER_READ_READY  = 0x00000020,
    INT_CARD_INSERTION     = 0x00000040,
    INT_CARD_REMOVAL       = 0x00000080,
    INT_CARD_INT           = 0x00000100,
    INT_A                  = 0x00000200,
    INT_B                  = 0x00000400,
    INT_C                  = 0x00000800,
    INT_RE_RUNING_EVENT    = 0x00001000,
    INT_BOOT_ACK_COMPLETE  = 0x00002000,
    INT_BOOT_DONE          = 0x00004000,
    INT_ERR                = 0x00008000,

    INT_ERR_CMD_TO         = 0x00010000,
    INT_ERR_CMD_CRC        = 0x00020000,
    INT_ERR_CMD_END_BIT    = 0x00040000,
    INT_ERR_CMD_INDEX      = 0x00080000,
    INT_ERR_DAT_TO         = 0x00100000,
    INT_ERR_DAT_CRC        = 0x00200000,
    INT_ERR_DAT_END_BIT    = 0x00400000,
    INT_ERR_CURRENT_LIMIT  = 0x00800000,
    INT_ERR_AUTO_CMD       = 0x01000000,
    INT_ERR_ADMA           = 0x02000000,
    INT_ERR_TUNING         = 0x04000000,
    INT_ERR_MASK           = 0x07FF0000,

    INT_NO_ERR             = 0,
}enum_INT_Status_t;

/* Auto CMD error status mask */
typedef enum
{
    AUTO_CMD12_NOT_EXECUTED = 0x00000001,
    AUTO_CMD_ERR_TO         = 0x00000002,
    AUTO_CMD_ERR_CRC        = 0x00000004,
    AUTO_CMD_ERR_END_BIT    = 0x00000008,
    AUTO_CMD_ERR_INDEX      = 0x00000010,
    AUTO_CMD23_ERR          = 0x00000080,
}enum_AUTO_CMD_ERR_STATUS_t;

/** 
  * @brief  Masks for errors Card Status Response R1
  */
#define RESP1_ERR_ADDR_OUT_OF_RANGE        (0x80000000U)
#define RESP1_ERR_ADDR_MISALIGNED          (0x40000000U)
#define RESP1_ERR_BLOCK_LEN_ERR            (0x20000000U)
#define RESP1_ERR_ERASE_SEQ_ERR            (0x10000000U)
#define RESP1_ERR_BAD_ERASE_PARAM          (0x08000000U)
#define RESP1_ERR_WRITE_PROT_VIOLATION     (0x04000000U)
#define RESP1_ERR_LOCK_UNLOCK_FAILED       (0x01000000U)
#define RESP1_ERR_COM_CRC_FAILED           (0x00800000U)
#define RESP1_ERR_ILLEGAL_CMD              (0x00400000U)
#define RESP1_ERR_CARD_ECC_FAILED          (0x00200000U)
#define RESP1_ERR_CC_ERROR                 (0x00100000U)
#define RESP1_ERR_GENERAL_UNKNOWN_ERROR    (0x00080000U)
#define RESP1_ERR_STREAM_READ_UNDERRUN     (0x00040000U)
#define RESP1_ERR_STREAM_WRITE_OVERRUN     (0x00020000U)
#define RESP1_ERR_CID_CSD_OVERWRITE        (0x00010000U)
#define RESP1_ERR_WP_ERASE_SKIP            (0x00008000U)
#define RESP1_ERR_CARD_ECC_DISABLED        (0x00004000U)
#define RESP1_ERR_ERASE_RESET              (0x00002000U)
#define RESP1_ERR_AKE_SEQ_ERROR            (0x00000008U)
#define RESP1_ERR_ERRORBITS                (0xFDFFE008U)

#define RCA_ERR_AKE_SEQ_ERROR           (0x00000008U)
#define RCA_ERR_GENERAL_UNKNOWN_ERROR   (0x00002000U)
#define RCA_ERR_ILLEGAL_CMD             (0x00004000U)
#define RCA_ERR_COM_CRC_FAILED          (0x00008000U)
#define RCA_ERR_ERRORBITS               (0x0000E008U)

/* SD Commands Index */
typedef enum
{
    SDMMC_CMD0_GO_IDLE_STATE         = 0x000,     // 0
      MMC_CMD1_SEND_OP_COND          = 0x100,     // 1
    SDMMC_CMD2_ALL_SEND_CID          = 0x200,     // 2
       SD_CMD3_SEND_RELATIVE_ADDR    = 0x300,     // 3
      MMC_CMD3_SET_RELATIVE_ADDR     = 0x300,     // 3
    SDMMC_CMD4_SET_DSR               = 0x400,     // 4
       SD_CMD6_SWITCH_FUNC           = 0x600,     // 6
      MMC_CMD6_SWITCH                = 0x600,     // 6
    SDMMC_CMD7_SEL_DESEL_CARD        = 0x700,     // 7
       SD_CMD8_SEND_IF_COND          = 0x800,     // 8
      MMC_CMD8_SEND_EXT_CSD          = 0x800,     // 8
    SDMMC_CMD9_SEND_CSD              = 0x900,     // 9
    SDMMC_CMD10_SEND_CID             = 0xA00,     // 10
       SD_CMD11_VOLTAGE_SWITCH       = 0xB00,     // 11
    SDMMC_CMD12_STOP_TRANSMISSION    = 0xC00,     // 12
    SDMMC_CMD13_SEND_STATUS          = 0xD00,     // 13
    SDMMC_CMD15_GO_INACTIVE_STATE    = 0xF00,     // 15
    SDMMC_CMD16_SET_BLOCKLEN         = 0x1000,    // 16
    SDMMC_CMD17_READ_SINGLI_BLOCK    = 0x1100,    // 17
    SDMMC_CMD18_READ_MULTIPLE_BLOCK  = 0x1200,    // 18
       SD_CMD19_SEND_TUNING_BLOCK    = 0x1300,    // 19
       SD_CMD20_SPEED_CLASS_CONTROL  = 0x1400,    // 20
      MMC_CMD21_SEND_TUNING_BLOCK    = 0x1500,    // 21
    SDMMC_CMD23_SET_BLOCK_COUNT      = 0x1700,    // 23
    SDMMC_CMD24_WRITE_BLOCK          = 0x1800,    // 24
    SDMMC_CMD25_WRITE_MULTIPLE_BLOCK = 0x1900,    // 25
      MMC_CMD226_PROGRAM_CID         = 0x1A00,    // 26
    SDMMC_CMD27_PROGRAM_CSD          = 0x1B00,    // 27
    SDMMC_CMD28_SET_WRITE_PROT       = 0x1C00,    // 28
    SDMMC_CMD29_CLR_WRITE_PROT       = 0x1D00,    // 29
    SDMMC_CMD30_SEND_WRITE_PROT      = 0x1E00,    // 30
      MMC_CMD30_SEND_WRITE_PROT_TYPE = 0x1F00,    // 31
       SD_CMD32_ERASE_WR_BLK_START   = 0x2000,    // 32
       SD_CMD33_ERASE_WR_BLK_END     = 0x2100,    // 33
      MMC_CMD35_ERASE_GROUP_START    = 0x2300,    // 35
      MMC_CMD36_ERASE_GROUP_END      = 0x2400,    // 36
    SDMMC_CMD38_ERASE                = 0x2600,    // 38
    SDMMC_CMD42_LOCK_UNLOCK          = 0x2A00,    // 42
    SDMMC_CMD55_APP_CMD              = 0x3700,    // 55
    SDMMC_CMD56_GEN_CMD              = 0x3800,    // 56
}enum_SD_MMC_CMD_t;

/* SD APP Commands Index */
typedef enum
{
    SD_ACMD6_SET_BUS_WIDTH           = 0x600,     // 6
    SD_ACMD13_SD_STATUS              = 0xD00,     // 13
    SD_ACMD22_SEND_NUM_WR_BLOCKS     = 0x1600,    // 22
    SD_ACMD23_SET_WR_BLK_ERASE_COUNT = 0x1700,    // 23
    SD_ACMD41_SD_SEND_OP_COND        = 0x2900,    // 41
    SD_ACMD42_SET_CLR_CARD_DETECT    = 0x2A00,    // 42
    SD_ACMD51_SEND_SCR               = 0x3300,    // 51
}enum_SD_ACMD_t;

/* SD BUS Speed mode */
typedef enum
{
    SPEED_DS     = 0x010,    /* default Speed up to 25MHz 3.3V signaling */ 
    SPEED_HS     = 0x011,    /* High    Speed up to 50MHz 3.3V signaling */ 
    SPEED_SDR12  = 0x100,    /* SDR up to 25MHz  1.8V signaling */ 
    SPEED_SDR25  = 0x101,    /* SDR up to 50MHz  1.8V signaling */ 
    SPEED_SDR50  = 0x102,    /* SDR up to 100MHz 1.8V signaling */ 
    SPEED_SDR104 = 0x103,    /* SDR up to 208MHz 1.8V signaling */ 
    SPEED_DDR50  = 0x104,    /* DDR up to 50MHz  1.8V signaling */ 

    SIGNALING_3_3V_MASK = 0x010,
    SIGNALING_1_8V_MASK = 0x100,
}enum_SpeedMode_t;

/** 
  * @brief  SDIO Command Control structure 
  */
typedef struct
{
    uint32_t Argument;            /*!< Specifies the SDIO command argument which is sent to a card 
                                       as part of a command message. */

    uint32_t CmdIndex;            /*!< Specifies the SDIO command index. 
                                       This parameter can be a value of @ref enum_SD_CMD_t/enum_SD_ACMD_t */

    uint32_t CmdType;             /*!< Specifies the SDIO command type.
                                       This parameter can be a value of @ref enum_CmdRes_Type_t */

    uint32_t DataType;            /*!< Specifies the SDIO command type.
                                       This parameter can be a value of @ref enum_CmdRes_Type_t */

    uint32_t ResponseType;        /*!< Specifies the SDIO response type.
                                       This parameter can be a value of @ref enum_CmdRes_Type_t */
}SDIO_CmdTypeDef;

/*
 * @brief SD Init Structure definition
 */
typedef struct
{
    uint32_t ClockDiv;            /*!< Specifies the clock frequency of the SDIO controller.
                                       This parameter can be a even number from 0 to 510 */  

    uint32_t SpeedMode;           /*!< Specifies the bus speed mode of the SDIO controller.
                                       This parameter can be a value of @ref enum_SpeedMode_t */  
}struct_SDInit_t;

/*
 * @brief MMC Init Structure definition
 */
typedef struct
{
    uint32_t ClockDiv;            /*!< Specifies the clock frequency of the SDIO controller.
                                       This parameter can be a even number from 0 to 510 */  
}struct_MMCInit_t;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* set SDMA system Address */
#define __SD_SET_SDMA_SYSTEM_ADDR(__SDx__, __ADDR__)           (__SDx__->Argument2 = __ADDR__)
/* set argument value */
#define __SD_SET_ARGUMENT1(__SDx__, __VALUE__)                 (__SDx__->Argument1 = __VALUE__)
#define __SD_SET_ARGUMENT2(__SDx__, __VALUE__)                 (__SDx__->Argument2 = __VALUE__)

/* __SD_SET_BLOCK_SIZE */
#define __SD_SET_BLOCK_SIZE(__SDx__, __SIZE__)                 (__SDx__->Block.BlockSize = __SIZE__)
/* __SD_SET_SDMA_BUFF */
#define __SD_SET_SDMA_BUFF(__SDx__, __BUFF__)                  (__SDx__->Block.HostSDMABuffer = __BUFF__)
/* __SD_SET_BLOCK_COUNT */
/* __SD_GET_BLOCK_COUNT */
#define __SD_SET_BLOCK_COUNT(__SDx__, __COUNT__)               (__SDx__->Block.BlockCount = __COUNT__)
#define __SD_GET_BLOCK_COUNT(__SDx__)                          (__SDx__->Block.BlockCount)

/* ----------------------*/
/*     Transfer Mode     */
/* ----------------------*/
/* __SD_DMA_ENABLE */
/* __SD_DMA_DISABLE */
#define __SD_DMA_ENABLE(__SDx__)                               (__SDx__->TransferConfig.DMAEnable = 1)
#define __SD_DMA_DISABLE(__SDx__)                              (__SDx__->TransferConfig.DMAEnable = 0)

/* Block Count register Enable */
#define __SD_BLOCK_COUNT_ENABLE(__SDx__)                       (__SDx__->TransferConfig.BlockCountEnable = 1)
#define __SD_BLOCK_COUNT_DISABLE(__SDx__)                      (__SDx__->TransferConfig.BlockCountEnable = 0)

/* 0x0: Auto command disable */
/* 0x1: Auto CMD12 enable */
/* 0x2: Auto CMD23 enable */
#define __SD_AUTO_CMD_ENABLE(__SDx__, __INDEX__)               (__SDx__->TransferConfig.AutoCMDEnable = __INDEX__)

/* data transfer direction */
#define __SD_DATA_DIRECTION(__SDx__, __DIR__)                  (__SDx__->TransferConfig.DataDirection = __DIR__)

/* Multi / Single Block Select */
#define __SD_MULTI_BLOCK_ENABLE(__SDx__)                       (__SDx__->TransferConfig.MultiBlockEnable = 1)
#define __SD_MULTI_BLOCK_DISABLE(__SDx__)                      (__SDx__->TransferConfig.MultiBlockEnable = 0)

/* MMC mode CMD11 / CMD20 Stream Read/Write Operations */
#define __SD_MMC_STREAM_MODE_ENABLE(__SDx__)                   (__SDx__->TransferConfig.StreamModeEnable = 1)
#define __SD_MMC_STREAM_MODE_DISABLE(__SDx__)                  (__SDx__->TransferConfig.StreamModeEnable = 0)

/* SPI mode enable */
#define __SD_SPI_MODE_ENABLE(__SDx__)                          (__SDx__->TransferConfig.SPIModeEnable = 1)
#define __SD_SPI_MODE_DISABLE(__SDx__)                         (__SDx__->TransferConfig.SPIModeEnable = 0)

/* Boot Ack Enable */
#define __SD_BOOT_ACK_ENABLE(__SDx__)                          (__SDx__->TransferConfig.BootAckEnable = 1)
#define __SD_BOOT_ACK_DISABLE(__SDx__)                         (__SDx__->TransferConfig.BootAckEnable = 0)

/* Alternate Boot Operation */
#define __SD_ALTERNATE_BOOT_START(__SDx__)                     (__SDx__->TransferConfig.AlternateBootOperation = 1)
#define __SD_ALTERNATE_BOOT_STOP(__SDx__)                      (__SDx__->TransferConfig.AlternateBootOperation = 0)

/* Boot Operation */
#define __SD_BOOT_START(__SDx__)                               (__SDx__->TransferConfig.BootOperation = 1)
#define __SD_BOOT_STOP(__SDx__)                                (__SDx__->TransferConfig.BootOperation = 0)

/* ----------------------*/
/*        Command        */
/* ----------------------*/
#define __SD_SEND_COMMAND(__SDx__, __CMD__)                    (__SDx__->Command = __CMD__)

/* Get response value */
#define __SD_GET_RESPONSE0(__SDx__)                            (__SDx__->Response0)
#define __SD_GET_RESPONSE1(__SDx__)                            (__SDx__->Response1)
#define __SD_GET_RESPONSE2(__SDx__)                            (__SDx__->Response2)
#define __SD_GET_RESPONSE3(__SDx__)                            (__SDx__->Response3)

/* Set BufferData address */
/* Get BufferData address */
#define __SD_SET_BUFFERDATA(__SDx__, __DATA__)                 (__SDx__->BufferData = __DATA__)
#define __SD_GET_BUFFERDATA(__SDx__)                           (__SDx__->BufferData)

/* Get present state */
#define __SD_GET_PRESENT_STATE(__SDx__)                        (__SDx__->PresentState)

/* ----------------------*/
/*     Host control 1    */
/* ----------------------*/
/* LED Control */
#define __SD_LED_CONTROL(__SDx__, __EN__)                      (__SDx__->Control0.LEDControl = __EN__)
/* Data Transfer Width */
#define __SD_DATA_WIDTH_1BIT(__SDx__)                          (__SDx__->Control0.DataTransferWidth = 0)
#define __SD_DATA_WIDTH_4BIT(__SDx__)                          (__SDx__->Control0.DataTransferWidth = 1)
/* High Speed Enable */
#define __SD_SPEED_MODE(__SDx__, __SPEED__)                    (__SDx__->Control0.HighSpeedEnable = __SPEED__)
/* DMA Select */
#define __SD_DMA_SELECT(__SDx__, __DMA__)                      (__SDx__->Control0.DMASelect = __DMA__)
/* 8 bit width mode */
#define __SD_8BIT_WIDTH_ENABLE(__SDx__)                        (__SDx__->Control0.ExtendDataTransferWidth = 1)
#define __SD_8BIT_WIDTH_DISABLE(__SDx__)                       (__SDx__->Control0.ExtendDataTransferWidth = 0)
/* Card Detect Test */
#define __SD_CRAD_DETECT(__SDx__, __DETECT__)                  (__SDx__->Control0.CardDetectTestLevel = __DETECT__)
/* Card Detect Signal Selection */
#define __SD_CRAD_DETECT_SIGNAL(__SDx__, __SIGNAL__)           (__SDx__->Control0.CardDetectSignalSelection = __SIGNAL__)

/* ----------------------*/
/*    Power control 1    */
/* ----------------------*/
/* SD Bus Power */
#define __SD_BUS_POWER_ON(__SDx__)                              (__SDx__->Control0.SDBusPower = 1)
#define __SD_BUS_POWER_OFF(__SDx__)                             (__SDx__->Control0.SDBusPower = 0)
/* SD Bus Voltage Select */
#define __SD_BUS_VOLTAGE_SELECT(__SDx__, __VOLTAGE__)           (__SDx__->Control0.SDBusVoltageSelect = __VOLTAGE__)
/* Open drain/push-pull in MMC mode */
#define __SD_MMC_OD_PP(__SDx__, __OD_PP__)                      (__SDx__->Control0.SMIH_OD_PP = __OD_PP__)
/* External Hardware reset in MMC mode */
#define __SD_MMC_EXT_RST(__SDx__, __RST__)                      (__SDx__->Control0.SMIH_RST_N = __RST__)

/* ----------------------*/
/*   Block Gap control   */
/* ----------------------*/
/* Stop At Block Gap request */
#define __SD_STOP_AT_BLOCK_GAP(__SDx__, __STOP__)               (__SDx__->Control0.StopRequest = __STOP__)
/* Continue At Block Gap request */
#define __SD_CONTINUE_AT_BLOCK_GAP(__SDx__, __CONTINUE__)       (__SDx__->Control0.ContinueRequest = __CONTINUE__)
/* Read Wait Control */
#define __SD_READ_WAIT(__SDx__, __WAIT__)                       (__SDx__->Control0.ReadWaitControl = __WAIT__)
/* Interrupt At Block Gap */
#define __SD_INT_AT_BLOCK_GAP(__SDx__, __INT__)                 (__SDx__->Control0.BlockGapInt = __INT__)

/* ----------------------*/
/*     Wakeup control    */
/* ----------------------*/
/* Wakeup Event Enable On Card Interrupt */
#define __SD_WAKEUP_ON_CARD_INT(__SDx__, __ON__)                (__SDx__->Control0.WEE_CardInterrupt = __ON__)
/* Wakeup Event Enable On SD Card Insertion */
#define __SD_WAKEUP_ON_CARD_INSERTION(__SDx__, __ON__)          (__SDx__->Control0.WEE_SDCardInsertion = __ON__)
/* Wakeup Event Enable On SD Card Removal */
#define __SD_WAKEUP_ON_CARD_REMOVAL(__SDx__, __ON__)            (__SDx__->Control0.WEE_SDCardRemoval = __ON__)

/* ----------------------*/
/*     Clock control     */
/* ----------------------*/
/* Internal Clock Enable/Disable */
#define __SD_INTERNAL_CLOCK_ENABLE(__SDx__)                     (__SDx__->Control1.InternalClockEnable = 1)
#define __SD_INTERNAL_CLOCK_DISABLE(__SDx__)                    (__SDx__->Control1.InternalClockEnable = 0)
/* Is Internal Clock Stable */
#define __SD_IS_INTERNAL_CLOCK_STABLE(__SDx__)                  (__SDx__->Control1.InternalClockStable == 1)
/* SD Clock Enable/Disable */
#define __SD_SDCLK_ENABLE(__SDx__)                              (__SDx__->Control1.SDClockEnable = 1)
#define __SD_SDCLK_DISABLE(__SDx__)                             (__SDx__->Control1.SDClockEnable = 0)
/* Clock Generator Select */
#define __SD_CLOCK_GENERATOR_SELECT(__SDx__, __SELECT__)        (__SDx__->Control1.ClockGeneratorSelect = __SELECT__)
/* SDCLK Frequency divide high 2bit */
#define __SD_CLOCK_DIV_HIGH_2BIT(__SDx__, __DIV__)              (__SDx__->Control1.SDCLKFrequencySelect1 = __DIV__)
/* SDCLK Frequency divide low 8bit */
#define __SD_CLOCK_DIV_LOW_8BIT(__SDx__, __DIV__)               (__SDx__->Control1.SDCLKFrequencySelect0 = __DIV__)

/* ----------------------*/
/*    Timeout control    */
/* ----------------------*/
/* Data Timeout Counter Value */
#define __SD_DATA_TIMEOUT_COUNT(__SDx__, __COUNT__)              (__SDx__->Control1.DATTimeoutValue = __COUNT__)

/* ----------------------*/
/*    Software control   */
/* ----------------------*/
/* Software Reset For All */
#define __SD_RST_SDIO_CONTROLLER(__SDx__)                       (__SDx__->Control1.ResetAll = 1)
/* Software Reset For CMD Line */
#define __SD_RST_CMD_LINE(__SDx__)                              (__SDx__->Control1.ResetCMDLine = 1)
/* Software Reset For DAT Line */
#define __SD_RST_DAT_LINE(__SDx__)                              (__SDx__->Control1.ResetDATLine = 1)

/* get interrupt status */
#define __SD_GET_INT_STATUS(__SDx__)                            (__SDx__->StatusInt)
/* clear interrupt status */
#define __SD_CLR_INT_STATUS(__SDx__, __STATUS__)                (__SDx__->StatusInt |= __STATUS__)
#define __SD_CLR_ALL_INT_STATUS(__SDx__)                        (__SDx__->StatusInt  = 0xFFFFFFFF)
/* interrupt Status enable/disable */
#define __SD_INT_STATUS_ENABLE(__SDx__, __STATUS__)             (__SDx__->StatusIntEN |=  (__STATUS__))
#define __SD_INT_STATUS_DISABLE(__SDx__, __STATUS__)            (__SDx__->StatusIntEN &= ~(__STATUS__))
#define __SD_INT_STATUS_ALL_ENABLE(__SDx__)                     (__SDx__->StatusIntEN = 0xFFFFFFFF)
#define __SD_INT_STATUS_ALL_DISABLE(__SDx__)                    (__SDx__->StatusIntEN = 0x00000000)
/* interrupt Signal enable/disable */
#define __SD_INT_ENABLE(__SDx__, __STATUS__)                    (__SDx__->SignalIntEN |=  (__STATUS__))
#define __SD_INT_DISABLE(__SDx__, __STATUS__)                   (__SDx__->SignalIntEN &= ~(__STATUS__))

/* get Auto CMD Error Status */
#define __SD_GET_AUTO_CMD_ERR_STATUS(__SDx__)                   (__SDx__->Control2 & 0x0000FFFF)

/* ----------------------*/
/*     Host control 2    */
/* ----------------------*/
/* UHS Mode Select */
#define __SD_UHS_MODE(__SDx__, __MODE__)                        (__SDx__->Control2.UHSModeSelect = __MODE__)
/* 1.8V Signaling */
#define __SD_1_8V_ENABLE(__SDx__, __EN__)                       (__SDx__->Control2.Signal1_8Enable = __EN__)
/* Driver Strength Select */
#define __SD_DRIVER_TYPE_SELECT(__SDx__, __TYPE__)              (__SDx__->Control2.DriverStrengthSelect = __TYPE__)
/* Execute Tuning */
#define __SD_EXECUTE_TUNING(__SDx__)                            (__SDx__->Control2.ExcuteTuning = 1)
#define __SD_EXECUTE_TUNING_GET(__SDx__)                        (__SDx__->Control2.ExcuteTuning)
/* Sampling Clock Select */
#define __SD_SAMPLING_CLOCK_SELECT(__SDx__, _SELECT__)          (__SDx__->Control2.SamplingClockSelect = _SELECT__)
#define __SD_SAMPLING_CLOCK_SELECT_GET(__SDx__)                 (__SDx__->Control2.SamplingClockSelect)
/* Consecutive Sampling */
#define __SD_CONSECUTIVE_SAMPLING(__SDx__, __COUNT__)           (__SDx__->ConsecutiveSampling = __COUNT__)
/* manual sampling delay set */
#define __SD_MANUAL_SAMPLING_SET(__SDx__, __COUNT__)            (__SDx__->ManualSampling = __COUNT__)
/* Asynchronous Interrupt Enable */
#define __SD_ASYN_INT_ENABLE(__SDx__, __EN__)                   (__SDx__->Control2.AsynchronousInterruptEnable = __EN__)
/* Preset config Enabled */
#define __SD_PRESET_ENABLE(__SDx__, __EN__)                     (__SDx__->Control2.SDCLK_IO_Operation = __EN__)

/* AHB Master Burst Size */
#define __SD_AHB_BURST_SIZE(__SDx__, __BURST__)                 (__SDx__->BurstSize = __BURST__)

/* Exported functions --------------------------------------------------------*/

/* SD_CMD_SetBlockCount */
uint32_t SD_CMD_SetBlockCount(struct_SD_t *SDx, uint32_t fu32_Argument);
/* Read */
uint32_t SD_CMD_ReadSingleBlock(struct_SD_t *SDx, uint32_t fu32_Argument);
uint32_t SD_CMD_ReadMultiBlock(struct_SD_t *SDx, uint32_t fu32_Argument);
uint32_t SD_CMD_ReadBlock_SDMA(struct_SD_t *SDx, uint32_t fu32_Argument);
/* Write */
uint32_t SD_CMD_WriteSingleBlock(struct_SD_t *SDx, uint32_t fu32_Argument);
uint32_t SD_CMD_WriteMultiBlock(struct_SD_t *SDx, uint32_t fu32_Argument);
uint32_t SD_CMD_WriteBlock_SDMA(struct_SD_t *SDx, uint32_t fu32_Argument);
/* Erase */
uint32_t SD_CMD_EraseStartAddr(struct_SD_t *SDx, uint32_t fu32_Argument);
uint32_t SD_CMD_EraseEndAddr(struct_SD_t *SDx, uint32_t fu32_Argument);
uint32_t SD_CMD_Erase(struct_SD_t *SDx);

/* SD_CMD_StopTransfer */
uint32_t SD_CMD_StopTransfer(struct_SD_t *SDx);
/* SD_CMD_BlockLength */
uint32_t SD_CMD_BlockLength(struct_SD_t *SDx,  uint32_t fu32_Argument);
/* SD_CMD_SelectCard / SD_CMD_DeselectCard */
uint32_t SD_CMD_SelectCard(struct_SD_t *SDx, uint32_t fu32_Argument);
uint32_t SD_CMD_DeselectCard(struct_SD_t *SDx);
/* SD_CMD_GoIdleState */
uint32_t SD_CMD_GoIdleState(struct_SD_t *SDx);
/* SD_CMD_VoltageSwitch */
uint32_t SD_CMD_VoltageSwitch(struct_SD_t *SDx);
/* SD_CMD_SwitchFunc */
uint32_t SD_CMD_SwitchFunc(struct_SD_t *SDx, uint32_t fu32_Argument);

/* SD_CMD_AllSendCID */
/* SD_CMD_SendRelAddr */
/* SD_CMD_SendCSD */
/* SD_CMD_SendStatus */
/* SD_CMD_SendInterfaceCondition */
uint32_t SD_CMD_AllSendCID(struct_SD_t *SDx, uint32_t *fp32_Response);
uint32_t SD_CMD_SendRelAddr(struct_SD_t *SDx, uint32_t *fp32_RCA);
uint32_t SD_CMD_SendCSD(struct_SD_t *SDx, uint32_t fu32_Argument, uint32_t *fp32_Response);
uint32_t SD_CMD_SendStatus(struct_SD_t *SDx, uint32_t fu32_Argument, uint32_t *fp_Resp);
uint32_t SD_CMD_SendInterfaceCondition(struct_SD_t *SDx);

/* SD_CMD_AppCommand */
uint32_t SD_CMD_AppCommand(struct_SD_t *SDx, uint32_t fu32_Argument);
/* SD_ACMD_SendOperCondition */
/* SD_ACMD_SetBusWidth */
uint32_t SD_ACMD_SendOperCondition(struct_SD_t *SDx, uint32_t fu32_Argument, uint32_t *fp32_Response);
uint32_t SD_ACMD_SetBusWidth(struct_SD_t *SDx, uint32_t fu32_Argument);

/* SD_SDCardClass_Init */
/* SD_SDMMCClass_Init */
void SD_SDCardClass_Init(struct_SD_t *SDx);
void SD_SDMMCClass_Init(struct_SD_t *SDx);

/* MMC_CMD_GoIdleState */
/* MMC_CMD_AllSendCID  */
/* MMC_CMD_SendCSD */
/* MMC_CMD_SelectCard */
/* MMC_CMD_DeselectCard */
#define MMC_CMD_GoIdleState    SD_CMD_GoIdleState
#define MMC_CMD_AllSendCID     SD_CMD_AllSendCID
#define MMC_CMD_SendCSD        SD_CMD_SendCSD
#define MMC_CMD_SelectCard     SD_CMD_SelectCard
#define MMC_CMD_DeselectCard   SD_CMD_DeselectCard
#define MMC_CMD_SendStatus     SD_CMD_SendStatus

/* SD_CMD_SetBlockCount */
#define MMC_CMD_SetBlockCount  SD_CMD_SetBlockCount
/* MMC_CMD_ReadSingleBlock */
/* MMC_CMD_ReadMultiBlock */
/* MMC_CMD_ReadBlock_SDMA */
#define MMC_CMD_ReadSingleBlock    SD_CMD_ReadSingleBlock
#define MMC_CMD_ReadMultiBlock     SD_CMD_ReadMultiBlock
#define MMC_CMD_ReadBlock_SDMA     SD_CMD_ReadBlock_SDMA
/* MMC_CMD_WriteSingleBlock */
/* MMC_CMD_WriteMultiBlock */
/* MMC_CMD_WriteBlock_SDMA */
#define MMC_CMD_WriteSingleBlock   SD_CMD_WriteSingleBlock
#define MMC_CMD_WriteMultiBlock    SD_CMD_WriteMultiBlock
#define MMC_CMD_WriteBlock_SDMA    SD_CMD_WriteBlock_SDMA

/* MMC_CMD_SendOperCondition */
uint32_t MMC_CMD_SendOperCondition(struct_SD_t *SDx, uint32_t fu32_Argument, uint32_t *fp32_Response);
/* MMC_CMD_SendExtendedCSD */
uint32_t MMC_CMD_SendExtendedCSD(struct_SD_t *SDx);
/* MMC_CMD_SetRelAddr */
uint32_t MMC_CMD_SetRelAddr(struct_SD_t *SDx, uint32_t fu32_RCA);
/* MMC_CMD_Switch */
uint32_t MMC_CMD_Switch(struct_SD_t *SDx, uint32_t fu32_Argument);
/* MMC_CMD_SendTuningBlock */
uint32_t MMC_CMD_SendTuningBlock(struct_SD_t *SDx);

#endif
