#pragma once

#include "utils.h"
#include "memory.h"

#define VGA_VIDEO_BUFFER_ADDRESS 0xA0000
#define VGA_VIDEO_BUFFER_WIDTH 320
#define VGA_VIDEO_BUFFER_HEIGHT 200

#define VGA_TEXT_BUFFER_ADDRESS 0xB8000
#define VGA_TEXT_BUFFER_HEIGHT 25
#define VGA_TEXT_BUFFER_WIDTH 80

#define PALETTE_MASK 0x3C6
#define PALETTE_READ 0x3C7
#define PALETTE_WRITE 0x3C8
#define PALETTE_DATA 0x3C9

byte* VGA_VIDEO_BUFFER = (char*)VGA_VIDEO_BUFFER_ADDRESS;
byte VGA_PALETTE[256];

byte* back_buffer;

uint16_t text_columns = 0;
short* VGA_TEXT_BUFFER = (short*)VGA_TEXT_BUFFER_ADDRESS;

byte* testArray;

struct rgb_color {

    byte red;
    byte green;
    byte blue; 
};

void init_graphics() {

    //back_buffer = malloc(320*200);
    //testArray = malloc(100);
    for (uint32_t i = 0; i < 256; i++) VGA_PALETTE[i] = i;
    
    for (int i = 0; i < 100; i++) {

        back_buffer[i] = 10;
    }
}

void set_palette_register(byte index, struct rgb_color* color) {
    
    port_byte_out(PALETTE_MASK, 0xFF);
    port_byte_out(PALETTE_WRITE, index);

    port_byte_out(PALETTE_DATA, color->red);
    port_byte_out(PALETTE_DATA, color->green);
    port_byte_out(PALETTE_DATA, color->blue);
}

void get_palette_register(byte index, struct rgb_color* color) {

    port_byte_out(PALETTE_MASK, 0xFF);
    port_byte_out(PALETTE_READ, index);

    color->red = port_byte_in(PALETTE_DATA);
    color->green = port_byte_in(PALETTE_DATA);
    color->blue = port_byte_in(PALETTE_DATA);
}

void clear_text_buffer() {

    for (uint32_t i = 0; i < VGA_TEXT_BUFFER_WIDTH * VGA_TEXT_BUFFER_HEIGHT; i++) { 
            VGA_TEXT_BUFFER[i] = 0x0F00;    
    }  
}

void clear_video_buffer(byte color) {

    for (uint32_t i = 0; i < VGA_VIDEO_BUFFER_WIDTH * VGA_VIDEO_BUFFER_HEIGHT; i++) { 
            VGA_VIDEO_BUFFER[i] = color;
    }  
}

void swap_buffers() {

    //byte_mem_cpy(back_buffer, VGA_VIDEO_BUFFER, 320*200);
}

byte* get_video_buffer() { return VGA_VIDEO_BUFFER; }

void draw_rect(int xPos, int yPos, uint32_t w, uint32_t h, byte col) {

    for (uint32_t y = 0; y < h; y++) {

        int yOffs = y + yPos;
        if (yOffs < 0 || yOffs >= VGA_VIDEO_BUFFER_HEIGHT) continue;

        for (uint32_t x = 0; x < w; x++) {

            int xOffs = x + xPos;
            if (xOffs < 0 || xOffs >= VGA_VIDEO_BUFFER_WIDTH) continue;

            VGA_VIDEO_BUFFER[xOffs + yOffs * VGA_VIDEO_BUFFER_WIDTH] = col;
        }
    }
}

void text_print(const char* string) {

    for (uint32_t i = 0; i < strlen(string); i++) {

        VGA_TEXT_BUFFER[i + text_columns * VGA_TEXT_BUFFER_WIDTH] = 0x0F00 | string[i];
    }

    text_columns++;
}
