/*
  ******************************************************************************
  * @file    driver_pmu.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   pmu module driver.
  *          This file provides firmware functions to manage the 
  *          Power Management Unit (PMU) peripheral
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "app_config.h"

#include "driver_pmu.h"

#include "jump_table.h"
#include "co_log.h"

#undef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL             (LOG_LEVEL_NONE)

#ifdef FT_CODE
#define ENABLE_SYSTEM_PROTECTION_IN_LVD    (0)
#else
#define ENABLE_SYSTEM_PROTECTION_IN_LVD    (1)
#endif

#define  PMU_TWEXT_CONFIG           2150  // 1150 + 1000
#define  PMU_RSTN_ON_TIME           1000

#define PMU_FSM_ON_DIV              0x01  //the follow tcnt based <DIV*32K_CLK(rc)>
#define PMU_FSM_ON_TCNT             (0x0c<<0)
//the follow tcnt should <= FSM_ON_TCNT
#define PMU_RC64M_ON_TCNT           (0x02<<0)
#define PMU_BBG_ON_TCNT             (0x01<<0)
#define PMU_RSTN_ON_TCNT            (0x0c<<0)
#define PMU_BUCK_ON_TCNT            (0x02<<0)
#define PMU_IOLDO_ON_TCNT           (0x02<<0)
#define PMU_DLDO_ON_TCNT            (0x03<<0)
#define PMU_VDDHA_ON_TCNT           (0x01<<0)
#define PMU_MEMPD_ON_TCNT           (0x04<<0)
#define PMU_MMEPK_ON_TCNT           (0x05<<0)
#define PMU_SHORT_ON_TCNT           (0x06<<0)
#define PMU_MEMRET_ON_TCNT          (0x07<<0)
#define PMU_PMUISO_ON_TCNT          (0x07<<0)

#define PMU_FSM_OFF_DIV             0x00  //the follow tcnt based <DIV*32K_CLK(rc)>
#define PMU_FSM_OFF_TCNT            0x06
//the follow tcnt should <= FSM_OFF_TCNT
#define PMU_RC64M_OFF_TCNT          0x01
#define PMU_BBG_OFF_TCNT            0x05
#define PMU_RSTN_OFF_TCNT           0x01
#define PMU_BUCK_OFF_TCNT           0x05  
#define PMU_IOLDO_OFF_TCNT          0x01
#define PMU_DLDO_OFF_TCNT           0x05
#define PMU_VDDHA_OFF_TCNT          0x05
#define PMU_MEMPD_OFF_TCNT          0x04
#define PMU_MMEPK_OFF_TCNT          0x01
#define PMU_SHORT_OFF_TCNT          0x01
#define PMU_MEMRET_OFF_TCNT         0x02
#define PMU_PMUISO_OFF_TCNT         0x01

static struct_ADC_Cal_Param_t ADC_Cal_Param;
extern uint32_t flash_capacity;
void pmu_reset_internal_cnt(void)
{
    uint8_t reset_on_cnt;
    uint32_t (*us_2_lpsycles)(uint32_t) = (uint32_t (*)(uint32_t))0x0001ad8d;

    reset_on_cnt = us_2_lpsycles(PMU_RSTN_ON_TIME) / (PMU_FSM_ON_DIV + 1);

    ool_write(PMU_REG_PMU_ONOFF_CNT,((PMU_FSM_OFF_TCNT << 5) + reset_on_cnt));
    ool_write(PMU_REG_RSTN_ONOFF_CNT,((PMU_RSTN_OFF_TCNT << 5) + reset_on_cnt));
}

void pmu_sub_init(void)
{
    struct_FT_Param_t FT_Param;

    flash_capacity = FLASH_CAPACITY;

    /* enable system memory that is closed at system_power_off */
    ool_write(PMU_REG_GATE_CTRL_1, 0x00);
    /* first powon clear cpu sleep reg */
    ool_write(PMU_REG_SLP_OP, 0x00); 
    
    /* set pmu system clock to RC/2 */
    ool_write(PMU_REG_CLK_CTRL, PMU_CLK_SEL_RCLP_DIV2);

    /* enable wakeup and sleep signal to control pmu state */
    ool_write(PMU_REG_SLP_CTRL, ool_read(PMU_REG_SLP_CTRL) | (PMU_WAKEUP_EN | PMU_SLEEP_EN));

    /* enable sleep timer clock */
    ool_write(PMU_REG_CLK_EN, ool_read(PMU_REG_CLK_EN) | PMU_SLP_TIMER_CLK_EN);
    ool_write(PMU_REG_RST_CTRL, ool_read(PMU_REG_RST_CTRL) & (~PMU_SLP_TIMER_SFT_RST));

    /* enable ble sleep timer to control sleep and wakeup procedure */
    ool_write(PMU_REG_BLE_SLP_CTRL, ool_read(PMU_REG_BLE_SLP_CTRL) | PMU_EN_SLP_TIMER_CTRL_PMU);
    ool_write(PMU_REG_SLP_CTRL, ool_read(PMU_REG_SLP_CTRL) | (PMU_BB_WAKEUP_EN | PMU_BB_SLEEP_EN));

    /* enable BLE sleep timer accept external wakeup signal */
    ool_write(PMU_REG_BLE_SLP_CTRL, ool_read(PMU_REG_BLE_SLP_CTRL) & (~PMU_EXT_WAKEUP_DSB));

    /* enable xor and interrupt wakeup BLE sleep timer from deep sleep */
    ool_write(PMU_REG_BLE_SLP_CTRL, ool_read(PMU_REG_BLE_SLP_CTRL) /*| PMU_BLE_WAKEUP_XOR_EN*/ | PMU_BLE_WAKEUP_INT_EN);

    ool_write(PMU_REG_ANA_PIN_CFG, 0);
    
    //set on/off counter basic divider
    ool_write(PMU_REG_FSM_DIV_PARA,    ((PMU_FSM_OFF_DIV   << 5) + PMU_FSM_ON_DIV   ));
    //set on/off fsm total counter
    ool_write(PMU_REG_PMU_ONOFF_CNT   ,((PMU_FSM_OFF_TCNT   << 5) + PMU_FSM_ON_TCNT   ));
    //set sub block's on/off timing parameter
    ool_write(PMU_REG_RC64M_ONOFF_CNT ,((PMU_RC64M_OFF_TCNT << 5) + PMU_RC64M_ON_TCNT ));
    ool_write(PMU_REG_BBG_ONOFF_CNT   ,((PMU_BBG_OFF_TCNT   << 5) + PMU_BBG_ON_TCNT   ));
    ool_write(PMU_REG_RSTN_ONOFF_CNT  ,((PMU_RSTN_OFF_TCNT  << 5) + PMU_RSTN_ON_TCNT  ));
    ool_write(PMU_REG_BUCK_ONOFF_CNT  ,((PMU_BUCK_OFF_TCNT  << 5) + PMU_BUCK_ON_TCNT  ));
    ool_write(PMU_REG_IOLDO_ONOFF_CNT ,((PMU_IOLDO_OFF_TCNT << 5) + PMU_IOLDO_ON_TCNT ));
    ool_write(PMU_REG_DLDO_ONOFF_CNT  ,((PMU_DLDO_OFF_TCNT  << 5) + PMU_DLDO_ON_TCNT  ));
    ool_write(PMU_REG_VDDHA_ONOFF_CNT ,((PMU_VDDHA_OFF_TCNT << 5) + PMU_VDDHA_ON_TCNT ));
    ool_write(PMU_REG_PDVDD_ONOFF_CNT ,((PMU_MEMPD_OFF_TCNT << 5) + PMU_MEMPD_ON_TCNT ));
    ool_write(PMU_REG_PKVDD_ONOFF_CNT ,((PMU_MMEPK_OFF_TCNT << 5) + PMU_MMEPK_ON_TCNT ));
    ool_write(PMU_REG_PKDVDD_ONOFF_CNT,((PMU_SHORT_OFF_TCNT << 5) + PMU_SHORT_ON_TCNT ));
    ool_write(PMU_REG_MEMRET_ONOFF_CNT,((PMU_MEMRET_OFF_TCNT<< 5) + PMU_MEMRET_ON_TCNT));
    ool_write(PMU_REG_ISO_ONOFF_CNT   ,((PMU_PMUISO_OFF_TCNT<< 5) + PMU_PMUISO_ON_TCNT));

    //bit1-0, adkey pull_en, bit3-2, adkey pull_res_ctl
    //bit5-4, adkey sense_ref, bit7-6, adkey sense_en
    ool_write(PMU_REG_ADKEY_CFG, 0x18); //disable adkey detect pull up

    // set VDDHA to IOLDO
    ool_write(PMU_REG_ADC_CFG, 0x00);

    //setup dldo @0x19
    ool_write(PMU_REG_DLDO_CFG_1, (ool_read(PMU_REG_DLDO_CFG_1)|0x70));//dldo @max @bit6:4

//    //disable buck powon pull up
//    ool_write(PMU_REG_BUCK_CFG_6, (ool_read(PMU_REG_BUCK_CFG_6)&0xf7));//bit3 for disable buck_mode_pin pull up

    //disable io voltage select pin pull
    ool_write(PMU_REG_IOLDO_CFG_2, ((ool_read(PMU_REG_IOLDO_CFG_2)&0xf8)|PMU_ALDO_3_3V));          // set IOLDO output voltage, flash Mode Pin down
    ool_write(PMU_REG_IOLDO_CFG_3, ((ool_read(PMU_REG_IOLDO_CFG_3)&0x1F)|(PMU_ALDO_3_3V << 5)));   // set IOLDO output voltage, flash Mode Pin up
    ool_write(PMU_REG_DLDO_CFG_2, (ool_read(PMU_REG_DLDO_CFG_2)|0x80));//bit7 for dynamic flash_vdd
    ool_write(PMU_REG_FLASHV_CHG_CFG, (ool_read(PMU_REG_FLASHV_CHG_CFG)&0xbf)|0x80|0x40);//bit7 for flash_vdd_en, bit6 for flash mode pin pull up

    //chg pkvdd ref @0x04
    ool_write(PMU_REG_PKVDD_CFG_1, (ool_read(PMU_REG_PKVDD_CFG_1)|0x20));//bit5 for pkvdd_ref_ctl sel
    ool_write(PMU_REG_PKVDD_CFG_2, 0x91); //SRAM&PK @0.856v
    
    //enable buck
    ool_write(PMU_REG_GATE_CTRL_0, (ool_read(PMU_REG_GATE_CTRL_0)&0xfd));//bit1 system buck always-off
    ool_read(PMU_REG_GATE_CTRL_0);//for delay
    ool_read(PMU_REG_GATE_CTRL_0);//for delay
    ool_write(PMU_REG_GATE_CTRL_0, (ool_read(PMU_REG_GATE_CTRL_0)|0x04));//bit2 system ldo always-off 
    ool_write(PMU_REG_BUCK_CFG_2, 0x18);    // reconfigure buck working frequency
    ool_write(PMU_REG_BUCK_CFG_3, (ool_read(PMU_REG_BUCK_CFG_3)&0xbf));//bit6 disable buck RES
    ool_write(PMU_REG_BUCK_CFG_6, ool_read(PMU_REG_BUCK_CFG_6) | 0x80); // PWM
    ool_write(PMU_REG_BUCK_CFG_4, 0x90);

//    //disable cache memory pk
//    ool_write(PMU_REG_GATE_CTRL_1, (ool_read(PMU_REG_GATE_CTRL_1)|0x08));//bit3 for cache
#if BLE_STACK_RETENTION_RAM_SIZE == 0xC000
    ool_write(PMU_REG_GATE_CTRL_1, (ool_read(PMU_REG_GATE_CTRL_1)|CO_BIT(PMU_SYS_REM_8K_POS)));
#endif
#if BLE_STACK_RETENTION_RAM_SIZE == 0x8000
    ool_write(PMU_REG_GATE_CTRL_1, (ool_read(PMU_REG_GATE_CTRL_1)|CO_BIT(PMU_SYS_REM_16K_POS)|CO_BIT(PMU_SYS_REM_8K_POS)));
#endif

    ool_write(PMU_REG_GATE_MASK_0, (ool_read(PMU_REG_GATE_MASK_0)|0x08));//ioldo always-on
    ool_write(PMU_REG_CTRL_MISC_1, (ool_read(PMU_REG_CTRL_MISC_1)&0xfb));//enable gpio isolation dynamic bit2
    ool_write(PMU_REG_CTRL_MISC_0, 0x50);                 //pmu pd/gpio/isolation always on
    ool_write(PMU_REG_GPIO_MUX_CFG_SEL, 0x40); // USB pad mapped to pk register

    // remove internal osc cap
    ool_write(PMU_REG_OSC_CAP_CFG, 0x00);
    
    // configure OSC driver
    ool_write(PMU_REG_OSC_DRV, 0x3f);

    // configure IO mux in PMU to GPIO
    ool_pd_write16(PMU_REG_PD_PORTA_MUX, 0x00);
    ool_pd_write16(PMU_REG_PD_PORTB_MUX, 0x00);
    ool_pd_write16(PMU_REG_PD_PORTC_MUX, 0x00);
    ool_pd_write16(PMU_REG_PD_PORTD_MUX, 0x00);
    ool_pd_write(PMU_REG_PD_PORTE_MUX, 0x00);
    
    pmu_cp_trim_config();
#ifndef FT_CODE
    pmu_ft_trim_config(&FT_Param);
#endif  // FT_CODE

//    //disable pull up/down  & set pmu oe as input 
//    ool_write32(PMU_REG_PORTA_PULL_EN,0x00000000);
//    ool_write32(PMU_REG_PORTA_PULL_SEL,0x00000000);
//    ool_write32(PMU_REG_PORTA_OE,0x00000000);  
//    ool_write(PMU_REG_GPIO_MUX_CFG_SEL, 0x5f);

//    ool_pd_write(PMU_REG_DIAG_CFG_1,0x16); // set portc diag-ports //06 for bt sleep_on
//    ool_write(PMU_REG_PORTC_SEL, 0x00);
//    ool_write(PMU_REG_PORTD_SEL, 0x00);
//    ool_pd_write(PMU_REG_PD_PORTE_MUX, ool_pd_read(PMU_REG_PD_PORTE_MUX)|0xC0);
//    ool_pd_write16(PMU_REG_PD_PORTC_MUX, 0xffff);
//    ool_pd_write16(PMU_REG_PD_PORTD_MUX, 0xffff);

    system_osc_doubler_calibration();
    
    __jump_table.sleep_algo_dur = 0;
    __jump_table.twext = PMU_TWEXT_CONFIG;
    __jump_table.twosc = PMU_TWEXT_CONFIG;
    __jump_table.local_drift = 250;
    
    pmu_calibration_start(PMU_CALI_SEL_RCLFOSC, LP_RC_CALIB_CNT);
    co_delay_10us(5*LP_RC_CALIB_CNT);
    pmu_get_rc_clk(true);
    pmu_calibration_stop();
    
    pmu_reset_internal_cnt();
    system_set_tx_power(RF_TX_POWER_0dBm);

#if ENABLE_SYSTEM_PROTECTION_IN_LVD == 1
    pmu_lvd_en(0, LVD_2_3_V, 5); 
    NVIC_EnableIRQ(PMU_IRQn);
#endif  // ENABLE_SYSTEM_PROTECTION_IN_LVD
}

__attribute__((section("ram_code"))) void pmu_ioldosw_ctrl(bool on)
{
    uint8_t (*ool_read_ptr)(uint8_t, uint8_t, uint8_t)          = (uint8_t (*)(uint8_t, uint8_t, uint8_t))0x5009;
    void (*ool_write_ptr)(uint8_t, uint8_t, uint8_t, uint8_t)   = (void (*)(uint8_t, uint8_t, uint8_t, uint8_t))0x5045;
    
    if(on) {
        ool_write_ptr(0, PMU_REG_IOLDO_CFG_1, 1, ool_read_ptr(0, PMU_REG_IOLDO_CFG_1, 1)|0x08);
    }
    else {
        ool_write_ptr(0, PMU_REG_IOLDO_CFG_1, 1, ool_read_ptr(0, PMU_REG_IOLDO_CFG_1, 1)&0xf7);
    }
}

__attribute__((section("ram_code"))) void pmu_ioldo_bypass(bool on)
{  
    if(on) {
        ool_write(PMU_REG_IOLDO_CFG_1, ool_read(PMU_REG_IOLDO_CFG_1) | 0x20);
    }
    else {
        ool_write(PMU_REG_IOLDO_CFG_1, ool_read(PMU_REG_IOLDO_CFG_1) & ~0x20);
    }
}

__attribute__((section("ram_code"))) void pmu_usb_pad_ctrl(bool on)
{  
    if(on) {
        ool_write(PMU_REG_GPIO_MUX_CFG_SEL, 0x00);
    }
    else {
        ool_write(PMU_REG_GPIO_MUX_CFG_SEL, 0x40);
    }
}


/*********************************************************************
 * @fn      pmu_adc_power_control
 *
 * @brief   Set the low voltage detection threshold
 *
 * @param   fb_power: true:  enable
*                     false: disable
 */
void pmu_adc_power_control(bool fb_power)
{
    /* power on ADC module */
    if (fb_power)
    {
        ool_write(PMU_REG_ADC_CFG, ool_read(PMU_REG_ADC_CFG) | 0x80);
    }
    /* power off */    
    else
    {
        ool_write(PMU_REG_ADC_CFG, ool_read(PMU_REG_ADC_CFG) & ~0x80);
    }
}

/*********************************************************************
 * @fn      lvd_threshold
 *
 * @brief   Set the low voltage detection threshold
 *
 * @param   Low voltage detection threshold value
 * 
 * @return  None
 */
void lvd_threshold(enum LVD_Voltage_Threshold Voltage_value)
{
    ool_write(PMU_REG_POWARN_CTRL,ool_read(PMU_REG_POWARN_CTRL) & 0x1F | (Voltage_value << 5));
}

/*********************************************************************
 * @fn      pmu_lvd_en
 *
 * @brief   Low voltage detection enable
 *
 * @param   mode - 0:Quick response to lvd. 1:normal response to lvd.
 *          voltage_Threshold - @ref  LVD_Voltage_Threshold
 *          DEB_Len  debounce
 *
 * @return  None
 */
void pmu_lvd_en(uint8_t mode,enum LVD_Voltage_Threshold Voltage_value,uint8_t DEB_Len)
{
    if(mode)
    {
        ool_pd_write(PMU_REG_PD_ANA_INT_LEVEL,ool_read(PMU_REG_PD_ANA_INT_LEVEL) & (~PMU_LVD_INT_TRIG_LEVEL));
        ool_pd_write(PMU_REG_PD_LVD_DEB_LEN,DEB_Len);
        lvd_threshold(Voltage_value);
        pmu_enable_isr(PMU_LVD_DEB_INT_EN);  
    }else{
        lvd_threshold(Voltage_value);
        ool_write(PMU_REG_ANA_PIN_CFG,ool_read(PMU_REG_ANA_PIN_CFG) | PMU_ONKEY_EN);
        ool_write(PMU_REG_PORTE_LAST_STATUS,ool_read(PMU_REG_PORTE_LAST_STATUS)& 0xBF);
        ool_write(PMU_REG_PORTE_XOR_EN,ool_read(PMU_REG_PORTE_XOR_EN) | PMU_LVD_FAST_XOR_EN );
        pmu_enable_isr(PMU_LVD_FAST_INT_EN);  
    }
}
/*********************************************************************
 * @fn      pmu_enable_charge
 *
 * @brief   enable charge function,and set charge current & voltage
 *
 * @param   cur - charge current, @ref enum charge_current_t
 *          vol - charge terminal voltage, @ref enum charge_term_vol_t
 *          en - true = enable charge, false = disable charge
 *
 * @return  None.
 */
void pmu_enable_charge(enum charge_current_t cur, enum charge_term_vol_t vol, bool en)
{
    /* charge reference select BBG */
    ool_write(PMU_REG_CHG_EN_CFG, ool_read(PMU_REG_CHG_EN_CFG) | 0x01);
    /* config charge voltage */
    ool_write(PMU_REG_CHG_TERM_VOL_CTL, (ool_read(PMU_REG_CHG_TERM_VOL_CTL)&0x8F) | (vol << 4));
    /* config charge current */
    ool_write(PMU_REG_CHG_CUR_CTL, (ool_read(PMU_REG_CHG_CUR_CTL)&0xC0) | (cur));

    /* enable/disable charge */
    if (en) 
    {
        ool_write(PMU_REG_CHG_EN_CFG, ool_read(PMU_REG_CHG_EN_CFG) | 0x04);
    }
    else 
    {
        ool_write(PMU_REG_CHG_EN_CFG, ool_read(PMU_REG_CHG_EN_CFG) & ~0x04);
    }
}

void pmu_ioldo_voltage(enum pmu_ioldo_voltage_sel_t ioldo_voltage)
{
    /* set IOLDO output voltage */
    ool_write(PMU_REG_IOLDO_CFG_2, ((ool_read(PMU_REG_IOLDO_CFG_2)&0xf8)|  ioldo_voltage));
    ool_write(PMU_REG_IOLDO_CFG_3, ((ool_read(PMU_REG_IOLDO_CFG_3)&0x1f)| (ioldo_voltage << 5)));  
}

void pmu_set_pin_dir(enum system_port_t port, uint8_t bits, uint8_t dir)
{
    uint8_t dir_reg = PMU_REG_PORTA_OE;
    dir_reg += port;

    if(dir == GPIO_DIR_OUT) {
        ool_write(dir_reg, ool_read(dir_reg) | bits);
    }
    else {
        ool_write(dir_reg, ool_read(dir_reg) & (~bits));
    }
}

__attribute__((section("ram_code"))) void pmu_set_gpio_value(enum system_port_t port, uint8_t bits, uint8_t value)
{
    uint8_t sel_reg = PMU_REG_PORTA_LAST_STATUS;
    uint8_t write_sel_reg = PMU_REG_PORTA_V;
    sel_reg += port;
    write_sel_reg += port;
    if (value == 0)
        ool_write(write_sel_reg, (ool_read(sel_reg) & (~bits)));
    else
        ool_write(write_sel_reg, (ool_read(sel_reg) | bits));
}

__attribute__((section("ram_code"))) uint8_t pmu_get_gpio_value(enum system_port_t port, uint8_t bit)
{
    uint8_t sel_reg = PMU_REG_PORTA_LAST_STATUS;
    sel_reg += port;
    return ( (ool_read(sel_reg) & CO_BIT(bit))>>bit );
}

__attribute__((section("ram_code"))) void pmu_enable_isr(uint16_t isr_map)
{
    ool_pd_write16(PMU_REG_PD_INT_EN, ool_pd_read16(PMU_REG_PD_INT_EN) | isr_map);
}

void pmu_disable_isr(uint16_t isr_map)
{
    ool_pd_write16(PMU_REG_PD_INT_EN, ool_pd_read16(PMU_REG_PD_INT_EN) & (~isr_map));
}

uint16_t pmu_get_isr_state(void)
{
    return ool_pd_read16(PMU_REG_PD_INT_STATUS);
}

__attribute__((section("ram_code"))) void pmu_clear_isr_state(uint16_t state_map)
{
    GLOBAL_INT_DISABLE();
    ool_pd_write16(PMU_REG_PD_INT_CLR, state_map);
    co_delay_10us(5);
    ool_pd_write16(PMU_REG_PD_INT_CLR, 0);
    GLOBAL_INT_RESTORE();
}

void pmu_set_pin_to_PMU(enum system_port_t port, uint8_t bits)
{
    uint8_t sel_reg = PMU_REG_PORTA_SEL;
    sel_reg += port;
    ool_write(sel_reg, (ool_read(sel_reg) & (~bits)));
}

void pmu_set_pin_to_CPU(enum system_port_t port, uint8_t bits)
{
    uint8_t sel_reg = PMU_REG_PORTA_SEL;
    sel_reg += port;
    ool_write(sel_reg, (ool_read(sel_reg) | bits));
}

void pmu_set_pin_pull(enum system_port_t port, uint8_t bits, enum system_port_pull_t type)
{
    uint8_t sel_reg = PMU_REG_PORTA_PULL_EN;
    uint8_t pull_reg = PMU_REG_PORTA_PULL_SEL;
    sel_reg += port;
    pull_reg += port;

    if(type == GPIO_PULL_NONE) {
        ool_write(sel_reg, (ool_read(sel_reg) & (~bits)));
    }
    else {
        if(type == GPIO_PULL_UP) {
            ool_write(pull_reg, (ool_read(pull_reg) | bits));
        }
        else if(type == GPIO_PULL_DOWN) {
            ool_write(pull_reg, (ool_read(pull_reg) & (~bits)));
        }
        else {
            return;
        }
        ool_write(sel_reg, (ool_read(sel_reg) | bits));
    }
}

void pmu_set_pin_mux_cfg_sel(enum system_port_t port, enum pmu_gpio_mux_cfg_sel_t sel)
{
    uint8_t sel_reg = PMU_REG_GPIO_MUX_CFG_SEL;

    if(sel == PMU_GPIO_MUX_CFG_PK) {
        ool_write(sel_reg, ool_read(sel_reg) | (1<<port));
    }
    else {
        ool_write(sel_reg, ool_read(sel_reg) & (~(1<<port)));
    }
}

void pmu_set_pin_mux(enum system_port_t port, enum system_port_bit_t bit, enum pmu_pin_func_t func)
{
    switch(port) {
        case GPIO_PORT_A:
            ool_pd_write16(PMU_REG_PD_PORTA_MUX, (ool_pd_read16(PMU_REG_PD_PORTA_MUX) & (~(0x03<<(bit*2))) | (func<<(bit*2))));
            break;
        case GPIO_PORT_B:
            ool_pd_write16(PMU_REG_PD_PORTB_MUX, (ool_pd_read16(PMU_REG_PD_PORTB_MUX) & (~(0x03<<(bit*2))) | (func<<(bit*2))));
            break;
        case GPIO_PORT_C:
            ool_pd_write16(PMU_REG_PD_PORTC_MUX, (ool_pd_read16(PMU_REG_PD_PORTC_MUX) & (~(0x03<<(bit*2))) | (func<<(bit*2))));
            break;
        case GPIO_PORT_D:
            ool_pd_write16(PMU_REG_PD_PORTD_MUX, (ool_pd_read16(PMU_REG_PD_PORTD_MUX) & (~(0x03<<(bit*2))) | (func<<(bit*2))));
            break;
        case GPIO_PORT_E:
            ool_pd_write16(PMU_REG_PD_PORTE_MUX, (ool_pd_read16(PMU_REG_PD_PORTE_MUX) & (~(0x03<<(bit*2))) | (func<<(bit*2))));
            break;
    }
}

void pmu_set_pin_xor_en(enum system_port_t port, uint8_t bits, bool en)
{
    uint8_t xor_reg = PMU_REG_PORTA_XOR_EN;

    xor_reg += port;
    
    if(en) {
        ool_write(xor_reg, ool_read(xor_reg) | (bits));
    }
    else {
        ool_write(xor_reg, ool_read(xor_reg) & (~bits));
    }
}

/*********************************************************************
 * @fn      pmu_charging_monitor_en
 *
 * @brief   Charging in/out monitor interrupt enable
 */
void pmu_charging_monitor_en(enum charge_type charge)
{
    if (charge == PMU_CHARGING_IN) 
    {
        ool_pd_write(PMU_REG_PD_ANA_INT_LEVEL, 0x00);
    }
    else 
    {
        ool_pd_write(PMU_REG_PD_ANA_INT_LEVEL, PMU_ACOK_INT_TRIG_LEVEL);
    }
    
    ool_pd_write(PMU_REG_PD_ACOK_DEB_LEN, 0x10);

    pmu_enable_isr(PMU_ACOK_INT_EN);
}

/*********************************************************************
 * @fn      pmu_battery_full_monitor_en
 *
 * @brief   battery_full monitor interrupt enable
 */
void pmu_battery_full_monitor_en(void)
{
    ool_pd_write(PMU_REG_PD_BAT_DEB_LEN, 0x10);

    pmu_enable_isr(PMU_BAT_FULL_INT_EN);
}

/*********************************************************************
 * @fn      pmu_buck_mode_enable
 *
 * @brief   power select buck mode
 */
void pmu_buck_mode_enable(void)
{
    /* enable buck mode */
    ool_write(PMU_REG_GATE_CTRL_0, (ool_read(PMU_REG_GATE_CTRL_0) & 0xFD));
    /* for delay */
    ool_read(PMU_REG_GATE_CTRL_0);
    ool_read(PMU_REG_GATE_CTRL_0);
    /* disable ldo mode */
    ool_write(PMU_REG_GATE_CTRL_0, (ool_read(PMU_REG_GATE_CTRL_0) | 0x04));
    /* reconfigure buck working frequency */
    ool_write(PMU_REG_BUCK_CFG_2, 0x18);
    /* disable buck RES */
    ool_write(PMU_REG_BUCK_CFG_3, (ool_read(PMU_REG_BUCK_CFG_3) & 0xBF));
    /* Buck PWM mode */
    ool_write(PMU_REG_BUCK_CFG_6, ool_read(PMU_REG_BUCK_CFG_6) | 0x80);
    /* BUCK_CZ_ST_IND_EN */
    ool_write(PMU_REG_BUCK_CFG_4, 0x90);
}

/*********************************************************************
 * @fn      pmu_ldo_mode_enable
 *
 * @brief   power select ldo mode
 */
void pmu_ldo_mode_enable(void)
{
    /* enable ldo mode */
    ool_write(PMU_REG_GATE_CTRL_0, (ool_read(PMU_REG_GATE_CTRL_0) & 0xFB));
    /* for delay */
    ool_read(PMU_REG_GATE_CTRL_0);
    ool_read(PMU_REG_GATE_CTRL_0);
    /* disable buck mode */
    ool_write(PMU_REG_GATE_CTRL_0, (ool_read(PMU_REG_GATE_CTRL_0) | 0x02));
}

/*********************************************************************
 * @fn      pmu_port_wakeup_func_set
 *
 * @brief   PortPin wakeup function congfig
 *
 * @param   port: Select Port.
 * @return  bits: Select Pin. 0x01--PIN0¡¢0x80--PIN7
 */
void pmu_port_wakeup_func_set(enum system_port_t port, uint8_t bits)
{
    uint8_t last_status_reg = PMU_REG_PORTA_LAST_STATUS;

    last_status_reg += port;
    
    /* PMU control */
    pmu_set_pin_to_PMU(port, bits);
    
    /* Config input¡¢Pull up */
    pmu_set_pin_pull(port, bits, GPIO_PULL_UP);
    pmu_set_pin_dir(port, bits, GPIO_DIR_IN);
    
    /* Read the current value and write */
    ool_write(last_status_reg, ool_read(last_status_reg));

    /* XOR Enable */
    pmu_set_pin_xor_en(port, bits, true);
    
    /* XOR interrupt enable */
    pmu_enable_isr(PMU_GPIO_XOR_INT_EN);
}

/*********************************************************************
 * @fn      pmu_port_wakeup_func_clear
 *
 * @brief   Get rtc current counter value
 *
 * @param   port: Select Port.
 * @return  bits: Select Pin. 0x01--PIN0¡¢0x80--PIN7
 */
void pmu_port_wakeup_func_clear(enum system_port_t port, uint8_t bits)
{
    /* CPU control */
    pmu_set_pin_to_CPU(port, bits);

    /* XOR Disable */
    pmu_set_pin_xor_en(port, bits, false);
}

/*********************************************************************
 * @fn      pmu_shutdown
 *
 * @brief   put system into shutdown mode. leakage is 0.8uA. Only HDONKEY
 *          can wake up system from shutdown mode.
 */
void pmu_shutdown(void)
{
    __disable_irq();
    uint8_t org_value = ool_read(PMU_REG_HDONKEY_CTRL);
    ool_write(PMU_REG_HDONKEY_CTRL, org_value | 0x40);
    ool_write(PMU_REG_HDONKEY_CTRL, org_value | 0x60);
    ool_write(PMU_REG_HDONKEY_CTRL, org_value | 0xe0);
}

/*********************************************************************
 * @fn      pmu_cp_trim_config
 *
 * @brief   CP(Chip Probing) trim value config.
 */
void pmu_cp_trim_config(void)
{
    struct_eFuseParam_t eFuseParam;

    uint32_t *TempPointer = (uint32_t *)&eFuseParam;
    
    /* eFuse clock enable */
    __SYSTEM_EFUSE_CLK_ENABLE();

    /* config read mode */
    EFUSE->eFuse_Ctrl = EFUSE_READ_MODE;
    /* wait config done */
    while(!(EFUSE->eFuse_Ctrl & EFUSE_CHECK_DONE));
    /* read data */
    *TempPointer++ = EFUSE->eFuse_Data0;
    *TempPointer++ = EFUSE->eFuse_Data1;
    *TempPointer++ = EFUSE->eFuse_Data2;
    *TempPointer++ = EFUSE->eFuse_Data3;
    
    eFuseParam.PKVDD_CODE -= 2;
    
    if (eFuseParam.Year != 0 && eFuseParam.Week != 0)
    {
        ool_write(0x40, ool_read(0x40) | 0x40);
        ool_write(PMU_REG_POWARN_CTRL, (ool_read(PMU_REG_POWARN_CTRL)&0xE0)| eFuseParam.BBG_CODE);
        ool_write(PMU_REG_SYSLDO_CFG,  (ool_read(PMU_REG_SYSLDO_CFG)&0xF8) | eFuseParam.SYSLDO_CODE);
        ool_write(PMU_REG_BUCK_CFG_6,  (ool_read(PMU_REG_BUCK_CFG_6)&0x8F) |(eFuseParam.BFB_CODE << 4));   // BFB   1.35V
        ool_write(PMU_REG_SBG_CTRL,    (ool_read(PMU_REG_SBG_CTRL)&0xF0)   | eFuseParam.SBG_CODE);
        ool_write(PMU_REG_PKVDD_CFG_2, (ool_read(PMU_REG_PKVDD_CFG_2)&0x0F)|(eFuseParam.PKVDD_CODE << 4)); // PKVDD 1.1V
        ool_write(PMU_REG_DLDO_CFG_1,  (ool_read(PMU_REG_DLDO_CFG_1)&0x8F) |(eFuseParam.DLDO_CODE  << 4)); // DLDO  1.1V
    }
}

/*********************************************************************
 * @fn      pmu_ft_trim_config
 *
 * @brief   FT(final test) trim value config.
 */
void pmu_ft_trim_config(struct_FT_Param_t *FT_Param)
{
    extern uint32_t modem_param_table[];
	uint8_t *TempPointer = (uint8_t *)FT_Param;
    uint8_t *modem_ptr = (void *)modem_param_table;
	
	flash_OTP_read(0x1000, 256, TempPointer);
	flash_OTP_read(0x2000, sizeof(struct_FT_Param_t)-256, TempPointer + 256);
	
	if ((FT_Param->u16_version >= 0xA000) && (FT_Param->u16_version <= 0xA006))
    {
        if ((FT_Param->Param.V6.TxChannelParam[0].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[0].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x78) = FT_Param->Param.V6.TxChannelParam[0].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x82) = FT_Param->Param.V6.TxChannelParam[0].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[5].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[5].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x79) = FT_Param->Param.V6.TxChannelParam[5].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x83) = FT_Param->Param.V6.TxChannelParam[5].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[9].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[9].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7A) = FT_Param->Param.V6.TxChannelParam[9].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x84) = FT_Param->Param.V6.TxChannelParam[9].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[13].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[13].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7B) = FT_Param->Param.V6.TxChannelParam[13].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x85) = FT_Param->Param.V6.TxChannelParam[13].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[19].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[19].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7C) = FT_Param->Param.V6.TxChannelParam[19].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x86) = FT_Param->Param.V6.TxChannelParam[19].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[21].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[21].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7D) = FT_Param->Param.V6.TxChannelParam[21].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x87) = FT_Param->Param.V6.TxChannelParam[21].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[25].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[25].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7E) = FT_Param->Param.V6.TxChannelParam[25].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x88) = FT_Param->Param.V6.TxChannelParam[25].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[29].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[29].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7F) = FT_Param->Param.V6.TxChannelParam[29].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x89) = FT_Param->Param.V6.TxChannelParam[29].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[33].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[33].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x80) = FT_Param->Param.V6.TxChannelParam[33].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x8A) = FT_Param->Param.V6.TxChannelParam[33].Modem_MODDAC;
        }
        if ((FT_Param->Param.V6.TxChannelParam[39].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V6.TxChannelParam[39].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x81) = FT_Param->Param.V6.TxChannelParam[39].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x8B) = FT_Param->Param.V6.TxChannelParam[39].Modem_MODDAC;
        }
        
        ADC_Cal_Param.u16_slopeA = FT_Param->u16_slopeA;
        ADC_Cal_Param.u16_slopeB = FT_Param->Param.V6.u16_slopeB;
        ADC_Cal_Param.s16_constantA = FT_Param->Param.V6.s16_constantA;
        ADC_Cal_Param.s16_constantB = FT_Param->Param.V6.s16_constantB;
    }
    else if(FT_Param->u16_version <= 0xB000) {
        if ((FT_Param->Param.V7.TxChannelParam[0].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[0].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x78) = FT_Param->Param.V7.TxChannelParam[0].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x82) = FT_Param->Param.V7.TxChannelParam[0].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[1].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[1].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x79) = FT_Param->Param.V7.TxChannelParam[1].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x83) = FT_Param->Param.V7.TxChannelParam[1].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[2].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[2].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7A) = FT_Param->Param.V7.TxChannelParam[2].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x84) = FT_Param->Param.V7.TxChannelParam[2].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[3].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[3].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7B) = FT_Param->Param.V7.TxChannelParam[3].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x85) = FT_Param->Param.V7.TxChannelParam[3].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[4].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[4].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7C) = FT_Param->Param.V7.TxChannelParam[4].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x86) = FT_Param->Param.V7.TxChannelParam[4].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[5].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[5].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7D) = FT_Param->Param.V7.TxChannelParam[5].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x87) = FT_Param->Param.V7.TxChannelParam[5].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[6].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[6].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7E) = FT_Param->Param.V7.TxChannelParam[6].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x88) = FT_Param->Param.V7.TxChannelParam[6].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[7].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[7].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x7F) = FT_Param->Param.V7.TxChannelParam[7].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x89) = FT_Param->Param.V7.TxChannelParam[7].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[8].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[8].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x80) = FT_Param->Param.V7.TxChannelParam[8].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x8A) = FT_Param->Param.V7.TxChannelParam[8].Modem_MODDAC;
        }
        if ((FT_Param->Param.V7.TxChannelParam[9].Modem_VCO_GAU != 0)
                && (FT_Param->Param.V7.TxChannelParam[9].Modem_MODDAC != 0)) {
            *(uint8_t *)(modem_ptr + 0x81) = FT_Param->Param.V7.TxChannelParam[9].Modem_VCO_GAU;
            *(uint8_t *)(modem_ptr + 0x8B) = FT_Param->Param.V7.TxChannelParam[9].Modem_MODDAC;
        }

        ADC_Cal_Param.u16_slopeA = FT_Param->u16_slopeA;
        ADC_Cal_Param.u16_slopeB = FT_Param->Param.V7.u16_slopeB;
        ADC_Cal_Param.s16_constantA = FT_Param->Param.V7.s16_constantA;
        ADC_Cal_Param.s16_constantB = FT_Param->Param.V7.s16_constantB;
        
        if (FT_Param->Param.V7.s16_constantA < 0)
        {
            if ((ADC_Cal_Param.s16_constantA % 1000) == 0)   /* N */
                ADC_Cal_Param.s16_constantA = FT_Param->Param.V7.s16_constantA;
            else if ((ADC_Cal_Param.s16_constantA % 1000) == -464)    /* - X2 */
            {
                ADC_Cal_Param.s16_constantA = -66 + (FT_Param->Param.V7.s16_constantA / 1000);
                ADC_Cal_Param.s16_constantA *= 1000;
            }
            else if ((ADC_Cal_Param.s16_constantA % 1000) == -536)    /* + X1 */
            {
                ADC_Cal_Param.s16_constantA = 65 + (FT_Param->Param.V7.s16_constantA / 1000);
                ADC_Cal_Param.s16_constantA *= 1000;
            }
        }
        else
        {
            if ((ADC_Cal_Param.s16_constantA % 1000) == 0)    /* N */
                ADC_Cal_Param.s16_constantA = FT_Param->Param.V7.s16_constantA;
            else if ((ADC_Cal_Param.s16_constantA % 1000) == 536)    /* - X1 */
            {
                ADC_Cal_Param.s16_constantA = 65 - (FT_Param->Param.V7.s16_constantA / 1000);
                ADC_Cal_Param.s16_constantA *= -1000;
            }
            else if ((ADC_Cal_Param.s16_constantA % 1000) == 464)    /* + X2 */
            {
                ADC_Cal_Param.s16_constantA = 66 + (FT_Param->Param.V7.s16_constantA / 1000);
                ADC_Cal_Param.s16_constantA *= 1000;
            }
            else if ((ADC_Cal_Param.s16_constantA % 1000) == 72)     /* - X3 */
            {
                ADC_Cal_Param.s16_constantA = 131 - (FT_Param->Param.V7.s16_constantA / 1000);
                ADC_Cal_Param.s16_constantA *= -1000;
            }
        }
    }
}

/*********************************************************************
 * @fn      pmu_get_adc_cal_param
 *
 * @brief   get adc ft calibration param.
 */
struct_ADC_Cal_Param_t *pmu_get_adc_cal_param(void)
{
    return &ADC_Cal_Param;
}

/*********************************************************************
 * @fn      pmu_low_speed_xtal_config
 *
 * @brief   pmu clock config
 */
void pmu_low_speed_xtal_config(enum pmu_clock_sel_t pmu_clock_sel)
{
    if (pmu_clock_sel == PMU_CLK_SEL_RCLP_DIV2)
    {
        /* Select the internal RC clock as pmu clock source */
        ool_write(PMU_REG_CLK_CTRL, (ool_read(PMU_REG_CLK_CTRL) & ~PMU_CLK_SEL_MASK) | PMU_CLK_SEL_RCLP_DIV2);
    }
    else if (pmu_clock_sel == PMU_CLK_SEL_XTAL32768)
    {
        /* enable XTAL */
        ool_write(PMU_REG_IOLDO_CFG_3, ool_read(PMU_REG_IOLDO_CFG_3) & 0xEF);
        /* Select the external low speed XTAL as pmu clock source */
        ool_write(PMU_REG_CLK_CTRL, (ool_read(PMU_REG_CLK_CTRL) & ~PMU_CLK_SEL_MASK) | PMU_CLK_SEL_XTAL32768);
    }
}

/*********************************************************************
 * @fn      pmu_Anti_shake_key_config
 *
 * @brief   Anti shake key config. 
 *          In low-power mode, it supports a pair Anti shake key detection.
 *          1. Only Detection level change.
 *          2. Bipolar detection.
 *          3. One of the pair of pins must remain unchanged.
 *
 * @param   Key_A: Anti shake key A Select port.
 * @param   Key_B: Anti shake key B Select port.
 * @param   fu8_filter: filter value. 1:1ms ~ 255:255ms
 */
void pmu_Anti_shake_key_config(enum filter_Key_A Key_A, enum filter_Key_B Key_B, uint8_t fu8_filter)
{
    /* Anti shake key clock enable */
    ool_write(PMU_REG_CLK_EN, ool_read(PMU_REG_CLK_EN) | (PMU_DEB_CLK_EN | PMU_QDEC_CLK_EN | PMU_DEB_DIV_EN));
    /* Stop reset */
    ool_write(PMU_REG_RST_CTRL, ool_read(PMU_REG_RST_CTRL) & ~(PMU_DEB_SFT_RST | PMU_QDEC_RST_DIS));

    /* IRQ mode config */
    ool_pd_write(PMU_REG_QDEC_CTRL0, 0x04);
    /* filter enable */
    ool_pd_write(PMU_REG_QDEC_CTRL1, 0x07);
    /* filter value */
    ool_pd_write(PMU_REG_QDEC_DEB_LEN, fu8_filter);
    /* key select port */
    ool_pd_write(PMU_REG_QDEC_MUX_0, (Key_A | Key_B));

    /* enable pmu Anti shake key interrupt */
    pmu_enable_isr(PMU_QDEC_INT_EN);
}

__attribute__((weak)) void pmu_gpio_isr(uint32_t pin_value)
{
}

__attribute__((weak)) void pmu_Anti_shake_key_isr(void)
{
}



__attribute__((section("ram_code"))) void pmu_isr(void)
{
    uint16_t state = pmu_get_isr_state();


    if(state & PMU_CALI_INT_STATUS) {
        /* restart calibration */
        pmu_get_rc_clk(true);
        pmu_calibration_restart(LP_RC_CALIB_LARGE_CNT);
        LOG_INFO(NULL, "lp clock is %d.\r\n", pmu_get_rc_clk(false));
    }
    if(state & PMU_GPIO_XOR_INT_STATUS) {
        uint32_t pin_value = ool_read32(PMU_REG_PORTA_LAST_STATUS);
        LOG_DBG(NULL, "pmu gpio value is %08x.\r\n", pin_value);
        pmu_gpio_isr(pin_value);
        ool_write32(PMU_REG_PORTA_LAST_STATUS, pin_value);
    }
    #if ENABLE_SYSTEM_PROTECTION_IN_LVD == 1
    if(state & PMU_LVD_FAST_INT_STATUS)
    {
        extern void system_lvd_protect_handle(void);
        LOG_INFO(NULL,"LVD");
        system_lvd_protect_handle();
    }
    #endif

    if(state & PMU_QDEC_INT_STATUS)
    {
        pmu_Anti_shake_key_isr();
    }
    
    LOG_INFO(NULL, "pmu_isr: %04x.\r\n", state);
    pmu_clear_isr_state(state);
}

