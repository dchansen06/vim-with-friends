#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "shared_memory.h"
#include "vfNCurse.h"

using namespace std;

bool readFile(volatile BufferContents* buffer, char *fileName) {
    ifstream inFile(fileName);
    if(!inFile) {
        inFile.close();
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
    return true;
}

bool writeFile(volatile BufferContents* buffer, char *fileName) {
    ofstream outFile(fileName);
    if(!outFile) {
        outFile.close();
        return false;
    }

    char ch;
    for(int i = 0; i < buffer->size; i++) {
        outFile << ch;
    }
    outFile.close();
    return true;
}


int main(int argc, char *argv[]) {
    if(argc < 2) {
        cout << "Too few arguments.\n";
        return 1;
    }
    
    bool isHost;
    volatile BufferContents *sharedBuffer = getSharedMemory(argv[1], isHost);
    if(isHost) {
        sharedBuffer->numberOfCursors = 1;
        sharedBuffer->cursorPosition[0] = 0;

        if(!readFile(sharedBuffer, argv[1])){
            sharedBuffer->size = 0;
        }
    }


}
