#include <iostream>
int main(){
    std::cout<<"I want to get some of sqaures from 1 to n"<<std::endl;
    int n;
    std::cout<<"n: ";
    std::cin>>n;
    
    int sum=0;
    for(int i=1; i<=n; i++){
        sum+=(i*i);
    }
    std::cout<<"sum: "<<sum<<std::endl;

    return 0;
}