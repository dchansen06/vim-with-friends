// Include statements
#include <curses.h>
#include <string>

#include "shared_memory.h"

#ifndef VFNCURSE_H
	#define VFNCURSE_H

	class ScreenInfo {
		
		private:
			// Cursor Object storing position of users cursor
			int curX, curY;

			// Helper Functions
			void initializeScreen(); // Initializes the screen
			void printChar(int); // Prints out a char


		public:
			
			// Constructor
			ScreenInfo();

			// Precondition: takes in a character for cursor movement
			// Postcondition: moves the cursor based on the input
			void moveCursor (int chr);
			
			// Precondition: takes in a reference to the screen buffer
			// Postcondition: prints it out to the screen
			void printScreen(volatile BufferContents* bc);

	};

	void vfNCurse();
#endif
