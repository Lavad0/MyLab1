cmake_minimum_required(VERSION 4.0)
project(ProjectForLab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProjectForLab1
        main.cpp
        tests.cpp
        Matrix/Matrix.cpp
        Matrix/Matrix.h)
