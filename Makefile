CXX = g++
CXXFLAGS = -Wall -Wextra -g
RM = rm
RMFLAGS = -f
LDFLAGS = -lncurses

all: main

%.o: %.cpp | %.h
	$(CXX) $(CXXFLAGS) -c $(^) -o $(@)

<<<<<<< HEAD
main: main.cpp shared_memory.o
	g++ $(^) -o $(@) -lncurses -Wall -Wextra

clean:
	$(RM) $(RMFLAGS) main *.o
