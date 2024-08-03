/**
 ****************************************************************************************
 *
 * @file frspim.h
 *
 * @brief Common header file for all radios.
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 *
 ****************************************************************************************
 */

#ifndef FRSPIM_H_
#define FRSPIM_H_

#include <stdint.h>

struct frspim_ctrl_t{
    uint32_t go:1;      /*Write:0--no action,1--transmit start(hw clear)*/
    uint32_t done:1;    /*Read:0--idle,1--busy*/
    uint32_t sel:2;     /*channel select*/
    uint32_t len:3;     /*TX/RX byte(1:4)*/
    uint32_t rsv0:1;
    uint32_t op:1;      /*1--write,0--read*/
    uint32_t rsv1:3;
    uint32_t ratio:2;   /*sclk = p_clk/(1+ratio)*2*/
    uint32_t rsv2:2;
    uint32_t addr:8;
    uint32_t rsv3:8;
};

struct frspim_wdat_t{
    uint32_t wbyte0:8;
    uint32_t wbyte1:8;
    uint32_t wbyte2:8;
    uint32_t wbyte3:8;
};

struct frspim_rdat_t{
    uint32_t rbyte0:8;
    uint32_t rbyte1:8;
    uint32_t rbyte2:8;
    uint32_t rbyte3:8;
};

struct frspim_reg_t{
    struct frspim_ctrl_t ctrl;
    struct frspim_wdat_t wdat;
    struct frspim_rdat_t rdat;
};

#define FR_SPI_CODEC_CHAN           1
#define FR_SPI_PMU_CHAN             0

#define ool_write(addr, data)       frspim_wr(FR_SPI_PMU_CHAN,(addr),1, (data))
#define ool_read(addr)              (uint8_t)frspim_rd(FR_SPI_PMU_CHAN,(addr),1)

#define ool_write16(addr,data)      frspim_wr(FR_SPI_PMU_CHAN,(addr),2, (data))
#define ool_read16(addr)            (uint16_t)frspim_rd(FR_SPI_PMU_CHAN,(addr),2)

#define ool_write32(addr,data)      frspim_wr(FR_SPI_PMU_CHAN,(addr),4, (data))
#define ool_read32(addr)            (uint32_t)frspim_rd(FR_SPI_PMU_CHAN,(addr),4)

void frspim_init(uint8_t ratio);
uint32_t frspim_rd (uint8_t chan_num, uint8_t addr, uint8_t len);
void frspim_wr (uint8_t chan_num, uint8_t addr, uint8_t len, uint32_t val);

uint32_t frspim_rd_ram (uint8_t chan_num, uint8_t addr, uint8_t len);
void frspim_wr_ram (uint8_t chan_num, uint8_t addr, uint8_t len, uint32_t val);
#endif

