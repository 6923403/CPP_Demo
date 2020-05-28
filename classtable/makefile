APP = TABT
main: usett.o tabt.o
	g++ usett.o tabt.o -o TABT
usett.o: usett1.cpp tabt.h
	g++ -c usett1.cpp -o usett.o
tabt.o: tabt.cpp tabt.h
	g++ -c tabt.cpp -o tabt.o

.PHONY: clean
clean:
	rm -r *.o
