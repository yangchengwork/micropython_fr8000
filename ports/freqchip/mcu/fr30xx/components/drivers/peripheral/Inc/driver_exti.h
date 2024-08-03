#ifndef _EXTI_H
#define _EXTI_H

#include <stdint.h>
#include "plf.h"
#include "driver_iomux.h"

enum ext_int_type_t
{
    EXT_INT_TYPE_LOW,
    EXT_INT_TYPE_HIGH,
    EXT_INT_TYPE_POS,
    EXT_INT_TYPE_NEG,
};


struct exti_ctrl_t  //EXTINTCTL. 0x14
{
    uint32_t pa_exti_en: 8;       //exti intr connect to gpio PA ctrl
    uint32_t pb_exti_en: 8;       //exti intr connect to gpio PB ctrl
    uint32_t resv: 16;
};
struct exti_status_t //EXTINTSTS    0x18
{
    uint32_t pa_exti_sts: 8;       //PA exti intr status
    uint32_t pb_exti_sts: 8;       //PB exti intr status
    uint32_t resv: 16;
};
struct exti_type_t  //EXTINTTYPE offset@0x1C
{
    uint32_t pa0_exti_type: 2;       //external intr source sel.
    uint32_t pa1_exti_type: 2;       //external intr source sel.
    uint32_t pa2_exti_type: 2;       //external intr source sel.
    uint32_t pa3_exti_type: 2;       //external intr source sel.
    uint32_t pa4_exti_type: 2;       //external intr source sel.
    uint32_t pa5_exti_type: 2;       //external intr source sel.
    uint32_t pa6_exti_type: 2;       //external intr source sel.
    uint32_t pa7_exti_type: 2;       //external intr source sel.
    uint32_t pb0_exti_type: 2;       //external intr source sel.
    uint32_t pb1_exti_type: 2;       //external intr source sel.
    uint32_t pb2_exti_type: 2;       //external intr source sel.
    uint32_t pb3_exti_type: 2;       //external intr source sel.
    uint32_t pb4_exti_type: 2;       //external intr source sel.
    uint32_t pb5_exti_type: 2;       //external intr source sel.
    uint32_t pb6_exti_type: 2;       //external intr source sel.
    uint32_t pb7_exti_type: 2;       //external intr source sel.
};
struct exti_cnt_t   //EXTINTCNT00 offset:0x20
{
    uint32_t pre_cnt: 12; //Precaler Value: set the external interrupt source 0 CNT_CLK: CNT_CLK=PCLK/(1+ Precaler Value)
    uint32_t des_cnt: 4;    //Counter Value. (only useful for level trigger mode)
    uint32_t resv: 16;
};


struct exti_reg_t
{
    struct exti_ctrl_t exti_ctrl;   //EXTINTCTL. 0x14
    struct exti_status_t exti_sts;  //EXTINTSTS    0x18
    struct exti_type_t exti_type;   //EXTINTTYPE offset@0x1C
    struct exti_cnt_t exti_cnt[16];     //EXTINTCNT00~EXTINTCNT15 offset:0x20~0x
};

extern volatile struct exti_reg_t *extiAB_regs;
extern volatile struct exti_reg_t *extiCD_regs;
extern volatile struct exti_reg_t *extiEF_regs;
extern volatile struct exti_reg_t *extiGH_regs;


void exti_enable(enum system_port_t port,enum system_port_bit_t bit);
void exti_disable(enum system_port_t port,enum system_port_bit_t bit);
uint8_t exti_get_src(enum system_port_t port);
void exti_intr_clr(enum system_port_t port,uint8_t bits);
void exti_set_type(enum system_port_t port,enum system_port_bit_t bit, enum ext_int_type_t type);
void exti_set_debounce_cnt(enum system_port_t port,enum system_port_bit_t bit, uint32_t clk, uint8_t cnt);



#endif //_EXTI_H

