#include "exchange.h"

#include <iostream>
#define EXCHANGE_RATE 1200

int bankerAsk(){
  int dollar;
  std::cout << "Banker : How much dollar do you wnat to exchange?\n"
    << "customer : "; 
  std::cin >> dollar;
  return dollar;
}

void exchange(int dollar){
  int money; 
  money = dollar * EXCHANGE_RATE;
 
  //implement here
  int KRW50000 = 0;
  int KRW10000 = 0;
  int KRW5000 = 0;
  int KRW1000 = 0;
  int KRW500 = 0;
  int KRW100 = 0;

  while (true){
    if (money >= 50000){
        KRW50000 += 1;
        money -= 50000;
    }

    else if(money >= 10000){
        KRW10000 += 1;
        money -= 10000;
    }
    else if(money >= 5000){
        KRW5000 += 1;
        money -= 5000;
    }
    else if(money >= 1000){
        KRW1000 += 1;
        money -= 1000;
    }
    else if(money >= 500){
        KRW500 += 1;
        money -= 500;
    }
    else if(money >= 100){
        KRW100 += 1;
        money -= 100;
    }
    else{
        break;
    }
}

std::cout << "KRW50000: " << KRW50000 <<std::endl;
std::cout << "KRW10000: " << KRW10000 <<std::endl;
std::cout << "KRW5000: " << KRW5000 <<std::endl;
std::cout << "KRW1000: " << KRW1000 <<std::endl;
std::cout << "KRW500: " << KRW500 <<std::endl;
std::cout << "KRW100: " << KRW100 <<std::endl;

std::cout << "EXCHANGED."<<std::endl;
	
}
    

