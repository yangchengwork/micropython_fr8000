/*
  ******************************************************************************
  * @file    driver_sd_card.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of SD card application HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SD_CARD_H__
#define __DRIVER_SD_CARD_H__

#include "fr30xx.h"

/** @addtogroup SD_Card_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

#define BLOCKSIZE    (512U) /*!< Block size is 512 bytes */

#define SDMA_ADDR_ALIGN_MASK      (0xFFF80000U) /*!< SDMA align 512K Bytes */
#define SDMA_ADDR_UNIT            (0x80000U)

#define CARD_STATUS_IDLE          (0x0) /*!< Card status idle */
#define CARD_STATUS_READ_BUSY     (0x1) /*!< Card status read  busy */
#define CARD_STATUS_WRITE_BUSY    (0x2) /*!< Card status write busy */
#define CARD_STATUS_ERASE_BUSY    (0x3) /*!< Card status erase busy */
#define CARD_STATUS_ERR           (0x4) /*!< Card status error */

/* card version */
#define CARD_VER_1_X    (1U)
#define CARD_VER_2_X    (2U)

/* card type */
#define CARD_TYPE_SDHC_SDXC    (1U)
#define CARD_TYPE_SDSC         (2U)

/* SDIO bus width */
#define SDIO_BUS_WIDTH_1BIT    (0U)
#define SDIO_BUS_WIDTH_4BIT    (2U)

/* Card current state in R1 */
#define CARD_CURRENT_STATE_IDLE    (0x000)
#define CARD_CURRENT_STATE_READY   (0x200)
#define CARD_CURRENT_STATE_IDENT   (0x400)
#define CARD_CURRENT_STATE_STBY    (0x600)
#define CARD_CURRENT_STATE_TRAN    (0x800)
#define CARD_CURRENT_STATE_DATA    (0xA00)
#define CARD_CURRENT_STATE_RCV     (0xC00)
#define CARD_CURRENT_STATE_PRG     (0xE00)
#define CARD_CURRENT_STATE_DIS     (0x1000)
#define CARD_CURRENT_STATE_MASK    (0x1E00)

/* ACMD41 argument */
#define ACMD41_ARG_VOLTAGE_WINDOW_27_28    (0x00008000)   // VDD Voltage Window 2.7V~2.8V
#define ACMD41_ARG_VOLTAGE_WINDOW_28_29    (0x00010000)   // VDD Voltage Window 2.8V~2.9V
#define ACMD41_ARG_VOLTAGE_WINDOW_29_30    (0x00020000)   // VDD Voltage Window 2.9V~3.0V
#define ACMD41_ARG_VOLTAGE_WINDOW_30_31    (0x00040000)   // VDD Voltage Window 3.0V~3.1V
#define ACMD41_ARG_VOLTAGE_WINDOW_31_32    (0x00080000)   // VDD Voltage Window 3.1V~3.2V
#define ACMD41_ARG_VOLTAGE_WINDOW_32_33    (0x00100000)   // VDD Voltage Window 3.2V~3.3V
#define ACMD41_ARG_VOLTAGE_WINDOW_33_34    (0x00200000)   // VDD Voltage Window 3.3V~3.4V
#define ACMD41_ARG_VOLTAGE_WINDOW_34_35    (0x00400000)   // VDD Voltage Window 3.4V~3.5V
#define ACMD41_ARG_VOLTAGE_WINDOW_35_36    (0x00800000)   // VDD Voltage Window 3.5V~3.6V
#define ACMD41_ARG_S18R                    (0x01000000)   // switch to 1.8V Accepted
#define ACMD41_ARG_XPC                     (0x10000000)   // 150mA(max) and speed class is supported
#define ACMD41_ARG_HCS                     (0x40000000)   // host capacity support information

/* OCR register fields definition */
#define OCR_BUSY       (0x80000000)         // Card power up status bit
#define OCR_CCS        (0x40000000)         // Card capacity status
#define OCR_S18A       (0x01000000)         // switch to 1.8V Accepted

/* error code */
#define E1_NUM_ERR       (0x0001)    // Number of SD blocks is 0.
#define E2_1_8V_ERR      (0x0002)    // Card not support 1.8V.
#define E3_SPEED_ERR     (0x0003)    // Card not support selected Speed.
#define E4_CARD_BUSY     (0x0004)    // Card busy.

/*
 * @brief  CSD register definition.
 */
typedef struct
{
    uint32_t rsv_0              : 2;
    uint32_t FILE_FORMAT        : 2;    /*!< file format                                */  
    uint32_t TMP_WRITE_PROTECT  : 1;    /*!< temporary write protection                 */  
    uint32_t PERM_WRITE_PROTECT : 1;    /*!< permanent write protection                 */  
    uint32_t COPY               : 1;    /*!< copy flag                                  */  
    uint32_t FILE_FORMAT_GRP    : 1;    /*!< file format group                          */  
    uint32_t rsv_1              : 5;
    uint32_t WRITE_BL_PARTIAL   : 1;    /*!< partial blocks for write allowed           */  
    uint32_t WRITE_BL_LEN       : 4;    /*!< max. write data block length               */  
    uint32_t R2W_FACTOR         : 3;    /*!< write speed factor                         */  
    uint32_t rsv_2              : 2;
    uint32_t WP_GRP_ENABLE      : 1;    /*!< write protect group enable                 */  
    uint32_t WP_GRP_SIZE        : 7;    /*!< write protect group size                   */  
    uint32_t SECTOR_SIZE_H      : 1;    /*!< erase sector seize                         */  
        
    uint32_t SECTOR_SIZE_L      : 6;    /*!< erase sector seize                         */  
    uint32_t REASE_BLK_EN       : 1;    /*!< erase single block enable                  */  
    uint32_t rsv_3              : 1;
    uint32_t C_SIZE             : 22;   /*!< device size. 22-bit                        */  
    uint32_t rsv_4              : 2;

    uint32_t rsv_5              : 4;
    uint32_t DSR_IMP            : 1;    /*!< DSR implemented                            */
    uint32_t READ_BLK_MISALIGN  : 1;    /*!< read  block misalignment                   */
    uint32_t WRITE_BLK_MISALIGN : 1;    /*!< write block misalignment                   */
    uint32_t READ_BL_PARTIAL    : 1;    /*!< partial blocks for read allowed            */
    uint32_t READ_BL_LEN        : 4;    /*!< max. read data block length                */
    uint32_t CCC                : 12;   /*!< crad command classes                       */
    uint32_t TRAN_SPEED         : 8;    /*!< max. data transfer rate                    */

    uint32_t NSAC               : 8;    /*!< data read access in CLK cycles(NSAC*100)   */
    uint32_t TAAC               : 8;    /*!< data read access time 1                    */  
    uint32_t rsv_6              : 6;
    uint32_t CSD_STRUCTURE      : 2;    /*!< CSD structure                              */  
    uint32_t rsv_7              : 8;
}SD_CardCSDTypeDef;

/*
 * @brief  CID register definition.
 */
typedef struct
{
    uint16_t ManufactDate;         /*!< Manufacturing Date    */
    uint16_t ProductSN_A;          /*!< Product Serial Number */
    uint16_t ProductSN_B;          /*!< Product Serial Number */
    uint8_t  ProductRevision;      /*!< Product Revision      */
    uint8_t  ProductName[5];       /*!< Product Name          */
    uint16_t OEM_ApplicationID;    /*!< OEM/Application ID    */
    uint8_t  ManufacturerID;       /*!< Manufacturer ID       */
    uint8_t  rsv_0;
}SD_CardCIDTypeDef;

/*
 * @brief  SCR register definition.
 */
typedef struct
{
    uint32_t SCR_STRUCTURE         : 4;     /*!< SCR structure                   */
    uint32_t SD_SPEC               : 4;     /*!< SD Memory Card - spec version   */
    uint32_t DATA_STAT_AFTER_ERASE : 1;     /*!< data status after erases        */
    uint32_t SD_SECURITY           : 3;     /*!< CPRM security support           */
    uint32_t SD_BUS_WIDTHS         : 4;     /*!< dat bus widths support          */
    uint32_t SD_SPEC3              : 1;     /*!< spec version 3.00 or higher     */
    uint32_t EX_SUPPORT            : 4;     /*!< extended security support       */
    uint32_t rsv_0                 : 9;
    uint32_t CMD_SUPPORT           : 2;     /*!< command support bit             */
    uint32_t Manufacturer          : 32;    /*!< reserved for Manufacturer usage */
}SD_CardSCRTypeDef;

/*
 * @brief  SD Card Status definition.
 */
typedef struct
{
    uint8_t  DAT_BUS_WIDTH;             /*!< Shows the currently defined data bus width                 */
    uint8_t  SECURED_MODE;              /*!< Card is in secured mode of operation                       */
    uint16_t SD_CARD_TYPE;              /*!< Carries information about card type                        */
    uint32_t SIZE_OF_PROTECTED_AREA;    /*!< Carries information about the capacity of protected area   */
    uint8_t  SPEED_CLASS;               /*!< Carries information about the speed class of the card      */
    uint8_t  PERFORMANCE_MOVE;          /*!< Carries information about the card's performance move      */
    uint8_t  AU_SIZE;                   /*!< Carries information about the card's allocation unit size  */
    uint16_t ERASE_SIZE;                /*!< Determines the number of AUs to be erased in one operation */
    uint8_t  ERASE_TIMEOUT;             /*!< Determines the timeout for any number of AU erase          */
    uint8_t  ERASE_OFFSET;              /*!< Carries information about the erase offset                 */
    uint8_t  UHS_SPEED_GRADE;           /*!< speed grade for UHS mode                                   */
    uint8_t  UHS_AU_SIZE;               /*!< Size of AU for UHS mode                                    */
}SD_CardStatusTypeDef;

/** 
  * @brief  SD Card Information Structure definition
  */ 
typedef struct
{
    uint32_t CardType;                     /*!< Specifies the card Type                */

    uint32_t CardVersion;                  /*!< Specifies the card version             */

    uint32_t Class;                        /*!< Specifies the class of the card class  */

    uint32_t MemoryCapacity;               /*!< Specifies Memory Capacity in KBytes    */
    
    uint32_t SpeedCapacity;                /*!< Specifies speed Capacity */
}SD_CardInfoTypeDef;

/*
 * @brief  SD handle Structure definition
 */
typedef struct
{
    struct_SD_t           *SDx;              /*!< SD registers base address      */

    struct_SDInit_t        Init;             /*!< SD communication parameters    */

    SD_CardInfoTypeDef     CardInfo;         /*!< SD Card information            */

    SD_CardCIDTypeDef     *CIDInfo;          /*!< CID information    */
    SD_CardCSDTypeDef     *CSDInfo;          /*!< CSD information    */

    uint32_t               CSD[4];           /*!< SD card CSD register */
    uint32_t               CID[4];           /*!< SD card CID register */
    uint32_t               SCR[2];           /*!< SD card SCR register */
    uint32_t               OCR;              /*!< SD card OCR register */
    uint32_t               RCA;              /*!< SD card RCA register */

    volatile uint32_t      CardStatus;       /*!< SD card status */
    volatile uint32_t      AddrAlign;        /*!< SDMA address align */
}SD_HandleTypeDef;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/

/* SDCard_Init */
uint32_t SDCard_Init(SD_HandleTypeDef *hsd);
/* SDCard_BusWidth_Select */
uint32_t SDCard_BusWidth_Select(SD_HandleTypeDef *hsd, uint32_t fu32_BusWidth);

/* Read/Write Blocks */
uint32_t SDCard_ReadBolcks(SD_HandleTypeDef *hsd, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);
uint32_t SDCard_WriteBolcks(SD_HandleTypeDef *hsd, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);

/* Read/Write Blocks use SDMA */
uint32_t SDCard_ReadBolcks_SDMA(SD_HandleTypeDef *hsd, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);
uint32_t SDCard_WriteBolcks_SDMA(SD_HandleTypeDef *hsd, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);

/* Read/Write Blocks use SDMA with interrupt */
uint32_t SDCard_ReadBolcks_SDMA_IT(SD_HandleTypeDef *hsd, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);
uint32_t SDCard_WriteBolcks_SDMA_IT(SD_HandleTypeDef *hsd, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);

/* SDCard_Erase */
uint32_t SDCard_Erase(SD_HandleTypeDef *hsd, uint32_t BlockStartAddr, uint32_t BlockEndAddr);

/* SDCard_Get_Block_count */
uint32_t SDCard_Get_Block_count(SD_HandleTypeDef *hsd);

/* SDCard_IRQHandler */
void SDCard_IRQHandler(SD_HandleTypeDef *hsd);

#endif
