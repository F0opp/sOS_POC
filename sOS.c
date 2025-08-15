#include "basicIO.h"


void sOS(void)
{
	asm volatile ("outb %0, %1" : : "a"((byte) 0x0A), "Nd" ((unsigned short) 0x3D4));
	asm volatile ("outb %0, %1" : : "a"((byte) 0x20), "Nd"((unsigned short) 0x3D5));


	byte str[STR_MAX_LEN];
	while (true)
	{
		read(str);

		if (strcmp(str, "clear"))
		{
			clear();
		}
		if (strcmppre(str, "echo ",  strlen("echo ")))
		{
			printStr(str + strlen("echo "));
		}
	}
}
