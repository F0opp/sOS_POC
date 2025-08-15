#define BYTE_ROW_LEN 160
#define ROW_LEN 80
#define NUM_ROWS 25
#define STR_MAX_LEN ROW_LEN
#define BYTE_CELL_LEN 2


void setCords(int r, int c, unsigned char val, unsigned char atr);
void setCell(unsigned char val, unsigned char atr);
void deleteChr();
void newLine();
void printChr(unsigned char chr);
void printStr(const unsigned char *text);

