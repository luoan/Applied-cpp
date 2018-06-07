#ifndef _picture_hpp_
#define _picture_hpp_


#include "ptr.hpp"
#include "image.h"
#include <iostream>

class Picture
{
  friend std::ostream& operator<<(std::ostream&, const Picture&);
public :
  Picture () { }
  Picture (int width, int height) { ip = new apImage(width, height); }

  int width()  const { return ip->width(); }
  int height() const { return ip->height(); }
  
  bool isValid() const { return ip->isValid(); }
  //这个设置为const 好像是可以巴，因为我们并没有改变ip指向
  void setPixel (int width, int height, 
        unsigned char pixel) const {
    ip->setPixel(width, height, pixel);
  }
  unsigned char getPixel (int width, int height) const {
    return ip->getPixel(width, height);
  }
  
private :
  Ptr<apImage> ip;
};

std::ostream& operator<< (std::ostream& os, const Picture& );
Picture thumbnail(const Picture&, int factor);

#endif
