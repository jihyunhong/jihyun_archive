#include <iostream>
#include "rule_of_three.hpp"
int main(){
    std::cout<<"X generated"<<std::endl;
    Derived X;
    for(int i=0; i<10; i++){
        X.base_array[i]=i*i; X.derived_array[i]=i+100;
    }
    X.print_info();

    std::cout<<"Y copied"<<std::endl;
    Derived Y=X;
    Y.print_info();
    
    std::cout<<"Z assigned"<<std::endl;
    Derived Z;
    Z=X;
    Z.print_info();

    std::cout<<"destructor"<<std::endl;
    Base* A=new Derived; 
    delete A; //this case is problematic..
    //without virtual destructor, destructor won't be seen with object's perspective
    Base* B=new Base;
    delete B;
    Derived* C=new Derived;
    delete C;
    std::cout<<"destructor end"<<std::endl;
    return 0;
}
