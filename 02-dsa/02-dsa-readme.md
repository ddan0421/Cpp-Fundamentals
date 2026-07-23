# Data Structures & Algorithms

Course notes, slides, labs, and practice work organized by unit. Each unit folder
maps to one or more textbook chapters and contains lecture slide notes,
supplemental reading summaries, and graded/practice labs.

> See [`dsa_overview.md`](./dsa_overview.md) for a single consolidated concept
> reference across all topics.

---

## Unit Overview

| Unit | Chapters | Focus |
|------|----------|-------|
| [Unit 1](#unit-1--foundations--lists) | 1–4 | Software engineering, data design, ADTs, unsorted & sorted lists |
| [Unit 2](#unit-2--stacks-queues--lists-plus) | 5–6 | Stacks, queues, templates, linked-list variants, copy semantics |
| [Unit 3](#unit-3--recursion--binary-search-trees) | 7–8 | Recursion, binary search trees |
| [Unit 4](#unit-4--heaps-priority-queues--hashing) | 9, 11 | Heaps, priority queues, heap sort, sets, maps, hashing |
| [Unit 5](#unit-5--sorting) | 12 | Comparison and non-comparison sorting algorithms |
| [Unit 6](#unit-6--graphs) | 13 | Graphs, traversals, shortest paths |

---

## Unit 1 — Foundations & Lists

Chapters 1–4. Establishes software-engineering practices, the ADT mindset, and
the first two list ADTs.

**Topics introduced**
- **Software engineering principles:** the software process, quality goals,
  specifications & design, verification, error types, program/integration
  testing, C++ I/O basics.
- **Data design & implementation:** views of data, abstraction levels, data
  encapsulation, the three levels of data, ADT operator categories, records
  (structs), 1-D and 2-D arrays, C++ classes vs. structs, object-oriented
  concepts, exception handling, namespaces.
- **Algorithm analysis:** Big-O notation and common orders of magnitude.
- **ADT Unsorted List:** list variants, operations, generic data types
  (`ItemType`), and both array-based and linked-list-based implementations.
- **ADT Sorted List:** pre/postconditions, array-based, dynamically-allocated
  array-based, and linked-list-based implementations; Big-O comparison; bounded
  vs. unbounded ADTs; OO design methodology.
- **Supplemental:** C-strings; Runestone intro, analysis, and linear structures
  (stack, queue, deque) overview.

**Key files:** `U01_Slides_C1-2.md`, `U01_Slides_C3-4.md`,
`U01_Runestone_C1-3.md`, `c-strings-notes.md` · **Labs:** `lab1/`, `practice_lab/`

---

## Unit 2 — Stacks, Queues & Lists Plus

Chapters 5–6. The stack and queue ADTs, plus advanced list techniques.

**Topics introduced**
- **Stack ADT:** logical level, operations, applications; array-based,
  dynamic-array-based, and linked-list-based implementations.
- **Queue ADT:** logical level, operations, applications; fixed-front vs.
  floating circular array queues, counted queue (inheritance), linked-list
  queue, and circular linked queue (single pointer).
- **Lists Plus:** C++ templates, circular linked lists, doubly linked lists,
  lists with headers and trailers.
- **Copy semantics:** shallow vs. deep copy, copy constructors, friend
  functions, operator overloading for deep copy, and the Rule of the Big 3.
- **Advanced:** linked list as an array of records; polymorphism with virtual
  functions.
- **Supplemental:** Runestone recursion chapter (three laws of recursion, stack
  frames, Tower of Hanoi, dynamic programming intro).

**Key files:** `U02_Slides_C5-6.md`, `U02_Runestone_C5.md`,
`Unit1_2_Summary.md`, `ch5_adt_stack_queue.pdf`, `ch6_lists_plus.pdf`
· **Labs:** `lab2/`, `practice_lab/`

---

## Unit 3 — Recursion & Binary Search Trees

Chapters 7–8. Recursive problem solving and the binary search tree.

**Topics introduced**
- **Programming with recursion:** anatomy of a recursive function, the
  three-question verification method, recursive list search, combinations,
  recursive linked-list processing (RevPrint), recursive binary search.
- **How recursion works:** activation records and the run-time stack, run-time
  traces, why static allocation can't support recursion.
- **Forms of recursion:** linear, tail, binary, and multiple recursion; recursive
  squaring; Fibonacci; recursive quick sort; removing recursion
  (iteration/stacking); deciding when to use recursion.
- **Binary search trees:** tree vocabulary, level/height/efficiency, the binary
  search property, recursive `PutItem`/`DeleteItem`.

**Key files:** `U03_Slides_C7-8.md`, `ch7_programming_with_recursion.pdf`,
`ch7_recursion_supplemental.pdf`, `ch8_binary_search_trees.pdf`, `references.md`
· **Labs:** `lab3/`, `practice_lab/`

---

## Unit 4 — Heaps, Priority Queues & Hashing

Chapters 9 & 11. Heap-backed priority queues and the set/map/hashing family.

**Topics introduced**
- **Priority queue ADT:** choosing an implementation.
- **Heaps:** array-based binary trees, heap definition, `ReheapDown`/`ReheapUp`,
  parent/child index math, a self-contained `MaxHeap`.
- **Priority queue via heap:** `PQType` class, enqueue/dequeue, efficiency
  comparison, the C++ `priority_queue` class and comparison functors.
- **Heap sort:** building the heap in place, sorting with the heap, analysis.
- **Sets:** logical/application/implementation levels; C++ standard library set.
- **Maps:** logical/application/implementation levels; C++ `unordered_map`.
- **Hashing:** hash functions, collisions, and collision handling.

**Key files:** `U04_Slides_C9-11.md`,
`ch9_heaps_priority_queues_and_heap_sort.pdf`, `ch11_sets_maps_hashing.pdf`
· **Labs:** `lab4/`, `practice_lab/`, `practice_lab2/`, `practice_lab3/`

---

## Unit 5 — Sorting

Chapter 12. A comprehensive tour of sorting algorithms and their trade-offs.

**Topics introduced**
- **O(N²) sorts:** straight selection sort, bubble sort (with early-stop
  ShortBubble), insertion sort, shell sort.
- **O(N log N) sorts:** merge sort, quick sort (Split/partition), heap sort.
- **Non-comparison sort:** radix sort (LSD, with negative-number support).
- **Analysis & considerations:** efficiency comparison, keys and stability,
  sorting with pointers, caching.
- **Advanced:** parallel merge sort (threads, chunking, timing with `<chrono>`).
- **In practice:** `std::sort` on user-defined types, with comparison functions,
  and on plain C-style arrays.

**Key files:** `U05_Slides_C12.md`, `ch12_sorting.pdf`
· **Labs:** `lab5/`, `practice_lab/`

---

## Unit 6 — Graphs

Chapter 13. Graph representations and core graph algorithms.

**Topics introduced**
- **Graph fundamentals:** logical level, edge direction, formal definition,
  adjacency & paths, completeness, weighted graphs, graph ADT operations.
- **Traversals:** depth-first search (DFS) and breadth-first search (BFS), with
  marking to avoid cycles.
- **Shortest path:** the single-source shortest-path problem and algorithm.
- **Implementations:** array-based (`AddVertex`, `AddEdge`, `GetWeight`,
  `GetToVertices`), linked adjacency lists, and hash-map adjacency lists with a
  visitor-pattern BFS.

**Key files:** `U06_Slides_C13.md`, `ch13_graphs.pdf`, `testbook.pdf`
· **Labs:** `lab6/`, `practice_lab/`

---

## Folder Conventions

- `U0X_Slides_*.md` — lecture slide notes for the unit's chapters.
- `U0X_Runestone_*.md` — supplemental reading summaries.
- `chNN_*.pdf` — textbook chapter PDFs.
- `labN/` — graded lab for the unit; `practice_lab*/` — practice exercises.
