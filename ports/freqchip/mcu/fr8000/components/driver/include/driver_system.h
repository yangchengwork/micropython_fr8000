#ifndef _DRIVER_SYSTEM_H
#define _DRIVER_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#include "plf.h"

enum system_clk_t {
    SYSTEM_SYS_CLK_8M,
    SYSTEM_SYS_CLK_16M,
    SYSTEM_SYS_CLK_24M,
    SYSTEM_SYS_CLK_32M,
    SYSTEM_SYS_CLK_48M,
    SYSTEM_SYS_CLK_96M,
};

struct system_clk_cfg_t {
    uint32_t sys_clk_sel:3;     // 000---8MHz,001---16MHz,010---24MHZ,011---32MHz,100---48MHz,101---96MHz
    uint32_t boot_clk_sel:1;        //0-- rc64M clock 1-- osc_24M clock used
    uint32_t i2c0_clk_sel:1;        //0--48MHz,1---96MHz
    uint32_t i2c1_clk_sel:1;        //0--48MHz,1---96MHz
    uint32_t ssim0_sclk_sel:1;      //0--48MHz,1---96MHz
    uint32_t ssim1_sclk_sel:1;      //0--48MHz,1---96MHz
    uint32_t ssis_sclk_sel:1;       //0--48MHz,1---96MHz
    uint32_t uart0_sclk_sel:1;      //0--48MHz,1---96MHz
    uint32_t lcd_para_sclk_sel:1;   //0--48MHz,1---96MHz
    uint32_t rc64m_cal_en:1;      //0--48MHz,1---96MHz
    uint32_t auxadc_clk_div:4;      //clk = clk_osc/(2*auxadc_clk_div)
    uint32_t out_clk_div:8;         //clk = clk_osc/(2*out_clk_div)
    uint32_t rc64m_cal_div:8;       //cal_clk = rc64M/(2*rc64m_cal_div)
};

struct system_clk_enable_t {
    uint32_t cm3_mas_clk_en:1;
    uint32_t lcd_para_clk_en:1;
    uint32_t ble_clk_en:1;
    uint32_t ble_em_clk_en:1;
    uint32_t efuse_clk_en:1;
    uint32_t gpio_clk_en:1;
    uint32_t auxadc_clk_en:1;
    uint32_t uart0_clk_en:1;
    uint32_t pdm_clk_en:1;
    uint32_t out_clk_en:1;
    uint32_t i2c0_clk_en:1;
    uint32_t i2c1_clk_en:1;
    uint32_t ssim0_clk_en:1;
    uint32_t ssim1_clk_en:1;
    uint32_t ssis_clk_en:1;
    uint32_t trng_clk_en:1;
    uint32_t rom_clk_en:1;
    uint32_t ram_clk_en:1;
    uint32_t bus_clk_en:1;
    uint32_t dma_clk_en:1;
    uint32_t i2s_clk_en:1;
    uint32_t apb_clk_en:1;
    uint32_t frspim_clk_en:1;
    uint32_t mdm_clk_en:1;
    uint32_t mdm_rf_clk_en:1;
    uint32_t mdm_rxv0_clk_en:1;
    uint32_t mdm_rxv1_clk_en:1;
    uint32_t rsv1:1;
    uint32_t f2lcd_clk_en:1;
    uint32_t usb_hclk_en:1;
    uint32_t usb_48M_en:1;
    uint32_t usb_12M_en:1;
};

struct system_mdm_dyn_qspi_t{
    uint32_t mdm_dyn_rst_tx_en:1;   // dyn reset source generated from tx_en negedge
    uint32_t mdm_dyn_rst_rx_en:1;   // dyn reset source genereated from rx_en negedge
    uint32_t mdm_dyn_rst_en_rf:1;   // dyn reset source mapped to rf block enable
    uint32_t mdm_dyn_rst_en_rx:1;   // dyn reset source mapped to rx block enable
    uint32_t mdm_dyn_rst_en_tx:1;   // dyn reset source mapped to tx block enable
    uint32_t mdm_dyn_rst_en_reg:1;  // dyn reset source mapped to register block enable
    uint32_t qspi_remap:1;          // 0-- qspi_io mapped to dedicated qspi_pads 1-- qspi_io mapped to portc
    uint32_t qspi0_remap:1;         // 0-- qspi0_io mapped to portc              1-- qspi0_io mapped to qspi_pads
    uint32_t qspi_ref_clk_sel:2;    // 00-- 48MHz 01--96MHz, others reserved.
    uint32_t qspi0_ref_clk_sel:2;   // 00-- 48MHz 01--96MHz, others reserved.
    uint32_t qspi_ref_128m_en:1;    // for debug
    uint32_t qspi_ref_src_cfg:2;    // for debug
    uint32_t rsv0:1;
    uint32_t qspi_ref_clk_en:1;
    uint32_t qspi0_ref_clk_en:1;
    uint32_t qspi_hclk_en:1;
    uint32_t qspi0_hclk_en:1;
    uint32_t qspi_io_ctl_oen:2;     // qspi sclk/csn output enable for TDM application
    uint32_t qspi0_io_ctl_oen:2;    // qspi0 sclk/csn output enable for TDM application
    uint32_t qspi_sclk_dly_sel:4;
    uint32_t qspi0_sclk_dly_sel:4;
};

struct system_rst_t {
    uint32_t rsv0:1;
    uint32_t ble_mas_rst:1;
    uint32_t ble_crypt_rst:1;
    uint32_t mdm_rf_rst:1;
    uint32_t mdm_rx_rst:1;
    uint32_t mdm_tx_rst:1;
    uint32_t mdm_reg_rst:1;
    uint32_t qspi_rst:1;
    uint32_t frspim_rst:1;
    uint32_t efuse_rst:1;
    uint32_t ssim0_rst:1;
    uint32_t ssim1_rst:1;
    uint32_t ssis_rst:1;
    uint32_t i2c0_rst:1;
    uint32_t i2c1_rst:1;
    uint32_t gpio_rst:1;
    uint32_t uart0_rst:1;
    uint32_t uart1_rst:1;
    uint32_t pwm_rst:1;
    uint32_t auxadc_rst:1;
    uint32_t pdm_rst:1;
    uint32_t trng_rst:1;
    uint32_t f2lcd_rst:1;
    uint32_t lcd_para_rst:1;
    uint32_t qspi0_rst:1;
    uint32_t i2s_rst:1;
    uint32_t rsv1:5;
};

struct system_misc_ctrl_t {
    uint32_t qspi_burn:1;                //flash sclk/csn/io0~1 mapped to pb0~b3
    uint32_t mem_remap:1;                //0-- 8KB shared memory mapped system 1--8KB ram to exchange memory
    uint32_t modem_if_sel:1;             //fixed @1'b1 
    uint32_t ble_phase_match_sel:1;      //0-- normal behavior for ble phase match 1-- half clock protect for timing
    uint32_t i2s_apb_clk_en:1;
    uint32_t rsv1:3;
    uint32_t gpio_clk_div:8;
    uint32_t timer_apb_clk_en:1;
    uint32_t frspim_apb_clk_en:1;
    uint32_t efuse_apb_clk_en:1;
    uint32_t ssim0_apb_clk_en:1;
    uint32_t ssim1_apb_clk_en:1;
    uint32_t ssis_apb_clk_en:1;
    uint32_t rich_i2c_apb_clk_en:1;
    uint32_t tiny_i2c_apb_clk_en:1;
    uint32_t rich_uart_apb_clk_en:1;
    uint32_t tiny_uart_apb_clk_en:1;
    uint32_t gpio_apb_clk_en:1;
    uint32_t pwm_apb_clk_en:1;
    uint32_t saradc_apb_clk_en:1;
    uint32_t pdm_apb_clk_en:1;
    uint32_t flash2lcd_apb_clk_en:1;
    uint32_t lcd_8080_apb_clk_en:1;
};

struct system_qspi_porte_cfg_t {
    uint32_t qspi_pe:6;         //qspi pad pull up/down enable
    uint32_t resv0:2;
    uint32_t qspi_ps:6;         //qspi pad pull up/down sel
    uint32_t resv1:2;
    uint32_t porte_pe:4;        //porte pull up/down enable
    uint32_t resv2:4;
    uint32_t porte_ps:4;        //porte pull up/down sel
    uint32_t resv3:4;
};

enum system_port_t {
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
};

enum system_port_bit_t {
    GPIO_BIT_0,
    GPIO_BIT_1,
    GPIO_BIT_2,
    GPIO_BIT_3,
    GPIO_BIT_4,
    GPIO_BIT_5,
    GPIO_BIT_6,
    GPIO_BIT_7,
};

enum system_port_pull_t {
    GPIO_PULL_UP,
    GPIO_PULL_DOWN,
    GPIO_PULL_NONE,
};

#define GPIO_DIR_IN             1
#define GPIO_DIR_OUT            0

#define SYSTEM_PORT_MUX_MSK     0xF
#define SYSTEM_PORT_MUX_LEN     4

#define PORT_FUNC_GPIO              0x00
#define PORT_FUNC_EXT_INT           0x01
#define PORT_FUNC_PWM               0x03
#define PORT_FUNC_PWM_EN            0x0a

#define PORTA0_FUNC_A0              0x00
#define PORTA0_FUNC_I2C0_CLK        0x01
#define PORTA0_FUNC_SSIM0_CLK       0x02
#define PORTA0_FUNC_SSIS_CLK        0x03
#define PORTA0_FUNC_UART0_RXD       0x04
#define PORTA0_FUNC_USB_DP          0x05
#define PORTA0_FUNC_PWM0            0x06
#define PORTA0_FUNC_PDM_CLK         0x07
#define PORTA0_FUNC_BLE_TX          0x08
#define PORTA0_FUNC_SIRIN           0x09
#define PORTA0_FUNC_I2S_BCLK        0x0A
#define PORTA0_FUNC_LCD_CSX         0x0D

#define PORTA1_FUNC_A1              0x00
#define PORTA1_FUNC_I2C0_DAT        0x01
#define PORTA1_FUNC_SSIM0_CSN       0x02
#define PORTA1_FUNC_SSIS_CSN        0x03
#define PORTA1_FUNC_UART0_TXD       0x04
#define PORTA1_FUNC_USB_DM          0x05
#define PORTA1_FUNC_PWM1            0x06
#define PORTA1_FUNC_PDM_DAT         0x07
#define PORTA1_FUNC_BLE_RX          0x08
#define PORTA1_FUNC_SIROUT          0x09
#define PORTA1_FUNC_I2S_frm         0x0A
#define PORTA1_FUNC_LCD_DCX         0x0d

#define PORTA2_FUNC_A2              0x00
#define PORTA2_FUNC_I2C1_CLK        0x01
#define PORTA2_FUNC_SSIM0_IO0       0x02
#define PORTA2_FUNC_SSIS_MOSI       0x03
#define PORTA2_FUNC_UART0_RTS       0x04
#define PORTA2_FUNC_UART1_RXD       0x05
#define PORTA2_FUNC_PWM2            0x06
#define PORTA2_FUNC_PDM_CLK         0x07
#define PORTA2_FUNC_WLAN_TX         0x08
#define PORTA2_FUNC_RS485_EN        0x09
#define PORTA2_FUNC_I2S_MOSI        0x0A
#define PORTA2_FUNC_LCD_WRX         0x0D

#define PORTA3_FUNC_A3              0x00
#define PORTA3_FUNC_I2C1_DAT        0x01
#define PORTA3_FUNC_SSIM0_IO1       0x02
#define PORTA3_FUNC_SSIS_MISO       0x03
#define PORTA3_FUNC_UART0_CTS       0x04
#define PORTA3_FUNC_UART1_TXD       0x05
#define PORTA3_FUNC_PWM3            0x06
#define PORTA3_FUNC_PDM_DAT         0x07
#define PORTA3_FUNC_WLAN_RX         0x08
#define PORTA3_FUNC_I2S_MISO        0x0A
#define PORTA3_FUNC_LCD_RDX         0x0D

#define PORTA4_FUNC_A4              0x00
#define PORTA4_FUNC_I2C0_CLK        0x01
#define PORTA4_FUNC_SSIM0_IO2       0x02
#define PORTA4_FUNC_SSIS_CLK        0x03
#define PORTA4_FUNC_UART0_RXD       0x04
#define PORTA4_FUNC_USB_DP          0x05
#define PORTA4_FUNC_PWM4            0x06
#define PORTA4_FUNC_PDM_CLK         0x07
#define PORTA4_FUNC_CLK_OUT         0x08
#define PORTA4_FUNC_I2S_BCLK        0x0A
#define PORTA4_FUNC_LCD_TE          0x0D

#define PORTA5_FUNC_A5              0x00
#define PORTA5_FUNC_I2C0_DAT        0x01
#define PORTA5_FUNC_SSIM0_IO3       0x02
#define PORTA5_FUNC_SSIS_CSN        0x03
#define PORTA5_FUNC_UART0_TXD       0x04
#define PORTA5_FUNC_USB_DM          0x05
#define PORTA5_FUNC_PWM5            0x06
#define PORTA5_FUNC_PDM_DAT         0x07
#define PORTA5_FUNC_ANTENNA_TX      0x08
#define PORTA5_FUNC_SIRIN           0x09
#define PORTA5_FUNC_I2S_FRM         0x0A
#define PORTA5_FUNC_LCD_TE          0x0D

#define PORTA6_FUNC_A6              0x00
#define PORTA6_FUNC_I2C1_CLK        0x01
#define PORTA6_FUNC_SSIM0_CLK       0x02
#define PORTA6_FUNC_SSIS_MOSI       0x03
#define PORTA6_FUNC_UART0_RTS       0x04
#define PORTA6_FUNC_UART1_RXD       0x05
#define PORTA6_FUNC_PWM6            0x06
#define PORTA6_FUNC_PDM_CLK         0x07
#define PORTA6_FUNC_ANTENNA_RX      0x08
#define PORTA6_FUNC_SIROUT          0x09
#define PORTA6_FUNC_I2S_MOSI        0x0A
#define PORTA6_FUNC_LCD_CSX         0x0D

#define PORTA7_FUNC_A7              0x00
#define PORTA7_FUNC_I2C1_DAT        0x01
#define PORTA7_FUNC_SSIM0_CSN       0x02
#define PORTA7_FUNC_SSIS_MISO       0x03
#define PORTA7_FUNC_UART0_CTS       0x04
#define PORTA7_FUNC_UART1_TXD       0x05
#define PORTA7_FUNC_PWM7            0x06
#define PORTA7_FUNC_PDM_DAT         0x07
#define PORTA7_FUNC_CLK_OUT         0x08
#define PORTA7_FUNC_RS485_EN        0x09
#define PORTA7_FUNC_I2S_MISO        0x0A
#define PORTA7_FUNC_LCD_DCX         0x0D

#define PORTB0_FUNC_B0              0x00
#define PORTB0_FUNC_I2C0_CLK        0x01
#define PORTB0_FUNC_SSIM0_CLK       0x02
#define PORTB0_FUNC_SSIS_CLK        0x03
#define PORTB0_FUNC_UART0_RXD       0x04
#define PORTB0_FUNC_USB_DP          0x05
#define PORTB0_FUNC_PWM0            0x06
#define PORTB0_FUNC_PDM_CLK         0x07
#define PORTB0_FUNC_BLE_TX          0x08
#define PORTB0_FUNC_SIRIN           0x09
#define PORTB0_FUNC_QSPI_BURN_SCLK  0x0A
#define PORTB0_FUNC_LCD_DAT0        0x0D

#define PORTB1_FUNC_B1              0x00
#define PORTB1_FUNC_I2C0_DAT        0x01
#define PORTB1_FUNC_SSIM0_CSN       0x02
#define PORTB1_FUNC_SSIS_CSN        0x03
#define PORTB1_FUNC_UART0_TXD       0x04
#define PORTB1_FUNC_USB_DM          0x05
#define PORTB1_FUNC_PWM1            0x06
#define PORTB1_FUNC_PDM_DAT         0x07
#define PORTB1_FUNC_BLE_RX          0x08
#define PORTB1_FUNC_SIROUT          0x09
#define PORTB1_FUNC_QSPI_BURN_CSN   0x0A
#define PORTB1_FUNC_LCD_DAT1        0x0D

#define PORTB2_FUNC_B2              0x00
#define PORTB2_FUNC_I2C1_CLK        0x01
#define PORTB2_FUNC_SSIM0_IO0       0x02
#define PORTB2_FUNC_SSIS_MOSI       0x03
#define PORTB2_FUNC_UART0_RTS       0x04
#define PORTB2_FUNC_UART1_RXD       0x05
#define PORTB2_FUNC_PWM2            0x06
#define PORTB2_FUNC_PDM_CLK         0x07
#define PORTB2_FUNC_WLAN_TX         0x08
#define PORTB2_FUNC_RS485_EN        0x09
#define PORTB2_FUNC_QSPI_BURN_MOSI  0x0A
#define PORTB2_FUNC_LCD_DAT2        0x0D

#define PORTB3_FUNC_B3              0x00
#define PORTB3_FUNC_I2C1_DAT        0x01
#define PORTB3_FUNC_SSIM0_IO1       0x02
#define PORTB3_FUNC_SSIS_MISO       0x03
#define PORTB3_FUNC_UART0_CTS       0x04
#define PORTB3_FUNC_UART1_TXD       0x05
#define PORTB3_FUNC_PWM3            0x06
#define PORTB3_FUNC_PDM_DAT         0x07
#define PORTB3_FUNC_WLAN_RX         0x08
#define PORTB3_FUNC_LCD_CSX         0x09
#define PORTB3_FUNC_QSPI_BURN_MISO  0x0A
#define PORTB3_FUNC_LCD_DAT3        0x0D

#define PORTB4_FUNC_B4              0x00
#define PORTB4_FUNC_I2C0_CLK        0x01
#define PORTB4_FUNC_SSIM0_IO2       0x02
#define PORTB4_FUNC_SSIS_CLK        0x03
#define PORTB4_FUNC_UART0_RXD       0x04
#define PORTB4_FUNC_USB_DP          0x05
#define PORTB4_FUNC_PWM4            0x06
#define PORTB4_FUNC_PDM_CLK         0x07
#define PORTB4_FUNC_CLK_OUT         0x08
#define PORTB4_FUNC_LCD_DCX         0x09
#define PORTB4_FUNC_I2S_BCLK        0x0A
#define PORTB4_FUNC_LCD_DAT4        0x0D

#define PORTB5_FUNC_B5              0x00
#define PORTB5_FUNC_I2C0_DAT        0x01
#define PORTB5_FUNC_SSIM0_IO3       0x02
#define PORTB5_FUNC_SSIS_CSN        0x03
#define PORTB5_FUNC_UART0_TXD       0x04
#define PORTB5_FUNC_USB_DM          0x05
#define PORTB5_FUNC_PWM5            0x06
#define PORTB5_FUNC_PDM_DAT         0x07
#define PORTB5_FUNC_ANTENNA_TX      0x08
#define PORTB5_FUNC_SIRIN           0x09
#define PORTB5_FUNC_I2S_FRM         0x0A
#define PORTB5_FUNC_LCD_DAT5        0x0D

#define PORTB6_FUNC_B6              0x00
#define PORTB6_FUNC_I2C1_CLK        0x01
#define PORTB6_FUNC_SSIM0_CLK       0x02
#define PORTB6_FUNC_SSIS_MOSI       0x03
#define PORTB6_FUNC_UART0_RTS       0x04
#define PORTB6_FUNC_UART1_RXD       0x05
#define PORTB6_FUNC_PWM6            0x06
#define PORTB6_FUNC_PDM_CLK         0x07
#define PORTB6_FUNC_ANTENNA_RX      0x08
#define PORTB6_FUNC_SIROUT          0x09
#define PORTB6_FUNC_I2S_MOSI        0x0A
#define PORTB6_FUNC_LCD_DAT6        0x0D

#define PORTB7_FUNC_B7              0x00
#define PORTB7_FUNC_I2C1_DAT        0x01
#define PORTB7_FUNC_SSIM0_CSN       0x02
#define PORTB7_FUNC_SSIS_MISO       0x03
#define PORTB7_FUNC_UART0_CTS       0x04
#define PORTB7_FUNC_UART1_TXD       0x05
#define PORTB7_FUNC_PWM7            0x06
#define PORTB7_FUNC_PDM_DAT         0x07
#define PORTB7_FUNC_CLK_OUT         0x08
#define PORTB7_FUNC_RS485_EN        0x09
#define PORTB7_FUNC_I2S_MISO        0x0A
#define PORTB7_FUNC_LCD_DAT7        0x0D

#define PORTC0_FUNC_C0              0x00
#define PORTC0_FUNC_I2C0_CLK        0x01
#define PORTC0_FUNC_SSIM1_CLK       0x02
#define PORTC0_FUNC_SSIS_CLK        0x03
#define PORTC0_FUNC_UART0_RXD       0x04
#define PORTC0_FUNC_LCD_CSX         0x05
#define PORTC0_FUNC_PWM0            0x06
#define PORTC0_FUNC_PDM_CLK         0x07
#define PORTC0_FUNC_SWV             0x08
#define PORTC0_FUNC_SIRIN           0x09
#define PORTC0_FUNC_I2S_BCLK        0x0A
#define PORTC0_FUNC_QSPI_IO3        0x0B
#define PORTC0_FUNC_QSPI0_IO3       0x0C
#define PORTC0_FUNC_LCD_DAT8        0x0D

#define PORTC1_FUNC_C1              0x00
#define PORTC1_FUNC_I2C0_DAT        0x01
#define PORTC1_FUNC_SSIM1_CSN       0x02
#define PORTC1_FUNC_SSIS_CSN        0x03
#define PORTC1_FUNC_UART0_TXD       0x04
#define PORTC1_FUNC_LCD_DCX         0x05
#define PORTC1_FUNC_PWM1            0x06
#define PORTC1_FUNC_PDM_DAT         0x07
#define PORTC1_FUNC_SWV             0x08
#define PORTC1_FUNC_SIROUT          0x09
#define PORTC1_FUNC_I2S_FRM         0x0A
#define PORTC1_FUNC_QSPI_SCLK0      0x0B
#define PORTC1_FUNC_QSPI0_SCLK0     0x0C
#define PORTC1_FUNC_LCD_DAT9        0x0D

#define PORTC2_FUNC_C2              0x00
#define PORTC2_FUNC_I2C1_CLK        0x01
#define PORTC2_FUNC_SSIM1_IO0       0x02
#define PORTC2_FUNC_SSIS_MOSI       0x03
#define PORTC2_FUNC_UART0_RTS       0x04
#define PORTC2_FUNC_UART1_RXD       0x05
#define PORTC2_FUNC_PWM2            0x06
#define PORTC2_FUNC_PDM_CLK         0x07
#define PORTC2_FUNC_SWV             0x08
#define PORTC2_FUNC_RS485_EN        0x09
#define PORTC2_FUNC_I2S_MOSI        0x0A
#define PORTC2_FUNC_QSPI_CSN0       0x0B
#define PORTC2_FUNC_QSPI0_CSN0      0x0C
#define PORTC2_FUNC_LCD_DAT10       0x0D

#define PORTC3_FUNC_C3              0x00
#define PORTC3_FUNC_I2C1_DAT        0x01
#define PORTC3_FUNC_SSIM1_IO1       0x02
#define PORTC3_FUNC_SSIS_MISO       0x03
#define PORTC3_FUNC_UART0_CTS       0x04
#define PORTC3_FUNC_UART1_TXD       0x05
#define PORTC3_FUNC_PWM3            0x06
#define PORTC3_FUNC_PDM_DAT         0x07
#define PORTC3_FUNC_SWV             0x08
#define PORTC3_FUNC_LCD_TE          0x09
#define PORTC3_FUNC_I2S_MISO        0x0A
#define PORTC3_FUNC_QSPI_IO1        0x0B
#define PORTC3_FUNC_QSPI0_IO1       0x0C
#define PORTC3_FUNC_LCD_DAT11       0x0D

#define PORTC4_FUNC_C4              0x00
#define PORTC4_FUNC_I2C0_CLK        0x01
#define PORTC4_FUNC_SSIM1_IO2       0x02
#define PORTC4_FUNC_SSIS_CLK        0x03
#define PORTC4_FUNC_UART0_RXD       0x04
#define PORTC4_FUNC_LCD_WRX         0x05
#define PORTC4_FUNC_PWM4            0x06
#define PORTC4_FUNC_PDM_CLK         0x07
#define PORTC4_FUNC_ANTENNA_RX      0x08
#define PORTC4_FUNC_LCD_TE          0x09
#define PORTC4_FUNC_I2S_BCLK        0x0A
#define PORTC4_FUNC_QSPI_IO2        0x0B
#define PORTC4_FUNC_QSPI0_IO2       0x0C
#define PORTC4_FUNC_LCD_DAT12       0x0D

#define PORTC5_FUNC_C5              0x00
#define PORTC5_FUNC_I2C0_DAT        0x01
#define PORTC5_FUNC_SSIM1_IO3       0x02
#define PORTC5_FUNC_SSIS_CSN        0x03
#define PORTC5_FUNC_UART0_TXD       0x04
#define PORTC5_FUNC_LCD_RDX         0x05
#define PORTC5_FUNC_PWM5            0x06
#define PORTC5_FUNC_PDM_DAT         0x07
#define PORTC5_FUNC_SWV             0x08
#define PORTC5_FUNC_SIRIN           0x09
#define PORTC5_FUNC_I2S_FRM         0x0A
#define PORTC5_FUNC_QSPI_IO0        0x0B
#define PORTC5_FUNC_QSPI0_IO0       0x0C
#define PORTC5_FUNC_LCD_DAT13       0x0D

#define PORTC6_FUNC_C6              0x00
#define PORTC6_FUNC_I2C1_CLK        0x01
#define PORTC6_FUNC_SSIM1_CLK       0x02
#define PORTC6_FUNC_SSIS_MOSI       0x03
#define PORTC6_FUNC_UART0_RTS       0x04
#define PORTC6_FUNC_UART1_RXD       0x05
#define PORTC6_FUNC_PWM6            0x06
#define PORTC6_FUNC_PDM_CLK         0x07
#define PORTC6_FUNC_SW_TCK          0x08
#define PORTC6_FUNC_SIROUT          0x09
#define PORTC6_FUNC_I2S_MOSI        0x0A
#define PORTC6_FUNC_QSPI_SCLK1      0x0B
#define PORTC6_FUNC_QSPI0_SCLK1     0x0C
#define PORTC6_FUNC_LCD_DAT14       0x0D

#define PORTC7_FUNC_C7              0x00
#define PORTC7_FUNC_I2C1_DAT        0x01
#define PORTC7_FUNC_SSIM1_CSN       0x02
#define PORTC7_FUNC_SSIS_MISO       0x03
#define PORTC7_FUNC_UART0_CTS       0x04
#define PORTC7_FUNC_UART1_TXD       0x05
#define PORTC7_FUNC_PWM7            0x06
#define PORTC7_FUNC_PDM_DAT         0x07
#define PORTC7_FUNC_SW_DIO          0x08
#define PORTC7_FUNC_RS485_EN        0x09
#define PORTC7_FUNC_I2S_MISO        0x0A
#define PORTC7_FUNC_QSPI_CSN1       0x0B
#define PORTC7_FUNC_QSPI0_CSN1      0x0C
#define PORTC7_FUNC_LCD_DAT15       0x0D

#define PORTD0_FUNC_D0              0x00
#define PORTD0_FUNC_I2C0_CLK        0x01
#define PORTD0_FUNC_SSIM1_CLK       0x02
#define PORTD0_FUNC_SSIS_CLK        0x03
#define PORTD0_FUNC_UART0_RXD       0x04
//#define PORTD0_FUNC_UART1_RXD       0x05
#define PORTD0_FUNC_PWM0            0x06
#define PORTD0_FUNC_PDM_CLK         0x07
#define PORTD0_FUNC_SARADC0         0x08
#define PORTD0_FUNC_SIRIN           0x09
#define PORTD0_FUNC_I2S_BCLK        0x0A
#define PORTD0_FUNC_LCD_WRX         0x0D

#define PORTD1_FUNC_D1              0x00
#define PORTD1_FUNC_I2C0_DAT        0x01
#define PORTD1_FUNC_SSIM1_CSN       0x02
#define PORTD1_FUNC_SSIS_CSN        0x03
#define PORTD1_FUNC_UART0_TXD       0x04
//#define PORTD1_FUNC_UART1_TXD       0x05
#define PORTD1_FUNC_PWM1            0x06
#define PORTD1_FUNC_PDM_DAT         0x07
#define PORTD1_FUNC_SARADC1         0x08
#define PORTD1_FUNC_SIROUT          0x09
#define PORTD1_FUNC_I2S_FRM         0x0A
#define PORTD1_FUNC_LCD_RDX         0x0D

#define PORTD2_FUNC_D2              0x00
#define PORTD2_FUNC_I2C1_CLK       0x01
#define PORTD2_FUNC_SSIM1_IO0       0x02
#define PORTD2_FUNC_SSIS_MOSI       0x03
#define PORTD2_FUNC_UART0_RTS       0x04
#define PORTD2_FUNC_UART1_RXD       0x05
#define PORTD2_FUNC_PWM2            0x06
#define PORTD2_FUNC_PDM_CLK         0x07
#define PORTD2_FUNC_SARADC2         0x08
#define PORTD2_FUNC_RS485_EN        0x09
#define PORTD2_FUNC_I2S_MOSI        0x0A
#define PORTD2_FUNC_LCD_TE          0x0D

#define PORTD3_FUNC_D3              0x00
#define PORTD3_FUNC_I2C1_DAT        0x01
#define PORTD3_FUNC_SSIM1_IO1       0x02
#define PORTD3_FUNC_SSIS_MISO       0x03
#define PORTD3_FUNC_UART0_CTS       0x04
#define PORTD3_FUNC_UART1_TXD       0x05
#define PORTD3_FUNC_PWM3            0x06
#define PORTD3_FUNC_PDM_DAT         0x07
#define PORTD3_FUNC_SARADC3         0x08
#define PORTD3_FUNC_I2S_MISO        0x0A
#define PORTD3_FUNC_LCD_TE          0x0D

#define PORTD4_FUNC_D4              0x00
#define PORTD4_FUNC_I2C0_CLK        0x01
#define PORTD4_FUNC_SSIM1_IO2       0x02
#define PORTD4_FUNC_SSIS_CLK        0x03
#define PORTD4_FUNC_UART0_RXD       0x04
//#define PORTD4_FUNC_UART1_RXD       0x05
#define PORTD4_FUNC_PWM4            0x06
#define PORTD4_FUNC_PDM_CLK         0x07
#define PORTD4_FUNC_SARADC4         0x08
#define PORTD4_FUNC_I2S_BCLK        0x0A
#define PORTD4_FUNC_LCD_CSX         0x0D

#define PORTD5_FUNC_D5              0x00
#define PORTD5_FUNC_I2C0_DAT        0x01
#define PORTD5_FUNC_SSIM1_IO3       0x02
#define PORTD5_FUNC_SSIS_CSN        0x03
#define PORTD5_FUNC_UART0_TXD       0x04
//#define PORTD5_FUNC_UART1_TXD       0x05
#define PORTD5_FUNC_PWM5            0x06
#define PORTD5_FUNC_PDM_DAT         0x07
#define PORTD5_FUNC_SARADC5         0x08
#define PORTD5_FUNC_SIRIN           0x09
#define PORTD5_FUNC_I2S_FRM         0x0A
#define PORTD5_FUNC_LCD_DCX         0x0D

#define PORTD6_FUNC_D6              0x00
#define PORTD6_FUNC_I2C1_CLK        0x01
#define PORTD6_FUNC_SSIM1_CLK       0x02
#define PORTD6_FUNC_SSIS_MOSI       0x03
#define PORTD6_FUNC_UART0_RTS       0x04
#define PORTD6_FUNC_UART1_RXD       0x05
#define PORTD6_FUNC_PWM6            0x06
#define PORTD6_FUNC_PDM_CLK         0x07
#define PORTD6_FUNC_SARADC6         0x08
#define PORTD6_FUNC_SIROUT          0x09
#define PORTD6_FUNC_I2S_MOSI        0x0A
#define PORTD6_FUNC_LCD_WRX         0x0D

#define PORTD7_FUNC_D7              0x00
#define PORTD7_FUNC_I2C1_DAT        0x01
#define PORTD7_FUNC_SSIM1_CSN       0x02
#define PORTD7_FUNC_SSIS_MISO       0x03
#define PORTD7_FUNC_UART0_CTS       0x04
#define PORTD7_FUNC_UART1_TXD       0x05
#define PORTD7_FUNC_PWM7            0x06
#define PORTD7_FUNC_PDM_DAT         0x07
#define PORTD7_FUNC_SARADC7         0x08
#define PORTD7_FUNC_RS485_EN        0x09
#define PORTD7_FUNC_I2S_MISO        0x0A
#define PORTD7_FUNC_LCD_RDX         0x0D

#define PORTE0_FUNC_E0              0x00
#define PORTE0_FUNC_I2C0_CLK        0x01
#define PORTE0_FUNC_SSIM1_IO0       0x02
#define PORTE0_FUNC_SSIS_CLK        0x03
#define PORTE0_FUNC_UART0_RXD       0x04
#define PORTE0_FUNC_UART1_RXD       0x05
#define PORTE0_FUNC_PWM0            0x06
#define PORTE0_FUNC_PDM_CLK         0x07
#define PORTE0_FUNC_BLE_TX          0x08
#define PORTE0_FUNC_SIRIN           0x09
#define PORTE0_FUNC_USB_DP          0x0A
#define PORTE0_FUNC_LCD_TE          0x0D

#define PORTE1_FUNC_E1              0x00
#define PORTE1_FUNC_I2C0_DAT        0x01
#define PORTE1_FUNC_SSIM1_IO1       0x02
#define PORTE1_FUNC_SSIS_CSN        0x03
#define PORTE1_FUNC_UART0_TXD       0x04
#define PORTE1_FUNC_UART1_TXD       0x05
#define PORTE1_FUNC_PWM1            0x06
#define PORTE1_FUNC_PDM_DAT         0x07
#define PORTE1_FUNC_BLE_RX          0x08
#define PORTE1_FUNC_SIROUT          0x09
#define PORTE1_FUNC_USB_DM          0x0A
#define PORTE1_FUNC_LCD_TE          0x0D

#define PORTE2_FUNC_E2              0x00
#define PORTE2_FUNC_I2C1_CLK        0x01
#define PORTE2_FUNC_SSIM0_IO0       0x02
#define PORTE2_FUNC_SSIS_MOSI       0x03
#define PORTE2_FUNC_UART0_RTS       0x04
#define PORTE2_FUNC_UART1_RXD       0x05
#define PORTE2_FUNC_PWM2            0x06
#define PORTE2_FUNC_PDM_CLK         0x07
#define PORTE2_FUNC_WLAN_TX         0x08
#define PORTE2_FUNC_RS485_EN        0x09

#define PORTE3_FUNC_E3              0x00
#define PORTE3_FUNC_I2C1_DAT        0x01
#define PORTE3_FUNC_SSIM0_IO1       0x02
#define PORTE3_FUNC_SSIS_MISO       0x03
#define PORTE3_FUNC_UART0_CTS       0x04
#define PORTE3_FUNC_UART1_TXD       0x05
#define PORTE3_FUNC_PWM3            0x06
#define PORTE3_FUNC_PDM_DAT         0x07
#define PORTE3_FUNC_WLAN_RX         0x08


#define SYSTEM_ONKEY_MAP_EXI11_POS  CO_BIT(7)
#define SYSTEM_ONKEY_MAP_EXI10_POS  CO_BIT(6)
#define SYSTEM_ONKEY_MAP_EXI9_POS   CO_BIT(5)
#define SYSTEM_ONKEY_MAP_EXI8_POS   CO_BIT(4)
#define SYSTEM_ONKEY_MAP_EXI3_POS   CO_BIT(3)
#define SYSTEM_ONKEY_MAP_EXI2_POS   CO_BIT(2)
#define SYSTEM_ONKEY_MAP_EXI1_POS   CO_BIT(1)
#define SYSTEM_ONKEY_MAP_EXI0_POS   CO_BIT(0)

#define GPIO_PA0              (1<<0)
#define GPIO_PA1              (1<<1)
#define GPIO_PA2              (1<<2)
#define GPIO_PA3              (1<<3)
#define GPIO_PA4              (1<<4)
#define GPIO_PA5              (1<<5)
#define GPIO_PA6              (1<<6)
#define GPIO_PA7              (1<<7)

#define GPIO_PB0              (1<<8)
#define GPIO_PB1              (1<<9)
#define GPIO_PB2              (1<<10)
#define GPIO_PB3              (1<<11)
#define GPIO_PB4              (1<<12)
#define GPIO_PB5              (1<<13)
#define GPIO_PB6              (1<<14)
#define GPIO_PB7              (1<<15)

#define GPIO_PC0              (1<<16)
#define GPIO_PC1              (1<<17)
#define GPIO_PC2              (1<<18)
#define GPIO_PC3              (1<<19)
#define GPIO_PC4              (1<<20)
#define GPIO_PC5              (1<<21)
#define GPIO_PC6              (1<<22)
#define GPIO_PC7              (1<<23)

#define GPIO_PD0              (1<<24)
#define GPIO_PD1              (1<<25)
#define GPIO_PD2              (1<<26)
#define GPIO_PD3              (1<<27)
#define GPIO_PD4              (1<<28)
#define GPIO_PD5              (1<<29)
#define GPIO_PD6              (1<<30)
#define GPIO_PD7              ((uint32_t)1<<31)

struct system_led_cntl_t {
    uint32_t led0_en:1;
    uint32_t led1_en:1;
    uint32_t led2_en:1;
    uint32_t led3_en:1;
    uint32_t led4_en:1;
    uint32_t led0_inv:1;
    uint32_t led1_inv:1;
    uint32_t led2_inv:1;
    uint32_t led3_inv:1;
    uint32_t led4_inv:1;
    uint32_t led_clk_div:6;
    uint32_t reserved:16;
};

struct system_led_cfg_t {
    uint32_t led_shift:24;
    uint32_t led_low_cnt:8;
};

struct system_charger_state_t {
    uint32_t bat_qs_data:3;
    uint32_t reserved1:1;
    uint32_t bat_state:1;
    uint32_t reserved2:3;
    uint32_t charger_state:1;
    uint32_t reserved3:23;
};

struct system_keyscan_ctrl_t {
    uint32_t int_en:1;
    uint32_t reserved:31;
};

struct system_regs_t {
    struct system_clk_cfg_t clk_cfg;                    //0x00
    struct system_clk_enable_t clk_gate;                //0x04
    struct system_mdm_dyn_qspi_t mdm_qspi_cfg;          //0x08
    struct system_rst_t rst;                            //0x0c
    struct system_misc_ctrl_t  misc;                    //0x10
    uint32_t dma_req[3];                                //0x14
    uint32_t port_mux[4];                               //0x20
    uint32_t port_pull_enable;                          //0x30
    uint32_t port_pull_sel;                             //0x34
    struct system_qspi_porte_cfg_t qspi_porte_cfg;      //0x38
    uint32_t porte_mux_sel;                             //0x3c
};

enum rf_tx_power_t {
    RF_TX_POWER_NEG_10dBm,
    RF_TX_POWER_NEG_4dBm,
    RF_TX_POWER_NEG_1dBm,
    RF_TX_POWER_0dBm,
    RF_TX_POWER_POS_1dBm,
    RF_TX_POWER_POS_2dBm,
    RF_TX_POWER_POS_3dBm,
    RF_TX_POWER_POS_4dBm,
    RF_TX_POWER_POS_5dBm,
    RF_TX_POWER_POS_6dBm,
    RF_TX_POWER_POS_7dBm,
    RF_TX_POWER_POS_8dBm,
    RF_TX_POWER_POS_9dBm,
    RF_TX_POWER_POS_10dBm,
    RF_TX_POWER_MAX,
};

extern struct system_regs_t *const system_regs;

/*********************************************************************
 * @fn      system_enable_cache
 *
 * @brief   enable cache
 * 
 * @param   invalid_ram: true(fixed)
 */
void system_enable_cache(uint8_t invalid_ram);
void system_disable_cache(void);

uint32_t system_get_clock(void);
uint8_t system_get_clock_config(void);
void system_set_clock(uint8_t clock_cfg);
void system_set_port_mux(uint8_t port, uint8_t bit, uint8_t func);

/* Exported macro ------------------------------------------------------------*/

/* peripheral clock select */
#define __SYSTEM_IF8080_CLK_SELECT_48M()                (system_regs->clk_cfg.lcd_para_sclk_sel = 0)
#define __SYSTEM_IF8080_CLK_SELECT_96M()                (system_regs->clk_cfg.lcd_para_sclk_sel = 1)

#define __SYSTEM_UART0_CLK_SELECT_48M()                 (system_regs->clk_cfg.uart0_sclk_sel = 0)
#define __SYSTEM_UART0_CLK_SELECT_96M()                 (system_regs->clk_cfg.uart0_sclk_sel = 1)

#define __SYSTEM_SPI_SLAVE_CLK_SELECT_48M()             (system_regs->clk_cfg.ssis_sclk_sel = 0)
#define __SYSTEM_SPI_SLAVE_CLK_SELECT_96M()             (system_regs->clk_cfg.ssis_sclk_sel = 1)

#define __SYSTEM_SPI1_MASTER_CLK_SELECT_48M()           (system_regs->clk_cfg.ssim1_sclk_sel = 0)
#define __SYSTEM_SPI1_MASTER_CLK_SELECT_96M()           (system_regs->clk_cfg.ssim1_sclk_sel = 1)

#define __SYSTEM_SPI0_MASTER_CLK_SELECT_48M()           (system_regs->clk_cfg.ssim0_sclk_sel = 0)
#define __SYSTEM_SPI0_MASTER_CLK_SELECT_96M()           (system_regs->clk_cfg.ssim0_sclk_sel = 1)

#define __SYSTEM_I2C1_MASTER_CLK_SELECT_48M()           (system_regs->clk_cfg.i2c1_clk_sel = 0)
#define __SYSTEM_I2C1_MASTER_CLK_SELECT_96M()           (system_regs->clk_cfg.i2c1_clk_sel = 1)

#define __SYSTEM_I2C0_MASTER_CLK_SELECT_48M()           (system_regs->clk_cfg.i2c0_clk_sel = 0)
#define __SYSTEM_I2C0_MASTER_CLK_SELECT_96M()           (system_regs->clk_cfg.i2c0_clk_sel = 1)

#define __SYSTEM_GET_UART0_CLK_SELECT(__CLK__)       do {if (system_regs->clk_cfg.uart0_sclk_sel == 0) \
                                                             __CLK__ = 48000000;                       \
                                                         else                                          \
                                                             __CLK__ = 96000000;}while(0)
   

/* peripheral clock enable/disable */
#define __SYSTEM_IF8080_CLK_ENABLE()                 do {system_regs->clk_gate.lcd_para_clk_en = 1; \
                                                         system_regs->misc.lcd_8080_apb_clk_en = 1;}while(0)
#define __SYSTEM_IF8080_CLK_DISABLE()                do {system_regs->clk_gate.lcd_para_clk_en = 0; \
                                                         system_regs->misc.lcd_8080_apb_clk_en = 0;}while(0)

#define __SYSTEM_GPIO_CLK_ENABLE()                   do {system_regs->clk_gate.gpio_clk_en = 1; \
                                                         system_regs->misc.gpio_apb_clk_en = 1;}while(0)
#define __SYSTEM_GPIO_CLK_DISABLE()                  do {system_regs->clk_gate.gpio_clk_en = 0; \
                                                         system_regs->misc.gpio_apb_clk_en = 0;}while(0)

#define __SYSTEM_ADC_CLK_ENABLE()                    do {system_regs->clk_gate.auxadc_clk_en = 1; \
                                                         system_regs->misc.saradc_apb_clk_en = 1;}while(0)
#define __SYSTEM_ADC_CLK_DISABLE()                   do {system_regs->clk_gate.auxadc_clk_en = 0; \
                                                         system_regs->misc.saradc_apb_clk_en = 0;}while(0)

#define __SYSTEM_UART0_CLK_ENABLE()                  do {system_regs->clk_gate.uart0_clk_en     = 1; \
                                                         system_regs->misc.rich_uart_apb_clk_en = 1;}while(0)
#define __SYSTEM_UART0_CLK_DISABLE()                 do {system_regs->clk_gate.uart0_clk_en     = 0; \
                                                         system_regs->misc.rich_uart_apb_clk_en = 0;}while(0)

#define __SYSTEM_UART1_CLK_ENABLE()                     (system_regs->misc.tiny_uart_apb_clk_en = 1)
#define __SYSTEM_UART1_CLK_DISABLE()                    (system_regs->misc.tiny_uart_apb_clk_en = 0)

#define __SYSTEM_PWM_CLK_ENABLE()                       (system_regs->misc.pwm_apb_clk_en = 1)
#define __SYSTEM_PWM_CLK_DISABLE()                      (system_regs->misc.pwm_apb_clk_en = 0)

#define __SYSTEM_PDM_CLK_ENABLE()                    do {system_regs->clk_gate.pdm_clk_en = 1; \
                                                         system_regs->misc.pdm_apb_clk_en = 1;}while(0)
#define __SYSTEM_PDM_CLK_DISABLE()                   do {system_regs->clk_gate.pdm_clk_en = 0; \
                                                         system_regs->misc.pdm_apb_clk_en = 0;}while(0)

#define __SYSTEM_I2C0_CLK_ENABLE()                   do {system_regs->clk_gate.i2c0_clk_en     = 1; \
                                                         system_regs->misc.rich_i2c_apb_clk_en = 1;}while(0)
#define __SYSTEM_I2C0_CLK_DISABLE()                  do {system_regs->clk_gate.i2c0_clk_en     = 0; \
                                                         system_regs->misc.rich_i2c_apb_clk_en = 0;}while(0)

#define __SYSTEM_I2C1_CLK_ENABLE()                   do {system_regs->clk_gate.i2c1_clk_en     = 1; \
                                                         system_regs->misc.tiny_i2c_apb_clk_en = 1;}while(0)
#define __SYSTEM_I2C1_CLK_DISABLE()                  do {system_regs->clk_gate.i2c1_clk_en     = 0; \
                                                         system_regs->misc.tiny_i2c_apb_clk_en = 0;}while(0)

#define __SYSTEM_SPI0_MASTER_CLK_ENABLE()            do {system_regs->clk_gate.ssim0_clk_en = 1; \
                                                         system_regs->misc.ssim0_apb_clk_en = 1;}while(0)
#define __SYSTEM_SPI0_MASTER_CLK_DISABLE()           do {system_regs->clk_gate.ssim0_clk_en = 0; \
                                                         system_regs->misc.ssim0_apb_clk_en = 0;}while(0)

#define __SYSTEM_SPI1_MASTER_CLK_ENABLE()            do {system_regs->clk_gate.ssim1_clk_en = 1; \
                                                         system_regs->misc.ssim1_apb_clk_en = 1;}while(0)
#define __SYSTEM_SPI1_MASTER_CLK_DISABLE()           do {system_regs->clk_gate.ssim1_clk_en = 0; \
                                                         system_regs->misc.ssim1_apb_clk_en = 0;}while(0)

#define __SYSTEM_SPI_SLAVE_CLK_ENABLE()              do {system_regs->clk_gate.ssis_clk_en = 1; \
                                                         system_regs->misc.ssis_apb_clk_en = 1;}while(0)
#define __SYSTEM_SPI_SLAVE_CLK_DISABLE()             do {system_regs->clk_gate.ssis_clk_en = 0; \
                                                         system_regs->misc.ssis_apb_clk_en = 0;}while(0)

#define __SYSTEM_I2S_CLK_ENABLE()                    do {system_regs->clk_gate.i2s_clk_en = 1; \
                                                         system_regs->misc.i2s_apb_clk_en = 1;}while(0)
#define __SYSTEM_I2S_CLK_DISABLE()                   do {system_regs->clk_gate.i2s_clk_en = 0; \
                                                         system_regs->misc.i2s_apb_clk_en = 0;}while(0)

#define __SYSTEM_TIMER_CLK_ENABLE()                     (system_regs->misc.timer_apb_clk_en = 1)
#define __SYSTEM_TIMER_CLK_DISABLE()                    (system_regs->misc.timer_apb_clk_en = 0)

#define __SYSTEM_DMA_CLK_ENABLE()                       (system_regs->clk_gate.dma_clk_en = 1)
#define __SYSTEM_DMA_CLK_DISABLE()                      (system_regs->clk_gate.dma_clk_en = 0)

#define __SYSTEM_USB_CLK_ENABLE()                    do {system_regs->clk_gate.usb_hclk_en  = 1; \
                                                         system_regs->clk_gate.usb_48M_en   = 1; \
                                                         system_regs->clk_gate.usb_12M_en   = 1;}while(0)
#define __SYSTEM_USB_CLK_DISABLE()                   do {system_regs->clk_gate.usb_hclk_en  = 0; \
                                                         system_regs->clk_gate.usb_48M_en   = 0; \
                                                         system_regs->clk_gate.usb_12M_en   = 0;}while(0)

#define __SYSTEM_EFUSE_CLK_ENABLE()                  do {system_regs->clk_gate.efuse_clk_en = 1; \
                                                         system_regs->misc.efuse_apb_clk_en = 1;}while(0)
#define __SYSTEM_EFUSE_CLK_DISABLE()                 do {system_regs->clk_gate.efuse_clk_en = 0; \
                                                         system_regs->misc.efuse_apb_clk_en = 0;}while(0)

#define __SYSTEM_OUT_CLK_ENABLE()                       (system_regs->clk_gate.out_clk_en = 1)
#define __SYSTEM_OUT_CLK_DISABLE()                      (system_regs->clk_gate.out_clk_en = 0)

#define __SYSTEM_OUT_CLK_DIV(__DIV__)                   (system_regs->clk_cfg.out_clk_div = __DIV__)

/* peripheral reset */
#define __SYSTEM_RESET_SPI0_MASTER()                   (system_regs->rst.ssim0_rst = 1)
#define __SYSTEM_RESET_SPI1_MASTER()                   (system_regs->rst.ssim1_rst = 1)
#define __SYSTEM_RESET_SPI_SLAVE()                     (system_regs->rst.ssis_rst  = 1)
#define __SYSTEM_RESET_I2C0()                          (system_regs->rst.i2c0_rst  = 1)
#define __SYSTEM_RESET_I2C1()                          (system_regs->rst.i2c1_rst  = 1)
#define __SYSTEM_RESET_GPIO()                          (system_regs->rst.gpio_rst  = 1)
#define __SYSTEM_RESET_UART0()                         (system_regs->rst.uart0_rst = 1)
#define __SYSTEM_RESET_UART1()                         (system_regs->rst.uart1_rst = 1)
#define __SYSTEM_RESET_PWM()                           (system_regs->rst.pwm_rst   = 1)
#define __SYSTEM_RESET_ADC()                           (system_regs->rst.auxadc_rst   = 1)
#define __SYSTEM_RESET_PDM()                           (system_regs->rst.pdm_rst      = 1)
#define __SYSTEM_RESET_LCD()                           (system_regs->rst.lcd_para_rst = 1)
#define __SYSTEM_RESET_I2S()                           (system_regs->rst.i2s_rst      = 1)

/* DMA request ID */
#define __DMA_REQ_ID_UART0_RX(__REQ_ID__)              do {system_regs->dma_req[0] &=       ~(0xF << 0); \
                                                           system_regs->dma_req[0] |=  __REQ_ID__ << 0;}while(0)
#define __DMA_REQ_ID_UART0_TX(__REQ_ID__)              do {system_regs->dma_req[0] &=       ~(0xF << 4); \
                                                           system_regs->dma_req[0] |=  __REQ_ID__ << 4;}while(0)

#define __DMA_REQ_ID_UART1_RX(__REQ_ID__)              do {system_regs->dma_req[0] &=       ~(0xF << 8); \
                                                           system_regs->dma_req[0] |=  __REQ_ID__ << 8;}while(0)
#define __DMA_REQ_ID_UART1_TX(__REQ_ID__)              do {system_regs->dma_req[0] &=       ~(0xF << 12); \
                                                           system_regs->dma_req[0] |=  __REQ_ID__ << 12;}while(0)

#define __DMA_REQ_ID_SPI0_MASTER_RX(__REQ_ID__)        do {system_regs->dma_req[0] &=       ~(0xF << 16); \
                                                           system_regs->dma_req[0] |=  __REQ_ID__ << 16;}while(0)
#define __DMA_REQ_ID_SPI0_MASTER_TX(__REQ_ID__)        do {system_regs->dma_req[0] &=       ~(0xF << 20); \
                                                           system_regs->dma_req[0] |=  __REQ_ID__ << 20;}while(0)

#define __DMA_REQ_ID_SPI1_MASTER_RX(__REQ_ID__)        do {system_regs->dma_req[0] &=       ~(0xF << 24); \
                                                           system_regs->dma_req[0] |=  __REQ_ID__ << 24;}while(0)
#define __DMA_REQ_ID_SPI1_MASTER_TX(__REQ_ID__)        do {system_regs->dma_req[0] &=       ~(0xFul << 28); \
                                                           system_regs->dma_req[0] |=  __REQ_ID__##ul << 28;}while(0)

#define __DMA_REQ_ID_I2C0_RX(__REQ_ID__)               do {system_regs->dma_req[1] &=       ~(0xF << 0); \
                                                           system_regs->dma_req[1] |=  __REQ_ID__ << 0;}while(0)
#define __DMA_REQ_ID_I2C0_TX(__REQ_ID__)               do {system_regs->dma_req[1] &=       ~(0xF << 4); \
                                                           system_regs->dma_req[1] |=  __REQ_ID__ << 4;}while(0)

#define __DMA_REQ_ID_I2C1_RX(__REQ_ID__)               do {system_regs->dma_req[1] &=       ~(0xF << 8); \
                                                           system_regs->dma_req[1] |=  __REQ_ID__ << 8;}while(0)
#define __DMA_REQ_ID_I2C1_TX(__REQ_ID__)               do {system_regs->dma_req[1] &=       ~(0xF << 12); \
                                                           system_regs->dma_req[1] |=  __REQ_ID__ << 12;}while(0)

#define __DMA_REQ_ID_SPI_SLAVE_RX(__REQ_ID__)          do {system_regs->dma_req[1] &=       ~(0xF << 16); \
                                                           system_regs->dma_req[1] |=  __REQ_ID__ << 16;}while(0)
#define __DMA_REQ_ID_SPI_SLAVE_TX(__REQ_ID__)          do {system_regs->dma_req[1] &=       ~(0xF << 20); \
                                                           system_regs->dma_req[1] |=  __REQ_ID__ << 20;}while(0)

#define __DMA_REQ_ID_ADC(__REQ_ID__)                   do {system_regs->dma_req[1] &=       ~(0xF << 24); \
                                                           system_regs->dma_req[1] |=  __REQ_ID__ << 24;}while(0)

#define __DMA_REQ_ID_PDM(__REQ_ID__)                   do {system_regs->dma_req[1] &=       ~(0xFul << 28); \
                                                           system_regs->dma_req[1] |=  __REQ_ID__##ul << 28;}while(0)

#define __DMA_REQ_ID_I2S_RX(__REQ_ID__)                do {system_regs->dma_req[2] &=       ~(0xF << 8); \
                                                           system_regs->dma_req[2] |=  __REQ_ID__ << 8;}while(0)
#define __DMA_REQ_ID_I2S_TX(__REQ_ID__)                do {system_regs->dma_req[2] &=       ~(0xF << 12); \
                                                           system_regs->dma_req[2] |=  __REQ_ID__ << 12;}while(0)




/*********************************************************************
 * @fn      system_sleep_enable
 *
 * @brief   enable system enter deep sleep mode when all conditions are satisfied.
 */
void system_sleep_enable(void);

/*********************************************************************
 * @fn      system_sleep_disable
 *
 * @brief   disable system enter deep sleep mode.
 */
void system_sleep_disable(void);

/*********************************************************************
 * @fn      system_get_curr_time
 *
 * @brief   get how many milliseconds have passed after system start-up,
 *          and the value will loop back to 0 after reaching 83886079(0x4FFFFFF).
 */
uint32_t system_get_curr_time(void);

/*********************************************************************
 * @fn      system_latency_enable
 *
 * @brief   reenable latency of connection indicated by conidx.
 *
 * @param   conidx  - connection index, 0xff means latency of all connections
 *                    should be reenabled.
 *
 * @return  None.
 */
void system_latency_enable(uint8_t conidx);

/*********************************************************************
 * @fn      system_latency_disable
 *
 * @brief   disable latency of connection indicated by conidx.
 *
 * @param   conidx  - connection index, 0xff means latency of all connections
 *                    should be disabled.
 *
 * @return  None.
 */
void system_latency_disable(uint8_t conidx);

/*********************************************************************
 * @fn      system_get_unique_ID
 *
 * @brief   get chip 6-byte unique ID.
 */
void system_get_unique_ID(uint8_t *ID_Buffer);
 
void system_set_port_pull(uint32_t port_sel, enum system_port_pull_t pull, bool en);
void system_osc_doubler_calibration(void);

/*********************************************************************
 * @fn      system_set_internal_flash_clock_div
 *
 * @brief   set internal flash clock divider
 * 
 * @param   div: 0=/2; 1=/4; 2=/6; 3=/8; 4=/10; 5=/12; 6=/14; 7=/16; 8=/18
 */
void system_set_internal_flash_clock_div(uint8_t div);

/*********************************************************************
 * @fn      system_enable_internal_flash_q_read
 *
 * @brief   set internal flash Quad Enable.
 * 
 * @param   opcode: 0x01 = Write Status Register command use 0x01.
 * @param   opcode: 0x31 = Write Status Register command use 0x31.
 */
void system_enable_internal_flash_q_read(uint8_t opcode);

void system_power_off(void);
void system_set_tx_power(enum rf_tx_power_t tx_power);
void system_init(void);


#endif  //_DRIVER_SYSTEM_H

