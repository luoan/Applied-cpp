#ifndef _image_h_
#define _image_h_


#include <iostream>

class apImage 
{
public :
  apImage ();
  apImage (int width, int height);

  apImage (const apImage& );
  apImage& operator= (const apImage& );
  ~apImage ();

  int width () const { return width_; }
  int height () const { return height_; }

  bool isValid () const { return pixels_; }

  void setPixel (int width, int height, unsigned char pixel);
  unsigned char getPixel (int width, int height) const;
  class rangeError { };
protected :
  apImage* clone() const { return new apImage(*this); }
private :
  int width_;
  int height_;
  unsigned char* pixels_;
  void init ();
  void cleanup ();
};

std::ostream& operator<< (std::ostream& , const apImage& ) ;

#endif
