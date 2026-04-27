#include <iostream>

using namespace std;

/*
Indicate that something unexpected has occurred or been detected␋
Allow program to deal with the problem in a controlled manner␋
Can be as simple or complex as program design requires


Terminology:

Exception: object or value that signals an error

Throw an exception: send a signal that an error has occurred

Catch/Handle an exception: process the exception; interpret the signal


Key Words:
throw – followed by an argument, is used to throw an exception
try – followed by a block { }, is used to invoke code that throws an exception
catch – followed by a block { }, is used to detect and process exceptions thrown
in preceding try block.  Takes a parameter that matches the type thrown.


Flow of Control:

1) A function that throws an exception is called from within a try block
2) If the function throws an exception, the function terminates and the try
block is immediately exited.  A catch block to process the exception is searched
for in the source code immediately following the try block.
3) If a catch block
is found that matches the exception thrown, it is executed.  If no catch block
that matches the exception is found, the program terminates.



*/

// // function that throws an exception
// int totalDays(int days, int weeks) {
//   if ((days < 0) || (days > 7))
//     throw "invalid number of days";
//   // the argument to throw is the
//   // character string
//   else
//     return (7 * weeks + days);
// }
//
// try // block that calls function
// {
//   totDays = totalDays(days, weeks);
//   cout << "Total days: " << days;
// } catch (char *msg) // interpret               //  exception
// {
//   cout << "Error: " << msg;
// }

/*
1) try block is entered.  totalDays function is called

2) If 1st parameter is between 0 and 7, total number of days is returned and
catch block is skipped over (no exception thrown)

3) If exception is thrown, function and
try block are exited, catch blocks are scanned for 1st one that matches the data
type of the thrown exception.  catch block executes

*/
double divide(int, int);
int main() {
  int num1, num2;
  double quotient;

  // Get two numbers.
  cout << "Enter two numbers: ";
  cin >> num1 >> num2;

  // Divide num1 by num2 and catch any potential exceptions
  try {
    quotient = divide(num1, num2);
    cout << "The quotient is " << quotient << endl;
  } catch (char *exceptionString) // If the exception is a string, the program
                                  // jumps to this catch clause
  {
    cout << exceptionString;
  }
  cout << "End of the program.\n";

  return 0;
}
double divide(int numerator, int denominator) {
  if (denominator == 0)
    throw "Error: Cannot divide by zero.\n";
  return static_cast<double>(numerator) / denominator;
}
