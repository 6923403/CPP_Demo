APP = Student
CC = g++

OBJECTS = main.o student.o stushow.o

Student: $(OBJECTS)
	$(CC) -Wall -O2 -g2 $(OBJECTS) -o $(APP)

#main.o: Console.h
objects:= $(patsubst %.c, %.o, $(wildcard *.c))

stu: $(objects)
	$(CC) $(objects) 

.PHONY: clean
clean:
	rm Student $(OBJECTS)
