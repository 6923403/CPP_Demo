APP = Printdata
main: main.o printdata.o
	g++ main.o printdata.o -o print
main.o: main.o printdata.h
	g++ -c main.cpp -o main.o
printdata.o: printdata.cpp printdata.h
	g++ -c printdata.cpp -o printdata.o

.PHONY:clean
clean:
	rm -f *.o
