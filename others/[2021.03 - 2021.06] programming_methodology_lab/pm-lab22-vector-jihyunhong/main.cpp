#include <iostream>
#include <vector>

#include "insert.h"
int main()
{
    /////////////////////////////////////////////
    // initial settings
    /////////////////////////////////////////////
    int arr_len = 5;
    int *arr_int = new int[arr_len];
    for (int i = 0; i < arr_len; i++)
        arr_int[i] = 2 * i + 1;
    std::vector<int> vec_int;
    for (int i = 0; i < arr_len; i++)
        vec_int.push_back(arr_int[i]);

    /////////////////////////////////////////////
    // print both arr_int and vec_int
    /////////////////////////////////////////////
    std::cout << "arr_int : ";
    for (int i = 0; i < arr_len; i++)
        std::cout << arr_int[i] << " ";
    std::cout << "\nvec_int : ";
    for (int i = 0; i < vec_int.size(); i++)
        std::cout << vec_int[i] << " ";
    std::cout << std::endl;

    // number to insert
    int new_number = 4;

    /////////////////////////////////////////////
    // insert new_number to both arr_int and vec_int
    /////////////////////////////////////////////
    Insert2Array(arr_int, arr_len, new_number);
    Insert2Vector(vec_int, new_number);

    /////////////////////////////////////////////
    // print both arr_int and vec_int
    /////////////////////////////////////////////
    std::cout << "Output of arr_int: ";
    for (int i = 0; i < arr_len + 1; i++)
        std::cout << arr_int[i] << " ";
    std::cout << "\nOutput of vec_int: ";
    for (int i = 0; i < vec_int.size(); i++)
        std::cout << vec_int[i] << " ";
    std::cout << std::endl;

    // free
    delete[] arr_int;

    return 0;
}
