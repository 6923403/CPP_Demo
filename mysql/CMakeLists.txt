cmake_minimum_required(VERSION 3.16)
project(server)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 11)
add_executable(server main.cpp
        sql/Connect_Sql.cpp)

include_directories("/usr/include/mysql")
link_directories("usr/lib/x86_64-linux-gnu")
set(L_LIBS  mysqlclient pthread)
target_link_libraries(server ${L_LIBS})
