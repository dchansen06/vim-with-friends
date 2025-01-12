all: main

%.o: %.cpp | %.h
	g++ -Wall -Wextra -c $(^) -o $(@)

main: main.cpp shared_memory.o
	g++ $(^) -o $(@) -lncurses -Wall -Wextra

clean:
	rm -f main *.o
