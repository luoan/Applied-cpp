#ifndef _apallocatorbase_hpp_
#define _apallocatorbase_hpp_


#include <stdint.h> // for uintptr_t

template <class T>
class apAllocatorBase_
{
 // template <class F> friend F* clone(const F* );
public :
  apAllocatorBase_(unsigned int n, unsigned int align) : pRaw_(0), pData_(0), 
   /* ref_(0), */size_(n), align_(align) { }

  virtual ~apAllocatorBase_() { }

  operator T* () { return pData_; }
  operator const T* () const { return pData_; }
  
  const T* pData() const { return pData_; }
  unsigned int size()  const { return size_; }
  //unsigned int ref()   const { return ref_; }
  unsigned int align() const { return align_; }

  //void addRef () { ++ref_; }
  //void subRef () { if (--ref_ == 0) delete this; }
protected :
  virtual void allocate() = 0;
  virtual void deallocate() = 0;

  T* alignPointer (void* raw);

  apAllocatorBase_ (const apAllocatorBase_& );// 因为apAllocator_定义了复制构造函数，所以他的基类也必须定义复制构造函数
                                              // 因为构造时会先构造基类
                                              // 貌似这样行不通
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
