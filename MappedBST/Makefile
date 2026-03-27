CXX=g++
SAN_FLAGS=-fsanitize=address,undefined
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -g $(SAN_FLAGS)
LINK.o=$(LINK.cc)

PROG=test
OBJS=$(PROG).o catch_main.o

all: $(PROG)

$(PROG): $(OBJS)

clean:
	rm -f *.o $(PROG)
