#include "image.h"

#include <string.h>
#include <iostream>

apImage::apImage () : width_(0), height_(0), pixels_(0) { }

apImage::apImage (int width, int height) : width_(width), height_(height), pixels_(0) 
{
  init ();
}

apImage::apImage (const apImage& src) : width_(0), height_(0), pixels_(0)
{
  if (src.isValid()) {
    width_ = src.width();
    height_ = src.height();
    init ();
    memcpy (pixels_, src.pixels_, width_ * height_);
  }
}

apImage& apImage::operator= (const apImage& src)
{
  if (&src != this) {
    cleanup ();
    width_ = src.width_;
    height_ = src.height_;
    init ();
    memcpy (pixels_, src.pixels_, width_ * height_);
  }
  return *this;
}

apImage::~apImage ()
{
  cleanup ();
}

void apImage::setPixel (int width, int height, unsigned char pixel)
{
  if (width<0 || height<0 ||
      width>=width_ || height>=height_ ||
      !isValid())
    throw rangeError();
  unsigned char* p = pixels_ + height * width_ + width;
  *p = pixel;
}

unsigned char apImage::getPixel (int width, int height) const 
{
  if (width < 0 || height < 0 ||
      width >= width_ || height>=height_ ||
      !isValid())
    throw rangeError ();
  unsigned char* p = pixels_ + height*width_ + width;
  return *p;
}

void apImage::init ()
{
  if (width_ > 0 && height_ > 0)
    pixels_ = new unsigned char [width_ *  height_];
}

void apImage::cleanup ()
{
  delete [] pixels_;
  width_ = 0;
  height_ = 0;
  pixels_ = 0;
}

std::ostream& operator<< (std::ostream& os, const apImage& image) 
{
  for (int h = 0; h != image.height(); ++h) {
    for (int w = 0; w != image.width(); ++w)
      os << (int)image.getPixel(w, h) << " ";
    os << std::endl;
  }
  return os;
}
