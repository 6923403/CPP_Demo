cmake_minimum_required(VERSION 3.15)
project(_workers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(_workers
    Commpany.cpp
    Commpany.h
    main.cpp
    WorkManger.cpp
    WorkManger.h CpManger.cpp CpManger.h)
