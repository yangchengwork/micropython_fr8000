/*
  ******************************************************************************
  * @file    driver_efuse.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of eFuse HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_EFUSE_H__
#define __DRIVER_EFUSE_H__

#include <stdint.h>
#include <stdbool.h>

#include "driver_system.h"
#include "plf.h"

/** @addtogroup eFuse_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Control Register */
/*  bit0: GO        */
/*  bit1: DONE      */
/*  bit2: READ      */
/*  bit3: WRITE     */

#define EFUSE_READ_MODE     (0x05)
#define EFUSE_WRITE_MODE    (0x09)
#define EFUSE_CHECK_DONE    (0x02)

/* ------------------------------------------------*/
/*                   eFuse Register                 */
/* ------------------------------------------------*/
typedef struct 
{
    volatile uint32_t        eFuse_Ctrl;      /* Offset 0x00 */
    volatile uint32_t        eFuse_Data0;     /* Offset 0x04 */
    volatile uint32_t        eFuse_Data1;     /* Offset 0x08 */
    volatile uint32_t        eFuse_Data2;     /* Offset 0x0C */
    volatile uint32_t        eFuse_Data3;     /* Offset 0x10 */
    volatile uint32_t        eFuse_Length;    /* Offset 0x14 */
}struct_eFuse_t;

#define EFUSE    ((struct_eFuse_t *)EFUSE_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup eFuse_Parameter_Section
  * @{
  */
/* ################################ eFuse Parameter Section Start ################################ */

/* ------------------------------------------------*/
/*                 eFuse Parameter                 */
/* ------------------------------------------------*/
typedef __PACKED_STRUCT 
{
    /* --------- vendor-specific --------- */
    volatile uint32_t BBG_CODE    : 5;
    volatile uint32_t IOLDO_CODE  : 3;
    volatile uint32_t SYSLDO_CODE : 3;
    volatile uint32_t BFB_CODE    : 3;
    volatile uint32_t DLDO_CODE   : 3;
    volatile uint32_t PKVDD_CODE  : 4;
    volatile uint32_t SBG_CODE    : 4;
    volatile uint32_t LOT_ID      : 24;
    volatile uint32_t WaferID     : 5;
    volatile uint32_t XY          : 16;
    volatile uint32_t Year        : 5;
    volatile uint32_t Week        : 6;
    volatile uint32_t IOLDO_DIFF  : 9;
    volatile uint32_t Version     : 2;
    volatile uint32_t rsv_0       : 4;
    /* --------- vendor-specific END--------- */

    volatile uint32_t rsv_1       : 32;
}struct_eFuseParam_t;

/* ---------------------------------------------*/
/*                 FT Parameter                 */
/* ---------------------------------------------*/
typedef struct 
{
	uint16_t u16_version;
	
    uint16_t u16_slopeA;
    
	union {
        struct {
            struct
            {
                uint8_t Modem_VCO_GAU;
                uint8_t Modem_MODDAC;
                uint8_t TxPowerLow;     // RF_PA is from RF_LDO
                uint8_t TxPowerHigh;    // RF_PA is from 3.3v IOLDO
                char FrequencyShift;
            } TxChannelParam[40];
            
            uint16_t Rate_1M[40];   // sensitivity
            uint16_t Rate_2M[40];   // sensitivity

            uint16_t u16_ChargeV;

            uint16_t u16_VDDIO;
            
            uint16_t u16_slopeB;
            int16_t  s16_constantA;
            int16_t  s16_constantB;
        } V6;
        struct {
            struct
            {
                uint8_t Modem_VCO_GAU;
                uint8_t Modem_MODDAC;
                uint8_t TxPowerLow;     // RF_PA is from RF_LDO
                uint8_t TxPowerHigh;    // RF_PA is from 3.3v IOLDO
                uint8_t TxPowerHigh2;   // RF_PA is from 2.0v IOLDO
                char FrequencyShift;
            } TxChannelParam[10];
            
            uint16_t Rate_1M[40];   // sensitivity
            uint16_t Rate_2M[40];   // sensitivity

            uint16_t u16_ChargeV;

            uint16_t u16_VDDIO;
            
            uint16_t u16_slopeB;
            int16_t  s16_constantA;
            int16_t  s16_constantB;
        } V7;
    } Param;
}struct_FT_Param_t;

typedef struct 
{
    uint32_t u16_slopeA;
    uint32_t u16_slopeB;
    int32_t  s16_constantA;
    int32_t  s16_constantB;
}struct_ADC_Cal_Param_t;

/* ################################ eFuse Parameter Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/* eFuse_read */
void eFuse_read(uint32_t *fp_Data);

#endif
