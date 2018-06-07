#ifndef _apstorage_h
#define _apstorage_h


#include "apalloc.hpp"
#include "ptr.hpp"
//#include "/home/luoan/appliedcpp_program/alloc/apalloc.hpp"
class apStorageRep
{
public :
  static Ptr<apStorageRep> gNull ();

  apStorageRep ();
  apStorageRep (unsigned int width, unsigned int height,
      unsigned int bytesperpixel);

  virtual ~apStorageRep () { };

  const unsigned char* base () const { return storage_.data(); }
  unsigned char*       base () /*const 无法被重载*/ { return storage_.data(); }

  unsigned int bytesPerPixel () const { return bytesPerPixel_; }

protected :
  apAlloc<unsigned char> storage_;
  unsigned int bytesPerPixel_;
  unsigned int width_;
  unsigned int height_;

  static Ptr<apStorageRep> sNull_;
};


template <class T>
class apStorageRepTmpl : public apStorageRep
{
public :
  apStorageRepTmpl () { }
  apStorageRepTmpl (unsigned int width, unsigned int height) : apStorageRep (width, height, sizeof(T)) { }

  virtual ~apStorageRepTmpl () { }

  const T* base () const { 
    return reinterpret_cast<const T*> (apStorageRep::base()); 
  }
  T* base () {
    return reinterpret_cast<T*> (apStorageRep::base());
  }
};


#endif
