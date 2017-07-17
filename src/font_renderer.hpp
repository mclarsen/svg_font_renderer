#ifndef FONT_RENDERER_HPP
#define FONT_RENDERER_HPP

#include <string>
#include <vector>

#include <image.hpp>


struct FontData;

class FontRenderer 
{
public:  
  FontRenderer(bool use_kerning);
  ~FontRenderer();
  Image* render_text(const std::string &text, const int size);
protected:
  void create_svg_xml(std::string &xml, 
                      const std::string &text,
                      const int size);

  void add_text_path(std::stringstream &ss, 
                     const std::string &character, 
                     const float scale, 
                     int offset);

  void add_svg_header(std::stringstream &ss, 
                      const std::string &text, 
                      std::vector<int> &offsets, 
                      const float scale);
  FontData *m_font_data;
  bool m_use_kerning; 
  FontRenderer();
};
#endif
