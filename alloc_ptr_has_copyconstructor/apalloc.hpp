#ifndef _apalloc_hpp_
#define _apalloc_hpp_


#include "apallocator.hpp"
#include "ptr.hpp"

template <class T, class A = apAllocator_<T> >
class apAlloc 
{
public :
  static apAlloc& gNull ();

  apAlloc ();
  apAlloc (unsigned int size, unsigned int align = 0);
  
  T& operator[](unsigned int index) const {
    pMem_.make_unique();
    return (*pMem_)[index]; //operator T* of apAllocatorBase_
  }
//  apAlloc (const apAlloc& );
//  apAlloc& operator= (const apAlloc& );
//  ~apAlloc ();

private :
  Ptr<A> pMem_;
  static apAlloc* sNull_;
};
#endif

template <class T, class A>
apAlloc<T, A>* apAlloc<T, A>::sNull_ = 0;

template <class T, class A>
apAlloc<T, A>& apAlloc<T, A>::gNull ()
{
  if (!sNull_)
    sNull_ = new apAlloc (0);
  return *sNull_;
}

template <class T, class A>
apAlloc<T, A>::apAlloc ()
{
  pMem_ = gNull().pMem_;
}

template <class T, class A>
apAlloc<T, A>::apAlloc (unsigned int size, unsigned int align)
{
  pMem_ = new A (size, align);
}
