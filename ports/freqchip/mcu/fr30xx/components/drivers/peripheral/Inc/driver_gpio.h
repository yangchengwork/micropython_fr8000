/*
  ******************************************************************************
  * @file    driver_gpio.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of GPIO HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

#include "fr30xx.h"

/** @addtogroup GPIO_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* -----------------------------------------------*/
/*                 GPIO Registers                 */
/* -----------------------------------------------*/
typedef struct 
{
    volatile uint32_t  GPIO_OutputEN;      /* Offset 0x00 */
    volatile uint32_t  GPIO_IN_DATA;       /* Offset 0x04 */
    volatile uint32_t  GPIO_OUT_DATA;      /* Offset 0x08 */
    volatile uint32_t  GPIO_BIT_SET;       /* Offset 0x0C */
    volatile uint32_t  GPIO_BIT_CLEAR;     /* Offset 0x10 */
    
    volatile uint32_t  EXTI_EN;            /* Offset 0x14 */
    volatile uint32_t  EXTI_INT_EN;        /* Offset 0x18 */
    volatile uint32_t  EXTI_INT_STATUS;    /* Offset 0x1C */
    volatile uint32_t  EXTI_TYPE;          /* Offset 0x20 */
    volatile uint32_t  EXTI_CNT[16];       /* Offset 0x24 */
}struct_GPIO_t;

#define GPIO_TypeDef struct_GPIO_t

#define GPIOA    (( GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB    (( GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC    (( GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD    (( GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE    (( GPIO_TypeDef *)GPIOE_BASE)


/* ################################ Register Section END ################################## */
/**
  * @}
  */


/** @addtogroup ADC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

/** @defgroup GPIO_pins GPIO pins
  * @{
  */
 /*
    GPIO_PIN_A0~GPIO_PIN_A15 GPIO_PIN_B0~GPIO_PIN_B15 
    GPIO_PIN_C0~GPIO_PIN_C15 GPIO_PIN_D0~GPIO_PIN_D15
    GPIO_PIN_E0~GPIO_PIN_E11
 */
#define GPIO_PIN_0                 ((uint16_t)0x0001)    /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)    /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)    /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)    /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)    /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)    /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)    /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)    /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)    /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)    /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)    /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)    /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)    /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)    /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)    /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)    /* Pin 15 selected   */
/**
  * @}
  */

/** @defgroup EXTI_line_index
  * @{
  */
#define EXTI_LINE_0                ((uint16_t)0x0001)    /* EXTI Line index 0  */
#define EXTI_LINE_1                ((uint16_t)0x0002)    /* EXTI Line index 1  */
#define EXTI_LINE_2                ((uint16_t)0x0004)    /* EXTI Line index 2  */
#define EXTI_LINE_3                ((uint16_t)0x0008)    /* EXTI Line index 3  */
#define EXTI_LINE_4                ((uint16_t)0x0010)    /* EXTI Line index 4  */
#define EXTI_LINE_5                ((uint16_t)0x0020)    /* EXTI Line index 5  */
#define EXTI_LINE_6                ((uint16_t)0x0040)    /* EXTI Line index 6  */
#define EXTI_LINE_7                ((uint16_t)0x0080)    /* EXTI Line index 7  */
#define EXTI_LINE_8                ((uint16_t)0x0100)    /* EXTI Line index 8  */
#define EXTI_LINE_9                ((uint16_t)0x0200)    /* EXTI Line index 9  */
#define EXTI_LINE_10               ((uint16_t)0x0400)    /* EXTI Line index 10 */
#define EXTI_LINE_11               ((uint16_t)0x0800)    /* EXTI Line index 11 */
#define EXTI_LINE_12               ((uint16_t)0x1000)    /* EXTI Line index 12 */
#define EXTI_LINE_13               ((uint16_t)0x2000)    /* EXTI Line index 13 */
#define EXTI_LINE_14               ((uint16_t)0x4000)    /* EXTI Line index 14 */
#define EXTI_LINE_15               ((uint16_t)0x8000)    /* EXTI Line index 15 */
/**
  * @}
  */

/* GPIO mode */
typedef enum
{
    GPIO_MODE_INPUT              = 0x1000u,    /*!< Input Floating Mode               */
    GPIO_MODE_INPUT_HRS          = 0x1001u,    /*!< Input High Resistance Mode        */
    GPIO_MODE_OUTPUT_PP          = 0x1002u,    /*!< Output Push Pull Mode             */
    GPIO_MODE_AF_PP              = 0x0002u,    /*!< Alternate Function Push Pull Mode */
    GPIO_MODE_EXTI_IT_LOW_LEVEL  = 0x1100u,    /*!< External Interrupt Mode with low  level trigger detection   */
    GPIO_MODE_EXTI_IT_HIGH_LEVEL = 0x1101u,    /*!< External Interrupt Mode with high level trigger detection   */
    GPIO_MODE_EXTI_IT_RISING     = 0x1102u,    /*!< External Interrupt Mode with Rising  edge trigger detection */
    GPIO_MODE_EXTI_IT_FALLING    = 0x1103u,    /*!< External Interrupt Mode with Falling edge trigger detection */

    GPIO_MODE_IO_MASK = 0x1000,    /*!< GPIO Function Mask */
    GPIO_MODE_IT_MASK = 0x0100,    /*!< EXTI Function Mask */
}enum_GPIO_MODE_t;

/* GPIO pull */
typedef enum
{
    GPIO_NOPULL,      /*!< No Pull-up or Pull-down activation  */
    GPIO_PULLUP,      /*!< Pull-up activation                  */
    GPIO_PULLDOWN,    /*!< Pull-down activation                */
}enum_Pull_t;

/* function selection */
typedef enum
{
    GPIO_FUNCTION_0,
    GPIO_FUNCTION_1,
    GPIO_FUNCTION_2,
    GPIO_FUNCTION_3,
    GPIO_FUNCTION_4,
    GPIO_FUNCTION_5,
    GPIO_FUNCTION_6,
    GPIO_FUNCTION_7,
    GPIO_FUNCTION_8,
    GPIO_FUNCTION_9,
    GPIO_FUNCTION_A,
    GPIO_FUNCTION_B,
    GPIO_FUNCTION_C,
    GPIO_FUNCTION_D,
    GPIO_FUNCTION_E,
    GPIO_FUNCTION_F,
}enum_Function_t;

/* GPIO Bit SET and Bit RESET enumeration */
typedef enum
{
  GPIO_PIN_CLEAR = 0u,
  GPIO_PIN_SET   = 1u,
}enum_PinStatus_t;

/* GPIO Drive Current Index */
typedef enum  
{
    GPIO_DRIVE_4mA,
    GPIO_DRIVE_8mA,
    GPIO_DRIVE_12mA,
    GPIO_DRIVE_16mA,
}enum_GPIO_Drive_Current_t;

/*
 * @brief   GPIO Init structure definition
 */
typedef struct
{
    uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                              This parameter can be any value of @ref GPIO_pins */

    uint32_t Mode;       /*!< Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref enum_GPIO_MODE_t */

    uint32_t Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                              This parameter can be a value of @ref enum_Pull_t */

    uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins.
                              This parameter can be a value of @ref enum_Function_t */
}GPIO_InitTypeDef;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/* gpio_init */
void gpio_init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);

/* gpio_set_portpull */
void gpio_set_portpull(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_Pull_t fe_Pull);

/* gpio_write_group */
/* gpio_write_pin */
void gpio_write_group(GPIO_TypeDef *GPIOx, uint16_t fu16_GroupStatus);
void gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_PinStatus_t fe_PinStatus);

/* gpio_read_group */
/* gpio_read_pin */
uint16_t gpio_read_group(GPIO_TypeDef *GPIOx);
enum_PinStatus_t gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin);

/* gpio_drive_current_config */
/* input schmitt enable/disable */
void gpio_drive_current_config(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_GPIO_Drive_Current_t fe_GPIO_Drive);

void gpio_wakeup_func_set(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_PinStatus_t ref_level);
void gpio_wakeup_ref_level_set(GPIO_TypeDef *GPIOx, uint16_t fu16_Pin, enum_PinStatus_t ref_level);

/* exti_interrupt_enable */
/* exti_interrupt_disable */
void exti_interrupt_enable(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line);
void exti_interrupt_disable(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line);

/* exti_get_LineStatus */
/* exti_clear_LineStatus */
bool exti_get_LineStatus(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line);
void exti_clear_LineStatus(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line);

/* exti_set_FilterCNT */
void exti_set_Filter(GPIO_TypeDef *GPIOx, uint16_t fu16_EXTI_Line, uint8_t fu8_DIV, uint16_t fu16_CNT);

/* gpioex_qspi_init */
/* gpioex_qspi_set_portpull */
/* gpioex_qspi_write_group */
/* gpioex_qspi_read_output_shadow */
/* gpioex_qspi_write_pin */
/* gpioex_qspi_read_group */
/* gpioex_qspi_read_pin */
/* gpioex_qspi_drive_current_config */
void gpioex_qspi_init(GPIO_InitTypeDef *GPIO_Init);
void gpioex_qspi_set_portpull(uint16_t fu16_Pin, enum_Pull_t fe_Pull);
void gpioex_qspi_write_group(uint16_t fu16_GroupStatus);
uint16_t gpioex_qspi_read_output_shadow(void);
void gpioex_qspi_write_pin(uint16_t fu16_Pin, enum_PinStatus_t fe_PinStatus);
uint16_t gpioex_qspi_read_group(void);
enum_PinStatus_t gpioex_qspi_read_pin(uint16_t fu16_Pin);
void gpioex_qspi_drive_current_config(uint16_t fu16_Pin, enum_GPIO_Drive_Current_t fe_GPIO_Drive);

/* gpioex_ospi_init */
/* gpioex_ospi_set_portpull */
/* gpioex_ospi_write_group */
/* gpioex_ospi_read_output_shadow */
/* gpioex_ospi_write_pin */
/* gpioex_ospi_read_group */
/* gpioex_ospi_read_pin */
/* gpioex_ospi_drive_current_config */
void gpioex_ospi_init(GPIO_InitTypeDef *GPIO_Init);
void gpioex_ospi_set_portpull(uint16_t fu16_Pin, enum_Pull_t fe_Pull);
void gpioex_ospi_write_group(uint16_t fu16_GroupStatus);
uint16_t gpioex_ospi_read_output_shadow(void);
void gpioex_ospi_write_pin(uint16_t fu16_Pin, enum_PinStatus_t fe_PinStatus);
uint16_t gpioex_ospi_read_group(void);
enum_PinStatus_t gpioex_ospi_read_pin(uint16_t fu16_Pin);
void gpioex_ospi_drive_current_config(uint16_t fu16_Pin, enum_GPIO_Drive_Current_t fe_GPIO_Drive);

#endif



