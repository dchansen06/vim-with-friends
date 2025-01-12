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
	return unlinkFile(argv[2]);
    } else if(argc < 2 || argc > 3) {
        cout << "Usage:\n\t./main [file]\n\t./main unlink [file]\n\nUse arrow keys to navigate\nshift + left arrow to quit without saving\nshift + right arrow to save and quit\n";
        return 1;
    }

    bool isHost;
    volatile BufferContents *sharedBuffer = getSharedMemory(static_cast<string>(argv[1]), isHost);
    int cursorIdentity;
    if(isHost) {
        cursorIdentity = 0;
        sharedBuffer->numCursors = 1;
        sharedBuffer->cursorPos[0] = 0;

        sharedBuffer->isBeingAccessed = false;
        if(!readFile(sharedBuffer, argv[1])){
            sharedBuffer->size = 1;
	    sharedBuffer->content[0] = '\n';
        } else {
	    if (sharedBuffer->content[sharedBuffer->size-1] != '\n')
		sharedBuffer->content[++sharedBuffer->size] = '\n';
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
        screen.printScreen(sharedBuffer);
        sharedBuffer->isBeingAccessed = false;

        update(sharedBuffer, cursorIdentity);
        usleep(16667);
	clear();
    }
	endwin();

	if (isHost && saveFlag)
		writeFile(sharedBuffer, argv[1]);

    unlinkFile(argv[1]);
}
