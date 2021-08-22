#include <iostream> 
#include "binary_search.hpp"
void Insertionsort(int* a, int n){
    //our goal is to sort n elements a[0]~a[n-1]
    for(int k=1; k<=n-1; k++){
        //Assume that k-sub array is sorted 
        //We will make (k+1)-sub array sorted

        //1. Find the appropriate index which is called as idx
        //s.t. a[k] will be inserted into idx
        int idx=0;
        int temp=a[k];
        while(idx<k){
            //this while loop will compare a[k] with a[0]~a[k-1]
            //if they find minimum idx s.t. a[idx]>=a[k]
            //it will exit the loop
            //else idx will be k 
            if(a[idx]>=temp){
                break;
            }
            idx++;
        }

        //2. Inserting the a[k] into a[idx]
        for(int j=k; j>idx; j--){
            //for j=k~idx+1
            //move (j-1)-th element to j-th element
            a[j]=a[j-1];
        }
        //then we will assign a[idx]=a[k];
        a[idx]=temp;
    }
}
int binary_search(int number, int* arr, int arr_length){//return idx if number exists, else return -1
    //initialization of min and max
    int min=0;
    int max=arr_length-1;
    
    while(min<=max){
        //idx is middle point
        int idx=(min+max)/2;
        if(arr[idx]>number){//if arr[idx]>number->change upper bound
            max=idx-1;
        }
        else if(arr[idx]<number){//if arr[idx]<number->change lower bound
            min=idx+1;
        }
        else{//we find the idx
            return idx;
        }
    }
    
    return -1;//number doesn't exist
}