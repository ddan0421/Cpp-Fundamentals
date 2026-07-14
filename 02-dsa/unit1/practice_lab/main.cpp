#include "SortedNumberList.h"
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  bool includeRemovals = true;

  // Numbers to insert during first loop:
  vector<double> numbersToInsert = {77.75, 15.25, -4.25, 63.5, 18.25, -3.5};

  // Insert each number and print sorted list's contents after each insertion
  SortedNumberList list;
  cout << fixed << setprecision(2);
  for (auto number : numbersToInsert) {
    cout << "List after inserting " << number << ": ";
    list.Insert(number);
    list.Print(cout, ", ", "", "\n");
  }

  if (includeRemovals) {
    cout << endl;

    vector<double> numbersToRemove = {77.75, // List's last element
                                      -4.25, // List's first element
                                      18.25, // Neither first nor last element

                                      // Remaining elements:
                                      15.25, 63.5, -3.5};

    // Remove numbers
    for (auto toRemove : numbersToRemove) {
      cout << "List after removing " << toRemove << ": ";
      list.Remove(toRemove);
      list.Print(cout, ", ", "", "\n");
    }
  }

  return 0;
}
