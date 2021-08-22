#include <cmath>
#include <iostream>
class point_2D{
public:
    point_2D(double x=0, double y=0){
        this->x=x;
        this->y=y;
    }
    double x, y;
};
point_2D operator-(point_2D& A, point_2D& B);

class Shape{
public:
    virtual void print()=0;
    virtual double getArea()=0;
};
class Triangle: public Shape{
public:
    Triangle(point_2D vertex1={0, 0}, point_2D vertex2={0, 1}, point_2D vertex3={1, 0});
    virtual void print();
    virtual double getArea();
    //parameters for triangle
    
    point_2D vertex[3];
};
class Circle: public Shape{
public:
    Circle(double radius=1);
    virtual void print();
    virtual double getArea();

    //parameters for circle
    double radius;
};