APP = COW
main: main.o cow.o
	g++ main.o cow.o -o cow
main.o: main.cpp cow.h
	g++ -c main.cpp -o main.o
cow.o: cow.cpp cow.h
	g++ -c cow.cpp -o cow.o

.PHONY:clean
clean:
	rm -r *.o
