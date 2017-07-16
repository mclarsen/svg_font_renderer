#include <font_renderer.hpp>
#include <font_parser.hpp>

#include <limits>
#include <sstream>

FontRenderer::FontRenderer()
{
  m_font_data = fontParseFromFile("/Users/larsen30/research/svg_stuff/svg_font_renderer/src/fonts/Crimson-Roman.svg");
}

FontRenderer::~FontRenderer()
{
  delete m_font_data;
}

void find_total_bbox(float bbox[4], NSVGimage *image)
{
  bbox[0] = std::numeric_limits<float>::max();
  bbox[1] = std::numeric_limits<float>::max();
  bbox[2] = std::numeric_limits<float>::lowest();
  bbox[3] = std::numeric_limits<float>::lowest();
    
  NSVGshape *shape_p = image->shapes;
  while(shape_p != NULL)
  {
    bbox[0] = std::min(bbox[0], shape_p->bounds[0]);
    bbox[1] = std::min(bbox[1], shape_p->bounds[1]);
    bbox[2] = std::max(bbox[2], shape_p->bounds[2]);
    bbox[3] = std::max(bbox[3], shape_p->bounds[3]);
  }
  std::cout<<"BBOX "<<bbox[0]<<" "<<bbox[1]<<" "<<bbox[2]<<" "<<bbox[3]<<"\n";
}

Image 
FontRenderer::render_text(const std::string &text, const int size)
{
  std::string xml;
  create_svg_xml(xml, text, size);
  float dpi = 96; 
  const char *units = "px";
  char *input = const_cast<char*>(xml.c_str());
  NSVGimage *nsvg_image = nsvgParse(input, units, dpi);
  float bbox[4];  
  find_total_bbox(bbox, nsvg_image);
  std::cout<<"**********\n";
  Image image;
  return image;
}

void 
FontRenderer::add_svg_header(std::stringstream &ss, 
                             const std::string &text, 
                             std::vector<int> &offsets, 
                             const float scale,
                             const int width,
                             const int height)
{
  const int num_chars = text.length();
  ss<<"<svg version\"1.1\" id=\"Layer_1\" x=\"0px\" y=\"0px\" ";
  ss<<"width=\""<<width<<"px\" height=\""<<height<<"px\" ";
  ss<<"viewbox=\"0 0 "<<width<<" "<<height<<"\" ";
  ss<<"enable-background=\"new 0 0 "<<width<<" "<<height<<"\" ";
  ss<<"xml:space=\"preserve\"> \n";
  
  for(int i = 0; i < num_chars; ++i)
  {
    std::stringstream chr_ss;
    chr_ss<<text[i];
    add_text_path(ss, chr_ss.str(), scale, offsets[i]);
  }

  ss<<"/svg>";
}

void 
FontRenderer::add_text_path(std::stringstream &ss, 
                            const std::string &character, 
                            const float scale, 
                            int offset)  
{
  if(!m_font_data->has_char(character))
  {
    return;
  }

  ss<<"<path ";
  ss<<"d=\""<<m_font_data->m_char_data[character].m_path<<"\" ";
  ss<<"transform=\"translate("<<offset*scale<<" 0) ";
  ss<<"scale("<<scale<<" "<<scale<<")\" ";
  ss<<"/>\n";
}

void 
FontRenderer::create_svg_xml(std::string &xml, 
                             const std::string &text,
                             const int size)
{
  std::cout<<"creating xml\n";

  std::cout<<m_font_data->m_atts.m_units_per_em<<"\n";;

  float units_per_em = std::stof(m_font_data->m_atts.m_units_per_em);
  float scaling_factor = (float(size))/(units_per_em); 
  size_t num_chars = text.length();
  std::cout<<"Size "<<num_chars<<"\n";
  std::vector<int> offsets(num_chars);
  offsets[0] = 0;
  float tot_width = 0; 
  for(int i = 0; i < num_chars; ++i)
  {
    std::stringstream ss;
    ss<<text[i - 1];
    offsets[i] = offsets[i -1] + m_font_data->m_char_data[ss.str()].m_advance;
    std::cout<<"offset "<<i<<" "<<offsets[i]<<"\n";
    if(i == num_chars - 1)
    {
      ss.str("");
      ss<<text[i];
      tot_width  = offsets[i] + m_font_data->m_char_data[ss.str()].m_advance;
    }
  }
  int width = tot_width * scaling_factor;
  std::stringstream ss; 
  add_svg_header(ss, text, offsets, scaling_factor, width, size);
  std::cout<<"Actual Dims w: "<<width<<" h: "<<size<<"\n"; 
  //std::cout<<ss.str()<<"\n";
  xml = ss.str();
}
