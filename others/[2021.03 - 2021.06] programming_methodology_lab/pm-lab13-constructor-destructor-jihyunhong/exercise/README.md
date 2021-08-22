# 1. Queue & Stack

- 대표적인 자료구조인 queue와 stack을 간단하게 구현해봅시다.
- main.cpp은 건드리지 말아주세요!
- queue.h를 참고해 필요한 생성자와 소멸자의 정의를 queue.cpp에 작성해주세요.
- queue.h와 queue.cpp을 참고해 stack.h와 stack.cpp을 작성해주세요.

## Queue와 Stack은 다음과 같이 동작합니다.

* Queue: First-In First-Out (FIFO) 🎢
  * 제일 오래된 데이터가 제일 먼저 나옵니다.
  * 놀이공원에서 먼저 온 사람부터 놀이기구를 타는 것을 떠올리시면 됩니다.

* Stack: Last-In First-Out (LIFO) 🍽
  * 가장 최근에 저장된 데이터가 제일 먼저 나옵니다.
  * 접시가 쌓여있을 때 가장 마지막에 올려진 접시가 가장 먼저 사용되는 것을 떠올리시면 됩니다.

## 여러분이 구현하셔야 할 Queue, Stack class는 다음과 같습니다.

* **생성자**
  * Default constructor
    * Member initializer list를 사용해 size를 넣어주세요.
    * size는 5로 설정해주시고, arr에는 0, 1, 2, 3, 4를 순서대로 저장해주세요.
    * `Queue(또는 Stack): default constructor call`이라는 문장이 출력되도록 해주세요.
  * Parameter constructor
    * this pointer를 사용해 size 값을 저장해주세요.
    * size만큼 반복하면서 standard input으로(std::cin) 배열의 원소 값을 받아주세요.
    * `Queue(또는 Stack): parameter constructor call`이라는 문장이 출력되도록 해주세요.
* **소멸자**
  * stack, queue 각자의 동작에 맞게 원소를 출력해주세요.
  * ⭐️⭐️⭐️ 동적으로 할당받은 메모리 공간을 해제해주세요.
  * `Queue(또는 Stack): destructor call`이라는 문장이 출력되도록 해주세요.


## 출력 예시

```
  > Create queue1
Queue: default constructor call

  > Create queue2
Queue size = 3
arr[0] = 66
arr[1] = 99
arr[2] = 11
Queue: parameter constructor call

  > Create stack1
Stack: default constructor call

  > Create stack2
Stack size = 3
arr[0] = 66
arr[1] = 99
arr[2] = 11  // 비교를 쉽게 하기 위해 queue에서와 똑같이 원소를 넣어줬습니다.
Stack: parameter constructor call

End of program
11 99 66     // LIFO
Stack: destructor call
4 3 2 1 0
Stack: destructor call
66 99 11     // FIFO
Queue: destructor call
0 1 2 3 4 
Queue: destructor call
```

# 2. Message 💌

- self-reference를 반환하는 chainable function을 구현해봅시다!
- Message라는 클래스는 단어 또는 문장을 출력해주는 함수들을 갖고있는 클래스입니다.

## Message는 greet, name, hbd, thx, period, exclam 이렇게 6개의 멤버함수를 갖습니다.

- **greet, name, hbd, thx**
  * 각각 "Hi", 인자로 넘어온 이름, "Happy birthday", "Thank you"를 출력하는 동작을 합니다.
  * 단, self-reference를 반환해 chainable하게 호출될 수 있는 함수들입니다.
- **period, exclam**
  * 각각 ".", "!"를 출력하는 동작을 합니다. 
  * 이들은 문장을 끝내는 역할을 하기 때문에 chainable하지 않은 함수입니다.
- main 함수에는 name(/\*NAME\*/) 이 부분에 아무 이름이나 넣어주시는 것 외에는 수정하지 말아주세요!!
- (optional) 깔끔하게 출력되도록 적절하게 " ", "\n"을 넣어주시면 좋습니다 :)

## 출력 예시

``` 
 Hi wanju!
 Happy birthday.
 Thank you jongmin!
```