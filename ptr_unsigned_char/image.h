#ifndef _IMAGE_H_
#define _IMAGE_H_


#include "ptr.hpp"

class apImage 
{
  // template <> friend unsigned char* clone(unsigned char*, int ); // error do not know why
public :
  apImage ();
  apImage (int width, int height);

  // because we have Ptr to handle the pointer the default 
  // copy constructor and oprator= and ~ is ok
  //apImage (const apImage& );
  //apImage& operator= (const apImage& );
  //~apImage ();
  ~apImage() { std::cout << "widht_ " << width_ << "~apImage "; }
  

  int width () const { return width_; }
  int height() const { return height_; }

  void setPixel (int width, int height, unsigned char pixel);
  unsigned char getPixel (int width, int height) const;

  bool isValid () const { return pixels_ != 0; }

  void show () const;
  class rangeError { };
//protected :
//  unsigned char* clone() const;
//  since Ptr p is not point to apImage 
//  this is useless !!!!! 
//  Ptr p point to unsigned char
//private :
  //void init    ();
  //void cleanup ();
  int width_;
  int height_;
  //unsigned char* pixles_;
  Ptr<unsigned char> pixels_;
};


//#include <string.h>

template <>
unsigned char* clone(const unsigned char* up, int length);
/*{
  unsigned char* p = new unsigned char [length];
  memcpy(p, up, length);
  return p;
}*/

#endif
