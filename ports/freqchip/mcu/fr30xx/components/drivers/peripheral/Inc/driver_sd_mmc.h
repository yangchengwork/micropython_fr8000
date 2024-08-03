/*
  ******************************************************************************
  * @file    driver_sd_mmc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of Multi-Media card application HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SD_MMC_H__
#define __DRIVER_SD_MMC_H__

#include "fr30xx.h"

/** @addtogroup eMMC_Card_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

/* MMC Voltage mode */
#define eMMC_HIGH_VOLTAGE_RANGE        0xC0FF8000U  /*!< for eMMC > 2Gb sector mode   */
#define eMMC_DUAL_VOLTAGE_RANGE        0xC0FF8080U  /*!< for eMMC > 2Gb sector mode   */

/* MMC Memory Cards type */
#define  eMMC_DUAL_VOLTAGE_CARD     0x00000080U
#define  eMMC_CAPACITY_HIGHER_2G    0x40000000U

/*
 * @brief Extended CSD revisions
 */
#define MMC_REV_V4_0        (0)
#define MMC_REV_V4_1        (1)
#define MMC_REV_V4_2        (2)
#define MMC_REV_V4_3        (3)
#define MMC_REV_V4_41       (5)
#define MMC_REV_V4_45       (6)

/*
 * @brief MMC speed supports in 
 */
#define MMC_DEVICE_TPYE_HS200_1_2V                  (0x20)
#define MMC_DEVICE_TPYE_HS200_1_8V                  (0x10)
#define MMC_DEVICE_TPYE_HIGH_SPEED_DUAL_1_2V        (0x08)
#define MMC_DEVICE_TPYE_HIGH_SPEED_DUAL_1_8V_3V     (0x04)
#define MMC_DEVICE_TPYE_HIGH_SPEED_SINGLE_52MHz     (0x02)
#define MMC_DEVICE_TPYE_HIGH_SPEED_SINGLE_26MHz     (0x01)

/* MMC bus width */
#define MMC_BUS_WIDTH_1BIT    (0U)
#define MMC_BUS_WIDTH_4BIT    (1U)
#define MMC_BUS_WIDTH_8BIT    (2U)
/* MMC bus width(dual data rate) */
#define MMC_BUS_WIDTH_4BIT_DDR    (5U)
#define MMC_BUS_WIDTH_8BIT_DDR    (6U)

/* MMC High speed timing values */
#define MMC_COMPATIBILITY_TIMING    (0U)
#define MMC_HIGH_SPEED_TIMING       (1U)
#define MMC_HS200_TIMING            (2U)

/* MMC CMD6 access mode */
#define MMC_CMD6_ACCESS_CMD_SET       (0x00000000)
#define MMC_CMD6_ACCESS_SET_BITS      (0x01000000)
#define MMC_CMD6_ACCESS_CLR_BITS      (0x02000000)
#define MMC_CMD6_ACCESS_WRITE_BYTE    (0x03000000)

/*
 * @brief The parameter index in the Extended CSD register.
 */
#define MMC_EX_CSD_INDEX_SEC_COUNT0    (212)
#define MMC_EX_CSD_INDEX_SEC_COUNT1    (213)
#define MMC_EX_CSD_INDEX_SEC_COUNT2    (214)
#define MMC_EX_CSD_INDEX_SEC_COUNT3    (215)
#define MMC_EX_CSD_INDEX_DEVICE_TYPE   (196)
#define MMC_EX_CSD_INDEX_EXT_CSD_REV   (192)
#define MMC_EX_CSD_INDEX_HS_TIMING     (185)
#define MMC_EX_CSD_INDEX_BUS_WIDTH     (183)

#define MMC_STATUS_IDLE            CARD_STATUS_IDLE          /*!< eMMC status idle */
#define MMC_STATUS_READ_BUSY       CARD_STATUS_READ_BUSY     /*!< eMMC status read  busy */
#define MMC_STATUS_WRITE_BUSY      CARD_STATUS_WRITE_BUSY    /*!< eMMC status write busy */
#define MMC_STATUS_ERASE_BUSY      CARD_STATUS_ERASE_BUSY    /*!< eMMC status erase busy */
#define MMC_STATUS_ERR             CARD_STATUS_ERR           /*!< eMMC status error */

/* eMMC error code */
#define ERR_HS200_NOT_SUPPORTED     (1001)
#define ERR_HS200_BUS_WIDTH_ERR     (1002)
#define ERR_TUNING_BUS_WIDTH_ERR    (1003)
#define ERR_TUNING_ERR              (1004)
#define ERR_DDR_NOT_SUPPORTED       (1005)
#define ERR_EMMC_BUSY               (1006)
#define ERR_NUM_ERR                 (1007)

/*
 * @brief MMC CSD register definition.
 */
typedef struct
{
    uint32_t ECC                : 2;    /*!< ECC code                                   */
    uint32_t FILE_FORMAT        : 2;    /*!< file format                                */  
    uint32_t TMP_WRITE_PROTECT  : 1;    /*!< temporary write protection                 */  
    uint32_t PERM_WRITE_PROTECT : 1;    /*!< permanent write protection                 */  
    uint32_t COPY               : 1;    /*!< copy flag                                  */  
    uint32_t FILE_FORMAT_GRP    : 1;    /*!< file format group                          */  
    uint32_t CONTENT_PROT_APP   : 1;    /*!< content protection application             */  
    uint32_t rsv_0              : 4;
    uint32_t WRITE_BL_PARTIAL   : 1;    /*!< partial blocks for write allowed           */  
    uint32_t WRITE_BL_LEN       : 4;    /*!< max. write data block length               */  
    uint32_t R2W_FACTOR         : 3;    /*!< write speed factor                         */  
    uint32_t DEFAULT_ECC        : 2;
    uint32_t WP_GRP_ENABLE      : 1;    /*!< write protect group enable                 */  
    uint32_t WP_GRP_SIZE        : 5;    /*!< write protect group size                   */  
    uint32_t ERASE_GRP_MULT_L   : 3;
    
    uint32_t ERASE_GRP_MULT_H   : 2;    /*!< Erase group size multiplier                */  
    uint32_t ERASE_GRP_SIZE     : 5;    /*!< Erase group size                           */
    uint32_t C_SIZE_MULT        : 3;    /*!< Device size multiplier                     */
    uint32_t VDD_W_CURR_MAX     : 3;    /*!< Max. write current @ VDD max               */
    uint32_t VDD_W_CURR_MIN     : 3;    /*!< Max. write current @ VDD min               */
    uint32_t VDD_R_CURR_MAX     : 3;    /*!< Max. read current @ VDD max                */
    uint32_t VDD_R_CURR_MIN     : 3;    /*!< Max. read current @ VDD min                */
    uint32_t C_SIZE_L           : 10;
    
    uint32_t C_SIZE_H           : 2;    /*!< device size. 12-bit                        */  
    uint32_t rsv_1              : 2;
    uint32_t DSR_IMP            : 1;    /*!< DSR implemented                            */
    uint32_t READ_BLK_MISALIGN  : 1;    /*!< read  block misalignment                   */
    uint32_t WRITE_BLK_MISALIGN : 1;    /*!< write block misalignment                   */
    uint32_t READ_BL_PARTIAL    : 1;    /*!< partial blocks for read allowed            */
    uint32_t READ_BL_LEN        : 4;    /*!< max. read data block length                */
    uint32_t CCC                : 12;   /*!< crad command classes                       */
    uint32_t TRAN_SPEED         : 8;    /*!< max. data transfer rate                    */

    uint32_t NSAC               : 8;    /*!< data read access in CLK cycles(NSAC*100)   */
    uint32_t TAAC               : 8;    /*!< data read access time 1                    */  
    uint32_t rsv_2              : 2;
    uint32_t SPEC_VERS          : 4;    /*!< System specification version               */  
    uint32_t CSD_STRUCTURE      : 2;    /*!< CSD structure                              */  
    uint32_t rsv_3              : 8;
}MMC_CardCSDTypeDef;

/*
 * @brief MMC CID register definition.
 */
typedef struct
{
    uint8_t  ManufactDate;         /*!< Manufacturing Date    */
    uint8_t  ProductSN_A;          /*!< Product Serial Number */
    uint16_t ProductSN_B;          /*!< Product Serial Number */
    uint8_t  ProductSN_C;          /*!< Product Serial Number */
    uint8_t  ProductRevision;      /*!< Product Revision      */
    uint8_t  ProductName[6];       /*!< Product Name          */
    uint8_t  OEM_ApplicationID;    /*!< OEM/Application ID    */
    uint8_t  BGA;                  /*!< Device/BGA            */
    uint8_t  ManufacturerID;       /*!< Manufacturer ID       */
    uint8_t  rsv_0;
}MMC_CardCIDTypeDef;

/*
 * @brief Extended CSD register definition.
 */
typedef struct
{
    uint32_t SEC_COUNT;         /*!< Sector Count                */ 
    uint8_t  DEVICE_TYPE;       /*!< Device type                 */ 
    uint8_t  EXT_CSD_REV;       /*!< Extended CSD revision       */ 
    uint8_t  HS_TIMING;         /*!< High-speed interface timing */ 
    uint8_t  BUS_WIDTH;         /*!< Bus width mode              */ 
}MMC_CardExCSDTypeDef;

/** 
  * @brief  MMC Card Information Structure definition
  */ 
typedef struct
{
    uint32_t CardType;                     /*!< Specifies the card Type                */

    uint32_t Class;                        /*!< Specifies the class of the card class  */

    uint32_t MemoryCapacity;               /*!< Specifies Memory Capacity in KBytes    */

    uint32_t Revision;                     /*!< Specifies the Revision                 */
}MMC_CardInfoTypeDef;

/*
 * @brief  eMMC handle Structure definition
 */
typedef struct
{
    struct_SD_t            *SDx;             /*!< SD registers base address      */

    struct_MMCInit_t        Init;            /*!< SD communication parameters    */

    MMC_CardInfoTypeDef     CardInfo;        /*!< MMC Card information            */

    MMC_CardCIDTypeDef     *CIDInfo;         /*!< CID information          */
    MMC_CardCSDTypeDef     *CSDInfo;         /*!< CSD information          */
    MMC_CardExCSDTypeDef    ExCSDInfo;       /*!< Extended CSD information */

    uint32_t               CSD[4];           /*!< SD card CSD register */
    uint32_t               CID[4];           /*!< SD card CID register */
    uint32_t               OCR;              /*!< SD card OCR register */
    uint32_t               RCA;              /*!< SD card RCA register */

    volatile uint32_t      eMMCStatus;       /*!< SD card status */
    volatile uint32_t      AddrAlign;        /*!< SDMA address align */
}MMC_HandleTypeDef;


/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/

/* eMMC_Init */
uint32_t eMMC_Init(MMC_HandleTypeDef *hmmc);
/* eMMC_BusWidth_Select */
uint32_t eMMC_BusWidth_Select(MMC_HandleTypeDef *hmmc, uint32_t fu32_BusWidth);
/*eMMC_Switch_HS200_Mode  */
uint32_t eMMC_Switch_HS200_Mode(MMC_HandleTypeDef *hmmc);
/* eMMC_Switch_DDR_Mode */
uint32_t eMMC_Switch_DDR_Mode(MMC_HandleTypeDef *hmmc, uint32_t fu32_DDRBusWidth);
/* eMMC_Execute_Tuning_Sequence */
uint32_t eMMC_Execute_Tuning_Sequence(MMC_HandleTypeDef *hmmc);
/* eMMC_ClockDiv_Updata */
void eMMC_ClockDiv_Updata(MMC_HandleTypeDef *hmmc, uint8_t fu8_ClockDiv);

/* Read/Write Blocks */
uint32_t eMMC_ReadBolcks(MMC_HandleTypeDef *hmmc, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);
uint32_t eMMC_WriteBolcks(MMC_HandleTypeDef *hmmc, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);

/* Read/Write Blocks use SDMA */
uint32_t eMMC_ReadBolcks_SDMA(MMC_HandleTypeDef *hmmc, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);
uint32_t eMMC_WriteBolcks_SDMA(MMC_HandleTypeDef *hmmc, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);

/* Read/Write Blocks use SDMA with interrupt */
uint32_t eMMC_ReadBolcks_SDMA_IT(MMC_HandleTypeDef *hmmc, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);
uint32_t eMMC_WriteBolcks_SDMA_IT(MMC_HandleTypeDef *hmmc, uint32_t *fp_Data, uint32_t fu32_BlockAddr, uint16_t fu16_BlockNum);

/* eMMC_IRQHandler */
void eMMC_IRQHandler(MMC_HandleTypeDef *hmmc);

#endif
