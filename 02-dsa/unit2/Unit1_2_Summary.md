# C++ Data Structures: Chapters 1–6 Summary

A running summary of what I've learned so far across Chapters 1–6 of C++ Data Structures and Object-Oriented design. It covers the key conceptual frameworks, architectural viewpoints, memory mechanics, and fundamental data structures with short C++ implementations.

> Note: The code snippets are illustrative fragments meant to highlight the core idea, not complete compilable programs. Examples that `throw` require `#include <stdexcept>`.

---

## 1. Object-Oriented Programming (OOP) Principles & Architectural Views

### Core OOP Relationships

Object-Oriented Design relies heavily on choosing the correct structural relationship between classes to maximize code reuse, flexibility, and proper data containment.

- **Encapsulation:** Bundling data attributes and the methods that manipulate them into a single unit (a class) while restricting direct access using visibility modifiers (`private`, `protected`). This enforces information hiding and protects the internal state of an object from unintended external mutation.
- **Composition (*has-a* relationship):** Occurs when a class contains an instance of another class as a member field. It provides a clean public interface layer where the outer class wraps and manages the lifetime of the inner object without gaining access to its protected or private internals.
- **Inheritance (*is-a* relationship):** A mechanism where a derived subclass inherits attributes and behaviors from a base superclass. It *reuses behavior* via the is-a relationship but couples the subclass tightly to the protected internals of the base class.
- **Polymorphism & Virtual Functions:** A **virtual function** is the mechanism that supports **dynamic binding** — the decision of *which* override to run is resolved at runtime via the virtual function table, based on the object's actual type rather than the pointer/reference type.

> Quick contrast: Composition is a *has-a* relationship; Inheritance is an *is-a* relationship; Encapsulation *restricts direct access* to data.

### Modeling Problem-Domain Objects

In object-oriented design, **problem-domain objects** model real-world entities from the application space — e.g., `Customer`, `Invoice`, `Order`. These are the nouns of the business problem.

- A **sorting algorithm** (or any pure procedure/behavior) is *not* a problem-domain object — it defines behavior, not a real-world entity, and is better treated as an implementation detail or service.
- Rule of thumb: if it's a "thing" the user/business cares about, it's likely a problem-domain object; if it's a "how" (an algorithm or internal mechanism), it usually is not.

```cpp
// Demonstration of Composition vs Inheritance
class Engine {
public:
    void ignite() { /* Ignition logic */ }
};

// Composition: A Car "has-a" Engine
class Car {
private:
    Engine engine; // Composed object
public:
    void start() {
        engine.ignite(); // Accesses public interface only
    }
};

// Inheritance: An ElectricCar "is-a" Car
class ElectricCar : public Car {
    // Inherits all public and protected attributes/behaviors of Car
};
```

### The Three Software Engineering Viewpoints

When planning and analyzing data structures, systems are evaluated using three distinct abstraction viewpoints:

1. **Application View (Domain/User View):** Focuses on the real-world *purpose and use* of the component (e.g., using a Queue to manage a prioritized buffer of printable documents).
2. **Logical View (Abstract Data Type View):** Defines the *operations and behavior* — the structural interface and semantic properties — independently of storage mechanics. It states *what* operations (like `push()`, `pop()`) exist and their guarantees.
3. **Implementation View (Low-Level Developer View):** Details the *memory layout and pointer manipulation* — the concrete engineering realization, including allocation and resizing logic.

> Key distinction to remember: when a structure deliberately **hides its implementation** and is described purely by the operations it supports (insert, delete, etc.), the **Logical (ADT) view** is being emphasized — *not* the Application view. The Application view is about real-world purpose; the Logical view is about behavior independent of storage.

### Abstract Data Types: Bounded vs. Unbounded

An **Abstract Data Type (ADT)** is defined by its logical interface, not its storage. ADTs are classified by whether their size is constrained:

- **Bounded ADT:** Its maximum size is **fixed by its interface/specification**. This is a property declared by the ADT's definition — it is not merely a side effect of "using arrays" or "being unable to grow." (A bounded ADT can still be implemented with linked nodes; the bound comes from the specification.)
- **Unbounded ADT:** No maximum size is imposed by the specification; it grows as needed (subject to available memory).

---

## 2. Memory Management, Pointer Mechanics, & Copy Semantics

### Pointer Fundamentals & Dereferencing

- **Pointer Variable:** A variable that explicitly holds a numeric address pointing to another location in system memory.
- **External Pointer:** A standalone reference variable (like `head` in a list) sitting on the stack that serves as the runtime entry point into a dynamic heap data structure.
- **Dereferencing:** Accessing data indirectly by applying the unary operator (`*`) to a pointer, instructing the program to read or modify the values stored at the target destination address.

### The Critical Need for User-Defined Destructors

In C++, the runtime automatically cleans up an object's local stack variables when it falls out of scope. However, if a class uses the `new` operator to instantiate memory blocks dynamically out on the **heap**, the compiler only manages the memory allocation of the raw pointer address on the stack.

When the parent object is destroyed, the stack reference vanishes, leaving the heap memory orphaned. To prevent **memory leaks**, a custom **user-defined destructor** must be written to explicitly traverse and deallocate (`delete` or `delete[]`) all dynamically allocated heap resources.

This is exactly why a destructor is critical in a **linked-stack** (or any linked structure): its job is to **deallocate the dynamically allocated nodes** one by one. It is *not* about resetting `top`, avoiding overflow, or reordering elements — those are unrelated to reclaiming heap memory.

The clearest signal that a class **needs a user-defined destructor** is that it **allocates memory dynamically with `new`**. A class containing only primitive members, only public methods, or templates does not by itself require one.

### Shallow Copy vs. Deep Copy

- **Shallow Copy:** The default behavior, which duplicates the literal values of member variables. If a member variable is a pointer to heap memory, it copies the raw address. Consequently, both objects point to the same heap destination, causing double-free crashes or race conditions.
- **Deep Copy:** Explicitly allocates a brand-new distinct segment of memory on the heap and copies the underlying values into the new block. The copy and original maintain independent memory addresses.

> One-line contrast: a **shallow copy duplicates the pointer value but not the pointed-to data** (both objects share one heap block); a **deep copy duplicates both the pointer *and* the pointed-to data** (each object owns its own block).

```cpp
#include <iostream>

class DynamicBuffer {
private:
    int* data;
    int size;

public:
    // Constructor
    DynamicBuffer(int s) {
        size = s;
        data = new int[size]; // Dynamic heap allocation
    }

    // User-Defined Destructor: Prevents memory leaks
    ~DynamicBuffer() {
        delete[] data;
    }

    // Copy Constructor implementing a DEEP COPY
    DynamicBuffer(const DynamicBuffer& other) {
        size = other.size;
        data = new int[size]; // Allocate brand-new distinct heap memory
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i]; // Replicate actual underlying data values
        }
    }
};
```

---

## 3. Advanced Stack & Queue Architecture

### Array-Based Stacks

- **Initial State:** The index tracking variable `top` is initialized to `-1` because arrays use zero-indexed numbering. An index of `0` denotes that the stack contains exactly one active item, so `-1` cleanly signifies *an empty stack before the first push* (not "the stack is full" and not a reserved metadata slot).
- **Push order matters:** before storing an item, a `push` must **first check for overflow**, and only then increment `top` and assign `items[top]`. Checking overflow *before* writing prevents an out-of-bounds write.
- **Stack Overflow:** Occurs at runtime when a `push` is invoked on a stack that has hit its maximum physical array limit (pushing onto a stack with no available space). Note this is distinct from a *full queue* — "enqueue into a full queue" is a queue condition, not stack overflow.
- **Stack Underflow:** Occurs when a `pop` or `peek` request is executed on an empty stack structure (`top == -1`).

### Optimizing Space: Shared Array Layout (Two-Way Stack)

To optimize space allocation within a fixed contiguous block of memory, two independent stacks can safely occupy a single array by growing from opposite ends toward each other.

- **Stack 1:** Anchored at index `0` and increments upwards (`0, 1, 2...`).
- **Stack 2:** Anchored at index `MAX_SIZE - 1` and decrements downwards (`MAX_SIZE - 1, MAX_SIZE - 2...`).
- **Overflow Boundary:** Space is maximized flexibly because an overflow error is only thrown when the sum of elements fills the array entirely, regardless of individual stack sizes. The overflow state triggers if `top1 + 1 == top2`.

```cpp
class TwoWayStack {
private:
    int* arr;
    int capacity;
    int top1;
    int top2;

public:
    TwoWayStack(int n) {
        capacity = n;
        top1 = -1;
        top2 = n;
        arr = new int[n];
    }

    ~TwoWayStack() { delete[] arr; }

    void push1(int val) {
        if (top1 + 1 == top2) throw std::overflow_error("Stack Overflow");
        arr[++top1] = val;
    }

    void push2(int val) {
        if (top1 + 1 == top2) throw std::overflow_error("Stack Overflow");
        arr[--top2] = val;
    }
};
```

### Circular Queues & Circular Indexing via Modulo (`%`)

In fixed-array queue implementations, advancing pointers sequentially causes a problem: elements eventually reach the end of the array, leaving empty spaces at the front due to previous `dequeue` operations.

To reuse memory without shifting elements (an expensive $O(n)$ operation), **circular indexing** uses the modulo (`%`) operator. The operator acts as a wrap-around boundary that maps an out-of-bounds index back to the starting position `0`.

$$\text{index} = (\text{index} + 1) \% \text{capacity}$$

```cpp
class CircularQueue {
private:
    int* arr;
    int front;
    int rear;
    int capacity;
    int count;

public:
    CircularQueue(int size) {
        capacity = size;
        front = 0;
        rear = -1;
        count = 0;
        arr = new int[capacity];
    }

    ~CircularQueue() { delete[] arr; }

    void enqueue(int item) {
        if (count == capacity) throw std::overflow_error("Queue Full");
        // Circular wrap-around arithmetic
        rear = (rear + 1) % capacity;
        arr[rear] = item;
        count++;
    }

    int dequeue() {
        if (count == 0) throw std::underflow_error("Queue Empty");
        int item = arr[front];
        // Circular wrap-around arithmetic
        front = (front + 1) % capacity;
        count--;
        return item;
    }
};
```

---

## 4. List Paradigms: Operations, Searching & Structural Optimizations

### Abstract Data Type Interface Hiding

By defining data structures strictly via a logical interface view, users interact exclusively with abstraction endpoints. The interior data configuration remains entirely hidden, which guarantees that changing the underlying implementation layout (e.g., migrating a list from an internal array backbone to linked nodes) will not break client applications. This is *why a list ADT can be used without knowing its implementation* — the interface specifies behavior independently of storage.

### Sorted vs. Unsorted List Operations

The cost of list operations depends heavily on whether the list maintains sorted order:

| Operation | Unsorted List | Sorted List |
| --- | --- | --- |
| **Insertion** | $O(1)$ — append anywhere (e.g., at the end) | $O(n)$ — must *find the correct position*, then shift/link |
| **Search** | $O(n)$ — linear scan, no order to exploit | $O(\log n)$ — binary search becomes possible (array-backed) |
| **Deletion (by key)** | $O(n)$ to find; removal itself can be $O(1)$ (swap with last, order irrelevant) | $O(n)$ to find and close the gap while preserving order |

- **Why deletion algorithms can look identical for sorted and unsorted lists:** deletion fundamentally locates an item **by its key**, not by its ordering. The act of removing the matched item is the same regardless of whether neighbors are ordered, so the core algorithm overlaps.
- **Insertion is where they diverge:** an unsorted list can drop a new item anywhere ($O(1)$), while a sorted list must first locate the correct insertion point to preserve order.

### Binary Search (Requires a Sorted List)

Binary search repeatedly halves the search interval, giving $O(\log n)$ lookups — but it has strict preconditions.

- **Precondition:** the list **must be sorted by the search key**. (It does *not* require the list to be array-based, duplicate-free, or bounded — only sorted.)
- **Termination:** the algorithm terminates because each iteration **adjusts `first` or `last`**, shrinking the interval until `first > last`. Updating the midpoint alone is a consequence; the narrowing of the `first`/`last` bounds is what guarantees the loop ends.

```cpp
// Iterative binary search over a sorted array.
// Returns the index of key, or -1 if not present.
int binarySearch(const int arr[], int n, int key) {
    int first = 0;
    int last = n - 1;
    while (first <= last) {              // terminates when first > last
        int mid = first + (last - first) / 2; // avoids overflow vs (first+last)/2
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            first = mid + 1;             // adjust bounds -> ensures progress
        } else {
            last = mid - 1;              // adjust bounds -> ensures progress
        }
    }
    return -1;
}
```

### Sentinel Nodes (Header & Trailer)

In basic linked configurations, inserting or deleting elements at the boundaries requires specialized validation checks (`if (head == nullptr)`). This design risk can be mitigated using **Sentinel Nodes**:

- A permanent dummy **Header** node placed at the entry location.
- A permanent dummy **Trailer** node placed at the termination location.
- **The Benefit:** The list is never empty, and every valid data node is guaranteed to sit between two physical nodes. This eliminates complex edge-case conditions, allowing a single unified algorithm for all insertions and deletions.

### Circular Singly Linked Lists

A variant where the final node's traditional terminal pointer value (`nullptr`) is replaced with a reference address looping straight back to the initial `head` node.

- **Successor Trait:** In a non-empty circular singly linked list, **every node is guaranteed to point to a valid successor node**. There are no terminal endpoints.
- **Tracking Efficiency:** Typically managed via a single reference pointing to the `tail` node. This gives instant $O(1)$ constant-time access to both the final element (`tail`) and the initial element (`tail->next`).

---

## 5. Generic Programming via C++ Templates

### Compile-Time Instantiation & Type Safety

C++ uses templates to implement generic code reuse without sacrificing performance or **type safety**.

> The feature that lets a **single class definition work with multiple data types while preserving type safety** is **compile-time instantiation** (the template mechanism). This is distinct from *operator overloading* and *runtime polymorphism / dynamic binding* (virtual functions) — those solve different problems. When a client writes `Stack<int> myStack`, the compiler generates a concrete `Stack` specialized for `int` **at compile time**, not at runtime, and not as a macro.

- **The Compilation Mechanism:** When a programmer writes a template structure like `template <typename T> class Stack`, the compiler does not synthesize any machine code initially; it treats it as a structural layout specification.
- **Template Instantiation:** The moment the compiler hits a concrete declaration (e.g., `Stack<int> myStack`), it initiates **Compile-Time Instantiation**. It parses the template layout, substitutes the type parameter `T` with the exact type `int`, and outputs a distinct, fully concrete class into the executable.
- Because compilation maps specific types to dedicated variants, full strict static type verification is achieved before execution.
- **Header Placement Gotcha:** Since instantiation happens wherever the concrete type is used, the compiler needs to see the full template *definition* (not just a declaration). For this reason, template classes and their member function definitions are typically kept entirely in the header file rather than split into a separate `.cpp`.

```cpp
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T val) {
        data = val;
        next = nullptr;
    }
};

template <typename T>
class GenericStack {
private:
    Node<T>* top;
public:
    GenericStack() {
        top = nullptr;
    }
    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
    }
};
```

---

## 6. Algorithmic Complexity Analysis & Isolated Unit Testing

### Time Complexities Summary

| Operation / Structure | Big-O Complexity | Rationale |
| --- | --- | --- |
| **Stack Push / Pop** | $O(1)$ Constant | Manipulations occur entirely at a pre-referenced memory location (`top`). |
| **Stack Search** | $O(n)$ Linear | Requires stepping sequentially through all elements to match target properties. |
| **Triangular Matrix Traversal** | $O(N^2)$ Quadratic | Iterating through an $N \times N$ lower triangular matrix ($\text{column} \le \text{row}$) requires processing $\frac{N(N+1)}{2}$ items. Dropping lower-order constants yields a quadratic relationship. |

### Component Unit Isolation Testing

When verifying functionality inside a function (e.g., `computeTax()`), developers must isolate the target execution paths from external unstable dependencies (such as production databases).

- **Test Driver:** Substitutes for a *caller* (the code "above" the unit). It drives the function under test by feeding it preset parameters and inspecting results.
- **Test Stub:** Substitutes for a *dependency the unit calls* (the code "below" it) that is missing, slow, or unsafe during testing. It returns predefined, controlled values so the unit can be exercised in isolation.

> Direction cheat-sheet: a **driver calls down into** the unit under test; a **stub stands in for what the unit calls**.

**Worked example:** Suppose `computeTax()` internally calls `lookupRate()`, which queries a live database you cannot use during testing. To test `computeTax()` in isolation, replace `lookupRate()` with a **stub** that returns controlled, predictable rate values. (A driver would be the right tool if you instead needed something to *call* `computeTax()`; a database test plan, regression suite, or inspection checklist do not isolate the dependency.)
