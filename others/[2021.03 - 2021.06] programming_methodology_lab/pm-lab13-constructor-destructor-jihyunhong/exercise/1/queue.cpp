// TODO
#include <iostream>
#include "queue.h"
using namespace std;

// 생성자는 return 타입이 없음(그냥 없음.)
Queue::Queue() : size(5){
    this->arr = new int[size];  // 동적으로 메모리 공간 할당!
    for (int i=0; i<size; i++){
        arr[i] = i;
    }
    cout << "Queue: default constructor call" << endl;
}

Queue::Queue(int size) {
    this->arr = new int[size];  // 동적으로 메모리 공간 할당!
    this->size = size;

    for (int i=0; i<size; i++){
        int num;
        cout << "arr[" << i << "] = ";
        cin >> num;
        arr[i] = num;
    }
    cout << "Queue: parameter constructor call" << endl;
}

Queue::~Queue() {
    for (int i=0; i<size; i++){
        cout << arr[i] << " "; 
    }
    cout << endl;
    
    delete []arr;   // 동적으로 할당된 메모리 공간 소멸!
    cout << "Queue: destructor call" << endl;
}
