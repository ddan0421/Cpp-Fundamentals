#include <iostream>

using namespace std;

int main() {

  // The increment and decrement operators
  int a = 9;
  a++;

  cout << a << endl;

  int b = 10;

  b--;

  cout << b << endl;

  // ++ and -- can be used before or after a variable;

  // pre-and post-operations will cause different comparisons

  int age = 49;
  if (age++ > 49)
    cout << "Congratulations - You have made it to the half-century"
         << " mark !" << endl;

  // The cout statement will not execute. The reason is that in the postfix
  // mode the comparison between age and 49 is made first. Then the value of age
  // is incremented by one.
  //
  // Things are much different if we replace the posfix operator with the prefix
  // operator:
  //
  if (++age > 49)
    cout << "Congratulations - You have made it to the half-century"
         << " mark !" << endl;
  // In this code age is incremented first. So its value is 50 when the
  // comparison is made. The conditional statement is true and the cout
  // statement is executed

  /*
   * while loop
   *
   * while (expression) // expression is evaluated and if true, then statement
   * is executed, and expression is evaluated
   * {
   *  statement_1;
   *  statement_2;
   *  ...
   * }
   */

  int num = 5;
  int numFac = 1;

  while (num > 0) {
    cout << "num is " << num << endl;
    numFac = numFac * num;
    num--;
  }

  cout << " 5! = " << numFac << endl;

  /*
   *
   * Counters - often a programmer needs to control the number of times a
   * particular loop is repeated. One common way to accomplish this is by using
   * a counter. A counter-controlled loop.
   */

  int score;
  float total = 0.0;
  float average;

  const int NUMBEROFTESTS = 5;
  int test = 1; // counter that controls the loop

  while (test <= NUMBEROFTESTS) {
    cout << "Enter your score on test " << test << ": " << endl;
    cin >> score;

    total = total + score;
    test++;
  }
  average = total / NUMBEROFTESTS;

  cout << "Your average based on " << NUMBEROFTESTS << " test scores is "
       << average << endl;

  /*
   * Use while loop as input validation
   * The loop is skipped for all valid input but for invalid input the loop is
   * executed and prompts the user to enter new (valid) input.
   */

  cout << "Please input your choice of drink "
       << "(a number from 1 to 4 or 0 to quit)" << endl;
  cout << " 1 - Coffee" << endl
       << " 2 - Tea" << endl
       << " 3 - Coke" << endl
       << " 4 - Orange Juice" << endl
       << endl
       << " 0 - QUIT" << endl
       << endl;
  int beverage;
  cin >> beverage;
  while (beverage < 0 || beverage > 4) {
    cout << "Valid choices are 0 - 4. Please re-enter: ";
    cin >> beverage;
  }

  /*
   * do-while loop
   * The while loop is a pre-test or top test loop.
   * Since we test the expression before entering the loop,
   * if the test expression in the while loop is initially false,
   * then no iterations of the loop will be executed.
   */
  int num1 = 5;
  int num2 = 7;
  do {
    num1 = num1 + 1;
    num2 = num2 - 1;

  } while (num2 < num1);
  // In this code the statements num1 = num1 + 1 and num2 = num2 - 1 are
  // executed exactly once. At this point num1 = 6 and num2 = 6 so the
  // expression num2 < num1 is false. Consequently, the program exits the loop
  // and moves to the next section of code.
  // A do-while loops can be useful for programs that involve a repeating menu.

  /* The for loop
   * for (initialization; test; update)
   *  statement; // or block in {}
   * No semicolon after the update expression or after the )
   */

  int count;
  for (count = 1; count <= 5; count++)
    cout << "Hello" << endl;

  int value;
  int total_num = 0;
  int number;
  float mean;

  cout << "Please enter a positive integer" << endl;
  cin >> value;

  if (value > 0) {
    for (number = 1; number <= value; number++) {
      cout << "number: " << number << endl;
      total_num = total_num + number;
      cout << "Total number: " << total_num << endl;
    } // curly braces are optional since
    // there is only one statement
    mean =
        static_cast<float>(total_num) / value; // note the use of the typecast
    // operator
    cout << "The mean average of the first " << value
         << " positive integers is " << mean << endl;
  } else
    cout << "Invalid input - integer must be positive" << endl;

  for (int row = 1; row <= 3; row++)
    for (int col = 1; col <= 3; col++)
      cout << row * col << endl;
  return 0;
}
