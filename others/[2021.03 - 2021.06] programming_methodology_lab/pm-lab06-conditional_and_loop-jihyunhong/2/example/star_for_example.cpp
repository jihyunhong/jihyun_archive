#include <iostream>
int main(){
    std::cout<<"enter the positive number n: ";
    int n;
    std::cin>>n;

    //print 1~n-1 *
    for(int i=1; i<=n-1; i++){
        for(int j=0; j<i; j++){// print * for j=0~i-1 i.e. i times..
            std::cout<<"*";
        }
        std::cout<<std::endl; //print new line
    }

    //print n~1 *
    for(int i=n; i>0; i--){
        for(int j=0; j<i; j++){// print * for j=0~i-1 i.e. i times..
            std::cout<<"*";
        }
        std::cout<<std::endl; //print new line
    }




    return 0;
}