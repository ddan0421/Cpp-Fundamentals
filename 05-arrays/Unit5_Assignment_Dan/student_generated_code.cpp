#include <iostream>

using namespace std;

// Dan Dan
// Option 3

// Write a program that will input letter grades (A, B, C, D, F), the
// number of which is input by the user (a maximum of 50 grades). The
// grades will be read into an array. A function will be called five times (once
// for each letter grade) and will return the total number of grades in that
// category. The input to the function will include the array, number of
// elements in the array and the letter category (A, B, C, D or F). The program
// will print the number of grades that are A, B, etc.

const int MAXGRADES = 50;
typedef char GradeType[MAXGRADES];
int getCount(const GradeType &, char);

int main() {
  int numIteration;
  GradeType letterArr;

  cout << "Please input the number of grades to be read in. (1-50)" << endl;
  cin >> numIteration;

  cout << "All grades must be upper case A B C D or F" << endl;

  for (int i = 0; i < numIteration; i++) {
    cout << "Input a grade" << endl;
    cin >> letterArr[i];
  }
  cout << endl << endl;
  cout << "Number of A=" << getCount(letterArr, 'A') << endl;
  cout << "Number of B=" << getCount(letterArr, 'B') << endl;
  cout << "Number of C=" << getCount(letterArr, 'C') << endl;
  cout << "Number of D=" << getCount(letterArr, 'D') << endl;
  cout << "Number of F=" << getCount(letterArr, 'F') << endl;

  return 0;
}

int getCount(const GradeType &array, char letter) {
  int count = 0;
  for (const auto &var : array) {
    if (var == letter) {
      count++;
    }
  }
  return count;
}
