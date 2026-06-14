# CSC 240 — Unit Summary (Lists)

**Chapters Covered:**
- Chapter 3: ADT Unsorted List
- Chapter 4: ADT Sorted List

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
- Dale's textbook simulates a generic by using a user-defined `ItemType` class that provides at least a `ComparedTo(other)` method.

```cpp
// Conceptual ItemType the list relies on
enum RelationType { LESS, GREATER, EQUAL };

class ItemType {
public:
    RelationType ComparedTo(ItemType other) const;
    void Initialize(int value);
    void Print() const;
private:
    int value;
};
```

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

If `myPtr` points to a struct/class object, use `->` to reach its fields:

```cpp
myPtr->info        // equivalent to (*myPtr).info
myPtr->next
```

---

### 7. Linked-List-Based Implementation

#### Node structure

A **node** has two fields: `info` (the data) and `next` (a pointer to the next node).

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
