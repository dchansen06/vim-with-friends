all: main

%.o: %.cpp
	g++ -Wall -Wextra -c $(^) -o $(@)

main: vfNCurse.o shared_memory.o
	g++ $(^) -o $(@) -lncurses -Wall -Wextra
