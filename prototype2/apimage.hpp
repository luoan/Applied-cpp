#ifndef _apimage_h
#define _apimage_h


#include "ptr.hpp"
#include "apalloc.hpp"
#include "rgb.h"

#include <iostream>

template <class T, class E>
class apImage
{
public :
  apImage ();
  apImage (unsigned int width, unsigned int height);

  ~apImage () { }

  int width()  const { return width_; }
  int height() const { return height_; }

  const T* pixels () const { return pixels_.data(); }
  T*       pixels ()       { return pixels_.data(); }

  T    getPixel (int x, int y) const;
  void setPixel (int x, int y, T pixel);
  //apImage<T, E> thumbnail (unsigned int reduction) const;
  apImage<T, E> thumbnail (unsigned int reduction) const;
private :
  apAlloc<T> pixels_;
  int width_;
  int height_;
};

template <class T, class E>
std::ostream& operator<< (std::ostream& os, const apImage<T, E>& image)
{
  for (int hei = 0; hei != image.height(); ++hei) {
    for (int wid = 0; wid != image.width(); ++wid) {
      T tmp = image.getPixel (wid, hei);
      os << tmp << "    ";
    }
    os << std::endl;
  }
  return os;
}


template <class T, class E>
apImage<T, E>::apImage () : width_(0), height_(0) { }

template <class T, class E>
apImage<T, E>::apImage (unsigned int width, unsigned int height) : width_(width), height_(height) 
{
  pixels_ = apAlloc<T> (width_ * height_);
}

template <class T, class E>
T apImage<T, E>::getPixel (int x, int y) const 
{
  return pixels_[y * width_ + x];
}

template <class T, class E>
void apImage<T, E>::setPixel (int x, int y, T pixel)
{
  pixels_[y*width_ + x] = pixel;
}

template <class T, class E>
apImage<T, E> apImage<T, E>::thumbnail (unsigned int reduction) const 
{
  apImage<T, E> output (width()/ reduction, height()/ reduction);

  for (unsigned int ty = 0; ty < output.height(); ++ty) {
    for (unsigned int tx =0; tx < output.width(); ++tx) {
      
      E sum = 0;
      for (unsigned int y = 0; y < reduction; ++y) {
        for (unsigned int x = 0; x < reduction;++x) 
          sum += getPixel (tx * reduction + x, ty*reduction + y);
      }
      output.setPixel (tx, ty, sum / (reduction * reduction));
    }
  }
  return output;
}

#endif
