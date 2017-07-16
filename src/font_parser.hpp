#ifndef FONT_PARSER_HPP
#define FONT_PARSER_HPP

#include <string>
#include <map>
#include <vector>
#include <sstream>

#define NANOSVG_IMPLEMENTATION
#include <third_party_builtin/nanosvg.h>
#include <iostream>

struct FontAttributes
{
  //https://www.w3.org/TR/SVG11/fonts.html#FontFaceElement
  std::string m_font_family;
  std::string m_font_weight;
  std::string m_font_stretch;
  std::string m_units_per_em;
  std::string m_panose_1;
  std::string m_ascent;
  std::string m_descent;
  std::string m_x_height;
  std::string m_cap_height;
  std::string m_bbox;
  std::string m_underline_thickness;
  std::string m_underline_position;
  std::string m_unicode_range;
};

struct CharacterData
{
  std::string m_path;    // "d"
  std::string m_name;    // ex. "uni2079", "space", "a", "B"
  std::string m_unicode; // ex "&#x2032;" 
  int m_advance;         // how much to advance the "cursor" after char
};

struct KerningAttr 
{
  std::string m_first;
  std::string m_second;
  int m_offset;
};

struct FontData
{
  std::map<std::string, CharacterData> m_char_data;
  std::map<std::string, std::string>   m_name_to_unicode;
  std::map<std::string, KerningAttr >  m_kerns;
  FontAttributes m_atts;
};

std::vector<std::string> 
&split(const std::string &s, char delim, std::vector<std::string> &elems)
{   
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim))
  {   
     elems.push_back(item);
  }
  return elems;
}
 
std::vector<std::string> 
split(const std::string &s, char delim)
{   
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

std::string 
trim(const std::string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//
// The kerning data has a .sc suffix that we need to strip
//
void 
strip_sc(std::string &name)
{
  std::vector<std::string> tokens = split(name, '.');
  if(tokens.size() > 1)
  {
    name = tokens[0];
  }
  else 
  {
    std::cerr<<"Warning: no .sc suffix\n";
  }
}


static void font__parseGlyph(NSVGparser* p, const char** attr)
{
  FontData *font = (FontData*) p->font_data;
  CharacterData character;
  int att_count = 0;
	for (int i = 0; attr[i]; i += 2) 
  {
		if (strcmp(attr[i], "d") == 0) 
    {
      character.m_path = std::string(attr[i+1]); 
      att_count++;
		} 
    else if (strcmp(attr[i], "glyph-name") == 0) 
    {
      character.m_name = std::string(attr[i+1]); 
      att_count++;
		} 
    else if (strcmp(attr[i], "unicode") == 0) 
    {
      character.m_unicode = std::string(attr[i+1]); 
      att_count++;
		} 
    else if (strcmp(attr[i], "horiz-adv-x") == 0) 
    {
      character.m_advance = std::stoi(attr[i+1]); 
      att_count++;
		} 
  }
  //
  // only add this if its complete
  //
  if(att_count == 4)
  {
    font->m_char_data[character.m_unicode] = character;
    font->m_name_to_unicode[character.m_name] = character.m_unicode;
    std::cout<<"adding char "<<character.m_name<<"\n";
  } 
}

static void font__parseKern(NSVGparser* p, const char** attr)
{
  FontData *font = (FontData*) p->font_data;
  KerningAttr kern;
  int att_count = 0;
	for (int i = 0; attr[i]; i += 2) 
  {
		if (strcmp(attr[i], "g1") == 0) 
    {
      kern.m_first = std::string(attr[i+1]); 
      att_count++;
		} 
    else if (strcmp(attr[i], "g2") == 0) 
    {
      kern.m_second = std::string(attr[i+1]); 
      att_count++;
		} 
    else if (strcmp(attr[i], "k") == 0) 
    {
      kern.m_offset = std::stoi(attr[i+1]); 
      att_count++;
		} 
  }
  //
  // only add this if its complete
  //
  if(att_count == 3)
  {
    font->m_kerns[kern.m_first] = kern;

    std::cout<<"adding kern "<<kern.m_first<<"\n";
  } 
}

static void font__parseFontFace(NSVGparser* p, const char** attr)
{
  FontData *font = (FontData*) p->font_data;
  int att_count = 0;
  FontAttributes &atts = font->m_atts;
	for (int i = 0; attr[i]; i += 2) 
  {
		if (strcmp(attr[i], "font-family") == 0) 
    {
      atts.m_font_family = attr[i+1];
		} 
    else if (strcmp(attr[i], "font-weight") == 0) 
    {
      atts.m_font_weight = attr[i+1];
		} 
    else if (strcmp(attr[i], "font-stretch") == 0) 
    {
      atts.m_font_stretch = attr[i+1];
		} 
    else if (strcmp(attr[i], "units-per-em") == 0) 
    {
      atts.m_units_per_em = attr[i+1];
		} 
    else if (strcmp(attr[i], "panose-1") == 0) 
    {
      atts.m_panose_1 = attr[i+1];
		} 
    else if (strcmp(attr[i], "ascent") == 0) 
    {
      atts.m_ascent = attr[i+1];
		} 
    else if (strcmp(attr[i], "descent") == 0) 
    {
      atts.m_descent = attr[i+1];
		} 
    else if (strcmp(attr[i], "x-height") == 0) 
    {
      atts.m_x_height = attr[i+1];
		} 
    else if (strcmp(attr[i], "cap-height") == 0) 
    {
      atts.m_cap_height = attr[i+1];
		} 
    else if (strcmp(attr[i], "bbox") == 0) 
    {
      atts.m_bbox = attr[i+1];
		} 
    else if (strcmp(attr[i], "underline-thickness") == 0) 
    {
      atts.m_underline_thickness = attr[i+1];
		} 
    else if (strcmp(attr[i], "underline-position") == 0) 
    {
      atts.m_underline_position = attr[i+1];
		} 
    else if (strcmp(attr[i], "unicode-range") == 0) 
    {
      atts.m_unicode_range = attr[i+1];
		} 
  }
   
}
static void font__startElement(void* ud, const char* el, const char** attr)
{
	NSVGparser* p = (NSVGparser*)ud;

	/*if (p->defsFlag) {
		// Skip everything but gradients in defs
		if (strcmp(el, "linearGradient") == 0) {
			nsvg__parseGradient(p, attr, NSVG_PAINT_LINEAR_GRADIENT);
		} else if (strcmp(el, "radialGradient") == 0) {
			nsvg__parseGradient(p, attr, NSVG_PAINT_RADIAL_GRADIENT);
		} else if (strcmp(el, "stop") == 0) {
			nsvg__parseGradientStop(p, attr);
		}
		return;
	}*/
  FontData *font = (FontData*) p->font_data;
  std::cout<<"element "<<el<<"\n";
	if (strcmp(el, "g") == 0) 
  {
		nsvg__pushAttr(p);
		nsvg__parseAttribs(p, attr);
	} 
  else if (strcmp(el, "path") == 0) 
  {
		if (p->pathFlag)	// Do not allow nested paths.
			return;
		nsvg__pushAttr(p);
		nsvg__parsePath(p, attr);
		nsvg__popAttr(p);
	} 
  else if (strcmp(el, "glyph") == 0) 
  {
		nsvg__pushAttr(p);
		font__parseGlyph(p, attr);
		nsvg__popAttr(p);
	} 
  else if (strcmp(el, "hkern") == 0) 
  {
		nsvg__pushAttr(p);
		font__parseKern(p, attr);
		nsvg__popAttr(p);
	} 
  else if (strcmp(el, "font-face") == 0) 
  {
		nsvg__pushAttr(p);
		font__parseFontFace(p, attr);
		nsvg__popAttr(p);
	} 
}

int font__parseXML(char* input,
                   void (*startelCb)(void* ud, const char* el, const char** attr),
                   void (*endelCb)(void* ud, const char* el),
                   void (*contentCb)(void* ud, const char* s),
                   void* ud)
{
	char* s = input;
	char* mark = s;
	int state = NSVG_XML_CONTENT;
	while (*s) {
		if (*s == '<' && state == NSVG_XML_CONTENT) {
			// Start of a tag
			*s++ = '\0';
			nsvg__parseContent(mark, contentCb, ud);
			mark = s;
			state = NSVG_XML_TAG;
		} else if (*s == '>' && state == NSVG_XML_TAG) {
			// Start of a content or new tag.
			*s++ = '\0';
			nsvg__parseElement(mark, startelCb, endelCb, ud);
			mark = s;
			state = NSVG_XML_CONTENT;
		} else {
			s++;
		}
	}

	return 1;
}
FontData* fontParse(char* input)

{
	NSVGparser* p;
	NSVGimage* ret = 0;

	p = nsvg__createParser();
	if (p == NULL) {
		return NULL;
	}
  FontData *font = new FontData();
  p->font_data = font;
	font__parseXML(input, 
                 font__startElement, 
                 nsvg__endElement, 
                 nsvg__content, 
                 p);


	//ret = p->image;
	//p->image = NULL;

	nsvg__deleteParser(p);

	//return ret;
  return NULL;
}

FontData* fontParseFromFile(const char* filename)
{
	FILE* fp = NULL;
	size_t size;
	char* data = NULL;
	FontData* font= NULL;
  bool error = false;
  while(true)
  {
    fp = fopen(filename, "rb");
    if (!fp)
    {
      error = true;
      break;
    }
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    data = (char*)malloc(size+1);
    if (data == NULL) 
    {
      error = true;
      break;
    }
    if (fread(data, 1, size, fp) != size)
    {
      error = true;
      break;
    }
    data[size] = '\0';	// Must be null terminated.
    fclose(fp);
    font = fontParse(data);
    free(data);
    break;
  }

  if(error)
  {
    if (fp) fclose(fp);
    if (data) free(data);
    if (font) delete font;
    return NULL;
  }
	return font;
}

#endif
