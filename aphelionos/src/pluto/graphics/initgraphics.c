#include <stdint.h>
#include "initgraphics.h"
//Made on Nov 2, ~8:00 PM

extern void outb(uint16_t port, uint8_t val);
extern uint8_t inb(uint16_t port);

void set_palette_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
    outb(0x3C8, index);
    outb(0x3C9, r);
    outb(0x3C9, g);
    outb(0x3C9, b);
}

void g_init(void){
    set_13hvga_mode();
    clear_g(0);
    //black
    set_palette_color(-1, 63, 63, 63);
    //white
    //set_palette_color(0, 63, 63, 63);
}

static void write_regs(const uint8_t *regs) {
    uint16_t index_port;
    uint16_t data_port;

    outb(0x3C2, *regs++);

    index_port = 0x3C4;
    data_port = 0x3C5;
    for (uint8_t i = 0; i < 5; i++) {
        outb(index_port, i);
        outb(data_port, *regs++);
    }

    index_port = 0x3D4;
    data_port = 0x3D5;
    outb(index_port, 0x11); outb(data_port, regs[0x11] & 0x7F);
    for (uint8_t i = 0; i < 25; i++) {
        outb(index_port, i);
        outb(data_port, *regs++);
    }

    index_port = 0x3CE;
    data_port = 0x3CF;
    for (uint8_t i = 0; i < 9; i++) {
        outb(index_port, i);
        outb(data_port, *regs++);
    }

    index_port = 0x3C0;
    for (uint8_t i = 0; i < 21; i++) {
        inb(0x3DA);
        outb(index_port, i);
        outb(index_port, *regs++);
    }
    inb(0x3DA);
    outb(0x3C0, 0x20);
}
static const uint8_t g_mode13h_regs[] = {
    0x63,
    0x03, 0x01, 0x0F, 0x00, 0x0E,
    0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
    0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
    0xFF,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
    0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x41, 0x00, 0x0F, 0x00, 0x00
};
//graphical clear
void clear_g(uint8_t color) {
    volatile uint8_t *video_mem = (volatile uint8_t *)0xA0000;
    for (int i = 0; i < 320 * 200; i++) {
        video_mem[i] = color;
    }
}

void set_13hvga_mode(void) {
    write_regs(g_mode13h_regs);
}

void draw_pixels(int x, int y, uint8_t color) {
    volatile uint8_t *video_mem = (volatile uint8_t *)0xA0000;
    if (x >= 0 && x < 320 && y >= 0 && y < 200) {
        video_mem[(y * 320) + x] = color;
    }
}
