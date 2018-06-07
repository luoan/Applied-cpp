#include "apalloc.hpp"
#include <iostream>

int main()
{
  apAlloc<char> ap1(10);
  apAlloc<char> ap2 = ap1;
  
  std::cout << (int) ap2[3] << std::endl;

  return 0;
}
