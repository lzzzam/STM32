# simple AVR Makefile
#
# written by michael cousins (http://github.com/mcous)
# released to the public domain

# Makefile
#
# targets:
#   all:    compiles the source code
#   test:   tests the isp connection to the mcu
#   flash:  writes compiled hex file to the mcu's flash memory
#   fuse:   writes the fuse bytes to the MCU
#   disasm: disassembles the code for debugging
#   clean:  removes all .hex, .elf, and .o files in the source code and library directories

# parameters (change this stuff accordingly)
# project name
PRJ = Boot
# avr mcu
MCU = atmega328p
# mcu clock frequency
CLK = 8000000
# avr programmer (and port if necessary)
# e.g. PRG = usbtiny -or- PRG = arduino -P /dev/tty.usbmodem411
PRG = stk500v1
# fuse values for avr: low, high, and extended
# these values are from an Arduino Uno (ATMega328P)
# see http://www.engbedded.com/fusecalc/ for other MCUs and options
LOCK = 0x3F
LFU  = 0xE2
HFU  = 0xD0
EFU  = 0xFD
# program source files (not including external libraries)
SRC = $(PRJ).cpp
# where to look for external libraries (consisting of .c/.cpp files and .h files)
# e.g. EXT = ../../EyeToSee ../../YouSART
EXT = /Users/luca/Documents/GitHub/Embedded-Software/AVR/Bootloader/lib


ICSP_PORT = /dev/cu.usbmodem14221
USART_PORT = /dev/cu.SLAB_USBtoUART
BOOT_FILE = /Users/luca/Documents/GitHub/Embedded-Software/AVR/Bootloader/Boot.hex
APP_FILE = /Users/luca/Documents/GitHub/Embedded-Software/AVR/Bootloader/test/App.hex
CONF = /Users/luca/Library/Arduino15/packages/MiniCore/hardware/avr/2.0.7/avrdude.conf

BAUD_RATE= 38400
F_CPU = 8000000
#################################################################################################
# \/ stuff nobody needs to worry about until such time that worrying about it is appropriate \/ #
#################################################################################################

# include path
INCLUDE := $(foreach dir, $(EXT), -I$(dir))
# c flags
CFLAGS    = -Wall -Os -mmcu=$(MCU) $(INCLUDE)
# any aditional flags for c++
CPPFLAGS =

# executables
AVRDUDE = avrdude -c$(PRG) -p$(MCU)
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE    = avr-size --format=avr --mcu=$(MCU)
CC      = avr-gcc

# generate list of objects
CFILES    = $(filter %.c, $(SRC))
EXTC     := $(foreach dir, $(EXT), $(wildcard $(dir)/*.c))
CPPFILES  = $(filter %.cpp, $(SRC))
EXTCPP   := $(foreach dir, $(EXT), $(wildcard $(dir)/*.cpp))
OBJ       = $(CFILES:.c=.o) $(EXTC:.c=.o) $(CPPFILES:.cpp=.o) $(EXTCPP:.cpp=.o)

# user targets
# compile all files
all: $(PRJ).hex

# test programmer connectivity
test:
	$(AVRDUDE) -v

console:
	screen /dev/cu.SLAB_USBtoUART $(BAUD_RATE)

# flash program to mcu
flash: all
	$(AVRDUDE)  -C$(CONF) -P/dev/cu.SLAB_USBtoUART -b$(BAUD_RATE) -U flash:w:$(PRJ).hex:i

# write fuses to mcu
fuse:
	avrdude -C$(CONF) -v -p$(MCU) -c$(PRG) -P$(ICSP_PORT) -b$(BAUD_RATE) -e -Ulock:w:$(LOCK):m -Uefuse:w:$(EFU):m -Uhfuse:w:$(HFU):m -Ulfuse:w:$(LFU):m

burn: Boot.hex
	$(AVRDUDE) -P$(ICSP_PORT) -b19200 -Uf:w:$(BOOT_FILE):i -Ulock:w:0x0F:m

burnApp: ./test/App.hex
	python ./Programmer.py $(APP_FILE) $(USART_PORT) $(BAUD_RATE)
#$(AVRDUDE) -P$(ICSP_PORT) -b19200 -Uhfuse:w:0xD1:m

# generate disassembly files for debugging
disasm: $(PRJ).elf
	$(OBJDUMP) -d $(PRJ).elf

# remove compiled files
clean:
	rm -f *.o
	$(foreach dir, $(EXT), rm -f $(dir)/*.o;)

# other targets
# objects from c files
.c.o:
	$(CC) $(CFLAGS) -DF_CPU=$(F_CPU) -DBAUD_RATE=$(BAUD_RATE) -c $< -o $@

# objects from c++ files
.cpp.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# elf file
$(PRJ).elf: $(OBJ)
	$(CC) $(CFLAGS) -Wl,--section-start=.text=0x7000 -o $(PRJ).elf $(OBJ)

# hex file
$(PRJ).hex: $(PRJ).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(PRJ).elf $(PRJ).hex
	$(SIZE) $(PRJ).elf
