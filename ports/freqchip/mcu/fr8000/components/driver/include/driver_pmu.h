/*
  ******************************************************************************
  * @file    driver_pmu.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of PMU HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_PMU_H__
#define __DRIVER_PMU_H__

#include <stdint.h>
#include <stdbool.h>

#include "driver_frspim.h"
#include "driver_system.h"
#include "driver_efuse.h"
#include "driver_flash.h"

#include "sys_utils.h"

//#include "co_printf.h"

#define ool_write(addr, data)       frspim_wr(FR_SPI_PMU_PK_CHAN,(addr),1, (data))
#define ool_read(addr)              (uint8_t)frspim_rd(FR_SPI_PMU_PK_CHAN,(addr),1)

#define ool_write16(addr,data)      frspim_wr(FR_SPI_PMU_PK_CHAN,(addr),2, (data))
#define ool_read16(addr)            (uint16_t)frspim_rd(FR_SPI_PMU_PK_CHAN,(addr),2)

#define ool_write32(addr,data)      frspim_wr(FR_SPI_PMU_PK_CHAN,(addr),4, (data))
#define ool_read32(addr)            (uint32_t)frspim_rd(FR_SPI_PMU_PK_CHAN,(addr),4)

#define ool_pd_write(addr, data)    frspim_wr(FR_SPI_PMU_PD_CHAN,(addr),1, (data))
#define ool_pd_read(addr)           (uint8_t)frspim_rd(FR_SPI_PMU_PD_CHAN,(addr),1)

#define ool_pd_write16(addr,data)   frspim_wr(FR_SPI_PMU_PD_CHAN,(addr),2, (data))
#define ool_pd_read16(addr)         (uint16_t)frspim_rd(FR_SPI_PMU_PD_CHAN,(addr),2)

#define ool_pd_write32(addr,data)   frspim_wr(FR_SPI_PMU_PD_CHAN,(addr),4, (data))
#define ool_pd_read32(addr)         (uint32_t)frspim_rd(FR_SPI_PMU_PD_CHAN,(addr),4)

#define PMU_REG_OSC_CAP             0x0c
#define PMU_OSC_CAP_PARA            0x1f
#define PMU_BOOT_CLK_SEL            0x80

/*****************The Following Regs belong to Analog domain***************/

#define PMU_REG_HDONKEY_CTRL        0x00
#define PMU_REG_SBG_CTRL            0x01
#define PMU_REG_VBE_CTRL            0x02
#define PMU_REG_POWARN_CTRL         0x03

#define PMU_REG_PKVDD_CFG_1         0x04

#define PMU_REG_PKVDD_CFG_2         0x05

#define PMU_REG_POR_CFG             0x07

#define PMU_REG_IOLDO_CFG_1         0x08

#define PMU_REG_IOLDO_CFG_2         0x09
#define PMU_REG_IOLDO_CFG_3         0x0b

enum pmu_ioldo_voltage_sel_t 
{
    PMU_ALDO_1_8V = 0,
    PMU_ALDO_2_0V = 1,
    PMU_ALDO_2_3V = 2,
    PMU_ALDO_2_5V = 3,
    PMU_ALDO_2_7V = 4,
    PMU_ALDO_2_9V = 5,
    PMU_ALDO_3_1V = 6,
    PMU_ALDO_3_3V = 7,
};

#define PMU_REG_OSC_CAP_CFG         0x0c
#define PMU_REG_CHG_EN_CFG          0x0d

#define PMU_REG_CHG_TERM_VOL_CTL    0x10
#define PMU_REG_CHG_CUR_CTL         0x11

enum charge_term_vol_t 
{
    PMU_CHG_END_VOL_4_1,      /* charge end voltage select 4.1V  */
    PMU_CHG_END_VOL_4_1_5,    /* charge end voltage select 4.15V */
    PMU_CHG_END_VOL_4_2,      /* charge end voltage select 4.2V  */
    PMU_CHG_END_VOL_4_2_5,    /* charge end voltage select 4.25V */
    PMU_CHG_END_VOL_4_3,      /* charge end voltage select 4.3V  */
    PMU_CHG_END_VOL_4_3_5,    /* charge end voltage select 4.35V */
    PMU_CHG_END_VOL_4_4,      /* charge end voltage select 4.4V  */
};

enum charge_current_t 
{
    PMU_CHG_CUR_8mA     = 0x01,    /* charge current select 8mA    */
    PMU_CHG_CUR_13mA    = 0x02,    /* charge current select 13mA    */
    PMU_CHG_CUR_23_4mA  = 0x04,    /* charge current select 23.4mA  */
    PMU_CHG_CUR_44_17mA = 0x08,    /* charge current select 44.17mA */
    PMU_CHG_CUR_85_57mA = 0x10,    /* charge current select 85.57mA */
    PMU_CHG_CUR_168mA   = 0x20,    /* charge current select 168mA   */
    PMU_CHG_CUR_180mA   = 0x23,    /* charge current select 180mA   */
    PMU_CHG_CUR_200mA   = 0x27,    /* charge current select 200mA   */
};

#define PMU_REG_FLASHV_CHG_CFG      0x11

#define PMU_REG_BUCK_CFG_1          0x12
#define PMU_REG_BUCK_CFG_2          0x13
#define PMU_REG_BUCK_CFG_3          0x14
#define PMU_REG_BUCK_CFG_4          0x15
#define PMU_REG_BUCK_CFG_5          0x16
#define PMU_REG_BUCK_CFG_6          0x17

#define PMU_REG_SYSLDO_CFG          0x18

#define PMU_REG_DLDO_CFG_1          0x19
#define PMU_REG_DLDO_CFG_2          0x1a

#define PMU_REG_ADKEY_CFG           0x1b

#define PMU_REG_ADC_CFG             0x1c

#define PMU_REG_OSC_DRV             0x1d

/*******************The Following Regs belong to PK domain*****************/

#define PMU_REG_WKUP_CNT_H          0x20

#define PMU_REG_CLK_CTRL            0x21

enum pmu_clock_sel_t
{
    PMU_CLK_SEL_RCLP,
    PMU_CLK_SEL_RCLP_DIV2,        // internal RC clock
    PMU_CLK_SEL_RCLP_DIV2_ALT,    
    PMU_CLK_SEL_XTAL32768,        // external low speed xtal
};

#define PMU_CLK_SEL_MASK            0x03

#define PMU_REG_FSM_DIV_PARA        0x22
/*
 * 在唤醒的时候那些counter的基础clock可以在pmu clock的基础上分频，
 * 来实现慢速唤醒，这个就是配置分频比。
 */
#define PMU_FSM_ON_CLK_DIV_MASK     0x3f
#define PMU_FSM_ON_CLK_DIV_POS      0
/* 
 * 在睡眠的时候那些counter的基础clock可以在pmu clock的基础上分频，
 * 这个就是配置分频比。
 */
#define PMU_FSM_OFF_CLK_DIV_MASK    0xc0
#define PMU_FSM_OFF_CLK_DIV_POS     6

#define PMU_REG_ANA_PIN_CFG         0x23
#define PMU_RSTN_PIN_DIS            0x04
#define PMU_HD_ONKEY_EN             0x02
#define PMU_ONKEY_EN                0x01

#define PMU_REG_CLK_EN              0x24
#define PMU_DEB_DIV_EN              0x80    // debounce clock div enable
#define PMU_QDEC_CLK_EN             0x40    // qdec clock enable
#define PMU_CALIB_CLK_EN            0x20    // calibration clock enable
#define PMU_DEB_CLK_EN              0x10    // debounce clock enable
#define PMU_KEYSCAN_CLK_EN          0x08    // keyscan clock enable
#define PMU_PWM_CLK_EN              0x04    // pwm clock enable
#define PMU_RTC_CLK_EN              0x02    // RTC clock enable
#define PMU_SLP_TIMER_CLK_EN        0x01    // sleep timer clock enable

#define PMU_REG_RST_CTRL            0x25
#define PMU_WTD_RST_DIS             0x80    // disable wtd reset system
#define PMU_QDEC_RST_DIS            0x40    // qdec soft reset
#define PMU_CALI_SFT_RST            0x20    // calibration soft reset
#define PMU_DEB_SFT_RST             0x10    // debounce module soft reset
#define PMU_KEYSCAN_SFT_RST         0x08    // keyscan soft reset
#define PMU_PWM_SFT_RST             0x04    // pwm soft reset
#define PMU_RTC_SFT_RST             0x02    // rtc soft reset
#define PMU_SLP_TIMER_SFT_RST       0x01    // sleep timer soft reset

#define PMU_REG_WTD_CTRL            0x26
#define PMU_WDT_CTRL_IRQ_EN         0x04
#define PMU_WDT_CTRL_CLR            0x02
#define PMU_WTD_CTRL_EN             0x01

#define PMU_REG_WTD_CNT_0           0x27
#define PMU_REG_WTD_CNT_1           0x28
#define PMU_REG_WTD_CNT_2           0x29

#define PMU_REG_WTD_TOUT_LEN        0x2A    // WDT中断产生后经过多少clock会复位系统

#define PMU_REG_SLP_CNT_0           0x2b
#define PMU_REG_SLP_CNT_1           0x2c
#define PMU_REG_SLP_CNT_2           0x2d
#define PMU_REG_SLP_CNT_3           0x2e

#define PMU_REG_BLE_SLP_CTRL        0x2f
#define PMU_BLE_WAKEUP_ONKEY_EN     0x40    // enable ONKEY wakeup BLE sleep timer
#define PMU_BLE_WAKEUP_XOR_EN       0x20    // enable XOR wakeup BLE sleep timer
#define PMU_BLE_WAKEUP_INT_EN       0x10    // enable interrupt wakeup BLE sleep timer
#define PMU_SLP_CNT_READ_SEL        0x08    // 0: actual sleep counter, 1: setting sleep counter
#define PMU_EN_SLP_TIMER_CTRL_PMU   0x04    // enable sleep timer to control pmu block
#define PMU_SFT_WAKEUP_REQ          0x02    // software wakeup request to sleep timer
#define PMU_EXT_WAKEUP_DSB          0x01    // disable external wakeup reqeust signal

#define PMU_REG_WKUP_CNT_L          0x30

#define PMU_REG_PMU_ONOFF_CNT       0x31
#define PMU_REG_RC64M_ONOFF_CNT     0x32
#define PMU_REG_BBG_ONOFF_CNT       0x33
#define PMU_REG_RSTN_ONOFF_CNT      0x34
#define PMU_REG_BUCK_ONOFF_CNT      0x35
#define PMU_REG_IOLDO_ONOFF_CNT     0x36
#define PMU_REG_DLDO_ONOFF_CNT      0x37
#define PMU_REG_VDDHA_ONOFF_CNT     0x38
#define PMU_REG_PDVDD_ONOFF_CNT     0x39
#define PMU_REG_PKVDD_ONOFF_CNT     0x3a
#define PMU_REG_PKDVDD_ONOFF_CNT    0x3b
#define PMU_REG_MEMRET_ONOFF_CNT    0x3c
#define PMU_REG_ISO_ONOFF_CNT       0x3d

#define PMU_REG_GATE_MASK_0         0x3e
#define PMU_REG_GATE_MASK_1         0x3f

#define PMU_REG_GATE_CTRL_0         0x40
#define PMU_REG_GATE_CTRL_1         0x41
#define PMU_SYS_REM_16K_POS         0
#define PMU_SYS_REM_32K_POS         1
#define PMU_EXC_REM_8K_POS          2
#define PMU_CACHE_4K_POS            3
#define PMU_SYS_REM_8K_POS          4

#define PMU_REG_CTRL_MISC_0         0x42

#define PMU_REG_PORTA_SEL           0x43    // 1: gpio is controlled by d_core logic, 0: pmu logic
#define PMU_REG_PORTB_SEL           0x44
#define PMU_REG_PORTC_SEL           0x45
#define PMU_REG_PORTD_SEL           0x46
#define PMU_REG_PORTE_SEL           0x47

#define PMU_REG_PORTA_PULL_EN       0x48    // 1: enable pull up/down, 0: floating
#define PMU_REG_PORTB_PULL_EN       0x49
#define PMU_REG_PORTC_PULL_EN       0x4a
#define PMU_REG_PORTD_PULL_EN       0x4b
#define PMU_REG_PORTE_PULL_EN       0x4c

#define PMU_REG_PORTA_PULL_SEL      0x4d    // 1: pull up, 0: pull down
#define PMU_REG_PORTB_PULL_SEL      0x4e
#define PMU_REG_PORTC_PULL_SEL      0x4f
#define PMU_REG_PORTD_PULL_SEL      0x50
#define PMU_REG_PORTE_PULL_SEL      0x51

#define PMU_REG_PORTA_XOR_EN        0x52    // 1: diable, 0: enable
#define PMU_REG_PORTB_XOR_EN        0x53
#define PMU_REG_PORTC_XOR_EN        0x54
#define PMU_REG_PORTD_XOR_EN        0x55

#define PMU_REG_PORTE_XOR_EN        0x56    // 1: diable, 0: enable
#define PMU_ADKEY1_XOR_EN           0x40    //deleted @application
#define PMU_LVD_FAST_XOR_EN         0x20
#define PMU_ADKEY0_XOR_EN           0x10    //deleted @application

#define PMU_REG_ANALOG_XOR_EN       0x57    // 1: enable, 0: disable

enum charge_type
{
    PMU_CHARGING_IN,
    PMU_CHARGING_OUT,
};
 
#define PMU_REG_PORTA_LAST_STATUS   0x58
#define PMU_REG_PORTB_LAST_STATUS   0x59
#define PMU_REG_PORTC_LAST_STATUS   0x5a
#define PMU_REG_PORTD_LAST_STATUS   0x5b
#define PMU_REG_PORTE_LAST_STATUS   0x5c

#define PMU_REG_ANALOG_LAST_STATUS  0x5d
#define PMU_OTD_LAST_STATUS        0x08
#define PMU_LVD_LAST_STATUS        0x04
#define PMU_ACOK_LAST_STATUS       0x02
#define PMU_BAT_FULL_LAST_STATUS   0x01


#define PMU_REG_SYSTEM_STATUS_SW    0x5e
#define PMU_SYS_PO_MAGIC            0x5A
#define PMU_SYS_WK_MAGIC            0xC3

#define PMU_REG_SLP_OP              0x5f
#define PMU_CPU_SLP_OP              0x01    // mcu put SoC into sleep mode after setting this bit

#define PMU_REG_SLP_CTRL            0x60
#define PMU_WAKEUP_EN               0x80
#define PMU_SLEEP_EN                0x40
#define PMU_ONKEY_WAKEUP_EN         0x20
#define PMU_XOR_WAKEUP_EN           0x10
#define PMU_INT_WAKEUP_EN           0x08
#define PMU_BB_WAKEUP_EN            0x04
#define PMU_CPU_SLEEP_EN            0x02
#define PMU_BB_SLEEP_EN             0x01

#define PMU_REG_GPIO_MUX_CFG_SEL    0x65
#define PMU_PORTE_MUX_CFG_SEL       0x10    // 1: pk register, 0: iomux in PD domain
#define PMU_PORTD_MUX_CFG_SEL       0x08
#define PMU_PORTC_MUX_CFG_SEL       0x04
#define PMU_PORTB_MUX_CFG_SEL       0x02
#define PMU_PORTA_MUX_CFG_SEL       0x01

enum pmu_gpio_mux_cfg_sel_t 
{
    PMU_GPIO_MUX_CFG_PD,
    PMU_GPIO_MUX_CFG_PK,
};

#define PMU_REG_PORTA_OE            0x66    // 1: input, 0: output
#define PMU_REG_PORTB_OE            0x67
#define PMU_REG_PORTC_OE            0x68
#define PMU_REG_PORTD_OE            0x69
#define PMU_REG_PORTE_OE            0x6a

#define PMU_REG_PORTA_V             0x6b
#define PMU_REG_PORTB_V             0x6c
#define PMU_REG_PORTC_V             0x6d
#define PMU_REG_PORTD_V             0x6e
#define PMU_REG_PORTE_V             0x6f

#define PMU_REG_CTRL_MISC_1         0x70

#define PMU_REG_OSC_HALF_DLY        0x74
#define PMU_OSC_EDGE_SEL            0x80
#define PMU_OSC_HALF_PARA           0x1f

#define PMU_REG_OSC_FULL_LDLY       0x75

#define PMU_REG_OSC_S96M_DLY        0x76
#define PMU_OSC_SDLY_PARA           0xf0
#define PMU_OSC_96M_DLY             0x0f

/*******************The Following Regs belong to PD domain*****************/

#define PMU_REG_PD_CALI_CTRL        0x00
#define PMU_CALI_IRQ_EN             0x10
#define PMU_CALI_SEL_POS            1
#define PMU_CALI_SEL_MASK           0x0e

enum pmu_cali_sel_t 
{
    PMU_CALI_SEL_RCLFOSC,
    PMU_CALI_SEL_XTAL32k,
    PMU_CALI_SEL_RCCALOUT,
    PMU_CALI_SEL_RC64M_DIV,
    PMU_CALI_EXTERN,
};

#define PMU_CALI_EN                 0x01

#define PMU_REG_PD_CALI_LEN_L       0x01
#define PMU_REG_PD_CALI_LEN_H       0x02

#define PMU_REG_PD_CALI_RESULT_0    0x03
#define PMU_REG_PD_CALI_RESULT_1    0x04
#define PMU_REG_PD_CALI_RESULT_2    0x05
#define PMU_REG_PD_CALI_RESULT_3    0x06

#define PMU_REG_PD_RTC_CTRL         0x07
#define PMU_RTC_UPD_EN              0x10
#define PMU_RTC_ALARMB_EN           0x04
#define PMU_RTC_ALARMA_EN           0x08
#define PMU_RTC_ALARMB_CLR          0x02
#define PMU_RTC_ALARMA_CLR          0x01

#define PMU_REG_PD_RTC_UPD_CNT_0    0x08
#define PMU_REG_PD_RTC_UPD_CNT_1    0x09
#define PMU_REG_PD_RTC_UPD_CNT_2    0x0a
#define PMU_REG_PD_RTC_UPD_CNT_3    0x0b

#define PMU_REG_PD_RTC_ALARMA_CNT_0 0x0c
#define PMU_REG_PD_RTC_ALARMA_CNT_1 0x0d
#define PMU_REG_PD_RTC_ALARMA_CNT_2 0x0e
#define PMU_REG_PD_RTC_ALARMA_CNT_3 0x0f

#define PMU_REG_PD_RTC_ALARMB_CNT_0 0x10
#define PMU_REG_PD_RTC_ALARMB_CNT_1 0x11
#define PMU_REG_PD_RTC_ALARMB_CNT_2 0x12
#define PMU_REG_PD_RTC_ALARMB_CNT_3 0x13

#define PMU_REG_PD_KEYSCAN_CTRL     0x18
#define PMU_KEYSCAN_VAL_RD          0x20
#define PMU_KEYSCAN_VAL_CLR         0x10
#define PMU_GHOST_DET_EN            0x08
#define PMU_KEYSCAN_LP_EN           0x04
#define PMU_KEYSCAN_GLITCH_EN       0x02
#define PMU_KEYSCAN_EN              0x01

#define PMU_REG_PD_KEYSCAN_INTERVAL_L   0x19
#define PMU_REG_PD_KEYSCAN_INTERVAL_H   0x1a

#define PMU_REG_PD_GLITCH_CFG       0x1b
#define PMU_KEYSCAN_GLITCH_LEN_POS  0
#define PMU_KEYSCAN_GLITCH_LEN_MASK 0x0f

#define PMU_REG_PD_KEYSCAN_ROW_SEL      0x1c
#define PMU_REG_PD_KEYSCAN_COL_SEL_0    0x1d
#define PMU_REG_PD_KEYSCAN_COL_SEL_1    0x1e
#define PMU_REG_PD_KEYSCAN_COL_SEL_2    0x1f

#define PMU_REG_PD_KEYSCAN_VAL_00       0x20
#define PMU_REG_PD_KEYSCAN_VAL_01       0x21
#define PMU_REG_PD_KEYSCAN_VAL_02       0x22
#define PMU_REG_PD_KEYSCAN_VAL_03       0x23
#define PMU_REG_PD_KEYSCAN_VAL_04       0x24
#define PMU_REG_PD_KEYSCAN_VAL_05       0x25
#define PMU_REG_PD_KEYSCAN_VAL_06       0x26
#define PMU_REG_PD_KEYSCAN_VAL_07       0x27
#define PMU_REG_PD_KEYSCAN_VAL_08       0x28
#define PMU_REG_PD_KEYSCAN_VAL_09       0x29
#define PMU_REG_PD_KEYSCAN_VAL_0a       0x2a
#define PMU_REG_PD_KEYSCAN_VAL_0b       0x2b
#define PMU_REG_PD_KEYSCAN_VAL_0c       0x2c
#define PMU_REG_PD_KEYSCAN_VAL_0d       0x2d
#define PMU_REG_PD_KEYSCAN_VAL_0e       0x2e
#define PMU_REG_PD_KEYSCAN_VAL_0f       0x2f
#define PMU_REG_PD_KEYSCAN_VAL_10       0x30
#define PMU_REG_PD_KEYSCAN_VAL_11       0x31
#define PMU_REG_PD_KEYSCAN_VAL_12       0x32
#define PMU_REG_PD_KEYSCAN_VAL_13       0x33

#define PMU_REG_PD_PTC0_CTRL            0x34
#define PMU_REG_PD_PTC1_CTRL            0x35
#define PMU_REG_PD_PTC2_CTRL            0x36
#define PMU_REG_PD_PTC3_CTRL            0x37
/* PTC CTRL bit  definition */
#define PMU_PTC_CTRL_PTC_CTN_RD         0x80
#define PMU_PTC_CTRL_PTC_INV            0x10
#define PMU_PTC_CTRL_PTC_RST            0x08
#define PMU_PTC_CTRL_PTC_MODE           0x04
#define PMU_PTC_CTRL_PTC_OUT_EN         0x02
#define PMU_PTC_CTRL_PTC_EN             0x01

#define PMU_REG_PD_PTC0_LRC_L           0x38
#define PMU_REG_PD_PTC0_LRC_H           0x39
#define PMU_REG_PD_PTC0_HRC_L           0x3A
#define PMU_REG_PD_PTC0_HRC_H           0x3B
#define PMU_REG_PD_PTC1_LRC_L           0x3C
#define PMU_REG_PD_PTC1_LRC_H           0x3D
#define PMU_REG_PD_PTC1_HRC_L           0x3E
#define PMU_REG_PD_PTC1_HRC_H           0x3F
#define PMU_REG_PD_PTC2_LRC_L           0x40
#define PMU_REG_PD_PTC2_LRC_H           0x41
#define PMU_REG_PD_PTC2_HRC_L           0x42
#define PMU_REG_PD_PTC2_HRC_H           0x43
#define PMU_REG_PD_PTC3_LRC_L           0x44
#define PMU_REG_PD_PTC3_LRC_H           0x45
#define PMU_REG_PD_PTC3_HRC_L           0x46
#define PMU_REG_PD_PTC3_HRC_H           0x47

#define PMU_REG_PD_BAT_DEB_LEN          0x58
#define PMU_REG_PD_ACOK_DEB_LEN         0x59
#define PMU_REG_PD_LVD_DEB_LEN          0x5a
#define PMU_REG_PD_OTD_DEB_LEN          0x5b

#define PMU_REG_PD_ANA_INT_LEVEL        0x5c
#define PMU_OTD_INT_TRIG_LEVEL          0x08
#define PMU_LVD_INT_TRIG_LEVEL          0x04
#define PMU_ACOK_INT_TRIG_LEVEL         0x02
#define PMU_BAT_INT_TRIG_LEVEL          0x01

#define PMU_REG_PD_INT_EN           0x5e
#define PMU_HDOFF_INT_EN            0x8000
#define PMU_ADKEY0_XOR_INT_EN       0x4000
#define PMU_GPIO_XOR_INT_EN         0x2000
#define PMU_QDEC_INT_EN             0x1000
#define PMU_KEYSCAN_INT_EN          0x0800
#define PMU_RTC_ALMB_INT_EN         0x0400
#define PMU_RTC_ALMA_INT_EN         0x0200
#define PMU_CALI_INT_EN             0x0100
#define PMU_ADKEY1_XOR_INT_EN       0x0080
#define PMU_LVD_FAST_INT_EN         0x0040
//reserved for bit5
#define PMU_WTD_INT_EN              0x0010
#define PMU_OTD_INT_EN              0x0008
#define PMU_LVD_DEB_INT_EN          0x0004
#define PMU_ACOK_INT_EN             0x0002
#define PMU_BAT_FULL_INT_EN         0x0001

#define PMU_REG_PD_INT_CLR          0x60
#define PMU_HDOFF_INT_CLR           0x8000
#define PMU_ADKEY0_INT_CLR          0x4000
#define PMU_GPIO_XOR_INT_CLR        0x2000
#define PMU_QDEC_INT_CLR            0x1000
#define PMU_KEYSCAN_INT_CLR         0x0800
#define PMU_RTC_ALMB_INT_CLR        0x0400
#define PMU_RTC_ALMA_INT_CLR        0x0200
#define PMU_CALI_INT_CLR            0x0100
#define PMU_ADKEY1_INT_CLR          0x0080
#define PMU_LVD_FAST_INT_CLR        0x0040
//reserved for bit5
#define PMU_WTD_INT_CLR             0x0010
#define PMU_OTD_INT_CLR             0x0008
#define PMU_LVD_DEB_INT_CLR         0x0004
#define PMU_ACOK_INT_CLR            0x0002
#define PMU_BAT_INT_CLR             0x0001

#define PMU_REG_PD_INT_STATUS       0x62
#define PMU_HDOFF_INT_STATUS        0x8000
#define PMU_ADKEY0_INT_STATUS       0x4000    //fixed
#define PMU_GPIO_XOR_INT_STATUS     0x2000
#define PMU_QDEC_INT_STATUS         0x1000
#define PMU_KEYSCAN_INT_STATUS      0x0800
#define PMU_RTC_ALMB_INT_STATUS     0x0400
#define PMU_RTC_ALMA_INT_STATUS     0x0200
#define PMU_CALI_INT_STATUS         0x0100
#define PMU_ADKEY1_INT_STATUS       0x0080
#define PMU_LVD_FAST_INT_STATUS     0x0040
#define PMU_WTD_INT_STATUS          0x0010   //fixed
#define PMU_OTD_INT_STATUS          0x0008   //fixed
#define PMU_LVD_DEB_INT_STATUS      0x0004
#define PMU_ACOK_INT_STATUS         0x0002   //fixed
#define PMU_BAT_INT_STATUS          0x0001   //fixed

#define PMU_REG_PD_XOR_PORTA_VALID      0x64
#define PMU_REG_PD_XOR_PORTB_VALID      0x65
#define PMU_REG_PD_XOR_PORTC_VALID      0x66
#define PMU_REG_PD_XOR_PORTD_VALID      0x67
#define PMU_REG_PD_XOR_PORTE_VALID      0x68

#define PMU_REG_PD_ANA_XOR_VALID        0x69
#define PMU_HD_ONKEY_XOR_VALID      0x80
#define PMU_ONKEY_XOR_VALID         0x40
#define PMU_ADKEY1_XOR_VALID        0x20
#define PMU_ADKEY0_XOR_VALID        0x10
#define PMU_OTD_XOR_VALID           0x08
#define PMU_LVD_XOR_VALID           0x04
#define PMU_ACOK_XOR_VALID          0x02
#define PMU_BAT_FULL_XOR_VALID      0x01

#define PMU_REG_PD_PORTA_MUX        0x6a
#define PMU_REG_PD_PORTB_MUX        0x6c
#define PMU_REG_PD_PORTC_MUX        0x6e
#define PMU_REG_PD_PORTD_MUX        0x70
#define PMU_REG_PD_PORTE_MUX        0x72
#define PMU_DIAG0_EN                0x10
#define PMU_DIAG1_EN                0x20
#define PMU_DIAG2_EN                0x40
#define PMU_DIAG3_EN                0x80

#define PMU_REG_DIAG_CFG_0          0x73
#define PMU_REG_DIAG_CFG_1          0x74

#define PMU_REG_QDEC_CTRL0          0x75
#define PMU_QDEC_CNT_RST            0x01
#define PMU_QDEC_3X_EN              0x02

enum pmu_qdec_irq_type
{
    PMU_ISR_QDEC_SINGLE_EN = 0x04,
    PMU_ISR_QDEC_MULTI_EN  = 0x08,
};

#define PMU_REG_QDEC_CTRL1          0x76
#define PMU_QDEC_DEB_EN_A           0x01
#define PMU_QDEC_DEB_EN_B           0x02
#define PMU_QDEC_DEB_EN_C           0x04
#define PMU_QDEC_CNT_MODE_MASK      0x30
#define PMU_QDEC_CNT_MODE_POS       4

#define PMU_REG_QDEC_LEN            0x77
#define PMU_REG_QDEC_DEB_LEN        0x78
#define PMU_REG_QDEC_CNTA           0x79
#define PMU_REG_QDEC_CNTB           0x7a
#define PMU_REG_QDEC_MUX_0          0x7b
#define PMU_REG_QDEC_MUX_1          0x7c

enum pmu_pin_func_t {
    PMU_PIN_FUNC_GPIO,
    PMU_PIN_FUNC_PWM,
    PMU_PIN_FUNC_KEYSCAN,
};

enum LVD_Voltage_Threshold{
    LVD_2_0_V,
    LVD_2_1_V,
    LVD_2_2_V,
    LVD_2_3_V,
    LVD_3_3_V,
    LVD_3_4_V,
    LVD_3_5_V,
    LVD_3_6_V, 
};

enum filter_Key_A{
    FILTER_KEY_A_PA0,
    FILTER_KEY_A_PA1,
    FILTER_KEY_A_PA2,
    FILTER_KEY_A_PA3,
    FILTER_KEY_A_PA4,
    FILTER_KEY_A_PA5,
    FILTER_KEY_A_PA6,
    FILTER_KEY_A_PA7,
    
    FILTER_KEY_A_PB0,
    FILTER_KEY_A_PB1,
    FILTER_KEY_A_PB2,
    FILTER_KEY_A_PB3,
    FILTER_KEY_A_PB4,
    FILTER_KEY_A_PB5,
    FILTER_KEY_A_PB6,
    FILTER_KEY_A_PB7, 
};

enum filter_Key_B{
    FILTER_KEY_B_PC0 = 0x10,
    FILTER_KEY_B_PC1 = 0x20,
    FILTER_KEY_B_PC2 = 0x30,
    FILTER_KEY_B_PC3 = 0x40,
    FILTER_KEY_B_PC4 = 0x50,
    FILTER_KEY_B_PC5 = 0x60,
    FILTER_KEY_B_PC6 = 0x70,
    FILTER_KEY_B_PC7 = 0x80,
    
    FILTER_KEY_B_PD0 = 0x90,
    FILTER_KEY_B_PD1 = 0xA0,
    FILTER_KEY_B_PD2 = 0xB0,
    FILTER_KEY_B_PD3 = 0xC0,
    FILTER_KEY_B_PD4 = 0xD0,
    FILTER_KEY_B_PD5 = 0xE0,
    FILTER_KEY_B_PD6 = 0xF0,
};

/* Exported functions --------------------------------------------------------*/

__STATIC_INLINE void pmu_porta_write(uint8_t value)
{
    ool_write(PMU_REG_PORTA_V, value);
}

__STATIC_INLINE void pmu_portb_write(uint8_t value)
{
    ool_write(PMU_REG_PORTB_V, value);
}

__STATIC_INLINE void pmu_portc_write(uint8_t value)
{
    ool_write(PMU_REG_PORTC_V, value);
}

__STATIC_INLINE void pmu_portd_write(uint8_t value)
{
    ool_write(PMU_REG_PORTD_V, value);
}

__STATIC_INLINE void pmu_porte_write(uint8_t value)
{
    ool_write(PMU_REG_PORTE_V, value);
}

__STATIC_INLINE uint8_t pmu_porta_read(void)
{
    return ool_read(PMU_REG_PORTA_LAST_STATUS);
}

__STATIC_INLINE uint8_t pmu_portb_read(void)
{
    return ool_read(PMU_REG_PORTB_LAST_STATUS);
}

__STATIC_INLINE uint8_t pmu_portc_read(void)
{
    return ool_read(PMU_REG_PORTC_LAST_STATUS);
}

__STATIC_INLINE uint8_t pmu_portd_read(void)
{
    return ool_read(PMU_REG_PORTD_LAST_STATUS);
}

__STATIC_INLINE uint8_t pmu_porte_read(void)
{
    return ool_read(PMU_REG_PORTE_LAST_STATUS);
}
void pmu_set_pin_mux(enum system_port_t port, enum system_port_bit_t bit, enum pmu_pin_func_t func);
void pmu_set_pin_pull(enum system_port_t port, uint8_t bits, enum system_port_pull_t type);

void pmu_set_pin_to_PMU(enum system_port_t port, uint8_t bits);

void pmu_set_pin_to_CPU(enum system_port_t port, uint8_t bits);

void pmu_set_pin_mux_cfg_sel(enum system_port_t port, enum pmu_gpio_mux_cfg_sel_t sel);

void pmu_set_pin_dir(enum system_port_t port, uint8_t bits, uint8_t dir);

void pmu_set_pin_xor_en(enum system_port_t port, uint8_t bits, bool en);

void pmu_set_gpio_value(enum system_port_t port, uint8_t bits, uint8_t value);

uint8_t pmu_get_gpio_value(enum system_port_t port, uint8_t bit);

void pmu_enable_isr(uint16_t isr_map);

void pmu_disable_isr(uint16_t isr_map);

uint16_t pmu_get_isr_state(void);

void pmu_clear_isr_state(uint16_t state_map);

void pmu_init(void);

void pmu_sub_init(void);

void pmu_calibration_start(enum pmu_cali_sel_t type, uint16_t counter);

void pmu_calibration_restart(uint16_t counter);

void pmu_calibration_stop(void);

uint32_t pmu_get_rc_clk(uint8_t redo);

void pmu_ioldosw_ctrl(bool on);

void pmu_usb_pad_ctrl(bool on);

void pmu_enable_charge(enum charge_current_t cur, enum charge_term_vol_t vol, bool en);
void pmu_ioldo_voltage(enum pmu_ioldo_voltage_sel_t ioldo_voltage);

void pmu_charging_monitor_en(enum charge_type charge);

void pmu_battery_full_monitor_en(void);

void pmu_buck_mode_enable(void);
void pmu_ldo_mode_enable(void);

void pmu_port_wakeup_func_set(enum system_port_t port, uint8_t bits);
void pmu_port_wakeup_func_clear(enum system_port_t port, uint8_t bits);

void pmu_shutdown(void);

void pmu_cp_trim_config(void);
void pmu_ft_trim_config(struct_FT_Param_t *FT_Param);
struct_ADC_Cal_Param_t *pmu_get_adc_cal_param(void);
    
void pmu_low_speed_xtal_config(enum pmu_clock_sel_t pmu_clock_sel);

void pmu_Anti_shake_key_config(enum filter_Key_A Key_A, enum filter_Key_B Key_B, uint8_t fu8_filter);

void lvd_threshold(enum LVD_Voltage_Threshold Voltage_value);
void pmu_lvd_en(uint8_t mode,enum LVD_Voltage_Threshold Voltage_value,uint8_t DEB_Len);

void pmu_adc_power_control(bool fb_power);
    
#endif  //_DRIVER_PMU_H
 
