cmake_minimum_required(VERSION 3.15)
project(functionmore)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(functionmore
        main.cpp
        test.cpp
        test.h)
