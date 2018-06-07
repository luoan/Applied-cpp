#include "apimage.h"

int main()
{
  apImage8 ap1(3, 5);
  apImage32 ap2(5, 5);
  
  ap1.setPixel (0, 0, 32);
  ap2.setPixel (0, 1, 190);
  //std::cout << ap1.width() << std::endl;
  //std::cout << (int)ap1.getPixel(0, 0) << std::endl;
  std::cout << ap1 << std::endl;

  std::cout << ap2 << std::endl;

  apImage32 ap3 = ap2.thumbnail(2);
  std::cout << ap3 << std::endl;
  return 0;
}
