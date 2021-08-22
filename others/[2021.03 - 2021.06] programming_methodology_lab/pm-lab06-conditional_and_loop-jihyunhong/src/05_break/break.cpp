#include <iostream>
#include <cstdlib>
int main(){
    for(int i=0; i<=10; i++){
        for(int j=0; j<=10; j++){
            std::cout<<"("<<i<<", "<<j<<")"<<" ";
            if(i+j==10){
                break;//will it end at (10, 0) or just end for corresponding i?
            }
        }
        std::cout<<std::endl;
    }
    return 0;
}