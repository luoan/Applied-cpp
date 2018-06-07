#include "apimage.hpp"

#include <iostream>

int main()
{
  apImage<unsigned char> ap1;
  apImage<char> ap2;

  apImage<char> ap3 = ap2;
  
  std::cout << ap1 << std::endl;
  apImage<char> ap5(13, 9);
  ap3 = ap5;
  std::cout << ap3 << std::endl;

  return 0;
}
