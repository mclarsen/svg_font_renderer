blt_add_executable(NAME svg_font_renderer_smoke
                   SOURCES svg_font_renderer_smoke.cpp
                   OUTPUT_DIR ${TEST_OUTPUT_DIRECTORY}
                   DEPENDS_ON gtest font_renderer)

blt_add_test( NAME svg_font_renderer_smoke 
              COMMAND svg_font_renderer_smoke)

blt_add_executable(NAME svg_font_renderer
                   SOURCES svg_font_renderer.cpp
                   OUTPUT_DIR ${TEST_OUTPUT_DIRECTORY}
                   DEPENDS_ON gtest font_renderer)

blt_add_test( NAME svg_font_renderer 
              COMMAND svg_font_renderer)
