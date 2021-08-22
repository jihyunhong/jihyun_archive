#include <iostream>
#include <string>
#include "arrayT.h"

template <typename T>
ArrayT<T>::ArrayT() : size(0) {
  array = new T[size];
}

// TODO //
template <typename T>
ArrayT<T>::ArrayT(int size){
  this->size = size;
  array = new T[size];
}

template <typename T>
ArrayT<T>::~ArrayT(){
  delete []array;
}

template <typename T>
T ArrayT<T>::getElement(int pos) const{
  if (pos < 0 || pos >= getSize()){
    std::cout << "Out of Range\n";
    return 0;
  }
  else{
    return array[pos];
  }
}

template <typename T>
void ArrayT<T>::setElement(int pos, T val){
  if (pos < 0 || pos >= getSize()){
    std::cout << "Out of Range\n";
    return;
  }
  else{ // 0 1 2 3 4 5
    array[pos] = val;
  }
}

template <typename T>
int ArrayT<T>::getSize() const{
  return size;
}

template <typename T>
void ArrayT<T>::print() const{
  for (int i=0; i<getSize(); i++){
    std::cout << array[i] << " ";
  }
  std::cout << "\n";
}

template <typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& rhs){
  if (this == &rhs) return *this;

  delete []array;

  size = rhs.size;
  array = new T[size];           // ------------------------- 조심!!!
  for (int i=0; i<size; i++){
    array[i] = rhs.array[i];    // ------------------------- 조심!!!
  }
  return *this;
}

template <typename T>
ArrayT<T>& ArrayT<T>::operator[](int index){
  return array[index];
}
