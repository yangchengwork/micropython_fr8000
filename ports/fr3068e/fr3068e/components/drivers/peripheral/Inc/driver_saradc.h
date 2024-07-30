/*
  ******************************************************************************
  * @file    driver_saradc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of SARADC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_SARADC_H__
#define __DRIVER_SARADC_H__

#include "fr30xx.h"

/** @addtogroup SARADC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Control Register for ADC */
typedef struct
{
    uint32_t SARADC_EN           : 1;
    uint32_t SARADC_Reset        : 1;
    uint32_t SARADC_FIFO_Reset   : 1;
    uint32_t SARADC_Soft_Trigger : 1;
    uint32_t rsv_0               : 28;
}REG_SARADC_Control_t;

/* Config Register for ADC */
typedef struct
{
    uint32_t SARADC_Mode                     : 1;
    uint32_t SARADC_Trigger_Mode             : 1;
    uint32_t rsv_0                           : 1;
    uint32_t SARADC_FIFO_EN                  : 1;
    uint32_t SARADC_MAX_Channle              : 4;
    uint32_t SARADC_FIFO_Channel_Sel         : 4;
    uint32_t SARADC_FIFO_Channel_Index_En    : 1;
    uint32_t rsv_1                           : 3;
    uint32_t SARADC_Interval_Clock_Div       : 4;
    uint32_t SARADC_Interval_Length          : 12;
}REG_SARADC_Config_t;

/* Timing Register for ADC */
typedef struct
{
    uint32_t SARADC_Clock_DIV             : 8;
    uint32_t SARADC_Sample_TimeoutCNT     : 4;
    uint32_t SARADC_Convert_TimeoutCNT    : 4;
    uint32_t SARADC_Hold_Time             : 12;
    uint32_t SARADC_Timing_Dynamic_Adjust : 4;
}REG_SARADC_Timing_t;

/* WDT Config Register for ADC */
typedef struct
{
    uint32_t WDT_EN                  : 1;
    uint32_t WDT_Mode                : 1;
    uint32_t rsv_0                   : 2;
    uint32_t WDT_Trigger_Threshold   : 4;
    uint32_t rsv_1                   : 8;
    uint32_t WDT_Monitor_Channel_Sel : 16;
}REG_SARADC_WDT_Config_t;

/* WDT Threshold Register for ADC */
typedef struct
{
    uint32_t WDT_Min_Limit : 16;
    uint32_t WDT_Max_Limit : 16;
}REG_SARADC_WDT_Threshold_t;

/* Queue Config Register for ADC */
typedef struct
{
    uint32_t Queue_En          : 1;
    uint32_t Queue_Mode        : 1;
    uint32_t rsv_0             : 2;
    uint32_t Queue_Channel_Num : 4;
    uint32_t Queue_Cycle       : 24;
}REG_SARADC_QueueConfig_t;

/* FIFO Data Register for ADC */
typedef struct
{
    uint32_t FIFO_Data          : 16;
    uint32_t FIFO_Channel_index : 16;
}REG_SARADC_FIFO_Data_t;

/* FIFO Config Register for ADC */
typedef struct
{
    uint32_t FIFO_Almost_Full_Threshold : 7;
    uint32_t rsv_0                      : 1;
    uint32_t DMA_EN                     : 1;
    uint32_t rsv_1                      : 7;
    uint32_t DMA_Threshold              : 7;
    uint32_t rsv_2                      : 9;
}REG_SARADC_FIFO_Config_t;

/* Analog Config Register for ADC */
typedef struct
{
    uint32_t Analog_PD            : 1;
    uint32_t rsv_0                : 1;
    uint32_t Analog_reset         : 1;
    uint32_t Input_channel_en     : 1;
    uint32_t Analog_smapling_time : 4;
    uint32_t rsv_1                : 2;
    uint32_t Analog_ATT_control   : 2;
    uint32_t Analog_REF_control   : 2;
    uint32_t Analog_INT_BUF_EN    : 1;
    uint32_t rsv_2                : 17;
}REG_SARADC_Analog_Config0_t;

/* Analog Config Register for ADC */
typedef struct
{
    uint32_t rsv_0           : 4;
    uint32_t INT_REF_CTRL    : 2;
    uint32_t rsv_1           : 26;
}REG_SARADC_Analog_Config1_t;

/* channel Config Register for ADC */
typedef struct
{
    uint32_t Channel_Map_N : 4;
    uint32_t Channel_Map_P : 4;
    uint32_t Difference_EN : 1;
    uint32_t rsv_0         : 23;
}REG_SARADC_Channel_Config_t;

/* Analog PGA0 Register for ADC */
typedef struct
{
    uint32_t PGA0_PD          : 1;
    uint32_t rsv_0            : 13;
    uint32_t PGA1I_TO_PGA2_EN : 1;
    uint32_t PGA1O_TO_PGA2_EN : 1;
    uint32_t rsv_1            : 16;
}REG_SARADC_Analog_PGA0_CTRL_t;

/* Analog PGA1 Register for ADC */
typedef struct
{
    uint32_t PGA1_PD          : 1;
    uint32_t rsv_0            : 3;
    uint32_t PGA1_GAIN        : 4;
    uint32_t rsv_1            : 8;
    uint32_t PGA1_OP_OSTG_IS  : 2;
    uint32_t rsv_2            : 2;
    uint32_t PGA1_SW_CTL      : 5;
    uint32_t rsv_3            : 7;
}REG_SARADC_Analog_PGA1_CTRL_t;

/* Analog PGA2 Register for ADC */
typedef struct
{
    uint32_t PGA2_PD          : 1;
    uint32_t rsv_0            : 3;
    uint32_t PGA2_GAIN        : 4;
    uint32_t rsv_1            : 8;
    uint32_t PGA2_OP_OSTG_IS  : 2;
    uint32_t rsv_2            : 2;
    uint32_t PGA2_SW_CTL      : 5;
    uint32_t rsv_3            : 7;
}REG_SARADC_Analog_PGA2_CTRL_t;

/* Analog GAIN Register for ADC */
typedef struct
{
    uint32_t GAIN_EN          : 1;
    uint32_t rsv_0            : 3;
    uint32_t GAIN_DEN         : 3;
    uint32_t rsv_1            : 1;
    uint32_t GAIN_NOM         : 8;
    uint32_t GAIN_DC          : 12;
    uint32_t rsv_3            : 4;
}REG_SARADC_Analog_GAIN_CTRL_t;

/* -------------------------------------------------*/
/*                 SARADC Registers                 */
/* -------------------------------------------------*/
typedef struct 
{
    volatile REG_SARADC_Control_t             SARADC_Control;               /* Offset 0x00 */
    volatile REG_SARADC_Config_t              SARADC_Config;                /* Offset 0x04 */
    volatile REG_SARADC_Timing_t              SARADC_Timing;                /* Offset 0x08 */
    volatile REG_SARADC_WDT_Config_t          SARADC_WDT0_Config;           /* Offset 0x0C */
    volatile REG_SARADC_WDT_Threshold_t       SARADC_WDT0_Threshold;        /* Offset 0x10 */
    volatile REG_SARADC_WDT_Config_t          SARADC_WDT1_Config;           /* Offset 0x14 */
    volatile REG_SARADC_WDT_Threshold_t       SARADC_WDT1_Threshold;        /* Offset 0x18 */
    volatile REG_SARADC_QueueConfig_t         SARADC_Queue0_Config;         /* Offset 0x1C */
    volatile uint32_t                         SARADC_Queue0_ChannelSel0;    /* Offset 0x20 */
    volatile uint32_t                         SARADC_Queue0_ChannelSel1;    /* Offset 0x24 */
    volatile REG_SARADC_QueueConfig_t         SARADC_Queue1_Config;         /* Offset 0x28 */
    volatile uint32_t                         SARADC_Queue1_ChannelSel0;    /* Offset 0x2C */
    volatile uint32_t                         SARADC_Queue1_ChannelSel1;    /* Offset 0x30 */
    volatile REG_SARADC_QueueConfig_t         SARADC_Queue2_Config;         /* Offset 0x34 */
    volatile uint32_t                         SARADC_Queue2_ChannelSel0;    /* Offset 0x38 */
    volatile uint32_t                         SARADC_Queue2_ChannelSel1;    /* Offset 0x3C */
    volatile REG_SARADC_Analog_Config0_t      SARADC_AnalogConfig0;         /* Offset 0x40 */
    volatile REG_SARADC_Analog_Config1_t      SARADC_AnalogConfig1;         /* Offset 0x44 */
    volatile uint32_t                         SARADC_FIFO_Data;             /* Offset 0x48 */
    volatile REG_SARADC_FIFO_Config_t         SARADC_FIFO_Config;           /* Offset 0x4C */
    volatile uint32_t                         SARADC_ChannelStatus;         /* Offset 0x50 */
    volatile uint32_t                         SARADC_FIFO_Count;            /* Offset 0x54 */
    volatile uint32_t                         SARADC_INT_Enble;             /* Offset 0x58 */
    volatile uint32_t                         SARADC_INT_Status;            /* Offset 0x5C */
    volatile uint32_t                         SARADC_INT_Raws;              /* Offset 0x60 */
    volatile REG_SARADC_Channel_Config_t      SARADC_ChannelConfig[16];     /* Offset 0x64 ~ 0xA0 */
    volatile uint32_t                         SARADC_ChannelData[16];       /* Offset 0xA4 ~ 0xE0 */
    volatile uint32_t                         SARADC_MICCtrl;               /* Offset 0xE4 */
    volatile REG_SARADC_Analog_PGA0_CTRL_t    SARADC_PGA0Ctrl;              /* Offset 0xE8 */
    volatile REG_SARADC_Analog_PGA1_CTRL_t    SARADC_PGA1Ctrl;              /* Offset 0xEC */
    volatile REG_SARADC_Analog_PGA2_CTRL_t    SARADC_PGA2Ctrl;              /* Offset 0xF0 */
    volatile uint32_t                         SARADC_VbeCtrl;               /* Offset 0xF4 */ 
    volatile uint32_t                         SARADC_VbatCtrl;              /* Offset 0xF8 */
    volatile REG_SARADC_Analog_GAIN_CTRL_t    SARADC_CAINCtrl;              /* Offset 0xFC */
}struct_SARADC_t;

#define SARADC              ((struct_SARADC_t *)SARADC_BASE)

/* ################################ Register Section END ################################ */
/**
  * @}
  */


/** @addtogroup SARADC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization, Config Section Start ################################ */

typedef enum  
{
    SARADC_CHANNEL_0,
    SARADC_CHANNEL_1,
    SARADC_CHANNEL_2,
    SARADC_CHANNEL_3,
    SARADC_CHANNEL_4,
    SARADC_CHANNEL_5,
    SARADC_CHANNEL_6,
    SARADC_CHANNEL_7,
    SARADC_CHANNEL_8,
    SARADC_CHANNEL_9,
    SARADC_CHANNEL_10,
    SARADC_CHANNEL_11,
    SARADC_CHANNEL_12,
    SARADC_CHANNEL_13,
    SARADC_CHANNEL_14,
    SARADC_CHANNEL_15,
}enum_saradc_channel_t;

/* SARADC channel mode */
typedef enum  
{
    SARADC_CH_MODE_SINGLE,          /* single-ended signal */
    SARADC_CH_MODE_DIFFERENTIAL,    /* differential signal */
}enum_saradc_channel_mode_t;

/* SARADC channel mapping */
typedef enum  
{
    ADC_CH_MAP_PMU_IO0,     /* PMU IO0 */
    ADC_CH_MAP_PMU_IO1,     /* PMU IO1 */
    ADC_CH_MAP_PMU_IO2,     /* PMU IO2 */
    ADC_CH_MAP_PMU_IO3,     /* PMU IO3 */
    ADC_CH_MAP_PMU_IO4,     /* PMU IO4 */
    ADC_CH_MAP_PORTD_11,    /* PortD_11 */
    ADC_CH_MAP_PORTD_12,    /* PortD_12 */
    ADC_CH_MAP_PORTD_13,    /* PortD_13 */
    ADC_CH_MAP_PORTD_14,    /* PortD_14 */
    ADC_CH_MAP_PORTD_15,    /* PortD_15 */
    ADC_CH_MAP_PGA_OUTN,    /* PGA out negative */
    ADC_CH_MAP_PGA_OUTP,    /* PGA out positive */
    ADC_CH_MAP_VBAT,        /* Vbat */
    ADC_CH_MAP_REFINT,      /* ADC reference voltage */
    ADC_CH_MAP_VBEN,        /* Core temperature negative */
    ADC_CH_MAP_VBEP,        /* Core temperature positive */
}enum_ADC_Channel_Map_t;

/* SARADC reference source */
typedef enum  
{
    SARADC_REF_IOLDO,              /* IOLDO voltage as reference source */
    SARADC_REF_EXTERNAL_INPUT,     /* external input voltage as reference source */
    SARADC_REF_INTERNAL_1P2V,      /* internal 1.2 voltage as reference source */
    SARADC_REF_INTERNAL_1P5V,      /* internal 1.5 voltage as reference source */
}enum_saradc_reference_t;

/* SARADC work mode */
typedef enum  
{
    SARADC_LOOP_MODE,
    SARADC_QUEUE_MODE,
}enum_saradc_mode_t;

/* SARADC voltage divider */
typedef enum  
{
    SARADC_VOLTAGE_DIVIDER_BYPASS,     // bypass
    SARADC_VOLTAGE_DIVIDER_0P25,       // 1/4 voltage divider
    SARADC_VOLTAGE_DIVIDER_0P5,        // 1/2 voltage divider
}enum_saradc_voltage_divider_t;

/* SARADC trigger mode */
typedef enum  
{
    SARADC_TRIGGER_HARDWARE,
    SARADC_TRIGGER_SOFTWARE,
}enum_saradc_trigger_mode_t;

/* SARADC fifo mode */
typedef enum  
{
    SARADC_FIFO_DISABLE,
    SARADC_FIFO_ENABLE,
}enum_saradc_fifo_mode_t;

/* SARADC wdt index */
typedef enum  
{
    SARADC_WDT0,
    SARADC_WDT1,
}enum_saradc_wdt_t;

/* SARADC wdt work mode */
typedef enum  
{
    SARADC_WDT_MODE0,    /* min <= adc <= max trigger */
    SARADC_WDT_MODE1,    /* adc < min || adc > max trigger */
}enum_saradc_wdt_mode_t;

/* SARADC wdt monitor channel select */
typedef enum  
{
    SARADC_WDT_MONITOR_CH0  = 0x0001,
    SARADC_WDT_MONITOR_CH1  = 0x0002,
    SARADC_WDT_MONITOR_CH2  = 0x0004,
    SARADC_WDT_MONITOR_CH3  = 0x0008,
    SARADC_WDT_MONITOR_CH4  = 0x0010,
    SARADC_WDT_MONITOR_CH5  = 0x0020,
    SARADC_WDT_MONITOR_CH6  = 0x0040,
    SARADC_WDT_MONITOR_CH7  = 0x0080,
    SARADC_WDT_MONITOR_CH8  = 0x0100,
    SARADC_WDT_MONITOR_CH9  = 0x0200,
    SARADC_WDT_MONITOR_CH10 = 0x0400,
    SARADC_WDT_MONITOR_CH11 = 0x0800,
    SARADC_WDT_MONITOR_CH12 = 0x1000,
    SARADC_WDT_MONITOR_CH13 = 0x2000,
    SARADC_WDT_MONITOR_CH14 = 0x4000,
    SARADC_WDT_MONITOR_CH15 = 0x8000,
}enum_saradc_wdt_monitor_channel_t;

/* SARADC queue index */
typedef enum  
{
    SARADC_QUEUE0,
    SARADC_QUEUE1,
    SARADC_QUEUE2,
}enum_saradc_queue_t;

/* SARADC queue work mode */
typedef enum  
{
    SARADC_QUEUE_SINGLE,    // Single mode
    SARADC_QUEUE_LOOP,      // Loop mode
}enum_saradc_queue_mode_t;

/* SARADC interrupt index */
typedef enum  
{
    SARADC_INT_STATUS_FIFO_EMPTY       = 0x001,
    SARADC_INT_STATUS_FIFO_FULL        = 0x002,
    SARADC_INT_STATUS_FIFO_ALMOST_FULL = 0x004,
    SARADC_INT_STATUS_CHANNEL_VALID    = 0x008,
    SARADC_INT_STATUS_CONVERT_ERR      = 0x010,
    SARADC_INT_STATUS_WDT0             = 0x020,
    SARADC_INT_STATUS_WDT1             = 0x040,
    SARADC_INT_STATUS_LOOP             = 0x080,
    SARADC_INT_STATUS_QUEUE0           = 0x100,
    SARADC_INT_STATUS_QUEUE1           = 0x200,
    SARADC_INT_STATUS_QUEUE2           = 0x400,
}enum_saradc_int_status_t;

/* SARADC VBAT control */
typedef enum
{
    SARADC_VABT_POWERDOWN    = 0x1,
    SARADC_VABT_DIVIDER_0P25 = 0x0,    // 1/4 voltage divider
    SARADC_VABT_DIVIDER_0P33 = 0x2,    // 1/3 voltage divider
    SARADC_VABT_DIVIDER_0P5  = 0x4,    // 1/2 voltage divider
    SARADC_VABT_DIVIDER_0P66 = 0x6,    // 2/3 voltage divider
}enum_saradc_vbat_ctrl_t;

/* SARADC VBAT control */
typedef enum
{
    SARADC_MICBIAS_OUTPUT_POWERDOWN = 0x1,
    SARADC_MICBIAS_OUTPUT_1P4 = 0x0,
    SARADC_MICBIAS_OUTPUT_1P6 = 0x2,
    SARADC_MICBIAS_OUTPUT_1P8 = 0x4,
    SARADC_MICBIAS_OUTPUT_2P0 = 0x6,
    SARADC_MICBIAS_OUTPUT_2P2 = 0x8,
    SARADC_MICBIAS_OUTPUT_2P4 = 0xA,
    SARADC_MICBIAS_OUTPUT_2P6 = 0xC,
    SARADC_MICBIAS_OUTPUT_2P8 = 0xE,
}enum_saradc_micbias_ctrl_t;

/**
  * @brief  ADC Initialization Structure definition
  */
typedef struct 
{
    uint32_t    saradc_reference;             /*!< Specifies the reference source of ADC.
                                                This parameter can be a value @ref enum_saradc_reference_t */

    uint32_t    saradc_clock_div;             /*!< Specifies the clock divider of saradc.
                                                This parameter can be a multiple of 2. Max 254 */

    uint32_t    saradc_sampling_cycle;        /*!< Specifies the sampling cycle of saradc.
                                                This parameter can be a value from 1 to 16 */

    uint32_t    saradc_interval_clock_div;    /*!< Specifies the interval clock divider of saradc.
                                                This parameter can be a value from 1 to 16 */

    uint32_t    saradc_voltage_divider;       /*!< Specifies Voltage divider of input voltage.
                                                This parameter can be a value @ref enum_saradc_voltage_divider_t */

    uint32_t    saradc_mode;                  /*!< Specifies the work mode of saradc.
                                                This parameter can be a value @ref enum_saradc_mode_t */
}saradc_InitConfig_t;


/**
  * @brief  ADC loop mode configuration parameters.
  */
typedef struct 
{
    uint32_t    loop_triggerMode;             /*!< Specifies the trigger mode of loop mode.
                                                   This parameter can be a value @ref enum_saradc_trigger_mode_t */

    uint32_t    loop_max_channel;             /*!< Specifies the MAX channel of loop mode.
                                                   This parameter can be a value from 1 to 16 */

    uint32_t    loop_interval;                /*!< Specifies the interval time of loop mode.
                                                   This parameter can be a value from 0 to 0xFFF */

    uint32_t    loop_FIFO_enable;             /*!< Specifies the FIFO mode of loop mode.
                                                   This parameter can be a value @ref enum_saradc_fifo_mode_t */

    uint32_t    loop_FIFO_channel_sel;        /*!< Specifies the binding channel of fifo. 
                                                   channel num from 0 to 15 */

    uint32_t    loop_FIFO_almost_threshold;   /*!< Specifies the almost threshold of fifo. 
                                                   This parameter can be a value from 0 to 64 */
}saradc_LoopConfig_t;

/**
  * @brief  saradc wdt Initialization Structure definition
  */
typedef struct 
{
    uint8_t    saradc_WDT_mode;                 /*!< Specifies the work mode of saradc wdt.
                                                     This parameter can be a value @ref enum_saradc_wdt_mode_t */

    uint16_t   saradc_WDT_monitor_channel;      /*!< Specifies the monitor channel of saradc wdt, multiple channels can be selected.
                                                     This parameter can be a value @ref enum_saradc_wdt_monitor_channel_t */

    uint8_t    saradc_WDT_trigger_threshold;    /*!< Specifies the channel trigger threshold of saradc wdt.
                                                     This parameter can be a value from 1 to 16 */

    uint16_t   saradc_WDT_min_limit;            /*!< Specifies the min limit value of saradc wdt.
                                                     This parameter can be a value from 0 to 0xFFF */

    uint16_t   saradc_WDT_max_limit;            /*!< Specifies the max limit value of saradc wdt.
                                                     This parameter can be a value from 0 to 0xFFF */
}saradc_WdtConfig_t;

/**
  * @brief  saradc queue Initialization Structure definition
  */
typedef struct 
{
    uint8_t    saradc_queue_mode;               /*!< Specifies the work mode of saradc queue.
                                                     This parameter can be a value @ref enum_saradc_queue_mode_t */

    uint8_t    saradc_queue_channels;           /*!< Specifies the number of channels in the queue.
                                                     This parameter can be a value from 1 to 16 */

    uint32_t   saradc_queue_cycle;              /*!< Specifies the queue cycle period.
                                                     This parameter can be a value from 0 to 0xFFFFFF */

    uint8_t    saradc_queue_chx_select[16];     /*!< Select channels for 1 to 16 positions in the queue.
                                                     This parameter can be a value from 0 to 15 */
}saradc_QueueConfig_t;

/* ################################ Initialization, Config Section END ################################## */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/* SARADC convert start/stop */
#define __SARADC_CONVERT_START()                               (SARADC->SARADC_Control.SARADC_EN = 1)
#define __SARADC_CONVERT_STOP()                                (SARADC->SARADC_Control.SARADC_EN = 0)
/* SARADC reset */
#define __SARADC_RESET()                                       (SARADC->SARADC_Control.SARADC_Reset = 1)
#define __SARADC_FIFO_RESET()                                  (SARADC->SARADC_Control.SARADC_FIFO_Reset = 1)
/* SARADC soft trigger convert */
#define __SARADC_SOFT_TRIGGER_CONVERT()                        (SARADC->SARADC_Control.SARADC_Soft_Trigger = 1)

/* SARADC work mode select */
#define __SARADC_WORK_MODE_SELECT(__MODE__)                    (SARADC->SARADC_Config.SARADC_Mode = __MODE__)
#define __SARADC_GET_WORK_MODE()                               (SARADC->SARADC_Config.SARADC_Mode)
/* SARADC trigger mode */
#define __SARADC_TRIGGER_MODE(__MODE__)                        (SARADC->SARADC_Config.SARADC_Trigger_Mode = __MODE__)
/* SARADC FIFO enable/dsiable */
#define __SARADC_FIFO_ENABLE()                                 (SARADC->SARADC_Config.SARADC_FIFO_EN = 1)
#define __SARADC_FIFO_DISABLE()                                (SARADC->SARADC_Config.SARADC_FIFO_EN = 0)
/* SARADC loop mode max channel config */
#define __SARADC_MAX_CHANNEL_CONFIG(__MAX__)                   (SARADC->SARADC_Config.SARADC_MAX_Channle = __MAX__)
/* SARADC FIFO Select specified channel */
#define __SARADC_FIFO_SELECT_CHANNEL(__CH__)                   (SARADC->SARADC_Config.SARADC_FIFO_Channel_Sel = __CH__)
#define __SARADC_FIFO_CHANNEL_INDEX_ENABLE(__CH__)             (SARADC->SARADC_Config.SARADC_FIFO_Channel_Index_En = 1)
#define __SARADC_FIFO_CHANNEL_INDEX_DISABLE(__CH__)            (SARADC->SARADC_Config.SARADC_FIFO_Channel_Index_En = 0)
/* SARADC interval counting clock divider */
#define __SARADC_INTERVAL_CLOCK_DIV_CONFIG(__DIV__)            (SARADC->SARADC_Config.SARADC_Interval_Clock_Div = __DIV__)
/* SARADC loop mode interval length */
#define __SARADC_LOOP_INTERVAL_LENGTH(__LEN__)                 (SARADC->SARADC_Config.SARADC_Interval_Length = __LEN__)

/* SARADC sampling clock divider */
#define __SARADC_SAMPLING_CLOCK_DIV_CONFIG(__DIV__)            (SARADC->SARADC_Timing.SARADC_Clock_DIV = __DIV__)
#define __SARADC_SAMPLING_TIMEOUT_CONFIG(__TO__)               (SARADC->SARADC_Timing.SARADC_Sample_TimeoutCNT = __TO__)
#define __SARADC_CONVERT_TIMEOUT_CONFIG(__TO__)                (SARADC->SARADC_Timing.SARADC_Convert_TimeoutCNT = __TO__)
#define __SARADC_HOLDTIME_LENGTH_CONFIG(__LEN__)               (SARADC->SARADC_Timing.SARADC_Hold_Time = __LEN__)
#define __SARADC_DYNAMIC_ADJUST_CONFIG(__DA__)                 (SARADC->SARADC_Timing.SARADC_Timing_Dynamic_Adjust = __DA__)

/* SARADC WDT0 config */
#define __SARADC_WDT0_ENABLE()                                 (SARADC->SARADC_WDT0_Config.WDT_EN = 1)
#define __SARADC_WDT0_DISABLE()                                (SARADC->SARADC_WDT0_Config.WDT_EN = 0)
#define __SARADC_WDT0_MODE_CONFIG(__MODE__)                    (SARADC->SARADC_WDT0_Config.WDT_Mode = __MODE__)
#define __SARADC_WDT0_TRIGGER_THRESHOLD(__THR__)               (SARADC->SARADC_WDT0_Config.WDT_Trigger_Threshold = __THR__)
#define __SARADC_WDT0_MONITOR_CHANNEL_ENABLE(__CH__)           (SARADC->SARADC_WDT0_Config.WDT_Monitor_Channel_Sel |= (__CH__))
#define __SARADC_WDT0_MONITOR_CHANNEL_DISABLE(__CH__)          (SARADC->SARADC_WDT0_Config.WDT_Monitor_Channel_Sel &= ~(__CH__))
#define __SARADC_WDT0_GET_MONITOR_CHANNEL()                    (SARADC->SARADC_WDT0_Config.WDT_Monitor_Channel_Sel)
#define __SARADC_WDT0_SET_MONITOR_CHANNEL(__CH__)              (SARADC->SARADC_WDT0_Config.WDT_Monitor_Channel_Sel = __CH__)
#define __SARADC_WDT0_MAX_LIMIT(__MAX__)                       (SARADC->SARADC_WDT0_Threshold.WDT_Max_Limit = __MAX__)
#define __SARADC_WDT0_MIN_LIMIT(__MIN__)                       (SARADC->SARADC_WDT0_Threshold.WDT_Min_Limit = __MIN__)
/* SARADC WDT1 config */
#define __SARADC_WDT1_ENABLE()                                 (SARADC->SARADC_WDT1_Config.WDT_EN = 1)
#define __SARADC_WDT1_DISABLE()                                (SARADC->SARADC_WDT1_Config.WDT_EN = 0)
#define __SARADC_WDT1_MODE_CONFIG(__MODE__)                    (SARADC->SARADC_WDT1_Config.WDT_Mode = __MODE__)
#define __SARADC_WDT1_TRIGGER_THRESHOLD(__THR__)               (SARADC->SARADC_WDT1_Config.WDT_Trigger_Threshold = __THR__)
#define __SARADC_WDT1_MONITOR_CHANNEL_ENABLE(__CH__)           (SARADC->SARADC_WDT1_Config.WDT_Monitor_Channel_Sel |= (__CH__))
#define __SARADC_WDT1_MONITOR_CHANNEL_DISABLE(__CH__)          (SARADC->SARADC_WDT1_Config.WDT_Monitor_Channel_Sel &= ~(__CH__))
#define __SARADC_WDT1_GET_MONITOR_CHANNEL()                    (SARADC->SARADC_WDT1_Config.WDT_Monitor_Channel_Sel)
#define __SARADC_WDT1_SET_MONITOR_CHANNEL(__CH__)              (SARADC->SARADC_WDT1_Config.WDT_Monitor_Channel_Sel = __CH__)
#define __SARADC_WDT1_MAX_LIMIT(__MAX__)                       (SARADC->SARADC_WDT1_Threshold.WDT_Max_Limit = __MAX__)
#define __SARADC_WDT1_MIN_LIMIT(__MIN__)                       (SARADC->SARADC_WDT1_Threshold.WDT_Min_Limit = __MIN__)

/* SARADC QUEUE0 config */
#define __SARADC_QUEUE0_ENABLE()                               (SARADC->SARADC_Queue0_Config.Queue_En = 1)
#define __SARADC_QUEUE0_DISABLE()                              (SARADC->SARADC_Queue0_Config.Queue_En = 0)
#define __SARADC_QUEUE0_MODE_CONFIG(__MODE__)                  (SARADC->SARADC_Queue0_Config.Queue_Mode = __MODE__)
#define __SARADC_QUEUE0_CHANNEL_NUM_CONFIG(__NUM__)            (SARADC->SARADC_Queue0_Config.Queue_Channel_Num = __NUM__)
#define __SARADC_QUEUE0_CYCLE_CONFIG(__CYCLE__)                (SARADC->SARADC_Queue0_Config.Queue_Cycle = __CYCLE__)
#define __SARADC_QUEUE0_LOW8_CHANNEL_CONFIG(__CH__)            (SARADC->SARADC_Queue0_ChannelSel0 = __CH__)
#define __SARADC_QUEUE0_HIGH8_CHANNEL_CONFIG(__CH__)           (SARADC->SARADC_Queue0_ChannelSel1 = __CH__)
/* SARADC QUEUE1 config */
#define __SARADC_QUEUE1_ENABLE()                               (SARADC->SARADC_Queue1_Config.Queue_En = 1)
#define __SARADC_QUEUE1_DISABLE()                              (SARADC->SARADC_Queue1_Config.Queue_En = 0)
#define __SARADC_QUEUE1_MODE_CONFIG(__MODE__)                  (SARADC->SARADC_Queue1_Config.Queue_Mode = __MODE__)
#define __SARADC_QUEUE1_CHANNEL_NUM_CONFIG(__NUM__)            (SARADC->SARADC_Queue1_Config.Queue_Channel_Num = __NUM__)
#define __SARADC_QUEUE1_CYCLE_CONFIG(__CYCLE__)                (SARADC->SARADC_Queue1_Config.Queue_Cycle = __CYCLE__)
#define __SARADC_QUEUE1_LOW8_CHANNEL_CONFIG(__CH__)            (SARADC->SARADC_Queue1_ChannelSel0 = __CH__)
#define __SARADC_QUEUE1_HIGH8_CHANNEL_CONFIG(__CH__)           (SARADC->SARADC_Queue1_ChannelSel1 = __CH__)
/* SARADC QUEUE2 config */
#define __SARADC_QUEUE2_ENABLE()                               (SARADC->SARADC_Queue2_Config.Queue_En = 1)
#define __SARADC_QUEUE2_DISABLE()                              (SARADC->SARADC_Queue2_Config.Queue_En = 0)
#define __SARADC_QUEUE2_MODE_CONFIG(__MODE__)                  (SARADC->SARADC_Queue2_Config.Queue_Mode = __MODE__)
#define __SARADC_QUEUE2_CHANNEL_NUM_CONFIG(__NUM__)            (SARADC->SARADC_Queue2_Config.Queue_Channel_Num = __NUM__)
#define __SARADC_QUEUE2_CYCLE_CONFIG(__CYCLE__)                (SARADC->SARADC_Queue2_Config.Queue_Cycle = __CYCLE__)
#define __SARADC_QUEUE2_LOW8_CHANNEL_CONFIG(__CH__)            (SARADC->SARADC_Queue2_ChannelSel0 = __CH__)
#define __SARADC_QUEUE2_HIGH8_CHANNEL_CONFIG(__CH__)           (SARADC->SARADC_Queue2_ChannelSel1 = __CH__)

/* SARADC ANALOG config */
#define __SARADC_ANALOG_RESET()                                (SARADC->SARADC_AnalogConfig0.Analog_reset = 0)
#define __SARADC_ANALOG_RESET_STOP()                           (SARADC->SARADC_AnalogConfig0.Analog_reset = 1)
#define __SARADC_IS_ANALOG_RESET()                             (SARADC->SARADC_AnalogConfig0.Analog_reset == 0)
#define __SARADC_ANALOG_POWER_ENABLE()                         (SARADC->SARADC_AnalogConfig0.Analog_PD = 0)
#define __SARADC_ANALOG_POWER_DISABLE()                        (SARADC->SARADC_AnalogConfig0.Analog_PD = 1)

/* SARADC ANALOG sampling time */
#define __SARADC_ANALOG_SAMPLING_TIME_CONFIG(__TIME__)         (SARADC->SARADC_AnalogConfig0.Analog_smapling_time = __TIME__)
/* SARADC Measure voltage divider config */
#define __SARADC_MEASURE_VOLTAGE_DIVIDER_CONFIG(__CFG__)       (SARADC->SARADC_AnalogConfig0.Analog_ATT_control = __CFG__)
/* SARADC ANALOG reference source select */
#define __SARADC_ANALOG_REFERENCE_SOURCE_SELECT(__SEL__)       (SARADC->SARADC_AnalogConfig0.Analog_REF_control = __SEL__)
/* SARADC input channel enable */
#define __SARADC_INPUT_CHANNEL_ENABLE()                        (SARADC->SARADC_AnalogConfig0.Input_channel_en = 1)
#define __SARADC_INPUT_CHANNEL_DISABLE()                       (SARADC->SARADC_AnalogConfig0.Input_channel_en = 0)
/* SARADC internal reference enable/disable */
#define __SARADC_INTERNAL_REFERENCE_BUF_ENABLE()               (SARADC->SARADC_AnalogConfig0.Analog_INT_BUF_EN = 1)
#define __SARADC_INTERNAL_REFERENCE_BUF_DISABLE()              (SARADC->SARADC_AnalogConfig0.Analog_INT_BUF_EN = 0)
/* SARADC internal reference voltage config */
#define __SARADC_INTERNAL_REFERENCE_VOLTAGE_CONFIG(__V__)      (SARADC->SARADC_AnalogConfig1.INT_REF_CTRL = __V__)

/* SARADC channel config */
#define __SARADC_CHANNEL_DIFFERENCE_ENABLE(__CH__)             (SARADC->SARADC_ChannelConfig[__CH__].Difference_EN = 1)
#define __SARADC_CHANNEL_DIFFERENCE_DISABLE(__CH__)            (SARADC->SARADC_ChannelConfig[__CH__].Difference_EN = 0)
#define __SARADC_CHANNEL_MAP_N_CONFIG(__CH__, __MAP__)         (SARADC->SARADC_ChannelConfig[__CH__].Channel_Map_N = __MAP__)
#define __SARADC_CHANNEL_MAP_P_CONFIG(__CH__, __MAP__)         (SARADC->SARADC_ChannelConfig[__CH__].Channel_Map_P = __MAP__)

/* SARADC DMA enable/disable */
#define __SARADC_DMA_ENABLE()                                  (SARADC->SARADC_FIFO_Config.DMA_EN = 1)
#define __SARADC_DMA_DISABLE()                                 (SARADC->SARADC_FIFO_Config.DMA_EN = 0)
#define __SARADC_DMA_THRESHOLD_CONFIG(__THR__)                 (SARADC->SARADC_FIFO_Config.DMA_Threshold = __THR__)
#define __SARADC_FIFO_THRESHOLD_CONFIG(__THR__)                (SARADC->SARADC_FIFO_Config.FIFO_Almost_Full_Threshold = __THR__)

/* SARADC get channel valid status */
#define __SARADC_GET_CHANNEL_VALID_STATUS()                    (SARADC->SARADC_ChannelStatus)

/* SARADC get fifo data/count */
/* SARADC get channel data */
#define __SARADC_GET_FIFO_DATA()                               (SARADC->SARADC_FIFO_Data)
#define __SARADC_GET_FIFO_COUNT()                              (SARADC->SARADC_FIFO_Count)
#define __SARADC_GET_CHANNEL_DATA(__CH__)                      (SARADC->SARADC_ChannelData[__CH__])

/* SARADC interrupt enable/disable */
#define __SARADC_INT_ENABLE(__INDEX__)                         (SARADC->SARADC_INT_Enble |= (__INDEX__))
#define __SARADC_INT_DISABLE(__INDEX__)                        (SARADC->SARADC_INT_Enble &= ~(__INDEX__))
/* SARADC get interrupt status */
/* SARADC get interrupt raw status */
#define __SARADC_GET_INT_STATUS()                              (SARADC->SARADC_INT_Status)
#define __SARADC_GET_INT_RAW_STATUS()                          (SARADC->SARADC_INT_Raws)
/* SARADC clear interrupt status */
#define __SARADC_CLR_INT_STATUS(__INDEX__)                     (SARADC->SARADC_INT_Status = (__INDEX__))

/* vbat,vbe measure config */
#define __SARADC_VBAT_MEASURE_CONFIG(__CFG__)                  (SARADC->SARADC_VbatCtrl = __CFG__)
#define __SARADC_VBE_MEASURE_CONFIG()                          (SARADC->SARADC_VbeCtrl = 0x2)
/* mic bias config */
#define __SARADC_MIC_BIAS_CONFIG(__CFG__)                      (SARADC->SARADC_MICCtrl = __CFG__)

/* PGA control */
#define __SARADC_PGA0_POWER_ENABLE()                           (SARADC->SARADC_PGA0Ctrl.PGA0_PD = 0)
#define __SARADC_PGA1_POWER_ENABLE()                           (SARADC->SARADC_PGA1Ctrl.PGA1_PD = 0)
#define __SARADC_PGA2_POWER_ENABLE()                           (SARADC->SARADC_PGA2Ctrl.PGA2_PD = 0)
#define __SARADC_PGA0_POWER_DISABLE()                          (SARADC->SARADC_PGA0Ctrl.PGA0_PD = 1)
#define __SARADC_PGA1_POWER_DISABLE()                          (SARADC->SARADC_PGA1Ctrl.PGA1_PD = 1)
#define __SARADC_PGA2_POWER_DISABLE()                          (SARADC->SARADC_PGA2Ctrl.PGA2_PD = 1)

#define __SARADC_PGA1I_TO_PGA2_EN(__EN__)                      (SARADC->SARADC_PGA0Ctrl.PGA1I_TO_PGA2_EN = __EN__)
#define __SARADC_PGA1O_TO_PGA2_EN(__EN__)                      (SARADC->SARADC_PGA0Ctrl.PGA1O_TO_PGA2_EN = __EN__)

#define __SARADC_PGA1_GAIN_CONFIG(__CFG__)                     (SARADC->SARADC_PGA1Ctrl.PGA1_GAIN = __CFG__)
#define __SARADC_PGA2_GAIN_CONFIG(__CFG__)                     (SARADC->SARADC_PGA2Ctrl.PGA2_GAIN = __CFG__)

#define __SARADC_PGA1_OP_OSTG_IS_CONFIG(__CFG__)               (SARADC->SARADC_PGA1Ctrl.PGA1_OP_OSTG_IS = __CFG__)
#define __SARADC_PGA2_OP_OSTG_IS_CONFIG(__CFG__)               (SARADC->SARADC_PGA2Ctrl.PGA2_OP_OSTG_IS = __CFG__)

#define __SARADC_PGA1_SW_CONFIG(__CFG__)                       (SARADC->SARADC_PGA1Ctrl.PGA1_SW_CTL = __CFG__)
#define __SARADC_PGA2_SW_CONFIG(__CFG__)                       (SARADC->SARADC_PGA2Ctrl.PGA2_SW_CTL = __CFG__)

#define __SARADC_GAIN_ENABLE()                                 (SARADC->SARADC_CAINCtrl.GAIN_EN = 1)
#define __SARADC_GAIN_DISABLE()                                (SARADC->SARADC_CAINCtrl.GAIN_EN = 0)
#define __SARADC_GAIN_DEN_CONFIG(__CFG__)                      (SARADC->SARADC_CAINCtrl.GAIN_DEN = __CFG__)
#define __SARADC_GAIN_NOM_CONFIG(__CFG__)                      (SARADC->SARADC_CAINCtrl.GAIN_NOM = __CFG__)
#define __SARADC_GAIN_DC_CONFIG(__CFG__)                       (SARADC->SARADC_CAINCtrl.GAIN_DC = __CFG__)

/* Exported functions --------------------------------------------------------*/

/* saradc_init */
void saradc_init(saradc_InitConfig_t *Init);

/* loop mode convert start/stop */
bool saradc_loop_config(saradc_LoopConfig_t *sConfig);
void saradc_loop_convert_start(void);
void saradc_loop_convert_stop(void);
void saradc_loop_software_trigger_convert(void);

/* wdt config */
void saradc_wdt_config(enum_saradc_wdt_t fe_wdt, saradc_WdtConfig_t *fstr_config);
void saradc_wdt_enable(enum_saradc_wdt_t fe_wdt);
void saradc_wdt_disable(enum_saradc_wdt_t fe_wdt);

/* queue config */
bool saradc_queue_config(enum_saradc_queue_t fe_queue, saradc_QueueConfig_t *fstr_config);
void saradc_queue_enable(enum_saradc_queue_t fe_queue);
void saradc_queue_disable(enum_saradc_queue_t fe_queue);

/* saradc_get_fifo_count */
/* saradc_get_fifo_data */
uint16_t saradc_get_fifo_count(void);
void saradc_get_fifo_data(uint16_t *fp_data, uint32_t fu32_length);

/* saradc_get_channel_valid_status */
/* saradc_get_channel_data */
bool saradc_get_channel_valid_status(enum_saradc_channel_t fe_channel);
uint16_t saradc_get_channel_data(enum_saradc_channel_t fe_channel);

/* saradc_channel_single_config */
/* saradc_channel_differential_config */
void saradc_channel_single_config(enum_saradc_channel_t fe_channel, enum_ADC_Channel_Map_t fe_Map);
void saradc_channel_differential_config(enum_saradc_channel_t fe_channel, enum_ADC_Channel_Map_t fe_Map_P, enum_ADC_Channel_Map_t fe_Map_N);

/* saradc_vbe_measure_enable/disable */
void saradc_vbe_measure_enable(void);
void saradc_vbe_measure_disable(void);

/* saradc_vbat_measure_enable/disable */
void saradc_vbat_measure_enable(enum_saradc_vbat_ctrl_t fe_VbatCfg);
void saradc_vbat_measure_disable(void);

/* saradc_mic_bias_output_enable/disable */
void saradc_mic_bias_output_enable(enum_saradc_micbias_ctrl_t fe_micbias);
void saradc_mic_bias_output_disable(void);

/* saradc_pga_enable/disable */
void saradc_pga_enable(void);
void saradc_pga_disable(void);
/* saradc_gain_enable/disable */
void saradc_gain_enable(void);
void saradc_gain_disable(void);

/* saradc interrupt enable/disable */
/* saradc interrupt get status/clear status */
void saradc_int_enable(enum_saradc_int_status_t fe_int);
void saradc_int_disable(enum_saradc_int_status_t fe_int);
uint32_t saradc_get_int_status(void);
uint32_t saradc_get_int_raw_status(void);
void saradc_int_status_clear(enum_saradc_int_status_t fe_int);

#endif
