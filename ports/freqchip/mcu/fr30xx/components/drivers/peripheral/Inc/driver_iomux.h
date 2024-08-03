/**
 * Copyright (c) 2019, Freqchip
 *
 * All rights reserved.
 *
 *
 */
#ifndef DRIVER_IOMUX_H
#define DRIVER_IOMUX_H

/**********************************************************************************************************************************
PX/MUX   4'h0        4'h1         4'h2        4'h3    4'h4         4'h5         4'h6         4'h7       4'h8        4'ha
PORTA0   gpio_a0     I2C0_CLK     I2S_CLK     PWM0    SSP0_CLK     UART0_RXD    UART1_RXD    CLK_OUT    PDM_CLK
PORTA1   gpio_a1     I2C0_DAT     I2S_FRM     PWM1    SSP0_CSN     UART0_TXD    UART1_TXD    ant_ctl[0] PDM_DATA
PORTA2   gpio_a2     I2C1_CLK     I2S_DOUT    PWM2    SSP0_DOUT    UART0_RXD    UART1_RXD    ant_ctl[0] PDM_CLK
PORTA3   gpio_a3     I2C1_DAT     I2S_DIN     PWM3    SSP0_DIN     UART0_TXD    UART1_TXD    ant_ctl[1] PDM_DATA
PORTA4   gpio_a4     I2C0_CLK     I2S_CLK     PWM4    SSP0_CLK     UART0_RXD    UART1_RXD    CLK_OUT    PDM_CLK
PORTA5   gpio_a5     I2C0_DAT     I2S_FRM     PWM5    SSP0_CSN     UART0_TXD    UART1_TXD    ant_ctl[1] PDM_DATA
PORTA6   gpio_a6     I2C1_CLK     I2S_DOUT    PWM0    SSP0_DOUT    UART0_RXD    UART1_RXD    CLK_OUT    PDM_CLK
PORTA7   gpio_a7     I2C1_DAT     I2S_DIN     PWM1    SSP0_DIN     UART0_TXD    UART1_TXD    ant_ctl[0] PDM_DATA

PORTB0   gpio_b0     I2C0_CLK     I2S_CLK     PWM0    SSP0_CLK     UART0_RXD    UART1_RXD    ble_tx     PDM_CLK
PORTB1   gpio_b1     I2C0_DAT     I2S_FRM     PWM1    SSP0_CSN     UART0_TXD    UART1_TXD    ble_rx     PDM_DATA
PORTB2   gpio_b2     I2C1_CLK     I2S_DOUT    PWM2    SSP0_DOUT    UART0_RXD    UART1_RXD    wlan_tx/in PDM_CLK
PORTB3   gpio_b3     I2C1_DAT     I2S_DIN     PWM3    SSP0_DIN     UART0_TXD    UART1_TXD    wlan_rx/in PDM_DATA
PORTB4   gpio_b4     I2C0_CLK     I2S_CLK     PWM4    SSP0_CLK     UART0_RXD    UART1_RXD    CLK_OUT    PDM_CLK
PORTB5   gpio_b5     I2C0_DAT     I2S_FRM     PWM5    SSP0_CSN     UART0_TXD    UART1_TXD    ant_ctl[0] PDM_DATA
PORTB6   gpio_b6     I2C1_CLK     I2S_DOUT    PWM2    SSP0_DOUT    UART0_RXD    UART1_RXD    ant_ctl[1] PDM_CLK
PORTB7   gpio_b7     I2C1_DAT     I2S_DIN     PWM3    SSP0_DIN     UART0_TXD    UART1_TXD    CLK_OUT    PDM_DATA

PORTC0   gpio_c0     I2C0_CLK     I2S_CLK     PWM0    SSP0_CLK     UART0_RXD    UART1_RXD    SWV        PDM_CLK
PORTC1   gpio_c1     I2C0_DAT     I2S_FRM     PWM1    SSP0_CSN     UART0_TXD    UART1_TXD    SWV        PDM_DATA
PORTC2   gpio_c2     I2C1_CLK     I2S_DOUT    PWM2    SSP0_DOUT    UART0_RXD    UART1_RXD    SWV        PDM_CLK
PORTC3   gpio_c3     I2C1_DAT     I2S_DIN     PWM3    SSP0_DIN     UART0_TXD    UART1_TXD    SWV        PDM_DATA
PORTC4   gpio_c4     I2C0_CLK     I2S_CLK     PWM4    SSP0_CLK     UART0_RXD    UART1_RXD    ant_ctl[1] PDM_CLK
PORTC5   gpio_c5     I2C0_DAT     I2S_FRM     PWM5    SSP0_CSN     UART0_TXD    UART1_TXD    SWV        PDM_DATA
PORTC6   gpio_c6     I2C1_CLK     I2S_DOUT    PWM4    SSP0_DOUT    UART0_RXD    UART1_RXD    SW_TCK     PDM_CLK
PORTC7   gpio_c7     I2C1_DAT     I2S_DIN     PWM5    SSP0_DIN     UART0_TXD    UART1_TXD    SW_DIO     PDM_DATA

PORTD0   gpio_d0     I2C0_CLK     I2S_CLK     PWM0    SSP0_CLK     UART0_RXD    UART1_RXD    ble_tx     PDM_CLK
PORTD1   gpio_d1     I2C0_DAT     I2S_FRM     PWM1    SSP0_CSN     UART0_TXD    UART1_TXD    ble_rx     PDM_DATA
PORTD2   gpio_d2     I2C1_CLK     I2S_DOUT    PWM2    SSP0_DOUT    UART0_RXD    UART1_RXD    wlan_tx/in PDM_CLK
PORTD3   gpio_d3     I2C1_DAT     I2S_DIN     PWM3    SSP0_DIN     UART0_TXD    UART1_TXD    wlan_rx/in PDM_DATA
PORTD4   gpio_d4     I2C0_CLK     I2S_CLK     PWM4    SSP0_CLK     UART0_RXD    UART1_RXD    ant_ctl[0] PDM_CLK     ADC0
PORTD5   gpio_d5     I2C0_DAT     I2S_FRM     PWM5    SSP0_CSN     UART0_TXD    UART1_TXD    ant_ctl[0] PDM_DATA    ADC1
PORTD6   gpio_d6     I2C1_CLK     I2S_DOUT    PWM0    SSP0_DOUT    UART0_RXD    UART1_RXD    CLK_OUT    PDM_CLK     ADC2
PORTD7   gpio_d7     I2C1_DAT     I2S_DIN     PWM1    SSP0_DIN     UART0_TXD    UART1_TXD    ant_ctl[1] PDM_DATA    ADC3

*************************************************************************************************************************************/
#if 1
#define PORTA0_FUNC_A0              0x00
#define PORTA0_FUNC_CM0_A0        0x01
#define PORTA0_FUNC_CM0_UART_RXD         0x02
#define PORTA0_FUNC_UART0_RXD            0x03
#define PORTA0_FUNC_SPIM0_CLK        0x04
#define PORTA0_FUNC_SPIS0_CLK       0x05
#define PORTA0_FUNC_PDM0_CLK       0x06
#define PORTA0_FUNC_I2C0_CLK         0x07
#define PORTA0_FUNC_PWM0         0x08
#define PORTA0_FUNC_TIM0_PAUSE         0x09

#define PORTA1_FUNC_A1              0x00
#define PORTA1_FUNC_CM0_A1        0x01
#define PORTA1_FUNC_CM0_UART_TXD         0x02
#define PORTA1_FUNC_UART0_TXD            0x03
#define PORTA1_FUNC_SPIM0_CSN        0x04
#define PORTA1_FUNC_SPIS0_CSN       0x05
#define PORTA1_FUNC_PDM0_SDA       0x06
#define PORTA1_FUNC_I2C0_SDA         0x07
#define PORTA1_FUNC_PWM1         0x08
#define PORTA1_FUNC_TIM1_PAUSE         0x09

#define PORTA2_FUNC_A2              0x00
#define PORTA2_FUNC_CM0_A2        0x01
#define PORTA2_FUNC_CM0_I2C_CLK         0x02
#define PORTA2_FUNC_UART2_RXD            0x03
#define PORTA2_FUNC_SPIM0_MOSI        0x04
#define PORTA2_FUNC_SPIS0_MOSI       0x05
#define PORTA2_FUNC_PDM1_CLK       0x06
#define PORTA2_FUNC_I2C1_CLK         0x07
#define PORTA2_FUNC_PWM2         0x08
#define PORTA2_FUNC_TIM0_TOG         0x09
#define PORTA2_FUNC_SPIM8_0_IO0         0x0A

#define PORTA3_FUNC_A3              0x00
#define PORTA3_FUNC_CM0_A3        0x01
#define PORTA3_FUNC_CM0_I2C_SDA         0x02
#define PORTA3_FUNC_UART2_TXD            0x03
#define PORTA3_FUNC_SPIM0_MISO        0x04
#define PORTA3_FUNC_SPIS0_MISO       0x05
#define PORTA3_FUNC_PDM1_SDA       0x06
#define PORTA3_FUNC_I2C1_SDA         0x07
#define PORTA3_FUNC_PWM3         0x08
#define PORTA3_FUNC_TIM1_TOG         0x09
#define PORTA3_FUNC_SPIM8_0_IO1         0x0A

#define PORTA4_FUNC_A4              0x00
#define PORTA4_FUNC_CM0_A0        0x01
#define PORTA4_FUNC_CM0_SPI_CLK         0x02
#define PORTA4_FUNC_UART2_CTS            0x03
#define PORTA4_FUNC_SPIM1_CLK        0x04
#define PORTA4_FUNC_SPIS1_CLK       0x05
#define PORTA4_FUNC_PDM0_CLK       0x06
#define PORTA4_FUNC_I2C0_CLK         0x07
#define PORTA4_FUNC_PWM4         0x08
#define PORTA4_FUNC_TIM0_PAUSE         0x09
#define PORTA4_FUNC_SPIM8_0_IO2         0x0A

#define PORTA5_FUNC_A5              0x00
#define PORTA5_FUNC_CM0_A1        0x01
#define PORTA5_FUNC_CM0_SPI_CSN         0x02
#define PORTA5_FUNC_UART2_RTS            0x03
#define PORTA5_FUNC_SPIM1_CSN        0x04
#define PORTA5_FUNC_SPIS1_FRM       0x05
#define PORTA5_FUNC_PDM0_SDA       0x06
#define PORTA5_FUNC_I2C0_SDA         0x07
#define PORTA5_FUNC_PWM5         0x08
#define PORTA5_FUNC_TIM1_PAUSE         0x09
#define PORTA5_FUNC_SPIM8_0_IO3         0x0A

#define PORTA6_FUNC_A6              0x00
#define PORTA6_FUNC_CM0_A2        0x01
#define PORTA6_FUNC_CM0_SPI_MOSI         0x02
#define PORTA6_FUNC_UART0_RXD            0x03
#define PORTA6_FUNC_SPIM1_MOSI        0x04
#define PORTA6_FUNC_SPIS1_MOSI       0x05
#define PORTA6_FUNC_PDM1_CLK       0x06
#define PORTA6_FUNC_I2C1_CLK         0x07
#define PORTA6_FUNC_PWM6         0x08
#define PORTA6_FUNC_TIM0_TOG         0x09
#define PORTA6_FUNC_SPIM8_0_CLK         0x0A

#define PORTA7_FUNC_A7              0x00
#define PORTA7_FUNC_CM0_A3        0x01
#define PORTA7_FUNC_CM0_SPI_MIS0         0x02
#define PORTA7_FUNC_UART0_TXD            0x03
#define PORTA7_FUNC_SPIM1_MISO        0x04
#define PORTA7_FUNC_SPIS1_MISO       0x05
#define PORTA7_FUNC_PDM1_SDA       0x06
#define PORTA7_FUNC_I2C1_SDA         0x07
#define PORTA7_FUNC_PWM7         0x08
#define PORTA7_FUNC_TIM1_TOG         0x09
#define PORTA7_FUNC_SPIM8_0_CSN         0x0A

#define PORTB0_FUNC_B0              0x00
#define PORTB0_FUNC_CM0_A0        0x01
#define PORTB0_FUNC_CM0_UART_RXD         0x02
#define PORTB0_FUNC_UART0_RXD            0x03
#define PORTB0_FUNC_SPIM1_CLK        0x04
#define PORTB0_FUNC_SPIS1_CLK       0x05
#define PORTB0_FUNC_PDM0_CLK       0x06
#define PORTB0_FUNC_I2C0_CLK         0x07
#define PORTB0_FUNC_PWM0         0x08
#define PORTB0_FUNC_TIM0_PAUSE         0x09
#define PORTB0_FUNC_SPIM8_0_IO0         0x0A
#define PORTB0_FUNC_PSRAM_QSPI_MIO0         0x0B

#define PORTB1_FUNC_B1              0x00
#define PORTB1_FUNC_CM0_A1        0x01
#define PORTB1_FUNC_CM0_UART_TXD         0x02
#define PORTB1_FUNC_UART0_TXD            0x03
#define PORTB1_FUNC_SPIM1_CSN        0x04
#define PORTB1_FUNC_SPIS1_FRM       0x05
#define PORTB1_FUNC_PDM0_SDA       0x06
#define PORTB1_FUNC_I2C0_SDA         0x07
#define PORTB1_FUNC_PWM1         0x08
#define PORTB1_FUNC_TIM1_PAUSE         0x09
#define PORTB1_FUNC_SPIM8_0_IO1         0x0A
#define PORTB1_FUNC_PSRAM_QSPI_MIO1         0x0B

#define PORTB2_FUNC_B2              0x00
#define PORTB2_FUNC_CM0_A2        0x01
#define PORTB2_FUNC_CM0_I2C_CLK         0x02
#define PORTB2_FUNC_UART2_RXD            0x03
#define PORTB2_FUNC_SPIM1_MOSI        0x04
#define PORTB2_FUNC_SPIS1_MOSI       0x05
#define PORTB2_FUNC_PDM1_CLK       0x06
#define PORTB2_FUNC_I2C1_CLK         0x07
#define PORTB2_FUNC_PWM2         0x08
#define PORTB2_FUNC_TIM0_TOG         0x09
#define PORTB2_FUNC_SPIM8_0_IO2         0x0A
#define PORTB2_FUNC_PSRAM_QSPI_MIO2         0x0B

#define PORTB3_FUNC_B3              0x00
#define PORTB3_FUNC_CM0_A3        0x01
#define PORTB3_FUNC_CM0_I2C_SDA         0x02
#define PORTB3_FUNC_UART2_TXD            0x03
#define PORTB3_FUNC_SPIM1_MISO        0x04
#define PORTB3_FUNC_SPIS1_MISO       0x05
#define PORTB3_FUNC_PDM1_SDA       0x06
#define PORTB3_FUNC_I2C1_SDA         0x07
#define PORTB3_FUNC_PWM3         0x08
#define PORTB3_FUNC_TIM1_TOG         0x09
#define PORTB3_FUNC_SPIM8_0_IO3         0x0A
#define PORTB3_FUNC_PSRAM_QSPI_MIO3         0x0B

#define PORTB4_FUNC_B4              0x00
#define PORTB4_FUNC_CM0_A0        0x01
#define PORTB4_FUNC_CM0_SPI_CLK         0x02
#define PORTB4_FUNC_UART2_CTS            0x03
#define PORTB4_FUNC_SPIM0_CLK        0x04
#define PORTB4_FUNC_SPIS0_CLK       0x05
#define PORTB4_FUNC_PDM0_CLK       0x06
#define PORTB4_FUNC_I2C0_CLK         0x07
#define PORTB4_FUNC_PWM4         0x08
#define PORTB4_FUNC_TIM1_PAUSE         0x09
#define PORTB4_FUNC_SPIM8_0_IO4         0x0A
#define PORTB4_FUNC_PSRAM_QSPI_MIO4         0x0B

#define PORTB5_FUNC_B5              0x00
#define PORTB5_FUNC_CM0_A1        0x01
#define PORTB5_FUNC_CM0_SPI_CSN         0x02
#define PORTB5_FUNC_UART2_RTS            0x03
#define PORTB5_FUNC_SPIM0_CSN       0x04
#define PORTB5_FUNC_SPIS0_CSN       0x05
#define PORTB5_FUNC_PDM0_SDA       0x06
#define PORTB5_FUNC_I2C0_SDA         0x07
#define PORTB5_FUNC_PWM5         0x08
#define PORTB5_FUNC_TIM1_PAUSE         0x09
#define PORTB5_FUNC_SPIM8_0_IO5         0x0A
#define PORTB5_FUNC_PSRAM_QSPI_MIO5         0x0B

#define PORTB6_FUNC_B6              0x00
#define PORTB6_FUNC_CM0_A2        0x01
#define PORTB6_FUNC_CM0_SPI_MOSI         0x02
#define PORTB6_FUNC_UART0_RXD            0x03
#define PORTB6_FUNC_SPIM0_MOSI       0x04
#define PORTB6_FUNC_SPIS0_MOSI       0x05
#define PORTB6_FUNC_PDM1_CLK       0x06
#define PORTB6_FUNC_I2C1_CLK         0x07
#define PORTB6_FUNC_PWM6         0x08
#define PORTB6_FUNC_TIM0_TOG         0x09
#define PORTB6_FUNC_SPIM8_0_IO6         0x0A
#define PORTB6_FUNC_PSRAM_QSPI_MIO6         0x0B

#define PORTB7_FUNC_B7              0x00
#define PORTB7_FUNC_CM0_A3        0x01
#define PORTB7_FUNC_CM0_SPI_MISO         0x02
#define PORTB7_FUNC_UART0_TXD            0x03
#define PORTB7_FUNC_SPIM0_MISO       0x04
#define PORTB7_FUNC_SPIS0_MISO       0x05
#define PORTB7_FUNC_PDM1_SDA       0x06
#define PORTB7_FUNC_I2C1_SDA         0x07
#define PORTB7_FUNC_PWM7         0x08
#define PORTB7_FUNC_TIM1_TOG         0x09
#define PORTB7_FUNC_SPIM8_0_IO7         0x0A
#define PORTB7_FUNC_PSRAM_QSPI_MIO7         0x0B

#define PORTC0_FUNC_C0              0x00
#define PORTC0_FUNC_CM0_A0        0x01
#define PORTC0_FUNC_CM0_SWCK         0x02
#define PORTC0_FUNC_UART0_RXD            0x03
#define PORTC0_FUNC_SPIM0_CLK       0x04
#define PORTC0_FUNC_SPIS0_CLK       0x05
#define PORTC0_FUNC_PDM0_CLK       0x06
#define PORTC0_FUNC_I2C0_CLK         0x07
#define PORTC0_FUNC_PWM0         0x08
#define PORTC0_FUNC_TIM0_PAUSE         0x09
#define PORTC0_FUNC_SPIM8_0_CLK         0x0A
#define PORTC0_FUNC_PSRAM_QSPI_CLK         0x0B

#define PORTC1_FUNC_C1              0x00
#define PORTC1_FUNC_CM0_A1        0x01
#define PORTC1_FUNC_CM0_SWIO         0x02
#define PORTC1_FUNC_UART0_TXD            0x03
#define PORTC1_FUNC_SPIM0_CSN       0x04
#define PORTC1_FUNC_SPIS0_CSN       0x05
#define PORTC1_FUNC_PDM0_SDA       0x06
#define PORTC1_FUNC_I2C0_SDA         0x07
#define PORTC1_FUNC_PWM1         0x08
#define PORTC1_FUNC_TIM1_PAUSE         0x09
#define PORTC1_FUNC_SPIM8_0_CSN         0x0A
#define PORTC1_FUNC_PSRAM_QSPI_N_SS         0x0B

#define PORTC2_FUNC_C2              0x00
#define PORTC2_FUNC_CM0_A2        0x01
#define PORTC2_FUNC_CM0_SWCK         0x02
#define PORTC2_FUNC_UART2_RXD            0x03
#define PORTC2_FUNC_SPIM0_MOSI       0x04
#define PORTC2_FUNC_SPIS0_MOSI       0x05
#define PORTC2_FUNC_PDM1_CLK       0x06
#define PORTC2_FUNC_I2C1_CLK         0x07
#define PORTC2_FUNC_PWM2         0x08
#define PORTC2_FUNC_TIM0_TOG         0x09
#define PORTC2_FUNC_SPIM8_0_IO0         0x0A
#define PORTC2_FUNC_PSRAM_QSPI_MIO0         0x0B

#define PORTC3_FUNC_C3              0x00
#define PORTC3_FUNC_CM0_A3        0x01
#define PORTC3_FUNC_CM0_SWIO         0x02
#define PORTC3_FUNC_UART2_TXD            0x03
#define PORTC3_FUNC_SPIM0_MISO       0x04
#define PORTC3_FUNC_SPIS0_MISO       0x05
#define PORTC3_FUNC_PDM1_SDA       0x06
#define PORTC3_FUNC_I2C1_SDA         0x07
#define PORTC3_FUNC_PWM3         0x08
#define PORTC3_FUNC_TIM1_TOG         0x09
#define PORTC3_FUNC_SPIM8_0_IO1         0x0A
#define PORTC3_FUNC_PSRAM_QSPI_MIO1         0x0B

#define PORTC4_FUNC_C4              0x00
#define PORTC4_FUNC_CM0_A0        0x01
#define PORTC4_FUNC_CM33_1_SWCK         0x02
#define PORTC4_FUNC_UART2_CTS            0x03
#define PORTC4_FUNC_SPIM1_CLK       0x04
#define PORTC4_FUNC_SPIS1_CLK       0x05
#define PORTC4_FUNC_PDM0_CLK       0x06
#define PORTC4_FUNC_I2C0_CLK         0x07
#define PORTC4_FUNC_PWM4         0x08
#define PORTC4_FUNC_TIM0_PAUSE         0x09
#define PORTC4_FUNC_SPIM8_0_IO2         0x0A
#define PORTC4_FUNC_PSRAM_QSPI_MIO2         0x0B

#define PORTC5_FUNC_C5              0x00
#define PORTC5_FUNC_CM0_A1        0x01
#define PORTC5_FUNC_CM33_1_SWIO         0x02
#define PORTC5_FUNC_UART2_RTS            0x03
#define PORTC5_FUNC_SPIM1_CSN       0x04
#define PORTC5_FUNC_SPIS1_FRM       0x05
#define PORTC5_FUNC_PDM0_SDA       0x06
#define PORTC5_FUNC_I2C0_SDA         0x07
#define PORTC5_FUNC_PWM5         0x08
#define PORTC5_FUNC_TIM1_PAUSE         0x09
#define PORTC5_FUNC_SPIM8_0_IO3         0x0A
#define PORTC5_FUNC_PSRAM_QSPI_MIO3         0x0B

#define PORTC6_FUNC_C6              0x00
#define PORTC6_FUNC_CM0_A2        0x01
#define PORTC6_FUNC_CM33_0_SWCK         0x02
#define PORTC6_FUNC_UART0_RXD            0x03
#define PORTC6_FUNC_SPIM1_MOSI       0x04
#define PORTC6_FUNC_SPIS1_MOSI       0x05
#define PORTC6_FUNC_PDM1_CLK       0x06
#define PORTC6_FUNC_I2C1_CLK         0x07
#define PORTC6_FUNC_PWM6         0x08
#define PORTC6_FUNC_TIM0_TOG         0x09
#define PORTC6_FUNC_SPIM8_0_CLK         0x0A
#define PORTC6_FUNC_PSRAM_QSPI_CLK         0x0B

#define PORTC7_FUNC_C7              0x00
#define PORTC7_FUNC_CM0_A3        0x01
#define PORTC7_FUNC_CM33_0_SWIO         0x02
#define PORTC7_FUNC_UART0_TXD            0x03
#define PORTC7_FUNC_SPIM1_MISO       0x04
#define PORTC7_FUNC_SPIS1_MISO       0x05
#define PORTC7_FUNC_PDM1_SDA       0x06
#define PORTC7_FUNC_I2C1_SDA         0x07
#define PORTC7_FUNC_PWM7         0x08
#define PORTC7_FUNC_TIM1_TOG         0x09
#define PORTC7_FUNC_SPIM8_0_CSN        0x0A
#define PORTC7_FUNC_PSRAM_QSPI_N_SS         0x0B

#define PORTD0_FUNC_D0              0x00
#define PORTD0_FUNC_CM0_A0        0x01
#define PORTD0_FUNC_CM0_UART_RXD         0x02
#define PORTD0_FUNC_UART0_RXD            0x03
#define PORTD0_FUNC_SPIM1_CLK       0x04
#define PORTD0_FUNC_SPIS1_CLK       0x05
#define PORTD0_FUNC_PDM0_CLK       0x06
#define PORTD0_FUNC_I2C0_CLK         0x07
#define PORTD0_FUNC_PWM0         0x08
#define PORTD0_FUNC_TIM0_PAUSE         0x09
#define PORTD0_FUNC_SPIM8_0_IO4        0x0A
#define PORTD0_FUNC_PSRAM_QSPI_MIO0         0x0B

#define PORTD1_FUNC_D1              0x00
#define PORTD1_FUNC_CM0_A1        0x01
#define PORTD1_FUNC_CM0_UART_TXD         0x02
#define PORTD1_FUNC_UART0_TXD            0x03
#define PORTD1_FUNC_SPIM1_CSN       0x04
#define PORTD1_FUNC_SPIS1_FRM       0x05
#define PORTD1_FUNC_PDM0_SDA       0x06
#define PORTD1_FUNC_I2C0_SDA         0x07
#define PORTD1_FUNC_PWM1         0x08
#define PORTD1_FUNC_TIM1_PAUSE         0x09
#define PORTD1_FUNC_SPIM8_0_IO5        0x0A
#define PORTD1_FUNC_PSRAM_QSPI_MIO1        0x0B

#define PORTD2_FUNC_D2              0x00
#define PORTD2_FUNC_CM0_A2        0x01
#define PORTD2_FUNC_CM0_I2C_CLK         0x02
#define PORTD2_FUNC_UART2_RXD            0x03
#define PORTD2_FUNC_SPIM1_MOSI       0x04
#define PORTD2_FUNC_SPIS1_MOSI       0x05
#define PORTD2_FUNC_PDM1_CLK       0x06
#define PORTD2_FUNC_I2C1_CLK         0x07
#define PORTD2_FUNC_PWM2         0x08
#define PORTD2_FUNC_TIM0_TOG         0x09
#define PORTD2_FUNC_SPIM8_0_IO6        0x0A
#define PORTD2_FUNC_PSRAM_QSPI_MIO2        0x0B

#define PORTD3_FUNC_D3              0x00
#define PORTD3_FUNC_CM0_A3        0x01
#define PORTD3_FUNC_CM0_I2C_SDA         0x02
#define PORTD3_FUNC_UART2_TXD            0x03
#define PORTD3_FUNC_SPIM1_MISO       0x04
#define PORTD3_FUNC_SPIS1_MISO       0x05
#define PORTD3_FUNC_PDM1_SDA       0x06
#define PORTD3_FUNC_I2C1_SDA         0x07
#define PORTD3_FUNC_PWM3         0x08
#define PORTD3_FUNC_TIM1_TOG         0x09
#define PORTD3_FUNC_SPIM8_0_IO7        0x0A
#define PORTD3_FUNC_PSRAM_QSPI_MIO3        0x0B

#define PORTD4_FUNC_D4              0x00
#define PORTD4_FUNC_CM0_A0        0x01
#define PORTD4_FUNC_CM0_SPI_CLK         0x02
#define PORTD4_FUNC_UART2_CTS            0x03
#define PORTD4_FUNC_SPIM0_CLK       0x04
#define PORTD4_FUNC_SPIS0_CLK       0x05
#define PORTD4_FUNC_PDM0_CLK       0x06
#define PORTD4_FUNC_I2C2_CLK         0x07
#define PORTD4_FUNC_PWM4         0x08
#define PORTD4_FUNC_TIM0_PAUSE         0x09
#define PORTD4_FUNC_PSRAM_QSPI_MIO4        0x0B

#define PORTD5_FUNC_D5              0x00
#define PORTD5_FUNC_CM0_A1        0x01
#define PORTD5_FUNC_CM0_SPI_CSN         0x02
#define PORTD5_FUNC_UART2_RTS            0x03
#define PORTD5_FUNC_SPIM0_CSN       0x04
#define PORTD5_FUNC_SPIS0_CSN       0x05
#define PORTD5_FUNC_PDM0_SDA       0x06
#define PORTD5_FUNC_I2C2_SDA         0x07
#define PORTD5_FUNC_PWM5         0x08
#define PORTD5_FUNC_TIM1_PAUSE         0x09
#define PORTD5_FUNC_PSRAM_QSPI_MIO5        0x0B

#define PORTD6_FUNC_D6              0x00
#define PORTD6_FUNC_CM0_A2        0x01
#define PORTD6_FUNC_CM0_SPI_MOSI         0x02
#define PORTD6_FUNC_UART0_RXD            0x03
#define PORTD6_FUNC_SPIM0_MOSI       0x04
#define PORTD6_FUNC_SPIS0_MOSI       0x05
#define PORTD6_FUNC_PDM1_CLK       0x06
#define PORTD6_FUNC_I2C3_CLK         0x07
#define PORTD6_FUNC_PWM6         0x08
#define PORTD6_FUNC_TIM0_TOG         0x09
#define PORTD6_FUNC_PSRAM_QSPI_MIO6        0x0B

#define PORTD7_FUNC_D7              0x00
#define PORTD7_FUNC_CM0_A3        0x01
#define PORTD7_FUNC_CM0_SPI_MISO         0x02
#define PORTD7_FUNC_UART0_TXD            0x03
#define PORTD7_FUNC_SPIM0_MISO       0x04
#define PORTD7_FUNC_SPIS0_MISO       0x05
#define PORTD7_FUNC_PDM1_SDA       0x06
#define PORTD7_FUNC_I2C3_SDA         0x07
#define PORTD7_FUNC_PWM7         0x08
#define PORTD7_FUNC_TIM1_TOG         0x09
#define PORTD7_FUNC_PSRAM_QSPI_MIO7        0x0B

#define PORTE0_FUNC_E0              0x00
#define PORTE0_FUNC_CM0_A4        0x01
#define PORTE0_FUNC_CM1_UART_RXD         0x02
#define PORTE0_FUNC_UART1_RXD            0x03
#define PORTE0_FUNC_SPIM2_CLK       0x04
#define PORTE0_FUNC_SPIS0_CLK       0x05
#define PORTE0_FUNC_PDM2_CLK       0x06
#define PORTE0_FUNC_I2C2_CLK         0x07
#define PORTE0_FUNC_PWM8         0x08
#define PORTE0_FUNC_TIM2_PAUSE         0x09
#define PORTE0_FUNC_SPIM8_1_IO0        0x0A

#define PORTE1_FUNC_E1              0x00
#define PORTE1_FUNC_CM0_A5        0x01
#define PORTE1_FUNC_CM1_UART_TXD         0x02
#define PORTE1_FUNC_UART1_TXD            0x03
#define PORTE1_FUNC_SPIM2_CSN       0x04
#define PORTE1_FUNC_SPIS0_CSN       0x05
#define PORTE1_FUNC_PDM2_SDA       0x06
#define PORTE1_FUNC_I2C2_SDA         0x07
#define PORTE1_FUNC_PWM9         0x08
#define PORTE1_FUNC_TIM3_PAUSE         0x09
#define PORTE1_FUNC_SPIM8_1_IO1        0x0A

#define PORTE2_FUNC_E2              0x00
#define PORTE2_FUNC_CM0_A6        0x01
#define PORTE2_FUNC_CM1_UART_RXD         0x02
#define PORTE2_FUNC_UART3_RXD            0x03
#define PORTE2_FUNC_SPIM2_MOSI       0x04
#define PORTE2_FUNC_SPIS0_MOSI       0x05
#define PORTE2_FUNC_PDM3_CLK       0x06
#define PORTE2_FUNC_I2C3_CLK         0x07
#define PORTE2_FUNC_PWM10         0x08
#define PORTE2_FUNC_TIM2_TOG         0x09
#define PORTE2_FUNC_SPIM8_1_IO2        0x0A

#define PORTE3_FUNC_E3              0x00
#define PORTE3_FUNC_CM0_A7        0x01
#define PORTE3_FUNC_CM1_UART_TXD         0x02
#define PORTE3_FUNC_UART3_TXD            0x03
#define PORTE3_FUNC_SPIM2_MISO       0x04
#define PORTE3_FUNC_SPIS0_MISO       0x05
#define PORTE3_FUNC_PDM3_SDA       0x06
#define PORTE3_FUNC_I2C3_SDA         0x07
#define PORTE3_FUNC_PWM11         0x08
#define PORTE3_FUNC_TIM3_TOG         0x09
#define PORTE3_FUNC_SPIM8_1_IO3        0x0A

#define PORTE4_FUNC_E4              0x00
#define PORTE4_FUNC_CM0_A4        0x01
#define PORTE4_FUNC_CM0_SPI_CLK         0x02
#define PORTE4_FUNC_UART3_CTS            0x03
#define PORTE4_FUNC_SPIM2_CLK       0x04
#define PORTE4_FUNC_SPIS1_CLK       0x05
#define PORTE4_FUNC_PDM2_CLK       0x06
#define PORTE4_FUNC_I2C2_CLK         0x07
#define PORTE4_FUNC_PWM12         0x08
#define PORTE4_FUNC_TIM2_PAUSE         0x09
#define PORTE4_FUNC_SPIM8_1_IO4        0x0A

#define PORTE5_FUNC_E5              0x00
#define PORTE5_FUNC_CM0_A5        0x01
#define PORTE5_FUNC_CM0_SPI_CSN         0x02
#define PORTE5_FUNC_UART3_RTS            0x03
#define PORTE5_FUNC_SPIM2_CSN       0x04
#define PORTE5_FUNC_SPIS1_FRM       0x05
#define PORTE5_FUNC_PDM2_SDA       0x06
#define PORTE5_FUNC_I2C2_SDA         0x07
#define PORTE5_FUNC_PWM13         0x08
#define PORTE5_FUNC_TIM3_PAUSE         0x09
#define PORTE5_FUNC_SPIM8_1_IO5        0x0A

#define PORTE6_FUNC_E6              0x00
#define PORTE6_FUNC_CM0_A6        0x01
#define PORTE6_FUNC_CM0_SPI_MOSI         0x02
#define PORTE6_FUNC_UART1_RXD            0x03
#define PORTE6_FUNC_SPIM2_MOSI       0x04
#define PORTE6_FUNC_SPIS1_MOSI       0x05
#define PORTE6_FUNC_PDM3_CLK       0x06
#define PORTE6_FUNC_I2C3_CLK         0x07
#define PORTE6_FUNC_PWM14         0x08
#define PORTE6_FUNC_TIM2_TOG         0x09
#define PORTE6_FUNC_SPIM8_1_IO6        0x0A

#define PORTE7_FUNC_E7              0x00
#define PORTE7_FUNC_CM0_A7        0x01
#define PORTE7_FUNC_CM0_SPI_MISO         0x02
#define PORTE7_FUNC_UART1_TXD            0x03
#define PORTE7_FUNC_SPIM2_MISO       0x04
#define PORTE7_FUNC_SPIS1_MISO       0x05
#define PORTE7_FUNC_PDM3_SDA       0x06
#define PORTE7_FUNC_I2C3_SDA         0x07
#define PORTE7_FUNC_PWM15         0x08
#define PORTE7_FUNC_TIM3_TOG         0x09
#define PORTE7_FUNC_SPIM8_1_IO7        0x0A

#define PORTF0_FUNC_F0              0x00
#define PORTF0_FUNC_CM0_A4        0x01
#define PORTF0_FUNC_CM0_SPI_CLK         0x02
#define PORTF0_FUNC_UART1_RXD            0x03
#define PORTF0_FUNC_SPIM2_CLK       0x04
#define PORTF0_FUNC_SPIS1_CLK       0x05
#define PORTF0_FUNC_PDM2_CLK       0x06
#define PORTF0_FUNC_I2C2_CLK         0x07
#define PORTF0_FUNC_PWM8         0x08
#define PORTF0_FUNC_TIM2_PAUSE         0x09
#define PORTF0_FUNC_SPIM8_1_CLK        0x0A

#define PORTF1_FUNC_F1              0x00
#define PORTF1_FUNC_CM0_A5        0x01
#define PORTF1_FUNC_CM0_SPI_CSN         0x02
#define PORTF1_FUNC_UART1_TXD            0x03
#define PORTF1_FUNC_SPIM2_CSN       0x04
#define PORTF1_FUNC_SPIS1_FRM       0x05
#define PORTF1_FUNC_PDM2_SDA       0x06
#define PORTF1_FUNC_I2C2_SDA         0x07
#define PORTF1_FUNC_PWM9         0x08
#define PORTF1_FUNC_TIM3_PAUSE         0x09
#define PORTF1_FUNC_SPIM8_1_CSN        0x0A

#define PORTF2_FUNC_F2              0x00
#define PORTF2_FUNC_CM0_A6        0x01
#define PORTF2_FUNC_CM0_SPI_MOSI         0x02
#define PORTF2_FUNC_UART3_RXD            0x03
#define PORTF2_FUNC_SPIM2_MOSI       0x04
#define PORTF2_FUNC_SPIS1_MOSI       0x05
#define PORTF2_FUNC_PDM3_CLK       0x06
#define PORTF2_FUNC_I2C3_CLK         0x07
#define PORTF2_FUNC_PWM10         0x08
#define PORTF2_FUNC_TIM2_TOG         0x09
#define PORTF2_FUNC_SPIM8_1_IO0        0x0A

#define PORTF3_FUNC_F3              0x00
#define PORTF3_FUNC_CM0_A7        0x01
#define PORTF3_FUNC_CM0_SPI_MISO         0x02
#define PORTF3_FUNC_UART3_TXD            0x03
#define PORTF3_FUNC_SPIM2_MISO       0x04
#define PORTF3_FUNC_SPIS1_MISO       0x05
#define PORTF3_FUNC_PDM3_SDA       0x06
#define PORTF3_FUNC_I2C3_SDA         0x07
#define PORTF3_FUNC_PWM11         0x08
#define PORTF3_FUNC_TIM3_TOG         0x09
#define PORTF3_FUNC_SPIM8_1_IO1        0x0A

#define PORTF4_FUNC_F4              0x00
#define PORTF4_FUNC_CM0_A4        0x01
#define PORTF4_FUNC_CM1_UART_RXD         0x02
#define PORTF4_FUNC_UART3_CTS            0x03
#define PORTF4_FUNC_SPIM2_CLK       0x04
#define PORTF4_FUNC_SPIS0_CLK       0x05
#define PORTF4_FUNC_PDM2_CLK       0x06
#define PORTF4_FUNC_I2C4_CLK         0x07
#define PORTF4_FUNC_PWM12         0x08
#define PORTF4_FUNC_TIM2_PAUSE         0x09
#define PORTF4_FUNC_SPIM8_1_IO2        0x0A

#define PORTF5_FUNC_F5              0x00
#define PORTF5_FUNC_CM0_A5        0x01
#define PORTF5_FUNC_CM1_UART_TXD         0x02
#define PORTF5_FUNC_UART3_RTS            0x03
#define PORTF5_FUNC_SPIM2_CSN       0x04
#define PORTF5_FUNC_SPIS0_CSN       0x05
#define PORTF5_FUNC_PDM2_SDA       0x06
#define PORTF5_FUNC_I2C4_SDA         0x07
#define PORTF5_FUNC_PWM13         0x08
#define PORTF5_FUNC_TIM3_PAUSE         0x09
#define PORTF5_FUNC_SPIM8_1_IO3        0x0A

#define PORTF6_FUNC_F6              0x00
#define PORTF6_FUNC_CM0_A6        0x01
#define PORTF6_FUNC_CM1_UART_RXD         0x02
#define PORTF6_FUNC_UART1_RXD            0x03
#define PORTF6_FUNC_SPIM2_MOSI       0x04
#define PORTF6_FUNC_SPIS0_MOSI       0x05
#define PORTF6_FUNC_PDM3_CLK       0x06
#define PORTF6_FUNC_I2C2_CLK         0x07
#define PORTF6_FUNC_PWM14         0x08
#define PORTF6_FUNC_TIM2_TOG         0x09
#define PORTF6_FUNC_SPIM8_1_CLK        0x0A

#define PORTF7_FUNC_F7              0x00
#define PORTF7_FUNC_CM0_A7        0x01
#define PORTF7_FUNC_CM1_UART_TXD         0x02
#define PORTF7_FUNC_UART1_TXD            0x03
#define PORTF7_FUNC_SPIM2_MISO       0x04
#define PORTF7_FUNC_SPIS0_MISO       0x05
#define PORTF7_FUNC_PDM3_SDA       0x06
#define PORTF7_FUNC_I2C2_SDA         0x07
#define PORTF7_FUNC_PWM15         0x08
#define PORTF7_FUNC_TIM3_TOG         0x09
#define PORTF7_FUNC_SPIM8_1_CSN        0x0A

#define PORTG0_FUNC_G0              0x00
#define PORTG0_FUNC_CM0_A4        0x01
#define PORTG0_FUNC_CM1_UART_RXD         0x02
#define PORTG0_FUNC_UART1_RXD            0x03
#define PORTG0_FUNC_SPIM2_CLK       0x04
#define PORTG0_FUNC_SPIS0_CLK       0x05
#define PORTG0_FUNC_PDM2_CLK       0x06
#define PORTG0_FUNC_I2C3_CLK         0x07
#define PORTG0_FUNC_PWM8         0x08
#define PORTG0_FUNC_TIM2_PAUSE         0x09
#define PORTG0_FUNC_SPIM8_1_IO4        0x0A

#define PORTG1_FUNC_G1              0x00
#define PORTG1_FUNC_CM0_A5        0x01
#define PORTG1_FUNC_CM1_UART_TXD         0x02
#define PORTG1_FUNC_UART1_TXD            0x03
#define PORTG1_FUNC_SPIM2_CSN       0x04
#define PORTG1_FUNC_SPIS0_CSN       0x05
#define PORTG1_FUNC_PDM2_SDA       0x06
#define PORTG1_FUNC_I2C3_SDA         0x07
#define PORTG1_FUNC_PWM9         0x08
#define PORTG1_FUNC_TIM3_PAUSE         0x09
#define PORTG1_FUNC_SPIM8_1_IO5        0x0A

#define PORTG2_FUNC_G2              0x00
#define PORTG2_FUNC_CM0_A6        0x01
#define PORTG2_FUNC_CM1_UART_RXD         0x02
#define PORTG2_FUNC_UART3_RXD            0x03
#define PORTG2_FUNC_SPIM2_MOSI       0x04
#define PORTG2_FUNC_SPIS0_MOSI       0x05
#define PORTG2_FUNC_PDM3_CLK       0x06
#define PORTG2_FUNC_I2C4_CLK         0x07
#define PORTG2_FUNC_PWM10         0x08
#define PORTG2_FUNC_TIM2_TOG         0x09
#define PORTG2_FUNC_SPIM8_1_IO6        0x0A

#define PORTG3_FUNC_G3              0x00
#define PORTG3_FUNC_CM0_A7        0x01
#define PORTG3_FUNC_CM1_UART_TXD         0x02
#define PORTG3_FUNC_UART3_TXD            0x03
#define PORTG3_FUNC_SPIM2_MISO       0x04
#define PORTG3_FUNC_SPIS0_MISO       0x05
#define PORTG3_FUNC_PDM3_SDA       0x06
#define PORTG3_FUNC_I2C4_SDA         0x07
#define PORTG3_FUNC_PWM11         0x08
#define PORTG3_FUNC_TIM3_TOG         0x09
#define PORTG3_FUNC_SPIM8_1_IO7        0x0A

#define PORTG4_FUNC_G4              0x00
#define PORTG4_FUNC_CM0_A4        0x01
#define PORTG4_FUNC_CM0_SPI_CLK         0x02
#define PORTG4_FUNC_UART3_CTS            0x03
#define PORTG4_FUNC_SPIM2_CLK       0x04
#define PORTG4_FUNC_SPIS1_CLK       0x05
#define PORTG4_FUNC_PDM2_CLK       0x06
#define PORTG4_FUNC_I2C3_CLK         0x07
#define PORTG4_FUNC_PWM12         0x08
#define PORTG4_FUNC_TIM2_PAUSE         0x09
#define PORTG4_FUNC_SPIM8_1_IO0        0x0A

#define PORTG5_FUNC_G5              0x00
#define PORTG5_FUNC_CM0_A5        0x01
#define PORTG5_FUNC_CM0_SPI_CSN         0x02
#define PORTG5_FUNC_UART3_RTS            0x03
#define PORTG5_FUNC_SPIM2_CSN       0x04
#define PORTG5_FUNC_SPIS1_FRM       0x05
#define PORTG5_FUNC_PDM2_SDA       0x06
#define PORTG5_FUNC_I2C3_SDA         0x07
#define PORTG5_FUNC_PWM13         0x08
#define PORTG5_FUNC_TIM3_PAUSE         0x09
#define PORTG5_FUNC_SPIM8_1_IO1        0x0A

#define PORTG6_FUNC_G6              0x00
#define PORTG6_FUNC_CM0_A6        0x01
#define PORTG6_FUNC_CM0_SPI_MOSI         0x02
#define PORTG6_FUNC_UART1_RXD            0x03
#define PORTG6_FUNC_SPIM2_MOSI       0x04
#define PORTG6_FUNC_SPIS1_MOSI       0x05
#define PORTG6_FUNC_PDM3_CLK       0x06
#define PORTG6_FUNC_I2C4_CLK         0x07
#define PORTG6_FUNC_PWM14         0x08
#define PORTG6_FUNC_TIM2_TOG         0x09
#define PORTG6_FUNC_SPIM8_1_IO2        0x0A

#define PORTG7_FUNC_G7              0x00
#define PORTG7_FUNC_CM0_A7        0x01
#define PORTG7_FUNC_CM0_SPI_MISO         0x02
#define PORTG7_FUNC_UART1_TXD            0x03
#define PORTG7_FUNC_SPIM2_MISO       0x04
#define PORTG7_FUNC_SPIS1_MISO       0x05
#define PORTG7_FUNC_PDM3_SDA       0x06
#define PORTG7_FUNC_I2C4_SDA         0x07
#define PORTG7_FUNC_PWM15         0x08
#define PORTG7_FUNC_TIM3_TOG         0x09
#define PORTG7_FUNC_SPIM8_1_IO3        0x0A

#define PORTH0_FUNC_H0              0x00
#define PORTH0_FUNC_CM0_A4        0x01
#define PORTH0_FUNC_CM0_SPI_CLK         0x02
#define PORTH0_FUNC_UART1_RXD            0x03
#define PORTH0_FUNC_SPIM2_CLK       0x04
#define PORTH0_FUNC_SPIS1_CLK       0x05
#define PORTH0_FUNC_PDM2_CLK       0x06
#define PORTH0_FUNC_I2C3_CLK         0x07
#define PORTH0_FUNC_PWM8         0x08
#define PORTH0_FUNC_TIM2_PAUSE         0x09
#define PORTH0_FUNC_SPIM8_1_CLK        0x0A

#define PORTH1_FUNC_H1              0x00
#define PORTH1_FUNC_CM0_A5        0x01
#define PORTH1_FUNC_CM0_SPI_CSN         0x02
#define PORTH1_FUNC_UART1_TXD            0x03
#define PORTH1_FUNC_SPIM2_CSN       0x04
#define PORTH1_FUNC_SPIS1_FRM       0x05
#define PORTH1_FUNC_PDM2_SDA       0x06
#define PORTH1_FUNC_I2C3_SDA         0x07
#define PORTH1_FUNC_PWM9         0x08
#define PORTH1_FUNC_TIM3_PAUSE         0x09
#define PORTH1_FUNC_SPIM8_1_CSN        0x0A

#define PORTH2_FUNC_H2              0x00
#define PORTH2_FUNC_CM0_A6        0x01
#define PORTH2_FUNC_CM0_SPI_MOSI         0x02
#define PORTH2_FUNC_UART3_RXD            0x03
#define PORTH2_FUNC_SPIM2_MOSI       0x04
#define PORTH2_FUNC_SPIS1_MOSI       0x05
#define PORTH2_FUNC_PDM3_CLK       0x06
#define PORTH2_FUNC_I2C4_CLK         0x07
#define PORTH2_FUNC_PWM10          0x08
#define PORTH2_FUNC_TIM2_TOG         0x09
#define PORTH2_FUNC_SPIM8_1_IO0        0x0A

#define PORTH3_FUNC_H3              0x00
#define PORTH3_FUNC_CM0_A7        0x01
#define PORTH3_FUNC_CM0_SPI_MISO         0x02
#define PORTH3_FUNC_UART3_TXD            0x03
#define PORTH3_FUNC_SPIM2_MISO       0x04
#define PORTH3_FUNC_SPIS1_MISO       0x05
#define PORTH3_FUNC_PDM3_SDA       0x06
#define PORTH3_FUNC_I2C4_SDA         0x07
#define PORTH3_FUNC_PWM11          0x08
#define PORTH3_FUNC_TIM3_TOG         0x09
#define PORTH3_FUNC_SPIM8_1_IO1        0x0A

#define PORTH4_FUNC_H4              0x00
#define PORTH4_FUNC_CM0_A4        0x01
#define PORTH4_FUNC_CM1_UART_RXD         0x02
#define PORTH4_FUNC_UART3_CTS            0x03
#define PORTH4_FUNC_SPIM2_CLK       0x04
#define PORTH4_FUNC_SPIS0_CLK       0x05
#define PORTH4_FUNC_PDM2_CLK       0x06
#define PORTH4_FUNC_I2C3_CLK         0x07
#define PORTH4_FUNC_PWM12          0x08
#define PORTH4_FUNC_TIM2_PAUSE         0x09
#define PORTH4_FUNC_SPIM8_1_IO2        0x0A

#define PORTH5_FUNC_H5              0x00
#define PORTH5_FUNC_CM0_A5        0x01
#define PORTH5_FUNC_CM1_UART_TXD         0x02
#define PORTH5_FUNC_UART3_RTS            0x03
#define PORTH5_FUNC_SPIM2_CSN       0x04
#define PORTH5_FUNC_SPIS0_CSN       0x05
#define PORTH5_FUNC_PDM2_SDA       0x06
#define PORTH5_FUNC_I2C3_SDA         0x07
#define PORTH5_FUNC_PWM13          0x08
#define PORTH5_FUNC_TIM3_PAUSE         0x09
#define PORTH5_FUNC_SPIM8_1_IO3        0x0A

#define PORTH6_FUNC_H6              0x00
#define PORTH6_FUNC_CM0_A6        0x01
#define PORTH6_FUNC_CM1_UART_RXD         0x02
#define PORTH6_FUNC_UART1_RXD            0x03
#define PORTH6_FUNC_SPIM2_MOSI       0x04
#define PORTH6_FUNC_SPIS0_MOSI       0x05
#define PORTH6_FUNC_PDM3_CLK       0x06
#define PORTH6_FUNC_I2C4_CLK         0x07
#define PORTH6_FUNC_PWM14          0x08
#define PORTH6_FUNC_TIM2_TOG         0x09

#define PORTH7_FUNC_H7              0x00
#define PORTH7_FUNC_CM0_A7        0x01
#define PORTH7_FUNC_CM1_UART_TXD         0x02
#define PORTH7_FUNC_UART1_TXD            0x03
#define PORTH7_FUNC_SPIM2_MISO       0x04
#define PORTH7_FUNC_SPIS0_MISOI       0x05
#define PORTH7_FUNC_PDM3_SDA       0x06
#define PORTH7_FUNC_I2C4_SDA         0x07
#define PORTH7_FUNC_PWM15          0x08
#define PORTH7_FUNC_TIM3_TOG         0x09


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

#define GPIO_PE0              (1<<0)
#define GPIO_PE1              (1<<1)
#define GPIO_PE2              (1<<2)
#define GPIO_PE3              (1<<3)
#define GPIO_PE4              (1<<4)
#define GPIO_PE5              (1<<5)
#define GPIO_PE6              (1<<6)
#define GPIO_PE7              (1<<7)

#define GPIO_PF0              (1<<8)
#define GPIO_PF1              (1<<9)
#define GPIO_PF2              (1<<10)
#define GPIO_PF3              (1<<11)
#define GPIO_PF4              (1<<12)
#define GPIO_PF5              (1<<13)
#define GPIO_PF6              (1<<14)
#define GPIO_PF7              (1<<15)

#define GPIO_PG0              (1<<16)
#define GPIO_PG1              (1<<17)
#define GPIO_PG2              (1<<18)
#define GPIO_PG3              (1<<19)
#define GPIO_PG4              (1<<20)
#define GPIO_PG5              (1<<21)
#define GPIO_PG6              (1<<22)
#define GPIO_PG7              (1<<23)

#define GPIO_PH0              (1<<24)
#define GPIO_PH1              (1<<25)
#define GPIO_PH2              (1<<26)
#define GPIO_PH3              (1<<27)
#define GPIO_PH4              (1<<28)
#define GPIO_PH5              (1<<29)
#define GPIO_PH6              (1<<30)
#define GPIO_PH7              ((uint32_t)1<<31)

#endif

enum system_port_t
{
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H,
};

enum system_port_bit_t
{
    GPIO_BIT_0,
    GPIO_BIT_1,
    GPIO_BIT_2,
    GPIO_BIT_3,
    GPIO_BIT_4,
    GPIO_BIT_5,
    GPIO_BIT_6,
    GPIO_BIT_7,
};
#define SET_FEILD(reg,field,pos,value)  (reg) = ( (reg) & ~(field<<(pos)) | (value<<(pos)))

#endif // DRIVER_IOMUX_H

