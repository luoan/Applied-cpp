#include "apstorage.h"

/*
 *apStroageRep
 * */
Ptr<apStorageRep> apStorageRep::sNull_;//这样就够了，调用默认构造函数。。

Ptr<apStorageRep> apStorageRep::gNull ()
{
  if (!sNull_)
    sNull_ = new apStorageRep ();
  return sNull_;
}

apStorageRep::apStorageRep () : width_(0), height_(0),
    bytesPerPixel_(0) 
{
  storage_ = apAlloc<unsigned char>(1);//0???
}

apStorageRep::apStorageRep (unsigned int width, unsigned int height,  unsigned int bytesperpixel)
{
  unsigned int allocation = width_ * height_ * bytesperpixel;
  if (allocation == 0) allocation = 1;

  storage_ = apAlloc<unsigned char>(allocation);
}


