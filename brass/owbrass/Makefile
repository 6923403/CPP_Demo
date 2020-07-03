APP = Brass
CC = g++

OBJECTS = main.o brass.o

all: main.o brass.o brass

main.o: main.cpp brass.h
	$(CC) -c main.cpp -o main.o

brass.o: brass.cpp brass.h
	$(CC) -c brass.cpp -o brass.o 

brass: $(OBJECTS)
	$(CC) -Wall -O2 $(OBJECTS) -o $(APP)

.PHONY: clean
clean: 
	rm -r $(APP) $(OBJECTS)
