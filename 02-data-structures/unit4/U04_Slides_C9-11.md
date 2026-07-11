# Unit 4 Notes — Chapters 9 & 11

**Textbook:** *C++ Plus Data Structures*, 6th Edition (Dale)

Comprehensive notes on:

- **Chapter 9** — Heaps, Priority Queues, and Heap Sort
- **Chapter 11** — Sets, Maps, and Hashing

---

# Chapter 9 — Heaps, Priority Queues, and Heap Sort

## 9.1 The ADT Priority Queue

A **priority queue** is an ADT in which only the **highest-priority** element can be accessed. It behaves almost like a regular queue, except that `Dequeue` returns the *highest-priority* item instead of the *oldest* item.

**Operations**

- **Transformers:** `Enqueue`, `Dequeue`, `MakeEmpty`
- **Observers:** `IsFull`, `IsEmpty`

**Real-world applications**

- Process/job scheduling in operating systems (jobs ordered by priority).
- Emergency-room triage (most urgent patients handled first).
- Course registration priority (graduating seniors choose first).
- Sorting (heap sort, discussed below).

### Choosing an implementation

| Implementation | Enqueue | Dequeue | Problem |
|---|---|---|---|
| Unsorted list | O(1) | O(N) | Dequeue must search for the highest priority |
| Array-based sorted list | O(N) | O(1) | Enqueue must shift data |
| Linked sorted list | O(N) | O(1) | Enqueue does a linear search for insertion point |
| Binary search tree | O(log N) | O(log N) | Efficient — *if balanced* |

**BST drawback:** BST efficiency depends on the tree's height. The pattern of `Enqueue`/`Dequeue` in a priority queue tends to produce tall, narrow (skewed) trees, which degrade to O(N). Because a priority queue only ever needs the highest-priority node, we can **relax the binary search property** and use a **heap**, which is *always* a tree of minimum height and keeps operations at O(log N).

---

## 9.2 Heaps

### Array-based binary trees

A complete binary tree can be stored in an array; the parent/child relationships become *implicit* (computed from indices instead of stored as pointers):

- Node at index `X` has:
  - **Left child** at `X * 2 + 1`
  - **Right child** at `X * 2 + 2`
  - **Parent** at `(X - 1) / 2`

For this implicit representation to have no "holes," the tree must be **full** or **complete** (otherwise dummy values are needed).

- **Full binary tree:** all leaves are on the same level, and every non-leaf node has two children.
- **Complete binary tree:** full, *or* full down to the last level with the leaves on the last level pushed as far **left** as possible.

### Definition of a heap

A **heap** is a binary tree with two properties:

1. **Shape property:** it is a **complete** binary tree.
2. **Order property:** the value of each node is **≥** the values of its children (a *maximum* heap).

Consequences:

- The **root** always holds the **maximum** value.
- A **minimum heap** simply reverses the order property (each parent ≤ its children).
- This is *not* the same "heap" as the region of memory used for dynamic allocation.

### The two core operations

- **ReheapDown:** given a heap that satisfies the order property *except at the root*, push the root down until the order property holds.
- **ReheapUp:** given a heap that satisfies the order property *except at the last (bottom) node*, push that node up until the order property is restored.

Both are O(log N) because a complete tree has minimum height.

---

## 9.3 Heap Implementation

Heaps are almost always used *inside* other structures (like priority queues), so `HeapType` is written as a `struct` (members are public by default) rather than a `class`.

```cpp
template<class ItemType>
// Assumes ItemType is either a built-in simple type
// or a class with overloaded relational operators.
struct HeapType
{
    void ReheapDown(int root, int bottom);
    void ReheapUp(int root, int bottom);
    ItemType* elements;   // Array allocated dynamically
    int numElements;
};
```

### ReheapDown

**Idea:** one of the root's two children is the maximum among {root's children}. Swap the root with the larger child, then recurse on that child's position. Continue until the (sub)root is a leaf or already ≥ both children.

**Determining a leaf:** every non-leaf must have at least a left child (shape property). So if `root*2 + 1 > bottom`, the node is a leaf.

**Pseudocode**

```
ReheapDown(heap, root, bottom)
    if heap.elements[root] is not a leaf
        Set maxChild to index of child with larger value
        if heap.elements[root] < heap.elements[maxChild]
            Swap(heap.elements[root], heap.elements[maxChild])
            ReheapDown(heap, maxChild, bottom)
```

**Implementation**

```cpp
template<class ItemType>
void HeapType<ItemType>::ReheapDown(int root, int bottom)
// Post: Heap property is restored.
{
    int maxChild;
    int rightChild;
    int leftChild;
    leftChild  = root * 2 + 1;
    rightChild = root * 2 + 2;
    if (leftChild <= bottom)
    {
        if (leftChild == bottom)
            maxChild = leftChild;             // only a left child exists
        else
        {
            if (elements[leftChild] <= elements[rightChild])
                maxChild = rightChild;
            else
                maxChild = leftChild;
        }
        if (elements[root] < elements[maxChild])
        {
            Swap(elements[root], elements[maxChild]);
            ReheapDown(maxChild, bottom);
        }
    }
}
```

### ReheapUp

**Idea:** compare the bottom node with its parent. If the parent is smaller, swap them and repeat on the parent. Stop at the root or when the node ≤ its parent.

**Parent index:** `(index - 1) / 2`.

**Pseudocode**

```
ReheapUp(heap, root, bottom)
    if bottom > root
        Set parent to index of parent of bottom node
        if heap.elements[parent] < heap.elements[bottom]
            Swap(heap.elements[parent], heap.elements[bottom])
            ReheapUp(heap, root, parent)
```

**Implementation**

```cpp
template<class ItemType>
void HeapType<ItemType>::ReheapUp(int root, int bottom)
// Post: Heap property is restored.
{
    int parent;
    if (bottom > root)
    {
        parent = (bottom - 1) / 2;
        if (elements[parent] < elements[bottom])
        {
            Swap(elements[parent], elements[bottom]);
            ReheapUp(root, parent);
        }
    }
}
```

### zyBooks `MaxHeap` — a self-contained implementation

A complete, runnable max-heap that owns its own dynamically-resized array. It uses the zyBooks vocabulary — `PercolateUp`/`PercolateDown` instead of `ReheapUp`/`ReheapDown` — but the algorithms are identical. `Insert` appends to the end and percolates up; `Remove` returns the root, moves the last item into the root, and percolates down.

**Key differences from `HeapType`:**

- Self-managing: `Insert`/`Remove` grow the array and update `heapSize`, so the caller never tracks bounds.
- `ResizeArray` doubles the backing array when full (amortized O(1) growth), so there is no fixed capacity.
- `PercolateDown` scans the node's children with a small loop, so the same code generalizes to more than two children.

**`MaxHeap.h`**

```cpp
#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <string>

class MaxHeap {
private:
   int* heapArray;
   int allocationSize;
   int heapSize;

   void PercolateDown(int nodeIndex) {
      int childIndex = 2 * nodeIndex + 1;
      int value = heapArray[nodeIndex];

      while (childIndex < heapSize) {
         // Find the max among the node and all the node's children
         int maxValue = value;
         int maxIndex = -1;
         for (int i = 0; i < 2 && i + childIndex < heapSize; i++) {
            if (heapArray[i + childIndex] > maxValue) {
               maxValue = heapArray[i + childIndex];
               maxIndex = i + childIndex;
            }
         }

         // Check for a violation of the max-heap property
         if (maxValue == value) {
            return;
         }
         else {
            // Swap heapArray[nodeIndex] and heapArray[maxIndex]
            std::cout << "   PercolateDown() swap: " << heapArray[nodeIndex];
            std::cout << " <-> " << heapArray[maxIndex] << std::endl;
            int temp = heapArray[nodeIndex];
            heapArray[nodeIndex] = heapArray[maxIndex];
            heapArray[maxIndex] = temp;

            // Continue loop from the max index node
            nodeIndex = maxIndex;
            childIndex = 2 * nodeIndex + 1;
         }
      }
   }

   void PercolateUp(int nodeIndex) {
      while (nodeIndex > 0) {
         // Compute the parent node's index
         int parentIndex = (nodeIndex - 1) / 2;

         // Check for a violation of the max-heap property
         if (heapArray[nodeIndex] <= heapArray[parentIndex]) {
            // No violation, so percolate up is done.
            return;
         }
         else {
            // Swap heapArray[nodeIndex] and heapArray[parentIndex]
            std::cout << "   PercolateUp() swap: " << heapArray[parentIndex];
            std::cout << " <-> " << heapArray[nodeIndex] << std::endl;
            int temp = heapArray[nodeIndex];
            heapArray[nodeIndex] = heapArray[parentIndex];
            heapArray[parentIndex] = temp;

            // Continue the loop from the parent node
            nodeIndex = parentIndex;
         }
      }
   }

   void ResizeArray() {
      int newAllocationSize = allocationSize * 2;
      int* newArray = new int[newAllocationSize];
      if (newArray) {
         // Copy from existing array to new array
         for (int i = 0; i < allocationSize; i++) {
            newArray[i] = heapArray[i];
         }

         // Delete old array and set pointer to new
         delete[] heapArray;
         heapArray = newArray;

         // Update allocation size
         allocationSize = newAllocationSize;
      }
   }

public:
   MaxHeap() {
      allocationSize = 1;
      heapArray = new int[allocationSize];
      heapSize = 0;
   }

   virtual ~MaxHeap() {
      delete[] heapArray;
   }

   void Insert(int value) {
      // Resize if needed
      if (heapSize == allocationSize) {
         ResizeArray();
      }

      // Add the new value to the end of the array
      std::cout << "Insert(" << value << "):" << std::endl;
      heapArray[heapSize] = value;
      heapSize++;

      // Percolate up from the last index to restore heap property
      PercolateUp(heapSize - 1);
   }

   int Remove() {
      // Save the max value from the root of the heap
      std::cout << "Remove():" << std::endl;
      int maxValue = heapArray[0];

      // Move the last item in the array into index 0
      int replaceValue = heapArray[heapSize - 1];
      heapSize--;
      if (heapSize > 0) {
         heapArray[0] = replaceValue;

         // Percolate down to restore max-heap property
         PercolateDown(0);
      }

      // Return the max value
      return maxValue;
   }

   std::string GetHeapArrayString() {
      if (heapSize == 0) {
         return std::string("[]");
      }

      std::string arrayString("[");
      arrayString += std::to_string(heapArray[0]);
      for (int i = 1; i < heapSize; i++) {
         arrayString += ", ";
         arrayString += std::to_string(heapArray[i]);
      }
      arrayString += "]";
      return arrayString;
   }

   int GetHeapSize() {
      return heapSize;
   }
};

#endif
```

**`main.cpp`**

```cpp
#include <vector>
#include "MaxHeap.h"
using namespace std;

int main() {
   MaxHeap maxHeap;
   vector<int> numbers = { 10, 2, 5, 18, 22 };

   // Add all numbers to the heap
   for (int number : numbers) {
      maxHeap.Insert(number);
      cout << "   --> array: " << maxHeap.GetHeapArrayString() << endl;
   }

   while (maxHeap.GetHeapSize() > 0) {
      int removedValue = maxHeap.Remove();
      cout << "   --> removed " << removedValue << ", array: ";
      cout << maxHeap.GetHeapArrayString() << endl;
   }
}
```

### Parent and child indices

The array *is* the tree — no pointers are stored. Instead, a node's relatives are computed directly from its index `i`:

- **Left child:** `2i + 1`
- **Right child:** `2i + 2`
- **Parent:** `(i - 1) / 2` (integer division)

| Node index | Parent index | Child indices |
|---|---|---|
| 0 | N/A | 1, 2 |
| 1 | 0 | 3, 4 |
| 2 | 0 | 5, 6 |
| 3 | 1 | 7, 8 |
| 4 | 1 | 9, 10 |
| 5 | 2 | 11, 12 |
| ... | ... | ... |

This is exactly why the code writes `childIndex = 2 * nodeIndex + 1` in `PercolateDown` and `parentIndex = (nodeIndex - 1) / 2` in `PercolateUp`.

### Visualizing the tree operations

Remember the array *is* the tree: index `i`'s children live at `2i+1` and `2i+2`, and its parent at `(i-1)/2`. Below, each insert/remove is shown as the underlying binary tree so you can see `PercolateUp`/`PercolateDown` moving a value along a single root-to-leaf path.

#### `Insert(18)` — percolate **up**

Starting heap after inserting `10, 2, 5` → array `[10, 2, 5]`:

```
      10
     /  \
    2    5
```

Append `18` at the next free leaf (index 3, left child of `2`). Heap property is now violated (`18 > 2`):

```
        10
       /  \
     (2)   5          array: [10, 2, 5, 18]
     /
   [18]               [18] just inserted, (2) is its parent
```

`PercolateUp`: `18 > 2`, so swap with parent:

```
        10
       /  \
    [18]   5          swap: 2 <-> 18
     /
    2                 array: [10, 18, 5, 2]
```

Continue: `18 > 10`, swap with parent again. Now `18` is the root, so we stop:

```
      [18]
      /  \
    10    5           swap: 10 <-> 18
    /
   2                  array: [18, 10, 5, 2]
```

#### `Insert(22)` — percolate **up**

Append `22` at the next free leaf (index 4, right child of `10`). Violation: `22 > 10`:

```
        18
       /  \
     (10)  5          array: [18, 10, 5, 2, 22]
     /  \
    2   [22]          [22] just inserted, (10) is its parent
```

`PercolateUp`: `22 > 10`, swap with parent:

```
        18
       /  \
    [22]   5          swap: 10 <-> 22
     /  \
    2    10           array: [18, 22, 5, 2, 10]
```

Continue: `22 > 18`, swap with parent. `22` is now the root, so we stop:

```
       [22]
       /  \
     18    5          swap: 18 <-> 22
     /  \
    2    10           array: [22, 18, 5, 2, 10]
```

#### `Remove()` — percolate **down** (removes 22)

`Remove` always returns the root. Save `22`, then move the **last leaf** (`10`) into the root and shrink the heap:

```
       [10]
       /  \
     18    5          root replaced by last leaf; array: [10, 18, 5, 2]
     /
    2                 returned max = 22
```

`PercolateDown`: the larger child of `10` is `18` (`18 > 5`), and `18 > 10`, so swap down:

```
       [18]
       /  \
     10    5          swap: 10 <-> 18
     /
    2                 array: [18, 10, 5, 2]
```

Now `10`'s only child is `2`, and `10 > 2` — heap property holds, so we stop. Final: `[18, 10, 5, 2]`.

#### `Remove()` — percolate **down** (removes 18)

Save `18`, move the last leaf (`2`) into the root and shrink:

```
      [2]
      /  \
    10    5           root replaced by last leaf; array: [2, 10, 5]
```

`PercolateDown`: the larger child of `2` is `10` (`10 > 5`), and `10 > 2`, so swap down. `2` is now a leaf, so we stop:

```
      [10]
      /  \
     2    5           swap: 2 <-> 10; array: [10, 2, 5]
```

The remaining removes shrink the heap the same way: `Remove()` → `10` (heap `[5, 2]`), `Remove()` → `5` (heap `[2]`), `Remove()` → `2` (heap `[]`). Popping the root repeatedly yields the values in descending order — the core idea behind heap sort.

---

## Priority Queue Implemented with a Heap

The largest element is always at index 0 (the root), so `Dequeue` is trivial to *find*; the work is in restoring the heap.

- **Dequeue:** save the root, move the last leaf into the root, shrink the heap, then `ReheapDown` from the root.
- **Enqueue:** place the new item in the next free leaf (preserves shape), then `ReheapUp` from that leaf.

```
Dequeue                                Enqueue
    Set item to root element               Increment length
    Move last leaf element into root       Put newItem in next available position
    Decrement length                       items.ReheapUp(0, length - 1)
    items.ReheapDown(0, length - 1)
```

### PQType class

```cpp
class FullPQ  {};
class EmptyPQ {};

template<class ItemType>
class PQType
{
public:
    PQType(int);
    ~PQType();

    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull() const;
    void Enqueue(ItemType newItem);
    void Dequeue(ItemType& item);
private:
    int length;
    HeapType<ItemType> items;
    int maxItems;
};

template<class ItemType>
PQType<ItemType>::PQType(int max)
{
    maxItems = max;
    items.elements = new ItemType[max];
    length = 0;
}

template<class ItemType>
void PQType<ItemType>::MakeEmpty()
{
    length = 0;
}

template<class ItemType>
PQType<ItemType>::~PQType()
{
    delete [] items.elements;
}
```

### Enqueue / Dequeue implementations

```cpp
template<class ItemType>
void PQType<ItemType>::Dequeue(ItemType& item)
// Post: element with highest priority has been removed
//       from the queue; a copy is returned in item.
{
    if (length == 0)
        throw EmptyPQ();
    else
    {
        item = items.elements[0];
        items.elements[0] = items.elements[length - 1];
        length--;
        items.ReheapDown(0, length - 1);
    }
}

template<class ItemType>
void PQType<ItemType>::Enqueue(ItemType newItem)
// Post: newItem is in the queue.
{
    if (length == maxItems)
        throw FullPQ();
    else
    {
        length++;
        items.elements[length - 1] = newItem;
        items.ReheapUp(0, length - 1);
    }
}

template<class ItemType>
bool PQType<ItemType>::IsFull() const
{
    return length == maxItems;
}

template<class ItemType>
bool PQType<ItemType>::IsEmpty() const
{
    return length == 0;
}
```

### Efficiency comparison

- `Enqueue`: O(1) to place + O(log N) `ReheapUp` = **O(log N)**.
- `Dequeue`: O(1) to swap + O(log N) `ReheapDown` = **O(log N)**.

| Implementation | Enqueue | Dequeue |
|---|---|---|
| **Heap** | O(log N) | O(log N) |
| Linked list (sorted) | O(N) | O(1) |
| Binary search tree (balanced) | O(log N) | O(log N) |
| Binary search tree (skewed) | O(N) | O(N) |

The heap wins overall: it is always minimum height (so it never degenerates like a skewed BST), and a priority queue never needs to access a random element — only the maximum.

---

## 9.4 Heap Sort

A selection sort repeatedly finds the maximum value and swaps it into place; the cost is the **O(N) search** for the next maximum each pass. A heap removes that cost: the maximum is *always* at the root, and reheaping is only **O(log N)**.

**General approach**

1. Take the root (max) element off the heap and put it in its place.
2. Reheap the remaining elements (next-largest moves to the root).
3. Repeat until no elements are left.

### Step 1 — Building the heap in place

The unsorted array already satisfies the **shape** property (no holes). We only need the **order** property. All leaf nodes are already trivially heaps, so we call `ReheapDown` on each non-leaf node **from the bottom up**.

- The **first non-leaf** node is at index `numValues / 2 - 1` (half the nodes of a complete tree are leaves).
- For heap sort, `ReheapDown` is used as a **global function** taking the array as an extra parameter (so it works directly on `values[]` without a `HeapType` struct).

```
BuildHeap
    for index going from first nonleaf node up to the root node
        ReheapDown(values, index, numValues - 1)
```

### Step 2 — Sorting with the heap

Swap the root (max) with the last heap element; that position is now in its final sorted spot, so shrink the heap by one and `ReheapDown`. The **sorted portion grows** from the right while the **heap shrinks** — both share the one array.

```
Sort Nodes
    for index going from last node up to next-to-root node
        Swap data in root node with values[index]
        ReheapDown(values, 0, index - 1)
```

### HeapSort implementation

```cpp
template<class ItemType>
void HeapSort(ItemType values[], int numValues)
// Assumption: Function ReheapDown is available.
// Post: The elements in the array values are sorted by key.
{
    int index;

    // Convert the array of values into a heap.
    for (index = numValues / 2 - 1; index >= 0; index--)
        ReheapDown(values, index, numValues - 1);

    // Sort the array.
    for (index = numValues - 1; index >= 1; index--)
    {
        Swap(values[0], values[index]);
        ReheapDown(values, 0, index - 1);
    }
}
```

### Analysis

- `ReheapDown` is O(log₂N).
- Building the heap uses ~N calls; sorting uses ~N more calls.
- Total: **O(N log₂N)**.
- The heap is only a **temporary internal structure** — it lives inside the array and is diminished element by element as the sorted portion grows. Using an *external* heap would have cost twice the memory.

### zyBooks `Heapsort` — a self-contained demo

The same two-phase algorithm (heapify, then repeatedly swap-and-reheap) as plain functions operating directly on a raw `int` array — no `HeapType` struct or templates. `MaxHeapPercolateDown` is the zyBooks name for `ReheapDown`, and it takes `heapSize` as a parameter so the "heap" can shrink while the sorted tail grows in the same array.

**`HeapsortDemo.cpp`**

```cpp
#include <iostream>
using namespace std;

void Heapsort(int* numbers, int numbersLength);
void MaxHeapPercolateDown(int nodeIndex, int* heapArray, int heapSize);

int main() {
   int numbers[] = { 82, 36, 49, 82, 34, 75, 18, 9, 23 };
   int numbersLength = sizeof(numbers) / sizeof(numbers[0]);
   cout << "UNSORTED: [";
   for (int i = 0; i < numbersLength - 1; i++) {
      cout << numbers[i] << ", ";
   }
   cout << numbers[numbersLength - 1] << "]" << endl;

   Heapsort(numbers, numbersLength);
   cout << "SORTED:   [";
   for (int i = 0; i < numbersLength - 1; i++) {
      cout << numbers[i] << ", ";
   }
   cout << numbers[numbersLength - 1] << "]" << endl;

   return 0;
}

// Sorts the array of numbers using the heapsort algorithm
void Heapsort(int* numbers, int numbersLength) {
   // Heapify numbers array
   for (int i = numbersLength / 2 - 1; i >= 0; i--) {
      MaxHeapPercolateDown(i, numbers, numbersLength);
   }

   for (int i = numbersLength - 1; i > 0; i--) {
      // Swap numbers[0] and numbers[i]
      int temp = numbers[0];
      numbers[0] = numbers[i];
      numbers[i] = temp;

      MaxHeapPercolateDown(0, numbers, i);
   }
}

// Performs a percolate-down operation in a max-heap
void MaxHeapPercolateDown(int nodeIndex, int* heapArray, int heapSize) {
   int childIndex = 2 * nodeIndex + 1;
   int value = heapArray[nodeIndex];

   while (childIndex < heapSize) {
      // Find the max among the node and all the node's children
      int maxValue = value;
      int maxIndex = -1;
      int i = 0;
      while (i < 2 && i + childIndex < heapSize) {
         if (heapArray[i + childIndex] > maxValue) {
            maxValue = heapArray[i + childIndex];
            maxIndex = i + childIndex;
         }
         i++;
      }

      if (maxValue == value) {
         return;
      }

      // Swap heapArray[nodeIndex] and heapArray[maxIndex]
      int temp = heapArray[nodeIndex];
      heapArray[nodeIndex] = heapArray[maxIndex];
      heapArray[maxIndex] = temp;

      nodeIndex = maxIndex;
      childIndex = 2 * nodeIndex + 1;
   }
}
```

Output:

```
UNSORTED: [82, 36, 49, 82, 34, 75, 18, 9, 23]
SORTED:   [9, 18, 23, 34, 36, 49, 75, 82, 82]
```

Note how `MaxHeapPercolateDown(0, numbers, i)` passes the shrinking size `i` as `heapSize`: everything at index `i` and beyond is already sorted and off-limits to the heap.

---

---

# Chapter 11 — Sets, Maps, and Hashing

## 11.1 Sets

### Logical level

A **set** is an *unordered collection of distinct values*, based on the mathematical concept.

- **Component (base) type:** the data type of the items in the set.
- **Subset:** a set whose items are entirely contained in another set.
- **Universal set:** the set of all possible values of the base type.
- **Empty set:** a set with no members.

**Operations**

- `Store`, `Delete` — add / remove an item.
- `Union` — combine two sets.
- `Intersection` — items found in **both** sets.
- `Difference` — items in the first set but **not** the second.
- `Cardinality` — number of items in the set.
- Observers `IsEmpty` / `IsFull`, transformer `MakeEmpty`, utility `Print`.

> Note: `Store`/`Delete` are technically redundant — `Store(x)` = union with `{x}`, `Delete(x)` = difference with `{x}` — but they make processing easier.

**Examples**

```
SetA = {A, B, D, G, Q, S}
SetB = {A, D, P, S, Z}

Union(SetA, SetB)        = {A, B, D, G, P, Q, S, Z}
Intersection(SetA, SetB) = {A, D, S}
Difference(SetA, SetB)   = {B, G, Q}
Difference(SetB, SetA)   = {P, Z}
```

### Application level

Storing an item that is *already* in the set does not change it; deleting an item that is *not* present does nothing. This makes sets ideal for tasks like collecting the distinct words/characters in a text.

### Implementation — two general approaches

- **Explicit representation:** record the presence *and* absence of **every** possible value of the base type.
- **Implicit representation:** record *only* the items actually in the set.

#### Explicit (bit vector) representation

Maps each item in the base type to a Boolean flag (`true` = present). A **bit vector** is an array of bits used as a compact list of these flags. Requires being able to enumerate every value of the base type — so it works best for **small base types** (e.g., the 26 uppercase letters → an array indexed 0–25).

- The empty set = all `false`; the universal set = all `true`.
- Binary operations use bitwise logic:
  - **Union** → OR the two bit vectors.
  - **Intersection** → AND the two bit vectors.
  - **Difference** → AND with the NOT (inversion) of the second bit vector.

```cpp
#include "map.h"
// map.h defines ItemType and a function "map" that maps an ItemType
// value into an index between 0 and max - 1 (or 0 and 399 for the
// default constructor).

class SetType
{
public:
    SetType();                       // Default constructor: array size 400
    SetType(int max);                // Parameterized constructor
    ~SetType();                      // Destructor
    SetType(const SetType& anotherSet); // Copy constructor
    void MakeEmpty();
    void Store(ItemType item);
    void Delete(ItemType item);
    bool IsEmpty();
    bool IsFull();
    int  CardinalityIs();
    SetType Union(SetType setB);
    SetType Intersection(SetType setB);
    SetType Difference(SetType setB);
    void Print(std::ofstream& outFile);
private:
    int maxItems;
    ItemType* items;
};
```

**Algorithms (explicit):**

```
Store(ItemType item)
    Set items[map(item)] to true

Delete(ItemType item)
    Set items[map(item)] to false

int Cardinality()
    Set count to 0
    for counter going from 0 to maxItems - 1
        if (items[counter])
            count++
    return count

Union(SetType setB)          // setA is self
    Set result.maxItems to maxItems
    for counter going from 0 to maxItems - 1
        result.items[counter] = items[counter] OR setB.items[counter]
    return result

Intersection(SetType setB)
    for counter going from 0 to maxItems - 1
        result.items[counter] = items[counter] AND setB.items[counter]
    return result

Difference(SetType setB)
    for counter going from 0 to maxItems - 1
        result.items[counter] = items[counter] AND NOT setB.items[counter]
    return result
```

> `IsFull` has no meaning for the explicit representation (every value has a slot).

#### Implicit representation

Store only the items that are actually in the set, using a list. Space is proportional to the set's cardinality (not the universal set's).

```cpp
class SetType
{
    // Set ItemType using a typedef statement.
public:
    SetType();
    SetType(int max);
    ~SetType();
    void MakeEmpty();
    void Store(ItemType item);
    void Delete(ItemType item);
    bool IsEmpty();
    bool IsFull();
    int  CardinalityIs();
    SetType Union(SetType setB);
    SetType Intersection(SetType setB);
    SetType Difference(SetType setB);
private:
    ListType items;   // implemented as a list
};
```

- `Store`: call `RetrieveItem` first; only `InsertItem` if the item is *not* already present (guarantees a single copy).
- `Delete`: call `RetrieveItem`; only delete if the item is actually present.

**Naive intersection — O(N²) or O(N log N):**

```
Intersection(SetType setB)         // self is setA
    Reset self
    for counter going from 1 to length
        GetNextItem(item) from self
        setB.RetrieveItem(item, found)
        if found
            result.Store(item)
    return result
```

**Faster O(N) intersection (merge)** — if `ItemType` overloads `<`, keep the underlying list *sorted* and walk both lists in parallel. (The set is still conceptually unordered; only the implementation is ordered.)

```
Intersection(SetType setB)
    Reset self
    Reset setB
    while NOT (self.IsEmpty OR setB.IsEmpty)
        GetNextItem(itemA) from self
        setB.GetNextItem(itemB)
        if (itemA < itemB)
            GetNextItem(itemA) from self
        else if (itemB < itemA)
            setB.GetNextItem(itemB)
        else                         // equal
            result.Store(itemA)
            GetNextItem(itemA) from self
            setB.GetNextItem(itemB)
    return result
```

This parallel walk of two ordered lists is called a **merge** and can implement all the binary operations in O(N).

#### Explicit vs. implicit

- Explicit must represent every base-type value (vector length = cardinality of the universal set) → best for **small** base types.
- Implicit must **search** the list to check membership → best when the universal set is large but individual sets are small.

#### Implicit representation using a BST

A binary search tree is an efficient way to store the items of an implicit set: `O(log n)` search/insert/delete on average, and an in-order traversal visits the elements in sorted order (handy for `Print` and for merge-style binary operations). The example below is a full, self-contained `Set` of `int` backed by a BST.

Key design points:

- **`BSTNode`** stores `data` plus `parent`, `left`, and `right` pointers. The `parent` pointer makes iteration and removal simpler. `GetSuccessor` returns the in-order successor (leftmost node of the right subtree, or the first ancestor reached from the left).
- **`BSTIterator`** wraps a node and walks the tree in-order via `GetSuccessor`, so a `Set` supports range-based `for` loops (`begin`/`end`).
- **`Set`** owns the tree (deep-copying copy constructor + destructor to avoid leaks/double frees). `Add` rejects duplicates by calling `Contains` first, guaranteeing uniqueness.
- The binary operations (`Union`, `Intersection`, `Difference`) and the higher-order `Filter` / `Map` are all implemented simply by iterating over the elements and building a new result `Set`.

**`Set.h`**

```cpp
#ifndef SET_H
#define SET_H

#include <functional>
#include <iterator>

class BSTNode {
public:
   int data;
   BSTNode* parent;
   BSTNode* left;
   BSTNode* right;

   BSTNode(int data, BSTNode* parent, BSTNode* left = nullptr, BSTNode* right = nullptr) {
      this->data = data;
      this->parent = parent;
      this->left = left;
      this->right = right;
   }

   int Count() {
      int leftCount = 0;
      int rightCount = 0;
      if (left) {
         leftCount = left->Count();
      }
      if (right) {
         rightCount = right->Count();
      }
      return 1 + leftCount + rightCount;
   }

   BSTNode* GetSuccessor() {
      // Successor resides in right subtree, if present
      if (right) {
         BSTNode* successor = right;
         while (successor->left != nullptr) {
            successor = successor->left;
         }
         return successor;
      }

      // Otherwise the successor is up the tree
      // Traverse up the tree until a parent is encountered from the left
      BSTNode* node = this;
      while (node->parent && node == node->parent->right) {
         node = node->parent;
      }
      return node->parent;
   }

   void ReplaceChild(BSTNode* currentChild, BSTNode* newChild) {
      if (currentChild == left) {
         left = newChild;
         if (left) {
            left->parent = this;
         }
      }
      else if (currentChild == right) {
         right = newChild;
         if (right) {
            right->parent = this;
         }
      }
   }
};

class BSTIterator {
private:
    BSTNode* currentNode;

public:
   BSTIterator(const BSTIterator& copyMe) {
      currentNode = copyMe.currentNode;
   }

   BSTIterator(BSTNode* startNode) {
      currentNode = startNode;
   }

   bool operator==(const BSTIterator& rhs) const {
      return currentNode == rhs.currentNode;
   }

   bool operator!=(const BSTIterator& rhs) const {
      return currentNode != rhs.currentNode;
   }

   // Dereference operator
   int& operator*() const {
      return currentNode->data;
   }

   // Pre-increment operator
   BSTIterator& operator++() {
      if (currentNode) {
         currentNode = currentNode->GetSuccessor();
      }
      return *this;
   }

   // Post-increment operator
   BSTIterator operator++(int) {
      BSTIterator previous(*this);
      if (currentNode) {
         currentNode = currentNode->GetSuccessor();
      }
      return previous;
   }
};

class Set {
private:
   BSTNode* root;

   BSTNode* CopySubtree(BSTNode* subtreeRoot, BSTNode* parent = nullptr) {
      BSTNode* newNode = nullptr;
      if (subtreeRoot) {
         newNode = new BSTNode(subtreeRoot->data, parent);
         newNode->left = CopySubtree(subtreeRoot->left, newNode);
         newNode->right = CopySubtree(subtreeRoot->right, newNode);
      }
      return newNode;
   }

   void DeleteTree(BSTNode* treeRoot) {
      if (treeRoot) {
         DeleteTree(treeRoot->left);
         DeleteTree(treeRoot->right);
         delete treeRoot;
      }
   }

   BSTNode* NodeSearch(int element) const {
      // Search the BST
      BSTNode* node = root;
      while (node) {
         // Compare node's data against the search element
         if (element == node->data) {
            return node;
         }
         else if (element > node->data) {
            node = node->right;
         }
         else {
            node = node->left;
         }
      }
      return node;
   }

   void RemoveNode(BSTNode* nodeToRemove) {
      if (nodeToRemove == nullptr) {
         return;
      }

      // Case 1: Internal node with 2 children
      if (nodeToRemove->left && nodeToRemove->right) {
         BSTNode* successor = nodeToRemove->GetSuccessor();

         // Copy the data value from the successor
         int dataCopy = successor->data;

         // Remove successor
         RemoveNode(successor);

         // Replace nodeToRemove's data with successor data
         nodeToRemove->data = dataCopy;
      }

      // Case 2: Root node (with 1 or 0 children)
      else if (nodeToRemove == root) {
         if (nodeToRemove->left) {
            root = nodeToRemove->left;
         }
         else {
            root = nodeToRemove->right;
         }

         if (root) {
            root->parent = nullptr;
         }

         delete nodeToRemove;
      }

      // Case 3: Internal node with left child only
      else if (nodeToRemove->left) {
         nodeToRemove->parent->ReplaceChild(nodeToRemove, nodeToRemove->left);
         delete nodeToRemove;
      }

      // Case 4: Internal node with right child only, or leaf node
      else {
         nodeToRemove->parent->ReplaceChild(nodeToRemove, nodeToRemove->right);
         delete nodeToRemove;
      }
   }

public:
   Set() {
      root = nullptr;
   }

   // Copy constructor
   Set(const Set& copyMe) {
      root = CopySubtree(copyMe.root);
   }

   virtual ~Set() {
      DeleteTree(root);
   }

   bool Add(int newElement) {
      if (Contains(newElement)) {
         return false;
      }

      BSTNode* newNode = new BSTNode(newElement, nullptr);

      // Special case for empty set
      if (root == nullptr) {
         root = newNode;
         return true;
      }

      BSTNode* node = root;
      while (node) {
         if (newElement < node->data) {
            // Go left
            if (node->left) {
               node = node->left;
            }
            else {
               node->left = newNode;
               newNode->parent = node;
               node = nullptr;
            }
         }
         else {
            // Go right
            if (node->right) {
               node = node->right;
            }
            else {
               node->right = newNode;
               newNode->parent = node;
               node = nullptr;
            }
         }
      }
      return true;
   }

   bool Contains(int element) const {
      return NodeSearch(element) != nullptr;
   }

   Set Difference(const Set& otherSet) const {
      Set result;
      for (int element : *this) {
         if (!otherSet.Contains(element)) {
            result.Add(element);
         }
      }
      return result;
   }

   Set Filter(std::function<bool(int)> predicate) const {
      Set result;
      for (int element : *this) {
         if (predicate(element)) {
            result.Add(element);
         }
      }
      return result;
   }

   Set Intersection(const Set& otherSet) const {
      Set result;
      for (int element : *this) {
         if (otherSet.Contains(element)) {
            result.Add(element);
         }
      }
      return result;
   }

   Set Map(std::function<int(int)> mapFunction) const {
      Set result;
      for (int element : *this) {
         int newElement = mapFunction(element);
         result.Add(newElement);
      }
      return result;
   }

   void Remove(int element) {
      RemoveNode(NodeSearch(element));
   }

   int Size() const {
      if (root) {
         return root->Count();
      }
      return 0;
   }

   Set Union(const Set& otherSet) const {
      Set result;
      for (int element : *this) {
         result.Add(element);
      }
      for (int element : otherSet) {
         result.Add(element);
      }
      return result;
   }

   BSTIterator begin() const {
      // Special case for empty set
      if (root == nullptr) {
         return BSTIterator(nullptr);
      }

      // Start the iterator at the minimum node
      BSTNode* minNode = root;
      while (minNode->left) {
         minNode = minNode->left;
      }
      return BSTIterator(minNode);
   }

   BSTIterator end() const {
      return BSTIterator(nullptr);
   }
};

#endif
```

**`main.cpp`** — exercises the set operations, plus the higher-order `Filter` and `Map`:

```cpp
#include <iostream>
#include <string>
#include "Set.h"
using namespace std;

bool IsEven(int value) {
   return value % 2 == 0;
}

bool IsOver50(int value) {
   return value > 50;
}

int Times10(int value) {
   return value * 10;
}

int Mod10(int value) {
   return value % 10;
}

void ShowSet(const Set& set, const string& setName) {
   cout << setName << ": ";
   for (int element : set) {
      cout << element << " ";
   }
   cout << endl;
}

int main() {
   int setAElements[] = { 95, 64, 19, 67, -24, 90 };
   int setBElements[] = { 67, 90, 67, 42, -84 };

   Set setA;
   Set setB;
   for (int element : setAElements) {
      setA.Add(element);
   }
   for (int element : setBElements) {
      setB.Add(element);
   }

   // Show the 2 sets
   ShowSet(setA, "Set A");
   ShowSet(setB, "Set B");

   // Perform union, intersection, and difference of 2 sets
   ShowSet(setA.Union(setB), "A union B");
   ShowSet(setA.Intersection(setB), "A intersect B");
   ShowSet(setA.Difference(setB), "A \\ B");
   ShowSet(setB.Difference(setA), "B \\ A");

   // Perform various filter operations
   ShowSet(setA.Filter(IsEven), "Set A filtered for evens");
   ShowSet(setB.Filter(IsEven), "Set B filtered for evens");
   ShowSet(setA.Filter(IsOver50), "Set A filtered for elements > 50");
   ShowSet(setB.Filter(IsOver50), "Set B filtered for elements > 50");

   // Perform various map operations
   ShowSet(setA.Map(Times10), "Set A mapped * 10");
   ShowSet(setB.Map(Times10), "Set B mapped * 10");
   ShowSet(setA.Map(Mod10), "Set A mapped % 10");
   ShowSet(setB.Map(Mod10), "Set B mapped % 10");
}
```

Because the BST is walked in-order, every printed set comes out **sorted ascending**, and duplicates (like the repeated `67` added to Set B) are silently ignored — exactly the "unordered collection of distinct values" semantics of a set.

### The C++ standard library set

Rather than writing your own set, the standard library provides ready-made containers. **`std::unordered_set`** (from `<unordered_set>`) stores an unordered collection of distinct values backed by a hash table, giving **average O(1)** insertion, removal, and lookup. (A related container, `std::set`, keeps its elements sorted using a balanced BST with O(log n) operations.)

The most commonly used member functions, illustrated starting with `exSet: { "Bread", "Jam", "Butter" }`:

| Member function | Usage and description | Example |
| --- | --- | --- |
| `insert()` | `unorderedSetInstance.insert(item)` — Inserts a new item into the `unordered_set`. Has no effect if the item is already in the set. | `exSet.insert("Milk");`<br>`exSet.insert("Jam");`<br><br>`exSet: { "Bread", "Jam", "Butter", "Milk" }` |
| `erase()` | `unorderedSetInstance.erase(item)` — Removes an item from the `unordered_set`. Returns 1 if the item was found and removed, 0 otherwise. | `exSet.erase("Jam");     // Returns 1`<br>`exSet.erase("Cookies"); // Returns 0`<br><br>`exSet: { "Bread", "Butter" }` |
| `size()` | `unorderedSetInstance.size()` — Returns the `unordered_set`'s length. | `cout << exSet.size();`<br><br>Output: `3` |
| `count()` | `unorderedSetInstance.count(item)` — Returns 1 if the `unordered_set` contains the item argument, 0 otherwise. | `cout << exSet.count("Cereal");`<br>`cout << endl;`<br>`cout << exSet.count("Bread");`<br><br>Output:<br>`0`<br>`1` |

**`main.cpp`** — inserting items, checking membership with `count()`, and removing with `erase()`:

```cpp
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

template <typename T>
void PrintSet(const unordered_set<T>& setToPrint, string separator = ", ",
   string suffix = "");

int main() {
   // Declare items to insert
   vector<string> itemsToInsert = {
      "Bread", "Butter", "Jam", "Milk", "Cereal"
   };
   
   // Create the unordered_set, insert items, then print
   unordered_set<string> groceryItems;
   for (const string& item : itemsToInsert) {
      groceryItems.insert(item);
      cout << "Inserted \"" << item << "\"" << endl;
   }
   PrintSet(groceryItems, ", ", "\n");
   
   // Declare an item to search for and remove if found
   string itemName = "Butter";
   
   // Search for the item using count()
   cout << "Set contains \"" << itemName << "\"? ";
   if (1 == groceryItems.count(itemName)) {
      cout << "Yes\nNow removing \"" << itemName << "\"" << endl;
      groceryItems.erase(itemName);
   }
   else {
      cout << "No" << endl;
   }
   
   PrintSet(groceryItems, ", ", "\n");
   
   return 0;
}

template <typename T>
void PrintSet(const unordered_set<T>& setToPrint, string separator,
   string suffix) {
   
   bool printedFirst = false;
   
   cout << "Set with " << setToPrint.size() << " items: {";
   for (const T& item : setToPrint) {
      if (printedFirst) {
         cout << separator << item;
      }
      else {
         cout << item;
         printedFirst = true;
      }
   }
   
   // Print the closing "}" and the suffix
   cout << "}" << suffix;
}
```

Because `unordered_set` is hash-based, iteration order is **unspecified** — the items may print in any order, and `insert()` silently ignores duplicates just like our custom `Set`.

---

## 11.2 Maps

### Logical level

A **map** is a collection of **key-value pairs**.

- **Key:** a value from the base type, used to look up an associated value.
- **Key-value pair:** an item consisting of a key and its associated value.

Like sets, maps store **unordered, unique** values. Unlike sets, maps have **no mathematical basis** — they do *not* support Union / Intersection / Difference. Instead they support **`Find`**: retrieve a key-value pair by searching for its key. `ItemType` must contain both the key and the value, and should support `==` and `<`.

### Application level

An array is essentially a map that uses integers as keys. A map generalizes this to keys that **cannot easily be converted into array indices** — e.g., mapping names → phone numbers, or a paint-chip name → its pigment formula.

### Implementation level

The most common operations are `Store` and `Find`, and maps are usually built once and then queried heavily → we want fast search. A **binary search tree** is a natural fit (efficient search, insert, delete).

```cpp
class MapType
{
public:
    MapType();                       // Default constructor
    ~MapType();                      // Destructor
    MapType(const MapType& anotherMap); // Copy constructor
    void MakeEmpty();
    void Store(ItemType item);
    void Delete(ItemType item);
    bool IsEmpty();
    bool IsFull();
    ItemType Find(ItemType item, bool& found);
    void Print(std::ofstream& outFile);
private:
    TreeType items;
};
```

Most `MapType` methods simply delegate to `TreeType`: `Find` → `GetItem`, `Delete` → `DeleteItem`, etc. The one new algorithm is `Store` (which must check for duplicates first, since `TreeType::PutItem` assumes the item isn't already present):

```
Store(ItemType item)
    ItemType someItem
    bool found
    Set someItem to GetItem, given item and found
    if not found
        items.PutItem(item)
```

**Other design approaches for `Find`:**

- Make `Find` a `void` function using an empty/dummy value or a `bool found` flag rather than throwing on failure — useful so that a search never "fails."
- The **C++ STL** overloads `[]` so a map can be treated like an array indexed by its keys (implemented internally with iterators; a search returns an iterator that points to a sentinel item on failure).

---

## 11.3 Hashing

### The goal: O(1) search

Sorted lists give O(log₂N) search. Can we do **O(1)**? Only if there is a **one-to-one mapping between keys and array indices**.

- Example that works: 100 employees with IDs 0–99, stored directly in `array[ID]`.
- Example that fails: 5-digit IDs (00000–99999) for only a few hundred employees would waste an array of 100,000 slots.

### Hash functions

- **Hashing:** ordering/accessing elements by manipulating the key to compute a location.
- **Hash function:** a function that manipulates the key to produce an array index.

For 5-digit IDs stored in a 100-slot array, use `Key % 100` (last two digits):

```cpp
int ItemType::Hash() const
// Post: Returns an integer between 0 and MAX_ITEMS - 1.
{
    return (idNum % MAX_ITEMS);
}
```

The hash function is used **both** to *store* an element and to *retrieve* it — they must use the *same* function, otherwise retrieval won't find what insertion stored.

```cpp
template<class ItemType>
void ListType<ItemType>::RetrieveItem(ItemType& item)
// Post: Returns the element in the array at position item.Hash().
{
    int location;
    location = item.Hash();
    item = info[location];
}

template<class ItemType>
void ListType<ItemType>::InsertItem(ItemType item)
// Post: item is stored in the array at position item.Hash().
{
    int location;
    location = item.Hash();
    info[location] = item;
    length++;
}
```

### Collisions

A **collision** occurs when two or more keys produce the same hash location (e.g., `01234` and `91234` both hash to `34` under `Key % 100`). A good hash function *minimizes* collisions by distributing elements uniformly, but they can't be entirely avoided.

---

### Collision resolution 1 — Linear probing

Store a colliding element in the **next available slot**, treating the array as circular (`(location + 1) % MAX_ITEMS`). To search, hash and then scan sequentially until the key is found, an empty slot is found, or we loop back to the start.

Empty slots are marked with a special `emptyItem` value (syntactically legal, semantically illegal — e.g., an ID of `-1`).

```cpp
template<class ItemType>
void ListType<ItemType>::InsertItem(ItemType item)
// Post: item is stored at position item.Hash() or the next free spot.
{
    int location;
    location = item.Hash();
    while (info[location] != emptyItem)
        location = (location + 1) % MAX_ITEMS;
    info[location] = item;
    length++;
}

template<class ItemType>
void ListType<ItemType>::RetrieveItem(ItemType& item, bool& found)
{
    int location;
    int startLoc;
    bool moreToSearch = true;
    startLoc = item.Hash();
    location = startLoc;
    do
    {
        if (info[location] == item || info[location] == emptyItem)
            moreToSearch = false;
        else
            location = (location + 1) % MAX_ITEMS;
    } while (location != startLoc && moreToSearch);

    found = (info[location] == item);
    if (found)
        item = info[location];
}
```

**Linear probing and deletion.** Simply setting a deleted slot back to `emptyItem` breaks search: if three keys collide, the middle one is deleted, and we then search for the third, the search stops at the now-empty middle slot and wrongly reports "not found." **Fix:** use a third special value, `deletedItem`, meaning "free now, but previously occupied." Insertion treats `deletedItem` like `emptyItem` (stop and reuse); retrieval does **not** stop on `deletedItem` (keep looking). Downside: many deletions leave long trails of `deletedItem` slots, degrading efficiency — so a plain probing hash table isn't ideal when many deletions occur.

**Clustering.** Even with a uniform hash function, linear probing causes **clustering** — elements bunch together around popular hash locations, making insertion/retrieval less efficient. In a cluster, a slot right after the cluster is far more likely to be filled next than an isolated slot.

---

### Collision resolution 2 — Rehashing

**Rehashing:** feed the *hash value* (not the key) into another function to compute a new location. Linear probing is just rehashing with `(HashValue + 1) % size`. The general linear-probing rehash is:

```
(HashValue + constant) % array-size
```

`constant` and `array-size` must be **relatively prime** (GCD = 1) so that repeated rehashing eventually covers **every** index. Example: `(HashValue + 3) % 100` (3 and 100 are relatively prime). A bad choice like `(HashValue + 2) % 100` only ever visits odd or even slots and can fail to find a free slot even when one exists.

**Quadratic probing:** the increment depends on how many times (I) the rehash has been applied:

```
(HashValue ± I²) % array-size
```

(first rehash +1, second −1, third +4, fourth −4, …). Reduces clustering, but does **not** necessarily examine every slot — unless `array-size` is a prime of the form `4 * k + 3`.

**Random probing:** use a pseudorandom generator for the increment. Eliminates clustering, but is slower than the other techniques.

---

### Collision resolution 3 — Buckets and Chaining

Allow multiple elements to share a hash location.

- **Bucket:** each hash location holds slots for several elements. When a bucket fills up, you're back to handling collisions again.
- **Chain:** the hash table stores **pointers** to linked lists; all elements that hash to the same location live on that location's chain.

**Chaining advantages over probing:**

- **Search** is limited to elements that *actually* share the hash location (a short chain), rather than scanning unrelated elements filled in by other collisions.
- **Deletion** is simple: just remove the node from the linked list (no `deletedItem` sentinel needed).

---

### Choosing a good hash function

- Make the table **larger** than the number of elements needed (space-vs-time tradeoff) to reduce collisions; best results when the table size is a **prime number**.
- Know the **statistical distribution** of your keys. A classic failure: hashing 6-digit employee IDs with `idNum % 100` where the last two digits are the *year hired* — a company founded in 1987 crowds nearly all records into a few slots, degrading search to O(N).

**Division method** — the most common:

```
Key % TableSize
```

Simple and efficient, though collisions can still be common.

**Hashing non-integer keys.** The division method needs integers. For strings, sum the characters' integer codes first:

```cpp
int Hash(char letters[])
// Post: Returns an integer between 0 and MAX_ITEMS - 1.
{
    int sum = 0;
    for (int index = 0; index < 5; index++)
        sum = sum + int(letters[index]);
    return sum % MAX_ITEMS;
}
```

**Folding.** Break the key into several pieces and **concatenate or XOR** them to form the hash value. Example (32-bit key → 8-bit index in 0–255): split into four 8-bit chunks, XOR the first and last, XOR the two middle ones, then XOR those two results into the final 8-bit index. Folding produces indices with no intuitive relationship to the key but a good, uniform distribution.

**Two considerations for exotic hash functions:**

1. **Efficiency** — a hash table gives O(1) search only if the hash function is fast to compute; a slow function defeats the purpose.
2. **Simplicity** — hash functions must be written and maintained; overly complex functions carry a technical cost. Perfect (collision-free) hash functions are hard but possible, especially for small, known sets of values.

---

## Quick Reference

| Topic | Key takeaway |
|---|---|
| Priority queue | Access only the highest-priority element; heap gives O(log N) enqueue/dequeue |
| Heap | Complete tree (shape) + parent ≥ children (order); max at root |
| Array indices | left `2i+1`, right `2i+2`, parent `(i-1)/2` |
| ReheapDown / ReheapUp | Restore order property downward / upward; O(log N) |
| Heap sort | Build heap in place, repeatedly swap root to the end + reheap; O(N log N) |
| Set | Unordered, distinct values; explicit (bit vector) vs. implicit (list) |
| Sorted implicit intersection | Merge two ordered lists → O(N) |
| Map | Key-value pairs; no set algebra; usually backed by a BST; supports Find |
| Hashing | Compute index from key for ~O(1) access |
| Collision handling | Linear/quadratic/random probing, rehashing, buckets, chaining |
| Deletion under probing | Needs a `deletedItem` sentinel; chaining avoids this |
