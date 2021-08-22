#include "Insertionsort.h"
#include <iostream>

void print_array(int a[], int n){
    for(int i=0; i<n; i++){
        std::cout<<a[i]<<" ";
    }
    std::cout<<std::endl;
}
int main(){

    int a[]={12, 33, 72, 41, 93};
    int b[]={7, 3, 1, 9, 2};
    int c[]={1, 3, 2, 8, 0};

    Insertionsort(a, 5);
    Insertionsort(b, 5);
    Insertionsort(c, 5);

    print_array(a, 5);
    print_array(b, 5);
    print_array(c, 5);
    return 0;

}