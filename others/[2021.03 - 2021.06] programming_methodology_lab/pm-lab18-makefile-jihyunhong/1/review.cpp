#include "review.h"

Review::Review() {} 

Review::Review(int* array, int len) {
    this -> len = len;
    this -> array = new int [this -> len];
    for (int i = 0; i < len; i++) 
        this->array[i] = array[i];
}

Review::Review(const Review &r) 
{ 
    std::cout<<"Copy constructor"<<std::endl; 
    len = r.len;
    array = new int [len];
    for (int i = 0; i < len; i++) 
        array[i] = r.array[i];
}
 
Review& Review::operator= (const Review &r) {
    std::cout<<"Assignment operator"<<std::endl;
    len = r.len;
    array = new int [len];
    for (int i = 0; i < len; i++) 
        array[i] = r.array[i];

    return *this;
} 

Review::~Review() {
    std::cout << "destructor" << std::endl;
    delete [] array;
}

void Review::view() {
    for(int i = 0; i < len; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}