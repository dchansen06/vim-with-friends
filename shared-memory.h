#include <sys/shm.h>
#include <fstream>
#include <iostream>
#define SHARED_MEMORY_H

#ifndef SHARED_MEMORY_H
	#define SHARED_MEMORY_H

	int getSharedMemory(string filename);

	/*
		Opening a file creates /tmp/vim-with-friends/.../
		Opening vim-with-friends checks for a tmp entry first
		When host closes file then tmp deleted
		Only host can write to file

		Share buffer memory between processes
		Everyone R/W same memory
	*/
#endif

int main() { std::cout << "Worked\n"; }
