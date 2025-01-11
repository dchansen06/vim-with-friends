// vfNCurse.cpp

// Include statements
#include <curses.h>
#include <string>

#include "vfNCurse.h"

using namespace std;

// Define Statements
#define HIGHLIGHTING 1

void vfNCurse(){

    // Creates cursor object and stores current mode of the editor
    Cursor cur = {0, 0};
    string mode = "NORMAL";
    bool quit = false;

    int chr = 'a';
    while (!quit){
        // Displays the mode
        displayMode(mode, cur);

        // Gets user input
        chr = getch();

        // Moves cursor if needed
        moveCursor(chr, cur);

        // Deals with commands in normal mode
        if (!(mode == "INSERT" && chr == '0')){
            moveCursor(chr, cur);
        }

        if (mode == "NORMAL"){
            switch (chr){
                case 'i':
                    mode = "INSERT";
                    break;
                case 'q':
                    quit = true;
                    break;
                case '0':
                    cur.X = 0;
                    move(cur.Y, cur.X);
                    break;
            }
        
        // Writes in insert mode
        } else if (mode == "INSERT"){
            if (chr == 27){
                mode = "NORMAL";
            } else if (chr < 256){
                attron(COLOR_PAIR(HIGHLIGHTING)); // Start highlighting

            }
        }

        refresh();
    }

    endwin();
}i

// Displays the current mode of the editor
void displayMode(string mode, Cursor cur){
    mvprintw(LINES-2, 0, mode.c_str()); // Prints out the mode
    move(cur.Y, cur.X); /// Puts cursor back where it goes
}

// Initializes ncurses
void initializeScreen(){
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
void moveCursor (int chr, Cursor& cur){
    switch (chr){
        // Move Up
        case KEY_UP:
            if (cur.Y != 0)
                cur.Y--;
            break;

        // Move down
        case KEY_DOWN:
            if(cur.Y != LINES-3)
                cur.Y++;
            break;

        // Move right
        case KEY_RIGHT:
            if (cur.X != COLS - 1)
                cur.X++;
            break;

        // Move left
        case KEY_LEFT:
            if (cur.X != 0)
                cur.X--;
            break;
    }
    move(cur.Y, cur.X);
}

// Precondition: takes in a reference to the screen buffer
// Postcondition: prints it out to the screen
void printScreen(ScreenBuffer& sb, Cursor cur){
    // Runs through the contents of the buffer, printing them to the screen
    for(sb.content: chr){
        printChar (chr, cur);
    }
}

ScreenBuffer* fillScreenBuffer(BufferContents* bufferContents)
{
	return (ScreenBuffer*){bufferContents->numberOfPointers, bufferContents->cursorPosition, bufferContents->content};
}

// Print a single character
void printChar (int chr, Cursor cur){
    // Print out the character
    addch(chr);
    // Move the cursor over
    if (cur.X != COLS - 1)
        move(cur.Y, ++cur.X);
}
