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

# test
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

file(GLOB_RECURSE test_files ${global_test_dir}/*.cpp)
foreach (test_file ${test_files})
    get_filename_component(test_name ${test_file} NAME_WE)
    get_filename_component(test_dir ${test_file} DIRECTORY)

    string(REPLACE ${global_test_dir} "" rel_dir ${test_dir})
    set(output_dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}${rel_dir})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})

    add_executable(${test_name} ${test_file})
    target_include_directories(${test_name} PRIVATE ${src_dir})
    target_link_libraries(${test_name} PRIVATE gtest_main)
    target_link_libraries(${test_name} PRIVATE element)

    include(GoogleTest)
    gtest_discover_tests(${test_name})

    set_target_properties(${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${output_dir}/${test_name}
    )
    message(STATUS "Test Created: ${test_name}")
endforeach ()