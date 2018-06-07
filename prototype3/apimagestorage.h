#ifndef _apimagestorage_h_
#define _apimagestorage_h_


#include "apstoragerep.h"
#include "ptr.hpp"

class apImageStorage
{
public :
  virtual ~apImageStorage () { }

protected :
  Ptr<apImageStorageRep> storage_;
};

template <class T>
class apImageStorageTmpl : public apImageStorage
{
public :
  apImageStorageTmpl () { }
  apImageStorageTmpl (unsigned int width, unsigned int height)
      : apaImageStorage (new apStorageRepTmpl<T>(width, height)) { }
  
  const apStorageRepTmpl<T>* operator-> () const {
    return static_cast<apStorageRepTmpl<T>*> (storage_->());
  }
};

#endif
