#ifndef PERSON_H_
#define PERSON_H_

#include <string>

class Person {
  private:
    std::string name_;
    int height_;
  public:
    Person(std::string name, int height){
      name_ = name;
      height_ = height;
    }
    int getHeight() const { return height_; };
    std::string getName() const { return name_; };
    
    friend std::ostream& operator<<(std::ostream &out, const Person &p){
      out << p.getName();
      return out;
    }
};

template <typename T>
T max(T num1, T num2){
  T max_num = num1;
  if (num2 > num1){
    max_num = num2;
  }
  return max_num;
}

//spcialization
template <>
Person max(Person p1, Person p2){
  if (p1.getHeight() > p2.getHeight()){
    return p1;
  }
  else{
    return p2;
  }
}

#endif


