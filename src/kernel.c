#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "disk.h"
#include "serial.h"
#include "strings.h"
#include "ustar.h"
#include "vga.h"
#include "descriptor_tables.h"

#define SERIAL_PORT 0x3f8
#define prints(s) print_serial(SERIAL_PORT, s)


void kernel_main() {

	int res = init_serial(SERIAL_PORT);
	prints("Hello123\n");
	init_descriptor_tables();
	
	vga_init_terminal();
	if (res == 1) {
		vga_terminal_writestring("Failed to init serial\n");
	} else {
		vga_terminal_writestring("Serial initiated\n");
	}
	
	prints("Hello2");
	inode nodes[10];
	char buf[100];
	int count = list_files(nodes);
	for (int i = 0; i < count; i++) {
		prints(nodes[i].filename);
		prints("\n");
		prints("Content:\n");
		int rres = read_file(&nodes[i], buf);
		if (!rres) {
			prints(buf);
		}
		prints("\n");
	}
	
	vga_terminal_writestring("Hello, low-level world!\n");
	
}
