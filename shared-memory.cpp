#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstdlib>

using namespace std;

string cleanFilename(string filename)
{
	return realpath(filename);
}

// Always returns a shared memory file descriptor
int getSharedMemory(string filename)
{
	string name = "";
	for (char letter : cleanFilename(filename)) {
		if (letter == '/')
			name += '.';
		else
			name += letter;
	}

	// BUFFER CONTENTS
	// size_t \0 int int ... \0 <CONTENTS>
		size_t size;
		
	};
	// <SIZE> \0 <CURSOR1> <CURSOR2> ... \0 <CONTENTS>

	const int SIZE = 524288;
	const char* NAME = name;

	if (shm_open(SIZE_NAME, O_RDONLY, 0666) >= 0) {
		int shm_size = shm_open(SIZE_NAME, O_RDONLY, 0666);
		void* ptr = mmap(0, SIZE_SIZE, PROT_READ, MAP_SHARED, shm_size, 0);
		printf("%s"
	}

	// Look inside temp for that file
		// Yes - Open that one
		// No - Make a new one
	shm_unlink(name);
}
