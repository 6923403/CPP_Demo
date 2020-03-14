APP = operatorBox
main: main.o opbox.o
	gcc main.o opbox.o -o operatorbox
main.o: main.o opbox.h
	g++ -c main.cpp -o main.o
op_box.o: opbox.cpp opbox.h
	g++ -c opbox.cpp -o opbox.o

.PHONY:clean
clean:
	rm -f *.o

