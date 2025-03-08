cmake_minimum_required(VERSION 3.29)
project(karin CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(srcs_windows
        windows/winWindow.cpp
        windows/winText.cpp
        geometry/Point.cpp
        geometry/Rectangle.cpp
        geometry/Size.cpp
        windows/direct2d/d2dWindow.cpp
        windows/direct2d/dwriteText.cpp
        color/Color.cpp
)

set(headers_windows
        ${include_dir}/karin/windows/winWindow.h
        ${include_dir}/karin/windows/winText.h
        ${include_dir}/karin/geometry/Point.h
        ${include_dir}/karin/geometry/Rectangle.h
        ${include_dir}/karin/geometry/Size.h
        ${include_dir}/karin/windows/direct2d/d2dFactory.h
        ${include_dir}/karin/windows/direct2d/d2dDevice.h
        ${include_dir}/karin/windows/direct2d/d2dWindow.h
        ${include_dir}/karin/windows/direct2d/dxgiDevice.h
        ${include_dir}/karin/windows/direct2d/dwriteFactory.h
        ${include_dir}/karin/windows/direct2d/dwriteText.h
        ${include_dir}/karin/color/Color.h
        ${include_dir}/karin/font/Font.h
        ${include_dir}/karin/font/Paragraph.h
)

add_library(karin ${srcs_windows} ${headers_windows})
target_include_directories(karin PUBLIC ${include_dir}/karin)

target_link_libraries(karin PRIVATE d2d1.lib)
target_link_libraries(karin PRIVATE dxgi.lib)
target_link_libraries(karin PRIVATE d3d11.lib)
target_link_libraries(karin PRIVATE dwrite.lib)