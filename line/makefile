APP= Line
main: main.o line.o
	g++ main.o line.o -o line
main.o: main.cpp line.h
	g++ -c main.cpp -o main.o
line.o: line.cpp line.h
	g++ -c line.cpp -o line.o

.PHONY:clean
clean:
	rm -f *.o
