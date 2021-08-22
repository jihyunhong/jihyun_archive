#include <iostream>
#include <vector>
#include <ctime>

#include "hangman.h"

Hangman::Hangman(std::vector<std::string> words) {
  srand(time(0));
  int n = rand() % words.size();
  word = words[n];

  // TODO
  guess.assign(word.size(), '_');   // guess는 단어 길이만큼 ‘_’로 초기화

  life = 5;   // life는 5로 초기화
}

// hello
void Hangman::run() {
  // TODO

  while(life > 0 && guess != word){   // while 조건문 만드는 법 공부하기...
    //int count = 0;
    printMan();
    std::cout << '[' << guess << "] ";
    char letter;
    std::cout << "Guess a letter: ";
    std::cin >> std::ws >> letter;  // stream에 남아있는 공백 문자를 제거해주고 입력을 받도록

    int index = word.find(letter);
    if (index == -1){
      std::cout << "Whoops! That letter isn't in there!" << std::endl;
      std::cout << "You have " << life << " guesses left." << std::endl << std::endl;
      life -= 1; 
    }
    else{
      //guess[index] = letter;
      for (int i=0; i<word.size(); i++){
        if (word.at(i) == letter){
          guess[i] = letter;
        }
      }
      // 행맨을 맞췄으면
      std::cout << "You found a letter!" << std::endl;
      std::cout << "You have " << life << " guesses left." << std::endl;
    }
  }
  
  printResult();
}

void Hangman::printMan() {
  int n = 5 - life;
  std::cout << "    ┏━━━┓\n";
  std::cout << "    ┃   "; (n > 0) ? std::cout << "●\n" : std::cout << "\n";
  std::cout << "    ┃  "; (n > 2) ? std::cout << "/|＼\n" : (n > 1) ? std::cout << " |＼\n" : std::cout << "\n";
  std::cout << "    ┃   "; (n > 3) ? std::cout << "|\n" : std::cout << "\n";
  std::cout << "    ┃  "; (n > 4) ? std::cout << "／\\\n" : (n > 3) ? std::cout << "／\n" : std::cout << "\n";
  std::cout << "    ┃\n";
  std::cout << "━━━━┛━━━━  ";
}

void Hangman::printResult() {
  if (life == 0) {
    printMan();
    std::cout << "\n\nyou lose...\n";
  } else {
    std::cout << "\nYeah! You got it!\n";
  }

  std::cout << "The word was \033[38;5;220m" << word << "\033[m.\n";
}
