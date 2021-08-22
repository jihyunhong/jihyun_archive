#include <iostream>

class Message {
public:
  Message& greet();
  Message& name(std::string name);
  Message& hbd();
  Message& thx();
  void period();
  void exclam();
};

/*  TODO
 1. name(std::string name)
 2. hbd()
 3. thx()
 4. period()
 5. exclam()
 */

Message& Message::name(std::string name) {
  std::cout << " " << name;
  return *this;
}

Message& Message::greet() {
  std::cout << " " << "Hi";
  return *this;
}

Message& Message::hbd() {
  std::cout << " " << "Happy birthday";
  return *this;
}

Message& Message::thx() {
  std::cout << " " << "Thank you";
  return *this;
}

void Message::period() {
  std::cout << "." << std::endl;
}

void Message::exclam() {
  std::cout <<  "!" << std::endl;
}


int main() {
  Message msg;
  msg.greet().name("Jihyun").exclam();
  msg.hbd().period();
  msg.thx().name("Jihyun").exclam();
  return 0;
}
