# 430.211 프로그래밍 방법론 LAB 18 : Virtual Functions
담당조교 : 함도규   
이메일 : hdk971110@scale.snu.ac.kr   
2021년 5월 3일 월요일

## Introduction
Virtual function의 개념과 사용법 등에 대해서 알아보자.

## 왜 virtual function이 필요한가?
* 상속과 관련이 있다.
``` c++
#include <string_view>
#include <iostream>
 
class Base
{
protected:
    int m_value;
 
public:
    Base(int value)
        : m_value{ value }
    {
    }
 
    std::string_view getName() const { return "Base"; }
    int getValue() const { return m_value; }
};
 
class Derived: public Base
{
public:
    Derived(int value)
        : Base{ value }
    {
    }
 
    std::string_view getName() const { return "Derived"; }
    int getValueDoubled() const { return m_value * 2; }
};

int main()
{
    Derived derived{ 5 };
 
    // Legal
    Base &rBase{ derived };
    Base *pBase{ &derived };
    /* Illegal
       Derived &rDerived{ base };
     */
 
    std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
    std::cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
    std::cout << "pBase is a " << pBase->getName() << " and has value " << pBase->getValue() << '\n';
 
    return 0;
}
```

```
derived is a Derived and has value 5
rBase is a Base and has value 5
pBase is a Base and has value 5
```
* Base를 가리키는 pointer나 참조하는 reference는 derived class의 객체를 가리키고 있더라도 derived class의 getName 함수를 볼 수 없기 때문에 base class의 getName 함수를 호출한다.

### Base class의 포인터나 레퍼런스의 사용
1. 포인터나 레퍼런스를 사용하지 않으면 derived class의 함수를 매번 만들어줘야한다.
```c++
void report(const Cat &cat)
{
    std::cout << cat.getName() << " says " << cat.speak() << '\n';
}

void report(const Dog &dog)
{
    std::cout << dog.getName() << " says " << dog.speak() << '\n';
}
```
```c++
// 가장 이상적인 방법
void report(const Animal &rAnimal)
{
    std::cout << rAnimal.getName() << " says " << rAnimal.speak() << '\n';
}
```

2. 각 derived class마다 array를 만들어줘야한다.
```c++
#if 0
int main()
{
    Cat cats[]{ { "Fred" }, { "Misty" }, { "Zeke" } };
    Dog dogs[]{ { "Garbo" }, { "Pooky" }, { "Truffle" } };

    for (const auto &cat : cats)
        std::cout << cat.getName() << " says " << cat.speak() << '\n';

    for (const auto &dog : dogs)
        std::cout << dog.getName() << " says " << dog.speak() << '\n';

    return 0;
}
#else
int main()
{
    Cat fred{ "Fred" };
    Cat misty{ "Misty" };
    Cat zeke{ "Zeke" };

    Dog garbo{ "Garbo" };
    Dog pooky{ "Pooky" };
    Dog truffle{ "Truffle" };

    // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
    Animal *animals[]{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };
    for (const auto animal : animals)
        std::cout << animal->getName() << " says " << animal->speak() << '\n';

    return 0;
}
#endif
```

## Virtual function, polymorphism, override
### Virtual function
* Virual function은 'virtual' 키워드로 정의가 됨.
* 'virtual'로 정의된 함수는 호출되는 순간 base와 derive 중에 devied class의 함수(most-derived)를 찾아서 실행한다.

### Polymorphism(다형성)
* 하나의 이름을 가진 함수를 호출했지만 어떨 때는 base class의 함수가 실행되고, 어떤 경우에는 derived class의 함수가 실행된다.
* 즉 하나의 메소드 또는 함수를 실행했음에도 불구하고 여러가지 다른 작업들을 하는 것을 'polymorphism(다형성)'이라고 한다.
* 다형성을 뜻하는 영어 단어인 'polymorphism' 은,여러개를 의미하는 그리스어 'poly' 와, 모습, 모양을 뜻하는 그리스어 'morphism' 에서 온 단어로 '여러가지 형태' 라는 의미하는

### Override
* 위와 같이 derived class의 base class와 signature가 동일한, 즉 똑같은 형태의 함수를 'override'라고 한다.

### 여러 번 상속 된 경우에는 어떻게 될까?
```c++
#include <iostream>
#include <string_view>

class A
{
public:
    virtual std::string_view getName() const { return "A"; }
};

class B: public A
{
public:
    virtual std::string_view getName() const { return "B"; }
};

class C: public B
{
public:
    virtual std::string_view getName() const { return "C"; }
};

class D: public C
{
public:
    virtual std::string_view getName() const { return "D"; }
};

int main()
{
    C c;
    A &rBase{ c };
    std::cout << "rBase is a " << rBase.getName() << '\n';

    return 0;
}
```

### 주의사항
1. virtual 함수의 signature는 정확히 일치해야한다. Returne type, name, arguments 등등.
2. 하나의 함수가 virtual로 생성이 된다면 다른 overrides들도 virtual로 간주가 되지만, virtual keyword는 항상 써주는게 좋다.
3. 절대로 constructor/destructor 안에서는 virtual 함수를 쓰지 마라.

### override and final keyword
#### override
* 함수가 base class의 함수를 override함을 명시적으로 표현함.
* 함수의 시그니처가 정확히 일치하지 않은 경우 에러 발생.
```c++
class A
{
public:
	virtual const char* getName1(int x) { return "A"; }
	virtual const char* getName2(int x) { return "A"; }
	virtual const char* getName3(int x) { return "A"; }
};
 
class B : public A
{
public:
	virtual const char* getName1(short int x) override { return "B"; } // compile error, function is not an override
	virtual const char* getName2(int x) const override { return "B"; } // compile error, function is not an override
	virtual const char* getName3(int x) override { return "B"; } // okay, function is an override of A::getName3(int)
 
};
```

#### final
* 'final' 키워드를 사용하면 해당 함수가 most-derived 로 판단하여 해당 함수를 호출함.
* 해당 class가 상속의 마지막 단계임을 명시함.
```c++
class A
{
public:
	virtual const char* getName() { return "A"; }
};

class B : public A
{
public:
	// note use of final specifier on following line -- that makes this function no longer overridable
	virtual const char* getName() override final { return "B"; } // okay, overrides A::getName()
};

class C : public B
{
public:
	virtual const char* getName() override { return "C"; } // compile error: overrides B::getName(), which is final
};
```

### Virtual destructor
* Derived 클래스 즉 상속을 다룰 때에는 항상 destructor를 virtual로 구현하여야 한다.
* 그래야 아래 예제 처럼 derived class를 가리키는 base pointer를 선언하고 delete를 하였을 때 derived 객체에서 선언된 멤버까지 다 제거할 수 있다.
```c++
#include <iostream>
#if 0
class Base
{
public:
    ~Base() // note: not virtual
    {
        std::cout << "Calling ~Base()\n";
    }
};

class Derived: public Base
{
private:
    int* m_array;

public:
    Derived(int length)
    {
        m_array = new int[length];
    }

    ~Derived() // note: not virtual (your compiler may warn you about this)
    {
        std::cout << "Calling ~Derived()\n";
        delete[] m_array;
    }
};
#else
class Base
{
public:
    virtual ~Base() // note: virtual
    {
        std::cout << "Calling ~Base()\n";
    }
};

class Derived: public Base
{
private:
    int* m_array;

public:
    Derived(int length)
    {
        m_array = new int[length];
    }

    virtual ~Derived() // note: virtual
    {
        std::cout << "Calling ~Derived()\n";
        delete[] m_array;
    }
};
#endif

int main()
{
    Derived *derived { new Derived(5) };
    Base *base { derived };

    delete base;

    return 0;
}
```

## Dynamic casting
* Base pointer를 가지고 derived class에 있는 멤버를 접근하고자 할 때 주로 사용된다.
* Derived 포인터를 Base 포인터로 컨버팅 하는 것을 'upcasting'이라고 한다.
* 그 반대로 Derived 포인터를 Base 포인터로 변환하는 것을 'downcasting'이라고 한다.
* 'Downcasting'을 사용하여 derived class의 멤버에 접근하려고 할 때 'dynamic_casitng'을 사용한다.

```c++
#include <iostream>
#include <string>
 
class Base
{
protected:
	int m_value;
 
public:
	Base(int value)
		: m_value(value)
	{
	}
	
	virtual ~Base() {}
};
 
class Derived : public Base
{
protected:
	std::string m_name;
 
public:
	Derived(int value, std::string name)
		: Base(value), m_name(name)
	{
	}
 
	const std::string& getName() const { return m_name; }
};
 
Base* getObject(bool bReturnDerived)
{
	if (bReturnDerived)
		return new Derived(1, "Apple");
	else
		return new Base(2);
}
int main()
{
	Base *b = getObject(true);

  Derived *d = dynamic_cast<Derived*>(b); // use dynamic cast to convert Base pointer into Derived pointer

  std::cout << "The name of the Derived is: " << d->getName() << '\n';
 
	delete b;
 
	return 0;
} 
```
* 이 때 b는 반드시 derived pointer여야 한다.
* 그렇지 않으면 dynamic_casting의 결과는 fail이 되고 null pointer를 return한다.
* 따라서 코드에 dynamic_casitng의 결과를 확인하는여 처리하는 코드를 넣는게 좋다.
* 포인터로 downcasting을 한 것럼 reference를 이용하는 방법도 가능하다.
```c++
int main()
{
	Derived apple(1, "Apple"); // create an apple
	Base &b = apple; // set base reference to object
	Derived &d = dynamic_cast<Derived&>(b); // dynamic cast using a reference instead of a pointer

	std::cout << "The name of the Derived is: " << d.getName() << '\n'; // we can access Derived::getName through d

	return 0;
}
```

### Dynamic casting vs Static casting
* static_casting이 빠르다.
* Downcasting을 하는 경우에는 dynamic_casting을 사용하자.
