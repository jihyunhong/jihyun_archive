#include <iostream>

void move(char start, char dest)
{
  std::cout << start << "에서 " << dest << "로 이동\n";
}


// n개의 원반을 start에서 dest로 옮깁니다.
void hanoi(int n, char start, char via, char dest)
{
  // TODO 
  // Terminate condition
  if (n == 1) {  
    move(start, dest);
  }
  // Recursive case
  else {  
    hanoi(n-1, start, dest, via);
    hanoi(1, start, via, dest);
    hanoi(n-1, via, start, dest);
  }  

}

int main()
{
  int num;  // 원반의 개수를 저장할 변수

  std::cout << "원반의 개수를 입력하세요 : ";
  std::cin >> num;

  hanoi(num, 'a','b','c');

  return 0;
}
