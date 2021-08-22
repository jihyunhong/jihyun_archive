# 430.211 프로그래밍 방법론 : g++ compiler, gdb debugger
담당조교 : 도완주   
이메일 : wj.doh@scale.snu.ac.kr   
2021년 4월 30일 금요일


## Introduction
지금까지 실습에서 .cpp 파일을 실행파일로 변환할때 `make` 명령어를 입력했습니다.

사실 `make` 명령어는 해당 위치에 `Makefile`이라는 파일이 있을 때에만 실행되는 명령어로, `Makefile`에 적혀있는 `shell` 명령을 순차적으로 실행해 줄 뿐입니다. 

`Makefile`에 대해서는 다음 실습시간에 배우고, 오늘은 `Makefile`을 작성하기 위해 먼저 알고있어야 하는 **컴파일** 과정에 대해 배워보겠습니다.

또한, 대표적인 c++ compiler인 **g++ compiler**를 사용해 소스코드를 컴파일 해보고, **gdb debugger**를 사용해 디버깅까지 해보도록 하겠습니다!


## 1. 컴파일(Compile)

### 1) 컴파일? 컴파일러?

여러분이 작성한 c++ 코드는 "**소스 코드(source code)**"라고 부릅니다. 이러한 소스코드는 사람이 이해하기 쉽고, 편리하게 작성할 수 있도록 설계되어 있습니다.

한편, 기계는 0과 1밖에 모릅니다. 따라서 소스코드를 기계가 이해할 수 있도록 0과 1로 이루어진 "**바이너리 코드(binary code)**"로 변환해주는 과정이 필요합니다.

이때, 소스코드를 바이너리 코드로 변환해주는 과정을 **컴파일**이라고 부르며, 변환을 해주는 프로그램을 **컴파일러**라고 합니다.

### 2) 소스파일부터 실행파일까지
![language_processing_system](https://user-images.githubusercontent.com/34891481/115185812-8efbfd00-a11b-11eb-83e9-567902ffa63e.jpeg)
1. `test.cpp` 소스파일을 컴파일하게 되면
2. 전처리기(Preprocessor)가 사전에 정의되어 있는 지시자를 변환합니다. :point_right: `test.i` 전처리가 완료된 파일 생성
3. 컴파일러(Compiler)가 어셈블리 코드(.s)를 생성합니다. :point_right: `test.s` 어셈블리어로 이루어진 파일 생성
4. 어셈블러(Assembler)가 어셈블리코드를 기계어로 번역합니다. :point_right: `test.o` 오브젝트 파일 생성
5. 링커(Linker)를 통해 기계어들을 연결하고 묶어서 실행파일을 만들어줍니다. :point_right: `test` 실행파일 생성

#### 전처리기(preprocessor)

* 프로그램을 컴파일할 때 **컴파일 직전에 실행되는 별도의 프로그램**입니다.

* `#include` 와 같이 #으로 시작하는 "전처리기 지시문"을 통해 컴파일러가 실행되기 적전에 다양한 역할을 합니다. 

* 예를들어, `#define MYNAME "John Doe"` 라고 정의되어있는 파일에서 `printf(MYNAME);` 이 문장은 전처리기를 거쳐 `printf("John Doe")`로 치환됩니다. 

* 전처리기를 거치면 **.i** 파일이 생성됩니다.

  > :bulb: ​#define 외에도 #include, #error, #pragme 등 다양한 전처리 지시어들이 있습니다.

#### 컴파일러(Compiler)

* 해당 언어(C언어 혹은 C++언어 등)의 규칙에 맞게 작성되었는지를 확인합니다.
* 또한, 같은 동작을 하는 더 빠르고 효율적인 코드로 최적화해 주기도 합니다.
* 컴파일러를 거치면 어셈블리어로 작성된 어셈블리 코드(**.s**)가 생성됩니다.

#### 어셈블러(Assembler)

* 어셈블러는 어셈블리 코드를 오브젝트 코드(**.o**)로 변역해줍니다.
* 오브젝트 코드는 기계가 이해할 수 있는 0과 1로 이루어져있습니다.

#### 링커(Linker)
* 링커는 여러 개의 object 파일을 모아서 하나의 실행파일로 만들어 줍니다.
* 프로그래머가 작성한 소스코드 뿐만 아니라 기존에 제공되는 라이브러리들도 함께 묶어 줍니다.
* 여러 파일로 부터 발생되는 의존성(dependency)도 해결하여 올바르게 실행될 수 있도록 합니다.


## 2. g++ compiler

> :bulb: g++ 명령어를 사용하면 **preprocessing, compilation, assembly, and linking**을 모두 수행해줍니다!

### 1) g++ compiler version 확인하기

`g++ --version` 

### 2) 한 개의 cpp file 컴파일 하고 실행하기

형식: `g++ <filename>`

예:  **`g++ hello.cpp`**

결과: 현재 working directory에 `a.out`이라는 이름으로 실행파일이 생성됨	

실행: **`./a.out`**

### 3) assembling, linking을 하지 않고 compile만 하기 :point_right: -S 옵션!

형식: `g++ -S <filename>`

예: **`g++ -S hello.cpp`**

결과: 현재 working directory에 `hello.s`라는 이름의 어셈블리 파일이 생성됨

어셈블리 파일 확인: **`cat hello.s`**

### 4) link 과정을 생략하고 compile, assemble만 진행하기 :point_right: -c 옵션!

형식: `g++ -c <filename>`

예: **`g++ -c hello.cpp`**

결과: 현재 working directory에 `hello.o`라는 이름의 object file이 생성됨

### 5) 실행 파일의 이름 지정하기 :point_right: -o 옵션!

형식: `g++ -o <target_name> <filename>`

예: **`g++ -o main hello.cpp`**

결과: 현재 working directory에 `main`이라는 이름의 executable file이 생성됨

실행: **`./main`**

### 6) 여러개의 파일을 한꺼번에 컴파일하기

1. object file 생성:  `g++ -c helloWorld.cpp hello.cpp`  :point_right: helloWorld.o, hello.o
2. executable file 생성: `g++ -o main helloWorld.o hello.o` :point_right:  main

### 7) 컴파일 과정에서 생성되는 파일들 모두 남기기

형식: `g++ --save-temps <filename>`

예: **`g++ --save-temps hello.cpp`**

결과: hello.i, hello.s, hello.o 등의 파일들이 생성


## 3. Syntax error & Semantic error

Error는 보통 Syntax error와 Semantic error로 나누어집니다.

* **Syntax error**는 C++ 문법에 맞지 않는 statement에서 발생하는 에러로, syntax error는 compile 시간에 대부분 잡을 수 있습니다.

  ``` c++
  #include <iostream>
  
  int main(void) {
      std::cout < "Hi there"; << x; // invalid operator (<), extraneous semicolon, undeclared variable (x)
      return 0 // missing semicolon at end of statement
  }
  ```

* **Semantic error**는 문법적으로는 문제 없지만 프로그래머가 의도한 대로 코드가 동작하지 않을 때 발생하는 error입니다.

  ``` c++
  #include <iostream>
  
  int add(int x, int y) {
      return x - y; // function is supposed to add, but it doesn't
  }
  
  int main(void) {
      std::cout << add(5, 3); // should produce 8, but produces 2
      return 0;
  }
  ```

## 4. GDB Debugger

### 1) Debugging이란?

* 컴퓨터 프로그래밍에서, **debugging** 이란 프로그램에서 문제를 발견하고, 그 문제의 근원을 따로 떼어낸 후, 그 문제를 수정하거나 해결할 방법을 찾는 일련의 과정을 의미합니다.
* Debugger(debugging tool)는 target 프로그램을 테스트하고 debugging하기 위한 프로그램입니다. Debugger는 프로그래머가 컴퓨터 리소스의 변화와 진행중인 동작들을 추적할 수 있도록 해줍니다. 일반적으로 debugger들은 target program을 **특정 지점에서 돌리거나 멈출 수 있고**, **문제가 발생한 곳에서 변수값들을 확인**할 수 있습니다.
* 대표적인 debugger로는 **GDB**(**G**NU **D**e**B**ugger)가 있으며, Visual Studio와 같은 IDE는 내부 debugger가 존재하기도 합니다.
* macOS의 경우, gdb 대신 **lldb**를 사용합니다. [참고링크!](https://developer.apple.com/library/archive/documentation/IDEs/Conceptual/gdb_to_lldb_transition_guide/document/lldb-command-examples.html#//apple_ref/doc/uid/TP40012917-CH3-SW1)

### 2) GDB란?

* GDB(GNU Debbuger)는 GNU 소프트웨어 시스템을 위한 기본 debugger입니다. GDB는 다양한 UNIX 계열 OS에서 동작하는 이식성있는 디버거로, C, C++, Ada 등의 여러 프로그래밍 언어의 디버깅을 지원합니다.
* **GDB** 는 다음의 정보들을 제공해줍니다.

  * gdb를 실행시킬 때 **core dump**를 함께 넣어주면, 몇 번 signal과 함께 비정상적으로 종료되었는지, 종료된 이유는 무엇인지 알려줍니다.

    > Core dump란 프로그램이 비정상적으로 종료되는 경우 프로그램이 종료될 당시의 **메모리 상태**를 기록한 것입니다.

  * Function을 실행할 때 error가 발생했다면, 프로그램의 어떤 line이 그 function을 호출했는지, 그리고 그 parameters가 무엇인지 알려줍니다.

  * 프로그램의 실행 중 특정 지점에서, 프로그램 variable들의 값이 무엇인지 알 수 있습니다.
* **GDB** 의 동작
  
  * GDB는 간단한 command line interface를 제공합니다.
  * GDB를 이용해 사용자는 특정 지점까지 프로그램을 실행시키고, 그 특정 지점에서 멈추어 값들을 출력시키고, 한 번에 한 line씩 진행하며 변화된 값들을 출력할 수 있습니다.

### 3) GDB 설치 및 실행

1. ```$ gdb --version```를 입력하여 설치되어 있는지 확인!
> MAC의 경우, 앞으로 나오는 명령어에서 gdb 대신 lldb를 입력해주세요!

2. 설치되어 있지 않다면 ```$ sudo apt-get install gdb```로 설치해주세요.

3. `g++ -g -o <exe_filename> <source_filename>` : 디버깅을 하기 위해서는 -g 옵션과 함께 컴파일을 해주어야 합니다. 
   예) `g++ -g -o main hello.cpp`

   > :bulb: 
   > -g 옵션을 사용하면 gdb가 필요로하는 정보(=debugging symbol table)를 함께 만들어줍니다. 더 자세히 알고싶으신 분들은 "심볼 테이블(symbol table)" 또는 "디버그 심볼(debug symbol)"을 구글링해보세요 :)

4. `gdb <exe_filename>` : gdb를 실행파일과 함께 실행
   예) `gdb main`
   
5. 대표적인 gdb 명령어들:

   * `quit` (또는 `q`) : gdb를 종료합니다.

   * `list` (또는 `l`) : 소스 코드의 내용을 10줄씩 line number와 함께 보여줍니다.

   * `break` (또는 `b`) : breakpoint를 지정합니다.
     * `b` : 현재의 line에 breakpoint 지정
     * `b <line_number>` :  `<linenumber>` 번째 line에 breakpoint를 지정
     * `b main` : main function 시작점에 breakpoint를 지정
   * `run` (또는 `r`) : breakpoint나 error를 마주칠 때까지 프로그램을 실행합니다.
     * `r <arg1> <arg2>` : 실행파일에 인자를 넘겨줄 수 있습니다.
   * `continue` (또는 `c`) : 다음 breakpoint나 error를 마주칠 때까지 프로그램을 실행합니다.
   * `step` (또는 `s`) : 프로그램의 다음 line을 실행합니다.
   * `next` (또는 `n`) : step과 유사하지만, 함수의 경우 함수 전체를 수행하고 넘어간다. (함수 내부를 line by line으로 검사하지 않는다.)
   * `info break` (또는 `info b`) : 모든 breakpoint들을 나열합니다.
   * `delete` (또는 `d`) : breakpoint를 제거합니다.
     * `d` : 모든 breakpoint들을 제거
     * `d <breakpoint_number>` : `<breakpoint_number>`번째 breakpoint를 제거
   * `print` (또는 `p`) : 변수의 값을 확인하거나 함수, 객체의 주소를 확인합니다.
     * `p <variable>` : `<variable>` 이라는 이름의 변수의 현재 값을 확인
     * `p <function_name>` : `<function_name>` 이라는 이름의 함수의 주소값을 확인
   * `display <variable>` : `<variable>`이라는 이름의 변수의 값을 매번 화면에 출력해줍니다.
   * `set <variable> = <value>` : `<variable>` 이라는 이름의 변수에 `<value>` 를 할당합니다.
   * `watch <variable> == <value>` : `<variable>` 이라는 이름의 변수가 `<value>` 로 바뀔 때 코드가 멈추는 watchpoint를 지정합니다.

* 참고 
  * [GDB Tutorial](http://www.gdbtutorial.com/gdb_commands)
  * [GDB to LLDB command map (for mac)](https://lldb.llvm.org/use/map.html)

### 4) GDB 실습 :space_invader:

``` c++
#include <iostream>

int main(void) {
  double j;
  for (int i = 0; i < 5; i++) {
    j = i/2 + i;
    std::cout << i << ". j = " << j << std::endl;
  }
  
  return 0;
}
```

1. -g 옵션과 함께 컴파일 : `$ g++ -g -o gdb_lab gdb_lab.cpp`

2. 결과 예측 및 프로그램 실행:

   * j는 i를 2로 나눈 값에 i를 더한 값이 대입되므로 출력 결과는 다음과 같을 것이다.

     ``` 
     0. j = 0
     1. j = 1.5
     2. j = 3
     3. j = 4.5
     4. j = 6
     ```

   * 하지만 실제 실행 결과는 다음과 같다.

     ```
     0. j = 0
     1. j = 1
     2. j = 3
     3. j = 4
     4. j = 6
     ```

3. gdb 디버거를 사용해 코드 디버깅! :bug:

   * `$ gdb gdb_lab` : 실행파일과 함께 gdb를 실행합니다.

   * `(gdb) l` : 소스 내용을 10줄씩 출력합니다.

     ```c++
     1	#include <iostream>
     2
     3	int main(void) {
     4	  double j;
     5	  for (int i = 0; i < 5; i++) {
     6	    j = i/2 + i;
     7	    std::cout << i << ". j = " << j << std::endl;
     8	  }
     9
     10	  return 0;
     ```

   * `(gdb) b 5` : for 문부터 자세히 들여다보기 위해 5번째 line에 breakpoint를 설정합니다.

     ``` 
     Breakpoint 1 at 0x962: file gdb_lab.cpp, line 5.
     ```

   * `(gdb) r` : breakpoint까지 코드를 실행합니다.

     ```
     Starting program: /scale/cal/home/wjdoh/temp/gdb_lab
     
     Breakpoint 1, main () at gdb_lab.cpp:5
     5	  for (int i = 0; i < 5; i++) {
     ```

   * `(gdb) s` : 한 줄 씩 실행합니다.

     ```
     6	    j = i/2 + i;
     ```

   * `(gdb) s`

     ```
     7	    std::cout << i << ". j = " << j << std::endl;
     ```

   * `(gdb) p j` : 현재 line에서 `j`의 값을 확인합니다.

     ```
     $1 = 0
     ```

   * `(gdb) n` : 현재 코드에서는 함수로 넘어가는 부분이 없으므로 step과 똑같이 실행됩니다. (한 줄 실행)

     ```
     0. j = 0
     5	  for (int i = 0; i < 5; i++) {
     ```

   * `(gdb) display i` : gdb 명령을 실행할 때마다 변수 `i`의 값을 화면에 출력합니다.

     ```
     1: i = 0
     ```

   * `(gdb) display j` : gdb 명령을 실행할 때마다 변수 `j`의 값을 화면에 출력합니다.

     ```
     2: j = 0
     ```

   * `(gdb) n` 

     ```
     6	    j = i/2 + i;
     1: i = 1
     2: j = 0
     ```

   * `(gdb) n` 

     ```
     7	    std::cout << i << ". j = " << j << std::endl;
     1: i = 1
     2: j = 1
     ```

   * 여기서 j의 값이 잘못 저장되는 것을 확인할 수 있습니다!! `i` 는 정수형이기 때문에 나누기 연산이 정수형으로 계산됩니다. 따라서 `j = i/2 + i` 를 `j = (double)i/2 + i` 로 type casting해주면 오류가 해결됩니다.

### 5) 참고: CGDB

* **CGDB**란 GDB를 위한 가벼운 터미널 기반의 인터페이스로, 기존의 GDB 화면과 함께, 실행하고있는 소스코드를 분할된 화면으로 보여줍니다. (궁금하신 분들은 구글링 :eyes: )
> [cgdb](https://cgdb.github.io/)
* 설치 (optional)
```
$ git clone git://github.com/cgdb/cgdb.git
$ cd cgdb
$ ./autogen.sh
$ ./configure --prefix=/usr/local
$ make
$ sudo make install
```

<img width="778" alt="스크린샷 2021-04-19 오후 3 08 59" src="https://user-images.githubusercontent.com/34891481/115189285-34fe3600-a121-11eb-977b-70a6afad5d0d.png">
