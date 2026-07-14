#ifndef MYSTACK_H_
#define MYSTACK_H_

#include "myLinkedList.hpp"
#include <iostream>

/*************************************************************************
 *  Name: Dan Dan                              CSC 240
 *  Date: 07/06/2026                           Lab 4
 *************************************************************************
 *  Statement:
 *  This program implements a template stack class using inheritance.
 *  The stack is built on top of the myLinkedList class from Lab 3.
 *
 *  Specifications:
 *  The TOP of the stack must be the FRONT of the linked list.
 *  Reuse inherited linked-list methods to implement stack behavior.
 *
 *  Input -
 *  Data passed into stack methods through the test driver.
 *
 *  Output -
 *  Results printed to the console verifying correct stack behavior.
 *************************************************************************/

// LAB 4 STUDENT TEMPLATE FILE
//
// IMPORTANT:
// - This is a template class, so ALL function implementations must be
//   completed in this header file.
// - Do NOT create a separate .cpp file for this class.
// - myStack MUST inherit from myLinkedList.
// - Do NOT create a new node structure.
// - Do NOT directly manipulate node pointers in myStack.
// - The TOP of the stack must be the FRONT of the linked list.
// - push must NOT use addLast.
// - Do NOT use myLinkedList::print() to print the stack.
//
// Stack to Linked List Mapping:
// - push     -> addFirst
// - pop      -> deleteAt(0)
// - getTop   -> getFirst
// - getCount -> getCount (reuse)

template <class type> class myStack : public myLinkedList<type> {
public:
  /******************************************************************
   * Default constructor
   * POST:
   *    The stack is empty.
   ******************************************************************/
  myStack();

  /******************************************************************
   * Copy constructor
   * PRE:
   *    otherStack is a valid myStack object.
   * POST:
   *    This stack becomes a deep copy of otherStack.
   *    Modifying one stack must NOT affect the other.
   ******************************************************************/
  myStack(const myStack<type> &otherStack);

  /******************************************************************
   * Destructor
   * POST:
   *    All dynamically allocated memory used by this stack is released.
   ******************************************************************/
  ~myStack();

  /******************************************************************
   * operator=
   * PRE:
   *    rhs is a valid myStack object.
   * POST:
   *    This stack becomes a deep copy of rhs.
   *    Self-assignment is handled safely.
   *    Returns *this.
   ******************************************************************/
  myStack<type> &operator=(const myStack<type> &rhs);

  /******************************************************************
   * isEmptyStack
   * POST:
   *    Returns true if the stack is empty and false otherwise.
   ******************************************************************/
  bool isEmptyStack() const;

  /******************************************************************
   * push
   * PRE:
   *    theItem is a valid value of type.
   * POST:
   *    theItem is added to the TOP of the stack.
   *    count increases by 1.
   ******************************************************************/
  void push(const type &theItem);

  /******************************************************************
   * pop
   * PRE:
   *    None.
   * POST:
   *    If the stack is not empty, ONLY the TOP element is removed.
   *    If the stack is empty, the stack remains unchanged.
   ******************************************************************/
  void pop();

  /******************************************************************
   * getTop
   * PRE:
   *    The stack is not empty.
   * POST:
   *    Returns the TOP element without modifying the stack.
   ******************************************************************/
  type getTop() const;

  /******************************************************************
   * getCount
   * POST:
   *    Returns the number of elements currently in the stack.
   ******************************************************************/
  int getCount() const;

  /******************************************************************
   * print
   * PRE:
   *    outStream is a valid output stream.
   * POST:
   *    If the stack is empty, prints:
   *       EMPTY STACK
   *    Otherwise prints the stack from TOP to BOTTOM,
   *    one value per line.
   ******************************************************************/
  void print(std::ostream &outStream) const;
};

/***********************************************************************
 * operator<<
 * PRE:
 *    outStream is a valid output stream.
 * POST:
 *    Outputs the stack using print(outStream), then returns outStream.
 ***********************************************************************/
template <class type>
std::ostream &operator<<(std::ostream &outStream,
                         const myStack<type> &theStack);

// ================= STUDENT IMPLEMENTATIONS =================

template <class type> myStack<type>::myStack() {
  // Base class default constructor initializes an empty list/stack.
}

template <class type> myStack<type>::myStack(const myStack<type> &otherStack) {
  myLinkedList<type>::operator=(otherStack);
}

template <class type> myStack<type>::~myStack() {
  // Base class destructor releases all linked-list nodes.
}

template <class type>
myStack<type> &myStack<type>::operator=(const myStack<type> &rhs) {
  if (this != &rhs) {
    myLinkedList<type>::operator=(rhs);
  }
  return *this;
}

template <class type> bool myStack<type>::isEmptyStack() const {
  return myLinkedList<type>::isEmpty();
}

template <class type> void myStack<type>::push(const type &theItem) {
  myLinkedList<type>::addFirst(theItem);
}

template <class type> void myStack<type>::pop() {
  if (!isEmptyStack()) {
    myLinkedList<type>::deleteAt(0);
  }
}

template <class type> type myStack<type>::getTop() const {
  return myLinkedList<type>::getFirst();
}

template <class type> int myStack<type>::getCount() const {
  return myLinkedList<type>::getCount();
}

template <class type> void myStack<type>::print(std::ostream &outStream) const {
  if (isEmptyStack()) {
    outStream << "EMPTY STACK" << "\n";
    return;
  }

  myStack<type> tempStack(*this);

  while (!tempStack.isEmptyStack()) {
    outStream << tempStack.getTop() << "\n";
    tempStack.pop();
  }
}

template <class type>
std::ostream &operator<<(std::ostream &outStream,
                         const myStack<type> &theStack) {
  theStack.print(outStream);
  return outStream;
}

#endif /* MYSTACK_H_ */
