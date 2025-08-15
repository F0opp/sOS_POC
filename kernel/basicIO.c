#include "basicIO.h"

volatile unsigned char *screen = (volatile unsigned char *) 0xB8000;
int row = 0, col = 0;




void setCell(unsigned char val, unsigned char atr)
{
	screen[row*BYTE_ROW_LEN + BYTE_CELL_LEN*col] = val;
	screen[row*BYTE_ROW_LEN + BYTE_CELL_LEN*col + 1] = atr;
}


void deleteChr()
{
	if (col == 0)
	{
		return ;
	}

	col--;
	setCell(0, 0);
}

void newLine()
{
	row++;
	col = 0;
}


void printChr(unsigned char chr)
{
	setCell(chr, 0x07);
	col++;

	if (col == ROW_LEN)
	{
		newLine();
	}
}


void printStr(const unsigned char *text)
{
	for (int i = 0; text[i]; i++)
	{
		printChr(text[i]);
	}
}
