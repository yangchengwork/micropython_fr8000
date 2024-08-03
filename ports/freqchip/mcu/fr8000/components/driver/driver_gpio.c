/*
  ******************************************************************************
  * @file    driver_gpio.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   GPIO module driver.
  *          This file provides firmware functions to manage the 
  *          General Purpose Input/Output (GPIO) peripheral
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "driver_gpio.h"

/************************************************************************************
 * @fn      gpio_init
 *
 * @brief   Initializes the GPIOx peripheral according to the specified 
 *          parameters in the GPIO_Init
 *
 * @param   fe_GPIO: to select the GPIO peripheral.
 *          GPIO_Init: pointer to a GPIO_InitTypeDef structure that contains the
 *                     configuration information for the specified GPIO peripheral.
 */
void gpio_init(enum_GPIOx_t fe_GPIO, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t lu32_Position = 0;
    uint32_t lu32_Current_Pin;

    volatile uint32_t *GPIO_Pull_EN     = &system_regs->port_pull_enable;
    volatile uint32_t *GPIO_Pull_Select = &system_regs->port_pull_sel;
    volatile uint32_t *GPIO_FuncMux;
    
    volatile uint32_t *GPIO_OutputEN;
    volatile uint32_t *GPIO_EXTI_EN;
    volatile uint32_t *GPIO_EXTI_INT_EN;
    volatile uint32_t *GPIO_EXTI_TYPE;
    
    volatile uint32_t  GPIO_Offset;

    /* Select the group register */
    switch (fe_GPIO)
    {
        case GPIO_A: 
        {
            GPIO_Offset = 0;

            GPIO_FuncMux     = &system_regs->port_mux[0];
            GPIO_OutputEN    = &GPIO->PortA_OutputEN;
            GPIO_EXTI_EN     = &GPIO->EXTI_EN_0;
            GPIO_EXTI_INT_EN = &GPIO->EXTI_INT_EN_0;
            GPIO_EXTI_TYPE   = &GPIO->EXTI_TYPE0;
        }break;

        case GPIO_B: 
        {
            GPIO_Offset = 8;

            GPIO_FuncMux     = &system_regs->port_mux[1];
            GPIO_OutputEN    = &GPIO->PortB_OutputEN;
            GPIO_EXTI_EN     = &GPIO->EXTI_EN_0;
            GPIO_EXTI_INT_EN = &GPIO->EXTI_INT_EN_0;
            GPIO_EXTI_TYPE   = &GPIO->EXTI_TYPE0;
        }break;

        case GPIO_C: 
        {
            GPIO_Offset = 16;
            
            GPIO_FuncMux     = &system_regs->port_mux[2];
            GPIO_OutputEN    = &GPIO->PortC_OutputEN;
            GPIO_EXTI_EN     = &GPIO->EXTI_EN_0;
            GPIO_EXTI_INT_EN = &GPIO->EXTI_INT_EN_0;
            GPIO_EXTI_TYPE   = &GPIO->EXTI_TYPE1;
        }break;

        case GPIO_D: 
        {
            GPIO_Offset = 24;

            GPIO_FuncMux     = &system_regs->port_mux[3];
            GPIO_OutputEN    = &GPIO->PortD_OutputEN;
            GPIO_EXTI_EN     = &GPIO->EXTI_EN_0;
            GPIO_EXTI_INT_EN = &GPIO->EXTI_INT_EN_0;
            GPIO_EXTI_TYPE   = &GPIO->EXTI_TYPE1;
        }break;

        case GPIO_E:
        {
            GPIO_Offset = 0;

            GPIO_FuncMux     = (uint32_t *)(0x50000038);
            GPIO_OutputEN    = &GPIO->PortE_OutputEN;
            GPIO_EXTI_EN     = &GPIO->EXTI_EN_1;
            GPIO_EXTI_INT_EN = &GPIO->EXTI_INT_EN_1;
            GPIO_EXTI_TYPE   = &GPIO->EXTI_TYPE2;
        }break;

        default: break; 
    }

    /* Configure Select pins */
    while ((GPIO_Init->Pin) >> lu32_Position != 0) 
    {
        /* Get current pin position */
        lu32_Current_Pin = (GPIO_Init->Pin) & (1uL << lu32_Position);
        
        if (lu32_Current_Pin) 
        {
            switch (GPIO_Init->Mode)
            {
                case GPIO_MODE_INPUT:
                {
                    *GPIO_OutputEN |=  lu32_Current_Pin;
                    *GPIO_EXTI_EN  &= ~(lu32_Current_Pin << GPIO_Offset);
                }break;

                case GPIO_MODE_OUTPUT_PP:
                {
                    *GPIO_OutputEN &= ~lu32_Current_Pin;
                    *GPIO_EXTI_EN  &= ~(lu32_Current_Pin << GPIO_Offset);
                }break;

                case GPIO_MODE_AF_PP:
                {
                    /* Port A/B/C/D */
                    if (fe_GPIO < GPIO_E) 
                    {
                        *GPIO_FuncMux = (*GPIO_FuncMux & ~(0xF << (lu32_Position * 4))) | (GPIO_Init->Alternate << (lu32_Position * 4));
                    }
                    /* Port E */
                    else 
                    {
                        if (lu32_Current_Pin == GPIO_PIN_0) 
                        {
                            *GPIO_FuncMux = (*GPIO_FuncMux & ~(0xF << 24)) | (GPIO_Init->Alternate << 24);
                        }
                        else if (lu32_Current_Pin == GPIO_PIN_1) 
                        {
                            *GPIO_FuncMux = (*GPIO_FuncMux & ~(0xFul << 28)) | (GPIO_Init->Alternate << 28);
                        }
                    }
                }break;

                case GPIO_MODE_EXTI_IT_RISING:
                case GPIO_MODE_EXTI_IT_FALLING:
                case GPIO_MODE_EXTI_IT_HIGH_LEVEL:
                case GPIO_MODE_EXTI_IT_LOW_LEVEL:
                {
                    *GPIO_OutputEN    |=   lu32_Current_Pin;
                    *GPIO_EXTI_EN     |=   lu32_Current_Pin << GPIO_Offset;
                    *GPIO_EXTI_INT_EN &= ~(lu32_Current_Pin << GPIO_Offset);
                    
                    if (fe_GPIO == GPIO_B || fe_GPIO == GPIO_D) 
                    {
                        *GPIO_EXTI_TYPE = (*GPIO_EXTI_TYPE & ~(0x3 << ((lu32_Position + 8) * 2))) | ((GPIO_Init->Mode & 0x3) << ((lu32_Position + 8) * 2));
                    }
                    else 
                    {
                        *GPIO_EXTI_TYPE = (*GPIO_EXTI_TYPE & ~(0x3 << (lu32_Position * 2))) | ((GPIO_Init->Mode & 0x3) << (lu32_Position * 2));
                    }
                }break;

                default: break; 
            }

            /* GPIO Function */
            if (GPIO_Init->Mode & GPIO_MODE_IO_MASK) 
            {
                /* Port A/B/C/D */
                if (fe_GPIO < GPIO_E) 
                {
                    *GPIO_FuncMux = *GPIO_FuncMux & ~(0xF << (lu32_Position * 4));
                }
                /* Port E */
                else
                {
                    if (lu32_Current_Pin == GPIO_PIN_0) 
                    {
                        *GPIO_FuncMux = *GPIO_FuncMux & ~(0xF << 24);
                    }
                    else if (lu32_Current_Pin == GPIO_PIN_1) 
                    {
                        *GPIO_FuncMux = *GPIO_FuncMux & ~(0xFul << 28);
                    }
                }
            }

            /* Set Pull UP or DOWN or NO */
            /* Port A/B/C/D */
            if (fe_GPIO < GPIO_E)
            {
                if (GPIO_Init->Pull == GPIO_NOPULL) 
                {
                    *GPIO_Pull_EN &= ~(lu32_Current_Pin << GPIO_Offset);
                }
                else if (GPIO_Init->Pull == GPIO_PULLUP) 
                {
                    *GPIO_Pull_EN     |= lu32_Current_Pin << GPIO_Offset;
                    *GPIO_Pull_Select |= lu32_Current_Pin << GPIO_Offset;
                }
                else if (GPIO_Init->Pull == GPIO_PULLDOWN) 
                {
                    *GPIO_Pull_EN     |=   lu32_Current_Pin << GPIO_Offset;
                    *GPIO_Pull_Select &= ~(lu32_Current_Pin << GPIO_Offset);
                }
            }
            /* Port E */
            else 
            {
                if (lu32_Current_Pin < GPIO_PIN_2) 
                {
                    if (GPIO_Init->Pull == GPIO_NOPULL) 
                    {
                        *GPIO_FuncMux &= ~(lu32_Current_Pin << 20);
                    }
                    else if (GPIO_Init->Pull == GPIO_PULLUP) 
                    {
                        *GPIO_FuncMux |= lu32_Current_Pin << 20;
                        *GPIO_FuncMux |= lu32_Current_Pin << 22;
                    }
                    else if (GPIO_Init->Pull == GPIO_PULLDOWN) 
                    {
                        *GPIO_FuncMux |=   lu32_Current_Pin << 20;
                        *GPIO_FuncMux &= ~(lu32_Current_Pin << 22);
                    }
                }
            }
        }

        lu32_Position++;
    }
}

/************************************************************************************
 * @fn      gpio_set_portpull
 *
 * @brief   set port pull
 *
 * @param   fe_GPIO: to select the GPIO peripheral.
 *          fu8_Pin: to select the Pin. (1bit ~ 1Pin)
 *          fe_Pull: pull up/pull down/no pull
 * @return  pin status.
 */
void gpio_set_portpull(enum_GPIOx_t fe_GPIO, uint8_t fu8_Pin, enum_Pull_t fe_Pull)
{
    volatile uint32_t *GPIO_Pull_EN     = &system_regs->port_pull_enable;
    volatile uint32_t *GPIO_Pull_Select = &system_regs->port_pull_sel;
    volatile uint32_t *GOIO_PortE_CFG   = (uint32_t *)(0x50000038);
    volatile uint32_t  GPIO_Offset;
    
    switch (fe_GPIO)
    {
        case GPIO_A: GPIO_Offset = 0;  break;
        case GPIO_B: GPIO_Offset = 8;  break;
        case GPIO_C: GPIO_Offset = 16; break;
        case GPIO_D: GPIO_Offset = 24; break;
        case GPIO_E: GPIO_Offset = 0;  break;

        default: break; 
    }
    
    /* Set Pull UP or DOWN or NO */
    /* Port A/B/C/D */
    if (fe_GPIO < GPIO_E)
    {
        if (fe_Pull == GPIO_NOPULL) 
        {
            *GPIO_Pull_EN &= ~(fu8_Pin << GPIO_Offset);
        }
        else if (fe_Pull == GPIO_PULLUP) 
        {
            *GPIO_Pull_EN     |= fu8_Pin << GPIO_Offset;
            *GPIO_Pull_Select |= fu8_Pin << GPIO_Offset;
        }
        else if (fe_Pull == GPIO_PULLDOWN) 
        {
            *GPIO_Pull_EN     |=   fu8_Pin << GPIO_Offset;
            *GPIO_Pull_Select &= ~(fu8_Pin << GPIO_Offset);
        }
    }
    /* Port E */
    else 
    {
        if (fu8_Pin < GPIO_PIN_2) 
        {
            if (fe_Pull == GPIO_NOPULL) 
            {
                *GOIO_PortE_CFG &= ~(fu8_Pin << 20);
            }
            else if (fe_Pull == GPIO_PULLUP) 
            {
                *GOIO_PortE_CFG |= fu8_Pin << 20;
                *GOIO_PortE_CFG |= fu8_Pin << 22;
            }
            else if (fe_Pull == GPIO_PULLDOWN) 
            {
                *GOIO_PortE_CFG |=   fu8_Pin << 20;
                *GOIO_PortE_CFG &= ~(fu8_Pin << 22);
            }
        }
    }
}

/************************************************************************************
 * @fn      gpio_write_group
 *
 * @brief   write gpio status, The unit is group.
 *
 * @param   fe_GPIO: to select the GPIO peripheral.
 *          fu8_GroupStatus: Group Status.(1bit ~ 1Pin)
 */
void gpio_write_group(enum_GPIOx_t fe_GPIO, uint8_t fu8_GroupStatus)
{
    switch (fe_GPIO)
    {
        case GPIO_A: GPIO->PortA_DATA = fu8_GroupStatus; break;
        case GPIO_B: GPIO->PortB_DATA = fu8_GroupStatus; break;
        case GPIO_C: GPIO->PortC_DATA = fu8_GroupStatus; break;
        case GPIO_D: GPIO->PortD_DATA = fu8_GroupStatus; break;
        case GPIO_E: GPIO->PortE_DATA = fu8_GroupStatus; break;

        default: break; 
    }
}

/************************************************************************************
 * @fn      gpio_write_pin
 *
 * @brief   write gpio status, The unit is pin.
 *
 * @param   fe_GPIO: to select the GPIO peripheral.
 *          fu8_Pin: to select the Pin.(1bit ~ 1Pin)
 *          fe_PinStatus: pin Status.
 */
void gpio_write_pin(enum_GPIOx_t fe_GPIO, uint8_t fu8_Pin, enum_PinStatus_t fe_PinStatus)
{
    switch (fe_GPIO)
    {
        case GPIO_A: GPIO->PortA_DATA = fe_PinStatus ? GPIO->PortA_DATA | fu8_Pin : GPIO->PortA_DATA & ~fu8_Pin; break;
        case GPIO_B: GPIO->PortB_DATA = fe_PinStatus ? GPIO->PortB_DATA | fu8_Pin : GPIO->PortB_DATA & ~fu8_Pin; break;
        case GPIO_C: GPIO->PortC_DATA = fe_PinStatus ? GPIO->PortC_DATA | fu8_Pin : GPIO->PortC_DATA & ~fu8_Pin; break;
        case GPIO_D: GPIO->PortD_DATA = fe_PinStatus ? GPIO->PortD_DATA | fu8_Pin : GPIO->PortD_DATA & ~fu8_Pin; break;
        case GPIO_E: GPIO->PortE_DATA = fe_PinStatus ? GPIO->PortE_DATA | fu8_Pin : GPIO->PortE_DATA & ~fu8_Pin; break;
            
        default: break; 
    }
}

/************************************************************************************
 * @fn      gpio_read_group
 *
 * @brief   read gpio status, The unit is group.
 *
 * @param   fe_GPIO: to select the GPIO peripheral.
 * @return  group status.(1bit ~ 1Pin)
 */
uint8_t gpio_read_group(enum_GPIOx_t fe_GPIO)
{
    uint8_t lu8_PinStatus;
    
    switch (fe_GPIO)
    {
        case GPIO_A: lu8_PinStatus = GPIO->PortA_DATA; break;
        case GPIO_B: lu8_PinStatus = GPIO->PortB_DATA; break;
        case GPIO_C: lu8_PinStatus = GPIO->PortC_DATA; break;
        case GPIO_D: lu8_PinStatus = GPIO->PortD_DATA; break;
        case GPIO_E: lu8_PinStatus = GPIO->PortE_DATA; break;

        default: break; 
    }
    
    return lu8_PinStatus;
}

/************************************************************************************
 * @fn      gpio_read_pin
 *
 * @brief   read gpio status, The unit is pin.
 *
 * @param   fe_GPIO: to select the GPIO peripheral.
 *          fu8_Pin: to select the Pin. (1bit ~ 1Pin)
 * @return  pin status.
 */
enum_PinStatus_t gpio_read_pin(enum_GPIOx_t fe_GPIO, uint8_t fu8_Pin)
{
    enum_PinStatus_t le_PinStatus;

    switch (fe_GPIO)
    {
        case GPIO_A: le_PinStatus = (GPIO->PortA_DATA & fu8_Pin) ? GPIO_PIN_SET : GPIO_PIN_CLEAR; break;
        case GPIO_B: le_PinStatus = (GPIO->PortB_DATA & fu8_Pin) ? GPIO_PIN_SET : GPIO_PIN_CLEAR; break;
        case GPIO_C: le_PinStatus = (GPIO->PortC_DATA & fu8_Pin) ? GPIO_PIN_SET : GPIO_PIN_CLEAR; break;
        case GPIO_D: le_PinStatus = (GPIO->PortD_DATA & fu8_Pin) ? GPIO_PIN_SET : GPIO_PIN_CLEAR; break;
        case GPIO_E: le_PinStatus = (GPIO->PortE_DATA & fu8_Pin) ? GPIO_PIN_SET : GPIO_PIN_CLEAR; break;

        default: break; 
    }
    
    return le_PinStatus;
}

/************************************************************************************
 * @fn      exti_interrupt_enable
 *
 * @brief   exti line interrupt enable.
 *
 * @param   fu8_EXTI_Line: to select the EXTI line.(0 ~ 35)
 */
void exti_interrupt_enable(uint8_t fu8_EXTI_Line)
{
    /* Port A/B/C/D */
    if (fu8_EXTI_Line < 32) 
    {
        GPIO->EXTI_INT_EN_0 |= 1 << fu8_EXTI_Line;
    }
    /* Port E */
    else 
    {
        GPIO->EXTI_INT_EN_1 |= 1 << (fu8_EXTI_Line - 32);
    }
}

/************************************************************************************
 * @fn      exti_interrupt_disable
 *
 * @brief   exti line interrupt disable.
 *
 * @param   fu8_EXTI_Line: to select the EXTI line.(0 ~ 35)
 */
void exti_interrupt_disable(uint8_t fu8_EXTI_Line)
{
    /* Port A/B/C/D */
    if (fu8_EXTI_Line < 32) 
    {
        GPIO->EXTI_INT_EN_0 &= ~(1 << fu8_EXTI_Line);
    }
    /* Port E */
    else 
    {
        GPIO->EXTI_INT_EN_1 &= ~(1 << (fu8_EXTI_Line - 32));
    }
}

/************************************************************************************
 * @fn      exti_get_LineStatus
 *
 * @brief   get exti line interrupt status.
 *
 * @param   fu8_EXTI_Line: to select the EXTI line.(0 ~ 35)
 * @return  true:  interrupt activate
 *          false: interrupt inactivate
 */
bool exti_get_LineStatus(uint8_t fu8_EXTI_Line)
{
    bool lb_EXTIStatus;

    /* Port A/B/C/D */
    if (fu8_EXTI_Line < 32) 
    {
        lb_EXTIStatus = GPIO->EXTI_INT_STATUS_0 & (1 << fu8_EXTI_Line) ? true : false; 
    }
    /* Port E */
    else 
    {
        lb_EXTIStatus = GPIO->EXTI_INT_STATUS_1 & (1 << (fu8_EXTI_Line - 32)) ? true : false; 
    }

    return lb_EXTIStatus;
}

/************************************************************************************
 * @fn      exti_clear_LineStatus
 *
 * @brief   clear exti line interrupt status.
 *
 * @param   fu8_EXTI_Line: to select the EXTI line.(0 ~ 35)
 */
void exti_clear_LineStatus(uint8_t fu8_EXTI_Line)
{
    /* Port A/B/C/D */
    if (fu8_EXTI_Line < 32) 
    {
        GPIO->EXTI_INT_STATUS_0 |= 1 << fu8_EXTI_Line; 
    }
    /* Port E */
    else 
    {
        GPIO->EXTI_INT_STATUS_1 |= 1 << (fu8_EXTI_Line - 32); 
    }
}

/************************************************************************************
 * @fn      exti_set_FilterCNT
 *
 * @brief   set exti line filer
 *
 * @param   fu16_EXTI_Line: to select the EXTI line.(0 ~ 35)
            fu8_DIV: filter clock divider.
            fu8_CNT: filter count.
 */
void exti_set_Filter(uint8_t fu8_EXTI_Line, uint8_t fu8_DIV, uint8_t fu8_CNT)
{
    GPIO->EXTI_CNT[fu8_EXTI_Line] = (uint32_t)fu8_DIV << 8 | (uint32_t)fu8_CNT;
}

/*
    for example:
    
    GPIO_InitTypeDef GPIO_Handle;

void main(void)
{
    // Output 
    GPIO_Handle.Pin       = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_Handle.Mode      = GPIO_MODE_OUTPUT_PP;

    gpio_init(GPIO_B, &GPIO_Handle);

    gpio_write_pin(GPIO_B, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_SET);
    gpio_write_pin(GPIO_B, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_CLEAR);

    gpio_write_group(GPIO_B, 0x03);
    gpio_write_group(GPIO_B, 0x00);

    // Input
    GPIO_Handle.Pin       = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_Handle.Mode      = GPIO_MODE_INPUT;
    GPIO_Handle.Pull      = GPIO_PULLDOWN;

    gpio_init(GPIO_B, &GPIO_Handle);
    
    gpio_read_group(GPIO_B);
    
    gpio_read_pin(GPIO_B, GPIO_PIN_2);
    gpio_read_pin(GPIO_B, GPIO_PIN_3);
    
    // EXTI interrupt
    GPIO_Handle.Pin       = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_Handle.Mode      = GPIO_MODE_EXTI_IT_RISING;
    GPIO_Handle.Pull      = GPIO_PULLDOWN;

    gpio_init(GPIO_B, &GPIO_Handle);

    while (1) 
    {
        if (exti_get_LineStatus(EXTI_LINE8_PB0))
        {
            exti_clear_LineStatus(EXTI_LINE8_PB0);
        }

        if (exti_get_LineStatus(EXTI_LINE8_PB1))
        {
            exti_clear_LineStatus(EXTI_LINE8_PB1);
        }
    }
    
    // Alternate Function
    GPIO_Handle.Pin       = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull      = GPIO_PULLDOWN;
    GPIO_Handle.Alternate = GPIO_FUNCTION_4;

    gpio_init(GPIO_B, &GPIO_Handle);
}

*/
