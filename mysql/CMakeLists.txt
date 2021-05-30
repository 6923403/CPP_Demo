cmake_minimum_required(VERSION 3.16)
project(mysql)

set(CMAKE_CXX_STANDARD 11)

target_link_libraries(mysql mysqlclient)

add_executable(server main.cpp
        sql/Connect_Sql.cpp)