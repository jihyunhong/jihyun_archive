/* 가지고 있는 달러를 은행에서 원화 현금으로 환전하려고 합니다.
   달러를 원화로 지폐와 동전의 수로 나타내어 보세요.
*/

#include <iostream>
#include "exchange.h"

int main(){

    int dollar;
    dollar = bankerAsk();
    exchange(dollar);

    return 0;
}
