#include <iostream>
#include "person.h"

int main() {
  std::cout << "\033[38;5;220m[Problem 2-1]\033[m\n";
  std::cout << max(5, 10) << std::endl;  // 10
  std::cout << max(10, 5) << std::endl;  // 10
  std::cout << max(5.555, 1.01234) << std::endl;  // 5.555
  std::cout << max(1.01234, 5.555) << std::endl;  // 5.555
  std::cout << max('A', 'G') << std::endl;  // G
  std::cout << max('G', 'A') << std::endl;  // G

  std::cout << "\n\033[38;5;220m[Problem 2-2]\033[m\n";
  Person p1("Olivia", 163);
  Person p2("Emily", 170);
  std::cout << max(p1, p2).getHeight() << std::endl;  // 170
  
  std::cout << "\n\033[38;5;220m[Problem 2-3]\033[m\n";
  std::cout << max(p1, p2) << std::endl;  // Emily
  Person p3("Jack", 180);
  std::cout << max(p3, p2) << std::endl;  // Jack

  return 0;
}
