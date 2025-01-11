// vfNCurse.cpp

// Include statements
#include <curses.h>
#include <string>

using namespace std;

// Define Statements
#define HIGHLIGHTING 1

struct Cursor{
    // xy coordinates of the cursor
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

int main(){

    // Sets up everything for ncurses
    initializeScreen();

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

<<<<<<< HEAD
        // Moves cursor if needed
        moveCursor(chr, cur);

        // Deals with commands in normal mode
=======
        if (!(mode == "INSERT" && chr == '0')){
            moveCursor(chr, cur);
        }

>>>>>>> 8acd0c5c75c1b8e33c4f82b4b8cdf545107e1117
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
<<<<<<< HEAD
        
        // Writes in insert mode
=======
>>>>>>> 8acd0c5c75c1b8e33c4f82b4b8cdf545107e1117
        } else if (mode == "INSERT"){
            if (chr == 27){
                mode = "NORMAL";
            } else if (chr < 256){
                attron(COLOR_PAIR(HIGHLIGHTING)); // Start highlighting
                addch(chr);
                attroff(COLOR_PAIR(HIGHLIGHTING)); // End highlighting
                if (cur.X != COLS - 1)
                    move(cur.Y, ++cur.X);
            }
        }

        refresh();
    }

    endwin();

    return 0;
}
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
