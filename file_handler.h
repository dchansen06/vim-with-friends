#include <string>

#include "shared_memory.h"

#ifndef SHARED_MEMORY_H
	#define SHARED_MEMORY_H

	bool writeFromBufferContent(BufferContent *bufferContent, std::string filename);
	bool readIntoBufferContent(std::string filename, BufferContent *bufferContent);
#endif
