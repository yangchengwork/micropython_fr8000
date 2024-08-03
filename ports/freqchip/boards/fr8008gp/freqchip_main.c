/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "gap_api.h"
#include "gatt_api.h"
#include "ble_stack.h"

#include "app_config.h"

#include "co_printf.h"
#include "co_log.h"

#include "driver_system.h"
#include "driver_pmu.h"
#include "driver_uart.h"
#include "driver_uart_ex.h"
#include "driver_gpio.h"

#include "plf.h"

// #include "uart_demo.h"
#if SEGGER_RTT_ENABLED
#include "SEGGER_RTT.h"
#endif

#undef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL        (LOG_LEVEL_INFO)
static const char *app_tag = "main";

#define SYSTEM_STACK_SIZE           0x1800

__attribute__((section("stack_section"))) static uint32_t system_stack[SYSTEM_STACK_SIZE/sizeof(uint32_t)];

extern int py_main(int argc, char **argv);

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

extern void uart_write(uint32_t uart_addr, const uint8_t *bufptr, uint32_t size);
extern void uart_putc_noint(uint32_t uart_addr, uint8_t c);

#define FREQCHIP_UART_BUF_SIZE      256
typedef struct freqchip_8000_uart_buf_status {
    uint8_t     buf[FREQCHIP_UART_BUF_SIZE];
    uint8_t     r_index;
    uint8_t     s_index;
} fr8000_uart_t;

static GPIO_InitTypeDef    GPIO_Handle;
static UART_HandleTypeDef  Uart0_handle;

static fr8000_uart_t uart_buf = {0};

void uart_demo(void)
{
    __SYSTEM_UART0_CLK_ENABLE();


    system_set_port_pull(GPIO_PA0,GPIO_PULL_UP,true);
    /* set PA0 and PA1 for REPL command interface */
    system_set_port_mux(GPIO_PORT_A, GPIO_BIT_0, PORTA0_FUNC_UART0_RXD);
    system_set_port_mux(GPIO_PORT_A, GPIO_BIT_1, PORTA1_FUNC_UART0_TXD);

    /* init uart0 */   
    Uart0_handle.UARTx = Uart0;
    Uart0_handle.Init.BaudRate   = 115200;
    Uart0_handle.Init.DataLength = UART_DATA_LENGTH_8BIT;
    Uart0_handle.Init.StopBits   = UART_STOPBITS_1;
    Uart0_handle.Init.Parity     = UART_PARITY_NONE;
    Uart0_handle.Init.FIFO_Mode  = UART_FIFO_ENABLE;
    
    uart_init_ex(&Uart0_handle);
    
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_SetPriority(UART0_IRQn, 0);
    __UART_INT_LINE_STATUS_ENABLE(Uart0_handle.UARTx);
    __UART_INT_RX_ENABLE(Uart0_handle.UARTx);
    // __enable_irq();
}

void proj_init(void)
{
#if SEGGER_RTT_ENABLED
    SEGGER_RTT_Init();
#else
#endif

    LOG_INFO(app_tag, "proj_init\r\n");
    LOG_INFO(app_tag, "lp clk=%d\r\n", pmu_get_rc_clk(false));

    /* system sleep is allowed */
    system_sleep_disable();
	
	GLOBAL_INT_START();

    uart_demo();
    LOG_INFO(app_tag, "micro python done\r\n");
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

    py_main(0, NULL);
    
    while (1) {
        // uart_putc_noint(UART1_BASE, '*');
    }
}

uint8_t freqchip_log_read_char(void)
{
    uint8_t ret = 0;
    if (uart_buf.r_index != uart_buf.s_index) {
        ret = uart_buf.buf[uart_buf.s_index];
        uart_buf.s_index++;
        // uart_putc_noint(UART0_BASE, ret);
    }
    return ret;
}

void freqchip_log_write(const char *str, uint8_t len)
{
    uart_write(UART0, (uint8_t*)str, len);
}

void uart0_isr(void)
{
    volatile struct_UART_t * const uart_reg_ram = (volatile struct_UART_t *)UART0_BASE;
    uint32_t isr_id = uart_reg_ram->FCR_IID.IID;
    uint8_t c;

    if ((isr_id&0x0f) == 0x04 || (isr_id&0x0f) == 0x0c) {
        c = (uint8_t)uart_reg_ram->DATA_DLL.DATA;
        // 为了省事，没有做溢出处理
        uart_buf.buf[uart_buf.r_index++] = c;
    } else if ((isr_id&0x0f) == 0x06) {
        volatile uint32_t tmp = uart_reg_ram->LSR.LSR_DWORD;
    }
}

int _read (int fd, char *pBuffer, int size)
{
//    co_printf("\nr\n");
}

int _getpid (int id)
{

}

int _close (int id)
{

}

int _kill (int pid, int sig)
{

}

int _fstat (int fildes,
        struct stat *st)
{

}

int _isatty (int file)
{
  // errno = ENOSYS;
  return 0;
}

int _lseek (int   file,
        int   ptr,
        int   dir)
{
  // errno = ENOSYS;
  return -1;
}
