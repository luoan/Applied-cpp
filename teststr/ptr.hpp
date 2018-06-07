#ifndef _ptr_h
#define _ptr_h


#include <stddef.h>
#include <stdexcept>
#include <iostream>

template <class T>
class Ptr 
{
public :
  Ptr () : p(0), refptr(new size_t(1)) { }
  Ptr (T* t) : p(t), refptr(new size_t(1)) { }

  Ptr (const Ptr& rhs) : p(rhs.p), refptr(rhs.refptr) { ++*refptr; }
  Ptr& operator= (const Ptr& rhs) {
    ++*rhs.refptr;
    if (--*refptr == 0) {
      delete p;
      delete refptr;
    }
    p = rhs.p;
    refptr = rhs.refptr;
    return *this;
  }
  ~Ptr () { if (--*refptr == 0) { delete p; delete refptr; }}

  void make_unique() {
    if (*refptr != 1) {
      --*refptr;
      p = p ? clone(p) : 0;
      refptr = new size_t(1);
    }
  }

  operator bool () const { return p; }
  T* operator-> () const { std::cout << "Ptr -> const" << std::endl; if (p) return p;  throw std::runtime_error("unbound Ptr"); }
  T* operator->() { std::cout << "Ptr ->" << std::endl; if(p) return p; throw std::runtime_error("unbound Ptr"); }
  T& operator*  () const { std::cout << "Ptr *()" << std::endl; if (p) return *p; throw std::runtime_error("unbound Ptr"); }
  T& operator*() { std::cout << "Ptr *()" << std::endl; if (p) return *p; throw std::runtime_error("unbound Ptr"); }
private :
  T* p;
  size_t* refptr;
};

#include <iostream>
template <class T>
T* clone(const T* tp)
{
  std::cout << "make_unique   use T* clone() " << std::endl;
  return tp->clone();
}

#endif
