#include <iomanip>
#include <iostream>
#include <ostream>
using namespace std;

// This program will input American money and convert it to foreign currency

// Dan Dan

// Prototypes of the functions
void convertMulti(float dollars, float &euros, float &pesos);
void convertMulti(float dollars, float &euros, float &pesos, float &yen);
float convertToYen(float dollars);
float convertToEuros(float dollars);
float convertToPesos(float dollars);

const float EURORATE = 1.06;
const float PESOSRATE = 9.73;
const float YENRATE = 124.35;

int main() {
  float dollars;
  float euros;
  float pesos;
  float yen;

  cout << fixed << showpoint << setprecision(2);

  cout << "Please input the amount of American Dollars you want converted "
       << endl;
  cout << "to euros and pesos" << endl;
  cin >> dollars;

  // Fill in the code to call convertMulti with parameters dollars, euros, and
  // pesos
  convertMulti(dollars, euros, pesos);

  // Fill in the code to output the value of those dollars converted to both
  // euros and pesos
  cout << "The value of $" << dollars << " that you input is converted to "
       << euros << " Euros or " << pesos << " Pesos." << endl
       << endl;

  cout << "Please input the amount of American Dollars you want converted\n";
  cout << "to euros, pesos and yen" << endl;
  cin >> dollars;

  // Fill in the code to call convertMulti with parameters dollars, euros, pesos
  // and yen
  convertMulti(dollars, euros, pesos, yen);

  // Fill in the code to output the value of those dollars converted to euros,
  // pesos and yen
  cout << "The value of $" << dollars << " that you input is converted to "
       << euros << " Euros or " << pesos << " Pesos or " << yen << " Yen."
       << endl
       << endl;

  cout << "Please input the amount of American Dollars you want converted\n";
  cout << "to yen" << endl;
  cin >> dollars;

  // Fill in the code to call convertToYen
  yen = convertToYen(dollars);

  // Fill in the code to output the value of those dollars converted to yen
  cout << "The value of $" << dollars << " is equivalent to " << yen << " Yen."
       << endl
       << endl;

  cout << "Please input the amount of American Dollars you want converted\n";
  cout << " to euros" << endl;
  cin >> dollars;

  // Fill in the code to call convert ToEuros
  euros = convertToEuros(dollars);

  // Fill in the code to output the value of those dollars converted to euros
  cout << "The value of $" << dollars << " is equivalent to " << euros
       << " Euros." << endl
       << endl;

  cout << "Please input the amount of American Dollars you want converted\n";
  cout << " to pesos " << endl;
  cin >> dollars;

  // Fill in the code to call convertToPesos
  pesos = convertToPesos(dollars);

  // Fill in the code to output the value of those dollars converted to pesos
  cout << "The value of $" << dollars << " is equivalent to " << pesos
       << " Pesos." << endl
       << endl;

  return 0;
}

// All of the functions are stubs that just serve to test the functions
// Replace with code that will cause the functions to execute properly

//  **************************************************************************
//  convertMulti
//
//  task:   This function takes a dollar value and converts it to euros
//            and pesos
//  data in:  dollars
//  data out: euros and pesos
//
//  *************************************************************************

void convertMulti(float dollars, float &euros, float &pesos) {
  euros = convertToEuros(dollars);
  pesos = convertToPesos(dollars);
}

//  ************************************************************************
//  convertMulti
//
//  task:   This function takes a dollar value and converts it to euros
//            pesos and yen
//  data in:  dollars
//  data out: euros pesos yen
//
//  ***********************************************************************

void convertMulti(float dollars, float &euros, float &pesos, float &yen) {
  euros = convertToEuros(dollars);
  pesos = convertToPesos(dollars);
  yen = convertToYen(dollars);
}

//  ****************************************************************************
//  convertToYen
//
//  task:        This function takes a dollar value and converts it to yen
//  data in:     dollars
//  data returned: yen
//
//  ***************************************************************************

float convertToYen(float dollars) {
  float yen = dollars * YENRATE;
  return yen;
}

//  ****************************************************************************
//  convertToEuros
//
//  task:        This function takes a dollar value and converts it to euros
//  data in:     dollars
//  data returned: euros
//
//  ****************************************************************************

float convertToEuros(float dollars) {
  float euros = dollars * EURORATE;
  return euros;
}

//  *****************************************************************************
//  convertToPesos
//
//  task:        This function takes a dollar value and converts it to pesos
//  data in:     dollars
//  data returned: pesos
//
//  ****************************************************************************

float convertToPesos(float dollars) {
  float pesos = dollars * PESOSRATE;
  return pesos;
}
