#ifndef _DRIVER_PMU_H
#define _DRIVER_PMU_H

#include <stdint.h>
#include <stdbool.h>

/// PMU module clock source
#define PMU_REG_CLK                 0x00
/// 1: external XTAL32768, 0: internal 62K RC
#define PMU_SYSCLK_SEL_POS          0
#define PMU_SYSCLK_SEL_BIT          0x01

/// configure PMU on-off base timing dividor
#define PMU_REG_FSM_TIMER           0x01
#define PMU_FSM_OFF_DIV_LSB         5
#define PMU_FSM_OFF_DIV_MSK         0xE0
#define PMU_FSM_ON_DIV_LSB          0
#define PMU_FSM_ON_DIV_MSK          0x1F

/// configure debounce module dividor
#define PMU_REG_DEB_CLK_DIV         0x02

/// configure PMU reset source
#define PMU_REG_RST_SRC_EN          0x03
#define PMU_LOW_BAT_RST_POS         2
#define PMU_LOW_BAT_RST_BIT         (1<<2)
#define PMU_WDT_RST_POS             1
#define PMU_WDT_RST_BIT             (1<<1)
#define PMU_PIN_RST_POS             0
#define PMU_PIN_RST_BIT             (1<<0)

/// configure module clock enalbe
#define PMU_REG_CLK_EN              0x04
#define PMU_EFUSE_CLK_EN_POS        7
#define PMU_EFUSE_CLK_EN_BIT        (1<<7)
#define PMU_FILTER_CLK_EN_POS       6
#define PMU_FILTER_CLK_EN_BIT       (1<<6)
#define PMU_QDEC_CLK_EN_POS         5
#define PMU_QDEC_CLK_EN_BIT         (1<<5)
#define PMU_KEYSCAN_CLK_EN_POS      4
#define PMU_KEYSCAN_CLK_EN_BIT      (1<<4)
#define PMU_DEB_CLK_EN_POS          3
#define PMU_DEB_CLK_EN_BIT          (1<<3)
#define PMU_RTC_CLK_EN_POS          2
#define PMU_RTC_CLK_EN_BIT          (1<<2)
#define PMU_WDT_CLK_EN_POS          1
#define PMU_WDT_CLK_EN_BIT          (1<<1)
#define PMU_LP_TICK_CLK_EN_POS      0
#define PMU_LP_TICK_CLK_EN_BIT      (1<<0)

/// reset modules inside PMU
#define PMU_REG_RST                 0x05
#define PMU_EFUSE_SFT_RST_POS       7
#define PMU_EFUSE_SFT_RST_BIT       (1<<7)
#define PMU_FILTER_SFT_RST_POS      6
#define PMU_FILTER_SFT_RST_BIT      (1<<6)
#define PMU_QDEC_SFT_RST_POS        5
#define PMU_QDEC_SFT_RST_BIT        (1<<5)
#define PMU_KEYSCAN_SFT_RST_POS     4
#define PMU_KEYSCAN_SFT_RST_BIT     (1<<4)
#define PMU_DEB_SFT_RST_POS         3
#define PMU_DEB_SFT_RST_BIT         (1<<3)
#define PMU_RTC_SFT_RST_POS         2
#define PMU_RTC_SFT_RST_BIT         (1<<2)
#define PMU_WDT_SFT_RST_POS         1
#define PMU_WDT_SFT_RST_BIT         (1<<1)
#define PMU_LP_TICK_SFT_RST_POS     0
#define PMU_LP_TICK_SFT_RST_BIT     (1<<0)

/// indicate which module could put PMU into sleep mode or wake up PMU
#define PMU_REG_SLP_WK_SRC          0x06
#define PMU_WK_IRQ_EN_POS           5
#define PMU_WK_IRQ_EN_BIT           (1<<5)
#define PMU_WK_TICK_EN_POS          4
#define PMU_WK_TICK_EN_BIT          (1<<4)
#define PMU_SLP_CPU_EN_POS          1
#define PMU_SLP_CPU_EN_BIT          (1<<1)
#define PMU_SLP_TICK_EN_POS         0
#define PMU_SLP_TICK_EN_BIT         (1<<0)

/// control PMU wakeup or enter sleep by software
#define PMU_REG_SW_OP               0x07
#define PMU_SW_WK_TICK_POS          1
#define PMU_SW_WK_TICK_BIT          (1<<1)
#define PMU_SW_EN_SLP_POS           0
#define PMU_SW_EN_SLP_BIT           (1<<0)

/// default value is 0xAD
#define PMU_REG_STATUS              0x08
#define PMU_STATUS_DEEP_SLEEP       0xC3
#define PMU_STATUS_NORAML           0xAD

/// indicate which module could wake up TICK
#define PMU_REG_TICK_CTRL           0x09
#define PMU_IRQ_WK_TICK_EN_POS      3
#define PMU_IRQ_WK_TICK_EN_BIT      (1<<3)
/// this bit has to be set when PMU_IRQ_WK_TICK_EN_BIT is set
#define PMU_EXT_WK_TICK_EN_POS      1
#define PMU_EXT_WK_TICK_EN_BIT      (1<<1)
#define PMU_TICK_SLP_PMU_EN_POS     0
#define PMU_TICK_SLP_PMU_EN_BIT     (1<<0)

/// counter from start PMU wakeup procedure to generate BTDM sleep interrupt
#define PMU_REG_TW_WKUP_L           0x0a
#define PMU_REG_TW_WKUP_H           0x0b

/// write: expect sleep duration, read: actual sleep duration
#define PMU_REG_TICK_COUNTER_0      0x0c
#define PMU_REG_TICK_COUNTER_1      0x0d
#define PMU_REG_TICK_COUNTER_2      0x0e
#define PMU_REG_TICK_COUNTER_3      0x0f

#define PMU_REG_WDT_CTRL            0x10
#define PMU_WDT_CLR_EN_POS          6
#define PMU_WDT_CLR_EN_BIT          (1<<6)
#define PMU_WDT_CLR_POS             4
#define PMU_WDT_CLR_BIT             (1<<4)
#define PMU_WDT_IRQ_EN_POS          3
#define PMU_WDT_IRQ_EN_BIT          (1<<3)
#define PMU_WDT_RST_CPU_POS         2
#define PMU_WDT_RST_CPU_BIT         (1<<2)
#define PMU_WDT_RST_CHIP_POS        1
#define PMU_WDT_RST_CHIP_BIT        (1<<1)
#define PMU_WDT_EN_POS              0
#define PMU_WDT_EN_BIT              (1<<0)

/// timeout counter between wdt interrupt is triggered to reset operation is executed
#define PMU_REG_WDT_TOUT_COUNTER_0  0x11
#define PMU_REG_WDT_TOUT_COUNTER_1  0x12

/// watchdog length
#define PMU_REG_WDT_LEN_0           0x13
#define PMU_REG_WDT_LEN_1           0x14
#define PMU_REG_WDT_LEN_2           0x15
#define PMU_REG_WDT_LEN_3           0x16

#define PMU_REG_RTC_CTRL            0x17
#define PMU_RTC_ALARM_B_EN_POS      5
#define PMU_RTC_ALARM_B_EN_BIT      (1<<5)
#define PMU_RTC_ALARM_A_EN_POS      4
#define PMU_RTC_ALARM_A_EN_BIT      (1<<4)
#define PMU_RTC_ALARM_B_CLR_POS     3
#define PMU_RTC_ALARM_B_CLR_BIT     (1<<3)
#define PMU_RTC_ALARM_A_CLR_POS     2
#define PMU_RTC_ALARM_A_CLR_BIT     (1<<2)
#define PMU_RTC_SAMPLE_POS          1
#define PMU_RTC_SAMPLE_BIT          (1<<1)
/// reload RTC counter with value set in PMU_REG_RTC_COUNTER_x
#define PMU_RTC_UPD_EN_POS          0
#define PMU_RTC_UPD_EN_BIT          (1<<0)

/// write: set RTC counter, read: current RTC counter
#define PMU_REG_RTC_COUNTER_0       0x18
#define PMU_REG_RTC_COUNTER_1       0x19
#define PMU_REG_RTC_COUNTER_2       0x1a
#define PMU_REG_RTC_COUNTER_3       0x1b

/// RTC alarm A target value
#define PMU_REG_ALARM_A_COUNTER_0   0x1c
#define PMU_REG_ALARM_A_COUNTER_1   0x1d
#define PMU_REG_ALARM_A_COUNTER_2   0x1e
#define PMU_REG_ALARM_A_COUNTER_3   0x1f

/// RTC alarm B target value
#define PMU_REG_ALARM_B_COUNTER_0   0x20
#define PMU_REG_ALARM_B_COUNTER_1   0x21
#define PMU_REG_ALARM_B_COUNTER_2   0x22
#define PMU_REG_ALARM_B_COUNTER_3   0x23

#define PMU_REG_QDEC_CTRL           0x24
#define PMU_QDEC_SMP_EN_POS         6
#define PMU_QDEC_SMP_EN_BIT         (1<<6)
#define PMU_QDEC_DEB_EN_POS         4
#define PMU_QDEC_DEB_EN_MSK         (0x3<<4)
#define PMU_QDEC_RST_PROC_POS       3
#define PMU_QDEC_RST_PROC_MSK       (0x1<<3)
#define PMU_QDEC_3x_EN_POS          2
#define PMU_QDEC_3x_EN_BIT          (0x1<<2)
#define PMU_QDEC_CNT_MODE_POS       0
#define PMU_QDEC_CNT_MODE_MSK       (0x3<<0)

#define PMU_REG_QDEC_CLR            0x25
#define PMU_QDEC_INT_CLR_POS        4
#define PMU_QDEC_INT_CLR_BIT        (1<<4)
#define PMU_QDEC_INT_EN_POS         0
#define PMU_QDEC_INT_EN_MSK         (0x3<<0)

#define PMU_REG_QDEC_CNT_LEN        0x26

#define PMU_REG_QDEC_DEB_LEN        0x27

#define PMU_REG_QDEC_DINAB_MUX      0x28

#define PMU_REG_QDEC_CNTA_VAL       0x29
#define PMU_REG_QDEC_CNTB_VAL       0x2a

#define PMU_REG_INT_MASK            0x32
#define PMU_OTD_INT_MASK_POS        15
#define PMU_OTD_INT_MASK_BIT        (1<<15)
#define PMU_BATFULL_INT_MASK_POS    12
#define PMU_BATFULL_INT_MASK_BIT    (1<<12)
#define PMU_CHG_ACOK_INT_MASK_POS   11
#define PMU_CHG_ACOK_INT_MASK_BIT   (1<<11)
#define PMU_LVD_INT_MASK_POS        10
#define PMU_LVD_INT_MASK_BIT        (1<<10)
#define PMU_ADKEY1_INT_MASK_POS     9
#define PMU_ADKEY1_INT_MASK_BIT     (1<<9)
#define PMU_ADKEY0_INT_MASK_POS     8
#define PMU_ADKEY0_INT_MASK_BIT     (1<<8)
#define PMU_GPIO_PMU_INT_MSK_POS    7
#define PMU_GPIO_PMU_INT_MSK_BIT    (1<<7)
#define PMU_GPIO_GROUPL_INT_MSK_POS 6
#define PMU_GPIO_GROUPL_INT_MSK_BIT (1<<6)
#define PMU_GPIO_GROUPH_INT_MSK_POS 5
#define PMU_GPIO_GROUPH_INT_MSK_BIT (1<<5)
#define PMU_KEYSCAN_INT_MSK_POS     3
#define PMU_KEYSCAN_INT_MSK_BIT     (1<<3)
#define PMU_RTC_B_INT_MSK_POS       2
#define PMU_RTC_B_INT_MSK_BIT       (1<<2)
#define PMU_RTC_A_INT_MSK_POS       1
#define PMU_RTC_A_INT_MSK_BIT       (1<<1)
#define PMU_WDT_INT_MSK_POS         0
#define PMU_WDT_INT_MSK_BIT         (1<<0)

#define PMU_REG_INT_RAW             0x34
#define PMU_OTD_INT_RAW_POS         15
#define PMU_OTD_INT_RAW_BIT         (1<<15)
#define PMU_BATFULL_INT_RAW_POS     12
#define PMU_BATFULL_INT_RAW_BIT     (1<<12)
#define PMU_CHG_ACOK_INT_RAW_POS    11
#define PMU_CHG_ACOK_INT_RAW_BIT    (1<<11)
#define PMU_LVD_INT_RAW_POS         10
#define PMU_LVD_INT_RAW_BIT         (1<<10)
#define PMU_ADKEY1_INT_RAW_POS      9
#define PMU_ADKEY1_INT_RAW_BIT      (1<<9)
#define PMU_ADKEY0_INT_RAW_POS      8
#define PMU_ADKEY0_INT_RAW_BIT      (1<<8)
#define PMU_GPIO_PMU_INT_RAW_POS    7
#define PMU_GPIO_PMU_INT_RAW_BIT    (1<<7)
#define PMU_GPIO_GROUPL_INT_RAW_POS 6
#define PMU_GPIO_GROUPL_INT_RAW_BIT (1<<6)
#define PMU_GPIO_GROUPH_INT_RAW_POS 5
#define PMU_GPIO_GROUPH_INT_RAW_BIT (1<<5)
#define PMU_KEYSCAN_INT_RAW_POS     3
#define PMU_KEYSCAN_INT_RAW_BIT     (1<<3)
#define PMU_RTC_B_INT_RAW_POS       2
#define PMU_RTC_B_INT_RAW_BIT       (1<<2)
#define PMU_RTC_A_INT_RAW_POS       1
#define PMU_RTC_A_INT_RAW_BIT       (1<<1)
#define PMU_WDT_INT_RAW_POS         0
#define PMU_WDT_INT_RAW_BIT         (1<<0)

#define PMU_REG_INT_STATUS             0x36
#define PMU_OTD_INT_STATUS_POS         15
#define PMU_OTD_INT_STATUS_BIT         (1<<15)
#define PMU_BATFULL_INT_STATUS_POS     12
#define PMU_BATFULL_INT_STATUS_BIT     (1<<12)
#define PMU_CHG_ACOK_INT_STATUS_POS    11
#define PMU_CHG_ACOK_INT_STATUS_BIT    (1<<11)
#define PMU_LVD_INT_STATUS_POS         10
#define PMU_LVD_INT_STATUS_BIT         (1<<10)
#define PMU_ADKEY1_INT_STATUS_POS      9
#define PMU_ADKEY1_INT_STATUS_BIT      (1<<9)
#define PMU_ADKEY0_INT_STATUS_POS      8
#define PMU_ADKEY0_INT_STATUS_BIT      (1<<8)
#define PMU_GPIO_PMU_INT_STATUS_POS    7
#define PMU_GPIO_PMU_INT_STATUS_BIT    (1<<7)
#define PMU_GPIO_GROUPL_INT_STATUS_POS 6
#define PMU_GPIO_GROUPL_INT_STATUS_BIT (1<<6)
#define PMU_GPIO_GROUPH_INT_STATUS_POS 5
#define PMU_GPIO_GROUPH_INT_STATUS_BIT (1<<5)
#define PMU_KEYSCAN_INT_STATUS_POS     3
#define PMU_KEYSCAN_INT_STATUS_BIT     (1<<3)
#define PMU_RTC_B_INT_STATUS_POS       2
#define PMU_RTC_B_INT_STATUS_BIT       (1<<2)
#define PMU_RTC_A_INT_STATUS_POS       1
#define PMU_RTC_A_INT_STATUS_BIT       (1<<1)
#define PMU_WDT_INT_STATUS_POS         0
#define PMU_WDT_INT_STATUS_BIT         (1<<0)

#define PMU_REG_ANA_STATUS          0x38
#define PMU_OTD_STATUS_POS          7
#define PMU_OTD_STATUS_BIT          (1<<7)
#define PMU_BATFULL_STATUS_POS      4
#define PMU_BATFULL_STATUS_BIT      (1<<4)
#define PMU_CHG_ACOK_STATUS_POS     3
#define PMU_CHG_ACOK_STATUS_BIT     (1<<3)
#define PMU_LVD_STATUS_POS          2
#define PMU_LVD_STATUS_BIT          (1<<2)
#define PMU_ADKEY1_STATUS_POS       1
#define PMU_ADKEY1_STATUS_BIT       (1<<1)
#define PMU_ADKEY0_STATUS_POS       0
#define PMU_ADKEY0_STATUS_BIT       (1<<0)

#define PMU_REG_ANA_LEVEL           0x39
#define PMU_OTD_LEVEL_POS           7
#define PMU_OTD_LEVEL_BIT           (1<<7)
#define PMU_BATFULL_LEVEL_POS       4
#define PMU_BATFULL_LEVEL_BIT       (1<<4)
#define PMU_CHG_ACOK_LEVEL_POS      3
#define PMU_CHG_ACOK_LEVEL_BIT      (1<<3)
#define PMU_LVD_LEVEL_POS           2
#define PMU_LVD_LEVEL_BIT           (1<<2)
#define PMU_ADKEY1_LEVEL_POS        1
#define PMU_ADKEY1_LEVEL_BIT        (1<<1)
#define PMU_ADKEY0_LEVEL_POS        0
#define PMU_ADKEY0_LEVEL_BIT        (1<<0)

#define PMU_REG_ADKEY_FILTER        0x3A
#define PMU_REG_LVD_FILTER          0x3B
#define PMU_REG_CHG_ACOK_FILTER     0x3C
#define PMU_REG_BAT_FULL_FILTER     0x3D
#define PMU_REG_OTD_FILTER          0x3F

#define PMU_REG_ANA_INT_EN          0x40
#define PMU_OTD_INT_EN_POS          7
#define PMU_OTD_INT_EN_BIT          (1<<7)
#define PMU_BATFULL_INT_EN_POS      4
#define PMU_BATFULL_INT_EN_BIT      (1<<4)
#define PMU_CHG_ACOK_INT_EN_POS     3
#define PMU_CHG_ACOK_INT_EN_BIT     (1<<3)
#define PMU_LVD_INT_EN_POS          2
#define PMU_LVD_INT_EN_BIT          (1<<2)
#define PMU_ADKEY1_INT_EN_POS       1
#define PMU_ADKEY1_INT_EN_BIT       (1<<1)
#define PMU_ADKEY0_INT_EN_POS       0
#define PMU_ADKEY0_INT_EN_BIT       (1<<0)

#define PMU_REG_ANA_INT_CLR         0x41
#define PMU_OTD_INT_CLR_POS         7
#define PMU_OTD_INT_CLR_BIT         (1<<7)
#define PMU_BATFULL_INT_CLR_POS     4
#define PMU_BATFULL_INT_CLR_BIT     (1<<4)
#define PMU_CHG_ACOK_INT_CLR_POS    3
#define PMU_CHG_ACOK_INT_CLR_BIT    (1<<3)
#define PMU_LVD_INT_CLR_POS         2
#define PMU_LVD_INT_CLR_BIT         (1<<2)
#define PMU_ADKEY1_INT_CLR_POS      1
#define PMU_ADKEY1_INT_CLR_BIT      (1<<1)
#define PMU_ADKEY0_INT_CLR_POS      0
#define PMU_ADKEY0_INT_CLR_BIT      (1<<0)

#define PMU_REG_PIN_INPUT_EN        0x42
#define PMU_REG_PIN_PULL_EN         0x44
#define PMU_REG_PIN_PULL_SEL        0x46
#define PMU_REG_PIN_DATA            0x48
#define PMU_REG_PIN_OUTPUT_EN       0x4a
#define PMU_REG_PIN_XOR_EN          0x4c
#define PMU_REG_PIN_LAST_V          0x4e
#define PMU_REG_PIN_XOR_RESULT      0x50
#define PMU_REG_PIN_XOR_CLR         0x52
#define PMU_REG_PIN_INT_EN          0x54
#define PMU_REG_WKUP_INT_EN         0x57
#define PMU_REG_WKUP_INT_CLR        0x58

#define PMU_REG_PIN_IOMUX_L         0x59
#define PMU_REG_PIN_IOMUX_M         0x5a
#define PMU_REG_PIN_IOMUX_H         0x5b

// CPU reset vector = {1'b0, PMU_REG_CPU_RESET_VECTOR, 7'b0}
#define PMU_REG_CPU_RESET_VECTOR    0x5c

#define PMU_REG_PMU_GATE_L          0x60
#define PMU_REG_PMU_GATE_M          0x61
#define PMU_REG_PMU_GATE_H          0x62

#define PMU_REG_PMU_MASK_L          0x63
#define PMU_REG_PMU_MASK_M          0x64
#define PMU_REG_PMU_MASK_H          0x65

#define PMU_REG_PKSRAM_MASK         0x6a
#define PMU_REG_PKSRAM_GATE         0x6e
#define PMU_RAM_RET_CACHE_BIT       (1<<0)
#define PMU_RAM_RET_CRAM0_BIT       (1<<1)  // 32K, 0x1ffe0000~0x1ffe7fff
#define PMU_RAM_RET_CRAM1_BIT       (1<<2)  // 32K, 0x1ffe8000~0x1ffeffff
#define PMU_RAM_RET_CRAM2_BIT       (1<<3)  // 32K, 0x1fff0000~0x1fff7fff
#define PMU_RAM_RET_CRAM3_BIT       (1<<4)  // 32K, 0x1fff8000~0x1fffffff
#define PMU_RAM_RET_SRAM0_BIT       (1<<5)  // 32K, 0x20000000~0x20007fff
#define PMU_RAM_RET_SRAM1_BIT       (1<<6)  // 32K, 0x20008000~0x2000ffff
#define PMU_RAM_RET_SRAM2_BIT       (1<<7)  // 32K, 0x20010000~0x20017fff
#define PMU_RAM_RET_SRAM3_BIT       (1<<8)  // 32K, 0x20018000~0x2001ffff
#define PMU_RAM_RET_SRAM4_BIT       (1<<9)  // 128K, 0x20020000~0x2003ffff
#define PMU_RAM_RET_SRAM5_BIT       (1<<10) // 128K, 0x20040000~0x2005ffff
#define PMU_RAM_RET_SRAM6_BIT       (1<<11) // 128K, 0x20060000~0x2007ffff
#define PMU_RAM_RET_DRAM_BIT        (1<<12) // 64K, 0x20080000~0x2008ffff
#define PMU_RAM_RET_IRAM_BIT        (1<<13) // 64K, 0x1ffd0000~0x1ffdffff
#define PMU_RAM_RET_DSP_CACHE_BIT   (1<<14)

#define PMU_REG_PMU_ONOFF_CNT       0x70
#define PMU_REG_BBG_ONOFF_CNT       0x71
#define PMU_REG_SYSBUCK_ONOFF_CNT   0x72
#define PMU_REG_IOBUCK_ONOFF_CNT    0x73
#define PMU_REG_IOLDO1_ONOFF_CNT    0x74
#define PMU_REG_IOLDO2_ONOFF_CNT    0x75
#define PMU_REG_APPDLDO_ONOFF_CNT   0x76
#define PMU_REG_DSPDLDO_ONOFF_CNT   0x77
#define PMU_REG_PKSTPD_ONOFF_CNT    0x78

#define PMU_REG_MEMPD_ONOFF_CNT     0x79
#define PMU_REG_MEMPK_ONOFF_CNT     0x7a

#define PMU_REG_OSCLDO_ONOFF_CNT    0x7b
#define PMU_REG_OSC_ONOFF_CNT       0x7c
#define PMU_REG_RC24PD_ONOFF_CNT    0x7d
#define PMU_REG_RAMPK_ONOFF_CNT     0x7e
#define PMU_REG_PMUISO_ONOFF_CNT    0x7f
#define PMU_REG_IOISO_ONOFF_CNT     0x80
#define PMU_REG_IORTON_ONOFF_CNT    0x81
#define PMU_REG_IOSNS_ONOFF_CNT     0x82
#define PMU_REG_RSTN_ONOFF_CNT      0x83

#define PMU_REG_PWR_GATE            0x85

#define PMU_REG_BLOCK_CTRL          0xA3
#define PMU_REG_ACC_KEY             0xA4

#define PMU_REG_DIAG_CTRL           0x8f
#define PMU_DIAG_EN_POS             7
#define PMU_DIAG_EN_BIT             (1<<7)
#define PMU_DIAG_SEL_LSB            0
#define PMU_DIAG_SEL_MSK            0x0f

#define PMU_REG_ADKEY_CTRL          0xc0
#define PMU_ADKEY_PU_RES_EN_POS     6
#define PMU_ADKEY_PU_RES_EN_BIT     (1<<6)
#define PMU_ADKEY_1_EN_POS          5
#define PMU_ADKEY_1_EN_BIT          (1<<5)
#define PMU_ADKEY_0_EN_POS          4
#define PMU_ADKEY_0_EN_BIT          (1<<4)

#define PMU_REG_APP_DLDO_CTRL       0xc2

#define PMU_REG_BBG_CTL             0xc6
#define PMU_BBG_CTL_VBE_EN_POS      3
#define PMU_BBG_CTL_VBE_EN_BIT      (1<<3)

#define PMU_REG_CHG_CFG_C8          0xc8
#define PMU_CHG_CFG_CUR_POS         0
#define PMU_CHG_CFG_CUR_MASK        0x3F

#define PMU_REG_CHG_GT_CTL          0xc9

#define PMU_REG_CHG_CFG_CB          0xcb
#define PMU_CHG_CFG_END_VOL_POS     4
#define PMU_CHG_CFG_END_VOL_MASK    0x7

#define PMU_REG_CHG_CFG_CD          0xcd
#define PMU_CHG_CFG_ENABLE_POS      3
#define PMU_CHG_CFG_ENABLE_BIT      (1<<3)
#define PMU_CHG_CFG_REF_SEL_POS     1
#define PMU_CHG_CFG_REF_SEL_BIT     (1<<1)

#define PMU_REG_DSP_DLDO_CTRL       0xd0
#define PMU_REG_CHG_SMP_CTL         0xd1

#define PMU_REG_IOBUCK_CTRL_0       0xd2
#define PMU_REG_IOBUCK_CTRL_1       0xd3
#define PMU_REG_IOBUCK_CTRL_2       0xd4
#define PMU_REG_IOBUCK_CTRL_3       0xd5
#define PMU_REG_IOBUCK_CTRL_4       0xd6
#define PMU_REG_IOBUCK_CTRL_5       0xd7
#define PMU_REG_IOBUCK_CTRL_6       0xd8
#define PMU_REG_IOBUCK_CTRL_7       0xd9
#define PMU_REG_IOBUCK_CTRL_8       0xda

#define PMU_REG_SYSBUCK_CTRL_0      0xdb
#define PMU_REG_SYSBUCK_CTRL_1      0xdc
#define PMU_REG_SYSBUCK_CTRL_2      0xdd
#define PMU_REG_SYSBUCK_CTRL_3      0xde
#define PMU_REG_SYSBUCK_CTRL_4      0xdf
#define PMU_REG_SYSBUCK_CTRL_5      0xe0
#define PMU_REG_SYSBUCK_CTRL_6      0xe1
#define PMU_REG_SYSBUCK_CTRL_7      0xe2
#define PMU_REG_SYSBUCK_CTRL_8      0xe3

#define PMU_REG_IOLDO1_CTRL_0       0xe4
#define PMU_REG_IOLDO1_CTRL_1       0xe5
#define PMU_REG_IOLDO2_CTRL_0       0xe6
#define PMU_REG_IOLDO2_CTRL_1       0xe7

#define PMU_REG_OSC_CTRL_0          0xe9
#define PMU_REG_OSC_CTRL_1          0xea
#define PMU_OSC_CLK_OUT_BUF_EN_BIT     (1<<2)
#define PMU_OSC_CLK_REF_SPLL_EN_BIT    (1<<1)
#define PMU_OSC_CLK_REF_AUPLL_EN_BIT   (1<<0)
#define PMU_OSC_AUPLL_PD_BIT           (1<<7)

#define PMU_REG_OSC_CTRL_2          0xeb
#define PMU_REG_OSC_CTRL_3          0xec
#define PMU_REG_OSC_CTRL_4          0xed
#define PMU_REG_OSC_CTRL_5          0xee


#define PMU_REG_PKVDD_CTRL          0xef

#define PMU_REG_PKVDDH_CTRL_0       0xf0
#define PMU_REG_PKVDDH_CTRL_1       0xf1
#define PMU_REG_SBG_CFG             0xf3

#define PMU_REG_SBG_TRIM_CFG        0xf4
#define PMU_BBG_LVD_CTL_POS         4
#define PMU_BBG_LVD_CTL_BIT         0x70

#define PMU_REG_ADC_CTL             0xf8
#define PMU_ADC_CTL_POWER_POS       2
#define PMU_ADC_CTL_POWER_BIT       (1<<2)
#define PMU_ADC_CTL_VBAT_EN_BIT     (1<<4)
#define PMU_ADC_CTL_VBE_EN_BIT      (1<<5)
#define PMU_ADC_CTL_PGA_EN_BIT      (1<<6)
#define PMU_ADC_CTL_MICBIAS_EN_BIT  (1<<7)

#define PMU_REG_EFUSE_CTL           0xfa
#define PMU_EFUSE_CTL_POWER_BIT    (1<<0)

#define PMU_REG_PWR_CTL             0xfc
#define PMU_PSRAM_PWR_POS           0
#define PMU_PSRAM_PWR_BIT           (1<<0)

/** @addtogroup PMU_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization Config Section Start ################################ */

/* PMU PIN index */
typedef enum
{
    PMU_PIN_0 = 0x0001,
    PMU_PIN_1 = 0x0002,
    PMU_PIN_2 = 0x0004,
    PMU_PIN_3 = 0x0008,
    PMU_PIN_4 = 0x0010,
    PMU_PIN_5 = 0x0020,
    PMU_PIN_6 = 0x0040,
    PMU_PIN_7 = 0x0080,
    PMU_PIN_8 = 0x0100,
    PMU_PIN_9 = 0x0200,
}enum_PMU_PINx_t;

typedef enum
{
    PMU_GPIO_NO_PULL,
    PMU_GPIO_PULL_UP,
    PMU_GPIO_PULL_DOWN,
}enum_PMU_GPIO_PULL_t;

typedef enum
{
    PMU_GPIO_MODE_INPUT,
    PMU_GPIO_MODE_OUTPUT,
}enum_PMU_GPIO_MODE_t;

typedef enum
{
    PMU_LVD_THD_2P9_V,
    PMU_LVD_THD_3P0_V,
    PMU_LVD_THD_3P1_V,
    PMU_LVD_THD_3P2_V,
    PMU_LVD_THD_3P3_V,
    PMU_LVD_THD_3P4_V,
    PMU_LVD_THD_3P5_V,
    PMU_LVD_THD_3P6_V,
}enum_PMU_LVD_THD_t;

typedef enum
{
    PMU_WDT_IRQ,
    PMU_WDT_RST_CHIP,
}enum_PMU_WDT_MODE_t;

typedef enum 
{
    PMU_3V3_IOLDO_1_7V,     /* 3.3V IOLDO select 1.7V */
    PMU_3V3_IOLDO_1_8V,     /* 3.3V IOLDO select 1.8V */
    PMU_3V3_IOLDO_1_9V,     /* 3.3V IOLDO select 1.9V */
    PMU_3V3_IOLDO_2_4V,     /* 3.3V IOLDO select 2.4V */
    PMU_3V3_IOLDO_2_5V,     /* 3.3V IOLDO select 2.5V */
    PMU_3V3_IOLDO_2_6V,     /* 3.3V IOLDO select 2.6V */
    PMU_3V3_IOLDO_2_9V,     /* 3.3V IOLDO select 2.9V */
    PMU_3V3_IOLDO_3_0V,     /* 3.3V IOLDO select 3.0V */
    PMU_3V3_IOLDO_3_1V,     /* 3.3V IOLDO select 3.1V */
    PMU_3V3_IOLDO_3_2V,     /* 3.3V IOLDO select 3.2V */
    PMU_3V3_IOLDO_3_3V,     /* 3.3V IOLDO select 3.3V */
    PMU_3V3_IOLDO_3_4V,     /* 3.3V IOLDO select 3.4V */
}enum_PMU_3V3_ioldo_voltage_t;

typedef enum 
{
    PMU_1V8_IOLDO_1_60V,     /* 3.3V IOLDO select 1.60V */
    PMU_1V8_IOLDO_1_65V,     /* 3.3V IOLDO select 1.65V */
    PMU_1V8_IOLDO_1_70V,     /* 3.3V IOLDO select 1.70V */
    PMU_1V8_IOLDO_1_75V,     /* 3.3V IOLDO select 1.75V */
    PMU_1V8_IOLDO_1_80V,     /* 3.3V IOLDO select 1.80V */
    PMU_1V8_IOLDO_1_85V,     /* 3.3V IOLDO select 1.85V */
    PMU_1V8_IOLDO_1_90V,     /* 3.3V IOLDO select 1.90V */
    PMU_1V8_IOLDO_1_95V,     /* 3.3V IOLDO select 1.95V */
    PMU_1V8_IOLDO_2_00V,     /* 3.3V IOLDO select 2.00V */
    PMU_1V8_IOLDO_2_05V,     /* 3.3V IOLDO select 2.05V */
    PMU_1V8_IOLDO_2_10V,     /* 3.3V IOLDO select 2.10V */
}enum_PMU_1V8_ioldo_voltage_t;


typedef enum 
{
    PMU_BATTERY_FULL,
    PMU_BATTERY_NOT_FULL,
}enum_PMU_battery_type_t;

/* ################################ Initialization Config Section END ################################## */
/**
  * @}
  */

void pmu_init(void);

void pmu_adjust_onoff_timing(uint16_t rst_us);

void pmu_set_pin_pull(enum_PMU_PINx_t bits, enum_PMU_GPIO_PULL_t type);
void pmu_set_pin_dir(enum_PMU_PINx_t bits, enum_PMU_GPIO_MODE_t dir);
void pmu_set_pin_value(enum_PMU_PINx_t bits, uint8_t value);
uint8_t pmu_get_pin_value(enum_PMU_PINx_t bit);
void pmu_port_wakeup_func_set(enum_PMU_PINx_t bits);
void pmu_port_wakeup_func_clear(enum_PMU_PINx_t bits);
void pmu_gpio_int_init(enum_PMU_PINx_t bits, enum_PMU_GPIO_PULL_t pull, uint8_t init_value);

void pmu_enable_isr(uint16_t isr_map);
void pmu_disable_isr(uint16_t isr_map);
uint16_t pmu_get_isr_state(void);
void pmu_clear_isr_state(uint16_t state_map);

void pmu_lp_rc_calib(uint32_t lp_rc_counter, uint32_t hp_osc_counter);
extern uint32_t pmu_lp_rc_get(void);

void pmu_lvd_enable(enum_PMU_LVD_THD_t voltage_threshold);
void pmu_adkey0_enable(void);
void pmu_adkey1_enable(void);

void pmu_adc_power_ctrl(bool enable);
void pmu_adc_vbe_power_ctrl(bool enable);
void pmu_adc_vbat_power_ctrl(bool enable);
void pmu_adc_pga_power_ctrl(bool enable);
void pmu_adc_micbias_power_ctrl(bool enable);
void pmu_psram_power_ctrl(bool enable);
void pmu_efuse_power_ctrl(bool enable);

void pmu_set_3V3_ioldo_voltage(enum_PMU_3V3_ioldo_voltage_t ioldo_voltage);
enum_PMU_3V3_ioldo_voltage_t pmu_get_3V3_ioldo_voltage(void);
void pmu_set_1V8_ioldo_voltage(enum_PMU_1V8_ioldo_voltage_t ioldo_voltage);

void pmu_ram_retention_set(uint16_t retention_sel);

void pmu_battery_full_monitor_en(enum_PMU_battery_type_t battery_type);

#endif  // _DRIVER_PMU_H
