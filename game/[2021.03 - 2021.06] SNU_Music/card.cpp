#include "card.h"

Card::Card(const std::string name, BankAccount* account) : cardName(name) {
  // TODO
  // account should be already existing BankAccount.
  // You should not make a new bank account in this constructor.
    withdrawalAccount = account;
}

const std::string& Card::GetName() const {
  // TODO
  return cardName;
}

BankAccount* Card::GetBankAccount() const {
  // TODO
  return withdrawalAccount;
}

bool Card::Pay(const int money) const {
  // TODO
  // pay money and return true.
  // This is not a credit card.
  // It is a debit card(check card).
  // One cannot use more money than the BankAccount balance.
  // If the BankAccount balance is not enough, return false
  // and the balance should remain the same.

  bool result = withdrawalAccount->Withdraw(money);

  if (result == false){
      return false;
  }
  return true;
}