// vfNCurse.cpp

// Include statements
#include <curses.h>
#include <string>

using namespace std;

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

// Precondition: takes in the current mode of the editor and the cursor object
// Postcondition: displays the current mode of the editor
void displayMode(string, Cursor);

int main(){

    // Sets up everything for ncurses
    initializeScreen();

    // Creates cursor object and stores current mode of the editor
    Cursor cur = {0, 0};
    string mode = "NORMAL";

    int chr = 'a';
    while (chr != 'q'){
        displayMode(mode, cur);
        chr = getch();
        moveCursor(chr, cur);
        if (mode == "NORMAL"){
            if (chr == 'i'){
                mode = "INSERT";
            }
        } else if (mode == "INSERT"){
            if (chr == 27){
                mode = "NORMAL";
                continue;
            }
            if (chr < 256){
                addch(chr);
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

}

// Precondition: takes in a character for cursor movement
// Postcondition: moves the cursor based on the input
void moveCursor (int chr, Cursor& cur){
        if (chr == KEY_UP && chr != 0){
            cur.Y--;
        }
        if (chr == KEY_DOWN && chr != LINES){
            cur.Y++;
        }
        if (chr == KEY_RIGHT && != COL){
            cur.X++;
        }
        if (chr == KEY_LEFT && != 0){
            cur.X--;
        }
        move(cur.Y, cur.X);
}
