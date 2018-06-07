cmake_minimum_required (VERSION 2.8)

project (Picture)

#add_library (image_shared SHARED image.cpp)
add_library (picture_shared SHARED picture.cpp image.cpp)

add_executable (picture main.cpp)
target_link_libraries (picture picture_shared)
#target_link_libraries (picture  image_shared picture_shared)
