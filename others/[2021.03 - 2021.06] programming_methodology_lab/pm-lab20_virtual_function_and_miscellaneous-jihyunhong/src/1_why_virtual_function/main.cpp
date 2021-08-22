#include <iostream>
class A{
public:
            void print(){std::cout<<"class A"<<std::endl;}
};
class B: public A{
public:
            void print(){std::cout<<"class B"<<std::endl;}
};
class C: public B{
public:
            void print(){std::cout<<"class C"<<std::endl;}
};
class D: public C{
public:
            void print(){ std::cout<<"class D"<<std::endl;}
};
int main(){
    A* X=new C;
    std::cout<<"result for X->print() is ";
    X->print();
    delete X;
}
