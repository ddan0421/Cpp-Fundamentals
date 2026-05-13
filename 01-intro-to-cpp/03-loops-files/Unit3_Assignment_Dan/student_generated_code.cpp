#include <iomanip>
#include <iostream>

// Option 1
//
// Dan Dan

using namespace std;
int main() {
  int coffee = 0, tea = 0, coke = 0, orange_juice = 0;
  int person = 1, choice;

  cout << "Please input the favorite beverage of person #" << person
       << ": choose 1, 2, 3, or 4 from the above menu or -1 to exit the program"
       << endl;
  cin >> choice;

  while (choice != -1) {
    switch (choice) {
    case 1:
      coffee++;
      break;
    case 2:
      tea++;
      break;
    case 3:
      coke++;
      break;
    case 4:
      orange_juice++;
      break;
    default:
      cout << "Invalid choice! Must choose from 1, 2, 3, or 4" << endl;
    }
    person++;
    cout << "Please input the favorite beverage of person #" << person
         << ": Choose 1, 2, 3, or 4 from the above menu or -1 to exit the "
            "program"
         << endl;
    cin >> choice;
  }

  cout << "The total number of people surveyed is " << person - 1
       << ". The results are as follows:" << endl;

  cout << left;
  cout << setw(15) << "Beverage" << setw(5) << "Number of Votes" << endl;
  cout << setw(15) << "Coffee" << setw(5) << coffee << endl;
  cout << setw(15) << "Tea" << setw(5) << tea << endl;
  cout << setw(15) << "Coke" << setw(5) << coke << endl;
  cout << setw(15) << "Orange Juice" << setw(5) << orange_juice << endl;

  return 0;
}
