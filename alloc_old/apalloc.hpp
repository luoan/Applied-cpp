#ifndef _apalloc_hpp_
#define _apalloc_hpp_


#include "apallocator.hpp"

#include <stdexcept>
#include <algorithm>

template <class T, class A = apAllocator_<T> > 
class apAlloc
{
public :
  static apAlloc& gNull ();

  apAlloc ();

  explicit apAlloc (unsigned int size, unsigned int align=0);
  
  ~apAlloc ();
  apAlloc (const apAlloc& );
  apAlloc& operator= (const apAlloc& );

  unsigned int size () const { return pMem_->size(); }
  unsigned int ref  () const { return pMem_->ref (); }
  bool       isNull () const { return pMem_ == gNull().pMem_; }

  const T* data () const { return *pMem_; }
  T*       data () { return *pMem_; }

  const T& operator[](unsigned int index) const;
  T& operator[](unsigned int index) ;

  virtual A* clone ();

  void duplicate ();

protected :
  A* pMem_;
  static apAlloc* sNull_;
};

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
apAlloc<T, A>::apAlloc () : pMem_(0)
{
  pMem_ = gNull ().pMem_;
  pMem_->addRef();
}

template <class T, class A>
apAlloc<T, A>::apAlloc (unsigned int size, 
    unsigned int align) : pMem_(0)
{
  pMem_ = new A (size, align);
}

template <class T, class A>
apAlloc<T, A>::~apAlloc ()
{
  pMem_->subRef ();
}

template <class T, class A>
apAlloc<T, A>::apAlloc (const apAlloc& src)
{
  pMem_ = src.pMem_;
  pMem_->addRef ();
}

template <class T, class A>
apAlloc<T, A>& apAlloc<T, A>::operator= (const apAlloc& src)
{
  if (pMem_ == src.pMem_)
    return *this;

  pMem_->subRef ();
  pMem_ = src.pMem_;
  pMem_->addRef ();
  return *this;
}

template <class T, class A>
const T& apAlloc<T, A>::operator[] (unsigned int index) const
{
  if (index >= size())
    throw std::range_error("Index out of range");
  return *(data() + index);
}

template <class T, class A>
T& apAlloc<T, A>::operator[] (unsigned int index)
{
  if (index >= size())
    throw std::range_error("Index out of range");

  duplicate ();
  return *(data() + index);
}

template <class T, class A>
A* apAlloc<T, A>::clone ()
{
  A* copy = new A (pMem_->size(), pMem_->align());

  T* src = *pMem_;
  T* dst = *copy;
  std::copy (src, &(src[pMem_->size()]), dst);

  return copy;
}

template <class T, class A>
void apAlloc<T, A>::duplicate ()
{
  if (ref () == 1) {
    return;
  }
  A* copy = clone();
  pMem_->subRef();
  pMem_ = copy;
}

#endif
