#include <cctype>

#include <ncurses.h>

#include "editor.h"
#include "shared_memory.h"

void insert(char character, volatile BufferContents *bufferContent)
{

}

void update(volatile BufferContents* bc, int cursorId)
{
    char input;
	switch(input = getch()) {
		case KEY_UP:
			int offsetToLeft = 0;
			while (offsetToLeft < bufferContent->size - bufferContent->cursorPos[cursorIdentity] && bufferContent->content[bufferContent->cursorPos[cursorIdentity] - offsetToLeft] != '\n')
				offsetToLeft++;

			int lineLengthAbove = 0;
			while(offsetToLeft + lineLengthAbove > bufferContent->cursorPos[cursorIdentity] && bufferContent->content[bufferContent->cursorPos[cursorIdentity] - offsetToLeft - lineLengthAbove] != '\n')
				lineLengthAbove++;

			cursorPos[cursorIdentity] -= lineLengthAbove;
			break;

		// Move cursor down
		case KEY_DOWN:
			if ()
			int cursorXPos; // Var to store X position of current cursor
			int nextLineLen = 0;

			int runBack = cursorID;
			int runForward = cursorID;
			
			// Finds the position of the last \n
			while (runBack != 0 && bc->content[runBack] != '\n')
				runBack--;
			
			// Calculates the x position of the cursor
			cursorXPos = cursorID - runBack;

			



			while(offsetToRight <= bufferContent->size - bufferContent->cursorPos[cursorIdentity] && bufferContent[bufferContent->cursorPos[cursorIdentity] + offsetToRight] != '\n')
				offsetToRight++;

			cursorPos += offsetToLeft + offsetToRight;
			break;
		case KEY_LEFT:
			cursorPos[cursorIdentity]--;
			break;
		case KEY_RIGHT:
			cursorPos[cursorIdentity]++;
			break;
		case KEY_HOME:
			int shift = bufferContent->cursorPos[cursorIdentity];
			while (shift >= 0 && bufferContent->content[shift] != '\n')
				shift--;

			cursorPos[cursorIdentity] = shift + 1;
			break;
		case KEY_BACKSPACE:
			for (int i = bufferContent->cursorPos[cursorIdentity]; i < bufferContent->size && i > 0; i++)
				bufferContent->content[i - 1] = bufferContent->content[i];

			bufferContent->size--;
			break;
		case KEY_ENTER:
			insert('\n', bufferContent);
			break;
		case KEY_TAB:
			insert('\t', bufferContent);
			break;
		default:
			if (isprint(input))
				insert(input, bufferContent);
			break;
	}
}
