CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -D CMS -D TESTSYS
CHECKER_LIST = diff molecule

all: $(CHECKER_LIST)

clean:
	rm -f $(CHECKER_LIST)

molecule: molecule.cpp
	$(CC) molecule.cpp $(CCARGS) -o molecule

diff: diff.cpp
	$(CC) diff.cpp $(CCARGS) -o diff
