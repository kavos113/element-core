cmake_minimum_required(VERSION 3.29)
project(element-test CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(test_srcs_windows
        windows/winWindowTest.cpp
        ../utils/WindowsGUITester.h
)

set(test_srcs_direct2d
        windows/direct2d/d2dFactoryTest.cpp
)

set(test_srcs_geometry
        geometry/PointTest.cpp
        geometry/RectangleTest.cpp
        geometry/SizeTest.cpp
)

set(test_names windows geometry direct2d)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

foreach (test_name IN LISTS test_names)
    add_executable(element-${test_name}-test ${test_srcs_${test_name}})
    add_dependencies(element-${test_name}-test element)
    target_link_libraries(element-${test_name}-test PRIVATE gtest_main element)
    target_include_directories(element-${test_name}-test PRIVATE ${include_dir})

    include(GoogleTest)
    gtest_discover_tests(element-${test_name}-test)
endforeach ()