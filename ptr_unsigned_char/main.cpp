#include "image.h"


apImage test()
{
  apImage p1(3, 6);
  std::cout << "in test() index p1 pixels_.refptr= " << *p1.pixels_.refptr << std::endl;
  apImage p2 = p1;
  std::cout << "in test() index p1 pixels_.refptr= " << *p1.pixels_.refptr << std::endl;
  std::cout << "in test() index p2 pixels_.refptr= " << *p2.pixels_.refptr << std::endl;
  apImage p3;
  return p1;
}
int main()
{
  std::cout << "in main" << std::endl;
  /*apImage pmain =*/ test();
  //std::cout << "in main() index pmain pixels_.refptr= " << *pmain.pixels_.refptr << std::endl;
  std::cout << "main return " << std::endl;
  
  return 0;
  /*
  apImage p1(3, 5);
  p1.setPixel(0, 1, 3);
  std::cout << "index p1 pixels_.refptr= " << *p1.pixels_.refptr << std::endl;
  p1.show();
  std::cout << std::endl;

  apImage p2 = p1;
  std::cout << "index p1 pixels_.refptr= " << *p1.pixels_.refptr << std::endl;
  std::cout << "index p2 pixels_.refptr= " << *p2.pixels_.refptr << std::endl;
  p2.setPixel(0, 1, 5);
  std::cout << " after p2.setPixel index p1 pixels_.refptr= " << *p1.pixels_.refptr << std::endl;
  std::cout << "index p2 pixels_.refptr= " << *p2.pixels_.refptr << std::endl;
  p2.show();
  std::cout << std::endl;

  p1.show();
  return 0;*/
}
