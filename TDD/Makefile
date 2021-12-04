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

# program source files (not including external libraries)
SRC = /Users/luca/Documents/GitHub/Embedded-Software/TDD/src/AllTests.c \
			/Users/luca/Documents/GitHub/Embedded-Software/TDD/src/SprintfTest.c \
			/Users/luca/Documents/GitHub/Embedded-Software/TDD/src/SprintfTestRunner.c

#################################################################################################
# \/ stuff nobody needs to worry about until such time that worrying about it is appropriate \/ #
#################################################################################################
# executables
CC      = gcc

# generate list of objects
CFILES    = $(filter %.c, $(SRC))
EXTC     := $(foreach dir, $(EXT), $(wildcard $(dir)/*.c))
CPPFILES  = $(filter %.cpp, $(SRC))
EXTCPP   := $(foreach dir, $(EXT), $(wildcard $(dir)/*.cpp))
OBJ       = $(CFILES:.c=.o) $(EXTC:.c=.o) $(CPPFILES:.cpp=.o) $(EXTCPP:.cpp=.o)


# compile all files
all: $(PRJ).exe
	./$(PRJ).exe

$(PRJ).exe: $(OBJ)
	gcc $(CFILES) ./Unity/src/unity.c ./Unity/extras/fixture/src/unity_fixture.c ./Unity/extras/memory/src/unity_memory.c -I ./Unity/src/ -I ./Unity/extras/fixture/src/ -I ./Unity/extras/memory/src/ -o $(PRJ).exe

# objects from c files
.c.o:
	$(CC) $(CFLAGS) $< -o $@

# objects from c++ files
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

# remove compiled files
clean:
	rm -f *.o *.elf *.hex
	$(foreach dir, $(EXT), rm -f $(dir)/*.o;)
