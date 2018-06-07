cmake_minimum_required (VERSION 2.8)

project (Prototype2_template)

include_directories (/home/luoan/appliedcpp_program/alloc)
add_library (rgb rgb.cpp)

add_executable (prototype2 main.cpp)
target_link_libraries (prototype2 rgb)
