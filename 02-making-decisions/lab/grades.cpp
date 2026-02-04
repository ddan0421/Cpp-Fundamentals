// This program prints "You Pass" if a student's average is
// 60 or higher and prints "You Fail" otherwise

// Dan Dan

#include <iostream>
using namespace std;

int main()
{
  float average;  // holds the grade average

  cout << "Input your average:" << endl;
  cin >> average;

  if (average > 100)
    cout << "Invalid data" << endl;
  else if (average >= 90 && average <= 100)
    cout << "'A' category" << endl;
  else if (average >= 80 && average <= 89)
    cout << "'B' category" << endl;
  else if (average >= 60 && average <= 79) // average >= 60 will pass
    cout << "You Pass" << endl;
  else if (average >= 0 && average <= 59)
    cout << "You Fail" << endl;
  else
    cout << "Invalid data" << endl; // extra line to handle average < 0
                                
  return 0;
}
