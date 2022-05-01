#include "ConsoleDisplay.h"

HANDLE consoleHandler;
HANDLE initConsoleHandler()
{
	HANDLE stdCnsHndlr;
	stdCnsHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleHandler = stdCnsHndlr;
	return consoleHandler;
}
void closeConsoleHandler(HANDLE hndlr)
{
	CloseHandle(hndlr);
}
int gotoxy(HANDLE consHandler, int x, int y)
{
	if (consHandler == INVALID_HANDLE_VALUE)
		return 0;
	COORD coords = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(consHandler, coords);
}