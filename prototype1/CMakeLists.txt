cmake_minimum_required (VERSION 2.8)

project (Prototype1)

#include_directories (../../alloc/)
include_directories (/home/luoan/appliedcpp_program/alloc)
add_library (apimage apimage.cpp)

add_executable (prototype1 main.cpp)
target_link_libraries (prototype1 apimage)
