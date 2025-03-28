cmake_minimum_required(VERSION 3.28)
project(sha1)

set(CMAKE_CXX_STANDARD 17)

add_executable(sha1 main.cpp
        sha1.cpp
        sha1.h)
