#include "gtest/gtest.h"
#include <font_renderer.hpp>

TEST(svg_font_renderer, render_test)
{
  FontRenderer renderer;
  Image image = renderer.render_text("test",100);
}
