APP = test
CXX = g++


main: main.o test.o
	g++ main.o test.o -o $(APP)

main.o: main.cpp test.h
	g++ -Wall -g -c main.cpp -o main.o

test.o: test.cpp test.h
	g++ -Wall -g -c test.cpp -o test.o

.PHONY: clean
clean:
	rm *.o
