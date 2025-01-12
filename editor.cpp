#include <cctype>

#include <ncurses.h>

#include "editor.h"
#include "shared_memory.h"

void insert(char character, volatile BufferContents *bufferContent)
{

}

void update(volatile BufferContents* bc, int& cursorID)
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

void moveDown (const int& content[], int size, int& cursorID){
			int cursorXPos; // Var to store X position of current cursor
			int nextLineLen;

			int posLastEndl = cursorID;
			int rightEndL = cursorID;
			
			// Finds the position of the last \n
			while (posLastEndl != 0 && content[posLastEndl] != '\n')
				posLastEndl--;
			
			// Calculates the x position of the cursor
			cursorXPos = cursorID - posLastEndl;

			// Runs till the end of current line
			while (content[rightEndL] != '\n'){

				// If already the last, then don't go anywhere
				if (rightEndL == size){
					return;
				}

				rightEndL++;

			}

			// Gets the size of the next line
			while (content[rightEndL + nextLineLen] != '\n')
				nextLineLen++;
			
			
			if (cursorXPos > nextLineLen){
				cursorID = rightEndL + nextLineLen;
				break;
			}
			cursorID = rightEndL + cursorXPos;
			break;
}
