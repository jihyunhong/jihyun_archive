#include <iostream>
#include "queue.h"
#include "stack.h"

int main() {
  int size;

  std::cout << "  > Create queue1" << '\n';
  Queue q1;
  std::cout << '\n';

  std::cout << "  > Create queue2" << '\n';
  std::cout << "Queue size = ";
  std::cin >> size;
  Queue q2(size);
  std::cout << '\n';

  std::cout << "  > Create stack1" << '\n';
  Stack s1;
  std::cout << '\n';

  std::cout << "  > Create stack2" << '\n';
  std::cout << "Stack size = ";
  std::cin >> size;
  Stack s2(size);

  std::cout << '\n' << "End of program" << '\n';
  return 0;
}