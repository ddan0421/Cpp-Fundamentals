#include <iostream>
#include <iomanip>

/*
 * I chose option1 for the lab 3.5 Student Generated Code Assignment
 */ 
using namespace std;

int main(){
  double grade1, grade2, grade3;
  cout << "Please input the first grade" << endl;
  cin >> grade1;
  cout << endl << "Please input the second grade" << endl;
  cin >> grade2;
  cout << endl << "Please input the third grade" << endl;
  cin >> grade3;

  double average_grade = (grade1 + grade2 + grade3) / 3.0;
 
  cout << setprecision(2) << fixed << showpoint;
  cout << endl << "The average of the three grades is " << average_grade << endl;

  return 0;

}


