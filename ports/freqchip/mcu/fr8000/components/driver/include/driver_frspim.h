#ifndef _DRIVER_FRSPIM_H
#define _DRIVER_FRSPIM_H

#include <stdint.h>

struct frspim_ctrl_t{
    uint32_t go:1; /* Write:0--no action,1--transmit start(hw clear)*/
    uint32_t done:1; /*Read:0--busy,1--idle*/
    uint32_t sel:1; /*0: pmu pk spi access; 1: pmu pd spi access*/
    uint32_t resv0:1;
    uint32_t len:3;     /*TX/RX byte(1:4)*/
    uint32_t rsv1:1;
    uint32_t op:1;      /*1--write,0--read*/
    uint32_t rsv2:3;
    uint32_t ratio:2;   /*sclk = p_clk/(1+ratio)*2*/
    uint32_t rsv3:2;
    uint32_t addr:8;
    uint32_t rsv4:8;
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

#define FR_SPI_PMU_PD_CHAN          1
#define FR_SPI_PMU_PK_CHAN          0

void frspim_init(uint8_t ratio);
uint32_t frspim_rd (uint8_t chan_num, uint8_t addr, uint8_t len);
void frspim_wr (uint8_t chan_num, uint8_t addr, uint8_t len, uint32_t val);

#endif  // _DRIVER_FRSPIM_H

