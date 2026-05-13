#include "Tree.h"
#include <iostream>

using namespace std;

int main() {
  Tree oak;
  cout << "We have " << oak.getObjectCount() << " trees" << endl;
  Tree elm;
  cout << "We have " << elm.getObjectCount() << " trees" << endl;
  Tree pine;
  cout << "We have " << pine.getObjectCount() << " trees" << endl;

  return 0;
}

// Explain why objectCount remains shared among all instances.
// since objectCount has a keyword static in front of it. It is not tied to a
// single object. It belongs to the class, not the instance.
