#include "image.h"

#include <iostream>

int main()
{
  apImage p(3, 5);
  unsigned char c = 13;
  std::cout << "c= " << c << std::endl;
  p.setPixel(0, 0, c);
  p.show();
  return 0;
}
