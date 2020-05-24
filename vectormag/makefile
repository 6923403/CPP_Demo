APP = RandWalk
main: main.o vector.o
	g++ main.o vector.o -o RandWalk
main.o: randwalk.cpp vector.h
	g++ -c randwalk.cpp -o main.o
vector.o: vector.cpp vector.h
	g++ -c vector.cpp -o vector.o

.PHONY:
clean:
	rm -r *.o
