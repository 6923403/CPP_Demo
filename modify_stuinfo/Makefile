APP = Student
CC = g++

OBJECTS = main.o Cpeople.o CStudent.o

Student: $(OBJECTS)
	$(CC) -Wall -O2 -g $(OBJECTS) -o $(APP)

#main.o: Console.h
objects:= $(patsubst %.c, %.o, $(wildcard *.c))

stu: $(objects)
	$(CC) $(objects) -o stu 

.PHONY: clean
clean:
	rm Student $(OBJECTS)
