APP = Screen
main: main.o screen.o
	g++ main.o screen.o -o screen
main.o: main.cpp screen.h
	g++ -c main.cpp -o main.o
screen.o: screen.cpp screen.h
	g++ -c screen.cpp -o screen.o

.PHONY:clean
clean:
	rm -f *.o
