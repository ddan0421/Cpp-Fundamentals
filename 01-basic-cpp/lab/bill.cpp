// This program will read in the quantity of a particular item and its price.
// It will then print out the total price.
// The input will come from the keyboard and the output will go to
// the screen.

// Dan Dan

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
	int	quantity;		// contains the amount of items purchased 
	float itemPrice;	// contains the price of each item
	float totalBill;	// contains the total bill.
  string itemName;

  cout << "Please input the name of the item" << endl;
  getline(cin, itemName);

	cout << setprecision(2) << fixed << showpoint;	// formatted output 
	cout << "Please input the number of items bought" << endl;

	// Fill in the input statement to bring in the quantity.
  cin >> quantity;

	// Fill in the prompt to ask for the price.
  cout << "Please input the price of each item" << endl;

	// Fill in the input statement to bring in the price of each item.
  cin >> itemPrice;

	// Fill in the assignment statement to determine the total bill.
  totalBill = quantity * itemPrice;

	// Fill in the output statement to print total bill,
	// with a label to the screen.
  cout << "The item that you bought is " << itemName << endl;
  cout << "The total bill is $" << totalBill << endl;

	return 0;
}
