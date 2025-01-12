#include <string>

#ifndef SHARED_MEMORY_H
	#define SHARED_MEMORY_H

	struct BufferContents {
		unsigned long long size;
		int numberOfCursors;
		int cursorPosition[16];	// MAGIC
		char content[];
	};

	volatile BufferContents* getSharedMemory(std::string filename, bool &host);

	int unlink(std::string filename);
#endif
