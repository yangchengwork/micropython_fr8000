/*
  ******************************************************************************
  * @file    driver_efuse.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   eFuse module driver.
  *          This file provides firmware functions to manage the eFuse.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "fr30xx.h"

/************************************************************************************
 * @fn      eFuse_siso_read
 *
 * @brief   read eFuse data.
 *
 * @param   fp_Data: read data buffer.
 */
void eFuse_siso_read(uint32_t *fp_Data)
{
    EFUSE_SISO->eFuse_Timing = 0x2401 & 0x3FFF;
    /* config read mode */
    EFUSE_SISO->eFuse_Ctrl = EFUSE_SISO_READ_MODE;
    /* wait config done */
    while(!(EFUSE_SISO->eFuse_Ctrl & EFUSE_SISO_CHECK_DONE));
    EFUSE_SISO->eFuse_Ctrl |= EFUSE_SISO_CHECK_DONE;

    /* read data */
    fp_Data[0] = EFUSE_SISO->eFuse_Data0;
    fp_Data[1] = EFUSE_SISO->eFuse_Data1;
    fp_Data[2] = EFUSE_SISO->eFuse_Data2;
}

/************************************************************************************
 * @fn      eFuse_siso_write
 *
 * @brief   write eFuse data.
 *
 * @param   fp_Data: write data buffer.
 */
void eFuse_siso_write(uint32_t *fp_Data)
{
    EFUSE_SISO->eFuse_Timing = 0x2460 & 0x3FFF;  
    /* write data */
    EFUSE_SISO->eFuse_Data0 = fp_Data[0];
    EFUSE_SISO->eFuse_Data1 = fp_Data[1];
    EFUSE_SISO->eFuse_Data2 = fp_Data[2];
    
    /* config write mode */
    EFUSE_SISO->eFuse_Ctrl = EFUSE_SISO_WRITE_MODE;
    /* wait config done */
    while(!(EFUSE_SISO->eFuse_Ctrl & EFUSE_SISO_CHECK_DONE));
    EFUSE_SISO->eFuse_Ctrl |= EFUSE_SISO_CHECK_DONE;
}

static void Efuse_delay(volatile uint32_t fu32_Delay)
{
    while(fu32_Delay--);
}

/************************************************************************************
 * @fn      eFuse_pipo_read
 *
 * @brief   read eFuse data.
 *
 * @param   fu8_Addr: efuse address, unit byte, range 0x00 ~ 0xFF;
 * @param   fp_Data: read data buffer.
 */
void eFuse_pipo_read(struct_eFuse_PIPO_t *hpipo, uint8_t fu8_Addr, uint8_t *fp_Data)
{ 
    hpipo->eFuse_Addr = fu8_Addr;

    /* config read mode */
    hpipo->eFuse_Ctrl = EFUSE_PIPO_GO | EFUSE_PIPO_READ_MODE;
    /* wait config done */
    while(!(hpipo->eFuse_Ctrl & EFUSE_PIPO_CHECK_DONE));

    fp_Data[0] = hpipo->eFuse_RData;
    hpipo->eFuse_Ctrl &= ~EFUSE_PIPO_READ_MODE;
}

/************************************************************************************
 * @fn      eFuse_pipo_write
 *
 * @brief   write eFuse data.
 *
 * @param   fu8_Addr: efuse address, unit byte, range 0x00 ~ 0xFF;
 * @param   fp_Data: write data value.
 */
void eFuse_pipo_write(struct_eFuse_PIPO_t *hpipo, uint8_t fu8_Addr, uint8_t fu8_Data)
{ 
    hpipo->eFuse_Ctrl = EFUSE_PIPO_AVDDEN;

    hpipo->eFuse_Addr  = fu8_Addr;
    hpipo->eFuse_WData = fu8_Data;

    /* config write mode */
    Efuse_delay(156);
    hpipo->eFuse_Ctrl |= EFUSE_PIPO_WRITE_MODE | EFUSE_PIPO_GO;    

    /* wait config done */
    while(!(hpipo->eFuse_Ctrl & EFUSE_PIPO_CHECK_DONE));

    hpipo->eFuse_Ctrl &= ~EFUSE_PIPO_WRITE_MODE;
    Efuse_delay(100);
    hpipo->eFuse_Ctrl &= ~EFUSE_PIPO_AVDDEN;
}
