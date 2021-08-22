# 430.211 프로그래밍 방법론 LAB 18 : Makefile
담당조교 : 남화용   
이메일 : hwayong.nam@scale.snu.ac.kr     
2021년 5월 3일 월요일

## Introduction
이번 시간에는 compile을 용이하게 하기 위한 Makefile에 대해 알아볼 예정입니다.


## Makefile
### make와 Makefile
* `make`는 파일 간의 종속관계를 파악하여 `Makefile`에 적힌 대로 컴파일러에게 명령하여 `shell`명령이 순차적으로 실행될 수 있도록 합니다.
* `Makefile`이 있는 디렉토리에서 `make` 명령어만 치면 컴파일이 됩니다!

### make 및 Makefile을 사용하면...
* 각 파일에 대한 반복적인 명령의 자동화로 인한 시간 절약
* 프로그램의 종속 구조를 빠르게 파악할 수 있으며 관리 용이
* 단순 반복 작업 및 재작성을 최소화

### Makefile의 구성
* 목적파일(`target`) : 명령어가 수행되어 나온 결과를 저장할 파일
* 의존성(`dependency`) : 목적파일을 만들기 위해 필요한 파일
* 명령어(`command`) : 실행 되어야 할 명령어들
* 매크로(`macro`) : 코드를 단순화 시키기 위한 방법

### Makefile의 구조
```
CC = g++
target1 : dependency1 dependency2
          command1 command2
target2 : dependency3 dependency4
          command3 command4
```
### Makefile 작성 규칙
* 매크로 정의는 `Makefile`에 정의한 대로 치환합니다.
* 명령어의 시작은 반드시 **탭**으로 시작합니다.
* Dependency가 없는 target도 사용 가능합니다.

### Makefile 작성 예제
목표 : `a.cpp`, `b.cpp`, `c.cpp`로 구성된 프로그램을 컴파일하여 `abc`라는 실행파일을 만들어보자.
1. 단순한 방법
```
abc : a.o b.o c.o
    g++ -o abc a.o b.o c.o 

a.o : a.cpp
    g++ -c -o a.o a.cpp

b.o : b.cpp
    g++ -c -o b.o b.cpp

c.o : c.cpp
    g++ -c -o c.o c.cpp

clean :
    rm *.o abc
```
* `clean`은 컴파일을 하면서 생기는 부산물인 오브젝트 파일들과 결과물인 실행파일을 `rm` 명령어로 지워줍니다.

* `rm *.o` 를 통해 object 파일인 .o파일들을 삭제해준다.

  

2. 매크로를 사용한 방법
* 매크로를 사용하면 좀 더 간편하고 깔끔한 Makefile을 작성할 수 있습니다.
```
CC = g++
CFLAGS = -c -o
TARGET = abc
OBJECTS = a.o b.o c.o

$(TARGET) : $(OBJECTS)
    $(CC) -o $(TARGET) $(OBJECTS)

a.o : a.cpp
    $(CC) $(CFLAGS) a.o a.cpp

b.o : b.cpp
    $(CC) $(CFLAGS) b.o b.cpp

c.o : c.cpp
    $(CC) $(CFLAGS) c.o c.cpp

clean :
    rm *.o abc
```



3. 내부 매크로를 사용한 방법

* 정해진 내부 매크로를 사용하면 더 간단하게 `Makefile`을 작성할 수 있습니다.
```
CC = g++
CFLAGS = -W -Wall
TARGET = abc
OBJECTS = a.o b.o c.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
    $(CC) $(CFLAGS) -o $@ $^

clean : 
    rm *.o $(TARGET)
```
* all은 타겟이 여러 개 일 때 사용합니다. 위 예제의 경우에는 작성하지 않았습니다.
* 타겟 파일을 만들기 위해서 OBJECTS들을 사용합니다. 이 때 오브젝트 파일이 없다면 오브젝트 파일과 이름이 동일한 cpp파일을 찾아서 생성합니다.
* -W -Wall : 아주 사소한 모호성에 대해서도 경고를 발생시킴(ex. define하고 사용하지 않은 변수에 대한 경고 등)
* $@ : 현재 타겟의 이름을 나타내는 매크로
* $^ : 현재 타겟의 종속 항목 리스트를 뜻하는 매크로
* 더 자세한 내용은 구글링을 해보세요~