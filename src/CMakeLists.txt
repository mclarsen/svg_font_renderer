cmake_minimum_required(VERSION 3.0)

project(font_renderer VERSION "0.0.0")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(sources font_renderer.cpp)
set(headers font_renderer.hpp)
add_library(font_renderer SHARED
            ${sources} 
            ${headers}
            ) 
