#include "string.h"


void memset(char *mem, char val, int size)
{
	for (int i = 0; i < size; i++)
	{
		mem[i] = val;
	}
}

void memcpy(char *dst, const char *src, int size)
{
	for (int i = 0; i < size; i++)
	{
		dst[i] = src[i];
	}
}

int strlen(const char *str)
{
	int size = 0;
	while (str[size])
	{
		size++;
	}
	return size;
}

void strset(char *str, char val)
{
	memset(str, val, strlen(str)+1);
}

void strcpy(char *dst, const char *src)
{
	memcpy(dst, src, strlen(src)+1);
}

int strcmppre(const char *s, const char *t, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (s[i] == 0 && t[i] == 0)
		{
			return 1;
		}
		if (s[i] != t[i])
		{
			return 0;
		}
	}
	return 1;
}

int strcmp(const char *s, const char *t)
{
	int sSize = strlen(s), tSize = strlen(t);
	if (sSize != tSize)
	{
		return 0;
	}
	return strcmppre(s, t, sSize);
}




