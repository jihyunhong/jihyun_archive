#include <iostream>
int main(){
    std::cout<<"Your score: ";
    int n;
    std::cin>>n;
    if(n>=60){
        std::cout<<"A+"<<std::endl;
    }
    else if(n>=50){
        std::cout<<"B+"<<std::endl;
    }
    return 0;

}