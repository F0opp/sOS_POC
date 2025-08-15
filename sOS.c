#include "basicIO.h"


int cmp(unsigned char *s, const unsigned char *t)
{
	int i = 0;
	for (i = 0; t[i]; i++)
	{
		if (s[i] != t[i])
		{
			return 0;
		}
	}
	return s[i] == 0;
}


void sOS(void)
{
	unsigned char str[STR_MAX_LEN];
	while (1)
	{
		read(str);
		if (cmp(str, "clear"))
		{
			clear();
		}
	}
}
