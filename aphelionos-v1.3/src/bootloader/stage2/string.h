#pragma once
#include "stdint.h"

const char* strchr(const char* str, char chr);
char* strcpy(char* dst, const char* src);
unsigned strlen(const char* str);

void far* memcpy_far(void far* dst, const void far* src, uint16_t num);