APP = Student
CC = g++

OBJECT = main.o Student.o

main: $(OBJECT)
	$(CC) -Wall -O2 $(OBJECT) -o $(APP)

main.o: main.cpp Student.h
	$(CC) -g -c main.cpp -o main.o

Student.o: Student.cpp Student.h
	$(CC) -g -c Student.cpp -o Student.o

.PHONY: clean
clean:
	rm Student $(OBJECTS)
