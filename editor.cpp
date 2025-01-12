#include <cctype>

#include <ncurses.h>

#include "editor.h"
#include "shared_memory.h"

void insert(char character, volatile BufferContents *bufferContent)
{

}

void update(volatile BufferContents *bufferContent, int cursorIdentity)
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
		case KEY_DOWN:
			int offsetToLeft = 0;
			while (offsetToLeft < bufferContent->size - bufferContent->cursorPos[cursorIdentity] && bufferContent->content[bufferContent->cursorPos[cursorIdentity] - offsetToLeft] != '\n')
				offsetToLeft++;

			int offsetToRight = 0;
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
			int i = bufferContent->cursorPos[cursorIdentity];
			while (i >= 0 && bufferContent->content[i] != '\n')
				i--;

			cursorPos[cursorIdentity] = i + 1;
			break;
		case KEY_BACKSPACE:
			for (int i = bufferContent->cursorPos[cursorIdentity]; i < bufferContent->size && i > 0; i++) {
				bufferContent->content[i - 1] = bufferContent->content[i];
			}
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
