#include <fstream>
#include <string>
#include <cstdlib>

#include "shared_memory.h"
#include "editor.h"

using namespace std;

volatile bool quitFlag = false;
volatile bool saveFlag = false;

bool readFile(volatile BufferContents* buffer, char *fileName)
{
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
	for(i = 0; !inFile.eof(); i++) {
		buffer->content[i] = ch;
		inFile.get(ch);
	}
	buffer->size = i;
	inFile.close();
	buffer->isBeingAccessed = false;
	return true;
}

bool writeFile(volatile BufferContents* buffer, char *fileName)
{
	while(buffer->isBeingAccessed){}

	buffer->isBeingAccessed = true;
	ofstream outFile(fileName);
	if(!outFile) {
		outFile.close();
		buffer->isBeingAccessed = false;
		return false;
	}

	for(volatile long long unsigned i = 0; i < buffer->size; i++)
		outFile << buffer->content[i];

	outFile.close();
	buffer->isBeingAccessed = false;
	return true;
}
