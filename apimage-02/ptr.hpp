#ifndef _ptr_h_
#define _ptr_h_


#include <stddef.h>
#include <stdexcept>

//template <class T> T* clone(const T* );

template <class T>
class Ptr 
{
public :
  Ptr () : p(0), refptr(new size_t(1)) { }
  Ptr (T* t) : p(t), refptr(new size_t(1)) { }

  Ptr (const Ptr& src) : p(src.p), refptr(src.refptr) { ++*refptr; }
  Ptr& operator= (const Ptr& src) {
    ++*src.refptr;
    if (--*refptr == 0) { delete p; delete refptr; }
    p = src.p;
    refptr = src.refptr;
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
  operator bool() const { return p; }
  T* operator->() const { if (p) return p; else throw std::runtime_error("unbound Ptr.p");}
  T& operator*() const  { if (p) return *p; else throw std::runtime_error("unbound Ptr.p");}

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
