// Tree.h

#include <iostream>
using namespace std;

class Tree {
private:
  static int objectCount; // Static member variable
public:
  Tree() { objectCount++; }
  static int getObjectCount() { return objectCount; }
};

// Definition outside the class
int Tree::objectCount = 0;
