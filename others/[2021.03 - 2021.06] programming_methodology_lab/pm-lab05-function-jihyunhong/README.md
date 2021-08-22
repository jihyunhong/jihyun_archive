
# Functions and Scopes
담당조교 : 김종민 \
이메일 : jongmin.kim@scale.snu.ac.kr \
2020년 3월 19일 금요일

참고자료: learncpp.com Ch.2 & Ch.6

## 함수 (Functions)
한번 잘 만든 함수는 에러를 발생시키지 않으므로 클린한 프로그램을 만드는 데 도움을 줍니다. 또한 함수는 내부의 코드에 대한 이해를 필요없게 합니다. `add()`같은 경우가 그러한데, `add`를 보면 함수의 functionality를 알 수 있으므로 함수의 내부에서 구현된 코드를 몰라도 함수의 기능만 알아내서 사용할 수 있습니다.

매번 코드를 새로 짤 필요 없이, 함수를 잘 만들어서 필요할 때마다 함수를 호출해서 사용하는 것이 중요합니다.

``` c++
#include <iostream> // for std::cout
 
// Definition of user-defined function doPrint()
void doPrint() // doPrint() is the called function in this example
{
    std::cout << "In doPrint()\n";
}
 
// Definition of function main()[function]
int main()
{
    std::cout << "Starting main()\n";
    doPrint(); // Interrupt main() by making a function call to doPrint().  main() is the caller.
    std::cout << "Ending main()\n"; // this statement is executed after doPrint() ends
 
    return 0;
}
```
>함수 이름 전에 적혀있는 `int`, `double` 등은 함수의 return type입니다. `void`는 반환값(return value)이 없음을 나타냅니다. 함수를 만들 때 return type을 설정해 줌으로써 함수가 어떤 타입의 값을 **caller**에게 전해줄 것인지 정할 수 있습니다.

>위와 같이 function `doPrint`를 define해 놓는다면 필요할때마다 호출해서 사용할 수 있습니다. 특정 기능을 함수로 만들어 놓고 필요할 때마다 호출해서 사용할 수 있으므로 코드를 간결하게 만들 수 있습니다. 



### 함수를 호출하는 함수
```c++
#include <iostream> // for std::cout
 
void doB()
{
    std::cout << "In doB()\n";
}
 
 
void doA()
{
    std::cout << "Starting doA()\n";
 
    doB();
 
    std::cout << "Ending doA()\n";
}
 
// Definition of function main()
int main()
{
    std::cout << "Starting main()\n";
 
    doA();
 
    std::cout << "Ending main()\n";
 
    return 0;
}
```
>함수는 함수를 호출할 수도 있습니다.(심지어 자기자신을 호출(recursive) 할 수도 있습니다!) 함수 안에서 다른 함수를 호출해서 사용하는 것은 복잡한 기능을 가진 함수를 만드는 데에 도움이 됩니다. 우리는 귀찮게 함수를 똑같은 코드를 중복해서 만들 필요 없이 한번 잘 정의된 함수를 재사용해서 다른 함수를 만드는 데 쓸 수 있습니다.

### 함수의 parameter와 return value
아래 `getValueFromUser` 함수를 보세요. integer(정수)를 받아서 2를 곱해주는 함수를 만들려고 합니다. `int getValueFromUser()`와 같이 return  type을 **int**로 설정해 주고, `return input;`에서 처럼 **int 값**을 (혹은 int값을 가진 data)를 return해주면 됩니다.

```c++
#include <iostream>
 
int getValueFromUser()
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;  
 
	return input;
}
 
int main()
{
	int num { getValueFromUser() };
 
	std::cout << num << " doubled is: " << num * 2 << '\n';
 
	return 0;
}
```

function이 return을 통해서 결과값을 반환하듯이, input을 가질 수도 있습니다. 이러한 input을 function은 **parameter**를 통해서 구현합니다. parameter를 통해 input을 받기 위해서는, 몇가지 형식을 따라야 합니다. 먼저 data의 type을 미리 지정해주어야 합니다.

```c++
// This function takes no parameters
// It does not rely on the caller for anything
void doPrint()
{
    std::cout << "In doPrint()\n";
}
 
// This function takes one integer parameter named x
// The caller will supply the value of x
void printValue(int x)
{
    std::cout << x  << '\n';
}
 
// This function has two integer parameters, one named x, and one named y
// The caller will supply the value of both x and y
int add(int x, int y)
{
    return x + y;
}

```
> **argument**는 caller로부터 function에게 전달되는 값입니다. `int add(int x, int y)`에서 `x`, `y`는 function의 parameter이고, 실제 함수를 호출했을 시 `x`, `y`에 전달되는 값이 argument입니다.

위의 function의 기능을 조금 조합하면
```c++
include <iostream>
 
int getValueFromUser() // this function now returns an integer value
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;  
 
	return input; // added return statement to return input back to the caller
}
 
void printDouble(int value)
{
	std::cout << value << " doubled is: " << value * 2 << '\n';
}
 
int main()
{
	int num { getValueFromUser() };
 
	printDouble(num);
	
	printDouble(getValueFromUser());
 
	return 0;
}
```

>`main`의 `printDouble(getValueFromUser());`를 보세요. argument를 return value로 설정할 수 있습니다.


## Scopes
variable을 기능에 따라 여러가지로 나눌 수 있습니다. variable을 한번 정의한 이후로, variable이 유효할 때까지를 variable의 scope라고 합니다. variable은 scope를 벗어나면 보통 메모리에서 삭제되거나 접근할 수 없습니다.

* scope example 1)
``` c++
#include <iostream>
 
void doSomething()
{
    std::cout << "Hello!\n";
}
 
int main()
{
    int x{ 0 }; // x's lifetime begins here
 
    doSomething(); // x is still alive during this function call
 
    return 0;
} // x's lifetime ends here
```

* scope example 2)
``` c++
#include <iostream>
 
int add(int x, int y) // x and y are created and enter scope here
{
    // x and y are visible/usable within this function only
    return x + y;
} // y and x go out of scope and are destroyed here
 
int main()
{
    int a{ 5 }; // a is created, initialized, and enters scope here
    int b{ 6 }; // b is created, initialized, and enters scope here
 
    // a and b are usable within this function only
    std::cout << add(a, b) << '\n'; // calls function add() with x=5 and y=6
 
    return 0;
} // b and a go out of scope and are destroyed here
```

* scope example 3)
``` c++
#include <iostream>
 
int add(int x, int y) // add's x and y are created and enter scope here
{
    // add's x and y are visible/usable within this function only
    return x + y;
} // add's y and x go out of scope and are destroyed here
 
int main()
{
    int x{ 5 }; // main's x is created, initialized, and enters scope here
    int y{ 6 }; // main's y is created, initialized, and enters scope here
 
    // main's x and y are usable within this function only
    std::cout << add(x, y) << '\n'; // calls function add() with x=5 and y=6
 
    return 0;
} // main's y and x go out of scope and are destroyed here
```


### forward declaration
밑의 프로그램은 function이 뒤에 있기 때문에 compile되지 않습니다.

``` c++
#include <iostream>
 
int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}
 
int add(int x, int y)
{
    return x + y;
}
```

여러분들의 프로그램이 많은 function들을 포함하고 있을 때, 프로그램 처음부터 많은 function들의 definition이 있을 경우 전체적인 프로그램 구조를 파악할 수 없게 합니다.

이런 경우 forward declaration을 활용하여 function prototype 만을 미리 적어두고, 뒤에 function의 definition을 적을 수 있습니다.

즉, forward declaration를 통해 declaration statement와 definition statement를 분리할 수 있습니다.

``` c++
#include <iostream>
 
int add(int x, int y); // forward declaration of add() (using a function prototype)
 
int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // this works because we forward declared add() above
    return 0;
}
 
int add(int x, int y) // even though the body of add() isn't defined until here
{
    return x + y;
}
```
> `int add(int, int);` 이렇게 적어도 상관없습니다. 편의에 따라 사용하면 됩니다.

> **Declaration(선언)** 과 **definition(정의)** 함수를 만드는 두 개의 과정입니다. Definition은 function 내부의 내용을 생성하는 작업입니다. Declaration은 function이라는 identifier가 존재한다고 컴파일러에게 말해주는 것입니다. 

>Declaration과 definition 개념은 function 뿐만 아니라 다른 identifier에도 적용할 수 있습니다. 간단한 data type인 int의 경우, `int x`는 declaration이면서 definition입니다.

## Preprocessor
`#include <iostream>`에서도 쓰였듯이 `#`은 C++에서 빈번하게 볼 수 있습니다. `#`은 구문이 preprocessor directive라는 것을 의미합니다. 컴파일을 공부하면서 배웠다시피, C++ 프로그램을 컴파일하는 과정에서 가장 먼저 preprocessing을 합니다. preprocessing은, 쉽게는 preprocessor directive를 code로 바꾸는 것이라고 이해할 수 있습니다.
`#include`를 통해서는 우리가 사용하고 싶은 라이브러리들을 코드 내부에 포함시킵니다.

### `define`
`define`은 여러가지 용도로 사용할 수 있습니다. 먼저 가장 간단하게 constant를 대체하는 경우에도 쓰입니다.
``` c++
#include <iostream>
 
#define MY_NAME "Alex"
 
int main()
{
    std::cout << "My name is: " << MY_NAME;
 
    return 0;
}
```
`define`의 다른 용도로 조건문(conditional statement)로 사용할 수 있습니다.

``` c++
#include <iostream>
 
#define PRINT_JOE
 
int main()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // if PRINT_JOE is defined, compile this code
#endif
 
#ifdef PRINT_BOB
    std::cout << "Bob\n"; // if PRINT_BOB is defined, compile this code
#endif
 
    return 0;
}
```
> 이런식으로 `ifdef`, `ifndef`, `endif`를 사용하여 conditional compilation이 가능합니다.

* 하지만 #define을 이용한 macro의 사용은 꼭 필요하지 않은 이상 사용하지 않는 것이 좋습니다.
* const variable이나 inline function (추후 설명) 등을 이용합시다.

## header files
여러분의 모든 코드가 하나의 .cpp파일에 있으면 한 파일의 길이가 너무 길어질 것입니다. `#include <iostream>`에서 보았듯이 파일에 없는 코드들을 사용할 수 있는 방법이 있습니다. 비단 `<iostream>`처럼 외부의 코드가 아니라 여러분들이 직접 짠 코드들도 이런 방식으로 연결해서 사용할 수 있습니다.

간단한 예를 들어서, 여러분들이 함수를 main.cpp에 define하는 경우를 들어 봅시다. `main`은 프로그램이 시작하는 곳이므로, function에 대한 정보를 일일이 적으면 main의 내용이 너무 커집니다.

[header.cpp]( src/header.cpp)
```cpp
#include <iostream>

#include "add.h" // Insert contents of add.h at this point. Note use of double quotes here.

int main()
{
  std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
  return 0;
}
```
[add.cpp](src/add.cpp)
```cpp
#include "add.h" // Insert header file containing declaration

int add(int x, int y) // define here!
{
  return x + y;
}
```
[add.h](src/add.h)
```cpp
#ifndef ADD_H
#define ADD_H

int add(int x, int y); // function prototype for add.h -- don't forget the semicolon!

#endif
```

여기서 `#ifndef ADD_H`, `#define ADD_H`, `#endif`와 같은 preprocessor directive를 활용하여 header guard를 만들 수 있습니다. 이러한 header guard를 만드는 이유는 header file을 단 한번만 include하기 위해서입니다. 위에서처럼 ADD_H로 파일의 이름을 쓰는 경우도 있고, 파일 이름이 겹칠 경우엔 프로젝트_디렉토리_파일이름으로 만들기도 합니다.

## Compound statements(blocks)

* **Compound statement** : Compiler에서 마치 single statement처럼 해석되는 0개 이상의 statement들의 집합.(*block* 또는 *block statement*라고도 함.)
	- `{`로 시작해서 `}`로 끝남. block은 마지막에 `;`붙일 필요 없음.


### Blocks inside other blocks

```c++
int add(int x, int y)
{ // block
    return x + y;
} // end block
 
int main()
{ // outer block
 
  // multiple statements
  int value {};
 
  { // inner(nested) block
    add(3, 4);
  } // end inner(nested) block
 
  return 0;
 
} // end outer block
```
* 이런식으로 block이 여러번 겹치는 경우, 밖에 있는 block을 *outer block*, 안에 있는 block을 *inner block* 또는 *nested block*이라고 부름.

## Local variables

* **Local variable**을 딱 한마디로 정의내릴 수는 없지만, 일반적으로는 **특정 scope**안에 속해있는 variable들을 통칭함.

### Local variables have block scope

* Local variable들은 *block scope*를 가지고 있음.
	- 즉, local variable들은 정의되는 시점부터 해당 *block*의 끝부분까지 *in scope*되어 있음.

```c++
int main()
{
  int i { 5 }; // i enters scope here
  double d { 4.0 }; // d enters scope here
 
  return 0;
} // i and d go out of scope here
```

* *Function parameter* 경우에는 function body에 속해있지는 않지만, 일반적으로 *function body scope*안에 정의되어 있다고 취급.

```c++
int max(int x, int y) // x and y enter scope here
{
  // assign the greater of x or y to maxNum
  int maxNum{ (x > y) ? x : y }; // maxNum enters scope here
 
  return maxNum;
} // x, y, and max leave scope here here
```

### All variable names within a scope must be unique

* 어떤 특정 scope안에서 variable은 항상 **유일**하게 선언되어있어야함.

```c++
void someFunction(int x)
{
  int x{}; // compilation failure due to name collision with function parameter
}
 
int main()
{
  return 0;
}
```

* 위 코드는 error! 왜일까?
	> Variable x가 이미 **function parameter**로서 **function body scope**에 선언이 되어있는데 한 번 더 선언되어 있기 때문.

### Local variable have automatic storage duration

* **Storage duration** : variable이 언제 생성되고 언제 사라지는지에 대한 규칙을 의미. 그냥 *duration*이라고도 함.
	- **Storage duration**이 variable의 **lifetime**을 결정.

* Local variable의 특징 중 하나는 **automatic storage duration**. 즉, *local variable*이 선언될 때 자동으로 생성되고, 해당 scope의 끝에 다다르면 자동으로 사라짐.
	- 그래서 *automatic variable*이라고도 불림.

### Local variables in nested blocks

```c++
#include <iostream>

int main()
{ // outer block
 
  int x { 5 }; // x enters scope and is created here
 
  { // nested block
    int y { 7 }; // y enters scope and is created here
 
    // x and y are both in scope here
    std::cout << x << " + " << y << " = " << x + y << '\n';
  } // y goes out of scope and is destroyed here
 
  // y can not be used here because it is out of scope in this block
 
  return 0;
} // x goes out of scope and is destroyed here
```

* 아래와 같은 코드에선?

```c++
int main()
{
  int x { 2 }; // local variable, no linkage
 
  {
    int x { 3 }; // this identifier x refers to a different object than the previous x
  }
 
  return 0;
}
```

### Variables should be defined in the most limited scope

* Variable은 제일 최소한의 scope안에 선언되는 것이 좋음.

## Introduction to global variables

* **Global variables** : Function 밖에 선언되어 있는 variable.

### Declaring and naming global variables

* 일반적으로 global variable은 `includes` 바로 밑, 코드 맨 위에 선언됨.

```c++
#include <iostream>
 
// Variables declared outside of a function are global variables
int g_x {}; // global variable g_x
 
void doSomething()
{
  // global variables can be seen and used everywhere in the file
  g_x = 3;
  std::cout << g_x << '\n';
}
 
int main()
{
  doSomething();
  std::cout << g_x << '\n';
 
  // global variables can be seen and used everywhere in the file
  g_x = 5;
  std::cout << g_x << '\n';
 
  return 0;
}
// g_x goes out of scope here
```

* 위 코드에서처럼 일반적으로 global variable을 선언할 때는 변수명 앞에 `g_` prefix를 붙여서 선언.

### Global variables have file scope and static duration

* Global variable은 일반적으로 **file scope** or **global scope** or **global namespace scope**를 가짐.
	- 즉, code 어느 부분에서도 **global variable**에는 접근 가능. 이를 *visible*이라고 표현.

*  **Static duration** : Global variable은 프로그램이 시작할 때 생성되고, 프로그램이 끝나면 사라짐.
	- 이러한 **static duration**을 가지는 variable을 **static variable**이라고 함.
		+ **Static variable**은 *local variable*과 달리 별도로 초기화를 하지 않아도 0으로 초기화됌.

### Constant global variables

* Local variable처럼 global variable도 `constant`로 선언 가능.
	- `constant`로 선언하면 반드시 선언할 때 **초기화**를 함께 해주어야됌.

```c++
#include <iostream>
 
const int g_x; // error: constant variables must be initialized
constexpr int g_w; // error: constant variables must be initialized
 
const int g_y { 1 };  // const global variable g_y, initialized with a value
constexpr int g_z { 2 }; // constexpr global variable g_z, initialized with a value
 
void doSomething()
{
  // global variables can be seen and used everywhere in the file
  std::cout << g_y << '\n';
  std::cout << g_z << '\n';
}
 
int main()
{
  doSomething();
 
  // global variables can be seen and used everywhere in the file
  std::cout << g_y << '\n';
  std::cout << g_z << '\n';
 
  return 0;
}
// g_y and g_z goes out of scope here
```

* **Non-constant global variable**은 왠만해선 사용하지 않는 것이 좋음! 이유에 대해서는 추후에 설명.

## Variable shadowing(name hiding)

### Shadowing of local variables

```c++
#include <iostream>
 
int main()
{ // outer block
  int apples { 5 }; // here's the outer block apples
 
  { // nested block
    // apples refers to outer block apples here
    std::cout << apples << '\n'; // print value of outer block apples
 
    int apples{ 0 }; // define apples in the scope of the nested block
 
    // apples now refers to the nested block apples
    // the outer block apples is temporarily hidden
 
    apples = 10; // this assigns value 10 to nested block apples, not outer block apples
 
    std::cout << apples << '\n'; // print value of nested block apples
  } // nested block apples destroyed
 
 
  std::cout << apples << '\n'; // prints value of outer block apples
 
  return 0;
} // outer block apples destroyed
```

* 위 코드 실행 결과는?

> 5   
> 10   
> 5

```c++
#include <iostream>
 
int main()
{ // outer block
  int apples{ 5 }; // here's the outer block apples
 
  { // nested block
    // apples refers to outer block apples here
    std::cout << apples << '\n'; // print value of outer block apples
 
    // no inner block apples defined in this example
 
    apples = 10; // this applies to outer block apples
 
    std::cout << apples << '\n'; // print value of outer block apples
  } // outer block apples retains its value even after we leave the nested block
 
  std::cout << apples << '\n'; // prints value of outer block apples
 
  return 0;
} // outer block apples destroyed
```

* 위 코드 실행 결과는?

> 5   
> 10   
> 10

### Shadowing of global variables

```c++
#include <iostream>
int value { 5 }; // global variable
 
void foo()
{
  std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
}
 
int main()
{
  int value { 7 }; // hides the global variable value until the end of this block
 
  ++value; // increments local value, not global value
 
  std::cout << "local variable value: " << value << '\n';
 
  foo();
 
  return 0;
} // local value is destroyed
```

* 위 코드 실행 결과는?

> local variable value: 8   
> global variable value: 5

* 하지만 global variable이 *global namespace*라는 점을 이용해서 `scope operator(::)`를 사용하여서 *global variable*에 접근 가능.

```c++
#include <iostream>
int value { 5 }; // global variable
 
int main()
{
  int value { 7 }; // hides the global variable value
  ++value; // increments local value, not global value
 
  --(::value); // decrements global value, not local value (parenthesis added for readability)
 
  std::cout << "local variable value: " << value << '\n';
  std::cout << "global variable value: " << ::value << '\n';
 
  return 0;
} // local value is destroyed
```

* 위 코드 실행 결과는?

> local variable value: 8   
> global variable vlaue: 4

* 요약: 같은 이름의 variable은 가장 좁은 scope의 것이 선택됨.
* 이러한 *variable shadowing*은 왠만해서 사용하지 않는 것이 좋음.

## Internal linkage (static)

* **Internal linkage** : Identifier가 하나의 file안에서는 접근가능하지만, 다른 파일들에서는 접근 불가능한 것.

### Global variables with internal linkage

* **Global variable with internal linkage**를 **internal variable**이라고 함.

* `static` : *Non-constant* global variable(기본적으로 **external**)을 *internal*하게 만들기 위해서 쓰이는 keyword.

```c++
// non-constant globals have external linkage by default,
// but can be given internal linkage via the static keyword
static int g_x; 

const int g_y { 1 }; // const globals have internal linkage by default
constexpr int g_z { 2 }; // constexpr globals have internal linkage by default
 
int main()
{
  return 0;
}
```

* 아래 코드에서 다른 예를 살펴보자.

internal_ex.cpp : 
```c++
constexpr int g_x { 2 }; // this internal g_x is only accessible within internal_ex.cpp
```

internal_main.cpp : 
```c++
#include <iostream>
 
static int g_x { 3 }; // this separate internal g_x is only accessible within internal_main.cpp
 
int main()
{
  std::cout << g_x << '\n'; // uses internal_main.cpp's g_x, prints 3
 
  return 0;
}
```
* 만약 위 두 파일을 한꺼번에 묶어서 실행시켰을 때 프로그램의 결과는?

	> 3

### Functions with internal linkage

* Function 또한 variable과 마찬가지로 linkage를 설정할 수 있음.

* Function은 기본적으로 **external linkage**이지만 `static` keyword를 사용함으로써 **internal linkage**로 사용할 수 있음.

a.cpp : 
```c++
// This function is declared as static, and can now be used only within this file
// Attempts to access it from another file via a function forward declaration will fail
static int add(int x, int y)
{
  return x + y;
}
```

main.cpp : 
```c++
#include <iostream>
 
int add(int x, int y); // forward declaration for function add
 
int main()
{
  std::cout << add(3, 4) << '\n';
 
  return 0;
}
```

* 만약 위 두 파일을 한꺼번에 묶어서 실행한다면?
	> **add** 함수가 `static`으로 선언되어 있기 때문에 a.cpp 밖에서는 접근할 수 없으므로 error.

## External linkage

* **External linkage** : Identifier가 선언된 파일 뿐만 아니라, 다른 파일들에서도 접근 가능한 것.
	- 진정한 의미의 *global*이라고 할 수 있음.

### Functions have external linkage by default

external_ex.cpp : 
```c++
#include <iostream>
 
void sayHi() // this function has external linkage, and can be seen by other files
{
  std::cout << "Hi!";
}
```

external_main.cpp :
```c++
void sayHi(); // forward declaration for function sayHi, makes sayHi accessible in this file

int main()
{
  sayHi(); // call to function defined in another file, linker will connect this call to the function definition

  return 0;
}
```

* 위 두 개의 코드를 묶어서 실행하면?
	> Hi!

### Global variables with external linkage

* **Global variables with external linkage**를 **external variables**이라고도 함.

* `extern` : Global variable을 *external linkage*하게 만들기 위해서 사용하는 keyword.

```c++
int g_x { 2 }; // non-constant globals are external by default
 
extern const int g_y { 3 }; // const globals can defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can defined as extern, making them external (but this is useless, see the note in the next section)
 
int main()
{
  return 0;
}
```

### Variable forward declarations via the extern keyword

* 위의 `sayHi()`함수가 있는 코드에서처럼 다른 파일에 있는 무언가를 가져다 쓰기 위해선 **forward declaration**이 필요.
	- Variable의 **forward declaration**을 `extern` keyword가 해줌.

a.cpp : 
```c++
// Global variable definitions
int g_x { 2 }; // Non-constant globals have external linkage by default
extern const int g_y { 3 }; // This extern gives g_y external linkage
```

main.cpp : 
```c++
#include <iostream>

// This extern is a forward declaration of a variable named g_x that is defined somewhere else
extern int g_x;

// This extern is a forward declaration of a const variable named g_y that is defined somewhere else
extern const int g_y; 
 
int main()
{
  std::cout << g_x; // Prints 2
 
  return 0;
}
```

* 지금까지의 내용을 정리하면... `extern` keyword는 두가지 의미를 가지고 있음.
	1. Give the variable external linkage
	2. Forward declaration for an external variable that is defined somewhere else.

	> 뒷부분에서 이와 관련된 내용을 좀 더 세심히 다룰 예정.

## Why global variables are evil

* 흔히들 개발자들 사이에서는 **global variable은 무조건 피해야한다**라는 암묵적인 룰이 존재.
  > 여기서 말하는 **global variable**이란 **non-const global variable**을 의미.

## Static local variables

### Static local variables

* *Local variable*에 `static` keyword를 쓰면 **automatic duration**이었던 것을 **static duration**으로 바꿔줌.

Automatic duration example : 
```c++
#include <iostream>

void incrementAndPrint()
{
  int value{ 1 }; // automatic duration by default
  ++value;
  std::cout << value << '\n';
} // value is destroyed here

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```
* 위 코드를 실행하면?
> 2   
> 2   
> 2   

Static duration example : 
```c++
#include <iostream>
 
void incrementAndPrint()
{
  static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
  ++s_value;
  std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope
 
int main()
{
  incrementAndPrint();
  incrementAndPrint();
  incrementAndPrint();
 
  return 0;
}
```

* 위 코드를 실행하면?
> 2   
> 3   
> 4   

* 일반적으로  **static local variable**은 변수명 앞에 `s_`를 붙여서 선언.

* **Static local variable**은 그럼 언제 쓰이는걸까?

```c++
int generateID()
{
  static int s_itemID{ 0 };
  return s_itemID++; // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
}
```
  - 위 코드와 같이 전체 프로그램에서 unique한 ID

## Scope, duration, and linkage summary

* [ 링크 ](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/) 참조

-------------------------------------------
 이 부분부터는 reading material입니다. 한번 읽어보시고 실습 수업에서 커버하진 않습니다.

## Appendix 1. namespace
C++ 프로그램은 수많은 영역(block)으로 구성되어 있습니다. 이러한 block의 예로 함수의 block이 있을 수 있습니다. 프로그램이 동작하는 과정을 간단하게 말하면 block들을 호출하고, block을 실행시키는 것이라고 볼 수도 있습니다. 

지금부터 함수의 block을 배웠듯이, namespace라는 block을 배워 볼 것입니다.
``` c++
#include <iostream>
 
int main()
{
    std::cout << "Hello world!"; // when we say cout, we mean the cout defined in the std namespace
    return 0;
}
```
`std`라는 것 또한 하나의 namespace입니다. 우리는 `std`라는 namespace의 변수와 함수등을 사용하기 위해 `::`라는 범위 확인 연산자(scope resolution operator)를 사용합니다. 즉, `std::cout`은 "`std`라는 namespace에 있는 `cout`이라는 변수를 사용한다"라고 번역할 수 있습니다.

### User-Defined Namespaces

* **Naming collision** : 같은 *scope*안에 *identical identifier*가 여러 개 있어서 compiler입장에서 어느 *identifier*를 사용해야될지 모르는 경우 error를 일으킴.

foo.cpp : 
```c++
// This doSomething() adds the value of its parameters
int doSomething(int x, int y)
{
	return x + y;
}
```

goo.cpp : 
```c++
// This doSomething() subtracts the value of its parameters
int doSomething(int x, int y)
{
  return x - y;
}
```

main.cpp : 
```c++
#include <iostream>

int doSomething(int x, int y); // forward declaration for doSomething

int main()
{
  std::cout << doSomething(4, 3) << '\n'; // which doSomething will we get?
  return 0;
}
```
* 위와 같은 경우에서 만약에 전체 프로그램이 *foo.cpp*나 *goo.cpp* 둘 중 하나만을 포함하고 있다면 아무 문제가 안되겠지만 둘을 모두 포함하고 있다면 *main.cpp*에서 실행되는 doSomething()함수가 두 파일 중 어느 파일에 있는 함수를 실행시켜야되는지 알 수가 없음.

* 제일 쉬운 방법은?
	- 함수의 이름을 바꿔주는 것.
		+ 하지만 이 방법은 프로그램 내에 있는 모든 함수들의 이름을 다 따라서 바꿔줘야하므로 매우 비효율적.

* 그래서 이러한 error와 비효율을 방지하고자 `namespace`라는 개념이 나옴.

### Defining your own namespaces

* **User-defined namespaces** : 사용자가 직접 만든 `namespace`.
	> 일반적으로 `namespace` 이름은 다 소문자로 작성.

### Accessing a namespace with the scope resolution operator(::)
* 위 코드를 아래와 같이 수정할 수 있음.

```c++
#include <iostream>
 
namespace foo // define a namespace named foo
{
  // This doSomething() belongs to namespace foo
  int doSomething(int x, int y)
  {
    return x + y;
  }
}
 
namespace goo // define a namespace named goo
{
  // This doSomething() belongs to namespace goo
  int doSomething(int x, int y)
  {
    return x - y;
  }
}
 
int main()
{
  std::cout << foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace foo
  std::cout << goo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace goo
  return 0;
}
```

### Scope resolution with no prefix

* **Scope resolution operator**를 prefix없이 쓴다면 **global namespace**를 찾음.

```c++
#include <iostream>
 
void print() // this print lives in the global namespace
{
	std::cout << " there\n";
}
 
namespace foo
{
	void print() // this print lives in the foo namespace
	{
		std::cout << "Hello";
	}
}
 
int main()
{
	foo::print(); // call foo::print()
	::print(); // call print() in global namespace (same as just calling print() in this case)
 
	return 0;
}
```

### Nested namespaces

```c++
#include <iostream>
 
namespace foo
{
  namespace goo // goo is a namespace inside the foo namespace
  {
    int add(int x, int y)
    {
      return x + y;
    }
  }
}
 
int main()
{
  std::cout << foo::goo::add() << '\n';
  return 0;
}
```

### When you should use namespaces

* 개발자가 본인이 작성한 코드를 다른 사람에게 공유해야 될 시 꼭 `namespace`를 설정하여서 공유를 해야지만 **name collision**등의 error를 방지할 수 있음.
