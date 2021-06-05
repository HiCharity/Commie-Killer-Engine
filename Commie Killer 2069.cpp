#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_PGEX_RAYCASTWORLD
#include "olcPGEX_RayCastWorld.h"

#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <cwchar>
#include "sfx.h"
#include "game.h"
using namespace std;



int main()
{
	RayCastWorldDemo_SIMPLE demo;
	int menu;
	HideCursor();
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 18;                   // Width of each character in the font
	cfi.dwFontSize.Y = 18;                  // Height
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xa);

	cout << "COMMIE KILLER 2069\n"
		<< "*********************\n"
		<< "<1> Play\n"
		<< "<2> Credits\n"
		<< "<ANY OTHER KEY> Exit\n\n";
		cin >> menu;

	switch (menu) {
	case 1:
		if (demo.Construct(X_PIXELS, Y_PIXELS, 4, 4, true))
			demo.Start();
		break;
	case 2: cout << "\n\nCreated by: Blake Pierce \n\n";
		cout << "Press <F> to play.   "; 
		cin >> menu;
		if (demo.Construct(X_PIXELS, Y_PIXELS, 4, 4, true))
			demo.Start();
		break;
	default: break;
	}
	cout << "\n\nYOU DIED\n\nRESTART GAME TO PLAY GAME\n\n";
	cin >> menu;
	_CrtDumpMemoryLeaks();
	return 0;
}
