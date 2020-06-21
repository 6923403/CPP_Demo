APP = Student
CC = g++

OBJECTS = main.o StuMenu.o

obj = $(patsubst %.c, %.o, $(wildcard *.c))

STU: $(OBJECTS)
	$(CC) -Wall -O2 $(OBJECTS) -o $(APP)

.PHONY: clean
clean:
	rm -r $(APP) ${OBJECTS}

