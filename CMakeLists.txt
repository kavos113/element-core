cmake_minimum_required(VERSION 3.29)
project(element CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(global_test_dir ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_subdirectory(${src_dir}/element)
set(lib_dir ${CMAKE_CURRENT_BINARY_DIR})

