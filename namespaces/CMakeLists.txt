cmake_minimum_required(VERSION 3.15)
project(namespaces)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(namespaces
        main.cpp
        test.cpp
        test.h)
