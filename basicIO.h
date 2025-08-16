#include "string.h"

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
#define LSHIFT_CODE 0x2a
#define RSHIFT_CODE 0x36
#define RELEASE_CODE 0x80

void setCords(int r, int c, byte val, byte atr);
void setCell(byte val, byte atr);
void deleteChr();
void newLine();
void printChr(byte chr);
void printStr(const byte *text);
void printNum(int num);
void clear();


void read(byte *str);
