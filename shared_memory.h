#include <string>

#ifndef SHARED_MEMORY_H
	#define SHARED_MEMORY_H

	struct BufferContents {
		unsigned int size;
		int numberOfCursors;
		int cursorPosition[16];	// MAGIC
        bool isBeingAccessed; // pause all accesses until this is cleared
		char content[];
	};

	// Always returns a shared memory file descriptor
	volatile BufferContents* getSharedMemory(std::string filename, bool &host);

	int unlink(std::string filename);
#endif
