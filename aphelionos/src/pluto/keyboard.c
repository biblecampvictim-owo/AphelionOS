#include <stdint.h>
#include "stdio.h"
#include "keyboard.h"
#include "keyboard_map.h"

extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t data);
extern void idt_set_gate(uint8_t vector, uint32_t base, uint16_t selector, uint8_t flags);
extern void keyboard_isr_stub(void);

static int shift_pressed = 0;
static int caps_lock_state = 0;
//SOMEONE STOP THIS CRIMINAL!!!! THIS IS NOT FORGIVABLE. THAT EVIL INDIVIDUAL. THIS IS JUST UNTHINKABLE.
#define KEYBOARD_BUFFER_SIZE 256
static char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static volatile int head = 0;
static volatile int tail = 0;

static void keyboard_buffer_push(char c) {
    int next = (head + 1) % KEYBOARD_BUFFER_SIZE;
    if (next != tail) { //Buffer not full
        keyboard_buffer[head] = c;
        head = next;
    }
}

char keyboard_getchar(void) {
    while (head == tail) {
        asm volatile("hlt");
    }
    char c = keyboard_buffer[tail];
    tail = (tail + 1) % KEYBOARD_BUFFER_SIZE;
    return c;
}

void pic_remap(void)
{
    uint8_t a1 = inb(0x21);
    uint8_t a2 = inb(0xA1);

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    
    outb(0x21, 0xFD); 
    outb(0xA1, 0xFF);
}

void keyboard_handler_main(void)
{
    uint8_t scancode = inb(0x60);

    if (scancode == 0x2A || scancode == 0x36)
    {
        shift_pressed = 1;
        outb(0x20, 0x20);
        return;
    }
    if (scancode == 0xAA || scancode == 0xB6)
    {
        shift_pressed = 0;
        outb(0x20, 0x20);
        return;
    }
    if (scancode == 0x3A)
    {
        caps_lock_state = !caps_lock_state;
        outb(0x20, 0x20);
        return;
    }
    
    if (scancode & 0x80)
    {
        outb(0x20, 0x20);
        return;
    }

    if (scancode == 0x0E) 
    {
        keyboard_buffer_push('\b');
        outb(0x20, 0x20);
        return;
    }
    //meow
    char c = shift_pressed ? keyboard_map_shifted[scancode] : keyboard_map[scancode];
    if (c != 0)
    {
        int is_letter = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
        if (is_letter)
        {
            if (c >= 'A' && c <= 'Z')
            {
                c += 32;
            }
            if (shift_pressed ^ caps_lock_state)
            {
                c -= 32;
            }
        }
        keyboard_buffer_push(c);
    }

    outb(0x20, 0x20);
}

void keyboard_init(void)
{
    pic_remap();
    idt_set_gate(0x21, (uint32_t)keyboard_isr_stub, 0x08, 0x8E);
}