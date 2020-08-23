cmake_minimum_required(VERSION 3.15)
project(Tinyhttpd C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_executable(Tinyhttpd
        httpd.c)
