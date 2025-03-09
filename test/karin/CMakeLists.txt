cmake_minimum_required(VERSION 3.29)
project(karin-test CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

macro(add_test api_name test_name)
    message(STATUS "Adding test for ${api_name} - ${test_name}")
    message(STATUS "Test sources: ${test_srcs_${test_name}}")
    message(STATUS "library: karin-${api_name}")
    add_executable(karin-${api_name}-${test_name}-test ${test_srcs_${test_name}})
    add_dependencies(karin-${api_name}-${test_name}-test karin-${api_name})
    target_link_libraries(karin-${api_name}-${test_name}-test PRIVATE gtest_main karin-${api_name})
    target_include_directories(karin-${api_name}-${test_name}-test PRIVATE ${include_dir})
    if (IS_SLOW_TEST)
        target_compile_definitions(karin-${api_name}-${test_name}-test PRIVATE SLOW_TEST)
    endif ()

    include(GoogleTest)
    gtest_discover_tests(karin-${api_name}-${test_name}-test)
endmacro()

set(test_srcs_windows
        windows/winWindowTest.cpp
        windows/winTextTest.cpp
        ../utils/WindowsGUITester.h
)

set(test_srcs_direct2d
        windows/direct2d/d2dFactoryTest.cpp
        windows/direct2d/d2dDeviceTest.cpp
        windows/direct2d/d2dWindowTest.cpp
        windows/direct2d/dxgiDeviceTest.cpp
        windows/direct2d/dwriteFactoryTest.cpp
)

set(test_srcs_geometry
        geometry/PointTest.cpp
        geometry/RectangleTest.cpp
        geometry/SizeTest.cpp
)

set(test_srcs_color color/ColorTest.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(IS_SLOW_TEST ON)

add_test(windows windows)
add_test(windows direct2d)
add_test(windows geometry)
add_test(windows color)