APP = MyTime
main: main.o mytime.o
	g++ main.o mytime.o -o mytime
main.o: main.cpp mytime.h
	g++ -c main.cpp -o main.o
mytime.o: mytime.cpp mytime.h
	g++ -c mytime.cpp -o mytime.o

.PHONY:clean
clean:
	rm -f *.o

