#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "disk.h"
#include "serial.h"

#define IO_BASE 0x1F0
#define BSY 0x80
#define DRQ 0x08
#define DF 0x20
#define ERR 1

extern void outb(uint16_t port_num, uint8_t value);
extern uint8_t inb(uint16_t port_num);
extern void out16(uint16_t port_num, uint16_t value);
extern uint16_t in16(uint16_t port_num);

void poll() {
	while(1) {
		uint8_t read_res = inb(IO_BASE + 7);
		if ((!(read_res & BSY) && (read_res & DRQ)) || (read_res & DF) || (read_res & ERR)) {
			return;
		}
		
	}
}

void setup_ata(uint32_t LBA, uint8_t sector_count) {
	outb(IO_BASE + 6, 0xE0 | ((LBA >> 24) & 0x0F));
	outb(IO_BASE + 1, 0x00);
	outb(IO_BASE + 2, sector_count);
	outb(IO_BASE + 3, (uint8_t) LBA);
	outb(IO_BASE + 4, (uint8_t) (LBA >> 8));
	outb(IO_BASE + 5, (uint8_t) (LBA >> 16));
}

void wait() {
	for (uint32_t i = 0; i < 100000; i++);
}

uint8_t read(uint16_t buffer[], uint32_t LBA, uint8_t sector_count) {
	setup_ata(LBA, sector_count);
	outb(IO_BASE + 7, 0x20);
	uint8_t red_count = 0;
	while (red_count < (sector_count == 0 ? 256 : sector_count)) {
		poll();
		for (int i = 0; i < 256; i++) {
			uint16_t value = in16(IO_BASE);
			buffer[i + 256 * red_count] = value;
		}
		if (inb(IO_BASE + 1)) {
			return 1;
		}
		red_count++;
	}
	wait();
	return 0;
}
void flush() {
	outb(IO_BASE + 7, 0xE7);
}



uint8_t write(uint16_t buffer[], uint32_t LBA, uint8_t sector_count) {
	setup_ata(LBA, sector_count);
	outb(IO_BASE + 7, 0x30);
	uint8_t wrote_count = 0;
	while (wrote_count < (sector_count == 0 ? 256 : sector_count)) {
		poll();
		for (int i = 0; i < 256; i++) {
			uint16_t value = buffer[i + 256 * wrote_count];
			out16(IO_BASE, value);
		}
		if (inb(IO_BASE + 1)) {
			return 1;
		}
		wrote_count++;
		flush();
	}
	wait();
	return 0;
}
