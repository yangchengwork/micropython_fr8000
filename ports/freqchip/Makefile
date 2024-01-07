BUILD_VERBOSE = 1

# Include the core environment definitions; this will set $(TOP).
include ../../py/mkenv.mk

CROSS = 1

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# Include py core make definitions.
include $(TOP)/py/py.mk

# Set CFLAGS and libraries.
CFLAGS = -I. -I$(BUILD) -I$(TOP)
LIBS = -lm

ifeq ($(CROSS), 1)
CROSS_COMPILE ?= arm-none-eabi-
endif

PROJECT_NAME     := firmware
TARGETS          := firmware
OUTPUT_DIRECTORY := build


# Define the required source files.
SRC_FILES = \
    main.c \
    mphalport.c \
    help.c \
    fr8000/proj_main.c \
    components/modules/platform/src/gcc/boot_vectors.c \
    components/modules/platform/src/gcc/exception_handlers.c \
    components/driver/driver_system.c \
    $(BUILD)/_frozen_mpy.c \
    $(TOP)/shared/readline/readline.c \
    $(TOP)/shared/runtime/gchelper_generic.c \
    $(TOP)/shared/runtime/pyexec.c \
    $(TOP)/shared/runtime/stdout_helpers.c \

ifeq ($(CROSS), 1)
SRC_FILES += shared/libc/string0.c
endif

SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c


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
# CFLAGS_CORTEX_M3 = -mthumb -mtune=cortex-m3 -mcpu=cortex-m3 -msoft-float -fsingle-precision-constant -Wdouble-promotion -Wfloat-conversion
CFLAGS = -Os -g $(INC) $(CFLAGS_CORTEX_M3) $(COPT)
# keep every function in a separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections
# CFLAGS += -fmessage-length=0 -fsigned-char
CFLAGS += -std=gnu11
# CFLAGS += -MP
# CFLAGS += -msoft-float

LDFLAGS_CORTEX_M3 = -mthumb -mcpu=cortex-m3
LDFLAGS = -Os -g $(LDFLAGS_CORTEX_M3)
LDFLAGS += -Tfreqchip8000.ld
LDFLAGS += components/modules/platform/src/gcc/syscall_gcc.txt
LDFLAGS += -Wl,--gc-sections
# LDFLAGS += --specs=nosys.specs
LDFLAGS += -L.

CSUPEROPT = -Os # save some code space

# Tune for Debugging or Optimization
ifeq ($(DEBUG), 1)
CFLAGS += -O0 -ggdb
else
CFLAGS += -Os -DNDEBUG
CFLAGS += -fdata-sections -ffunction-sections
endif

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_FILES:.c=.o))

ifeq ($(CROSS), 1)
all: $(BUILD)/firmware.bin
else
all: $(BUILD)/firmware.elf
endif

$(BUILD)/_frozen_mpy.c: $(TOP)/tests/frozen/frozentest.mpy $(BUILD)/genhdr/qstrdefs.generated.h
	$(ECHO) "MISC freezing bytecode"
	$(Q)$(TOP)/tools/mpy-tool.py -f -q $(BUILD)/genhdr/qstrdefs.preprocessed.h -mlongint-impl=none $< > $@

$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(ECHO) $(Q)$(CC) $(LDFLAGS) -o $@ $^ -Wl,-Map=$(BUILD)/firmware.map $(LIBS)
	$(Q)$(SIZE) $@

$(BUILD)/firmware.out: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(CC) $(LDFLAGS) -o $@ $^ -Wl,-Map=$(BUILD)/firmware.map $(LIBS)
	$(Q)$(SIZE) $@

$(BUILD)/firmware.bin: $(BUILD)/firmware.out
	$(Q)$(OBJCOPY) -O binary $^ $(BUILD)/firmware.bin

$(BUILD)/firmware.dfu: $(BUILD)/firmware.bin
	$(ECHO) "Create $@"
	$(Q)$(PYTHON) $(DFU) -b 0x08000000:$(BUILD)/firmware.bin $@

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
