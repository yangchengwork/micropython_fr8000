/*
  ******************************************************************************
  * @file    driver_adc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2021
  * @brief   Header file of ADC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_ADC_H__
#define __DRIVER_ADC_H__

#include "fr30xx.h"

/** @addtogroup ADC_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

#define ADC_MAX_CHANNELS        (8)
#define ADC_MAX_IO_INPUT_MAP    (4)

/* Control Register for ADC */
typedef struct
{
    uint32_t ADC_ConvertEN   : 1;
    uint32_t ADC_Reset       : 1;
    uint32_t rsv_0           : 1;
    uint32_t ADC_SoftTrigger : 1;
    uint32_t rsv_1           : 28;
}REG_ADC_Control_t;

/* Config Register for ADC */
typedef struct
{
    uint32_t ADC_ChannelMax         : 4;
    uint32_t ADC_ConvertMode        : 1;
    uint32_t ADC_TriggerMode        : 1;
    uint32_t ADC_FIFO_EN            : 1;
    uint32_t rsv_0                  : 1;
    uint32_t ADC_SoftTriggerChannel : 4;
    uint32_t rsv_1                  : 20;
}REG_ADC_Config_t;

/* Timing Register for ADC */
typedef struct
{
    uint32_t Clock_DIV    : 8;
    uint32_t rsv_0        : 8;
    uint32_t SetupCycle   : 6;
    uint32_t SampleCycle  : 5;
    uint32_t TimeoutCycle : 5;
}REG_ADC_Timing_t;

/* ----------------------------------------------*/
/*                 ADC Registers                 */
/* ----------------------------------------------*/
typedef struct 
{
    volatile REG_ADC_Control_t    Control;           /* Offset 0x00 */
    volatile REG_ADC_Config_t     Config;            /* Offset 0x04 */
    volatile REG_ADC_Timing_t     Timing;            /* Offset 0x08 */
    volatile uint32_t             rsv_0;             /* Offset 0x0C */
    volatile uint32_t             rsv_1;             /* Offset 0x10 */
    volatile uint32_t             rsv_2;             /* Offset 0x14 */
    volatile uint32_t             Channel_Status;    /* Offset 0x18 */
    volatile uint32_t             rsv_3;             /* Offset 0x1C */
    volatile uint32_t             ADC_INT_Enble;     /* Offset 0x20 */
    volatile uint32_t             ADC_INT_Status;    /* Offset 0x24 */
    volatile uint32_t             ADC_INT_Raws;      /* Offset 0x28 */
    volatile uint32_t             ACT0;              /* Offset 0x2C */
    volatile uint32_t             ACT1;              /* Offset 0x30 */
    volatile uint32_t             ChannelMap[8];     /* Offset 0x34 ~ 0x50 */
    volatile uint32_t             rsv0[8];
    volatile uint32_t             ChannelData[8];    /* Offset 0x74 ~ 0x90 */
}struct_ADC_t;

#define ADC              ((struct_ADC_t *)ADC_BASE)

/* ################################ Register Section END ################################ */
/**
  * @}
  */


/** @addtogroup ADC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization, Config Section Start ################################ */

#define ADC_INT_CONVERT_ERR      (0x10)
#define ADC_INT_CHANNEL_VALID    (0x08)

#define ADC_ACT0_REF_1P2V        (0x1A036)
#define ADC_ACT0_REF_IOLDO       (0xDA036)

#define ADC_ACT1_VBE_EN     (0x02)
#define ADC_ACT1_VBAT_EN    (0x04)
#define ADC_ACT1_IS         (0x40)

/* ADC interrupt index */
typedef enum  
{
    ADC_CHANNEL_MAP_PMU_P4,    /* PMU P4 */
    ADC_CHANNEL_MAP_PMU_P5,    /* PMU P5 */
    ADC_CHANNEL_MAP_PMU_P6,    /* PMU P6 */
    ADC_CHANNEL_MAP_PMU_P7,    /* PMU P7 */
    ADC_CHANNEL_MAP_VBE,       /* VBE */
    ADC_CHANNEL_MAP_VBAT,      /* 1/4 VBAT */
}enum_ADC_Channel_Map_t;

/* ADC interrupt index */
typedef enum  
{
    ADC_FIFO_EMPTY       = 0x01,
    ADC_FIFO_FULL        = 0x02,
    ADC_FIFO_ALMOST_FULL = 0x04,
    ADC_CHANNEL_VALID    = 0x08,
    ADC_ERR              = 0x10,
}enum_ADC_int_index_t;

/* ADC convert mode */
typedef enum  
{
    ADC_SINGLE_MODE,
    ADC_LOOP_MODE,
}enum_ADC_convert_mode_t;

/* ADC FIFO mode */
typedef enum    
{
    ADC_FIFO_DISABLE,
    ADC_FIFO_ENABLE,
}enum_ADC_FIFO_EN_t;

/* ADC convert mode */
typedef enum  
{
    ADC_HARDWARE_TRIGGER,
    ADC_SOFTWARE_TRIGGER,
}enum_ADC_trigger_mode_t;

typedef enum  
{
    ADC_REF_IOLDO,
    ADC_REF_1P2V,
}enum_ADC_reference_t;

/**
  * @brief  hard trigger config definition
  */
typedef struct 
{
    uint32_t ADC_Convert_Mode;        /*!< Specifies the convert mode, single or loop.
                                           This parameter can be a value @ref enum_ADC_convert_mode_t */

    uint32_t ADC_Channel_Max;         /*!< Specifies the number of Maximum conversion channels.
                                           This parameter can be a value between 1 ~ 8 */
}struct_HardTriggerConfig_t;

/**
  * @brief  ADC Initialization Structure definition
  */
typedef struct 
{
    uint32_t    ADC_Reference;         /*!< Specifies the reference source of ADC.
                                            This parameter can be a value @ref enum_ADC_reference_t */

    uint32_t                      ADC_TriggerMode;         /*!< Specifies the number of ADC Trigger Mode.
                                                                This parameter can be a value @ref enum_ADC_trigger_mode_t */

    struct_HardTriggerConfig_t    HardTriggerConfig;       /*!< ADC hard trigger config parameters */

}adc_InitConfig_t;

/* ################################ Initialization, Config Section END ################################ */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/* ADC hard Convert Enable/Disable */
#define __ADC_CONVERT_ENABLE()                              (ADC->Control.ADC_ConvertEN = 1)
#define __ADC_CONVERT_DISABLE()                             (ADC->Control.ADC_ConvertEN = 0)

/* ADC State machine Reset */
#define __ADC_RESET()                                       (ADC->Control.ADC_Reset = 1)
/* soft trigger convert */
#define __ADC_SOFT_TRIGGER()                                (ADC->Control.ADC_SoftTrigger = 1)
/* set soft trigger channel */
#define __ADC_SET_SOFT_TRIGGER_CHANNEL(__CHANNEL__)         (ADC->Config.ADC_SoftTriggerChannel = __CHANNEL__)

/* Set max channel */
#define __ADC_SET_MAX_CHANNEL(__MAXCH__)                    (ADC->Config.ADC_ChannelMax = __MAXCH__)
/* Set convert mode */
#define __ADC_SET_CONVERT_MODE(__MODE__)                    (ADC->Config.ADC_ConvertMode = __MODE__)
/* Set trigger mode */
#define __ADC_SET_TRIGGER_MODE(__MODE__)                    (ADC->Config.ADC_TriggerMode = __MODE__)

/* set adc clock div */
#define __ADC_SET_CLK_DIV(__DIV__)                          (ADC->Timing.Clock_DIV = __DIV__)
/* set convert setup/sample/timout cycle */
#define __ADC_SET_SETUP_CYCLE(__CYCLE__)                    (ADC->Timing.SetupCycle   = __CYCLE__)
#define __ADC_SET_SAMPLE_CYCLE(__CYCLE__)                   (ADC->Timing.SampleCycle  = __CYCLE__)
#define __ADC_SET_TIMEOUT_CYCLE(__CYCLE__)                  (ADC->Timing.TimeoutCycle = __CYCLE__)

/* Get ADC Channel status */
#define __ADC_GET_CHANNEL_STATUS()                          (ADC->Channel_Status)

/* ADC interrupt enable/disable */
#define __ADC_INT_ENABLE(__INDEX__)                         (ADC->ADC_INT_Enble |= __INDEX__)
#define __ADC_INT_DISABLE(__INDEX__)                        (ADC->ADC_INT_Enble &= ~(__INDEX__))
#define __ADC_GET_INT_STATUS()                              (ADC->ADC_INT_Raws)

/* Set channel map */
#define __ADC_SET_CHANNEL_MAP(__CHANNEL__, __MAP__)         (ADC->ChannelMap[__CHANNEL__] = __MAP__)
/* Get channel data */
#define __ADC_GET_CHANNEL_DATA(__CHANNEL__)                 (ADC->ChannelData[__CHANNEL__])


/* Exported functions --------------------------------------------------------*/

/* adc_init */
void adc_init(adc_InitConfig_t InitConfig);

/* adc_convert_start/stop */
void adc_convert_start(void);
void adc_convert_start_IT(void);
void adc_convert_stop(void);

void adc_channel_valid_int_enable(void);
void adc_channel_valid_int_dsiable(void);

/* adc_soft_trigger_convert */
void adc_soft_trigger_convert(uint8_t fu8_Channel);

/* adc_get_channel_valid_status */
bool adc_get_channel_valid_status(uint8_t fu8_Channel);
/* adc_get_channel_data */
uint32_t adc_get_channel_data(uint8_t fu8_Channel);

/* adc_set_channel_maping */
void adc_set_channel_maping(uint8_t fu8_Channel, enum_ADC_Channel_Map_t fe_Map);

uint32_t adc_get_channel_data_FT(uint8_t fu8_Channel);

#endif
