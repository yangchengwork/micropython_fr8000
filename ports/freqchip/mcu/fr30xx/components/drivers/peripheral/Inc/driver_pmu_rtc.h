/*
  ******************************************************************************
  * @file    driver_pmu_rtc.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of pmu rtc HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_PMU_RTC_H__
#define __DRIVER_PMU_RTC_H__

#include "fr30xx.h"

/** @addtogroup RTC_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization¡¢Config Section Start ################################ */

typedef struct 
{
    uint32_t UnitBackup;
}str_Time_t;

typedef enum
{
    AlARM_A = 0x10,
    AlARM_B = 0x20,
}enum_Alarm_t;

/* ################################ Initialization¡¢Config Section END ################################## */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/* rtc_AlarmA_Handler */
/* rtc_AlarmB_Handler */
void rtc_AlarmA_Handler(void);
void rtc_AlarmB_Handler(void);

/* rtc_init */
void rtc_init(uint32_t InitValue);

/* rtc_CountEnable */
/* rtc_CountDisable */
void rtc_CountEnable(void);
void rtc_CountDisable(void);

/* rtc_AlarmConfig */
void rtc_AlarmConfig(enum_Alarm_t fe_Alarm, uint32_t fu32_hour, uint32_t fu32_Minute, uint32_t fu32_Second);

/* rtc_GetCount */
uint32_t rtc_GetCount(void);

/* rtc_CountUpdate */
void rtc_CountUpdate(uint32_t fu32_CountValue);

/* rtc_AlarmUpdate */
void rtc_AlarmUpdate(enum_Alarm_t fe_Alarm);

/* rtc_AlarmEnable */
/* rtc_AlarmDisable */
void rtc_AlarmEnable(enum_Alarm_t fe_Alarm);
void rtc_AlarmDisable(enum_Alarm_t fe_Alarm);

/* rtc_AlarmRead */
/* rtc_AlarmSet */
uint32_t rtc_AlarmRead(enum_Alarm_t fe_Alarm);
void rtc_AlarmSet(enum_Alarm_t fe_Alarm, uint32_t fu32_CountValue);

void rtc_AlarmStart_ms(enum_Alarm_t fe_Alarm, uint32_t fu32_ms);
void rtc_AlarmUpdate_ms(enum_Alarm_t fe_Alarm, uint32_t fu32_ms);

#endif
