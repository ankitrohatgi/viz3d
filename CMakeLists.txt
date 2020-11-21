cmake_minimum_required(VERSION 3.8)
project(imgui_opengl3)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED FATAL_ERROR)
pkg_search_module(GLFW REQUIRED glfw3 FATAL_ERROR)
set(IMGUI_SRC thirdparty/imgui/imgui.cpp
              thirdparty/imgui/imgui_draw.cpp
              thirdparty/imgui/imgui_widgets.cpp
              thirdparty/imgui/imgui_demo.cpp
              thirdparty/imgui/examples/imgui_impl_glfw.cpp
              thirdparty/imgui/examples/imgui_impl_opengl3.cpp)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GL3W)
include_directories(${OpenGL_INCLUDE_DIRS} thirdparty/gl3w thirdparty/imgui thirdparty/imgui/examples)
set(GL3W_SRC thirdparty/gl3w/GL/gl3w.c)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # MacOS
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_package(GLFW3 REQUIRED glfw3)
    include_directories(/usr/local/include)
    add_executable(imgui_opengl3 main.cpp ${GL3W_SRC} ${IMGUI_SRC})
    target_link_libraries(imgui_opengl3 ${OpenGL_LIBRARIES} dl ${GLFW_LIBRARIES} "-framework CoreFoundation")
    target_compile_options(imgui_opengl3 PRIVATE -Wno-deprecated-declarations -O3)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows") # Windows
    # unsupported
else(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # Ubuntu linux
    set(OpenGL_GL_PREFERENCE "GLVND")
    add_executable(imgui_opengl3 main.cpp ${GL3W_SRC} ${IMGUI_SRC})
    target_link_libraries(imgui_opengl3 ${OpenGL_LIBRARIES} GL GLU dl glfw)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # end if