#include <unistd.h>
#include "py/mpconfig.h"

extern uint8_t freqchip_log_read_char(void);
extern void freqchip_log_write(const char *str, uint8_t len);

// Receive single character, blocking until one is available.
int mp_hal_stdin_rx_chr(void) {
    unsigned char c = 0;
    c = freqchip_log_read_char();
    return c;
}

// Send the string of given length.
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    freqchip_log_write(str, len);
}
