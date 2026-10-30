ASM=nasm
CC=gcc
CXX=g++
LD=ld
OBJCOPY=objcopy

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

CFLAGS = -m64 -ffreestanding -fno-pie -fno-stack-protector -mno-red-zone -Wall -Wextra -Iinclude -I.
LDFLAGS = -m elf_x86_64 -T linker.ld -nostdlib
ASMFLAGS = -f elf64

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

ENTRY_OBJ = $(BUILD_DIR)/pluto/kentry.o
OTHER_ASM_OBJS = $(filter-out $(ENTRY_OBJ), $(patsubst %.asm, $(BUILD_DIR)/pluto/%.o, $(ASM_SOURCES)))
OBJS = $(ENTRY_OBJ) $(OTHER_ASM_OBJS) $(C_OBJS) $(CPP_OBJS)

all: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/pluto/%.o: %.asm
	mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/pluto/%.o: %.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/pluto/%.o: %.cpp $(HEADERS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -e kernel_entry $(OBJS) -o $(BUILD_DIR)/kernel.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/kernel.elf $@

clean:
	rm -rf $(BUILD_DIR)/pluto/ $(BUILD_DIR)/kernel.bin $(BUILD_DIR)/kernel.elf