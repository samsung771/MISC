#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include "ConGame.h"

#define m_nScreenWidth 100
#define m_nScreenHeight 100
#define fontw 2
#define fonth 2


int main()
{	
	SMALL_RECT window = { 0,0,1,1 };
	SetConsoleWindowInfo(hConsole, TRUE, &window);
	COORD coord = { (short)m_nScreenWidth, (short)m_nScreenHeight };
	SetConsoleScreenBufferSize(hConsole, coord);
	SetConsoleActiveScreenBuffer(hConsole);

	CONSOLE_FONT_INFOEX cfi{};
	GetCurrentConsoleFontEx(hConsole, TRUE, cfi);
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	setTitle("Testing");
	while (true) {
	}
	Sleep(10);
}

