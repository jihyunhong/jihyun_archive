#include <iostream>
#include "binary_search.hpp"
int main(){
    int A[]={12, 33, 72, 41, 93};
    int G[]={4, 2, 7, 0, 2};
    Insertionsort(A, 5);
    Insertionsort(G, 5);

    std::cout<<binary_search(11, A, 5)<<std::endl;
    std::cout<<binary_search(12, A, 5)<<std::endl;
    std::cout<<binary_search(15, A, 5)<<std::endl;
    std::cout<<binary_search(33, A, 5)<<std::endl;
    std::cout<<binary_search(41, A, 5)<<std::endl;
    std::cout<<binary_search(72, A, 5)<<std::endl;
    std::cout<<binary_search(93, A, 5)<<std::endl;
    //-1 0 -1 1 2 3 4
    std::cout<<binary_search(72, G, 5)<<std::endl;
    std::cout<<binary_search(0, G, 5)<<std::endl;
    std::cout<<binary_search(2, G, 5)<<std::endl;
    std::cout<<binary_search(4, G, 5)<<std::endl;
    std::cout<<binary_search(7, G, 5)<<std::endl;
    //-1 0 1or2 3 4
    return 0;
}
