#include <iostream>
int main(){
    std::cout<<"Is n prime(n=1~5)?"<<std::endl;
    std::cout<<"n: ";
    int n;
    std::cin>>n;
    switch(n){
        case 1:
            break;
        case 2:
        case 3:
            std::cout<<"n is prime"<<std::endl;
            break;
        case 4:
            break;
        case 5:
            std::cout<<"n is prime"<<std::endl;
            break;
        default:
            std::cout<<"out of range"<<std::endl;
    }
    return 0;
}