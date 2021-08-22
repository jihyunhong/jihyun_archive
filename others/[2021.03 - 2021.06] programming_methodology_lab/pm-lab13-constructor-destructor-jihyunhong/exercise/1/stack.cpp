// TODO
#include <iostream>
#include "stack.h"
using namespace std;

// 생성자는 return 타입이 없음(그냥 없음.)
Stack::Stack() : size(5){
    this->arr = new int[size];  // 동적으로 메모리 공간 할당!
    for (int i=0; i<size; i++){
        arr[i] = i;
    }
    cout << "Stack: default constructor call" << endl;
}

Stack::Stack(int size) {
    this->arr = new int[size];  // 동적으로 메모리 공간 할당!
    this->size = size;

    for (int i=0; i<size; i++){
        int num;
        cout << "arr[" << i << "] = ";
        cin >> num;
        arr[i] = num;
    }
    cout << "Stack: parameter constructor call" << endl;
}

Stack::~Stack() {
    for (int i=size-1; i>=0; i--){
        cout << arr[i] << " ";
    }
    cout << endl;
    delete []arr;   // 동적으로 할당된 메모리 공간 소멸!
    cout << "Stack: destructor call" << endl;
}