#ifndef _ptr_hpp
#define _ptr_hpp


#include <stdexcept>
#include <stddef.h>

//template <class T> T* clone(const T* );

template <class T>
class Ptr 
{
public :
  Ptr () : p(0), refptr(new size_t(1))  { }
  Ptr (T* t) : p(t), refptr(new size_t(1))  { }

  Ptr (const Ptr& rhs) : p(rhs.p), refptr(rhs.refptr) { ++*refptr; }
  Ptr& operator= (const Ptr& rhs) {
    ++*rhs.refptr;
    if (--*refptr == 0) {
      delete refptr;
      delete p;
    }
    p = rhs.p;
    refptr = rhs.refptr;
    return *this;
  }
  ~Ptr () { if (--*refptr == 0) { delete p; delete refptr; }}

  void make_unique () {
    if (*refptr != 1) {
      --*refptr;
      p = p ? clone(p) : 0;
      refptr = new size_t (1);
    }
  }

  operator bool () const { return p; }
  T* operator->() const { return p; }
  T& operator*()  const { return *p; }
private :
  T* p;
  size_t* refptr;
};

template <class T>
T* clone(const T* tp)
{
  return tp->clone();
}

#endif
