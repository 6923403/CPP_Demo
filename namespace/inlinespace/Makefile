APP = XY
CXX = g++
CXXFILES = main.o test.o

all: main test app

main: main.cpp test.h
	$(CXX) -g -c main.cpp -o main.o

test: test.cpp test.h
	$(CXX) -g -c test.cpp -o test.o

app: main.o test.o
	$(CXX) -g  main.o test.o -o $(APP)

.PHONY: clean
clean:
	rm $(CXXFILES)
