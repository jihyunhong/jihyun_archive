#include <iostream>

#include "Circle.h"

int main()
{
  Circle a, b;
  int ID_a, ID_b;
  int Radius_a, Radius_b;
  std::cout << "Write the ID of the 1st circle : ";
  std::cin >> ID_a;
  std::cout << "Write the Radius of the 1st circle : ";
  std::cin >> Radius_a;
  std::cout << std::endl;
  std::cout << "Write the ID of the 2nd circle : ";
  std::cin >> ID_b;
  if (ID_a == ID_b)
  {
    std::cout << "Error : The ID is the same as the ID of the 1st circle" << std::endl;
    std::cout << "Write the ID of the 2nd circle again: ";
    std::cin >> ID_b;
  }
  std::cout << "Write the Radius of the 2nd circle : ";
  std::cin >> Radius_b;
  std::cout << std::endl;

  //-------- Implement here ---------//
  //fill each circle class with information.

  a.setID(ID_a);
  a.getID();
  a.setRadius(Radius_a);
  a.getArea();
  a.show();

  b.setID(ID_b);
  b.getID();
  b.setRadius(Radius_b);
  b.getArea();
  b.show();


  //-------- Implement here ---------//
  // compare circles and print out which circle is bigger.
  // Do pay attention the spelling and blank.

  if (a.getArea() > b.getArea()){
    std::cout << "Circle " << a.getID() <<" is " << "bigger than Circle "<< b.getID() << std::endl; 
  }
  else if(a.getArea() < b.getArea()){
    std::cout << "Circle " << b.getID() <<" is " << "bigger than Circle "<< a.getID() << std::endl; 
  }
  else{
    std::cout << "Circle " << a.getID() <<" is " << "equal to Circle "<< b.getID() << std::endl; 
  }








  return 0;
}
