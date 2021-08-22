#include <iostream>

#include "review.h"

// don't modify main.cpp

int main() 
{
    int *array;
    int len = 4;
    array = new int [4];
    for (int i = 0; i < len; i++)
        array[i] = i;

    // Look here //
    // Think of differences between line 18 and line 19 //
    Review t1(array, len), t2;
    t2 = t1; 
    Review t3 = t1;

    t1.view();
    t2.view();
    t3.view();

    delete [] array;

    return 0; 
} 