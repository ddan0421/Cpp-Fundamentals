// This program illustrates the use of a sentinel in a while loop.
// The user is asked for monthly rainfall totals until a sentinel
// value of -1 is entered. Then the total rainfall is displayed.

// Dan Dan

// Exercise 5: The problem seems to function correctly. If I enter -1 first. It
// will out put "No data has been entered." If I enter only values of 0 for one
// or more months, the program will still keep tracking and updating the total
// as 0, and the final result is 0 inches. The numerical data you should not
// enter is any negative value since there shouldn't be any negative inches of
// rainfall.
//
// Exercise 6: The purpose of if (month==1): cout << "No data has been entered"
// << endl; is to handle the case when the user enters -1 in the first run
// because during the first run, the month is already 1, so if month variable
// stays at 1 and doesn't get updated that means the user enteres -1 in the
// first run.
//

#include <iostream>
using namespace std;

int main() {
  // Fill in the code to define and initialize to 1 the variable month
  int month = 1;
  float total = 0, rain;

  cout << "Enter the total rainfall for month " << month << endl;
  cout << "Enter -1 when you are finished" << endl;

  // Fill in the code to read in the value for rain
  cin >> rain;

  // Fill in the code to start a while loop that iterates
  // while rain does not equal -1
  while (rain != -1) {
    // Fill in the code to update total by adding it to rain
    total = total + rain;
    // Fill in the code to increment month by one
    month++;

    cout << "Enter the total rainfall in inches for month " << month << endl;
    cout << "Enter -1 when you are finished" << endl;

    // Fill in the code to read in the value for rain
    cin >> rain;
  }

  if (month == 1)
    cout << "No data has been entered" << endl;

  else
    cout << "The total rainfall for the " << month - 1 << " months is " << total
         << " inches." << endl;

  return 0;
}
