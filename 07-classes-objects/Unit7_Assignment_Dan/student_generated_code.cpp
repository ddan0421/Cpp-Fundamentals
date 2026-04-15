#include <iostream>

using namespace std;

class SavingsAccount {
public:
  SavingsAccount();
  ~SavingsAccount();
  void initialDollars(float initDollars);
  void initialCents(float initCents);

  void depositDollars(float inputDollars);
  void depositCents(float inputCents);
  void withdrawDollars(float outDollars);
  void withdrawCents(float outCents);

  void displayTotal();

private:
  float dollars;
  float cents;
};

void SavingsAccount::initialDollars(float initDollars) {
  dollars = initDollars;
}
