#include <iostream>

// Dan Dan
// Option 1

using namespace std;

float convertKiloToMiles(int);
float convertMilesToKilo(int);

int main() {
  int choice;

  while (true) {
    int choice;

    cout << "Please input" << endl
         << "1 Convert miles to kilometers" << endl
         << "2 Convert kilometers to miles" << endl
         << "3 Quit" << endl;

    cin >> choice;

    float input, output;

    if (choice == 1) {
      cout << "\nPlease input the miles to be converted" << endl;
      cin >> input;
      output = convertMilesToKilo(input);
      cout << input << " miles = " << output << " kilometers" << endl << endl;
    } else if (choice == 2) {
      cout << "\nPlease input the kilometers to be converted" << endl;
      cin >> input;
      output = convertKiloToMiles(input);
      cout << input << " kilometers = " << output << " miles" << endl << endl;
    } else if (choice == 3) {
      break;
    } else {
      cout << "Invalid choice. Please choose either 1 or 2 for converting "
              "either Kilo or Miles or enter 3 to Quit."
           << endl;
    }
  }
  return 0;
}

float convertKiloToMiles(int kilo) {
  float miles = static_cast<float>(kilo) * (0.621);
  return miles;
}

float convertMilesToKilo(int miles) {
  float kilo = static_cast<float>(miles) * (1.61);
  return kilo;
}
