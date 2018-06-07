#include "apallocator.hpp"

int main()
{
  apAllocator_<char> ap1(3);
  apAllocator_<char> ap2(10000, 1);

  return 0;
}
