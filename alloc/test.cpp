#include "apalloc.hpp"

#include <iostream>
int main()
{
  //apAlloc<char> ap1;
  //apAlloc<char> ap2;
  //apAlloc<char> ap3;
  //std::cout << "ap1.pMem_.pData_ " << (long)ap1.pMem_->pData() << std::endl;
  //std::cout << "ap2.pMem_.pData_ " << (long)ap2.pMem_->pData() << std::endl;
  apAlloc<char> ap4(32);
  apAlloc<char> ap5(19);

  ap5 = ap4;
  //ap5[0] = 13;
  char a = 5;
  if (ap5[0] == a)
    return 0;
  
  //std::cout << (int) ap5[0] << std::endl;
  return 0;
}
