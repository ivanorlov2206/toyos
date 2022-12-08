enum VGA_COLOR {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

uint8_t vga_entry_color(enum VGA_COLOR fg, enum VGA_COLOR bg);
void vga_init_terminal();
void vga_terminal_setcolor(uint8_t color);
void vga_terminal_write(const char *s, size_t size);
void vga_terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void vga_terminal_putchar(char c);
void vga_terminal_writestring(const char *s);
