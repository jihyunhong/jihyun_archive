#include "shape.hpp"
point_3D operator-(point_3D& A, point_3D& B){
    point_3D v;
    v.x=A.x-B.x;
    v.y=A.y-B.y;
    v.z=A.z-B.z;
    return v;
}

point_2D operator-(point_2D& A, point_2D& B){
    point_2D v;
    v.x=A.x-B.x;
    v.y=A.y-B.y;
    return v;
}

void Sphere::print(){
    //you should implement here
    std::cout<< "Sphere" << std::endl;
    return;
}
void Cylinder::print(){
    //you should implement here
    std::cout<< "Cylinder" << std::endl;
    return;
}
void Tetrahedron::print(){
    //you should implement here
    std::cout<< "Tetrahedron" << std::endl;
    return;
}
void Prism::print(){
    //you should implement here
    std::cout<< "Prism" << std::endl;
    return;
}

Sphere::Sphere(double r){
    this->radius=r;
}
Cylinder::Cylinder(double radius, double height){
    this->radius=radius;
    this->height=height;
}
Tetrahedron::Tetrahedron(point_3D vertex1, point_3D vertex2, point_3D vertex3, point_3D vertex4) {
    vertex[0] = vertex1;
    vertex[1] = vertex2;
    vertex[2] = vertex3;
    vertex[3] = vertex4;
}
Prism::Prism(point_2D base1, point_2D base2, point_2D base3, double height){
    base[0]=base1;
    base[1]=base2;
    base[2]=base3;
    this->height=height;
}

double Sphere::getVolume(){
    //you should implement here
    double result = (4/3.0) * M_PI * radius * radius * radius;
    return result;
}
double Cylinder::getVolume(){
    //you should implement here
    double result = M_PI * radius * radius * height;
    return result;
}
double Tetrahedron::getVolume(){
    //you should implement here
    point_3D OA = vertex[1] - vertex[0];
    point_3D OB = vertex[2] - vertex[0];
    point_3D OC = vertex[3] - vertex[0];
    point_3D external_product;
    external_product.x = OA.y * OB.z - OA.z * OB.y;
    external_product.y = OA.z * OB.x - OA.x * OB.z;
    external_product.z = OA.x * OB.y - OA.y * OB.x;

    double result = (1/6.0) * (external_product.x * OC.x + external_product.y* OC.y + external_product.z * OC.z);
    result = std::fabs(result);
    return result;
}

double Prism::getVolume(){
    //you should implement here
    point_2D OA = base[1]- base[0];
    point_2D OB = base[2] - base[0];

    double result = std::fabs(0.5 * (OA.x * OB.y - OA.y * OB.x));
    return result * height;
}


