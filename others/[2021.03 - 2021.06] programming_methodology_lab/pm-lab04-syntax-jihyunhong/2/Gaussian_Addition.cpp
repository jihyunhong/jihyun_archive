//=========| cin.cpp |=========// 
/* 
   연습문제 2 : cin으로 자연수 n을 입력받아서 1부터 n까지의 합을 출력하시오.
               (Gaussian Addition 참고)

   출력은 아래와 같이 나오면 됩니다.
---------------------------------------
   n = 10
   result = 55
---------------------------------------
 */

#include <iostream>
using namespace std;

int main(){
    int n, i;
    int sum = 0;
    cout << "n = ";
    cin >> n;

    for (i=1; i<(n+1) ; i++){
        sum += i;
    }
    cout << "result = " << sum << endl;

    return 0;
}

