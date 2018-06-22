cmake_minimum_required(VERSION 3.1)
project(simpleSTL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -DDEBUG")

set(SOURCE_FILES main.cpp list.h)
add_executable(simpleSTL ${SOURCE_FILES})

set(TREE_TEST tree/test.cpp)
add_executable(test_tree ${TREE_TEST})