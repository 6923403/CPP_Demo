APP = MORE_SHAPE
main: main.o shape.o
	gcc main.o shape.o -c main
main.o: main.cpp shape.h
	gcc -c main.cpp -o main.o
shape.o: shape.cpp shape.h
	gcc -c shape.cpp -o shape.o

.PHONY:clean
clean:
	rm -f *.o
