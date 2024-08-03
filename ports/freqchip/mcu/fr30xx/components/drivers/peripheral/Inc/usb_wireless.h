/*
  ******************************************************************************
  * @file    usb_wireless.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file for usb_wireless.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __USB_WIRELESS_H__
#define __USB_WIRELESS_H__

#include "fr30xx.h"

#define HCI_ENDPOINT_DEBUG    (0)

#define wireless_malloc    malloc
#define wireless_free      free

#define HCI_TYPE_COMMAND_PACKET             (0x01)
#define HCI_TYPE_ACL_DATA_PACKET            (0x02)
#define HCI_TYPE_SYNCHRONOUS_DATA_PACKET    (0x03)
#define HCI_TYPE_EVENT_PACKET               (0x04)
#define HCI_TYPE_ISO_DATA_PACKET            (0x05)

#define HCI_EVENT_PACKET_MAX_LENGTH    (16)
#define HCI_ACLT_PACKET_MAX_LENGTH     (64)

#define HCI_EVENT_STATUS_IDLE    (0)
#define HCI_EVENT_STATUS_BUSY    (1)
#define HCI_ACLT_STATUS_IDLE     (0)
#define HCI_ACLT_STATUS_BUSY     (1)

/**
 * Double List structure
 */
struct fr_list_node
{
    struct fr_list_node *next;            /**< point to next node. */
    struct fr_list_node *prev;            /**< point to prev node. */
};
typedef struct fr_list_node fr_list_t;    /**< Type for lists. */

/* initialize a list */
static inline void fr_list_init(fr_list_t *l)
{
    l->next = l->prev = l;
}
/* insert a node after a list */
static inline void fr_list_insert_after(fr_list_t *l, fr_list_t *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}
/* insert a node before a list */
static inline void fr_list_insert_before(fr_list_t *l, fr_list_t *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}
/* rt_list_remove */
static inline void fr_list_remove(fr_list_t *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

typedef struct 
{
    fr_list_t list;

    uint16_t HCI_RxPacket_Type;
    uint16_t HCI_RxPacket_Count;
    uint16_t HCI_RxPacket_Length;
    uint16_t HCI_RxPacket_Residual;
    uint8_t  HCI_RxPacket_Data[];
}str_Wrieless_HCI_RxPacket_t;

typedef struct 
{
    volatile uint8_t  HCI_ACLT_Status;
             uint8_t  HCI_ACLT[1024];
    volatile uint16_t HCI_ACLT_Count;
    volatile uint16_t HCI_ACLT_Length;

    volatile uint8_t  HCI_Event_Status;
             uint8_t  HCI_Event[1024];
    volatile uint16_t HCI_Event_Count;
    volatile uint16_t HCI_Event_Length;

    fr_list_t HCI_RxPacket_list;

    str_Wrieless_HCI_RxPacket_t *Current_CMD_RxPacket;
    str_Wrieless_HCI_RxPacket_t *Current_ACL_RxPacket;
}str_Wrieless_HCI_Handle_t;



/* Exported inline functions --------------------------------------------------------*/

void usb_wireless_init(void);

void usb_wrieless_send_event(void);
void usb_wrieless_send_acl(void);

#endif
