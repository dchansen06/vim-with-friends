#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

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

	const char* NAME = name.c_str();

	int shm = shm_open(NAME, O_EXCL|O_CREAT|O_RDWR, 0666);

	if (EEXIST != errno) {
		host = true;
		cout << "Trying to do ftruncate " << ftruncate(shm, SIZE) << endl;
		//ftruncate(shm, SIZE);
		return (volatile BufferContents*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm, 0);
	} else {
		host = false;
		shm = shm_open(NAME, O_RDWR, 0666);
		return (volatile BufferContents*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm, 0);
	}
}
