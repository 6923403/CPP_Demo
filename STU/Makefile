APP = Student
CC = g++

OBJECTS = main.o Student.o Console.o Course.o Date.o \
	 ElectiveCourse.o ObligatoryCourse.o

Student: $(OBJECTS)
	$(CC) -Wall -O2 -g $(OBJECTS) -o $(APP)

#main.o: Console.h
objects:= $(patsubst %.c, %.o, $(wildcard *.c))

stu: $(objects)
	$(CC) $(objects) -o stu 

.PHONY: clean
clean:
	rm Student $(OBJECTS)
