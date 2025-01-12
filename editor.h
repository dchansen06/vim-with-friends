#include "shared_memory.h"

#ifndef EDITOR_H
	#define EDITOR_H

	void insert(char character, volatile BufferContents *bufferContent, int cursorIdentity);
	void moveDown (volatile char content[], int size, volatile int& cursorID);
	void moveUp (volatile char content[], int size, volatile int& cursorID);
	void moveRight (int size, volatile int& cursorID);
	void moveLeft (volatile int& cursorID);
	void update(volatile BufferContents* bufferContent, int cursorIdentity);
#endif
