CXX = g++
CXXFLAGS = -Wall -Wextra -g
RM = rm
RMFLAGS = -f
LDFLAGS = -lncurses

all: main

%.o: %.cpp | %.h
	$(CXX) $(CXXFLAGS) -c $(^) -o $(@)

main: main.cpp vfNCurse.o shared_memory.o
	$(CXX) $(CXXFLAGS) $(^) -o $(@) $(LDFLAGS)

clean:
	$(RM) $(RMFLAGS) main *.o
