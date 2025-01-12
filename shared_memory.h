#include <string>

#ifndef SHARED_MEMORY_H
	#define SHARED_MEMORY_H

	struct BufferContents {
		unsigned int size;
		int numCursors;
		int cursorPos[16];	// MAGIC
		bool isBeingAccessed; // pause all accesses until this is cleared
		char content[];
	};

	volatile BufferContents* getSharedMemory(std::string filename, bool &host);

	int unlink(std::string filename);
#endif
