#include <cctype>

#include <ncurses.h>

#include "editor.h"

void insert(char character, BufferContents *bufferContent)
{

}

void update(BufferContents *bufferContent, int cursorIdentity)
{
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
			int offsetToLeft = 0, offsetToRight = 0;
			while (offsetToLeft < bufferContent->size - bufferContent->cursorPos[cursorIdentity] && bufferContent->content[bufferContent->cursorPos[cursorIdentity] - offsetToLeft] != '\n')
				offsetToLeft++;

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
