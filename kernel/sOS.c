int nxtChr= 0;
volatile unsigned char *screen = (volatile unsigned char *) 0xB8000;


void printChr(unsigned char text)
{
    screen[nxtChr] = text;
    screen[nxtChr+1] = 0x0F;
    nxtChr += 2;
}

void printStr(const unsigned char *str)
{
	for (int i = 0; str[i]; i++) 
	{
		printChr(str[i]);
	}
}


void sOS(void)
{
    printStr("hello, world");
    printChr('!');

	while (1)
	{
		int x = 7896;
	}
}
