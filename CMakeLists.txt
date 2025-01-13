cmake_minimum_required(VERSION 3.10)

project(vici)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    Q1.cpp
)

add_executable(Q1 ${SOURCES})
