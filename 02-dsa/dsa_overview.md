# Data Structures & Algorithms

A concept reference with example code, organized by topic. Each section covers
the core ideas, key definitions, complexity facts, common gotchas, and C++
snippets.

> Code snippets are illustrative; some are fragments meant to highlight an idea.
> Examples that `throw` require `#include <stdexcept>`.

---

## Table of Contents

1. [Introduction to Data Structures & Algorithms](#1-introduction-to-data-structures--algorithms)
2. [Lists](#2-lists)
3. [Stacks & Queues](#3-stacks--queues)
4. [Searching & Algorithm Analysis](#4-searching--algorithm-analysis)
5. [Trees](#5-trees)
6. [Heaps & Priority Queues](#6-heaps--priority-queues)
7. [Hash Tables & Maps](#7-hash-tables--maps)
8. [Sorting Algorithms](#8-sorting-algorithms)
9. [Graphs](#9-graphs)
10. [Algorithm Design Techniques](#10-algorithm-design-techniques)
11. [Balanced Trees](#11-balanced-trees)
12. [B-Trees](#12-b-trees)
13. [Additional Topics](#13-additional-topics)
14. [Complexity Cheat Sheet](#14-complexity-cheat-sheet)
15. [Common Pitfalls](#15-common-pitfalls)

---

## 1. Introduction to Data Structures & Algorithms

### Data structures

A **data structure** organizes, stores, and defines operations on data. Common
operations: access/update, search, insert, remove.

| Structure | Description |
|-----------|-------------|
| Record | Stores named subitems (fields). |
| Array | Ordered elements, each directly accessible by positional index. |
| Linked list | Ordered items in nodes; each node holds data + pointer to the next node. |
| Binary tree | Each node has up to two children (left, right). |
| Hash table | Unordered items mapped (hashed) to positions in an array. |
| Heap | Tree where a node's key relates (≥ or ≤) to its children's keys. |
| Graph | Vertices connected by edges representing relationships. |

Choosing a structure depends on the data and the operations needed. Example:
inserting mid-sequence is cheap in a linked list (repoint a pointer) but costly
in an array (shift all higher-indexed items).

### Algorithms

An **algorithm** is a sequence of steps that solves a computational problem. A
**computational problem** specifies an input, a question about the input, and a
desired output.

```cpp
int FindMax(const int* arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; ++i)
        if (arr[i] > max) max = arr[i];
    return max;
}
```

An algorithm is **efficient** if its runtime grows no more than polynomially
with input size. **NP-complete** problems have no known efficient algorithm; if
an efficient algorithm existed for one, all NP-complete problems could be solved
efficiently. For these, aim for a good (non-optimal) solution.

### Abstract data types (ADTs)

An **ADT** is described by its operations ("insert at rear," "remove front"),
not by how it's implemented. The same ADT can be built on different underlying
structures, and users need no knowledge of the implementation.

| ADT | Description | Common underlying structures |
|-----|-------------|-------------------------------|
| List | Ordered data. | Array, linked list |
| Dynamic array | Ordered data with indexed access. | Array |
| Stack | Insert/remove at top only (LIFO). | Linked list, array |
| Queue | Insert at end, remove at front (FIFO). | Linked list, array |
| Deque | Insert/remove at both ends. | Linked list, array |
| Bag | Unordered, duplicates allowed. | Array, linked list |
| Set | Collection of distinct items. | BST, hash table |
| Priority queue | Items served by priority. | Heap |
| Dictionary (Map) | Associates keys with values. | Hash table, BST |

- **Bounded ADT:** maximum size fixed by the specification (not merely a side
  effect of using an array — a bounded ADT can even use linked nodes).
- **Unbounded ADT:** grows as needed, limited only by memory.

**Abstraction** lets users interact at a high level with internals hidden.
Knowledge of the implementation is needed only to analyze or improve efficiency.

### Object-oriented foundations

- **Encapsulation:** bundle data with the methods operating on it; restrict
  direct access (`private`, `protected`) to protect internal state.
- **Composition (*has-a*):** a class holds an instance of another and uses only
  its public interface.
- **Inheritance (*is-a*):** a subclass reuses a base class's attributes/behavior.
- **Polymorphism / virtual functions:** dynamic binding resolves which override
  runs at runtime, based on the object's actual type.

```cpp
class Engine { public: void ignite() { /* ... */ } };

class Car {                 // composition: a Car has-a Engine
    Engine engine;
public:
    void start() { engine.ignite(); }
};

class ElectricCar : public Car { /* is-a Car */ };
```

**Three viewpoints** when analyzing a structure: the **application view**
(real-world purpose), the **logical/ADT view** (operations and behavior,
independent of storage), and the **implementation view** (memory layout and
pointer mechanics).

### Algorithm efficiency

**Computational complexity** measures resources used — usually **runtime** and
**memory**. Runtime complexity `T(N)` counts constant-time operations for input
size `N`.

- **Best case:** input causing the fewest operations.
- **Worst case:** input causing the most operations.
- Input size `N` always stays a variable (otherwise every best case would be
  `N = 0`).

**Space complexity** `S(N)` is the number of fixed-size memory units used.
**Auxiliary space complexity** excludes the input data. Example: duplicating an
array is `S(N) = 2N + k`; finding a max is `S(N) = N + k` but auxiliary `k`.

### Memory, pointers & copy semantics

Linked structures allocate nodes on the **heap** with `new`. The compiler only
frees the stack pointer, so a **user-defined destructor** must `delete` heap
resources to avoid **memory leaks**. The clearest signal a class needs a
destructor is that it allocates with `new`.

- **Shallow copy:** copies the pointer value only — both objects share one heap
  block (risking double-free).
- **Deep copy:** allocates a new block and copies the underlying data — each
  object owns its memory.

```cpp
class Buffer {
    int* data;
    int size;
public:
    Buffer(int s) : size(s) { data = new int[size]; }
    ~Buffer() { delete[] data; }                 // prevents leaks
    Buffer(const Buffer& other) : size(other.size) {
        data = new int[size];                    // deep copy: own block
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }
};
```

### Testing components in isolation

- **Test driver:** stands in for a *caller* — feeds preset inputs to the unit
  under test and checks results (calls *down into* the unit).
- **Test stub:** stands in for a *dependency the unit calls* — returns
  controlled values so the unit can run in isolation.

---

## 2. Lists

### List ADT

A **list** holds **ordered** data. Common operations: `Append`, `Prepend`,
`InsertAfter`, `Remove`, `Contains`/`Search`, `Print`, `Sort`, `IsEmpty`,
`GetLength`. A list can be implemented with a linked list or an array — an array
is not required.

### Singly-linked lists

Each node stores **data** and a **next** pointer; the list keeps **head** and
**tail** pointers.

```cpp
class Node {
public:
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};
```

Appending/prepending to an **empty** list sets both head and tail. On a
non-empty list, append updates the tail only; prepend updates the head only.

```cpp
void Append(Node*& head, Node*& tail, Node* n) {
    if (head == nullptr) { head = tail = n; }
    else { tail->next = n; tail = n; }
}
void Prepend(Node*& head, Node*& tail, Node* n) {
    if (head == nullptr) { head = tail = n; }
    else { n->next = head; head = n; }
}
```

**Search** walks from the head; **insert-after-item** searches then inserts
(worst case `O(n)` because the search dominates).

```cpp
Node* Search(Node* head, int key) {
    for (Node* cur = head; cur; cur = cur->next)
        if (cur->data == key) return cur;
    return nullptr;
}
```

**Remove** tracks a `previous` pointer, since a singly-linked node cannot look
backward. Removing the head advances `head`; removing the tail updates `tail`.

```cpp
bool Remove(Node*& head, Node*& tail, int key) {
    Node* prev = nullptr;
    Node* cur = head;
    while (cur) {
        if (cur->data == key) {
            if (prev == nullptr) head = cur->next;    // removing head
            else prev->next = cur->next;
            if (cur == tail) tail = prev;             // removing tail
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}
```

### Doubly-linked lists

Each node adds a **previous** pointer, enabling backward traversal and removing
a known node in `O(1)` (no need to find the predecessor).

```cpp
class DNode {
public:
    int data;
    DNode* next;
    DNode* previous;
    DNode(int d) : data(d), next(nullptr), previous(nullptr) {}
};

void RemoveNode(DNode*& head, DNode*& tail, DNode* n) {
    if (n->next) n->next->previous = n->previous;
    if (n->previous) n->previous->next = n->next;
    if (n == head) head = n->next;
    if (n == tail) tail = n->previous;
    delete n;
}
```

### Traversal

Forward traversal works for both list types; reverse traversal needs the
`previous` pointer (doubly-linked).

```cpp
void Traverse(Node* head) {
    for (Node* cur = head; cur; cur = cur->next)
        std::cout << cur->data << " ";
}
```

### Dummy (sentinel) nodes

A **dummy node** with an unused value permanently sits at the head (and
optionally the tail) and is never removed. It guarantees head/tail are never
null, eliminating empty-list special cases from insert/remove code. An empty
list is just the dummy node(s).

### Recursion on lists

```cpp
void TraverseRecursive(Node* node) {
    if (node) { Visit(node); TraverseRecursive(node->next); }
}
// Reverse: recurse first, then visit (prints in reverse even for singly-linked)
void TraverseReverse(Node* node) {
    if (node) { TraverseReverse(node->next); Visit(node); }
}
```

### Array-based lists (dynamic arrays)

Backed by an array plus `allocationSize` and `length`. When full, resize
(commonly **double** the allocation). `std::vector` is the standard-library
array-based list.

```cpp
void Append(int*& arr, int& len, int& cap, int item) {
    if (len == cap) {                            // grow
        cap *= 2;
        int* bigger = new int[cap];
        for (int i = 0; i < len; ++i) bigger[i] = arr[i];
        delete[] arr;
        arr = bigger;
    }
    arr[len++] = item;
}
```

Complexity: resize `O(n)`, prepend/insert-at-front `O(n)` (shift), append `O(1)`
amortized, search/remove-at `O(n)`.

### Sorting linked lists

The core obstacle is that linked lists lack indexed (constant-time) random
access.

- **Feasible:** insertion sort (doubly-linked can scan backward; singly-linked
  scans forward for the insert position) and merge sort (find the middle by a
  linear scan; merging needs no extra storage).
- **Hard to adapt:** shell sort (can't jump the gap), quicksort (partition needs
  backward traversal), heap sort (needs indexed child access).

---

## 3. Stacks & Queues

### Stack ADT (LIFO)

Insert/remove only at the **top**. Operations: `Push`, `Pop`, `Peek`,
`IsEmpty`, `GetLength`. Check for emptiness before `Pop`/`Peek`.

**Linked-list stack** — push = prepend, pop = remove head; both `O(1)`.

```cpp
class Stack {
    struct SNode { int data; SNode* next; };
    SNode* top = nullptr;
public:
    void Push(int x) { top = new SNode{x, top}; }
    int Pop() {
        SNode* n = top;
        int v = n->data;
        top = n->next;
        delete n;
        return v;
    }
};
```

**Array-based stack** — top item at `array[length-1]`. A **bounded** stack has a
fixed `maxLength` ("full" when reached); an **unbounded** stack grows (resize).
Push must check for overflow *before* writing.

**Two-way (shared) stack** — two stacks share one array, growing from opposite
ends. Overflow occurs only when they meet (`top1 + 1 == top2`), maximizing space
regardless of individual sizes.

```cpp
class TwoWayStack {
    int* arr; int cap; int top1; int top2;
public:
    TwoWayStack(int n) : cap(n), top1(-1), top2(n) { arr = new int[n]; }
    ~TwoWayStack() { delete[] arr; }
    void push1(int v) { if (top1 + 1 == top2) throw std::overflow_error("full"); arr[++top1] = v; }
    void push2(int v) { if (top1 + 1 == top2) throw std::overflow_error("full"); arr[--top2] = v; }
};
```

### Queue ADT (FIFO)

Insert at the **end**, remove from the **front**. Operations: `Enqueue`,
`Dequeue`, `Peek`, `IsEmpty`, `GetLength`.

**Linked-list queue** — front = head, back = tail; both operations `O(1)`.

**Array-based (circular) queue** — uses `frontIndex` and modulo arithmetic to
wrap around, reusing freed front slots without shifting. Front item at
`array[frontIndex]`; insert index `(frontIndex + length) % cap`.

```cpp
class CircularQueue {
    int* arr; int cap; int front; int count;
public:
    CircularQueue(int n) : cap(n), front(0), count(0) { arr = new int[n]; }
    ~CircularQueue() { delete[] arr; }
    void Enqueue(int x) {
        if (count == cap) throw std::overflow_error("full");
        arr[(front + count) % cap] = x;          // wrap-around
        count++;
    }
    int Dequeue() {
        if (count == 0) throw std::underflow_error("empty");
        int x = arr[front];
        front = (front + 1) % cap;
        count--;
        return x;
    }
};
```

Only enqueue may resize; dequeue is always `O(1)`.

### Deque ADT

A **double-ended queue** allows insertion/removal at both ends: `PushFront`,
`PushBack`, `PopFront`, `PopBack`, `PeekFront`, `PeekBack`.

### C++ `std::stack` and `std::queue`

- `std::stack`: `push`, `pop` (removes only, returns nothing), `top` (returns),
  `size`. Ideal for **undo**.
- `std::queue`: `push` (enqueue), `pop` (removes front), `front` (returns),
  `size`. Ideal for processing items in arrival order.

```cpp
#include <stack>
std::stack<std::string> actions;
actions.push("edit");
std::string last = actions.top();  // inspect
actions.pop();                     // remove
```

---

## 4. Searching & Algorithm Analysis

### Linear search

Scan from the start until the key is found or the end is reached. Best case
`O(1)` (first element), worst case `O(N)`.

```cpp
int LinearSearch(const int* a, int n, int key) {
    for (int i = 0; i < n; ++i)
        if (a[i] == key) return i;
    return -1;
}
```

### Binary search

Requires a **sorted** array. Check the middle; discard the half that can't
contain the key. Each step halves the search space → worst case `O(log N)`.

```cpp
int BinarySearch(const int* a, int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;        // avoids overflow
        if (a[mid] < key)      low = mid + 1;
        else if (a[mid] > key) high = mid - 1;
        else return mid;
    }
    return -1;
}
```

Termination is guaranteed because each iteration narrows `low`/`high` until
`low > high`.

### Constant-time operations

A **constant-time** (`O(1)`) operation takes the same time regardless of operand
values: fixed-size arithmetic, assignment, comparison, indexed array access.
String concatenation and value-dependent loops are **not** constant time. Any
*constant number* of constant-time operations is still `O(1)`.

### Growth of functions & Big-O

**Big-O** describes the growth rate of an upper bound on runtime. Rules:

1. Keep only the highest-order term in a sum.
2. Drop constant factors.

Example: `5 + 13N + 7N²` → `O(N²)`.

- **Big-O (`O`)** — upper bound growth.
- **Big-Omega (`Ω`)** — lower bound growth.
- **Big-Theta (`Θ`)** — both upper and lower bound.

**Common classes** (best → worst): `O(1)`, `O(log N)`, `O(N)`, `O(N log N)`,
`O(N²)`, `O(2ⁿ)`, `O(N!)`.

**Analyzing loops:** a single loop over `N` with `O(1)` body is `O(N)`. Nested
loops where the inner runs `N-1, N-2, ..., 1` total `N(N-1)/2` → `O(N²)`.

### Recursion

A **recursive** algorithm applies itself to smaller subproblems and needs a
**base case** to terminate.

```cpp
int Factorial(int n) {
    if (n <= 1) return 1;              // base case
    return n * Factorial(n - 1);       // recursive case
}
```

An **activation record** (stack frame) holds a call's **parameters**, **local
variables**, and **return address**. Too many pending calls cause **stack
overflow**. **Tail recursion** is when the recursive call is the final
operation, allowing loop-like optimization.

### Recurrence relations & recursion trees

The runtime `T(N)` of a recursive function appears on both sides of its
**recurrence relation**. A **recursion tree** separates work done directly by a
call from work delegated to recursive calls.

| Recurrence | Result |
|------------|--------|
| `T(N) = k + T(N/2)` | `O(log N)` |
| `T(N) = N + 2·T(N/2)` | `O(N log N)` |
| `T(N) = N + T(N-1)` | `O(N²)` |

---

## 5. Trees

### Binary tree terminology

Each node has up to two children (left, right).

- **Root:** node with no parent. **Leaf:** node with no children. **Internal:**
  node with ≥ 1 child.
- **Edge:** link from parent to child. **Depth:** edges from root to a node (root
  depth 0). **Level:** all nodes at one depth. **Height:** the largest depth
  (single node → height 0).
- **Full:** every node has 0 or 2 children. **Complete:** all levels full except
  possibly the last, filled left-to-right. **Perfect:** all internal nodes have
  2 children and all leaves are on the same level.
- **Subtree:** a node plus all its descendants.

Applications: file systems, binary space partitioning (fast rendering by
halving candidate objects per level), and storing collections for fast lookup.

### Binary search trees (BST)

**Ordering property:** for every node, all keys in its left subtree are less and
all keys in its right subtree are greater. Keys are distinct.

```cpp
class BSTNode {
public:
    int key;
    BSTNode* left = nullptr;
    BSTNode* right = nullptr;
    BSTNode(int k) : key(k) {}
};
```

**Search** eliminates one subtree per comparison → worst case `O(H)`, where `H`
is the height. A balanced tree gives `H ≈ ⌊log₂ N⌋`, so search is `O(log N)`.

```cpp
BSTNode* Search(BSTNode* root, int key) {
    BSTNode* cur = root;
    while (cur) {
        if (key == cur->key) return cur;
        cur = (key < cur->key) ? cur->left : cur->right;
    }
    return nullptr;
}
```

**Insert** descends to the correct null child and links the new node.

```cpp
void Insert(BSTNode*& root, BSTNode* n) {
    if (!root) { root = n; return; }
    BSTNode* cur = root;
    while (cur) {
        if (n->key < cur->key) {
            if (!cur->left) { cur->left = n; return; }
            cur = cur->left;
        } else {
            if (!cur->right) { cur->right = n; return; }
            cur = cur->right;
        }
    }
}
```

**Remove** handles three cases:

1. **Leaf:** set the parent's pointer to null.
2. **One child:** the parent's pointer is reassigned to the single child.
3. **Two children:** replace the key with the **successor** (leftmost node of
   the right subtree), then remove the successor.

```cpp
BSTNode* Successor(BSTNode* node) {   // leftmost node of the right subtree
    BSTNode* cur = node->right;
    while (cur && cur->left) cur = cur->left;
    return cur;
}
```

### Traversals

A traversal visits each node once → `O(N)`.

| Traversal | Order | Note |
|-----------|-------|------|
| Inorder | Left, Node, Right | BST keys in sorted order |
| Preorder | Node, Left, Right | reproduces insertion order |
| Postorder | Left, Right, Node | used to delete/free a tree |

```cpp
void Inorder(BSTNode* n)   { if (!n) return; Inorder(n->left);  Visit(n); Inorder(n->right); }
void Preorder(BSTNode* n)  { if (!n) return; Visit(n); Preorder(n->left);  Preorder(n->right); }
void Postorder(BSTNode* n) { if (!n) return; Postorder(n->left); Postorder(n->right); Visit(n); }
```

Iterative traversal uses an explicit **stack** (not an array/queue); level-order
traversal (BFS) uses a **queue**.

### Height & insertion order

- Minimum N-node height: `⌊log₂ N⌋`. Maximum: `N - 1` (degenerate list-like
  tree).
- Inserting keys in **random** order keeps height near minimum; **sorted** input
  produces the worst (maximum) height.

```cpp
int Height(BSTNode* n) {
    if (!n) return -1;                           // null → -1, single node → 0
    return 1 + std::max(Height(n->left), Height(n->right));
}
```

### Set ADT

An unordered collection of **distinct** elements. Operations: `Add`, `Remove`,
`Contains`, size/**cardinality**, `IsSubsetOf`. Two sets are equal if they hold
the same elements regardless of order.

- **Union** `X ∪ Y`: all elements from both. (commutative)
- **Intersection** `X ∩ Y`: elements in both. (commutative)
- **Difference** `X − Y`: elements in X not in Y. (not commutative)
- **Filter(pred):** subset satisfying a predicate. **Map(f):** apply `f` to each.

A set can be backed by a BST (sorted iteration) or a hash table.
`std::unordered_set` provides `insert`, `erase`, `count`, `size`; iteration is
in **no particular order**.

### Tries (prefix trees)

A **trie** stores a set of strings; each non-root node represents one character,
and a **terminal node** marks the end of a stored string. With `O(1)` child
lookups, insert/search/remove for a string of length `M` is `O(M)` —
independent of how many strings are stored. Common in autocomplete.

```cpp
class TrieNode {
    std::unordered_map<char, TrieNode*> children;
public:
    void Insert(const std::string& s) {
        TrieNode* node = this;
        for (char c : s) {
            if (!node->children.count(c)) node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->children['\0'] = new TrieNode();   // terminal marker
    }
};
```

---

## 6. Heaps & Priority Queues

### Heap concept

- **Max-heap:** a *complete binary tree* where every node's key ≥ its children's
  → the root is the maximum.
- **Min-heap:** every node's key ≤ its children's → the root is the minimum.

Because a heap is always complete, its height is minimal (`⌊log₂ N⌋`). Insert
and remove are both `O(log N)`.

### Array representation

Heaps are stored in an array by reading levels top-to-bottom, left-to-right.
For a node at index `i` (0-based):

| Relationship | Index |
|--------------|-------|
| Left child | `2*i + 1` |
| Right child | `2*i + 2` |
| Parent | `(i - 1) / 2` |

- **Leaves** are the nodes at indices `N/2 ... N-1` (≈ N/2 of them).
- The **last non-leaf** (last internal node) is at index `N/2 - 1`.

### Percolate up / down

- **Insert:** add at the end, then **percolate up** (swap with parent while it
  violates the heap property).
- **Remove:** the root is removed; move the last element to the root, then
  **percolate down** (swap with the larger child until valid).

```cpp
void PercolateUp(std::vector<int>& h, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h[i] <= h[parent]) return;
        std::swap(h[i], h[parent]);
        i = parent;
    }
}

void PercolateDown(std::vector<int>& h, int i, int size) {
    while (2 * i + 1 < size) {
        int child = 2 * i + 1;                   // left child
        if (child + 1 < size && h[child + 1] > h[child]) child++;  // larger child
        if (h[i] >= h[child]) return;
        std::swap(h[i], h[child]);
        i = child;
    }
}
```

### Heapsort

**Heapify** an array by calling percolate-down on every internal node, from
index `N/2 - 1` down to 0 (leaves already satisfy the property). Then repeatedly
swap the root to the end, shrink the heap, and percolate down. In place, no
recursion, `O(N log N)` in all cases. A max-heap yields ascending order.

```cpp
void Heapsort(std::vector<int>& v) {
    int n = v.size();
    for (int i = n / 2 - 1; i >= 0; --i)         // build heap starting at N/2-1
        PercolateDown(v, i, n);
    for (int end = n - 1; end > 0; --end) {
        std::swap(v[0], v[end]);                 // move max to the end
        PercolateDown(v, 0, end);                // shrink the heap region
    }
}
```

### Priority queue ADT

Each item has a **priority**; `Dequeue` removes the highest-priority item. Backed
by a heap:

| PQ operation | Heap operation | Cost |
|--------------|----------------|------|
| Enqueue | Insert | `O(log N)` |
| Dequeue | Remove root | `O(log N)` |
| Peek | Return root | `O(1)` |

Use a **max-heap** when a larger value = higher priority; a **min-heap** when a
smaller number = higher priority. Equal priorities typically follow FIFO.

### Treaps

A **treap** combines a BST on a key with a randomly assigned priority kept in
heap order. Random priorities keep the tree balanced (`~O(log N)`). Insert
uses rotations to percolate up; delete sets priority to −∞ and rotates the node
down to a leaf.

### C++ `std::priority_queue`

```cpp
#include <queue>
std::priority_queue<int> maxPQ;                                  // largest = top
std::priority_queue<int, std::vector<int>, std::greater<int>> minPQ; // smallest = top
maxPQ.push(5);
int top = maxPQ.top();   // inspect highest priority
maxPQ.pop();             // remove it
```

A custom comparator is a class overloading `operator()`; returning `a < b`
gives larger items priority.

---

## 7. Hash Tables & Maps

### Map ADT

A **map** (dictionary) associates distinct **keys** with **values**. Operations:
`Insert(key, value)` (updates on duplicate key), `Remove`, `Get`, `Contains`,
`GetLength`. Iteration is typically unordered.

### Hash tables

A **hash function** turns a key into a fixed-size non-negative **hash code**; the
**bucket index** is `hashCode % tableSize`. Computing an index is `O(1)`.

```cpp
int HashString(const std::string& s) {
    int h = 0;
    for (unsigned char c : s) h += c;            // simple (weak) sum
    return h & 0x7fffffff;                        // force non-negative
}
```

A **collision** is when two distinct keys map to the same bucket. Resolved by
**chaining** or **open addressing**.

### Chaining

Each bucket holds a linked list of items. Insert/get/remove find the bucket then
search its list. A distinct key never appears twice.

```cpp
class ChainingHashTable {
    std::vector<std::list<std::pair<int,int>>> table;   // key,value pairs
    int Bucket(int key) const { return (key & 0x7fffffff) % table.size(); }
public:
    ChainingHashTable(int cap = 11) : table(cap) {}
    void Insert(int key, int value) {
        auto& bucket = table[Bucket(key)];
        for (auto& kv : bucket)
            if (kv.first == key) { kv.second = value; return; }  // update
        bucket.push_back({key, value});
    }
};
```

### Open addressing

Items are stored directly in the array; on collision, probe for another slot.
Buckets have three states: **occupied**, **empty-since-start**, and
**empty-after-removal** (a tombstone). A search stops at a match or at an
empty-since-start bucket — but must **not** stop at a tombstone, or it would
hide items inserted later.

- **Linear probing:** `(hash + i) % size` for `i = 0, 1, 2, ...` — suffers from
  clustering.
- **Quadratic probing:** `(hash + c₁·i + c₂·i²) % size` — reduces clustering.
  `c₁`, `c₂` must not be multiples of the table size (often a prime is used).
- **Double hashing:** `(hash1 + i·hash2(key)) % size`. `hash2` must never return
  0.

```cpp
int QuadraticProbeSlot(const std::vector<int>& table, int cap, int key, int EMPTY = -1) {
    int h = (key & 0x7fffffff) % cap;
    for (int i = 0; i < cap; ++i) {
        int idx = (h + i * i) % cap;             // c1=0, c2=1
        if (table[idx] == EMPTY) return idx;
    }
    return -1;                                    // full
}
```

### Load factor & resizing

**Load factor** = items / buckets. Resize (rehash all items, `O(N)`) when the
load factor is too high or lists get too long; a common new size is the next
prime ≥ `2·N`. Open-addressing load factor cannot exceed 1.0; chaining's can.

### Common hash functions

- **Perfect hash:** no collisions (possible when all keys are known ahead) →
  `O(1)` everything.
- **Modulo hash:** `key % tableSize`.
- **Mid-square hash:** square the key, extract middle bits, mod by size.
- **Multiplicative (djb2):** start at 5381, `hash = hash*33 + c` per character.
- **Direct hashing:** use the key itself as the index (no collisions), but keys
  must be non-negative integers and the array size = largest key + 1.

A good hash function distributes keys **uniformly** for `O(1)` average
operations (`O(N)` worst case). Password storage hashes the password (never
stores it), ideally with a random **salt**.

### C++ `unordered_map`

```cpp
#include <unordered_map>
std::unordered_map<std::string, double> prices;
prices["milk"] = 3.50;                 // insert/update
if (prices.count("milk")) {            // membership
    double p = prices["milk"];         // lookup
}
prices.erase("milk");                  // remove
```

---

## 8. Sorting Algorithms

### Overview

| Algorithm | Best | Average | Worst | Space | Stable | Comparison sort |
|-----------|------|---------|-------|-------|--------|-----------------|
| Selection | O(N²) | O(N²) | O(N²) | O(1) | No | Yes |
| Insertion | O(N) | O(N²) | O(N²) | O(1) | Yes | Yes |
| Bubble | O(N²)* | O(N²) | O(N²) | O(1) | Yes | Yes |
| Shell | O(N log N) | ~O(N^1.5) | gap-dependent | O(1) | No | Yes |
| Quicksort | O(N log N) | O(N log N) | O(N²) | O(log N) | No | Yes |
| Merge | O(N log N) | O(N log N) | O(N log N) | O(N) | Yes | Yes |
| Heapsort | O(N log N) | O(N log N) | O(N log N) | O(1) | No | Yes |
| Radix | O(d·(N+k)) | O(d·(N+k)) | O(d·(N+k)) | O(N+k) | Yes | No |

\* Basic bubble sort without early-exit is O(N²) even when sorted. A **fast**
sort averages `O(N log N)` or better; the best possible average for a comparison
sort is `O(N log N)`. **Stability** means equal keys keep their relative order.

### Selection sort

Select the minimum of the unsorted region and swap it into place. Always `O(N²)`,
fewest swaps.

```cpp
void SelectionSort(std::vector<int>& v) {
    for (int i = 0; i < (int)v.size() - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < (int)v.size(); ++j)
            if (v[j] < v[min]) min = j;
        std::swap(v[i], v[min]);
    }
}
```

### Insertion sort

Insert each element into its place within a growing sorted prefix. `O(N)` on
nearly-sorted data — excellent for that case.

```cpp
void InsertionSort(std::vector<int>& v) {
    for (int i = 1; i < (int)v.size(); ++i) {
        int key = v[i], j = i - 1;
        while (j >= 0 && v[j] > key) { v[j + 1] = v[j]; --j; }
        v[j + 1] = key;
    }
}
```

### Shell sort

Insertion-sort interleaved subarrays spaced by a **gap**, shrinking the gap to 1.
Pre-sorting the interleaved parts makes the final pass cheap. Gaps must include
1; a common sequence (…, 15, 7, 3, 1) gives up to `O(N^1.5)`.

### Quicksort

Partition around a **pivot** (low partition ≤ pivot ≤ high partition), then
recurse. Average `O(N log N)`; worst `O(N²)` when the pivot is repeatedly the
smallest/largest. Partitioning happens before the recursive calls.

```cpp
int Partition(std::vector<int>& v, int lo, int hi) {
    int mid = lo + (hi - lo) / 2, pivot = v[mid];
    while (true) {
        while (v[lo] < pivot) ++lo;
        while (pivot < v[hi]) --hi;
        if (lo >= hi) return hi;
        std::swap(v[lo++], v[hi--]);
    }
}
void Quicksort(std::vector<int>& v, int lo, int hi) {
    if (hi <= lo) return;
    int p = Partition(v, lo, hi);
    Quicksort(v, lo, p);
    Quicksort(v, p + 1, hi);
}
```

### Merge sort

Recursively split in half, then **merge** sorted halves. Guaranteed
`O(N log N)`, stable, but needs `O(N)` extra space.

```cpp
void Merge(std::vector<int>& v, int lo, int mid, int hi) {
    std::vector<int> tmp;
    int i = lo, j = mid + 1;
    while (i <= mid && j <= hi)
        tmp.push_back(v[i] <= v[j] ? v[i++] : v[j++]);   // <= keeps it stable
    while (i <= mid) tmp.push_back(v[i++]);
    while (j <= hi)  tmp.push_back(v[j++]);
    for (int k = 0; k < (int)tmp.size(); ++k) v[lo + k] = tmp[k];
}
void MergeSort(std::vector<int>& v, int lo, int hi) {
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;
    MergeSort(v, lo, mid);
    MergeSort(v, mid + 1, hi);
    Merge(v, lo, mid, hi);
}
```

### Radix sort

A non-comparison, **stable** sort for integers using 10 buckets, processing
digits from **least to most significant**. Multi-key sorting follows the same
rule — sort by the least significant key first so a stable pass preserves
earlier ordering.

```cpp
void CountingSortByDigit(std::vector<int>& v, int exp) {
    std::vector<int> out(v.size());
    int count[10] = {0};
    for (int x : v) count[(x / exp) % 10]++;
    for (int i = 1; i < 10; ++i) count[i] += count[i - 1];
    for (int i = v.size() - 1; i >= 0; --i)      // reverse keeps it stable
        out[--count[(v[i] / exp) % 10]] = v[i];
    v = out;
}
void RadixSort(std::vector<int>& v) {
    if (v.empty()) return;
    int mx = *std::max_element(v.begin(), v.end());
    for (int exp = 1; mx / exp > 0; exp *= 10)   // least significant digit first
        CountingSortByDigit(v, exp);
}
```

### C++ `std::sort`

Sorts ascending using `operator<`; pass a comparator for custom order (return
`true` when the first argument should come first).

```cpp
#include <algorithm>
std::sort(v.begin(), v.end());
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });  // descending
```

---

## 9. Graphs

### Fundamentals

A **graph** has **vertices** connected by **edges**.

- **Adjacent:** two vertices joined by an edge.
- **Path:** a sequence of edges; **path length** = edge count (or sum of weights).
- **Distance:** edges on the shortest path.
- **Connected:** a path exists between every pair. **Cycle:** a path that starts
  and ends at the same vertex; **cyclic/acyclic** accordingly.
- **Sparse:** far fewer edges than the maximum `V(V-1)/2`.

**Directed graph (digraph):** edges have direction; `Y` is adjacent to `X` only
if an edge goes from `X` to `Y`. A **DAG** is a directed acyclic graph.

**Weighted graph:** edges carry weights; the **shortest path** minimizes the
weight sum. A **negative-weight cycle** means no shortest path exists.

### Representations

- **Adjacency list:** each vertex stores its adjacent vertices. Space `O(V + E)`,
  adjacency check `O(V)`. Good for sparse graphs.
- **Adjacency matrix:** `V × V` matrix; `[i][j] = 1` if an edge exists. Adjacency
  check `O(1)`, space `O(V²)`.

### Breadth-first search (BFS)

Visit the start, then all vertices at distance 1, 2, … using a **queue**. A
vertex is enqueued once (when discovered).

```cpp
void BFS(const std::vector<std::vector<int>>& adj, int start) {
    std::vector<bool> discovered(adj.size(), false);
    std::queue<int> q;
    discovered[start] = true; q.push(start);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        Visit(v);
        for (int nb : adj[v])
            if (!discovered[nb]) { discovered[nb] = true; q.push(nb); }
    }
}
```

### Depth-first search (DFS)

Follow a path to its end before backtracking, using a **stack** (or recursion).

```cpp
void DFS(const std::vector<std::vector<int>>& adj, int start) {
    std::vector<bool> visited(adj.size(), false);
    std::stack<int> s;
    s.push(start);
    while (!s.empty()) {
        int v = s.top(); s.pop();
        if (!visited[v]) {
            visited[v] = true;
            Visit(v);
            for (int nb : adj[v]) s.push(nb);    // push only unvisited when marking
        }
    }
}
```

Both BFS and DFS are `O(V + E)` on an adjacency list.

### Dijkstra's shortest path

From a start vertex, find shortest paths to all others. Each vertex tracks a
**distance** and **predecessor**. Repeatedly pick the unvisited vertex with the
smallest distance and **relax** its edges. Works for non-negative weights only.
When using a priority queue, skip an extracted vertex if already finalized (to
avoid finalizing it more than once).

```cpp
std::vector<int> Dijkstra(const std::vector<std::vector<std::pair<int,int>>>& adj, int src) {
    int n = adj.size();
    std::vector<int> dist(n, INT_MAX);
    std::vector<bool> done(n, false);
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>,
                        std::greater<>> pq;
    dist[src] = 0; pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (done[u]) continue;                   // already finalized
        done[u] = true;
        for (auto [v, w] : adj[u])
            if (!done[v] && d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
    }
    return dist;
}
```

### Bellman-Ford

Also computes single-source shortest paths but **supports negative weights** and
**detects negative cycles**. Relax all edges `V-1` times, then one more pass: if
any edge can still be relaxed, a negative cycle exists. Runtime `O(V·E)`.

### Topological sort

On a **DAG**, order vertices so every edge `X → Y` has `X` before `Y`. Count each
vertex's incoming edges; repeatedly remove a vertex with zero incoming edges,
appending it and decrementing its successors' counts. Runtime `O(V + E)`. Used
for ordering prerequisites/tasks.

### Minimum spanning tree (Kruskal's)

An **MST** connects all vertices of a weighted, connected, undirected graph with
minimum total edge weight (it's a set of *edges*). Kruskal's: pull edges from a
priority queue (lowest weight first); add an edge only if it joins two different
vertex sets, then merge the sets. Runtime `O(E log E)`.

### All-pairs shortest path (Floyd-Warshall)

Builds a `V × V` matrix of shortest distances between all pairs. For each
intermediate vertex `k`, relax every pair `(a, b)` through `k`. Runtime `O(V³)`;
supports negative weights but not negative cycles.

```cpp
for (int k = 0; k < V; ++k)
    for (int a = 0; a < V; ++a)
        for (int b = 0; b < V; ++b)
            if (dist[a][k] + dist[k][b] < dist[a][b])
                dist[a][b] = dist[a][k] + dist[k][b];
```

---

## 10. Algorithm Design Techniques

### Huffman compression

Assigns variable-length, prefix-free codes so frequent characters get shorter
codes. Build a frequency table, make each character a leaf in a min-priority
queue, then repeatedly merge the two lowest-frequency nodes into a parent whose
frequency is their sum. Codes are read root→leaf (left = 0, right = 1).

```cpp
struct HuffNode {
    char ch; int freq;
    HuffNode *left, *right;
};
struct FreqCompare {
    bool operator()(HuffNode* a, HuffNode* b) { return a->freq > b->freq; }
};
HuffNode* BuildTree(const std::unordered_map<char,int>& table) {
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, FreqCompare> pq;
    for (auto [c, f] : table) pq.push(new HuffNode{c, f, nullptr, nullptr});
    while (pq.size() > 1) {
        HuffNode* l = pq.top(); pq.pop();
        HuffNode* r = pq.top(); pq.pop();
        pq.push(new HuffNode{'\0', l->freq + r->freq, l, r});
    }
    return pq.top();
}
```

### Heuristics

A **heuristic** trades optimality/accuracy for speed. Example: the 0-1 knapsack
(maximize value under a weight limit, at most one of each item) — greedily taking
the highest-value item that fits is fast but not necessarily optimal.
**Move-to-front** on a list makes repeated searches for the same key cheap.

### Greedy algorithms

Always choose what looks best *right now*. Optimal for some problems:

- **Make change** (standard US coins): take the largest coin that fits, repeat.
- **Fractional knapsack:** sort by value/weight ratio, take whole items, then a
  fraction of the next — greedy is optimal here (at most one fractional item).
- **Activity selection:** sort by finish time, repeatedly take the next
  non-conflicting activity.

```cpp
void MakeChange(int amount) {
    for (int coin : {25, 10, 5, 1})
        while (amount >= coin) { std::cout << coin << " "; amount -= coin; }
}
```

### Dynamic programming (DP)

Split a problem into subproblems, **store and reuse** their solutions. Turns
exponential recomputation into polynomial time.

```cpp
// Fibonacci: recursive O(2^n) vs. DP O(n)
int FibDP(int n) {
    if (n == 0) return 0;
    int prev = 0, cur = 1;
    for (int i = 1; i < n; ++i) { int next = prev + cur; prev = cur; cur = next; }
    return cur;
}
```

**Longest common substring** (contiguous) — build an `N × M` matrix where a
match sets `matrix[i][j] = 1 + matrix[i-1][j-1]` and a mismatch sets 0; the
largest entry gives the length. `O(N·M)`.

**Longest common subsequence** (not necessarily contiguous) — mismatch instead
takes `max(matrix[i-1][j], matrix[i][j-1])`.

---

## 11. Balanced Trees

### AVL trees

A height-balanced BST. Each node's **balance factor** = height(left) −
height(right) must be −1, 0, or +1. A null subtree has height −1. Height stays
`O(log N)`. Storing each node's height makes the balance factor `O(1)`.

**Rotations** rearrange nodes while preserving BST ordering. After insert/remove,
rebalance every ancestor from the changed node up to the root.

| Imbalance | Node BF | Child BF | Fix |
|-----------|---------|----------|-----|
| Left-Left | +2 | +1 | Right rotation |
| Left-Right | +2 | −1 | Left rotate child, then right rotate node |
| Right-Right | −2 | −1 | Left rotation |
| Right-Left | −2 | +1 | Right rotate child, then left rotate node |

```cpp
void Rebalance(AVLNode* node) {
    node->UpdateHeight();
    if (node->Balance() == -2) {                 // right-heavy
        if (node->right->Balance() == 1) RotateRight(node->right);  // right-left
        RotateLeft(node);
    } else if (node->Balance() == 2) {           // left-heavy
        if (node->left->Balance() == -1) RotateLeft(node->left);    // left-right
        RotateRight(node);
    }
}
```

Insert and remove are `O(log N)` (search + at most a couple of `O(1)` rotations
per level). Two-child removal uses the inorder successor.

### Red-black trees

A BST with colored nodes keeping height `O(log N)`:

1. Every node is red or black.
2. The root is black.
3. A red node's children are black (no two reds in a row).
4. Null children count as black leaves.
5. Every path from a node to its descendant null leaves has the same number of
   black nodes.

Insert: BST-insert the node **red**, then fix violations by recoloring
(parent/uncle/grandparent) or rotating. Removing a red node needs no repair;
removing a black node requires restructuring to preserve the black-height. Any
BST becomes a valid red-black tree by coloring all nodes black.

---

## 12. B-Trees

### B-tree fundamentals

A **B-tree of order K** allows each node up to **K−1 keys** and **K children**.
Properties: keys are distinct, all leaves are at the same level, an internal node
with N keys has N+1 children, and keys within a node are sorted (each key
separates a smaller-left and larger-right subtree). Higher order → more
keys/children per node. B-trees keep search/insert/remove at `O(log N)` and are
used in databases and filesystems (few, wide nodes minimize disk reads).

### 2-3-4 trees (order-4 B-tree)

Internal nodes have 2, 3, or 4 children (1, 2, or 3 keys):

| Keys | Children | Name |
|------|----------|------|
| 1 | 2 | 2-node |
| 2 | 3 | 3-node |
| 3 | 4 | 4-node (full) |

**Search** recurses into the child bracketed by the surrounding keys.

**Insert** (preemptive split): new keys always go into a leaf. On the way down,
**split** every full (3-key) node — its middle key moves up into the parent,
leaving two smaller nodes. Splitting the root is the only way the tree grows in
height.

**Remove** (preemptive merge): a key is ultimately removed from a leaf with ≥ 2
keys. On the way down, grow every single-key node via a **rotation** (borrow from
a sibling with ≥ 2 keys) or **fusion** (merge with a sibling and a parent key —
the inverse of a split). To remove a key in an internal node, replace it with its
successor from a leaf.

---

## 13. Additional Topics

### Bubble sort

Repeatedly compare adjacent elements, swapping out-of-order pairs; each pass
bubbles the next largest element into place. `O(N²)` (basic version has no early
exit). Impractical versus faster sorts.

```cpp
void BubbleSort(std::vector<int>& v) {
    for (int i = 0; i < (int)v.size() - 1; ++i)
        for (int j = 0; j < (int)v.size() - i - 1; ++j)
            if (v[j] > v[j + 1]) std::swap(v[j], v[j + 1]);
}
```

### Quickselect

Finds the k-th smallest element using quicksort's partition, but recurses only
into the partition containing index k. Average `O(N)`, worst `O(N²)`.

```cpp
int Quickselect(std::vector<int>& v, int lo, int hi, int k) {
    if (lo >= hi) return v[lo];
    int p = Partition(v, lo, hi);
    if (k <= p) return Quickselect(v, lo, p, k);
    return Quickselect(v, p + 1, hi, k);
}
```

### Bucket sort

Distribute non-negative numbers into buckets by value range, sort each bucket,
then concatenate. Bucket index = `number * bucketCount / (maxValue + 1)`. Also a
general category term for grouping items by a shared attribute then combining.

### Circular linked lists

The tail's `next` points back to the head (a doubly-linked variant also links
head's `previous` to the tail) — useful for repeating processes. Traversal stops
when it returns to the head, not at null; a one-node list points to itself.

```cpp
void CircularTraverse(Node* head) {
    if (!head) return;
    Node* cur = head;
    do { Visit(cur); cur = cur->next; } while (cur != head);
}
```

---

## 14. Complexity Cheat Sheet

| Operation | Complexity |
|-----------|-----------|
| Array indexed access | O(1) |
| Stack push/pop, queue enqueue/dequeue | O(1) |
| Linked-list / array search (unsorted) | O(N) |
| Array prepend / insert-at-front | O(N) |
| Binary search (sorted array) | O(log N) |
| BST search/insert/remove (balanced / skewed) | O(log N) / O(N) |
| Tree traversal (in/pre/post-order, BFS) | O(N) |
| Heap insert / remove | O(log N) |
| Build heap (heapify) | O(N) |
| Heapsort / merge sort | O(N log N) |
| Quicksort average / worst | O(N log N) / O(N²) |
| Radix sort | O(d·(N+k)) |
| Hash table insert/get/remove (average / worst) | O(1) / O(N) |
| Graph BFS/DFS (adjacency list) | O(V + E) |
| Dijkstra (binary heap) | O((V + E) log V) |
| Bellman-Ford | O(V·E) |
| Topological sort | O(V + E) |
| Kruskal's MST | O(E log E) |
| Floyd-Warshall | O(V³) |
| AVL / red-black / B-tree search/insert/remove | O(log N) |

### Heap array formulas (0-based, node `i`)

- Left child: `2*i + 1` · Right child: `2*i + 2` · Parent: `(i - 1) / 2`
- Last non-leaf / heapify start: `N/2 - 1` · Leaves: indices `N/2 ... N-1`

---

## 15. Common Pitfalls

- **Bounded ADT** size is fixed by its *specification*, not by using an array.
- A **user-defined destructor** is needed whenever a class allocates with `new`.
- **Shallow copy** duplicates only the pointer; **deep copy** duplicates the
  data too.
- Array-stack `top` starts at `-1`; check overflow *before* writing.
- **Binary search** requires a sorted list; it terminates as `low`/`high` narrow.
- A **driver calls down into** the unit under test; a **stub stands in for what
  the unit calls**.
- **Tree traversal is O(N)**, not O(N log N).
- **Inorder successor** = leftmost node of the **right** subtree (rightmost of
  the left subtree is the predecessor).
- **Iterative traversal / DFS uses a stack**; BFS uses a queue.
- An **activation record** stores parameters, local variables, **and the return
  address**.
- **Heap left child** is `2*i + 1` (0-based); `2*i + 2` is the right child.
- **Leaves** of a complete tree ≈ **N/2**; log₂(N) is the *height*.
- **Heapify starts at `N/2 - 1`** (last non-leaf), not `N - 1`.
- **Priority-queue dequeue is O(log N)** with a heap, not O(N).
- **Stability** = preserving the relative order of equal keys.
- **Multi-key / radix sort:** sort by the **least significant key first**.
- **Directed edge (B, A)** means B → A, so A is adjacent to B.
- **Dijkstra** needs non-negative weights; **Bellman-Ford** handles negatives and
  detects negative cycles.
- **Open-addressing search** must skip tombstones (empty-after-removal), not stop
  at them.
- **Quicksort worst case** is O(N²); merge sort and heapsort stay O(N log N).
