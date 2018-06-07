cmake_minimum_required (VERSION 2.8)

project (Picture)

add_library (pic_shared SHARED grade.cpp core.cpp pic.cpp student_info.hpp)
#add_library (pic_shared SHARED pic.cpp student_info.hpp) #wrong

add_executable (picture main.cpp)
target_link_libraries (picture pic_shared)
