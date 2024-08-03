
dir2:=$(shell pwd)/$(lastword $(MAKEFILE_LIST))
name:=$(lastword $(MAKEFILE_LIST))
dir=$(shell dirname $(dir2))

FR_COMPONTENTS = $(dir)/components

# Define the required source files.
SRC_C += \
	$(FR_COMPONTENTS)/drivers/device/fr30xx/system_fr30xx.c \
	$(FR_COMPONTENTS)/drivers/device/fr30xx/trim_fr30xx.c \
	$(FR_COMPONTENTS)/drivers/device/fr30xx/gcc/syscalls.c \
	$(FR_COMPONTENTS)/drivers/device/fr30xx/gcc/sysmem.c \
	$(FR_COMPONTENTS)/drivers/peripheral/Src/driver_flash.c \
	$(FR_COMPONTENTS)/drivers/peripheral/Src/driver_efuse.c \
	$(FR_COMPONTENTS)/drivers/peripheral/Src/driver_frspim.c \
	$(FR_COMPONTENTS)/drivers/peripheral/Src/driver_gpio.c \
	$(FR_COMPONTENTS)/drivers/peripheral/Src/driver_pmu.c \
	$(FR_COMPONTENTS)/drivers/peripheral/Src/driver_pmu_iwdt.c \
	$(FR_COMPONTENTS)/drivers/peripheral/Src/driver_qspi.c \
	$(FR_COMPONTENTS)/drivers/peripheral/Src/driver_uart.c \
	$(FR_COMPONTENTS)/modules/common/src/co_util.c \
	$(FR_COMPONTENTS)/modules/crc/crc32.c \

SRC_S += \
	$(FR_COMPONTENTS)/drivers/device/fr30xx/gcc/startup_fr30xx.S

# include header files
INC += -I. \
	-I$(FR_COMPONTENTS)/drivers/cmsis \
	-I$(FR_COMPONTENTS)/drivers/device \
	-I$(FR_COMPONTENTS)/drivers/device/fr30xx \
	-I$(FR_COMPONTENTS)/drivers/peripheral/Inc \
	-I$(FR_COMPONTENTS)/modules/common/include \
	-I$(FR_COMPONTENTS)/modules/crc \

CFLAGS_CORTEX_M33 += -mthumb -mcpu=cortex-m33 -mfloat-abi=hard -fsigned-char -fmessage-length=0
CFLAGS_CORTEX_M33 += -ffunction-sections -fdata-sections
CFLAGS = -O3 -g3 $(INC) $(CFLAGS_CORTEX_M33) $(COPT)
CFLAGS += -std=gnu11

LDFLAGS = -O3 $(CFLAGS_CORTEX_M33)
LDFLAGS += -T$(dir)/freqchip3068e.ld
LDFLAGS += -g3 -Xlinker --gc-sections 
LDFLAGS += --specs=nosys.specs --specs=nano.specs -u _printf_float
LDFLAGS += -L.

