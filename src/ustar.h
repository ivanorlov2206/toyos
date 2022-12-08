#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "filesystems.h"

#define BLOCK_SIZE 512

struct tar_header {
	char name[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag;
	char linkname[100];
	char magic[6];
	char version[2];
	char uname[32];
	char gname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[167];
};

int8_t check_is_tar_header(unsigned char *buffer);
uint32_t get_file_size(struct tar_header *head);
int find_file_by_name(inode *node, char *name);
int list_files(inode nodes[]);
int read_file(inode *node, char *buf);
