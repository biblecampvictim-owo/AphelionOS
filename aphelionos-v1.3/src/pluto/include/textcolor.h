#ifndef TEXT_COLOR_H
#define TEXT_COLOR_H

static void red_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x04 << 8) | c;
    }
}

static void green_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x02 << 8) | c;
    }
}

static void blue_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x01 << 8) | c;
    }
}

static void cyan_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x03 << 8) | c;
    }
}

static void pink_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x05 << 8) | c;
    }
}

static void orange_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x06 << 8) | c;
    }
}
static void darkwhite_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x08 << 8) | c;
    }
}
static void brightred_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x0C << 8) | c;
    }
}
static void white_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x0F << 8) | c;
    }
}
static void purple_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x09 << 8) | c;
    }
}
//red orange yellow green cyan blue purple
static void yellow_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x0E << 8) | c;
    }
}


static void grey_text(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x08 << 8) | c;
    }
}

#endif