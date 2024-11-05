cmake_minimum_required(VERSION 3.29)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib)

add_subdirectory(core)
add_subdirectory(windows)
add_library(element SHARED element.cpp)
target_link_libraries(element PRIVATE core windows)