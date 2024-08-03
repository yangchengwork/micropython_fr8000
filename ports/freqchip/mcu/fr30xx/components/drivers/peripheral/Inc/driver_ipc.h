/*
  ******************************************************************************
  * @file    driver_ipc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of IPC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_IPC_H__
#define __DRIVER_IPC_H__

#include "fr30xx.h"

/*IPC CTRL REG  0x00*/
typedef volatile union
{
   volatile uint32_t Word;
   struct
   {
      uint32_t CH0_IN_EN           : 1;     //Channel 0 input message enable
      uint32_t CH1_IN_EN           : 1;     //Channel 1 input message enable
	  uint32_t CH2_IN_EN           : 1;     //Channel 2 input message enable
	  uint32_t CH3_IN_EN           : 1;     //Channel 3 input message enable
	  uint32_t CH0_OUT_EN          : 1;     //Channel 0 output message enable
	  uint32_t CH1_OUT_EN          : 1;     //Channel 1 output message enable
	  uint32_t CH2_OUT_EN          : 1;     //Channel 2 output message enable
	  uint32_t CH3_OUT_EN          : 1;     //Channel 3 output message enable
	  uint32_t RSV                 : 24;	   
   } Bits;
} REG_IPC_CTRL_t;

/*IPC Message Pending REG  0x04*/
typedef volatile union
{
   volatile uint32_t Word;
   struct
   {
      uint32_t CH0_IN               : 1;//Channel 0 input message pending
      uint32_t CH1_IN               : 1;//Channel 1 input message pending
	  uint32_t CH2_IN               : 1;//Channel 2 input message pending
	  uint32_t CH3_IN               : 1;//Channel 3 input message pending
	  uint32_t CH0_OUT              : 1;//Channel 0 output message pending
	  uint32_t CH1_OUT              : 1;//Channel 1 output message pending
	  uint32_t CH2_OUT              : 1;//Channel 2 output message pending
	  uint32_t CH3_OUT              : 1;//Channel 3 output message pending
	  uint32_t RSV                  : 24;   
   } Bits;
} REG_IPC_MSG_PENDING_t;

/*IPC Message IN Clear REG  0x28*/
typedef volatile struct
{
    uint32_t CH0_IN                 : 1;//write 1 to clear Channel 0 input message interrupt
    uint32_t CH1_IN                 : 1;//write 1 to clear Channel 1 input message interrupt
    uint32_t CH2_IN                 : 1;//write 1 to clear Channel 2 input message interrupt
    uint32_t CH3_IN                 : 1;//write 1 to clear Channel 3 input message interrupt
    uint32_t RSV                    : 28;   
} REG_IPC_MSG_CLR_t;

/*IPC ISR Interrupt Enable REG  0x2C*/
typedef volatile union
{
    uint32_t Word;
    struct {
        uint32_t CH0_IN             : 1;//Channel 0 input enable
        uint32_t CH1_IN             : 1;//Channel 1 input enable
        uint32_t CH2_IN             : 1;//Channel 2 input enable
        uint32_t CH3_IN             : 1;//Channel 3 input enable
        uint32_t CH0_OUT            : 1;//Channel 0 output enable
        uint32_t CH1_OUT            : 1;//Channel 1 output enable
        uint32_t CH2_OUT            : 1;//Channel 2 output enable
        uint32_t CH3_OUT            : 1;//Channel 3 output enable
        uint32_t RSV1               : 24;
    } Bits;
} REG_IPC_ISR_EN_t;

/*IPC MSG Interrupt Status REG  0x30*/
typedef volatile union
{
    uint32_t Word;
    struct {
        uint32_t CH0_IN             : 1;//Channel 0 input interrupt status
        uint32_t CH1_IN             : 1;//Channel 1 input interrupt status
        uint32_t CH2_IN             : 1;//Channel 2 input interrupt status
        uint32_t CH3_IN             : 1;//Channel 3 input interrupt status
        uint32_t CH0_OUT            : 1;//Channel 0 output interrupt status
        uint32_t CH1_OUT            : 1;//Channel 1 output interrupt status
        uint32_t CH2_OUT            : 1;//Channel 2 output interrupt status
        uint32_t CH3_OUT            : 1;//Channel 3 output interrupt status
        uint32_t RSV1               : 24;
    } Bits;
} REG_IPC_ISR_STA_t;

/*IPC MSG Interrupt Raw Status REG  0x34*/
typedef volatile union
{
    uint32_t Word;
    struct {
        uint32_t CH0_IN             : 1;//Channel 0 input raw interrupt status
        uint32_t CH1_IN             : 1;//Channel 1 input raw interrupt status
        uint32_t CH2_IN             : 1;//Channel 2 input raw interrupt status
        uint32_t CH3_IN             : 1;//Channel 3 input raw interrupt status
        uint32_t CH0_OUT            : 1;//Channel 0 output raw interrupt status
        uint32_t CH1_OUT            : 1;//Channel 1 output raw interrupt status
        uint32_t CH2_OUT            : 1;//Channel 2 output raw interrupt status
        uint32_t CH3_OUT            : 1;//Channel 3 output raw interrupt status
        uint32_t RSV1               : 24;
    } Bits;
} REG_IPC_ISR_RAW_STA_t;

typedef struct 
{
    volatile REG_IPC_CTRL_t          IPC_CTRL;                 /* Offset 0x00 */
    volatile REG_IPC_MSG_PENDING_t   IPC_PENDING;              /* Offset 0x04 */
	volatile uint32_t                IPC_MSG_IN0;              /* Offset 0x08 */
	volatile uint32_t                IPC_MSG_IN1;              /* Offset 0x0C */
	volatile uint32_t                IPC_MSG_IN2;              /* Offset 0x10 */
	volatile uint32_t                IPC_MSG_IN3;              /* Offset 0x14 */
	volatile uint32_t                IPC_MSG_OUT0;             /* Offset 0x18 */	
    volatile uint32_t                IPC_MSG_OUT1;             /* Offset 0x1C */
	volatile uint32_t                IPC_MSG_OUT2;             /* Offset 0x20 */
	volatile uint32_t                IPC_MSG_OUT3;             /* Offset 0x24 */
    volatile REG_IPC_MSG_CLR_t       IPC_MSG_CLR;              /* Offset 0x28 */
    volatile REG_IPC_ISR_EN_t        IPC_ISR_EN;               /* Offset 0x2C */
    volatile REG_IPC_ISR_STA_t       IPC_ISR_STA;              /* Offset 0x30 */
    volatile REG_IPC_ISR_RAW_STA_t   IPC_ISR_RAW_STA;          /* Offset 0x34 */
}struct_IPC_t;

#define IPC_MCU         ((struct_IPC_t *)IPC_BASE)
#define IPC_DSP         ((struct_IPC_t *)DSP_IPC_BASE)

#define IPC_INT_STATUS_CH0_IN       (1<<0)
#define IPC_INT_STATUS_CH1_IN       (1<<1)
#define IPC_INT_STATUS_CH2_IN       (1<<2)
#define IPC_INT_STATUS_CH3_IN       (1<<3)
#define IPC_INT_STATUS_CH0_OUT      (1<<4)
#define IPC_INT_STATUS_CH1_OUT      (1<<5)
#define IPC_INT_STATUS_CH2_OUT      (1<<6)
#define IPC_INT_STATUS_CH3_OUT      (1<<7)

typedef enum{
	IPC_CH_0        = (1<<0),
	IPC_CH_1        = (1<<1),
	IPC_CH_2        = (1<<2),
    IPC_CH_3        = (1<<3),
}enum_IPC_Chl_Sel_t;

typedef struct __IPC_HandleTypeDef
{
    struct_IPC_t *IPCx;
    
    uint8_t TxEnableChannels;
    uint8_t RxEnableChannels;
    
    uint8_t TxOngoingChannels;
    
    void (*TxCallback)(struct __IPC_HandleTypeDef *hipc, enum_IPC_Chl_Sel_t ch);                /*!< Tx Callback */
    void (*RxCallback)(struct __IPC_HandleTypeDef *hipc, enum_IPC_Chl_Sel_t ch, uint32_t msg);  /*!< Rx Callback */

}IPC_HandleTypeDef;

void ipc_IRQHandler(IPC_HandleTypeDef *hipc);

void ipc_init(IPC_HandleTypeDef *hipc);
void ipc_msg_send(IPC_HandleTypeDef *hipc, enum_IPC_Chl_Sel_t ch, uint32_t msg);

#endif
