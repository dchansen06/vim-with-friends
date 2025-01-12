#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "shared_memory.h"
#include "vfNCurse.h"
#include "editor.h"

using namespace std;

bool readFile(volatile BufferContents* buffer, char *fileName) {
    while(buffer->isBeingAccessed){}

    buffer->isBeingAccessed = true;
    ifstream inFile(fileName);
    if(!inFile) {
        inFile.close();
        buffer->isBeingAccessed = false;
        return false;
    }

    char ch;
    inFile.get(ch);
    int i;
    for(i = 0; !inFile.eof(); i++){
        buffer->content[i] = ch;
        inFile.get(ch);
    }
    buffer->size = i;
    inFile.close();
    buffer->isBeingAccessed = false;
    return true;
}

bool writeFile(volatile BufferContents* buffer, char *fileName) {
    while(buffer->isBeingAccessed){}

    buffer->isBeingAccessed = true;
    ofstream outFile(fileName);
    if(!outFile) {
        outFile.close();
        buffer->isBeingAccessed = false;
        return false;
    }

    for(volatile long long unsigned i = 0; i < buffer->size; i++) {
        outFile << buffer->content[i];
    }

    outFile.close();
    buffer->isBeingAccessed = false;
    return true;
}


int main(int argc, char *argv[]) {
    if(argc < 2) {
        cout << "Too few arguments.\n";
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
            sharedBuffer->size = 0;
        }
    } else {
        while(sharedBuffer->isBeingAccessed){}
        cursorIdentity = sharedBuffer->numCursors;
	    sharedBuffer->cursorPos[sharedBuffer->numCursors++] = 0;
    }
    
    ScreenInfo screen;

    while(true) {
        update(sharedBuffer, cursorIdentity);
        screen.printScreen(sharedBuffer);
    }


    unlink(argv[1]);
}
