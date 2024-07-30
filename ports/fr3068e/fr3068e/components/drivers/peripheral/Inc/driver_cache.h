/*
  ******************************************************************************
  * @file    driver_cache.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2022
  * @brief   Header file of cache HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_CACHE_H__
#define __DRIVER_CACHE_H__

#include "fr30xx.h"

/** @addtogroup CACHE_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

/* Enabling Register 0 */
typedef struct
{
    uint32_t ENABLE     : 1;
    uint32_t FLUSH      : 1;
    uint32_t BANK_FLUSH : 1;
    uint32_t rsv        : 29;
} REG_Enabling_t;

/* Control Register */
typedef struct
{
    uint32_t BIST_ACTIVE    : 1;
    uint32_t BIST_END       : 1;
    uint32_t BIST_OUT       : 1;
    uint32_t WR_MODE        : 2;
    uint32_t INST_POL       : 1;
    uint32_t INST_ACTIVE    : 1;
    uint32_t ADDR_RANG0_EN  : 1;
    uint32_t ADDR_RANG0_POL : 1;
    uint32_t ADDR_RANG1_EN  : 1;
    uint32_t ADDR_RANG1_POL : 1;
    uint32_t ADDR_RANG2_EN  : 1;
    uint32_t ADDR_RANG2_POL : 1;
    uint32_t ADDR_RANG3_EN  : 1;
    uint32_t ADDR_RANG3_POL : 1;
    uint32_t rsv            : 17;
} REG_Cache_Control_t;

/* Address Range 0 defination*/
typedef struct {
    uint32_t bank   :16;
    uint32_t mask   :16;
} REG_ADDR_RANGE0_t;

/* Address Range 1 defination*/
typedef struct {
    uint32_t rsv_0  :8;
    uint32_t bank   :8;
    uint32_t rsv_1  :8;
    uint32_t mask   :8;
} REG_ADDR_RANGE1_t;

/* Address Range 2 defination*/
typedef struct {
    uint32_t rsv_0  :8;
    uint32_t bank   :8;
    uint32_t rsv_1  :8;
    uint32_t mask   :8;
} REG_ADDR_RANGE2_t;

/* Address Range 3 defination*/
typedef struct {
    uint32_t rsv_0  :8;
    uint32_t bank   :8;
    uint32_t rsv_1  :8;
    uint32_t mask   :8;
} REG_ADDR_RANGE3_t;

/* -----------------------------------------------*/
/*                   CACHE Register                 */
/* -----------------------------------------------*/
typedef struct 
{
    volatile REG_Enabling_t         ENABLING;           /* Offset 0x00 */
    volatile REG_Cache_Control_t    CTRL;               /* Offset 0x04 */
    volatile uint32_t               BANK_FLUSH_ADDR;    /* Offset 0x08 */
    volatile uint32_t               BANK_FLUSH_MASK;    /* Offset 0x0C */
    volatile REG_ADDR_RANGE0_t      ADDR_RANGE0;        /* Offset 0x10 */
    volatile REG_ADDR_RANGE1_t      ADDR_RANGE1;        /* Offset 0x14 */
    volatile REG_ADDR_RANGE2_t      ADDR_RANGE2;        /* Offset 0x18 */
    volatile REG_ADDR_RANGE3_t      ADDR_RANGE3;        /* Offset 0x1C */
}struct_CACHE_t;

#define CACHE           ((struct_CACHE_t *)AHBC_CACHE_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup SPI_Initialization_Config_Section
  * @{
  */
/* ################################ Initializatio Config Section Start ################################ */

typedef enum {
    CACHE_WR_BYPASS,
    CACHE_WR_FLUSH,
    CACHE_WR_WRITE_THROUGH,
} enum_CACHE_WR_MODE_T;

typedef enum {
    CACHE_POL_NON_CACHABLE,
    CACHE_POL_CACHABLE,
} enum_CACHE_POL_T;

/* ################################ Initializatio Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

#define __CACHE_ENABLE(__CACHE__)                           (__CACHE__->ENABLING.ENABLE = 1)
#define __CACHE_DISABLE(__CACHE__)                          (__CACHE__->ENABLING.ENABLE = 0)

#define __CACHE_FLUSH(__CACHE__)                            (__CACHE__->ENABLING.FLUSH = 1)

#define __CACHE_BANK_FLUSH(__CACHE__)                       (__CACHE__->ENABLING.BANK_FLUSH = 1)
#define __CACHE_BANK_FLUSH_DONE(__CACHE__)                  (__CACHE__->ENABLING.BANK_FLUSH == 0)
#define __CACHE_BANK_FLUSH_ADDR_SET(__CACHE__, addr)        (__CACHE__->BANK_FLUSH_ADDR = addr)
#define __CACHE_BANK_FLUSH_MASK_SET(__CACHE__, mask)        (__CACHE__->BANK_FLUSH_MASK = mask)

#define __CACHE_BIST_START(__CACHE__)                       (__CACHE__->CTRL.BIST_ACTIVE = 1)
#define __CACHE_BIST_END(__CACHE__)                         (__CACHE__->CTRL.BIST_END == 1)
#define __CACHE_BIST_PASS(__CACHE__)                        (__CACHE__->CTRL.BIST_OUT == 0)

#define __CACHE_WR_MODE_SET(__CACHE__, mode)                (__CACHE__->CTRL.WR_MODE = mode)
#define __CACHE_WR_MODE_GET(__CACHE__, mode)                (__CACHE__->CTRL.WR_MODE)

#define __CACHE_ADDR_RANGEx_ENABLE(__CACHE__, x)            (__CACHE__->CTRL.ADDR_RANG##x##_EN = 1)
#define __CACHE_ADDR_RANGEx_DISABLE(__CACHE__, x)           (__CACHE__->CTRL.ADDR_RANG##x##_EN = 0)
#define __CACHE_ADDR_RANGEx_POL_SET(__CACHE__, x, __pol)    (__CACHE__->CTRL.ADDR_RANG##x##_POL = __pol)

#define __CACHE_ADDR_RANGEx_BANK_SET(__CACHE__, x, __bank)  (__CACHE__->ADDR_RANGE##x.bank = (__bank))
#define __CACHE_ADDR_RANGEx_MASK_SET(__CACHE__, x, __mask)  (__CACHE__->ADDR_RANGE##x.mask = (__mask))

#endif  // __DRIVER_CACHE_H__

