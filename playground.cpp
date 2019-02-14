#include <iostream>

int main()
{
  int y = 3;
  int *x = &y;
  int &ref = *x;
  ref++;
  std::cout << y << std::endl;
  return 0;
}
