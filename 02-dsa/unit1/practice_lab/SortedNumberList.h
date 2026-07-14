#ifndef SORTEDNUMBERLIST_H
#define SORTEDNUMBERLIST_H
#include "NumberList.h"

class SortedNumberList : public NumberList {
private:
  // Optional: Add any desired private functions here
  void PrependNode(NumberListNode *newNode) {
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else {
      newNode->SetNext(head);
      head->SetPrevious(newNode);
      head = newNode;
    }
  }

  void InsertNodeAfter(NumberListNode *currentNode, NumberListNode *newNode) {
    if (head == nullptr) {
      head = newNode;
      tail = newNode;
    } else if (currentNode == tail) {
      tail->SetNext(newNode);
      newNode->SetPrevious(tail);
      tail = newNode;
    } else {
      NumberListNode *successor = currentNode->GetNext();
      newNode->SetNext(successor);
      newNode->SetPrevious(currentNode);
      currentNode->SetNext(newNode);
      successor->SetPrevious(newNode);
    }
  }

  void MoveAfter(NumberListNode *nodeToMove, NumberListNode *nodeBefore) {
    NumberListNode *successor = nodeToMove->GetNext();
    NumberListNode *predecessor = nodeToMove->GetPrevious();

    if (successor) {
      successor->SetPrevious(predecessor);
    }
    if (predecessor) {
      predecessor->SetNext(successor);
    }
    if (nodeToMove == head) {
      head = successor;
    }
    if (nodeToMove == tail) {
      tail = predecessor;
    }

    nodeToMove->SetNext(nullptr);
    nodeToMove->SetPrevious(nullptr);

    // If nodeBefore is non-null, use InsertNodeAfter(), otherwise use
    // PrependNode()
    if (nodeBefore) {
      InsertNodeAfter(nodeBefore, nodeToMove);
    } else {
      PrependNode(nodeToMove);
    }
  }

  NumberListNode *Search(double dataValue) const {
    NumberListNode *currentNode = head;
    while (currentNode) {
      if (currentNode->GetData() == dataValue) {
        return currentNode;
      }
      currentNode = currentNode->GetNext();
    }

    return nullptr;
  }

  void RemoveNode(NumberListNode *currentNode) {
    NumberListNode *successor = currentNode->GetNext();
    NumberListNode *predecessor = currentNode->GetPrevious();

    if (successor) {
      successor->SetPrevious(predecessor);
    }
    if (predecessor) {
      predecessor->SetNext(successor);
    }

    if (currentNode == head) {
      head = successor;
    }
    if (currentNode == tail) {
      tail = predecessor;
    }

    delete currentNode;
  }

public:
  SortedNumberList() {
    head = nullptr;
    tail = nullptr;
  }

  // Inserts the number into the list in the correct position such that the
  // list remains sorted in ascending order.
  void Insert(double number) {
    // TODO: Type your code here

    PrependNode(new NumberListNode(number));

    NumberListNode *currentNode = head->GetNext();
    while (currentNode) {
      NumberListNode *nextNode = currentNode->GetNext();
      NumberListNode *searchNode = currentNode->GetPrevious();

      while (searchNode && searchNode->GetData() > currentNode->GetData()) {
        searchNode = searchNode->GetPrevious();
      }

      // Move currentNode after searchNode
      MoveAfter(currentNode, searchNode);

      // Advance to next node
      currentNode = nextNode;
    }
  }

  // Removes the node with the specified number value from the list. Returns
  // true if the node is found and removed, false otherwise.
  bool Remove(double number) {
    // TODO: Type your code here
    NumberListNode *target = Search(number);
    if (target != nullptr) {
      RemoveNode(target);
      return true;
    }
    return false;
  }
};

#endif
