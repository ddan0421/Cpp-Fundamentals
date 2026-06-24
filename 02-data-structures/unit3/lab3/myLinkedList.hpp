#ifndef MYLINKEDLIST_H_
#define MYLINKEDLIST_H_

#include <iostream>

/*************************************************************************
 *  Name: Dan Dan                              CSC 240
 *  Date: 06/24/2026                           Lab 3
 *************************************************************************
 *  Statement:
 *  This program implements a template class that represents a singly
 *  linked list. The class supports insertion, deletion, searching,
 *  indexed operations, deep copy behavior, and operator overloading
 *  using dynamic memory techniques.
 *
 *  Specifications:
 *  All member function implementations for this template class must be
 *  completed in this header file. Memory must be managed manually using
 *  new and delete. The list correctly maintains first, last, and
 *  count as nodes are added, copied, and removed.
 *
 *  Input -
 *  Data passed into class methods through the test driver.
 *
 *  Output -
 *  Results printed to the console from the test program, verifying
 *  correct behavior of linked list operations.
 *************************************************************************/

// LAB 3 STUDENT TEMPLATE FILE
//
// IMPORTANT:
// - This is a template class, so ALL function implementations must be
//   completed in this header file.
// - Do NOT create a separate .cpp implementation file for this class.
// - Test your work frequently using testmyLinkedList.cpp.
// - Build one function at a time, then test it before moving on.
// - Follow all preconditions and postconditions carefully.
// - Keep the output format exactly as shown in the expected output file.

template <class type> struct linkNode {
  type data;
  linkNode<type> *nextElement;
};

template <class type> class myLinkedList {
private:
  /******************************************************************
   * copyList
   * PRE:
   *    otherList is a valid linked list object.
   * POST:
   *    This list becomes a deep copy of otherList.
   *    All nodes in this list are newly allocated nodes.
   *    first, last, and count are updated correctly.
   *
   * TODO / HINTS:
   * - If this list already has nodes, clear it first.
   * - If otherList is empty, this list should become empty.
   * - Traverse otherList from front to back.
   * - Copy DATA, not node pointers.
   ******************************************************************/
  void copyList(const myLinkedList<type> &otherList) {
    destroyList();
    linkNode<type> *currentNode = otherList.first;
    while (currentNode != nullptr) {
      addLast(currentNode->data);
      currentNode = currentNode->nextElement;
    }
  }

protected:
  int count;             // number of elements in the list
  linkNode<type> *first; // pointer to the first node
  linkNode<type> *last;  // pointer to the last node

public:
  /******************************************************************
   * Destructor
   * POST:
   *    All dynamically allocated nodes are deleted.
   *    No memory leak remains from this object.
   *
   * TODO:
   * - Call destroyList().
   ******************************************************************/
  ~myLinkedList() { destroyList(); }

  /******************************************************************
   * Default constructor
   * POST:
   *    count == 0
   *    first == nullptr
   *    last  == nullptr
   ******************************************************************/
  myLinkedList();

  /******************************************************************
   * Array constructor
   * PRE:
   *    If n > 0, anArray points to a valid array of n elements.
   * POST:
   *    This list stores the array values in the SAME ORDER.
   *    count is set correctly.
   *    first and last are updated correctly.
   *
   * TODO / HINTS:
   * - Initialize data members first.
   * - If n <= 0 or anArray is invalid, the list should remain empty.
   * - Reuse addLast to keep logic simple.
   ******************************************************************/
  myLinkedList(int n, const type *anArray) {
    setDataMembers();
    if (n > 0 && anArray != nullptr) {
      for (int i = 0; i < n; i++) {
        addLast(anArray[i]);
      }
    }
  }

  /******************************************************************
   * Copy constructor
   * PRE:
   *    otherLinkedList is a valid linked list object.
   * POST:
   *    This list is a deep copy of otherLinkedList.
   *    Modifying one list must NOT change the other.
   *
   * TODO / HINTS:
   * - Initialize data members first.
   * - Then call copyList().
   ******************************************************************/
  myLinkedList(const myLinkedList &otherLinkedList) {
    setDataMembers();
    copyList(otherLinkedList);
  }

  /******************************************************************
   * getCount
   * POST:
   *    Returns the number of nodes currently in the list.
   ******************************************************************/
  int getCount() const { return count; }

  /******************************************************************
   * isEmpty
   * POST:
   *    Returns true if the list has no nodes.
   *    Returns false otherwise.
   *
   * TODO:
   * - Use count or first consistently.
   ******************************************************************/
  bool isEmpty() const {
    if (first == nullptr) {
      return true;
    } else {
      return false;
    }
  }

  /******************************************************************
   * print
   * PRE:
   *    outStream is a valid output stream.
   * POST:
   *    If the list is empty, prints EMPTY LIST.
   *    Otherwise prints all node values in order with arrows:
   *    value -> value -> value
   *
   * TODO / HINTS:
   * - Do not print an extra arrow after the last node.
   * - Match the expected output exactly.
   ******************************************************************/
  void print(std::ostream &outStream) const {
    if (isEmpty()) {
      outStream << "EMPTY LIST";
      return;
    }

    linkNode<type> *currentNode = first;
    while (currentNode != nullptr) {
      if (currentNode != first) {
        outStream << " -> ";
      }
      outStream << currentNode->data;
      currentNode = currentNode->nextElement;
    }
  }

  /******************************************************************
   * getFirst
   * PRE:
   *    The list is not empty.
   * POST:
   *    Returns the value stored in the first node.
   ******************************************************************/
  type getFirst() const { return first->data; }

  /******************************************************************
   * getLast
   * PRE:
   *    The list is not empty.
   * POST:
   *    Returns the value stored in the last node.
   ******************************************************************/
  type getLast() const { return last->data; }

  /******************************************************************
   * search
   * PRE:
   *    item is a valid value of type.
   * POST:
   *    Returns true if item is found in the list.
   *    Returns false otherwise.
   *
   * TODO / HINTS:
   * - A linear traversal is enough.
   * - You may reuse indexOf if desired.
   ******************************************************************/
  bool search(const type &item) const;

  /******************************************************************
   * addFirst
   * PRE:
   *    theItem is a valid value of type.
   * POST:
   *    theItem is inserted at the front of the list.
   *    first is updated correctly.
   *    If the list was empty, last is also updated.
   *    count increases by 1.
   *
   * TODO / HINTS:
   * - Allocate one new node.
   * - New node should point to the old first node.
   ******************************************************************/
  void addFirst(const type &theItem);

  /******************************************************************
   * addLast
   * PRE:
   *    theItem is a valid value of type.
   * POST:
   *    theItem is inserted at the end of the list.
   *    last is updated correctly.
   *    If the list was empty, first is also updated.
   *    count increases by 1.
   *
   * TODO / HINTS:
   * - Handle the empty-list case separately.
   ******************************************************************/
  void addLast(const type &theItem) {
    linkNode<type> *newNode = new linkNode<type>;
    newNode->data = theItem;
    newNode->nextElement = nullptr;

    if (first == nullptr) {
      first = newNode;
      last = newNode;
    } else {
      last->nextElement = newNode;
      last = newNode;
    }
    count++;
  }

  /******************************************************************
   * insertAt
   * PRE:
   *    location is intended to be between 0 and count inclusive.
   * POST:
   *    If location is valid:
   *       - theItem is inserted at that position
   *       - true is returned
   *       - count increases by 1
   *    If location is invalid:
   *       - the list is unchanged
   *       - false is returned
   *
   * TODO / HINTS:
   * - If location == 0, use addFirst.
   * - If location == count, use addLast.
   * - Otherwise move to the PREVIOUS node (the node just before
   *   the insertion point), then rewire pointers carefully.
   * - Order matters:
   *      newNode->nextElement = current->nextElement;
   *      current->nextElement = newNode;
   ******************************************************************/
  bool insertAt(int location, const type &theItem);

  /******************************************************************
   * deleteItem
   * PRE:
   *    item is a valid value of type.
   * POST:
   *    If item is found, only the FIRST occurrence is removed.
   *    If item is not found, the list is unchanged.
   *    first, last, and count are updated correctly.
   *
   * TODO / HINTS:
   * - Handle deleting the first node.
   * - Handle deleting a middle node.
   * - Handle deleting the last node.
   * - If the list becomes empty, set first and last to nullptr.
   ******************************************************************/
  void deleteItem(const type &item);

  /******************************************************************
   * deleteAt
   * PRE:
   *    location is intended to be between 0 and count - 1.
   * POST:
   *    If location is valid:
   *       - the node at that position is removed
   *       - true is returned
   *       - count decreases by 1
   *    If location is invalid:
   *       - the list is unchanged
   *       - false is returned
   *
   * TODO / HINTS:
   * - Handle location 0 separately.
   * - For other positions, move to the PREVIOUS node.
   * - Be sure to update last when deleting the final node.
   ******************************************************************/
  bool deleteAt(int location);

  /******************************************************************
   * indexOf
   * PRE:
   *    item is a valid value of type.
   * POST:
   *    Returns the index of the first occurrence of item.
   *    Returns -1 if item is not found.
   *
   * TODO:
   * - Traverse from first to last while keeping an index counter.
   ******************************************************************/
  int indexOf(const type &item) const;

  /******************************************************************
   * operator=
   * PRE:
   *    rhs is a valid linked list object.
   * POST:
   *    This list becomes a deep copy of rhs.
   *    Self-assignment is handled safely.
   *    Returns *this.
   *
   * TODO / HINTS:
   * - Check for self-assignment first.
   * - Reuse copyList().
   ******************************************************************/
  myLinkedList &operator=(const myLinkedList &rhs);

  /******************************************************************
   * operator==
   * PRE:
   *    rhs is a valid linked list object.
   * POST:
   *    Returns true only if both lists have the same length and
   *    the same values in the same order.
   *
   * TODO / HINTS:
   * - Check count first.
   * - Then traverse both lists together.
   ******************************************************************/
  bool operator==(const myLinkedList<type> &rhs) const;

  /******************************************************************
   * operator!=
   * PRE:
   *    rhs is a valid linked list object.
   * POST:
   *    Returns the opposite of operator==.
   ******************************************************************/
  bool operator!=(const myLinkedList<type> &rhs) const;

  /******************************************************************
   * setDataMembers
   * POST:
   *    count == 0
   *    first == nullptr
   *    last  == nullptr
   ******************************************************************/
  void setDataMembers();

  /******************************************************************
   * destroyList
   * POST:
   *    All nodes are deleted.
   *    first == nullptr
   *    last  == nullptr
   *    count == 0
   *
   * TODO / HINTS:
   * - Walk through the list one node at a time.
   * - Save the next pointer before deleting the current node.
   ******************************************************************/
  void destroyList() {
    linkNode<type> *currentNode = first;
    while (currentNode) {
      linkNode<type> *toBeDeleted = currentNode;
      currentNode = currentNode->nextElement;
      delete toBeDeleted;
    }
    first = nullptr;
    last = nullptr;
    count = 0;
  }
};

/***********************************************************************
 * operator<<
 * PRE:
 *    outStream is a valid output stream.
 * POST:
 *    Outputs the list using print(outStream), then returns outStream.
 *
 * TODO:
 * - Usually just call theList.print(outStream);
 ***********************************************************************/
template <class type>
std::ostream &operator<<(std::ostream &outStream,
                         const myLinkedList<type> &theList) {
  theList.print(outStream);
  return outStream;
}

// ================= IMPLEMENTED PARTS =================

template <class type> void myLinkedList<type>::setDataMembers() {
  first = nullptr;
  last = nullptr;
  count = 0;
}

template <class type> myLinkedList<type>::myLinkedList() { setDataMembers(); }

#endif /* MYLINKEDLIST_H_ */
