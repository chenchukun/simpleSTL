cmake_minimum_required(VERSION 3.5)
project(simpleSTL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCE_FILES main.cpp list.h)
add_executable(simpleSTL ${SOURCE_FILES})