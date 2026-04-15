#include <iostream>

using namespace std;

class SavingsAccount {
public:
  SavingsAccount();
  ~SavingsAccount();
  void initialDeposit(int initDollars, int initCents);
  void deposit(int inputDollars, int inputCents);
  void withdraw(int outDollars, int outCents);

  void displayTotal();

private:
  void normalize();

  int dollars;
  int cents;
};

void SavingsAccount::normalize() {
  dollars += cents / 100;
  cents = cents % 100;

  if (cents < 0) {
    dollars -= 1;
    cents += 100;
  }
}

void SavingsAccount::initialDeposit(int initDollars, int initCents) {
  dollars = initDollars;
  cents = initCents;
  normalize();
}

void SavingsAccount::deposit(int inputDollars, int inputCents) {
  dollars += inputDollars;
  cents += inputCents;
  normalize();
}

void SavingsAccount::withdraw(int withdrawDollars, int withdrawCents) {
  dollars -= withdrawDollars;
  cents -= withdrawCents;
  normalize();
}

void SavingsAccount::displayTotal() {
  cout << "Dollars = " << dollars << " Cents = " << cents << endl;
}

SavingsAccount::SavingsAccount() {}
SavingsAccount::~SavingsAccount() {}

int main() {
  int inputDollars, inputCents;

  char userChoice;
  bool existDepositTrue = false;
  bool existWithdrawTrue = false;

  SavingsAccount bank1;

  cout << "Please input the initial dollars" << endl;
  cin >> inputDollars;

  cout << "Please input the initial cents" << endl;
  cin >> inputCents;
  bank1.initialDeposit(inputDollars, inputCents);

  while (existDepositTrue == false) {
    cout << "Would you like to make a deposit? Y or y for yes" << endl;
    cin >> userChoice;
    if (userChoice == 'Y' || userChoice == 'y') {
      cout << "Please input the dollars to be deposited" << endl;
      cin >> inputDollars;

      cout << "Please input the cents to be deposited" << endl;
      cin >> inputCents;
      bank1.deposit(inputDollars, inputCents);
    } else {
      existDepositTrue = true;
    }
  }

  while (existWithdrawTrue == false) {
    cout << "Would you like to make a withdrawal? Y or y for yes" << endl;
    cin >> userChoice;
    if (userChoice == 'Y' || userChoice == 'y') {
      cout << "Please input the dollars to be withdrawn" << endl;
      cin >> inputDollars;

      cout << "Please input the cents to be withdrawn" << endl;
      cin >> inputCents;

      bank1.withdraw(inputDollars, inputCents);
    } else {
      existWithdrawTrue = true;
    }
  }

  bank1.displayTotal();
  return 0;
}
