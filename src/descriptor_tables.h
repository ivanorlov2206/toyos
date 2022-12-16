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




void init_descriptor_tables();
