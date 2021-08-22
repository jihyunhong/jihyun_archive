#include "Insertionsort.h"
void Insertionsort(int* a, int n){
    //Insertion sort will be implemented here
    int i, j, tmp;

    for(i=1; i<n; i++){
        tmp = a[i];
        for(j=i-1; j>=0 && a[j]>tmp; j--){
            a[j+1] = a[j];
        }
        a[j+1] = tmp;
    }
}
