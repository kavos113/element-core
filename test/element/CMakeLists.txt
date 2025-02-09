cmake_minimum_required(VERSION 3.29)
project(element-test CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(test_srcs
        windows/winWindowTest.cpp
        ../utils/WindowsGUITester.h
        geometry/PointTest.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(element-test ${test_srcs})
add_dependencies(element-test element)
target_link_libraries(element-test PRIVATE gtest_main element)
target_include_directories(element-test PRIVATE ${include_dir})

include(GoogleTest)
gtest_discover_tests(element-test)