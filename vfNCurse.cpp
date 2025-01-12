// vfNCurse.cpp

// Include statements
#include <curses.h>
#include <string>

#include "vfNCurse.h"

using namespace std;

// Define Statements
#define HIGHLIGHTING 1

// Constructor
ScreenInfo::ScreenInfo(){
    // Initializes the screen
    initializeScreen();

    // Initialize cursor
    myCur.X = 0;
    myCur.Y = 0;

}

// Displays the current mode of the editor
void ScreenInfo::displayMode(string mode){
    mvprintw(LINES-2, 0, mode.c_str()); // Prints out the mode
    move(myCur.Y, myCur.X); // Puts cursor back where it goes
}

// Initializes the screen
void ScreenInfo::initializeScreen(){
    // Initializes the ncurse screen
    initscr();
    
    // Disables line buffering (stops the terminal screen from taking the characters)
    // Sets curses screen to take in one character at a time
    cbreak();
    
    // Don't echo the input back to the screen - don't print out what has been typed in
    noecho();
    
    // Clears the terminal screen
    clear();
    
    // Allows input from the arrow keys
    keypad(stdscr, TRUE);
    
    // Color
    // Tests if the terminal supports color
    if (has_colors() == FALSE){
        endwin();
        printf("Your terminal doesn't support color!");
        exit(1);
    }
    start_color(); // Initializes color
    init_pair(HIGHLIGHTING, COLOR_BLACK, COLOR_WHITE); // Associates HIGHLIGHTING to black on white
}

// Precondition: takes in a character for cursor movement
// Postcondition: moves the cursor based on the input
void ScreenInfo::moveCursor (int chr){
    switch (chr){
        // Move Up
        case KEY_UP:
            if (myCur.Y != 0)
                myCur.Y--;
            break;

        // Move down
        case KEY_DOWN:
            if(myCur.Y != LINES-3)
                myCur.Y++;
            break;

        // Move right
        case KEY_RIGHT:
            if (myCur.X != COLS - 1)
                myCur.X++;
            break;

        // Move left
        case KEY_LEFT:
            if (myCur.X != 0)
                myCur.X--;
            break;
    }
    move(myCur.Y, myCur.X);
}

// Precondition: takes in a reference to the screen buffer
// Postcondition: prints it out to the screen
void ScreenInfo::printScreen(ScreenBuffer* sb){
    // Runs through the contents of the buffer, printing them to the screen
    for(size_t i = 0; i < sb->size; i++){
        refresh();
        int chr = sb->content[i]; // Get the character form the array
        
        // Check for escape characters
        switch (chr){
            case '\t':
                for (int i = 0; i < 4; i++){
                    printChar (' ');
                }
                continue;
            case '\n':
                myCur.X = 0;
                myCur.Y++;
                move(myCur.Y, myCur.X);
                continue;
        }
        
        // Otherwise, prints out the character
        printChar (chr);
    }
    refresh();
}

ScreenBuffer* fillScreenBuffer(BufferContents* bufferContents)
{
	return (ScreenBuffer*)bufferContents;	// May have to do more edits later, for now it is good
}

// Print a single character
void ScreenInfo::printChar (int chr){
    // Print out the character
    addch(chr);
    // Move the cursor over
    if (myCur.X != COLS - 1)
        move(myCur.Y, ++myCur.X);
}

bool ScreenInfo::checkCursor (Cursor cursors[], int numCurs){
    // Checks each cursor position
    for (int i = 0; i < numCurs; i++){
        // If found return true
       if (myCur == cursors[i]){
           return true;
       }
    }
    return false;
}
