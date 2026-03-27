SAN_FLAGS=-fsanitize=address,undefined
CXX=clang++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -g $(SAN_FLAGS)
LDFLAGS=$(SAN_FLAGS)
LINK.o=$(LINK.cc)

PROG=main
OBJS=$(PROG).o intarray.o test_int_array.o

all: $(PROG)

$(PROG): $(OBJS)

clean:
	rm -f *.o $(PROG)
