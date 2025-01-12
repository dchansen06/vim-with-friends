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

	if (path == nullptr)
		path = (char*)filename.c_str();

	for (char letter : (string)path) {
		if (letter == '/')
			name += '.';
		else
			name += letter;
	}

	return "/tmp/vfNCurse/" + name;
}

volatile BufferContents* getSharedMemory(string filename, bool &host)
{
	const int SIZE = 524288;

	filename = cleanFilename(filename);
	const char* NAME = filename.c_str();

	int shm = shm_open(NAME, O_EXCL|O_CREAT|O_RDWR|O_TRUNC, 0666);

	if (EEXIST != errno) {
		host = true;
		ftruncate(shm, SIZE);
		return (volatile BufferContents*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm, 0);
	} else {
		host = false;
		shm = shm_open(NAME, O_RDWR, 0666);
		return (volatile BufferContents*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm, 0);
	}
}

int unlink(std::string filename)
{
	return shm_unlink(cleanFilename(filename).c_str());
}
