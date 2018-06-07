cmake_minimum_required (VERSION 2.8)

project (PictureM)

add_executable (picturem main.cpp )
target_link_libraries (picturem image_shared)

add_library (image image.cpp)
add_library (image_shared SHARED image.cpp)


