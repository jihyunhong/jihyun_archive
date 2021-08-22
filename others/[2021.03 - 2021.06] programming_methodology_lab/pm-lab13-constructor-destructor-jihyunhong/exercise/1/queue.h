#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

class Queue {
  int *arr;
  int size;
public:
  Queue();
  Queue(int size);
  ~Queue();
};

#endif