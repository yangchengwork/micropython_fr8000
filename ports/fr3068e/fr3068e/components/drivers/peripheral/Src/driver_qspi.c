/*
  ******************************************************************************
  * @file    driver_qspi.c
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2024
  * @brief   QSPI module driver.
  *          This file provides firmware functions to manage the 
  *          Quad Serial Peripheral Interface (QSPI) peripheral
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#include "fr30xx.h"

#define QSPI_STIG_MAX_SINGLE_LEN            8
#define QSPI_STIG_BANK_DEPTH                128

__RAM_CODE int qspi_stig_cmd(struct qspi_regs_t *QSPI, struct qspi_stig_reg_t cmd, enum qspi_stig_cmd_type_t type, int len, uint8_t *buffer)
{
    uint32_t tmp_u32[2];
    uint8_t *tmp_u8 = (uint8_t *)tmp_u32;

    if(type == QSPI_STIG_CMD_BANK_READ) {
        if(QSPI_STIG_BANK_DEPTH < len) {
            return -1;
        }
    }
    else {
        if(QSPI_STIG_MAX_SINGLE_LEN < len) {
            return -1;
        }
    }

    while(__QSPI_IS_BUSY(QSPI));

    if(type == QSPI_STIG_CMD_EXE) {
        __QSPI_STIG_CMD_SET(QSPI, cmd);
        __QSPI_STIG_EXECUTE(QSPI);
        while(__QSPI_STIG_ON_GOING(QSPI));
    }
    else {
        if(type == QSPI_STIG_CMD_WRITE) {
            for (volatile int32_t i=0; i<len; i++) {
                *tmp_u8++ = *buffer++;
            }

            __QSPI_STIG_DATA_L_SET(QSPI, tmp_u32[0]);
            __QSPI_STIG_DATA_H_SET(QSPI, tmp_u32[1]);
            
            __QSPI_STIG_CMD_SET(QSPI, cmd);
            __QSPI_STIG_WRITE_BYTES_SET(QSPI, len);
            __QSPI_STIG_EXECUTE(QSPI);
            while(__QSPI_STIG_ON_GOING(QSPI));
        }
        else {
            __QSPI_STIG_CMD_SET(QSPI, cmd);
            __QSPI_STIG_READ_BYTES_SET(QSPI, len);
            __QSPI_STIG_EXECUTE(QSPI);
            while(__QSPI_STIG_ON_GOING(QSPI));
            
            if(type == QSPI_STIG_CMD_READ) {
                tmp_u32[0] = __QSPI_STIG_DATA_L_GET(QSPI);
                tmp_u32[1] = __QSPI_STIG_DATA_H_GET(QSPI);
                for (volatile int32_t i=0; i<len; i++) {
                    *buffer++ = *tmp_u8++;
                }
            }
            else {
                //TBD, BANK READ
            }
        }
    }

    return 0;
}

