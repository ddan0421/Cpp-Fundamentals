# CSC 240 — Unit Summary (Lists)

**Chapters Covered:**
- Chapter 3: ADT Unsorted List
- Chapter 4: ADT Sorted List

---

## Reference: Pointers and the `->` operator

Linked lists lean heavily on pointers. This section is the general rule; linked-list code applies it to `head`, `tail`, and `next`.

### Pointer vs object

A **pointer variable** stores a **memory address** — where something lives — not the object itself.

```cpp
int value = 42;
int* p = &value;    // p holds the address of value
```

| Syntax | Meaning |
|--------|---------|
| `&value` | address-of: "where does `value` live?" |
| `*p` | dereference: "go to what `p` points at" |
| `p` alone | the address itself (a bookmark) |

### `.` vs `->`

Use **`.`** when you have the object directly. Use **`->`** when you have a **pointer to** an object.

```cpp
struct Node {
    int data;
    Node* next;
};

Node node;          // an actual node object
Node* ptr = &node;  // a pointer to that node

node.data = 10;     // dot: object.member
ptr->data = 10;     // arrow: pointer->member

// These are equivalent:
ptr->data
(*ptr).data
```

**Rule:** `->` means *follow the pointer, then access the member*.

### What `->` is **not**

- **`head->next`** does not mean "`head` has a `next` field." `head` is just a pointer variable on the list object. `->` follows `head` to a **node**, then reads that node's `next`.
- The **`->` in diagrams** (e.g. `[ Bobby ] -> [ Judy ]`) shows logical flow between nodes — related idea, but not C++ syntax.

### Linked-list examples

```cpp
SinglyLinkedNode* head;   // bookmark — no data, no next
SinglyLinkedNode* tail;   // bookmark — no data, no next

// head points at a node; that node has data and next:
head->data              // read the first node's value
head->next              // follow link to second node (or null)

// Append: tail points at the last node; we update THAT node's next, then move tail:
tail->next = newNode;   // link old last node → new node
tail = newNode;         // update bookmark (not a -> operation)
```

When you see `something->field`, ask: **"What does `something` point at?"** The field belongs to that target, not to the pointer variable itself.

---

## Big Picture

A **list** is the first non-trivial ADT we build. Both chapters build the same logical thing — a linear collection of items — but they explore four different *implementations*:

| | **Array-based** | **Linked List-based** |
|---|---|---|
| **Unsorted** | Ch. 3 (first half) | Ch. 3 (second half) |
| **Sorted** | Ch. 4 (first half) | Ch. 4 (second half) |

The pattern is: keep the logical interface identical, swap out the implementation, and compare the Big-O behavior.

---

## Chapter 3: ADT Unsorted List

### 1. What is a List?

- **List**: a *homogeneous* collection of elements with a *linear* relationship between them.
- **Linear relationship**: every element except the first has a unique **predecessor**, and every element except the last has a unique **successor**.
- **Length**: the number of items currently in the list (varies over time).

```
[ Bobby ] -> [ Judy ] -> [ Kit ] -> [ Lila ]
   ^first                            last^
```

### 2. List Variants

| Term | Definition |
|------|-----------|
| **Unsorted List** | Items appear in no particular order (insertion order, typically). |
| **Sorted List** | Items ordered by **key**; there is a semantic relationship among keys. |
| **Key** | The attribute(s) of an item used to determine logical order. |

### 3. Unsorted List Operations

| Category | Operations |
|----------|-----------|
| **Constructor** | Make empty list (or initialize with some elements) |
| **Transformers** | `PutItem`, `DeleteItem`, `MakeEmpty` |
| **Observers** | `IsFull`, `GetLength`, `GetItem` |
| **Iterators** | `ResetList`, `GetNextItem` |

### 4. Generic Data Types

- A **generic data type** specifies operations without committing to a concrete item type.
- C++ supports this with **templates**.
- Dale's textbook simulates a generic by using a user-defined `ItemType` class that provides at least a `ComparedTo(other)` method. The list code calls only `ComparedTo`, `Initialize`, and `Print` — swap in any `ItemType` that implements them and the list works unchanged.

#### Specification — `ItemType.h`

```cpp
// ItemType.h
#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <iostream>

const int MAX_ITEMS = 5;                  // capacity used by the array-based list
enum RelationType { LESS, GREATER, EQUAL };

class ItemType {
public:
    ItemType();                           // default ctor: value = 0
    RelationType ComparedTo(ItemType other) const;
    void Initialize(int number);
    void Print(std::ostream& out) const;
private:
    int value;
};

#endif
```

#### Implementation — `ItemType.cpp`

```cpp
// ItemType.cpp
#include "ItemType.h"

ItemType::ItemType() {
    value = 0;
}

RelationType ItemType::ComparedTo(ItemType other) const {
    if (value < other.value) return LESS;
    if (value > other.value) return GREATER;
    return EQUAL;
}

void ItemType::Initialize(int number) {
    value = number;
}

void ItemType::Print(std::ostream& out) const {
    out << value;
}
```

#### How the list uses it

The list ADT never touches `value` directly — it only invokes the public interface above. To make the list hold `string` keys, `Date` keys, or anything else, write a new `ItemType` with the same four members; **no list code needs to change**.

```cpp
// Example client snippet
UnsortedType list;
ItemType x, y, z;
x.Initialize(42);
y.Initialize(17);
z.Initialize(99);
list.PutItem(x);
list.PutItem(y);
list.PutItem(z);

bool found;
ItemType target; target.Initialize(17);
ItemType result = list.GetItem(target, found);
if (found) result.Print(std::cout);       // prints "17"
```

> **Note on real templates**: Dale's `NodeType<ItemType>` shown later *is* a true C++ template. Templating the list class itself (`template <class T> class UnsortedType`) is the natural next step — but the textbook keeps `ItemType` concrete for clarity in chapters 3–4.

---

### 5. Array-Based Implementation

#### Visual layout

```
listData:   [ Judy ][ Bobby ][ Kit ][ Lila ][   ][   ][   ]
             0       1        2      3       4    5    6
length = 4
currentPos = -1   (used by iterator)
```

#### Class skeleton

```cpp
// UnsortedType.h  (array-based)
const int MAX_ITEMS = 100;

class UnsortedType {
public:
    UnsortedType();                          // constructor
    bool IsFull() const;
    int  GetLength() const;
    void MakeEmpty();
    ItemType GetItem(ItemType item, bool& found);
    void PutItem(ItemType item);
    void DeleteItem(ItemType item);
    void ResetList();
    ItemType GetNextItem();
private:
    int length;
    ItemType info[MAX_ITEMS];
    int currentPos;
};
```

#### Constructor

- A **class constructor** is implicitly invoked when an object is created.
- Used to initialize members and allocate resources.
- For the array-based list, the constructor just sets `length = 0` (memory is already statically reserved).

```cpp
UnsortedType::UnsortedType() { length = 0; }
```

**Constructor rules (slide 10):**
1. No return type, no return value.
2. A class may have several constructors — chosen by parameter count/type (overloading).
3. Constructor parameters are passed in the declaration: `SomeClass obj(p1, p2);`
4. The parameter-less constructor is the **default constructor**.
5. A class **must** have a default constructor to declare an *array* of objects of that type.

#### Observers

`IsFull` and `GetLength` are trivial.

```cpp
bool UnsortedType::IsFull() const   { return length == MAX_ITEMS; }
int  UnsortedType::GetLength() const{ return length; }
```

`GetItem` is a **linear search** that uses `ComparedTo`:

```cpp
ItemType UnsortedType::GetItem(ItemType item, bool& found) {
    bool moreToSearch = (length > 0);
    int  location     = 0;
    found = false;
    while (moreToSearch && !found) {
        if (info[location].ComparedTo(item) == EQUAL) {
            found = true;
            item  = info[location];                 // return a copy
        } else {
            location++;
            moreToSearch = (location < length);
        }
    }
    return item;
}
```

#### Transformer: `PutItem` — O(1)

Just append at the end and bump `length`. Order doesn't matter, so we don't search.

```cpp
void UnsortedType::PutItem(ItemType item) {
    info[length] = item;
    length++;
}
```

```
Before: [Judy][Bobby][Kit][   ][   ]   length = 3
PutItem(Lila)
After : [Judy][Bobby][Kit][Lila][   ]  length = 4
```

#### Transformer: `DeleteItem` — two strategies

Linear search to find the item, then remove. Removing the *last* item is just `length--`. For an interior item, the slides give two choices:

| Strategy | What it does | Cost |
|---------|--------------|------|
| **Move Up** | Shift every element after the deletion point left by one | O(N) per delete |
| **Swap with last** | Copy the last item into the deleted slot, then `length--` | **O(1)** |

Because the list is *unsorted*, the swap trick is legal — order doesn't matter:

```
Delete Bobby (move-up):
[Judy][Bobby][Kit][Lila]  ->  [Judy][Kit][Lila][   ]

Delete Bobby (swap-with-last):
[Judy][Bobby][Kit][Lila]  ->  [Judy][Lila][Kit][   ]   // cheaper!
```

```cpp
void UnsortedType::DeleteItem(ItemType item) {
    int location = 0;
    while (info[location].ComparedTo(item) != EQUAL) location++;
    info[location] = info[length - 1];   // swap-with-last
    length--;
}
```

#### Iterators

The field `currentPos` tracks where the iterator is. `ResetList` parks it at the *predecessor* of the first item — for an array, that's index `-1`.

```cpp
void     UnsortedType::ResetList()    { currentPos = -1; }
ItemType UnsortedType::GetNextItem()  { currentPos++; return info[currentPos]; }
```

Client usage:

```cpp
list.ResetList();
for (int i = 0; i < list.GetLength(); i++) {
    ItemType x = list.GetNextItem();
    x.Print();
}
```

---

### 6. Pointers & Dynamic Memory (Prep for Linked List)

#### Pointers

- A **pointer variable** holds the memory address of another variable.
- Declared with `*`: `int* intPointer;`
- **Address-of `&`**: `intPointer = &alpha;`
- **Dereference `*`**: `*intPointer = 25;` writes through the pointer.

```cpp
int alpha = 10;
int* p   = &alpha;     //  p ---> [10]
*p       = 25;         //  alpha is now 25
```

#### Dynamic allocation — `new` / `delete`

- **Dynamic allocation** = allocating memory at *run time* (vs. static at compile time).
- New variables live on the **heap** (a.k.a. free store).
- `new` returns a pointer; if memory is exhausted, it throws `std::bad_alloc` (older code returned `NULL`).
- Memory must be freed manually with `delete`.

```cpp
int* ptr = new int;     // allocate one int on the heap
*ptr     = 42;
delete ptr;             // free it (C++ has no garbage collector!)
ptr      = nullptr;     // good hygiene
```

#### Memory leaks (slide 21–25)

A **memory leak** is dynamically-allocated memory that is never freed. Memory that exists but can no longer be reached is called **garbage**.

```cpp
float* money   = new float;   // money   ---> [ ? ]
*money         = 33.46;       // money   ---> [33.46]
float* myMoney = new float;   // myMoney ---> [ ? ]

*myMoney = *money;            // copies the VALUE; both cells still exist
myMoney  = money;             // now myMoney points to money's cell
                              // myMoney's ORIGINAL cell is unreachable -> LEAK
```

```
After the leak:
   money   ----v
              [33.46]
   myMoney ----^

   [ ? ]   <-- unreachable garbage (memory leak)
```

#### Arrow operator

See **Reference: Pointers and the `->` operator** at the top of these notes for the full rule (`.` vs `->`, pointer vs object).

In linked-list code, `->` almost always means "follow this node pointer, then use a field":

```cpp
location->info = item;     // equivalent to (*location).info = item
location->next = listData; // wire the chain
tail->next = newNode;      // tail points at a node; update THAT node's next
```

---

### 7. Linked-List-Based Implementation

#### Simpler intro example (head + tail, append, prepend, search, insert-after, remove-after, print)

Before the full `UnsortedType` ADT below, this minimal example shows the core pointer wiring with plain `int` data. It uses **both `head` and `tail`** so `Append` is O(1) and preserves insertion order. It also includes `Prepend` (insert at head), which matches Dale's head-insertion style.

`InsertNodeAfter(currentNode, newNode)` handles 3 insertion scenarios:
1. **Insert as first node**: if `head == nullptr`, set both `head` and `tail` to `newNode`.
2. **Insert after tail**: if `currentNode == tail`, wire `tail->next` to `newNode` and move `tail`.
3. **Insert in middle**: wire `newNode->next` to `currentNode->next`, then `currentNode->next` to `newNode`.

`RemoveNodeAfter(currentNode)` handles 2 removal scenarios:
1. **Remove head**: if `currentNode == nullptr`, advance `head`, `delete` the old head; if the list is now empty, set `tail = nullptr`.
2. **Remove node after `currentNode`**: skip over `currentNode->next`, `delete` it; if that was the last node, set `tail = currentNode`.

`currentNode` is a pointer to an existing node. Pass **`nullptr`** to remove the head.

`currentNode` can also be `nullptr` when inserting into an empty list (`InsertNodeAfter` only).

```cpp
#include <iostream>

// 1. The Node Structure
class SinglyLinkedNode {
public:
   int data;
   SinglyLinkedNode* next;

   SinglyLinkedNode(int initialData) {
      data = initialData;
      next = nullptr;
   }
};

// 2. The Linked List Class
class SinglyLinkedList {
private:
   SinglyLinkedNode* head;
   SinglyLinkedNode* tail;

public:
   // Constructor: Sets up our empty list
   SinglyLinkedList() {
      head = nullptr;
      tail = nullptr;
   }

   // The high-level function you call to add a number
   void Append(int item) {
      AppendNode(new SinglyLinkedNode(item));
   }

   // The low-level function that wires the pointers together
   void AppendNode(SinglyLinkedNode* newNode) {
      if (head == nullptr) { // Check if list is empty
         head = newNode;
         tail = newNode;
      }
      else { // If list already has items
         tail->next = newNode;
         tail = newNode;
      }
   }

   // The high-level function you call to add a number at the front
   void Prepend(int item) {
      PrependNode(new SinglyLinkedNode(item));
   }

   // The low-level function that wires the pointers at the front
   void PrependNode(SinglyLinkedNode* newNode) {
      if (head == nullptr) {
         head = newNode;
         tail = newNode;
      }
      else {
         newNode->next = head;
         head = newNode;
      }
   }

   // Search for the first node whose data matches dataValue
   SinglyLinkedNode* Search(int dataValue) const {
      SinglyLinkedNode* currentNode = head;
      while (currentNode) {
         if (currentNode->data == dataValue) {
            return currentNode;
         }
         currentNode = currentNode->next;
      }
      return nullptr;
   }

   void InsertNodeAfter(SinglyLinkedNode* currentNode,
      SinglyLinkedNode* newNode) {
      if (head == nullptr) {
         head = newNode;
         tail = newNode;
      }
      else if (currentNode == tail) {
         tail->next = newNode;
         tail = newNode;
      }
      else {
         newNode->next = currentNode->next;
         currentNode->next = newNode;
      }
   }

   void RemoveNodeAfter(SinglyLinkedNode* currentNode) {
      if (currentNode == nullptr) {
         // Special case: remove head
         SinglyLinkedNode* nodeToRemove = head;
         head = head->next;
         delete nodeToRemove;

         if (head == nullptr) {
            tail = nullptr; // Last item was removed
         }
      }
      else if (currentNode->next) {
         SinglyLinkedNode* nodeToRemove = currentNode->next;
         SinglyLinkedNode* succeedingNode = nodeToRemove->next;
         currentNode->next = succeedingNode;
         delete nodeToRemove;

         if (succeedingNode == nullptr) {
            tail = currentNode; // Last item was removed
         }
      }
   }

   // Helper function to print the list so we can see it working
   void Print() const {
      SinglyLinkedNode* temp = head;
      while (temp != nullptr) {
         std::cout << temp->data << " -> ";
         temp = temp->next;
      }
      std::cout << "null\n";
   }
};

// 3. Execution
int main() {
    SinglyLinkedList list;

    std::cout << "Appending 95...\n";
    list.Append(95);
    list.Print();

    std::cout << "\nAppending 42...\n";
    list.Append(42);
    list.Print();

    std::cout << "\nPrepending 13...\n";
    list.Prepend(13);
    list.Print();

    std::cout << "\nSearching for 95...\n";
    SinglyLinkedNode* found = list.Search(95);
    if (found) {
       std::cout << "Found node with data = " << found->data << "\n";
    } else {
       std::cout << "95 not found\n";
    }

    if (found) {
       std::cout << "\nInserting 77 after 95...\n";
       list.InsertNodeAfter(found, new SinglyLinkedNode(77));
       list.Print();
    }

    if (found) {
       std::cout << "\nRemoving node after 95 (77)...\n";
       list.RemoveNodeAfter(found);
       list.Print();
    }

    std::cout << "\nRemoving head (13)...\n";
    list.RemoveNodeAfter(nullptr);
    list.Print();

    found = list.Search(95);
    if (found) {
       std::cout << "\nRemoving node after 95 (42)...\n";
       list.RemoveNodeAfter(found);
       list.Print();
    }

    return 0;
}
```

Output:

```
Appending 95...
95 -> null

Appending 42...
95 -> 42 -> null

Prepending 13...
13 -> 95 -> 42 -> null

Searching for 95...
Found node with data = 95

Inserting 77 after 95...
13 -> 95 -> 77 -> 42 -> null

Removing node after 95 (77)...
13 -> 95 -> 42 -> null

Removing head (13)...
95 -> 42 -> null

Removing node after 95 (42)...
95 -> null
```

| This example | Dale `UnsortedType` (below) |
|---|---|
| `int` only | Generic `ItemType` |
| `Append` at **tail** | `PutItem` at **head** |
| `head` + `tail` | `listData` (head only) |
| `Append` / `Prepend` / `Search` / `InsertNodeAfter` / `RemoveNodeAfter` / `Print` only | Full ADT + destructor / `delete` |

#### Clarification: `head` / `tail` vs `next`

**`head` and `tail` do not have `next`.** Only **nodes** do.

There are two different kinds of things in play:

| Kind | What it is | Has `next`? |
|------|------------|-------------|
| **`SinglyLinkedList`** | The list object | No — it only stores pointer *variables* |
| **`SinglyLinkedNode`** | A node on the heap | Yes — each node has `data` and `next` |

```cpp
// On the list object — just bookmarks (addresses), not nodes:
SinglyLinkedNode* head;
SinglyLinkedNode* tail;

// On each node — the actual chain links:
SinglyLinkedNode* next;
```

After `Append(95)` then `Append(42)`:

```
SinglyLinkedList object          nodes on the heap
┌─────────────────┐
│ head ───────────────► [ data: 95 | next ────┐ ]
│ tail ───────────────────────────────────────┼──► [ data: 42 | next: null ]
└─────────────────┘                           │
                                              └──────────────►
```

- **`head`** — where the list starts (traverse, print, search).
- **`tail`** — shortcut to the last node so append is O(1) without walking the whole chain.
- **`next`** — lives inside each node; `tail->next` means “the `next` field of the node `tail` points at,” not “tail’s next.”

When appending to a non-empty list, both lines are required:

```cpp
tail->next = newNode;   // link old last node → new node  (update a node in the chain)
tail = newNode;         // move tail bookmark to new last (update the list object)
```

| If you only do… | What goes wrong |
|-----------------|-----------------|
| `tail = newNode` only | Old last node still has `next = null`; new node is not connected. |
| `tail->next = newNode` only | Chain is linked, but `tail` still points at the old node; next append breaks. |

On an **empty** list there is no old last node, so you set both bookmarks directly: `head = newNode; tail = newNode;`

---

#### Doubly-linked list

A **doubly-linked list** is a data structure for implementing a list ADT, where each node has **data**, a pointer to the **next** node, and a pointer to the **previous** node. The list structure typically has pointers to the first node and the last node. The doubly-linked list's first node is called the **head**, and the last node the **tail**.

A doubly-linked list is similar to a singly-linked list, but instead of using a single pointer to the next node in the list, each node has a pointer to the next **and** previous nodes. Such a list is called "doubly-linked" because each node has two pointers, or "links". A doubly-linked list is a type of **positional list**: a list where elements contain pointers to the next and/or previous elements in the list.

```
DoublyLinkedList object          nodes on the heap
┌─────────────────┐
│ head ───────────────►  ┌─────────┐      ┌─────────┐      ┌─────────┐      ┌─────────┐
│                      │ data 77 │      │ data 18 │      │ data 61 │      │ data 54 │
│ tail ──────────────────────────────────────────────────────────────────────────────►│
└─────────────────┘      │ next ───┼─────►│ next ───┼─────►│ next ───┼─────►│ next: null
                         │ previous: null │ previous ◄─┼─────┤ previous ◄─┼─────┤ previous ◄─┼─────┤
                         └─────────┘      └─────────┘      └─────────┘      └─────────┘
```

- **`head`** — bookmark to the first node (`77`); that node's `previous` is `null`.
- **`tail`** — bookmark to the last node (`54`); that node's `next` is `null`.
- **`next` / `previous`** — live inside each node; every interior node points both forward and backward.

| | **Singly-linked** | **Doubly-linked** |
|---|---|---|
| Links per node | `next` only | `next` **and** `previous` |
| List bookmarks | often `head` (sometimes `head` + `tail`) | typically `head` **and** `tail` |
| Walk forward | yes | yes |
| Walk backward | no (must restart from head) | yes (follow `previous`) |
| Delete a known node | need the **predecessor** (inchworm walk) | update `previous` and `next` on neighbors directly |

> Dale's `UnsortedType` / `SortedType` in chapters 3–4 use **singly-linked** lists. Doubly-linked lists are a common alternative when you need efficient deletion or backward traversal; more on that below.

#### Simpler intro example (head + tail, append, prepend, search, insert-after)

Same pattern as the singly-linked intro above: plain `int` data, `head` + `tail` bookmarks, and separate high-level (`Append` / `Prepend`) vs low-level (`AppendNode` / `PrependNode`) wiring functions. The difference is that every link update must set **both** directions — when you attach a new node, its `previous` and the neighbor's `next`/`previous` must all be updated.

```cpp
#include <iostream>

// 1. The Node Structure
class DoublyLinkedNode {
public:
   int data;
   DoublyLinkedNode* next;
   DoublyLinkedNode* previous;

   DoublyLinkedNode(int initialData) {
      data = initialData;
      next = nullptr;
      previous = nullptr;
   }
};

// 2. The Linked List Class
class DoublyLinkedList {
private:
   DoublyLinkedNode* head;
   DoublyLinkedNode* tail;

public:
   DoublyLinkedList() {
      head = nullptr;
      tail = nullptr;
   }

   void Append(int item) {
      AppendNode(new DoublyLinkedNode(item));
   }

   void AppendNode(DoublyLinkedNode* newNode) {
      if (head == nullptr) {
         head = newNode;
         tail = newNode;
      }
      else {
         tail->next = newNode;
         newNode->previous = tail;
         tail = newNode;
      }
   }

   void Prepend(int item) {
      DoublyLinkedNode* newNode = new DoublyLinkedNode(item);
      PrependNode(newNode);
   }

   void PrependNode(DoublyLinkedNode* newNode) {
      if (head == nullptr) {
         head = newNode;
         tail = newNode;
      }
      else {
         newNode->next = head;
         head->previous = newNode;
         head = newNode;
      }
   }

   // Search for the first node whose data matches dataValue
   DoublyLinkedNode* Search(int dataValue) const {
      DoublyLinkedNode* currentNode = head;
      while (currentNode) {
         if (currentNode->data == dataValue) {
            return currentNode;
         }
         currentNode = currentNode->next;
      }

      return nullptr;
   }

   void InsertNodeAfter(DoublyLinkedNode* currentNode,
      DoublyLinkedNode* newNode) {
      if (head == nullptr) {
         head = newNode;
         tail = newNode;
      }
      else if (currentNode == tail) {
         tail->next = newNode;
         newNode->previous = tail;
         tail = newNode;
      }
      else {
         DoublyLinkedNode* successor = currentNode->next;
         newNode->next = successor;
         newNode->previous = currentNode;
         currentNode->next = newNode;
         successor->previous = newNode;
      }
   }
};
```

**Append to a non-empty list** — three updates (singly-linked only needed two):

```cpp
tail->next = newNode;        // old last node → new node
newNode->previous = tail;      // new node ← old last node
tail = newNode;                // move tail bookmark
```

**Prepend to a non-empty list** — same idea at the front:

```cpp
newNode->next = head;          // new node → old first node
head->previous = newNode;      // old first node ← new node
head = newNode;                // move head bookmark
```

| If you only wire `next`… | What goes wrong |
|--------------------------|-----------------|
| Append without `newNode->previous = tail` | Forward chain works, but you cannot walk backward from the new node. |
| Prepend without `head->previous = newNode` | Forward chain works, but the old head's `previous` still points at nothing useful. |

More methods (remove, print, etc.) to follow.

---

#### Node structure

A **node** has two fields: `info` (the data) and `next` (a pointer to the next node).

#### Required supporting types (`ItemType` + `NodeType`)

`UnsortedType` depends on:
1. an `ItemType` with `ComparedTo`, `Initialize`, and `Print`,
2. a node template that stores one `ItemType` plus a link.

```cpp
enum RelationType { LESS, EQUAL, GREATER };

class ItemType {
public:
    ItemType() : value(0) {}

    RelationType ComparedTo(ItemType other) const {
        if (value < other.value) return LESS;
        if (value > other.value) return GREATER;
        return EQUAL;
    }

    void Initialize(int number) { value = number; }
    void Print(std::ostream& out) const { out << value; }

private:
    int value;
};
```

```cpp
template <class ItemType>
struct NodeType {
    ItemType        info;
    NodeType<ItemType>* next;
};
```

```
   listData
      |
      v
    +------+------+    +------+------+    +------+------+
    | Kit  |  *---+--> | Lila |  *---+--> | Bobby| NULL |
    +------+------+    +------+------+    +------+------+
       info  next         info  next         info  next
```

#### Class skeleton

```cpp
class UnsortedType {
public:
    UnsortedType();                          // constructor
    ~UnsortedType();                         // destructor
    bool IsFull() const;
    int  GetLength() const;
    void MakeEmpty();
    ItemType GetItem(ItemType item, bool& found);
    void PutItem(ItemType item);
    void DeleteItem(ItemType item);
    void ResetList();
    ItemType GetNextItem();
private:
    NodeType<ItemType>* listData;            // head pointer
    int length;
    NodeType<ItemType>* currentPos;          // iterator cursor
};
```

#### Constructor

Set head to `NULL` and length to 0:

```cpp
UnsortedType::UnsortedType() { length = 0; listData = NULL; }
```

#### `IsFull` — try/catch with `new`

A linked list has no fixed capacity; the only failure mode is running out of heap memory. We attempt to allocate one node and catch `bad_alloc`.

```cpp
bool UnsortedType::IsFull() const {
    NodeType<ItemType>* location;
    try {
        location = new NodeType<ItemType>;
        delete location;
        return false;                 // allocation succeeded
    }
    catch (std::bad_alloc exception) {
        return true;                  // heap exhausted
    }
}
```

#### `PutItem` — insert at the head (O(1))

For an *unsorted* linked list, the cheapest spot to insert is at the head.

```cpp
void UnsortedType::PutItem(ItemType item) {
    NodeType<ItemType>* location;
    location       = new NodeType<ItemType>;   // 1. new node
    location->info = item;                     // 2. fill info
    location->next = listData;                 // 3. point to old head
    listData       = location;                 // 4. head -> new node
    length++;
}
```

**Order matters!** If step 4 ran before step 3, we'd overwrite `listData` and lose access to the rest of the chain — a giant memory leak.

```
Before:  listData -> [Kit | *] -> [Lila | NULL]
PutItem(Bobby):
  Step 1-2:  location -> [Bobby | ? ]
  Step 3  :  location -> [Bobby | *] -> [Kit | *] -> [Lila | NULL]
  Step 4  :  listData -> [Bobby | *] -> [Kit | *] -> [Lila | NULL]
```

#### `GetItem` — linear search, just with pointers

```cpp
ItemType UnsortedType::GetItem(ItemType item, bool& found) {
    NodeType<ItemType>* location = listData;
    found = false;
    while (location != NULL && !found) {
        if (location->info.ComparedTo(item) == EQUAL) {
            found = true;
            item  = location->info;
        } else {
            location = location->next;
        }
    }
    return item;
}
```

#### `DeleteItem` — must update the predecessor's `next`

To unlink a node, the *previous* node's `next` pointer must skip over it. The slide's algorithm peeks one node ahead via `location->next->info`:

```cpp
void UnsortedType::DeleteItem(ItemType item) {
    NodeType<ItemType>* location = listData;
    NodeType<ItemType>* tempLocation;

    // Special case: item is at the head
    if (item.ComparedTo(listData->info) == EQUAL) {
        tempLocation = listData;
        listData     = listData->next;
    } else {
        while (location->next->info.ComparedTo(item) != EQUAL)
            location = location->next;
        tempLocation     = location->next;
        location->next   = (location->next)->next;
    }
    delete tempLocation;        // free the unlinked node
    length--;
}
```

```
Before:  listData -> [Kate | *] -> [Lila | *] -> [Bobby | NULL]
DeleteItem(Lila):
         listData -> [Kate | *]---------------> [Bobby | NULL]
                            (Lila's node delete'd)
```

#### Iterator (linked list)

`currentPos` is now a node pointer, not an index. `ResetList` sets it to `NULL`, and `GetNextItem` interprets `NULL` as "start at the head."

```cpp
void UnsortedType::ResetList() { currentPos = NULL; }

ItemType UnsortedType::GetNextItem() {
    if (currentPos == NULL) currentPos = listData;
    else                    currentPos = currentPos->next;
    return currentPos->info;
}
```

#### `MakeEmpty` — walk the chain, free every node (O(N))

```cpp
void UnsortedType::MakeEmpty() {
    NodeType<ItemType>* tempPtr;
    while (listData != NULL) {
        tempPtr  = listData;
        listData = listData->next;
        delete tempPtr;
    }
    length = 0;
}
```

#### Destructor — prevent leaks when the list dies

When the `UnsortedType` object leaves scope, its memory is reclaimed *but the nodes it points to are not*. The destructor must walk the list and `delete` each node.

```cpp
UnsortedType::~UnsortedType() { MakeEmpty(); }
```

#### Full combined implementation file (linked `UnsortedType`)

Now that each component is explained separately, here is the same linked-list `UnsortedType` assembled into one implementation file.

```cpp
// UnsortedType_linked.cpp
#include <iostream>
#include <new>       // std::bad_alloc

enum RelationType { LESS, EQUAL, GREATER };

class ItemType {
public:
    ItemType() : value(0) {}

    RelationType ComparedTo(ItemType other) const {
        if (value < other.value) return LESS;
        if (value > other.value) return GREATER;
        return EQUAL;
    }

    void Initialize(int number) { value = number; }
    void Print(std::ostream& out) const { out << value; }

private:
    int value;
};

template <class ItemType>
struct NodeType {
    ItemType        info;
    NodeType<ItemType>* next;
};

class UnsortedType {
public:
    UnsortedType();
    ~UnsortedType();

    bool IsFull() const;
    int  GetLength() const { return length; }
    void MakeEmpty();

    ItemType GetItem(ItemType item, bool& found);
    void PutItem(ItemType item);
    void DeleteItem(ItemType item);

    void ResetList();
    ItemType GetNextItem();

private:
    NodeType<ItemType>* listData;   // head pointer
    int length;
    NodeType<ItemType>* currentPos; // iterator cursor
};

UnsortedType::UnsortedType() {
    length = 0;
    listData = NULL;
    currentPos = NULL;
}

UnsortedType::~UnsortedType() {
    MakeEmpty();
}

bool UnsortedType::IsFull() const {
    NodeType<ItemType>* location;
    try {
        location = new NodeType<ItemType>;
        delete location;
        return false;
    } catch (std::bad_alloc exception) {
        return true;
    }
}

void UnsortedType::PutItem(ItemType item) {
    NodeType<ItemType>* location;
    location = new NodeType<ItemType>;
    location->info = item;
    location->next = listData;
    listData = location;
    length++;
}

ItemType UnsortedType::GetItem(ItemType item, bool& found) {
    NodeType<ItemType>* location = listData;
    found = false;
    while (location != NULL && !found) {
        if (location->info.ComparedTo(item) == EQUAL) {
            found = true;
            item = location->info;
        } else {
            location = location->next;
        }
    }
    return item;
}

void UnsortedType::DeleteItem(ItemType item) {
    NodeType<ItemType>* location = listData;
    NodeType<ItemType>* tempLocation;

    // Special case: item at head
    if (item.ComparedTo(listData->info) == EQUAL) {
        tempLocation = listData;
        listData = listData->next;
    } else {
        while (location->next->info.ComparedTo(item) != EQUAL) {
            location = location->next;
        }
        tempLocation = location->next;
        location->next = (location->next)->next;
    }
    delete tempLocation;
    length--;
}

void UnsortedType::ResetList() {
    currentPos = NULL;
}

ItemType UnsortedType::GetNextItem() {
    if (currentPos == NULL) currentPos = listData;
    else                    currentPos = currentPos->next;
    return currentPos->info;
}

void UnsortedType::MakeEmpty() {
    NodeType<ItemType>* tempPtr;
    while (listData != NULL) {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    length = 0;
    currentPos = NULL;
}

int main() {
    UnsortedType list;

    ItemType a, b, c;
    a.Initialize(10);
    b.Initialize(25);
    c.Initialize(17);

    list.PutItem(a);
    list.PutItem(b);
    list.PutItem(c);

    bool found = false;
    ItemType target;
    target.Initialize(25);
    ItemType result = list.GetItem(target, found);

    std::cout << "Found 25? " << (found ? "yes" : "no") << "\n";
    if (found) {
        std::cout << "Matched item: ";
        result.Print(std::cout);
        std::cout << "\n";
    }

    return 0;
}
```

#### Lifetime of a variable

| Kind | Lives for |
|------|-----------|
| **Global** | Entire program execution |
| **Local** | The block in which it's declared |
| **Dynamically allocated** | From `new` until `delete` |
| **`static` local** | Entire program (but only visible in its block) |

---

### 8. Comparing the Two Unsorted-List Implementations

| Operation | Array-based | Linked List-based |
|-----------|-------------|-------------------|
| Class Constructor | O(1) | O(1) |
| Destructor | not needed (no heap memory) | **O(N)** — must free every node |
| `MakeEmpty` | O(1) | O(N) |
| `IsFull` | O(1) | O(1) |
| `GetLength` | O(1) | O(1) |
| `ResetList` | O(1) | O(1) |
| `GetNextItem` | O(1) | O(1) |
| `PutItem` | **O(1)** (append) | **O(1)** (insert at head) |
| `GetItem` | O(N) | O(N) |
| `DeleteItem` | O(N) (search) + O(1) swap-with-last | O(N) (search) + O(1) unlink |

- **Memory**: array reserves `MAX_ITEMS` whether full or not; linked list grows/shrinks exactly with the data.
- **Bounded vs. unbounded**: array is bounded by `MAX_ITEMS`; linked list is bounded only by heap size.

---

## Chapter 4: ADT Sorted List

The interface is **identical** to Unsorted List — only the *invariant* changes:

> After every operation, the list is sorted in ascending order by key.

This invariant changes how `PutItem`, `DeleteItem`, and `GetItem` are implemented.

### 1. Sorted List — Pre/Postconditions

```
PutItem
   Pre : list is not full and item is not in list, list is sorted.
   Post: item is in the list, list is still sorted, length incremented.

DeleteItem
   Pre : item is in the list, list is sorted.
   Post: item is no longer in the list, list is still sorted.

GetNextItem (iterator)
   Post: returns the next item in KEY ORDER.
```

The application level (the *client*) doesn't change at all — same calls, same return types. They simply get items back in sorted order.

---

### 2. Array-Based Sorted List

#### `PutItem` — find position, shift right, insert (O(N))

```
Original: [Alex][Chris][John][Kit][    ]    length = 4
PutItem(Becca)

Step 1 — linear search for first item > Becca:
                ^ stop here (Chris)

Step 2 — shift Chris, John, Kit right by one:
          [Alex][    ][Chris][John][Kit]

Step 3 — insert Becca:
          [Alex][Becca][Chris][John][Kit]   length = 5
```

```cpp
void SortedType::PutItem(ItemType item) {
    bool moreToSearch;
    int  location = 0;

    moreToSearch = (location < length);
    while (moreToSearch) {
        switch (item.ComparedTo(info[location])) {
            case LESS    : moreToSearch = false;            break;
            case GREATER : location++;
                           moreToSearch = (location < length); break;
            // EQUAL forbidden by precondition
        }
    }
    // Shift everything from `location` rightward by one
    for (int i = length; i > location; i--)
        info[i] = info[i - 1];
    info[location] = item;
    length++;
}
```

#### `DeleteItem` — linear search, then shift left (O(N))

```
Original: [Alex][Becca][Chris][John][Kit]
DeleteItem(Chris)

Step 1 — find Chris (index 2).
Step 2 — shift John, Kit left by one (overwriting Chris):
          [Alex][Becca][John][Kit][    ]
Step 3 — length--;
```

```cpp
void SortedType::DeleteItem(ItemType item) {
    int location = 0;
    while (info[location].ComparedTo(item) != EQUAL) location++;
    for (int i = location; i < length - 1; i++)
        info[i] = info[i + 1];
    length--;
}
```

> Note we **cannot** use the swap-with-last trick from the unsorted list — it would break the sort invariant.

#### `GetItem` — two improvements over Unsorted List

**Improvement 1: early termination.** Because the list is sorted, we can stop as soon as we pass where the item would be.

```
List: [Alice][Bob][Diane][Ed]   search for "Chris"
  Alice  < Chris -> keep going
  Bob    < Chris -> keep going
  Diane  > Chris -> STOP, not in list
```

```cpp
ItemType SortedType::GetItem(ItemType item, bool& found) {
    bool moreToSearch = (length > 0);
    int  location     = 0;
    found = false;
    while (moreToSearch && !found) {
        switch (item.ComparedTo(info[location])) {
            case LESS    : moreToSearch = false; break;    // early exit
            case GREATER : location++;
                           moreToSearch = (location < length); break;
            case EQUAL   : found = true; item = info[location]; break;
        }
    }
    return item;
}
```

**Improvement 2: binary search — O(log₂ N).**

#### Binary Search

A search that **halves** the remaining search space each iteration. Requires (a) sorted data and (b) random access — so it works on the array-based list, **not** on a linked list.

```cpp
ItemType SortedType::BinarySearch(ItemType item, bool& found) {
    int first = 0;
    int last  = length - 1;
    int midPoint;
    found = false;

    while (first <= last && !found) {
        midPoint = (first + last) / 2;
        switch (item.ComparedTo(info[midPoint])) {
            case LESS    : last  = midPoint - 1; break;
            case GREATER : first = midPoint + 1; break;
            case EQUAL   : found = true; item = info[midPoint]; break;
        }
    }
    return item;
}
```

**Trace — searching for `bat` in `[ant][cat][chicken][cow][dog][fish][snake]`:**

```
Iter 1: first=0 last=6 mid=3 (dog)     bat < dog     -> last  = 2
Iter 2: first=0 last=2 mid=1 (cat)     bat < cat     -> last  = 0
Iter 3: first=0 last=0 mid=0 (ant)     bat > ant     -> first = 1
Iter 4: first=1 last=0  -> first > last, loop exits, found = false
```

- Linear search may still beat binary search for **small N (< ~20)** due to per-iteration overhead.

---

### 3. Dynamically-Allocated Array-Based Sorted List

Lets the client decide capacity at run time. The fixed array is replaced by a heap-allocated `ItemType*`.

```cpp
class SortedType {
public:
    SortedType();              // default: capacity 500
    SortedType(int max);       // parameterized
    ~SortedType();             // frees the array
    bool IsFull() const;       // length == maxItems
    // ...
private:
    int       length;
    ItemType* info;            // heap-allocated array
    int       maxItems;
    int       currentPos;
};

SortedType::SortedType()         { length = 0; maxItems = 500; info = new ItemType[500]; }
SortedType::SortedType(int max)  { length = 0; maxItems = max; info = new ItemType[max]; }
SortedType::~SortedType()        { delete [] info; }            // note: [] for arrays
bool SortedType::IsFull() const  { return length == maxItems; }
```

```
   info ----> [Alex][Becca][Chris][John][Kit][   ]...[   ]
              ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
              maxItems slots on the heap (set at construction)
```

Visually similar to the static array, but the array lives on the heap and its size is chosen at run time. The list remains **unbounded from the client's perspective** if we ever grow it (Dale leaves growing as an exercise).

---

### 4. Linked-List-Based Sorted List

Two changes drive everything:

1. `GetItem` can use the *early-termination* optimization but **cannot** use binary search (no random access).
2. `PutItem` and `DeleteItem` must update node links to keep the order.

#### `GetItem` (linked, sorted)

```cpp
ItemType SortedType::GetItem(ItemType item, bool& found) {
    NodeType<ItemType>* location = listData;
    bool moreToSearch = (location != NULL);
    found = false;
    while (moreToSearch && !found) {
        switch (item.ComparedTo(location->info)) {
            case LESS    : moreToSearch = false; break;        // early exit
            case GREATER : location = location->next;
                           moreToSearch = (location != NULL); break;
            case EQUAL   : found = true; item = location->info; break;
        }
    }
    return item;
}
```

#### `PutItem` — the "inchworm" two-pointer walk

To insert `Becca` between `Alex` and `Chris`, we need to make `Alex.next` point to the new `Becca` node. But singly-linked nodes only know their *successor*. Solution: walk **two** pointers in lock-step — `predLoc` always one step behind `location`.

```
Initial:    predLoc=NULL  location=listData

Step 1: predLoc <- location          (predLoc catches up)
Step 2: location <- location->next   (location moves forward)

  Together this is the "inchworm" — predLoc and location keep one
  node apart as they crawl down the list.
```

```cpp
void SortedType::PutItem(ItemType item) {
    NodeType<ItemType>* newNode;
    NodeType<ItemType>* predLoc;
    NodeType<ItemType>* location;
    bool moreToSearch;

    location     = listData;
    predLoc      = NULL;
    moreToSearch = (location != NULL);

    // Find insertion point: stop at first node whose info is > item
    while (moreToSearch) {
        switch (location->info.ComparedTo(item)) {
            case LESS    : predLoc = location;
                           location = location->next;
                           moreToSearch = (location != NULL); break;
            case GREATER : moreToSearch = false; break;
        }
    }

    // Build the new node and splice it in
    newNode       = new NodeType<ItemType>;
    newNode->info = item;
    newNode->next = location;

    if (predLoc == NULL) listData       = newNode;    // insert at head
    else                 predLoc->next  = newNode;
    length++;
}
```

**Four insertion cases** (figure 4.10):

```
(a) Insert Alex at the BEGINNING (predLoc == NULL):
      Before: listData -> [Chris]->[John]->[Kit]->NULL
      After : listData -> [Alex] ->[Chris]->[John]->[Kit]->NULL

(b) Insert Kit in the MIDDLE:
      Before: listData -> [Alex]->[Chris]->[John]->[Kate]->NULL
      After : listData -> [Alex]->[Chris]->[John]->[Kit]->[Kate]->NULL
                                                ^ predLoc

(c) Insert Kate at the END (location == NULL):
      Before: listData -> [Alex]->[Chris]->[John]->[Kit]->NULL
      After : listData -> [Alex]->[Chris]->[John]->[Kit]->[Kate]->NULL

(d) Insert John into an EMPTY list (listData == NULL):
      Before: listData -> NULL
      After : listData -> [John]->NULL
```

#### `DeleteItem` — same "two-pointer" idea (four cases)

```cpp
void SortedType::DeleteItem(ItemType item) {
    NodeType<ItemType>* location = listData;
    NodeType<ItemType>* tempLocation;

    // Case: delete the head
    if (item.ComparedTo(listData->info) == EQUAL) {
        tempLocation = listData;
        listData     = listData->next;
    } else {
        // Walk until location->next is the target
        while (item.ComparedTo((location->next)->info) != EQUAL)
            location = location->next;
        tempLocation     = location->next;
        location->next   = (location->next)->next;
    }
    delete tempLocation;
    length--;
}
```

**Four deletion cases** (figure 4.11):

```
(a) Delete only node (David):     listData -> [David]->NULL    =>  listData -> NULL
(b) Delete first node  (Radio):   listData -> [Radio]->[Leah]->[Miriam]->NULL
                                  listData -> [Leah]->[Miriam]->NULL
(c) Delete middle node (Leah):    listData -> [Radio]->[Leah]->[Miriam]->NULL
                                  listData -> [Radio]----------->[Miriam]->NULL
(d) Delete last node   (Miriam):  listData -> [Radio]->[Leah]->[Miriam]->NULL
                                  listData -> [Radio]->[Leah]->NULL
```

---

### 5. Big-O Comparison of Sorted List Operations

| Operation | Array-based | Dyn. Array | Linked List |
|-----------|-------------|------------|-------------|
| Constructor | O(1) | O(1) | O(1) |
| Destructor | — | O(1) | **O(N)** |
| `MakeEmpty` | O(1) | O(1) | O(N) |
| `IsFull` | O(1) | O(1) | O(1) |
| `GetLength` | O(1) | O(1) | O(1) |
| `ResetList` | O(1) | O(1) | O(1) |
| `GetNextItem` | O(1) | O(1) | O(1) |
| `GetItem` (linear, early exit) | O(N) | O(N) | O(N) |
| `GetItem` (**binary search**) | **O(log N)** | **O(log N)** | not possible |
| `PutItem` | O(N) (search + shift) | O(N) | O(N) (search only, no shift) |
| `DeleteItem` | O(N) (search + shift) | O(N) | O(N) (search only, no shift) |

#### Sorted vs. Unsorted List (the punchline)

| | Unsorted | Sorted |
|---|---|---|
| `PutItem` | **O(1)** (append) | **O(N)** (must locate the right slot) |
| `GetItem` | O(N) | O(N), or **O(log N)** with binary search |
| `DeleteItem` | O(N) | O(N) |

Choose **sorted** when you read/search a lot and write rarely; choose **unsorted** when you write a lot and rarely need order.

---

### 6. Bounded vs. Unbounded ADTs

| Term | Meaning |
|------|---------|
| **Bounded ADT** | There *is* a logical upper limit on the number of items. |
| **Unbounded ADT** | No logical upper limit. |

- Static-array list ⇒ bounded by `MAX_ITEMS`.
- Linked list ⇒ unbounded (limited only by heap).
- Dynamically-allocated array ⇒ bounded at construction time, but can be made unbounded by reallocating.
- *Boundedness is an implementation detail*; clients only know about it via documentation.

---

### 7. Object-Oriented Design Methodology (Ch. 4 wrap-up)

Four steps:

1. **Brainstorming** — group generates candidate classes. *All ideas welcome*; defer critique.
2. **Filtering** — drop duplicates, merge overlap, keep classes core to the problem. Write a CRC card for each survivor.
3. **Scenarios** — walk through user interactions; assign **responsibilities** (knowledge or actions) to classes. A set of related scenarios = a **use case**.
4. **Responsibility Algorithms** — write the algorithm for each responsibility.
   - *Knowledge responsibilities*: usually just return encapsulated data.
   - *Action responsibilities*: design with top-down refinement.

---

## Key Themes Across Both Chapters

1. **Same ADT, multiple implementations** — the *interface* is fixed; the choice of array vs. linked, sorted vs. unsorted is an implementation trade-off.
2. **Trade-offs are visible in Big-O** — Unsorted `PutItem` is O(1); Sorted `PutItem` is O(N). Pick the right one for the access pattern.
3. **Random access vs. sequential access** — arrays support binary search (O(log N)); linked lists cannot.
4. **Manual memory management** — every `new` needs a `delete`; the destructor exists to prevent leaks when objects holding heap data go out of scope.
5. **Algorithm cases drive code structure** — both `PutItem` and `DeleteItem` for a sorted linked list have **four cases** (empty, head, middle, end) that must each be handled.
6. **The "inchworm" two-pointer walk** is the reusable trick for any singly-linked-list mutation that needs the predecessor.
