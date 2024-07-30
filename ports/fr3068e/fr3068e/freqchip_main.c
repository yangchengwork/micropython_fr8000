/*
  ******************************************************************************
  * @file    main.c
  * @author  FreqChip Firmware Team
  * @brief   main source File.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "fr30xx.h"

extern int py_main(void);

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
int fputc(int ch, FILE *stream)
{  
    while(__UART_IS_TxFIFO_FULL(UART3));
    __UART_WRITE_FIFO(UART3, ch);

    return ch;
}
#endif

#ifdef __GNUC__
int _write(int file, char *ptr, int len)
{
    UART_HandleTypeDef Uart_Handler;
    Uart_Handler.UARTx = UART3;
    uart_transmit(&Uart_Handler, (uint8_t *)ptr, len);
    while(!(Uart_Handler.UARTx->USR.TFE));
    return len;
}
#endif
/*********************************************************************
 * @fn      system_clock_config
 *
 * @brief   System Misc Init.
 */
void system_clock_config(void)
{
    System_ClkConfig_t ClkConfig;

    /* CORE HSCLK Config */
    ClkConfig.CORE_HSCLK_CFG.CORE_HSCLK_Source = CORE_HSCLK_SEL_HES;
    /* PLL clock = HSE_VALUE*N + (HSE_VALUE/65535)*M */
    /* SPLL CLK Config */
    ClkConfig.SPLL_CFG.PowerEn = PLL_POWER_ENABLE;
    ClkConfig.SPLL_CFG.PLL_N = 8;
    ClkConfig.SPLL_CFG.PLL_M = 0;
    /* PLL clock = HSE_VALUE*N + (HSE_VALUE/65535)*M */
    /* AUPLL CLK Config */
    ClkConfig.AUPLL_CFG.PowerEn = PLL_POWER_DISABLE;
    ClkConfig.AUPLL_CFG.PLL_N = 8;
    ClkConfig.AUPLL_CFG.PLL_D = 0;
    ClkConfig.AUPLL_CFG.PLL_K = 0;    

    System_CORE_HSCLK_config(&ClkConfig.CORE_HSCLK_CFG);
    if (System_SPLL_config(&ClkConfig.SPLL_CFG,200) == -1)
        while(1);    
    if (System_AUPLL_config(&ClkConfig.AUPLL_CFG,200) == -1)
        while(1);

    ClkConfig.MCU_Clock_Source = MCU_CLK_SEL_CORE_HSCLK;
    ClkConfig.SOC_DIV  = 1;    /* This parameter is valid when MCU_Clock_Source == MCU_CLK_SEL_SPLL_CLK */
    ClkConfig.MCU_DIV  = 1;
    ClkConfig.APB0_DIV = 1;
    ClkConfig.APB1_DIV = 1;
    ClkConfig.APB2_DIV = 1;

    System_MCU_clock_Config(&ClkConfig);
}

UART_HandleTypeDef  Uart3_handle;
int main(void)
{
    GPIO_InitTypeDef    GPIO_Handle;
    
    pmu_init();
    
    system_clock_config();

    /* Uart3 IO init */
    GPIO_Handle.Pin       = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_Handle.Mode      = GPIO_MODE_AF_PP;
    GPIO_Handle.Pull      = GPIO_PULLUP;
    GPIO_Handle.Alternate = GPIO_FUNCTION_1;
    gpio_init(GPIOB, &GPIO_Handle);

    __SYSTEM_UART_CLK_SELECT_COREH();    
    Uart3_handle.UARTx = UART3;
    Uart3_handle.Init.BaudRate   = 115200;
    Uart3_handle.Init.DataLength = UART_DATA_LENGTH_8BIT;
    Uart3_handle.Init.StopBits   = UART_STOPBITS_1;
    Uart3_handle.Init.Parity     = UART_PARITY_NONE;
    Uart3_handle.Init.FIFO_Mode  = UART_FIFO_ENABLE;
    uart_init(&Uart3_handle);

    printf("SystemCoreClock:%d\r\n", system_get_CoreClock());
    printf("SystemDSPClock:%d\r\n", system_get_DSPClock());
    printf("System_CORE_HSCLK:%d\r\n", system_get_CORE_HSCLK());
    printf("System_SPLLCLK:%d\r\n", system_get_SPLLCLK());
    printf("System_AUPLLCLK:%d\r\n", system_get_AUPLLCLK());

    py_main();
    
    while(1);
}
