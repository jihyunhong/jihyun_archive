# 430.211 프로그래밍 방법론 LAB 10 : Dynamic Allocation
담당조교 : 함도규   
이메일 : hdk971110@scale.snu.ac.kr     
2021년 4월 05일 월요일

## Introduction
Chapter 9.13-14에 해당하는 dynamic allocation에 대한 내용을 다루고 실습을 해보도록 한다.

## Dynamic memory allocation(P.6.9 ~ P.6.9a)
* 지금까지는 고정된, 미리 정해진 크기의 array를 배움.
* 정해진 크기의 array를 사용하면 프로그램이 동작하는 동안 필요한 max 크기만큼을 잡아야한다.
* 배열의 크기를 그때그때 상황에 맞게 딱 필요한 만큼만 정의해서 사용하고 싶다. --> `Dynamic Memory Allocation`
``` c++
// SINGLE VARIABLE
// allocating
int *ptr = new int;
// delete
delete ptr;
ptr = 0; // could be NULL or nullptr
// initialization
int *ptr1{ new int(5) };
int *ptr2{ new int{6} };

// ARRAY ALLOCATION
// allocating
int *array{ new int[length]{} };
// delete
delete[] array;
```
### Dangling pointer
* 아무것도 가리키고 있지 않은 pointer
* delete 이후의 포인터를 가리킴
* Dangling pointer의 연산 및 동작은 예측되지 않는 동작을 야기시킬 수 있다.

### Memory leak(메모리 누수)
* 동적 할당을 통해 메모리를 할당 후 delete하지 않으면, 결국엔 메모리가 부족할 수 있다.
* 이렇게 메모리가 계속 소비되면서 반환하지 않으면 메모리 누수가 생긴다.
* 할당된 메모리의 사용이 끝나면 반드시 delete해야 한다.
