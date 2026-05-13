// This program will read in prices and store them into a two-dimensional array.
// It will print those prices in a table form.

// Dan Dan

// Exercise 2:
// getprices have the parameters numOfRows and numOfCols passed by reference
// because we need to eventually reuse these variables (# of rows and # of
// columns) and the function allows us the modify and assign these variables and
// be used in printPrices. Therefore, printPrices() has those parameters paseed
// by values since the purpose is to use these variables not modifying them.

// Exercise 5:
// Highest price is 102.34
// lowest price is 1.45

#include <iomanip>
#include <iostream>
using namespace std;

const int MAXROWS = 10;
const int MAXCOLS = 10;

typedef float PriceType[MAXROWS][MAXCOLS]; // creates a new data type
                                           // of a 2D array of floats

void getPrices(PriceType, int &, int &); // gets the prices into the array
void printPrices(PriceType, int, int);   // prints data as a table
float findHighestPrice(PriceType, int, int);
float findLowestPrice(PriceType, int, int);

int main() {
  int rowsUsed;         // holds the number of rows used
  int colsUsed;         // holds the number of columns used
  PriceType priceTable; // a 2D array holding the prices

  getPrices(priceTable, rowsUsed,
            colsUsed); // calls getPrices to fill the array
  printPrices(priceTable, rowsUsed,
              colsUsed); // calls printPrices to display array
  float highest = findHighestPrice(priceTable, rowsUsed, colsUsed);
  cout << "Highest price is " << highest << endl;

  float lowest = findLowestPrice(priceTable, rowsUsed, colsUsed);
  cout << "lowest price is " << lowest << endl;

  return 0;
}

//*******************************************************************************
//	getPrices
//
//	task:	  This procedure asks the user to input the number of rows and
//	          columns. It then asks the user to input (rows * columns)
// number of 	          prices. The data is placed in the array. 	data in:
// none 	data out: an array filled with numbers and the number of rows
// and columns used.
//
//*******************************************************************************

void getPrices(PriceType table, int &numOfRows, int &numOfCols) {
  cout << "Please input the number of rows from 1 to " << MAXROWS << endl;
  cin >> numOfRows;

  cout << "Please input the number of columns from 1 to " << MAXCOLS << endl;
  cin >> numOfCols;

  for (int row = 0; row < numOfRows; row++) {
    for (int col = 0; col < numOfCols; col++) {
      // Fill in the code to read and store the next value in the array
      cout << "Please input a price of an item with 2 decimal places" << endl;
      cin >> table[row][col];
    }
  }
}

//***************************************************************************
//	printPrices
//
//	task:	  This procedure prints the table of prices
//	data in:  an array of floating point numbers and the number of rows
//	          and columns used.
//	data out: none
//
//****************************************************************************

void printPrices(PriceType table, int numOfRows, int numOfCols) {
  cout << fixed << showpoint << setprecision(2);

  for (int row = 0; row < numOfRows; row++) {
    for (int col = 0; col < numOfCols; col++) {
      // Fill in the code to print the table
      cout << setw(4) << table[row][col] << " ";
    }
    cout << endl;
  }
}

float findHighestPrice(PriceType table, int numOfRows, int numOfCols)
// This function returns the highest price in the array
{
  float highestPrice;
  highestPrice = table[0][0]; // make first element the highest price
  for (int row = 0; row < numOfRows; row++)
    for (int col = 0; col < numOfCols; col++)
      if (highestPrice < table[row][col])
        highestPrice = table[row][col];
  return highestPrice;
}

float findLowestPrice(PriceType table, int numOfRows, int numOfCols)
// This function returns the highest price in the array
{
  float lowestPrice;
  lowestPrice = table[0][0]; // make first element the highest price
  for (int row = 0; row < numOfRows; row++)
    for (int col = 0; col < numOfCols; col++)
      if (table[row][col] < lowestPrice)
        lowestPrice = table[row][col];
  return lowestPrice;
}
