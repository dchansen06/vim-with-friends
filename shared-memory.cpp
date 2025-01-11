#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <string>
#include <cstdlib>

using namespace std;

string cleanFilename(string filename)
{
	char* output = realpath(filename, new char[PATH_MAX+1]);
	string out = output;
	delete output;
	return out;
}

// Always returns a shared memory file descriptor
BufferContents* getSharedMemory(string filename)
{
	string name = "";
	for (char letter : cleanFilename(filename)) {
		if (letter == '/')
			name += '.';
		else
			name += letter;
	}

	// CONTENT
	// int \0 int int ... \0 void*
	// <NUMBER OF CURSORS> \0 <CURSOR1> <CURSOR2> ... \0 <CONTENTS>


	// SIZE
	// unsigned long long
	const int SIZE_SIZE = 524288;
	const char* SIZE_NAME = "SIZE_" + name;
	const char* NAME = name;
	BufferContents* bc;
	BufferContents bufferContents;

	int shm_size = shm_open(SIZE_NAME, O_RDONLY, 0666);
	int shm = shm_open(NAME, O_CREAT | O_RDWR, 0666);
	if (shm_size >= 0) {
		bc = (BufferContents*)mmap(0, SIZE_SIZE, PROT_READ, MAP_SHARED, shm_size, 0);
		bufferContents.size = bc->size;
		return (BufferContents*)mmap(0, bc->size, PROT_WRITE, MAP_SHARED, shm, 0);
	} else {
		// Must make new everything
	}

	// Look inside temp for that file
		// Yes - Open that one
		// No - Make a new one
	shm_unlink(name);
}

/*	struct BufferContents {
		unsigned long long size;
		int numberOfCursors;
		int[] cursorPosition;
		void* content;
	};*/

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
