#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


typedef struct gdt_descriptor {
	uint16_t size;
	uint32_t offset;
} __attribute((packed)) gdt_descriptor;

typedef struct segment_descriptor_t{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t limit_and_flags;
	uint8_t base_high;
} __attribute((packed)) segment_descriptor_t;


typedef struct idt_descriptor {
	uint16_t limit;
	uint32_t base;
} __attribute((packed)) idt_descriptor;

typedef struct idt_entry {
	uint16_t base_low;
	uint16_t sel;
	uint8_t reserved;
	uint8_t flags;
	uint16_t base_high;
} __attribute((packed)) idt_entry_t;


void init_descriptor_tables();


extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
