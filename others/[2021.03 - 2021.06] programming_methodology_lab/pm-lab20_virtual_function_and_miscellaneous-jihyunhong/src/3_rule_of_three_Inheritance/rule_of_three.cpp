#include <iostream> 
#include "rule_of_three.hpp"
//constructor
Base::Base(int n){
    std::cout<<"base class constructed"<<std::endl;
    this->base_n=n;
    this->base_array=new int [n];
}
Derived::Derived(int n){
    std::cout<<"derived class constructed"<<std::endl;
    this->derived_n=n;
    this->derived_array=new int [n];
}

//copy constructor
Base::Base(Base& b){
    std::cout<<"base class copied"<<std::endl;
    this->base_n=b.base_n;
    this->base_array=new int [b.base_n];
    for(int i=0; i<b.base_n; i++){
        this->base_array[i]=b.base_array[i];
    }
}
Derived::Derived(Derived& d): Base(d){
    std::cout<<"derived class copied"<<std::endl;
    this->derived_n=d.derived_n;
    this->derived_array=new int[d.derived_n];
    for(int i=0; i<d.derived_n; i++){
        this->derived_array[i]=d.derived_array[i];
    }
}

//assignment operator
Base& Base::operator=(Base const& b){
    std::cout<<"base class assigned"<<std::endl;
    if(this!=&b){
        this->base_n=b.base_n;
        for(int i=0; i<b.base_n; i++){
            this->base_array[i]=b.base_array[i];
        }
    }
    return *this;
}
Derived& Derived::operator=(const Derived& d){
    if(this!=&d){
        std::cout<<"derived class assigned"<<std::endl;
        Base::operator=(d);
        this->derived_n=d.derived_n;
        for(int i=0; i<10; i++){
            this->derived_array[i]=d.derived_array[i];
        }
    }
    return *this;
}

//destructor
Base::~Base(){
    std::cout<<"base class deleted"<<std::endl;
    delete[] (this->base_array);
}
Derived::~Derived(){
    std::cout<<"derived class deleted"<<std::endl;
    delete[] (this->derived_array);
}





void Derived::print_info(){
    std::cout<<"base array: ";
    for(int i=0; i<this->base_n; i++){
        std::cout<<(this->base_array[i])<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"derived array: ";
    for(int i=0; i<this->derived_n; i++){
        std::cout<<(this->derived_array[i])<<" ";
    }
    std::cout<<std::endl;
}