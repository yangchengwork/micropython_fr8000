
dir2:=$(shell pwd)/$(lastword $(MAKEFILE_LIST))
name:=$(lastword $(MAKEFILE_LIST))
dir=$(shell dirname $(dir2))

# Define the required source files.
SRC_C += \
	$(dir)/components/driver/driver_pmu.c \
	$(dir)/components/driver/driver_uart_ex.c \
	$(dir)/components/driver/driver_dma.c \
	$(dir)/components/driver/driver_gpio.c \
	$(dir)/components/modules/platform/src/gcc/boot_vectors.c \
	$(dir)/components/modules/common/src/co_log.c \
	$(dir)/components/driver/driver_system.c \

# include header files
INC += -I. \
	-I$(dir)/components/modules/platform/include \
	-I$(dir)/components/modules/platform/include/cmsis \
	-I$(dir)/components/modules/common/include \
	-I$(dir)/components/modules/os/include \
	-I$(dir)/components/ble/include/gatt \
	-I$(dir)/components/ble/include/gap \
	-I$(dir)/components/ble/include \
	-I$(dir)/components/driver/include \
	-I$(dir)/components/driver/drv_common \

CFLAGS_CORTEX_M3 = -mthumb -mcpu=cortex-m3 -fsigned-char -fmessage-length=0
CFLAGS = -O3 -g3 $(INC) $(CFLAGS_CORTEX_M3) $(COPT)
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -std=gnu11

LDFLAGS_CORTEX_M3 = -mthumb -mcpu=cortex-m3
LDFLAGS = -O3 $(LDFLAGS_CORTEX_M3)
LDFLAGS += -T $(dir)/freqchip8000.ld
LDFLAGS += -T $(dir)/components/modules/platform/src/gcc/syscall_gcc.txt
LDFLAGS += -g3 -Xlinker 
LDFLAGS += --gc-sections 
LDFLAGS += --specs=nosys.specs -u _printf_float
LDFLAGS += -L.
LIBS  += $(dir)/components/modules/platform/src/gcc/libfr800x_stack.a

