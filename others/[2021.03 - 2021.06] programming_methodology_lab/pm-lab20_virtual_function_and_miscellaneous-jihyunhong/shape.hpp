#include <cmath>
#include <iostream>
class point_3D{
public:
    point_3D(double x=0, double y=0, double z=0){
        this->x=x; this->y=y; this->z=z;
    }
    
    double x, y, z;
};
point_3D operator-(point_3D& A, point_3D& B);

class point_2D{
public:
    point_2D(double x=0, double y=0){
        this->x=x; this->y=y;
    }
    double x, y;
};
point_2D operator-(point_2D& A, point_2D& B);



class Shape{
public:
    virtual void print()=0;
    virtual double getVolume()=0;
};

class curved_shape: public Shape{
public:
    virtual void print(){
        std::cout<<"curved shape"<<std::endl;
    }
};

class polyhedral: public Shape{
public:
    virtual void print(){
        std::cout<<"polyhedral"<<std::endl;
    }
};

class Sphere: public curved_shape{
public:
    Sphere(double radius=1);
    virtual void print();
    virtual double getVolume();

    //parameter's for shape
    double radius;
};

class Cylinder: public curved_shape{
public:
    Cylinder(double radius=1, double height=1);
    virtual void print();
    virtual double getVolume();

    //parameter's for shape
    double radius;
    double height;
};

class Tetrahedron: public polyhedral{
public:
    Tetrahedron(point_3D vertex1={0, 0, 0}, point_3D vertex2={0, 0, 1}, point_3D vertex3={0, 1, 0}, point_3D vertex4={1, 0, 0});
    virtual void print();
    virtual double getVolume();

    //parameter's for shape
    point_3D vertex[4];
};

class Prism: public polyhedral{
public:
    Prism(point_2D base1={0, 0}, point_2D base2={1, 0}, point_2D base3={0, 1}, double height=1);
    virtual void print();
    virtual double getVolume();

    //parameter's for shape
    point_2D base[3];
    double height;
};