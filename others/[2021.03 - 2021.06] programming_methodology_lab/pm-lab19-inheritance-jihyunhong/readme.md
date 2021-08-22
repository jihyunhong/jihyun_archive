# 430.211 프로그래밍 방법론 : Inheritance

담당 조교 : 박재영

이메일 : jypark@scale.snu.ac.kr  
2021년 5월 7일  금요일

## Introduction

### Motivation : is vs has

``` cpp
#include <string>
 
class Person{
// In this example, we're making our members public for simplicity
public: 
    std::string m_name;
    int m_age;
 
    Person(std::string name = "", int age = 0)
        : m_name(name), m_age(age) {}
 
    std::string getName() const { return m_name; }
    int getAge() const { return m_age; }
};
```
BaseballPlayer라는 class에도 이름과 나이를 추가하고 싶습니다. 여기서 우리는 몇가지 선택지가 있습니다.
1. BaseballPlayer에도 `m_name`, `m_age`라는 member variable과 `getName()`, `getAge()`라는 member function을 두는 것입니다. 하지만 c++ 프로그래머로서 이렇게 쓸데없이 코드를 반복해서 쓰는 것은 지양하여야 합니다.
2. BaseballPlayer에 Person이라는 class를 composition을 이용해서 member로 추가하는 것입니다. 하지만 **BaseballPlayer has person**은 이상한 것처럼 보입니다. :boom:
3. BaseballPlayer가 person으로부터 이름과 나이를 inherit하는 방법이 있습니다. **inherit은 BaseballPlayer is person**의 관계와 같습니다.:smiley:

#### Inheritance 간단한  예제 1: BaseballPlayer


``` c++
class BaseballPlayer : public Person //이게 inherit 문법, public inherit임
{
public:
    double m_battingAverage;
    int m_homeRuns;
 
    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage(battingAverage), m_homeRuns(homeRuns) {}
};
```

> BaseballPlayer가 Person을 inherit하는 것은 이렇게 매우 간단합니다.​​ 이제 BaseballPlayer에서 Person의 member variable, member function에 접근해 보겠습니다.

#### Inherited class의 member에 접근

main함수에서 Person의 member에 접근합니다.

``` c++
#include <iostream>
#include <string>

class Person{
public:
    std::string m_name;
    int m_age;
 
    Person(std::string name = "", int age = 0)
        : m_name(name), m_age(age){}
 
    std::string getName() const { return m_name; }
    int getAge() const { return m_age; }
 
};
 
// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
public:
    double m_battingAverage;
    int m_homeRuns;
 
    BaseballPlayer(double battingAverage = 0.0, int homeRuns = 0)
       : m_battingAverage(battingAverage), m_homeRuns(homeRuns)
    {}
};
 
int main()
{
    BaseballPlayer joe; 	// Create a new BaseballPlayer object
    joe.m_name = "Joe";		// Assign joe a name (can do this directly, m_name is public)
    // Print out the name
    std::cout << joe.getName() << '\n'; // use the getName() function we've acquired from the Person base class
 
    return 0;
}
```

> inherit은 **is**의 관계를 가진다고 했는데,  BaseballPlayer인 **Joe가 Person인 것처럼 Person의 멤버 변수, 함수를 사용**합니다. 

Person을 inherit하는 Employee class를 만들어 보겠습니다.

#### Inheritance 간단한 예제 2 : Employee

``` c++
class Employee: public Person
{
public:
    double m_hourlySalary;
    long m_employeeID;
 
    Employee(double hourlySalary = 0.0, long employeeID = 0)
        : m_hourlySalary(hourlySalary), m_employeeID(employeeID) {}
 
    void printNameAndSalary() cons{
        std::cout << m_name << ": " << m_hourlySalary << '\n';
    }
};
```
> Employee의 printNameandsalary()가 m_name에 접근하는 것을 관찰해 보세요. :eyes:


### Constructor in inheritance
자 간단한 inheritance 코드를 보면서 생각해 봅시다.

``` c++
#include <iostream>
 
class Base{
public:
    int m_id;
 
    Base(int id=0)
        : m_id(id)
    {
        std::cout << "Base\n";
    }
    int getId() const { return m_id; }
};
 
class Derived: public Base		//여기서 Base를 inherit
{
public:
    double m_cost;
 
    Derived(double cost=0.0)
        : m_cost(cost)
    {
        std::cout << "Derived\n";
    }
    double getCost() const { return m_cost; }
};
 
int main()
{
    std::cout << "Instantiating Derived\n";
    Derived cDerived;
    return 0;
}
```
>  무슨 일이 일어날까요? Base의 constructor가 Derived에도 적용이 될까요? 닭이 먼저냐 알이 먼저냐 하는 유명한 문제를 기억하실 겁니다. 여기선 부모와 자식의 관계기 때문에, 부모가 먼저고 자식이 그 다음입니다. :smiley:

**출력 : **

*Instantiating Derived*
*Base*
*Derived*

<hr/>

#### 정리
**Base class를 instantiate** 했을 때 발생하는 일들

1. Base class를 위한 메모리가 할당됩니다.
2. Base constructor를 호출합니다.
3. initialization list를 통해 variable들을 initialize합니다.
4. Constructor의 body가 실행됩니다.
5. caller에게 control이 다시 넘어갑니다.

한편, **Derived class를 instantiate** 했을 때 발생하는 일들
1. Derived class를 위한 메모리가 할당됩니다.
2. Derived constructor를 호출합니다.
3. Derived class에서 설정한 Base constructor가 호출됩니다. 
4. Base constructor가 일을 마친 후, Derived constructor로 다시 넘어갑니다.
5. initialization list를 통해 variable들을 initialize합니다.
6. Constructor의 body가 실행됩니다.
7. caller에게 control이 다시 넘어갑니다.

Derived constructor가 **먼저 호출**되지만, Derived class가 호출되고 variable을 **initialize하기도 전**에 Base constructor가 호출되기 때문에, Base constructor가 일을 다 마치고 Derived constructor가 일을 합니다.

<hr/>

그러면 Derived class에서 **base class의 object들을 initialize**하는 방법을 배워보겠습니다.

### 잘못된 예시1 : Initialization list

``` c++
class Derived: public Base
{
public:
    double m_cost;
 
    Derived(double cost=0.0, int id=0)
        // m_id가 base의 member variable, does not work
        : m_cost(cost), m_id(id) {}
 
    double getCost() const { return m_cost; }
};
```
c++에서는 initialization list에 있는 value들은 **같은 class에서만 initialize가 가능**합니다. base의 member였던 m_id는 inherit된 것이기 때문에 initialization list를 통해 초기화할 수 없습니다.

이렇게 만든 이유는 **m_id**가 **const**나 **reference** 일 때와 관련이 있습니다. const의 경우는 만들어질 때 initialize되어야 하기 때문에, Base constructor에서  initiallize하고 난 후 Derived에서 한번 더 initialize되는 것을 방지하기 위함입니다.

### 잘못된 예시2 : Assign value in constructor

``` c++
class Derived: public Base
{
public:
    double m_cost;
 
    Derived(double cost=0.0, int id=0)
        : m_cost{ cost }
    {
        m_id = id;	//what if m_id is const or reference?
    }
 
    double getCost() const { return m_cost; }
};
```
이 방법은 실제로 잘 작동하지만, 또다시 **m_id**가 **const**나 **reference**일 때 문제가 생깁니다(const나 reference는 constructor의 initialization list에서 딱 한번 initialized 됩니다.). 이렇게 하는 경우 2번 initialize되는 문제가 계속 발생할 것입니다.

### Best Practice : call Base constructor

``` c++
class Derived: public Base
{
public:
    double m_cost;
 
    Derived(double cost=0.0, int id=0)
        : Base{ id }, m_cost{ cost }// Call Base(int) constructor with value id!
    {}
 
    double getCost() const { return m_cost; }
};
```
이렇게 Derived constructor에서 **직접 m_id를 다룰** 필요없이, 적당한 **Base constructor을 호출**하면 됩니다 :smiley:

<hr/>

#### 정리 

**Base constructor를 call** 했을 때 발생하는 일들

1. Derived class를 위한 메모리가 할당됩니다.
2. Derived constructor를 호출합니다.
3. 컴파일러가 Derived class에서 특정한 Base class constructor를 call했는지 체크합니다. 찾으면, Base contructor를 실행시킵니다.
4. Base class constructor가 m_id를 set합니다.
5. Base class constructor의 body가 실행되고, return을 통해 caller로 jump합니다.
6. Derived class constructor가 m_cost를 set합니다.
7. Derived class constructor의 body가 실행되고, return을 통해 caller로 jump합니다.

이렇게 하면 **Base의 constructor를 호출**할 수 있기 때문에 **Base의 member variable들을 private**으로 설정할 수도 있습니다.

<hr/>

### Private member variable inheritance

Base의 private member들을 Derived에서 접근하려면 Base의 member function들로만 접근할 수 있습니다.

``` c++
#include <iostream>
#include <string>
 
class Person
{
private:
    std::string m_name;
    int m_age;
 
public:
    Person(const std::string& name = "", int age = 0)
        : m_name{ name }, m_age{ age }
    {}
 
    const std::string& getName() const { return m_name; }
    int getAge() const { return m_age; }
 
};
// BaseballPlayer publicly inheriting Person
class BaseballPlayer : public Person
{
private:
    double m_battingAverage;
    int m_homeRuns;
 
public:
    BaseballPlayer(const std::string& name = "", int age = 0,
        double battingAverage = 0.0, int homeRuns = 0)
        : Person{ name, age }, // call Person(const std::string&, int) to initialize these fields
            m_battingAverage{ battingAverage }, m_homeRuns{ homeRuns }
    {
    }
 
    double getBattingAverage() const { return m_battingAverage; }
    int getHomeRuns() const { return m_homeRuns; }
};

int main()
{
    BaseballPlayer pedro{ "Pedro Cerrano", 32, 0.342, 42 };
 
    std::cout << pedro.getName() << '\n';
    std::cout << pedro.getAge() << '\n';
    std::cout << pedro.getHomeRuns() << '\n';
 
    return 0;
}
```

### Inheritance chain

Inheritance는 nested될 수도 있습니다.

``` c++
#include <iostream>
 
class A
{
public:
    A(int a)
    {
        std::cout << "A: " << a << '\n';
    }
};
 
class B: public A
{
public:
    B(int a, double b)
    : A{ a }
    {
        std::cout << "B: " << b << '\n';
    }
};
 
class C: public B
{
public:
    C(int a , double b , char c)
    : B{ a, b }
    {
        std::cout << "C: " << c << '\n';
    }
};
 
int main()
{
    C c{ 5, 4.3, 'R' };
 
    return 0;
}
```

### Destructors

destructors는 construction의 역순으로 호출합니다.
자식 class의 destructor가 먼저 호출되고 난 후, 부모 class의 destructor가 호출됩니다.


### New access specifiers : protected
`public`과 `private`외에 다른 access specifier `protected`가 있습니다. 이러한 access specifiers는 inheritance를 사용할 때 의미가 있습니다.

``` c++
class Base
{
public:
    int m_public; // can be accessed by anybody
protected:
    int m_protected; // can be accessed by Base members, friends, and derived classes
private:
    int m_private; // can only be accessed by Base members and friends (but not derived classes)
};
 
class Derived: public Base
{
public:
    Derived()
    {
        m_public = 1; // allowed: can access public base members from derived class
        m_protected = 2; // allowed: can access protected base members from derived class
        m_private = 3; // not allowed: can not access private base members from derived class
    }
};
 
int main()
{
    Base base;
    base.m_public = 1; // allowed: can access public members from outside class
    base.m_protected = 2; // not allowed: can not access protected members from outside class
    base.m_private = 3; // not allowed: can not access private members from outside class
}
```
>이러한 protected specifier를 사용하면 derived class에서 protected member에 직접 접근을 할 수 있습니다. 따라서 protected는 public inheritance를 해도 protected입니다. 

inheritance에는 3가지 종류가 있습니다.

``` c++
// Inherit from Base publicly
class Pub: public Base
{};
 
// Inherit from Base protectedly
class Pro: protected Base
{};
 
// Inherit from Base privately
class Pri: private Base
{};
 
class Def: Base // Defaults to private inheritance
{};
```

#### 먼저 public inheritance

Access specifiers in base class | Access specifier when inherited publicly
------------------------------- | -----------------------------------------
public | public
protected | protected
private | inaccessible

``` c++
class Base
{
public:
    int m_public;
protected:
    int m_protected;
private:
    int m_private;
};
 
class Pub: public Base // note: public inheritance
{
    // Public inheritance means:
    // Public inherited members stay public (so m_public is treated as public)
    // Protected inherited members stay protected (so m_protected is treated as protected)
    // Private inherited members stay inaccessible (so m_private is inaccessible)
public:
    Pub()
    {
        m_public = 1; // okay: m_public was inherited as public
        m_protected = 2; // okay: m_protected was inherited as protected
        m_private = 3; // not okay: m_private is inaccessible from derived class
    }
};
 
int main()
{
    // Outside access uses the access specifiers of the class being accessed.
    Base base;
    base.m_public = 1; // okay: m_public is public in Base
    base.m_protected = 2; // not okay: m_protected is protected in Base
    base.m_private = 3; // not okay: m_private is private in Base
 
    Pub pub;
    pub.m_public = 1; // okay: m_public is public in Pub
    pub.m_protected = 2; // not okay: m_protected is protected in Pub
    pub.m_private = 3; // not okay: m_private is inaccessible in Pub
```

#### private inheritance

Access specifiers in base class | Access specifier when inherited publicly
------------------------------- | -----------------------------------------
public | private
protected | private
private | inaccessible

``` c++
class Base
{
public:
    int m_public;
protected:
    int m_protected;
private:
    int m_private;
};
 
class Pri: private Base // note: private inheritance
{
    // Private inheritance means:
    // Public inherited members become private (so m_public is treated as private)
    // Protected inherited members become private (so m_protected is treated as private)
    // Private inherited members stay inaccessible (so m_private is inaccessible)
public:
    Pri()
    {
        m_public = 1; // okay: m_public is now private in Pri
        m_protected = 2; // okay: m_protected is now private in Pri
        m_private = 3; // not okay: derived classes can't access private members in the base class
    }
};
 
int main()
{
    // Outside access uses the access specifiers of the class being accessed.
    // In this case, the access specifiers of base.
    Base base;
    base.m_public = 1; // okay: m_public is public in Base
    base.m_protected = 2; // not okay: m_protected is protected in Base
    base.m_private = 3; // not okay: m_private is private in Base
 
    Pri pri;
    pri.m_public = 1; // not okay: m_public is now private in Pri
    pri.m_protected = 2; // not okay: m_protected is now private in Pri
    pri.m_private = 3; // not okay: m_private is inaccessible in Pri
```

#### protected inheritance

Access specifiers in base class | Access specifier when inherited publicly
------------------------------- | -----------------------------------------
public | protected
protected | protected
private | inaccessible

>쉽게 볼수 없는 inheritance입니다. 사용빈도는 public >> private >> protected라고 생각하시면 됩니다.

### adding functionality in derived class

Inherited class에서 멤버변수 추가 없이, functionality만 추가할 수도 있습니다.

``` c++
#include <iostream>
 
class Base
{
protected:
    int m_value;
 
public:
    Base(int value)
        : m_value(value)
    {}
    void identify() { std::cout << "I am a Base\n"; }
};

class Derived: public Base
{
public:
    Derived(int value)
        :Base(value)
    {}
    int getValue() { return m_value; }
};

int main()
{
    Derived derived(5);
    std::cout << "derived has value " << derived.getValue() << '\n';
 
    return 0;
}
```

###  inherited function call을 했을 때 derived에 없다면
derived class는 base의 모든 member variable, member function을 inherit하였으므로,function이 derived에 없다면 base에 있는 member function을 찾습니다.

``` c++
class Base
{
protected:
    int m_value;
 
public:
    Base(int value)
        : m_value(value)
    {
    }
 
    void identify() { std::cout << "I am a Base\n"; }
};
 
class Derived: public Base
{
public:
    Derived(int value)
        : Base(value)
    {
    }
};
int main()
{
    Base base(5);
    base.identify();
 
    Derived derived(7);
    derived.identify();
 
    return 0;
}
```
derived class는 identify라는 member function이 없습니다. 하지만 base class에 있기 때문에 호출할 수 있죠. `derived.identify()`의 출력은 무엇일지 한번 상상해 보세요.

다른 예제)
``` c++
class Base
{
protected:
    int m_value;
 
public:
    Base(int value)
        : m_value(value)
    {
    }
 
    void identify() { std::cout << "I am a Base\n"; }
};
 
class Derived: public Base
{
public:
    Derived(int value)
        : Base(value)
    {
    }
	void identify() { std::cout << "I am a Derived\n";}
};
int main()
{
    Base base(5);
    base.identify();
 
    Derived derived(7);
    derived.identify();
 
    return 0;
}
```
Base와 Derived 모두가 member function으로 identify()를 가지고 있습니다. 이 경우에 base에 identify가 있어도 compiler가 Derived에서 먼저 identify() 함수를 찾겠죠. 이때의 출력을 예상해 보세요. 

``` c++
class Derived: public Base
{
public:
    Derived(int value)
        : Base(value)
    {
    }
 
    int GetValue() { return m_value; }
 
    void identify()
    {
        Base::identify(); // call Base::identify() first
        std::cout << "I am a Derived\n"; // then identify ourselves
    }
};
```
> inheritance는 이런 것도 가능합니다. base class의 member function에 기능을 추가하고  싶을땐 Base::identify를 호출해 보세요. ::라는 scope quaulifier을 class inheritance에서도 사용할 수 있습니다. :smiley:

class가 friend function을 사용할 때도 비슷한 일을 할 수 있습니다.

``` c++
class Base
{
private:
	int m_value;
 
public:
	Base(int value)
		: m_value(value)
	{
	}
 
	friend std::ostream& operator<< (std::ostream &out, const Base &b)
	{
		out << "In Base\n";
		out << b.m_value << '\n';
		return out;
	}
};
 
class Derived : public Base
{
public:
	Derived(int value)
		: Base(value)
	{
	}
 
	friend std::ostream& operator<< (std::ostream &out, const Derived &d)
	{
		out << "In Derived\n";
		// static_cast Derived to a Base object, so we call the right version of operator<<
		out << static_cast<Base>(d); 
		return out;
	}
};
 
int main()
{
	Derived derived(7);
 
	std::cout << derived;
 
	return 0;
}
```

inheritance에서 derived는 access specifier을 바꿀 수도 있습니다.

``` c++
#include <iostream>
class Base
{
public:
	int m_value;
};
 
class Derived : public Base
{
private:
	using Base::m_value;
 
public:
	Derived(int value)
	// We can't initialize m_value, since it's a Base member (Base must initialize it)
	{
		// But we can assign it a value
		m_value = value;
	}
};
 
int main()
{
	Derived derived(7);
 
	// The following won't work because m_value has been redefined as private
	std::cout << derived.m_value;
 
	return 0;
}
```

>하지만 inaccessible한 경우에는 using을 이용해 access specifier을 바꿀 수 없습니다.

 inherit된 member function을 숨길 수도 있습니다. 첫번째로 단순하게 public에서 private으로 옮기는 방법이 있습니다.

``` c++
#include <iostream>
class Base
{
public:
	int m_value;
};
 
class Derived : public Base
{
private:
	using Base::m_value;
 
public:
	Derived(int value)
	// We can't initialize m_value, since it's a Base member (Base must initialize it)
	{
		// But we can assign it a value
		m_value = value;
	}
};
 
int main()
{
	Derived derived(7);
 
	// The following won't work because m_value has been redefined as private
	std::cout << derived.m_value;
 
	return 0;
}
```

두번째로, member function에 deleted라고 표시하는 방법이 있습니다.

``` c++
#include <iostream>
class Base
{
private:
	int m_value;
 
public:
	Base(int value)
		: m_value(value)
	{
	}
 
	int getValue() { return m_value; }
};
 
class Derived : public Base
{
public:
	Derived(int value)
		: Base(value)
	{
	}
 
 
	int getValue() = delete; // mark this function as inaccessible
};
 
int main()
{
	Derived derived(7);
 
	// The following won't work because getValue() has been deleted!
	std::cout << derived.getValue();
 
	return 0;
}
```

inheritance의 길은 끝이 없습니다. inheritance 중 multiple inheritance에 대해서 배워보겠습니다.

simple example)

``` c++
#include <string>
 
class Person
{
private:
    std::string m_name;
    int m_age;
 
public:
    Person(std::string name, int age)
        : m_name(name), m_age(age)
    {
    }
 
    std::string getName() { return m_name; }
    int getAge() { return m_age; }
};
 
class Employee
{
private:
    std::string m_employer;
    double m_wage;
 
public:
    Employee(std::string employer, double wage)
        : m_employer(employer), m_wage(wage)
    {
    }
 
    std::string getEmployer() { return m_employer; }
    double getWage() { return m_wage; }
};
 
// Teacher publicly inherits Person and Employee
class Teacher: public Person, public Employee
{
private:
     int m_teachesGrade;
 
public:
    Teacher(std::string name, int age, std::string employer, double wage, int teachesGrade)
        : Person(name, age), Employee(employer, wage), m_teachesGrade(teachesGrade)
    {
    }
};
```

multiple inheritance를 하면 어려개의 부모 class를 가진 자식 class를 만들 수 있습니다. 하지만 부모 class가 완전히 독립적이지 않는 한 문제가 발생하게 됩니다...
``` c++
#include <iostream>
 
class USBDevice
{
private:
    long m_id;
 
public:
    USBDevice(long id)
        : m_id(id)
    {
    }
 
    long getID() { return m_id; }
};
 
class NetworkDevice
{
private:
    long m_id;
 
public:
    NetworkDevice(long id)
        : m_id(id)
    {
    }
 
    long getID() { return m_id; }
};
 
class WirelessAdapter: public USBDevice, public NetworkDevice
{
public:
    WirelessAdapter(long usbId, long networkId)
        : USBDevice(usbId), NetworkDevice(networkId)
    {
    }
};
 
int main()
{
    WirelessAdapter c54G(5442, 181742);
    std::cout << c54G.getID(); // Which getID() do we call?
 
    return 0;
}
```

어떤 getID를 호출해야 되는지 알수없는 compiler가 불만을 제기할 것입니다. 물론 여러분들은 `c54G.USBDevice::getID()`라고 scope specifier를 달아 줘서 해결할 수도 있습니다. 이건 간단한 문제였지만 정말 많이 얽히고섥히게 되면 심각한 문제가 될 수도 있습니다.

조금 더 복잡한 케이스를 한번 보겠습니다. 소위 '다이아몬드' 문제입니다.

``` c++
class PoweredDevice
{
};
 
class Scanner: public PoweredDevice
{
};
 
class Printer: public PoweredDevice
{
};
 
class Copier: public Scanner, public Printer
{
};
```
물론 아까처럼 explicit scope specifier를 통해 해결할 수도 있지만, 사실 그렇게 모든 일을 하면 피곤해집니다. 사실 이런 multiple inheritance는 많은 경우 지양해야 합니다. 앞으로 프로그래밍의 숙련도가 쌓이면서 multiple inheritance를 활용해야 하는 경우가 생긴다면, 혹시 single inheritance로 해결할 수 없는 문제인지, 아니면 multiple inheritance를 깔끔하게 활용할 수 있는지 고민해 보세요.

### pointer and references to the base class
base class에 pointer나 reference를 사용할 수 있습니다. 또한, base class의 포인터나 reference도 derived로 설정할 수 있습니다. 하지만, base class의 pointer와 reference이기 때문에 derived의 base 부분만 볼 수 있습니다.
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
    std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
 
    Derived &rDerived{ derived };
    std::cout << "rDerived is a " << rDerived.getName() << " and has value " << rDerived.getValue() << '\n';
 
    Derived *pDerived{ &derived };
    std::cout << "pDerived is a " << pDerived->getName() << " and has value " << pDerived->getValue() << '\n';
 
    return 0;
}
```

``` c++
int main()
{
    Derived derived{ 5 };
 
    // These are both legal!
    Base &rBase{ derived };
    Base *pBase{ &derived };
 
    std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
    std::cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
    std::cout << "pBase is a " << pBase->getName() << " and has value " << pBase->getValue() << '\n';
 
    return 0;
}
```

**have fun!**

### EOF
