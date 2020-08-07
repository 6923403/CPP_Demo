APP = decode
CXX = g++
CXXFLAGS = -Wall -g -c
CXXAPP = -Wall -c
FILES: main.o test.o

all: main test app

main: main.cpp test.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

test: test.cpp test.h
	$(CXX) $(CXXFLAGS) test.cpp -o test.o

app: $(FILES)
	$(CXX) $(CXXAPP) $(FILES) -o $(APP)
