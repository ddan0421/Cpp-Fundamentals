#include <iostream>

using namespace std;

int main(){
  /*
   * switch statement format
   * switch (expression) // integer
   * {
   *  case exp1: statement1;
   *  case exp2: statement2;
   *  ...
   *  case expn: statementn;
   *  default: statementn+1;
   * }
   *
   *
   * 1) expression must be an integer variable
   * or an expression that evaluates to an integer value 
   * 2) exp1 through expn must be constant integer expressions or
   * literals, and must be unique in the switch statement
   * 3) default is optional but recommended
   *
   * How it works
   * 1) expression is evaluated
   * 2) The value of expression is compared against exp1 through expn.
   * 3) If expression matches value expi, the program branches to the statement 
   * following expi and continues to the end of the switch 
   * 4) If no matching value is found, the program branches to the statement after 
   * default:
   *
   * break statement
   * Used to exit a switch statement 
   * If it is left out, the program "falls through"
   * the remaining statements in the switch statement 
   *
   * switch statement is a natural choice for menu-driven program:
   * - display the menu 
   * - then, get the user's menu selection
   * - use user input as expression in switch statement 
   * - use menu choices as expr in case statements 
   */ 

  char grade;

  cout << "What grade did you earn in Programming I?" << endl;
  cin >> grade;

  switch(grade)
  {
    case 'A': cout << "an A - Excellent work!" << endl;
      break;
    case 'B': cout << "you got a B - good job" << endl;
      break;
    case 'C': cout << "earning a C is satisfactory" << endl;
      break;
    case 'D': cout << "while D is passing, there is a problem" << endl;
      break;
    case 'F': cout << "you failed - better luck next time" << endl;
      break;
    default: cout << "You did not enter an A, B, C, D, or F" << endl;
  }


  return 0;
}

