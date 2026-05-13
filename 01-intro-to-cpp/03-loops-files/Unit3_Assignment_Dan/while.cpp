// Dan Dan

#include <iostream>
using namespace std;

// Exercise 1: The code is not user friendly because the loop stops only when
// the user enters 'x'. It would be nice to print out something to hint the user
// to enter a specific letter or number to quit.
//
// Exercise 2: Make the code more use friendly by making the print statement
// more detailed
//
// Exercise 3: After making the code more user friendly from Exercise 2 and then
// change the while loop to do-while loop. The program is changed a little bit.
// The do-while loop prints out the letter x if I want to quit the program. This
// shows that do-while loop will have the loop run at least once and checks the
// condition and then exits. However, for while loop it will skip the loop if
// the letter is x.

int main() {
  char letter;
  do {
    cout << "Enter a letter. Type 'x' to quit." << endl;
    cin >> letter;
    cout << "The letter you entered is " << letter << endl;
  } while (letter != 'x');

  return 0;
}
