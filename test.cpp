#include <iostream>

int main()
{
  unsigned char* cp1 = new unsigned char[10];

  unsigned char* cp2 = cp1;
  
  delete [] cp1;

  return 0;
}
