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

  // Precondition: None.
  // Postcondition: An empty list is created with items set to nullptr and
  // length set to 0.
  myList() {
    items = nullptr;
    length = 0;
  }

  // Precondition: The list object exists.
  // Postcondition: The dynamically allocated array is freed.
  ~myList() { delete[] items; }

  // Precondition: n >= 0 and theItem is a valid value of the list's type.
  // Postcondition: A list of size n is created with every element set to
  // theItem.
  myList(int n, const type &theItem) {
    length = n;
    items = new type[length];
    for (int i = 0; i < n; i++) {
      items[i] = theItem;
    }
  }

  // Precondition: n >= 0 and anArray points to a valid array of at least n
  // elements.
  // Postcondition: A list of size n is created containing a copy of the first
  // n elements of anArray.
  myList(int n, const type *anArray) {
    length = n;
    items = new type[length];
    for (int i = 0; i < length; i++) {
      items[i] = anArray[i];
    }
  }

  // Precondition: other is a valid myList object.
  // Postcondition: A new list is created as an independent deep copy of other;
  // the two lists share no memory.
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

  // Precondition: rhs is a valid myList object.
  // Postcondition: This list becomes an independent deep copy of rhs (old
  // memory is freed); returns a reference to this list. Self-assignment leaves
  // the list unchanged.
  myList<type> &operator=(const myList<type> &rhs) {
    if (this == &rhs) {
      return *this;
    }
    type *newItems = new type[rhs.length];
    for (int i = 0; i < rhs.length; i++) {
      newItems[i] = rhs.items[i];
    }
    delete[] items;
    items = newItems;
    length = rhs.length;

    return *this;
  }

  // Precondition: theItem is a valid value of the list's type.
  // Postcondition: theItem is appended to the end of this list, length
  // increases by 1, and a reference to this list is returned.
  myList<type> &operator+=(const type &theItem) {
    append(theItem);
    return *this;
  }

  // Precondition: rhs is a valid myList object.
  // Postcondition: A copy of every element of rhs is appended to the end of
  // this list, length increases by rhs.length, and a reference to this list is
  // returned.
  myList<type> &operator+=(const myList<type> &rhs) {
    type *newItems = new type[length + rhs.length];
    for (int i = 0; i < length + rhs.length; i++) {
      if (i < length) {
        newItems[i] = items[i];
      } else {
        newItems[i] = rhs.items[i - length];
      }
    }
    delete[] items;
    items = newItems;
    length += rhs.length;
    return *this;
  }

  // Precondition: outStream is a valid output stream and rhs is a valid myList
  // object.
  // Postcondition: The contents of rhs are written to outStream via print();
  // outStream is returned. The list is not modified.
  friend std::ostream &operator<<(std::ostream &outStream,
                                  const myList<type> &rhs) {
    rhs.print(outStream);
    return outStream;
  }

  // Precondition: theItem is a valid value of the list's type.
  // Postcondition: Returns a new list containing this list's elements followed
  // by theItem. This list is not modified.
  myList<type> operator+(const type &theItem) const {
    myList<type> itemCopy(*this);
    itemCopy.append(theItem);
    return itemCopy;
  }

  // Precondition: rhs is a valid myList object.
  // Postcondition: Returns a new list containing this list's elements followed
  // by rhs's elements. Neither operand is modified.
  myList<type> operator+(const myList<type> &rhs) const {
    myList<type> itemCopy(*this);
    itemCopy += rhs;
    return itemCopy;
  }

  /**********************************************************************
   * CORE MEMBER FUNCTIONS
   **********************************************************************/

  // Precondition: outStream is a valid output stream.
  // Postcondition: The list elements are written to outStream separated by
  // single spaces, with no trailing space. The list is not modified.
  void print(std::ostream &outStream) const {
    for (int i = 0; i < length; i++) {
      if (i > 0) {
        outStream << " ";
      }
      outStream << items[i];
    }
  }

  // Precondition: theItem is a valid value of the list's type.
  // Postcondition: Returns true if theItem is found in the list, false
  // otherwise. The list is not modified.
  bool isIn(const type &theItem) const {
    for (int i = 0; i < length; i++) {
      if (items[i] == theItem) {
        return true;
      }
    }
    return false;
  }

  // Precondition: theItem is a valid value of the list's type; location is the
  // target index.
  // Postcondition: If 0 <= location <= length, theItem is inserted at location,
  // existing elements shift right, and length increases by 1. Otherwise the
  // list is left unchanged.
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

  // Precondition: theItem is a valid value of the list's type.
  // Postcondition: theItem is added to the end of the list and length increases
  // by 1.
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

  // Precondition: The list's type supports the < operator.
  // Postcondition: The list elements are rearranged in ascending order; length
  // is unchanged.
  void sort() {
    int seek;
    int minCount;
    int minValue;
    for (seek = 0; seek < (length - 1); seek++) {
      minCount = seek;
      minValue = items[seek];
      for (int index = seek + 1; index < length; index++) {
        if (items[index] < minValue) {
          minValue = items[index];
          minCount = index;
        }
      }
      items[minCount] = items[seek];
      items[seek] = minValue;
    }
  }

  /**********************************************************************
   * ADDITIONAL METHODS (REQUIRED)
   **********************************************************************/

  // Precondition: None.
  // Postcondition: Returns the number of elements in the list. The list is not
  // modified.
  int getLength() const { return length; }

  // Precondition: None.
  // Postcondition: Returns true if the list has no elements, false otherwise.
  // The list is not modified.
  bool isEmpty() const { return length == 0; }

  // Precondition: location is the index of the element to remove.
  // Postcondition: If 0 <= location < length, the element at location is
  // removed, length decreases by 1, and returns true. Otherwise the list is
  // left unchanged and returns false.
  bool removeAt(int location) {
    if (location < 0 || location >= length) {
      return false;
    }

    type *newItems = new type[length - 1];
    for (int i = 0; i < length - 1; i++) {
      if (i < location) {
        newItems[i] = items[i];
      } else {
        newItems[i] = items[i + 1];
      }
    }
    delete[] items;
    items = newItems;
    length--;
    return true;
  }

  // Precondition: None.
  // Postcondition: All elements are removed, the array is freed, items is set
  // to nullptr, and length is reset to 0.
  void clear() {
    delete[] items;
    items = nullptr;
    length = 0;
  }

  // Precondition: theItem is a valid value of the list's type.
  // Postcondition: Returns the index of the first occurrence of theItem, or -1
  // if it is not found. The list is not modified.
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
