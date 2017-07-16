#include <image.hpp>
#include <third_party_builtin/lodepng/lodepng.h>
#include <assert.h>
#include <iostream>

Image::Image()
  : m_width(0),
    m_height(0)
{

}
Image::~Image()
{

}

void 
Image::flip_vertical()
{
  std::vector<unsigned char> tmp(m_width * m_height * 4);
  for (int y = 0; y < m_height; ++y)
  {
    memcpy(&(tmp[y*m_width*4]),
           &(m_buffer[(m_height-y-1)*m_width*4]),
           m_width*4);
  }
  m_buffer.swap(tmp);
}

void 
Image::save_png(const std::string &file_name) const
{
  unsigned char *encoded_buffer = NULL;
  size_t buffer_size;
  unsigned error = lodepng_encode_memory(&encoded_buffer,
                                         &buffer_size,
                                         &m_buffer[0],
                                         m_width,
                                         m_height,
                                         LCT_RGBA, // these settings match those for 
                                         8);       // lodepng_encode32_file
  if(error)
  {
    std::cerr<<"Error saving PNG buffer to file: " << file_name<<"\n";
    if(encoded_buffer)
    {
      free(encoded_buffer);
    }
    return;
  }
  
  error = lodepng_save_file(encoded_buffer,
                            buffer_size,
                            file_name.c_str());

  if(error)
  {
    std::cerr<<"Error saving PNG buffer to file: " << file_name<<"\n";
  }

  if(encoded_buffer)
  {
    free(encoded_buffer);
  }
}

void 
Image::resize(const int &width, const int &height)
{
  assert(width > 0);
  assert(height > 0);

  int size = width * height * 4;
  m_buffer.resize(size);
  m_width = width;
  m_height = height;
}
int 
Image::get_width() const
{
  return m_width;
}

int 
Image::get_height() const
{
  return m_height;
}

const unsigned char * 
Image::get_buffer() const
{
  assert(m_width != 0);
  assert(m_height != 0);
  return &m_buffer[0];
}
