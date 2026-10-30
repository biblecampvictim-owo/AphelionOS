#ifndef RED_ERROR_H
#define RED_ERROR_H

static inline void red_error(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
        
    for (int i = 0; i < 80 * 25 - 5; i++) {
        if ((vga_buffer[i] & 0xFF) == 'E' &&
            (vga_buffer[i+1] & 0xFF) == 'R' &&
            (vga_buffer[i+2] & 0xFF) == 'R' &&
            (vga_buffer[i+3] & 0xFF) == 'O' &&
            (vga_buffer[i+4] & 0xFF) == 'R') {
            
            for (int j = 0; j < 5; j++) {
                unsigned char c = vga_buffer[i+j] & 0xFF;
                vga_buffer[i+j] = (0x0C << 8) | c;
            }
            
        }
    }
}

#endif 