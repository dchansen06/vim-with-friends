#include <cctype>

#include <ncurses.h>

#include "editor.h"
#include "shared_memory.h"

void insert(char character, volatile BufferContents *bufferContent, int cursorIdentity)
{
	for (volatile unsigned long position = bufferContent->size; i >= bufferContent->cursorPos[cursorIdentity]; i--) {
		bufferContent->size++;
		bufferContent->content[i+1] = bufferContent->content[i];
	}

	bufferContent->content[bufferCount->cursorPos[cursorIdentity]] = character;
	bufferCount->cursorPos[cursorIdentity]++;
}

void update(volatile BufferContents *bufferContent, int cursorIdentity)
{
	char input = getch();

	if (input == ERR)
		return;	// Nothing to do

	switch(input) {
		case KEY_UP:
			;
			int offsetToLeft = 0;
			while (offsetToLeft < bufferContent->size - bufferContent->cursorPos[cursorIdentity] && bufferContent->content[bufferContent->cursorPos[cursorIdentity] - offsetToLeft] != '\n')
				offsetToLeft++;

			int lineLengthAbove = 0;
			while(offsetToLeft + lineLengthAbove > bufferContent->cursorPos[cursorIdentity] && bufferContent->content[bufferContent->cursorPos[cursorIdentity] - offsetToLeft - lineLengthAbove] != '\n')
				lineLengthAbove++;

			bufferContent->cursorPos[cursorIdentity] -= lineLengthAbove;
			break;
		case KEY_DOWN:
			;
			int offsetLeft = 0;
			int offsetToRight = 0;
			while (offsetLeft < bufferContent->size - bufferContent->cursorPos[cursorIdentity] && bufferContent->content[bufferContent->cursorPos[cursorIdentity] - offsetLeft] != '\n')
				offsetLeft++;

			while(offsetToRight <= bufferContent->size - bufferContent->cursorPos[cursorIdentity] && bufferContent->content[bufferContent->cursorPos[cursorIdentity] + offsetToRight] != '\n')
				offsetToRight++;

			bufferContent->cursorPos[cursorIdentity] += offsetLeft + offsetToRight;
			break;
		case KEY_LEFT:
			bufferContent->cursorPos[cursorIdentity]--;
			break;
		case KEY_RIGHT:
			bufferContent->cursorPos[cursorIdentity]++;
			break;
		case KEY_HOME:
			;
			int shift = bufferContent->cursorPos[cursorIdentity];
			while (shift >= 0 && bufferContent->content[shift] != '\n')
				shift--;

			bufferContent->cursorPos[cursorIdentity] = shift + 1;
			break;
		case KEY_BACKSPACE:
			for (int i = bufferContent->cursorPos[cursorIdentity]; i < bufferContent->size && i > 0; i++)
				bufferContent->content[i - 1] = bufferContent->content[i];

			// MOVE OTHER CURSORS THAT ARE AFTER

			bufferContent->size--;
			break;
		case KEY_ENTER:
			insert('\n', bufferContent, cursorIdentity);
			break;
		case KEY_TAB:
			insert('\t', bufferContent, cursorIdentity);
			break;
		default:
			if (isprint(input))
				insert(input, bufferContent, cursorIdentity);
			break;
	}
}
