// This program will allow the user to input from the keyboard
// whether the last word to the following proverb should be party or country:
// "Now is the time for all good men to come to the aid of their ___"
// Inputting a 1 will use the word party. Any other number will use the word
// country.

// Dan Dan
//
//
// Exercise 1: if I enter a float, it will first get truncated since the
// parameter only takes integer. Therefore, a float like -3.97 will become -3.
// It will output country since I used else statement to capture any input
// number other than 1.

#include <iostream>
#include <string>
using namespace std;

// Fill in the prototype of the function writeProverb.
void writeProverb(string);

int main() {
  string wordInput;

  cout << "Given the phrase:" << endl;
  cout << "Now is the time for all good men to come to the aid of their ___"
       << endl;

  /*
  cout << "Input a 1 if you want the sentence to be finished with party"
       << endl;
  cout << "Input a 2 if you want the sentence to be finished with country"
       << endl;
  */

  cout << "Please input the word you would like to have finish the proverb"
       << endl;

  cin >> wordInput;

  writeProverb(wordInput);

  /*
   * Exercise 2
    while (true) {
      cin >> wordCode;

      if (wordCode == 1 || wordCode == 2) {
        writeProverb(wordCode);
        break;
      } else {
        cout << "I'm sorry but that is an incorrect choice; Please input a 1 or
   2"
            << endl;
      }
    }
  */

  return 0;
}

//  ******************************************************************************
//  writeProverb
//
//  task:   This function prints a proverb. The function takes a number
//            from the call. If that number is a 1 it prints "Now is the time
//            for all good men to come to the aid of their party."
//            Otherwise, it prints "Now is the time for all good men
//            to come to the aid of their country."
//  data in:  code for ending word of proverb (integer)
//  data out: no actual parameter altered
//
//  *****************************************************************************

void writeProverb(string word) {

  /* Exercise 2
  // Fill in the body of the function to accomplish what is described above
  if (number == 1) {
    cout
        << "Now is the time for all good men to come to the aid of their party."
        << endl;
  } else if (number == 2) {
    cout << "Now is the time for all good men to come to the aid of their "
            "country."
         << endl;
  }
  */
  cout << "Now is the time for all good men to come to the aid of their "
       << word << endl;
}
