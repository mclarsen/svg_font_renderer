#ifndef FONT_RENDERER_IMAGE_HPP
#define FONT_RENDERER_IMAGE_HPP

#include <vector>
#include <string>

class Image
{
protected:
  std::vector<unsigned char> m_buffer;
  int m_width;
  int m_height;
public:
  Image();
  ~Image();
  void save_png(const std::string &file_name) const;
  void resize(const int &width, const int &height);
  int get_width() const;
  int get_height() const;
  void flip_vertical();
  const unsigned char * get_buffer() const;
  friend class FontRenderer;
};

#endif
