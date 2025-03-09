cmake_minimum_required(VERSION 3.29)
project(karin CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src/karin)
set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(test_dir ${CMAKE_CURRENT_SOURCE_DIR}/test/karin)
set(vcpkg_install_dir ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed)
add_subdirectory(${src_dir})
add_subdirectory(${test_dir})
set(lib_dir ${CMAKE_CURRENT_BINARY_DIR})
