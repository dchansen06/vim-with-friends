#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "files.h"
#include "shared_memory.h"

using namespace std;

bool readFile(volatile BufferContents* buffer, char *fileName) {
    ifstream inFile;
    inFile.open(fileName);
    if(inFile) {
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
    inFile.close();
    return false;
}
