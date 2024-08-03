/*
  ******************************************************************************
  * @file    usb_mass_storage.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file for usb_mass_storage.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __USB_MASS_STORAGE_H__
#define __USB_MASS_STORAGE_H__

#include "fr30xx.h"

/* mass storage device max lun */
#define FREQCHIP_MASS_STORAGE_MAX_LUN   (1)

/* Bulk Only Transport Calss Request descriptor */
#define BULK_ONLY_MASS_STORAGE_RESET    (0xFF)
#define GET_MAX_LUN                     (0xFE)

#define CBW_SIGNATURE    (0x43425355)
#define CSW_SIGNATURE    (0x53425355)

/* UFI SCSI Command */
#define SCSI_CMD_FormatUnit            (0x04)
#define SCSI_CMD_Inquiry               (0x12)
#define SCSI_CMD_ModeSENSE6            (0x1A)
#define SCSI_CMD_Start_Stop            (0x1B)
#define SCSI_CMD_ModeSelect            (0x55)
#define SCSI_CMD_ModeSense             (0x5A)
#define SCSI_CMD_Prevent               (0x1E)
#define SCSI_CMD_Read10                (0x28)
#define SCSI_CMD_Read12                (0xA8)
#define SCSI_CMD_ReadCapacity          (0x25)
#define SCSI_CMD_ReadForamtCapacity    (0x23)
#define SCSI_CMD_RequestSense          (0x03)
#define SCSI_CMD_RexeroUnit            (0x01)
#define SCSI_CMD_Seek                  (0x2B)
#define SCSI_CMD_SendDianostic         (0x1D)
#define SCSI_CMD_TestUnitReady         (0x00)
#define SCSI_CMD_Verify                (0x2F)
#define SCSI_CMD_Write10               (0x2A)
#define SCSI_CMD_Write12               (0xAA)
#define SCSI_CMD_WriteAndVerify        (0x2E)

/* CBW (Command Block Wrapper) */
typedef struct 
{
    uint32_t dCBWSignature;    // 0x43425355
    uint32_t dCBWTag;
    uint32_t dCBWDataTransferLength;
    uint8_t  bmCBWFlags;
    uint8_t  bCBWLUN;
    uint8_t  bCBWCBLength;
    uint8_t  CBWCB[16];
}usb_CBW_t;

/* CSW (Command Status Wrapper) */
typedef struct 
{
    uint32_t dCSWSignature;    // 0x53425355
    uint32_t dCSWTag;
    uint32_t dCSWDataResidue;
    uint8_t  bmCSWStatus;
}usb_CSW_t;

/* Exported inline functions --------------------------------------------------------*/

/* usb_mass_storage_init */
void usb_mass_storage_init(void);

#endif
