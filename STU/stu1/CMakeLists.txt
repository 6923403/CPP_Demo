cmake_minimum_required(VERSION 3.15)
project(stu1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(stu1
        main.cpp
        Student.cpp
        Student.h)
