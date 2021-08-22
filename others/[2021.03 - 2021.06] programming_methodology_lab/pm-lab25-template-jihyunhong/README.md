430.211 프로그래밍 방법론 : Template
========================================================
담당 조교 : 도완주    
이메일 : wj.doh@scale.snu.ac.kr     
2021년 5월 28일 월요일

## Introduction

템플릿은 '틀'을 의미합니다. 

붕어빵 틀을 한 번 떠올려보세요! 모양은 정해져있고, 속에 팥을 넣으면 팥 붕어빵, 슈크림을 넣으면 슈크림 붕어빵이 만들어지죠? 앞으로 배우게 될 C++에서의 템플릿도 이와 같습니다.

> **<')333><**
> 붕어빵 틀은 '붕어빵'을 만들어냅니다. '모양'은 결정되어있지만, '속에 넣을 내용물'은 정해져있지 않습니다.

템플릿은 (1) **함수 템플릿**과 (2) **클래스 템플릿**의 두 가지 종류가 있습니다.

## 1. Function template
함수 오버로딩을 사용하면 같은 이름의 함수에 다른 자료형의 인자를 넘겨줄 수 있었습니다.
하지만 함수 오버로딩을 같은 코드를 중복해서 작성해야한다는 단점이 있었습니다.
템플릿을 사용하면 함수 정의를 한 번만 하고도, 서로 다른 자료형에 대해 동작하는 함수를 작성할 수 있습니다.

* 함수템플릿은 **함수**를 만들어 냅니다. **함수의 기능**은 결정되어있지만, **자료형**은 정해져있지 않습니다.
* '함수를 만들어낸다'는 말이 아직은 알쏭달쏭하죠? 예시를 통해서 함수 템플릿을 이해해봅시다! 

``` c++
int add(int num1, int num2) {
  return num1 + num2;
}
```

이 함수의 **기능**은 **덧셈**이고, 대상 **자료형**은 **int형** 입니다.

이제 템플릿을 정의해볼까요?

``` c++
T add(T num1, T num2) {
  return num1 + num2;
}
```

이 함수 템플릿이 만들 수 있는 함수의 **기능**은 **덧셈**이고, 대상 **자료형**은 **결정되어 있지 않습니다.** 

하지만 위와 같이 작성하면 컴파일러 입장에서는 당황스럽겠죠? T가 무엇을 의미하는지 컴파일러는 아직 알지 못하기 때문에 이를 알려주는 문장(=template parameter declaration)을 함께 적어줘야합니다. 따라서 제대로 적은 함수 템플릿은 다음과 같습니다.

``` c++
template <typename T>    // Template Parameter declaration
T add(T num1, T num2) { 
  return num1 + num2;   
}
```

* **Template Type Parameter** 란, 템플릿에서 사용하는, 특정한 type이 아닌 모든 type을 대변할 수 있는 type parameter입니다.

  * 위의 코드에서는 **T**가 template type parameter이고, 관습적으로 'T'라는 문자를 사용한 것일 뿐 다른 문자를 사용하셔도 문제 없습니다.

  * 한 번에 여러개의 type parameters를 설정할 수 있습니다.

    ``` c++
    template <typename T1, typename T2>
    // template function here
    ```

  * `typename` 대신 `class`라고 쓰기도 합니다. 하지만 이 때 적은 `class`는 class-object에서의 class는 아닙니다! 
    * c++ 초창기에 템플릿 선언 키워드로 class만 사용할 수 있었는데, class-object에서의 class와 키워드가 동일하다는 지적에 의해 typename이라는 키워드도 함께 쓸 수 있도록 정정된 것이라고 합니다.
    * 하지만 typename보다 class가 더 입력하기 쉽기 때문에 여전히 많은 사람들이 class 키워드를 많이 사용한다고 합니다.

위에서 정의한 함수 템플릿을 이용해서 함수를 만들어볼까요?

``` c++
#include <iostream>

template <typename T>
T add(T num1, T num2) {
  return num1 + num2;
}

int main(void) {
  std::cout << add<int>(15, 20)        << std::endl;  // int형 덧셈을 진행하는 add함수
  std::cout << add<double>(3.14, 2.75) << std::endl;  // double형 덧셈을 진행하는 add함수
  std::cout << add<int>(6, 16)         << std::endl;
  return 0;
}
```

출력 결과

```
35
5.89
22
```

위의 코드를 조금 더 설명하자면, `add<int>(15, 20)` 이 부분에서 `<int>`를 통해 컴파일러는 함수 템플릿에서 `T` 를 `int` 로 바꾼 다음의 형태로 함수를 하나 만들게 됩니다.

``` c++
int add(int num1, int num2) {
  return num1 + num2;
}
```

마찬가지로 `add<double>(3.14, 2.75)` 를 마주치면 다음의 형태로 함수를 만들게 됩니다.

``` c++
double add(double num1, double num2) {
  return num1 + num2;
}
```

그럼 `add<int>(6, 16)` 을 마주치면 또 함수를 새로 만들까요? 그렇지는 않습니다. 한 번 함수가 만들어지면 그 다음에는 만들어진 함수를 호출할 뿐 새로 함수를 만들지는 않습니다. 즉, 함수는 자료형 당 최대 하나씩만 만들어집니다.

또, 컴파일 할 때 함수가 만들어진다면 속도가 느려지지않을까 궁금하실 겁니다. 컴파일 속도는 느려집니다! 하지만 실행 속도가 느려지는 것은 아니기 때문에 크게 신경쓸 요소는 아니라고 생각합니다.

### 함수 템플릿과 템플릿 함수

앞에서 작성한 함수 템플릿(function template)은 다음과 같습니다.

``` c++
template <typename T>
T add(T num1, T num2) {
  return num1 + num2;
}
```

한편, 위의 템플릿을 기반으로 컴파일러가 만들어 내는 다음 유형의 함수들은 **템플릿 함수(templated function)** 또는 function template instance라고 합니다.

``` c++
int add(int num1, int num2) {
  return num1 + num2;
}

double add(double num1, double num2) {
  return num1 + num2;
}
```

함수 템플릿과 템플릿 함수가 헷갈린다면 두 단어 중 **뒷부분**이 핵심이라는 것을 떠올리시면 헷갈리지 않을실겁니다. 

* 함수 **템플릿** 👉 "**템플릿**"인데 함수를 만드는데 사용되는 템플릿
* 템플릿 **함수** 👉 "**함수**"인데 템플릿을 기반으로 만들어진 함수

### 둘 이상의 type에 대해 템플릿 선언하기

``` c++
#include <iostream>

template <typename T1, typename T2>  // 둘 이상의 template type
void showData(double num) {
  std::cout << (T1)num << ", " << (T2)num << std::endl;
}

int main(void) {
  showData<char, int>(65);
  showData<char, int>(67);
  showData<char, double>(68.9);
  showData<short, double>(69.2);
  showData<short, double>(70.4);
  return 0;
}
```

출력결과

```
A, 65
C, 67
D, 68.9
69, 69.2
70, 70.4
```

### template type parameter

template type parameter에는 built-in type(char, int, double ...)뿐만 아니라 class와 같은 user-defined type도 대입 될 수 있습니다. 

* 하지만, user-defined type을 넣어주는 프로그램을 작성할 때에는 해당 type이 type parameter에 들어갔을 때, 제대로 적용이 되는지에 대한 검토가 필요합니다.
* 특히 Operator에서 에러가 발생하기 쉬운데, operator overloading을 통해서 해결 할 수 있습니다.

template type parameter에 user-defined class를 대입시켜봅시다! 따로 설명을 쓰지 않아도 충분히 이해하실 수 있으실 겁니다. :)

```c++
#include <iostream>

template <typename T>
const T& max(const T& x, const T& y) {
  return (x > y) ? x : y;    // 인자로 전달된 두 데이터 중 큰 값을 반환
}

class Account {
private:
  int balance;
public:
  Account(int balance) : balance(balance) { }
  
  friend bool operator>(const Account &acc1, const Account &acc2) {
    return (acc1.balance > acc2.balance);
  }
  void showBalance() const {
    std::cout << balance << std::endl;
  }
};

int main(void) {
  Account nickle(5);
  nickle.showBalance();
  
  Account dime(10);
  dime.showBalance();
  
  Account bigger(max(nickle, dime));
  bigger.showBalance();
  return 0;
}
```

### 함수 템플릿의 특수화 (Function template specialization)

함수 템플릿을 정의했지만, 특정한 type에 대해서는 기능을 따로 정의하고 싶을 때에 function template specialization을 사용합니다. 예시를 보며 설명드리겠습니다!

```c++
#include <iostream>

template <class T>
void print(T value) {       
  std::cout << value << '\n';
}       

template <>  // template <> 키워드로 선언합니다.
void print(double value) {  // double type에 대해서는 위에 작성한 함수 템플릿 대신 이 함수를 사용하도록 합니다.
  std::cout << std::scientific << value << '\n';
}

int main(void) {
  print(5);
  print(6.7);
  return 0;
}
```

* 출력 결과

```
5
6.700000e+00
```

double형 자료에 대해서는 scientific notation을 사용해 출력하도록 특수화했고, 의도한대로 결과가 잘 나왔습니다. :)


## 2. Class template

함수를 템플릿으로 정의했듯이 클래스도 템플릿으로 정의할 수 있습니다. 

Standard library에도 class template으로 작성된 경우가 많으며 대표적으로 vector가 class template를 사용해 작성되어있습니다.

클래스 템플릿의 정의 방법은 함수 템플릿과 동일합니다!

``` c++
#include <iostream>

template <typename T>
class Point {
private:
  T xpos, ypos;
public:
  Point(T x=0, T y=0) : xpos(x), ypos(y) { }
  void showPosition() const {
    std::cout << '[' << xpos << ", " << ypos << ']' << std::endl;
  }
};

int main(void) {
  Point<int> pos1(3, 4);
  pos1.showPosition();
  
  Point<double> pos2(2.4, 3.6);
  pos2.showPosition();
  
  Point<char> pos3('P', 'F');
  pos3.showPosition();
  
  return 0;
}
```

### 클래스 템플릿의 선언과 정의의 분리, 파일 분할

클래스 템플릿도 멤버함수를 클래스 외부에 정의할 수 있습니다!

위에서 예로 든 Point 클래스의 멤버함수를 클래스 외부에 정의해보면 다음과 같습니다.

``` c++
template <typename T> // 클래스 템플릿 선언
class Point {
private:
  T xpos, ypos;
public:
  Point(T x=0, T y=0); // 매개변수의 디폴트 값은 클래스 내에만 표시
  void showPosition() const;
};

template <typename T> // 함수 템플릿 선언
Point<T>::Point(T x, T y) : xpos(x), ypos(y) { }

template <typename T> // 함수 템플릿 선언
void Point<T>::showPosition() const {
  std::cout << '[' << xpos << ", " << ypos << ']' << std::endl;
}
```

기존에 했던 방법대로 파일을 분할해볼까요?

* PointTemplate.h

``` c++
#ifndef __POINT_TEMPLATE_H_
#define __POINT_TEMPLATE_H_
template <typename T>
class Point {
private:
  T xpos, ypos;
public:
  Point(T x=0, T y=0);
  void showPosition() const;
};
#endif
```

* PointTemplate.cpp

``` c++
#include <iostream>
#include "PointTemplate.h"

template <typename T> 
Point<T>::Point(T x, T y) : xpos(x), ypos(y) { }

template <typename T> 
void Point<T>::showPosition() const {
  std::cout << '[' << xpos << ", " << ypos << ']' << std::endl;
}
```

* PointMain.cpp

``` c++
#include <iostream>
#include "PointTemplate.h"

int main(void) {
  Point<int> pos1(3, 4);
  pos1.showPosition();
  
  Point<double> pos2(2.4, 3.6);
  pos2.showPosition();
  
  Point<char> pos3('P', 'F');
  pos3.showPosition();
}
```

기존에 하던 방식대로 헤더파일, 멤버함수 정의, 메인함수를 적절히 잘 나눈 것 같은데 컴파일을 해보면 문제가 발생합니다! 무엇이 잘못된 걸까요?

컴파일은 `.cpp` 파일만을 대상으로 이루어집니다. 컴파일 이후 링커에 의해 object file들이 모아져 하나의 유기적으로 연결된 실행파일이 만들어지죠. 기존에 작성하던 class 들은 **run time 에 인스턴스가 만들어지기 때문에** 인스턴스가 생성되는 시점에는 클래스의 선언만 있는 헤더파일(`.h`)과 클래스의 멤버 함수들의 정의가 있는 `.cpp` 파일, 그리고 main 함수가 있는 `.cpp` 파일이 이미 모두 링킹되어있는 상태입니다.

하지만 오늘 배운 템플릿 클래스는 **컴파일 시점에 인스턴스가 생성**됩니다. 따라서 main 함수가 있는 `PointMain.cpp` 파일은 `PointTemplate.h` 헤더파일만 알고, 멤버 함수가 정의되어있는 `PointTemplate.cpp` 파일은 모르는 상태에서 인스턴스를 생성하려해서 컴파일 에러가 발생하는 것이지요!

그렇다면 해결 방법은 무엇이 있을까요?

1. 클래스 템플릿의 정의부분을 담고 있는 `.cpp` 파일을 main 함수가 있는 `.cpp` 파일에 `#include` 합니다.
   * 위의 예제에서는 `PointMain.cpp` 파일에 `#include "PointTemplate.cpp"` 을 추가!
2. 헤터파일에 클래스 템플릿의 정의부분을 포함시킵니다.
   * 위의 예제에서는 `PointTemplate.cpp` 파일의 내용을 `PointTemplate.h` 에 포함시키고 `PointTemplate.cpp` 파일 제거

### 클래스 템플릿의 특수화 (Class Template Specialization)

앞서 배운 함수 템플릿의 특수화와 방법 및 개념이 매우 유사하기 때문에 어렵지 않게 배우실 수 있을겁니다!

함수 템플릿을 특수화하는 이유는 특정 자료형에 대해서 구분이 되는 다른 행동을 정의하기 위해서였습니다. 마찬가지로 클래스를 특수화하는 이유는 **특정 자료형을 기반으로 생성된 객체에 대해서 구분이 되는 다른 행동양식을 적용하기 위해서** 입니다.

다음과 같은 클래스 템플릿이 있다고 해봅시다.

``` c++
template <typename T>
class Simple {
public:
  T simpleFunc(T num) { ... }
};
```

이를 기반으로 int형에 대해 특수화를 진행해볼까요?

``` c++
template <> // 함수 템플릿의 특수화에서와 마찬가지로 template <> 키워드를 사용합니다.
class Simple<int> {
public:
  int simpleFunc(int num) { ... }
};
```

정말 간단하죠! 이제 `Simple<int> obj;` 이렇게 객체를 생성하면 특수화된 템플릿 클래스 `Simple<int>`를 대상으로 객체가 생성됩니다.

### 클래스 템플릿의 부분 특수화

이번에는 결정되지 않은 자료형이 1개보다 많은 경우에 부분적으로만 특수화를 진행하는 방법에 대해 배워보도록 하겠습니다.

``` c++
template <typename T1, typename T2>
class Simple {
  ...
};

template <>
class Simple<char, int> { // T1에 char형, T2에 int형이 대입된 경우 특수화
  ...
};

template <typename T1>
class Simple<T1, int> { // T2에 int형이 대입된 경우에만 특수화! --> 부분 특수화
  ...
};
```

