/*
  ******************************************************************************
  * @file    driver_qspi.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Header file of QSPI HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_QSPI_H__
#define __DRIVER_QSPI_H__

#include "fr30xx.h"

/** @addtogroup QSPI_Registers_Section
  * @{
  */
/* ################################ Register Section Start ################################ */

struct qspi_config_reg_t {  //@0x00
    uint32_t enable:1;
    uint32_t cpol:1;
    uint32_t cpha:1;
    uint32_t reserved0:1;
    uint32_t octal_xccela:1;
    uint32_t octal_opi:1;
    uint32_t octal_div2:1;
    uint32_t enable_DAC:1;  //direct access controller
    uint32_t enable_legacy:1;
    uint32_t peri_sel:1;
    uint32_t peri_sel_line:4;   //与peri_sel配合使用
    uint32_t write_en_pin:1;
    uint32_t enable_DMA:1;
    uint32_t enable_AHB_remap:1;
    uint32_t enable_XIP_next_R:1;   //enter XIP Mode on next READ
    uint32_t enalbe_XIP:1;  //enter XIP Mode immediately
    uint32_t baud_rate:4;
    uint32_t enable_AHB_decoder:1;
    uint32_t enable_DTR_prot:1;
    uint32_t reserved2:1;
    uint32_t sclk_out_mode:2;
    uint32_t rxds_smp_mode:1;
    uint32_t rxd_push_mask:1;
    uint32_t reserved3:1;
    uint32_t status:1;
};

struct qspi_read_ins_reg_t {        //@0x04
    uint32_t opcode:8;
    uint32_t instruction_type:2;
    uint32_t enable_DDR:1;
    uint32_t reserved0:1;
    uint32_t addr_type:2;
    uint32_t reserved1:2;
    uint32_t data_type:2;
    uint32_t reserved2:2;
    uint32_t enable_mode:1;
    uint32_t reserved3:3;
    uint32_t dummy_cycles:5;
    uint32_t reserved4:3;
};

struct qspi_write_ins_reg_t {       //@0x08
    uint32_t opcode:8;
    uint32_t disable_WEL:1;
    uint32_t reserved0:3;
    uint32_t addr_type:2;
    uint32_t reserved1:2;
    uint32_t data_type:2;
    uint32_t reserved2:6;
    uint32_t dummy_cycles:5;
    uint32_t reserved3:3;
};

struct qspi_device_delay_reg_t {    //@0x0c
    uint32_t sel_start_offset:8;
    uint32_t sel_end_offset:8;
    uint32_t sel_dessert_diff:8;
    uint32_t sel_dessert:8;
};

struct qspi_read_cap_reg_t {        //@0x10
    uint32_t enable_loopback_clk:1;
    uint32_t delay_capture:4;
    uint32_t sample_edge:1;
    uint32_t reserved0:10;
    uint32_t delay_trans:4;
    uint32_t reserved1:12;
};

struct qspi_device_size_cfg_t {     //@0x14
    uint32_t addr_bytes:4;  //number of address bytes. 0=1byte
    uint32_t page_bytes:12; //number of bytes per device page
    uint32_t block_bytes:5; //number of bytes per block. bytes = 2^block_bytes
    uint32_t CS0_size:2;
    uint32_t CS1_size:2;
    uint32_t CS2_size:2;
    uint32_t CS3_size:2;
    uint32_t reserved0:3;
};

struct qspi_dma_peri_cfg_t {        //@0x20
    uint32_t bytes_per_req:4;   //2^bytes_per_req
    uint32_t reserved0:4;
    uint32_t bytes_per_burst:4; //2^bytes_per_burst
    uint32_t reserved1:20;
};

struct qspi_sram_level_reg_t {      //@0x2c
    uint32_t read_part:16;
    uint32_t write_part:16;
};

struct qspi_write_comp_ctrl_reg_t { //@0x38
    uint32_t opcode_poll:8;
    uint32_t poll_bit_index:3;  //the bit index that should be polled
    uint32_t reserved0:2;
    uint32_t poll_polarity:1;
    uint32_t disable_poll:1;
    uint32_t enable_expiration:1;
    uint32_t poll_count:8;
    uint32_t poll_repetition_delay:8;
};

struct qspi_write_protect_reg_t {
    uint32_t inversion:1;
    uint32_t enable:1;
    uint32_t reserved0:30;
};

struct qspi_ind_read_crtl_reg_t {   //@0x60
    uint32_t start:1;
    uint32_t cancel:1;
    uint32_t progress_status:1;
    uint32_t sram_status:1;
    uint32_t queue_status:1;
    uint32_t comp_status:1;
    uint32_t num_operation_comp:2;
    uint32_t reserved0:24;
};

struct qspi_ind_write_crtl_reg_t {   //@0x70
    uint32_t start:1;
    uint32_t cancel:1;
    uint32_t progress_status:1;
    uint32_t reserved0:1;
    uint32_t queue_status:1;
    uint32_t comp_status:1;
    uint32_t num_operation_comp:2;
    uint32_t reserved1:24;
};

struct qspi_stig_mem_reg_t {
    uint32_t mem_bank_req:1;
    uint32_t mem_bank_status:1;
    uint32_t reserved0:6;
    uint32_t mem_bank_data:8;
    uint32_t mem_bank_req_bytes:3;
    uint32_t reserved1:1;
    uint32_t mem_bank_addr:9;
    uint32_t reserved2:3;
};

struct qspi_stig_reg_t {
    uint32_t execute:1;
    uint32_t progress_status:1;
    uint32_t enable_bank:1;
    uint32_t reserved0:4;
    uint32_t dummy_cycles:5;
    uint32_t write_bytes:3;     //0~1bytes
    uint32_t enable_write:1;
    uint32_t addr_bytes:2;      //0~1bytes
    uint32_t enable_mode:1;
    uint32_t enable_cmd_addr:1;
    uint32_t read_bytes:3;
    uint32_t enable_read:1;
    uint32_t opcode:8;
};

struct qspi_poll_flash_status_t {
    uint32_t status:8;
    uint32_t valid:1;
    uint32_t reserved0:7;
    uint32_t dummy_cycles:4;
    uint32_t reserved1:12;
};
struct qspi_cs_ctrl_t{
    uint32_t rd_brk_en:1;
    uint32_t page_boundary_protect_en:1;
    uint32_t disable_cs_after_first_byte:1;
    uint32_t resv0:13;
    uint32_t page_boundary:12;
    uint32_t resv1:4;
};

struct qspi_regs_t {
    volatile struct qspi_config_reg_t config;                   //@0x00
    volatile struct qspi_read_ins_reg_t read_conf;
    volatile struct qspi_write_ins_reg_t write_conf;
    volatile struct qspi_device_delay_reg_t delay;
    volatile struct qspi_read_cap_reg_t read_cap;               //@0x10
    volatile struct qspi_device_size_cfg_t size_cfg;
    volatile uint32_t sram_part_cfg;
    volatile uint32_t AHB_trigger_address;
    volatile struct qspi_dma_peri_cfg_t dma_cfg;                //@0x20
    volatile uint32_t remap_address;
    volatile uint32_t mode_bits;
    volatile struct qspi_sram_level_reg_t sram_level;
    volatile uint32_t tx_threshold;                             //@0x30
    volatile uint32_t rx_threshold;
    volatile struct qspi_write_comp_ctrl_reg_t poll_cfg;
    volatile uint32_t poll_expiration;
    volatile uint32_t int_status;                               //@0x40
    volatile uint32_t int_mask;
    uint32_t reserved0[2];
    volatile uint32_t lower_write_protect;                      //@0x50
    volatile uint32_t upper_write_protect;
    volatile struct qspi_write_protect_reg_t write_protect;
    uint32_t reserved1;
    volatile struct qspi_ind_read_crtl_reg_t ind_read_ctrl;     //@0x60
    volatile uint32_t ind_read_watermark;
    volatile uint32_t ind_read_start_addr;
    volatile uint32_t ind_read_bytes;
    volatile struct qspi_ind_write_crtl_reg_t ind_write_ctrl;   //@0x70
    volatile uint32_t ind_write_watermark;
    volatile uint32_t ind_write_start_addr;
    volatile uint32_t ind_write_bytes;
    volatile uint32_t ind_range_width;                          //@0x80
    uint32_t reserved2[2];
    volatile struct qspi_stig_mem_reg_t cmd_ctrl_mem;
    volatile struct qspi_stig_reg_t cmd_ctrl;         //@0x90
    volatile uint32_t cmd_address;
    uint32_t reserved3[2];
    volatile uint32_t read_data_L;                              //@0xa0
    volatile uint32_t read_data_H;
    volatile uint32_t write_data_L;
    volatile uint32_t write_data_H;
    volatile struct qspi_poll_flash_status_t poll_status;       //@0xb0
    volatile struct qspi_cs_ctrl_t cs_ctrl;
    uint32_t reserved4[17];
    volatile uint32_t module_id;                                //@0xfc
};

#define QSPI0       ((struct qspi_regs_t *)FLASH_QSPI_BASE)
#define QSPI1       ((struct qspi_regs_t *)DSP_QSPI_BASE)
#define OSPI        ((struct qspi_regs_t *)PSRAM_OSPI_BASE)

/* ################################ Register Section END ################################## */
/**
  * @}
  */

/** @addtogroup QSPI_Initialization_Config_Section
  * @{
  */
/* ################################ Initialization、Config Section Start ################################ */

#define QSPI_INT_MODE_FAIL          0x00000001
#define QSPI_INT_UNDERFLOW          0x00000002
#define QSPI_INT_COMP_INDIRECT      0x00000004
#define QSPI_INT_FAIL_INDIRECT      0x00000008
#define QSPI_INT_FAIL_WR_PROTECT    0x00000010
#define QSPI_INT_ILLEGAL_AHB        0x00000020
#define QSPI_INT_INDIRECT_WATER     0x00000040
#define QSPI_INT_OVERFLOW           0x00000080
#define QSPI_INT_TXFF_NOFULL        0x00000100
#define QSPI_INT_TXFF_FULL          0x00000200
#define QSPI_INT_RXFF_NOEMPTY       0x00000400
#define QSPI_INT_RXFF_FULL          0x00000800
#define QSPI_INT_RD_PART_FULL       0x00001000
#define QSPI_INT_POLL_EXPIRED       0x00002000
#define QSPI_INT_COMP_STIG          0x00004000

enum qspi_flash_size_t {
    QSPI_FLASH_SIZE_512Mb,
    QSPI_FLASH_SIZE_1Gb,
    QSPI_FLASH_SIZE_2Gb,
    QSPI_FLASH_SIZE_4Gb,
};

enum qspi_mem_bank_bytes_t {
    QSPI_MEM_BANK_BYTES_16,
    QSPI_MEM_BANK_BYTES_32,
    QSPI_MEM_BANK_BYTES_64,
    QSPI_MEM_BANK_BYTES_128,
    QSPI_MEM_BANK_BYTES_256,
    QSPI_MEM_BANK_BYTES_512,
};

enum qspi_wire_type_t {
    QSPI_WIRE_TYPE_STAND,
    QSPI_WIRE_TYPE_DIO,
    QSPI_WIRE_TYPE_QIO,
    QSPI_WIRE_TYPE_OIO,
};

enum qspi_baud_rate_t {
    QSPI_BAUDRATE_DIV_2,
    QSPI_BAUDRATE_DIV_4,
    QSPI_BAUDRATE_DIV_6,
    QSPI_BAUDRATE_DIV_8,
    QSPI_BAUDRATE_DIV_10,
    QSPI_BAUDRATE_DIV_12,
    QSPI_BAUDRATE_DIV_14,
    QSPI_BAUDRATE_DIV_16,
    QSPI_BAUDRATE_DIV_18,
    QSPI_BAUDRATE_DIV_20,
    QSPI_BAUDRATE_DIV_22,
    QSPI_BAUDRATE_DIV_24,
    QSPI_BAUDRATE_DIV_26,
    QSPI_BAUDRATE_DIV_28,
    QSPI_BAUDRATE_DIV_30,
    QSPI_BAUDRATE_DIV_32,
};

enum qspi_stig_cmd_type_t {
    QSPI_STIG_CMD_READ,
    QSPI_STIG_CMD_BANK_READ,
    QSPI_STIG_CMD_WRITE,
    QSPI_STIG_CMD_EXE,
};

enum qspi_stig_addr_bytes_t {
    QSPI_STIG_ADDR_BYTES_1,
    QSPI_STIG_ADDR_BYTES_2,
    QSPI_STIG_ADDR_BYTES_3,
    QSPI_STIG_ADDR_BYTES_4,
};

enum qspi_device_addr_bytes_t {
    QSPI_DEVICE_ADDR_BYTES_1,
    QSPI_DEVICE_ADDR_BYTES_2,
    QSPI_DEVICE_ADDR_BYTES_3,
    QSPI_DEVICE_ADDR_BYTES_4,
};

/* ################################ Initialization、Config Section END ################################## */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* QSPI Enable/Disable */
#define __QSPI_ENABLE(__QSPIx__)                            (__QSPIx__->config.enable = 1)
#define __QSPI_DISABLE(__QSPIx__)                           (__QSPIx__->config.enable = 0)

#define __QSPI_CFG_CPOL_SET(__QSPIx__, __VAULE__)           (__QSPIx__->config.cpol = __VAULE__)
#define __QSPI_CFG_CPHA_SET(__QSPIx__, __VAULE__)           (__QSPIx__->config.cpha = __VAULE__)
#define __QSPI_CFG_OCTAL_XCCELA_ENABLE(__QSPIx__)           (__QSPIx__->config.octal_xccela = 1)
#define __QSPI_CFG_OCTAL_XCCELA_DISABLE(__QSPIx__)          (__QSPIx__->config.octal_xccela = 0)
#define __QSPI_CFG_OCTAL_OPI_ENABLE(__QSPIx__)              (__QSPIx__->config.octal_opi = 1)
#define __QSPI_CFG_OCTAL_OPI_DISABLE(__QSPIx__)             (__QSPIx__->config.octal_opi = 0)

#define __QSPI_CFG_DAC_ENABLE(__QSPIx__)                    (__QSPIx__->config.enable_DAC = 1)
#define __QSPI_CFG_DAC_DISABLE(__QSPIx__)                   (__QSPIx__->config.enable_DAC = 0)

#define __QSPI_CFG_LEGACY_ENABLE(__QSPIx__)                 (__QSPIx__->config.enable_legacy = 1)
#define __QSPI_CFG_LEGACY_DISABLE(__QSPIx__)                (__QSPIx__->config.enable_legacy = 0)

#define __QSPI_CFG_WRITE_PROTECT_ENABLE(__QSPIx__)          (__QSPIx__->config.write_en_pin = 1)
#define __QSPI_CFG_WRITE_PROTECT_DISABLE(__QSPIx__)         (__QSPIx__->config.write_en_pin = 0)

#define __QSPI_CFG_REMAP_ENABLE(__QSPIx__)                  (__QSPIx__->config.enable_AHB_remap = 1)
#define __QSPI_CFG_REMAP_DISABLE(__QSPIx__)                 (__QSPIx__->config.enable_AHB_remap = 0)

#define __QSPI_CFG_AHB_DECODER_ENABLE(__QSPIx__)            (__QSPIx__->config.enable_AHB_decoder = 1)
#define __QSPI_CFG_AHB_DECODER_DISABLE(__QSPIx__)           (__QSPIx__->config.enable_AHB_decoder = 0)

#define __QSPI_CFG_DTR_ENABLE(__QSPIx__)                    (__QSPIx__->config.enable_DTR_prot = 1)
#define __QSPI_CFG_DTR_DISABLE(__QSPIx__)                   (__QSPIx__->config.enable_DTR_prot = 0)

#define __QSPI_CFG_BAUDRATE_SET(__QSPIx__, baudrate)        (__QSPIx__->config.baud_rate = baudrate)

#define __QSPI_IS_BUSY(__QSPIx__)                           (__QSPIx__->config.status == 0)

#define __QSPI_READ_OPCODE_SET(__QSPIx__, _opcode)          (__QSPIx__->read_conf.opcode = _opcode)
#define __QSPI_READ_INSTRUCTION_TYPE_SET(__QSPIx__, type)   (__QSPIx__->read_conf.instruction_type = type)
#define __QSPI_READ_ADDRESS_TYPE_SET(__QSPIx__, type)       (__QSPIx__->read_conf.addr_type = type)
#define __QSPI_READ_DATA_TYPE_SET(__QSPIx__, type)          (__QSPIx__->read_conf.data_type = type)
#define __QSPI_READ_MODE_ENABLE_SET(__QSPIx__, en)          (__QSPIx__->read_conf.enable_mode = en)
#define __QSPI_READ_DUMMY_CYCLES_SET(__QSPIx__, cycles)     (__QSPIx__->read_conf.dummy_cycles = cycles)
#define __QSPI_READ_DDR_ENABLE(__QSPIx__)                   (__QSPIx__->read_conf.enable_DDR = 1)
#define __QSPI_READ_DDR_DISABLE(__QSPIx__)                  (__QSPIx__->read_conf.enable_DDR = 0)
#define __QSPI_READ_DDR_GET(__QSPIx__)                      (__QSPIx__->read_conf.enable_DDR)

#define __QSPI_WRITE_OPCODE_SET(__QSPIx__, _opcode)         (__QSPIx__->write_conf.opcode = _opcode)
#define __QSPI_WRITE_WEL_ENABLE(__QSPIx__)                  (__QSPIx__->write_conf.disable_WEL = 0)
#define __QSPI_WRITE_WEL_DISABLE(__QSPIx__)                 (__QSPIx__->write_conf.disable_WEL = 1)
#define __QSPI_WRITE_ADDRESS_TYPE_SET(__QSPIx__, type)      (__QSPIx__->write_conf.addr_type = type)
#define __QSPI_WRITE_DATA_TYPE_SET(__QSPIx__, type)         (__QSPIx__->write_conf.data_type = type)
#define __QSPI_WRITE_DUMMY_CYCLES_SET(__QSPIx__, cycles)    (__QSPIx__->write_conf.dummy_cycles = cycles)

#define __QSPI_DEVICE_PAGE_SIZE_SET(__QSPIx__, page_size)   (__QSPIx__->size_cfg.page_bytes = page_size)
#define __QSPI_DEVICE_CS0_SIZE_SET(__QSPIx__, cs_size)      (__QSPIx__->size_cfg.CS0_size = cs_size)

#define __QSPI_DELAY_CS_END_SET(__QSPIx__, _delay)          (__QSPIx__->delay.sel_end_offset = _delay)
#define __QSPI_DELAY_CS_START_SET(__QSPIx__, _delay)        (__QSPIx__->delay.sel_start_offset = _delay)
#define __QSPI_DELAY_CS_DESSERT_SET(__QSPIx__, __dessert)   (__QSPIx__->delay.sel_dessert = __dessert)

#define __QSPI_READ_CAPTURE_LP_CLK_EN(__QSPIx__)            (__QSPIx__->read_cap.enable_loopback_clk = 1)
#define __QSPI_READ_CAPTURE_DELAY_SET(__QSPIx__, delay)     (__QSPIx__->read_cap.delay_capture = delay)

#define __QSPI_DEVICE_ADDR_BYTES_SET(__QSPIx__, bytes)      (__QSPIx__->size_cfg.addr_bytes = bytes)

#define __QSPI_REMAP_ADDRESS_SET(__QSPIx__, address)        (__QSPIx__->remap_address = address)

#define __QSPI_MODE_BIT_SET(__QSPIx__, mode)                (__QSPIx__->mode_bits = mode)

#define __QSPI_POLL_OPCODE_SET(__QSPIx__, opcode)           (__QSPIx__->poll_cfg.opcode_poll = opcode)
#define __QSPI_POLL_BIT_INDEX_SET(__QSPIx__, index)         (__QSPIx__->poll_cfg.poll_bit_index = index)
#define __QSPI_POLL_POLARITY_SET(__QSPIx__, pol)            (__QSPIx__->poll_cfg.poll_polarity = pol)
#define __QSPI_POLL_ENABLE(__QSPIx__)                       (__QSPIx__->poll_cfg.disable_poll = 0)
#define __QSPI_POLL_DISABLE(__QSPIx__)                      (__QSPIx__->poll_cfg.disable_poll = 1)
#define __QSPI_POLL_EXPIRE_ENABLE(__QSPIx__)                (__QSPIx__->poll_cfg.enable_expiration = 1)
#define __QSPI_POLL_EXPIRE_DISABLE(__QSPIx__)               (__QSPIx__->poll_cfg.enable_expiration = 0)
#define __QSPI_POLL_COUNT_SET(__QSPIx__, count)             (__QSPIx__->poll_cfg.poll_count = count)
#define __QSPI_POLL_DELAY_SET(__QSPIx__, delay)             (__QSPIx__->poll_cfg.poll_repetition_delay = delay)

#define __QSPI_POLL_EXPIRATION_SET(__QSPIx__, duration)     (__QSPIx__->poll_expiration = duration)

#define __QSPI_CMD_ADDRESS_SET(__QSPIx__, address)          (__QSPIx__->cmd_address = address)

#define __QSPI_STIG_CMD_SET(__QSPIx__, cmd)                 (__QSPIx__->cmd_ctrl = cmd)
#define __QSPI_STIG_OPCODE_SET(__QSPIx__, opcode)           (__QSPIx__->cmd_ctrl.opcode = opcode)
#define __QSPI_STIG_READ_ENABLE(__QSPIx__)                  (__QSPIx__->cmd_ctrl.enable_read = 1)
#define __QSPI_STIG_READ_DISABLE(__QSPIx__)                 (__QSPIx__->cmd_ctrl.enable_read = 0)
#define __QSPI_STIG_READ_BYTES_SET(__QSPIx__, bytes)        (__QSPIx__->cmd_ctrl.read_bytes = (bytes)-1)
#define __QSPI_STIG_CMD_ADDRESS_ENABLE(__QSPIx__)           (__QSPIx__->cmd_ctrl.enable_cmd_addr = 0)
#define __QSPI_STIG_CMD_ADDRESS_DISABLE(__QSPIx__)          (__QSPIx__->cmd_ctrl.enable_cmd_addr = 1)
#define __QSPI_STIG_CMD_ADDRESS_BYTES_SET(__QSPIx__, bytes) (__QSPIx__->cmd_ctrl.addr_bytes = (bytes)-1)
#define __QSPI_STIG_MODE_ENABLE(__QSPIx__)                  (__QSPIx__->cmd_ctrl.enable_mode = 1)
#define __QSPI_STIG_MODE_DISABLE(__QSPIx__)                 (__QSPIx__->cmd_ctrl.enable_mode = 0)
#define __QSPI_STIG_WRITE_ENABLE(__QSPIx__)                 (__QSPIx__->cmd_ctrl.enable_write = 1)
#define __QSPI_STIG_WRITE_DISABLE(__QSPIx__)                (__QSPIx__->cmd_ctrl.enable_write = 0)
#define __QSPI_STIG_WRITE_BYTES_SET(__QSPIx__, bytes)       (__QSPIx__->cmd_ctrl.write_bytes = (bytes)-1)
#define __QSPI_STIG_DUMMY_CYCLES_SET(__QSPIx__, cycles)     (__QSPIx__->cmd_ctrl.dummy_cycles = cycles)
#define __QSPI_STIG_EXECUTE(__QSPIx__)                      (__QSPIx__->cmd_ctrl.execute = 1)
#define __QSPI_STIG_ON_GOING(__QSPIx__)                     (__QSPIx__->cmd_ctrl.progress_status == 1)

#define __QSPI_STIG_DATA_L_SET(__QSPIx__, data_l)           (__QSPIx__->write_data_L = data_l)
#define __QSPI_STIG_DATA_H_SET(__QSPIx__, data_h)           (__QSPIx__->write_data_H = data_h)
#define __QSPI_STIG_DATA_L_GET(__QSPIx__)                   (__QSPIx__->read_data_L)
#define __QSPI_STIG_DATA_H_GET(__QSPIx__)                   (__QSPIx__->read_data_H)

#define __QSPI_CS_CTRL_RD_BRK_ENABLE(__QSPIx__)             (__QSPIx__->cs_ctrl.rd_brk_en = 1)
#define __QSPI_CS_CTRL_RD_BRK_DISABLE(__QSPIx__)            (__QSPIx__->cs_ctrl.rd_brk_en = 0)
#define __QSPI_CS_CTRL_DIS_CS_AFT_FIRST_BYTE_SET(__QSPIx__) (__QSPIx__->cs_ctrl.disable_cs_after_first_byte = 1)
#define __QSPI_CS_CTRL_DIS_CS_AFT_FIRST_BYTE_CLR(__QSPIx__) (__QSPIx__->cs_ctrl.disable_cs_after_first_byte = 0)
#define __QSPI_CS_PAGE_BOUNDARY_PROTECT_ENABLE(__QSPIx__)   (__QSPIx__->cs_ctrl.page_boundary_protect_en = 1)
#define __QSPI_CS_PAGE_BOUNDARY_PROTECT_DISABLE(__QSPIx__)  (__QSPIx__->cs_ctrl.page_boundary_protect_en = 0)
#define __QSPI_CS_PAGE_BOUNDARY_SET(__QSPIx__, _v)          (__QSPIx__->cs_ctrl.page_boundary = _v)

int qspi_stig_cmd(struct qspi_regs_t *QSPI, const struct qspi_stig_reg_t cmd, enum qspi_stig_cmd_type_t type, int len, uint8_t *buffer);

#endif /* _DRIVER_QSPI_H_ */

