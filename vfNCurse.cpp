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
    printingCur.X= 0;
    printingCur.Y = 0;

}

// Displays the current mode of the editor
void ScreenInfo::displayMode(string mode){
    mvprintw(LINES-2, 0, mode.c_str()); // Prints out the mode
    move(printingCur.Y, printingCur.X); // Puts cursor back where it goes
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

    // Hides the real cursor
    curs_set(0);

    // No blocking getch(), but getch() now returns ERR if nothing going in
    nodelay(0, true);
}

// Precondition: takes in a reference to the screen buffer
// Postcondition: prints it out to the screen
void ScreenInfo::printScreen(volatile BufferContents* bc){
    printingCur.X = printingCur.Y = 0;
    // Runs through the contents of the buffer, printing them to the screen
    for(volatile unsigned long long i = 0; i < bc->size; i++){
        int chr = bc->content[i]; // Get the character form the array
        
        // Check for escape characters
        switch (chr){
            case '\t':
                for (int i = 0; i < 4; i++){
                    printChar (' ');
                }
                continue;
            case '\n':
                if(printingCur.Y >= LINES){
                    goto leaveLoop;
                }
                printingCur.X = 0;
                printingCur.Y++;
                move(printingCur.Y, printingCur.X);
                continue;
        }
        
        // Otherwise, prints out the character
        for (volatile int j = 0; j < bc->numCursors; j++){
            if ((int)i == bc->cursorPos[j])
            attron(COLOR_PAIR(HIGHLIGHTING));
        }
        printChar (chr);
        attroff(COLOR_PAIR(HIGHLIGHTING));
    }
leaveLoop:
    refresh();
    
}

// Print a single character
void ScreenInfo::printChar (int chr){
    // Print out the character
    // Move the cursor over
    if (printingCur.X != COLS - 1) {
        addch(chr);
        move(printingCur.Y, ++printingCur.X);
    }
}

int ScreenInfo::getLines (){
    return LINES;
}
