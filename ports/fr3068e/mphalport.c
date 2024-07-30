#include <unistd.h>
#include "py/mpconfig.h"

#include "driver_uart.h"

extern uint8_t fr8000_read_char(void);
// Receive single character, blocking until one is available.
int mp_hal_stdin_rx_chr(void) {
    unsigned char c = 0;
    // int r = read(STDIN_FILENO, &c, 1);
    // (void)r;
    // c = fr8000_read_char();
    return c;
}

// Send the string of given length.
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    // int r = write(STDOUT_FILENO, str, len);
    // (void)r;
    /*
    while(len--) {
        uart_putc_noint_no_wait(UART1, *str++);
    }
    */
    // uart_write(UART1, (uint8_t*)str, len);
    UART_HandleTypeDef Uart_Handler;
    Uart_Handler.UARTx = UART3;
    uart_transmit(&Uart_Handler, (uint8_t *)str, len);
    while(!(Uart_Handler.UARTx->USR.TFE));
    // return len;
}
