/*
  ******************************************************************************
  * @file    usb_cdc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file for usb_cdc.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __USB_CDC_H__
#define __USB_CDC_H__

#include "fr30xx.h"

/*---------------------------------------------------------------------*/
/*  CDC definitions                                                    */
/*---------------------------------------------------------------------*/
#define CDC_SEND_ENCAPSULATED_COMMAND               0x00
#define CDC_GET_ENCAPSULATED_RESPONSE               0x01
#define CDC_SET_COMM_FEATURE                        0x02
#define CDC_GET_COMM_FEATURE                        0x03
#define CDC_CLEAR_COMM_FEATURE                      0x04
#define CDC_SET_LINE_CODING                         0x20
#define CDC_GET_LINE_CODING                         0x21
#define CDC_SET_CONTROL_LINE_STATE                  0x22
#define CDC_SEND_BREAK                              0x23

/* CDC line coding */
typedef struct
{
    uint32_t dwDTERate;      // Baud rate
    uint8_t  bCharFormat;    // Stop bits
             /* 
                0: 1   Stop bit 
                1: 1.5 Stop bit 
                2: 2   Stop bit 
             */
    uint8_t  bParityType;    // Parity
             /*
                0: None
                1: Odd
                2: Even
                3: Mark
                4: Space
             */
    uint8_t  bDataBits;      // Data bits
}USBD_CDC_LineCodingTypeDef;

/* usb_cdc_init */
void usb_cdc_init(void);

/* usb_cdc_serialReceive */
void usb_cdc_serialReceive(void);

#endif
