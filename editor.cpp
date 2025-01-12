#include <cctype>

#include <iostream>

#include <ncurses.h>

#include "editor.h"
#include "shared_memory.h"
#include "file_handler.h"

void insert(char character, volatile BufferContents *bufferContent, int cursorIdentity)
{
	bufferContent->size++;

	for (volatile int i = bufferContent->size - 1; i >= bufferContent->cursorPos[cursorIdentity]; i--) {
		bufferContent->content[i+1] = bufferContent->content[i];
	}

	bufferContent->content[bufferContent->cursorPos[cursorIdentity]] = character;
	bufferContent->cursorPos[cursorIdentity]++;

	for (int i = 0; i < bufferContent->numCursors; i++) {
		if (bufferContent->cursorPos[i] > bufferContent->cursorPos[cursorIdentity])
			bufferContent->cursorPos[i]--;
	}
}

void update(volatile BufferContents* bufferContent, int cursorIdentity)
{
	int input = getch();

	if (input == ERR)
		return;	// Nothing to do

	switch(input) {
		case KEY_SRIGHT:	// Save
			saveFlag = true;
			quitFlag = true;
			break;
		case KEY_SLEFT:		// Close /wo save
			quitFlag = true;
			break;
		case KEY_RIGHT:
			moveRight(bufferContent->size, bufferContent->cursorPos[cursorIdentity]);
			break;
		case KEY_UP:
			moveUp(bufferContent->content, bufferContent->size, bufferContent->cursorPos[cursorIdentity]);
			break;
		case KEY_DOWN:
			moveDown(bufferContent->content, bufferContent->size, bufferContent->cursorPos[cursorIdentity]);
			break;
		case KEY_LEFT:
			moveLeft(bufferContent->size, bufferContent->cursorPos[cursorIdentity]);
			break;
		case KEY_BACKSPACE:
			if (bufferContent->cursorPos[cursorIdentity] <= 0)
				break;

			for (volatile unsigned int i = bufferContent->cursorPos[cursorIdentity]; i < bufferContent->size && i > 0; i++)
				bufferContent->content[i - 1] = bufferContent->content[i];

			for (int i = 0; i < 16; i++) {
				if (bufferContent->cursorPos[i] >= bufferContent->cursorPos[cursorIdentity])
					bufferContent->cursorPos[i]--;
			}

			bufferContent->size--;
			break;
		case '\n':
			insert('\n', bufferContent, cursorIdentity);
			break;
		case '\t':
			insert('\t', bufferContent, cursorIdentity);
			break;
		default:
			if (isprint(input))
				insert(input, bufferContent, cursorIdentity);
			break;
	}
}

// Moves the cursor down a line
void moveDown (volatile char content[], int size, volatile int& cursorID){
			int cursorXPos; // Var to store X position of current cursor
			int nextLineLen = 0;

			int beginThisLine = cursorID;
			int rightEndl = cursorID;

			// Finds the position of the last \n
			while (beginThisLine >= 0 && content[beginThisLine] != '\n')
				beginThisLine--;

			beginThisLine++; // Gets the position of this line

			// Calculates the x position of the cursor
			cursorXPos = cursorID - beginThisLine;

			// Runs till the end of current line
			while (content[rightEndl] != '\n'){

				// If already the last, then don't go anywhere
				if (rightEndl >= size){
					return;
				}

				rightEndl++;

			}

			// Gets the size of the next line
			while (content[rightEndl + nextLineLen] != '\n')
				nextLineLen++;
			
			nextLineLen++;
			
			if (cursorXPos > nextLineLen){
				cursorID = rightEndl + nextLineLen;
				return;
			}
			cursorID = rightEndl + cursorXPos;
			return;
}

// Moves the cursor up a line
void moveUp (volatile char content[], volatile int& cursorID){
			int cursorXPos; // Var to store X position of current cursor
			int beginAboveLine;

			int beginThisLine = cursorID;
			
			// Finds the position of the last \n
			while (beginThisLine != 0 && content[beginThisLine] != '\n')
				beginThisLine--;
			
			beginThisLine++;
			// Calculates the x position of the cursor
			cursorXPos = cursorID - beginThisLine;

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
				return;
			}
			cursorID = beginAboveLine + cursorXPos;
            return;
}

// Move cursor right
void moveRight (int size, volatile int& cursorID){
	if (cursorID == size){
		return;
	}
	cursorID++;
}

// Move cursor left
void moveLeft (int size, volatile int& cursorID){
	if (cursorID == 0){
		return;
	}
	cursorID--;
}

