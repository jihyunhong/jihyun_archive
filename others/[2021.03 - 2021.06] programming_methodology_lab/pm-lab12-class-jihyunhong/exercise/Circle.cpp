#include "Circle.h"

void Circle::setID(int id)
{
  //Implement here
  ID = id; 
}

void Circle::setRadius(int radius)
{
  //Implement here
  Radius = radius;
}

int Circle::getID()
{
  //Implement here
  return ID;
}

double Circle::getArea()
{
  //Implement here
  //pi = 3.14
  return Radius * Radius * 3.14;

}
void Circle::show()
{
  //Implement here
  //Do pay attention the spelling and blank 
  std::cout << "Area of circle " << getID() << " is " << getArea()<< std::endl; 

}