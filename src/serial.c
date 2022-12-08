#include "serial.h"
#include "strings.h"

extern void outb(uint16_t port_num, uint8_t value);
extern uint8_t inb(uint16_t port_num);

int init_serial(uint16_t port) {
	outb(port + 1, 0x00);
	outb(port + 3, 0x80);
	outb(port + 0, 0x03);
	outb(port + 1, 0x00);
	outb(port + 3, 0x03);
	outb(port + 2, 0xC7);
	outb(port + 4, 0x0B);
	outb(port + 4, 0x1E);
	outb(port + 0, 0xAE);
	
	if (inb(port + 0) != 0xAE)
		return 1;
	
	outb(port+4, 0x0F);
	outb(0x3f8+1, 0x00);
	return 0;
}

int serial_received(uint16_t port) {
	return inb(port + 5) & 1;
}

int is_transmit_empty(uint16_t port) {
	return inb(port + 5) & 0x20;
}
void write_serial(uint16_t port, char c) {
	while(is_transmit_empty(port) == 0);
	outb(port, c);
}

uint8_t read_serial(uint16_t port) {
	while (serial_received(port) == 0);
	return inb(port);
}

uint8_t read_string_serial(uint16_t port, char *res, size_t n) {
	size_t pos = 0;
	while (pos < n) {
		char ch = (char) read_serial(port);
		print_num_serial(port, ch);
		if (ch == '\n')
			break;
		res[pos++] = ch;
	}
	res[pos] = '\0';
}

void print_serial_n(uint16_t port, const char *s, size_t len) {
	for (size_t i = 0; i < len; i++)
		write_serial(port, s[i]);
}

void print_serial(uint16_t port, const char *s) {
	print_serial_n(port, s, strlen(s));
}

void print_num_serial(uint16_t port, int x) {
	char buf[32];
	itoa(buf, x);
	print_serial(port, buf);
}


