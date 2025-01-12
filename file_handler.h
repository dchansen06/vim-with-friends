#include "shared_memory.h"

#ifndef FILE_HANDLER_H
	#define FILE_HANDLER_H
	extern volatile bool quitFlag;
	extern volatile bool saveFlag;

	bool readFile(volatile BufferContents* buffer, char *fileName);
	bool writeFile(volatile BufferContents* buffer, char *fileName);
#endif
