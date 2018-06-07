cmake_minimum_required (VERSION 2.8)

project (Prototype3)

include_directories (../alloc)

add_library (apstorage apstorage.cpp)

add_executable (prototype3 main.cpp)
target_link_libraries (prototype3 apstorage)
