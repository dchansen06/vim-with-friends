CXX = g++
CXXFLAGS = -Wall -Wextra -g
RM = rm
RMFLAGS = -f
LDFLAGS = -lncurses

all: main

%.o: %.cpp | %.h
	$(CXX) $(CXXFLAGS) -c $(^) -o $(@)

main: main.o shared_memory.o
	g++ $(^) -o $(@) -lncurses -Wall -Wextra

clean:
	$(RM) $(RMFLAGS) main *.o
