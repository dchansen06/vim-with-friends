#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "unistd.h"

#include "shared_memory.h"
#include "vfNCurse.h"
#include "editor.h"
#include "file_handler.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 3) {	// ./main unlink <file>
	unlinkFile(argv[2]);
	return 2;
    } else if(argc < 2) {
        cout << "Too few arguments.\n";
        return 1;
    }

    bool isHost;
    volatile BufferContents *sharedBuffer = getSharedMemory(static_cast<string>(argv[1]), isHost);
    int cursorIdentity;
    if(isHost) {
        cursorIdentity = 0;
        sharedBuffer->numCursors = 1;
        sharedBuffer->cursorPos[0] = 5;

        sharedBuffer->isBeingAccessed = false;
        if(!readFile(sharedBuffer, argv[1])){
            sharedBuffer->size = 0;
        }
    } else {
        while(sharedBuffer->isBeingAccessed){}
        cursorIdentity = sharedBuffer->numCursors;
	    sharedBuffer->cursorPos[sharedBuffer->numCursors++] = 0;
    }

    ScreenInfo screen;

    while(!quitFlag) {
        while(sharedBuffer->isBeingAccessed){}
        sharedBuffer->isBeingAccessed = true;
        update(sharedBuffer, cursorIdentity);
	clear();
        screen.printScreen(sharedBuffer);
        sharedBuffer->isBeingAccessed = false;

        usleep(16667);
    }
	endwin();

	if (isHost && saveFlag)
		writeFile(sharedBuffer, argv[1]);

    unlinkFile(argv[1]);
}
