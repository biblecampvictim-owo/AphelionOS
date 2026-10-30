#ifndef IDT_H
#define IDT_H

#include <stdint.h>
//Keep me on fire, Keep me on fire!!!
struct IDTEntry {
    uint16_t offset_low;       
    uint16_t selector;       
    uint8_t  ist;             
    uint8_t  type_attr;       
    uint16_t offset_mid;      
    uint32_t offset_high;     
    uint32_t reserved;        
} __attribute__((packed));

struct IDTPtr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

void idt_set_gate(uint8_t vector, void* base, uint16_t selector, uint8_t flags);
void idt_init(void);

#endif