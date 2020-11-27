cmake_minimum_required(VERSION 3.16)
project(QuadTree)

set(CMAKE_CXX_STANDARD 17)

add_executable(QuadTree main.cpp)

set_target_properties(-Wl,--stack,4194304 -o QuadTree main.cpp)