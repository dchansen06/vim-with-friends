#include <string>

#ifndef SHARED_MEMORY_H
	#define SHARED_MEMORY_H

	struct BufferContents {
		unsigned long long size;
		int numberOfCursors;
		int cursorPosition[16];	// MAGIC
		char content[];
	};

	// Always returns a shared memory file descriptor
	volatile BufferContents* getSharedMemory(std::string filename, bool &host);

	/*
		Opening a file creates /tmp/vim-with-friends/.../
		Opening vim-with-friends checks for a tmp entry first
		When host closes file then tmp deleted
		Only host can write to file

		Share buffer memory between processes
		Everyone R/W same memory
	*/
#endif
