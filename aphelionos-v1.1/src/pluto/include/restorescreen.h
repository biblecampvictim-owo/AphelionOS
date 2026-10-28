#ifndef RESTORESCREEN_H
#define RESTORESCREEN_H 
//define this WITH bgcolor.h in file

static void restore_screen(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x07 << 8) | c;
    }
}
#endif