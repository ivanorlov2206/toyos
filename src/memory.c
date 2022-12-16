#include "memory.h"

int8_t memcmp(unsigned char *s1, unsigned char *s2, size_t count) {
	for (size_t i = 0; i < count; i++) {
		if (*(s1 + i) < *(s2 + i))
			return -1;
		else if (*(s1 + i) > *(s2 + i))
			return 1;
	} 
	return 0;
}

void memcpy(unsigned char *src, unsigned char *dst, size_t count) {
	for (size_t i = 0; i < count; i++) {
		dst[i] = src[i];
	}
}

void memset(unsigned char *src, unsigned char value, size_t count) {
	for (size_t i = 0; i < count; i++)
		*(src + i) = value;
}
