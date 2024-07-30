/*
  ******************************************************************************
  * @file    driver_gpio.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   GPIO module driver.
  *          This file provides firmware functions to manage the 
  *          General Purpose Input/Output (GPIO) peripheral
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "fr30xx.h"

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
__RAM_CODE void gpio_init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t lu32_Position = 0;
    uint32_t lu32_Current_Pin;

    volatile uint32_t *GPIO_InputOpenCircuit;
    volatile uint32_t *GPIO_Pull_EN;
    volatile uint32_t *GPIO_Pull_Select;
    volatile uint32_t *GPIO_FuncMuxL;
    volatile uint32_t *GPIO_FuncMuxH;

    /* Select the group register */
    if (GPIOx == GPIOA)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortA_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortA_PullSelect);
        GPIO_FuncMuxL    = &(SYSTEM->PortA_L_FuncMux);
        GPIO_FuncMuxH    = &(SYSTEM->PortA_H_FuncMux);
        GPIO_InputOpenCircuit = &(SYSTEM->PortA_InputOpenCircuit);
    }
    else if (GPIOx == GPIOB)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortB_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortB_PullSelect);
        GPIO_FuncMuxL    = &(SYSTEM->PortB_L_FuncMux);
        GPIO_FuncMuxH    = &(SYSTEM->PortB_H_FuncMux);
        GPIO_InputOpenCircuit = &(SYSTEM->PortB_InputOpenCircuit);        
    }
    else if (GPIOx == GPIOC)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortC_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortC_PullSelect);
        GPIO_FuncMuxL    = &(SYSTEM->PortC_L_FuncMux);
        GPIO_FuncMuxH    = &(SYSTEM->PortC_H_FuncMux);
        GPIO_InputOpenCircuit = &(SYSTEM->PortC_InputOpenCircuit);
    }
    else if (GPIOx == GPIOD)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortD_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortD_PullSelect);
        GPIO_FuncMuxL    = &(SYSTEM->PortD_L_FuncMux);
        GPIO_FuncMuxH    = &(SYSTEM->PortD_H_FuncMux);
        GPIO_InputOpenCircuit = &(SYSTEM->PortD_InputOpenCircuit);        
    }
    else if(GPIOx == GPIOE)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortE_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortE_PullSelect);
        GPIO_FuncMuxL    = &(SYSTEM->PortE_L_FuncMux);
        GPIO_FuncMuxH    = &(SYSTEM->PortE_H_FuncMux);
        GPIO_InputOpenCircuit = &(SYSTEM->PortE_InputOpenCircuit);
    }
    else {
        return;
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
                    *GPIO_InputOpenCircuit  |=  lu32_Current_Pin;
                    GPIOx->GPIO_OutputEN    |=  lu32_Current_Pin;
                    GPIOx->EXTI_EN          &= ~lu32_Current_Pin;
                    GPIOx->EXTI_INT_EN      &= ~lu32_Current_Pin;
                }break;

                case GPIO_MODE_INPUT_HRS:
                {
                    *GPIO_InputOpenCircuit  &= ~lu32_Current_Pin;                    
                    GPIOx->GPIO_OutputEN    |=  lu32_Current_Pin;
                    GPIOx->EXTI_EN          &= ~lu32_Current_Pin;
                    GPIOx->EXTI_INT_EN      &= ~lu32_Current_Pin;
                    /* High Resistance Mode does not pull up or down */
                    GPIO_Init->Pull = GPIO_NOPULL;
                }break;

                case GPIO_MODE_OUTPUT_PP:
                {
                    *GPIO_InputOpenCircuit  &= ~lu32_Current_Pin;                      
                    GPIOx->GPIO_OutputEN    &= ~lu32_Current_Pin;
                    GPIOx->EXTI_EN          &= ~lu32_Current_Pin;
                    GPIOx->EXTI_INT_EN      &= ~lu32_Current_Pin;
                }break;

                case GPIO_MODE_AF_PP:
                {
                    *GPIO_InputOpenCircuit |= lu32_Current_Pin;
                    GPIOx->EXTI_EN         &= ~lu32_Current_Pin;
                    GPIOx->EXTI_INT_EN     &= ~lu32_Current_Pin;
                    
                    /* Port 0 ~ 7 */
                    if (lu32_Position < 8) 
                    {
                        *GPIO_FuncMuxL = (*GPIO_FuncMuxL & ~(0xF << (lu32_Position * 4))) | (GPIO_Init->Alternate << (lu32_Position * 4));
                    }
                    /* Port 8 ~ 15 */
                    else 
                    {
                        *GPIO_FuncMuxH = (*GPIO_FuncMuxH & ~(0xF << ((lu32_Position - 8) * 4))) | (GPIO_Init->Alternate << ((lu32_Position - 8) * 4));
                    }
                }break;

                case GPIO_MODE_EXTI_IT_RISING:
                case GPIO_MODE_EXTI_IT_FALLING:
                case GPIO_MODE_EXTI_IT_HIGH_LEVEL:
                case GPIO_MODE_EXTI_IT_LOW_LEVEL:
                {
                    *GPIO_InputOpenCircuit |= lu32_Current_Pin;
                    
                    GPIOx->EXTI_TYPE = (GPIOx->EXTI_TYPE & ~(0x3 << (lu32_Position * 2))) | ((GPIO_Init->Mode & 0x3) << (lu32_Position * 2));

                    GPIOx->GPIO_OutputEN |=  lu32_Current_Pin;
                    GPIOx->EXTI_EN       |=  lu32_Current_Pin;
                    GPIOx->EXTI_INT_EN   &= ~lu32_Current_Pin;
                }break;

                default: break; 
            }

            /* GPIO Function */
            if (GPIO_Init->Mode & GPIO_MODE_IO_MASK) 
            {
                /* Port 0 ~ 7 */
                if (lu32_Position < 8) 
                {
                    *GPIO_FuncMuxL = *GPIO_FuncMuxL & ~(0xF << (lu32_Position * 4));
                }
                /* Port 8 ~ 15 */
                else 
                {
                    *GPIO_FuncMuxH = *GPIO_FuncMuxH & ~(0xF << ((lu32_Position - 8) * 4));
                }
            }

            /* Set Pull UP/DOWN or NO Pull */
            if (GPIO_Init->Pull == GPIO_NOPULL) 
            {
                *GPIO_Pull_EN &= ~lu32_Current_Pin;
            }
            else if (GPIO_Init->Pull == GPIO_PULLUP) 
            {
                *GPIO_Pull_EN     |= lu32_Current_Pin;
                *GPIO_Pull_Select |= lu32_Current_Pin;
            }
            else if (GPIO_Init->Pull == GPIO_PULLDOWN) 
            {
                *GPIO_Pull_EN     |=  lu32_Current_Pin;
                *GPIO_Pull_Select &= ~lu32_Current_Pin;
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
 * @param   GPIOx: where x can be (GPIOA ~ GPIOB) to select the GPIO peripheral.
 * @param   fu16_Pin: to select the Pin (1bit ~ 1Pin). @ref GPIO_pins
 * @param   fe_Pull: pull up/pull down/no pull @ref enum_Pull_t
 * @return  pin status.
 */
void gpio_set_portpull(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_Pull_t fe_Pull)
{
    uint32_t lu32_Position = 0;
    uint32_t lu32_Current_Pin;

    volatile uint32_t *GPIO_Pull_EN;
    volatile uint32_t *GPIO_Pull_Select;

    /* Select the group register */
    if (GPIOx == GPIOA)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortA_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortA_PullSelect);
    }
    else if (GPIOx == GPIOB)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortB_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortB_PullSelect);
    }
    else if (GPIOx == GPIOC)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortC_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortC_PullSelect);
    }
    else if (GPIOx == GPIOD)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortD_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortD_PullSelect);
    }
    else if (GPIOx == GPIOE)
    {
        GPIO_Pull_EN     = &(SYSTEM->PortE_PullEN);
        GPIO_Pull_Select = &(SYSTEM->PortE_PullSelect);
    }
    
    /* Configure Select pins */
    while (fu16_Pin >> lu32_Position != 0) 
    {
        /* Get current pin position */
        lu32_Current_Pin = fu16_Pin & (1uL << lu32_Position);
        
        if (lu32_Current_Pin) 
        {
            /* Set Pull UP or DOWN or NO */
            if (fe_Pull == GPIO_NOPULL) 
            {
                *GPIO_Pull_EN &= ~lu32_Current_Pin;
            }
            else if (fe_Pull == GPIO_PULLUP) 
            {
                *GPIO_Pull_EN     |= lu32_Current_Pin;
                *GPIO_Pull_Select |= lu32_Current_Pin;
            }
            else if (fe_Pull == GPIO_PULLDOWN) 
            {
                *GPIO_Pull_EN     |=  lu32_Current_Pin;
                *GPIO_Pull_Select &= ~lu32_Current_Pin;
            }
        }

        lu32_Position++;
    }
}

/************************************************************************************
 * @fn      gpio_write_group
 *
 * @brief   write gpio status, The unit is group.
 *
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_GroupStatus: Group Status.(1bit ~ 1Pin)
 */
void gpio_write_group(GPIO_TypeDef *GPIOx, uint16_t fu16_GroupStatus)
{
    GPIOx->GPIO_OUT_DATA = fu16_GroupStatus;
}

/************************************************************************************
 * @fn      gpio_write_pin
 *
 * @brief   write gpio status, The unit is pin.
 *
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_Pin: to select the Pin (1bit ~ 1Pin). @ref GPIO_pins
 * @param   fe_PinStatus: pin Status. @ref enum_PinStatus_t
 */
void gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_PinStatus_t fe_PinStatus)
{
    if (fe_PinStatus)
    {
        GPIOx->GPIO_BIT_SET = fu16_Pin;
    }
    else
    {
        GPIOx->GPIO_BIT_CLEAR = fu16_Pin;
    }
}

/************************************************************************************
 * @fn      gpio_read_group
 *
 * @brief   read gpio status, The unit is group.
 *
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @return  group status.(1bit ~ 1Pin)
 */
uint16_t gpio_read_group(GPIO_TypeDef *GPIOx)
{
    return GPIOx->GPIO_IN_DATA;
}

/************************************************************************************
 * @fn      gpio_read_pin
 *
 * @brief   read gpio status, The unit is pin.
 *
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_Pin: to select the Pin (1bit ~ 1Pin). @ref GPIO_pins
 * @return  pin status.
 */
enum_PinStatus_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin)
{
    enum_PinStatus_t le_PinStatus;

    le_PinStatus = (GPIOx->GPIO_IN_DATA & fu16_Pin) ? GPIO_PIN_SET : GPIO_PIN_CLEAR;

    return le_PinStatus;
}

/************************************************************************************
 * @fn      gpio_drive_current_config
 *
 * @brief   gpio drive current config.
 *
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_Pin: to select the Pin (1bit ~ 1Pin). @ref GPIO_pins
 * @param   fe_GPIO_Drive: Drive Current. @ref enum_GPIO_Drive_Current_t
 */
void gpio_drive_current_config(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_GPIO_Drive_Current_t fe_GPIO_Drive)
{
    uint32_t lu32_Position = 0;
    uint32_t lu32_Current_Pin;

    /* Configure Select pins */
    while (fu16_Pin >> lu32_Position != 0) 
    {
        /* Get current pin position */
        lu32_Current_Pin = fu16_Pin & (1uL << lu32_Position);
        
        if (lu32_Current_Pin) 
        {
            if (GPIOx == GPIOA)
                SYSTEM->PortA_DriveCfg = (SYSTEM->PortA_DriveCfg & ~(0x3 << (lu32_Position * 2))) | (fe_GPIO_Drive << (lu32_Position * 2));
            else if (GPIOx == GPIOB)
                SYSTEM->PortB_DriveCfg = (SYSTEM->PortB_DriveCfg & ~(0x3 << (lu32_Position * 2))) | (fe_GPIO_Drive << (lu32_Position * 2));
            else if (GPIOx == GPIOC)
                SYSTEM->PortC_DriveCfg = (SYSTEM->PortC_DriveCfg & ~(0x3 << (lu32_Position * 2))) | (fe_GPIO_Drive << (lu32_Position * 2));
            else if (GPIOx == GPIOD)
                SYSTEM->PortD_DriveCfg = (SYSTEM->PortD_DriveCfg & ~(0x3 << (lu32_Position * 2))) | (fe_GPIO_Drive << (lu32_Position * 2));
            else if (GPIOx == GPIOE)
                SYSTEM->PortE_DriveCfg = (SYSTEM->PortE_DriveCfg & ~(0x3 << (lu32_Position * 2))) | (fe_GPIO_Drive << (lu32_Position * 2));            
        }

        lu32_Position++;
    }
}

/*********************************************************************
 * @fn      gpio_wake_up_set
 *
 * @brief   GPIO wakeup function congfig(PA~PE)
 * 
 * @param   GPIOx - where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_Pin: to select the Pin (1bit ~ 1Pin). @ref GPIO_pins
 * @param   ref_level - When the level of indicated pins change from ref_level to the other type,
 *                      PMU_GPIO_GROUPH_INT or PMU_GPIO_GROUPL_INT interrupt will be generated.
 */
void gpio_wakeup_func_set(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_PinStatus_t ref_level)
{
    volatile uint32_t *GPIO_InputOpenCircuit;
    volatile uint32_t *GPIO_Reference_Status;
    volatile uint32_t *GPIO_WakeupEN;

    /* Select the group register */
    if (GPIOx == GPIOA)
    {
        GPIO_InputOpenCircuit = &(SYSTEM->PortA_InputOpenCircuit);
        GPIO_Reference_Status = &(SYSTEM->PortA_Reference_Status);
        GPIO_WakeupEN = &(SYSTEM->PortA_WakeupEN);
    }
    else if (GPIOx == GPIOB)
    {
        GPIO_InputOpenCircuit = &(SYSTEM->PortB_InputOpenCircuit);
        GPIO_Reference_Status = &(SYSTEM->PortB_Reference_Status);
        GPIO_WakeupEN = &(SYSTEM->PortB_WakeupEN);
    }
    else if (GPIOx == GPIOC)
    {
        GPIO_InputOpenCircuit = &(SYSTEM->PortC_InputOpenCircuit);
        GPIO_Reference_Status = &(SYSTEM->PortC_Reference_Status);
        GPIO_WakeupEN = &(SYSTEM->PortC_WakeupEN);
    }
    else if (GPIOx == GPIOD)
    {
        GPIO_InputOpenCircuit = &(SYSTEM->PortD_InputOpenCircuit);
        GPIO_Reference_Status = &(SYSTEM->PortD_Reference_Status);
        GPIO_WakeupEN = &(SYSTEM->PortD_WakeupEN);
    }
    else if(GPIOx == GPIOE)
    {
        GPIO_InputOpenCircuit = &(SYSTEM->PortE_InputOpenCircuit);
        GPIO_Reference_Status = &(SYSTEM->PortE_Reference_Status);
        GPIO_WakeupEN = &(SYSTEM->PortE_WakeupEN);
    }
    else {
        return;
    }
    
	if(ref_level == GPIO_PIN_SET)
    {
        *GPIO_InputOpenCircuit |= fu16_Pin;
        *GPIO_Reference_Status |= fu16_Pin;
    }
    else
    {
        *GPIO_InputOpenCircuit |= fu16_Pin;
        *GPIO_Reference_Status &= (~fu16_Pin);
    }
    *GPIO_WakeupEN |= fu16_Pin;

    /* enable PMU_GPIO_GROUPH_INT and PMU_GPIO_GROUPL_INT interrupt */
	pmu_enable_isr(PMU_GPIO_GROUPH_INT_MSK_BIT | PMU_GPIO_GROUPL_INT_MSK_BIT);
}

/*********************************************************************
 * @fn      gpio_wakeup_ref_level_set
 *
 * @brief   used to set which level could generate interrupt
 * 
 * @param   GPIOx - where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_Pin: to select the Pin (1bit ~ 1Pin). @ref GPIO_pins
 * @param   ref_level - When the level of indicated pins change from ref_level to the other type,
 *                      PMU_GPIO_GROUPH_INT or PMU_GPIO_GROUPL_INT interrupt will be generated.
 */
void gpio_wakeup_ref_level_set(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_PinStatus_t ref_level)
{
    volatile uint32_t *GPIO_Reference_Status;

    /* Select the group register */
    if (GPIOx == GPIOA)
    {
        GPIO_Reference_Status = &(SYSTEM->PortA_Reference_Status);
    }
    else if (GPIOx == GPIOB)
    {
        GPIO_Reference_Status = &(SYSTEM->PortB_Reference_Status);
    }
    else if (GPIOx == GPIOC)
    {
        GPIO_Reference_Status = &(SYSTEM->PortC_Reference_Status);
    }
    else if (GPIOx == GPIOD)
    {
        GPIO_Reference_Status = &(SYSTEM->PortD_Reference_Status);
    }
    else if(GPIOx == GPIOE)
    {
        GPIO_Reference_Status = &(SYSTEM->PortE_Reference_Status);
    }
    else {
        return;
    }
    
    if(ref_level == GPIO_PIN_SET)
    {
        *GPIO_Reference_Status |= fu16_Pin;
    }
    else
    {
        *GPIO_Reference_Status &= (~fu16_Pin);
    }
}

/************************************************************************************
 * @fn      exti_interrupt_enable
 *
 * @brief   exti line interrupt enable.
 * 
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_EXTI_Line: to select the EXTI line.(1bit ~ 1Pin)
 */
void exti_interrupt_enable(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line)
{
    GPIOx->EXTI_INT_EN |= fu16_EXTI_Line;
}

/************************************************************************************
 * @fn      exti_interrupt_disable
 *
 * @brief   exti line interrupt disable.
 *
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_EXTI_Line: to select the EXTI line (1bit ~ 1Pin). @ref EXTI_line_index
 */
void exti_interrupt_disable(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line)
{
    GPIOx->EXTI_INT_EN &= ~fu16_EXTI_Line;
}

/************************************************************************************
 * @fn      exti_get_LineStatus
 *
 * @brief   get exti line interrupt status.
 *
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu8_EXTI_Line: to select the EXTI line (1bit ~ 1Pin). @ref EXTI_line_index
 * @return  true:  interrupt activate
 *          false: interrupt inactivate
 */
bool exti_get_LineStatus(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line)
{
    bool lb_EXTIStatus;

    lb_EXTIStatus = (GPIOx->EXTI_INT_STATUS & fu16_EXTI_Line) ? true : false;

    return lb_EXTIStatus;
}

/************************************************************************************
 * @fn      exti_clear_LineStatus
 *
 * @brief   clear exti line interrupt status.
 *
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu8_EXTI_Line: to select the EXTI line (1bit ~ 1Pin). @ref EXTI_line_index
 */
void exti_clear_LineStatus(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line)
{
    GPIOx->EXTI_INT_STATUS |= fu16_EXTI_Line;
}

/************************************************************************************
 * @fn      exti_set_FilterCNT
 *
 * @brief   set exti line filer.
 * 
 * @param   GPIOx: where x can be (GPIOA ~ GPIOD) to select the GPIO peripheral.
 * @param   fu16_EXTI_Line: to select the EXTI line (1bit ~ 1Pin). @ref EXTI_line_index
 * @param   fu8_DIV: filter clock divider. (can be a 4-bit value)
 * @param   fu16_CNT: filter count. (can be a 12-bit value)
 */
void exti_set_Filter(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line, uint8_t fu8_DIV, uint16_t fu16_CNT)
{
    uint32_t lu32_Position = 0;
    uint32_t lu32_Current_Pin;
    
    /* Init write value */
    uint32_t lu32_WriteValue = fu8_DIV << 12 | fu16_CNT;

    /* Configure Select pins */
    while (fu16_EXTI_Line >> lu32_Position != 0) 
    {
        /* Get current pin position */
        lu32_Current_Pin = fu16_EXTI_Line & (1uL << lu32_Position);
        
        if (lu32_Current_Pin) 
        {
            GPIOx->EXTI_CNT[lu32_Position] = lu32_WriteValue;
        }

        lu32_Position++;
    }
}
