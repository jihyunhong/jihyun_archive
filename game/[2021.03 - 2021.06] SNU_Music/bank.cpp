#include "bank.h"

BankAccount::BankAccount(const std::string name, int money) : bankName(name) {
  // TODO
  // Create BankAccount with name and initial balance = money
  balance = money;
}

const std::string& BankAccount::GetName() const {
  // TODO
  return bankName;
}

int BankAccount::GetBalance() const {
  // TODO
  return balance;
}

void BankAccount::Deposit(const int money) {
  // TODO
  // increase the balance
  balance += money;
}

bool BankAccount::Withdraw(const int money) {
  // TODO
  // Decrease the balance and return true.
  // However the operation should fail if balance is not enough.
  // In that case, return false and balance should not change.
  if (balance < money){
      return false;
  }

  balance -= money;
  return true;
}