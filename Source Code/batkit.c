/*
	Batkit: The 19 in 1 tool for batch scripts.

	Copyright (c) 2021 shoaib hassan, anic17.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>

*/
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
//Global variables
int xpos = 0;
int ypos = 0;
int argc_next = 1;
int argvindex = 2;
//Function
void setcursor(int, DWORD);
void window(int hide);
void mousevent(int usage);
void gotoxy(short x, short y);
void gotoxy(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setcursor(int visible, DWORD size)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
void window(int hide)
{
	if (hide >= 0 && hide <= 12)
	{
		ShowWindow(GetConsoleWindow(), hide);
	}
}
void getitle()
{
	char title[1024];
	GetConsoleTitle(title, 1023);
	char *fnd = strstr(title, " - ");
	if (fnd)
		*fnd = 0;
	printf("%s\n", title);
}
void mousevent(int usage)
{
	HANDLE hConsoleInput;
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	if (hConsoleInput == INVALID_HANDLE_VALUE)
	{
		exit(0);
	}
	DWORD mode;
	LPDWORD lpMode = &mode;
	if (GetConsoleMode(hConsoleInput, lpMode) == 0)
	{
		exit(0);
	}
	if (SetConsoleMode(hConsoleInput, ENABLE_MOUSE_INPUT) == 0)
	{
		exit(0);
	}
	INPUT_RECORD buf;
	PINPUT_RECORD lpBuffer = &buf;
	DWORD nLength = 1;
	DWORD nNumberOfEventsRead;
	int x, y, button;
	while (1)
	{
		if (ReadConsoleInput(hConsoleInput, lpBuffer, nLength, &nNumberOfEventsRead) == 0)
		{
			exit(0);
		}
		if (buf.EventType == MOUSE_EVENT)
		{
			if (usage == 1)
			{
				x = buf.Event.MouseEvent.dwMousePosition.X;
				y = buf.Event.MouseEvent.dwMousePosition.Y;
				button = buf.Event.MouseEvent.dwButtonState;
				printf("%d:%d:%d\n", x, y, button);
				break;
			}
			if (buf.Event.MouseEvent.dwButtonState)
			{
				x = buf.Event.MouseEvent.dwMousePosition.X;
				y = buf.Event.MouseEvent.dwMousePosition.Y;
				button = buf.Event.MouseEvent.dwButtonState;
				printf("%d:%d:%d\n", x, y, button);
				break;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	while (argc_next < argc)
	{
		// Main function: If the string is empty (NULL), return 1 and quit the program
		if (argv[1] == NULL)
		{
			return EXIT_FAILURE;
		}

		/*
		/H argument: HideCursor
		Hide or unhide the cursor
		*/
		if (stricmp(argv[argc_next], "/h") == 0)
		{
			setcursor(atoi(argv[argc_next + 1]), 20);
			argc_next++;
		}
		/*
		/t argument: get title
		prints the title on screen
		*/
		if (stricmp(argv[argc_next], "/t") == 0)
		{
			getitle();
		}
		/*
		/cs argument: cursor size
		change cursor size friom 1 to 100
		*/
		if (stricmp(argv[argc_next], "/cs") == 0)
		{
			setcursor(1, atoi(argv[argc_next + 1]));
			argc_next++;
		}
		/*
		/p argument: set window
		hide or show or minimize or maximize window
		*/
		if (stricmp(argv[argc_next], "/p") == 0)
		{
			window(atoi(argv[argc_next + 1]));
			argc_next++;
		}
		/* 
			/K argument: Key
			Use function getch() in "conio.h"
		*/
		if (stricmp(argv[argc_next], "/k") == 0)
		{

			int key = _getch();
			if (key == 0 || key == 224)
			{
				key = 255 + _getch();
			}
			return (key);
		}

		/*
		W argument: Wait
		Wait specified milliseconds
		*/
		if (stricmp(argv[argc_next], "/w") == 0)
		{
			Sleep(atoi(argv[argc_next + 1]));
			argc_next++;
		}
		HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		/*
			/G argument: Goto
			Go to a specific position at the console buffer
		*/
		if (stricmp(argv[argc_next], "/g") == 0)
		{
			int x_a = atoi(argv[argc_next + 1]);
			int y_a = atoi(argv[argc_next + 2]);
			x_a = x_a + xpos;
			y_a = y_a + ypos;
			gotoxy(x_a, y_a);
			argc_next += 2;
		}
		/*
			/C argument: text
			Changes color of text
		*/
		if (stricmp(argv[argc_next], "/c") == 0)
		{
			int color = (int)strtol(argv[argc_next + 1], NULL, 16);
			SetConsoleTextAttribute(hConsoleHandle, (color / 16) << 4 | color % 16);
			argc_next++;
		}
		/*
			/d argument: display
			Prints the text on the screen
		*/
		if (stricmp(argv[argc_next], "/d") == 0)
		{
			printf("%s", argv[argc_next + 1]);
			argc_next++;
		}
		/*
			/ad argument: display the assi code of character
		*/
		if (stricmp(argv[argc_next], "/ad") == 0)
		{
			for (int i = 0; i < strlen(argv[argvindex]); i++)
			{
				printf("%d ", argv[argvindex][i]);
				argc_next++;
			}
		}
		/*
			/l argument: strlen
			Return the length of string
		*/
		if (stricmp(argv[argc_next], "/l") == 0)
		{
			return strlen(argv[2]);
		}
		/*
			/m argument: mouse clicks
			prints the mouse click on x y position
		*/
		if (stricmp(argv[argc_next], "/m") == 0)
		{
			mousevent(0);
			return 0;
		}
		/*
			/m_ argument: mouse hover
		*/
		if (stricmp(argv[argc_next], "/m_") == 0)
		{
			mousevent(1);
			return 0;
		}
		/*
			/s argument: plays a wav file
		*/
		if (stricmp(argv[argc_next], "/s") == 0)
		{
			PlaySound(argv[argc_next + 1], NULL, 0x00020000L | 0x0002);
			argc_next++;
		}
		/*
			/n argument: Prints or got a new line
		*/
		if (stricmp(argv[argc_next], "/n") == 0)
		{
			printf("\n");
		}
		/*
			/o argument: change xy origin of console
		*/
		if (stricmp(argv[argc_next], "/o") == 0)
		{
			xpos = atoi(argv[argc_next + 1]);
			ypos = atoi(argv[argc_next + 2]);
			gotoxy(xpos, ypos);
			argc_next += 2;
		}
		/*
			/q argument: enable or diable quick edit mode.
			Prints the ASCII
		*/
		if (stricmp(argv[argc_next], "/q") == 0)
		{
			HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
			DWORD dwMode;
			// Get current console mode
			GetConsoleMode(hConsoleInput, &dwMode);

			// Disable QuickEdit mode
			if (atoi(argv[argc_next + 1]) == 0)
			{
				// Disable QuickEdit mode
				SetConsoleMode(hConsoleInput, 0x0080 | (dwMode & ~0x0040));
			}
			else
			{
				// Enable QuickEdit mode
				SetConsoleMode(hConsoleInput, dwMode | 0x0040 | 0x0080);
			}
			// Close the open handle

			CloseHandle(hConsoleInput);
			argc_next++;
		}
		/*
			/A argument: ASCII
			Prints the ASCII
		*/
		if (stricmp(argv[argc_next], "/a") == 0)
		{
			printf("%c", atoi(argv[argc_next + 1]));
			argc_next++;
		}
		/*
			/k_ argument: key
			use function getch() in conio.h without blocking
		*/
		if (stricmp(argv[argc_next], "/k_") == 0)
		{
			if (kbhit() != 0)
			{
				int key = _getch();
				if (key == 0 || key == 224)
				{
					key = 255 + _getch();
				}
				return (key);
			}
		}
		argc_next++;
	}
	return 0;
}
