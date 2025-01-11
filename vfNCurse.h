// Include statements
#include <curses.h>
#include <string>

#ifndef VFNCURSE_H
	#define VFNCURSE_H
	struct Cursor{
		int X;
		int Y;
	};

	// Precondition: takes in a character for cursor movement
	// Postcondition: moves the cursor based on the input
	void moveCursor (int chr, Cursor& cursor);

	// Initializes ncurses
	void initializeScreen();

	// Precondition: takes in the current mode of the editor and the cursor object
	// Postcondition: displays the current mode of the editor
	void displayMode(string, Cursor);

	void vfNCurse();
#endif
