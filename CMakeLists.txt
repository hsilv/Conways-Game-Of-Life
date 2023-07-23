cmake_minimum_required(VERSION 3.25)
project(Tarea2 VERSION 1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_library(framebuffer_lib STATIC src/framebuffer.cpp)

target_sources(framebuffer_lib PRIVATE src/render.cpp)

add_executable(Tarea2 src/main.cpp) 
target_link_libraries(Tarea2 ${SDL2_LIBRARIES} framebuffer_lib)
