430.211 프로그래밍 방법론 : Basic3. Loop and Conditional
---------------------------------------
담당 조교 : 함도규

이메일 : hdk971110@scale.snu.ac.kr

2021년 3월 22일 월요일

## Control flow
여러분들의 프로그램은 main의 처음에서 시작해서 순차적으로 statement들을 실행시킵니다. 이렇게 프로그램이  동작하는 경로를 execution path라고 합니다. 여러분들의 execution path가 main의 처음부터 끝까지 statement들을 하나하나 다 수행하는 것일수도 있지만, control flow statement를 활용하면 execution path를 여러분들이 원하는 대로 변경할 수 있습니다. 

### Halt
가장 단순한 control flow statement는 halt입니다. 여러분들의 프로그램은 halt statement를 만나면 종료하게 되는데, 이것은 `return`을 통해 main을 끝내는 것과 유사하게 동작합니다. halt는 `exit()` 함수를 통해 사용할 수 있는데, exit 함수는 cstdlib header에 define되어 있습니다. `exit()`는 integer parameter를 가지고, 이 값을 operating system에 return합니다.

`return`과 다른 점은 `exit()`는 `main`에서가 아니라 그 어디에서 호출되어도 동작합니다. `exit()`을 만난 순간 program은 즉시 종료합니다. (반면 return은 함수를 종료하고 값을 반환합니다.)

``` c++
#include <cstdlib> // needed for exit()
#include <iostream>
 
void cleanup()
{
    // code here to do any kind of cleanup required
}
 
int main()
{
    std::cout << 1;
    cleanup();
 
    exit(0); // terminate and return 0 to operating system
 
    // The following statements never execute
    std::cout << 2;
    return 0;
}
```

<hr/>

### Conditional branches

Conitional branch(조건문)은 조건문의 expression의 값에 따라 execution path를 바꾸는 Statement입니다. 가장 단순한 conditional branch로 if가 있습니다.
#### if statement
if 안의 expression이 true, false냐에 따라 실행하는 statement들이 달라집니다.

if statement의 형태 1
``` c++
if (expression)
	statement
```
if statement의 형태 2

``` c++
if (expression)
	statement
else
	statement
```

예제
``` c++
#include <iostream>
 
int main()
{
    std::cout << "Enter a number: ";
    int x;
    std::cin >> x;
 
    if (x > 10)
    {
        // both statements will be executed if x > 10
        std::cout << "You entered " << x << "\n";
        std::cout << x << "is greater than 10\n";
    }
    else
    {
        // both statements will be executed if x <= 10
        std::cout << "You entered " << x << "\n";
        std::cout << x << "is not greater than 10\n";
    }
 
    return 0;
}
```

예제 2
``` c++
#include <iostream>
 
int main()
{
    std::cout << "Enter a number: ";
    int x;
    std::cin >> x;
 
    if (x > 10)
        std::cout << x << "is greater than 10\n";
    else
        std::cout << x << "is not greater than 10\n";
 
    return 0;
}
```
> if statement 후에 {}를 포함해야 하지만, compiler가 자동적으로 {}를 만들어주기 때문에 따로 {}를 적을 필요는 없습니다.하지만, explicit하게 {}가 적혀 있지 않더라도, implicit하게는 {}가 있는 것의 차이를 알고 있어야 합니다. :wink:

``` c++
#include <iostream>
 
int main()
{
    if (true)
        int x = 5;
    else
        int x = 6;
 
    std::cout << x;
 
    return 0;
}
```
이런 코드는 compile되지 않습니다. x는 {} block 내에서만 define되고 discard되기 때문에, `std::cout<< x;`에서 x를 찾을 수 없습니다.

``` c++
#include <iostream>
 
int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
 
    if (x > 10)
        std::cout << x << "is greater than 10\n";
    else
    {
        if (x < 10) 
            std::cout << x << "is less than 10\n";
        else
            std::cout << x << "is exactly 10\n";
    }
 
    return 0;
}
```
이런식으로 x를 if문 전에 deifne하는 것이 좋습니다.

``` c++
#include <iostream>
 
int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
 
    if (int y=x; y > 10)
        std::cout << x << "is greater than 10\n";
    else
    {
        if (y < 10) 
            std::cout << x << "is less than 10\n";
        else
            std::cout << x << "is exactly 10\n";
    }
 
    return 0;
}
```

if문 안에서 declaration을 할 수도 있습니다.

if문 예시 ***Dangling if***

``` c++
#include <iostream>
 
int main()
{
    std::cout << "Enter a number: ";
    int x;
    std::cin >> x;
 
    if (x >= 10) // outer if statement
        // it is bad coding style to nest if statements this way
        if (x <= 20) // inner if statement
            std::cout << x << "is between 10 and 20\n";
 
        // which if statement does this else belong to?
        else
            std::cout << x << "is greater than 20\n";
 
    return 0;
}
```
if문 응용2  ***Chained if***

``` c++
#include <iostream>
 
int main()
{
    std::cout << "Enter a number: ";
    int x;
    std::cin >> x;
 
    if (x > 10)
        std::cout << x << "is greater than 10\n";
    else if (x < 10) 
        std::cout << x << "is less than 10\n";
    else
        std::cout << x << "is exactly 10\n";
 
    return 0;
}
```


#### Conditional expression

이전에 expression이 single value가 될 때까지 evaluate된다는 것을 배웠습니다.
if문에서의 conditional expression은 true or falue로 evaluate되므로, logical operator를 사용하여 응용할 수 있습니다.

``` c++
#include <iostream>
 
int main()
{
    std::cout << "Enter an integer: ";
    int x;
    std::cin >> x;
 
    std::cout << "Enter another integer: ";
    int y;
    std::cin >> y;
 
    if (x > 0 && y > 0) // && is logical and -- checks if both conditions are true
        std::cout << "both numbers are positive\n";
    else if (x > 0 || y > 0) // || is logical or -- checks if either condition is true
        std::cout << "One of the numbers is positive\n";
    else
        std::cout << "Neither number is positive\n";
 
    return 0;
}
```
#### Init statement

이렇게 init statement를 활용해서 만들면 if문 안에 들어가는 변수(여기서는 fullName)을 if문 안에서만 사용할 수 있습니다.

``` c++
#include <iostream>
#include <string>
 
int main()
{
    std::string firstName{};
    std::string lastName{};
 
    std::cout << "First name: ";
    std::cin >> firstName;
 
    std::cout << "Last name: ";
    std::cin >> lastName;
 
    if (std::string fullName{ firstName + ' ' + lastName }; fullName.length() > 20)
    {
        std::cout << '"' << fullName << "\"is too long!\n";
    }
    else
    {
        std::cout << "Your name is " << fullName << '\n';
    }
 
    // code that doesn't need @fullName
 
    return 0;
}
```
<hr/>

#### Switch statement

switch statement는 if문을 사용해서도 동일하게 구현할 수 있지만, 조건이 많아서 if문에서 쓰면 
지저분해 보이는 것을 switch문을 통해 깔끔하게 만들 수 있습니다. switch문은 전체가 하나의 block이므로 `break`을 사용해 주세요. `break`는 loop을 탈출하는 statement입니다.(나중에 `for, while, do while`에서도 사용할 수 있습니다.)

예제
``` cpp
void printColor(Colors color)
{
    switch (color)
    {
        case COLOR_BLACK:
            std::cout << "Black";
            break;
        case COLOR_WHITE:
            std::cout << "White";
            break;
        case COLOR_RED:
            std::cout << "Red";
            break;
        case COLOR_GREEN:
            std::cout << "Green";
            break;
        case COLOR_BLUE:
            std::cout << "Blue";
            break;
        default:
            std::cout << "Unknown";
            break;
    }
}
```

예제 2
`default` label은 다른 case들이 expression과 match가 안될경우 실행됩니다.

``` c++
bool isDigit(char c)
{
    switch (c)
    {
        case '0': // if c is 0
        case '1': // or if c is 1
        case '2': // or if c is 2
        case '3': // or if c is 3
        case '4': // or if c is 4
        case '5': // or if c is 5
        case '6': // or if c is 6
        case '7': // or if c is 7
        case '8': // or if c is 8
        case '9': // or if c is 9
            return true; // then return true
        default:
            return false;
    }
}
```
#### Jumps
`switch`문은 정상적으로 작동하기 위해서 `break, return, goto`등이 필요합니다.
jump는 statement가 아닌 다른 statement로 바로 이동(:runner: jump)하게 합니다. function call또한 jump와 유사한데, function call의 순간 CPU는 funtion의 top으로 jump하게 됩니다.


``` c++
switch (2)
{
   case 1: // Does not match
       std::cout << 1 << '\n'; // skipped
   case 2: // Match!
       std::cout << 2 << '\n'; // Execution begins here
   case 3:
       std::cout << 3 << '\n'; // This is also executed
   case 4:
       std::cout << 4 << '\n'; // This is also executed
   default:
       std::cout << 5 << '\n'; // This is also executed
}
```
switch문은 break문과 결합하여 자주 사용합니다.

``` c++
switch (2)
{
   case 1: // Does not match -- skipped
       std::cout << 1 << '\n';
       break;
   case 2: // Match!  Execution begins at the next statement
       std::cout << 2 << '\n'; // Execution begins here
       break; // Break terminates the switch statement
   case 3:
       std::cout << 3 << '\n';
       break;
   case 4:
       std::cout << 4 << '\n';
       break;
   default:
       std::cout << 5 << '\n';
       break;
}
// Execution resumes here
```

#### Variable declaration in switch statement

switch문 내에서 변수를 생성할 때 **declaration**은 되지만 **initialization**은 되지 않습니다. 위에서 말 했듯이 switch는 하나의 block처럼 작동합니다. 좋은 방법은 그냥 switch문 바로 아래 혹은 첫번째 case 에다가 declaration을 적는 것입니다. Initialization을 하고 컴파일을 했을 때 에러가 나지 않으면 결과는 **undefined behaviour**이니 주의하세요! :man_teacher:

```cpp
switch (1)
{
  int a; // okay, declaration is allowed before the case labels
  int b = 5; // illegal, initialization is not allowed before the case labels
  
  case 1:
        int y; // okay, declaration은 됨
        y = 4; // okay, this is an assignment
        break;
  
  case 2:
        y = 5; // okay, 다른 케이스여도 assignment는 됨
        break;

  case 3:
        int z = 4; // illegal : initialization은 안됨
        break;
        
  default:
        std::cout << "default case" << std::endl;
        break;
}

```

<hr/>

#### Goto statements

위에서 말했던 jump문(goto, break, continue 등등)중 goto문에 대해서 얘기해 보겠습니다. goto문은 간단합니다. goto가 가리키는 라벨로 코드를 jump하게 합니다.

예제

```cpp
#include <iostream>
#include <cmath> // for sqrt() function
 
int main()
{
    double x;
tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number"; 
    std::cin >> x;
 
    if (x < 0.0)
        goto tryAgain; // this is the goto statement
 
    std::cout << "The sqrt of " << x << " is " << sqrt(x) << std::endl;
    return 0;
}
```

> 여기서 tryAgain이 라벨입니다. 간단하죠? goto문은 유용해 보이지만 의외로 많이 쓰이지 않습니 다. 간단한 계산보다는 운영체제나 게임 등의 코드에서 많이 쓰입니다. 🍝 스파게티 코드는 스파 게티처럼 코드의 execution path가 이리저리 엉켜있는 것을 의미하는데, goto문을 남발하면 여러 분의 코드가 스파게티 코드가 될 수 있습니다. 보통 다른 statement로 대체해서 많이 사용합니다

### Loops(while, for, do while)
loop은 statement들을 반복적으로 수행하기 위해 쓰입니다.

#### while statement

`while` statement는 코드를 condition이 참일 때 동안 여러번 반복하는 execution path를 만들어 줍니 다. 각각의 반복을 **iteration**이라고 부릅니다.

```cpp
#include <iostream>
 
int main()
{
    int count{ 0 };
    while (count < 10)
    {
      std::cout << count << ' ';
      ++count;
    }
    std::cout << "done!";
 
    return 0;
}
```

##### Infinite loop

```cpp
#include <iostream>
int main()
{
while (true) // while의 condition은 항상 true
{
std::cout << "무한루프가 실행 중입니다." << std::endl;
}
return 0; // this line will never execute
}

```

##### Overflow 조심

이 코드가 몇번 iteration을 돌지 분석해 보세요

```cpp
#include <iostream>
 
int main()
{
    unsigned int count{ 10 };
 
    // count from 10 down to 0
    while (count >= 0)
    {
        if (count == 0)
        {
            std::cout << "blastoff!";
        }
        else
        {
            std::cout << count << ' ';
        }
        --count;
    }
 
    return 0;
}
```

##### 1부터 50까지 프린트하기

```cpp
#include <iostream>
 
// Iterate through every number between 1 and 50
int main()
{
    int count{ 1 };
    while (count <= 50)
    {
        // print the number (pad numbers under 10 with a leading 0 for formatting purposes)
        if (count < 10)
        {
            std::cout << "0" << count << ' ';
        }
        else
        {
            std::cout << count << ' ';
        }
 
        // if the loop variable is divisible by 10, print a newline
        if (count % 10 == 0)
        {
            std::cout << '\n';
        }
            
        // increment the loop counter
        ++count;
    }
 
    return 0;
}
```

##### Nested Loops

```cpp
#include <iostream>
 
// Loop between 1 and 5
int main()
{
    int outer{ 1 };
    while (outer <= 5)
    {
        // loop between 1 and outer
        int inner{ 1 };
        while (inner <= outer)
        {
            std::cout << inner++ << ' ';
        }
 
        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    }
 
    return 0;
}
```

#### do while문

do while문은 while문과 거의 동일하게 동작합니다. 단지 1번의 iteration을 보장한다는 것만 빼면요.

```cpp
#include <iostream>
 
int main()
{
    // selection must be declared outside do/while loop
    int selection;
 
    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }
    while (selection != 1 && selection != 2 &&
        selection != 3 && selection != 4);
 
    // do something with selection here
    // such as a switch statement
 
    std::cout << "You selected option #" << selection << "\n";
 
    return 0;
}
```

#### For statements

cpp에서 가장 많이 사용되는 loop statement입니다. 몇번 iterate(반복)할 것인지 알고있다면 for문을 사용하면 좋습니다. for문의 구조는 다음과 같습니다. for문의 condition은 3가지 statement로 이루어져 있습니다. 예시를 많이 들어 보겠습니다.

```cpp
for (init-statement; condition-expression; end-expression)
statement
```

##### 예시

```cpp
for (int count{ 0 }; count < 10; ++count)
  std::cout << count << ' ';
```

##### 예시2

```cpp
for (int count{ 9 }; count >= 0; count -= 2)
  std::cout << count << ' ';
```

##### for문의 statement는 null statement여도 된다

```cpp
int count=0;
for ( ; count < 10; )
{
  std::cout << count << ' ';
  ++count;
}

```

##### Multiple iterators

2차원의 object를 다룰 때 유용합니다(e.g. 행렬)

```cpp
#include <iostream>
 
int main()
{
	for (char c{ 'a' }; c <= 'e'; ++c) // outer loop on letters
	{
		std::cout << c; // print our letter first
		
		for (int i{ 0 }; i < 3; ++i) // inner loop on all numbers
			std::cout << i;
 
		std::cout << '\n';
	}
 
	return 0;
}
```

> 이상 기본적인 for loops에 대해서 배워보았습니다. for loop은 modern cpp에서 더욱 발전해서 더더 유용하고 사용하기 편한 statement가 되었습니다. 나중에 modern cpp의 for loop에 대해 서도 공부할 것입니다. :man_teacher:

지금까지 아래 c++의 4가지 loop에 대해서 배워보았습니다. loop이라는 개념은 모든 프로그래밍 언어 에서 핵심적으로 사용되는 중요한 개념이므로, 조금씩 연습해서 익숙해져 보세요

* switch 
* while 
* do while 
* for

<hr/>

#### Break statements

이전에 보았다시피 break는 switch문에서 case를 끝내기 위해 거의 필수적으로 사용됩니다. 하지만 break를 다른 loop statement에서도 사용할 수 있습니다.

##### Break in switch statement

```cpp
switch (ch)
{
    case '+':
        doAddition(x, y);
        break;
    case '-':
        doSubtraction(x, y);
        break;
    case '*':
        doMultiplication(x, y);
        break;
    case '/':
        doDivision(x, y);
        break;
}
```

##### Break in for, while statement

break를 loop에서 사용하면, loop을 더이상 iterate(반복)하지 않고 바로 종료해 버립니다.

```cpp
#include <iostream>
 
int main()
{
    int sum{ 0 };
 
    // Allow the user to enter up to 10 numbers
    for (int count{ 0 }; count < 10; ++count)
    {
        std::cout << "Enter a number to add, or 0 to exit: ";
        int num{};
        std::cin >> num;
 
        // exit loop if user enters 0
        if (num == 0)
            break;
 
        // otherwise add number to our sum
        sum += num;
    }
 
    std::cout << "The sum of all the numbers you entered is " << sum << "\n";
 
    return 0;
}
```

while에서도 마찬가지입니다.

```cpp
#include <iostream>
 
int main()
{
    while (true) // infinite loop
    {
        std::cout << "Enter 0 to exit or anything else to continue: ";
        int num{};
        std::cin >> num;
 
        // exit loop if user enters 0
        if (num == 0)
            break;
    }
 
    std::cout << "We're out!\n";
 
    return 0;
}
```

##### Break vs return

```cpp
#include <iostream>
 
int breakOrReturn()
{
    while (true) // infinite loop
    {
        std::cout << "Enter 'b' to break or 'r' to return: ";
        char ch;
        std::cin >> ch;
 
        if (ch == 'b')
            break; // execution will continue at the first statement beyond the loop
 
        if (ch == 'r')
            return 1; // return will cause the function to immediately return to the caller (in this case, main())
    }
 
    // breaking the loop causes execution to resume here
 
    std::cout << "We broke out of the loop\n";
 
    return 0;
}
 
int main()
{
    int returnValue{ breakOrReturn() };
    std::cout << "Function breakOrReturn returned " << returnValue << '\n';
 
    return 0;
}
```

##### Break 예제

```cpp
#include <iostream>
 
int main()
{
    int count{ 0 }; // count how many times the loop iterates
    while (true) // loop until user terminates
    {
        std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
        char ch;
        std::cin >> ch;
 
        if (ch == 'e')
            break;
 
        ++count;
        std::cout << "We've iterated " << count << " times\n";
    }
 
    return 0;
}
```

#### Continue

continue는 loop의 iteration을 끝내고 다음 iteration으로 넘어갑니다.

```cpp
for (int count{ 0 }; count  < 20; ++count)
{
    // if the number is divisible by 4, skip this iteration
    if ((count % 4) == 0)
        continue; // jump to end of loop body
 
    // If the number is not divisible by 4, keep going
    std::cout << count << std::endl;
 
    // The continue statement jumps to here
}
```

#### Pseudo Random number generation

`srand` 와 `rand` 는 PRNG(Pseudo Random number generation)라고 불리는데 random number을 생 성하기 위해서 사용합니다. `srand()` 는 seed를 정하는 함수로 random number의 초기값이라고 볼 수 있습니다. `rand()` 는 초기값을 바탕으로 random number를 리턴해주는 함수입니다.

##### srand와 rand를 안만들고 random number 만들기

```cpp
#include <iostream>
 
unsigned int PRNG()
{
    // our initial starting seed is 5323
    static unsigned int seed{ 5323 };
 
    // Take the current seed and generate a new value from it
    // Due to our use of large constants and overflow, it would be
    // hard for someone to casually predict what the next number is
    // going to be from the previous one.
    seed = 8253729 * seed + 2396403;
 
    // Take the seed and return a value between 0 and 32767
    return seed % 32768;
}
 
int main()
{
    // Print 100 random numbers
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << PRNG() << '\t';
 
        // If we've printed 5 numbers, start a new row
        if (count % 5 == 0)
            std::cout << '\n';
    }
 
    return 0;
}
```

##### srand와 rand 사용

```cpp
#include <iostream>
#include <cstdlib> // for std::rand() and std::srand()
 
int main()
{
    std::srand(5323); // set initial seed value to 5323
 
    // Print 100 random numbers
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << std::rand() << '\t';
 
        // If we've printed 5 numbers, start a new row
        if (count % 5 == 0)
            std::cout << '\n';
	}
 
    return 0;
}
```

> rand() 는 0과 RAND_MAX사이에 임의의 숫자를 생성해 줍니다. 하지만 이 코드를 반복해서 돌 려보면, 항상 같은 결과를 낼 것입니다. 따라서 rand() 는 완벽한 랜덤이 아니고, 첫번째 코드와 거의 비슷한 코드라고 볼 수 있습니다.

##### random number?

실행할 때마다 다른 결과를 보여주는 코드를 만들고 싶다면 단순히 시간을 이용하면 됩니다. 아래 코드 는 srand() 의 argument만 바꾼 코드입니다.

```cpp
#include <iostream>
#include <cstdlib> // for std::rand() and std::srand()
#include <ctime> // for std::time()
 
int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock
 
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << std::rand() << '\t';
 
        // If we've printed 5 numbers, start a new row
        if (count % 5 == 0)
            std::cout << '\n';
	}
 
    return 0;
}
```

#### Handling invalid text input

learncpp에서 invalid text input을 다루는 내용이 있어서 포함시켰습니다. 프로그램 동작이 중요한 경 우에 사용하면 좋을 것 같습니다. 일반적인 많은 프로그램들은 invalid text input을 집어넣으면 그냥 종 료하고 다시 실행하는 경우가 많습니다. 아래에서 보시다시피 간단했던 코드들이 길어지게 되므로 필요 한 경우에만 사용하면 될 것 같습니다.

```cpp
#include <iostream>
 
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a double value: ";
        double x;
        std::cin >> x;
 
        // Check for failed extraction
        if (std::cin.fail()) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            std::cin.clear(); // put us back in 'normal' operation mode
            std::cin.ignore(32767,'\n'); // and remove the bad input
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
        else
        {
            std::cin.ignore(32767,'\n'); // remove any extraneous input
 
            // the user can't enter a meaningless double value, so we don't need to worry about validating that
            return x;
        }
    }
}
 
char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char op;
        std::cin >> op;
 
        // Chars can accept any single input character, so no need to check for an invalid extraction here
 
        std::cin.ignore(32767,'\n'); // remove any extraneous input
 
        // Check whether the user entered meaningful input
        if (op == '+' || op == '-' || op == '*' || op == '/')    
            return op; // return it to the caller
        else // otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
    } // and try again
}
 
void printResult(double x, char op, double y)
{
    if (op == '+')
        std::cout << x << " + " << y << " is " << x + y << '\n';
    else if (op == '-')
        std::cout << x << " - " << y << " is " << x - y << '\n';
    else if (op == '*')
        std::cout << x << " * " << y << " is " << x * y << '\n';
    else if (op == '/')
        std::cout << x << " / " << y << " is " << x / y << '\n';
    else // Being robust means handling unexpected parameters as well, even though getOperator() guarantees op is valid in this particular program
        std::cout << "Something went wrong: printResult() got an invalid operator.";
 
}
 
int main()
{
    double x = getDouble();
    char op = getOperator();
    double y = getDouble();
 
    printResult(x, op, y);
 
    return 0;
}
```

<hr/>

#### Testing your code

코드를 작성하고 난 후, 코드가 의도한 대로 정상적으로 작동하는지 확인하는 과정이 필요합니다. 디버 거(gdb 등)을 사용할 수도 있지만, 그 전에 test 코드를 작성한다면 더 빠르고 편리하게 코드를 테스트해 볼 수 있습니다. 보통 간단하게는 아래처럼 test 코드를 작성합니다. 프로그램이 복잡해질 수록, 코드의 동작을 분석하기가 어려우므로 test코드를 잘 작성하는 것이 중요합니다.

```cpp
#include <iostream>
 
void compare(int x, int y)
{
	if (x > y)
		std::cout << x << " is greater than " << y << '\n'; // case 1
	else if (x < y)
		std::cout << x << " is less than " << y << '\n'; // case 2
	else
		std::cout << x << " is equal to " << y << '\n'; // case 3
}
 
int main()
{
	std::cout << "Enter a number: ";
	int x;
	std::cin >> x;
 
	std::cout << "Enter another number: ";
	int y;
	std::cin >> y;
 
        compare(x, y);
}
```

