#include <cstdlib>
#include <iostream>

using namespace std;

void order(char &, char &);
void order(int &, int &);
void order(double &, double &);

int main() {
  string dataType;
  cout << "Select a data type among char, int, and double: ";
  cin >> dataType;

  cout << endl;

  if (dataType == "char" | dataType == "int" | dataType == "double") {

    if (dataType == "char") {
      char in1, in2;
      cout << "Enter the first value: ";
      cin >> in1;

      cout << endl;

      cout << "Enter the secound value: ";
      cin >> in2;

      order(in1, in2);

      cout << in1 << " " << in2 << endl;
    } else if (dataType == "int") {
      int in1, in2;
      cout << "Enter the first value: ";
      cin >> in1;

      cout << endl;

      cout << "Enter the secound value: ";
      cin >> in2;

      order(in1, in2);

      cout << in1 << " " << in2 << endl;

    } else {
      double in1, in2;
      cout << "Enter the first value: ";
      cin >> in1;

      cout << endl;

      cout << "Enter the secound value: ";
      cin >> in2;

      order(in1, in2);

      cout << in1 << " " << in2 << endl;
    }
  } else {
    cout << "Invalid Option" << endl;
    exit(0);
  }

  return 0;
}

void order(char &input1, char &input2) {
  char store;
  if (input1 > input2) {
    store = input1;
    input1 = input2;
    input2 = store;
  }
}

void order(int &input1, int &input2) {
  int store;
  if (input1 > input2) {
    store = input1;
    input1 = input2;
    input2 = store;
  }
}

void order(double &input1, double &input2) {
  double store;
  if (input1 > input2) {
    store = input1;
    input1 = input2;
    input2 = store;
  }
}
