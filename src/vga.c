#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "strings.h"

uint8_t vga_entry_color(enum VGA_COLOR fg, enum VGA_COLOR bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char ch, uint8_t color) {
	return (uint16_t) ch | (uint16_t) color << 8;
}



size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

void vga_init_terminal() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xC03FF000;
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			*(terminal_buffer+y*VGA_WIDTH+x) = vga_entry(' ', terminal_color);
		}
	}
}




void vga_terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void vga_terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	*(terminal_buffer + index) = vga_entry(c, color);
}


void vga_terminal_putchar(char c) {
	vga_terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}




void vga_terminal_write(const char *s, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (s[i] == '\n') {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		} else {
			vga_terminal_putchar(s[i]);
		}
	}
}

void vga_terminal_writestring(const char *s) {
	vga_terminal_write(s, strlen(s));
}
