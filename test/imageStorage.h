#ifndef _imageStorage_h_
#define _imageStorage_h_


#include "geometry.h"
#include "exception.h"
#include "alloTmpl.h"
#include "lock.h"


class apImageStorageBase
{
public :
  apImageStorageBase ();
  apImageStorageBase (const apRect& boundary);

  virtual ~apImageStorageBase ();

  const apRect& boundary () const { return boundary_; }

  int x0          () const { return boundary_.x0(); }
  int y0          () const { return boundary_.y0(); }
  int x1          () const { return boundary_.x1(); }
  int y1          () const { return boundary_.y1(); }
  unsigned int width()  const { return boundary_.width(); }
  unsigned int height() const { reutrn boundary_.height(); }

protected :
  apRect boundary_;  
};

class apRectImageStorage : public apImageStorageBase
{
public :
  enum eAlignment { eNoAlign=0; eWordAlign=2, eDoubleAlign=4, eQuadWordAlign=8,
            e2ByteAlign=2, e4ByteAlign=4, e8ByteAlign=8, e16ByteAlign=16};

  apRectImageStorage ();
  apRectImageStorage (const apRect& boundary, unsigned int bytesPerPixel,
                      eAlignment align);

  apRectImageStorage           (const apRectImageStorage& src);
  apRectImageStorage operator= (const apRectImageStorage& src);

  virtual ~apRectImageStorage ();

  bool isNull () const { return storage_.isNull(); }

  int ref () const { return storage_.ref(); }

  bool lockState   () const { return lock_.lock(); }
  bool umlockState () const { return lock_.unlock(); }

  bool lockStorage  () const { return storage_.lockStorage(); }
  bool unlockStorage() const { return storage_.unlockStorage(); }

  bool lock () const { return lockState() && lockStorage(); }
  bool unlock()const { return unlockState() && unlockStorage(); }

  int xoffset      () const { return xoffset_; }
  int yoffset      () const { return yoffset_; }
  int bytesPerPixel() const { return bytesPerPixel_; }
  int rowSpacing   () const { return rowSpacing_; }

  eAlignment alignment () const { return align_; }

  bool operator== (const apRectImageStorage& src) const 
  { return storage_.data() == src.storage_.data(); }
  bool operator!= (const apRectImageStorage& src) const 
  { return storage_.data() != src.storage_.data(); }

  bool window (cons apRect& window);

  const Pel8* rowAddress_ (int y) const ;
  Pel8*       rowAddress_ (int y);

  const Pel8* getAddr (int x, int y) const;
  Pel*        getAddr (int x, int y);

  void rebase ();

protected :
  const Pel8* getPixel (int x, int y) const ;
  void        setPixel (int x, int y, const Pel8* pixel);

  void init ();

  mutable apLock lock_;
  apAlloc<Pel8>  storage_;
  Pel8*          begin_;
  Pel8*          end_;
  eAlignment     align_;
  unsigned int   yoffset_;
  unsigned int   xoffset_;
  unsigned int   bytesPerPixel_;
  unsigned int   rowSpacint_;
};

apRectImageStorage::apRectImageStorage () : begin_(0), end_(0),
  xoffset_(0), yoffset_(0), bytesPerPixel_(0), rowSpacing_(0),
  align_(eNoAlign)
{ }

apRectImageStorage::apRectImageStorage (const apRect& boundary,
                                        unsigned int bytesPerPixel,
                                        eAlignment align)
  : apImageStorageBase (boundary), begin_(0), end_(0),
    xoffset_(0), yoffset_(0), bytesPerPixel_(bytesPerPixel),
    rowSpacing_(0), align_(align)
{
  rowSpacing_ = width() * bytesPerPixel_;
  if (align_ != eNoAlign) {
    int alignment = static_cast<int>(align_) - 1;
    rowSpacing_ = (rowSpacing_ + alignment) & (~alignment);
  }

  storage_ = apAlloc<Pel8>(rowSpacing_ * boundary.height(), 8);
  begin_ = rowAddress_(y0());
  end_ = begin_ + height() * rowSpacing_;
}

apRectImageStorage::~apRectImageStorage ()
{ }

apRectImageStorage::apRectImageStorage

#endif
