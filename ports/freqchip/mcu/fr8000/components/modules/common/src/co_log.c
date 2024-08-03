#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "app_config.h"
#include "os_timer.h"
#include "gatt_api.h"
#include "gap_api.h"

#include "driver_system.h"
#include "driver_uart.h"
#include "driver_uart_ex.h"
#include "co_log.h"

#if LOG_OUTPUT_SEL == LOG_OUTPUT_RTT
    #include "SEGGER_RTT.h"
    #define printf(...)         SEGGER_RTT_printf(0, __VA_ARGS__)
    #define vprintf(fmt, args)  SEGGER_RTT_vprintf(0, fmt, &args)
#elif ((LOG_OUTPUT_SEL == LOG_OUTPUT_UART0)||(LOG_OUTPUT_SEL == LOG_OUTPUT_UART1))
    #ifdef LOG_USE_SIMPLIFIED_PRINTF
        #include "co_printf.h"
        #define printf(...)         co_printf(__VA_ARGS__)
        #define vprintf(fmt, args)  print(0, fmt, args);
    #endif  // LOG_USE_SIMPLIFIED_PRINTF
#else
    #error "LOG output selection error!"
#endif

void log_printf_level(const char *level)
{
    printf(level);
#ifdef LOG_ENABLE_TIME
    printf("[%08d] ", system_get_curr_time());
#endif  // LOG_ENABLE_TIME
}

void log_printf(const char* tag,
                            const char* file_name,
                            uint32_t line,
                            const char *format, ...)
{
    va_list args;

    if(tag)
        printf("[%s] ",tag);
    
#ifdef LOG_ENABLE_FILE_LINE
    printf("%s %d: ", file_name, line);
#endif  // LOG_ENABLE_FILE_LINE
    
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void log_init(void)
{
#if LOG_OUTPUT_SEL == LOG_OUTPUT_UART0
    fputc_imp = fputc_uart0;
    _write_imp = _write_uart0;
#if (1<<LOG_UART_RX_PORT_SEL) != GPIO_PA0
    system_set_port_mux(GPIO_PORT_A, GPIO_BIT_0, PORTA0_FUNC_A0);
#endif
#if (1<<LOG_UART_TX_PORT_SEL) != GPIO_PA1
    system_set_port_mux(GPIO_PORT_A, GPIO_BIT_1, PORTA1_FUNC_A1);
#endif
    system_set_port_pull(1 << LOG_UART_RX_PORT_SEL, GPIO_PULL_UP, true);
    system_set_port_mux(LOG_UART_RX_PORT_SEL/8, LOG_UART_RX_PORT_SEL%8, 4);
    system_set_port_mux(LOG_UART_TX_PORT_SEL/8, LOG_UART_TX_PORT_SEL%8, 4);
    system_regs->clk_gate.uart0_clk_en = 1;
    system_regs->rst.uart0_rst = 0;
    uart_init(UART0, LOG_UART_BAUDRATE_CFG);
#endif
#if LOG_OUTPUT_SEL == LOG_OUTPUT_UART1
    fputc_imp = fputc_uart1;
    _write_imp = _write_uart1;
    system_set_port_pull(1 << LOG_UART_RX_PORT_SEL, GPIO_PULL_UP, true);
    system_set_port_mux(LOG_UART_RX_PORT_SEL/8, LOG_UART_RX_PORT_SEL%8, 5);
    system_set_port_mux(LOG_UART_TX_PORT_SEL/8, LOG_UART_TX_PORT_SEL%8, 5);
    system_regs->misc.tiny_uart_apb_clk_en = 1;
    system_regs->rst.uart1_rst = 0;
    uart_init(UART1, LOG_UART_BAUDRATE_CFG);
#endif
    
    /* set log output levels used in host library */
    tim_local_log_level = LOG_LEVEL_NONE;
    gap_local_log_level = LOG_LEVEL_NONE;
    sm_local_log_level = LOG_LEVEL_NONE;
    bond_m_local_log_level = LOG_LEVEL_NONE;
    gatt_local_log_level= LOG_LEVEL_NONE;
}
