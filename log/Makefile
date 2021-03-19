APP = logg
CXX = g++
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CXXFLAGS = -W -Wall -O0 -g
else
	CXXFLAGS = -O2
endif

log: main.cpp logger.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(APP)

clean:
	rm $(APP)
