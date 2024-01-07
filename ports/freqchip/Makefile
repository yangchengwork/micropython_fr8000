# BUILD_VERBOSE = 1

# Include the core environment definitions; this will set $(TOP).
include ../../py/mkenv.mk

# Include py core make definitions.
include $(TOP)/py/py.mk
include $(TOP)/extmod/extmod.mk

# Set CFLAGS and libraries.
CFLAGS += -I. -I$(BUILD) -I$(TOP)
LIBS += -lm

CROSS_COMPILE ?= arm-none-eabi-

# Define the required source files.
SRC_C = \
	main.c \
	mphalport.c \
    help.c \
    fr8000/proj_main.c \
    components/modules/platform/src/gcc/boot_vectors.c \
    components/modules/platform/src/gcc/exception_handlers.c \
    components/driver/driver_system.c \
	shared/readline/readline.c \
	shared/runtime/gchelper_generic.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \

# Define source files containung qstrs.
SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c

# MicroPython feature configurations
MICROPY_ROM_TEXT_COMPRESSION ?= 1

# include header files
INC += -I. \
	-Icomponents/modules/platform/include \
	-Icomponents/modules/platform/include/cmsis \
	-Icomponents/modules/common/include \
	-Icomponents/driver/include \
	-Icomponents/driver/drv_common \
	-Ifr8000 \
	-I$(TOP) \
	-I$(BUILD) \

CFLAGS_CORTEX_M3 = -mthumb -mcpu=cortex-m3 -fsigned-char -fmessage-length=0
CFLAGS = -Os -g $(INC) $(CFLAGS_CORTEX_M3) $(COPT)
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -std=gnu11

# Debugging/Optimization
ifeq ($(DEBUG), 1)
CFLAGS += -g
COPT = -O0
else
COPT += -Os -DNDEBUG
endif

LDFLAGS_CORTEX_M3 = -mthumb -mcpu=cortex-m3
LDFLAGS = -Os -g $(LDFLAGS_CORTEX_M3)
LDFLAGS += -Tfreqchip8000.ld
LDFLAGS += components/modules/platform/src/gcc/syscall_gcc.txt
LDFLAGS += -Wl,--gc-sections
# LDFLAGS += --specs=nosys.specs
LDFLAGS += -L.

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

# Define the top-level target, the main firmware.
# all: $(BUILD)/firmware.elf
all: $(BUILD)/firmware.bin

# Define how to build the firmware.
$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	$(Q)$(SIZE) $@

$(BUILD)/firmware.out: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ -Wl,-Map=$(BUILD)/firmware.map $(LIBS)
	$(Q)$(SIZE) $@

$(BUILD)/firmware.bin: $(BUILD)/firmware.out
	$(Q)$(OBJCOPY) -O binary $^ $(BUILD)/firmware.bin

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
