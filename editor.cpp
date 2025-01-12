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

void update(volatile BufferContents* bufferContent, int& cursorIdentity)
{
	char input = getch();

	if (input == ERR)
		return;	// Nothing to do

	switch(input) {
		case 27: // ␛
			if (getch() != '[')
				break;

			input = getch();
			switch(input) {
				case 'A':
					moveUp(bufferContent->content, bufferContent->size, bufferContent->cursorPos[cursorIdentity]);
					break;
				case 'B':
					moveDown(bufferContent->content, bufferContent->size, bufferContent->cursorPos[cursorIdentity]);
					break;
				case 'C':
					moveRight(bufferContent->content, bufferContent->size, bufferContent->cursorPos[cursorIdentity]);
					break;
				case 'D':
					moveLeft(bufferContent->content, bufferContent->size, bufferContent->cursorPos[cursorIdentity]);
					break;
			}
			break;
		case KEY_HOME:
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

// Moves the cursor down a line
void moveDown (volatile char content[], int size, int& cursorID){
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

// Moves the cursor up a line
void moveUp (volatile char content[], int size, int& cursorID){
			int cursorXPos; // Var to store X position of current cursor
			int beginAboveLine;

			int beginThisLine = cursorID;
			
			// Finds the position of the last \n
			while (beginThisLine != 0 && content[beginThisLine] != '\n')
				beginThisLine--;
			
			beginThisLine++;
			// Calculates the x position of the cursor
			cursorXPos = cursorID - beginThisLine - 1;

			// Runs till the end of current line
			beginAboveLine = beginThisLine-2;
			while (content[beginAboveLine] != '\n'){
				// If already the last, then don't go anywhere
				if (beginAboveLine == 0){
					return;
				}

				beginAboveLine++;

			}

			beginAboveLine++;

			if (cursorXPos > beginThisLine - beginAboveLine){
				cursorID = beginThisLine - 2;
				break;
			}
			cursorID = beginAboveLine + cursorXPos;
			break;
}

// Move cursor right
void moveRight (volatile char content[], int size, int& cursorID){
	if (cursorID == size){
		return;
	}
	cursorID++;
}

// Move cursor left
void moveLeft (volatile char content[], int size, int& cursorID){
	if (cursorID == 0){
		return;
	}
	cursorID--;
}

