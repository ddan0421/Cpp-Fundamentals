#include <iostream>

using namespace std;

int main() {

  // The increment and decrement operators
  int a = 9;
  a++;

  cout << a << endl;

  int b = 10;

  b--;

  cout << b << endl;

  // ++ and -- can be used before or after a variable;

  // pre-and post-operations will cause different comparisons

  int age = 49;
  if (age++ > 49)
    cout << "Congratulations - You have made it to the half-century"
         << " mark !" << endl;

  // The cout statement will not execute. The reason is that in the postfix
  // mode the comparison between age and 49 is made first. Then the value of age
  // is incremented by one.
  //
  // Things are much different if we replace the posfix operator with the prefix
  // operator:
  //
  if (++age > 49)
    cout << "Congratulations - You have made it to the half-century"
         << " mark !" << endl;
  // In this code age is incremented first. So its value is 50 when the
  // comparison is made. The conditional statement is true and the cout
  // statement is executed

  /*
   * while loop
   *
   * while (expression) // expression is evaluated and if true, then statement
   * is executed, and expression is evaluated
   * {
   *  statement_1;
   *  statement_2;
   *  ...
   * }
   */

  int num = 5;
  int numFac = 1;

  while (num > 0) {
    cout << "num is " << num << endl;
    numFac = numFac * num;
    num--;
  }

  cout << " 5! = " << numFac << endl;

  return 0;
}
