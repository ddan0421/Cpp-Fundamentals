#include <iostream>

using namespace std;

class SavingsAccount {
public:
  SavingsAccount();
  ~SavingsAccount();
  void initialDollars(int initDollars);
  void initialCents(int initCents);

  void depositDollars(int inputDollars);
  void depositCents(int inputCents);
  void withdrawDollars(int outDollars);
  void withdrawCents(int outCents);

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

void SavingsAccount::initialDollars(int initDollars) { dollars = initDollars; }

void SavingsAccount::initialCents(int initCents) {
  cents = initCents;
  normalize();
}

void SavingsAccount::depositDollars(int inputDollars) {
  dollars += inputDollars;
}

void SavingsAccount::depositCents(int inputCents) {
  cents += inputCents;
  normalize();
}

void SavingsAccount::withdrawDollars(int withdrawDollars) {
  dollars -= withdrawDollars;
}

void SavingsAccount::withdrawCents(int withdrawCents) {
  cents -= withdrawCents;
  normalize();
}

void SavingsAccount::displayTotal() {
  cout << "Dollars = " << dollars << " Cents = " << cents << endl;
}

SavingsAccount::SavingsAccount() {}
SavingsAccount::~SavingsAccount() {}

int main() {
  int inputMoney;

  char userChoice;
  bool existDepositTrue = false;
  bool existWithdrawTrue = false;

  SavingsAccount bank1;

  cout << "Please input the initial dollars" << endl;
  cin >> inputMoney;
  bank1.initialDollars(inputMoney);

  cout << "Please input the initial cents" << endl;
  cin >> inputMoney;
  bank1.initialCents(inputMoney);

  while (existDepositTrue == false) {
    cout << "Would you like to make a deposit? Y or y for yes" << endl;
    cin >> userChoice;
    if (userChoice == 'Y' || userChoice == 'y') {
      cout << "Please input the dollars to be deposited" << endl;
      cin >> inputMoney;
      bank1.depositDollars(inputMoney);

      cout << "Please input the cents to be deposited" << endl;
      cin >> inputMoney;
      bank1.depositCents(inputMoney);
    } else {
      existDepositTrue = true;
    }
  }

  while (existWithdrawTrue == false) {
    cout << "Would you like to make a withdrawal? Y or y for yes" << endl;
    cin >> userChoice;
    if (userChoice == 'Y' || userChoice == 'y') {
      cout << "Please input the dollars to be withdrawn" << endl;
      cin >> inputMoney;
      bank1.withdrawDollars(inputMoney);

      cout << "Please input the cents to be withdrawn" << endl;
      cin >> inputMoney;
      bank1.withdrawCents(inputMoney);
    } else {
      existWithdrawTrue = true;
    }
  }

  bank1.displayTotal();
  return 0;
}
