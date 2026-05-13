// This program has the user input a number n and then finds the
// mean of the first n positive integers

// Dan Dan

// Exercise 1: The removal of static_cast<float> may truncates the decimal part
// of the results. When I enter odd numbers, the result should contain non-zero
// decimal parts. For example, if I enter the number 10, it should return 5.5
// but without the static_cast<float> it will return 5 which is truncated and
// wrong. When I enter even numbers, the result appear to be correct, but the
// result should contain zero in the decimal place, but it doesn't due to the
// truncation. For example, if I enter 11, the result should be 6.0 but it shows
// 6 due to the truncation.
//
// Exercise 2: If I enter a float such as 2.99, the variable value will truncate
// any float number since the variable value is integer. so the variable value
// will treat the input value 2.99 as 2. In the for loop, the value number will
// go from 1 to 2 and then stops.
//

#include <iostream>
using namespace std;

int main() {
  int n; // value is some positive number n
  int m;
  int total = 0; // total holds the sum of the first n positive numbers
  int number;
  float mean; // the average of the first n positive numbers
  int count = 0;

  cout << "Please enter a positive integer (start)" << endl;
  cin >> n;

  cout << "Please enter a positive integer (end)" << endl;
  cin >> m;

  if (n > 0 && m > 0) {
    for (number = n; number <= m; number++) {
      total = total + number;
      count++;
    } // curly braces are optional since there is only one statement

    mean = static_cast<float>(total) / count; // note the use of the typecast
                                              // operator here
    cout << "The average for the consecutive positive integers from " << n
         << " to " << m << " is " << mean << endl;
  }

  else
    cout << "Invalid input - integer must be positive" << endl;

  return 0;
}
