cmake_minimum_required(VERSION 3.0)

project(font_renderer VERSION "0.0.0")

include(blt/SetupBLT.cmake)

configure_file(font_renderer_config.h.in 
               ${CMAKE_BINARY_DIR}/config/font_renderer_config.h
               @ONLY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/config)

set(sources font_renderer.cpp
            image.cpp
            third_party_builtin/lodepng/lodepng.cpp
   )
set(headers font_renderer.hpp
            image.hpp
            third_party_builtin/lodepng/lodepng.h
   )

blt_add_library(
  NAME font_renderer SHARED
  SOURCES ${sources} 
  HEADERS ${headers}
) 

add_subdirectory(tests)

file(COPY fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
