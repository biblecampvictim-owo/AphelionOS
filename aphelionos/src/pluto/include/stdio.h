#pragma once
#include <stdint.h>

extern unsigned char g_vga_color;

void clrscr();
void putc(char c);
void puts(const char* str);
void printf(const char* fmt, ...);
void print_buffer(const char* msg, const void* buffer, uint32_t count);
void set_vga_color(unsigned char color);