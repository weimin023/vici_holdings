cmake_minimum_required(VERSION 3.10)

project(vici)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Q1 Q1.cpp)
add_executable(Q2 Q2.cpp)
add_executable(Q3 Q3.cpp)
add_executable(Q4 test_threads.cpp)