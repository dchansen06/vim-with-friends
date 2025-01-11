#include <string>

#include "shared_memory.h"

#ifndef SHARED_MEMORY_H
	#define SHARED_MEMORY_H

	writeFromBufferContent(BufferContent *bufferContent, std::string filename);
	readIntoBufferContent(std::string filename, BufferContent *bufferContent);
#endif
