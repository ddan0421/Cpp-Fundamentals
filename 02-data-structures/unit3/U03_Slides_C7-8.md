# Unit 3 Lecture Notes: Recursion & Binary Search Trees

> Combined lecture notes for **Chapter 7 — Programming with Recursion** and
> **Chapter 8 — Binary Search Trees**. Concepts are drawn from the chapter
> slide decks; all C++ code is taken from the course textbook
> (*C++ Plus Data Structures*, Nell Dale).

---

## Table of Contents

1. [Chapter 7: Programming with Recursion](#chapter-7-programming-with-recursion)
   - [What Is Recursion?](#what-is-recursion)
   - [The Classic Example: Factorial](#the-classic-example-factorial)
   - [Anatomy of a Recursive Function](#anatomy-of-a-recursive-function)
   - [Verifying Recursion: The Three-Question Method](#verifying-recursion-the-three-question-method)
   - [Writing Recursive Functions](#writing-recursive-functions)
   - [Example: Searching a List](#example-searching-a-list)
   - [Using Recursion to Simplify: Combinations](#using-recursion-to-simplify-combinations)
   - [Recursive Linked-List Processing: RevPrint](#recursive-linked-list-processing-revprint)
   - [Recursive Binary Search](#recursive-binary-search)
   - [Recursive PutItem and DeleteItem](#recursive-putitem-and-deleteitem)
   - [How Recursion Works (Under the Hood)](#how-recursion-works-under-the-hood)
   - [Recursive Quick Sort](#recursive-quick-sort)
   - [Supplemental: Forms of Recursion](#supplemental-forms-of-recursion)
   - [Debugging & Removing Recursion](#debugging--removing-recursion)
   - [Deciding When to Use Recursion](#deciding-when-to-use-recursion)
2. [Chapter 8: Binary Search Trees](#chapter-8-binary-search-trees)
   - [Searching Review](#searching-review)
   - [Trees: Vocabulary](#trees-vocabulary)
   - [Level, Height, and Efficiency](#level-height-and-efficiency)
   - [The Binary Search Property](#the-binary-search-property)
   - [The TreeType Class](#the-treetype-class)
   - [IsFull / IsEmpty](#isfull--isempty)
   - [GetLength / CountNodes](#getlength--countnodes)
   - [GetItem / Retrieve](#getitem--retrieve)
   - [PutItem / Insert](#putitem--insert)
   - [DeleteItem / Delete](#deleteitem--delete)
   - [Print and Tree Traversals](#print-and-tree-traversals)
   - [Constructor, Destructor, MakeEmpty](#constructor-destructor-makeempty)
   - [Copying a Tree](#copying-a-tree)
   - [ResetTree and GetNextItem](#resettree-and-getnextitem)
   - [Iterative BST Operations](#iterative-bst-operations)
   - [Recursion or Iteration?](#recursion-or-iteration)
   - [BSTs vs. Linear Lists: Big-O](#bsts-vs-linear-lists-big-o)

---

# Chapter 7: Programming with Recursion

## What Is Recursion?

**Recursion** is a powerful programming technique in which a function calls
itself in order to divide work into smaller portions.

- **Recursive call:** when the function being called is the same as the one
  making the call.
- **Direct recursion:** a function calls itself directly.
- **Indirect recursion:** a chain of function calls eventually leads back to
  the function that started the chain (A calls B, B calls A).

> Analogy: a recursive definition is like a set of Russian nesting dolls — each
> doll contains a smaller version of itself until you reach the smallest doll
> that cannot be subdivided.

Recursion is supported by languages that use **dynamic storage allocation**
(such as C++). Some early languages (FORTRAN, BASIC, COBOL) did not allow it.

---

## The Classic Example: Factorial

The factorial function `n!` is the classic mathematical example of recursion:

```
4! = 4 * 3 * 2 * 1 = 24
```

Its **recursive definition** is:

```
n! = 1                if n = 0      (base case)
n! = n * (n - 1)!     if n > 0      (general case)
```

Expanding `4!` shows the recursion in action:

```
4! = 4 * 3! = 4 * 3 * 2! = 4 * 3 * 2 * 1! = 4 * 3 * 2 * 1 * 0! = 4 * 3 * 2 * 1 * 1 = 24
```

### Code: Iterative vs. Recursive Factorial

```cpp
// Iterative solution
int Factorial(int number)
{
    int fact = 1;
    for (int count = 2; count <= number; count++)
        fact = fact * count;
    return fact;
}
```

```cpp
// Recursive solution
int Factorial(int number)
// Pre:  number is nonnegative.
// Post: Function value = factorial of number.
{
    if (number == 0)                       // Base case
        return 1;
    else                                   // General case
        return number * Factorial(number - 1);
}
```

**Recursive vs. iterative differences:**

- The iterative version uses a **looping** construct (`for`); the recursive
  version uses a **branching** construct (`if`/`else`).
- The iterative version uses local variables; the recursive version uses its
  **parameters** to carry state. (Sometimes recursive solutions need extra
  parameters.)

---

## Anatomy of a Recursive Function

Key vocabulary:

- **Recursive definition:** something defined in terms of a smaller version of
  itself.
- **Base case:** the case for which the solution is stated *non*recursively
  (`n! = 1 if n = 0`). There must be at least one base case.
- **General (recursive) case:** the case defined using recursion
  (`n! = n * (n-1)! if n > 0`).
- **Recursive algorithm:** an algorithm expressed in terms of (1) smaller
  instances of itself and (2) a base case.

> **Every possible chain of recursive calls must eventually reach a base case.**
> Each recursive call should make progress toward a base case.

---

## Verifying Recursion: The Three-Question Method

Walking through execution by hand is tedious and doesn't prove correctness for
*all* inputs. Instead, answer **yes** to all three questions:

1. **Base-Case Question:** Is there a non-recursive way out of the function, and
   does it work correctly for the base case?
2. **Smaller-Caller Question:** Does each recursive call involve a smaller case
   of the problem, leading inescapably toward the base case?
3. **General-Case Question:** Assuming the recursive calls work correctly, does
   the rest of the function work correctly?

### Applied to `Factorial`

1. **Base case:** when `n == 0`, returns `1` (correct value of `0!`) with no
   further recursion. ✔
2. **Smaller caller:** each call passes `n - 1`, eventually reaching `0`. ✔
3. **General case:** assuming `Factorial(n-1)` is correct, `n * Factorial(n-1)`
   matches the mathematical definition. ✔

This mirrors a proof by induction.

---

## Writing Recursive Functions

General approach:

1. Get an exact definition of the problem.
2. Determine the size of the problem solved on each call (expressed in the
   parameters).
3. Identify and solve the **base case(s)** (ensures *yes* to the Base-Case
   Question).
4. Identify and solve the **general case(s)** in terms of a smaller case
   (ensures *yes* to the Smaller-Caller and General-Case Questions).

---

## Example: Searching a List

**Problem:** check if a value is in a list.
**Recursive idea:** `Return (value is in the first position?) OR (value is in the rest of the list?)`

The list type and the function signature:

```cpp
struct ListType
{
    int length;
    int info[MAX_ITEMS];
};
```

- **Base case 1:** the item is at the current index → return `true`.
- **Base case 2:** the end of the list is reached → return `false`.
- **General case:** recursively search starting at `startIndex + 1`.

```cpp
bool ValueInList(ListType list, int value, int startIndex)
{
    if (list.info[startIndex] == value)
        return true;                                   // Base case 1
    else if (startIndex == list.length - 1)
        return false;                                  // Base case 2
    else
        return ValueInList(list, value, startIndex + 1);  // General case
}
```

To search the whole list: `ValueInList(list, value, 0)`.

> **Note:** `ValueInList` is a *poor* use of recursion — its recursion depth is
> O(N), it copies the whole list on each call (if passed by value), and the
> iterative version is just as clear. It's useful as a teaching example only.

---

## Using Recursion to Simplify: Combinations

**Problem:** How many combinations of `members` size can be made from a group of
`group` elements? ("n choose k")

- **Base case 1:** if `members == 1`, return `group`.
- **Base case 2:** if `members == group`, return `1`.
- **General case:** `Combinations(group-1, members-1) + Combinations(group-1, members)`.

```cpp
int Combinations(int group, int members)
// Pre:  group and members are positive.
// Post: Function value = number of combinations of members size
//       that can be constructed from the total group size.
{
    if (members == 1)
        return group;                       // Base case 1
    else if (members == group)
        return 1;                           // Base case 2
    else
        return (Combinations(group - 1, members - 1) +
                Combinations(group - 1, members));
}
```

> **Efficiency warning:** `Combinations` recomputes the same values many times.
> It is an exponential-time `O(2^N)` solution to a linear-time `O(N)` problem —
> simple and elegant, but impractical for large inputs.

---

## Recursive Linked-List Processing: RevPrint

**Problem:** print the elements of a linked list **in reverse order**. This is
awkward iteratively (you'd need to walk backwards or use a stack) but elegant
recursively.

- **Base case:** if the list is empty (`listPtr == NULL`), do nothing.
- **General case:** RevPrint the rest of the list (`listPtr->next`), *then*
  print `listPtr->info`.

```cpp
// Prints the list in reverse order
void RevPrint(NodeType* listPtr)
{
    if (listPtr != NULL)
    {
        RevPrint(listPtr->next);                 // Reverse-print the rest
        std::cout << listPtr->info << std::endl; // Then print this node
    }
}
```

Because the head pointer is private, `RevPrint` is an **auxiliary
(non-member)** function. A public member function calls it:

```cpp
void ListType::PrintReversed()
{
    RevPrint(listData);
}
```

---

## Recursive Binary Search

Binary search is *inherently* recursive: each step cuts the search area in half.

- **Base case 1:** `fromLocation > toLocation` → not found, return `false`.
- **Base case 2:** item equals the middle value → return `true`.
- **General case:** search the lower or upper half depending on the comparison.

```cpp
template<class ItemType>
bool BinarySearch(ItemType info[], ItemType item,
                  int fromLocation, int toLocation)
{
    if (fromLocation > toLocation)
        return false;                          // Base case 1
    else
    {
        int midPoint;
        midPoint = (fromLocation + toLocation) / 2;
        if (item < info[midPoint])
            return BinarySearch(info, item, fromLocation, midPoint - 1);
        else if (item == info[midPoint])
            return true;                       // Base case 2
        else
            return BinarySearch(info, item, midPoint + 1, toLocation);
    }
}
```

Initial call: `BinarySearch(info, item, 0, length - 1)`.
Both the recursive and iterative versions are `O(log2 N)`, so binary search is a
**good** candidate for recursion.

---

## Recursive PutItem and DeleteItem

Inserting/deleting at the front or end of a linked list are edge cases. Recursion
lets us program them as if we only ever deal with the edge cases. Instead of
making the public functions recursive, we write recursive helper functions
`Insert` and `Delete`.

> **Critical:** the list pointer must be passed **by reference to a pointer**
> (`NodeType<ItemType>*& listPtr`) so the function can update the caller's link.
> Otherwise changes to `listPtr` are lost when the call returns.

### Recursive Insert

- **Base case 1:** the list is empty → insert the item.
- **Base case 2:** `item < listPtr->info` → insert as the first node.
- **General case:** `Insert(listPtr->next, item)`.

```cpp
template<class ItemType>
void Insert(NodeType<ItemType>*& listPtr, ItemType item)
{
    if (listPtr == NULL || item < listPtr->info)
    {
        // Save current pointer.
        NodeType<ItemType>* tempPtr = listPtr;
        // Get a new node.
        listPtr = new NodeType<ItemType>;
        listPtr->info = item;
        listPtr->next = tempPtr;
    }
    else
        Insert(listPtr->next, item);
}
```

### Recursive Delete

- **Base case:** `item == listPtr->info` → delete the node.
- **General case:** `Delete(listPtr->next, item)`.

```cpp
template<class ItemType>
void Delete(NodeType<ItemType>*& listPtr, ItemType item)
{
    if (item == listPtr->info)
    {
        NodeType<ItemType>* tempPtr = listPtr;
        listPtr = listPtr->next;
        delete tempPtr;
    }
    else
        Delete(listPtr->next, item);
}
```

---

## How Recursion Works (Under the Hood)

**Binding** = associating a memory address with a variable name. *When* it
happens matters:

- **Static binding** (static storage allocation): at **compile time**. Each
  variable gets a single fixed address in a symbol table.
- **Dynamic binding** (dynamic storage allocation): at **run time**. Variables
  are referenced by offsets resolved during execution.

### Why static allocation can't support recursion

With static allocation, each parameter/local has exactly one address. A recursive
call would **overwrite** the previous call's variables. Recursion needs each call
to have its own storage — which requires dynamic allocation.

### Activation Records and the Run-Time Stack

- An **activation record (stack frame)** stores a function call's parameters,
  local variables, return address, and register values.
- Every call (including recursive calls) **pushes** a new activation record onto
  the **run-time stack**; completing the call **pops** it.
- This LIFO behavior gives each recursive call its own memory and naturally
  tracks the order of calls.

### Run-time trace of `Factorial(4)`

| Call # | number | result | return address |
|:------:|:------:|:------:|:--------------:|
| 1 | 4 | ??? | 5200 (main)    |
| 2 | 3 | ??? | 1010 (recursive) |
| 3 | 2 | ??? | 1010 |
| 4 | 1 | ??? | 1010 |
| 5 | 0 | 1   | 1010 |

Once the base case (`number == 0`) returns `1`, the stack unwinds, each call
multiplying by its `number`, until call 1 returns `24` to `main`.

A simplified run-time version of the function:

```cpp
int Factorial(int number)
{
    // Function prologue
    actRec = new ActivationRecordType;
    actRec->returnAddr = retAddr;
    actRec->number = number;
    // actRec->result is undefined

    if (actRec->number == 0)
        actRec->result = 1;
    else
        actRec->result = actRec->number * Factorial(actRec->number - 1);

    // Function epilogue
    returnValue = actRec->result;
    retAddr = actRec->returnAddr;
    delete actRec;
    // Jump (goto) retAddr
}
```

**Recursion depth** = the number of recursive calls. It parallels the Big-O of
the equivalent iterative solution, since both are based on the problem size.

---

## Recursive Quick Sort

Quick Sort is a **divide-and-conquer** sort: it's easier to sort two small lists
than one large one. The list is repeatedly split and each part is quick-sorted.

**Algorithm** (if more than one element):
1. Select a `splitVal`.
2. Split the array so that:
   - `values[first] .. values[splitPoint-1] <= splitVal`
   - `values[splitPoint] = splitVal`
   - `values[splitPoint+1] .. values[last] > splitVal`
3. Quick Sort the left half and the right half.

- **Base case:** fewer than 2 items (`first >= last`) → do nothing.

```cpp
template<class ItemType>
void QuickSort(ItemType values[], int first, int last)
{
    if (first < last)
    {
        int splitPoint;
        Split(values, first, last, splitPoint);
        // values[first]..values[splitPoint-1] <= splitVal
        // values[splitPoint] = splitVal
        // values[splitPoint+1]..values[last] > splitVal
        QuickSort(values, first, splitPoint - 1);
        QuickSort(values, splitPoint + 1, last);
    }
}
```

Initial call: `QuickSort(values, 0, numberOfValues - 1)`.

### The Split function

Walk `first` rightward and `last` leftward, swapping values that are on the wrong
side of `splitVal`, until the indices cross.

```cpp
void Split(ItemType values[], int first, int last, int& splitPoint)
{
    ItemType splitVal = values[first];
    int saveFirst = first;
    bool onCorrectSide;
    first++;
    do
    {
        onCorrectSide = true;
        while (onCorrectSide)                  // Move first toward last.
            if (values[first] > splitVal)
                onCorrectSide = false;
            else
            {
                first++;
                onCorrectSide = (first <= last);
            }

        onCorrectSide = (first <= last);
        while (onCorrectSide)                  // Move last toward first.
            if (values[last] <= splitVal)
                onCorrectSide = false;
            else
            {
                last--;
                onCorrectSide = (first <= last);
            }

        if (first < last)
        {
            Swap(values[first], values[last]);
            first++;
            last--;
        }
    } while (first <= last);

    splitPoint = last;
    Swap(values[saveFirst], values[splitPoint]);
}
```

**Choosing a split value:** using `values[first]` works well for random data,
but on an already-sorted array it produces lopsided splits (slow). For nearly
sorted data, the middle value `values[(first + last) / 2]` is a better choice.

---

## Supplemental: Forms of Recursion

*(From the Goodrich/Tamassia/Goldwasser supplemental slides — pseudocode form.)*

### Recursion trace / visualization

A **recursion trace** draws a box for each call, an arrow from caller to callee,
and an arrow back showing each return value (e.g., for `recursiveFactorial(4)`).

### Linear recursion

The method makes **a single** recursive call.

```
Algorithm LinearSum(A, n):
    if n = 1 then
        return A[0]
    else
        return LinearSum(A, n - 1) + A[n - 1]
```

```
Algorithm ReverseArray(A, i, j):
    if i < j then
        Swap A[i] and A[j]
        ReverseArray(A, i + 1, j - 1)
    return
```

> **Defining arguments for recursion:** sometimes we add parameters to enable
> recursion (e.g., `ReverseArray(A, i, j)` rather than `ReverseArray(A)`).

### Computing powers — recursive squaring

A naive `p(x, n) = x * p(x, n-1)` is `O(n)`. Repeated squaring is `O(log n)`:

```
Algorithm Power(x, n):
    if n = 0 then
        return 1
    if n is odd then
        y = Power(x, (n - 1) / 2)
        return x * y * y
    else
        y = Power(x, n / 2)
        return y * y
```

> Use a variable (`y`) once and reuse it rather than calling the method twice —
> this is what makes it `O(log n)`.

### Tail recursion

The recursive call is the method's **last** step (e.g., array reversal). Tail
recursion converts easily into a loop, saving resources:

```
Algorithm IterativeReverseArray(A, i, j):
    while i < j do
        Swap A[i] and A[j]
        i = i + 1
        j = j - 1
    return
```

### Binary recursion

**Two** recursive calls per non-base case (e.g., the English-ruler `DrawTicks`).

```
Algorithm BinarySum(A, i, n):
    if n = 1 then
        return A[i]
    return BinarySum(A, i, n/2) + BinarySum(A, i + n/2, n/2)
```

### Computing Fibonacci numbers

`F0 = 0`, `F1 = 1`, `Fi = Fi-1 + Fi-2`. The naive binary recursion is
**exponential** (`nk > 2^(k/2)`):

```
Algorithm BinaryFib(k):
    if k = 1 then
        return k
    else
        return BinaryFib(k - 1) + BinaryFib(k - 2)
```

A **linear** recursion is far better (`k - 1` calls):

```
Algorithm LinearFibonacci(k):
    if k = 1 then
        return (k, 0)
    else
        (i, j) = LinearFibonacci(k - 1)
        return (i + j, i)
```

### Multiple recursion

Potentially **many** recursive calls (e.g., solving summation puzzles like
`pot + pan = bib`):

```
Algorithm PuzzleSolve(k, S, U):
    for all e in U do
        Remove e from U          {e is now being used}
        Add e to the end of S
        if k = 1 then
            Test whether S solves the puzzle
            if S solves the puzzle then
                return "Solution found: " S
        else
            PuzzleSolve(k - 1, S, U)
        Add e back to U          {e is now unused}
        Remove e from the end of S
```

---

## Debugging & Removing Recursion

**Debugging:** the worst problem is **infinite recursion**, which exhausts the
run-time stack ("stack overflow"). A common beginner mistake is using a *loop*
(`while`) instead of a *branch* (`if`) for the base/general split. Use the
Three-Question Method and add debug prints of parameters at entry/exit.

Two techniques remove recursion:

### Iteration (for tail recursion)

When the recursive call is the last action, the pushing/popping is superfluous —
just loop. Base cases become loop terminating conditions.

```cpp
// Iterative ValueInList
bool ValueInList(ListType list, int value, int startIndex)
{
    bool found = false;
    while (!found && startIndex < list.length)
        if (value == list.info[startIndex])
            found = true;
        else
            startIndex++;
    return found;
}
```

### Stacking (for non-tail recursion)

When work is done *after* the recursive call (like `RevPrint`), replace the
system's run-time stack with a programmer-managed stack.

```cpp
#include "StackType.h"

void ListType::RevPrint()
{
    StackType<NodeType*> stack;
    NodeType* listPtr;
    listPtr = listData;
    while (listPtr != NULL)          // Put pointers onto the stack.
    {
        stack.Push(listPtr);
        listPtr = listPtr->next;
    }
    // Retrieve pointers in reverse order and print elements.
    while (!stack.IsEmpty())
    {
        listPtr = stack.Top();
        stack.Pop();
        std::cout << listPtr->info;
    }
}
```

The non-recursive version is longer — we must stack/unstack explicitly instead
of letting the run-time stack do it.

---

## Deciding When to Use Recursion

**Efficiency:** recursion generally costs more time and space (each call creates
an activation record and copies value parameters). Some recursive algorithms are
*inherently* inefficient (e.g., `Combinations` is `O(2^N)`).

**Clarity:** for many problems the recursive solution is simpler, more elegant,
and faster to write. Programmer time has value — trading some execution time for
development time and clarity is often worthwhile.

**Use recursion when:**

- The depth of recursion is relatively **shallow** — `O(log N)` is great, even
  `O(N)` can be acceptable.
- The recursive version does **about the same amount of work** as the iterative
  version (e.g., both Binary Search versions are `O(log N)`; but `Combinations`
  is `O(2^N)` recursive vs. `O(N)` iterative).
- The recursive version is **shorter and simpler** (e.g., `RevPrint`).

---

# Chapter 8: Binary Search Trees

## Searching Review

Often we must access an element matching a condition (e.g., the student with ID
203), not just by direct index. Each structure defines its own search methods.

**Search specification:**

```
FindItem(item, location)
Function:       Determine whether an element has a key matching item's.
Precondition:   List initialized; item's key initialized.
Postcondition:  location = position of matching element, or NULL if none.
```

| Strategy | Notes | Complexity |
|---|---|---|
| **Linear search** | Walk the list, check each item. Required if unsorted. | `O(N)`, avg `N/2` |
| **High-probability ordering** | Move/swap frequently-searched items toward the front (self-adjusting list). | `O(N)` worst, avg approaches `O(1)` |
| **Key ordering (sorted list)** | Linear search can stop early once it passes where the item should be. | `O(N)` worst, avg `N/2` |
| **Binary search** | Divide-and-conquer on a sorted *array*. | `O(log2 N)` |

Binary search requires an array — there's no practical way to find the midpoint
of a linked list. The **binary search tree** gives us `O(log2 N)` searching
*and* the flexibility of a linked structure.

---

## Trees: Vocabulary

- **Binary tree:** a structure with a unique starting node (the **root**) in
  which every node has **at most two children**, and a **unique path** exists
  from the root to every node.
- **Children / parent:** the node to the left/right of a node is its **left
  child** / **right child**; that node is their **parent**.
- **Leaf node:** a node with no children.
- **Subtree:** the left/right child of a node is the root of that node's
  left/right **subtree**. *Every node is the root of a subtree* → trees are
  **recursive structures**.
- **Ancestor / descendant:** a node is an ancestor of another if it is the
  parent (or parent of an ancestor) of that node.

> **Not a tree:** if two paths reach the same node (a node with two parents), it
> violates the unique-path rule.

---

## Level, Height, and Efficiency

- **Level:** the distance of a node from the root (root is level 0). The maximum
  number of nodes at level `N` is `2^N`.
- **Height:** the maximum level in the tree.
- With `N` nodes, the **maximum** height is `N` (a degenerate, list-shaped tree)
  and the **minimum** height is `log2 N + 1` (a full, bushy tree).

**Height determines efficiency:** a minimum-height tree supports `O(log2 N)`
access to every element; a maximum-height tree degrades to `O(N)` — no better
than a linked list.

---

## The Binary Search Property

> **Binary Search Property:** the left subtree of a node contains only values
> **less** than the node's value, and the right subtree contains only values
> **greater** than the node's value.

A binary tree with this property is a **Binary Search Tree (BST)**. To search,
compare with the root and go left or right accordingly — at most *height*
comparisons. For 1,000 nodes in a minimum-height tree, that's ≤ 10 comparisons
instead of up to 1,000 in a linked list.

**Logical-level operations:**
- Transformers: `PutItem`, `DeleteItem`, `MakeEmpty`
- Observers: `IsEmpty`, `IsFull`, `GetLength`, `GetItem`
- Iterators: `ResetTree`, `GetNextItem` (support **traversals**)
- Utility: `Print`

**Application level:** BSTs can replace lists, providing `O(log N)` insertion,
deletion, and search (assuming a near-minimum-height tree).

---

## The TreeType Class

The implementation is a linked structure of dynamically allocated nodes. Because
BSTs are inherently recursive, member functions call **recursive helper
functions** that take a node pointer (`root`) as a parameter.

```cpp
#include <iostream>
struct TreeNode;
typedef char ItemType;
// Assumption: ItemType is a type for which the operators "<"
// and "==" are defined--either an appropriate built-in type or
// a class that overloads these operators.
enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

class TreeType
{
public:
    TreeType();                                 // Constructor.
    ~TreeType();                                // Destructor.
    TreeType(const TreeType& originalTree);     // Copy constructor.
    void operator=(TreeType& originalTree);
    void MakeEmpty();
    bool IsEmpty() const;
    bool IsFull() const;
    int  GetLength() const;
    ItemType GetItem(ItemType item, bool& found);
    void PutItem(ItemType item);
    void DeleteItem(ItemType item);
    void ResetTree(OrderType order);
    ItemType GetNextItem(OrderType order, bool& finished);
    void Print(std::ofstream& outFile) const;
private:
    TreeNode* root;
};
```

The node definition:

```cpp
struct TreeNode
{
    ItemType  info;
    TreeNode* left;
    TreeNode* right;
};
```

**Design-notation → C++ mapping:**

| Design Notation | C++ Code |
|---|---|
| `Node(location)` | `*location` |
| `Info(location)` | `location->info` |
| `Left(location)` | `location->left` |
| `Right(location)` | `location->right` |
| `Set Info(location) to value` | `location->info = value` |

---

## IsFull / IsEmpty

Identical to the linked-list versions. `IsFull` tries to allocate a node and
catches `bad_alloc`; `IsEmpty` checks whether `root` is `NULL`.

```cpp
bool TreeType::IsFull() const
// Returns true if the free store has no room for another node and false otherwise.
{
    TreeNode* location;
    try
    {
        location = new TreeNode;
        delete location;
        return false;
    }
    catch (std::bad_alloc exception)
    {
        return true;
    }
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty and false otherwise.
{
    return root == NULL;
}
```

---

## GetLength / CountNodes

Number of nodes = (nodes in left subtree) + (nodes in right subtree) + 1.

**Two key lessons** (from working through buggy versions):
1. **Always check for an empty tree first.**
2. **Leaf nodes do not need to be treated as a separate case** — an empty tree
   returning 0 handles them elegantly.

- **Base case:** if `tree == NULL`, return 0.
- **General case:** `CountNodes(left) + CountNodes(right) + 1`.

```cpp
int CountNodes(TreeNode* tree);

int TreeType::GetLength() const
// Calls the recursive function CountNodes to count the nodes in the tree.
{
    return CountNodes(root);
}

int CountNodes(TreeNode* tree)
// Post: Returns the number of nodes in the tree.
{
    if (tree == NULL)
        return 0;
    else
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}
```

---

## GetItem / Retrieve

Search by comparing with the current node and recursing left or right.

- **Base case 1:** key matches `tree->info` → set `item` and `found = true`.
- **Base case 2:** `tree == NULL` → `found = false`.
- **General case:** recurse into the left or right subtree.

```cpp
void Retrieve(TreeNode* tree, ItemType& item, bool& found);

ItemType TreeType::GetItem(ItemType item, bool& found) const
// Calls recursive function Retrieve to search the tree for item.
{
    Retrieve(root, item, found);
    return item;
}

void Retrieve(TreeNode* tree, ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem;
//       otherwise, found is false and item is unchanged.
{
    if (tree == NULL)
        found = false;                          // item is not found.
    else if (item < tree->info)
        Retrieve(tree->left, item, found);      // Search left subtree.
    else if (item > tree->info)
        Retrieve(tree->right, item, found);     // Search right subtree.
    else
    {
        item = tree->info;                      // item is found.
        found = true;
    }
}
```

---

## PutItem / Insert

A new node is always inserted as a **leaf** at its correct position. `Insert`
takes a **reference to a pointer** (`TreeNode*& tree`) so that `new` links the
node into the existing tree (it updates the parent's `left`/`right` link).

- **Base case:** if `tree == NULL`, allocate a new leaf node.
- **General case:** insert into the left subtree (if `item < info`) or the right
  subtree (if `item > info`).

```cpp
void Insert(TreeNode*& tree, ItemType item);

void TreeType::PutItem(ItemType item)
// Calls the recursive function Insert to insert item into tree.
{
    Insert(root, item);
}

void Insert(TreeNode*& tree, ItemType item)
// Inserts item into tree.
// Post: item is in tree; search property is maintained.
{
    if (tree == NULL)
    {   // Insertion place found.
        tree = new TreeNode;
        tree->right = NULL;
        tree->left  = NULL;
        tree->info  = item;
    }
    else if (item < tree->info)
        Insert(tree->left, item);    // Insert in left subtree.
    else
        Insert(tree->right, item);   // Insert in right subtree.
}
```

> **Why the reference parameter matters:** passing a pointer **by value** lets
> you change what it points to, but **by reference** lets you change the caller's
> pointer itself — which is exactly how the new leaf gets linked to its parent.

**Insertion order determines tree shape:** inserting values in sorted (or
reverse-sorted) order produces a skewed, list-like tree (`O(N)`); a random mix
produces a short, bushy tree (`O(log N)`). E.g., input `A B C D E F G` yields a
degenerate tree, while `D B F A C E G` yields a balanced one.

---

## DeleteItem / Delete

`Delete` finds the node, then `DeleteNode` removes it. There are **three cases**:

1. **Leaf (no children):** set the parent's link to `NULL`.
2. **One child:** set the parent's link to point to the node's child.
3. **Two children:** *most complex* — replace the node's `info` with its
   **logical predecessor** (the largest value in its left subtree, i.e., the
   rightmost node of the left subtree), then delete that predecessor node.

```cpp
void DeleteNode(TreeNode*& tree);
void Delete(TreeNode*& tree, ItemType item);

void TreeType::DeleteItem(ItemType item)
// Calls the recursive function Delete to delete item from tree.
{
    Delete(root, item);
}

void Delete(TreeNode*& tree, ItemType item)
// Deletes item from tree.
// Post: item is not in tree.
{
    if (item < tree->info)
        Delete(tree->left, item);      // Look in left subtree.
    else if (item > tree->info)
        Delete(tree->right, item);     // Look in right subtree.
    else
        DeleteNode(tree);              // Node found; call DeleteNode.
}
```

`DeleteNode` — note the one-child / no-child cases are merged (when `left` is
`NULL`, storing `right` into `tree` also handles the both-`NULL` case):

```cpp
void GetPredecessor(TreeNode* tree, ItemType& data);

void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree.
//       If tree is a leaf node or has only one non-NULL child pointer, the node
//       is deleted; otherwise, the user's data is replaced by its logical
//       predecessor and the predecessor's node is deleted.
{
    ItemType data;
    TreeNode* tempPtr;
    tempPtr = tree;
    if (tree->left == NULL)
    {
        tree = tree->right;
        delete tempPtr;
    }
    else if (tree->right == NULL)
    {
        tree = tree->left;
        delete tempPtr;
    }
    else
    {
        GetPredecessor(tree->left, data);
        tree->info = data;
        Delete(tree->left, data);     // Delete predecessor node.
    }
}
```

Finding the predecessor (rightmost node of the left subtree) — a simple loop
suffices, no recursion needed:

```cpp
void GetPredecessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the rightmost node in tree.
{
    while (tree->right != NULL)
        tree = tree->right;
    data = tree->info;
}
```

---

## Print and Tree Traversals

Printing a tree is not as simple as a list — there are many ways to traverse it.
**Inorder traversal** accesses elements from smallest to largest: process the
**left subtree, then the node, then the right subtree**.

- **Base case:** if `tree == NULL`, do nothing.
- **General case:** traverse left in order, print `tree->info`, traverse right.

```cpp
void PrintTree(TreeNode* tree, std::ofstream& outFile)
// Prints info member of items in tree in sorted order on outFile.
{
    if (tree != NULL)
    {
        PrintTree(tree->left, outFile);     // Print left subtree.
        outFile << tree->info;
        PrintTree(tree->right, outFile);    // Print right subtree.
    }
}

void TreeType::Print(std::ofstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
    PrintTree(root, outFile);
}
```

### The three traversals

The name tells you **when the node itself is visited** relative to its subtrees:

```
Inorder(tree)               Preorder(tree)              Postorder(tree)
  if tree is not NULL         if tree is not NULL         if tree is not NULL
    Inorder(Left(tree))         Visit Info(tree)            Postorder(Left(tree))
    Visit Info(tree)            Preorder(Left(tree))        Postorder(Right(tree))
    Inorder(Right(tree))        Preorder(Right(tree))       Visit Info(tree)
```

- **Inorder** → values in ascending order (used by `Print`).
- **Postorder** → visits children before the node (used by the destructor, since
  leaves are cheapest to delete).
- **Preorder** → visits the node first (useful for other binary-tree
  applications, less so for BSTs).

> **Visualization trick:** draw a loop hugging the tree from the root down the
> left side and back. Each node is "touched" three times. Visit on the 1st touch
> → preorder; 2nd touch → inorder; 3rd touch → postorder.

---

## Constructor, Destructor, MakeEmpty

The constructor sets `root` to `NULL`. The destructor uses a **postorder**
traversal so that each node is a leaf by the time it's deleted.

```cpp
TreeType::TreeType()
{
    root = NULL;
}

void Destroy(TreeNode*& tree);

TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
    Destroy(root);
}

void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
    if (tree != NULL)
    {
        Destroy(tree->left);
        Destroy(tree->right);
        delete tree;
    }
}
```

> `MakeEmpty` is identical to the destructor body, but it must also set
> `root = NULL` after the call to `Destroy`.

---

## Copying a Tree

Both the **copy constructor** and the **assignment operator** must deep-copy the
data *and* structure, so they call a recursive `CopyTree` helper.

```cpp
void CopyTree(TreeNode*& copy, const TreeNode* originalTree);

TreeType::TreeType(const TreeType& originalTree)
// Calls the recursive function CopyTree to copy originalTree into root.
{
    CopyTree(root, originalTree.root);
}

void TreeType::operator=(const TreeType& originalTree)
// Calls the recursive function CopyTree to copy originalTree into root.
{
    if (&originalTree == this)
        return;                       // Ignore assigning self to self.
    Destroy(root);                    // Deallocate existing tree nodes.
    CopyTree(root, originalTree.root);
}
```

- **Base case:** if `originalTree == NULL`, set `copy = NULL`.
- **General case:** create a node, copy `info`, then recursively copy the left
  and right subtrees.

```cpp
void CopyTree(TreeNode*& copy, const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate of originalTree.
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->info = originalTree->info;
        CopyTree(copy->left,  originalTree->left);
        CopyTree(copy->right, originalTree->right);
    }
}
```

---

## ResetTree and GetNextItem

These iterators let the **client choose the traversal order** via an
`OrderType` parameter. The approach: `ResetTree` builds a **queue** of node
contents in the requested order; `GetNextItem` dequeues them one at a time.

Three queues are kept in the private section of `TreeType`:

```cpp
enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};
class TreeType
{
public:
    // Function prototypes go here.
private:
    TreeNode* root;
    QueType preQue;
    QueType inQue;
    QueType postQue;
};

// Auxiliary function prototypes.
void PreOrder(TreeNode*, QueType&);    // Enqueues tree items in preorder.
void InOrder(TreeNode*, QueType&);     // Enqueues tree items in inorder.
void PostOrder(TreeNode*, QueType&);   // Enqueues tree items in postorder.
```

```cpp
void TreeType::ResetTree(OrderType order)
// Calls a function to create a queue of the tree elements in the desired order.
{
    switch (order)
    {
        case PRE_ORDER  : PreOrder(root, preQue);   break;
        case IN_ORDER   : InOrder(root, inQue);     break;
        case POST_ORDER : PostOrder(root, postQue); break;
    }
}

void PreOrder(TreeNode* tree, QueType& preQue)
// Post: preQue contains the tree items in preorder.
{
    if (tree != NULL)
    {
        preQue.Enqueue(tree->info);
        PreOrder(tree->left, preQue);
        PreOrder(tree->right, preQue);
    }
}

void InOrder(TreeNode* tree, QueType& inQue)
// Post: inQue contains the tree items in inorder.
{
    if (tree != NULL)
    {
        InOrder(tree->left, inQue);
        inQue.Enqueue(tree->info);
        InOrder(tree->right, inQue);
    }
}

void PostOrder(TreeNode* tree, QueType& postQue)
// Post: postQue contains the tree items in postorder.
{
    if (tree != NULL)
    {
        PostOrder(tree->left, postQue);
        PostOrder(tree->right, postQue);
        postQue.Enqueue(tree->info);
    }
}
```

```cpp
ItemType TreeType::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; otherwise false.
{
    ItemType item;
    finished = false;
    switch (order)
    {
        case PRE_ORDER  : preQue.Dequeue(item);
                          if (preQue.IsEmpty())  finished = true;
                          break;
        case IN_ORDER   : inQue.Dequeue(item);
                          if (inQue.IsEmpty())   finished = true;
                          break;
        case POST_ORDER : postQue.Dequeue(item);
                          if (postQue.IsEmpty()) finished = true;
                          break;
    }
    return item;
}
```

---

## Iterative BST Operations

A general `FindNode` returns a pointer to the matching node (`nodePtr`) **and**
its parent (`parentPtr`). It is used by both iterative `PutItem` and
`DeleteItem`.

- If found: `nodePtr` → the node, `parentPtr` → its parent (or `NULL` if root).
- If not found: `nodePtr == NULL`, `parentPtr` → the logical parent (the
  insertion point).

```cpp
void FindNode(TreeNode* tree, ItemType item,
              TreeNode*& nodePtr, TreeNode*& parentPtr)
// Post: If a node is found with the same key as item's, then nodePtr points
//       to that node and parentPtr points to its parent node. If the root node
//       has the same key as item's, parentPtr is NULL. If no node has the same
//       key, then nodePtr is NULL and parentPtr points to the node in the tree
//       that is the logical parent of item.
{
    nodePtr   = tree;
    parentPtr = NULL;
    bool found = false;
    while (nodePtr != NULL && !found)
    {
        if (item < nodePtr->info)
        {
            parentPtr = nodePtr;
            nodePtr   = nodePtr->left;
        }
        else if (item > nodePtr->info)
        {
            parentPtr = nodePtr;
            nodePtr   = nodePtr->right;
        }
        else
            found = true;
    }
}
```

### Iterative PutItem

Create the node, find the insertion point with `FindNode`, then attach. If
`parentPtr == NULL`, the tree was empty and the new node becomes the root.

```cpp
void TreeType::PutItem(ItemType item)
// Post: item is in tree.
{
    TreeNode* newNode;
    TreeNode* nodePtr;
    TreeNode* parentPtr;
    newNode = new TreeNode;
    newNode->info  = item;
    newNode->left  = NULL;
    newNode->right = NULL;
    FindNode(root, item, nodePtr, parentPtr);
    if (parentPtr == NULL)                 // Insert as root.
        root = newNode;
    else if (item < parentPtr->info)
        parentPtr->left = newNode;
    else
        parentPtr->right = newNode;
}
```

### Iterative DeleteItem

Use `FindNode` to locate the node and its parent, then reuse `DeleteNode`. We
must pass the **actual pointer in the tree** (`parentPtr->left` or
`parentPtr->right`, or `root`), not a copy.

```cpp
void TreeType::DeleteItem(ItemType item)
// Post: There is no node in the tree whose info member matches item.
{
    TreeNode* nodePtr;
    TreeNode* parentPtr;
    FindNode(root, item, nodePtr, parentPtr);
    if (nodePtr == root)
        DeleteNode(root);
    else
        if (parentPtr->left == nodePtr)
            DeleteNode(parentPtr->left);
        else
            DeleteNode(parentPtr->right);
}
```

---

## Recursion or Iteration?

Applying the Chapter 7 guidelines to BSTs:

- **Is the recursion shallow?** Yes — a well-balanced BST has `O(log2 N)` height.
- **Is the recursive version shorter / cleaner?** Yes — much shorter than the
  iterative versions plus the supporting `FindNode`.
- **Is the recursive version less efficient?** No — both are `O(log2 N)`. The
  only concern is **space**: `item` is a value parameter copied on each call; if
  `ItemType` is large and the tree is tall, prefer a `const` reference parameter.

**Verdict:** the recursive BST functions earn an "A" — an excellent use of
recursion.

---

## BSTs vs. Linear Lists: Big-O

A BST combines the best of both worlds: fast (`O(log2 N)`) searching like a
sorted array, plus insertions/deletions without shifting data like a linked
list. The tradeoffs: an extra pointer per node (more memory) and more complex
algorithms. BSTs suit **random access**; for purely **sequential** processing, a
linked list may be better.

> **Degenerate tree warning:** efficiency relies on a balanced tree. If elements
> are inserted in sorted order, the tree becomes a linked list and operations
> degrade to `O(N)`.

| Operation | Binary Search Tree | Array-Based Sorted List | Linked List |
|---|:---:|:---:|:---:|
| Class constructor | `O(1)` | `O(1)` | `O(1)` |
| Destructor | `O(N)` | `O(1)`* | `O(N)` |
| MakeEmpty | `O(N)` | `O(1)`* | `O(N)` |
| GetLength | `O(N)` | `O(1)` | `O(1)` |
| IsFull | `O(1)` | `O(1)` | `O(1)` |
| IsEmpty | `O(1)` | `O(1)` | `O(1)` |
| GetItem (find) | `O(log2 N)` | `O(log2 N)` | `O(N)` |
| PutItem | `O(log2 N)` | `O(N)` | `O(N)` |
| DeleteItem | `O(log2 N)` | `O(N)` | `O(N)` |

\* The array-based destructor/MakeEmpty are `O(1)` only because no dynamic
per-element deallocation is required.

**Key takeaways:**
- `GetItem`, `PutItem`, `DeleteItem` are all `O(log2 N)` on a balanced BST —
  they find the node `O(log2 N)` plus `O(1)` work.
- `GetLength` is `O(N)` here because we *count* nodes on demand (keeping a length
  field would make it `O(1)`).
- `MakeEmpty`, `Print`, and the destructor are `O(N)` because they traverse every
  node.
