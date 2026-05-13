// This program finds the average time spent programming by a student
// each day over a three day period.

// Dan Dan

#include <iostream>
using namespace std;

int main() {
  int numStudents;
  float numHours_cs, total_cs, average_cs, numHours_bio, total_bio, average_bio;
  int student, day = 0; // these are the counters for the loops

  cout << "This program will find the average number of hours a day"
       << " that a student spent programming over a long weekend\n\n";
  cout << "How many students are there ?" << endl << endl;
  cin >> numStudents;

  int numDays; // Exercise 1
  cout << "Enter the number of days in the long weekend" << endl;
  cin >> numDays;

  for (student = 1; student <= numStudents; student++) {
    total_cs = 0;
    total_bio = 0;

    for (day = 1; day <= numDays; day++) {
      cout << "Please enter the number of hours spent programming by student "
           << student << " on day " << day << "." << endl;
      cin >> numHours_cs;

      cout << "Please enter the number of hours spent on biology by student "
           << student << " on day " << day << "." << endl;
      cin >> numHours_bio;

      total_cs = total_cs + numHours_cs;
      total_bio = total_bio + numHours_bio;
    }

    average_cs = total_cs / numDays;
    average_bio = total_bio / numDays;

    cout << endl;
    cout << "The average number of hours per day spent programming by "
         << "student " << student << " is " << average_cs;

    cout << endl;
    cout << "The average number of hours per day spent on biology by "
         << "student " << student << " is " << average_bio << endl;

    if (average_cs > average_bio) {
      cout << "Student " << student << " spent more time on programming."
           << endl
           << endl;
    } else if (average_cs < average_bio) {
      cout << "Student " << student << " spent more time on biology." << endl
           << endl;
    } else {
      cout << "Student " << student << " spent the same time on both subjects."
           << endl
           << endl;
    }
  }

  return 0;
}
