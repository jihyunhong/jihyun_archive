
# Pass/Return by Value, Pointer, Reference
담당조교 : 김종민 \
이메일 : jongmin.kim@scale.snu.ac.kr \
2021년 4월 9일 금요일

참고자료: learncpp.com Ch.9 & Ch.10
## References
* A reference is a type of C++ variable that acts as an `alias` to another object or value.
* & : "reference-to"
``` c++
int value = 8;
int &ref = value; // ref is a reference to value
cout << ref << endl;
cout << value << endl;
```
### References as alias(별명)
``` c++
int value = 8;
int &ref = value; // ref는 value를 지칭하는 또다른 이름
```
* **value와 ref를 &(address-of) operator로 확인해보면 동일한 주소가 출력됨.**
* Reference는 무조건 선언과 동시에 초기화 해야한다.
* 한번 정의된 reference는 다시 다른 변수에 할당할 수 없다.

### References as function parameters
* 함수의 인자로 reference 가 전달될 때는 변수가 복사되는 것이 아니기 때문에 \
    함수 내에서 수정되는 값을 함수의 밖에서도 유지될 수 있도록 한다.
* **함수의 인자로 reference를 사용하면 변수의 불필요한 복사를 필요로 하지 않기 \
    때문에 되도록 reference를 사용하여 전달하도록 한다.**

### Reference vs Pointer 
``` c++
int value{ 5 };
int *const ptr{ &value }; // ref는 한번 선언되면 재할당이 안되기 때문에 \ 
                            const pointer로 선언
int &ref{ value };
// ref = *ptr
```
* Reference가 선언 및 사용에 있어 제약이 많기 때문에 안전하기 때문에 특별한 경우를 제외하고는 reference를 선호.

### Member selection with pointers and references
* Member selection operator : `.`, `->`
``` c++
struct Person
{
    int age;
    double weight;
};
Person person; // define a person

// Member selection
person.age = 4;
Person &ref = person;
ref.age = 5;

Person *ptr = &person;
(*ptr).age = 3;
ptr->age = 2;
```
## Function parameters and arguments

* 본격적인 **function**에 대한 설명을 하기에 앞서 몇 가지의 용어들에 대해 설명.

### Parameters vs. Arguments

* 사실 *parameter*와 *argument*는 되게 혼용되서 쓰이는 단어이지만, 나중에 헷갈리지 않기 위해서는 둘의 차이를 명확히 알아두는 것이 좋음.

* **Function parameter** : *Function declaration*을 할 때 쓰이는 variable. 
  > *Formal parameter*라고도 불림.
```c++
void foo(int x); // declaration (function prototype) -- x is a parameter
 
void foo(int x) // definition (also a declaration) -- x is a parameter
{
}
```

* **Argument** : caller에 의해서 함수로 전달되는 value.
  > *Actual parameter*라고도 불림.
```c++
foo(6); // 6 is the argument passed to parameter x
foo(y+1); // the value of y+1 is the argument passed to parameter x
```

## Passing arguments by value

### Pass by value

```c++
include <iostream>
 
void foo(int y)
{
  std::cout << "y = " << y << '\n';
  
  y = 6;

  std::cout << "y = " << y << '\n';
} // y is destroyed here
 
int main()
{
  int x = 5;
  std::cout << "x = " << x << '\n';
 
  foo(x);
 
  std::cout << "x = " << x << '\n';
  return 0;
}
```

* 위 코드 실행결과는?
> x = 5   
> y = 5   
> y = 6   
> x = 5

### Pros and cons of pass by value

* 장점
  - Argument의 형식이 variable, literal, expression, struct, class 등등 어떤 것이 될 수 있음.
  - Original argument의 값이 함수 내부에서 바뀌지 않음.

* 단점
  - 만약에 argument의 형태가 size가 큰 struct나 class의 형태이고, function call이 자주 일어난다면 argument의 값이 parameter로 **복사**되는 과정에서 performance적으로 많은 penalty가 존재.

* 그렇다면 언제 **pass by value**를 이용해야되고, 어떤 경우에 이용하면 안될까?
  - 사용할 때 : Argument의 형태가 *fundamental data type* 또는 *enumerators*이거나, 아니면 argument의 값이 함수 내부에서 바뀌면 안되는 경우.
  - 사용하지 않는 것이 좋을 때 : Argument의 형태가 *struct*이거나 *class*인 경우. (std::arrary, std::vector, std::string 등의 경우 포함).

## Passing arguments by reference

```c++
void addOne(int &ref)
{
  ref = ref + 1;
}

int main()
{
  int value = 5;

  cout << "value = " << value << '\n';
  addOne(value);
  cout << "value = " << value << '\n';
  return 0;
}
```

* 위 코드의 실행 결과는?
> value = 5   
> value = 6

### Returning multiple values via out parameters

```c++ 
#include <iostream>
#include <cmath>    // for std::sin() and std::cos()
 
void getSinCos(double degrees, double &sinOut, double &cosOut)
{
  // sin() and cos() take radians, not degrees, so we need to convert
  static constexpr double pi { 3.14159265358979323846 }; // the value of pi
  double radians = degrees * pi / 180.0;
  sinOut = std::sin(radians);
  cosOut = std::cos(radians);
}
 
int main()
{
  double sin(0.0);
  double cos(0.0);
 
  // getSinCos will return the sin and cos in variables sin and cos
  getSinCos(30.0, sin, cos);
 
  std::cout << "The sin is " << sin << '\n';
  std::cout << "The cos is " << cos << '\n';
  return 0;
}
```
* 위 코드에서 `sinOut`과 `cosOut`과 같이 함수의 return값을 저장하고 있는 변수를 **out parameter**라고 함.

* 정말 불가피한 경우가 아니라면 이런 식으로 parameter를 이용해서 value를 return하는 것은 별로 좋은 방식이 아님.

### Pass by const reference

```c++
void foo(const int &x) // x is a const reference
{
  x = 6;  // compile error: a const reference cannot have its value changed!
}
```

* **Pass by reference**방식을 사용할 때, argument의 값이 바뀔 필요가 없다면 무조건적으로 **pass by const reference**방식을 사용할 것을 권장.
* Pass by value처럼 original argument의 값이 바뀔 걱정을 하지 않아도 되면서 **복사**가 일어나지 않아 performance에 도움이 됨.

### Reference to pointers

```c++
#include <iostream>

void foo(int *&ptr) // pass pointer by reference
{
	ptr = nullptr; // this changes the actual ptr argument passed in, not a copy
}

int main()
{
	int x = 5;
	int *ptr = &x;
	std::cout << "ptr is: " << (ptr ? "non-null" : "null") << '\n'; // prints non-null
	foo(ptr);
	std::cout << "ptr is: " << (ptr ? "non-null" : "null") << '\n'; // prints null

	return 0;
}
```

```c++
#include <iostream>

// Note: You need to specify the array size in the function declaration
void printElements(int (&arr)[4])
{
  int length{ sizeof(arr) / sizeof(arr[0]) }; // we can now do this since the array won't decay

  for (int i{ 0 }; i < length; ++i)
  {
    std::cout << arr[i] << std::endl;
  }
}

int main()
{
    int arr[]{ 99, 20, 14, 80 };

    printElements(arr);

    return 0;
}
```
* Pointer에 대한 reference로 pass를 해야되는 경우도 있음. (Q: 어떤 경우가 있을까?)

### Pros and cons of pass by reference

* 장점
  - (물론 단점이 되기도 하지만) 어쨋든 함수 내부에서 argument의 값이 바뀔 수 있도록 해줌.
  - 복사본을 만드는 것이 아니기 때문에 performance적으로 이득임.
  - Multiple values를 return해줄 수 있음.
  - Reference는 항상 초기화되어야 하기 때문에, null value에 대한 걱정을 덜 수 있음.

* 단점
  - 4번째 장점으로 인해서 오히려 함수로 전달되는 argument가 normal variable로 한정되는 문제가 생김.
  - 3번째 장점으로 인해서 오히려 제 3자로 하여금 parameter가 input을 위한건지 output을 위한건지 헷갈리게 할 수 있음.
  - 함수를 call할 때는 pass by value방식이나 pass by reference방식이나 형태가 똑같기 때문에 어떤 방식으로 함수를 call하는 것인지 알려면, 함수가 declare되어 있는 부분을 직접 봐야되는 불편함이 존재.

* 그렇다면 언제 **pass by reference**를 이용해야되고, 어떤 경우에 이용하면 안될까?
  - 사용할 때 : Struct/class를 넘기거나, argument의 값을 함수 안에서 바꾸어야될 필요성이 있거나, fixed array의 type information에 접근해야될 필요성이 있을 때.
  - 사용하지 않는 것이 좋을 때 : Argument가 굳이 함수 내에서 바뀔 필요 없을 때. (이 경우는 **pass by value** 또는  **pass by const reference** 사용).

## Passing arguments by address (pointer)

* 변수 그 자체가 아닌 변수의 주소를 넘기는 방식.

```c++
#include <iostream>

void foo(int *ptr)
{
  *ptr = 6;
}

int main()
{
  int value = 5;

  std::cout << "value = " << value << '\n';
  foo(&value);
  std::cout << "value = " << value << '\n';
  return 0;
}
```

* **Passing arguments by address**를 사용할 때는 넘겨주는 argument가 가리키고 있는 주소가 null pointer가 아닌지 체크하는 것이 중요. 왜냐하면 역참조를 할 때 만약에 해당 주소가 null pointer라면 error가 발생되기 때문.
* 위의 코드에서 ptr이 nullptr이면 **Segmentation Fault** 발생!
```c++
void printArray(int *array, int length)
{
  // if user passed in a null pointer for array, bail out early!
  if (!array)
    return;

  for (int index=0; index < length; ++index)
    cout << array[index] << ' ';
}

int main()
{
  int array[6] = { 6, 5, 4, 3, 2, 1 };
  printArray(array, 6);
}
```

* **Passing arguments by reference**일 때와 마찬가지로 parameter를 `const`로 선언 가능.
```c++
void printArray(const int *array, int length)
{
  // if user passed in a null pointer for array, bail out early!
  if (!array)
    return;

  for (int index=0; index < length; ++index)
    std::cout << array[index] << ' ';
}

int main()
{
  int array[6] = { 6, 5, 4, 3, 2, 1 };
  printArray(array, 6);
}
```
* Q: const int* 와 int* const는 어떻게 다를까?

### Arguments are actually passed by value

```c++
#include <iostream>

void setToNull(int *tempPtr)
{
  // we're making tempPtr point at something else, not changing the value that tempPtr points to.
  tempPtr = nullptr; // use 0 instead if not C++11
}

int main()
{
  // First we set ptr to the address of five, which means *ptr = 5
  int five = 5;
  int *ptr = &five;

  // This will print 5
  std::cout << *ptr;

  // tempPtr will receive a copy of ptr
    setToNull(ptr);

  // ptr is still set to the address of five!

  // This will print 5
  if (ptr)
    std::cout << *ptr;
  else
    std::cout << " ptr is null";

  return 0;
}
```

* 위 코드 실행 결과는?
  > 55

* 만약에 원하는 결과가 "5 ptr is null"이라면 **pass by reference to pointer**를 사용!

```c++
#include <iostream>

void setToSix(int *tempPtr)
{
  *tempPtr = 6; // we're changing the value that tempPtr (and ptr) points to
}

int main()
{
  // First we set ptr to the address of five, which means *ptr = 5
  int five = 5;
  int *ptr = &five;

  // This will print 5
  std::cout << *ptr;

  // tempPtr will receive a copy of ptr
  setToSix(ptr);

  // tempPtr changed the value being pointed to to 6, so ptr is now pointing to the value 6

  // This will print 6
  if (ptr)
    std::cout << *ptr;
  else
    std::cout << " ptr is null";

  return 0;
}
```

* 위 코드 실행 결과는?
  > 56

### Pros and cons of pass by address (pointer)

* 장점
  - Argument의 값을 함수 안에서 바꿀 수 있음.
  - Argument의 내용에 대한 복사본이 생기지 않기 때문에 performace 측면에서 이득.
  - Out parameter를 통해서 여러 가지의 value를 return 가능.
* 단점
  - Literal과 같이 따로 주소를 가지고 있지 않은 표현들에 대해서는 **pass by address**를 사용하지 못함.
  - 혹시 null pointer를 전달하지는 않는지 계속 검사를 해주어야 함.
  - 어쨋든 주소를 한 번 거쳐서 value에 접근하는 것이기 때문에, **pass by value**에 비해서는 느림.

* 그렇다면 언제 **pass by address**를 이용해야되고, 어떤 경우에 이용하면 안될까?
  - 사용할 때 : Built-in array를 전달하거나, null pointer/pointer 구분이 명확할 때.
  - 사용하지 않는 것이 좋을 때 : null pointer/pointer 구분이 명확하지 않을 때, class/struct를 전달할 때(**pass by reference**사용), fundamental type을 전달할 때(**pass by value** 사용).

## Returning values by value, reference, and address

* Returning의 경우도 passing의 경우와 비슷하지만 추가적으로 조심해야 할 사항들이 존재.

### Return by value
```c++
int doubleValue(int x)
{
  int value{  x  *  2  };
  return value;  // A copy of value will be returned here
}  // value goes out of scope here
```
* 마찬가지로 값이 **복사**되어서 반환(return).
* 사용할 때
  - 함수 내부에서 선언된 변수의 값을 반환할 때
  - function argument로 들어온 값을 반환할 때
* 사용하지 않는 것이 좋을 때
  - array나 pointer를 반환할 때
  - 큰 사이즈의 struct나 class를 반환할 때

### Return by address (pointer)
* address (pointer)로 반환 시에는 해당 pointer가 가리키는 object가 duration이 끝나 (scope에서 벗어나) 파괴되지 않는지 조심해야 합니다.

```c++
int* doubleValue(int x)
{
  int value{ x * 2 };
  return &value;  // return value by address here
}  // value destroyed here
```
> 잘못된 사용례
```c++
int* allocateArray(int size)
{
  return new int[size];
}
int main()
{
  int *array{ allocateArray(25) };
  // do stuff with array
  delete[] array;
  return 0;
}
```
> 올바른 사용례: dynamic allocation된 object를 반환

* 사용할 때
  - dynamic allocate된 object를 반환할 때
  - pass by address로 전달된 function argument를 반환할 때
* 사용하지 않는 것이 좋을 때
  - 함수 내부에서 선언되거나 pass by value로 전달된 function argument를 반환할 때 (return by value 이용)
  - pass by reference로 전달된 function argument를 반환할 때 (return by reference 이용)

### Return by reference
* Return by address로 반환 시와 유사하게 reference가 가리키는 원래 object가 duration이 끝나 (scope에서 벗어나) 파괴되지 않는지 조심해야 합니다.

```c++
int& doubleValue(int x)
{
  int value{ x * 2 };
  return value;  // return value by reference here
}  // value destroyed here
```
> 잘못된 사용례

* Return by reference는 주로 **복사**를 하고 싶지 않을 때, class의 member function에서 많이 사용하게 됩니다.
* 사용할 때
  - reference parameter를 반환할 때
  - pass by address나 pass by reference로 전달된 function argument의 member를 반환할 때
  - function 반환 시 파괴되지 않을 큰 사이즈의 struct나 class를 반환할 때
* 사용하지 않는 것이 좋을 때
  - 함수 내부에서 선언되거나 pass by value로 전달된 function argument를 반환할 때 (return by value 이용)
  - built-in array나 pointer 값을 반환할 때 (return by address 이용)

## Inline functions

* Function call에도 overhead 존재. Function body가 길거나, 아니면 body의 code가 복잡한 경우, function call overhead가 function body를 수행하는 시간에 비해서 큰 비중을 차지하지 않음.

* 하지만 function body가 작거나, 수행하는 code가 매우 간단한 경우, 정작 함수의 body를 수행하는 시간보다 funcion call overhead가 더 큰 경우가 있음.

* 이러한 경우 `inline` keyword를 사용해서 이를 해결 가능.

```c++
int min(int x, int y)
{
  return x > y ? y : x;
}

int main()
{
  std::cout << min(5, 6) << '\n';
  std::cout << min(3, 2) << '\n';
  return 0;
}
```

```c++
inline int min(int x, int y)
{
  return x > y ? y : x;
}
```

```c++
int main()
{
  std::cout << (5 > 6 ? 6 : 5) << '\n';
  std::cout << (3 > 2 ? 2 : 3) << '\n';
  return 0;
}
```

* 하지만 modern compiler의 경우에는 개발자가 직접 함수를 `inline`으로 선언을 하지 않더라도 compiler가 알아서 짧은 길이의 function은 inline으로 처리해서 자동 최적화를 해줌.

## Structs

* **Struct** 는 structure의 약자로, 여러 variable들을 묶은 **aggregate data type**

* Struct라는 하나의 unit에 여러 type의 variable들을 그룹화할 수 있음.

* ```struct``` keyword 사용

* 생성된 Struct는 마치 int나 double과 같은 type처럼 사용 가능

```c++
#include <iostream>
#include <string>

using namespace std;

// Declaring and defining structs
struct Student
{
  std::string name{};
  std::string id{};
  int age{};
  double gpa{};
}; // 반드시 ';'으로 마무리

void printInformation(Student student);
Student gradeDown(Student student);

int main()
{
  // Initializing structs
  Student joonki{ "Lee Joon KI", "2018-17453", 22, 3.4 };
  Student shinhye{ "Park Shin Hye", "2016-18293", 24, 4.0 };
  // if we omit later parts. It will be initialized to default values
  Student noOne{ "No One", "2020-00000" };
  // initialized to: noOne.age = 0, noOne.gpu = 0.0

  // Accessing struct members
  joonki.gpa = 2.6;
  shinhye.gpa += 0.3;


  printInformation(joonki);
  cout << '\n';
  printInformation(shinhye);
  cout << '\n';

  shinhye = gradeDown(shinhye);
  printInformation(shinhye);
}


// 함수의 parameter로 struct 사용 가능
void printInformation(Student student)
{
    cout << "Name:   " << student.name << '\n';
    cout << "ID:   " << student.id << '\n';
    cout << "Age:  " << student.age << '\n';
    cout << "GPA: " << student.gpa << '\n';
}

// 함수의 return값도 struct로 가능
Student gradeDown(Student student)
{
  student.gpa -= 1.0;
  return student;
}
```
* '.' 기호를 이용해 struct의 member에 접근 가능
* ```student.gpa```처럼 사용 가능
* ```struct Student person1{"Name", "ID", 10, 4.0}``` 또는 ```struct Student person1 = {"Name", "ID", 10, 4.0}``` 이런 식으로 initialize(초기화) 가능

#### Nested Structs

* 생성한 struct도 하나의 data type이므로, struct내에 struct를 사용할 수 있다.

```c++
struct Employee
{
    short id;
    int age;
    double wage;
};

struct Company
{
    Employee CEO; // Employee is a struct within the Company struct
    int numberOfEmployees;
};

Company myCompany{{ 1, 42, 60000.0 }, 5 };
```

#### Struct Pointers
* 다른 type들처럼 pointer를 만들 수도 있음
```c++
// typical list implementation
struct Node {
  std::string value;
  Node* left{};
  Node* right{};
};

int main {
  Node* node1 = new Node("Rock", nullptr, nullptr);
  Node* node2 = new Node("Scissors", nullptr, nullptr);
  
  node2->left = node1;
  node1->right = node2;
  
  Node* node3 = new Node("Paper", node2, node1);
  node1->left = node3;
  
  //.|-- node1(Rock) ---- node2(Scissors) ---- node3(Paper) --|
  // |---------------------(connected)------------------------| 
  return 0;
}
```
* 예시로 위와 같은 간단한 pointer로 연결된 list를 만들 수 있다.
* '->' 기호를 사용해서 pointer가 가리키는 struct object의 member에 접근할 수 있다.
