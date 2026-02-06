// This program illustrates the use of logical operators

// Dan Dan

#include <iostream>
using namespace std;

int main()
{
  char year;
  float gpa;

  cout << "What year student are you ?" << endl;
  cout << "Enter 1 (freshman), 2 (sophomore), 3 (junior), or 4 (senior)"
  << endl << endl;
  cin >> year;

  cout << "Now enter your GPA" << endl;
  cin >> gpa;

  if (gpa >= 2.0 && year == '4') // Exercise 1: can replace gpa >= 2.0 with !(gpa < 2.0)
    cout << "It is time to graduate soon" << endl;

  else
  // else if (year != '4' || gpa <2.0)// Exercise 2: you shouldn't replace with year < 4 or year <=3 because year is char type
    cout << "You need more schooling" << endl;

  return 0;
}
