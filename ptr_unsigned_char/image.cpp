#include "image.h"

#include <string.h>
#include <iostream>

apImage::apImage () : width_(0), height_(0)/*, pixels_(0)*/ { }

apImage::apImage (int width, int height) : width_(width), height_(height)/*, pixels_(0) */
{ 
  //init ();
  if (width_ > 0 && height > 0) 
    pixels_ = new unsigned char [width_ * height_];
}


void apImage::show () const 
{
  for (int hei=0; hei < height_; ++hei) {
    for (int wid=0; wid < width_; ++wid) 
      std::cout << (int)getPixel(wid, hei) << " ";
    
    std::cout << std::endl;
  }
}

void apImage::setPixel (int x, int y, unsigned char pixel)
{
  if (x < 0 || y < 0 ||
      x >= width_ || y >= height_ ||
      !isValid())
    throw rangeError ();
  
  pixels_.make_unique(width_ * height_);
  //pixels_.make_unique(); //not right
  unsigned char* p = pixels_; //+ y*width_ + x;
  p += y*width_ + x;
  *p = pixel;
}

unsigned char apImage::getPixel (int x, int y) const 
{
  if (x < 0 || y < 0 ||
      x >= width_ || y >= height_ ||
      !isValid())
    throw rangeError ();

  //unsigned char* p = pixels_ + y*width_ + x;
  // not work!!!!  maybe define operator+?????
  unsigned char* p = pixels_;//.get();
  p += y*width_ + x;
  return *p;
}

template <>
unsigned char* clone(const unsigned char* up, int length)
{
  unsigned char* p = new unsigned char[length];
  memcpy(p, up, length);
  return p;
}

/*
 * not usefull
 * since Ptr p point to unsigned char not apImage !!!!!!!
 *
unsigned char* apImage::clone() const 
{
  unsigned char* up = new unsigned char [width_ * height_];
  memcpy(up, pixels_, width_ * height_);
  // pixles_ here will call 
  // Ptr operatorT*()
  return up;
}*/
/*
apImage::apImage (const apImage& src) : width_(0), height_(0)
{
  if (src.isValid()) {
    width_ = src.width();
    height_ = src.height();
    init ();
    memcpy(pixels_, src.pixels_, width_ * height_);
  }
}*/

/*
apImage& apImage::operator= (const apImage& src) 
{
  if (&src != this) {
    cleanup();
  }
}
*/
/*
void apImage::init () 
{
  if (width_ >0 && height_ > 0)
    pixles_ = new unsigned char [width_ * height_];
}*/

/*
void apImage::cleanup ()
{
  width_ = 0;
  height_ = 0;
  // ptr will handle pixels_ 
}*/



