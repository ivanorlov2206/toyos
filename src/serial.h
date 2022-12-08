#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void print_serial(uint16_t port, const char *s);
int init_serial(uint16_t port);
void print_num_serial(uint16_t port, int x);
void print_serial_n(uint16_t port, const char *s, size_t len);
uint8_t read_string_serial(uint16_t port, char *res, size_t n);
