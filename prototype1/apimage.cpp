#include "apimage.h"

apImage8::apImage8  () : width_(0), height_(0) { }

apImage8::apImage8 (int width, int height) :
    width_ (width), height_(height)
{ 
  pixels_ = apAlloc<Pel8>(width_ * height_);
}

apImage8::~apImage8 () { }

Pel8 apImage8::getPixel (int x, int y) const
{
  return pixels_[y*width_ + x];
}

void apImage8::setPixel (int x, int y, Pel8 pixel)
{
  pixels_[y*width_ + x] = pixel;
}

apImage8 apImage8::thumbnail (unsigned int reduction) const 
{
  apImage8 output (width() / reduction, height() / reduction);

  for (unsigned int ty = 0; ty < output.height(); ty++) {
    for (unsigned int tx=0; tx < output.width(); tx++) {
      unsigned int sum = 0;
      for (unsigned int y = 0; y < reduction; ++y) {
        for (unsigned int x=0; x<reduction; ++x) {
          sum += getPixel (tx*reduction + x, ty* reduction+y);
        }
      }
      output.setPixel (tx, ty, sum / (reduction*reduction));
    }
  }
  return output;
}

std::ostream& operator<< (std::ostream& os, const apImage8& image)
{
  std::cout << "in operator<<" << std::endl;
  for (int hei = 0; hei != image.height(); ++hei) {
    for (int wid = 0; wid != image.width(); ++wid) {
     // std::cout << "getPixel width heith" << wid << " " << hei <<  " "  
     //   <<  (int)image.getPixel(wid, hei) << std::endl;
      os << (int)image.getPixel (wid, hei) << " ";
    }
    std::cout << std::endl;
  }
  return os;
}

/*
 *Pel32
 * */
apImage32::apImage32 () : width_(0), height_(0) { }

apImage32::apImage32 (int width, int height) :
    width_(width), height_(height)
{
  pixels_ = apAlloc<Pel32>(width_ * height_);
}

apImage32::~apImage32 () { }

Pel32 apImage32::getPixel (int x, int y) const 
{
  return pixels_[y*width_ + x];
}

void apImage32::setPixel (int x, int y, Pel32 pixel)
{
  pixels_[y*width_ + x] = pixel;
}

apImage32 apImage32::thumbnail (unsigned int reduction) const 
{
  apImage32 output (width() / reduction, height()/ reduction);

  for (unsigned int ty = 0; ty < output.height(); ++ty) {
    for (unsigned int tx = 0; tx < output.width(); ++tx) {
      unsigned long sum = 0;
      for (unsigned int y = 0; y < reduction; ++y) {
        for (unsigned int x = 0; x < reduction; ++x) 
          sum += getPixel (tx*reduction + x, ty*reduction+y);
      }
      output.setPixel (tx, ty, sum / (reduction * reduction));
    }
  }
  return output;
}

std::ostream& operator<< (std::ostream& os, const apImage32& image)
{
  for (int hei = 0; hei != image.height(); ++hei) {
    for (int wid = 0; wid != image.width(); ++wid)
      os << (int)image.getPixel(wid, hei) << " ";
    std::cout << std::endl;
  }
  return os;
}
