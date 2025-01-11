all: vfNCurse

%.o: %.cpp
	g++ -Wall -Wextra -c $(^) -o $(@)

vfNCurse: vfNCurse.cpp
	g++ $^ -o $@ -lncurses -Wall
