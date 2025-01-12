// Include statements
#include <curses.h>
#include <string>

#include "shared_memory.h"

#ifndef VFNCURSE_H
	#define VFNCURSE_H
	struct Cursor {
		int position; // Position in the content array

		// XY position on the screen
		int X;
		int Y;
	};

	class ScreenInfo {
		
		private:
			// Cursor Object storing position of users cursor
			Cursor printingCur;

			// Helper Functions
			void initializeScreen(); // Initializes the screen
			void displayMode(std::string); // Prints the mode of the editor
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

			// Returns the number of lines on the screen
			int getLines();

	};

	void vfNCurse();
#endif
