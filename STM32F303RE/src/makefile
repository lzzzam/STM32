ROOT   = ../..
CC_DIR = $(ROOT)/toolchain/gcc-arm-none-eabi-10-2020-q4-major
#CC     = $(CC_DIR)/bin/arm-none-eabi-gcc
CC = arm-none-eabi-gcc

CFLAGS += -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 \
		  -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants 
		 
CFLAGS += -Wstrict-prototypes -Wuninitialized -Wall -Wextra -Wmissing-declarations \
		  -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wmissing-prototypes  \
		  -Wbad-function-cast

#CFLAGS += -Wunused -Werror -Wpadded -Wconversion 

CFLAGS += $(foreach file,$(INC),-I"$(file)")

INC = \
./driver/inc

SRC += \
driver/src/ADC.c \
driver/src/GPIO.c \
driver/src/I2C.c \
driver/src/I2S.c \
driver/src/RCC.c \
driver/src/SPI.c

TARGET = test/GPIO_01_Read_UserButton.c

BUILD_DIR	= ../out
OUT_DIRS  	= $(foreach file, $(SRC),$(BUILD_DIR)/$(dir $(file)))
OBJS 		= $(foreach file, $(SRC),$(BUILD_DIR)/$(file:%.c=%.o))


all: $(BUILD_DIR) $(OBJS) $(TARGET)

# Each subdirectory must supply rules for building sources it contributes
$(BUILD_DIR)/%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	$(CC) $(CFLAGS) -c "$<" -o "$@" 
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD_DIR):
	@echo 'Creating build directory'
	@mkdir -p $(BUILD_DIR)
	@echo '$(BUILD_DIR) created'
	@echo 'Creating sub-directories'
	@mkdir -p $(OUT_DIRS)
	@echo '$(OUT_DIRS) created'
	@echo ' '

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: foo
foo:
	@echo $(OBJS)

	