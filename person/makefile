APP = Person
main: main.o person.o
	g++ main.o person.o -o person
main.o: main.cpp person.h
	g++ -c main.cpp -o main.o
person.o: person.cpp person.h
	g++ -c person.cpp -o person.o

.PHONY:
clean:
	rm -r *.o
