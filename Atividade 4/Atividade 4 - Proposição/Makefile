TARGET = led

BUILD_DIR = ./build
BASE_DIR  = ./

.SECONDEXPANSION:
.PRECIOUS: $(BUILD_DIR)/ $(BUILD_DIR)%/

# Define the linker script location and chip architecture.
#LD_SCRIPT = stm32.ld
LD_SCRIPT = $(BASE_DIR)/system/stm32f103xb.ld
MCU_SPEC  = cortex-m3

# Toolchain definitions (ARM bare metal defaults)
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump
OS = arm-none-eabi-size

# Assembly directives.
ASFLAGS += -c
#ASFLAGS += -O0
ASFLAGS += -mcpu=$(MCU_SPEC)
ASFLAGS += -mthumb
ASFLAGS += -Wall
# (Set error messages to appear on a single line.)
ASFLAGS += -fmessage-length=0

# C compilation directives
REQ_CFLAGS += -mcpu=$(MCU_SPEC)
REQ_CFLAGS += -mthumb
REQ_CFLAGS += -Wall
#CFLAGS += -g
CFLAGS += -O3
REQ_CFLAGS += --specs=nosys.specs
# (Set error messages to appear on a single line.)
REQ_CFLAGS += -fmessage-length=0
# (Set system to ignore semihosted junk)
REQ_CFLAGS += --specs=nano.specs
REQ_CFLAGS += -DUART_USE_DMA=1 -DADC_USE_DMA=1

# Linker directives.
REQ_LFLAGS += -nostdlib
#LFLAGS += -lgcc
REQ_LFLAGS += -nostartfiles
LFLAGS += --cref -Map $(BUILD_DIR)/$(TARGET).map
REQ_LFLAGS += -T./$(LD_SCRIPT)
REQ_LFLAGS += -L /usr/lib/gcc/arm-none-eabi/7.3.1/thumb/v7-m

STARTUP_SRC	= startup_stm32f103xb.s
C_SRC    	= 
APP_SRC    	= $(TARGET).c

include $(BASE_DIR)/system/system.mk

OBJS = $(BUILD_DIR)/$(STARTUP_SRC:.s=.o)
OBJS += $(addprefix $(BUILD_DIR)/, $(notdir $(C_SRC:.c=.o)))
OBJS += $(BUILD_DIR)/$(APP_SRC:.c=.o)

.PHONY: all, list, elf
all: flash

elf: $(BUILD_DIR)/$(TARGET).hex

list: $(C_SRC) $(APP_SRC) $(STARTUP_SRC)
	$(CC) -g -Wa,-adhln $(INCLUDE_DIRS) $(REQ_CFLAGS) $$(CFLAGS) $$^ > $(BUILD_DIR)/$(TARGET).lst

$(BUILD_DIR)/%.o: $(BASE_DIR)/system/%.s | $$(@D)/
	$(CC) -x assembler-with-cpp $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c | $$(@D)/
	$(CC) -c $(INCLUDE_DIRS) $(REQ_CFLAGS) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(LD) $^ $(REQ_LFLAGS) $(LFLAGS) -o $@

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OC) -S -O ihex $< $@
	$(OS) $<

$(BUILD_DIR)/:
	mkdir -p $@

$(BUILD_DIR)%/:
	mkdir -p $@

.PHONY: flash, flash2
flash: $(BUILD_DIR)/$(TARGET).hex
	stm32flash -w $< /dev/ttyUSB0

flash2: $(BUILD_DIR)/$(TARGET).hex
	st-flash --format ihex write $<

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
