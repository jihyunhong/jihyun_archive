430.211 프로그래밍 방법론 : Object-oriented Programming 1
========================================================

담당 조교 : 남화용  

이메일 : hwayong.nam@scale.snu.ac.kr  

2021년 4월 12일 월요일  

## Introduction

* **Procedural programming** vs **Object-oriented programming**
  * Procedural programming (ex. C, PASCAL, BASIC)
    * Properties (variables)와 behaviors (functions)가 분리되어 있음.
  * Object-oriented programming (ex. C++, Java, Python)
    * Properties (variables)와 behaviors (functions)가 하나의 **object** 에 존재함.
    * 현실에서 모든 대상(object)은 그 특성과 행동으로 특정지어진다는 것을 반영.

* **Object** : Class의 instance

* **Class** : Object를 정의하는 templete(틀)

* Class : Object = 붕어빵 틀 : 붕어빵

* **OOP** (object-oriented programming)의 구성요소
  * Encapsulation
  * Abstraction
  * Polymorphism
  * Inheritance

## 1. Classes and Class Members

* **Class**: member variable (state)와 member function (behavior)로 구성된 user-defined type
  * Struct는 member function이 없고, member variable만 있음.
* ```class``` keword로 선언

* **Member variable** (혹은 **member data**) Class 내부에서 define된 variables

* **Member function** (혹은 **method**): Class 내부에서 defined된 functions

* Member variable이나 member function을 access할 때는 operator (**.**)를 사용
  * Struct와 동일

* Class definition

```c++
class Rectangle // Class name
{
public:   // Access specifier
  double length;    // Member variable
  double width;     // Member varaible

  double getArea()  // Member function
  {
    return length * width;
  }
}; // 세미콜론 필수
```

## 2. Public vs Private Access Specifiers

* **Acess specifier** : specifier로 정의된 member들의 접근 권한을 결정

* **Public member** : Class의 밖에서도 access할 수 있는 member

* **Private member** : Class내의 member들만 aceess할 수 있는 member

* **Protected member** : Friends, derived classs에서는 public이지만 그 외에는 private. Inheritance에서 자세히 배움


* 일반적으로 member variable은 private로, member function은 public으로 함. 즉, class 외부에서는 해당 class의 member function을 통하지 않으면 member variable을 접근할 수 없음.

* Access specifier 예시 코드

```c++
class Date
{
private:      // Private members
  int m_month;
  int m_day;
  int m_year;

public:       // Public members
  void setDate(int month, int day, int year)
  {
    m_month = month;
    m_day = day;
    m_year = year;
  }

  void print()
  {
    std::cout << m_month << '/' << m_day << '/' << m_year;
  }
};
```

## 3. Access Functions and Encapsulation

* **Encapsulation** (혹은 **information hiding**)이란
  * Object가 어떻게 구현되어 있는지에 대한 자세한 정보를 숨기는 것
  * 대신 사용자들은 public members를 통해서만 object를 접근할 수 있고, 따라서 사용자들은 해당 object가 어떻게 구현되어있는 지 몰라도 object를 사용할 수 있음.
  * 이런 encapsulation을 활용하면 class re-usability와 maintainability에 용이
  * 또한, data가 함부로 수정하지 않도록 보호할 수 있고, 오용을 방지할 수 있음.

* **Access function**
  * Private member variable을 직접 얻거나(get), 값을 설정(set)할 수 있는 간단한 public function.
  * 종류
    * Getter (혹은 accessor) : Private member variable의 값을 return하는 function
    * Setter (혹은 mutator) : Private member variable의 값을 수정하는 function

* Getter, Setter 예시 코드

```c++
class Date
{
private:
    int m_month;

public:
    int getMonth() { return m_month; } // getter
    void setMonth(int month) { m_month = month; } // setter
};
```