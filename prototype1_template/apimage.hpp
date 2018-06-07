#ifndef _apimage_h
#define _apimage_h


//#include "/home/luoan/appliedcpp_program/alloc/apalloc.hpp"
#include "apalloc.hpp"
#include <iostream>

typedef unsigned char Pel8;
typedef unsigned int Pel32;


template <class T>
class apImage 
{
public :
  apImage ();
  apImage (int width, int height);
  
  virtual ~apImage ();

  int width() const { return width_; }
  int height() const { return height_;}

  const T* pixels () const { return pixels_.data(); }
  T* pixels () { return pixels_.data(); }

  T getPixel (int x, int y) const;
  void setPixel (int x, int y, T pixel);
  virtual apImage thumbnail (unsigned int reduction) const;
private :
  apAlloc<T> pixels_;
  int width_;
  int height_;
};

template <class T>
std::ostream& operator<< (std::ostream& os, const apImage<T>& image)
{
  for (int hei = 0; hei != image.height(); ++hei) {
    for (int wid = 0; wid != image.width(); ++wid) 
      os << (int)image.getPixel (wid, hei) <<  " ";
    os << std::endl;
  }

  return os;
}

template <class T>
apImage<T>::apImage () : width_(0), height_(0) { }

template <class T>
apImage<T>::apImage (int width, int height) : width_(width), height_(height)
{  pixels_ = apAlloc<T>(width_ * height_); }

template <class T>
apImage<T>::~apImage () { }

template <class T>
T apImage<T>::getPixel (int x, int y) const 
{
  return pixels_[y * width_ + x];
}

template <class T>
void apImage<T>::setPixel (int x, int y, T pixel) 
{
  pixels_[y*width_ + x] = pixel;
}

template <class T>
apImage<T> apImage<T>::thumbnail (unsigned int reduction) const 
{
  apImage<T> output (width()/reduction, height()/reduction);

  for (unsigned int ty=0; ty < output.height(); ty++) {
    for (unsigned int tx =0; tx < output.width(); tx++) {
      unsigned long long sum = 0;
      for (unsigned int y =0; y < reduction; ++y) {
        for (unsigned int x = 0; x < reduction; ++x)
          sum += getPixel(tx*reduction + x, ty*reduction + y);
      }
    }
  }

  return output;
}

#endif
