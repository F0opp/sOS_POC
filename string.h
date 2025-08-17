#include "types.h"

#define STR_MAX_LEN 80*25


void memset(byte *mem, byte val, int size);
void memcpy(byte *dst, const byte *src, int size);
int strlen(const byte *str);
void strset(byte *str, byte val);
void strcpy(byte *dst, const byte *src);
bool strcmppre(const byte *s, const byte *t, int size);
bool strcmp(const byte *s, const byte *t);
