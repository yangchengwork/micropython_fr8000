/*
  ******************************************************************************
  * @file    usbh_mass_storage.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file for usbh_mass_storage.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __USBH_MASS_STORAGE_H__
#define __USBH_MASS_STORAGE_H__

#include "fr30xx.h"

/* Class communication status */
#define CLASS_COMM_IDLE                         (0)
#define CLASS_COMM_GET_MAX_LUN                  (1)
#define CLASS_COMM_SCSI_INQUIRY                 (2)
#define CLASS_COMM_SCSI_READ_FORMAT_CAPACITY    (3)
#define CLASS_COMM_SCSI_READ_CAPACITY           (4)
#define CLASS_COMM_SCSI_MODE_SENSE6             (5)
#define CLASS_COMM_SCSI_WAIT_READ_WRITE         (6)
#define CLASS_COMM_SCSI_TEST_UNIT_READY         (7)
#define CLASS_COMM_SCSI_READ                    (8)
#define CLASS_COMM_SCSI_WRITE                   (9)

/* class request data status */
#define CLASS_DATA_NONE       (0)
#define CLASS_DATA_CHECK      (1)
#define CLASS_DATA_READY      (2)
#define CLASS_DATA_WITHOUT    (3)
/* send status */
#define SCSI_PACKET_STATUS_IDLE         (0)
#define SCSI_PACKET_STATUS_SUCCEED      (1)
#define SCSI_PACKET_STATUS_FAIL         (2)
#define SCSI_PACKET_STATUS_NAK_LIMIT    (3)

/* mass storage device max lun */
#define SUPPORT_MASS_STORAGE_MAX_LUN    (1)

/* Class error code */
#define CLASS_ERROR_CODE_GET_MAX_LUN_ERR                       (ERROR_CODE_CLASS_BASE + 0)
#define CLASS_ERROR_CODE_OVER_MAX_LUN                          (ERROR_CODE_CLASS_BASE + 1)
#define CLASS_ERROR_CODE_SCSI_INQURIY_ERR                      (ERROR_CODE_CLASS_BASE + 2)
#define CLASS_ERROR_CODE_SCSI_INQURIY_CSW_ERR                  (ERROR_CODE_CLASS_BASE + 3)
#define CLASS_ERROR_CODE_SCSI_READ_FORMAT_CAPACITIES_ERR       (ERROR_CODE_CLASS_BASE + 4)
#define CLASS_ERROR_CODE_SCSI_READ_FORMAT_CAPACITIESCSW_ERR    (ERROR_CODE_CLASS_BASE + 5)
#define CLASS_ERROR_CODE_SCSI_READ_CAPACITIES_ERR              (ERROR_CODE_CLASS_BASE + 6)
#define CLASS_ERROR_CODE_SCSI_READ_CAPACITIESCSW_ERR           (ERROR_CODE_CLASS_BASE + 7)
#define CLASS_ERROR_CODE_SCSI_BLOCK_LENGTH_ERR                 (ERROR_CODE_CLASS_BASE + 8)
#define CLASS_ERROR_CODE_SCSI_MODE_SENSE6_ERR                  (ERROR_CODE_CLASS_BASE + 9)
#define CLASS_ERROR_CODE_SCSI_MODE_SENSE6CSW_ERR               (ERROR_CODE_CLASS_BASE + 10)
#define CLASS_ERROR_CODE_SCSI_READ_ERR                         (ERROR_CODE_CLASS_BASE + 11)
#define CLASS_ERROR_CODE_SCSI_READCSW_ERR                      (ERROR_CODE_CLASS_BASE + 12)

/* scsi status */
#define SCSI_STATUS_IDLE                           (0)
#define SCSI_STATUS_SEND_CMD                       (1)
#define SCSI_STATUS_WAIT_SEND_CMD_END              (2)
#define SCSI_STATUS_RECEIVE_DATA                   (3)
#define SCSI_STATUS_WAIT_RECEIVE_DATA_END          (4)
#define SCSI_STATUS_RECEIVE_STATUS                 (5)
#define SCSI_STATUS_WAIT_RECEIVE_STATUS_END        (6)

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

/* private CBW param */
typedef struct 
{
    uint8_t   *CBW_Ready;
    usb_CBW_t *CBW;
    uint8_t   *reply_data;
    uint16_t   reply_length;
    uint8_t    CBW_length;
    uint16_t   CBW_count;
}CBW_Param_t;
/* private CSW param */
typedef struct 
{
    usb_CSW_t *CSW;
    uint8_t    CSW_reply_length;
    uint8_t    CSW_count;
}CSW_Param_t;


/* CDB inquiry */
typedef struct 
{
    uint8_t OperationCode;
    uint8_t EVPD;
    uint8_t PageCode;
    uint8_t RSV;
    uint8_t AllocationLength;
    uint8_t Control;
}usb_CDB_inquiry_t;
/* standard inquiry data */
typedef struct 
{
    uint8_t PeripheralQualifier;
    uint8_t RMB;
    uint8_t Version;
    uint8_t ReponseDataForma;
    uint8_t AppendDataLength;
    uint8_t RSV[3];
    uint8_t VenderInfo[8];
    uint8_t ProductInfo[16];
    uint8_t ProducetVerInfo[4];
}usb_inquiry_data_t;


/* CDB read format capacities */
typedef struct 
{
    uint8_t OperationCode;
    uint8_t RSV[6];
    uint8_t AllocationLength_MSB;
    uint8_t AllocationLength_LSB;
    uint8_t Control;
}usb_CDB_read_format_capacities_t;
/* Current/Maximum Capacity Descriptor */
typedef struct 
{
    uint8_t Number_of_Blocks[4];
    uint8_t DescripterCode;
    uint8_t Blcok_Length[3];
}usb_capacity_descriptor_data_t;
/* standard inquiry data */
typedef struct 
{
    uint8_t RSV[3];
    uint8_t CapacityListLength;
    usb_capacity_descriptor_data_t capacity_descriptor[7];
}usb_read_format_capacities_data_t;


/* CDB read format capacities */
typedef struct 
{
    uint8_t  OperationCode;
    uint8_t  RelAdr;
    uint32_t LogicalBlockAddress;
    uint32_t Control;
    uint32_t RSV[2];
}usb_CDB_read_capacities_t;
/* read capacity data */
typedef struct 
{
    uint8_t  u8_Last_LogicalBlockAddress[4];
    uint8_t  u8_Blcok_Length[4];
    uint32_t u32_Last_LogicalBlockAddress;
    uint32_t u32_Blcok_Length;
    uint32_t Device_Capacity;
}usb_read_capacity_data_t;


/* CDB mode sense6 */
typedef struct 
{
    uint8_t  OperationCode;
    uint8_t  DisableBlockDesc;
    uint8_t  PageAndSubpageCode;
    uint8_t  AllocationLength_MSB;
    uint8_t  AllocationLength_LSB;
    uint8_t  Control;
    uint8_t  RSV[2];
    uint32_t PAD[2];
}usb_CDB_mode_sense6_t;
/* mode sense6 */
typedef struct 
{
    uint8_t  ModeDataLength;
    uint8_t  MediumType;
    uint8_t  WriteProtect;
    uint8_t  BlcokDescLength;
    uint32_t PAD[3];
}usb_mode_sense6_data_t;


/* CDB read(10) */
typedef struct 
{
    uint8_t  OperationCode;
    uint8_t  RelAdr;
    uint8_t  LogicalBlockAddress[4];
    uint8_t  RSV0;
    uint8_t  TransferLength[2];
    uint8_t  RSV1[3];
    uint32_t PAD;
}usb_CDB_read_t;


/* CDB TEST UNIT READY */
typedef struct 
{
    uint32_t OperationCode;
    uint32_t Control;
    uint32_t PAD[2];
}usb_CDB_test_unit_ready_t;


/* Exported Variables --------------------------------------------------------*/
extern usb_inquiry_data_t inquiry_data;
extern usb_read_format_capacities_data_t read_format_capacities_data;
extern usb_read_capacity_data_t read_capacity_data;
extern usb_mode_sense6_data_t mode_sense6_data;

/* Exported functions --------------------------------------------------------*/

/* usbh_mass_storage_init */
void usbh_mass_storage_init(void);

/* usbh_msu_get_max_lun */
uint32_t usbh_msu_get_max_lun(void);

/* usbh_msu_get_capacity */
uint32_t usbh_msu_get_capacity(void);

/* usbh_msu_read_block */
int32_t usbh_msu_read_block(uint32_t LogicalBlockAddress, uint16_t TransferBlocks, uint8_t *Buffer);

/* usbh_msu_get_busy_status */
int32_t usbh_msu_get_busy_status(void);

/* usbh_msu_test_unit_ready */
int32_t usbh_msu_test_unit_ready(void);

#endif
