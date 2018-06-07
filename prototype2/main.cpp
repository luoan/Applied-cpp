#include "apimage.hpp"
//#include "rgb.hpp"

#include <iostream>

int main()
{/*
  apImage<unsigned char, long> ap1(5, 5);
  ap1.setPixel (0, 0, 13);
  apImage<unsigned char, long> ap2;
  ap2 = ap1.thumbnail (2);
  //ap1.setPixel (0 ,0, 13);
  std::cout << ap1 << std::endl;
  std::cout << ap2 << std::endl;
*/

  
  apImage<RGB, RGB> ap1(5, 3);
  apImage<RGB, RGB> ap2;
  apImage<RGB, RGB> ap3(3, 3);
  ap1.setPixel (0, 0, RGB(1, 3, 5));

  std::cout << ap1 << std::endl;

  return 0;
}
