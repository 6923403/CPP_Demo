APP = Maketest
CXX = g++
CXXFLAGS = -W -Wall -O0 -g

LIB += -lpthread
SRCS = $(wildcard ./src/*.cpp)
PWD := $(shell pwd)
INC = -I $(PWD)/include
SRC = -I $(PWD)/src
OBJS = $(SRCS: .cpp = .o)

all: ap
ap: $(OBJS)
	$(CXX) $(INC) $(CXXFLAGS) $(SRCS) $(LIB) -o $(APP)

.PHONY: clean
clean:
	rm  -f VcPcap 

