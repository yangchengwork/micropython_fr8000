/*
  ******************************************************************************
  * @file    driver_uart.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   UART module driver.
  *          This file provides firmware functions to manage the 
  *          Universal Asynchronous Receiver/Transmitter (UART) peripheral
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "fr30xx.h"

/************************************************************************************
 * @fn      uart_IRQHandler
 *
 * @brief   Handle UART interrupt request.
 *
 * @param   huart: UART handle.
 */
__WEAK void uart_IRQHandler(UART_HandleTypeDef *huart)
{
    switch (__UART_INT_GET_ID(huart->UARTx))
    {
        case INT_INDEX_TXE: 
        {
            /* Data transit end */
            if (huart->u32_TxCount >= huart->u32_TxSize) 
            {
                __UART_INT_TXE_DISABLE(huart->UARTx);
                
                huart->b_TxBusy = false;
            }
            else 
            {
                /* UART_FIFO_ENABLE */
                if (__UART_IS_FIFO_Enable(huart)) 
                {
                    /* Until TxFIFO full */
                    while(!__UART_IS_TxFIFO_FULL(huart->UARTx))
                    {
                        huart->UARTx->DATA_DLL.DATA = huart->p_TxData[huart->u32_TxCount++];

                        /* Data transit end */
                        if (huart->u32_TxCount >= huart->u32_TxSize)
                        {
                            __UART_INT_TXE_DISABLE(huart->UARTx);
                            
                            huart->b_TxBusy = false;
                            
                            if (huart->TxCpltCallback != NULL) 
                            {
                                huart->TxCpltCallback(huart);
                            }
                            
                            break;
                        }
                    }
                }
                else 
                {
                    huart->UARTx->DATA_DLL.DATA = huart->p_TxData[huart->u32_TxCount++];
                }
            }
        }break;


        case INT_INDEX_RX: 
        case INT_INDEX_RX_TOUT:
        {
            /* Rx ready */
            while (huart->UARTx->LSR.LSR_BIT.DR)
            {
                huart->p_RxData[huart->u32_RxCount++] = huart->UARTx->DATA_DLL.DATA;
                
                /* Data receive end */
                if (huart->u32_RxCount >= huart->u32_RxSize)
                {
                    __UART_INT_RX_DISABLE(huart->UARTx);

                    huart->b_RxBusy = false;

                    if (huart->RxCpltCallback != NULL) 
                    {
                        huart->RxCpltCallback(huart);
                    }
                            
                    break;
                }
            }
        }break;

        default: break; 
    }
}

/************************************************************************************
 * @fn      uart_init
 *
 * @brief   Initialize the UART according to the specified parameters in the struct_UARTInit_t
 *
 * @param   huart: UART handle.
 */
bool uart_init(UART_HandleTypeDef *huart)
{
    /* Config Data Length */
    huart->UARTx->LCR.Bits.DLS  = huart->Init.DataLength;
    /* Config Stop Bits*/
    huart->UARTx->LCR.Bits.STOP = huart->Init.StopBits;
    /* Config Auto Flow */
    if(huart->Init.AUTO_FLOW)
    {
        __UART_AUTO_FLOW_CONTROL_ENABLE( huart->UARTx);
    }
    /* Config Parity */
    if (huart->Init.Parity != UART_PARITY_NONE) 
    {
        huart->UARTx->LCR.Bits.PEN = 1;

        switch (huart->Init.Parity)
        {
            case UART_PARITY_ODD:  huart->UARTx->LCR.Bits.SP = 0; huart->UARTx->LCR.Bits.EPS = 0; break;
            case UART_PARITY_EVEN: huart->UARTx->LCR.Bits.SP = 0; huart->UARTx->LCR.Bits.EPS = 1; break;
            case UART_PARITY_0:    huart->UARTx->LCR.Bits.SP = 1; huart->UARTx->LCR.Bits.EPS = 1; break;
            case UART_PARITY_1:    huart->UARTx->LCR.Bits.SP = 1; huart->UARTx->LCR.Bits.EPS = 0; break;

            default: break;
        }
    }
    else 
    {
        huart->UARTx->LCR.Bits.PEN = 0;
    }

    /* Config FIFO¡¢DMA¡¢RxFIF/TxFIFO threshold */
    huart->FCR_Shadow = huart->Init.FIFO_Mode | (huart->Init.FIFO_Mode << FCR_DMAM);

    huart->UARTx->FCR_IID.FCR = huart->FCR_Shadow;

    /* Config BaudRate */
    if(uart_config_baudRate(huart) != true)
    {
         return false;
    }
    else
    {
         return true;        
    }
}

/************************************************************************************
 * @fn      uart_transmit
 *
 * @brief   Send an amount of data in blocking mode.
 *
 * @param   huart: UART handle.
 * @param   fp_Data: Pointer to data buffer.
 * @param   fu32_Size: Amount of data to be sent.
 */
void uart_transmit(UART_HandleTypeDef *huart, uint8_t *fp_Data, uint32_t fu32_Size)
{
    /* UART_FIFO_ENABLE */
    if (__UART_IS_FIFO_Enable(huart))
    {
        while (fu32_Size--) 
        {
            /* TxFIFO FULL */
            while(!(huart->UARTx->USR.TFNF));
            /* Send data */
            huart->UARTx->DATA_DLL.DATA = *fp_Data++;
        }
    }
    else 
    {
        while (fu32_Size--) 
        {
            /* Tx not empty */
            while(!(huart->UARTx->LSR.LSR_BIT.THRE));
            /* Send data */
            huart->UARTx->DATA_DLL.DATA = *fp_Data++;
        }
    }
}

/************************************************************************************
 * @fn      uart_receive
 *
 * @brief   Receive an amount of data in blocking mode.
 *
 * @param   huart: UART handle.
 * @param   fp_Data: Pointer to data buffer.
 * @param   fu32_Size: Amount of data to be receive.
 */
void uart_receive(UART_HandleTypeDef *huart, uint8_t *fp_Data, uint32_t fu32_Size)
{
    while (fu32_Size--) 
    {
        /* Rx ready */
        while (!(huart->UARTx->LSR.LSR_BIT.DR));
        /* receive data */
        *fp_Data++ = huart->UARTx->DATA_DLL.DATA;
    }
}

/************************************************************************************
 * @fn      uart_transmit_IT
 *
 * @brief   Send an amount of data in interrupt mode.
 *
 * @param   huart: UART handle.
 * @param   fp_Data: Pointer to data buffer.
 * @param   fu32_Size: Amount of data to be sent.
 */
void uart_transmit_IT(UART_HandleTypeDef *huart, uint8_t *fp_Data, uint32_t fu32_Size)
{
    if (huart->b_TxBusy)
        return;

    huart->p_TxData    = fp_Data;
    huart->u32_TxCount = 0;
    huart->u32_TxSize  = fu32_Size;
    huart->b_TxBusy    = true;

    /* UART_FIFO_ENABLE */
    if (__UART_IS_FIFO_Enable(huart)) 
    {
        /* Tx empty interrupt and fifo enable */
        __UART_INT_TXE_ENABLE_FE(huart->UARTx);
    }
    else 
    {
        /* Tx empty interrupt and fifo disable */
        __UART_INT_TXE_ENABLE_FD(huart->UARTx);
    }
}

/************************************************************************************
 * @fn      uart_transmit_IT
 *
 * @brief   Receive an amount of data in interrupt mode.
 *
 * @param   huart: UART handle.
 * @param   fp_Data: Pointer to data buffer.
 * @param   fu32_Size: Amount of data to be receive.
 */
void uart_receive_IT(UART_HandleTypeDef *huart, uint8_t *fp_Data, uint32_t fu32_Size)
{
    if (huart->b_RxBusy)
        return;

    huart->p_RxData    = fp_Data;
    huart->u32_RxCount = 0;
    huart->u32_RxSize  = fu32_Size;
    huart->b_RxBusy    = true;

    /* data ready¡¢character timeout interrupt enable */
    __UART_INT_RX_ENABLE(huart->UARTx);
}

/************************************************************************************
 * @fn      uart_config_baudRate
 *
 * @brief   Config BaudRate
 *
 * @param   huart: UART handle.
 */
bool uart_config_baudRate(UART_HandleTypeDef *huart)
{
    uint32_t i;
    uint32_t lu32_UartClock;
    uint32_t lu32_Integer;
    uint64_t lu64_Fractional;
    uint16_t lu32_TempValue[2];
    
    lu32_UartClock = system_get_peripheral_clock(PER_CLK_UARTx);
    
    /* Calculate the integer part */
    lu32_Integer = lu32_UartClock / (16 * huart->Init.BaudRate);
    
    /* Calculate the fractional part */
    lu64_Fractional = lu32_UartClock % (16 * huart->Init.BaudRate);
    lu64_Fractional = (lu64_Fractional * 10000) / (16 * huart->Init.BaudRate);

    for (i = 0; i < 0x3F; i++)
    {
        lu32_TempValue[0] = (i * 10000) / 64;
        lu32_TempValue[1] = ((i + 1) * 10000) / 64;
        
        if (lu64_Fractional >= lu32_TempValue[0] && lu64_Fractional <= lu32_TempValue[1]) 
        {
            if (lu64_Fractional - lu32_TempValue[0] < lu32_TempValue[1] - lu64_Fractional) 
            {
                lu64_Fractional = i;
            }
            else 
            {
                lu64_Fractional = i + 1;
            }

            break;
        }
        else if (i == 0x3E)
        {
            lu64_Fractional = 0x3F;
        }
    }
    
    /* DLL DLH register access enable */
    __UART_DLL_DLH_ACCESS_ENABLE(huart->UARTx);

    if(!(__UART_IS_DLL_DLH_ACCESS(huart->UARTx)))
    {
        return false;  
    } 

    huart->UARTx->DATA_DLL.DLL =  lu32_Integer & 0xFF;
    huart->UARTx->IER_DLH.DLH  = (lu32_Integer >> 8) & 0xFF;
    huart->UARTx->DLF.DLF      =  lu64_Fractional;

    /* DLL DLH register access disable */
    __UART_DLL_DLH_ACCESS_DISABLE(huart->UARTx);
    return true;    
}




