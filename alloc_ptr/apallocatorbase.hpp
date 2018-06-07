#ifndef _apallocatorbase_hpp_
#define _apallocatorbase_hpp_


#include <stdint.h> // for uintptr_t

template <class T>
class apAllocatorBase_
{
  //template <class F> friend F* clone(const F* );
public :
  apAllocatorBase_(unsigned int n, unsigned int align) : pRaw_(0), pData_(0), 
   /* ref_(0), */size_(n), align_(align) { }

  virtual ~apAllocatorBase_() { }

  operator T* () { return pData_; }
  operator T* () const { return pData_; }

  unsigned int size()  const { return size_; }
  //unsigned int ref()   const { return ref_; }
  unsigned int align() const { return align_; }

  //void addRef () { ++ref_; }
  //void subRef () { if (--ref_ == 0) delete this; }
protected :
  virtual void allocate() = 0;
  virtual void deallocate() = 0;

  T* alignPointer (void* raw);

  apAllocatorBase_ (const apAllocatorBase_& );
  apAllocatorBase_& operator=(const apAllocatorBase_& );

  char* pRaw_;
  T* pData_;
  unsigned int size_;
  //unsigned int ref_;
  unsigned int align_;
};

template <class T>
T* apAllocatorBase_<T>::alignPointer (void* raw)
{
  T* p = reinterpret_cast<T*> (
    (reinterpret_cast<uintptr_t>(raw) + align_ - 1)
      & ~(align_ - 1)
    );
  return p; 
}
#endif
