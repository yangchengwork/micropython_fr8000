/*
  ******************************************************************************
  * @file    trim_fr30xx.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   Header file of trim HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __TRIM_FR1010_H__
#define __TRIM_FR1010_H__

#include "fr30xx.h"

/** @addtogroup trim_Parameter_Section
  * @{
  */
/* ################################ trim Parameter Section Start ################################ */

/*--------------------------------------------------*/
/*                CP trim Parameter                 */
/*--------------------------------------------------*/
typedef __PACKED_STRUCT 
{
    /* --------- vendor-specific --------- */
    uint8_t BBG_CODE    ;
    uint8_t SBG_CODE    ;
    uint8_t PKVDD_CODE  ;
    uint8_t SPKVDD_CODE ;
    uint8_t OSCLDO_CODE ;
    uint8_t ADLDO_CODE  ;
    uint8_t DDLDO_CODE  ;
    uint32_t WaferID    ;
    uint8_t CPEVEN_CKECK;
    uint8_t SBUCK_CODE  ;
    uint8_t IOLDO1      ;
    uint8_t IOLDO2      ;
    uint8_t CHG_GT      ;
    uint8_t IOBUCK_CODE ;
    uint8_t AULDO_CODE  ;
    uint8_t CHG_TER     ;
    uint8_t CHG_SMP     ;
    uint8_t FTEVEN_CHECK;

    /* --------- vendor-specific END--------- */
}struct_CP_Trim_t;

/*--------------------------------------------------*/
/*                FT trim Parameter                 */
/*--------------------------------------------------*/
typedef struct Tx_Power_param{
    uint8_t Digi_param;
    uint8_t Ana_param;
    
}Tx_Power_param_t;

typedef struct 
{
    uint16_t u16_Version;
    uint16_t u16_ioldo;
    
    int32_t  s32_ConstantA;
    int32_t  s32_ConstantB;
    uint16_t u16_SlopeA;
    uint16_t u16_SlopeB;
    union {
        struct{
            Tx_Power_param_t Tx_Power[4]; 
            uint16_t u16_ChargeV;
            uint32_t u32_crc;
        }V2;
        struct{
            uint16_t u16_ChargeV;
            int16_t  s16_BasePower;
            uint32_t u32_crc;
        }V3;
    }Param;

}struct_FT_Trim_t;

typedef struct 
{
    uint32_t u16_slopeA;
    uint32_t u16_slopeB;
    int32_t  s32_constantA;
    int32_t  s32_constantB;
}struct_ADC_Cal_Param_t;

/* ################################ trim Parameter Section END ################################## */
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void trim_cp_config(void);
void trim_ft_config(void);

struct_ADC_Cal_Param_t *trim_get_adc_cal_param(void);
int16_t trim_get_txpower_param(void);

void trim_get_device_uuid(uint8_t *buffer, uint8_t *length);

#endif  // __TRIM_FR1010_H__
