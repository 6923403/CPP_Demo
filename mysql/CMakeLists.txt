cmake_minimum_required(VERSION 3.16)
project(mysql)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 11)
add_executable(mysql main.cpp
        log/easylogging.cc
        sql/Connect_Sql.cpp
        thread_pool/Thread_Pool.hpp)

include_directories("/usr/include/mysql")
link_directories("usr/lib/x86_64-linux-gnu")
set(L_LIBS  mysqlclient pthread)
target_link_libraries(mysql ${L_LIBS})
