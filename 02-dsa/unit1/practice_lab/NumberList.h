#ifndef NUMBERLIST_H
#define NUMBERLIST_H
#include "NumberListNode.h"
#include <iostream>
#include <string>

// Base class for a double-linked list of NumerListNodes
class NumberList {
protected:
  NumberListNode *head;
  NumberListNode *tail;

public:
  NumberList() {
    head = nullptr;
    tail = nullptr;
  }

  virtual ~NumberList() {}

  NumberListNode *GetHead() const { return head; }

  // Prints this list's contents in order from head to tail
  void Print(std::ostream &output = std::cout, std::string separator = ", ",
             std::string prefix = "", std::string suffix = "") const {

    // Print prefix first
    output << prefix;

    // Start at the list's head
    NumberListNode *node = head;

    // First node's data is printed without accompanying separator
    if (node) {
      output << node->GetData();
      node = node->GetNext();
    } else {
      // Special case for empty list
      output << "(empty)";
    }

    // Remaining nodes are printed with separator before
    while (node) {
      output << separator << node->GetData();
      node = node->GetNext();
    }

    // Suffix is printed last
    output << suffix;
  }
};

#endif
