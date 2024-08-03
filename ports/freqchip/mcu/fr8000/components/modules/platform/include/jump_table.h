#ifndef _JUMP_TABLE_H
#define _JUMP_TABLE_H

#include <stdint.h>

#include "co_math.h"

#define IMAGE_TYPE_CONTROLLER               0x00000000
#define IMAGE_TYPE_HOST                     0x11111111
#define IMAGE_TYPE_FULL                     0x22222222
#define IMAGE_TYPE_APP                      0x33333333

#define APP_BOOT_UART_PC_EN_MAGIC           0x55
#define APP_BOOT_ESCAPE_HS_MAGIC            0xFE

#define JUMP_TABLE_STATIC_KEYS_IRK          (1<<0)
#define JUMP_TABLE_STATIC_KEYS_PRIV_P256    (1<<1)
#define JUMP_TABLE_STATIC_KEYS_PUBL_P256    (1<<2)

#if 0
#define SYSTEM_OPTION_SLEEP_ENABLE          CO_BIT(0)
#define SYSTEM_OPTION_EXT_WAKEUP_ENABLE     CO_BIT(1)
#define SYSTEM_OPTION_PRINT_SEL_MSK         0x0C
#define SYSTEM_OPTION_PRINT_SWO             0x00
#define SYSTEM_OPTION_PRINT_UART1           0x04
#define SYSTEM_OPTION_PRINT_UART2           0x08
#define SYSTEM_OPTION_DEEP_SLEEP_ENABLE     CO_BIT(4)
#define SYSTEM_OPTION_LP_CLK_SEL_MSK        0x60
#define SYSTEM_OPTION_LP_CLK_RC             0x00
#define SYSTEM_OPTION_LP_CLK_32K            0x20
#define SYSTEM_OPTION_LP_CLK_32768          0x40
#define SYSTEM_OPTION_FIX_BAD_CHANNEL       CO_BIT(7)
#define SYSTEM_OPTION_TL_SEL                CO_BIT(8)   //0:uart0, 1:uart1
#define SYSTEM_OPTION_VECTOR_REMAP          CO_BIT(9)
#define SYSTEM_OPTION_WAIT_SLEEP_FLAG       CO_BIT(10)
#else
#define SYSTEM_OPTION_CODED_PHY_500         CO_BIT(0)
#define SYSTEM_OPTION_ACT_MOVE_CFG          CO_BIT(1)
#define SYSTEM_OPTION_SCAN_EXT_ADV          CO_BIT(2)
#define SYSTEM_OPTION_SLEEP_ENABLE          CO_BIT(3)
#define SYSTEM_OPTION_EXT_WAKEUP_ENABLE     CO_BIT(4)
#define SYSTEM_OPTION_LIGHT_SLEEP_ENABLE    CO_BIT(5)
#define SYSTEM_OPTION_PRINT_UART0           0x00
#define SYSTEM_OPTION_PRINT_UART1           CO_BIT(6)
#define SYSTEM_OPTION_PRINT_SWO             CO_BIT(7)
#define SYSTEM_OPTION_PRINT_MASK            (CO_BIT(6)|CO_BIT(7))
#define SYSTEM_OPTION_ENABLE_RTOS           CO_BIT(8)
#define SYSTEM_OPTION_DISABLE_HANDSHAKE     CO_BIT(9)
#define SYSTEM_OPTION_ENABLE_CACHE          CO_BIT(10)
#define SYSTEM_OPTION_ENABLE_QSPI_QMODE     CO_BIT(11)  // 1: 4 lines, 0: 2 lines(default)
#define SYSTEM_OPTION_ENABLE_FLASH_DS       CO_BIT(12)  // 1: enable flash deep sleep mode
#define SYSTEM_OPTION_RTOS_HEAP_SEL         CO_BIT(13)  // 1: KE_MEM_NON_RETENTION, 0: KE_MEM_ENV
#define SYSTEM_OPTION_BOOT_UART_PC_EN       CO_BIT(14)  // 1: use PC6/PC7 for boot up uart, 0: use PA2/PA3
#define SYSTEM_OPTION_ENABLE_HCI_MODE       CO_BIT(15)  // enable uart read start for HCI
#define SYSTEM_OPTION_FLASH_DEAL_CACHE      CO_BIT(16)
#define SYSTEM_OPTION_FLASH_ENABLE_PROTECT  CO_BIT(17)
#define SYSTEM_OPTION_CACHE_RETENTION       CO_BIT(18)
#define SYSTEM_OPTOIN_FIX_ADV_END_BUG       CO_BIT(19)
#define SYSTEM_OPTION_IGNORE_ADV_MIN        CO_BIT(20)
#define SYSTEM_OPTION_REMOVE_ADV_DELAY      CO_BIT(21)
#define SYSTEM_OPTION_FIX_TX_PACKET_BUG     CO_BIT(22)
#define SYSTEM_OPTION_ENABLE_FLASH_Q_R_F    CO_BIT(23)
#define SYSTEM_OPTION_ENABLE_FLASH_Q_R      CO_BIT(24)
#define SYSTEM_OPTION_ENABLE_FLASH_D_R_F    CO_BIT(25)
#define SYSTEM_OPTION_ENABLE_FLASH_D_R      CO_BIT(26)
#define SYSTEM_OPTION_ENABLE_FLASH_Q_W      CO_BIT(27)
#define SYSTEM_OPTION_ENABLE_FLASH_D_W      CO_BIT(28)
#define SYSTEM_OPTION_ENABLE_AUTO_LEN_REQ   CO_BIT(29)
#define SYSTEM_OPTION_ENABLE_AUTO_PHY_REQ   CO_BIT(30)
#define SYSTEM_OPTION_UP_PARAM_REQ_REPORT   CO_BIT(31)
#endif

#define JUMP_TABLE_CHECKWORD            0x51525251
#define JUMP_TABLE_OTA_IMAGE_VALID      0x51525251
#define JUMP_TABLE_COMPRESSED_LABEL     0x51525251

/// List of parameters identifiers
enum param_id_t
{
    /// Definition of the tag associated to each parameters
    /// Local Bd Address
    PARAM_BD_ADDRESS                 = 0x01,
    /// Device Name
    PARAM_DEVICE_NAME                = 0x02,
    
    /// SP Private Key 192
    PARAM_SP_PRIVATE_KEY_P192        = 0x13,
    /// SP Public Key 192
    PARAM_SP_PUBLIC_KEY_P192         = 0x14,

    /// SC Private Key (Low Energy)
    PARAM_LE_PRIVATE_KEY_P256        = 0x80,
    /// SC Public Key (Low Energy)
    PARAM_LE_PUBLIC_KEY_P256         = 0x81,
    /// SC Debug: Used Fixed Private Key from NVDS (Low Energy)
    PARAM_LE_DBG_FIXED_P256_KEY      = 0x82,
};

enum param_status_t
{
    /// PARAM status OK
    PARAM_SUCCESS,
    /// 
    PARAM_FAILED,
};

enum rtos_entry_type_t
{
    RTOS_ENTRY_TYPE_INIT,
    RTOS_ENTRY_TYPE_STACK_PUSH,
    RTOS_ENTRY_TYPE_STACK_YIELD,
    RTOS_ENTRY_TYPE_WAKEUP_RESTORE,
    RTOS_ENTRY_TYPE_POST_GATT_MSG,
};

struct bd_addr_
{
    ///6-byte array address value
    uint8_t  addr[6];
};

struct jump_table_reserved_t
{
    uint32_t reserved_data;
};

struct jump_table_image_t
{
    uint32_t image_size;
    uint32_t image_type;
};

struct jump_table_middle_t
{
    void *entry;
    //used to init ke_mem, prf_env, ke_task_env, need to be called in rwip_init function
    void (*memory_init_app)(void);
};

struct jump_table_version_t
{
    uint32_t *stack_top_address;
    uint32_t firmware_version;
};

struct jump_table_last_t
{
    uint16_t local_drift;
    uint16_t sleep_algo_dur;    // unit: 312.5us, can be used to wakeup early (enlarge this value)
    uint16_t twext;
    //uint16_t twrm;
    uint16_t twosc;

    /*
     * these parameters will be used several times.
     */
    uint8_t (*param_get)(uint8_t param_id, uint8_t * lengthPtr, void *buf);
    uint8_t (*param_set)(uint8_t param_id, uint8_t length, uint8_t *buf);
    uint32_t system_option;
    uint32_t diag_port;
    uint32_t slp_max_dur;
    uint16_t sleep_max_during;      // used in connection mode, unit:10ms
    uint16_t max_adv_buffer_size;
    uint16_t max_rx_buffer_size;
    uint16_t max_tx_buffer_size;
    uint16_t max_rx_time;
    uint16_t max_tx_time;
    uint16_t lp_cycle_sleep_delay;  // unit: pmu clock cycle, add lp_cycle_wakeup_delay to control minimum sleep time
    uint16_t lp_clk_calib_cnt;
    uint8_t sleep_delay_for_os;     // unit: ms
    uint8_t prf_max;
    uint8_t task_max;
    uint8_t system_clk;
    uint8_t handshake_to;
    uint8_t boot_uart_pc_en_magic;  // when pc6 and pc7 are used for boot up, this byte need to be set to 0x55 for enable double check
    uint8_t initial_qspi_bandrate;
    uint8_t flash_protect_mask;
    uint8_t latency_calc_adjust;
    uint8_t chmap_update_period;

    uint8_t enable_activity_num;
    uint8_t enable_adv_activity_num;
    uint8_t enable_con_num;
    uint8_t em_ble_rx_buf_num;
    uint8_t em_ble_tx_buf_num;

    struct bd_addr_ addr;
    uint32_t checkword;
};

struct jump_table_t
{
    /*
     * these parameters are used only one time.
     */
    uint32_t reserved_data;
    uint32_t image_size;
    uint32_t image_type;
    void *entry;
    //used to init ke_mem, prf_env, ke_task_env, need to be called in rwip_init function
    void (*memory_init_app)(void);
    uint32_t *stack_top_address;
    uint32_t firmware_version;
    uint16_t local_drift;
    uint16_t sleep_algo_dur;    // unit: 312.5us, can be used to wakeup early (enlarge this value)
    uint16_t twext;
    //uint16_t twrm;
    uint16_t twosc;

    /*
     * these parameters will be used several times.
     */
    uint8_t (*param_get)(uint8_t param_id, uint8_t * lengthPtr, void *buf);
    uint8_t (*param_set)(uint8_t param_id, uint8_t length, uint8_t *buf);
    uint32_t system_option;
    uint32_t diag_port;
    uint32_t slp_max_dur;
    uint16_t sleep_max_during;      // used in connection mode, unit:10ms
    uint16_t max_adv_buffer_size;
    uint16_t max_rx_buffer_size;
    uint16_t max_tx_buffer_size;
    uint16_t max_rx_time;
    uint16_t max_tx_time;
    uint16_t lp_cycle_sleep_delay;  // unit: pmu clock cycle, add lp_cycle_wakeup_delay to control minimum sleep time
    uint16_t lp_clk_calib_cnt;
    uint8_t sleep_delay_for_os;     // unit: ms
    uint8_t prf_max;
    uint8_t task_max;
    uint8_t system_clk;
    uint8_t handshake_to;
    uint8_t boot_uart_pc_en_magic;  // when pc6 and pc7 are used for boot up, this byte need to be set to 0x55 for enable double check
    uint8_t initial_qspi_bandrate;
    uint8_t flash_protect_mask;
    uint8_t latency_calc_adjust;
    uint8_t chmap_update_period;

    uint8_t enable_activity_num;
    uint8_t enable_adv_activity_num;
    uint8_t enable_con_num;
    uint8_t em_ble_rx_buf_num;
    uint8_t em_ble_tx_buf_num;

    struct bd_addr_ addr;
    uint32_t checkword;
};

struct image_crc_t {
    // jump_table字段（不包含checkword）的校验值，在keil编译完成之后，由脚本生成
    uint32_t jump_table_crc;
    // image段的校验值，在keil编译完成之后，由脚本生成
    uint32_t image_crc;
};

struct image_compressed_info_t {
    // 需要由服务器端或者手机APP生成，服务器或者手机由当前固件版本号获取旧固件，
    // 然后与新固件对比生成差分文件，之后计算得到该字段
    uint32_t compressed_image_crc;
    // 需要由服务器端或者手机APP生成，JUMP_TABLE_COMPRESSED_LABEL表示差分升级模式，且上面crc字段有效
    uint32_t compressed_label;
};

struct image_info_t {
    struct jump_table_t jump_table;
    struct image_crc_t crc;
    struct image_compressed_info_t compressed_info;
    // 由max(old_bin_size, new_bin_size)得到，ota.c中的程序负责生成并写入到flash
    uint32_t image_storage_offset;
    // 由ota.c负责写入，只是image段的长度，不包含jump_table部分
    uint32_t image_length;
    // 当收到手机传来的数据之后，可能会有些条件不满足OTA条件（比如电池电量不够），这个时候
    // 在这个字段标记上原因，image_valid不更新，等后续满足条件之后再标记image_valid进行升级
    uint32_t ota_delay_reason;
    // 如果flash加入了写保护功能，在这个地方加入mask的标志位，表示status的那几个bit位为保护
    // 相关的字段，然后在bootloader进行处理前会进行接触写保护，然后在开始进行操作。另外bit8
    // 表示解除写保护时采用06还是50 opcode
    uint32_t flash_protect_mask;
    // ota.收完所有数据后会进行校验，通过之后会在该标志位写入标识，指示ota数据生效
    uint32_t image_valid;
};

extern struct jump_table_t __jump_table;

/* called by function in controller partition */
extern uint8_t (*gapc_get_conidx)(uint16_t conhdl);
extern void (*appm_init)(void);
extern void (*rwble_hl_init)(void);

extern uint32_t (*svc_exception_handler)(uint32_t svc_pc);
extern void (*low_power_save_entry)(uint8_t);
extern void (*low_power_restore_entry)(uint8_t);
extern void (*user_entry_before_sleep)(void);
extern void (*user_entry_after_sleep)(void);
extern void (*rtos_entry)(uint8_t type, void *arg);

void jump_table_set_static_keys_store_offset(uint32_t offset);
uint8_t jump_table_get_static_keys(uint8_t type, uint8_t *data);
void jump_table_set_static_keys(uint8_t type, uint8_t *data);

#endif //_JUMP_TABLE_H


