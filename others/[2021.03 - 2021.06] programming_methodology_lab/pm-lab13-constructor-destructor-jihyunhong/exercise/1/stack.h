#ifndef STACK_H
#define STACK_H

#include <iostream>

class Stack {
  int *arr;
  int size;
public:
  Stack();
  Stack(int size);
  ~Stack();
};

#endif