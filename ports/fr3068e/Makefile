# BUILD_VERBOSE = 1

PROJECT_NAME := fr3068e_micropython

# Include the core environment definitions; this will set $(TOP).
include ../../py/mkenv.mk

# Include py core make definitions.
include $(TOP)/py/py.mk
include $(TOP)/extmod/extmod.mk

# Set CFLAGS and libraries.
CFLAGS += -I. -I$(BUILD) -I$(TOP)
LIBS += -lm

CROSS_COMPILE ?= arm-none-eabi-
OBJDUMP ?= $(CROSS_COMPILE)objdump

FR_BOARDDIR = ./fr3068e
FR_COMPONTENTS = $(FR_BOARDDIR)/components

# Define the required source files.
SRC_S = \
	$(FR_COMPONTENTS)/drivers/device/fr30xx/gcc/startup_fr30xx.S

SRC_C = \
	main.c \
	mphalport.c \
	help.c \
	$(FR_BOARDDIR)/freqchip_main.c \
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
	shared/readline/readline.c \
	shared/runtime/gchelper_generic.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \

# components/modules/platform/src/gcc/exception_handlers.c \

# Define source files containung qstrs.
SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c

# MicroPython feature configurations
MICROPY_ROM_TEXT_COMPRESSION ?= 1

# include header files
INC += -I. \
	-I$(FR_COMPONTENTS)/drivers/cmsis \
	-I$(FR_COMPONTENTS)/drivers/device \
	-I$(FR_COMPONTENTS)/drivers/device/fr30xx \
	-I$(FR_COMPONTENTS)/drivers/peripheral/Inc \
	-I$(FR_COMPONTENTS)/modules/common/include \
	-I$(FR_COMPONTENTS)/modules/crc \
	-I$(TOP) \
	-I$(BUILD) \

CFLAGS_CORTEX_M33 += -mthumb -mcpu=cortex-m33 -mfloat-abi=hard -fsigned-char -fmessage-length=0
CFLAGS_CORTEX_M33 += -ffunction-sections -fdata-sections
CFLAGS = -O3 -g3 $(INC) $(CFLAGS_CORTEX_M33) $(COPT)
CFLAGS += -std=gnu11

# Debugging/Optimization
ifeq ($(DEBUG), 1)
CFLAGS += -g
COPT = -O0
else
COPT += -Os -DNDEBUG
endif

LDFLAGS = -O3 $(CFLAGS_CORTEX_M33)
LDFLAGS += -Tfreqchip3068e.ld
LDFLAGS += -g3 -Xlinker --gc-sections 
LDFLAGS += --specs=nosys.specs --specs=nano.specs -u _printf_float
LDFLAGS += -L.

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))
OBJ += $(addprefix $(BUILD)/, $(SRC_S:.S=.o))

Target_OBJS : $(OBJ)
$(BUILD)/%.o : %.c
	$(info Bulid: compiling $^)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC) -c -o  $@ $<

$(BUILD)/%.o : %.S
	$(info Bulid: compiling $^)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC) -c -o  $@ $<

$(BUILD)/%.o : %.s
	$(info Bulid: compiling $^)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC) -c -o  $@ $<


# Define the top-level target, the main firmware.
# all: $(BUILD)/$(PROJECT_NAME).elf
all: $(BUILD)/$(PROJECT_NAME).bin

# Define how to build the firmware.
$(BUILD)/$(PROJECT_NAME).elf: $(OBJ)
	$(Q)$(CC) $(LDFLAGS) -Wl,-Map,"$(PROJECT_NAME).map" -o $(BUILD)/$(PROJECT_NAME).elf $^ $(LIBS)
	$(NO_ECHO)$(OBJCOPY) -O binary -S $(BUILD)/$(PROJECT_NAME).elf $(PROJECT_NAME).bin
	$(NO_ECHO)$(OBJCOPY) -O ihex   -S $(BUILD)/$(PROJECT_NAME).elf $(PROJECT_NAME).hex
	$(NO_ECHO)$(OBJDUMP) -D $(BUILD)/$(PROJECT_NAME).elf > $(PROJECT_NAME).dis


$(BUILD)/$(PROJECT_NAME).bin: $(BUILD)/$(PROJECT_NAME).elf
	$(Q)$(OBJCOPY) -O binary $^ $(BUILD)/$(PROJECT_NAME).bin
	
# $(Q)$(OBJDUMP) -D $(BUILD)/$(PROJECT_NAME).elf > $(PROJECT_NAME).dis

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
