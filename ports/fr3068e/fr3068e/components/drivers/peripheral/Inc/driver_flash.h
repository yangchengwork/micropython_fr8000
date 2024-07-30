/*
 * flash.h
 *
 *  Created on: 2018-1-25
 *      Author: owen
 */

#ifndef _DRIVER_FLASH_H
#define _DRIVER_FLASH_H

#include <stdint.h>
#include <stdbool.h>

#include "driver_qspi.h"

#define FLASH_READ_DEVICE_ID            0x90
#define FLASH_READ_IDENTIFICATION       0x9F
    
#define FLASH_AAI_PROGRAM_OPCODE        0xAF
#define FLASH_PAGE_PROGRAM_OPCODE       0x02
#define FLASH_READ_OPCODE               0x03
#define FLASH_FAST_READ_OPCODE          0x0B
#define FLASH_FAST_DTR_READ_OPCODE      0x0D
#define FLASH_READ_DUAL_OPCODE          0xBB
#define FLASH_READ_DTR_DUAL_OPCODE      0xBD
#define FLASH_READ_DUAL_OPCODE_2        0x3B
#define FLASH_PAGE_DUAL_PROGRAM_OPCODE  0xA2
#define FLASH_PAGE_QUAL_READ_OPCODE     0xEB
#define FLASH_PAGE_DTR_QUAL_READ_OPCODE 0xED
#define FLASH_PAGE_QUAL_READ_OPCODE_2   0x6B
#define FLASH_PAGE_QUAL_PROGRAM_OPCODE  0x32

    
#define FLASH_CHIP_ERASE_OPCODE         0x60
#define FLASH_SECTORE_ERASE_OPCODE      0x20
#define FLASH_BLOCK_32K_ERASE_OPCODE    0x52
#define FLASH_BLOCK_64K_ERASE_OPCODE    0xD8
#define FLASH_ST_SECTORE_ERASE_OPCODE   0xD8
#define FLASH_ST_BULK_ERASE_OPCODE      0xC7
    
#define FLASH_WRITE_DISABLE_OPCODE      0x04
#define FLASH_WRITE_ENABLE_OPCODE       0x06
#define FLASH_WRITE_STATUS_REG_OPCODE   0x01
#define FLASH_READ_STATUS_REG_OPCODE    0x05
#define FLASH_READ_STATUS_HIGH_REG_OPCODE    0x35

#define FLASH_SEC_REG_READ_OPCODE       (0x48)
#define FLASH_SEC_REG_PROGRAM_OPCODE    (0x42)
#define FLASH_SEC_REG_ERASE_OPCODE      (0x44)

#define FLASH_ST_ID                     0x20
#define FLASH_SST_ID                    0xBF

#define FLASH_OP_TYPE_ERASE             0
#define FLASH_OP_TYPE_WRITE             1

enum flash_gen_uuid_type_t {
    FLASH_GEN_UUID_TYPE_40,
    FLASH_GEN_UUID_TYPE_12,
};

enum flash_rd_type_t {
    FLASH_RD_TYPE_SINGLE,
    FLASH_RD_TYPE_SINGLE_FAST,
    FLASH_RD_TYPE_DUAL,
    FLASH_RD_TYPE_DUAL_FAST,
    FLASH_RD_TYPE_QUAD,
    FLASH_RD_TYPE_QUAD_FAST,
    FLASH_RD_TYPE_DTR_SINGLE_FAST,
    FLASH_RD_TYPE_DTR_DUAL_FAST,
    FLASH_RD_TYPE_DTR_QUAD_FAST,
};

enum flash_wr_type_t {
    FLASH_WR_TYPE_SINGLE,
    FLASH_WR_TYPE_DUAL,
    FLASH_WR_TYPE_QUAD,
};

void flash_set_read_fast_quad(struct qspi_regs_t *qspi);
void flash_set_read_quad(struct qspi_regs_t *qspi);
void flash_set_read_fast_dual(struct qspi_regs_t *qspi);
void flash_set_read_dual(struct qspi_regs_t *qspi);
void flash_set_read_fast_single(struct qspi_regs_t *qspi);
void flash_set_read_single(struct qspi_regs_t *qspi);
void flash_set_write_quad(struct qspi_regs_t *qspi);
void flash_set_write_dual(struct qspi_regs_t *qspi);
void flash_set_write_single(struct qspi_regs_t *qspi);

uint16_t flash_read_status(struct qspi_regs_t *qspi, bool read_high);
void flash_write_status(struct qspi_regs_t *qspi, uint16_t status_entity, bool write_high);
void flash_write_status_volatile(struct qspi_regs_t *qspi, uint16_t status, bool write_high);
void flash_write_status_2(struct qspi_regs_t *qspi, uint8_t status);
void flash_write_status_2_volatile(struct qspi_regs_t *qspi, uint8_t status);
uint8_t flash_write(struct qspi_regs_t *qspi, uint32_t offset, uint32_t length, const uint8_t *buffer);
uint8_t flash_read(struct qspi_regs_t *qspi, uint32_t offset, uint32_t length, uint8_t *buffer);
uint8_t flash_erase(struct qspi_regs_t *qspi, uint32_t offset, uint32_t size);
void flash_chip_erase(struct qspi_regs_t *qspi);
void flash_enter_deep_sleep(struct qspi_regs_t *qspi);
void flash_exit_deep_sleep(struct qspi_regs_t *qspi);
void flash_enable_quad(struct qspi_regs_t *qspi);
void flash_set_IO_DRV(struct qspi_regs_t *qspi, uint8_t drv);
void flash_set_capture_delay(struct qspi_regs_t *qspi, uint8_t delay);
void flash_init_controller(struct qspi_regs_t *qspi, enum flash_rd_type_t rd_type, enum flash_wr_type_t wr_type);
uint32_t flash_init(struct qspi_regs_t *qspi);
uint32_t flash_read_id(struct qspi_regs_t *qspi);
void flash_gen_uuid(struct qspi_regs_t *qspi, uint8_t *buffer, enum flash_gen_uuid_type_t type);

void flash_set_baudrate(struct qspi_regs_t *qspi, uint8_t baudrate);

void flash_OTP_read(struct qspi_regs_t *qspi,uint32_t offset, uint32_t length, uint8_t *buffer);
void flash_OTP_write(struct qspi_regs_t *qspi,uint32_t offset, uint32_t length, uint8_t *buffer);
void flash_OTP_erase(struct qspi_regs_t *qspi,uint32_t offset);

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
void flash_protect_bit_set(struct qspi_regs_t *qspi, uint8_t bits, uint8_t cmp, uint8_t wr_volatile, uint8_t status_2_separate);

#endif /* _DRIVER_FLASH_H */

