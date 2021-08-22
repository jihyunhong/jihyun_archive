#include "shape.hpp"

point_2D operator-(point_2D& A, point_2D& B){
    point_2D v;
    v.x=A.x-B.x;
    v.y=A.y-B.y;
    return v;
}

void Triangle::print(){
    std::cout<<"Triangle"<<std::endl;
}
void Circle::print(){
    std::cout<<"Circle"<<std::endl;
}

Triangle::Triangle(point_2D vertex1, point_2D vertex2, point_2D vertex3){
    vertex[0]=vertex1;
    vertex[1]=vertex2;
    vertex[2]=vertex3;
}
Circle::Circle(double radius){
    this->radius=radius;
}

double Triangle::getArea(){
    point_2D vec1=vertex[1]-vertex[0];
    point_2D vec2=vertex[2]-vertex[0];
    double area=0.5*((vec1.x)*(vec2.y)-(vec2.x)*(vec1.y));
    if(area<0){
        area=-area;
    }
    return area;
}
double Circle::getArea(){
    return M_PI*radius*radius;
}


