# 版本设置
cmake_minimum_required(VERSION 3.10)
project(logging)
# 声明项目名称与语言
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 11)
# 构建hello
add_executable(logging main.cpp
        easylogging.cc)