cmake_minimum_required(VERSION 3.16)
project(ieee754)

set(CMAKE_CXX_STANDARD 14)

add_executable(ieee754 main.cpp IEEE754.cpp IEEE754.h)