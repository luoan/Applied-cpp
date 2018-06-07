#ifndef _rgb_h
#define _rgb_h


#include <iostream>

typedef unsigned char Pel8;
typedef unsigned int Pel32;

struct RGB 
{
  Pel8 red;
  Pel8 green;
  Pel8 blue;
  
  RGB (Pel8 b = 0) : red(b), green(b), blue(b) { }
  RGB (Pel8 r, Pel8 g, Pel8 b) : red(r), green(g), blue(b) { }
};

struct RGBPel32 
{
  Pel32 red;
  Pel32 green;
  Pel32 blue;
  RGBPel32 (Pel32 l = 0) : red(l), green(l), blue(l) { }
};

RGB& operator+= (RGB& s1, RGB& s2 );
RGBPel32& operator+= (RGBPel32&, const RGB& );
RGB operator/ (const RGBPel32&, int );
std::ostream& operator<< (std::ostream&, const RGB& );

#endif
