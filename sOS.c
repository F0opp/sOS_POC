#include "basicIO.h"


void sOS(void)
{
	asm volatile ("outb %0, %1" : : "a"((byte) 0x0A), "Nd" ((unsigned short) 0x3D4));
	asm volatile ("outb %0, %1" : : "a"((byte) 0x20), "Nd"((unsigned short) 0x3D5));
	

	byte str[STR_MAX_LEN];
	while (true)
	{
		printChr('>');
		read(str);

		if (strcmp(str, "clear"))
		{
			clear();
		}
		else if (strcmppre(str, "echo ",  strlen("echo ")))
		{
			printStr(str + strlen("echo "));
		}
		else if (strcmppre(str, "yes ", strlen("yes ")) || strcmp(str, "yes"))
		{
			byte *prnt = 0;
			if (strcmp(str, "yes"))
			{
				prnt = "y";
			}
			else
			{
				prnt = str + strlen("yes ");
			}

			while (true)
			{
				printStr(prnt);
			}
		}
		else
		{
			printStr("no such command");
		}
	}
}
