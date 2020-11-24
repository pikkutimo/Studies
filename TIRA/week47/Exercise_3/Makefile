CXX=g++
CXXFLAGS=-std=c++11
BIN=main

SRC=$(*.cpp)
OBJ=main.o utilities.o

main: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)