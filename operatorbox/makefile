APP = operatorBox
main: main.o op_box.o
	gcc main.o op_box.o -o operatorbox
main.o: main.o op_box.h
	g++ -c main.cpp -o main.o
op_box.o: op_box.cpp op_box.h
	g++ -c op_box.cpp -o op_box.o

.PHONY:clean
clean:
	rm -f *.o

