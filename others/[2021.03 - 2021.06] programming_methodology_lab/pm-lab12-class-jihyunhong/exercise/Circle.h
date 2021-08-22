#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>

class Circle
{
private: 
  int ID;
  double Radius;

public:
  void setID(int id);
  void setRadius(int radius);
  int getID();
  double getArea();
  void show();
};

#endif