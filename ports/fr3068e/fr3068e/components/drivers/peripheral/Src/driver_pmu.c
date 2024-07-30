#include "fr30xx.h"
#include "co_util.h"

#define PMU_FSM_ON_DIV          0x03  //the follow tcnt based <((DIV+1))*40K_CLK(rc)>
#define PMU_PMU_ON_CNT          (0x18<<0)
//the follow tcnt should <= PMU_PMU_ON_CNT
#define PMU_BBG_ON_CNT          (0x01<<0)
#define PMU_SYSBUCK_ON_CNT      (0x02<<0)
#define PMU_IOBUCK_ON_CNT       (0x02<<0)
#define PMU_IOLDO1_ON_CNT       (0x02<<0)
#define PMU_IOLDO2_ON_CNT       (0x02<<0)
#define PMU_APPDLDO_ON_CNT      (0x06<<0)
#define PMU_DSPDLDO_ON_CNT      (0x06<<0)
#define PMU_PKSTPD_ON_CNT       (0x08<<0)

#define PMU_MEMPK_ON_CNT        (0x0b<<0)
#define PMU_MEMPD_ON_CNT        (0x09<<0)
#define PMU_RAMPK_ON_CNT        (0x0c<<0)

#define PMU_OSCLDO_ON_CNT       (0x06<<0)
#define PMU_OSC_ON_CNT          (0x08<<0)
#define PMU_RC24PD_ON_CNT       (0x08<<0)
#define PMU_PMUISO_ON_CNT       (0x17<<0)
#define PMU_IOISO_ON_CNT        (0x17<<0)
#define PMU_IORTON_ON_CNT       (0x17<<0)
#define PMU_IOSNS_ON_CNT        (0x17<<0)
#define PMU_RSTN_ON_CNT         (0x18<<0)

#define PMU_FSM_OFF_DIV         (0x00<<5)  //the follow tcnt based <((DIV+1))*40K_CLK(rc)>
#define PMU_PMU_OFF_CNT         (0x06<<5)
//the follow tcnt should <= PMU_PMU_OFF_CNT
#define PMU_BBG_OFF_CNT         (0x05<<5)
#define PMU_SYSBUCK_OFF_CNT     (0x04<<5)
#define PMU_IOBUCK_OFF_CNT      (0x01<<5)
#define PMU_IOLDO1_OFF_CNT      (0x01<<5)
#define PMU_IOLDO2_OFF_CNT      (0x01<<5)
#define PMU_APPDLDO_OFF_CNT     (0x03<<5)
#define PMU_DSPDLDO_OFF_CNT     (0x03<<5)
#define PMU_PKSTPD_OFF_CNT      (0x01<<5)
#define PMU_MEMPK_OFF_CNT       (0x01<<5)
#define PMU_MEMPD_OFF_CNT       (0x03<<5)
#define PMU_OSCLDO_OFF_CNT      (0x03<<5)
#define PMU_OSC_OFF_CNT         (0x01<<5)
#define PMU_RC24PD_OFF_CNT      (0x03<<5)
#define PMU_RAMPK_OFF_CNT       (0x01<<5)
#define PMU_PMUISO_OFF_CNT      (0x01<<5)
#define PMU_IOISO_OFF_CNT       (0x02<<5)
#define PMU_IORTON_OFF_CNT      (0x02<<5)
#define PMU_IOSNS_OFF_CNT       (0x02<<5)
#define PMU_RSTN_OFF_CNT        (0x01<<5)

__RAM_CODE static uint32_t us_2_lpcycles(uint32_t us)
{
    uint32_t lpcycles;        
    uint32_t tmp_low, tmp_high;

    mul_64(&tmp_low, &tmp_high, system_get_LPRCCLK(), us);
    lpcycles = simple_div_64(tmp_low, tmp_high, 1000000);

    return(lpcycles);
}

void pmu_init(void)
{ 
    /* setup sleep and wakeup counters */
    ool_write(PMU_REG_FSM_TIMER         , PMU_FSM_ON_DIV     | PMU_FSM_OFF_DIV    );
    ool_write(PMU_REG_PMU_ONOFF_CNT     , PMU_PMU_ON_CNT     | PMU_PMU_OFF_CNT    );
    ool_write(PMU_REG_BBG_ONOFF_CNT     , PMU_BBG_ON_CNT     | PMU_BBG_OFF_CNT    );
    ool_write(PMU_REG_SYSBUCK_ONOFF_CNT , PMU_SYSBUCK_ON_CNT | PMU_SYSBUCK_OFF_CNT);
    ool_write(PMU_REG_IOBUCK_ONOFF_CNT  , PMU_IOBUCK_ON_CNT  | PMU_IOBUCK_OFF_CNT );
    ool_write(PMU_REG_IOLDO1_ONOFF_CNT  , PMU_IOLDO1_ON_CNT  | PMU_IOLDO1_OFF_CNT );
    ool_write(PMU_REG_IOLDO2_ONOFF_CNT  , PMU_IOLDO2_ON_CNT  | PMU_IOLDO2_OFF_CNT );
    ool_write(PMU_REG_APPDLDO_ONOFF_CNT , PMU_APPDLDO_ON_CNT | PMU_APPDLDO_OFF_CNT);
    ool_write(PMU_REG_DSPDLDO_ONOFF_CNT , PMU_DSPDLDO_ON_CNT | PMU_DSPDLDO_OFF_CNT);
    ool_write(PMU_REG_PKSTPD_ONOFF_CNT  , PMU_PKSTPD_ON_CNT  | PMU_PKSTPD_OFF_CNT );
    ool_write(PMU_REG_MEMPK_ONOFF_CNT   , PMU_MEMPK_ON_CNT   | PMU_MEMPK_OFF_CNT  );
    ool_write(PMU_REG_MEMPD_ONOFF_CNT   , PMU_MEMPD_ON_CNT   | PMU_MEMPD_OFF_CNT  );
    ool_write(PMU_REG_OSCLDO_ONOFF_CNT  , PMU_OSCLDO_ON_CNT  | PMU_OSCLDO_OFF_CNT );
    ool_write(PMU_REG_OSC_ONOFF_CNT     , PMU_OSC_ON_CNT     | PMU_OSC_OFF_CNT    );
    ool_write(PMU_REG_RC24PD_ONOFF_CNT  , PMU_RC24PD_ON_CNT  | PMU_RC24PD_OFF_CNT );
    ool_write(PMU_REG_RAMPK_ONOFF_CNT   , PMU_RAMPK_ON_CNT   | PMU_RAMPK_OFF_CNT  );
    ool_write(PMU_REG_PMUISO_ONOFF_CNT  , PMU_PMUISO_ON_CNT  | PMU_PMUISO_OFF_CNT );
    ool_write(PMU_REG_IOISO_ONOFF_CNT   , PMU_IOISO_ON_CNT   | PMU_IOISO_OFF_CNT  );
    ool_write(PMU_REG_IORTON_ONOFF_CNT  , PMU_IORTON_ON_CNT  | PMU_IORTON_OFF_CNT );
    ool_write(PMU_REG_IOSNS_ONOFF_CNT   , PMU_IOSNS_ON_CNT   | PMU_IOSNS_OFF_CNT  );
    ool_write(PMU_REG_RSTN_ONOFF_CNT    , PMU_RSTN_ON_CNT    | PMU_RSTN_OFF_CNT   );

    /* splite PKVDDH and PKVDD */
    ool_write(PMU_REG_PKVDDH_CTRL_0, 0x60);
    ool_write(PMU_REG_PKVDDH_CTRL_0, 0x70);

    /* shut down OSC buffer */
    ool_write(PMU_REG_OSC_CTRL_1, ool_read(PMU_REG_OSC_CTRL_1) & (~0x04));
    /* PLL analog clock enable */
    ool_write(PMU_REG_OSC_CTRL_1, ool_read(PMU_REG_OSC_CTRL_1) | (PMU_OSC_CLK_REF_SPLL_EN_BIT | PMU_OSC_CLK_REF_AUPLL_EN_BIT)); 
    ool_write(PMU_REG_OSC_CTRL_1, ool_read(PMU_REG_OSC_CTRL_1) & (~(PMU_OSC_AUPLL_PD_BIT|PMU_OSC_CLK_OUT_BUF_EN_BIT))); 
    /* set PKVDD to 1.1v */
    ool_write(PMU_REG_PKVDD_CTRL, 0xca);
    /* set PKVDDH to 1.1v, set RAMPKVDD to 0.7v */
    ool_write(PMU_REG_PKVDDH_CTRL_1, 0x34);

    /*sram ldo always on*/
    ool_write(PMU_REG_PMU_GATE_M,ool_read(PMU_REG_PMU_GATE_M)|0x08);
    
    /* buck load inductor will not be shorted */
    ool_write(PMU_REG_SYSBUCK_CTRL_1, 0x43);
    /* disable internal load of sys-buck and io-buck */
    ool_write(PMU_REG_IOBUCK_CTRL_4, 0x73);
    ool_write(PMU_REG_SYSBUCK_CTRL_4, 0x73);
    
    /* 
     * IOLDO dynamic bias, used to avoid unexpect leakage when IOLDO 
     * output configuration is large than VBAT input voltage
     */
    ool_write(PMU_REG_IOLDO1_CTRL_1, ool_read(PMU_REG_IOLDO1_CTRL_1) | (1<<4));
    ool_write(PMU_REG_IOLDO2_CTRL_1, ool_read(PMU_REG_IOLDO2_CTRL_1) | (1<<4));
    
    /* enable BT sleep timer clock */
    ool_write(PMU_REG_CLK_EN, PMU_LP_TICK_CLK_EN_BIT);

#if 0
    /* sleep and wake up is controlled by TICK */
    ool_write(PMU_REG_SLP_WK_SRC, PMU_SLP_TICK_EN_BIT | PMU_WK_TICK_EN_BIT);

    /* 
     * BIT0: BB generate sleep signal en 
     * BIT1: external interrupt wakeup BT timer enable
     */
    ool_write(PMU_REG_TICK_CTRL, PMU_TICK_SLP_PMU_EN_BIT | PMU_EXT_WK_TICK_EN_BIT | PMU_IRQ_WK_TICK_EN_BIT);
    
    /* reset lp tick */
    ool_write(PMU_REG_RST, PMU_LP_TICK_SFT_RST_BIT);
    while (ool_read(PMU_REG_RST) & PMU_LP_TICK_SFT_RST_BIT);
#else
    /* sleep and wake up is controlled by TICK */
    ool_write(PMU_REG_SLP_WK_SRC, PMU_SLP_CPU_EN_BIT | PMU_WK_IRQ_EN_BIT);
    
    /* release RTC clock */
    ool_write(PMU_REG_CLK_EN, ool_read(PMU_REG_CLK_EN) | PMU_RTC_CLK_EN_BIT);
    /* release interrupt mask of RTC alarm B */
    ool_write16(PMU_REG_INT_MASK, ool_read16(PMU_REG_INT_MASK) | PMU_RTC_B_INT_MSK_BIT);
#endif

    /* enable GPIO wakeup system as default setting */
    ool_write(PMU_REG_WKUP_INT_EN, 0x03);

    /* disable power fsm */
    ool_write(PMU_REG_PWR_GATE, 0xff);
    /* IO33 and IO18 always on */
    ool_write(PMU_REG_PMU_MASK_L, 0x18);
    /* set mask of GPIO SNS & ISO */
    ool_write(PMU_REG_PMU_MASK_M, ool_read(PMU_REG_PMU_MASK_M) | 0x80 | 0x20);  //bit7 : GPIO_SNS; bit5 : GPIO_ISO

//    /* configure PMU_PIN_8 output BBG_EN signal */
//    ool_write(PMU_REG_DIAG_CTRL, 0x82);
////    ool_write16(PMU_REG_PIN_IOMUX_L, 0xffff);
//    ool_write(PMU_REG_PIN_IOMUX_H, 0x03);
//    /* disable input as default setting */
//    ool_write16(PMU_REG_PIN_INPUT_EN, 0x0000);
    
    /* remove internal cap of osc */
    ool_write(PMU_REG_OSC_CTRL_4, 0x20);

#ifndef CHIP_UPDATE
    /* ADkey pull up Resistor disable */
    ool_write(PMU_REG_ADKEY_CTRL, ool_read(PMU_REG_ADKEY_CTRL) & ~PMU_ADKEY_PU_RES_EN_BIT);
#endif
    /* OSC config */
    ool_write(PMU_REG_OSC_CTRL_0, 0x2A);
    
    trim_cp_config();
    trim_ft_config();
}

__RAM_CODE void pmu_adjust_onoff_timing(uint16_t rst_us)
{
    uint8_t rst_cnt = (us_2_lpcycles(rst_us) + PMU_FSM_ON_DIV) / (PMU_FSM_ON_DIV + 1);
    if (PMU_RAMPK_ON_CNT >= rst_cnt) {
        while(1);
    }

    ool_write(PMU_REG_PMUISO_ONOFF_CNT  , ((rst_cnt-1)<<0)  | PMU_PMUISO_OFF_CNT );
    ool_write(PMU_REG_IOISO_ONOFF_CNT   , ((rst_cnt-1)<<0)  | PMU_IOISO_OFF_CNT );
    ool_write(PMU_REG_IORTON_ONOFF_CNT  , ((rst_cnt-1)<<0)  | PMU_IORTON_OFF_CNT );
    ool_write(PMU_REG_IOSNS_ONOFF_CNT   , ((rst_cnt-1)<<0)  | PMU_IOSNS_OFF_CNT );
    ool_write(PMU_REG_RSTN_ONOFF_CNT    , (rst_cnt<<0)      | PMU_RSTN_OFF_CNT    );
    ool_write(PMU_REG_PMU_ONOFF_CNT     , (rst_cnt<<0)      | PMU_PMU_OFF_CNT   );
}

/******************************************************************************
 * @fn      pmu_adc_power_ctrl
 *
 * @brief   ADC power control. true:  enable. 
 *                             false: disable.
 */
void pmu_adc_power_ctrl(bool enable)
{
    if (enable)
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) | PMU_ADC_CTL_POWER_BIT);
    else
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) & ~PMU_ADC_CTL_POWER_BIT);
}

/******************************************************************************
 * @fn      pmu_adc_vbat_power_ctrl
 *
 * @brief   VBAT(Battery level detection) power control. true:  enable. 
 *                                                       false: disable.
 */
void pmu_adc_vbat_power_ctrl(bool enable)
{
    if (enable)
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) | PMU_ADC_CTL_VBAT_EN_BIT);
    else
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) & ~PMU_ADC_CTL_VBAT_EN_BIT);
}

/******************************************************************************
 * @fn      pmu_adc_vbe_power_ctrl
 *
 * @brief   VBE(For temperature detection) power control. true:  enable. 
 *                                                        false: disable.
 */
void pmu_adc_vbe_power_ctrl(bool enable)
{
    if (enable)
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) | PMU_ADC_CTL_VBE_EN_BIT);
    else
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) & ~PMU_ADC_CTL_VBE_EN_BIT);
}

/******************************************************************************
 * @fn      pmu_adc_pga_power_ctrl
 *
 * @brief   PGA(Programmable Gain Amplifier) power control. true:  enable. 
 *                                                          false: disable.
 */
void pmu_adc_pga_power_ctrl(bool enable)
{
    if (enable)
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) | PMU_ADC_CTL_PGA_EN_BIT);
    else
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) & ~PMU_ADC_CTL_PGA_EN_BIT);
}

/******************************************************************************
 * @fn      pmu_adc_micbias_power_ctrl
 *
 * @brief   MICBIAS power control. true:  enable. 
 *                                 false: disable.
 */
void pmu_adc_micbias_power_ctrl(bool enable)
{
    if (enable)
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) | PMU_ADC_CTL_MICBIAS_EN_BIT);
    else
        ool_write(PMU_REG_ADC_CTL, ool_read(PMU_REG_ADC_CTL) & ~PMU_ADC_CTL_MICBIAS_EN_BIT);
}

/******************************************************************************
 * @fn      pmu_efuse_power_ctrl
 *
 * @brief   EFUSEpower control. true:  enable. 
 *                              false: disable.
 */
void pmu_efuse_power_ctrl(bool enable)
{
    if (enable)
        ool_write(PMU_REG_EFUSE_CTL, ool_read(PMU_REG_EFUSE_CTL) | PMU_EFUSE_CTL_POWER_BIT);
    else
        ool_write(PMU_REG_EFUSE_CTL, ool_read(PMU_REG_EFUSE_CTL) & ~PMU_EFUSE_CTL_POWER_BIT);
}

/******************************************************************************
 * @fn      pmu_psram_power_ctrl
 *
 * @brief   ADC power control. true:  enable. 
 *                             false: disable.
 */
void pmu_psram_power_ctrl(bool enable)
{
    if (enable)
        ool_write(PMU_REG_PWR_CTL, ool_read(PMU_REG_PWR_CTL) | PMU_PSRAM_PWR_BIT);
    else
        ool_write(PMU_REG_PWR_CTL, ool_read(PMU_REG_PWR_CTL) & ~PMU_PSRAM_PWR_BIT);
}

/*********************************************************************
 * @fn      pmu_battery_full_monitor_en
 *
 * @brief   battery_full monitor interrupt enable
 */
void pmu_battery_full_monitor_en(enum_PMU_battery_type_t battery_type)
{
    if (battery_type == PMU_BATTERY_FULL)
        ool_write(PMU_REG_ANA_LEVEL, ool_read(PMU_REG_ANA_LEVEL) & ~PMU_BATFULL_LEVEL_BIT);
    else
        ool_write(PMU_REG_ANA_LEVEL, ool_read(PMU_REG_ANA_LEVEL) | PMU_BATFULL_LEVEL_BIT);

    ool_write(PMU_REG_CLK_EN, ool_read(PMU_REG_CLK_EN) | PMU_FILTER_CLK_EN_BIT);
    ool_write(PMU_REG_BAT_FULL_FILTER, 200);

    ool_write(PMU_REG_ANA_INT_EN, ool_read(PMU_REG_ANA_INT_EN) | PMU_BATFULL_INT_EN_BIT);
    pmu_enable_isr(PMU_BATFULL_INT_MASK_BIT);
}

/*********************************************************************
 * @fn      pmu_lvd_enable
 *
 * @brief   low-voltage detect config and enable.
 * 
 * @param   voltage_threshold - voltage threshold, @ref enum_PMU_LVD_THD_t
 */
void pmu_lvd_enable(enum_PMU_LVD_THD_t voltage_threshold)
{
    /* lvd level config */
    ool_write(PMU_REG_SBG_TRIM_CFG, (ool_read(PMU_REG_SBG_TRIM_CFG) & (~PMU_BBG_LVD_CTL_BIT)) | (voltage_threshold << PMU_BBG_LVD_CTL_POS));
    /* filter */
    ool_write(PMU_REG_CLK_EN, ool_read(PMU_REG_CLK_EN) | PMU_FILTER_CLK_EN_BIT);
    ool_write(PMU_REG_LVD_FILTER, 200);
    /* lvd interrupt enable */
    ool_write(PMU_REG_ANA_INT_EN, ool_read(PMU_REG_ANA_INT_EN) | PMU_LVD_INT_EN_BIT);
    pmu_enable_isr(PMU_LVD_INT_MASK_BIT);
}

/*********************************************************************
 * @fn      pmu_adkey0_enable
 *
 * @brief   adkey0 config and enable.
 */
void pmu_adkey0_enable(void)
{
    /* PMU_IO4 pull up */
    pmu_set_pin_dir(PMU_PIN_4, PMU_GPIO_MODE_INPUT);
    pmu_set_pin_pull(PMU_PIN_4, PMU_GPIO_PULL_UP);
    /* adkey0 enable */
    ool_write(PMU_REG_ADKEY_CTRL, ool_read(PMU_REG_ADKEY_CTRL) & ~PMU_ADKEY_0_EN_BIT);
    /* filter */
    ool_write(PMU_REG_CLK_EN, ool_read(PMU_REG_CLK_EN) | PMU_FILTER_CLK_EN_BIT);
    ool_write(PMU_REG_ADKEY_FILTER, 200);
    /* adkey interrupt enable */
    ool_write(PMU_REG_ANA_INT_EN, ool_read(PMU_REG_ANA_INT_EN) | PMU_ADKEY0_INT_EN_BIT);
    pmu_enable_isr(PMU_ADKEY0_INT_MASK_BIT);
}

/*********************************************************************
 * @fn      pmu_adkey1_enable
 *
 * @brief   adkey1 config and enable.
 */
void pmu_adkey1_enable(void)
{
    /* PMU_IO5 pull up */
    pmu_set_pin_dir(PMU_PIN_5, PMU_GPIO_MODE_INPUT);
    pmu_set_pin_pull(PMU_PIN_5, PMU_GPIO_PULL_UP);
    /* adkey1 enable */
    ool_write(PMU_REG_ADKEY_CTRL, ool_read(PMU_REG_ADKEY_CTRL) & ~PMU_ADKEY_1_EN_BIT);
    /* filter */
    ool_write(PMU_REG_CLK_EN, ool_read(PMU_REG_CLK_EN) | PMU_FILTER_CLK_EN_BIT);
    ool_write(PMU_REG_ADKEY_FILTER, 200);
    /* adkey interrupt enable */
    ool_write(PMU_REG_ANA_INT_EN, ool_read(PMU_REG_ANA_INT_EN) | PMU_ADKEY1_INT_EN_BIT);
    pmu_enable_isr(PMU_ADKEY1_INT_MASK_BIT);
}

/******************************************************************************
 * @fn      pmu_set_3V3_ioldo_voltage
 *
 * @brief   set 3.3V IOLDO voltage.
 */
void pmu_set_3V3_ioldo_voltage(enum_PMU_3V3_ioldo_voltage_t ioldo_voltage)
{
    ool_write(PMU_REG_IOLDO1_CTRL_0, (ool_read(PMU_REG_IOLDO1_CTRL_0)&0xF0) | ioldo_voltage);
}

/******************************************************************************
 * @fn      pmu_get_3V3_ioldo_voltage
 *
 * @brief   get 3.3V IOLDO voltage setting.
 */
enum_PMU_3V3_ioldo_voltage_t pmu_get_3V3_ioldo_voltage(void)
{
    return ool_read(PMU_REG_IOLDO1_CTRL_0)&0x0F;
}

/******************************************************************************
 * @fn      pmu_set_1V8_ioldo_voltage
 *
 * @brief   set 1.8V IOLDO voltage.
 */
void pmu_set_1V8_ioldo_voltage(enum_PMU_1V8_ioldo_voltage_t ioldo_voltage)
{
    ool_write(PMU_REG_IOLDO2_CTRL_0, (ool_read(PMU_REG_IOLDO2_CTRL_0)&0xF0) | ioldo_voltage);
}

/******************************************************************************
 * @fn      pmu_ram_retention_set
 *
 * @brief   select which partition should be retention after enter deep sleep mode.
 *
 * @param   retention_sel: ram selections, @ref PMU_RAM_RET_xx_BIT
 */
void pmu_ram_retention_set(uint16_t retention_sel)
{
    ool_write16(PMU_REG_PKSRAM_GATE, ~retention_sel);
}

void pmu_set_pin_pull(enum_PMU_PINx_t bits, enum_PMU_GPIO_PULL_t type)
{
    uint8_t en_reg = PMU_REG_PIN_PULL_EN;
    uint8_t pull_reg = PMU_REG_PIN_PULL_SEL;

    if(type == PMU_GPIO_NO_PULL) {
        ool_write16(en_reg, (ool_read16(en_reg) & (~bits)));
    }
    else {
        if(type == PMU_GPIO_PULL_UP) {
            ool_write16(pull_reg, (ool_read16(pull_reg) | bits));
        }
        else if(type == PMU_GPIO_PULL_DOWN) {
            ool_write16(pull_reg, (ool_read16(pull_reg) & (~bits)));
        }
        else {
            return;
        }
        ool_write16(en_reg, (ool_read16(en_reg) | bits));
    }
}

void pmu_set_pin_dir(enum_PMU_PINx_t bits, enum_PMU_GPIO_MODE_t dir)
{
    uint8_t oe_reg = PMU_REG_PIN_OUTPUT_EN;
    uint8_t ie_reg = PMU_REG_PIN_INPUT_EN;

    if(dir == PMU_GPIO_MODE_INPUT) {
        ool_write16(oe_reg, ool_read16(oe_reg) |  bits);
        ool_write16(ie_reg, ool_read16(ie_reg) | (((bits & 0xff) << 2) | ((bits & 0x300) >> 8)));
    }
    else {
        ool_write16(oe_reg, ool_read16(oe_reg) & (~bits));
        ool_write16(ie_reg, ool_read16(ie_reg) & (~(((bits & 0xff) << 2) | ((bits & 0x300) >> 8))));
    }
}

void pmu_set_pin_value(enum_PMU_PINx_t bits, uint8_t value)
{
    uint8_t data_reg = PMU_REG_PIN_DATA;

    if (value == 0)
        ool_write16(data_reg, (ool_read16(data_reg) & (~bits)));
    else
        ool_write16(data_reg, (ool_read16(data_reg) | bits));
}

uint8_t pmu_get_pin_value(enum_PMU_PINx_t bit)
{
    uint8_t data_reg = PMU_REG_PIN_DATA;

    if ((ool_read16(data_reg) & bit))
        return true;
    else
        return false;
}

void pmu_set_pin_xor_en(enum_PMU_PINx_t bits, bool en)
{
    uint8_t xor_reg = PMU_REG_PIN_XOR_EN;
    
    if(en) {
        ool_write16(xor_reg, ool_read16(xor_reg) | (bits));
    }
    else {
        ool_write16(xor_reg, ool_read16(xor_reg) & (~bits));
    }
}

/*********************************************************************
 * @fn      pmu_port_wakeup_func_set
 *
 * @brief   PortPin wakeup function congfig
 *
 * @param   bits: Select Pin. 0x01--PIN0 0x80--PIN7
 */
void pmu_port_wakeup_func_set(enum_PMU_PINx_t bits)
{
    uint8_t last_status_reg = PMU_REG_PIN_LAST_V;
    uint8_t data_reg = PMU_REG_PIN_DATA;

    /* Config input Pull up */
    pmu_set_pin_pull(bits, PMU_GPIO_PULL_UP);
    pmu_set_pin_dir(bits, PMU_GPIO_MODE_INPUT);

    /* Read the current value and write */
    ool_write16(last_status_reg, ool_read16(data_reg));

    /* XOR Enable */
    pmu_set_pin_xor_en(bits, true);

    /* XOR interrupt enable */
    ool_write(PMU_REG_PIN_INT_EN, 0x01);
}

/*********************************************************************
 * @fn      pmu_gpio_int_init
 *
 * @brief   pmu pin wakeup function config. Compare with pmu_port_wakeup_func_set, this
 *          function provides two parameter to set pull mode and initial value
 *
 * @param   bits: Select Pin. 0x01--PIN0 0x80--PIN7
 *          pull: pull mode selection, @ref enum_PMU_GPIO_PULL_t
 *          init_value: initial value. Once the level of corresponding pin changes to opposite
 *                      level with initial value, PMU_GPIO_PMU_INT will be generated.
 */
void pmu_gpio_int_init(enum_PMU_PINx_t bits, enum_PMU_GPIO_PULL_t pull, uint8_t init_value)
{
    uint8_t last_status_reg = PMU_REG_PIN_LAST_V;
    uint8_t data_reg = PMU_REG_PIN_DATA;

    /* Config input Pull up */
    pmu_set_pin_pull(bits, pull);
    pmu_set_pin_dir(bits, PMU_GPIO_MODE_INPUT);

    /* Read the current value and write */
    if (init_value) {
        ool_write16(last_status_reg, ool_read16(last_status_reg) | bits);
    }
    else {
        ool_write16(last_status_reg, ool_read16(last_status_reg) & (~bits));
    }

    /* XOR Enable */
    pmu_set_pin_xor_en(bits, true);

    /* XOR interrupt enable */
    ool_write(PMU_REG_PIN_INT_EN, 0x01);
}

/*********************************************************************
 * @fn      pmu_port_wakeup_func_clear
 *
 * @brief   Get rtc current counter value
 *
 * @param   bits: Select Pin. 0x01--PIN0 0x80--PIN7
 */
void pmu_port_wakeup_func_clear(enum_PMU_PINx_t bits)
{
    /* XOR Disable */
    pmu_set_pin_xor_en(bits, false);
}

void pmu_enable_isr(uint16_t isr_map)
{
    ool_write16(PMU_REG_INT_MASK, ool_read16(PMU_REG_INT_MASK) | isr_map);
}

void pmu_disable_isr(uint16_t isr_map)
{
    ool_write16(PMU_REG_INT_MASK, ool_read16(PMU_REG_INT_MASK) & (~isr_map));
}

uint16_t pmu_get_isr_state(void)
{
    return ool_read16(PMU_REG_INT_STATUS);
}

void pmu_clear_isr_state(uint16_t state_map)
{
    if (state_map & PMU_BATFULL_INT_STATUS_BIT) {
        ool_write(PMU_REG_ANA_INT_CLR, ool_read(PMU_REG_ANA_INT_CLR) | PMU_BATFULL_INT_CLR_BIT);
    }

    if (state_map & PMU_CHG_ACOK_INT_STATUS_BIT) {
        ool_write(PMU_REG_ANA_INT_CLR, ool_read(PMU_REG_ANA_INT_CLR) | PMU_CHG_ACOK_INT_CLR_BIT);
    }

    if (state_map & PMU_LVD_INT_STATUS_BIT) {
        ool_write(PMU_REG_ANA_INT_CLR, ool_read(PMU_REG_ANA_INT_CLR) | PMU_LVD_INT_CLR_BIT);
    }

    if (state_map & PMU_ADKEY0_INT_STATUS_BIT) {
        ool_write(PMU_REG_ANA_INT_CLR, ool_read(PMU_REG_ANA_INT_CLR) | PMU_ADKEY0_INT_CLR_BIT);
    }
    if (state_map & PMU_ADKEY1_INT_STATUS_BIT) {
        ool_write(PMU_REG_ANA_INT_CLR, ool_read(PMU_REG_ANA_INT_CLR) | PMU_ADKEY1_INT_CLR_BIT);
    }

    if (state_map & PMU_WDT_INT_STATUS_BIT) {
        ool_write(PMU_REG_RTC_CTRL, ool_read(PMU_REG_RTC_CTRL) | PMU_WDT_CLR_BIT);
    }
    
    if (state_map & PMU_RTC_A_INT_STATUS_BIT) {
        ool_write(PMU_REG_RTC_CTRL, ool_read(PMU_REG_RTC_CTRL) | PMU_RTC_ALARM_A_CLR_BIT);
    }
    
    if (state_map & PMU_GPIO_PMU_INT_STATUS_BIT) {
        ool_write16(PMU_REG_PIN_XOR_CLR, ool_read16(PMU_REG_PIN_XOR_RESULT));
    }
    
    if (state_map & PMU_GPIO_GROUPH_INT_STATUS_BIT) {
        ool_write(PMU_REG_WKUP_INT_CLR, ool_read(PMU_REG_WKUP_INT_CLR) | 0x01);
    }

    if (state_map & PMU_GPIO_GROUPL_INT_STATUS_BIT) {
        ool_write(PMU_REG_WKUP_INT_CLR, ool_read(PMU_REG_WKUP_INT_CLR) | 0x02);
    }
}

__WEAK void PMU_Battery_Full_IRQHandler(void)
{
}

__WEAK void RTC_ALARMA_IRQHandler(void)
{
}

__WEAK void RTC_ALARMB_IRQHandler(void)
{
}

__WEAK void PMU_GPIO_PMU_IRQHandler(void)
{
}

__WEAK void PMU_GPIO_GROUPH_IRQHandler(void)
{    
}

__WEAK void PMU_GPIO_GROUPL_IRQHandler(void)
{
}

__WEAK void PMU_LVD_IRQHandler(void)
{
}

__WEAK void PMU_ADKEY0_IRQHandler(void)
{
}

__WEAK void PMU_ADKEY1_IRQHandler(void)
{
}

__WEAK void PMU_IWDT_IRQhandler(void)
{
}

void pmu_irq(void)
{
    uint16_t state_map = pmu_get_isr_state();
//    printf("%s state%d \r\n",__func__,state_map);
//    pmu_clear_isr_state(state_map);

    if (state_map & PMU_BATFULL_INT_STATUS_BIT) {
        PMU_Battery_Full_IRQHandler();
    }

    if (state_map & PMU_LVD_INT_STATUS_BIT) {
        PMU_LVD_IRQHandler();
    }
    
    if (state_map & PMU_RTC_A_INT_STATUS_BIT) {
        RTC_ALARMA_IRQHandler();
    }
    
    if (state_map & PMU_RTC_B_INT_STATUS_BIT) {
        RTC_ALARMB_IRQHandler();
    }
    
    if (state_map & PMU_GPIO_PMU_INT_STATUS_BIT) {
        PMU_GPIO_PMU_IRQHandler();
    }
    
    if (state_map & PMU_GPIO_GROUPH_INT_STATUS_BIT) {
        PMU_GPIO_GROUPH_IRQHandler();
    }
    
    if (state_map & PMU_GPIO_GROUPL_INT_STATUS_BIT) {
        PMU_GPIO_GROUPL_IRQHandler();
    }

    if (state_map & PMU_ADKEY0_INT_STATUS_BIT) {
        PMU_ADKEY0_IRQHandler();
    }

    if (state_map & PMU_ADKEY1_INT_STATUS_BIT) {
        PMU_ADKEY1_IRQHandler();
    }
    
    if (state_map & PMU_WDT_INT_STATUS_BIT) {
        PMU_IWDT_IRQhandler();
    }
    pmu_clear_isr_state(state_map);
}
