#include <iostream>
int main(){
    std::cout<<"enter the positive number n: ";
    int n;
    std::cin>>n;


    /*make the program which prints
    ******* (number of is n)
     **...* (one blank in the left)
      *...* (two blanks in the left)
    ...
          * (n-1 blanks in the left)
    
    you should implement below*/
    int i, j;
    for (i=0; i<n; i++){
      for (j=0; j<n; j++){
        if (j < i){
          std::cout << " ";
        }
        else{
          std::cout << "*";
        }
      }
    std::cout << std::endl;
    }

    return 0;
}
