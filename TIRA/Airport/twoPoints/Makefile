CXX=g++
CXXFLAGS=-std=c++11
BIN=main

SRC=$(*.cpp)
OBJ=main.o queue.o utilities.o node.o plane.o random.o runway.o

main: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)