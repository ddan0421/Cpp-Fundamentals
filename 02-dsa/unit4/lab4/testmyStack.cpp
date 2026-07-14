#include "myLinkedList.hpp"
#include "myStack.hpp"
#include <iostream>

using namespace std;

int main() {
  myStack<int> s;

  cout << "Initial stack is" << endl;
  cout << s;
  cout << "Count is " << s.getCount() << endl;
  cout << "isEmptyStack is " << boolalpha << s.isEmptyStack() << endl;
  cout << endl;

  cout << "After push of 10 stack is" << endl;
  s.push(10);
  cout << s;
  cout << "Count is " << s.getCount() << endl;
  cout << "isEmptyStack is " << boolalpha << s.isEmptyStack() << endl;
  cout << endl;

  cout << "After push of 25 stack is" << endl;
  s.push(25);
  cout << s;
  cout << "Count is " << s.getCount() << endl;
  cout << "isEmptyStack is " << boolalpha << s.isEmptyStack() << endl;
  cout << endl;

  cout << "After push of 100 stack is" << endl;
  s.push(100);
  cout << s;
  cout << "Count is " << s.getCount() << endl;
  cout << "isEmptyStack is " << boolalpha << s.isEmptyStack() << endl;
  cout << endl;

  cout << "Top is " << s.getTop() << endl;
  cout << endl;

  s.pop();
  cout << "After pop stack is" << endl;
  cout << s;
  cout << "Count is " << s.getCount() << endl;
  cout << "isEmptyStack is " << boolalpha << s.isEmptyStack() << endl;
  cout << "Top after pop is " << s.getTop() << endl;
  cout << endl;

  cout << "Testing copy constructor" << endl;
  myStack<int> s2(s);
  cout << "Copied stack is" << endl;
  cout << s2;
  cout << "Count is " << s2.getCount() << endl;
  cout << "Top is " << s2.getTop() << endl;
  cout << endl;

  cout << "Testing assignment operator" << endl;
  myStack<int> s3;
  s3 = s;
  cout << "Assigned stack is" << endl;
  cout << s3;
  cout << "Count is " << s3.getCount() << endl;
  cout << "Top is " << s3.getTop() << endl;
  cout << endl;

  cout << "Testing self-assignment" << endl;
  s3 = s3;
  cout << s3;
  cout << "Count is " << s3.getCount() << endl;
  cout << "Top is " << s3.getTop() << endl;
  cout << endl;

  cout << "Modifying original stack with push(500)" << endl;
  s.push(500);
  cout << "Original stack is" << endl;
  cout << s;
  cout << "Count is " << s.getCount() << endl;
  cout << "Top is " << s.getTop() << endl;
  cout << endl;

  cout << "Copied stack should be unchanged" << endl;
  cout << s2;
  cout << "Count is " << s2.getCount() << endl;
  cout << "Top is " << s2.getTop() << endl;
  cout << endl;

  cout << "Assigned stack should be unchanged" << endl;
  cout << s3;
  cout << "Count is " << s3.getCount() << endl;
  cout << "Top is " << s3.getTop() << endl;
  cout << endl;

  cout << "Popping all elements from original stack..." << endl;
  s.pop();
  s.pop();
  s.pop();
  cout << s;
  cout << "Count is " << s.getCount() << endl;
  cout << "isEmptyStack is " << boolalpha << s.isEmptyStack() << endl;
  cout << endl;

  cout << "Testing pop on empty stack" << endl;
  s.pop();
  cout << s;
  cout << "Count is " << s.getCount() << endl;
  cout << "isEmptyStack is " << boolalpha << s.isEmptyStack() << endl;
  cout << endl;

  cout << "Testing separate empty stack" << endl;
  myStack<int> emptyStack;
  emptyStack.pop();
  cout << emptyStack;
  cout << "Count is " << emptyStack.getCount() << endl;
  cout << "isEmptyStack is " << boolalpha << emptyStack.isEmptyStack() << endl;

  return 0;
}
