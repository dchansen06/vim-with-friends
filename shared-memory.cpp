#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

string cleanFilename(string filename)
{
	char* output = realpath(filename, new char[PATH_MAX + 1]);
	string out = output;
	delete output;
	return out;
}

BufferContents* getSharedMemory(string filename, bool &host)
{
	string name = "";
	for (char letter : cleanFilename(filename)) {
		if (letter == '/')
			name += '.';
		else
			name += letter;
	}

	const int SIZE = 524288;
	const char* NAME = name;
	BufferContents* bc;

	int shm = shm_open(NAME, O_RDWR, 0666);
	if (shm >= 0) {
		shm_unlink(NAME);

		host = false;
		shm = shm_open(NAME, O_RWDR, 066);

		return (BufferContents*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm, 0);
	} else {
		host = true;

		shm = shm_open(NAME, O_CREAT | O_RDWR, 0666);
		ftruncate(shm, SIZE);

		if (shm >= 0)
			return (BufferContents*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm, 0);
	}

	return nullptr;
}

void parseBufferContents(BufferContents bufferContents, unsigned long long &size, int &numberOfCursors, int[] cursorPosition, void* content)
{
	size = bufferContents.size;
	numberOfCursors = bufferContents.numberOfCursors;
	cursorPosition = bufferContents.cursorPosition;
	content = bufferContents.content;
}

BufferContents readBufferConents(BufferContents &bufferContents, unsigned long long size, int numberOfCursors, int[] cursorPosition, void* content)
{
	BufferContents bc;
	bc.size = size;
	bc.numberOfCursors = numberOfCursors;
	bc.cursorPosition = cursorPosition;
	bc.content = content;
	return bc;
}
