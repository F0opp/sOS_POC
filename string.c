#include "string.h"


void memset(byte *mem, byte val, int size)
{
	for (int i = 0; i < size; i++)
	{
		mem[i] = val;
	}
}

void memcpy(byte *dst, const byte *src, int size)
{
	for (int i = 0; i < size; i++)
	{
		dst[i] = src[i];
	}
}

int strlen(const byte *str)
{
	int size = 0;
	while (str[size])
	{
		size++;
	}
	return size;
}

void strset(byte *str, byte val)
{
	memset(str, val, strlen(str)+1);
}

void strcpy(byte *dst, const byte *src)
{
	memcpy(dst, src, strlen(src)+1);
}

bool strcmppre(const byte *s, const byte *t, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (s[i] == 0 && t[i] == 0)
		{
			return true;
		}
		if (s[i] != t[i])
		{
			return false;
		}
	}
	return true;
}

bool strcmp(const byte *s, const byte *t)
{
	int sSize = strlen(s), tSize = strlen(t);
	if (sSize != tSize)
	{
		return false;
	}
	return strcmppre(s, t, sSize);
}




