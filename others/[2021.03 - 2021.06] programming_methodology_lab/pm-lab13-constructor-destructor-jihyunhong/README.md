430.211 프로그래밍 방법론 : Constructor, Destructor and the hidden "this" pointer
========================================================
담당 조교 : 도완주    
이메일 : wj.doh@scale.snu.ac.kr         
2021년 4월 16일 금요일      

참고자료

* learncpp.com chapter 11.5 ~ 11.10
* 열혈 C++ 프로그래밍 Chapter 04



## Introduction

객체가 생성될 때 자동으로 호출되는 "생성자"와 객체가 소멸될 때 자동으로 호출되는 "소멸자"를 작성하는 방법에 대해 배워보도록 하겠습니다.
또한, 멤버 함수 내에서 사용할 수 있는 **this**라는 이름의 포인터에 대해 알아보도록 하겠습니다! :surfer:

## 1. Constructors

### 1) Constructor

Constructor란 **객체가 처음 생성될 때 자동으로 호출**되는 special member function으로, 생성자를 잘 작성해두면 **객체의 생성과 동시에 원하는 값으로 멤버 변수를 초기화** 할 수 있습니다.

Constructor는 보통의 멤버 함수들과는 달리, 몇 가지 규칙이 있습니다!

1. Constructor의 이름은 반드시 class의 이름과 동일해야 합니다.
2. Constructor는 return type이 없습니다. (void도 아닙니다! 그냥 없습니다!)

Constructor는 다음과 같은 특징이 있습니다.

1. 객체가 생성될 때 **딱 한 번 호출**됩니다.
2. 생성자도 함수의 일종이므로 **오버로딩**이 가능합니다.
3. 매개변수에 **default argument**를 설정할 수도 있습니다!

``` c++
class SimpleClass {
private:
  int num;
public:
  SimpleClass(int n) { num = n; } // return type이 없고, 함수의 이름이 class의 이름과 동일합니다. --> 이 클래스의 생성자(Constructor)!!
};
```

### 2) Default Constructor

Default Constructor란 **parameter가 없는 생성자**를 의미합니다. 아무런 argument 없이 객체를 생성하면 자동으로 default constructor가 호출됩니다.

프로그래머가 아무런 생성자도 정의해두지 않으면 *"아무런 parameter도 받지 않고, 아무런 연산도 수행하지 않는"* `SimpleClass() {}` 이런 모양의 default constructor가 자동으로 추가됩니다.

### 3) Other Overloaded Constructor

parameter를 가지는 constructor입니다. 객체가 생성될 때 넘겨준 인자에 맞는 함수의 원형을 찾아 해당 생성자를 호출합니다.

``` c++
class SimpleClass {
private:
  int num;
public:
  SimpleClass() { num = 0; } // default constructor를 overloading한 것
  SimpleClass(int n) { num = n; } // constructor with parameter
};

int main(void) {
  SimpleClass simple1;    // 인자가 없음 --> default constructor가 호출되고, num에는 0이 저장됩니다.
  SimpleClass simple2(5); // int형 인자가 있음 --> overloaded constructor가 호출되고, num에는 5가 저장됩니다.
}
```

### 4) Member Initializer Lists (MIL)

const로 선언되어있는 멤버 변수를 어떻게 초기화 할까요?

``` c++
class Something {
private:
  const int value;
public:
  Something() { value = 1; }
};
```

단순히 위와 같이 class를 정의하면 컴파일 과정에서 무시무시한 에러를 마주치게 됩니다!

> **error**: constructor for 'Something' must explicitly initialize the const member 'value'
> **error**: cannot assign to non-static data member 'value' with const-qualified type 'const int'

위와 같은 에러는 `const`로 선언된 멤버 변수 `value`에 값을 **대입**하려해서 발생한 에러입니다. 따라서 코드를 다음과 같이 수정해주면 에러가 발생하지 않게 됩니다.

``` c++
class Something {
private:
  const int value;
public:
  Something(): value(1) {}
};
```

> 이때 **` : value(1) {}`** 이 부분이 바로 member initializer list 입니다!!

*왜 에러가 사라진 걸까요?*

`Something() { value = 1; }` 이 생성자는 다음의 두 문장에 비유할 수 있습니다.

``` c++
int value;
value = 1;
```

반면, `Something() : value(1) {}` 이 생성자는 다음의 한 문장에 비유할 수 있습니다.

``` c++
int value = 1;
```

즉, member initializer list를 사용하면 **선언과 동시에 초기화**가 이루어집니다. 따라서 선언과 동시에 초기화해야하는 `const`멤버변수도 member initializer list를 사용해 초기화가 가능해진 것입니다!

> const가 아닌 멤버 변수들도 같은 방법으로 member initializer list를 사용해 초기화 할 수 있습니다 :)

### 5) member initializer list 예시

``` c++
#include <iostream>
class Rectangle {
private:
  const double m_length=1.0; // default value
  const double m_width=1.0;  // default value
public:
  Rectangle(double length, double width) : m_length(length), m_width(width) { } // argument를 받아 const로 선언되어있는 member variable 초기화
  Rectangle(double length) : m_length(length) { } // length만 인자로 받고, width는 default value로 초기화
  void print() {
    std::cout << "length: " << m_length << ", width: " << m_width << '\n';
  } 
};
 
int main() {
  Rectangle x(2.0, 3.0);
  x.print(); // length: 2, width: 3
 
  Rectangle y(4.0);
  y.print(); // length: 4, width: 1
 
  return 0;
}
```



## 2. Destrcutors

### 1) Destructor

객체가 생성될 때 자동으로 호출되는 것이 Constructor라면, 객체가 소멸될 때 자동으로 호출되는 것이 Destructor입니다.

Constructor와 마찬가지로, Destructor를 정의할 때에는 몇 가지 규칙이 있습니다.

1. 이름은 반드시 클래스의 이름 앞에 '~'가 붙은 형태여야 합니다.
   * class 이름이 `Student`라면, destructor 함수의 이름은 `~Student`
2. Return type이 없습니다! (생성자와 똑같죠?)
3. 매개변수는 반드시 void로 선언되어야 합니다. 따라서 오버로딩도, default argument 설정도 불가능합니다!

### 2) Destructor는 왜 사용할까요?

소멸자는 주로 생성자에서 할당한 리소스의 소멸에 사용됩니다. 예를 들어, 생성자에서 new 연산자를 이용해 동적으로 메모리를 할당했다면 소멸자에서 delete 연산자를 이용해 해당 메모리 공간을 소멸해줍니다!

``` c++
class IntArray {
private:
  int* array;
  int length;
public:
  /* 생성자 */
  IntArray(int length) {
    this->array = new int[length]; // 동적으로 메모리 공간 할당!
    this->length = length;
  }
  /* 소멸자 */
  ~IntArray() {
    delete []array; // 동적으로 할당한 메모리 공간 소멸!
  }
};
```



## 3. The Hidden "this" Pointer

### 1) this pointer?

* **`this`** pointer는 **함수를 호출한 객체의 주소 값을 저장해둔 포인터**입니다. (말 그대로 **이것!** 을 가리키는 포인터입니다.)
* 다음의 코드를 통해 this pointer에대해 더 자세히 알아봅시다!

``` c++
#include <iostream>

class Simple {
private:
  int myData;
public:
  Simple(int data) { myData = data; }
  void setData(int data) { myData = data; } 
  // 👉 void setData(Simple* const this, int data) { this->myData = data; }
  int getData() { return myData; }
};

int main(void) {
  Simple A(1); 
  A.setData(2); 
  // 👉 setData(&A, 2);
  std::cout << A.getData() << std::endl;
  
  return 0;
}
```

* 위의 코드에서 `A.setData(2);` 이 부분을 보시면, 인자를 `2` 하나만 넘겨준 것 같지만 컴파일 과정에서 `setData(&A, 2);` 이렇게 객체의 주소값을 함께 넘겨주는 코드로 바뀌게 됩니다.
* 또한 멤버 함수도 `void setData(int data) { myData = data; }` 이 부분이 `void setData(Simple* const this, int data) { this->myData = data; }` 이렇게 바뀌게 됩니다. 
* 정리하자면, `A.setData(2);`는 `setData(&A, 2);`로 변환되어 호출되고, 객체 A의 주소값(`&A`)이 `setData`함수의 인자로 넘어가 `this` pointer에 저장되는 것입니다!
* 따라서 `setData` 함수에서 `this` 포인터를 사용해 객체 자신의 멤버 변수에 접근할 수 있습니다.

### 2) this pointer는 언제나 함수를 호출한 객체를 가리킵니다.

``` c++
int main(void) {
  Simple A(1);  // this = &A inside the Simple constructor
  Simple B(2);  // this = &B inside the Simple constructor
  A.setData(3); // this = &A inside member function setData
  B.setData(4); // this = &B inside member function setData
  
  return 0;
}
```

### 3) this pointer의 활용

1. 멤버변수(member variable)의 이름과 매개변수(parameter)의 이름이 같은 경우

   ``` c++
   class Something {
   private:
     int data;
   public:
     Something(int data) {
       this->data = data; // this->data is the member, data is the local parameter
     }
   };
   ```

   * 위의 코드를 보시면, Constructor의 매개변수 이름도 `data`이고 Something 객체의 멤버 변수 이름도 `data`입니다.

   * 이런 경우 this 포인터를 사용해 멤버 변수와 매개 변수를 구분할 수 있습니다.

     > 이제 더이상 멤버 변수의 이름과 매개 변수의 이름을 다르게 하기위해 창의력을 발휘할 필요가 없어졌습니다! :grin:

2. self-reference의 반환 :point_right: "chainable" function!

   * self-reference란 객체 자신을 참조할 수 있는 참조자를 의미합니다. 우리는 this 포인터를 이용해서 객체가 자신의 참조에 사용할 수 있는 참조자의 반환문을 구성할 수 있습니다.
   * 0으로 초기화된 객체에 5를 더하고 3을 빼고 4를 곱하는 작업을 생각해봅시다.

   ``` c++
   class Calc {
   private:
     int value;
   public:
     Calc() { value = 0; }
     void add(int value) { this->value += value; }
     void sub(int value) { this->value -= value; }
     void mult(int value) { this-> value *= value; }
     int getValue() { return value; }
   };
   ```

   * 위와 같이 클래스가 구성되어있다면, main함수는 다음과 같아야 할 것입니다.

   ``` c++
   #include <iostream>
   int main(void) {
     Calc calc;
     calc.add(5);  // returns void
     calc.sub(3);  // returns void
     calc.mult(4); // returns void
     std::cout << calc.getValue() << std::endl;
     
     return 0;
   }
   ```

   * 하지만, 만약 위의 멤버함수들이 **객체 자신의 참조자를 반환**하도록 함수를 재구성한다면 코드는 훨씬 간단해집니다!

   ``` c++
   #include <iostream>
   
   class Calc {
   private:
     int value;
   public:
     Calc() { value = 0; }
     Calc& add(int value) { this->value += value; return *this; }
     Calc& sub(int value) { this->value -= value; return *this; }
     Calc& mult(int value) { this-> value *= value; return *this; }
     int getValue() { return value; }
   };
   
   int main(void) {
     Calc calc;
     calc.add(5).sub(3).mult(4); // 3줄이었던 코드가 1줄로 줄어들었다!
     std::cout << calc.getValue() << std::endl;
     
     return 0;
   }
   ```

   * `calc.add(5).sub(3).mult(4);` 
     * 먼저 `calc.add(5)`가 호출됩니다. `add` 멤버 함수로 인해 `calc`의 멤버 변수 `value`의 값은 `5`가 됩니다. `value`가 저장되면 `*this`를 반환합니다. 이는 `calc` 객체의 참조자로 다음 연산에 사용됩니다.
     * `value`에 `5`가 더해진 `calc` 객체의 참조가 반환되어 `calc.sub(3)`이 호출됩니다. 마찬가지로 연산이 이루어지고 `value`의 값이 `2`인 객체의 참조형을 반환합니다.
     * 마지막으로 `calc.mult(4)`가 호출되어 최종적으로 `calc` 객체에 `value`는 `8`이 저장됩니다.
   * 위와같이 self-reference를 반환해 다른 멤버 함수를 계속해서 이어 붙일 수 있는 함수를 ***chainable function***이라 부릅니다.

