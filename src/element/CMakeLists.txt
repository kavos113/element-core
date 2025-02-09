cmake_minimum_required(VERSION 3.29)
project(element CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(srcs_windows
        windows/winWindow.cpp
        geometry/Point.cpp
)

add_library(element ${srcs_windows})
target_include_directories(element PUBLIC ${include_dir}/element)