#define BYTE_ROW_LEN 160
#define ROW_LEN 80
#define NUM_ROWS 25
#define STR_MAX_LEN ROW_LEN
#define BYTE_CELL_LEN 2

#define ENTER_CODE 0x1c
#define BACKSPACE_CODE 0x0e
#define CAPSLOCK_CODE 0x3a
#define SPECIAL_CODE 0xe0
#define SLASH_CODE 0x35


void setCords(int r, int c, unsigned char val, unsigned char atr);
void setCell(unsigned char val, unsigned char atr);
void deleteChr();
void newLine();
void printChr(unsigned char chr);
void printStr(const unsigned char *text);
void clear();


void read(unsigned char *str);
