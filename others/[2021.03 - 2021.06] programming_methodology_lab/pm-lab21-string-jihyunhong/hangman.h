#ifndef HANGMAN_H_
#define HANGMAN_H_

#include <vector>

class Hangman {
  std::string word;
  std::string guess;
  int life;
public:
  Hangman(std::vector<std::string> words);
  void run();
  void printMan();
  void printResult();
};

#endif  // HANGMAN_H_
