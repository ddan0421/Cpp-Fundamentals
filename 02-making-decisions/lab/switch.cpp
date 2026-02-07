// This program illustrates the use of the switch statement.

// Dan Dan

#include <iostream>
using namespace std;

int main()
{
  char grade;

  cout << "What grade did you earn in Programming I ?" << endl;
  cin >> grade;

  //Replace swithc statement with if else statement
  if (grade == 'A')
  {
    cout << "YOU PASSED!" << endl;
    cout << "an A - excellent work !" << endl;
  }
  else if (grade == 'B')
  { 
    cout << "YOU PASSED!" << endl;
    cout << "you got a B - good job" << endl;
  }
  else if (grade == 'C')
  {
    cout << "YOU PASSED!" << endl;
    cout << "earning a C is satisfactory" << endl;
  }
  else if (grade == 'D')
  { 
    cout << "YOU PASSED!" << endl;
    cout << "while D is passing, there is a problem" << endl;
  }
  else if (grade == 'F')
  {
      cout << "you failed - better luck next time" << endl;
  }
  else 
  {
    cout << "You did not enter an A, B, C, D, or F" << endl;

  }


  return 0;
}
