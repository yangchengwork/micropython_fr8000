# BUILD_VERBOSE = 1

PROJECT_NAME := fr8000_micropython

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

# Define the required source files.
SRC_C = \
	main.c \
	mphalport.c \
	help.c \
	fr8000/proj_main.c \
	components/driver/driver_pmu.c \
	components/driver/driver_uart_ex.c \
	components/driver/driver_dma.c \
	components/driver/driver_gpio.c \
	components/modules/platform/src/gcc/boot_vectors.c \
	components/modules/common/src/co_log.c \
	components/driver/driver_system.c \
	shared/readline/readline.c \
	shared/runtime/gchelper_generic.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \

# components/modules/platform/src/gcc/exception_handlers.c \

# Define source files containung qstrs.
SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c

# Disable text compression in debug builds
MICROPY_ROM_TEXT_COMPRESSION = 0

# include header files
INC += -I. \
	-Icomponents/modules/platform/include \
	-Icomponents/modules/platform/include/cmsis \
	-Icomponents/modules/common/include \
	-Icomponents/modules/os/include \
	-Icomponents/ble/include/gatt \
	-Icomponents/ble/include/gap \
	-Icomponents/ble/include \
	-Icomponents/driver/include \
	-Icomponents/driver/drv_common \
	-Ifr8000 \
	-I$(TOP) \
	-I$(BUILD) \

CFLAGS_CORTEX_M3 = -mthumb -mcpu=cortex-m3 -fsigned-char -fmessage-length=0
CFLAGS = -O3 -g3 $(INC) $(CFLAGS_CORTEX_M3) $(COPT)
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
LDFLAGS = -O3 $(LDFLAGS_CORTEX_M3)
LDFLAGS += -Tfreqchip8000.ld
LDFLAGS += -T components/modules/platform/src/gcc/syscall_gcc.txt
LDFLAGS += -g3 -Xlinker 
LDFLAGS += --gc-sections 
LDFLAGS += --specs=nosys.specs -u _printf_float
LDFLAGS += -L.
LIBS  += components/modules/platform/src/gcc/libfr800x_stack.a

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

Target_OBJS : $(OBJ)

$(BUILD)/%.o : %.c
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
