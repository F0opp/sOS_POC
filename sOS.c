#include "basicIO.h"


void sOS(void)
{
	byte str[STR_MAX_LEN];
	for (int i = 0; i < 5; i++)
	{
		read(str);
	}
	clear();
	while (1)
	{
		read(str);
	}
}
