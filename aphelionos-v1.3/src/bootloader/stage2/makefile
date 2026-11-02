BUILD_DIR?=build/
ASM?=nasm
ASMFLAGS?=-f obj
CC16?=/home/lucca/watcom/binl64/owcc
CFLAGS16?=-march=i86 -zp1 -Wc,-d3 -Wc,-s -Wc,-wx -Wc,-ms -Wc,-zl -Wc,-zq -za99
LD16?=/home/lucca/watcom/binl64/wlink

SOURCES_C=$(wildcard *.c)
SOURCES_ASM=$(wildcard *.asm)
OBJECTS_C=$(patsubst %.c, $(BUILD_DIR)/stage2/c/%.obj, $(SOURCES_C))
OBJECTS_ASM=$(patsubst %.asm, $(BUILD_DIR)/stage2/asm/%.obj, $(SOURCES_ASM))

.PHONY: all stage2 clean always

all: stage2

stage2: $(BUILD_DIR)/stage2.bin

$(BUILD_DIR)/stage2.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	$(LD16) NAME $(BUILD_DIR)/stage2.bin FILE \{ $(OBJECTS_ASM) $(OBJECTS_C) \} OPTION MAP=$(BUILD_DIR)/stage2.map @linker.lnk

$(BUILD_DIR)/stage2/c/%.obj: %.c always
	$(CC16) -c $(CFLAGS16) -fo=$@ $<

$(BUILD_DIR)/stage2/asm/%.obj: %.asm always
	$(ASM) $(ASMFLAGS) -o $@ $<
always:
	mkdir -p $(BUILD_DIR)/stage2/c
	mkdir -p $(BUILD_DIR)/stage2/asm

clean:
	rm -f $(BUILD_DIR)/stage2.bin