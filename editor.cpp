#include <cctype>

#include <ncurses.h>

#include "editor.h"
#include "shared_memory.h"

void insert(char character, volatile BufferContents *bufferContent, int cursorIdentity)
{
	for (volatile unsigned long i = bufferContent->size; i >= bufferContent->cursorPos[cursorIdentity]; i--) {
		bufferContent->size++;
		bufferContent->content[i+1] = bufferContent->content[i];
	}

	bufferContent->content[bufferContent->cursorPos[cursorIdentity]] = character;
	bufferContent->cursorPos[cursorIdentity]++;

	for (int i = 0; i < 16; i++) {
		if (bufferContent->cursorPos[i] > bufferContent->cursorPos[cursorIdentity])
			bufferContent->cursorPos[i]--;
	}
}

void update(volatile BufferContents* bc, int& cursorID)
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

		// Move cursor down
		case KEY_DOWN:
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

			for (int i = 0; i < 16; i++) {
				if (bufferContent->cursorPos[i] > bufferContent->cursorPos[cursorIdentity])
					bufferContent->cursorPos[i]--;
			}

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

void moveDown(volatile char* content, volatile int size, int& cursorID){
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
