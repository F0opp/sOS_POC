#include "basicIO.h"
#include "string.h"

volatile unsigned char *screen = (volatile unsigned char *) 0xB8000;
int row = 0, col = 0;


int getIndex(int r, int c)
{
	return r*BYTE_ROW_LEN + BYTE_CELL_LEN*c;
}


void setCords(int r, int c, unsigned char val, unsigned char atr)
{
	int ind = getIndex(r, c);
	screen[ind] = val;
	screen[ind+1] = atr;
}

void setCell(unsigned char val, unsigned char atr)
{
	setCords(row, col, val, atr);
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

	if (row == NUM_ROWS)
	{
		for (int r = 0; r < NUM_ROWS-1; r++)
		{
			memcpy(screen + getIndex(r, 0), screen + getIndex(r+1, 0), BYTE_ROW_LEN);
		}
		memset(screen + getIndex(NUM_ROWS-1, 0), 0, BYTE_ROW_LEN);
		row--;
	}
}


void printChr(unsigned char chr)
{
	if (chr == '\n')
	{
		newLine();
		return ;
	}
	
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
	newLine();
}


void clear()
{
	for (int r = 0; r < NUM_ROWS; r++)
	{
		for (int c = 0; c < ROW_LEN; c++)
		{
			setCords(r, c, 0, 0);
		}
	}

	row = col = 0;
}





unsigned char scancodes[0x80] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'};
unsigned char capslockScancodes[0x80] = {0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'};


inline unsigned char getByteFromPort(unsigned short port)
{
	unsigned char byte;
	asm volatile ("inb %1, %0" : "=a"(byte) : "Nd"(port));
	return byte;
}

unsigned char readByte()
{
	int status = 0;

	do
	{
		status = getByteFromPort(0x64);
	}
	while ((status & 1) == 0);

	return getByteFromPort(0x60);
}


void addToBuff(unsigned char *str, int *top, unsigned char val)
{
	if (top == STR_MAX_LEN-1)
	{
		return ;
	}

	printChr(val);
	str[*top] = val;
	(*top)++;
}



int capslock = 0;
void read(unsigned char *str)
{
	int top = 0;
	unsigned char inp = 0;


	while (inp != ENTER_CODE)
	{
		inp = readByte();

		if (inp == SPECIAL_CODE)
		{
			inp = readByte();
			if (inp == SLASH_CODE)
			{
				addToBuff(str, &top, '/');
			}
			

			continue;
		}


		if (inp == BACKSPACE_CODE)
		{
			deleteChr();
			if (top != 0)
			{
				top--;
			}
		}

		if (inp == CAPSLOCK_CODE)
		{
			capslock = !capslock;
		}

		if (scancodes[inp] != 0)
		{
			if (capslock)
			{
				addToBuff(str, &top, capslockScancodes[inp]);
			}
			else
			{
				addToBuff(str, &top, scancodes[inp]);
			}
		}
	}


	newLine();
	for (int i = top; i < STR_MAX_LEN; i++)
	{
		str[i] = 0;
	}
}
























