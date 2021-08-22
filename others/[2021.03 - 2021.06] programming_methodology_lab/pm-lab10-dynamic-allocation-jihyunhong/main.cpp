#include <iostream>

//check through valgrind
int main(){
    int n;
    std::cout<<"enter the number: ";
    std::cin>>n;
    int **a;
    a = new int*[n];
    for (int i=0; i<n; i++){
        a[i] = new int[i+1];
    }

    // you should implement the code here
    // you will get the chunk from heap
    // a[i] will be pointer which points the array of length i+1 (i=0~n-1)
   
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            a[i][j] = i+j;
        }
    }

    for(int i=0; i<n; i++){ //print a[i][j] for all i=0~n-1, j=0~i as TA has done in PPT 
        for(int j=0; j<=i; j++){
            std::cout<<a[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    //You must deallocate all the chunks from heap
    for (int i=0; i<n; i++){
        delete [] a[i];
    }
    delete [] a;

    return 0;
}