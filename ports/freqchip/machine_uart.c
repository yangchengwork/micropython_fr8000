#include "py/obj.h"

#include "py/mphal.h"
// #include "co_log.h"
// #include "modmachine.h"
#include "driver_uart_ex.h"

#undef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL        (LOG_LEVEL_INFO)
static const char *app_tag = "uart";

#define MICROPY_PY_MACHINE_UART_CLASS_CONSTANTS 

typedef struct _machine_uart_obj_t {
    mp_obj_base_t base;
    // USART_TypeDef *uartx;
    // pyb_uart_t uart_id : 8;
    uint8_t uart_id : 4;
    bool is_static : 1;
    bool is_enabled : 1;
    bool attached_to_repl;              // whether the UART is attached to REPL
    byte char_width;                    // 0 for 7,8 bit chars, 1 for 9 bit chars
    uint16_t char_mask;                 // 0x7f for 7 bit, 0xff for 8 bit, 0x1ff for 9 bit
    uint16_t timeout;                   // timeout waiting for first char
    uint16_t timeout_char;              // timeout waiting between chars
    uint16_t read_buf_len;              // len in chars; buf can hold len-1 chars
    volatile uint16_t read_buf_head;    // indexes first empty slot
    uint16_t read_buf_tail;             // indexes first full slot (not full if equals head)
    byte *read_buf;                     // byte or uint16_t, depending on char size
    uint16_t mp_irq_trigger;            // user IRQ trigger mask
    uint16_t mp_irq_flags;              // user IRQ active IRQ flags
    // mp_irq_obj_t *mp_irq_obj;           // user IRQ object
} machine_uart_obj_t;



STATIC void mp_machine_uart_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    // LOG_INFO(app_tag, "UART(%d)\r\n", ((machine_uart_obj_t*)self_in)->uart_id);
    mp_printf(print, "UART(1)");
}

// 将来要提取到 uart.c中
#define UART_HWCONTROL_NONE                  0x00000000U
#define UART_WORDLENGTH_8B                  0x00000000U
#define UART_WORDLENGTH_9B                  0x00000001U

// assumes Init parameters have been set up correctly
bool uart_init_obj(machine_uart_obj_t *uart_obj,
    uint32_t baudrate, uint32_t bits, uint32_t parity, uint32_t stop, uint32_t flow) {
    return true;
}

void uart_attach_to_repl(machine_uart_obj_t *self, bool attached) {
    self->attached_to_repl = attached;
}

void uart_set_rxbuf(machine_uart_obj_t *self, size_t len, void *buf) {
}

uint32_t uart_get_baudrate(machine_uart_obj_t *self) {
    return 115200;
}

bool uart_exists(int uart_id) {
    if (uart_id < 0 || uart_id > 1) {
        return false;
    }
    return true;
}

MP_REGISTER_ROOT_POINTER(struct _machine_uart_obj_t *machine_uart_obj_all[2]);

// ---------------------------------------------


STATIC void mp_machine_uart_init_helper(
    machine_uart_obj_t *self, 
    size_t n_args, 
    const mp_obj_t *pos_args, 
    mp_map_t *kw_args) {
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_baudrate, MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 115200} },
        { MP_QSTR_bits, MP_ARG_INT, {.u_int = 8} },
        { MP_QSTR_parity, MP_ARG_OBJ, {.u_rom_obj = MP_ROM_NONE} },
        { MP_QSTR_stop, MP_ARG_INT, {.u_int = 1} },
        { MP_QSTR_flow, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = UART_HWCONTROL_NONE} },
        { MP_QSTR_timeout, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_timeout_char, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_rxbuf, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = -1} },
        { MP_QSTR_read_buf_len, MP_ARG_KW_ONLY | MP_ARG_INT, {.u_int = 64} }, // legacy
    };

    // parse args
    struct {
        mp_arg_val_t baudrate, bits, parity, stop, flow, timeout, timeout_char, rxbuf, read_buf_len;
    } args;

    mp_arg_parse_all(n_args, pos_args, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, (mp_arg_val_t *)&args);

    // baudrate
    uint32_t baudrate = args.baudrate.u_int;

    // parity
    uint32_t bits = args.bits.u_int;
    uint32_t parity;
    if (args.parity.u_obj == mp_const_none) {
        parity = UART_PARITY_NONE;
    } else {
        mp_int_t p = mp_obj_get_int(args.parity.u_obj);
        parity = (p & 1) ? UART_PARITY_ODD : UART_PARITY_EVEN;
        bits += 1; // STs convention has bits including parity
    }

    // LOG_INFO(app_tag, "%s:%d %d,%d,%d,%d\r\n", __func__, __LINE__, args.baudrate.u_int, 
    //     args.bits, args.stop, args.flow);

    // number of bits
    if (bits == 8) {
        bits = UART_WORDLENGTH_8B;
    } else if (bits == 9) {
        bits = UART_WORDLENGTH_9B;
    #ifdef UART_WORDLENGTH_7B
    } else if (bits == 7) {
        bits = UART_WORDLENGTH_7B;
    #endif
    } else {
        mp_raise_ValueError(MP_ERROR_TEXT("unsupported combination of bits and parity"));
    }

    // stop bits
    uint32_t stop;
    switch (args.stop.u_int) {
        case 1:
            stop = UART_STOPBITS_1;
            break;
        default:
            stop = UART_STOPBITS_2;
            break;
    }

    // flow control
    uint32_t flow = args.flow.u_int;

    // Save attach_to_repl setting because uart_init will disable it.
    bool attach_to_repl = self->attached_to_repl;

    // init UART (if it fails, it's because the port doesn't exist)
    if (!uart_init_obj(self, baudrate, bits, parity, stop, flow)) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("UART(%d) doesn't exist"), self->uart_id);
    }

    // Restore attach_to_repl setting so UART still works if attached to dupterm.
    uart_attach_to_repl(self, attach_to_repl);

    // set timeout
    self->timeout = args.timeout.u_int;

    // set timeout_char
    // make sure it is at least as long as a whole character (13 bits to be safe)
    // minimum value is 2ms because sys-tick has a resolution of only 1ms
    self->timeout_char = args.timeout_char.u_int;
    uint32_t min_timeout_char = 13000 / baudrate + 2;
    if (self->timeout_char < min_timeout_char) {
        self->timeout_char = min_timeout_char;
    }

    if (self->is_static) {
        // Static UARTs have fixed memory for the rxbuf and can't be reconfigured.
        if (args.rxbuf.u_int >= 0) {
            mp_raise_ValueError(MP_ERROR_TEXT("UART is static and rxbuf can't be changed"));
        }
        uart_set_rxbuf(self, self->read_buf_len, self->read_buf);
    } else {
        // setup the read buffer
        m_del(byte, self->read_buf, self->read_buf_len << self->char_width);
        if (args.rxbuf.u_int >= 0) {
            // rxbuf overrides legacy read_buf_len
            args.read_buf_len.u_int = args.rxbuf.u_int;
        }
        if (args.read_buf_len.u_int <= 0) {
            // no read buffer
            uart_set_rxbuf(self, 0, NULL);
        } else {
            // read buffer using interrupts
            size_t len = args.read_buf_len.u_int + 1; // +1 to adjust for usable length of buffer
            uint8_t *buf = m_new(byte, len << self->char_width);
            uart_set_rxbuf(self, len, buf);
        }
    }

    // compute actual baudrate that was configured
    uint32_t actual_baudrate = uart_get_baudrate(self);

    // check we could set the baudrate within 5%
    uint32_t baudrate_diff;
    if (actual_baudrate > baudrate) {
        baudrate_diff = actual_baudrate - baudrate;
    } else {
        baudrate_diff = baudrate - actual_baudrate;
    }

    if (20 * baudrate_diff > actual_baudrate) {
        mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("set baudrate %d is not within 5%% of desired value"), actual_baudrate);
    }
}

// UART(id, baudrate)
//
// Initialise the UART bus with the given parameters:
//   - `id`is bus id.
//   - `baudrate` is the clock rate.
STATIC mp_obj_t mp_machine_uart_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    // check arguments
    mp_arg_check_num(n_args, n_kw, 1, MP_OBJ_FUN_ARGS_MAX, true);

    int uart_id = 0;
    if (mp_obj_is_str(all_args[0])) {
        // LOG_INFO(app_tag, "%s,str=%s\r\n", __func__, all_args[0]);
        if (0) {
        } else {
            mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("UART(%s) doesn't exist"), all_args[0]);
        }
    } else {
        uart_id = mp_obj_get_int(all_args[0]);
        // LOG_INFO(app_tag, "%s,int=%d\r\n", __func__, uart_id);
        if (!uart_exists(uart_id)) { // 现在mp_raise_msg_varg 无法打印，会复位
            mp_raise_msg_varg(&mp_type_ValueError, MP_ERROR_TEXT("UART(%d) doesn't exist"), uart_id);
        }
    }

    machine_uart_obj_t *self;
    if (MP_STATE_PORT(machine_uart_obj_all)[uart_id] == NULL) {
        // create new UART object
        self = m_new0(machine_uart_obj_t, 1);
        self->base.type = &machine_uart_type;
        self->uart_id = uart_id;
        MP_STATE_PORT(machine_uart_obj_all)[uart_id] = self;
    } else {
        self = MP_STATE_PORT(machine_uart_obj_all)[uart_id];
    }

    if (n_args > 1 || n_kw > 0) {
        // start the peripheral
        mp_map_t kw_args;
        mp_map_init_fixed_table(&kw_args, n_kw, all_args + n_args);
        mp_machine_uart_init_helper(self, n_args - 1, all_args + 1, &kw_args);
    }

    return MP_OBJ_FROM_PTR(self);
}


STATIC void mp_machine_uart_deinit(machine_uart_obj_t *self) {
    (void)self;
}

// Write a single character on the bus.  `data` is an integer to write.
STATIC void mp_machine_uart_writechar(machine_uart_obj_t *self, uint16_t data) {
    // nrfx_err_t err = uart_tx_char(self, data);
    // if (err != NRFX_SUCCESS) {
    //     mp_hal_raise(err);
    // }
}

// uart.any()
STATIC mp_int_t mp_machine_uart_any(machine_uart_obj_t *self) {
    return 0; // ringbuf_avail((ringbuf_t *)&self->buf.rx_ringbuf);
}

// uart.txdone()
STATIC bool mp_machine_uart_txdone(machine_uart_obj_t *self) {
    return false;
}

STATIC mp_uint_t mp_machine_uart_read(mp_obj_t self_in, void *buf_in, mp_uint_t size, int *errcode) {

    return size;
}

STATIC mp_uint_t mp_machine_uart_write(mp_obj_t self_in, const void *buf_in, mp_uint_t size, int *errcode) {

    return size;
}

STATIC mp_uint_t mp_machine_uart_ioctl(mp_obj_t self_in, mp_uint_t request, uintptr_t arg, int *errcode) {
    machine_uart_obj_t *self = self_in;
    (void)self;
    mp_uint_t ret = 0;

    return ret;
}