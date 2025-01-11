#include <string>

#ifndef SHARED_MEMORY_H
	#define SHARED_MEMORY_H

	// Always returns a shared memory file descriptor
	int getSharedMemory(std::string filename);

	struct BufferContents {
		unsigned long long size;
		int numberOfCursors;
		int[] cursorPosition;
		void* content;
	};

	BufferContents parseBufferContents(unsigned long long &size, int &numberOfCursors, int[] cursorPosition, void* content);
	void fillBufferConents(BufferContents &bufferContents, unsigned long long size, int numberOfCursors, int[] cursorPosition, void* content);

	/*
		Opening a file creates /tmp/vim-with-friends/.../
		Opening vim-with-friends checks for a tmp entry first
		When host closes file then tmp deleted
		Only host can write to file

		Share buffer memory between processes
		Everyone R/W same memory
	*/
#endif
