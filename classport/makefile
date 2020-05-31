APP = Port
main: main.o port.o
	g++ main.o port.o -o Port
main.o: main.cpp port.h
	g++ -c main.cpp -o main.o
port.cpp: port.cpp port.h
	g++ -c port.cpp -o port,o

.PHONY:clean
clean:
	rm -r *.o
