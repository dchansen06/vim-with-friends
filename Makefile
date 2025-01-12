CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17
RM = rm
RMFLAGS = -f
LDFLAGS = -lncurses
BINNAME = vwf

.PHONY: all install test clean

.DELETE_ON_ERROR:

all: $(BINNAME)

install: all
	cp $(BINNAME) ~/.local/bin

%.o: %.cpp | %.h
	$(CXX) $(CXXFLAGS) -c $(^) -o $(@)

vwf: main.cpp vfNCurse.o shared_memory.o editor.o file_handler.o
	$(CXX) $(CXXFLAGS) $(^) -o $(@) $(LDFLAGS)

test: $(BINNAME)
	#-./$(^) u test.txt
	./$(^) test.txt

clean:
	$(RM) $(RMFLAGS) $(BINNAME) *.o
