#include <font_renderer.hpp>
#include <font_parser.hpp>
FontRenderer::FontRenderer()
{
  m_font_data = fontParseFromFile("/Users/larsen30/research/svg_stuff/svg_font_renderer/src/fonts/Crimson-Roman.svg");

}

FontRenderer::~FontRenderer()
{
  delete m_font_data;
}

Image 
FontRenderer::render_text(const std::string &text, const int size)
{
   
  Image image;
  return image;
}


void 
FontRenderer::create_svg_xml(std::string &xml, 
                             const std::string &text,
                             const int size)
{

}
