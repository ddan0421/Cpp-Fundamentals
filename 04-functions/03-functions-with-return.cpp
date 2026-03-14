#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;
/*
 * Scope
 * Global scope - any identifier that can be accessed at any time during the
 * execution of the program.
 *
 * Local scope - refers to identifiers defined within a block. They are active
 * only within the bounds of that particular block.
 *
 * A block in C++ begins with a left brace { and ends with a right brace}
 *
 * name precedence - determine which memory location is active among a group of
 * two or more variables with the same name. The most recently defined variable
 * has precedence over any other variable with the same name.
 *
 * Lifetime - similar but not exactly the same as scope. It refers to the time
 * during a program that an identifier has storage assigned to it.
 */

/*
 * Static Local variables
 *  - the values of local variables do not remain between multiple function
 * calls.
 *  - There  may be times when a function needs to retain the value of a
 * variable between calls. can be done by defining the variable to be static,
 * which means it is initialized at most once and its memoery space is retained
 * even after the function in which it is defined has finished executing.
 *
 */

// here is a example of static local variables

// void showStatic(); // Function prototype
// void showStatic2();
//
// int main() {
//   // Call the showStatic function five times.
//   for (int i = 0; i < 5; i++)
//     showStatic();
//
//   cout << endl;
//
//   for (int i = 0; i < 5; i++)
//     showStatic2();
//   return 0;
// }
//
// void showStatic() {
//   static int statNum;
//   cout << "statNum is " << statNum << endl;
//   statNum++;
// }

/*
 * Output:
 * statNum is 0
 * statNum is 1
 * statNum is 2
 * statNum is 3
 * statNum is 4
 *
 * statNum is automatically initialized to 0. Notice that it retains its value
 * between function calls.
 */

// void showStatic2() {
//   static int statNum = 5;
//   cout << "statNum is " << statNum << endl;
//   statNum++;
// }

/*
 * Output:
 * statNum is 5
 * statNum is 6
 * statNum is 7
 * statNum is 8
 * statNum is 9
 *
 * statNum is automatically initialized to 0. Notice that it retains its value
 * between function calls.
 */

/*
 *
 *  Default Arguments
 *  - The number of arguments must equal the number of parameters.
 *  - It is possible to assign default values to all parameters so that the
 * calling instruction does not have to pass values for all the arguments.
 *  - These default values usually defined in the prototype.
 *  - pass by reference arguments should be placed first (since by their very
 * nature they must be included in the call). If an parameter is left out, then
 * all the following parameters must also be left out.
 */

// example of default arguments

// void calNetPay(float &net, int hours = 40, float rate = 6.00);
// // function prototype with default arguments specified
//
// int main() {
//   int hoursWorked = 20;
//   float payRate = 5.00;
//   float pay; // net pay calculated by the calNetPay function
//   cout << setprecision(2) << fixed << showpoint;
//   calNetPay(pay); // call to the function with only 1 parameter
//   cout << "The net pay is $" << pay << endl;
//   return 0;
// }
// void calNetPay(float &net, int hours, float rate) { net = hours * rate; }
//

// Functions that return value
/*
 * For value returning functions we replace the word void with the data type
of the value that is returned. Since these functions return one value, there
should be no effect on any parameters that are passed from the call. This means
that all parameters of value returning functions should be pass by value, NOT
pass by reference. Nothing in C++ prevents the programmer from using pass by
reference in value returning functions; however, they should not be used.
*/
//
//
// float calNetPay(int hours, float rate);
// int main()
// {
//   int hoursWorked = 20;
//   float payRate = 5.00;
//   float netPay;
//   cout << setprecision(2) << fixed << showpoint;
//   netPay = calNetPay(hoursWorked, payRate);
//   //This call to the function is not a stand-alone statement, but rather part
//   of an assignment statement. cout << " The net pay is $" << netPay << endl;
//   return 0;
// }
//
// float calNetPay(int hours, float rate)
// {
//   return hours * rate;
// }

/*
 * Overloading Functions
 *
 * The convention in C++ is that every variable, function, constant, etc. name
 * with the same scope needs to be unique. However, there is an exception. Two
 * or more functions may have the same name as long as their parameters differ
 * in quantity or data type. For example, a programmer could have two functions
 * with the same name that do the exact same thing to variables of different
 * data types.
 */

int square(int);
double square(double);

int main() {
  int userInt;
  double userFloat;

  cout << fixed << setprecision(2) << showpoint;
  cout << "Enter an integer and a floating-point value: ";
  cin >> userInt >> userFloat;

  // Display their squares.
  cout << "Here are their squares: ";
  cout << square(userInt) << " and " << square(userFloat) << endl;

  return 0;
}

int square(int num) { return num * num; }

double square(double num) { return num * num; }

/*
 * exit() function
 * - terminates the execution of a program
 * - Can be called from any function
 * - Can pass an int value to operating system to indicate satatus of program
 * termination
 * - Usually used for abnormal termination of program
 * - requires cstdlib header file
 *
 *   example:
 *    exit(0);
 *
 * - The cstdlib header defines two constants that are commonly passed, to
 * indicate success or failure:
 *   - exit(EXIST_SUCCESS);
 *   - exit(EXIST_FAILURE);
 */

/*
 * A stub is nothing more than a dummy function that is called
 * instead of the actual function. It usually does little more than write a
 * message to the screen indicating that it was called with certain arguments.
 */

// int findSqrRoot(int x); // prototype for a user defined function that
// // returns the square root of the number passed to it
// int main() {
//   int number;
//   cout << "Input the number whose square root you want." << endl;
//   cout << "Input a -99 when you would like to quit." << endl;
//   cin >> number;
//   while (number != -99) {
//     cout << "The square root of your number is " << findSqrRoot(number) <<
//     endl; cout << "Input the number whose square root you want." << endl;
//     cout << "Input a -99 when you would like to quit." << endl;
//     cin >> number;
//   }
//   return 0;
// }
// int findSqrRoot(int x) {
//   cout << "findSqrRoot function was called with " << x << " as its
//   argument\n"; return 0;
// } // This bold section is the stub.

/*
 * This example shows that the programmer can test the execution of main and the
 * call to the function without having yet written the function to find the
 * square root
 */

/*
 * A driver is a module that tests a function by simply calling it. While one
 * programmer may be working on the main function, another programmer may be
 * developing the code for a particular function. In this case the programmer is
 * not so concerned with the calling of the function but rather with the body of
 * the function itself. In such a case a driver (call to the function) can be
 * used just to see if the function performs properly.
 */

// int findSqrRoot(int x); // prototype for a user defined function that
// // returns the square root of the number passed to it
// int main() {
//   int number;
//   cout << "Calling findSqrRoot function with a 4" << endl;
//   cout << "The result is " << findSqrRoot(4) << endl;
//   return 0;
// }
// int findSqrRoot(int x) { return sqrt(x); }

// In this example, the main function is used solely as a tool (driver) to call
// the findSqrRoot function to see if it performs properly.
