all: vfNCurse

%.o: %.cpp
	g++ -Wall -Wextra -c $(^) -o $(@)

vfNCurse: vfNCurse.o shared_memory.o
	g++ $(^) -o $(@) -lncurses -Wall -Wextra
