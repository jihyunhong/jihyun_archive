#include <iostream>
class Base{
public:
    Base(int n=10);
    Base(Base& b);
    Base& operator=(Base const& b);
    virtual ~Base();


    int base_n;
    int* base_array; 
};
class Derived: public Base{
public:
    Derived(int n=10);
    Derived(Derived& d);
    Derived& operator=(const Derived& d);
    virtual ~Derived();
    void print_info();

    int derived_n;
    int* derived_array;
};