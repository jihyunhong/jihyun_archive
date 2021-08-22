430.211 프로그래밍 방법론 : Chapter 13
===========================

담당조교 : 남 화 용


이메일 : hwayong.nam@scale.snu.ac.kr  

2021년 4월 19일  금요일

## Introduction

이번 시간에 배울 주제는 **Copy Constructor**와 **Destructor**입니다.

## The copy constructor

```c++
#include <cassert>
#include <iostream>

class Fraction
{
private:
  int m_numerator;
  int m_denominator;

public:
  // Default constructor
  Fraction(int numerator=0, int denominator=1) : m_numerator(numerator), m_denominator(denominator)
  {
    assert(denominator != 0);
  }

  // Copy constructor
  Fraction(const Fraction &fraction) : m_numerator(fraction.m_numerator), m_denominator(fraction.m_denominator)
  // Note: We can access the members of parameter fraction directly, because we're inside the Fraction class
  {
    // no need to check for a denominator of 0 here since fraction must already be a valid Fraction
    std::cout << "Copy constructor called\n"; // just to prove it works
  }

  friend std::ostream& operator<<(std::ostream& out, const Fraction &f1);
};

std::ostream& operator<<(std::ostream& out, const Fraction &f1)
{
  out << f1.m_numerator << "/" << f1.m_denominator;
  return out;
}

int main()
{
  Fraction fiveThirds(5, 3); // Direct initialize a Fraction, calls Fraction(int, int) constructor
  Fraction fCopy(fiveThirds); // Direct initialize -- with Fraction copy constructor
  std::cout << fCopy << '\n';
}
```

* 함수 call을 할 때, 만약 object가 argument로 넘겨진다면 parameter에 복사될 때 **copy constructor**가 실행됨.

* **Copy constructor** : 기존에 존재하는 object의 복사본에 해당하는 새로운 object를 만들 때 사용됨.

* 만약 프로그래머가 따로 **copy constructor**를 만들어주지 않으면, 컴퓨터는 **default constructor**를 자동으로 생성해줌.

## Shallow vs. deep copying

### Shallow copying

```c++
#include <cstring> // for strlen()
#include <cassert> // for assert()

class MyString
{
private:
  char *m_data;
  int m_length;

public:
  MyString(const char *source="")
  {
    assert(source); // make sure source isn't a null string

    // Find the length of the string
    // Plus one character for a terminator (\0)
    m_length = std::strlen(source) + 1;

    // Allocate a buffer equal to this length
    m_data = new char[m_length];

    // Copy the parameter string into our internal buffer
    for (int i{ 0 }; i < m_length; ++i)
      m_data[i] = source[i];

    // Make sure the string is terminated
    m_data[m_length-1] = '\0';
  }

  ~MyString() // destructor
  {
    // We need to deallocate our string
    delete[] m_data;
  }

  char* getString() { return m_data; }
  int getLength() { return m_length; }
};

int main()
{
  MyString hello{ "Hello, world!" };
  {
    MyString copy{ hello }; // use default copy constructor
  } // copy is a local variable, so it gets destroyed here.  The destructor deletes copy's string, which leaves hello with a dangling pointer

  std::cout << hello.getString() << '\n'; // this will have undefined behavior

  return 0;
}
```

* 위 코드는 아래의 **default copy constructor**를 자동으로 호출함.

```c++
MyString::MyString(const MyString &source) : m_length{ source.m_length }, m_data{ source.m_data }
{
}
```

### Deep copying

```c++
// assumes m_data is initialized
void MyString::deepCopy(const MyString& source)
{
  // first we need to deallocate any value that this string is holding!
  delete[] m_data;

  // because m_length is not a pointer, we can shallow copy it
  m_length = source.m_length;

  // m_data is a pointer, so we need to deep copy it if it is non-null
  if (source.m_data)
  {
    // allocate memory for our copy
    m_data = new char[m_length];

    // do the copy
    for (int i{ 0 }; i < m_length; ++i)
      m_data[i] = source.m_data[i];
  }
  else
    m_data = nullptr;
}

// Copy constructor
MyString::MyString(const MyString& source): m_data{ nullptr }
{
  deepCopy(source);
}
```