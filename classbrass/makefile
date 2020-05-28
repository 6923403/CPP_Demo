APP = Brass
main: main.o brass.o
	g++ main.o brass.o -o Brass
main.o: usebrass1.cpp brass.h
	g++ -c usebrass1.cpp -o main.o
brass.o: brass.cpp brass.h
	g++ -c brass.cpp -o brass.o

.PHONY:clean
clean:
	rm -r *.o
