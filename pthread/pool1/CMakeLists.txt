cmake_minimum_required(VERSION 3.17)
project(CPP_Demo)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -lpthread)

include_directories(.)

add_executable(CPP_Demo
        main.cpp
        pool.cpp
        pool.h)
