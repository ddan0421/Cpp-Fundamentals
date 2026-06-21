# CSC 240 — Unit Summary (Stacks, Queues, and Lists Plus)

**Chapters Covered:**
- Chapter 5: ADTs Stack and Queue
- Chapter 6: Lists Plus

---

## Big Picture

Chapter 5 introduces two new ADTs with **restricted access**: Stack (LIFO) and Queue (FIFO). Chapter 6 returns to lists and adds the C++ tools (templates, copy constructors, operator overloading, virtual functions, iterators) plus richer list variants (circular, doubly linked, header/trailer, array-of-records).

| Chapter | ADTs / Concepts | Implementations explored |
|---------|----------------|--------------------------|
| **5** | Stack, Queue, Counted Queue | Static array, dynamic array, linked list, circular linked |
| **6** | Templates, circular & doubly linked lists, copying, polymorphism, iterators | Singly, circular, doubly, doubly-circular, array-of-records |

---

# Chapter 5: ADTs Stack and Queue

## Part A — Stack

### 1. Stack Logical Level

- **Stack**: an ADT where items are added/removed *only at the top*.
- Access pattern: **LIFO** (Last In, First Out).
- Items are homogeneous (like lists).
- Logically unbounded; some implementations may be bounded.

```
   Top --> [ D ]   <-- last pushed, first popped
           [ C ]
           [ B ]
           [ A ]   <-- first pushed, last popped
```

### 2. Stack Operations

| Operation | Description |
|-----------|-------------|
| **`Push(item)`** | Add `item` to the top |
| **`Pop()`** | Remove the top item |
| **`Top()`** | Return (but do not remove) the top item |
| **`IsEmpty()`** | `true` if no items |
| **`IsFull()`** | `true` if no room (implementation dependent) |

> If `Pop`/`Top` is called on an empty stack ⇒ **stack underflow**. If `Push` is called on a full stack ⇒ **stack overflow**. Both should throw exceptions.

### 3. Stack Applications

- Tracking function calls (the **call stack**).
- Syntax analysis (matching parentheses/braces in compilers).
- Traversing trees and graphs (DFS).
- Some languages are entirely stack-based (e.g., **Forth**, PostScript).
- Reversing a sequence — push everything, then pop everything.

---

### 4. Array-Based Stack

#### Visual layout

```
items:  [ A ][ B ][ C ][ D ][   ][   ][   ]
          0    1    2    3    4    5    6
top = 3                                 MAX_ITEMS = 7
```

- `top` is the **index of the current top element** (−1 means empty).
- `Push` increments `top` then writes; `Pop` just decrements `top`.

#### Class skeleton + constructor

```cpp
// StackType.h  (array-based)
class FullStack  {};   // exception class
class EmptyStack {};

const int MAX_ITEMS = 100;
typedef int ItemType;

class StackType {
public:
    StackType();                  // sets top = -1
    bool IsFull()  const;
    bool IsEmpty() const;
    void Push(ItemType item);
    void Pop();
    ItemType Top() const;
private:
    int      top;
    ItemType items[MAX_ITEMS];
};

StackType::StackType() { top = -1; }

bool StackType::IsFull()  const { return top == MAX_ITEMS - 1; }
bool StackType::IsEmpty() const { return top == -1; }
```

#### Push / Pop / Top — all O(1)

```cpp
void StackType::Push(ItemType newItem) {
    if (IsFull()) throw FullStack();
    top++;
    items[top] = newItem;
}

void StackType::Pop() {
    if (IsEmpty()) throw EmptyStack();
    top--;                            // value is now "garbage", but unreachable
}

ItemType StackType::Top() const {
    if (IsEmpty()) throw EmptyStack();
    return items[top];
}
```

#### Push / Pop trace

```
Initial:  top = -1     items = [   ][   ][   ][   ][   ]
Push A:   top =  0     items = [ A ][   ][   ][   ][   ]
Push B:   top =  1     items = [ A ][ B ][   ][   ][   ]
Push C:   top =  2     items = [ A ][ B ][ C ][   ][   ]
Pop  :    top =  1     items = [ A ][ B ][ C ][   ][   ]   // C still in memory, but inaccessible
Top  :    returns B
```

---

### 5. Dynamic-Array-Based Stack

Identical idea but the array lives on the heap so the client picks the max size at run time.

```cpp
class StackType {
public:
    StackType();              // default capacity 500
    StackType(int max);       // parameterized
    ~StackType();             // delete[] items
    // ... same interface ...
private:
    int       top;
    int       maxStack;
    ItemType* items;
};

StackType::StackType()        { top = -1; maxStack = 500;  items = new ItemType[500]; }
StackType::StackType(int max) { top = -1; maxStack = max;  items = new ItemType[max]; }
StackType::~StackType()       { delete [] items; }
```

> **Rule of thumb**: any class that holds a heap pointer needs a destructor. (Later, also a copy constructor and `operator=` — see Ch. 6, "Rule of the Big 3.")

#### Zybooks example (Array-based stack implementation)

Supports both a **bounded** stack (fixed `maxLength`) and an **unbounded** stack that doubles its allocation when full (`Resize()`). `Push` returns `bool` — `false` when the bounded stack hits its cap.

**`StackADT.h`**

```cpp
#ifndef STACKADT_H
#define STACKADT_H

#include <iostream>

class StackADT {
public:
   // Member functions that may change the stack
   virtual bool Push(int item) = 0;
   virtual int Pop() = 0;

   // Member functions that do not change the stack
   virtual int GetLength() const = 0;
   virtual bool IsEmpty() const = 0;
   virtual int Peek() const = 0;
   virtual void Print(std::ostream& printStream = std::cout,
      const std::string& separator = ", ") const = 0;
};

#endif
```

**`ArrayStack.h`**

```cpp
#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <iostream>
#include "StackADT.h"

class ArrayStack : public StackADT {
private:
   int allocationSize;
   int* array;
   int length;
   int maxLength;

   void Resize() {
      // Allocate new array and copy existing items
      int newSize = allocationSize * 2;
      int* newArray = new int[newSize];
      for (int i = 0; i < length; i++) {
         newArray[i] = array[i];
      }

      // Free old array and assign new
      delete[] array;
      array = newArray;
      allocationSize = newSize;
   }

public:
   ArrayStack(int optionalMaxLength = -1) {
      allocationSize = 1;
      array = new int[allocationSize];
      length = 0;
      maxLength = optionalMaxLength;
   }
```

**One constructor, two modes.** The default argument `= -1` lets a single `ArrayStack` class behave as either bounded or unbounded, depending on how you construct it:

| How you call it | What `maxLength` becomes | Behavior |
|----------------|--------------------------|----------|
| `ArrayStack bounded(4);` | `4` | **Bounded** — `Push` returns `false` once `length` reaches 4 |
| `ArrayStack unbounded;` | `-1` (the default) | **Unbounded** — no fixed cap; `Resize()` grows the array as needed |

**Why `-1` works as "no limit":** `Push` rejects new items with `if (length == maxLength) return false;`. Since `length` is always `>= 0`, it can never equal `-1`. So when you omit the argument, that check never triggers and the stack keeps growing via `Resize()`.

```cpp
   virtual ~ArrayStack() {
      delete[] array;
   }

   virtual int GetLength() const override {
      return length;
   }

   virtual int GetMaxLength() const {
      return maxLength;
   }

   virtual bool IsEmpty() const override {
      return 0 == length;
   }

   virtual int Peek() const override {
      return array[length - 1];
   }

   virtual int Pop() override {
      length--;
      return array[length];
   }
```

**`Pop()` precondition:** This implementation always decrements `length` and returns `array[length]` — it does not check whether the stack is empty first. If `Pop()` is called when `length` is 0, `length` becomes `-1` and `array[-1]` is an out-of-bounds access. The caller must ensure the stack has at least one item (e.g. check `GetLength() > 0` or `!IsEmpty()`) before calling `Pop()`.

```cpp
   virtual void Print(std::ostream& printStream = std::cout,
      const std::string& separator = ", ") const override {
      if (length > 0) {
         // Print first item with no separator
         printStream << array[length - 1];
      }

      // Print remaining items, each preceded by the separator
      for (int i = length - 2; i >= 0; i--) {
         printStream << separator << array[i];
      }
   }

   virtual bool Push(int item) override {
      // If at max length, return false
      if (length == maxLength) {
         return false;
      }

      // Resize if length equals allocation size
      if (length == allocationSize) {
         Resize();
      }

      // Push the item and return true
      array[length] = item;
      length++;
      return true;
   }
};

#endif
```

**`ArrayBasedStacks.cpp`**

```cpp
#include <iostream>
#include "ArrayStack.h"
using namespace std;

int main(int argc, char* argv[]) {
   // Make two stacks, one bounded to 4 items and the other unbounded
   ArrayStack boundedStack(4);
   ArrayStack unboundedStack;

   // Push 8 items to each
   cout << "Pushing values 1 through 8 to each stack" << endl;
   for (int i = 1; i <= 8; i++) {
      boundedStack.Push(i);
      unboundedStack.Push(i);
   }

   // Pop two items off each stack
   cout << "Popping twice" << endl;
   for (int i = 0; i < 2; i++) {
      boundedStack.Pop();
      unboundedStack.Pop();
   }

   // Push 4 more items onto each stack
   cout << "Pushing values to each stack: 10, 20, 30 and 40" << endl;
   for (int i = 10; i <= 40; i += 10) {
      boundedStack.Push(i);
      unboundedStack.Push(i);
   }

   // Display contents of each stack
   cout << "Bounded stack (maxLength=" << boundedStack.GetMaxLength();
   cout << ") contents:" << endl;
   while (boundedStack.GetLength() > 0) {
      cout << "  " << boundedStack.Pop() << endl;
   }
   cout << "Unbounded stack contents:" << endl;
   while (unboundedStack.GetLength() > 0) {
      cout << "  " << unboundedStack.Pop() << endl;
   }

   return 0;
}
```

---

### 6. Linked-List-Based Stack

- A linked list naturally models a stack — *push at the head, pop from the head*. Both are O(1).
- No fixed capacity (bounded only by the heap).

#### Node + class layout

```cpp
struct NodeType {
    ItemType info;
    NodeType* next;
};

class StackType {
public:
    StackType();
    ~StackType();
    bool IsFull()  const;
    bool IsEmpty() const;
    void Push(ItemType item);
    void Pop();
    ItemType Top() const;
private:
    NodeType* topPtr;
};

StackType::StackType() { topPtr = NULL; }
```

#### Push (textbook, page 643)

```cpp
void StackType::Push(ItemType newItem) {
    if (IsFull()) throw FullStack();
    NodeType* location = new NodeType;
    location->info = newItem;
    location->next = topPtr;     // new node points to old top
    topPtr         = location;   // top now points to new node
}
```

```
Before:   topPtr -> [B|*] -> [A|NULL]
Push(C):  topPtr -> [C|*] -> [B|*] -> [A|NULL]
```

**What is `topPtr`?** It's the stack's *single data member* — a pointer that holds the **memory address of the top node** (the head of the chain). It is *not* a node itself; it just "points at" the most-recently-pushed node. When the stack is empty, `topPtr == NULL`. Everything below the top is reached by following each node's `next` link, so `topPtr` is the one and only handle the object keeps to the entire list.

**Why `location->next = topPtr` matters:** `location` is the brand-new node we just allocated. Before we touch `topPtr`, it still points at the *old* top. This line makes the new node's `next` link point to that old top — i.e., it **hooks the new node onto the front of the existing chain** so nothing below it is lost.

```
Step 1: location->next = topPtr     // new node grabs the old top
   topPtr ------> [B|*] -> [A|NULL]
   location --> [C|*] ----^         (C->next now points to B)

Step 2: topPtr = location           // top officially moves up to C
   topPtr --> [C|*] -> [B|*] -> [A|NULL]
```

> Order is critical: link the new node to the old top **first**, *then* move `topPtr`. If you reassigned `topPtr = location` first, you'd lose the address of the old top (a memory leak / orphaned chain) before `location->next` could ever capture it.

#### Pop (textbook, page 640) — the "save, advance, delete" pattern

```cpp
void StackType::Pop() {
    if (IsEmpty()) throw EmptyStack();
    NodeType* tempPtr = topPtr;        // remember the old top
    topPtr            = topPtr->next;  // advance
    delete tempPtr;                    // free the old node
}
```

```
Before:   topPtr -> [C|*] -> [B|*] -> [A|NULL]
                    ^
                    tempPtr
Step 1:   topPtr -> [B|*] -> [A|NULL]      (tempPtr still -> [C|*])
Step 2:   delete tempPtr   => C node freed
```

For a one-element stack the same code works: `topPtr->next` is `NULL`, which is exactly the empty-stack state.

#### Top, IsFull, IsEmpty, destructor

```cpp
ItemType StackType::Top() const {
    if (IsEmpty()) throw EmptyStack();
    return topPtr->info;
}

bool StackType::IsEmpty() const { return topPtr == NULL; }

bool StackType::IsFull() const {                       // try to allocate one node
    NodeType* location;
    try   { location = new NodeType; delete location; return false; }
    catch (std::bad_alloc) { return true; }
}
```

Inside the `try` block, the code performs a clever test:

- **`location = new NodeType;`** — It literally attempts to allocate a brand-new node from the system's heap memory.
- **`delete location;`** — If that allocation succeeds, it means the stack is **not** full (there is still memory available). Because we don't actually need this node right now, we immediately delete it to avoid a memory leak.
- **`return false;`** — It returns `false`, telling the program: "Nope, we aren't full yet. Keep pushing items!"

If `new` fails, the runtime throws `std::bad_alloc`, the `catch` runs, and `IsFull()` returns `true`.

```cpp
StackType::~StackType() {                              // walk the chain, free each node
    NodeType* tempPtr;
    while (topPtr != NULL) {
        tempPtr = topPtr;
        topPtr  = topPtr->next;
        delete tempPtr;
    }
}
```

#### Zybooks example (Singly-linked-based stack implementation)

**`StackADT.h`**

```cpp
#ifndef STACKADT_H
#define STACKADT_H

#include <iostream>

class StackADT {
public:
   // Member functions that may change the stack
   virtual void Push(int item) = 0;
   virtual int Pop() = 0;

   // Member functions that do not change the stack
   virtual int GetLength() const = 0;
   virtual bool IsEmpty() const = 0;
   virtual int Peek() const = 0;
   virtual void Print(std::ostream& printStream = std::cout,
      const std::string& separator = ", ") const = 0;
};

#endif
```

**`Stack.h`**

```cpp
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "StackADT.h"

// Node to store an item in a linked-list-based stack
class StackNode {
public:
   int data;
   StackNode* next;

   StackNode(int dataValue, StackNode* nextNode) {
      data = dataValue;
      next = nextNode;
   }
};

// Linked-list-based stack
class Stack : public StackADT {
private:
   StackNode* top;

public:
   Stack() {
      top = nullptr;
   }

   virtual ~Stack() {
      while (top) {
         StackNode* nodeToDelete = top;
         top = top->next;
         delete nodeToDelete;
      }
   }

   virtual int GetLength() const override {
      StackNode* node = top;
      int count = 0;
      while (node) {
         count++;
         node = node->next;
      }
      return count;
   }

   virtual bool IsEmpty() const override {
      return top == nullptr;
   }

   virtual int Peek() const override {
      return top->data;
   }

   virtual void Push(int newData) override {
      top = new StackNode(newData, top);
   }

   virtual int Pop() override {
      // Copy top node's data
      StackNode* poppedNode = top;
      int poppedItem = top->data;

      // Remove top node
      top = top->next;

      // Delete former top node
      delete poppedNode;

      // Return the popped item
      return poppedItem;
   }

   // Prints stack items from top to bottom, with the separator string between
   // each pair of items
   virtual void Print(std::ostream& printStream = std::cout,
      const std::string& separator = ", ") const override {
      StackNode* node = top;

      if (node) {
         // Print first item with no separator
         printStream << node->data;
         node = node->next;
      }

      // Print remaining items, each preceded by the separator
      while (node) {
         printStream << separator << node->data;
         node = node->next;
      }
   }
};

#endif
```

**`main.cpp`**

```cpp
#include <iostream>
#include "Stack.h"
using namespace std;

int main() {
   int numbers[] = { 76, 81, 91, 34, 62, 88, 77, 21, 18 };

   // Initialize a new Stack and add numbers
   Stack numStack;
   for (int number : numbers) {
       numStack.Push(number);
   }

   // Show the stack before any pop operations occur
   cout << "Stack: ";
   numStack.Print();
   cout << endl;

   // Pop until stack is empty, printing each popped item and remaining stack
   while (!numStack.IsEmpty()) {
      cout << "Popped " << numStack.Pop() << endl;
      cout << "Stack: ";
      numStack.Print();
      cout << endl;
   }

   return 0;
}
```

---

### 7. Comparing Stack Implementations (Table 5.1)

| Operation | Static Array | Dynamic Array | Linked |
|-----------|-------------|---------------|--------|
| Constructor | O(1) | O(1) | O(1) |
| `IsFull` | O(1) | O(1) | O(1) |
| `IsEmpty` | O(1) | O(1) | O(1) |
| **`Push`** | O(1) | O(1) | O(1) |
| **`Pop`** | O(1) | O(1) | O(1) |
| **`Top`** | O(1) | O(1) | O(1) |
| Destructor | — | O(1) | **O(N)** |

**Trade-off**: arrays are smaller, faster (no `new`/`delete` per op), simpler — pick when you know the max. Linked is more memory-efficient when the size varies a lot and avoids overflow.

---

## Part B — Queue

### 8. Queue Logical Level

- **Queue**: ADT where elements are added at the **rear** and removed from the **front**.
- Access pattern: **FIFO** (First In, First Out).
- Real-world example: a line at a cash register.

```
        front                                     rear
          v                                         v
        [ A ][ B ][ C ][ D ]
         ^                                          ^
     dequeue here                              enqueue here
```

### 9. Queue Operations

| Operation | Description |
|-----------|-------------|
| **`Enqueue(item)`** | Add `item` to the rear |
| **`Dequeue(item)`** | Remove the front item and return it |
| **`IsEmpty()`** | `true` if empty |
| **`IsFull()`** | `true` if no room |
| **`MakeEmpty()`** | Remove all items |

### 10. Queue Applications

- OS scheduling jobs on the processor (round-robin).
- Buffering data between processes / over network sockets.
- Print spooler queues.
- Simulation modeling (bank teller lines, call centers).

---

### 11. Fixed-Front Array Queue (the *naive* design)

Front is glued to index 0. Enqueue is cheap; Dequeue shifts every element left by one.

```
Initial:        [ A ][ B ][ C ][ D ][   ]    rear=3
Enqueue(E):     [ A ][ B ][ C ][ D ][ E ]    rear=4
Dequeue (A):    [ B ][ C ][ D ][ E ][   ]    rear=3   <-- everyone shifted left!
```

- `Enqueue`: O(1).
- `Dequeue`: **O(N)** because every remaining element shifts up — bad for large queues.

---

### 12. Floating Circular Array Queue (the *good* design)

Both `front` and `rear` move. When either pointer would fall off the end of the array, it wraps back to index 0 using modular arithmetic:

```
nextIndex = (currentIndex + 1) % maxQue;
```

**The "next index calculator."** Think of this formula as a safe way to advance a pointer by one slot. You take the pointer's current index, add 1 to move forward, then apply `% maxQue` so the result always stays in `[0, maxQue − 1]`. If adding 1 would go past the last slot, the modulo wraps it back to 0.

The same formula drives **both** pointers — only the meaning of the move differs:

**For `rear` (Enqueue — adding data)**

| Step | What happens |
|------|----------------|
| 1 | You want to enqueue a new item |
| 2 | Run `newRear = (rear + 1) % maxQue` |
| 3 | Move `rear` to `newRear` |
| 4 | Store the new item in `items[newRear]` |

**For `front` (Dequeue — removing data)**

| Step | What happens |
|------|----------------|
| 1 | You want to dequeue an item |
| 2 | Run `newFront = (front + 1) % maxQue` |
| 3 | Move `front` to `newFront` |
| 4 | The item at `items[newFront]` is the one that leaves the queue |

> Dale's design: `front` points to the cell **before** the first element, so the item removed is always at the *new* front index after the formula runs.

**Why `front = 5` before the first dequeue:** Dale intentionally places `front` one slot *before* the first item (A at index 0). That way the **same** advance formula used for every dequeue — `front = (front + 1) % maxQue` — lands on the item to remove. First dequeue: `(5+1) % 6 = 0` → read `items[0]` (A). After that, `front = 0` sits before B at index 1, and the next dequeue does `(0+1) % 6 = 1` → read B. This also keeps empty/full simple: both pointers start at 5, and `front == rear` means empty.

```
Where the DATA is:     index 0 = A (first),  index 4 = E (last)   ← rear = 4
Where the POINTERS are: front = 5 (before A), rear = 4 (at E)
```

#### Visual: wrap-around in action

```
maxQue = 6

After Enqueue A,B,C,D,E:
  current:  front=5, rear=4
  index:    0   1   2   3   4   5
           [A] [B] [C] [D] [E] [ ]
            ^                          first item (A) is here at index 0
                                 ^front  front PTR is one slot before A (index 5)
                            ^rear       rear PTR is at E (index 4)

Dequeue A:
  formula:  new_front = (5+1) % 6 = 0
  current:  front=5, rear=4  →  new: front=0, rear=4
  index:    0   1   2   3   4   5
           [A] [B] [C] [D] [E] [ ]
            ^front (item A removed from here)
                            ^rear

Dequeue B:
  formula:  new_front = (0+1) % 6 = 1
  current:  front=0, rear=4  →  new: front=1, rear=4
  index:    0   1   2   3   4   5
           [ ] [B] [C] [D] [E] [ ]
                ^front (item B removed from here)
                            ^rear

Enqueue F:
  formula:  new_rear = (4+1) % 6 = 5
  current:  front=1, rear=4  →  new: front=1, rear=5
  index:    0   1   2   3   4   5
           [ ] [ ] [C] [D] [E] [F]
                ^front          ^rear (F placed here)

Enqueue G — WRAPS!:
  formula:  new_rear = (5+1) % 6 = 0   ← modulo sends us back to index 0
  current:  front=1, rear=5  →  new: front=1, rear=0
  index:    0   1   2   3   4   5
           [G] [ ] [C] [D] [E] [F]
            ^rear ^front (G placed here; rear jumped from 5 → 0)
```

#### Distinguishing empty from full

The trick used by Dale: reserve one slot. `front` points to the cell **before** the actual first element.

- **Empty**: `front == rear`
- **Full** : `(rear + 1) % maxQue == front`

That's why the constructor allocates `max + 1` slots.

#### Full implementation (textbook page 673)

```cpp
class FullQueue  {};
class EmptyQueue {};

class QueType {
public:
    QueType(int max);
    QueType();                          // default 500
    ~QueType();
    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull()  const;
    void Enqueue(ItemType newItem);
    void Dequeue(ItemType& item);
private:
    int       front;
    int       rear;
    ItemType* items;
    int       maxQue;
};

QueType::QueType(int max) {
    maxQue = max + 1;                   // one extra slot for the empty/full trick
    front  = maxQue - 1;
    rear   = maxQue - 1;
    items  = new ItemType[maxQue];
}

QueType::~QueType()       { delete [] items; }
void QueType::MakeEmpty() { front = maxQue - 1; rear = maxQue - 1; }
bool QueType::IsEmpty() const { return rear == front; }
bool QueType::IsFull()  const { return (rear + 1) % maxQue == front; }

void QueType::Enqueue(ItemType newItem) {
    if (IsFull()) throw FullQueue();
    rear         = (rear + 1) % maxQue;
    items[rear]  = newItem;
}

void QueType::Dequeue(ItemType& item) {
    if (IsEmpty()) throw EmptyQueue();
    front = (front + 1) % maxQue;
    item  = items[front];
}
```

All operations are now **O(1)**.

#### Zybooks example (Array-based queue implementation)

Supports **bounded** (`maxLength` set) and **unbounded** (`maxLength = -1`) queues. Unlike Dale's design above, `frontIndex` points **at** the first item (not one slot before it). A separate `length` counter tracks how many items are in the queue. Wrap-around uses `(frontIndex + offset) % allocationSize`; `Resize()` compacts items and resets `frontIndex` to 0.

**`QueueADT.h`**

```cpp
#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <iostream>

class QueueADT {
public:
   // Member functions that may change the queue
   virtual bool Enqueue(int item) = 0;
   virtual int Dequeue() = 0;

   // Member functions that do not change the queue
   virtual int GetLength() const = 0;
   virtual bool IsEmpty() const = 0;
   virtual int Peek() const = 0;
   virtual void Print(std::ostream& printStream = std::cout,
      const std::string& separator = ", ") const = 0;
};

#endif
```

**`ArrayQueue.h`**

```cpp
#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include "QueueADT.h"

class ArrayQueue : public QueueADT {
private:
   int allocationSize;
   int* array;
   int frontIndex;
   int length;
   int maxLength;

   void Resize() {
      // Allocate new array and copy existing items
      int newSize = allocationSize * 2;
      if (maxLength >= 0 && newSize > maxLength) {
         newSize = maxLength;
      }
      int* newArray = new int[newSize];
      for (int i = 0; i < length; i++) {
         int itemIndex = (frontIndex + i) % allocationSize;
         newArray[i] = array[itemIndex];
      }

      // Delete old array, assign new array, and assign new allocation size
      delete[] array;
      array = newArray;
      allocationSize = newSize;

      // Reset frontIndex to 0
      frontIndex = 0;
   }

public:
   ArrayQueue(int maximumLength = -1) {
      allocationSize = (0 == maximumLength) ? 0 : 1;
      array = new int[allocationSize];
      length = 0;
      frontIndex = 0;
      maxLength = maximumLength;
   }

   virtual ~ArrayQueue() {
      delete[] array;
   }

   virtual int Dequeue() override {
      // Get the item at the front of the queue
      int toReturn = array[frontIndex];

      // Decrement length and advance frontIndex
      length--;
      frontIndex = (frontIndex + 1) % allocationSize;

      // Return the front item
      return toReturn;
   }

   virtual bool Enqueue(int item) override {
      // If at max length, return false
      if (length == maxLength) {
         return false;
      }

      // Resize if length equals allocation size
      if (length == allocationSize) {
         Resize();
      }

      // Enqueue the item and return true
      int itemIndex = (frontIndex + length) % allocationSize;
      array[itemIndex] = item;
      length++;
      return true;
   }

   virtual int GetLength() const override {
      return length;
   }

   virtual int GetMaxLength() {
      return maxLength;
   }

   virtual bool IsEmpty() const override {
      return 0 == length;
   }

   virtual int Peek() const override {
      return array[frontIndex];
   }

   virtual void Print(std::ostream& printStream = std::cout,
      const std::string& separator = ", ") const override {
      if (length > 0) {
         // Front item is not preceded by separator
         printStream << array[frontIndex];
      }
      for (int i = 1; i < length; i++) {
         // Each item after the front is preceded by the separator
         int index = (frontIndex + i) % allocationSize;
         printStream << separator << array[index];
      }
   }
};

#endif
```

**`ArrayBasedQueues.cpp`**

```cpp
#include <iostream>
#include "ArrayQueue.h"
using namespace std;

int main() {
   // Make two queues, one bounded to 4 items and the other unbounded
   ArrayQueue boundedQueue(4);
   ArrayQueue unboundedQueue;

   // Enqueue 8 items in each
   cout << "Enqueueing values 1 through 8 to each queue" << endl;
   for (int i = 1; i <= 8; i++) {
      boundedQueue.Enqueue(i);
      unboundedQueue.Enqueue(i);
   }

   // Dequeue two items from each queue
   cout << "Dequeuing twice" << endl;
   for (int i = 0; i < 2; i++) {
      cout << "  Dequeued " << boundedQueue.Dequeue();
      cout << " from bounded queue" << endl;
      cout << "  Dequeued " << unboundedQueue.Dequeue();
      cout << " from unbounded queue" << endl;
   }

   // Enqueue 4 more items
   cout << "Enqueueing values: 10, 20, 30 and 40" << endl;
   for (int i = 10; i <= 40; i+=10) {
      boundedQueue.Enqueue(i);
      unboundedQueue.Enqueue(i);
   }

   // Display contents of each queue
   cout << "Bounded queue (maxLength=";
   cout << boundedQueue.GetMaxLength();
   cout << ") contents:" << endl;
   while (boundedQueue.GetLength() > 0) {
      cout << "  " << boundedQueue.Dequeue() << endl;
   }
   cout << "Unbounded queue contents:" << endl;
   while (unboundedQueue.GetLength() > 0) {
      cout << "  " << unboundedQueue.Dequeue() << endl;
   }
}
```

---

### 13. Counted Queue (inheritance example)

We want a `GetLength` operation. Instead of editing `QueType`, *derive* a new class that adds a length counter.

```cpp
class CountedQueType : public QueType {
public:
    CountedQueType(int max);
    void Enqueue(ItemType newItem);    // override
    void Dequeue(ItemType& item);      // override
    int  GetLength() const;
private:
    int length;
};

// Constructor initializer calls the base ctor:
CountedQueType::CountedQueType(int max) : QueType(max) { length = 0; }

void CountedQueType::Enqueue(ItemType newItem) {
    try   { QueType::Enqueue(newItem); length++; }
    catch (FullQueue) { throw FullQueue(); }
}

void CountedQueType::Dequeue(ItemType& item) {
    try   { QueType::Dequeue(item);    length--; }
    catch (EmptyQueue) { throw EmptyQueue(); }
}

int CountedQueType::GetLength() const { return length; }
```

Key syntax points:
- **`class Derived : public Base`** — public inheritance.
- **`Derived(...) : Base(...) { }`** — *constructor initializer* calls the base-class constructor.
- **`QueType::Enqueue(...)`** — use scope resolution to call the base's version.
- Derived classes **cannot** touch the base's private data members (`front`, `rear`); they must go through the public API.

---

### 14. Linked-List Queue

Use two external pointers — `front` and `rear` — so both ends are O(1) reachable.

```
   front                           rear
     v                               v
   [ A |*] -> [ B |*] -> [ C |*] -> [ D | NULL ]
```

#### Class layout

```cpp
struct NodeType { ItemType info; NodeType* next; };

class QueType {
public:
    QueType();
    ~QueType();
    void MakeEmpty();
    void Enqueue(ItemType);
    void Dequeue(ItemType&);
    bool IsEmpty() const;
    bool IsFull()  const;
private:
    NodeType* front;
    NodeType* rear;
};
```

#### Enqueue — add at the rear (textbook, page 691)

```cpp
void QueType::Enqueue(ItemType newItem) {
    if (IsFull()) throw FullQueue();
    NodeType* newNode = new NodeType;
    newNode->info = newItem;
    newNode->next = NULL;
    if (rear == NULL) front      = newNode;   // empty: front also points here
    else              rear->next = newNode;   // non-empty: splice in
    rear = newNode;
}
```

```
Before (empty):  front=NULL,  rear=NULL
Enqueue(A):      front -> [A|NULL] <- rear
Enqueue(B):      front -> [A|*] -> [B|NULL] <- rear
Enqueue(C):      front -> [A|*] -> [B|*] -> [C|NULL] <- rear
```

#### Dequeue — remove from the front

```cpp
void QueType::Dequeue(ItemType& item) {
    if (IsEmpty()) throw EmptyQueue();
    NodeType* tempPtr = front;
    item  = front->info;
    front = front->next;
    if (front == NULL) rear = NULL;    // queue is now empty
    delete tempPtr;
}
```

```
Before:  front -> [A|*] -> [B|*] -> [C|NULL] <- rear
Dequeue: front -------> [B|*] -> [C|NULL] <- rear   (A node deleted, item = 'A')
```

#### Why not reverse front and rear?

If `front` pointed to the rear of the chain and `rear` to the head (so Enqueue mimics Push), then **Dequeue would need the predecessor of the new front node** — but singly-linked nodes can't go backward. You'd be forced into an O(N) scan. The chosen layout (front at head, rear at tail) keeps both ops O(1). [See slide 34, "A bad queue design."]

#### Zybooks example (Linked-list-based queue implementation)

Same two-pointer idea as the textbook (`front` at head, tail pointer at end), but uses `end` instead of `rear` and **`delete`s the front node on dequeue** — unlike the array version, which only advances an index.

**`QueueADT.h`**

```cpp
#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <iostream>

class QueueADT {
public:
   // Member functions that may change the queue
   virtual bool Enqueue(int item) = 0;
   virtual int Dequeue() = 0;

   // Member functions that do not change the queue
   virtual int GetLength() const = 0;
   virtual bool IsEmpty() const = 0;
   virtual int Peek() const = 0;
   virtual void Print(std::ostream& printStream = std::cout,
      const std::string& separator = ", ") const = 0;
};

#endif
```

**`Queue.h`**

```cpp
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "QueueADT.h"

// Node to store an item in a linked-list-based queue
class QueueNode {
public:
   int data;
   QueueNode* next;

   QueueNode(int dataValue, QueueNode* nextNode = nullptr) {
      data = dataValue;
      next = nextNode;
   }
};

class Queue : public QueueADT {
private:
   QueueNode* front;
   QueueNode* end;

public:
   Queue() {
      front = nullptr;
      end = nullptr;
   }

   virtual ~Queue() {
      while (front) {
         QueueNode* nodeToDelete = front;
         front = front->next;
         delete nodeToDelete;
      }
   }

   virtual bool Enqueue(int newData) override {
      // Create a new node
      QueueNode* newNode = new QueueNode(newData);

      // Append newNode to the end of the linked list
      if (nullptr == front) {
         front = newNode;
      }
      else {
         end->next = newNode;
      }
      end = newNode;

      return true;
   }

   virtual int Dequeue() override {
      // Copy front node's data
      QueueNode* dequeuedNode = front;
      int dequeuedItem = front->data;

      // Remove front node
      front = front->next;
      delete dequeuedNode;

      // If empty, assign end with nullptr
      if (nullptr == front) {
         end = nullptr;
      }

      // Return dequeued item
      return dequeuedItem;
   }

   virtual int GetLength() const override {
      int length = 0;
      QueueNode* node = front;
      while (node) {
         length++;
         node = node->next;
      }
      return length;
   }

   virtual bool IsEmpty() const override {
      return nullptr == front;
   }

   virtual int Peek() const override {
      return front->data;
   }

   virtual void Print(std::ostream& printStream = std::cout,
      const std::string& separator = ", ") const override {
      QueueNode* node = front;
      if (node) {
         // Front item is not preceded by separator
         printStream << node->data;
         node = node->next;
      }
      while (node) {
         // Each item after the front is preceded by the separator
         printStream << separator << node->data;
         node = node->next;
      }
   }
};

#endif
```

**`main.cpp`**

```cpp
#include <iostream>
#include "Queue.h"
using namespace std;

int main() {
   int numbers[] = { 83, 44, 57, 66, 92, 49, 64, 55 };

   // Initialize a new Queue and add numbers
   Queue numQueue;
   for (int number : numbers) {
      numQueue.Enqueue(number);
   }

   // Print queue
   cout << "Queue: ";
   numQueue.Print();
   cout << endl;

   // Dequeue each item and print the queue. Repeat until empty.
   while (!numQueue.IsEmpty()) {
      cout << "Dequeued " << numQueue.Dequeue() << endl;
      cout << "Queue: ";
      numQueue.Print();
      cout << endl;
   }

   return 0;
}
```

---

### 15. Circular Linked Queue (only one pointer!)

Make the chain circular and store only a pointer to the **rear**. Then:
- The rear is `rear` itself (O(1)).
- The front is `rear->next` (O(1)).

```
        rear
          v
   .--> [ A |*] -> [ B |*] -> [ C |*] -> [ D |*] -.
   |                                              |
   '----------------------------------------------'
   (D->next points back to A, the "front")
```

- Empty queue: `rear == NULL`.

---

### 16. Comparing Queue Implementations (Table 5.2)

| Operation | Dynamic Array | Linked |
|-----------|--------------|--------|
| Constructor | O(1) | O(1) |
| `MakeEmpty` | O(1) | **O(N)** |
| `IsFull` | O(1) | O(1) |
| `IsEmpty` | O(1) | O(1) |
| `Enqueue` | O(1) | O(1) |
| `Dequeue` | O(1) | O(1) |
| Destructor | O(1) | **O(N)** |

**Memory trade-off** (Figure 5.21):
- Array uses a *fixed* `(maxQue × element_size)` regardless of fill.
- Linked uses `count × (element_size + pointer_size)` — wins for small/varying queues, **loses** when the queue gets large or the element is tiny (4-byte pointer dwarfs a 2-byte int).

Example: 80-byte strings, max 100 elements:
- Array always uses `80 × 101 + 4 = 8084` bytes.
- Linked uses `84 × N + 8` bytes — wins until N ≈ 96, then loses.

---

# Chapter 6: Lists Plus

## 1. C++ Templates

- A **generic data type** specifies operations without committing to a concrete element type.
- A **template** lets the compiler *generate* a specialized class for each type the client uses.

```cpp
template <class ItemType>
class StackType {
public:
    StackType();
    bool IsEmpty() const;
    bool IsFull()  const;
    void Push(ItemType item);
    void Pop();
    ItemType Top() const;
private:
    int      top;
    ItemType items[MAX_ITEMS];
};
```

Clients instantiate it:

```cpp
StackType<int>    intStack;
StackType<float>  floatStack;
StackType<char>   charStack;
StackType<string> stringStack;
```

The compiler emits a distinct compiled class for each `T` you actually use.

#### Templated member functions

Every member function that uses the template type must be templated too. The class name in the definition includes the template arg:

```cpp
template <class ItemType>
void StackType<ItemType>::Push(ItemType newItem) {
    if (IsFull()) throw FullStack();
    top++;
    items[top] = newItem;
}
```

#### Templates and source files — the "include the .cpp at the end of the .h" pattern

Normally `.h` (declarations) and `.cpp` (definitions) compile separately. But with templates, the compiler needs to see the *implementation* when it sees the type argument. Two solutions:

1. Put the implementation directly inside the header.
2. Keep `.cpp`, but `#include "StackType.cpp"` at the **bottom** of `StackType.h`.

---

## 2. Circular Linked Lists

Every node has a successor. The "last" node points back to the "first". A single external pointer often points to the **rear** so both ends are reachable.

```
   external  (points to LAST node)
       v
   .--> [A|*] -> [B|*] -> [C|*] -> [D|*] -.
   |                                       |
   '---------------------------------------'
```

#### `FindItem` helper — search until you wrap around

```
Stop when either:
  1. location->info >= item (found, or item not present in a sorted list)
  2. location reaches the first node again (full lap completed)

Returns: (location, predecessor, found_flag)
```

Four search-result cases (Figure 6.4):

```
(a) General case — Find B in [A, B, C, D]:
      stop with location -> [B], predecessor -> [A], found=true

(b) Smallest item — Find A:
      starts with predecessor -> [D] (the rear), location -> [A], found=true

(c) Not present — Find C in [A, B, D]:
      stop with location -> [D], predecessor -> [B], found=false

(d) Larger than any — Find E in [A, B, C, D]:
      full lap, location wraps back to [A], found=false
```

#### Insertion cases (Figure 6.5)

```
(a) General  (Insert C into [A, B, D, E]):
      predecessor -> [B];  link [B]->[C]->[D]

(b) Empty list:
      new node points to itself; external pointer -> new node

(c) Insert at FRONT  (Insert A into [B, C, D]):
      same as general — no special case in a circular list!

(d) Insert at END  (Insert E into [A, B, C, D]):
      general case + update external pointer to new node
```

> The big win of circular lists: inserting at the front no longer needs special-case code (it's the same as inserting anywhere else).

#### Deletion cases (Figure 6.6)

```
(a) General — predecessor->next = location->next; delete location;
(b) Delete smallest — same as general (no special case)
(c) Delete only item — set external pointer to NULL
(d) Delete largest (the one external points to) — update external pointer to predecessor
```

---

## 3. Doubly Linked Lists

Every node has **two** pointers: `next` (successor) and `back` (predecessor).
- First node: `back == NULL`.
- Last node: `next == NULL`.
- Walk in either direction in O(1) per step.

```
   NULL <- [A] <-> [B] <-> [C] <-> [D] -> NULL
```

```cpp
struct NodeType {
    ItemType  info;
    NodeType* next;
    NodeType* back;
};
```

#### Insertion (Figure 6.9)

Both the predecessor *and* the successor need their pointers updated:

```cpp
// Insert newNode between predLoc and predLoc->next
newNode->back        = predLoc;
newNode->next        = predLoc->next;
predLoc->next->back  = newNode;
predLoc->next        = newNode;
```

#### Deletion (Figure 6.10)

```cpp
// Remove the node at `location` (general case)
location->back->next = location->next;
location->next->back = location->back;
delete location;
```

End cases: if `location->back == NULL`, you're deleting the first node; if `location->next == NULL`, the last; if both, the only one.

#### Benefit: no more "inchworm"

In a singly linked sorted list, every insert/delete needs the *predecessor* — hence the two-pointer "inchworm" walk. With doubly linked, `location->back` gives the predecessor for free, so a single pointer (and a simple `FindItem`) is enough.

---

## 4. Lists with Headers and Trailers

Add dummy nodes at both ends so the *real* nodes are always between two sentinels — eliminating "is this the first/last?" special cases.

```
       header                                          trailer
   ["AAAAA"|*] -> [Adam|*] -> [Eve|*] -> [Zoe|*] -> ["ZZZZZ"|NULL]
```

The header value is smaller than any possible key; the trailer is larger. Insertion and deletion no longer need to test "predecessor is NULL" or "successor is NULL" — there's always a predecessor and a successor.

---

## 5. Copying Structures (the big chapter)

### 5.1 The problem

```cpp
template <class T>
void CopyStack(StackType<T> oldStack, StackType<T>& copy) {
    StackType<T> tempStack;
    T item;
    while (!oldStack.IsEmpty())  { item = oldStack.Top(); oldStack.Pop(); tempStack.Push(item); }
    while (!tempStack.IsEmpty()) { item = tempStack.Top(); tempStack.Pop(); copy.Push(item); }
}
```

With the **array-based** stack, `oldStack` is a value parameter — the array lives inside the object, so popping the copy doesn't touch the original. **Safe.**

With the **linked** stack, only the `topPtr` pointer is copied. Both `oldStack` and the caller's stack point to the *same* chain of nodes. Popping the copy *destroys the caller's stack*. **Disaster.**

### 5.2 Shallow vs. Deep Copy

```
Original:   caller.topPtr ---->  [C] -> [B] -> [A] -> NULL


SHALLOW (default):
            caller.topPtr ---.
                             v
                            [C] -> [B] -> [A] -> NULL
                             ^
            oldStack.topPtr -'
            (both pointers, ONE chain)


DEEP (what we want):
            caller.topPtr   -->  [C] -> [B] -> [A] -> NULL
            oldStack.topPtr -->  [C'] -> [B'] -> [A'] -> NULL
            (two separate chains)
```

| Term | What it copies |
|------|----------------|
| **Shallow copy** | Just the data members (including any pointers, **as pointers**) |
| **Deep copy** | Data members AND the data they point to |

C++ uses **shallow copy by default** for: passing by value, returning by value, declarations like `Stack a = b;`, and `a = b;`.

### 5.3 Copy Constructor

A special constructor invoked implicitly when a class object is *copied* (passed by value, initialized in a declaration, or returned from a function). It must take a `const` reference to its own type:

```cpp
template <class ItemType>
class StackType {
public:
    StackType();                                                // default
    StackType(const StackType<ItemType>& anotherStack);         // COPY constructor
    ~StackType();
    // ... etc.
};
```

Implementation (textbook page 797):

```cpp
template <class ItemType>
StackType<ItemType>::StackType(const StackType<ItemType>& anotherStack) {
    NodeType<ItemType>* ptr1;
    NodeType<ItemType>* ptr2;
    if (anotherStack.topPtr == NULL) {
        topPtr = NULL;
    } else {
        topPtr        = new NodeType<ItemType>;
        topPtr->info  = anotherStack.topPtr->info;
        ptr1          = anotherStack.topPtr->next;   // walking the SOURCE
        ptr2          = topPtr;                      // last node copied into NEW
        while (ptr1 != NULL) {
            ptr2->next       = new NodeType<ItemType>;
            ptr2             = ptr2->next;
            ptr2->info       = ptr1->info;
            ptr1             = ptr1->next;
        }
        ptr2->next = NULL;
    }
}
```

### 5.4 Friend Functions — `Copy(s1, s2)` instead of `s1.Copy(s2)`

The dot syntax `myStack.Copy(yourStack)` is ambiguous (which one gets copied into which?). A **friend function** is a non-member that's allowed to touch private data:

```cpp
template <class ItemType>
class StackType {
public:
    friend void Copy(StackType<ItemType>, StackType<ItemType>&);
    // ...
};

template <class ItemType>
void Copy(StackType<ItemType> original, StackType<ItemType>& copy) {
    if (original.topPtr == NULL) { copy.topPtr = NULL; return; }

    NodeType<ItemType>* ptr1;
    NodeType<ItemType>* ptr2;
    copy.topPtr        = new NodeType<ItemType>;
    copy.topPtr->info  = original.topPtr->info;
    ptr1               = original.topPtr->next;
    ptr2               = copy.topPtr;
    while (ptr1 != NULL) {
        ptr2->next     = new NodeType<ItemType>;
        ptr2           = ptr2->next;
        ptr2->info     = ptr1->info;
        ptr1           = ptr1->next;
    }
    ptr2->next = NULL;
}
```

A friend has no implicit `self`; it accesses private members through its parameters (`original.topPtr`).

### 5.5 Operator Overloading — making `s1 = s2;` do a deep copy

Declare the operator inside the class, then implement it like any other member:

```cpp
template <class ItemType>
class StackType {
public:
    void operator=(StackType<ItemType> anotherStack);   // overloaded =
    bool operator==(StackType<ItemType> other) const;
    // ...
};
```

Now `myStack = yourStack;` is translated by the compiler into `myStack.operator=(yourStack);` and your deep-copy code runs.

#### Example: overloading `<`, `>`, `==` on `DateType` (textbook page 805)

```cpp
bool DateType::operator<(DateType other) const {
    if (year  < other.year)  return true;
    if (year  > other.year)  return false;
    if (month < other.month) return true;
    if (month > other.month) return false;
    return day < other.day;
}

bool DateType::operator>(DateType other) const  { /* mirror image */ }

bool DateType::operator==(DateType other) const {
    return year == other.year && month == other.month && day == other.day;
}
```

Now client code reads naturally: `if (myBirthday < yourBirthday) { ... }`.

#### Overloading rules (slide 33–34 / textbook page 806)

- At least one operand must be a class instance.
- You **cannot** change precedence, define new symbols, or change operand count.
- These operators **cannot be overloaded**: `::`, `.`, `sizeof`, `?:`.
- `=`, `()`, `[]`, `->` **must** be member functions.
- `<<`, `>>` (stream operators) **must** be friend functions.
- `++` and `--` overloads require prefix form (`++obj`).

### 5.6 The Rule of the Big 3

> If one of {destructor, copy constructor, `operator=`} is needed, *all three* are usually needed.

This applies to any class that owns a heap resource (linked list, dynamic array, file handle, etc.).

---

## 6. Linked List as an Array of Records

"Array vs. linked list" and "static vs. dynamic" are **two different axes**.

| | Static | Dynamic |
|---|--------|---------|
| **Array** | `int a[10];` | `int* a = new int[10];` |
| **Linked** | array indices act as "pointers" (this section!) | the usual `new NodeType` chain |

### 6.1 Why an array of records?

- Languages/environments without dynamic allocation or pointers can still have linked lists.
- Easy to serialize: write the whole array to a file; indices stay valid next run (memory addresses don't).
- Avoids the runtime cost of `new`/`delete` on every node — useful in OS kernels.

### 6.2 Mechanics

- Each "node" is a struct `{ ItemType info; int next; }` in a big array.
- Use index `-1` (constant `NUL`) instead of `NULL` for end-of-list.
- Manage your *own* free space — unused slots are themselves a linked list (the **free list**).

```
   info  next                external pointers
   ----------                 list = 0
0: David  4
1:  ---   5    <-- free       free = 1
2: Miriam 6
3:  ---   8    <-- free
4: Joshua 7
5:  ---   3    <-- free
6: Robert -1
7: Leah   2
8:  ---   9    <-- free
9:  ---  -1    <-- free (end of free list)

list (data):  0 -> 4 -> 7 -> 2 -> 6 -> NUL   (David, Joshua, Leah, Miriam, Robert)
free list:    1 -> 5 -> 3 -> 8 -> 9 -> NUL
```

### 6.3 Bookkeeping functions (textbook page 821)

```cpp
const int NUL = -1;

struct NodeType   { int info; int next; };
struct MemoryType { int free; NodeType* nodes; };

void InitializeMemory(int maxItems, MemoryType& storage) {
    for (int i = 1; i < maxItems; i++)
        storage.nodes[i-1].next = i;
    storage.nodes[maxItems-1].next = NUL;
    storage.free = 0;
}

void GetNode(int& nodeIndex, MemoryType& storage) {       // "new"
    nodeIndex      = storage.free;
    storage.free   = storage.nodes[storage.free].next;
}

void FreeNode(int nodeIndex, MemoryType& storage) {       // "delete"
    storage.nodes[nodeIndex].next = storage.free;
    storage.free                  = nodeIndex;
}
```

### 6.4 Dictionary of equivalences

| Design idea | Pointer-based code | Array-of-records code |
|-------------|-------------------|-----------------------|
| `Node(loc)` | `*loc` | `storage.nodes[loc]` |
| `Info(loc)` | `loc->info` | `storage.nodes[loc].info` |
| `Next(loc)` | `loc->next` | `storage.nodes[loc].next` |
| allocate    | `loc = new NodeType;` | `GetNode(loc, storage);` |
| free        | `delete loc;` | `FreeNode(loc, storage);` |

One array can even hold **multiple lists** (Figure 6.19): each external "pointer" is just an int, and all lists draw nodes from the same shared free list.

---

## 7. Polymorphism with Virtual Functions

- **Polymorphism**: choose which function to call based on the actual object's type.
- **Static binding**: decision made at *compile* time (overloading).
- **Dynamic binding**: decision made at *run* time (virtual functions).

In C++, an overridden member function dispatches **dynamically** when:
- the function is declared `virtual` in the base class, AND
- the actual parameter is passed by **reference** or via a **pointer to the base class**.

If the object is passed **by value**, only the base subobject is copied (**slicing**) and the base's version runs.

### 7.1 Worked example (slides 48–50)

```cpp
#include <iostream>

class One {
public:
    virtual void Print() const;
};

class Two : public One {
public:
    void Print() const;          // override
};

void One::Print() const { std::cout << "Print class One" << std::endl; }
void Two::Print() const { std::cout << "Print class Two" << std::endl; }
```

Three callers — by reference, by pointer, by value:

```cpp
void PrintRef(One&  ptr) { ptr.Print();  }   // by reference
void PrintPtr(One*  ptr) { ptr->Print(); }   // by pointer
void PrintVal(One   ptr) { ptr.Print();  }   // by value (sliced!)
```

Driver:

```cpp
int main() {
    One one;
    Two two;

    std::cout << "Result of printing one:\n";
    PrintRef(one);    // "Print class One"
    PrintPtr(&one);   // "Print class One"
    PrintVal(one);    // "Print class One"

    std::cout << "Result of printing two:\n";
    PrintRef(two);    // "Print class Two"   <- dynamic dispatch via reference
    PrintPtr(&two);   // "Print class Two"   <- dynamic dispatch via pointer
    PrintVal(two);    // "Print class One"   <- SLICED! base copy only

    std::cout << "Pointer to a derived type:\n";
    One* onePtr = new One;
    PrintPtr(onePtr); // "Print class One"
    onePtr      = new Two;
    PrintPtr(onePtr); // "Print class Two"
    return 0;
}
```

**Lesson**: virtual + reference/pointer = polymorphism. Virtual + by-value = slicing.

---

## 8. A Specialized List ADT — Doubly Linked, Circular

The Case Study list of integers requires:
- duplicates allowed,
- bidirectional iteration (forward AND backward at the same time),
- inserting at the front *or* the back.

Neither doubly-linked-only (no easy access to last) nor circular-singly (no backward walk) is enough. Combine them: a **doubly linked circular** list with an external pointer to the rear.

```
                     list (points to last node)
                                v
   .---> [A | back | next] <-> [B | back | next] <-> [C | back | next] <-.
   |                                                                      |
   '----------------------------------------------------------------------'
```

### 8.1 Public interface

```cpp
class SpecializedList {
public:
    SpecializedList();
    ~SpecializedList();
    SpecializedList(const SpecializedList& someList);   // copy constructor

    void ResetForward();
    void GetNextItem(int& item, bool& finished);

    void ResetBackward();
    void GetPriorItem(int& item, bool& finished);

    void PutFront(int item);
    void PutEnd(int item);

    int  GetLength();

private:
    NodeType* list;             // points to last node
    NodeType* currentNextPos;   // forward iterator
    NodeType* currentBackPos;   // backward iterator
    int       length;
};

struct NodeType { NodeType* next; NodeType* back; int info; };
```

Two cursors: forward and backward iteration are **independent** — calling `GetNextItem` doesn't affect a backward iteration in progress.

### 8.2 `PutFront` — handles empty and non-empty in O(1) (textbook page 837)

```cpp
void SpecializedList::PutFront(int item) {
    NodeType* newNode = new NodeType;
    newNode->info     = item;
    if (list == NULL) {                       // empty list: node points to itself
        newNode->back = newNode;
        newNode->next = newNode;
        list = newNode;
    } else {
        newNode->back       = list;           // back -> rear
        newNode->next       = list->next;     // next -> old front
        list->next->back    = newNode;        // old front's back -> new node
        list->next          = newNode;        // rear's next     -> new node
    }
    length++;
}
```

### 8.3 `PutEnd` is just `PutFront` plus moving `list`!

```cpp
void SpecializedList::PutEnd(int item) {
    PutFront(item);
    list = list->next;     // rotate one step so the new node IS the rear
}
```

### 8.4 Iteration

```cpp
void SpecializedList::ResetForward()  { currentNextPos = NULL; }
void SpecializedList::ResetBackward() { currentBackPos = NULL; }

void SpecializedList::GetNextItem(int& item, bool& finished) {
    if (currentNextPos == NULL) currentNextPos = list->next;     // first call -> head
    else                        currentNextPos = currentNextPos->next;
    item     = currentNextPos->info;
    finished = (currentNextPos == list);                         // wrapped to rear?
}

void SpecializedList::GetPriorItem(int& item, bool& finished) {
    if (currentBackPos == NULL) currentBackPos = list;           // first call -> rear
    else                        currentBackPos = currentBackPos->back;
    item     = currentBackPos->info;
    finished = (currentBackPos == list->next);                   // wrapped to head?
}
```

---

## 9. Range-Based `for` and C++ Iterators

### 9.1 The classic index loop has pitfalls

```cpp
for (int i = 0; i < length; i++)  cout << numbers[i];
// Off-by-one? <= length? Initialized to 1 instead of 0?
```

### 9.2 Range-based `for` (introduced in C++11)

```cpp
for (int e : numbers) cout << e;     // "for each e in numbers"
```

- No index variable.
- No termination expression.
- Works on built-in arrays AND any collection that implements `begin()` / `end()`.

This is **syntactic sugar**: the compiler rewrites the loop as

```cpp
for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    auto e = *it;
    /* body */
}
```

So `e` is just `*it` for some iterator object.

### 9.3 Making your own ADT iterable

You need **two ADT methods** and **three operators on the iterator**:

```cpp
// On the ADT:
Iterator begin();      // iterator pointing at the first element
Iterator end();        // iterator just past the last element

// On the Iterator class:
T&        operator*();                              // dereference
Iterator& operator++();                             // advance
bool      operator!=(const Iterator& it) const;     // compare
```

### 9.4 `SortedTypeIterator` for a linked sorted list (textbook page 846)

```cpp
template <class T>
class SortedTypeIterator {
public:
    SortedTypeIterator(NodeType<T>* start);
    T& operator*();
    SortedTypeIterator<T>& operator++();
    bool operator!=(const SortedTypeIterator<T>& it) const;
private:
    NodeType<T>* item;
};
```

Implementations:

```cpp
template <class T>
SortedTypeIterator<T>::SortedTypeIterator(NodeType<T>* start) { this->item = start; }

template <class T>
T& SortedTypeIterator<T>::operator*() { return item->info; }

template <class T>
SortedTypeIterator<T>& SortedTypeIterator<T>::operator++() {
    if (item == NULL || item->next == NULL) item = NULL;     // hit the end
    else                                    item = item->next;
    return *this;
}

template <class T>
bool SortedTypeIterator<T>::operator!=(const SortedTypeIterator<T>& it) const {
    return item != it.item;
}
```

And on the list:

```cpp
template <class T>
SortedTypeIterator<T> SortedType<T>::begin() { return SortedTypeIterator<T>(listData); }

template <class T>
SortedTypeIterator<T> SortedType<T>::end()   { return SortedTypeIterator<T>(NULL); }
```

Client code:

```cpp
SortedType<int> nums;
nums.PutItem(3); nums.PutItem(1); nums.PutItem(2);

for (int n : nums) std::cout << n << " ";   // prints 1 2 3
```

The compiler unrolls this into the iterator loop above.

---

## Key Themes Across Both Chapters

1. **Restricted access ADTs** (Stack/Queue) are just lists with extra rules. The implementations from Ch. 3–4 carry straight over — only the *interface* gets locked down to LIFO / FIFO.
2. **Pick the right end of the list** — stacks push/pop at one end (the head). Queues need both ends; either two pointers + linear chain, or one pointer + circular chain.
3. **Wrap-around with modular arithmetic** turns an array into a circular buffer and rescues the O(N) `Dequeue`.
4. **Inheritance vs. composition** — `CountedQueType : public QueType` extends behavior (*is-a*); `LargeInt` *contains* a `SpecializedList` (*has-a*).
5. **Templates** decouple "how the structure works" from "what it holds", with zero runtime cost.
6. **Deep vs. shallow copy** — any class that owns a heap resource needs the **Big 3**: destructor, copy constructor, `operator=`.
7. **Polymorphism** = `virtual` + pointer/reference. Pass by value loses it (slicing).
8. **Specialized lists** are built by mixing primitives: doubly linked + circular = bidirectional traversal with direct access to both ends.
9. **Iterators** unify iteration across all ADTs and feed directly into the modern range-based `for` loop — eliminating off-by-one bugs and exposing a stable API regardless of how the collection is stored.
