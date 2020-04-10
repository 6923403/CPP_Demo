APP = FBOX
main: main.o fbox.o
	g++ main.o fbox.o -o fbox
main.o: main.cpp fbox.h
	g++ -c main.cpp -o main.o
fbox.0: fbox.cpp fbox.h
	g++ -c fbox.cpp -o fbox.o

.PHONY:clean
clean:
	rm -f *.o
