
#include "ustar.h"
#include "strings.h"
#include "memory.h"
#include "disk.h"
#include "serial.h"

#define iterate_files(header_var, block_iterator) \
{ \
	uint16_t buffer[256]; \
	size_t block_iterator = 0; \
	for (int block_iterator = 0; block_iterator < (1 << 29); block_iterator++) { \
		int rres = read(buffer, block_iterator, 1); \
		if (rres) { \
			break; \
		} \
		if (check_is_tar_header((unsigned char *) buffer)) { \
			struct tar_header *header_var = (struct tar_header *) buffer;

#define end_file_iteration } \
} \
}



void dec2oct(uint8_t size, char buffer[], uint32_t x) {
	int8_t pos = size - 2;
	buffer[size - 1] = '\0';
	while (x > 0 && pos >= 0) {
		buffer[pos--] = '0' + (x % 8);
		x /= 8;
	}
	for (int8_t i = pos; i >= 0; i--) {
		buffer[i] = '0';
	}
}

uint32_t oct2dec(char buffer[], size_t len) {
	uint32_t res = 0;
	for (size_t i = 0; i < len; i++) {
		res += (uint32_t)(buffer[i] - '0') * (1 << ((len - i - 1) * 3));
	}
	return res;
}

int8_t check_is_tar_header(unsigned char *buffer) {
	if (!memcmp(buffer+257, (unsigned char *)"ustar", 5))
		return 1;
	return 0;
}

uint32_t get_file_size(struct tar_header *head) {
	return oct2dec(head->size, sizeof(head->size) - 1);
}

uint32_t get_file_block_count(uint32_t size_in_bytes) {
	return (size_in_bytes + BLOCK_SIZE - 1) / BLOCK_SIZE;
}

inode header_to_inode(struct tar_header *header, size_t block) {
	inode node;
	memcpy((unsigned char *)header->name, (unsigned char *)node.filename, 100);
	node.lba_block = block;
	node.type = FILE;
	node.filesize = get_file_size(header);
	return node;
}

int find_file_by_name(inode *node, char *name) {
	iterate_files(header, it)
		if (!memcmp((unsigned char *)header->name, (unsigned char *)name, strlen(name))) {
			*node = header_to_inode(header, it);
			return 0;
		}
	end_file_iteration
	return -1;
}

int read_file(inode *node, char *buf) {
	uint32_t count = get_file_block_count(node->filesize);
	uint16_t fbuffer[256];
	for (size_t i = 0; i < count; i++) {
		int rres = read(fbuffer, node->lba_block + i + 1, 1);
		if (rres)
			return -1;
		memcpy((unsigned char *)fbuffer, (unsigned char *)buf + 512 * i, 512);
	}
	return 0;
}


int list_files(inode nodes[]) {
	int pos = 0;
	iterate_files(header, it)
		nodes[pos] = header_to_inode(header, it);
		pos++;
	end_file_iteration
	return pos;
}
