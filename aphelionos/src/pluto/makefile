ASM=nasm
CC=gcc
CXX=g++
LD=ld

HEADERS = $(wildcard *.h) \
          $(wildcard *.hpp) \
          $(wildcard include/*.h) \
          $(wildcard include/*.hpp) \
          $(wildcard include/*/*.h) \
          $(wildcard include/*/*.hpp) \
          $(wildcard */*.h) \
          $(wildcard */*.hpp) \
          $(wildcard */*/*.h) \
          $(wildcard */*/*.hpp) \
          $(wildcard */*/*/*.h) \
          $(wildcard */*/*/*.hpp)
            
BUILD_DIR ?= ../../build

CFLAGS=-m32 -ffreestanding -fno-pie -nostdlib -c -I. -Iinclude
CXXFLAGS=-m32 -ffreestanding -fno-pie -fno-exceptions -fno-rtti -nostdlib -c -I. -Iinclude
ASMFLAGS=-f elf32

C_SOURCES = $(wildcard *.c) \
            $(wildcard */*.c) \
            $(wildcard */*/*.c) \
            $(wildcard */*/*/*.c)

C_OBJS = $(patsubst %.c, $(BUILD_DIR)/pluto/%.o, $(C_SOURCES))

CPP_SOURCES = $(wildcard *.cpp) \
              $(wildcard */*.cpp) \
              $(wildcard */*/*.cpp) \
              $(wildcard */*/*/*.cpp)

CPP_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/pluto/%.o, $(CPP_SOURCES))

ASM_SOURCES = $(wildcard *.asm) \
              $(wildcard */*.asm) \
              $(wildcard */*/*.asm) \
              $(wildcard */*/*/*.asm)

ENTRY_OBJ = $(BUILD_DIR)/pluto/entry.o
OTHER_ASM_OBJS = $(filter-out $(ENTRY_OBJ), $(patsubst %.asm, $(BUILD_DIR)/pluto/%.o, $(ASM_SOURCES)))
OBJS = $(ENTRY_OBJ) $(OTHER_ASM_OBJS) $(C_OBJS) $(CPP_OBJS)

all: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/pluto/%.o: %.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/pluto/%.o: %.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/pluto/%.o: %.cpp $(HEADERS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/kernel.bin: $(OBJS)
	$(LD) -m elf_i386 --oformat binary -Ttext 0x30000 -e _start $(OBJS) -o $@

clean:
	rm -rf $(BUILD_DIR)/pluto/ $(BUILD_DIR)/kernel.bin