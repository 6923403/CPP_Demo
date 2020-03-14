APP=2048Game
main: main.o game.o
	g++ -O2 main.o game.o -o 2048game
main.o: main.cpp game.h
	g++ -c main.cpp -o main.o
game.o: game.cpp game.h
	g++ -c game.cpp -o game.o

.PHONY:clean
clean:
	rm -f *.o
