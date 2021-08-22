#include <iostream>

#include "test.h"

// TODO
// implement swap functions here
// Q: why not use swapByValue?

// swap two integers by "pass by reference"
void swapByRef(int &ref1, int &ref2){
  int temp = ref1;
  ref1 = ref2;
  ref2 = temp;
} //... Implement

// swap two integers by "pass by pointer"
void swapByPtr(int *ptr1, int *ptr2){
  int temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
} //... Implement

// swap two variable-size integer arrays
// YOU DO NOT NEED "new", "delete", etc
// i.e. YOU DO NOT NEED DYNAMIC ALLOCATION IN THIS FUNCTION
// THERE IS A VERY SIMPLE SOLUTION!
void swapArray(int **a, int **b){
    int *temp;
    temp = *a;
    *a = *b;
    *b = temp;
} //... Implement

int main() {
  int a = 1;
  int b = 2;
  std::cout << a << " " << b << std::endl;
  swapByRef(a,b);
  std::cout << a << " " << b << std::endl;

  int c = 3;
  int d = 4;
  std::cout << c << " " << d << std::endl;
  swapByPtr(&c, &d);
  std::cout << c << " " << d << std::endl;

  // two integer arrays e and f
  int* e = new int [5];
  e[0] = 1; e[1] = 2; e[2] = 3; e[3] = 4; e[4] = 5;
  int* f = new int [7];
  f[0] = 6; f[1] = 7; f[2] = 8; f[3] = 9; f[4] = 10;
  f[5] = 11; f[6] = 12;

  // print status before swapping
  for(int i = 0; i < 5; i++) {
    std::cout << e[i]  << " ";
  }
  std::cout << std::endl;
  for(int j = 0; j < 7; j++) {
    std::cout << f[j] << " ";
  }
  std::cout << std::endl;
  
  // swap two arrays
  // std::cout << &e[0] << std::endl;;
  // std::cout << &f[0] << std::endl;;
  swapArray(&e, &f);
  // std::cout << &e[0] << std::endl;;
  // std::cout << &f[0] << std::endl;;

  // print status after swapping
  for(int i = 0; i < 7; i++) {
    std::cout << e[i]  << " ";
  }
  std::cout << std::endl;
  for(int j = 0; j < 5; j++) {
    std::cout << f[j] << " ";
  }
  std::cout << std::endl;

  TEST();

  return 0;
}

// just doing some checks
// do not care what this function is doing
void TEST() {
  using vf = decltype(swapByRef);
  using vg = decltype(swapByPtr);
  using vh = decltype(swapArray);
  std::cout << std::endl << "TEST FLAGS" << std::endl;
  std::cout << "Do not care about the output below this" << std::endl;

  std::cout << (int)std::is_same<vf, va>::value;
  std::cout << (int)std::is_same<vf, vb>::value;
  std::cout << (int)std::is_same<vf, vc>::value;
  std::cout << (int)std::is_same<vf, vd>::value;
  std::cout << (int)std::is_same<vf, ve>::value;
  std::cout << (int)std::is_same<vg, va>::value;
  std::cout << (int)std::is_same<vg, vb>::value;
  std::cout << (int)std::is_same<vg, vc>::value;
  std::cout << (int)std::is_same<vg, vd>::value;
  std::cout << (int)std::is_same<vg, ve>::value;
  std::cout << (int)std::is_same<vh, va>::value;
  std::cout << (int)std::is_same<vh, vb>::value;
  std::cout << (int)std::is_same<vh, vc>::value;
  std::cout << (int)std::is_same<vh, vd>::value;
  std::cout << (int)std::is_same<vh, ve>::value << std::endl;
}

