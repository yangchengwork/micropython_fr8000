/*
  ******************************************************************************
  * @file    usb_host.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file for usb_host.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __USB_HOST_H__
#define __USB_HOST_H__

#include "fr30xx.h"

#define ENDPOINT0_MAX    (64)

#define ENDPOINT_0_MASK    (0x01)
#define ENDPOINT_1_MASK    (0x02)
#define ENDPOINT_2_MASK    (0x04)
#define ENDPOINT_3_MASK    (0x08)
#define ENDPOINT_4_MASK    (0x10)
#define ENDPOINT_5_MASK    (0x20)
#define ENDPOINT_6_MASK    (0x40)
#define ENDPOINT_7_MASK    (0x80)

typedef struct 
{
    uint8_t *descriptor_Ready;
    uint8_t *descriptor_request;
    uint8_t *descriptor_point;
    uint8_t  descriptor_length;
    uint8_t  descriptor_count;
}descriptor_Param_t;

/* USB Device standard request */
typedef struct 
{
    uint8_t bmRequestType;    // Characteristics of request
    /*
       D7: Data transfer direction
            0 : Host-to-device 
            1 : Device-to-host
       D6...5: Type
            0 : Standard 
            1 : Class 
            2 : Vendor 
            3 : Reserved
       D4...0: Recipient
            0 : Device 
            1 : Interface 
            2 : Endpoint 
            3 : Other
            4 ~ 31 : Reserved
    */
    uint8_t bRequest;         // Specific request
    uint8_t wValue[2];        // Word-sized field that varies according to request
    uint8_t wIndex[2];        // Word-sized field that varies according to request
    uint8_t wLength[2];       // Number of bytes to transfer if there is a Data stage
}usb_StandardRequest_t;

/* descriptor format(Deivce) */
typedef struct 
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t  iManufacturer;
    uint8_t  iProduct;
    uint8_t  iSerialnumber;
    uint8_t  bNumConfigurations;
}descriptor_Dvc;

/* descriptor format(Configuration) */
typedef struct 
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t wTotalLength;
    uint8_t  bNumInterfaces;
    uint8_t  bConfigurationValue;
    uint8_t  iConfiguration;
    uint8_t  bmAttributes;
    uint8_t  bMaxPower;
}descriptor_Cfg;

/* descriptor format(Interface) */
typedef struct 
{
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iConfiguration;
}descriptor_Ifc;

/* descriptor format(Endpoint) */
typedef struct 
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t  bInterval;
}descriptor_Ep;

#define USB_HOST_MAX_IFC_NUM    (5)

#define USB_STANDARD_REQUEST_LENGTH    (8)

/* descriptor type */
#define DESCRIPTOR_TYPE_DEVICE           (0x01)
#define DESCRIPTOR_TYPE_CONFIGURATION    (0x02)
#define DESCRIPTOR_TYPE_STRING           (0x03)
#define DESCRIPTOR_TYPE_INTERFACE        (0x04)
#define DESCRIPTOR_TYPE_ENDPOINT         (0x05)

/* Class decide */
#define DEVICE_CLASS_INFO_IN_IFC           (0x00)
#define DEVICE_MASS_STORAGE_CLASS          (0x08)
#define DEVICE_SCSI_TRANSPARENT_CMD_SET    (0x06)
#define DEVICE_BULK_ONLY_TRANSPORT         (0x50)

#define END0_IN_STATUS_PACKET_INDEX_SET_ADDR      (1)
#define END0_IN_STATUS_PACKET_INDEX_SET_CONFIG    (2)

/* enum descriptor status */
#define DEVICE_DESC_NONE       (0)
#define DEVICE_DESC_CHECK      (1)
#define DEVICE_DESC_READY      (2)
#define DEVICE_DESC_WITHOUT    (3)

/* send status */
#define SEND_STATUS_IDLE       (0)
#define SEND_STATUS_SUCCEED    (1)
#define SEND_STATUS_FAIL       (2)
#define SEND_STATUS_NAK_LIMIT  (3)
/* receive status */
#define RECEIVE_STATUS_IDLE          (0)
#define RECEIVE_STATUS_SUCCEED       (1)
#define RECEIVE_STATUS_FAIL          (2)
#define RECEIVE_STATUS_NAK_LIMIT     (3)

/* Error code */
#define ERROR_CODE_NO_ERR                          (0)
#define ERROR_CODE_DEVICE_NO_RESPONSE              (1)
#define ERROR_CODE_RECEIVE_DESC_DVC_FAIL           (2)
#define ERROR_CODE_RECEIVE_DESC_DVC_TIMEOUT        (3)
#define ERROR_CODE_RECEIVE_DESC_DVC_ERROR          (4)
#define ERROR_CODE_SET_ADDR_FAIL                   (5)
#define ERROR_CODE_SET_ADDR_TIMEOUT                (6)
#define ERROR_CODE_SET_ADDR_STATUS_ERR             (7)
#define ERROR_CODE_UNKNOWN_DEVICE                  (8)
#define ERROR_CODE_UNKNOWN_STORAGE_DEVICE          (9)
#define ERROR_CODE_RECEIVE_DESC_CFG_FAIL           (10)
#define ERROR_CODE_RECEIVE_DESC_CFG_ERROR          (11)
#define ERROR_CODE_RECEIVE_DESC_LENGTH_ERROR       (12)
#define ERROR_CODE_SET_CONFIG_FAIL                 (13)
#define ERROR_CODE_SET_CONFIG_STATUS_ERR           (14)
#define ERROR_CODE_CLASS_BASE                      (15)

/* Connect status */
#define DEVICE_IDLE                                (0)
#define DEVICE_CONNECT                             (1)
#define DEVICE_CONNECT_RETRY                       (2)
#define DEVICE_WAIT_A                              (3)
#define DEVICE_WAIT_B                              (4)
#define DEVICE_TX_REQUEST_GET_DESC_DVC             (5)
#define DEVICE_WAIT_TX_REQUEST_GET_DESC_DVC_END    (6)
#define DEVICE_RX_DESC_DVC_RESPONSE                (7)
#define DEVICE_WAIT_RX_DESC_DVC_RESPONSE_END       (8)
#define DEVICE_SECOND_RESET                        (9)
#define DEVICE_SET_ADDRESS                         (10)
#define DEVICE_WAIT_SEND_END                       (11)
#define DEVICE_RX_STATUS_PACKET                    (12)
#define DEVICE_ENUM                                (13)
#define DEVICE_SET_CONFIG                          (14)
#define DEVICE_CLASS_HANDLE                        (15)
#define DEVICE_DISCONNECT                          (16)

/* enum status */
#define ENUM_STATUS_IDLE                           (0)
#define ENUM_STATUS_REQUEST_DESC                   (1)
#define ENUM_STATUS_WAIT_REQUEST_DESC_END          (2)
#define ENUM_STATUS_RX_REPLY_DESC                  (3)
#define ENUM_STATUS_WAIT_RX_REPLY_DESC_END         (4)
#define ENUM_STATUS_OUT_STATUS                     (5)
#define ENUM_STATUS_WAIT_OUT_STATUS_END            (6)

/* USB host find device class  */
#define DEVICE_CLASS_UNKNOWN                       (0)
#define DEVICE_CLASS_STORAGE_DEVICE                (20)
#define DEVICE_CLASS_HID_DEVICE                    (21)
#define DEVICE_CLASS_CDC_DEVICE                    (22)
#define DEVICE_CLASS_OTHER_DEVICE                  (23)

/* Exported Variate ----------------------------------------------------------*/
extern void (*USBH_Resume_Handler)(void);
extern void (*USBH_Connect_Handler)(void);
extern void (*USBH_Disconnect_Handler)(void);
extern void (*USBH_Class_Handler)(void);
extern void (*Endpoints_Handler)(uint8_t RxStatus, uint8_t TxStatus);

extern uint8_t (*USB_Host_get_calss_desc)(void);

extern descriptor_Param_t desc_Param;

/* mass storage class */
extern descriptor_Ifc *Storage_Ifc;
extern descriptor_Ep  *Storage_IN_Endpoint;
extern descriptor_Ep  *Storage_OUT_Endpoint;

/* Exported functions --------------------------------------------------------*/

/* USB_Host_thread */
void USB_Host_thread(void);

/* USB_Host_get_descriptor */
static uint8_t USB_Host_get_descriptor(void);

/* USB_Host_get_error_code */
/* USB_Host_set_error_code */
uint32_t USB_Host_get_error_code(void);
void USB_Host_set_error_code(uint32_t fu32_Error_code);

/* USB_Host_get_connect_status */
/* USB_Host_set_connect_status */
uint32_t USB_Host_get_connect_status(void);
void USB_Host_set_connect_status(uint32_t fu32_ConnectStatus);

/* USB_Host_get_enum_status */
/* USB_Host_set_enum_status */
uint32_t USB_Host_get_enum_status(void);
void USB_Host_set_enum_status(uint32_t fu32_EnumStatus);

/* USB_Host_get_device_class */
uint32_t USB_Host_get_device_class(void);

/* get Manufacturer String length/content */
uint8_t USB_Host_get_Manufacturer_String_length(void);
void USB_Host_get_Manufacturer_String(uint8_t *fp_Buffer);

/* get Product String length/content */
uint8_t USB_Host_get_Product_String_length(void);
void USB_Host_get_Product_String(uint8_t *fp_Buffer);

/* get Serialnumber String length/content */
uint8_t USB_Host_get_Serialnumber_String_length(void);
void USB_Host_get_Serialnumber_String(uint8_t *fp_Buffer);

#endif
