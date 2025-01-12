#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/stat.h>

#include "shared_memory.h"

using namespace std;

string cleanFilename(string filename)
{
	string name = "";

	char buf[PATH_MAX];
	char* path = realpath(filename.c_str(), buf);

	if (path == NULL) {
		path = (char*)filename.c_str();
	}

	for (char letter : (string)path) {
		if (letter == '/')
			name += '.';
		else
			name += letter;
	}

	return name;
}

volatile BufferContents* getSharedMemory(string filename, bool &host)
{
	const int SIZE = 524288;

	filename = "/" + cleanFilename(filename);
	const char* NAME = filename.c_str();

	int shm = shm_open(NAME, O_EXCL|O_CREAT|O_RDWR, 0666);

	if (EEXIST != errno && shm >= 0) {
		host = true;
		ftruncate(shm, SIZE);
		return (volatile BufferContents*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm, 0);
	} else if (EEXIST == errno) {
		host = false;
		shm = shm_open(NAME, O_RDWR, 0666);
		return (volatile BufferContents*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm, 0);
	} else {
		cerr << "Something went bad!\n";
		exit(-1);
	}
}

int unlinkFile(std::string filename)
{
	return shm_unlink(("/" + cleanFilename(filename)).c_str());
}
