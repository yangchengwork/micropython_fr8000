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

#define FLASH_READ_DEVICE_ID            0x90
#define FLASH_READ_IDENTIFICATION       0x9F
    
#define FLASH_AAI_PROGRAM_OPCODE        0xAF
#define FLASH_PAGE_PROGRAM_OPCODE       0x02
#define FLASH_READ_OPCODE               0x03
#define FLASH_FAST_READ_OPCODE          0x0B
#define FLASH_READ_DUAL_OPCODE          0xBB
#define FLASH_READ_DUAL_OPCODE_2        0x3B
#define FLASH_PAGE_DUAL_PROGRAM_OPCODE  0xA2
#define FLASH_PAGE_QUAL_READ_OPCODE     0xEB
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

enum flash_rd_type_t {
    FLASH_RD_TYPE_SINGLE,
    FLASH_RD_TYPE_SINGLE_FAST,
    FLASH_RD_TYPE_DUAL,
    FLASH_RD_TYPE_DUAL_FAST,
    FLASH_RD_TYPE_QUAD,
    FLASH_RD_TYPE_QUAD_FAST,
};

enum flash_wr_type_t {
    FLASH_WR_TYPE_SINGLE,
    FLASH_WR_TYPE_DUAL,
    FLASH_WR_TYPE_QUAD,
};

extern void (*flash_erase_write_protect)(bool before_operation, uint8_t type);

void flash_set_read_fast_quad(void);
void flash_set_read_quad(void);
void flash_set_read_fast_dual(void);
void flash_set_read_dual(void);
void flash_set_read_fast_single(void);
void flash_set_read_single(void);
void flash_set_write_quad(void);
void flash_set_write_dual(void);
void flash_set_write_single(void);

uint16_t flash_read_status(bool read_high);
void flash_write_status(uint16_t status_entity, bool write_high);
void flash_write_status_volatile(uint16_t status, bool write_high);
uint8_t flash_write(uint32_t offset, uint32_t length, uint8_t *buffer);
uint8_t flash_read(uint32_t offset, uint32_t length, uint8_t *buffer);
uint8_t flash_write_legacy(uint32_t offset, uint32_t length, uint8_t *buffer);
uint8_t flash_read_legacy(uint32_t offset, uint32_t length, uint8_t *buffer);
uint8_t flash_erase(uint32_t offset, uint32_t size);
void flash_chip_erase(void);
//void flash_change_bitrate(uint8_t bitrate);
void flash_enter_deep_sleep(void);
void flash_exit_deep_sleep(void);
void flash_enable_quad(void);
void flash_init_controller(enum flash_rd_type_t rd_type, enum flash_wr_type_t wr_type);
uint32_t flash_init(enum flash_rd_type_t rd_type, enum flash_wr_type_t wr_type);
uint32_t flash_read_id(void);
void flash_protect_disable(uint8_t wr_mode);
void flash_protect_enable(uint8_t wr_mode);


/*********************************************************************
* @fn      flash_OTP_read / flash_OTP_write / flash_OTP_erase
*
* @brief   otp section size: 512 Byte 
*
* @param   offset - Security flash section offset, only valid for 0x1000,0x2000,0x3000 
*          length - buffer length to be read from security flash section. rang[1,512]
*          buffer - pointer to buffer which will store data
*/
void flash_OTP_read(uint32_t offset, uint32_t length, uint8_t *buffer);
void flash_OTP_write(uint32_t offset, uint32_t length, uint8_t *buffer);
void flash_OTP_erase(uint32_t offset);

#endif /* _DRIVER_FLASH_H */

