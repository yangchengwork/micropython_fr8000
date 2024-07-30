/*
  ******************************************************************************
  * @file    system_fr30xx.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Device Peripheral Access Layer System Source File.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  * 
  ******************************************************************************
*/
#include "fr30xx.h"

static uint32_t System_CORE_HSCLK = 24000000;
static uint32_t System_SPLLCLK;
static uint32_t System_AUPLLCLK;

uint32_t SystemCoreClock = 24000000;
static uint32_t SystemDSPClock = 24000000;
static uint32_t System48MClock = 48000000;
static uint32_t System_LPRCCLK = 57000;

static uint32_t system_prevent_sleep_label = SYSTEM_PREVENT_SLEEP_TYPE_DISABLE;

__RAM_CODE static uint32_t mul_mod(uint32_t u, uint32_t v, uint32_t z)
{
    // 如果u*v没有溢出, 则直接计算

    if((u*v)/u == v) return (u*v)/z;

    // 进行长乘法(结果为64位)

    uint32_t u0, v0, w0;
    uint32_t u1, v1, w1, w2, t;

    u0 = u & 0xFFFF; u1 = u >> 16;
    v0 = v & 0xFFFF; v1 = v >> 16;
    w0 = u0*v0;
    t = u1*v0 + (w0 >> 16);
    w1 = t & 0xFFFF;
    w2 = t >> 16;
    w1 = u0*v1 + w1;

    // x为高32位, y为低32位

    uint32_t x = u1*v1 + w2 + (w1 >> 16);
    uint32_t y = u*v;

    // 进行长除法(被除数为64位)

    for (int i = 1; i <= 32; i++)
    {
        t = (int)x >> 31; // All 1 's if x(31) = 1.

        x = (x << 1) | (y >> 31); // Shift x || y left
        y <<= 1; // one bit.

        if((x|t) >= z) { x -= z; y++; }
    }

    return y; // y为商, x为余数
}

/*********************************************************************
 * @fn      SystemInit
 *
 * @brief   System Misc Init.
 */
void SystemInit(void)
{
/* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10 and CP11 Full Access */
#endif    
    /* SOC FCLK enable */
    __SYSTEM_SOC_FCLK_ENABLE();
    
    /* MISC */ 
    __SYSTEM_MISC_CLK_ENABLE();
    __SYSTEM_MISC_IO_CONFIG();
}

/*********************************************************************
 * @fn      System_CORE_HSCLK_CFG
 *
 * @brief   CORE HSCLK config.
 */
__RAM_CODE void System_CORE_HSCLK_config(System_CORE_HSCLKConfig_t *COREHConfig)
{
    if (COREHConfig->CORE_HSCLK_Source == CORE_HSCLK_SEL_HES)
    {
        __SYSTEM_CORE_HIGH_CLK_SELECT_OSC();
        System_CORE_HSCLK = HSE_VALUE;
    }
    else
    {
        __SYSTEM_CORE_HIGH_CLK_SELECT_RC();
        System_CORE_HSCLK = HSI_VALUE;
    }
}
#ifndef CHIP_UPDATE

/*********************************************************************
 * @fn      System_SPLL_config
 *
 * @brief   SPLL config.
 * 
 * @param   PLLConfig    : SPLL config parameter.
 * @param   fu32_timeout : Wait for SPLL stable timeout, unit 1us.
 * 
 * @return  0: succeed.
 * 
 */
__RAM_CODE int System_SPLL_config(System_SPLLConfig_t *PLLConfig, uint32_t fu32_timeout)
{
    #define SPLL_ANALOG_POWER_DISABLE               (0XC04B1827)
    #define SPLL_ANALOG_POWER_ENABLE_WITHOUT_M_0    (0x44141C84) 
    #define SPLL_ANALOG_POWER_ENABLE_WITHOUT_M_7    (0x44141CF4) 
    #define SPLL_ANALOG_POWER_ENABLE_WITHOUT_M_2    (0X44141CA4) 
    #define SPLL_ANALOG_POWER_ENABLE_WITH_M_0       (0xC4141C84) 
    #define SPLL_ANALOG_POWER_ENABLE_WITH_M_7       (0xC4141CF4) 
    #define SPLL_ANALOG_POWER_ENABLE_WITH_M_2       (0XC4141CA4) 
    #define SPLL_ANALOG_CONFIG1                     (0x775F5F00)
    #define SPLL_ANALOG_CONFIG2                     (0x07563425)     
  
    if (PLLConfig->PowerEn)
    {
        if(PLLConfig->PLL_N < 6){
            while(1);
        }

        /* spll reference clock disable */
        ool_write(PMU_REG_OSC_CTRL_1, ool_read(PMU_REG_OSC_CTRL_1) & ~PMU_OSC_CLK_REF_SPLL_EN_BIT);
        
        SYSTEM->SPLLConfig1 = SPLL_ANALOG_CONFIG1;
        SYSTEM->SPLLConfig2 = SPLL_ANALOG_CONFIG2;

        if (PLLConfig->PLL_M * 2 > 65535) {
            SYSTEM->SPLLConfig3.PLL_N = PLLConfig->PLL_N*2 + 1;
            SYSTEM->SPLLConfig3.PLL_M = PLLConfig->PLL_M*2 - 65535;
        }
        else {
            SYSTEM->SPLLConfig3.PLL_N = PLLConfig->PLL_N*2;
            SYSTEM->SPLLConfig3.PLL_M = PLLConfig->PLL_M*2;
        }
        
        if (SYSTEM->SPLLConfig3.PLL_M)
        {
            for (int i = 0; i < 30 ; i++)
            {
                SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_ENABLE_WITH_M_0;
                system_delay_us(20);
                SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_ENABLE_WITH_M_7;
                system_delay_us(20);
            }

            SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_ENABLE_WITH_M_2;
        }
        else
        {
            for (int i = 0; i < 30 ; i++)
            {
                SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_ENABLE_WITHOUT_M_0;
                system_delay_us(20);
                SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_ENABLE_WITHOUT_M_7;
                system_delay_us(20);
            }

            SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_ENABLE_WITHOUT_M_2;
        }

        system_delay_us(20);
        /* spll reference clock enable */
        ool_write(PMU_REG_OSC_CTRL_1, ool_read(PMU_REG_OSC_CTRL_1) | PMU_OSC_CLK_REF_SPLL_EN_BIT);
        system_delay_us(100);

        if (fu32_timeout > 10)
            fu32_timeout = 10;

        /* Wait for PLL stability timeout, unit 1us */
        for (int i = 0; i < fu32_timeout; i++)
        {
            system_delay_us(1);
        }

            __SYSTEM_SPLL_CLK_DIV2_ENABLE();
        System_SPLLCLK = (PLLConfig->PLL_N*HSE_VALUE) + mul_mod(PLLConfig->PLL_M,HSE_VALUE,0xffff);
    }
    else
    {
        SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_DISABLE;
        System_SPLLCLK = 0;
    }

    return 0;
}

/*********************************************************************
 * @fn      System_AUPLL_config
 *
 * @brief   AUPLL config.
 * 
 * @param   PLLConfig    : AUPLL config parameter.
 * @param   fu32_timeout : Wait for AUPLL stable timeout, unit 1us.
 * 
 * @return  0: succeed.
 * 
 */
__RAM_CODE int System_AUPLL_config(System_AUPLLConfig_t *PLLConfig, uint32_t fu32_timeout)
{
    #define AUPLL_ANALOG_POWER_DISABLE               (0XC04B1827)
    #define AUPLL_ANALOG_POWER_ENABLE_WITHOUT_M_0    (0x44141C84) 
    #define AUPLL_ANALOG_POWER_ENABLE_WITHOUT_M_7    (0x44141CF4) 
    #define AUPLL_ANALOG_POWER_ENABLE_WITHOUT_M_2    (0X44141CA4) 
    #define AUPLL_ANALOG_POWER_ENABLE_WITH_M_0       (0xC4141C84) 
    #define AUPLL_ANALOG_POWER_ENABLE_WITH_M_7       (0xC4141CF4) 
    #define AUPLL_ANALOG_POWER_ENABLE_WITH_M_2       (0XC4141CA4)
    #define AUPLL_ANALOG_CONFIG1                     (0x775F5F00)
    #define AUPLL_ANALOG_CONFIG2                     (0x06663425) 

    if (PLLConfig->PLL_K > PLLConfig->PLL_D)
        return -1;

    if (PLLConfig->PowerEn)
    {
        if(PLLConfig->PLL_N < 6){
            while(1);
        }

        /* aupll reference clock disable */
        ool_write(PMU_REG_OSC_CTRL_1, ool_read(PMU_REG_OSC_CTRL_1) & ~PMU_OSC_CLK_REF_AUPLL_EN_BIT);

        SYSTEM->AUPLLConfig1 = AUPLL_ANALOG_CONFIG1;
        SYSTEM->AUPLLConfig2 = AUPLL_ANALOG_CONFIG2;
        
        uint32_t AUPLL_K,AUPLL_D;
        
        if (PLLConfig->PLL_K*2 == PLLConfig->PLL_D)
        {
            SYSTEM->AUPLLConfig3.PLL_N = PLLConfig->PLL_N*2 + 1;
            AUPLL_K = 0;
            AUPLL_D = 0;
        }
        else if (PLLConfig->PLL_K*2 > PLLConfig->PLL_D)
        {
            SYSTEM->AUPLLConfig3.PLL_N = PLLConfig->PLL_N*2 + 1;
            AUPLL_D = PLLConfig->PLL_D;
            AUPLL_K = PLLConfig->PLL_K*2 - AUPLL_D;
        }
        else
        {
            SYSTEM->AUPLLConfig3.PLL_N = PLLConfig->PLL_N*2;
            AUPLL_D = PLLConfig->PLL_D;
            AUPLL_K = PLLConfig->PLL_K*2;
        }

        if (AUPLL_K)
        {
            int remainder, Num1, Num2;
            Num1 = AUPLL_D;
            Num2 = AUPLL_K;
            remainder = Num1 % Num2;
 
            while(remainder != 0)
            {
                Num1 = Num2;      
                Num2 = remainder; 
                remainder = Num1 % Num2;
            }

            AUPLL_K /= Num2;
            AUPLL_D /= Num2;

            AUPLL_K = (65536/AUPLL_D)*AUPLL_K;
            AUPLL_D = (65536/AUPLL_D)*AUPLL_D - 1;
            
            SYSTEM->AUPLLConfig3.PLL_M = AUPLL_K;
            SYSTEM->AUPLLConfig4 = AUPLL_D;
        }

        
        if (AUPLL_K)
        {
            for (int i = 0; i < 30 ; i++)
            {
                SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_ENABLE_WITH_M_0;
                system_delay_us(20);
                SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_ENABLE_WITH_M_7;
                system_delay_us(20);
            }

            SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_ENABLE_WITH_M_2;
        }
        else
        {
            for (int i = 0; i < 30 ; i++)
            {
                SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_ENABLE_WITHOUT_M_0;
                system_delay_us(20);
                SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_ENABLE_WITHOUT_M_7;
                system_delay_us(20);
            }

            SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_ENABLE_WITHOUT_M_2;
        }

        system_delay_us(20);
        /* aupll reference clock enable */
        ool_write(PMU_REG_OSC_CTRL_1, ool_read(PMU_REG_OSC_CTRL_1) | PMU_OSC_CLK_REF_AUPLL_EN_BIT);
        system_delay_us(100);

        if (fu32_timeout > 10)
            fu32_timeout = 10;

        /* Wait for PLL stability timeout, unit 1us */
        for (int i = 0; i < fu32_timeout; i++)
        {
            system_delay_us(1);
        }
        
        if(PLLConfig->PLL_K ==0 || PLLConfig->PLL_D == 0)
        {
            System_AUPLLCLK = (PLLConfig->PLL_N*HSE_VALUE);
        }
        else
        {
            System_AUPLLCLK = (PLLConfig->PLL_N*HSE_VALUE) + mul_mod(PLLConfig->PLL_K, HSE_VALUE, PLLConfig->PLL_D);//((uint64_t)(PLLConfig->PLL_K/PLLConfig->PLL_D)*HSE_VALUE);  
        }

    }
    else
    {
        SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_DISABLE;
        System_AUPLLCLK = 0;
    }

    return 0;
}
#else
/*********************************************************************
 * @fn      System_SPLL_config
 *
 * @brief   SPLL config.
 * 
 * @param   PLLConfig    : SPLL config parameter.
 * @param   fu32_timeout : Wait for SPLL stable timeout, unit 1us.
 * 
 * @return  0: succeed.
 * 
 */
__RAM_CODE int System_SPLL_config(System_SPLLConfig_t *PLLConfig, uint32_t fu32_timeout)
{
    #define SPLL_ANALOG_POWER_DISABLE               (0x44F01CA7)
    #define SPLL_ANALOG_POWER_ENABLE_WITHOUT_M      (0x44F01CA4) 
    #define SPLL_ANALOG_POWER_ENABLE_WITH_M         (0xC4F01CA4) 
    #define SPLL_ANALOG_CONFIG1                     (0x775F5800)
    #define SPLL_ANALOG_CONFIG2                     (0x07563425) 
    
    if ((PLLConfig->PLL_N < 6) || (PLLConfig->PLL_N > 10)) 
        return -1;
    
    if (PLLConfig->PowerEn)
    {
        SYSTEM->SPLLConfig1 = SPLL_ANALOG_CONFIG1;
        SYSTEM->SPLLConfig2 = SPLL_ANALOG_CONFIG2;
       
        SYSTEM->SPLLConfig3.PLL_N = PLLConfig->PLL_N;
        SYSTEM->SPLLConfig3.PLL_M = PLLConfig->PLL_M;
        
        if (SYSTEM->SPLLConfig3.PLL_M)
        {
            SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_ENABLE_WITH_M;
        }
        else
        {
            SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_ENABLE_WITHOUT_M;
        }
        system_delay_us(50);
        __SYSTEM_SPLL_CLK_DIV2_ENABLE();
        System_SPLLCLK = (PLLConfig->PLL_N*HSE_VALUE) + mul_mod(PLLConfig->PLL_M,HSE_VALUE,0xffff);
    }
    else
    {
        SYSTEM->SPLLConfig0 = SPLL_ANALOG_POWER_DISABLE;
        System_SPLLCLK = 0;
    }

    return 0;
}

/*********************************************************************
 * @fn      System_AUPLL_config
 *
 * @brief   AUPLL config.
 * 
 * @param   PLLConfig    : AUPLL config parameter.
 * @param   fu32_timeout : Wait for AUPLL stable timeout, unit 1us.
 * 
 * @return  0: succeed.
 * 
 */
__RAM_CODE int System_AUPLL_config(System_AUPLLConfig_t *PLLConfig, uint32_t fu32_timeout)
{
    #define AUPLL_ANALOG_POWER_DISABLE               (0x44F01CA7)
    #define AUPLL_ANALOG_POWER_ENABLE_WITHOUT_M      (0x44F01CA4) 
    #define AUPLL_ANALOG_POWER_ENABLE_WITH_M         (0xC4F01CA4) 
    #define AUPLL_ANALOG_CONFIG1                     (0x775F5800)
    #define AUPLL_ANALOG_CONFIG2                     (0x07563425) 
    
    if (PLLConfig->PLL_K > PLLConfig->PLL_D)
        return -1;
 
    if ((PLLConfig->PLL_N < 6) || (PLLConfig->PLL_N > 10)) 
        return -1;
    
    if (PLLConfig->PowerEn)
    {
        SYSTEM->AUPLLConfig1 = AUPLL_ANALOG_CONFIG1;
        SYSTEM->AUPLLConfig2 = AUPLL_ANALOG_CONFIG2;
       
        SYSTEM->AUPLLConfig3.PLL_N = PLLConfig->PLL_N;
        SYSTEM->AUPLLConfig3.PLL_M = PLLConfig->PLL_K;
        SYSTEM->AUPLLConfig4 = PLLConfig->PLL_D;
        
        if(PLLConfig->PLL_K){
            int remainder, Num1, Num2;
            Num1 = PLLConfig->PLL_D;
            Num2 = PLLConfig->PLL_K;
            remainder = Num1 % Num2;
            uint32_t AUPLL_K,AUPLL_D;
            
            AUPLL_K = PLLConfig->PLL_K;
            AUPLL_D = PLLConfig->PLL_D;
            
            while(remainder != 0)
            {
                Num1 = Num2;      
                Num2 = remainder; 
                remainder = Num1 % Num2;
            }

            AUPLL_K /= Num2;
            AUPLL_D /= Num2;

            AUPLL_K = (65536/AUPLL_D)*AUPLL_K;
            AUPLL_D = (65536/AUPLL_D)*AUPLL_D - 1;
            
            SYSTEM->AUPLLConfig3.PLL_M = AUPLL_K;
            SYSTEM->AUPLLConfig4 = AUPLL_D;          
        }
    
        if (SYSTEM->AUPLLConfig3.PLL_M)
        {
            SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_ENABLE_WITH_M;
        }
        else
        {
            SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_ENABLE_WITHOUT_M;
        }
        system_delay_us(50);
        System_AUPLLCLK = (PLLConfig->PLL_N*HSE_VALUE) + mul_mod(PLLConfig->PLL_K,HSE_VALUE,PLLConfig->PLL_D);
    }
    else
    {
        SYSTEM->AUPLLConfig0 = AUPLL_ANALOG_POWER_DISABLE;
        System_AUPLLCLK = 0;
    }

    return 0;    
}
#endif
/*********************************************************************
 * @fn      System_MCU_clock_Config
 *
 * @brief   MCU clock congfig.
 */
__RAM_CODE void System_MCU_clock_Config(System_ClkConfig_t *ClkConfig)
{
    /* MCU clock source select CORE_HSCLK */
    if (ClkConfig->MCU_Clock_Source == MCU_CLK_SEL_CORE_HSCLK)
    {
        __SYSTEM_MCU_CLK_DIV(ClkConfig->MCU_DIV);
        __SYSTEM_MCU_CLK_SELECT_COREH();

        SystemDSPClock  = System_CORE_HSCLK;
        SystemCoreClock = System_CORE_HSCLK / ClkConfig->MCU_DIV;
    }
    /* MCU clock source select SPLLCLK */
    else
    {
        __SYSTEM_SOC_CLK_DIV(ClkConfig->SOC_DIV);
        __SYSTEM_MCU_CLK_DIV(ClkConfig->MCU_DIV);
        __SYSTEM_MCU_CLK_SELECT_SPLL();

        SystemDSPClock  = System_SPLLCLK / ClkConfig->SOC_DIV;
        SystemCoreClock = SystemDSPClock / ClkConfig->MCU_DIV;
    }
    __SYSTEM_APB0_CLK_RATIO(ClkConfig->APB0_DIV);
    __SYSTEM_APB1_CLK_RATIO(ClkConfig->APB1_DIV);
    __SYSTEM_APB2_CLK_RATIO(ClkConfig->APB2_DIV);
}

/*********************************************************************
 * @fn      System_get_CoreClock/
 *          System_get_DSPClock/
 *          System_get_CORE_HSCLK/
 *          System_get_SPLLCLK/
 *          System_get_AUPLLCLK/
 *
 * @brief   get system clock.unit HZ.
 */
__RAM_CODE uint32_t system_get_CoreClock(void)
{
    return SystemCoreClock;
}
uint32_t system_get_DSPClock(void)
{
    return SystemDSPClock;
}
uint32_t system_get_CORE_HSCLK(void)
{
    return System_CORE_HSCLK;
}
uint32_t system_get_SPLLCLK(void)
{
    return System_SPLLCLK;
}
uint32_t system_get_AUPLLCLK(void)
{
    return System_AUPLLCLK;
}
__RAM_CODE uint32_t system_get_LPRCCLK(void)
{
    return System_LPRCCLK;
}
void system_set_LPRCCLK(uint32_t clk)
{
    System_LPRCCLK = clk;
}

/*********************************************************************
 * @fn      system_get_peripheral_clock
 *
 * @brief   get peripheral clock. unit HZ
 *
 * @param   fe_peripheral : peripheral select.
 *
 * @return  peripheral clock unit HZ.
 */
uint32_t system_get_peripheral_clock(per_clock_index_t peripheral)
{
    uint32_t PerClock;

    switch (peripheral)
    {
        case PER_CLK_UARTx:
        {
            /* clock from SPLL */
            if (SYSTEM->ClockSEL0.UART_CLK_SEL)
                PerClock = (system_get_SPLLCLK()/2) / (SYSTEM->BlockClockDIV1.UART_CLK_DIV + 1);
            else
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV1.UART_CLK_DIV + 1);
        }break;
        
        case PER_CLK_GPIOx:
        {
            /* clock from SPLL */
            if (SYSTEM->ClockSEL0.GPIO_CLK_SEL)
                PerClock = (system_get_SPLLCLK()/2) / (SYSTEM->BlockClockDIV1.GPIO_CLK_DIV + 1);
            else
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV1.GPIO_CLK_DIV + 1);
        }break;
        
        case PER_CLK_I2Cx:
        {
            /* clock from SPLL */
            if (SYSTEM->ClockSEL0.I2C_CLK_SEL)
                PerClock = (system_get_SPLLCLK()/2) / (SYSTEM->BlockClockDIV1.I2C_CLK_DIV + 1);
            else
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV1.I2C_CLK_DIV + 1);
        }break;

        case PER_CLK_TIMER01:{
            PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV2.TIMER01_CLK_DIV + 1);
        }break;

        case PER_CLK_TIMER23:{
            PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV2.TIMER23_CLK_DIV + 1);
        }break;

        case PER_CLK_TIMER45:{
            PerClock = system_get_CORE_HSCLK() / (SYSTEM->AudioClockDIV.TIMER45_CLK_DIV + 1);
        }break;        
        
        case PER_CLK_SPIS:
        {
            /* clock from HCLK */
            if (SYSTEM->ClockSEL0.SSIS_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV0.SSIS_CLK_DIV + 1);
            /* clock from SPLL */
            else if (SYSTEM->ClockSEL0.SSIS_CLK_SEL == 1)
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV0.SSIS_CLK_DIV + 1);
            /* clock from APLL */
            else if (SYSTEM->ClockSEL0.SSIS_CLK_SEL == 2)
                PerClock = system_get_AUPLLCLK() / (SYSTEM->BlockClockDIV0.SSIS_CLK_DIV + 1);               
            /* clock from 48M */
            else
                PerClock = System48MClock / (SYSTEM->BlockClockDIV0.SSIS_CLK_DIV + 1); 
        }break;
        
        case PER_CLK_SPIMX8_0:
        {
            /* clock from HCLK */
            if (SYSTEM->ClockSEL0.MSPI0_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV0.MSPI0_CLK_DIV + 1);
            /* clock from SPLL */
            else if (SYSTEM->ClockSEL0.MSPI0_CLK_SEL == 1)
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV0.MSPI0_CLK_DIV + 1);
            /* clock from APLL */
            else if (SYSTEM->ClockSEL0.MSPI0_CLK_SEL == 2)
                PerClock = system_get_AUPLLCLK() / (SYSTEM->BlockClockDIV0.MSPI0_CLK_DIV + 1);
            /* clock from 48M */
            else
                PerClock = System48MClock / (SYSTEM->BlockClockDIV0.MSPI0_CLK_DIV + 1);             
        }break;
                
        case PER_CLK_SPIMX8_1:
        {
            /* clock from HCLK */
            if (SYSTEM->ClockSEL0.MSPI1_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV0.MSPI1_CLK_DIV + 1);
            /* clock from SPLL */
            else if (SYSTEM->ClockSEL0.MSPI1_CLK_SEL == 1)
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV0.MSPI1_CLK_DIV + 1);
            /* clock from APLL */
            else if (SYSTEM->ClockSEL0.MSPI1_CLK_SEL == 2)
                PerClock = system_get_AUPLLCLK() / (SYSTEM->BlockClockDIV0.MSPI1_CLK_DIV + 1);
            /* clock from 48M */
            else
                PerClock = System48MClock / (SYSTEM->BlockClockDIV0.MSPI1_CLK_DIV + 1); 
        }break;
        
        case PER_CLK_PWM:
        {
            /* clock from HCLK */
            if (SYSTEM->ClockSEL0.PWM_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV2.PWM_CLK_DIV + 1);
            /* clock from SPLL */                
            else
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV2.PWM_CLK_DIV + 1);
        }break;

        case PER_CLK_PDM0:
        case PER_CLK_PDM1:
        {
            uint32_t PDMx_CLK_SEL, PDMx_CLK_DIV;
            if (peripheral == PER_CLK_PDM0) {
                PDMx_CLK_SEL = SYSTEM->ClockSEL1.PDM0_CLK_SEL;
                PDMx_CLK_DIV = SYSTEM->AudioClockDIV.PDM0_CLK_DIV;
            }
            else if (peripheral == PER_CLK_PDM1){
                PDMx_CLK_SEL = SYSTEM->ClockSEL1.PDM1_CLK_SEL;
                PDMx_CLK_DIV = SYSTEM->AudioClockDIV.PDM1_CLK_DIV;
            }

            /* clock from HCLK */
            if (PDMx_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (PDMx_CLK_DIV + 1);
            /* clock from AUPLL */
            else if (PDMx_CLK_SEL == 1)
                PerClock = system_get_AUPLLCLK() / (PDMx_CLK_DIV + 1);
            /* clock from 48M */
            else if (PDMx_CLK_SEL == 3)
                PerClock = System48MClock / (PDMx_CLK_DIV + 1);              
        }break;

        case PER_CLK_SDIOH0:
        {
            /* clock from HCLK */
            if (SYSTEM->ClockSEL0.SDIOH0_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV0.SDIOH0_CLK_DIV + 1);
            /* clock from SPLL */
            else if (SYSTEM->ClockSEL0.SDIOH0_CLK_SEL == 1)
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV0.SDIOH0_CLK_DIV + 1);
            /* clock from SPLL */
            else if (SYSTEM->ClockSEL0.SDIOH0_CLK_SEL == 2)
                PerClock = system_get_AUPLLCLK() / (SYSTEM->BlockClockDIV0.SDIOH0_CLK_DIV + 1);            
            /* clock from 48M */
            else
                PerClock = System48MClock / (SYSTEM->BlockClockDIV0.SDIOH0_CLK_DIV + 1);
                
        }break;

        case PER_CLK_CANx:
        {
            /* clock from HCLK */
            if (SYSTEM->ClockSEL0.MCAN_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV2.MCAN_CLK_DIV + 1);
            /* clock from SPLL */    
            else if (SYSTEM->ClockSEL0.MCAN_CLK_SEL == 1)
                PerClock = (system_get_SPLLCLK()/2) / (SYSTEM->BlockClockDIV2.MCAN_CLK_DIV + 1);
            /* clock from AUPLL */    
            else if (SYSTEM->ClockSEL0.MCAN_CLK_SEL == 2)
                PerClock = (system_get_AUPLLCLK()/2) / (SYSTEM->BlockClockDIV2.MCAN_CLK_DIV + 1);   
            /* clock from 48M */
            else
                PerClock = System48MClock / (SYSTEM->BlockClockDIV2.MCAN_CLK_DIV + 1);                         
        }break;

        case PER_CLK_I2Sx:
        {
            /* clock from SPLL */
            if (SYSTEM->ClockSEL1.I2S_CLK_SEL == 2)
                PerClock = (system_get_AUPLLCLK()) / (SYSTEM->AudioClockDIV.I2S_CLK_DIV + 1);
            else if (SYSTEM->ClockSEL1.I2S_CLK_SEL == 1)
                PerClock = (system_get_SPLLCLK()) / (SYSTEM->AudioClockDIV.I2S_CLK_DIV + 1);
            else if (SYSTEM->ClockSEL1.I2S_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->AudioClockDIV.I2S_CLK_DIV + 1);
        }break;

        case PER_CLK_OSPI:
        {
            /* clock from 48M */
            if (SYSTEM->ClockSEL0.OSPI_CLK_SEL == 3)
                PerClock = System48MClock / (SYSTEM->BlockClockDIV0.OSPI_CLK_DIV + 1);           
            /* clock from APLL */
            else if (SYSTEM->ClockSEL0.OSPI_CLK_SEL == 2)
                PerClock = (system_get_AUPLLCLK()) / (SYSTEM->BlockClockDIV0.OSPI_CLK_DIV + 1);
            /* clock from SPLL */                
            else if(SYSTEM->ClockSEL0.OSPI_CLK_SEL == 1)
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV0.OSPI_CLK_DIV + 1);  
            /* clock from HCLK */                
            else if(SYSTEM->ClockSEL0.OSPI_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV0.OSPI_CLK_DIV + 1);             
        }break;

        case PER_CLK_QSPI0:
        {       
            /* clock from 48M */
            if (SYSTEM->ClockSEL0.QSPI0_CLK_SEL == 3)
                PerClock = System48MClock / (SYSTEM->BlockClockDIV0.QSPI0_CLK_DIV + 1);           
            /* clock from APLL */
            else if (SYSTEM->ClockSEL0.QSPI0_CLK_SEL == 2)
                PerClock = (system_get_AUPLLCLK()) / (SYSTEM->BlockClockDIV0.QSPI0_CLK_DIV + 1);
            /* clock from SPLL */                
            else if(SYSTEM->ClockSEL0.QSPI0_CLK_SEL == 1)
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV0.QSPI0_CLK_DIV + 1);  
            /* clock from HCLK */                
            else if(SYSTEM->ClockSEL0.QSPI0_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV0.QSPI0_CLK_DIV + 1);              
        }break; 

        case PER_CLK_QSPI1:
        {  
            /* clock from 48M */
            if (SYSTEM->ClockSEL0.QSPI1_CLK_SEL == 3)
                PerClock = System48MClock / (SYSTEM->BlockClockDIV0.QSPI1_CLK_DIV + 1);           
            /* clock from APLL */
            else if (SYSTEM->ClockSEL0.QSPI1_CLK_SEL == 2)
                PerClock = (system_get_AUPLLCLK()) / (SYSTEM->BlockClockDIV0.QSPI1_CLK_DIV + 1);
            /* clock from SPLL */                
            else if(SYSTEM->ClockSEL0.QSPI1_CLK_SEL == 1)
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV0.QSPI1_CLK_DIV + 1);  
            /* clock from HCLK */                
            else if(SYSTEM->ClockSEL0.QSPI1_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV0.QSPI1_CLK_DIV + 1);             
        }break; 

        case PER_CLK_SPIMx:
        {
            /* clock from SPLL */
            if (SYSTEM->ClockSEL0.SSIM_CLK_SEL == 1)
                PerClock = system_get_SPLLCLK() / (SYSTEM->BlockClockDIV1.SSIM_CLK_DIV + 1);
            else
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV1.SSIM_CLK_DIV + 1);          
        }break; 

        case PER_CLK_DISPLAY:
        {
            /* clock from 48M */
            if (SYSTEM->ClockSEL0.DISPLAY_CLK_SEL == 3)
                PerClock = System48MClock / (SYSTEM->BlockClockDIV1.DISPLAY_CLK_DIV + 1);              
            /* clock from SPLL */
            if (SYSTEM->ClockSEL0.DISPLAY_CLK_SEL == 2)
                PerClock = (system_get_AUPLLCLK()/2) / (SYSTEM->BlockClockDIV1.DISPLAY_CLK_DIV + 1);
            else if (SYSTEM->ClockSEL0.DISPLAY_CLK_SEL == 1)
                PerClock = (system_get_SPLLCLK()/2) / (SYSTEM->BlockClockDIV1.DISPLAY_CLK_DIV + 1);                
            else if (SYSTEM->ClockSEL0.DISPLAY_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->BlockClockDIV1.DISPLAY_CLK_DIV + 1); 
            
        }break;        

        case PER_CLK_SPDIF:
        {
            /* clock from 48M */
            if (SYSTEM->ClockSEL1.SPDIF_CLK_SEL == 3)
                PerClock = System48MClock / (SYSTEM->AudioClockDIV.SPDIF_CLK_DIV + 1);            
            /* clock from SPLL */
            if (SYSTEM->ClockSEL1.SPDIF_CLK_SEL == 2)
                PerClock = (system_get_AUPLLCLK()/2) / (SYSTEM->AudioClockDIV.SPDIF_CLK_DIV + 1);
            else if(SYSTEM->ClockSEL1.SPDIF_CLK_SEL == 1)
                PerClock = (system_get_SPLLCLK()/2) / (SYSTEM->AudioClockDIV.SPDIF_CLK_DIV + 1);  
            else if(SYSTEM->ClockSEL1.SPDIF_CLK_SEL == 0)
                PerClock = system_get_CORE_HSCLK() / (SYSTEM->AudioClockDIV.SPDIF_CLK_DIV + 1);       
        }break;         
        
        default: PerClock = 0;break;
    }
    return PerClock;
}

/*********************************************************************
 * @fn      system_dmac_request_id_config
 *
 * @brief   dmac request id config.
 *
 * @param   fe_source : dma request source.
 * @param   fe_id     : user select request id.
 *
 * @return  None.
 */
void system_dmac_request_id_config(dmac_request_source_t fe_source, dmac_request_id_t fe_id)
{
    uint8_t  lu8_RequestSource;
    uint8_t  lu8_RequestIDReg;   

    lu8_RequestIDReg   = fe_source / 4;
    lu8_RequestSource  = fe_source % 4;

    SYSTEM->DmacHsCfg[lu8_RequestIDReg] &= ~(0x1F << lu8_RequestSource * 8);
    SYSTEM->DmacHsCfg[lu8_RequestIDReg] |=  fe_id << (lu8_RequestSource * 8);
}

/*********************************************************************
 * @fn      system_xip_flash_init
 *
 * @brief   used to reintialize xip flash. Usually this function will be called
 *          when system boot up or wakeup from sleep mode.
 *
 * @param   cfg: xip flash configurations. DIV_SEL should not be set to
 *               QSPI_BAUDRATE_DIV_2 for FR306x series
 * @param   wake_up: true - this function is called during wakeup procedure.
 *                   false - this function is called during boot up procedure.
 */
__RAM_CODE void system_xip_flash_init(System_XIPConfig_t *cfg, bool wake_up)
{
    uint32_t ref_clk;

    if ((cfg->CLK_SRC_SEL > XIP_CLK_SEL_AUPLL)
            || (cfg->RD_TYPE > FLASH_RD_TYPE_DTR_QUAD_FAST)
            || (cfg->WR_TYPE > FLASH_WR_TYPE_QUAD)
            || (cfg->DIV_SEL > QSPI_BAUDRATE_DIV_32)) {
        return;
    }

    GLOBAL_INT_DISABLE();
#if defined(CHIP_SEL_FR3066DQC_V1) || defined(CHIP_SEL_FR3068EC_V1)
    if (cfg->DIV_SEL == QSPI_BAUDRATE_DIV_2) {
        while(1);
    }
    __SYSTEM_FR3066DQC_QSPI0_IO2_IO3_CONFIG();
#else
    #error "unsupported chip!"
#endif
    while(__QSPI_IS_BUSY(QSPI0));

    if (wake_up == false) {
        flash_enable_quad(QSPI0);
    }
    flash_init_controller(QSPI0, cfg->RD_TYPE, cfg->WR_TYPE);
    flash_set_baudrate(QSPI0, cfg->DIV_SEL);
    __QSPI_DELAY_CS_START_SET(QSPI0, 4);
    __QSPI_DELAY_CS_END_SET(QSPI0, 4);
    __QSPI_DELAY_CS_DESSERT_SET(QSPI0, 8);
    if (cfg->CLK_SRC_SEL == XIP_CLK_SEL_COREH) {
        __SYSTEM_QSPI0_CLK_SELECT_COREH();
        ref_clk = System_CORE_HSCLK;
    }
    else if (cfg->CLK_SRC_SEL == XIP_CLK_SEL_SPLL) {
        __SYSTEM_QSPI0_CLK_SELECT_SPLL();
        ref_clk = System_SPLLCLK;
    }
    else if (cfg->CLK_SRC_SEL == XIP_CLK_SEL_AUPLL) {
        __SYSTEM_QSPI0_CLK_SELECT_AUPLL();
        ref_clk = System_AUPLLCLK;
    }
    
    if (cfg->DIV_SEL == QSPI_BAUDRATE_DIV_2) {
        if (ref_clk > (24000000*6)) {
            __QSPI_READ_CAPTURE_DELAY_SET(QSPI0, 3);
        }
        else if (ref_clk > (24000000*4)) {
            __QSPI_READ_CAPTURE_DELAY_SET(QSPI0, 2);
        }
        else {
            __QSPI_READ_CAPTURE_DELAY_SET(QSPI0, 1);
        }
    }
    else if (cfg->DIV_SEL == QSPI_BAUDRATE_DIV_4) {
        if (ref_clk >= (24000000*6)) {
            __QSPI_READ_CAPTURE_DELAY_SET(QSPI0, 2);
        }
    }

    GLOBAL_INT_RESTORE();
}

/*********************************************************************
 * @fn      system_delay_us
 *
 * @brief   system delay unit us, use system free counter.
 *
 * @param   fu32_delay: delay unit us.
 */
__RAM_CODE void system_delay_us(uint32_t fu32_delay)
{
    uint32_t backups_tack = FREE_COUNTER_VALUE;

    while(backups_tack - FREE_COUNTER_VALUE < fu32_delay);
}

/*********************************************************************
 * @fn      system_cache_enable
 *
 * @brief   cache enable.
 *
 * @param   invalid_ram : true:  invalidating the cache SRAM.
 *                        false: hold the cache SRAM.
 */
__RAM_CODE void system_cache_enable(bool invalid_ram)
{
    uint32_t prim;
    
    // manul enable the cache and invalidating the SRAM
    prim = __get_PRIMASK();
    __disable_irq();
    switch (*(volatile uint32_t *)(FLASH_CACHE_BASE + 4) & 0x03) {
        case 0x01:  // enabling
            while(((*(volatile uint32_t *)(FLASH_CACHE_BASE+4)) & 0x03) != 0x02);
        case 0x02:  // enabled
            break;
        case 0x03:  // disabling
            while(((*(volatile uint32_t *)(FLASH_CACHE_BASE+4)) & 0x03) != 0x00);
        default:
            *(volatile uint32_t *)FLASH_CACHE_BASE = 0x38;
            *(volatile uint32_t *)FLASH_CACHE_BASE = 0x3c;
            while(((*(volatile uint32_t *)(FLASH_CACHE_BASE+4)) & 0x10) == 0);
            if(invalid_ram)
            {
                *(volatile uint32_t *)FLASH_CACHE_BASE = 0x3e;
                while((*(volatile uint32_t *)FLASH_CACHE_BASE) & 0x02);
            }
            *(volatile uint32_t *)FLASH_CACHE_BASE = 0x3d;
            while(((*(volatile uint32_t *)(FLASH_CACHE_BASE+4)) & 0x03) != 0x02);
            break;
    }
    if(!prim)
    {
        __enable_irq();
    }
}

/*********************************************************************
 * @fn      system_cache_disable
 *
 * @brief   cache disable.
 *
 */
__RAM_CODE void system_cache_disable(void)
{
    uint32_t prim;
    
    // manul disable the cache
    prim = __get_PRIMASK();
    __disable_irq();
    *(volatile uint32_t *)FLASH_CACHE_BASE = 0x3c;
    *(volatile uint32_t *)FLASH_CACHE_BASE = 0x38;
    while(((*(volatile uint32_t *)(FLASH_CACHE_BASE+0x04)) & 0x03) != 0x00);

    if(!prim)
    {
        __enable_irq();
    }
}

void system_prevent_sleep_set(uint32_t type)
{
    GLOBAL_INT_DISABLE();
    system_prevent_sleep_label |= type;
    GLOBAL_INT_RESTORE();
}

void system_prevent_sleep_clear(uint32_t type)
{
    GLOBAL_INT_DISABLE();
    system_prevent_sleep_label &= (~type);
    GLOBAL_INT_RESTORE();
}

uint32_t system_prevent_sleep_get(void)
{
    return system_prevent_sleep_label;
}

void system_reset(void)
{
    __disable_irq();
    // reboot
    iwdt_Init_t iwdt_env;
    iwdt_env.iwdt_Count = 300;
    iwdt_env.iwdt_Timeout = 10;
    iwdt_env.iwdt_int_Enable = WDT_INT_DISABLE;
    iwdt_init(iwdt_env);
    iwdt_Enable();
//    ool_write(PMU_REG_IOLDO1_CTRL_0, (ool_read(PMU_REG_IOLDO1_CTRL_0) & 0xf0) | 0x01);
    while(1);
}

/* ====================================================================================================== */
/* ===============================   GLOBAL interrupt controller    ===================================== */
/* ====================================================================================================== */
void GLOBAL_INT_START(void)
{
    __asm (
        "CPSIE   i          \n"
    );
}

void GLOBAL_INT_STOP(void)
{
    __asm (
        "CPSID   i          \n"
    );
}

__RAM_CODE void CPU_SR_Restore(uint32_t org_base_pri)
{
    __asm (
        "MSR     BASEPRI, %[org]\n"
        :
        : [org]"r"(org_base_pri)
        :
    );
}

__RAM_CODE uint32_t CPU_SR_Save(uint32_t new_basepri)
{
    uint32_t old_basepri;
    __asm (
        "MRS     R4, BASEPRI\n"
        "MSR     BASEPRI, %[new]\n"
        "MOV     %[old], R4     \n"
        : [old]"=r"(old_basepri)
        : [new]"r"(new_basepri)
        : "r4"
    );
    return old_basepri;
}

/*********************************************************************
 * @fn      system_get_unique_ID
 *
 * @brief   get chip 5-bytes unique ID.
 *
 * @param   buffer - buffer used to store unique device ID
 * @param   length - IN: how many bytes is available in buffer
 *                   OUT: how many valid bytes is returned
 */
void system_get_unique_ID(uint8_t *buffer, uint8_t *length)
{
    trim_get_device_uuid(buffer, length);
}
