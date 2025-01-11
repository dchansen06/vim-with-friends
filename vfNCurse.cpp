#include <curses.h>
#include <iostream>

struct Cursor{
    
    // xy coordinates of the cursor
    int X;
    int Y;

};

// Precondition: takes in a character for cursor movement
// Postcondition: moves the cursor based on the input
void moveCursor (int, Cursor&);

// Initializes ncurses
void initializeScreen();

int main(){

    // Sets up everything for ncurses
    initializeScreen();

    // Creates cursor object
    Cursor cur = {0, 0};

    int chr = 'a';
    while (chr != 'p'){
        chr = getch();
        moveCursor(chr, cur);
    }
    
    printw("Hello World");

    getch();

    endwin();

    return 0;
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
}

// Precondition: takes in a character for cursor movement
// Postcondition: moves the cursor based on the input
void moveCursor (int chr, Cursor& cur){
        if (chr == KEY_UP){
            cur.Y--;
        }
        if (chr == KEY_DOWN){
            cur.Y++;
        }
        if (chr == KEY_RIGHT){
            cur.X++;
        }
        if (chr == KEY_LEFT){
            cur.X--;
        }
        move(cur.Y, cur.X);
}
