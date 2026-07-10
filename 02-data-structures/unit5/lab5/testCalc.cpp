#include "myCalc.hpp"
#include "myLinkedList.hpp"
#include "myStack.hpp"
#include <iostream>
#include <string>

using namespace std;

void runTest(const string &expression, const string &expectedPostfix,
             int expectedValue) {
  myCalc c(expression);

  cout << "Input:            " << c.getInput() << endl;
  cout << "Expected postfix: " << expectedPostfix << endl;
  cout << "Actual postfix:   " << c.postFixInput() << endl;
  cout << "Expected value:   " << expectedValue << endl;
  cout << "Actual value:     " << c.evaluate() << endl;
  cout << "----------------------------------------" << endl;
}

void runResetTest() {
  cout << "Reset Input Test" << endl;

  myCalc c("2+3=");

  cout << "Original input:   " << c.getInput() << endl;
  cout << "Original postfix: " << c.postFixInput() << endl;
  cout << "Original value:   " << c.evaluate() << endl;

  c.resetInput("(4+6)*2=");

  cout << "Reset input expected:   (4+6)*2=" << endl;
  cout << "Reset input actual:     " << c.getInput() << endl;
  cout << "Reset postfix expected: 4 6 + 2 *" << endl;
  cout << "Reset postfix actual:   " << c.postFixInput() << endl;
  cout << "Reset value expected:   20" << endl;
  cout << "Reset value actual:     " << c.evaluate() << endl;

  cout << "----------------------------------------" << endl;
}

int main() {
  cout << "CSC 240 Lab 5 - myCalc Expanded Test Driver" << endl;
  cout << "Positive integers only; parentheses required; integer division."
       << endl;
  cout << "Postfix tokens should be separated by one space." << endl;
  cout << "----------------------------------------" << endl;

  cout << "Basic / Original-Style Tests" << endl;
  cout << "----------------------------------------" << endl;
  runTest("5/2=", "5 2 /", 2);
  runTest("2+4*6/5=", "2 4 6 * 5 / +", 6);
  runTest("244+54*65=", "244 54 65 * +", 3754);
  runTest("(2+3)*5=", "2 3 + 5 *", 25);
  runTest("(10+3)*(51/2)/(30-4)=", "10 3 + 51 2 / * 30 4 - /", 12);
  runTest("11/3+100-2*5/12-18=", "11 3 / 100 + 2 5 * 12 / - 18 -", 85);

  cout << "Additional Coverage Tests" << endl;
  cout << "----------------------------------------" << endl;

  // Left-to-right associativity for same-precedence operators
  runTest("20-5-3=", "20 5 - 3 -", 12);
  runTest("20/5/2=", "20 5 / 2 /", 2);

  // Parentheses overriding normal precedence
  runTest("100/(5*2)=", "100 5 2 * /", 10);

  // Nested / grouped parentheses
  runTest("((2+3)*(4+1))=", "2 3 + 4 1 + *", 25);

  // Mixed precedence, parentheses, subtraction, and division
  runTest("8*(3+2)-12/4=", "8 3 2 + * 12 4 / -", 37);

  // Single positive integer expression
  runTest("42=", "42", 42);

  // Public resetInput test
  runResetTest();

  return 0;
}
