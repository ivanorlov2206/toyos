#include "descriptor_tables.h"
#include "serial.h"
#include "memory.h"

extern void gdt_flush(uint32_t idt_addr);
static void init_gdt();
static void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access);

segment_descriptor_t gdt_entries[5];
gdt_descriptor gdt_ptr;
#define SERIAL_PORT 0x3f8

void init_descriptor_tables() {
	init_gdt();
}

static void init_gdt() {
	gdt_ptr.offset = (uint32_t) &gdt_entries;
	gdt_ptr.size = (sizeof(segment_descriptor_t) * 5) - 1;
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0xCF, 0x9A);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0xCF, 0x92);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xCF, 0xFA);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xCF, 0xF2);
	
	gdt_flush((uint32_t)&gdt_ptr);
}

static void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access) {
	gdt_entries[num].base_low = base & 0xFFFF;
	gdt_entries[num].base_mid = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
	
	gdt_entries[num].limit_low = limit & 0xFFFF;
	gdt_entries[num].limit_and_flags = (limit >> 16) & 0x0F;
	
	gdt_entries[num].limit_and_flags |= flags & 0xF0;
	gdt_entries[num].access = access;
	
}
