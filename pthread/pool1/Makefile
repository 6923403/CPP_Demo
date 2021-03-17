APP = Pool
CXX = g++
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS = -W -Wall -O0 -g
else
	CXXFLAGS = -O2
endif

pool: main.cpp pool.cpp
	$(CXX) $(CXXFLAGS) $^ -lpthread -o $(APP)

clean:
	rm $(APP)
