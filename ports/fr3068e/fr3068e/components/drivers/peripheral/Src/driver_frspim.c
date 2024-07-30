/**
****************************************************************************************
*
* @file frspim.c
*
* @brief freqchip spi master initialization and specific functions
*
* Copyright (C) RivieraWaves 2009-2013
*
*
****************************************************************************************
*/

/**
****************************************************************************************
* @addtogroup RF_FR
* @ingroup RF
* @brief FREQCHIP Radio Driver
*
* This is the driver block for FR radio
* @{
****************************************************************************************
*/

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "fr30xx.h"

/*
 * DEFINES
 ****************************************************************************************
 */

volatile struct frspim_reg_t * const frspim_reg = (volatile struct frspim_reg_t * )FRSPIM_BASE;

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */


void frspim_init(uint8_t ratio)
{
    frspim_reg->ctrl.ratio = ratio;
}


/*****************************************************************************************
 * @brief SPI access
 ****************************************************************************************
 */


/*****************************************************************************************
 * @brief Bluejay specific read access
 *
 * @param[in] addr    register address
 *
 * @return uint32_t value
 ****************************************************************************************
 */
__RAM_CODE uint32_t frspim_rd (uint8_t chan_num, uint8_t addr, uint8_t len)
{
    uint32_t data;
    
    GLOBAL_INT_DISABLE();
    frspim_reg->ctrl.len = len;
    frspim_reg->ctrl.sel = chan_num;
    frspim_reg->ctrl.op = 0;
    frspim_reg->ctrl.addr = addr;
    
    frspim_reg->ctrl.go = 1;
    while(!frspim_reg->ctrl.done);
    
    data = (*((uint32_t *)(&frspim_reg->rdat)));
    GLOBAL_INT_RESTORE();
    
    return data;
}

/*****************************************************************************************
 * @brief Bluejay specific read access for ram
 *
 * @param[in] addr    register address
 *
 * @return uint32_t value
 ****************************************************************************************
 */
__RAM_CODE uint32_t frspim_rd_ram (uint8_t chan_num, uint8_t addr, uint8_t len)
{
    uint32_t data;
   
    GLOBAL_INT_DISABLE();
    
    *(volatile uint32_t *)(&frspim_reg->ctrl) = 0x00001011 | (addr<<16);   
    while(!frspim_reg->ctrl.done);
    
    data = *(volatile uint32_t *)(&frspim_reg->rdat);
    GLOBAL_INT_RESTORE();
    
    return data;
}
/*****************************************************************************************
 * @brief Freqchip specific write access
 *
 * @param[in] addr    register address
 * @param[in] value   value to write
 *
 * @return uint32_t value
 ****************************************************************************************
 */
__RAM_CODE void frspim_wr (uint8_t chan_num, uint8_t addr, uint8_t len, uint32_t val)
{
    GLOBAL_INT_DISABLE();
    frspim_reg->ctrl.len = len;
    frspim_reg->ctrl.sel = chan_num;
    frspim_reg->ctrl.op = 1;
    frspim_reg->ctrl.addr = addr;
    (*((uint32_t *)(&frspim_reg->wdat))) = val;
    
    frspim_reg->ctrl.go = 1;
    while(!frspim_reg->ctrl.done);
    GLOBAL_INT_RESTORE();
}

/*****************************************************************************************
 * @brief Freqchip specific write access for ram
 *
 * @param[in] addr    register address
 * @param[in] value   value to write
 *
 * @return uint32_t value
 ****************************************************************************************
 */
__RAM_CODE void frspim_wr_ram (uint8_t chan_num, uint8_t addr, uint8_t len, uint32_t val)
{
    GLOBAL_INT_DISABLE();
    
    *(volatile uint32_t *)(&frspim_reg->wdat) = val;
    *(volatile uint32_t *)(&frspim_reg->ctrl) = 0x00001111 | (addr<<16);;
    
    while(!frspim_reg->ctrl.done);
    GLOBAL_INT_RESTORE();
}


