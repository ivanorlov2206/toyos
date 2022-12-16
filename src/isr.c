#include "serial.h"
#include "isr.h"

void isr_handler(uint32_t int_no, uint32_t err_no) {
	print_num_serial(0x3f8, int_no);
	print_serial(0x3f8, "Yess!\n");
}
