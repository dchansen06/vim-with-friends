#include <iostream>
#include <string>
#include <fstream>

#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

#include <sys/mman.h>

#include "shared_memory.h"

using namespace std;

string cleanFilename(string filename)
{
	char buf[PATH_MAX];
	char* path = realpath(filename.c_str(), buf);

	if (path != nullptr) {
		return (string)path;
	} else {
		cerr << "Invalid filename given!\n";
		exit(-1);
	}
}

volatile BufferContents* getSharedMemory(string filename, bool &host)
{
	string name = "";
	for (char letter : cleanFilename(filename)) {
		if (letter == '/')
			name += '.';
		else
			name += letter;
	}

	const int SIZE = 524288;
	const char* NAME = ("/tmp" + name).c_str();	// Later mkdir so that we can /tmp/vim-with-friends/

	int shm = shm_open(NAME, O_EXCL|O_CREAT|O_RDWR, 0666);
	cout << "SHM: " << shm << " should be >=0 for client\n";
	if (shm >= 0) {
		host = false;
		return (volatile BufferContents*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm, 0);
	} else {
		host = true;

		shm = shm_open(NAME, O_EXCL|O_CREAT|O_RDWR, 0666);
		ftruncate(shm, SIZE);

		if (shm >= 0)
			return (volatile BufferContents*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm, 0);
	}

	return nullptr;
}
