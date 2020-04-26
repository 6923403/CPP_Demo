APP = Employee
main: main.o Em.o
	g++  main.o Em.o -o Em
main.o: main.cpp Em.h
	g++ -c main.cpp -o main.o
Em.o: Em.cpp Em.h
	g++ -c Em.cpp -o Em.o

.PHONY:clean
clean:
	rm -f *.o
