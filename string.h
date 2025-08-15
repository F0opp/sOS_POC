#include "types.h"

void memset(byte *mem, byte val, int size);
void memcpy(byte *dst, const byte *src, int size);
int strlen(const byte *str);
void strset(byte *str, byte val);
void strcpy(byte *dst, const byte *src);
int strcmppre(const byte *s, const byte *t, int size);
int strcmp(const byte *s, const byte *t);
