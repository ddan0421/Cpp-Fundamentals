#include <iomanip>
#include <iostream>

using namespace std;

const int MAXROW = 3;
const int MAXCOL = 4;

typedef int GradeType[MAXROW][MAXCOL];

void getGrades(GradeType);
float getAverage(const GradeType &, int);

int main() {
  GradeType grades;
  getGrades(grades);

  cout << fixed << setprecision(2) << showpoint;
  cout << endl;

  cout << "Average grades per student:" << endl;
  cout << "Student 1: " << getAverage(grades, 0) << endl;
  cout << "Student 2: " << getAverage(grades, 1) << endl;
  cout << "Student 3: " << getAverage(grades, 2) << endl;

  return 0;
}

void getGrades(GradeType gradeArray) {
  for (int i = 0; i < MAXROW; i++) {
    cout << "Enter grades for Student " << i + 1 << ":" << endl;
    for (int j = 0; j < MAXCOL; j++) {
      cout << "Grade " << j + 1 << ": ";
      cin >> gradeArray[i][j];
    }
  }
}

float getAverage(const GradeType &gradeArray, int studentPos) {
  int sum = 0;
  for (const auto &var : gradeArray[studentPos]) {
    sum += var;
  }
  float average = static_cast<float>(sum) / (MAXCOL);
  return average;
}
