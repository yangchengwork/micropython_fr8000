/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdio.h>
#include <string.h>

// #include "gap_api.h"
// #include "gatt_api.h"
// #include "ble_stack.h"

#include "app_config.h"

#include "co_printf.h"
#include "co_log.h"

#include "driver_system.h"
#include "driver_pmu.h"
#include "driver_uart.h"
#include "driver_gpio.h"

#include "plf.h"

// #include "uart_demo.h"

#undef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL        (LOG_LEVEL_INFO)
const char *app_tag = "uart";

#define SYSTEM_STACK_SIZE           0x800

__attribute__((section("stack_section"))) static uint32_t system_stack[SYSTEM_STACK_SIZE/sizeof(uint32_t)];

extern int py_main(void);

const struct jump_table_version_t _jump_table_version __attribute__((section("jump_table_3"))) = 
{
    .stack_top_address = &system_stack[SYSTEM_STACK_SIZE/sizeof(uint32_t)],
    .firmware_version = 0x00000000,
};

const struct jump_table_image_t _jump_table_image __attribute__((section("jump_table_1"))) =
{
    .image_type = IMAGE_TYPE_APP,
    .image_size = 0x30000,
};

void proj_init(void)
{
    LOG_INFO(app_tag, "proj_init\r\n");
    LOG_INFO(app_tag, "lp clk=%d\r\n", pmu_get_rc_clk(false));

    /* system sleep is allowed */
    system_sleep_disable();
	
	GLOBAL_INT_START();
}

void user_main(void)
{
    /* initialize log module */
    log_init();

    /* initialize PMU module at the beginning of this program */
    pmu_sub_init();

    /* set system clock */
    system_set_clock(SYSTEM_CLOCK_SEL);

    proj_init();

    /* demo select: UART_TRANSMIT_RECEIVE */
	/* demo select: UART_TRANSMIT_RECEIVE_IT  */
    /* demo select: UART_TRANSMIT_RECEIVE_DMA  */
    // uart_demo(UART_TRANSMIT_RECEIVE);
    py_main();
    
    while (1) {}
}

uint8_t fr8000_read_char(void)
{
    uint8_t ret = 0;
    return ret;
}


