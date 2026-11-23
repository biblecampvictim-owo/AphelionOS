#ifndef INIT_GRAPHICS_H
#define INIT_GRAPHICS_H

#include <stdint.h>


void g_init(void);
void set_13hvga_mode(void);
void draw_pixels(int x, int y, uint8_t color);
void set_palette_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void clear_g(uint8_t color);

#endif