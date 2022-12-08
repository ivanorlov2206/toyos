#include "strings.h"
#include "serial.h"

size_t strlen(const char *s) {
	int res = 0;
	while(s[res])
		res++;
	return res;
}

size_t get_int_len(int x) {
	size_t res = 0;
	while (x > 0) {
		x /= 10;
		res++;
	}
	return res;
}

void itoa(char buf[], int x) {
	uint8_t sign = 0;
	if (x < 0) {
		sign = 1;
		x = -x;
	} else if (x == 0) {
		buf[0] = '0';
		buf[1] = 0;
		return;
	}
	size_t nlen = get_int_len(x);
	size_t i = nlen + sign;
	while (i > sign) {
		buf[--i] = '0' + (x % 10);
		x /= 10;
	}
	if (sign)
		buf[0] = '-';
	buf[nlen+sign] = '\0';
}
