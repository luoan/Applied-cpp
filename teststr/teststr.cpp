#include "str.h"

#include <iostream>
int main()
{
  Str s1("hello");
  Str s2(s1);
  Str s3(s1);

  char c = s2[0];
  
  std::cout << s1 << std::endl;
  return 0;
}
