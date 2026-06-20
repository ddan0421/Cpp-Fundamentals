#ifndef NUMBERLISTNODE_H
#define NUMBERLISTNODE_H

class NumberListNode {
protected:
  double data;
  NumberListNode *next;
  NumberListNode *previous;

public:
  // Constructs this node with the specified numerical data value. The next
  // and previous pointers are each assigned nullptr.
  NumberListNode(double initialData) {
    data = initialData;
    next = nullptr;
    previous = nullptr;
  }

  // Constructs this node with the specified numerical data value, next
  // pointer, and previous pointer.
  NumberListNode(double initialData, NumberListNode *nextNode,
                 NumberListNode *previousNode) {
    data = initialData;
    next = nextNode;
    previous = previousNode;
  }

  virtual ~NumberListNode() {}

  // Returns this node's data.
  virtual double GetData() { return data; }

  // Sets this node's data.
  virtual void SetData(double newData) { data = newData; }

  // Gets this node's next pointer.
  virtual NumberListNode *GetNext() { return next; }

  // Sets this node's next pointer.
  virtual void SetNext(NumberListNode *newNext) { next = newNext; }

  // Gets this node's previous pointer.
  virtual NumberListNode *GetPrevious() { return previous; }

  // Sets this node's previous pointer.
  virtual void SetPrevious(NumberListNode *newPrevious) {
    previous = newPrevious;
  }
};

#endif
