#ifndef _DRIVER_RTC_H_
#define _DRIVER_RTC_H_
#include <stdint.h>

#define CO_BIT(pos) (1UL<<(pos))

#define PMU_RTC_CRL      0x37
#define PMU_UPDATE_EN    CO_BIT(0)
#define PMU_VAL_RD       CO_BIT(1)
#define ALAMA_CLR        CO_BIT(2)
#define ALAMB_CLR        CO_BIT(3)
#define ALAMA_EN         CO_BIT(4)
#define ALAMB_EN         CO_BIT(5)

#define PMU_REG_RST_CTRL 0x02

#define PMU_REG_CLK_CTRL 0x01



enum rtc_idx_t
{
    RTC_A,
    RTC_B,
};

 void rtc_test(void);
 void rtc_stop(void);
void rtc_isr_ram(uint8_t rtc_idx);

#endif
