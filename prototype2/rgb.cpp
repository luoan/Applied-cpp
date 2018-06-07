#include "rgb.h"
#include <iostream>

RGB& operator+= (RGB& s1, RGB& s2)
{
  s1.red += s2.red;
  s1.green += s2.green;
  s1.blue += s2.blue;
  return s1;
}

RGBPel32& operator+= (RGBPel32& s1, const RGB& s2)
{
  s1.red += s2.red;
  s1.green += s2.green;
  s1.blue += s2.blue;
  return s1;
}

RGB operator/ (const RGBPel32& s1, int den)
{
  RGB div;
  div.red = s1.red / den;
  div.green = s1.green / den;
  div.blue = s1.blue / den;
  return div;
}

std::ostream& operator<< (std::ostream& os, const RGB& s)
{
  os << (int)s.red << " " << (int)s.green << " "
    << (int)s.blue;
  return os;
}
