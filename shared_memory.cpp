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
		cerr << "Something went really wrong, could not find " << path << endl;
		exit(-1);
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

	filename = "/tmp" + cleanFilename(filename);
	const char* NAME = filename.c_str();

	errno = 0;
	int shm = shm_open(NAME, O_EXCL|O_CREAT|O_RDWR, 0666);
	cout << "shm is " << shm << " and errno is " << errno << " and filename is " << NAME << endl;

	if (EEXIST != errno && shm >= 0) {
		host = true;
		ftruncate(shm, SIZE);
		return (volatile BufferContents*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm, 0);
	} else if (shm >= 0) {
		host = false;
		shm = shm_open(NAME, O_RDWR, 0666);
		return (volatile BufferContents*)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm, 0);
	} else {
		cerr << "Something went wrong horribly!\n";
		exit(-1);
	}
}

int unlink(std::string filename)
{
	return shm_unlink(cleanFilename(filename).c_str());
}
