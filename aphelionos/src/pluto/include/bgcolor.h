#ifndef BGCOLOR_H 
#define BGCOLOR_H
//i changed restore_normal_background to set_black_background to make it match the others
//red
/*This code randomly became very buggy after i upgraded the kernel to 64 bits,
I still dont know why. I feel like I should have the knowdledge to figure out why after such a pain,
but i dont. This deserves a respectful fuck*/
//Update: This is fixed now, But i think this comment deserves to still be in the code
#include <stdint.h>

//its Nov 23, 2:06 2026 as i am writing this and i just realised "static" void does not do what i think it does.
//I have no idea how this now actually works the way i want it to work.
//But hey, after all they say the number one programming rule is: If it works do not touch it
//oh and also it just explodes when i remove "static"


extern unsigned char g_vga_color;

static void outb(unsigned short port, unsigned char val);
static unsigned char inb(unsigned short port);

static void vga_disable_blink(void) {
    (void)inb(0x3DA);
    outb(0x3C0, 0x10 | 0x20);
    uint8_t mode = inb(0x3C1);
    mode &= (uint8_t)~0x08;

    (void)inb(0x3DA);
    outb(0x3C0, 0x10 | 0x20);
    outb(0x3C0, mode);
}


static void apply_vga_attr(unsigned char attr) {
    g_vga_color = attr;
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = ((unsigned short)attr << 8) | c;
    }
}

static void set_red_background(void) {
    apply_vga_attr(0x4F);
}
//blue
static void set_blue_background(void) {
    apply_vga_attr(0x1F);
}
//DOMAIN EXPANSION, HOLLOW P- okay fine ill shut up (god i dont even watch that)
static void set_purple_background(void) {
    apply_vga_attr(0x5F);
}
//special one for help.c
static void set_purple_background_helpc(void) {
    apply_vga_attr(0x5E);
}
static void set_cyan_background(void) {
    apply_vga_attr(0x3F);
}
static void set_grey_background(void) {
    apply_vga_attr(0x8F);
}
//purely for testing
static void set_test_background(void) {
    apply_vga_attr(0x7F);
}
//black with white
static void set_black_background(void) {
    apply_vga_attr(0x0F);
}
//white with blue text
static void set_white_blue_background(void) {
    vga_disable_blink();
    apply_vga_attr(0xF1);
}
static void set_black_green_background(void) {
    vga_disable_blink();
    apply_vga_attr(0x02);
}
static void set_black_red_background(void) {
    vga_disable_blink();
    apply_vga_attr(0x04);
}
#endif