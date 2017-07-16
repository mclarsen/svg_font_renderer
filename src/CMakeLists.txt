cmake_minimum_required(VERSION 3.0)

project(font_renderer VERSION "0.0.0")

include(blt/SetupBLT.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)

set(sources font_renderer.cpp)
set(headers font_renderer.hpp)

blt_add_library(
  NAME font_renderer SHARED
  SOURCES ${sources} 
  HEADERS ${headers}
) 
