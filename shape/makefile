APP = Shape
main: main.o shape.o
	g++ main.o shape.o -o Shape
main.o: main.cpp shape.h
	g++ -c main.cpp -o main.o
shape.o: shape.cpp shape.h
	g++ -c shape.cpp -o shape.o

.PHONY:clean
clean:
	rm -f *.o
