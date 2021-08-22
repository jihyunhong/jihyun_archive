# 1. arrayT class를 template class로 수정해주세요.

- main.cpp, test.cpp 파일은 건드리실 필요 없습니다.
- arrayT.h 에 선언되어있는 arrayT class를 참고하여 arrayT 클래스를 template class로 변환해주세요.

## TODO - arrayT.cpp, arrayT.h

### arrayT.h

* 주어진 코드에서는 int형 값만 받을 수 있습니다.
* 다양한 자료형을 받을 수 있도록 arrayT class를 template class로 수정해주세요.

### arrayT.cpp

* **생성자, 소멸자, assignment operator**
  * 기본 생성자는 제공해드렸습니다. size 값을 인자로 받는 생성자를 작성해주세요.
  * 소멸자와 assignment operator는 지금까지 해오던 대로 구현해주시면 됩니다.

* **getElement**
  * 인자로 받은 위치의 원소 값을 반환합니다.
  * 범위를 확인해서, 배열의 범위를 벗어난 경우 "Out of Range"를 출력하도록 해주세요.

* **getSize**
  * 배열의 크기를 반환합니다.

* **print**
  * 배열의 원소를 모두 출력합니다.


### 코드를 잘 작성하셨다면, 컴파일하고 실행했을 때 다음과 같이 출력되어야 합니다.
```
-- Check setElement() works --
Out of Range
Out of Range
Out of Range

-- Check assignment operator works --

-- First element of each arrays --
65
65.1
A

-- Check print() works --
arrayInt: 65 66 67 68 69 70 71 72 73 74 
arrayDouble: 65.1 66.1 67.1 68.1 69.1 70.1 71.1 72.1 73.1 74.1 
arrayChar: A B C D E F G H I J 

-- Check getElement() handles exception --
Out of Range
Out of Range
Out of Range
```

# 2. 더 큰 값을 반환하는 함수 max를 함수 template으로 작성해주세요.

* main.cpp은 수정하지 마시고, person.h에 모든 코드를 작성해주세요!

### 2-1. 두 값을 인자로 받아 더 큰 값을 반환하는 함수 template을 작성해주세요.

* 현재 max() 함수는 인자로 int형을 받고, int형 값을 반환합니다.
* 다양한 자료형의 인자를 받을 수 있도록 max 함수를 template화 해주세요.
* 두 인자의 자료형과 반환 type은 모두 같습니다.

### 2-2. 템플릿 특수화를 사용해 person.h에 선언되어있는 Person 클래스도 max 함수를 사용할 수 있도록 해주세요.

* Person이 max 함수의 인자로 들어오면, 두 사람의 키를 비교해 더 키가 큰 사람을 반환해줍니다.

### 2-3. Person class를 ostream에 넣었을 때 이름이 출력되도록 코드를 작성해주세요.

* 이를 위해 person.h를 수정해야할 수 있습니다.
