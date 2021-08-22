#include <iostream>
#include <cstdlib>
int main(){
    //srand(time(0));//to make truely random
    srand(10);
    int n=rand()%100;
    std::cout<<"find n which is 0~99"<<std::endl;
 
    int your_input;
    std::cout<<"your input: ";
    std::cin>>your_input;

    while(your_input!=n){
        if(your_input>n){
            std::cout<<your_input<<" is bigger than n"<<std::endl;
        }
        else if(your_input<n){
            std::cout<<your_input<<" is smaller than n"<<std::endl;
        }

        std::cout<<"please give new input: ";
        std::cin>>your_input;
    }
    std::cout<<"your input is "<<your_input<<" which is same with n: "<<n<<std::endl;
    
    return 0;
}