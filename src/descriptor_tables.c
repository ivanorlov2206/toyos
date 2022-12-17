#include "descriptor_tables.h"
#include "serial.h"
#include "memory.h"

#define ISR_COUNT 10
#define GDT_ENTRIES_COUNT 5

#define SET_INT(num) idt_set_gate(num, (uint32_t) isr ## num, 0x08, 0x8E)

extern void gdt_flush(uint32_t gdt_addr);
static void init_gdt();
static void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access);

extern void idt_flush(uint32_t idt_addr);
static void init_idt();
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

idt_entry_t idt_entries[ISR_COUNT];
idt_descriptor idt_ptr;


segment_descriptor_t gdt_entries[GDT_ENTRIES_COUNT];
gdt_descriptor gdt_ptr;
#define SERIAL_PORT 0x3f8

void init_descriptor_tables() {
	init_gdt();
	init_idt();
}

static void init_gdt() {
	gdt_ptr.offset = (uint32_t) &gdt_entries;
	gdt_ptr.size = (sizeof(segment_descriptor_t) * GDT_ENTRIES_COUNT) - 1;
	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0xCF, 0x9A);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0xCF, 0x92);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xCF, 0xFA);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xCF, 0xF2);
	
	gdt_flush((uint32_t)&gdt_ptr);
}

static void init_idt() {
	idt_ptr.base = (uint32_t) &idt_entries;
	idt_ptr.limit = (sizeof(idt_entry_t) * ISR_COUNT) - 1;
	
	memset(&idt_entries, 0, sizeof(idt_entry_t) * ISR_COUNT);
	
	SET_INT(0);
	SET_INT(1);
	SET_INT(2);
	SET_INT(3);
	SET_INT(4);
	SET_INT(5);
	SET_INT(6);
	SET_INT(7);
	SET_INT(8);
	SET_INT(9);
	
	idt_flush(&idt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
	idt_entries[num].base_low = base & 0xFFFF;
	idt_entries[num].base_high = (base >> 16) & 0xFFFF;
	
	idt_entries[num].flags = flags;
	idt_entries[num].reserved = 0;
	idt_entries[num].sel = sel;
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
