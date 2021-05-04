cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
# 声明项目名称与语言
project(demo LANGUAGES CXX)
# 构建hello
add_executable(add o_add.cpp)
