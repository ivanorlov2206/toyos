typedef enum {
	FILE = 100,
	DIRECTORY = 200
} filetype;

typedef struct {
	char filename[100];
	uint32_t lba_block;
	uint32_t filesize;
	filetype type;
} inode;
