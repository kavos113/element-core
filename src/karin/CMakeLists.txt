cmake_minimum_required(VERSION 3.29)
project(karin CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(srcs_common
        geometry/Point.cpp
        geometry/Rectangle.cpp
        geometry/Size.cpp
        color/Color.cpp
)

set(headers_common
        ${include_dir}/karin/geometry/Point.h
        ${include_dir}/karin/geometry/Rectangle.h
        ${include_dir}/karin/geometry/Size.h
        ${include_dir}/karin/color/Color.h
        ${include_dir}/karin/font/Font.h
        ${include_dir}/karin/font/Paragraph.h
)

set(srcs_windows
        windows/winWindow.cpp
        windows/winText.cpp
        windows/direct2d/d2dWindow.cpp
        windows/direct2d/dwriteText.cpp
)

set(headers_windows
        ${include_dir}/karin/windows/winWindow.h
        ${include_dir}/karin/windows/winText.h
        ${include_dir}/karin/windows/direct2d/d2dFactory.h
        ${include_dir}/karin/windows/direct2d/d2dDevice.h
        ${include_dir}/karin/windows/direct2d/d2dWindow.h
        ${include_dir}/karin/windows/direct2d/dxgiDevice.h
        ${include_dir}/karin/windows/direct2d/dwriteFactory.h
        ${include_dir}/karin/windows/direct2d/dwriteText.h
)

set(srcs_x11
        x11/x11Window.cpp
)

set(headers_x11
        ${include_dir}/karin/x11/x11Window.h
)


if (WIN32)
    add_library(karin-windows ${srcs_windows} ${headers_windows} ${srcs_common} ${headers_common})
    target_include_directories(karin-windows PUBLIC ${include_dir}/karin)
endif ()

add_library(karin-x11 ${srcs_x11} ${headers_x11} ${srcs_common} ${headers_common})
target_include_directories(karin-x11 PUBLIC ${include_dir}/karin)
if (WIN32)
    target_include_directories(karin-x11 PUBLIC ${vcpkg_install_dir}/x64-windows/include)
endif ()


if (MSVC AND WIN32)
    target_link_libraries(karin-windows PRIVATE d2d1.lib)
    target_link_libraries(karin-windows PRIVATE dxgi.lib)
    target_link_libraries(karin-windows PRIVATE d3d11.lib)
    target_link_libraries(karin-windows PRIVATE dwrite.lib)
else ()
    if (UNIX)
        target_link_libraries(karin-x11 PRIVATE X11)
    endif ()
endif ()