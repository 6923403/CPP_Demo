cmake_minimum_required(VERSION 3.17)
project(CPP_Demo)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CPP_Demo
        main.cpp
        logger.cpp
        logger.h)
