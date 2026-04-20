#include <iostream>
using namespace std;
// - instance variable: A member variable in a class. Each object has its own
// copy.
// - static variable: one variable shared among all objects of a class.
// - static member function: can be used to access static member variable; can
// be called before any objects are defined
//
class Tree {
private:
  static int objectCount; // Declaration of static member variable
public:
  // Constructor increments the shared count
  Tree() { objectCount++; }

  // Accessor function for objectCount
  int getObjectCount() const { return objectCount; }
};

// Definition and initialization outside the class
int Tree::objectCount = 0;

int main() {
  Tree oak;
  Tree elm;
  Tree pine;
  cout << "We have " << pine.getObjectCount() << " trees in our program!"
       << endl;
  return 0;
}
