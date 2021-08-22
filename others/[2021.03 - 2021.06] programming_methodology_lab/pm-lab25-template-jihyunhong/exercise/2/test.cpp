#include <iostream>
#include "person.h"

int main() {
  double d1;
  double d2;
  std::cin >> d1 >> d2;

  std::cout << max(d1, d2) << std::endl;
  std::cout << max((int)d1, (int)d2) << std::endl;
  std::cout << max((char)d2, (char)d1) << std::endl;

  std::string name1;
  std::string name2;
  std::cin >> name1 >> name2;
  std::cin >> d1 >> d2;
  Person p1(name1, d1);
  Person p2(name2, d2);
  std::cout << max(p1, p2) << std::endl;

  return 0;
}
