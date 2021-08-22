#include <iostream>
#include "shape.hpp"
int main(){
    point_3D vertex4_1, vertex4_2, vertex4_3, vertex4_4, vertex5_1, vertex5_2, vertex5_3, vertex5_4;
    vertex4_1.x=1.1; vertex4_1.y=-1; vertex4_1.z=0;
    vertex4_2.x=12.3; vertex4_2.y=8.7; vertex4_2.z=2.0/7.0;
    vertex4_3.x=3.0; vertex4_3.y=-19; vertex4_3.z=2.65;
    vertex4_4.x=-2.0/19.0; vertex4_4.y=3.1; vertex4_4.z=4.3;
    
    vertex5_1.x=3.87; vertex5_1.y=-2; vertex5_1.z=1;
    vertex5_2.x=2.9; vertex5_2.y=4.5; vertex5_2.z=13.5/4.9;
    vertex5_3.x=1.2; vertex5_3.y=-0.2; vertex5_3.z=1.2/199.0;
    vertex5_4.x=-2.13; vertex5_4.y=4.2321; vertex5_4.z=5.2;
    
    point_2D v_6_1, v_6_2, v_6_3;
    v_6_1.x= 1.2; v_6_1.y=2.1;
    v_6_2.x= -4.02; v_6_2.y=0.91;
    v_6_3.x= 7.0/13.0; v_6_3.y=8.098;

    Shape** shape_ptr=new Shape* [8];
    shape_ptr[0]=new Cylinder(); //3.14159
    shape_ptr[1]=new Cylinder(3.2, 2.3); //73.9908
    shape_ptr[2]=new Sphere(); //4.18879
    shape_ptr[3]=new Sphere(1.4); //11.494
    shape_ptr[4]=new Tetrahedron(vertex4_1, vertex4_2, vertex4_3, vertex4_4);//183.795
    shape_ptr[5]=new Tetrahedron(vertex5_1, vertex5_2, vertex5_3, vertex5_4);//14.6774
    shape_ptr[6]=new Prism();//0.5
    shape_ptr[7]=new Prism(v_6_1, v_6_2, v_6_3, 1.23);//19.7395

    for(int i=0; i<8; i++){
        shape_ptr[i]->print();
        std::cout<<shape_ptr[i]->getVolume()<<std::endl;
    }
    for(int i=0; i<8; i++){
        delete shape_ptr[i];
    }
    delete[] shape_ptr;
    
    return 0;
}