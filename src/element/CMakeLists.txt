cmake_minimum_required(VERSION 3.29)
project(element CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(srcs_windows
        windows/winWindow.cpp
        windows/winText.cpp
        geometry/Point.cpp
        geometry/Rectangle.cpp
        geometry/Size.cpp
        windows/direct2d/d2dWindow.cpp
        windows/direct2d/d2dWindow.cpp
        color/Color.cpp
)

set(headers_windows
        ${include_dir}/element/windows/winWindow.h
        ${include_dir}/element/windows/winText.h
        ${include_dir}/element/geometry/Point.h
        ${include_dir}/element/geometry/Rectangle.h
        ${include_dir}/element/geometry/Size.h
        ${include_dir}/element/windows/direct2d/d2dFactory.h
        ${include_dir}/element/windows/direct2d/d2dDevice.h
        ${include_dir}/element/windows/direct2d/d2dWindow.h
        ${include_dir}/element/windows/direct2d/d2dWindow.h
        ${include_dir}/element/windows/direct2d/dxgiDevice.h
        ${include_dir}/element/color/Color.h
)

add_library(element ${srcs_windows} ${headers_windows})
target_include_directories(element PUBLIC ${include_dir}/element)

target_link_libraries(element PRIVATE d2d1.lib)
target_link_libraries(element PRIVATE dxgi.lib)
target_link_libraries(element PRIVATE d3d11.lib)