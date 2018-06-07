#include "picture.h"

#include <iostream>

int main()
{
  Picture p1 (5, 5);
  std::cout << p1 << std::endl;
  p1.setPixel (0, 0, 255);
  p1.setPixel (2, 2, 133);
  std::cout << p1 << std::endl;

  Picture p2 = thumbnail(p1, 2);
  std::cout << p2 << std::endl;

  return 0;
}

/*
#include "image.h"

#include <iostream>

int main()
{
  apImage p1 (3, 5);
  p1.setPixel (2, 1, 9);
  std::cout << p1 << std::endl;

  return 0;
}*/
