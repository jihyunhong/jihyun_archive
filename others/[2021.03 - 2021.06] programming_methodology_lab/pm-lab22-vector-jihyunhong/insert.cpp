#include "insert.h"

void Insert2Array(int *&array, int arraylen, int number)
{
    int *array2 = new int[arraylen+1];

    for (int i=0; i<arraylen; i++){
        array2[i] = array[i];
    }
    // 4
    // 0 1 2 3 4 5
    // 1 3 5 7 9
    int index; // 2
    for (int i=0; i<arraylen; i++){
        if (array2[i] < number && number << array2[i+1]){
            index = i+1;
        }
    }

    for (int i=arraylen; i>index; i--){
        array2[i] = array2[i-1];
    }
    array2[index] = number;

    delete []array;
    array = array2;


    // // 새로운 array allocation
    // int *new_array = new int[arraylen+1];

    // // copy
    // int index;
    // for(int i = 0; i<arraylen; i++){
    //     new_array[i] = array[i];
    // }

    // for (int i=0; i<arraylen; i++){
    //     if (array[i] > number){
    //         index = i;
    //         break;
    //     }
    // }

    // for (int i=arraylen-1; i>=index; i--){
    //     new_array[i+1] = new_array[i];
    // }

    // new_array[index] = number;

    // delete []array;
    // array = new_array;
}

void Insert2Vector(std::vector<int> &vec, int number)
{
    // Implement here

    // 4
    // 0 1 2 3 4 5
    // 1 3 5 7 9
    
    // for (int i=0; i<vec.size(); i++){
    //     if (vec[i] < number && number < vec[i+1]){
    //         vec.insert(vec.begin()+i+1, number);
    //     }
    // }

    for (auto itr=vec.begin(); itr != vec.end(); itr++){
        if (*itr >= number){
            vec.insert(itr, number);
            break;
        }
    }
}
