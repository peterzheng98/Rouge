cmake_minimum_required(VERSION 3.15)
project(Rouge)

set(CMAKE_CXX_STANDARD 14)

add_executable(Rouge main.cpp src/Rouge.cpp src/Rouge.h)
add_executable(UnitTest Test.cpp src/Rouge.cpp src/Rouge.h)