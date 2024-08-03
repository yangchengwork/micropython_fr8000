/*
  ******************************************************************************
  * @file    driver_flash.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   Internal XIP Flash module driver.
  *          This file provides firmware functions to manage the internal
  *          stacked xip flash
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2042 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "fr30xx.h"

#define FLASH_ID_PUYA_P25Q32            0x00166085
#define FLASH_ID_PUYA_P25Q16            0x00156085
#define FLASH_ID_PUYA_P25Q80            0x00146085
#define FLASH_ID_PUYA_P25Q40            0x00136085
#define FLASH_ID_XMC_XM25LU32           0x00165020
#define FLASH_ID_XMC_XMQ25U80           0x00145020
#define FLASH_ID_GIANTEC_GT25Q16A       0x001560c4
#define FLASH_ID_GIANTEC_GT25Q80A       0x001460c4
#define FLASH_ID_GD_GD25WQ80E           0x001465c8

struct qspi_stig_reg_t sector_erase_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = QSPI_STIG_ADDR_BYTES_3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = FLASH_SECTORE_ERASE_OPCODE,
};

struct qspi_stig_reg_t read_id_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 3,
    .enable_read = 1,
    .opcode = FLASH_READ_IDENTIFICATION,
};

struct qspi_stig_reg_t read_uuid_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 7,
    .enable_read = 1,
    .opcode = 0x4b,
};

struct qspi_stig_reg_t read_status_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 1,
    .enable_read = 1,
    .opcode = 0x05,
};

struct qspi_stig_reg_t read_status_h_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 1,
    .enable_read = 1,
    .opcode = 0x35,
};

struct qspi_stig_reg_t write_enable_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x06,
};

struct qspi_stig_reg_t write_volatile_enable_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x50,
};

struct qspi_stig_reg_t write_status_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 1,
    .enable_write = 1,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x01,
};

struct qspi_stig_reg_t write_status_2_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 1,
    .enable_write = 1,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x31,
};

struct qspi_stig_reg_t write_status_3_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 1,
    .enable_write = 1,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x11,
};

struct qspi_stig_reg_t write_status_h_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 1,
    .enable_write = 1,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x31,
};

struct qspi_stig_reg_t block_erase_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = QSPI_STIG_ADDR_BYTES_3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0xD8,
};

struct qspi_stig_reg_t chip_erase_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x60,
};

struct qspi_stig_reg_t write_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 1,
    .addr_bytes = QSPI_STIG_ADDR_BYTES_3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x02,
};

struct qspi_stig_reg_t write_disable_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0x04,
};

struct qspi_stig_reg_t read_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = QSPI_STIG_ADDR_BYTES_3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 0,
    .enable_read = 1,
    .opcode = 0x03,
};

struct qspi_stig_reg_t deep_sleep_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0xB9,
};

struct qspi_stig_reg_t wakeup_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 0,
    .enable_mode = 0,
    .enable_cmd_addr = 0,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = 0xAB,
};

struct qspi_stig_reg_t sec_sector_erase_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = QSPI_STIG_ADDR_BYTES_3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = FLASH_SEC_REG_ERASE_OPCODE,
};

struct qspi_stig_reg_t sec_sector_read_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 1,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = QSPI_STIG_ADDR_BYTES_3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 0,
    .enable_read = 1,
    .opcode = FLASH_SEC_REG_READ_OPCODE,
};

struct qspi_stig_reg_t sec_sector_write_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 1,
    .addr_bytes = QSPI_STIG_ADDR_BYTES_3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 0,
    .enable_read = 0,
    .opcode = FLASH_SEC_REG_PROGRAM_OPCODE,
};

struct qspi_stig_reg_t read_uid_cmd = {
    .enable_bank = 0,
    .dummy_cycles = 0,
    .write_bytes = 0,
    .enable_write = 0,
    .addr_bytes = 3,
    .enable_mode = 0,
    .enable_cmd_addr = 1,
    .read_bytes = 7,
    .enable_read = 1,
    .opcode = 0x4b,
};

__RAM_CODE __attribute__((noinline)) void flash_wait_wip_clear(struct qspi_regs_t *qspi)
{
    uint8_t status;
    
    while(1) {
        system_delay_us(100);
        qspi_stig_cmd(qspi, read_status_cmd, QSPI_STIG_CMD_READ, 1, &status);
        if((status & 0x01) == 0) {
            break;
        }
    }
}

__RAM_CODE void flash_enable_quad(struct qspi_regs_t *qspi)
{
    uint8_t status[2];
    uint32_t flash_id;

    qspi_stig_cmd(qspi, read_status_cmd, QSPI_STIG_CMD_READ, 1, &status[0]);
    qspi_stig_cmd(qspi, read_status_h_cmd, QSPI_STIG_CMD_READ, 1, &status[1]);
    if((status[1] & 0x02) == 0x02) {
        return;
    }
    
    flash_id = flash_read_id(qspi);
    if ((flash_id == FLASH_ID_PUYA_P25Q32)
            || (flash_id == FLASH_ID_PUYA_P25Q16)
            || (flash_id == FLASH_ID_XMC_XM25LU32)
            || (flash_id == FLASH_ID_XMC_XMQ25U80)
            || (flash_id == FLASH_ID_GIANTEC_GT25Q16A )
            || (flash_id == FLASH_ID_GIANTEC_GT25Q80A)) {
        status[1] |= 0x02;  //enable quad mode
        qspi_stig_cmd(qspi, write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
        qspi_stig_cmd(qspi, write_status_h_cmd, QSPI_STIG_CMD_WRITE, 1, &status[1]);
    }
    else if ((flash_id == FLASH_ID_GD_GD25WQ80E)
            || (flash_id == FLASH_ID_PUYA_P25Q80)
            || (flash_id == FLASH_ID_PUYA_P25Q40)) {
        status[1] |= 0x02;  //enable quad mode
        qspi_stig_cmd(qspi, write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
        qspi_stig_cmd(qspi, write_status_cmd, QSPI_STIG_CMD_WRITE, 2, &status[0]);
    }
    else {
        while(1);
    }

    flash_wait_wip_clear(qspi);
}

__RAM_CODE void flash_set_IO_DRV(struct qspi_regs_t *qspi, uint8_t drv)
{
    uint8_t data;

    data = (drv<<5) | 0x0c;
    qspi_stig_cmd(qspi, write_volatile_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    qspi_stig_cmd(qspi, write_status_3_cmd, QSPI_STIG_CMD_WRITE, 1, &data);
}

__RAM_CODE void flash_set_capture_delay(struct qspi_regs_t *qspi, uint8_t delay)
{
    __QSPI_READ_CAPTURE_DELAY_SET(qspi, delay);
}

__RAM_CODE void flash_set_read_dtr_fast_quad(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_PAGE_DTR_QUAL_READ_OPCODE);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_QIO);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_QIO);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 7);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 1);
    __QSPI_MODE_BIT_SET(qspi, 0);
    
//    __QSPI_CFG_DTR_ENABLE(qspi);
    __QSPI_READ_DDR_ENABLE(qspi);
}

__RAM_CODE void flash_set_read_fast_quad(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_PAGE_QUAL_READ_OPCODE);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_QIO);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_QIO);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 4);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 1);
    __QSPI_MODE_BIT_SET(qspi, 0);
}

__RAM_CODE void flash_set_read_quad(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_PAGE_QUAL_READ_OPCODE_2);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_QIO);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 8);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 0);
    __QSPI_MODE_BIT_SET(qspi, 0);
}

__RAM_CODE void flash_set_read_dtr_fast_dual(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_READ_DTR_DUAL_OPCODE);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_DIO);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_DIO);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 0);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 0);
    __QSPI_MODE_BIT_SET(qspi, 0);
    
//    __QSPI_CFG_DTR_ENABLE(qspi);
    __QSPI_READ_DDR_ENABLE(qspi);
}

__RAM_CODE void flash_set_read_fast_dual(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_READ_DUAL_OPCODE);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_DIO);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_DIO);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 0);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 1);
    __QSPI_MODE_BIT_SET(qspi, 0);
}

__RAM_CODE void flash_set_read_dual(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_READ_DUAL_OPCODE_2);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_DIO);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 8);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 0);
    __QSPI_MODE_BIT_SET(qspi, 0);
}

__RAM_CODE void flash_set_read_dtr_fast_single(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_FAST_DTR_READ_OPCODE);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 6);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 0);
    __QSPI_MODE_BIT_SET(qspi, 0);
    
//    __QSPI_CFG_DTR_ENABLE(qspi);
    __QSPI_READ_DDR_ENABLE(qspi);
}

__RAM_CODE void flash_set_read_fast_single(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_FAST_READ_OPCODE);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 8);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 0);
    __QSPI_MODE_BIT_SET(qspi, 0);
}

__RAM_CODE void flash_set_read_single(struct qspi_regs_t *qspi)
{
    __QSPI_READ_OPCODE_SET(qspi, FLASH_READ_OPCODE);
    __QSPI_READ_INSTRUCTION_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_READ_DUMMY_CYCLES_SET(qspi, 0);
    __QSPI_READ_MODE_ENABLE_SET(qspi, 0);
    __QSPI_MODE_BIT_SET(qspi, 0);
}

__RAM_CODE void flash_set_write_quad(struct qspi_regs_t *qspi)
{
    __QSPI_WRITE_OPCODE_SET(qspi, FLASH_PAGE_QUAL_PROGRAM_OPCODE);
    __QSPI_WRITE_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_WRITE_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_QIO);
    __QSPI_WRITE_DUMMY_CYCLES_SET(qspi, 0);
}

__RAM_CODE void flash_set_write_dual(struct qspi_regs_t *qspi)
{
    __QSPI_WRITE_OPCODE_SET(qspi, FLASH_PAGE_DUAL_PROGRAM_OPCODE);
    __QSPI_WRITE_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_WRITE_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_DIO);
    __QSPI_WRITE_DUMMY_CYCLES_SET(qspi, 0);
}

__RAM_CODE void flash_set_write_single(struct qspi_regs_t *qspi)
{
    __QSPI_WRITE_OPCODE_SET(qspi, FLASH_PAGE_PROGRAM_OPCODE);
    __QSPI_WRITE_ADDRESS_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_WRITE_DATA_TYPE_SET(qspi, QSPI_WIRE_TYPE_STAND);
    __QSPI_WRITE_DUMMY_CYCLES_SET(qspi, 0);
}

__RAM_CODE void flash_set_read_type(struct qspi_regs_t *qspi, uint8_t rd_type)
{
    switch(rd_type) {
        case FLASH_RD_TYPE_SINGLE:
            flash_set_read_single(qspi);
            break;
        case FLASH_RD_TYPE_SINGLE_FAST:
            flash_set_read_fast_single(qspi);
            break;
        case FLASH_RD_TYPE_DUAL:
            flash_set_read_dual(qspi);
            break;
        case FLASH_RD_TYPE_DUAL_FAST:
            flash_set_read_fast_dual(qspi);
            break;
        case FLASH_RD_TYPE_QUAD:
            flash_set_read_quad(qspi);
            break;
        case FLASH_RD_TYPE_QUAD_FAST:
            flash_set_read_fast_quad(qspi);
            break;
        case FLASH_RD_TYPE_DTR_SINGLE_FAST:
            flash_set_read_dtr_fast_single(qspi);
            break;
        case FLASH_RD_TYPE_DTR_DUAL_FAST:
            flash_set_read_dtr_fast_dual(qspi);
            break;
        case FLASH_RD_TYPE_DTR_QUAD_FAST:
            flash_set_read_dtr_fast_quad(qspi);
            break;
        default:
            flash_set_read_single(qspi);
            break;
    }
}

__RAM_CODE void flash_set_write_type(struct qspi_regs_t *qspi, uint8_t wr_type)
{
    switch(wr_type) {
        case FLASH_WR_TYPE_SINGLE:
            flash_set_write_single(qspi);
            break;
        case FLASH_WR_TYPE_DUAL:
            flash_set_write_dual(qspi);
            break;
        case FLASH_WR_TYPE_QUAD:
            flash_set_write_quad(qspi);
            break;
        default:
            flash_set_write_single(qspi);
            break;
    }
}

__RAM_CODE void flash_init_controller(struct qspi_regs_t *qspi, enum flash_rd_type_t rd_type, enum flash_wr_type_t wr_type)
{
    while(__QSPI_IS_BUSY(qspi));

    flash_set_read_type(qspi, rd_type);
    flash_set_write_type(qspi, wr_type);
    
    __QSPI_POLL_OPCODE_SET(qspi, 0x05);
    __QSPI_POLL_BIT_INDEX_SET(qspi, 0);
    __QSPI_POLL_POLARITY_SET(qspi, 0);
    __QSPI_POLL_EXPIRATION_SET(qspi, 0);
    __QSPI_POLL_EXPIRE_DISABLE(qspi);
    __QSPI_POLL_COUNT_SET(qspi, 2);
    __QSPI_POLL_DELAY_SET(qspi, 16);
    __QSPI_POLL_DISABLE(qspi);

    //init configuration register
    __QSPI_CFG_CPOL_SET(qspi, 1);
    __QSPI_CFG_CPHA_SET(qspi, 1);
    __QSPI_CFG_DAC_ENABLE(qspi);
    __QSPI_CFG_LEGACY_DISABLE(qspi);
    __QSPI_CFG_REMAP_ENABLE(qspi);
    __QSPI_CFG_BAUDRATE_SET(qspi, QSPI_BAUDRATE_DIV_16);

    __QSPI_CFG_AHB_DECODER_ENABLE(qspi);

    __QSPI_DELAY_CS_START_SET(qspi, 2);
    __QSPI_DELAY_CS_END_SET(qspi, 2);

    __QSPI_REMAP_ADDRESS_SET(qspi, 0);

    __QSPI_ENABLE(qspi);
}

uint32_t flash_read_id(struct qspi_regs_t *qspi)
{
    uint32_t flash_id;
    
    qspi_stig_cmd(qspi, read_id_cmd, QSPI_STIG_CMD_READ, 3, (uint8_t *)&flash_id);

    return (flash_id&0xffffff);
}

void flash_read_uid(struct qspi_regs_t *qspi, uint8_t *flash_uid)
{
    qspi_stig_cmd(qspi, read_uid_cmd,QSPI_STIG_CMD_READ, 8, flash_uid);
//    printf("LOT ID: 0x%02x%02x%02x%02x\r\n",flash_uid[3],flash_uid[2],flash_uid[1],flash_uid[0]);
//    printf("WAFER ID: 0x%02x\r\n",flash_uid[4]);
//    printf("X: %04x, Y: %04x\r\n",(flash_uid[5]<<4)|(flash_uid[6]>>4),((flash_uid[6]&0x0f)<<8)|flash_uid[7]);
//    printf("\r\n");
}

__RAM_CODE void flash_set_baudrate(struct qspi_regs_t *qspi, uint8_t baudrate)
{
    if (baudrate <= QSPI_BAUDRATE_DIV_32) {
        GLOBAL_INT_DISABLE();
        while(__QSPI_IS_BUSY(qspi));
        __QSPI_CFG_BAUDRATE_SET(qspi, baudrate);
        if ((baudrate == QSPI_BAUDRATE_DIV_2)
            || ((baudrate == QSPI_BAUDRATE_DIV_4) && (__QSPI_READ_DDR_GET(qspi) == 1))) {
            __QSPI_READ_CAPTURE_DELAY_SET(qspi, 2);
        }
        GLOBAL_INT_RESTORE();
    }
}

uint32_t flash_init(struct qspi_regs_t *qspi)
{
    flash_exit_deep_sleep(qspi);

    return flash_read_id(qspi);
}

uint16_t flash_read_status(struct qspi_regs_t *qspi, bool read_high)
{
    uint8_t *status;
    uint16_t status_entity;

    status = (uint8_t *)&status_entity;

    qspi_stig_cmd(qspi, read_status_cmd, QSPI_STIG_CMD_READ, 1, &status[0]);
    if(read_high) {
        qspi_stig_cmd(qspi, read_status_h_cmd, QSPI_STIG_CMD_READ, 1, &status[1]);
    }

    return status_entity;
}

__RAM_CODE void flash_write_status(struct qspi_regs_t *qspi, uint16_t status, bool write_high)
{
    uint8_t count = 1;

    if(write_high) {
        count++;
    }

    qspi_stig_cmd(qspi, write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    qspi_stig_cmd(qspi, write_status_cmd, QSPI_STIG_CMD_WRITE, count, (void *)&status);

    flash_wait_wip_clear(qspi);
}

__RAM_CODE void flash_write_status_2(struct qspi_regs_t *qspi, uint8_t status)
{
    qspi_stig_cmd(qspi, write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    qspi_stig_cmd(qspi, write_status_2_cmd, QSPI_STIG_CMD_WRITE, 1, (void *)&status);

    flash_wait_wip_clear(qspi);
}

__RAM_CODE void flash_write_status_volatile(struct qspi_regs_t *qspi, uint16_t status, bool write_high)
{
    uint8_t count = 1;
    uint8_t poll_status;

    if(write_high) {
        count++;
    }
    
    qspi_stig_cmd(qspi, write_volatile_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    qspi_stig_cmd(qspi, write_status_cmd, QSPI_STIG_CMD_WRITE, count, (void *)&status);
}

__RAM_CODE  void flash_write_status_2_volatile(struct qspi_regs_t *qspi, uint8_t status)
{
    qspi_stig_cmd(qspi, write_volatile_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    qspi_stig_cmd(qspi, write_status_2_cmd, QSPI_STIG_CMD_WRITE, 1, (void *)&status);
}

/************************************************************************************
 * @fn      flash_protect_bit_set
 *
 * @brief   set flash protection relevant bits.
 *
 * @param   qspi: qspi controller base address
 *          bits: flash protection bits in status 1, BIT4:0 is valid.
 *          cmp:  flash protection compare bit in status 2. 
 *                  0xff means this field should be ignored
 *                  BIT7: clear or set CMP bit
 *                  BIT0-2: CMP bit offset in status 2
 *          wr_volatile: write status registers in volatile mode or not
 *          status_2_separate: write status 2 together with status 1 or separately
 */
__RAM_CODE void flash_protect_bit_set(struct qspi_regs_t *qspi, uint8_t bits, uint8_t cmp, uint8_t wr_volatile, uint8_t status_2_separate)
{
    uint8_t status[2];
    uint16_t status_tmp;
    uint8_t skip_status_1 = 0;

    if(cmp != 0xff) {
        status_tmp = flash_read_status(qspi, true);
        status[0] = status_tmp & 0xff;
        status[1] = (status_tmp>>8) & 0xff;

        if(cmp & 0x80) {
            // set cmp bit
            if((status[1] & (1<<(cmp&0x07))) != 0) {
                cmp = 0xff;
            }
            else {
                status[1] |= (1<<(cmp&0x07));
            }
        }
        else {
            // clear cmp bit
            if((status[1] & (1<<(cmp&0x07))) == 0) {
                cmp = 0xff;
            }
            else {
                status[1] &= (~(1<<(cmp&0x07)));
            }
        }
    }
    else {
        status_tmp = flash_read_status(qspi, false);
        status[0] = status_tmp & 0xff;
    }

    bits &= 0x1f;

    if((status[0] & 0x7C) == (bits << 2)) {
        skip_status_1 = 1;
        if (cmp == 0xff) {
            return;
        }
    }

    status[0] &= 0x80;
    status[0] |= (bits << 2);

    GLOBAL_INT_DISABLE();
    if(cmp != 0xff) {
        if(status_2_separate) {
            if(wr_volatile) {
                if(skip_status_1 == 0) {
                    flash_write_status_volatile(qspi, status[0], false);
                }
                flash_write_status_2_volatile(qspi, status[1]);
            }
            else {
                if(skip_status_1 == 0) {
                    flash_write_status(qspi, status[0], false);
                }
                flash_write_status_2(qspi, status[1]);
            }
        }
        else {
            status_tmp = status[0] | (status[1]<<8);
            if(wr_volatile) {
                flash_write_status_volatile(qspi, status_tmp, true);
            }
            else {
                flash_write_status(qspi, status_tmp, true);
            }
        }
    }
    else {
        if(wr_volatile) {
            flash_write_status_volatile(qspi, status[0], false);
        }
        else {
            flash_write_status(qspi, status[0], false);
        }
    }
    GLOBAL_INT_RESTORE();
}

static __RAM_CODE __attribute__((noinline)) void do_write(const uint8_t *src, uint8_t *dst, uint32_t length)
{
    __asm (
        " B        CHECK        \n"
        "COPY_NEXT:             \n"
        " LDRB     r4,[%0],#1   \n"
        " STRB     r4,[%1],#1   \n"
        " SUBS     %2, %2, #1   \n"
        "CHECK:                 \n"
        " CMP      %2, #0       \n"
        " BNE      COPY_NEXT    \n"
        :
        : "r"(src), "r"(dst), "r"(length)
        : "r4"
    );
}

__RAM_CODE __attribute__((noinline)) uint8_t flash_write(struct qspi_regs_t *qspi, uint32_t offset, uint32_t length, const uint8_t *buffer)
{
    uint32_t page_left;
    uint32_t dac_addr_offset;
    uint8_t *dst;

    if(length == 0) {
        return 0;
    }
    
    if ((uint32_t)qspi == FLASH_QSPI_BASE) {
        dac_addr_offset = FLASH_DAC_BASE;
    }
    else if ((uint32_t)qspi == DSP_QSPI_BASE) {
        dac_addr_offset = DSP_FLASH_DAC_BASE;
    }
    else {
        return 0;
    }
    
    page_left = 0x100 - (offset & 0xff);
    if(length < page_left) {
        page_left = length;
    }
    
    dst = (void *)(offset | dac_addr_offset);
    GLOBAL_INT_DISABLE();
    if ((uint32_t)qspi == FLASH_QSPI_BASE) {
        system_cache_disable();
        flash_protect_bit_set(QSPI0, 0x00, 0x06, true, true);
    }
    while(length) {
        do_write(buffer, dst, page_left);
        buffer += page_left;
        dst += page_left;
        flash_wait_wip_clear(qspi);

        length -= page_left;
        page_left = (length > 256) ? 256 : length;
    }
    if ((uint32_t)qspi == FLASH_QSPI_BASE) {
        flash_protect_bit_set(QSPI0, 0x1f, 0x06, true, true);
        system_cache_enable(true);
    }
    GLOBAL_INT_RESTORE();

    return 0;
}

uint8_t flash_read(struct qspi_regs_t *qspi, uint32_t offset, uint32_t length, uint8_t *buffer)
{
    if ((uint32_t)qspi == FLASH_QSPI_BASE) {
        memcpy(buffer, (void *)(offset | FLASH_DAC_BASE), length);
    }
    else if((uint32_t)qspi == DSP_QSPI_BASE) {
        memcpy(buffer, (void *)(offset | DSP_FLASH_DAC_BASE), length);
    }

    return 0;
}

__RAM_CODE __attribute__((noinline)) uint8_t flash_erase(struct qspi_regs_t *qspi, uint32_t offset, uint32_t size)
{
    if(size == 0) {
        size = 0x1000;
    }
    
    offset &= 0xFFFFF000;
    GLOBAL_INT_DISABLE();
    if ((uint32_t)qspi == FLASH_QSPI_BASE) {
        system_cache_disable();
        flash_protect_bit_set(QSPI0, 0x00, 0x06, true, true);
    }
    while(size) {
        qspi_stig_cmd(qspi, write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
        __QSPI_CMD_ADDRESS_SET(qspi, offset);
        qspi_stig_cmd(qspi, sector_erase_cmd, QSPI_STIG_CMD_EXE, 0, 0);
        flash_wait_wip_clear(qspi);

        offset += 0x1000;
        if(size > 0x1000)
            size -= 0x1000;
        else {
            size = 0;
        }
    }
    if ((uint32_t)qspi == FLASH_QSPI_BASE) {
        flash_protect_bit_set(QSPI0, 0x1f, 0x06, true, true);
        system_cache_enable(true);
    }
    GLOBAL_INT_RESTORE();
    
    return 0;
}

__RAM_CODE void flash_chip_erase(struct qspi_regs_t *qspi)
{
    qspi_stig_cmd(qspi, write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    qspi_stig_cmd(qspi, chip_erase_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    system_delay_us(20);
    
    flash_wait_wip_clear(qspi);
}

__RAM_CODE void flash_enter_deep_sleep(struct qspi_regs_t *qspi)
{
    qspi_stig_cmd(qspi, deep_sleep_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    system_delay_us(20);
}

__RAM_CODE void flash_exit_deep_sleep(struct qspi_regs_t *qspi)
{
    qspi_stig_cmd(qspi, wakeup_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    system_delay_us(20);
}


/*********************************************************************
* @fn      flash_OTP_read
*
* @brief   read data from OTP sections. otp section size: 512 = 0x200 
*
* @param   offset - Security flash section offset, only valid for 0x1000,0x2000,0x3000 
*          length - buffer length to be read from security flash section. rang[1,512]
*          buffer - pointer to buffer which will store data
*
* @return  None.
*/
__RAM_CODE void flash_OTP_read(struct qspi_regs_t *qspi,uint32_t offset, uint32_t length, uint8_t *buffer)
{
    uint32_t i = 0;

    offset &= 0x3000;
    if(length > 512) 
        length = 512;

    GLOBAL_INT_DISABLE();
    for(; (i+8) <= length; )
    {
        __QSPI_CMD_ADDRESS_SET(qspi, offset);
        qspi_stig_cmd(qspi,sec_sector_read_cmd, QSPI_STIG_CMD_READ, 8, buffer + i );
        i+=8;
        offset+=8;
    }
    if(i < length)          
    {
        __QSPI_CMD_ADDRESS_SET(qspi, offset);
        qspi_stig_cmd(qspi,sec_sector_read_cmd, QSPI_STIG_CMD_READ, (length-i), (buffer+i));
    }
    GLOBAL_INT_RESTORE();
}

/*********************************************************************
* @fn      flash_OTP_write
*
* @brief   write data to OTP sections. otp section size: 512 = 0x200 
*
* @param   offset - Security flash section offset, only valid for 0x1000,0x2000,0x3000 
*          length - buffer length to be written into security flash section. rang[1,512]
*          buffer - pointer to buffer which will be written
*
* @return  None.
*/
__RAM_CODE void flash_OTP_write(struct qspi_regs_t *qspi,uint32_t offset, uint32_t length, uint8_t *buffer)
{
    uint8_t status[1];
    uint32_t i = 0;

#define SINGLE_LENGTH       8
    offset &= 0x3000;
    if(length > 512) 
        length = 512;

    GLOBAL_INT_DISABLE();

    for(; (i+SINGLE_LENGTH) <= length; )
    {
        qspi_stig_cmd(qspi,write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
        __QSPI_CMD_ADDRESS_SET(qspi, offset);
        qspi_stig_cmd(qspi,sec_sector_write_cmd, QSPI_STIG_CMD_WRITE, SINGLE_LENGTH, buffer+i);
        while(1) {
            system_delay_us(20);
            qspi_stig_cmd(qspi,read_status_cmd, QSPI_STIG_CMD_READ, 1, &status[0]);
            if((status[0] & 0x01) == 0) {
                break;
            }
        }
        qspi_stig_cmd(qspi,write_disable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
        i+=SINGLE_LENGTH;
        offset+=SINGLE_LENGTH;
    }
    if(i < length)          
    {
        qspi_stig_cmd(qspi,write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
        __QSPI_CMD_ADDRESS_SET(qspi, offset);
        qspi_stig_cmd(qspi,sec_sector_write_cmd, QSPI_STIG_CMD_WRITE, (length-i), (buffer+i));
        while(1) {
            system_delay_us(20);
            qspi_stig_cmd(qspi,read_status_cmd, QSPI_STIG_CMD_READ, 1, &status[0]);
            if((status[0] & 0x01) == 0) {
                break;
            }
        }
        qspi_stig_cmd(qspi,write_disable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    }
    
    GLOBAL_INT_RESTORE();
}

/*********************************************************************
* @fn      flash_OTP_erase
*
* @brief   erase whole OTP section . 
*
* @param   offset - Security flash section offset, only valid for 0x1000,0x2000,0x3000 
*
* @return  None.
*/
__RAM_CODE void flash_OTP_erase(struct qspi_regs_t *qspi,uint32_t offset)
{
    uint8_t status;
    offset &= 0x3000;

    GLOBAL_INT_DISABLE();
    qspi_stig_cmd(qspi,write_enable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    __QSPI_CMD_ADDRESS_SET(qspi, offset);
    qspi_stig_cmd(qspi,sec_sector_erase_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    
    while(1) {
        system_delay_us(20);
        qspi_stig_cmd(qspi,read_status_cmd, QSPI_STIG_CMD_READ, 1, &status);
        if((status & 0x01) == 0) {
            break;
        }
    }
    qspi_stig_cmd(qspi,write_disable_cmd, QSPI_STIG_CMD_EXE, 0, 0);
    GLOBAL_INT_RESTORE();
}

/*********************************************************************
* @fn      flash_read_uuid
*
* @brief   read out UUID of internal flash. 
*
* @param   buffer - point to a 8-bytes buffer used to store UUID 
*
* @return  None.
*/
__RAM_CODE void flash_read_uuid(struct qspi_regs_t *qspi, uint8_t *buffer, uint8_t *length)
{
    uint32_t flash_id;
    
    if ((*length == 0) || (buffer == 0)) {
        return;
    }
    
    GLOBAL_INT_DISABLE();
    flash_id = flash_read_id(qspi);
    if ((flash_id == FLASH_ID_GIANTEC_GT25Q16A)
            || (flash_id == FLASH_ID_GIANTEC_GT25Q80A)) {
        uint8_t _length = *length > 8 ? 8 : *length;
        __QSPI_CMD_ADDRESS_SET(qspi, 0);
        qspi_stig_cmd(qspi, read_uuid_cmd, QSPI_STIG_CMD_READ, _length, buffer);
        *length = _length;
    }
    else if (flash_id == FLASH_ID_PUYA_P25Q16) {
        uint8_t _length = *length > 16 ? 16 : *length;
        while (__QSPI_IS_BUSY(qspi));
        uint32_t org_cfg = *(volatile uint32_t *)&qspi->read_conf;
        uint32_t org_addr_bytes = qspi->size_cfg.addr_bytes;
        *(volatile uint32_t *)&qspi->read_conf = 0x0000004b;
        qspi->size_cfg.addr_bytes = 3;
        system_cache_disable();
        uint8_t *ptr = (void *)0x08000000;
        do_write(ptr, buffer, _length);
        while (__QSPI_IS_BUSY(qspi));
        system_cache_enable(false);
        *(volatile uint32_t *)&qspi->read_conf = org_cfg;
        qspi->size_cfg.addr_bytes = org_addr_bytes;
        *length = _length;
    }
    else {
        *length = 0;
    }
    GLOBAL_INT_RESTORE();
}

/*********************************************************************
* @fn      flash_read_uuid
*
* @brief   read out UUID of internal flash. 
*
* @param   buffer - point to a 8-bytes buffer used to store UUID 
* @param   type - type of request UUID, @ref flash_gen_uuid_type_t
*
* @return  None.
*/
__RAM_CODE void flash_gen_uuid(struct qspi_regs_t *qspi, uint8_t *buffer, enum flash_gen_uuid_type_t type)
{
    uint32_t flash_id;
    uint8_t _buffer[16];

    GLOBAL_INT_DISABLE();
    flash_id = flash_read_id(qspi);
    GLOBAL_INT_RESTORE();
    if ((flash_id == FLASH_ID_GIANTEC_GT25Q16A)
            || (flash_id == FLASH_ID_GIANTEC_GT25Q80A)) {
        volatile uint32_t lot_id_bcd, lot_id_bin;
        GLOBAL_INT_DISABLE();
        __QSPI_CMD_ADDRESS_SET(qspi, 0);
        qspi_stig_cmd(qspi, read_uuid_cmd, QSPI_STIG_CMD_READ, 8, _buffer);
        GLOBAL_INT_RESTORE();

        lot_id_bcd = _buffer[0] | (_buffer[1]<<8);
        lot_id_bin = 0;
        for (uint8_t i=0; i<4; i++) {
            lot_id_bin *= 10;
            lot_id_bin += (lot_id_bcd>>((3-i)*4))&0xf;
        }
        if (type == FLASH_GEN_UUID_TYPE_12) {
            buffer[0] = lot_id_bin & 0xff;
            buffer[1] = (lot_id_bin >> 8) & 0x0f;
        }
        else {
            buffer[0] = _buffer[7];
            buffer[1] = _buffer[6];
            buffer[2] = _buffer[5];
            lot_id_bin %= 2600;
            lot_id_bin *= 25;
            lot_id_bin += _buffer[4];
            buffer[3] = lot_id_bin & 0xff;
            buffer[4] = (lot_id_bin>>8) & 0xff;
        }
    }
    else if (flash_id == FLASH_ID_PUYA_P25Q16) {
        uint32_t lot_id_bin;
        GLOBAL_INT_DISABLE();
        while (__QSPI_IS_BUSY(qspi));
        uint32_t org_cfg = *(volatile uint32_t *)&qspi->read_conf;
        uint32_t org_addr_bytes = qspi->size_cfg.addr_bytes;
        *(volatile uint32_t *)&qspi->read_conf = 0x0000004b;
        qspi->size_cfg.addr_bytes = 3;
        system_cache_disable();
        uint8_t *ptr = (void *)0x08000000;
        uint8_t *dst = &_buffer[0];
        do_write(ptr, dst, 16);
        while (__QSPI_IS_BUSY(qspi));
        system_cache_enable(false);
        *(volatile uint32_t *)&qspi->read_conf = org_cfg;
        qspi->size_cfg.addr_bytes = org_addr_bytes;
        GLOBAL_INT_RESTORE();

        lot_id_bin = (_buffer[6]-'0')
                        + (_buffer[5]-'0')*10
                        + (_buffer[4]-'0')*100;
        if (type == FLASH_GEN_UUID_TYPE_12) {
            buffer[0] = lot_id_bin & 0xff;
            buffer[1] = (lot_id_bin >> 8) & 0x0f;
        }
        else {
            buffer[0] = _buffer[11];
            buffer[1] = _buffer[10];
            buffer[2] = _buffer[9];
            if (_buffer[3] >= 'A') {
                lot_id_bin += ((_buffer[3] - 'A' + 10) * 1000);
            }
            else {
                lot_id_bin += ((_buffer[3] - '0') * 1000);
            }
            lot_id_bin %= 2600;
            lot_id_bin *= 25;
            lot_id_bin += _buffer[7];
            buffer[3] = lot_id_bin & 0xff;
            buffer[4] = (lot_id_bin>>8) & 0xff;
        }
    }    
}
