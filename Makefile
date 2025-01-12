CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17
RM = rm
RMFLAGS = -f
LDFLAGS = -lncurses

all: main

%.o: %.cpp | %.h
	$(CXX) $(CXXFLAGS) -c $(^) -o $(@)

main: main.cpp vfNCurse.o shared_memory.o editor.o file_handler.o
	$(CXX) $(CXXFLAGS) $(^) -o $(@) $(LDFLAGS)

test: main
	./$^ u text.txt
	./$^ text.txt

clean:
	$(RM) $(RMFLAGS) main *.o
