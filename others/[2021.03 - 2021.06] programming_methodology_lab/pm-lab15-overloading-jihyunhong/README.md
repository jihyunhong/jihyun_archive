# Operator Overloading and Rule of Three
담당조교 : 김종민 \
이메일 : jongmin.kim@scale.snu.ac.kr \
2021년 4월 23일 금요일

참고자료: learncpp.com Ch.13, https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)
## Introduction to operator overloading

* C++에서 **operator**는 **function**으로 구현되어 있음.

```c++
int x = 2;
int y = 3;

std::cout << x + y << '\n';
```

* 위 코드에서 `x+y`는 실제로는 `operator+(x, y)`으로 치환됨. 

## Operator overloading의 세 가지 방법

### By using friend functions

```c++
#include <iostream>
 
class Cents
{
private:
  int m_cents;
 
public:
  Cents(int cents) { m_cents = cents; }
 
  // add Cents + Cents using a friend function
  friend Cents operator+(const Cents &c1, const Cents &c2);

  // add Cents + int using a friend function
  friend Cents operator+(const Cents &c1, int value);
 
  int getCents() const { return m_cents; }
};
 
// note: this function is not a member function!
Cents operator+(const Cents &c1, const Cents &c2)
{
  // use the Cents constructor and operator+(int, int)
  // we can access m_cents directly because this is a friend function
  return Cents(c1.m_cents + c2.m_cents);
}

// note: this function is not a member function!
Cents operator+(const Cents &c1, int value)
{
  // use the Cents constructor and operator+(int, int)
  // we can access m_cents directly because this is a friend function
  return Cents(c1.m_cents + value);
} 

int main()
{
  Cents cents1(6);
  Cents cents2(8);
  Cents cents3 = Cents(4) + 6;

  Cents centsSum = cents1 + cents2;
  std::cout << "I have " << centsSum.getCents() << " cents." << std::endl;
  std::cout << "I have " << cents3.getCents() << " cents." << std::endl;
 
  return 0;
}
```

> 위 코드의 실행 결과는?   
> I have 14 cents.   
> I have 10 cents.

### By using normal functions

```c++
#include <iostream>

class Cents
{
private:
  int m_cents;

public:
  Cents(int cents) { m_cents = cents; }

  int getCents() const { return m_cents; }
};

// note: this function is not a member function nor a friend function!
Cents operator+(const Cents &c1, const Cents &c2)
{
  // use the Cents constructor and operator+(int, int)
  // we don't need direct access to private members here
  return Cents(c1.getCents() + c2.getCents());
}

int main()
{
  Cents cents1(6);
  Cents cents2(8);
  Cents centsSum = cents1 + cents2;
  std::cout << "I have " << centsSum.getCents() << " cents." << std::endl;

  return 0;
}
```

* 일반적으로 **friend function**을 이용하는 것보다 **normal function**을 이용하는 것을 선호. 왜냐하면 **friend function**을 이용한 방식은 member variable에 direct하게 접근할 수 있기 때문.

### By using member functions

```c++
#include <iostream>

class Cents
{
private:
  int m_cents;

public:
  Cents(int cents) { m_cents = cents; }

  // Overload Cents + int
  Cents operator+(int value);

  int getCents() { return m_cents; }
};

// note: this function is a member function!
// the cents parameter in the friend version is now the implicit *this parameter
Cents Cents::operator+(int value)
{
  return Cents(m_cents + value);
}

int main()
{
  Cents cents1(6);
  Cents cents2 = cents1 + 2;
  std::cout << "I have " << cents2.getCents() << " cents.\n";

  return 0;
}
```

* 위 그림에서 `operator+`는 `operator+(&cents1,2)`로 translate됨.

* 그럼 어떨 때 **friend/normal function**을 쓰고, 어떨 때 **member function**을 쓰는 것이 좋을까?
  - `+`와 같이 left operand의 값이 바뀔 일이 없을 때는 **friend/normal function**.
  - `+=`과 같이 left operand의 값이 바뀌는 경우에는 **member function**.

## Overloading unary operators +, -, and !
* '+', '-'는 7 + 8과 같이 binary operator로도 쓰이지만, 단순히 부호를 표시하는 +7, -8 등 unary operator로도 쓰임.
* Unary operator들은 연산이 끝나고나면 operand의 값이 바뀌기 때문에 **member function** 사용.

```c++
#include <iostream>

class Cents
{
private:
  int m_cents;

public:
  Cents(int cents) { m_cents = cents; }

  // Overload -Cents as a member function
  Cents operator-() const;

  int getCents() const { return m_cents; }
};

// note: this function is a member function!
Cents Cents::operator-() const
{
  return Cents(-m_cents);
}

int main()
{
  const Cents nickle(5);
  std::cout << "A nickle of debt is worth " << (-nickle).getCents() << " cents\n";

  return 0;
}
```
> 새로운 object ```Cents(-m_cents)```를 생성해서 return by value하는 점을 생각해 보세요. Why?

## Overloading the comparison operators

* **Comparison operator**는 left operand를 변화시키지 않기 때문에 **friend function**으로 선언.

```c++
#include <iostream>
#include <string>

class Car
{
private:
  std::string m_make;
  std::string m_model;

public:
  Car(std::string make, std::string model) : m_make{ make }, m_model{ model }
  {
  }

  friend bool operator== (const Car &c1, const Car &c2);
  friend bool operator!= (const Car &c1, const Car &c2);
};

bool operator== (const Car &c1, const Car &c2)
{
  return (c1.m_make== c2.m_make && c1.m_model== c2.m_model);
}

bool operator!= (const Car &c1, const Car &c2)
{
  return !(c1== c2);
}

int main()
{
  Car corolla{ "Toyota", "Corolla" };
  Car camry{ "Toyota", "Camry" };

  if (corolla == camry)
    std::cout << "a Corolla and Camry are the same.\n";

  if (corolla != camry)
    std::cout << "a Corolla and Camry are not the same.\n";

  return 0;
}
```

## Overloading the increment and decrement operators

* **Increment and decrement operator** ```++```과 ```--```는 unary operator이기도 하고, operand의 값을 바꾸기 때문에 **member function** 사용.
* 앞에 붙을 때(prefix)와 뒤에 붙을 때(postfix)가 다름을 유의하세요.
```c++
class Digit
{
private:
  int m_digit;
public:
  Digit(int digit=0) : m_digit(digit)
  {
  }

  Digit& operator++(); // prefix
  Digit& operator--(); // prefix

  Digit operator++(int); // postfix
  Digit operator--(int); // postfix

  friend std::ostream& operator<< (std::ostream &out, const Digit &d);
};

Digit& Digit::operator++()
{
  // If our number is already at 9, wrap around to 0
  if (m_digit == 9)
    m_digit = 0;
  // otherwise just increment to next number
  else
    ++m_digit;

  return *this;
}

Digit& Digit::operator--()
{
  // If our number is already at 0, wrap around to 9
  if (m_digit == 0)
    m_digit = 9;
  // otherwise just decrement to next number
  else
    --m_digit;

  return *this;
}

Digit Digit::operator++(int)
{
  // Create a temporary variable with our current digit
  Digit temp(m_digit);

  // Use prefix operator to increment this digit
  ++(*this); // apply operator

  // return temporary result
  return temp; // return saved state
}

Digit Digit::operator--(int)
{
  // Create a temporary variable with our current digit
  Digit temp(m_digit);

  // Use prefix operator to decrement this digit
  --(*this); // apply operator

  // return temporary result
  return temp; // return saved state
}

std::ostream& operator<< (std::ostream &out, const Digit &d)
{
  out << d.m_digit;
  return out;
}

int main()
{
  Digit digit(5);

  std::cout << digit;
  std::cout << ++digit; // calls Digit::operator++();
  std::cout << digit++; // calls Digit::operator++(int);
  std::cout << digit;
  std::cout << --digit; // calls Digit::operator--();
  std::cout << digit--; // calls Digit::operator--(int);
  std::cout << digit;

  return 0;
}
```

* 위 코드에서 쓰인 *dummy variable* 또는 *dummy argument*는 단순히 prefix와 postfix를 구분하기 위한 변수.

## Overloading the subscript operator

* Subscript operator ```[]```는 비록 operand의 값을 바꾸지는 않지만 member function으로 선언해야됨.
```c++
class IntList
{
private:
  int m_list[10]{};

public:
  int& operator[] (int index);
};

int& IntList::operator[] (int index)
{
  return m_list[index];
}

int main()
{
  IntList list{};
  list[2] = 3; // set a value
  std::cout << list[2] << '\n'; // get a value

  return 0;
}
```
> Class IntList를 마치 array의 한 index 값을 사용하는 것처럼 이용 가능

## Overloading the parenthesis operator

* **parenthesis operator** ```( )```는 위의 **subscript operator**와 마찬가지로 **member function**으로 선언되어야 함.
* 괄호 안의 여러 개의 input을 받을 수 있음.
```c++
#include <iostream>
#include <cassert> // for assert()
class Matrix
{
private:
  double data[4][4]{};

public:
  double& operator()(int row, int col);
  void operator()();
};

double& Matrix::operator()(int row, int col)
{
  assert(col >= 0 && col < 4);
  assert(row >= 0 && row < 4);

  return data[row][col];
}

void Matrix::operator()()
{
  // reset all elements of the matrix to 0.0
  for (int row{ 0 }; row < 4; ++row)
    for (int col{ 0 }; col < 4; ++col)
      data[row][col] = 0.0;
}

int main()
{
  Matrix matrix;
  matrix(1, 2) = 4.5;
  matrix(); // erase matrix
  std::cout << matrix(1, 2) << '\n'; // 0

  return 0;
}
```

## Overloading the I/O operators

### Overloading operator <<, >>


* 다음과 같이 friend function 으로 선언
* 반환값과 parameter 설정에 유의!
* output_stream << variable : 출력 스트림에 variable의 출력할 값을 넘겨준다는 의미
* input_stream >> variable : 입력 스트립에서 부터 variable로 값을 가져온다는 의미


```c++
#include <iostream>
 
class Point
{
private:
  double m_x, m_y, m_z;
 
public:
  Point(double x=0.0, double y=0.0, double z=0.0): m_x(x), m_y(y), m_z(z)
  {
  }
 
  friend std::ostream& operator<< (std::ostream &out, const Point &point);
  friend std::istream& operator>> (std::istream &in, Point &point);
};
 
std::ostream& operator<< (std::ostream &out, const Point &point)
{
  // Since operator<< is a friend of the Point class, we can access Point's members directly.
  out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ")";
 
  return out;
}
 
std::istream& operator>> (std::istream &in, Point &point)
{
  // Since operator>> is a friend of the Point class, we can access Point's members directly.
  // note that parameter point must be non-const so we can modify the class members with the input values
  in >> point.m_x;
  in >> point.m_y;
  in >> point.m_z;
 
  return in;
}

int main()
{
  std::cout << "Enter a point: \n";

  Point point;
  std::cin >> point;

  std::cout << "You entered: " << point << '\n';

  return 0;
}

```

## Assignment Operator
* **Assignment operator** ```=```은 왼쪽 variable로 오른쪽 값을 **복사**하는 operator.
```c++
#include <cassert>
#include <iostream>

class Fraction // 분수를 나타내는 class
{
private:
  int m_numerator; // 분자
  int m_denominator; // 분모
public:
  // Default constructor
  Fraction(int numerator=0, int denominator=1)  :
  m_numerator(numerator), m_denominator(denominator)
  {
    assert(denominator != 0);
  }
  
  // Copy constructor
  Fraction(const Fraction &copy)  :
  m_numerator(copy.m_numerator), m_denominator(copy.m_denominator)
  {
    // no need to check for a denominator of 0 here since copy must already be a valid Fraction
    std::cout << "Copy constructor called\n"; // just to prove it works
  }
  
  // Overloaded assignment operator
  Fraction& operator= (const Fraction &fraction);
};

//////** LOOK HERE! **//////
// A simplistic implementation of operator= (see better implementation below)
Fraction& Fraction::operator= (const Fraction &fraction)
{
  // do the copy
  m_numerator = fraction.m_numerator;
  m_denominator = fraction.m_denominator;
  // return the existing object so we can chain this operator
  return *this;
}

int main()
{
  Fraction fiveThirds(5,  3);
  Fraction f;
  f = fiveThirds;  // calls overloaded assignment
  std::cout << f;
  return 0;
}
```
> 출력: 5/3
* Return by reference : assignment operator는 값을 **복사**한 후, 자기 자신(```*this```)을 reference형 (즉, 변경 가능한 상태)으로 반환한다. 
* const reference parameter : assignment operator는 parameter인 ```=``` 오른쪽에 오는 값을 변경해선 안 되나, **복사**로 인한 성능 저하를 막기 위해 const reference형으로 parameter를 가져온다.

### Assignment Operator vs Copy Constructor
* 위의 Fraction class에 대해 다음과 같은 작업을 하면
```c++
Fraction fiveThirds(5, 3); // Constructor called
Fraction newFraction1(fiveThirds); // Copy Constructor called
Fraction newFraction2 = fiveThirds; // Copy Constructor called!!
Fraction newFraction3; 
newFraction3 = fiveThirds; // Assignment Operator called
```
* 다음과 같이 declaration이 이미 된 변수에 대해서만 assignment operator가 call된다.
* 또한, 다음과 같은 예시를 자세히 보자
```c++
Fraction foo(Fraction frac) {
 // do something to frac
 return frac;
}

...

Fraction fiveThirds(5, 3);
Fraction ret;
ret = foo(fiveThirds);
```
> 1. ```foo```의 argument ```fiveThirds```가 parameter ```frac```으로 copy constructor를 통해 복사된다. (pass by value)
> 2. ```foo```의 return value인 ```frac```이 ```foo(fiveThirds)```를 나타내는 **임시 객체**로 copy constructor를 통해 **복사**된다. (return by value)
> 3. ```foo(fiveThirds)```를 나타내는 **임시 객체**로부터 ```ret```로 assignment operator를 통해 **복사**된다.

이 예시를 통해 copy constructor와 assignment operator가 각각 어떤 경우에 호출되는지 구분하시기 바랍니다.

### Deep copying in assignment operator
다음과 같이 dynamic allocation을 사용하는 ```class IntList```가 있다.
```c++
class IntList
{
private:
  int listLength;
  int* intArray;
public:
  IntList(int length) : listLength(length)
  {
    intArray = new int [length];
  }
  IntList& operator= (const IntList& rhs);
};
```
이 class의 assignment operator는 다음과 같이 구현된다.
```c++
IntList& IntList::operator= (const IntList& rhs) // functional, but not complete
{
  // 1. 자신(왼쪽에 오는 변수)의 메모리 clean
  delete[] intArray;
  // 2. 새롭게 dynamic allocation
  listLength = rhs.listLength;
  intArray = new int [listLength];
  // 3. deep copy
  for (int i = 0; i < listLength; i++)
  {
	  intArray[i] = rhs.intArray[i];
  }
  // 4. return left-hand side
  return *this;
}
```
* 앞서 ```Fraction```과 같은 간단한 assignment operator의 경우, 사용자가 직접 구현하지 않아도 **default assignment operator**가 자동 생성되어 복사해줄 수 있음. (자동 생성되는 건 ```IntList```도 마찬가지)
* 하지만, 자동생성되는 assignment operator는 **shallow copy**임.
```c++
IntList& IntList::operator= (const IntList& rhs) // 자동생성되는 assignment operator
{
  listLength = rhs.listLength;
  intArray = rhs.intArray; // shallow copy!, only copy the pointer
}
```
* 일반적으로 dynamic allocation이 필요한 class의 경우, 직접 assignment operator를 구현해주어야 **deep copy**를 할 수 있음.

### Preventing errors in self assignment
```a = a```와 같이 self assignment가 발생할 수 있습니다. 하지만 앞서 구현한 assignment operator는 먼저 자신의 memory를 clean하고 그 후에 복사를 진행하기 때문에, self assignment의 경우, 복사 전에 오른쪽 값이 memory에서 지워져 버리는 문제가 발생합니다. 이를 방지하기 위해 다음과 같이 assignment operator를 수정해야 합니다.
```c++
IntList& IntList::operator= (const IntList& rhs)
{
  // 0. self assignment check
  if ( this == &rhs ) // object의 주소가 같은 지 체크
  {
    return *this;
  }
  // 1. 자신(왼쪽에 오는 변수)의 메모리 clean
  delete[] intArray;
  // 2. 새롭게 dynamic allocation
  listLength = rhs.listLength;
  intArray = new int [listLength];
  // 3. deep copy
  for (int i = 0; i < listLength; i++)
  {
	  intArray[i] = rhs.intArray[i];
  }
  // 4. return left-hand side
  return *this;
}
```

## Rule of Three
앞서 **copy constructor**, **destructor**, 그리고 **assignment operator**를 배웠습니다. 이 셋 사이에는 공통점이 있습니다. 바로 **dynamic allocation으로 deep copy가 필요한 경우, 직접 구현해야 한다는 점입니다**.

그러므로, 일반적으로 그러한 class를 구현할 때, **copy constructor**, **destructor**, 그리고 **assignment operator** 세 가지를 모두 다 구현을 해야 합니다. 이를 **Rule of Three**라고 합니다.
이를 바탕으로 ```IntList``` class를 개선하면 다음과 같습니다.
```c++
class IntList
{
private:
  int listLength;
  int* intArray;
public:
  IntList(int length) : listLength(length)
  {
    intArray = new int [length];
  }
  // 1. Copy Constructor
  IntList(const IntList& copy);
  // 2. Destructor
  ~IntList();
  // 3. Assignment Operator
  IntList& operator= (const IntList& rhs);
};
// 1. Copy Constructor
IntList::IntList(const IntList& copy) : listLength(copy.listLength)
{
  intArray = new int [length];
  for (int i = 0; i < listLength; i++)
  {
	  intArray[i] = rhs.intArray[i];
  }
}
// 2. Destructor
IntList::~IntList()
{
  delete[] intArray;
}
// 3. Assignment Operator
IntList& IntList::operator= (const IntList& rhs)
{
  if ( this == &rhs ) return *this;
  delete[] intArray;
  listLength = rhs.listLength;
  intArray = new int [listLength];
  for (int i = 0; i < listLength; i++)
  {
	  intArray[i] = rhs.intArray[i];
  }
  return *this;
}
```

