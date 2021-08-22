#include <iostream>
#include <string>


/**
 * Lab Inheritacne
 * 이번 실습에서는 간단하게 inheritance를 c++로 구현할 것입니다.
 * Meat을 base class로 하는 Beef, Pork, Chicken을 구현하면 됩니다.
 * Meat Class를 수정하지 마세요!
 * 
 * 1. Inheritance class 구현 
 *   Meat을 상속하는 Beef, Pork와 Chicken class를 구현해 주세요.
 *   Beef는 public inheritance, Pork는 protected inheritance, Chicken은 private inheritance 입니다. 
 * 
 * 2. Inherited class인 Beef, Pork, Chicken이 만족해야 하는 조건은 다음과 같습니다.
 *   a. Beef.cook()은 Barbeque, Beef.cook2()는 Bulgogi를 리턴합니다.
 *      Beef.getName은 base가 된 Meat의 getName()을 호출합니다.
 *   b. Pork.cook()은 Barbeque, Pork.cook2()는 Jokbal를 리턴합니다.
 *      Pork.getName은 base가 된 Meat의 getName()을 호출합니다.
 *   c. Chicken.cook()은 Barbeque, Chicken.cook2()는 Fried Chicken 을 리턴합니다.
 *      Chicken.getName은 base가 된 Meat의 getName()을 호출합니다.
 */

class Meat
{
protected:
    std::string m_name;
 
    Meat(const std::string &name)
        : m_name(name) {}
 
public:
    const std::string& getName() const { return m_name; }
    std::string cook() const { return "Barbeque"; }
    std::string cook2() const { return "Meat pie"; }
};


// a. Beef.cook()은 Barbeque, Beef.cook2()는 Bulgogi를 리턴합니다.
//  *      Beef.getName은 base가 된 Meat의 getName()을 호출합니다.
class Beef: public Meat{
public:
    Beef()
        : Meat("Beef")
        {}
    using Meat::getName;
    using Meat::cook;
    std::string cook2() const { return "Bulgogi"; }
};


//  b. Pork.cook()은 Barbeque, Pork.cook2()는 Jokbal를 리턴합니다.
//  *      Pork.getName은 base가 된 Meat의 getName()을 호출합니다.
class Pork: protected Meat{
public:
    Pork()
       : Meat("Pork")
        {}

    using Meat::getName;
    using Meat::cook;
    std::string cook2() const { return "Jokbal"; }
};


// c. Chicken.cook()은 Barbeque, Chicken.cook2()는 Fried Chicken 을 리턴합니다.
//  *      Chicken.getName은 base가 된 Meat의 getName()을 호출합니다.
class Chicken: private Meat{
public:
    Chicken()
        : Meat("Chicken")
        {}
    using Meat::getName;
    using Meat::cook;
    std::string cook2() const { return "Fried Chicken"; }
};