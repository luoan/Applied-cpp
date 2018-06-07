#ifndef _apallocator_hpp_
#define _apallocator_hpp_


#include "apallocatorbase.hpp"

template <class T>
class apAllocator_ : public apAllocatorBase_<T>
{
public :
  explicit apAllocator_ (unsigned int n, unsigned int align=0) :
      apAllocatorBase_<T>(n, align) {
    allocate();
    this->addRef ();
  }

  virtual ~apAllocator_() { deallocate(); }
private :
  virtual void allocate ();
  virtual void deallocate ();

  apAllocator_ (const apAllocator_& );
  apAllocator_& operator= (const apAllocator_& );
  //both empty;
};

template <class T>
void apAllocator_<T>::allocate()
{
  if (this->size_ == 0) {
    this->pData_ = new T[1];
    this->pRaw_ = 0;
    return;
  }
  if (this->align_ < 2) {
    this->pData_ = new T[this->size_];
    this->pRaw_ = 0;
  }
  else {
    this->pRaw_ = new char [sizeof(T) * this->size_ + (this->align_ - 1)];
    this->pData_ = this->alignPointer(this->pRaw_);
  }
}

template <class T>
void apAllocator_<T>::deallocate ()
{
  if (this->pRaw_)
    delete [] this->pRaw_;
  else
    delete [] this->pData_;
  this->pRaw_ = this->pData_ = 0;
}

#endif
