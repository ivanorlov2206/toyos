#include "serial.h"
#include "isr.h"

void isr_handler(void) {
	print_serial(0x3f8, "Yess!\n");
}
