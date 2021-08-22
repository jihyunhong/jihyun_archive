#include <iostream>
#include "shape.hpp"

int main(){
    Shape** shape_ptr_array=new Shape* [3];
    // shape_ptr_array[0]=new Shape; error.. Abstract Class
    shape_ptr_array[1]=new Triangle();
    shape_ptr_array[2]=new Circle();

    shape_ptr_array[1]->print();
    std::cout<<shape_ptr_array[1]->getArea()<<std::endl;
    shape_ptr_array[2]->print();
    std::cout<<shape_ptr_array[2]->getArea()<<std::endl;


    delete shape_ptr_array[0];
    delete shape_ptr_array[1];
    delete shape_ptr_array[2];
    delete[] shape_ptr_array;
}
