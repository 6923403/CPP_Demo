APP = BOX
main: main.o box.o
	g++ main.o box.o -o box
main.o: main.cpp box.h
	g++ -c main.cpp -o main.o
box.o: box.cpp box.h
	g++ -c box.cpp -o box.o

.PHONY:clean
clean:
	rm -f *.o
