#include "basicIO.h"

volatile byte *screen = (volatile byte *) 0xB8000;
int row = 0, col = 0;


int getIndex(int r, int c)
{
	return r*BYTE_ROW_LEN + BYTE_CELL_LEN*c;
}


void setCords(int r, int c, byte val, byte atr)
{
	int ind = getIndex(r, c);
	screen[ind] = val;
	screen[ind+1] = atr;
}

void setCell(byte val, byte atr)
{
	setCords(row, col, val, atr);
}


void deleteChr()
{
	if (col == 0)
	{
		row--;
		col = ROW_LEN;
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


void printChr(byte chr)
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


void printStr(const byte *text)
{
	for (int i = 0; text[i]; i++)
	{
		printChr(text[i]);
	}
	newLine();
}


void printNum(int num)
{
	if (num == 0)
	{
		printChr('0');
		newLine();
		return ;
	}
	byte str[STR_MAX_LEN];
	memset(str, 0, STR_MAX_LEN);
	int sz = 0, cpy = num;

	while (cpy)
	{
		sz++;
		cpy /= 10;
	}
	while (num)
	{
		sz--;
		str[sz] = num%10 + '0';
		num /= 10;
	}

	
	printStr(str);
}


void clear()
{
	memset(screen, 0, NUM_ROWS*BYTE_ROW_LEN);
	row = col = 0;
}





byte scancodes[0x80] = {0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'};
byte capslockScancodes[0x80] = {0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0, 0, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 0, 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'};


inline byte getByteFromPort(unsigned short port)
{
	byte byte;
	asm volatile ("inb %1, %0" : "=a"(byte) : "Nd"(port));
	return byte;
}

byte readByte()
{
	int status = 0;

	do
	{
		status = getByteFromPort(0x64);
	}
	while ((status & 1) == 0);

	return getByteFromPort(0x60);
}


void addToBuff(byte *str, int *top, byte val)
{
	printChr(val);
	str[*top] = val;
	(*top)++;
}



bool capslock = false;
void read(byte *str)
{
	int top = 0;
	byte inp = 0;


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
			if (top != 0)
			{
				top--;
				deleteChr();
			}
		}

		if (inp == CAPSLOCK_CODE || inp == LSHIFT_CODE || inp == RSHIFT_CODE || inp == LSHIFT_CODE + RELEASE_CODE || inp == RSHIFT_CODE + RELEASE_CODE)
		{
			capslock = !capslock;
		}

		if (inp >= RELEASE_CODE)
		{
			continue;
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
	str[top] = 0;
	memset(str + top, 0, STR_MAX_LEN - strlen(str));
}
























