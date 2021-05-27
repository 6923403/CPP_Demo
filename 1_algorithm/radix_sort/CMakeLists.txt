# 版本设置
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
# 声明项目名称与语言
project(CPP_Test LANGUAGES CXX)
add_definitions(-std=c++11)
# 构建hello
add_executable(radix radix.cpp)