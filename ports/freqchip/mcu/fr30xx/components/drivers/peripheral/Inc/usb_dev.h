/*
  ******************************************************************************
  * @file    usb_dev.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file for usb_dev.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __USB_DEV_H__
#define __USB_DEV_H__

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

/* Build the returned data */
typedef struct 
{
    uint16_t RequestLength;
    uint8_t *DataBuffer;
    uint32_t DataLength;
}usb_ReturnData_t;

/* USB Device descriptors structure */
typedef struct
{
    uint8_t  *DeviceDescriptor;
    uint8_t  *ConfigurationDescriptor;
    uint8_t  *InterfaceStrDescriptor;
    uint8_t  *EndpointDescriptor;

    uint8_t  *stringManufacture;
    uint8_t  *stringProduct;
    uint8_t  *stringSerialNumber;
    uint8_t  *stringLanuageID;
    uint8_t  *stringOS;    // Extended Compat ID OS Feature Descriptor
}usb_DescriptorsTypeDef_t;


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

/* bmRequestType bit mask */
#define REQUEST_DIRECTION_MASK   (0x80)
#define REQUEST_TYPE_MASK        (0x60)
#define REQUEST_RECIPIENT_MASK   (0x0F)
/* direction define */
#define DIRECTION_IN             (0x80)
#define DIRECTION_OUT            (0x00)
/* Type define */
#define TYPE_STANDARD            (0x00)
#define TYPE_CLASS               (0x20)
#define TYPE_VENDOR              (0x40)
/* Recipient define */
#define RECIPIENT_DEVICE         (0x00)
#define RECIPIENT_INTERFACE      (0x01)
#define RECIPIENT_ENDPOINT       (0x02)

/* standard request code */
#define REQUEST_GET_STATUS              (0)
#define REQUEST_CLEAR_FEATURE           (1)
#define REQUEST_SET_FEATURE             (3)
#define REQUEST_SET_ADDRESS             (5)
#define REQUEST_GET_DESCRIPTOR          (6)
#define REQUEST_SET_DESCRIPTOR          (7)
#define REQUEST_GET_CONFIGURATION       (8)
#define REQUEST_SET_CONFIGURATION       (9)
#define REQUEST_GET_INTERFACE           (10)
#define REQUEST_SET_INTERFACE           (11)
#define REQUEST_SYNCH_FRAME             (12)

/* USB2.0 Descriptor type and number */
#define DESCRIPTOR_DEVICE                       (1)
#define DESCRIPTOR_CONFIGURATION                (2)
#define DESCRIPTOR_STRING                       (3)
#define DESCRIPTOR_INTERFACE                    (4)
#define DESCRIPTOR_ENPOINT                      (5)
#define DESCRIPTOR_DEVICE_QUALIFIER             (6)
#define DESCRIPTOR_OTHER_SPEED_CONFIGURATION    (7)
#define DESCRIPTOR_INTERFACE_POWER              (8)
/* HID class standard descriptor */
#define DESCRIPTOR_HID                          (33)    /* 0x21 */
#define DESCRIPTOR_HID_REPORT                   (34)    /* 0x22 */
#define DESCRIPTOR_HID_PHYSICAL                 (35)    /* 0x23 */

/* USB3.2 Descriptor type and number */
#define DESCRIPTOR_OTG                          (9)
#define DESCRIPTOR_DEBUG                        (10)
#define DESCRIPTOR_INTERFACE_ASSOCIATION        (11)
#define DESCRIPTOR_BOS                          (15)
#define DESCRIPTOR_DEVICE_CAPABILITY            (16)
#define DESCRIPTOR_SUPERSPEED_USB_ENDPOINT_COMPANION                (48)
#define DESCRIPTOR_SUPERSPEEDPLUS_ISOCHRONOUS_ENDPOINT_COMPANION    (49)
/* string index */
#define STRING_MANUFACTURE              (1)
#define STRING_PRODUCT                  (2)
#define STRING_SERIAL_Number            (3)
#define STRING_LANUAGE_ID               (0)
#define STRING_OS                       (0xEE)


/* Exported Variate ----------------------------------------------------------*/
extern void (*Endpoint_0_StandardClassRequest_Handler)(usb_StandardRequest_t* pStandardRequest, usb_ReturnData_t* pReturnData);
extern void (*Endpoint_0_ClassRequest_Handler)(usb_StandardRequest_t* pStandardRequest, usb_ReturnData_t* pReturnData);
extern void (*Endpoint_0_VendorRequest_Handler)(usb_StandardRequest_t* pStandardRequest, usb_ReturnData_t* pReturnData);

extern void (*Endpoint_0_DataOut_Handler)(void);

extern void (*Endpoints_Handler)(uint8_t RxStatus, uint8_t TxStatus);

extern void (*USB_SOF_Handler)(void);
extern void (*USB_Reset_Handler)(void);
extern void (*USB_Resume_Handler)(void);
extern void (*USB_Suspend_Handler)(void);
extern void (*USB_Connect_Handler)(void);

extern void (*USB_InterfaceAlternateSet_callback)(uint8_t Interface);

/* Exported functions --------------------------------------------------------*/

/* usbdev_get_dev_desc */
void usbdev_get_dev_desc(uint8_t *Descriptor);

/* usbdev_get_config_desc */
void usbdev_get_config_desc(uint8_t *Descriptor);

/* string Descriptor */
void usbdev_get_string_Manufacture(uint8_t *Descriptor);
void usbdev_get_string_Product(uint8_t *Descriptor);
void usbdev_get_string_SerialNumber(uint8_t *Descriptor);
void usbdev_get_string_LanuageID(uint8_t *Descriptor);
void usbdev_get_string_OS(uint8_t *Descriptor);

uint16_t usbdev_get_device_status(void);
uint16_t usbdev_get_in_endpoints_status(uint32_t index);
uint16_t usbdev_get_out_endpoints_status(uint32_t index);
uint8_t usbdev_get_device_configuration_num(void);
uint8_t usbdev_get_interface_alternate_num(uint32_t index);


#endif
