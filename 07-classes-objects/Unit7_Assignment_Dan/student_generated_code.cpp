#include <iostream>

using namespace std;

class SavingsAccount {
public:
  SavingsAccount();
  SavingsAccount(int initDollars, int initCents);
  ~SavingsAccount();

  void deposit(int inputDollars, int inputCents);
  void withdraw(int outDollars, int outCents);

  void displayTotal();

private:
  void normalize();

  int dollars;
  int cents;
};

SavingsAccount::SavingsAccount() {
  dollars = 0;
  cents = 0;
}

SavingsAccount::SavingsAccount(int initDollars, int initCents) {
  dollars = initDollars;
  cents = initCents;
}

SavingsAccount::~SavingsAccount() {}

void SavingsAccount::normalize() {
  dollars += cents / 100;
  cents = cents % 100;

  if (cents < 0) {
    dollars -= 1;
    cents += 100;
  }
}

void SavingsAccount::deposit(int inputDollars, int inputCents) {
  dollars += inputDollars;
  cents += inputCents;
  normalize();
}

void SavingsAccount::withdraw(int withdrawDollars, int withdrawCents) {
  int totalCents = dollars * 100 + cents;
  int withdrawTotal = withdrawDollars * 100 + withdrawCents;

  if (withdrawTotal > totalCents) {
    cout << "Insufficient funds!" << endl;
    return;
  }

  dollars -= withdrawDollars;
  cents -= withdrawCents;
  normalize();
}

void SavingsAccount::displayTotal() {
  cout << "Dollars = " << dollars << " Cents = " << cents << endl;
}

int main() {
  int inputDollars, inputCents;

  char userChoice;
  bool existDepositTrue = false;
  bool existWithdrawTrue = false;

  cout << "Please input the initial dollars" << endl;
  cin >> inputDollars;

  cout << "Please input the initial cents" << endl;
  cin >> inputCents;

  SavingsAccount bank1(inputDollars, inputCents);
  SavingsAccount bank2;
  while (existDepositTrue == false) {
    cout << "Would you like to make a deposit? Y or y for yes" << endl;
    cin >> userChoice;
    if (userChoice == 'Y' || userChoice == 'y') {
      cout << "Please input the dollars to be deposited" << endl;
      cin >> inputDollars;

      cout << "Please input the cents to be deposited" << endl;
      cin >> inputCents;
      bank1.deposit(inputDollars, inputCents);
      bank2.deposit(inputDollars, inputCents);
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
      bank2.withdraw(inputDollars, inputCents);

    } else {
      existWithdrawTrue = true;
    }
  }

  bank1.displayTotal();
  bank2.displayTotal();

  return 0;
}
