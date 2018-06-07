#ifndef _apimage_h
#define _apimage_h


#include "apalloc.hpp"
#include <iostream>

typedef unsigned char Pel8;

class apImage8
{
public :
  apImage8 ();
  apImage8 (int width, int height);

  virtual ~apImage8 ();

  int width () const { return width_; }
  int height () const { return height_; }

  const Pel8* pixels () const { return pixels_.data(); }
  Pel8*       pixels ()  { return pixels_.data(); }

  Pel8 getPixel (int x, int y) const;
  void setPixel (int x, int y, Pel8 pixel);

  virtual apImage8 thumbnail (unsigned int reduction) const;
protected :
  apAlloc<Pel8> pixels_;
  int width_;
  int height_;
};

typedef unsigned int Pel32;

class apImage32 
{
public :
  apImage32 ();
  apImage32 (int width, int height);

  virtual ~apImage32 ();

  int width () const { return width_; }
  int height() const { return height_; }

  const Pel32* pixels () const { return pixels_.data(); }
  Pel32*       pixels ()  { return pixels_.data(); }

  Pel32 getPixel (int x, int y) const;
  void setPixel (int x, int y, Pel32 pixel);

  virtual apImage32 thumbnail (unsigned int reduction) const;
protected :
  apAlloc<Pel32> pixels_;
  int width_;
  int height_;
};

std::ostream& operator<< (std::ostream&, const apImage8& );
std::ostream& operator<< (std::ostream&, const apImage32& );

#endif
