/*
  ******************************************************************************
  * @file    driver_common.h
  * @author  FreqChip Firmware Team
  * @version V1.0.0
  * @date    2023
  * @brief   driver common header file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 FreqChip.
  * All rights reserved.
  ******************************************************************************
*/
#ifndef __DRIVER_COMMON_H__
#define __DRIVER_COMMON_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/* ================================================================================ */
/* =======================     Use Uart to Debug print     ======================== */
/* ================================================================================ */
#define UART_DEBUG_ENABLE    (1)

#if (UART_DEBUG_ENABLE == 1)
    #define freq_printf    printf                                   
#else
    #define freq_printf(format, ...)    ((void)0)
#endif

#include "driver_aes.h"

#include "driver_cache.h"

#include "driver_cali.h"

#include "driver_can.h"

#include "driver_psd_dac.h"

#include "driver_crc.h"

#include "driver_dma.h"

#include "driver_display.h"

#include "driver_efuse.h"

#include "driver_flash.h"

#include "driver_frspim.h"

#include "driver_gpio.h"

#include "driver_i2s.h"

#include "driver_i2c.h"

#include "driver_ipc.h"

#include "driver_pdm.h"

#include "driver_pmu.h"
#include "driver_pmu_iwdt.h"
#include "driver_pmu_rtc.h"

#include "driver_pwm.h"

#include "driver_spi.h"
#include "driver_qspi.h"

#include "driver_sd.h"
#include "driver_sd_card.h"
#include "driver_sd_mmc.h"

#include "driver_spdif.h"

#include "driver_saradc.h"

#include "driver_tick.h"

#include "driver_timer.h"

#include "driver_trng.h"

#include "driver_uart.h"

#include "driver_yuv2rgb.h"

#include "driver_wdt.h"

#include "usb_core.h"

#ifndef  USB_OTG_USE_HOST
#include "usb_audio.h"
#include "usb_cdc.h"
#include "usb_hid.h"
#include "usb_winusb.h"
#include "usb_mass_storage.h"
#include "usb_wireless.h"
#include "usb_dev.h"
#else
#include "usbh_mass_storage.h"
#include "usb_host.h"
#endif

#endif
