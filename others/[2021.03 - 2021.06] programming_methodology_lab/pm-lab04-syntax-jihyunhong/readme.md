430.211 프로그래밍 방법론 : chapter 1,4,5
===========================

담당조교 : 남화용

이메일 : hwayong.nam@scale.snu.ac.kr

2021년 3월 15일 금요일

chapter 1
===========================

## Introduction

* 안녕하세요 프로그래밍 방법론 수업에 오신 걸 환영합니다. 지금부터 C++을 프로그래밍하는데 필요한 여러가지 주제들에 대해서 알아볼 것입니다. 
* C++ 전체를 깊게 이해하기에는 C++가 너무 광범위하기 때문에, 수업에서는 각각의 주제를 너무 깊지 않게 소개할 것입니다.
* 수업에서 소개한 내용을 이해했다면 기본적인 C++ 프로그래밍을 할 수 있고, 다른 자료를 통해서 쉽게 다른 C++ 개념들 또한 배울 수 있습니다. 
* 이번 시간에 배울 내용은 Syntax, Fundamental data types 및 Operators입니다. 

## Basic structure of a program

### Instruction and Statement

* C++ 프로그램들은 컴퓨터가 무엇을 해야할지 알려주는 **Instruction**(명령어)들로 이루어져 있습니다. 명령어를 통해 컴퓨터에게 일을 지시하고, 컴퓨터는 사람을 대신해서 일을 해줍니다. 
* Instruction들 중에서도 가장 흔한 타입은 **statement**입니다. statement는 C++에서 가장 작은 computation unit입니다. 대화를 할 때 문장과 비슷하게 생각하시면 됩니다. 대부분의 statement들은 그 끝을 알려주기 위해서 **semicolon (`;`)** 을 사용합니다. 

> semicolon을 보고 마침표와 같이 "아, statement가 끝났구나" 생각하시면 됩니다. 

### main function

* `main` function은 C++에서 가장 특별한 function입니다. 모든 C++ 프로그램은 `main` function에서 시작해서 순서대로 실행합니다. 
* 또한 중간에 모종의 이유로 프로그램이 갑자기 끝나지 않았다면, `main` function의 끝에 도달하면 프로그램이 끝납니다. 
* 따라서 `main` 함수는 운영체제로 하여금 프로그램의 시작 지점을 알려주고, 운영체제는 main 에 있는 코드들을 실행하다가 `main` 함수가 끝나면 다시 운영체제에게 프로그램이 끝났음을 알려줍니다.

> 소스 코드는 기본적으로 위에서부터 아래 순서대로 실행되지만, 때로 다른 지점으로 점프를 하거나, 한 지점을 여러번 도는 등 다양한 실행 방식이 존재합니다.

### Basic code structure

``` c++ 
1  #include <iostream> 
2 
3  int main() 
4  {
5     std::cout << "Hello world!"; 
6     return 0; //statement
7  }
```

1. 첫번째 줄은 **preprocessor directive**(전처리 지시문)입니다. 위의 경우 preprocessor directive는 C++ library에서 우리가 사용하고 싶은 내용을 나타냅니다. 위의 예시에서 `iostream`은 우리가 `cout`을 사용하기 위해 필요합니다.
   즉, `#include <iostream>`은 `iostream`에 있는 내용을 사용할 것이라고 설정해주는 구문입니다.

2. 두번째 줄은 빈칸인데, 이런 경우에 컴파일러는 비어있는 줄을 무시합니다. 두번째 줄은 그냥 프로그래머가 코드를 보기 편하게 하기 위한 용도입니다.

3. 세번째 줄의 `int main()`은 우리가 `main`이라는 함수를 만들 것이라는 define statement입니다. 위에서 설명했듯이 모든 C++ 프로그램은 `main`을 가지고 있고, `main`에서 실행을 시작하고, 대체로 `main`의 마지막에서 프로그램이 종료됩니다.

4. 네번째, 일곱번째 줄은 `int main()`에서 `main` 함수를 만들 것이라는 statement와 함께, 함수의 내용을 적을 function body를 나타냅니다. function body는 `{}`와 같이 curly brace로 나타내고, `{`와 `}` 사이에 함수의 내용을 작성하게 됩니다.

>`{}` 두 개의 괄호가 의미하는 것은 하나의 영역(block)입니다. 지금처럼 함수의 내용을 block 안에 작성하였듯이, 괄호를 통해 block을 표시하고 그 안에 있는 내용들을 묶을 수 있습니다.

5. line 5는 `main`의 function body의 첫번째 statement입니다. `std::cout`은 character output을 나타내고, `<<` operator와 함께 console 창에 character(글자나 숫자)를 보내는 역할을 합니다. 프로그래머는 console 창에 보이는 output을 확인하여 프로그램의 동작 상태를 확인할 수 있습니다. 1에서 iostream이라는 라이브러리를 사용한다고 했는데, 이렇게 console창에 글자를 띄우기 위해서는 실제로 이보다 많은 줄의 코드가 필요합니다. 이미 구현해놓은 iostream 라이브러리를 통해 편하게 원하는 기능을 사용할 수 있습니다.

6. line 6는 return statement입니다. 실행 중인 프로그램이 종료된 후, 프로그램은 return 값을 운영체제에 반환합니다.위의 경우 `return 0;`을 통해 0을 반환합니다. 통상적으로 0은 프로그램이 정상적으로 동작했다는 것을 의미합니다. return statement 이후 프로그램이 종료됩니다. 
   이러한 return statement는 `main` 함수의 경우는 return값을 operating system에 반환하고, 그 외에도 함수 또한 return statement를 통해 함수의 실행결과를 반환합니다.

>영어 문장에도 문법이 있듯이, C++에도 문법이 있습니다. 이러한 문법을 어길 경우에(예를 들어 semicolon을 까먹었다던지) syntax error(문법 오류)가 발생합니다. syntatx error를 가진 program을 compile할 경우 compiler가 syntax error가 있기 때문에 compile할수 없다는 메시지를 남길 것입니다. 처음부터 error가 없는 program을 작성할 순 없지만, C++의 syntax에 유의하면서 조심스럽게 프로그램을 작성해 보세요.

#### syntax error가 있는 프로그램

``` c++ {.line-numbers}
#include <iostream>
 
int main()
{
   std::cout << "Hello world!"
   return 0
}
```

main 함수의 2줄 뒤에 ';'가 붙어 있지 않아 syntax error가 발생

### Comment

위에서 설명한 것처럼 C++는 프로그래머가 프로그램의 구조를 이해하기 편하게 하기 위한 많은 기능을 가지고 있습니다. 그 중에서도 comment 기능은 프로그램의 구조를 이해하기 편하게 만드는 가장 쉽고 강력한 툴입니다.
여러분들의 프로그램에서, 코드 근처에 comment를 남겨서 코드에 대한 설명을 남겨 보세요. comment(주석)은 단순히 `//` 또는 `/* */`를 사용하시면 됩니다.


#### Comment하는 방법 1 : `//`

``` c++
std::cout << "Hello world!\n";   // std::cout lives in the iostream library
std::cout << "It is very nice to meet you!\n"; // this is much easier to read
std::cout << "Yeah!\n";                        // don't you think so?
```

>한줄씩 comment할 때는 `//`를 활용해 보세요.

#### Comment하는 방법 2 : `/* */`

``` c++
/* This is a multi-line comment.
   This line will be ignored.
   So will this one. */
```

> comment가 길 경우 코멘트를 한 줄에 적지 마시고 `/* */`에 싸서 comment해 보세요.
> :satisfied:

#### Comment 예시

코드의 의미를 설명하는 경우

``` c++
// This program calculates the student's final grade based on his test and homework
scores.    	// line을 벗어나 comment로 처리되지 않음
    
// This function uses Newton's method to approximate the root of a given equation.
```

코드의 구조를 설명하는 경우

``` c++
// To generate a random item, we're going to do the following:
// 1) Put all of the items of the desired rarity on a list
// 2) Calculate a probability for each item based on level and weight factor
// 3) Choose a random number
// 4) Figure out which item that random number corresponds to
// 5) Return the appropriate item
```

> code를 comment할 수도 있는데, 이런 경우 C++ compiler는 그 코드를 무시합니다. 여러분들의 프로그램에서 특정 코드를 빼고 실행하고 싶을 때 코드를 comment해 보세요.

### Data

프로그램이 입력을 받고, 그에 따라 여러분들이 원하는 결과값을 출력할 때까지 프로그램은 특정 값들을 읽고, 바꾸고, 써야 합니다. 프로그램에서 이러한 값들을 data라고 합니다. 우리는 C++ 프로그램에서 data를 읽고, 처리하고, 저장합니다. 이러한 data들은 프로그램 내에서 생성할 수도 있고, 외부와(다른 파일, 프로그램이라던지, 인터넷 네트워크, 데이터베이스 등등) data를 주고받을 수도 있습니다.

여러분들의 메모리에는 여러가지 data들이 저장되어 있습니다. data들은 메모리 안에서 자신의 region을 차지하고 있습니다. data들은 메모리 안에서 값도 가지고, 데이터의 property에 관한 정보들도 가지고 있습니다.(데이터가 갖는 값 외에 그 데이터가 어떤 종류의 데이터인지 설명해 주는). C++ 는 메모리에 있는 data에 접근하기 위해 object라는 방법을 사용합니다. object는 메모리에 있는 region을 말합니다.

> 나중에 object가 여러 의미로 사용되면서 헷갈릴 수 있습니다. object는 변수 외에도 다양한 방법으로 활용되지만, 지금은 그냥 data에 접근하는 방법이구나 하고 이해하시면 됩니다. 

메모리에 있는 오브젝트에 이름이 있는 경우, 이것을 variable(변수)라고 말합니다. 또한 변수의 이름을 identifier라고 합니다.

#### definition of a variable

``` c++
int x; // define a variable named x, of type int
```

#### definition of multiple variables

1. 여기서 a, b가 variable들의 identifier(변수명)입니다.

``` c++
int a;
int b;
```

2. 여러 변수를 한번에 선언할 수도 있습니다.

``` c++
int a, b;
```

3. 변수를 선언하고 세미콜론을 붙여주세요.

``` c++
int a, int b; // wrong (compiler error)
 
int a, b; // correct
```

## variable assignment

변수에 value(값)을 assign하는 방법을 배울 겁니다. 변수는 처음 define하고 사라질 때까지 여러 값을 가질 수 있습니다.

### define a variable and then assign a value

``` c++
int width; // define an integer variable named width
width = 5; // copy assignment of value 5 into variable width
 
// variable width now has value 5
```

### change the value of the variable

``` c++
#include <iostream>
 
int main()
{
	int width;
	width = 5; // copy assignment of value 5 into variable width
 
	// variable width now has value 5
 
	width = 7; // change value stored in variable width to 7
 
	// variable width now has value 7
 
	return 0;
}
```

### 초기화(initialization)

* 변수가 정의되고 난 후, 혹은 정의되면서 초깃값을 지정받는 것을 초기화 (initialization) 라고 합니다. 
* c++에서는 나중에 값을 변경하는 것과 초기화를 구분하는데, 초기화를 하기 전까지 변수에 지정된 값을 사용해서는 안됩니다.
* 복잡한 변수에서 초기화는 때로 나중에 값을 변경하는 것과 매우 다른 의미를 가집니다. 

1. by copy initialization `=`

``` c++
int width = 5; // copy initialization of value 5 into variable width
```

2. by direct initialization `()`

``` c++
int width( 5 ); // direct initialization of value 5 into variable width
```

3. by brace initialization `{}`

``` c++
int width{ 5 }; // direct brace initialization of value 5 into variable width (preferred)

int height = { 6 }; // copy brace initialization of value 6 into variable height

int width{}; // zero initialization to value 0
```

4. explicit zero initialization vs zero initialization

- explicit zero initialization

``` c++
int x { 0 }; // explicit initialization to value 0
std::cout << x; // we're using that zero value
```

- zero initialization

``` c++
int x{}; // zero initialization
std::cin >> x; // we're immediately replacing that value
```

>copy, direct, brace 등 3가지 initialization이 있다는 사실만 알고 가시면 됩니다. 앞으로 c++를 접하다 보면 변수에 따라 3가지 initialization이 차이가 있다는 것을 알게 되실 겁니다. 변수에서 세가지 초기화가 어떻게 다른지 알아보고 적당한 초기화를 하는 것이 포인트입니다. 

#### cin and cout

``` c++
#include <iostream>  // for std::cout and std::cin
 
int main()
{
    std::cout << "Enter a number: "; // ask user for a number
    int x{}; // define variable x to hold user input
    std::cin >> x; // get number from keyboard and store it in variable x
    std::cout << "You entered " << x << '\n';
    return 0;
}
```

>`cin`과 `cout`은 iostream 라이브러리에서 제공하는 변수입니다. 두 변수를 이용해서 프로그램에 입력과 출력을 할 수 있습니다. 

#### uninitialized variable

``` c++
#include <iostream>
 
void doNothing(const int &x) // Don't worry about what &x is for now, we're just using it to trick the compiler into thinking variable x is used
{
}
 
int main()
{
    // define an integer variable named x
    int x; // this variable is uninitialized
 
    doNothing(x); // make compiler think we're using this variable
 
    // print the value of x to the screen (who knows what we'll get, because x is uninitialized)
    std::cout << x;
 
    return 0;
}
```

>uninitialized variable을 프로그램에 계속 남겨두는 것은 위험합니다. uninitialized variable의 값을 알 수 없으므로 프로그램이 우리가 예측하지 못하게 행동할 수 있습니다. 바로 초기화를 하지 않을 것 같다면, `{}`로 변수마다 디폴트로 지정되어 있는 초기화를 해 두면 좋습니다.



chapter 4
===========================

## Introdunction to fundamental data type

### Bits, bytes, and memory addressing

* **변수**(variable) : 정보를 저장하고 있는 memory공간의 이름.

* **Bit** : Memory의 최소 단위. Binary digit의 약자.
  - 0 또는 1을 저장.
* Memory는 *memory address*(그냥 간단히 address라고도 함)라는 단위로 구성.
  - Modern architecture에서 모든 bit가 memory address를 가질 수는 없음. Memory address의 개수는 한정되어 있기 때문.
  - 각 memory address는 bit대신 byte단위로 data를 가지고 있음.
  - **1byte = 8 bits**
          

### Data types

* 컴퓨터의 모든 data : 단순히 연속된 bit들로 이루어짐.
  - 따라서 compiler에게 data type을 활용하여 memory의 내용을 어떻게 파악할지 알려줌.
  - ex) 컴퓨터에 저장된건 0100 0001 -> 65

### Fundamental Data types

* C++은 내부적으로 여러 **built-in data type**들을 내장하고 있음.

  - 이러한 built-in type들을 basic type, primitive type이라고도 부름.

  - | Types                                     | Category             | Meaning                                          | Example |
    | ----------------------------------------- | -------------------- | ------------------------------------------------ | ------- |
    | float<br>double<br>                       | Floating Point       | a number with a fractional part                  | 3.141   |
    | bool                                      | Integral (Boolean)   | true or false                                    | true    |
    | char<br>                                  | Integral (Character) | a single character of text                       | 'c'     |
    | short<br>int<br>long<br>long long (C++11) | Integral (Integer)   | positive and negative whole numbers, including 0 | 6       |
    | void                                      | Void                 | no type                                          | n/a     |

## Void

* `Void` : 정말 간단히 *no type*을 의미.

* 하지만 변수는 void type으로 선언 불가.

```c++
void value; // won't work, variables can't be defined with a void type
```

## Object sizes and the sizeof operator

### Fundamental data type sizes

* 아래 표에 나오는 size와 별개로 data size는 compiler와 computer architecture에 따라 달라질 수 있음.

* | Category       | Type      | Size    |
  | -------------- | --------- | ------- |
  | boolean        | bool      | 1 byte  |
  | character      | char      | 1 byte  |
  | integer        | short     | 2 bytes |
  |                | int       | 4 bytes |
  |                | long      | 4 bytes |
  |                | long long | 8 bytes |
  | floating point | float     | 4 bytes |
  |                | double    | 8 bytes |

### The sizeof operator

* Parameter로 data type이나 object를 주면 그것의 *size를 byte단위*로 return해줌.

```c++
#include <iostream>
int main()
{
  std::cout << "bool:\t\t" << sizeof(bool) << " bytes\n";
  std::cout << "char:\t\t" << sizeof(char) << " bytes\n";
  std::cout << "int:\t\t" << sizeof(int) << " bytes\n";
  std::cout << "double:\t\t" << sizeof(double) << " bytes\n";

  return 0;
}
```

## Signed Integers

* `Integer` : 0을 포함한 양의 정수 및 음의 정수를 나타낼 수 있는 data type

  - Integer는 다음과 같은 4가지 종류가 있음.

  - | type      | Size    |
    | --------- | ------- |
    | short     | 2 bytes |
    | int       | 4 bytes |
    | long      | 4 bytes |
    | long long | 8 bytes |

### Signed Integer Ranges

* `Range` : 하나의 data type이 취할 수 있는 범위

* Integer값이 취할 수 있는 범위를 결정하는 두 요소 : *bit수*와 *signed/unsigned 여부*

  - | Size / Type    | Range                           |
    | -------------- | ------------------------------- |
    | 1 byte signed  | -128 to 127                     |
    | 2 bytes signed | -32,768 to 32,767               |
    | 4 bytes signed | -2,147,483,648 to 2,147,483,647 |

  - 일반화하면 `-(2^(n-1)) to (2^(n-1)-1)`

### Integer Overflow

* **Integer overflow** : 저장할 수 있는 값의 범위를 넘어서는 값을 저장하려할 때 발생. 줄여서 그냥 overflow라고도 함.
  - 일반적으로 overflow의 경우, 이를 저장하기 위해서는 더 많은 bit가 필요하므로 값의 손실이 일어남.
    + 하지만 signed integer의 경우, 값의 손실이 일어나는 정확한 규칙이 존재하지 않아서 결과가 어떻게 될지 모름.

### Integer Division

```c++
#include <iostream>
int main()
{
  std::cout << 8 / 5;
  return 0;
}
```

* 위의 코드를 실행해보면?

> 1

* *Integer division*의 결과는 무조건 *integer*를 return.
* 비슷하게 -8 / 5는 -1을 return.

## Unsigned Integers, and why to avoid them.

* **Unsigned integer** : Non-negative value를 가지는 함수

### Defined unsigned integer

```c++
unsigned short us;
unsigned int ui;
unsigned long ul;
unsigned long long ull;
```

### Unsigned Integer Range

* | Size/Type        | Range              |
  | ---------------- | ------------------ |
  | 1 byte unsigned  | 0 to 255           |
  | 2 bytes unsigned | 0 to 65,535        |
  | 4 bytes unsigned | 0 to 4,294,967,295 |

 - 만약 n bit가 존재한다면 표현 가능한 범위 : `0 to (2^n)-1`

### Unsigned Integer Overflow

* *Unsigned integer*에 큰 값을 집어넣으려고 한다면?
  - 이때는 overflow가 일어나지 않고 일정한 규칙에 따라서 의도한 바와 다른 숫자가 저장됌.
  - 해당 bit수로 표현 가능한 수보다 1 더 큰 수로 나눈 나머지를 저장시킴.
    + Ex) 1 byte에 280을 저장하려 한다면 280 % 256 = 24해서 24를 저장.
  - 저장하려는 값이 음수인 경우는 다음과 같이 저장됌.

```c++
#include <iostream>
int main()
{
  unsigned short x{ 0 }; 
  std::cout << " x was : " << x << '\n';

  x = -1;
  std::cout << " x is now : " << x << '\n';

  x = -2;
  std::cout << " x is now : " << x << '\n';

  return 0;
}
```

* 위 코드를 실행해보면?

> x was : 0   
> x is now : 65535   
> x is now : 65534

### The controversy over unsigned numbers

* Unsigned number는 프로그래밍 과정에서 왠만하면 안쓰는게 좋음.
  1. 두 개의 unsigned number 사이의 뺄셈을 생각해보면 *3-5=-2*가 나와야하지만 실제 실행결과값은 다른값이 출력됌. 왜냐하면 unsigned number는 -2라는 음수값을 저장할 수 없기 때문. 또한 `--`operator를 써도 똑같은 문제 발생 가능.
  2. 두번째 이유는, signed number와 unsigned number의 연산을 생각하였을 때, signed number가 unsigned number로 형변환됌.

### So where is it reasonable to use unsigned numbers?

1. Bit manipulation (chapter O).

2. Array indexing (추후, array 관련 chapter에서 설명 예정).

3. Embedded system이나 processor/memory limit한 상황에서 개발을 할 때는 performance를 위해서 unsigned를 사용하기도 함.

### What is std::size_t?

```c++
#include <iostream>

int main()
{
  std::cout << sizeof(int) << '\n';

  return 0;
}
```

* 위 코드 실행 시 *4*가 출력됌. 그렇다면 이 4라는 숫자의 data type은 뭘까? Int? Short?

* `sizeof()`뿐만 아니라 size나 length를 return해주는 대부분의 함수들의 return type은 `std::size_t`임.

* `std::size_t`는 **unsigned integral type**으로 정의되어있음.

* `std::size_t`의 크기는 시스템에 따라 다르지만 대부분 부호가 없고 최소 16bit의 길이를 가지고 있음. 하지만 대부분의 시스템에서는 application의 *address-width*와 같음.
  - 예를 들어 32 bit application에서는 32-bit unsigned integer일 것이고 64-bit application에서는 64-bit unsigned integer일 것.

* 일반적으로 `std::size_t`는 해당 시스템에서 생성할 수 있는 가장 큰 크기의 object를 저장할 수 있을만큼 크게 정의됌.
  - 만약 `std::size_t`가 4 byte라면 해당 시스템에서 생성할 수 있는 가장 큰 크기의 object는 4 byte unsigned integer인 4,294,967,295보다 클 수 없음.

## Floating point numbers

* **Floating type variable** : Real number를 저장하기 위한 variable.

* Float, double, long double 이렇게 세가지 타입이 존재.

* **Floating type variable**은 항상 *signed*.

* | Category       | Type   | Size    |
  | -------------- | ------ | ------- |
  | floating point | float  | 4 bytes |
  |                | double | 8 bytes |

* Floating type variable을 선언할 때 혹시 모를 혼선을 막기 위해서 뒤에 꼭 *소수점 이하 0*을 붙일 것.

```c++
int x{5};
double d{5.0}; // suffix가 아무것도 안붙어있으면 floating type은 default가 double type으로 설정되어있음.
float f{5.0f}; // suffix f를 붙이면 float type.
```

```c++
#include <iostram>

int main()
{
  std::cout << 5.0 << '\n';
  std::cout << 6.7 << '\n';

  return 0;
}
```

* 위 코드를 실행해보면 다음과 같이 나옴.

> 5   
> 6.7 

* 즉, 만약 소수점 아래부분이 0이라면 std::cout은 해당 부분을 굳이 출력하지 않음.

### Floating point precision

* **Precision of floating point** : 정보 손실 없이 표현할 수 있는 *significant digits*(유효자릿수)를 의미.

* 기본적으로 std:cout의 기본 precision은 *6자리*임.

``` c++
#include <iostream>

int main()
{
  std::cout << 9.87654321f << '\n';
  std::cout << 987.654321f << '\n';
  std::cout << 987654.321f << '\n';
  std::cout << 9876543.21f << '\n';
  std::cout << 0.0000987654321f << '\n';

  return 0;
}
```

* 위 코드를 실행하면?

> 9.87654   
> 987.654   
> 987654   
> 9.87654e+006   
> 9.87654e-005

* Floating point value의 precision 자릿수를 정하는 요소
  - **Size** : Float data type보다 double data type이 더 precision이 큼.
    + Float : 6 ~ 9 사이의 precision을 가짐. 대부분의 float value는 최소 7자리 이상의 유효숫자를 가지고 있음.
    + Double : 15 ~ 18 사이의 precision을 가짐. 대부분의 double value는 최소 16자리 이상의 유효숫자를 가지고 있음.
  - `Value` : 특정 값들은 다른 값들보다 더 큰 precision을 가지고 있음.

### NaN and Inf

* `NaN`은 *Not a Number*를 의미하고, `Inf`는 *infinity*를 의미. `Inf`는 positive, negative 모두 다 가능.

## Boolean values

### Boolean variables

* **Boolean type** : yes/no, or true/false 이러한 타입을 나타내는 변수들.

* **Boolean variable**을 선언하기 위해서 `bool`이라는 keyword 사용.

* Boolean variable을 초기화하거나 값을 대입할 때는, `true`, `false` keyword를 사용.
  - default 초기화는 `false`.

```c++
bool b1 {!true}; // b1은 false로 초기화됌.
```

### Printing Boolean Variables

```c++
#include <iostream>

int main()
{
  std::cout << true << '\n';
  std::cout << !true << '\n';
}
```

* 위 코드를 실행해보면?

> 1   
> 0

### Integer to Boolean conversion

* *0*은 `false`, *그 이외의 값*은 모두 `true`로 치환됌.

* 하지만 Boolean variable을 *uniform initialization*으로는 integer를 이용하여 초기화 불가능.

## Chars

* **Char** data type
  - Letter를 저장하기 위한 data type.
  - Integral type이고, 저장될시 integer형태로 저장됌. 
  - 크기는 1 byte.

* 그렇다면 computer는 저장된 것이 숫자인지 문자인지 어떻게 알까?

* [ ASCII_CODE ](https://www.learncpp.com/cpp-tutorial/chars/)

### Initializing chars

* `''`를 이용하여서 char를 표현 가능.

```c++
char ch1 { 'a' }; // prefer
char ch2 { 97 };
```

> 두가지 방법 모두 가능하나 일반적으로 위의 방법을 선호. 아래 방식은 computer로 하여금 헷갈릴 수 있게 할 수 있음.

#### Printing chars

```c++
#include <iostream>

int main()
{
  char ch1 { 'a' };
  std::cout << ch1 << '\n';

  return 0;
}
```

### Printing chars as integers via type casting

```c++
#include <iostream>

int main()
{
  char ch {97};
  int i(ch);

  std::cout << i;

  return 0;
}
```

* 위 방법은 매우 위험한 방법. computer에 따라서 다르게 반응할 수 있음.

* **Type cast**방법을 쓰는게 효율적.
  - **Type cast**란 어느 하나의 data type을 다른 data type으로 바꿔주는 것.
  - *Fundamental data type*들끼리의 **type cast**를 **static cast**라고 함.
  - 기본적인 형태는 다음과 같다.
* `static_cast<new_type>(expression)`


```c++
#include <iostream>

int main()
{
  char ch { 'a' };
  std::cout << ch << '\n';
  std::cout << static_cast<int>(ch) << '\n';
  std::cout << ch << '\n';

  return 0;
}
```

### Escape Sequences

* C++에서 문자들 중에서 특별한 의미를 가지는 문자들이 존재. 해당 문자들을 *escape sequences*라고 부름. 해당 문자들은 `\`로 시작.

* | Name           | Symbol | Meaning                   |
  | -------------- | ------ | ------------------------- |
  | Newline        | \n     | Moves cursor to next line |
  | Horizontal tab | \t     | Prints a horizontal tab   |



## Literals

* `"Hello, world!"`, `5`와 같이 값이 고정된 값을 literal이라고 함. 이런 값들은 변수와 달리 값이 고정되어 있음.
* **Constant** : 바뀌지 않는 값을 의미.

 - C++에서는 *literal constants*와 *symbolic constants*가 존재.

* **Literal constants** : Code에 direct하게 삽입되는 value.

```c++
return 5; // 5는 integer literal
bool bv { true }; // true는 boolean literal
std::cout << 3.4; // 3.4는 double literal
```

* 기본적으로 literal들도 data type을 가지고 있음.

  - | Literal value        | Examples         | Default type        |
    | -------------------- | ---------------- | ------------------- |
    | integral type        | 5, 0, -3         | int                 |
    | boolean value        | true, false      | bool                |
    | floating point value | 3.4, -2.2        | double (not float!) |
    | char value           | 'a'              | char                |
    | C-style string       | "Hellow, world!" | const char[14]      |



## Const and symbolic constants

### Const variables

* 코딩을 하다보면 특정 값은 해당 프로그램 내에서 한 값으로 고정을 해놓는게 편한 경우가 존재함. 그럴 경우 `const`라는 keyword를 사용함.

```c++
const double gravity { 9.8 }; // 더 선호하는 방법
int const sidesInSquare { 4 }; // 이러한 방식도 가능하나, 일반적으로 const를 data type보다 앞에 쓰는 경우가 훨씬 많음.
```

* 주의해야할 것은, `const` variable들은 무조건 *define*될 때 *initializing*되어야 함. 그리고 한 번 초기화된 이후로는 다시는 값의 변경이 불가함. 만약 초기화를 시키지 않으면 *compile error*가 발생.

```c++
const double gravity { 9.8 };
gravity = 10; // compile error
```

```c++
int age;
std::cin >> age;

const userAge { age }; // 이러한 식으로 다른 variable을 이용하여서도 초기화 가능.
```

* 다음과 같이도 `const`를 사용 가능.

```c++
void printInteger(const int myValue)
{
  std::cout << myValue;
}
```

* 위와 같이 *function parameter*를 `const` keyword로 선언하는 것은 두 가지 의미를 가짐.
  1. Function을 call한 사용자로 하여금 해당 function안에서는 myValue값이 바뀌지 않을 것을 알려줌.
  2. Function안에서 myValue값이 바뀌지 않도록 해줌.

* Function parameter가 *call by value*라면 아무 문제가 없지만 추후에 배우게 되는 다른 방식이라면 문제가 발생.



# Chapter5

## Operator precedence and associativity

### Chapter Introduction

* **Operand** : 피연산자

* **Operator** : 연산자

* **Output value** : 연산 결과값

### Operator precedence

* `2 + 3 * 4`라는 연산이 있을 때, 사람들은 자연스럽게 `+`보다 `*`가 더 우선이라는 것을 알기에, `2 + (3 * 4)`로 이해를 함. 마찬가지로 computer 속 연산에서도 이러한 **operator precedence**가 존재.

### Operator associativity

* 만약 **operator precedence**가 같은 연산이 두 개 존재한다면, **operator associativity**룰에 따라서 왼쪽에서 오른쪽 방향으로 연산을 할지, 아니면 오른쪽에서 왼쪽 방향으로 연산을 할지가 정해짐.

### Table of operators

* [ Table of Operators ](https://www.learncpp.com/cpp-tutorial/operator-precedence-and-associativity/)

* 하지만 아무리 **operator precedence**와 **operator associativity**가 존재하더라도, 연산을 확실히 하기위해서는 **parenthesization**을 꼭 쓰는 것을 권장.

## Arithmetic operators

### Unary arithmetic operators

* **Unary**란 operand를 *하나*만 필요로 하는 operator를 말함.

* `+`와 `-` 두 개 존재.

* `+`는 operand 그대로를 return해주고 `-`는 operand에 *-1*을 곱한 결과를 return해줌. 따라서 일반적으로 `+`는 잘 쓰이지 않음.

### Binary arithmetic operators

* **Binary**란 operand를 **두 개** 필요로 하는 operator를 말함.

* 다음과 같은 5가지가 존재.

* | Operator           | Symbol | Form  | Operation                       |
  | ------------------ | ------ | ----- | ------------------------------- |
  | Addition           | +      | x + y | x plus y                        |
  | Subtraction        | -      | x - y | x minus y                       |
  | Multiplication     | *      | x * y | x multiplied by y               |
  | Division           | /      | x / y | x divided by y                  |
  | Modulus(Remainder) | %      | x % y | The remainder of x divided by y |

### Integer and floating point division

* **Integer division**은 *Integer*를 return해주고, **Floating point division**은 *Floating point*를 return해줌.

* `7 / 4`는 *1*을 return해주고 `7.0 / 4.0`은 *1.75*를 return해줌.

### Using static_cast<> to do floating point division with integers

* 정수끼리의 연산에서 소수를 얻고싶으면 `static_cast<>`를 통해서 *type casting*을 시켜주면 됌.

```c++
#include <iostream>

int main()
{
  int x { 7 };
  int y { 4 };

  std::cout << "int / int = " << x / y << '\n';
  std::cout << "double / int = " << static_cast<double>(x) / y << '\n';
  std::cout << " int / double = " << x / static_cast<double>(y) << '\n';
  std::cout << " double / double = " << static_cast<double>(x) / static_cast<double>(y) << '\n';

  return 0;
}
```

* 위 코드를 실행해보면?

> int / int = 1   
> double / int = 1.75   
> int / double = 1.75   
> double / double = 1.75   

* 결론 : 두 개의 integer operand 중 하나라도 *floating point*라면 전체 연산은 *floating point operation*으로 처리됨.

* 참고 : 0으로 어떤 숫자를 나눌려한다면??
  - 당연히 *error!*
  - Computer에 심각한 오류를 일으킬 수 있으므로 주의해야함.

### Arithmetic assignment operators

* | Operator                  | Symbol | Form    | Operation                       |
  | ------------------------- | ------ | ------- | ------------------------------- |
  | Assignment                | =      | x = y   | Assign value y to x             |
  | Addition assignment       | +=     | x += y  | Add y to x                      |
  | Subtraction assignment    | -=     | x -= y  | Subtract y from x               |
  | Multiplication assignment | * =    | x * = y | Multiply x by y                 |
  | Division assignment       | /=     | x /= y  | Divide x by y                   |
  | Modulus assignment        | %=     | x %= y  | Put the remainder of x / y in x |

```c++
x = x + 4;

x += 4;
```

* 위 두 줄의 코드는 서로 똑같은 코드

### Increment/decrement operators, and side effects

* | Operator                           | Symbol | Form | Operation                                      |
  | ---------------------------------- | ------ | ---- | ---------------------------------------------- |
  | Prefix increment (pre-increment)   | ++     | ++x  | Increment x, then return x                     |
  | Prefix decrement (pre-decrement)   | --     | --x  | Decrement x, the return x                      |
  | Postfix increment (post-increment) | ++     | x++  | Copy x, then increment x, then return the copy |
  | Postfix decrement (post-decrement) | --     | x--  | Copy x, then decrement x, then return the copy |

```c++
#include <iostream>

int main()
{
  int x { 5 };
  int y = ++x;

  std::cout << x << ' ' << y << '\n';

  return 0;
}
```

```c++
#include <iostream>

int main()
{
  int x { 5 };
  int y = x++;
  std::cout << x << ' ' << y << '\n';

  return 0;
}
```

* **Postfix**연산이 **prefix**연산보다 값을 계산함에 있어서 훨씬 step이 더 많음. 따라서 performace적으로 봤을 때 **prefix** 연산이 더 좋음.

### Side effects

* **Side effect** : 의도한 바와 다른 연산 결과를 나타내는 것

```c++
#include <iostream>

int add(int x, int y)
{
  return (x + y);
}

int main()
{
  int x{ 5 };
  int value = add(x, ++x);

  std::cout << value << '\n';

  return 0;
}
```

* 위 코드에서 add함수는 과연 `add(5,6)`으로 function call이 될까 아니면 `add(6,6)`으로 function call이 될까?

* Computer는 function call을 할 때 parameter계산 순서를 따로 정해놓지 않음. 따라서 위의 두가지 방법 중 어느 방법으로 function call이 될지는 아무도 모름. 따라서 애초에 이러한 *side effects*를 방지하는 수 밖에 없음. 

* 하나의 statement에서 *side effects*를 가질 수 있는 variable을 여러 번 사용하지 않는 것이 좋음.

  

## Modulus

### The modulus operator

* **Modulus operator** : 흔히 *remainder operator*라고도 불리는데, 나눗셈에서 *나머지*를 return해줌.

* 일반적으로 어떤 수가 다른 수로 정확히 나눠떨어지는지 검사할 때 유용하게 사용됌.
  - **Modulus operation**의 결과가 0이라면 정확하게 나누어떨어지는 것.

### Modulus with negative numbers

* 음수를 이용해서도 **modulus operation** 가능.

* `x % y`를 한다고 가정했을 때 일반적으로 *remainder*의 부호는 *x*의 부호를 따라감.

## Relational operators and floating point comparisons

* **Relational operator**란 두 개의 value를 비교할 수 있도록 해주는 operator.

* | Operator               | Symbol | Form   | Operation                                                |
  | ---------------------- | ------ | ------ | -------------------------------------------------------- |
  | Greater than           | >      | x > y  | true if x is greater than y, otherwise false             |
  | Less than              | <      | x < y  | true if x is less than y, otherwise false                |
  | Greater than or equals | >=     | x >= y | true if x is greater than or equal to y, otherwise false |
  | Less than or equals    | <=     | x <= y | true if x is less than or equal to y, otherwise false    |
  | Equality               | ==     | x == y | true if x equals y, otherwise false                      |
  | InEquality             | !=     | x != y | true if x does not equal to y                            |

## Logical operators

* | Operator    | Symbol | Form     | Operation                                       |
  | ----------- | ------ | -------- | ----------------------------------------------- |
  | Logical NOT | !      | !x       | true if x is false, or false if x is true       |
  | Logical AND | &&     | x && y   | true if x and y are both true, otherwise false  |
  | Logical OR  | \|\|   | x \|\| y | true if either x or y are true, otherwise false |

### Mixing ANDs and ORs

* *Logical AND*와 *logical OR*을 혼합해서 쓰는 사람들이 많음.

* 하지만 실제로는 *logical AND*가 *logical OR*보다 *operator precedence*가 더 높기 때문에 프로그래머가 의도한 바와 다르게 결과가 나오는 경우가 생김.

* `Value1 || value2 && value3`라는 연산을 생각했을 때 프로그래머가 의도한 바는 `(value1 || value2) && value3`이겠지만 실제로는 `value1 || (value2 && value3)` 이런 식으로 계산이 됌.

* 따라서 *logical AND*와 *logical OR*을 혼합해서 쓸 때는 꼭 **괄호**를 사용할 것.
