#ifndef MYLIST_HPP
#define MYLIST_HPP

#include <iostream>

/*************************************************************************
 *  Name: Dan Dan                                CSC 240
 *  Date: 06/22/2026                             Lab 2
 *************************************************************************
 *  Statement:
 *  This program implements a template class that represents a dynamic
 *  array-based list. The class supports insertion, appending, searching,
 *  sorting, clearing, and list manipulation operations.
 *
 *  Specifications:
 *  The class uses a dynamically allocated array and follows an exact-fit
 *  resizing model. Memory must be managed manually using new and delete[].
 *  All member function implementations for this template class must be
 *  completed in this header file.
 *
 *  Input -
 *  Values passed into constructors and member functions by the test driver.
 *
 *  Output -
 *  Results printed to the console showing list behavior and operations.
 *************************************************************************/

template <class type> class myList {
  // ============================================================
  // DESIGN NOTE (IMPORTANT)
  // ============================================================
  // This class uses an "exact-fit" dynamic array model:
  //
  // - The array size ALWAYS equals the number of elements (length)
  // - There is NO capacity variable
  // - Every insert/append/remove requires:
  //      1. Allocate a new array
  //      2. Copy elements
  //      3. Delete old array
  //      4. Update length
  //
  // This is intentional to reinforce dynamic memory concepts.
  // ============================================================

private:
  type *items; // pointer to dynamic array
  int length;  // number of elements

public:
  /**********************************************************************
   * CONSTRUCTORS / DESTRUCTOR
   **********************************************************************/

  // Default constructor
  // Creates an empty list
  myList() {
    items = nullptr;
    length = 0;
  }

  // Destructor
  // Frees dynamically allocated memory
  ~myList() { delete[] items; }

  // Fill constructor
  // Creates a list of size n, filled with value theItem
  myList(int n, const type &theItem) {
    length = n;
    items = new type[length];
    for (int i = 0; i < n; i++) {
      items[i] = theItem;
    }
  }

  // Array constructor
  // Creates a list from an existing array
  myList(int n, const type *anArray) {
    length = n;
    items = new type[length];
    for (int i = 0; i < length; i++) {
      items[i] = anArray[i];
    }
  }

  // Copy constructor
  // Creates a deep copy of another list
  //
  // Teaching Note:
  // - You MUST allocate new memory
  // - Copy values one-by-one
  // - DO NOT copy the pointer directly
  myList(const myList<type> &other) {
    length = other.length;
    items = new type[other.length];
    for (int i = 0; i < other.length; i++) {
      items[i] = other.items[i];
    }
  }

  /**********************************************************************
   * OVERLOADED OPERATORS
   **********************************************************************/

  // Assignment operator
  //
  // Steps:
  // 1. Check self-assignment
  // 2. delete[] old memory
  // 3. allocate new memory
  // 4. copy elements
  myList<type> &operator=(const myList<type> &rhs);

  // Add one item to end (reuse append logic)
  // Return *this to support chaining
  myList<type> &operator+=(const type &theItem);

  // Append another list
  //
  // Steps:
  // - allocate new array of size length + rhs.length
  // - copy current list
  // - copy rhs
  // - return *this to support chaining
  myList<type> &operator+=(const myList<type> &rhs);

  // Output operator
  //
  // IMPORTANT:
  // This uses print(), so print() MUST work first
  friend std::ostream &operator<<(std::ostream &outStream,
                                  const myList<type> &rhs) {
    rhs.print(outStream);
    return outStream;
  }

  // Return new list with one added item
  //
  // DO NOT modify current object
  myList<type> operator+(const type &theItem) const;

  // Return new list combining two lists
  //
  // Similar to += but returns NEW object
  myList<type> operator+(const myList<type> &rhs) const;

  /**********************************************************************
   * CORE MEMBER FUNCTIONS
   **********************************************************************/

  // Print list contents
  //
  // Also used by operator<<
  void print(std::ostream &outStream) const {
    for (int i = 0; i < length; i++) {
      if (i > 0) {
        outStream << " ";
      }
      outStream << items[i];
    }
  }

  // Search for item
  //
  // Linear search
  bool isIn(const type &theItem) const {
    for (int i = 0; i < length; i++) {
      if (items[i] == theItem) {
        return true;
      }
    }
    return false;
  }

  // Insert at position
  //
  // Steps:
  // 1. allocate new array (length + 1)
  // 2. copy before index
  // 3. insert item
  // 4. shift remaining elements
  // 5. delete old array
  //
  // NOTE:
  // If location is invalid, handle safely.
  // Do NOT access out-of-bounds memory.
  void insert(const type &theItem, int location) {
    if (location < 0 || location > length) {
      return;
    }
    type *newItems = new type[length + 1];
    for (int i = 0; i < length + 1; i++) {
      if (i == location) {
        newItems[i] = theItem;
      } else if (i < location) {
        newItems[i] = items[i];
      } else {
        newItems[i] = items[i - 1];
      }
    }
    delete[] items;
    items = newItems;
    length++;
  }

  // Append to end
  //
  // Steps:
  // 1. allocate new array (length + 1)
  // 2. copy elements
  // 3. add new item
  // 4. delete old array
  void append(const type &theItem) {
    type *newItems = new type[length + 1];
    for (int i = 0; i < length + 1; i++) {
      if (i < length) {
        newItems[i] = items[i];
      } else {
        newItems[i] = theItem;
      }
    }
    delete[] items;
    items = newItems;
    length++;
  }

  // Sort list
  //
  // Any correct sorting algorithm is acceptable
  void sort();

  /**********************************************************************
   * ADDITIONAL METHODS (REQUIRED)
   **********************************************************************/

  // Return number of elements
  int getLength() const { return length; }

  // Check if list is empty
  bool isEmpty() const { return length == 0; }

  // Remove element at index
  //
  // Steps:
  // 1. allocate new array (length - 1)
  // 2. copy all except removed element
  // 3. delete old array
  //
  // NOTE:
  // If location is invalid, handle safely.
  bool removeAt(int location);

  // Clear entire list
  //
  // Should reset to empty state
  void clear();

  // Find index of item
  //
  // Return -1 if not found
  int find(const type &theItem) const {
    for (int i = 0; i < length; i++) {
      if (items[i] == theItem) {
        return i;
      }
    }
    return -1;
  }
};

#endif
