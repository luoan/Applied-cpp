#include "picture.h"

std::ostream& operator<< (std::ostream& os, const Picture& p)
{
  os << *(p.ip);
}

Picture thumbnail(const Picture& source, int factor)
{
  if (!source.isValid() || factor <= 0)
    throw std::runtime_error("can not thumbnail");

  Picture thumb(source.width()/factor, source.height()/factor);

  for (int h = 0; h != thumb.height(); ++h) {
    for (int w = 0; w != thumb.width(); ++w) {
      thumb.setPixel(w, h, source.getPixel(w, h));
    }
  }

  return thumb;
}
