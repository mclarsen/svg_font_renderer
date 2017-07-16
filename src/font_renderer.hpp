#ifndef FONT_RENDERER_HPP
#define FONT_RENDERER_HPP

#include<string>

struct Image
{
  unsigned char *m_buffer;
  int m_width;
  int m_height;
};

struct FontData;

class FontRenderer 
{
public:  
  FontRenderer();
  ~FontRenderer();
  Image render_text(const std::string &text, const int size);
protected:
  void create_svg_xml(std::string &xml, 
                      const std::string &text,
                      const int size);

  FontData *m_font_data;
};
#endif
