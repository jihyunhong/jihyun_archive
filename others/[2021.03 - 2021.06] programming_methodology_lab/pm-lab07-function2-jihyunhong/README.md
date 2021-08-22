430.211 프로그래밍 방법론 : Basic04: More about Function
===========================
담당조교 : 도완주   
이메일 : wj.doh@scale.snu.ac.kr   
2021년 3월 26일 금요일

참고자료
* learncpp.com 
  * 10.7, 10.8 & 10.12
* tcpschoop.com 
  * 코딩의 고수 > C++ > C++ 함수 > 디폴드 인수, 함수 오버로딩
  * 코딩의 고수 > C++ > 함수의 기본 > 재귀 호출



## Introduction
저번주 실습에서 우리는 함수의 기초적인 개념들에 대해 배웠습니다!

이번 시간에는 (1) **default argument** (2) **function overloading** 그리고 (3) **recursive call**에 대해 배우겠습니다.

1. default argument: 인수의 개수를 달리하여 같은 함수를 호출하는 것
2. function overloading: 같은 이름의 함수를 중복하여 정의하는 것
3. recursive call: 함수 내부에서 자기 자신(함수)을 또다시 호출하는 것



## 1. default argument

default argument는 함수의 parameter에 기본값을 정의해둔 것을 의미합니다.

함수를 호출할 때 argument를 전달하지 않으면, 함수는 자동으로 미리 정의되어 있는 default값을 사용하게 됩니다. (물론 argument를 전달하면 default값이 아닌, 전달된 값을 사용합니다. )

프로그램을 실행시키는 사용자가 default값을 사용할지, 인자를 넘겨줄지 선택할 수 있기 때문에 **optional parameter**라고도 부릅니다.

``` c++
#include <iostream>

void greet(std::string name, std::string msg="Good morning!") {
  std::cout << "Hello " << name << ", " << msg << std::endl;
}

int main(void) {
  greet("Monica", "How do you do?"); // msg will use user-supplied
  greet("Steve");                    // msg will use default argument "Good morning!"
  
  return 0;
}
```

> 인자를 넘겨준 경우에는 넘겨준 인자로, 인자를 빠뜨린 경우에는 default값으로 출력됩니다.

###  :bangbang: default argument를 사용할 때 주의할 점 :bangbang:

1. default argument는 가장 오른쪽부터 parameter부터 시작하여 순서대로만 지정할 수 있습니다.

   * `void Display(int x=1, int y, char ch='a', int z); // error!!`
   * `void Display(int x=1, int y=2, char ch, int z=3); // error!!`

2. 함수로 전달된 argument들은 왼쪽부터 순서대로 parameter 목록에 대입됩니다. 따라서 default argument가 설정된 함수를 호출할 때에 인수의 전달을 건너뛸 수 없습니다.

   * `void Display(int x, int y, char ch='a', int z=4);`
     * `Display(1, 2);` 👍    Display(1, 2, 'a', 4)와 같음
     * `Display(3, 4, 'b');` 👍    Display(3, 4, 'b', 4)와 같음
     * `Display(5, 6, 10);` 👎    인수 전달은 건너뛸 수 없음

3. default argument는 딱 1번만 정의될 수 있습니다.

  * 함수 선언 부분에 default argument를 명시하고, 함수의 정의에서는 default argument를 생략하도록 합시다.

   ``` c++
   void printValues(int x, int y=10);
   
   void printValues(int x, int y=10) // error: redefinition of default argument
   {
       std::cout << "x: " << x << '\n';
       std::cout << "y: " << y << '\n';
   }
   ```


## 2. function overloading

### 함수 오버로딩이 왜 필요할까요?

함수 오버로딩을 설명하기에 앞서 지난주에 배운 함수를 다시 떠올려봅시다.

``` c++
#include <iostream>
 
int add(int x, int y) {
  return x + y;
}
 
int main() {
  std::cout << add(3, 5) << std::endl;
 
  return 0;
} 
```

위와 같은 코드에서 함수 `add`는 int형 parameter `x, y`를 받아서 둘을 더하고 그 결과를 int형으로 반환합니다. 따라서 위의 코드를 실행하면 `8`이 출력될 것입니다.

그런데, 만약 함수 add에 int형이 아닌 double형 인자를 넘겨주면 어떻게 될까요? 인자를 `3.3, 5.5`로 바꾸고 컴파일 해보세요!

컴파일에러는 나지 않지만 예상했던 결과 `8.8`이 아니라 여전히 `8`이 출력되는 것을 확인하셨을 겁니다. 이는 실수형 값이 정수형 변수에 대입되면 소수점 아래가 날라가는 형변환이 자동으로 발생했기 때문입니다. 

> 이와 같이 자동으로 형변환이 일어나는 것을 암시적 형변환이라 합니다.

그럼 인자의 type에 맞게 함수를 여러개 정의해볼까요?

``` c++
#include <iostream>

int addInt(int x, int y) {
  return x + y;
}

double addDouble(double x, double y) {
  return x + y;
}

int main() {
  std::cout << addInt(3, 5) << std::endl;
 	std::cout << addDouble(3.3, 5.5) << std::endl;
  return 0;
} 
```

똑같이 두 인자를 더한 값을 반환하는 함수인데 인자의 type에 따라 다른 함수 이름을 써야한다니.. 뭔가 더 좋은 방법이 있을 것 같죠? 이런 불편함을 해소하기 위해 **함수 오버로딩**이라는 기능이 등장했습니다. 

함수 오버로딩을 사용해 코드를 다시 작성해보면 다음과 같습니다.

``` c++
#include <iostream>

int add(int x, int y) {
  return x + y;
}

double add(double x, double y) {
  return x + y;
}

int main() {
  std::cout << add(3, 5) << std::endl;  // int add(int x, int y) 함수 호출
 	std::cout << add(3.3, 5.5) << std::endl;  // double add(double x, double y) 함수 호출
  return 0;
} 
```

위와같이 함수호출 시 전달되는 **인자**를 통해서 호출하고자 하는 함수를 구분할 수 있으며, 이러한 기능을 함수 오버로딩이라고 부릅니다.

### 함수 시그니처 (function signature)

함수 오버로딩의 핵심을 바로 함수 시그니처(function signature)에 있습니다.

함수 시그니처란 **함수의 원형에 명시되는 매개변수 리스트**를 가리킵니다.

만약 두 함수가 매개변수의 :white_check_mark:**개수**와 그 :white_check_mark:**type**이 모두 같다면, 두 함수의 시그니처는 같다고 할 수 있습니다.

함수 오버로딩은 서로 다른 시그니처를 갖는 여러 함수를 같은 이름으로 정의하는 것이라고 할 수 있습니다.

``` c++
int add(int x, int y);
double add(double x, double y); // type을 달리함
int add(int x, int y, int z); // 개수를 달리함
```

### :bangbang: ​function overloading을 사용할 때 주의할 점 :bangbang:

아래의 3가지 경우는 overloading을 실패한 경우로, 컴파일 과정에서 오류가 발생하게 됩니다.

1. return type만 다른 경우 :ng_woman:

   ``` c++
   int foo1(char c) {
     return 0;
   }
   
   double foo1(char c) {
     return 0.0;
   }
   ```

   > error: functions that differ only in their return type cannot be overloaded

2. 인자의 이름만 다른 경우 :ng_woman:

   ``` c++
   int foo2(int a, int b) {
     return a + b;
   }
   
   int foo2(int x, int y) {
     return x + y;
   }
   ```

   > error: redefinition of 'foo2'

3. 디폴트 인자에 의해서, 궁극적으로 인자의 개수가 같은 경우 :ng_woman:

   ``` c++
   int foo3(int a) {
     return a;
   }
   
   int foo3(int a, int b=0) {
     return a + b;
   }
   ```

   > error: call to 'foo3' is ambiguous

## 3. Recursive call

재귀 호출이란 함수 내부에서 함수 자기 자신을 또다시 호출하는 것을 말합니다.

처음에는 재귀 호출이 왜 필요한가에 대해 이해하기 힘들 수도 있습니다. 하지만 재귀 호출은 알고리즘이나 자료 구조론에서는 매우 중요한 개념 중 하나입니다. 또한, 재귀 호출을 사용하면 복잡한 문제도 매우 간단하게 표현할 수 있습니다.

### Factorial function

재귀 호출을 설명할 때 빠질 수 없는 Factorial 함수를 구현해봅시다!

먼저, 재귀 호출을 이용하지 않고 반복문을 사용해 구현하면 다음과 같습니다.

``` c++
#include <iostream>

int fatorial(int num) {
  int result = 1;
  for (int i = num; i > 0; i--) {
    result *= i;
  }
  return result;
}

int main(void) {
  int n;
  std::cout << "Enter a number: ";
  std::cin >> n;
  std::cout << "The value of " << n <<"! is " << factorial(n) << std::endl;
  return 0;
}
```

이제 위의 함수를 재귀 호출을 사용해 다시 작성해봅시다.

``` c++
int fatorial(int num) {
  // Terminate condition
  if (num == 1) return num;
  // Recursive case
  return num * factorial(num - 1);
}
```

> 코드가 훨씬 간결해졌습니다!

### Terminate condition

재귀 호출을 사용해 함수를 작성할 때, 가장 주의해야 할 부분은 바로 **종료 조건**입니다. 

재귀 호출은 자기가 자신을 계속해서 호출하므로, 재귀 호출을 중단하기 위한 종료 조건을 명시해두지 않으면 스택 오버플로우에 의해 종료될 것입니다.

> 스택 오버플로우(stack overflow)는 메모리 구조 중 스택(stack) 영역에서 해당 프로그램이 사용할 수 있는 메모리 공간을 넘어서 사용하려고 할 때 발생합니다.

위에서 다룬 팩토리얼 함수에서는 `if (num == 1) return num;` 이 terminate condition 입니다.

### Recursive vs. Iterative

|           | Iterative                                          | Recursive                                |
| --------- | -------------------------------------------------- | ---------------------------------------- |
| 기본      | 명령을 반복적으로 실행                             | 함수 자체를 호출                         |
| 조건      | 제어 조건이 참이라면 무한 반복 발생                | 조건에 수렴하지 않을 경우 무한 재귀 발생 |
| 무한 반복 | CPU 사이클을 반복적으로 사용 (무한 루프)           | 스택 오버플로우 발생 (비정상 종료)       |
| 속도      | 빠름                                               | 느림                                     |
| 가독성    | 코드 길이가 길어지고 변수가 많아져 가독성이 떨어짐 | 코드 길이와 변수가 적어 가독성이 높아짐  |

위의 표를 보면 재귀함수보다 반복문이 좋아보입니다. 그럼, 재귀 함수를 사용하는 이유는 무엇일까요?

1. 알고리즘 자체가 재귀적인 표현이 자연스러운 경우에 재귀함수를 쓰는 것이 유용합니다.
2. 변수 사용을 줄여줄 수 있습니다. 
3. 가독성이 향상됩니다.