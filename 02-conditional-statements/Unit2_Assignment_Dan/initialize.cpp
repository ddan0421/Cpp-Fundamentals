// This program tests whether or not an initialized value
// is equal to a value input by the user

// Dan Dan

#include <iostream>
using namespace std;

int main()
{
  int num1, num2; // num1 is not initialized

  cout << "Please enter an integer" << endl;
  cin >> num1;

  cout << "Please enter another integer" << endl;
  cin >> num2;

  cout << "num1 = " << num1 << " and num2 = " << num2 << endl;

  if (num1 == num2) // == is equality and = is assignment
    cout << "The values are the same. \nHey that's a coincidence!" << endl;

  else
    cout << "The values are not the same" << endl;

  return 0;
}
