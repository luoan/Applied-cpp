#ifndef _apalloc_hpp
#define _apalloc_hpp


#include "ptr.hpp"
#include <stdint.h>
#include <algorithm>
#include <iostream>
/*
 *apAllocatorBase_
 * */
template <class T>
class apAllocatorBase_
{
public :
  apAllocatorBase_ (unsigned int size, 
      unsigned int align) : pRaw_(0), pData_(0), size_(size), align_(align) { }

  virtual ~apAllocatorBase_ () { };

  T*  pData ()  { /*std::cout << "apAllocatorBase_ pData() "<< std::endl;*/ return pData_; }
  const T*    pData() const { /*std::cout << "apAllocatorBase_() pData() const " << std::endl;*/ return pData_; }
  unsigned int size() const { return size_; }
  unsigned int align() const { return align_; }

protected :
  virtual void allocate ()   = 0;
  virtual void deallocate () = 0;

  T* alignPointer(void* );

  // empty no copy constructor or operator=
  apAllocatorBase_ (const apAllocatorBase_& );
  apAllocatorBase_& operator= (const apAllocatorBase_& );
  char* pRaw_;
  T*    pData_;
  unsigned int size_;
  unsigned int align_;
};

template <class T>
T* apAllocatorBase_<T>::alignPointer (void* raw)
{
  T* p = reinterpret_cast<T*> (
      (reinterpret_cast<uintptr_t>(raw) + align_ -1)
      & ~(align_ - 1));
  return p;
}


/*
 *apAllocator_
 * */
template <class T>
class apAllocator_ : public apAllocatorBase_<T>
{
  template <class F> friend F* clone(const F* );
  //F* clone (const F* ); // wrong
public :
  explicit apAllocator_<T> (unsigned int n, 
      unsigned int align = 0) : apAllocatorBase_<T> (n, align) 
  {
    allocate ();
  }

  virtual ~apAllocator_ () { deallocate (); }
protected :
  apAllocator_* clone() const;
private :
  virtual void allocate ();
  virtual void deallocate ();

  apAllocator_ (const apAllocator_& );
  apAllocator_& operator= (const apAllocator_& );
};

template <class T>
apAllocator_<T>* apAllocator_<T>::clone() const 
{
  //std::cout << "\nbegin apAllocator_ clone" << std::endl;
  apAllocator_* p = new apAllocator_ (this->size(), this->align()) ;
  std::copy (this->pData(), this->pData() + this->size(), p->pData());
  //std::cout << "end apAllocator_ clone\n" << std::endl;
  return p;
}

template <class T>
void apAllocator_<T>::allocate ()
{
  if (this->size_ == 0) {
    std::cout << "apAllocator_ allocate() size=0" << std::endl;
    this->pData_ = new T[1];
    this->pRaw_ = 0;
    return;
  }
  if (this->align_ < 2) {
    std::cout << "apAllocator_ allocate() size!=0" << std::endl;
    this->pData_ = new T[this->size_];
    this->pRaw_ = 0;
  }
  else {
    this->pRaw_ = new char [sizeof(T) * this->size_ + (this->align_ - 1)];
    this->pData_ = this->alignPointer (this->pRaw_);
  }
}

template <class T>
void apAllocator_<T>::deallocate ()
{
  if (this->pRaw_)
    delete [] this->pRaw_;
  else 
    delete [] this->pData_;
  this->pRaw_ = 0;
  this->pData_ = 0;
}


/*
 *apAlloc
 * */
template <class T, class A = apAllocator_<T> >
class apAlloc 
{
public :
  static apAlloc& gNull ();

  apAlloc ();
  explicit apAlloc (unsigned int size, unsigned int align=0);

  unsigned int size () const { return pMem_->size(); }
  bool isNull () const { return pMem_ == gNull().pMem_; }
  
  const T* data () const { return pMem_->pData(); }
  T* data () { return pMem_->pData(); } // 不要make_unique，operator[]调用这个
  
  const T& operator[] (unsigned int index) const {
    if (index >= size()) throw std::range_error("Index out of range");
    //std::cout << "operator[] const " << std::endl;
    return (data())[index];
    //return (pMem_->pData())[index];
    //return *(data() + index); // also ok
  }
  
  T& operator[] (unsigned int index)  {
    if (index >= size()) throw std::range_error("Index out of range");
    //std::cout << "operator[]" << std::endl;
    pMem_.make_unique ();
    return (data())[index];
    //return (pMem_->pData())[index];
    //return *(data() + index);
  }

protected :
  Ptr<A> pMem_;
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
apAlloc<T, A>::apAlloc ()
{
  pMem_ = gNull().pMem_;
}

template <class T, class A>
apAlloc<T, A>::apAlloc (unsigned int size, unsigned int align)
{
  pMem_ = new A(size, align);
}

#endif
