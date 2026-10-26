#include "string.h"
#include "stdio.h"

const char* strchr(const char* str, char chr)
{
    if (str == NULL)
        return NULL;

    while (*str)
    {
        if (*str == chr)
            return str;

        ++str;
    }

    return NULL;
}

char* strcpy(char* dst, const char* src)
{
    char* origDst = dst;

    if (dst == NULL)
        return NULL;

    if (src == NULL)
    {
        *dst = '\0';
        return dst;
    }
    
    while (*src)
    {
        *dst = *src;
        ++src;
        ++dst;
    }

    *dst = '\0';
    return origDst;
}

unsigned strlen(const char* str)
{
    unsigned len = 0;
    while (*str)
    {   
        ++len;
        ++str;
    }

    return len;
}

void far* memcpy_far(void far* dst, const void far* src, uint16_t num)
{
    uint8_t far* d = (uint8_t far*)dst;
    const uint8_t far* s = (const uint8_t far*)src;

    while (num--)
        *d++ = *s++;

    return dst;
}