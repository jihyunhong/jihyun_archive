#include <iostream>
#include "arrayT.cpp"

int main() {
  int size;
  std::cin >> size;

  ArrayT<int> arrayInt(size);
  ArrayT<double> arrayDouble(size);
  ArrayT<char> arrayChar(size);
  

  if (true) {
    ArrayT<int> arrayIntTemp(size);
    ArrayT<double> arrayDoubleTemp(size);
    ArrayT<char> arrayCharTemp(size);

    std::cout << "-- Check setElement() works --" << std::endl;
    for (int i = 0; i < size + 1; ++i) {
      double temp;
      std::cin >> temp;
      arrayIntTemp.setElement(i, temp);
      arrayDoubleTemp.setElement(i, temp);
      arrayCharTemp.setElement(i, temp);
    }
    std::cout << std::endl;

    std::cout << "-- Check assignment operator works --" << std::endl;
    arrayInt = arrayIntTemp;
    arrayDouble = arrayDoubleTemp;
    arrayChar = arrayCharTemp;
    std::cout << std::endl;
  }
  
  std::cout << "-- First element of each arrays --" << std::endl;
  std::cout << arrayInt.getElement(0) << std::endl;
  std::cout << arrayDouble.getElement(0) << std::endl;
  std::cout << arrayChar.getElement(0) << std::endl;
  std::cout << std::endl;

  std::cout << "-- Check print() works --" << std::endl;
  std::cout << "arrayInt: "; arrayInt.print();
  std::cout << "arrayDouble: "; arrayDouble.print();
  std::cout << "arrayChar: "; arrayChar.print();
  std::cout << std::endl;

  std::cout << "-- Check getElement() handles exception --" << std::endl;
  arrayInt.getElement(arrayInt.getSize());
  arrayInt.getElement(arrayInt.getSize());
  arrayInt.getElement(arrayInt.getSize());
  std::cout << std::endl;

  return 0;
}
