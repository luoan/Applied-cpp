#ifndef _PTR_H_
#define _PTR_H_


#include <stddef.h>
#include <stdexcept>
#include <iostream>

template <class T> T* clone(const T*, int );
//template <> unsigned char* clone(const unsigned char*, int);

template <class T>
class Ptr 
{
  //friend class apImage
public :
  Ptr () : p(0), refptr(new size_t(1)) { }
  Ptr (T* t) : p(t), refptr(new size_t(1)) { 
   // std::cout << "ptr T* t" << std::endl;
  }

  Ptr(const Ptr& rhs) : p(rhs.p), refptr(rhs.refptr) { ++*refptr; }
  Ptr& operator= (const Ptr& rhs) {
    ++*rhs.refptr;
    if (--*refptr == 0) {
      delete [] p;
      delete refptr;
    }
    p = rhs.p;
    refptr =rhs.refptr;
    return *this;
  }
  ~Ptr () { if (--*refptr == 0) { std::cout << "in Ptr::~Ptr()" << std::endl; delete [] p; delete refptr;}}
  
  void make_unique (int length) {
    if (*refptr != 1) { 
      --*refptr;
      p = p ? clone(p, length) : 0;
      refptr = new size_t(1);
    }
  }
  operator T* () const   { /*std::cout << "operatorT* " << "ptr.p= " << p << std::endl;*/ return p; }
  //T* get() const { return p; }
  operator bool () const { return p; }
  T* operator->() const  { return p; }
  T& operator*() const   { return *p; }

//private :
  T* p;
  size_t* refptr;
};

template <class T>
T* clone(const T* tp, int length)
{
  return tp->clone();
}
/*
#include <string.h>
template <>
unsigned char* clone(const unsigned char* up, int length)
{
  unsigned char* p = new unsigned char [length];
  memcpy(p, up, length);
  return p;
}*/
#endif
