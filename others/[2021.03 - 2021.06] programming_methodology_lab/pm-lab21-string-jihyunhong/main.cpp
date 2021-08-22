#include <iostream>
#include <fstream>
#include <vector>

#include "hangman.h"

int main(int argc, char *argv[]) {
  std::ifstream input;
  if (argc > 1) input.open(argv[1]);
  if (!input.is_open()) {
    return 1;
  }

  std::vector<std::string> v;
  while (input) {
    std::string word;
    getline(input, word);
    if (word.length() > 3) v.push_back(word);
  }
  input.close();

  Hangman hangman(v);
  hangman.run();

  return 0;
}
