#ifndef _apallocator_hpp_
#define _apallocator_hpp_


#include "apallocatorbase.hpp"
#include <algorithm>

template <class T>
class apAllocator_ : public apAllocatorBase_<T>
{
  //template <class F> friend class Ptr;
  template <class F> friend F* clone (const F* );//
                                                //
                                                // 设置为apAllocator_ 的友元是因为clone 是protected的
                                                // 
public :
  explicit apAllocator_ (unsigned int n, unsigned int align=0) :
      apAllocatorBase_<T>(n, align) {
    allocate();
 //   this->addRef ();
  }

  virtual ~apAllocator_() { deallocate(); }
protected :
  apAllocator_* clone() const;
private :
  virtual void allocate ();
  virtual void deallocate ();

  apAllocator_ (const apAllocator_& );
  apAllocator_& operator= (const apAllocator_& );
  //empty
};
template <class T>
apAllocator_<T>* apAllocator_<T>::clone () const 
{
  apAllocator_* p = new apAllocator_(this->size(), this->align());
  //std::copy (this->pData_, this->pData_ + this->size(), p->pData_);
  std::copy (this->pData(), this->pData_ + this->size(), p->pData());
  return p;
}

/*
template <class T>
apAllocator_<T>::apAllocator_ (const apAllocator_& src)
{
  apAllocator_ (src.size(), src.align());
  std::copy (this->pData_, this->pData_ + this->size(), src.pData_);
}*/
/*
template <class T>
apAllocator_<T>* apAllocator_<T>::clone () const 
{
  apAllocator_* p = new apAllocator_(this->size_, this->align_);
  std::copy (this->pData_, this->pData_+this->size(), p->pData_);// *p is not ok will call the copy construction !!!
  return p;
}
*/
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
