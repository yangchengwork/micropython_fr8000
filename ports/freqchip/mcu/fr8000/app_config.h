#ifndef _APP_CONFIG_H
#define _APP_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> SYSTEM Configuration
// <o> SYSTEM_CLOCK_SEL
//  <i> system clock selection, default: 48MHz
//  <4=> 48MHz
//  <5=> 96MHz
#define SYSTEM_CLOCK_SEL            5

// <o> LP_RC_CALIB_CNT
//  <i> lowpower clock calibration counter, the calibration will take about 18us*LOW_RC_CALIB_CNT, default: 100
//  <50-1000:10>
#define LP_RC_CALIB_CNT             60

// <o> LP_RC_CALIB_LARGE_CNT
//  <i> lowpower clock calibration counter, the calibration will take about 18us*LOW_RC_CALIB_CNT, default: 100
//  <5000-60000:1000>
#define LP_RC_CALIB_LARGE_CNT       10000
// </h>

// <h> LOG Configuration
// <c1> LOG_ENABLE
// <i> enable log module
#define LOG_ENABLE
// </c>

// <c1> LOG_ENABLE_FILE_LINE
// <i> display file name and line number in log
//#define LOG_ENABLE_FILE_LINE
// </c>

// <c1> LOG_ENABLE_TIME
// <i> display how many milliseconds have passed after power on in log
//#define LOG_ENABLE_TIME
// </c>

#define LOG_OUTPUT_RTT              0
#define LOG_OUTPUT_UART0            1
#define LOG_OUTPUT_UART1            2

// <o> LOG_OUTPUT_SEL
//  <i> LOG output selection, default: LOG_OUTPUT_UART0
//  <0=> LOG_OUTPUT_RTT
//  <1=> LOG_OUTPUT_UART0
//  <2=> LOG_OUTPUT_UART1
#define LOG_OUTPUT_SEL              0

// <o> LOG_UART_BAUDRATE_CFG
//  <i> uart buadrate used for log module, default: BAUDRATE_115200
//  <1152=> BAUDRATE_115200
//  <9216=> BAUDRATE_921600
#define LOG_UART_BAUDRATE_CFG       1152

// <o> LOG_UART_RX_PORT_SEL
//  <i> which pin is used for uart RX, default: PA2
//  <0=> PA0
//  <1=> PA1
//  <2=> PA2
//  <3=> PA3
//  <4=> PA4
//  <5=> PA5
//  <6=> PA6
//  <7=> PA7
//  <8=> PB0
//  <9=> PB1
//  <10=> PB2
//  <11=> PB3
//  <12=> PB4
//  <13=> PB5
//  <14=> PB6
//  <15=> PB7
//  <16=> PC0
//  <17=> PC1
//  <18=> PC2
//  <19=> PC3
//  <20=> PC4
//  <21=> PC5
//  <22=> PC6
//  <23=> PC7
//  <24=> PD0
//  <25=> PD1
//  <26=> PD2
//  <27=> PD3
//  <28=> PD4
//  <29=> PD5
//  <30=> PD6
//  <31=> PD7
#define LOG_UART_RX_PORT_SEL        0

// <o> LOG_UART_TX_PORT_SEL
//  <i> which pin is used for uart TX, default: PA3
//  <0=> PA0
//  <1=> PA1
//  <2=> PA2
//  <3=> PA3
//  <4=> PA4
//  <5=> PA5
//  <6=> PA6
//  <7=> PA7
//  <8=> PB0
//  <9=> PB1
//  <10=> PB2
//  <11=> PB3
//  <12=> PB4
//  <13=> PB5
//  <14=> PB6
//  <15=> PB7
//  <16=> PC0
//  <17=> PC1
//  <18=> PC2
//  <19=> PC3
//  <20=> PC4
//  <21=> PC5
//  <22=> PC6
//  <23=> PC7
//  <24=> PD0
//  <25=> PD1
//  <26=> PD2
//  <27=> PD3
//  <28=> PD4
//  <29=> PD5
//  <30=> PD6
//  <31=> PD7
#define LOG_UART_TX_PORT_SEL        1

// <c3> LOG_USE_SIMPLIFIED_PRINTF
// <i> if LOG_USE_SIMPLIFIED_PRINTF is defined, a build-in simplified co_printf will
// <i> be used to replace printf in libc. Some commonly used print formats are supported
// <i> by co_printf, such as %d %s %c %x etc.
//#define LOG_USE_SIMPLIFIED_PRINTF
// </c>

// </h>


// <h> FLASH Configuration
// <o> FLASH_CAPACITY
//  <i> Internal Flash capacity selection, Default: 4Mb
//  <0x00080000=> 4Mb
//  <0x00040000=> 2Mb
#define FLASH_CAPACITY          0x00080000

#if FLASH_CAPACITY == 0x00080000
    #define BLE_STACK_KEY_STORAGE_OFFSET    0x7F000
    #define BLE_BONDING_INFO_SAVE_ADDR      0x7D000
    #define BLE_REMOTE_SERVICE_SAVE_ADDR    0x7E000
#elif FLASH_CAPACITY == 0x00040000
    #define BLE_STACK_KEY_STORAGE_OFFSET    0x3F000
    #define BLE_BONDING_INFO_SAVE_ADDR      0x3D000
    #define BLE_REMOTE_SERVICE_SAVE_ADDR    0x3E000
#else
    #error "flash capacity configuration error!"
#endif	//FOR_2M_FLASH
// </h>

// <h> BLE STACK Configuration

// <o> BLE_STACK_ENABLE_MESH
//  <i> check to enable or disable sig mesh, default: DISABLE
//  <0=> DISABLE
//  <1=> ENABLE
#define BLE_STACK_ENABLE_MESH               0

// <o> BLE_STACK_ENABLE_CONNECTIONS
//  <i> used to define maximum number of connections
//  <1-30:1>
#define BLE_STACK_ENABLE_CONNECTIONS        1

// <o> BLE_STACK_RX_BUFFER_CNT
//  <i> used to define how many receive buffers reserved in link layer
//  <4-20:1>
#define BLE_STACK_RX_BUFFER_CNT             8

// <o> BLE_STACK_RX_BUFFER_SIZE
//  <i> used to define how many space reserved for each RX buffer
//  <37-251:1>
#define BLE_STACK_RX_BUFFER_SIZE            37

// <o> BLE_STACK_TX_BUFFER_CNT
//  <i> used to define how many transmit buffers reserved in link layer
//  <4-20:1>
#define BLE_STACK_TX_BUFFER_CNT             8

// <o> BLE_STACK_TX_BUFFER_SIZE
//  <i> used to define how many space reserved for each RX buffer
//  <27-251:1>
#define BLE_STACK_TX_BUFFER_SIZE            27

// <o> BLE_STACK_ADV_BUFFER_SIZE
//  <i> used to define how many space reserved for each advertising buffer
//  <31-251:1>
#define BLE_STACK_ADV_BUFFER_SIZE           31

// <o> BLE_STACK_RETENTION_RAM_SIZE
//  <i> used to define retention RAM size after enter deepsleep, default: 56KB
//  <0xE000=> 56KB
//  <0xC000=> 48KB
//  <0x8000=> 32KB
#define BLE_STACK_RETENTION_RAM_SIZE       0xE000
// </h>
// <<< end of configuration section >>>

#endif  // _APP_CONFIG_H
