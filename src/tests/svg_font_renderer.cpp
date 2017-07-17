#include "gtest/gtest.h"
#include <font_renderer.hpp>

TEST(svg_font_renderer, render_test)
{
  FontRenderer renderer(false);
  Image *image = renderer.render_text("aAbBcCdDeEfFgGhHiIjJ0123456789",50);
  image->flip_vertical();
  image->save_png("normal.png");
  delete image;
}

TEST(svg_font_renderer, render_kerning_test)
{
  FontRenderer renderer(true);
  Image *image = renderer.render_text("aAbBcCdDeEfFgGhHiIjJ0123456789",50);
  image->flip_vertical();
  image->save_png("kerning.png");
  delete image;
}

TEST(svg_font_renderer, render_big_A_test)
{
  FontRenderer renderer(false);
  Image *image = renderer.render_text("A",1000);
  image->flip_vertical();
  image->save_png("big_A.png");
  delete image;
}
