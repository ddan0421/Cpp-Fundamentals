# Arrays: Searching and Sorting — Notes (Unit 6)

A compact “mini lecture” based on the course examples in `01-search-algo.cpp`, `02-sort-algo.cpp`, `Unit6_Assignment_Dan/`, related pre-lab work, and the **Pre-lab Reading Assignment** in `Unit6-Lab07_Instructions.pdf` (Lesson 8 — Searching and Sorting Arrays). Use it as a review sheet before labs and exams.

---

## Pre-lab reading (Lab 7 / Lesson 8)

The lab handout’s reading section defines the goals of the unit and walks through the same algorithms summarized below.

### What the unit introduces (from the handout)

1. The idea of a **search routine** — a procedure for locating a specific **datum** in a **collection** of data.
2. **Linear search** and **binary search**, with their trade-offs.
3. The idea of a **sorting algorithm** (to create the order binary search needs, or for presentation).
4. **Bubble sort** and **selection sort**.

Before lab, the course expects you to **read** that section (~20 min., textbook page 138 in the original) and complete the separate **Pre-lab Writing Assignment** (fill-in and short trace problems).

### Vocabulary and analogy

- A **search algorithm** is a **procedure for locating a specific value** in a collection. The textbook uses a **phone book**: sections are alphabetized, so you jump to “W” and scan for “Wilson Electric” — still a search, but structure makes it easier than a random list.
- In code, the collection is usually an **array** (`int`, `char`, …).

### Linear search — “Harpoon” and first match

The reading uses a **character array** for the first full program:

```cpp
char word[8] = "Harpoon";
// indices 0..6 are letters; word[7] is '\0' (null terminator — end of string)
```

A linear search for `'o'` checks left to right and returns **`4`** (first `'o'`). It **does not** continue to the second `'o'` at index 5 — the function returns as soon as it finds a match.

- **Not found:** convention is **`−1`**, which is not a valid subscript.
- **User-facing “position”:** the sample prints **`found + 1`** (e.g. index `4` → “5th position”) because people often count from 1, not 0.

This matches the end-to-end pattern in **section 8** below: report **index** inside the function, convert to **position** for output if required.

### Binary search — must be **consistently** ordered

- **Advantage:** each probe **eliminates about half** of the remaining range (very fast on large arrays).
- **Requirement:** data must be in **non-increasing** (descending) or **non-decreasing** (ascending) order **throughout** — the comparisons in your code must match that order.

The reading stresses an array that **fails** binary search: values that **mostly** go one way but **break** the order (e.g. decreasing then increasing in the middle). Binary search is only valid when the ordering rule holds for **every** adjacent step in the logical sense (monotone in the direction you assume).

**Ascending vs descending:** the same `first` / `last` / `middle` loop works; you flip whether “smaller than middle” discards the left or right half. The textbook’s **Sample Program 8.2** uses an array sorted **largest to smallest**; compare your `if` / `else` branches to the ascending case so you discard the correct half.

**Duplicates:** if a value appears more than once, binary search returns **some** index where `array[middle] == value` — often the **first** occurrence in the file’s `2` example, but **which** duplicate you get depends on array layout and the path of midpoints. Know this for lab questions that ask “which 19” or “which 12.”

### Bubble sort (from the reading’s trace)

- Compare **adjacent** pairs; **swap** if out of order; repeat until a full pass does **no** swaps.
- After each pass, the **next largest** value tends to “**bubble**” toward the high end; the inner loop can shrink the active **upper bound** (`bottom` in the sample) because the tail is settled.
- **Trade-off:** simple to understand, but on large arrays values only **move one slot per swap** in the basic version — can be slow.

### Selection sort (from the reading)

- Each pass: find the **smallest** (for ascending) in the unsorted suffix and **swap** it into the next position (`seek`).
- **Advantage (common statement):** at most about **`n − 1` moves** for `n` elements.
- **Cost:** on the order of **`n(n − 1) / 2` comparisons** in the usual nested-loop form.

### Pre-lab writing assignment — quick review cues

The fill-in section checks the same ideas: linear search is **simple** but **time-consuming** on large arrays (especially when the target is absent); binary search is **more efficient** but needs **ordered** data; after **3** halving steps the remaining interval is about **1/8** of the original; **bubble** sort moves slowly one step at a time; **selection** sort caps moves at **`n − 1`**. Trace exercises ask for the **first few swaps** of bubble and selection on small arrays — do those by hand, then match your program’s step-by-step output in Lab 8.3.

---

## 1. Why this unit matters

- **Search** answers: “Is this value in the collection, and where?”
- **Sort** answers: “Put the values in a defined order” (usually ascending or descending).

Many algorithms assume **order** (especially binary search). In practice you often **sort first, then search**.

---

## 2. Linear search (sequential search)

### Idea

Start at index `0` and examine each element in order until you find the target or run out of elements.

### When it shines

- **Simple** to code and reason about.
- Works on **any** array: values do **not** need to be sorted.

### Trade-off

- For large arrays, checking “one by one” can be slow.
- If the value is **missing**, you may have to inspect **every** element before you know for sure.

### Typical return convention

- Return the **index** (subscript) where the value was found.
- Return **`-1`** if the value is not found (a sentinel that cannot be a valid index).

### Two styles (both appear in the notes)

**For-loop version** (direct):

```cpp
int searchList(int list[], int numElems, int value) {
  for (int count = 0; count < numElems; count++) {
    if (list[count] == value)
      return count;
  }
  return -1;
}
```

**While-loop with flag** (pretest loop):

```cpp
int linearSearch(int arr[], int size, int value) {
  int index = 0;
  int position = -1;
  bool found = false;

  while (index < size && !found) {
    if (arr[index] == value) {
      found = true;
      position = index;
    }
    index++;
  }
  return position;
}
```

### Pitfall (easy to catch in grading)

The loop must only use valid indices: **`0` through `numElems - 1`**. Using `count <= numElems` walks past the last element and is undefined behavior.

### Duplicates

If the value appears more than once, a simple linear search usually returns the **first** match it encounters (depends on loop direction and code).

---

## 3. Binary search

### Idea

If the data are **sorted** (ascending or descending — but the comparisons must match that order), compare the target to the **middle** element and **discard half** of the range on each step.

### Requirement

The array must be **ordered** according to the comparisons used in the algorithm (for ascending order, “smaller values on the left, larger on the right”).

### Typical return convention

Same as linear search: **index** or **`-1`**.

### Ascending-order pattern (from the course examples)

Use two indices, `first` and `last`, and shrink the interval:

```cpp
int binarySearch(int array[], int numElems, int value) {
  int first = 0;
  int last = numElems - 1;
  int middle;

  while (first <= last) {
    middle = first + (last - first) / 2;  // avoids overflow on large ranges

    if (array[middle] == value)
      return middle;
    else if (array[middle] < value)
      first = middle + 1;
    else
      last = middle - 1;
  }
  return -1;
}
```

### Why `middle = first + (last - first) / 2`

It computes the midpoint in a safe way for integer indices and matches the “split the range in half” idea.

### If the array is not actually sorted

Binary search is **not** logically correct: you might get a wrong answer or a misleading index. Always **sort first** (or maintain sorted data) when using binary search.

### Pre-lab insight: how fast the range shrinks

Each successful “halving” step (when you still have not found the value) roughly cuts the remaining interval by half. After **3** halving steps, the remaining interval is about **1/8** of the original (because $(1/2)^3 = 1/8$).

---

## 4. Bubble sort

### Idea (ascending)

Repeatedly walk through the array, comparing **adjacent** pairs. If a pair is out of order, **swap** them. Repeat until a full pass makes **no swaps**.

### Intuition

Large values “bubble” toward the end; after each pass, you can often shrink the inner loop’s upper bound because the tail becomes settled.

### Trade-offs

- Conceptually simple.
- Can be inefficient on large arrays because values only move **one position** per swap in the basic version.

### Core structure (do-while + flag) from `02-sort-algo.cpp`

- `bottom` starts at `elems - 1` and decreases as the largest elements settle.
- `swap` tracks whether any exchange happened this pass.

### Descending-order variant (assignment-style)

To sort **descending**, reverse the comparison used for swapping (for example, bubble when `array[count] < array[count + 1]` instead of `>`).

---

## 5. Selection sort

### Idea (ascending)

For each position `seek` from `0` to `n - 2`:

1. Scan the rest of the array for the **smallest** value.
2. Swap that smallest into position `seek`.

### Trade-offs (from the notes)

- **Moves** are relatively cheap in a common analysis: at most about **`n - 1` swaps** in many presentations.
- Comparisons are still plentiful: on the order of **$n(n-1)/2$** comparisons for the usual nested-loop structure.

### Descending-order variant (assignment-style)

Scan for the **largest** remaining value each pass and swap it into place (same structure, different comparison).

---

## 6. Working with C-arrays in functions

### Parameter syntax you will see

These mean the same thing for a 1-D array parameter:

```cpp
void f(int arr[], int size);
void f(int *arr, int size);
```

### Why pass `size`

In C++, an array parameter does **not** carry its length. The function needs **`size`** (or an end pointer) to avoid reading past the end.

### `const` for read-only data

If a function must not modify the array, prefer:

```cpp
int binarySearch(const int array[], int numElems, int value);
```

This documents intent and prevents accidental writes.

---

## 7. Vectors: sorting and searching (`std::vector`)

Vectors are array-like containers that **know their size** and can grow. For many assignments you include:

```cpp
#include <vector>
```

### Creating and filling

```cpp
std::vector<int> v;           // empty
v.push_back(10);              // append

std::vector<int> w(8, 0);     // 8 ints, each initialized to 0
std::vector<int> z(50);       // 50 default-initialized ints
```

### Size without a separate `SIZE` constant

Use the **member function** `size()`:

```cpp
for (size_t i = 0; i < v.size(); ++i) {
  // use v[i]
}
```

`size()` returns a `size_t` (unsigned). It is common to write:

```cpp
for (int i = 0; i < static_cast<int>(v.size()); ++i) { ... }
```

when you need a signed index type to match the rest of your code.

### Passing vectors to functions — references matter

By default, passing `std::vector<T> v` **copies** the whole vector. That is usually wrong for sort routines (slow, and sorts the **copy**, not the caller’s data).

**Preferred patterns:**

```cpp
// Sort modifies the caller’s vector — pass by non-const reference
void selectionSort(std::vector<int> &v);

// Search does not modify — pass by const reference
int linearSearch(const std::vector<int> &v, int target);

// If you only need read access and an index result:
int binarySearch(const std::vector<int> &v, int target);
```

Inside these functions you can use `v.size()` instead of a separate size parameter:

```cpp
void selectionSort(std::vector<int> &v) {
  int n = static_cast<int>(v.size());
  for (int seek = 0; seek < n - 1; ++seek) {
    int minIndex = seek;
    int minValue = v[seek];
    for (int i = seek + 1; i < n; ++i) {
      if (v[i] < minValue) {
        minValue = v[i];
        minIndex = i;
      }
    }
    std::swap(v[minIndex], v[seek]);
  }
}
```

### When you still pass an explicit size

Sometimes course code (and C-style interfaces) uses:

```cpp
void SelectionSort(int array[], int Elem);
```

If you store data in a vector but want to reuse that exact function, you can pass a pointer to the first element:

```cpp
std::vector<int> arr(n);
SelectionSort(arr.data(), static_cast<int>(arr.size()));
```

`arr.data()` gives a pointer to contiguous storage (like an array). You are responsible for keeping the **size** consistent with how many elements are valid.

### `const` correctness with vectors

- Use `const std::vector<T> &` when the function **reads** elements only.
- Use `std::vector<T> &` when the function **mutates** (sorting, swapping, filling).

---

## 8. End-to-end pattern: sort, then binary search

1. Ensure values are ordered the way your `binarySearch` expects (ascending vs descending comparisons).
2. Run your sort (`bubbleSort`, `selectionSort`, …).
3. Run `binarySearch`.
4. Translate index to “human position” if needed: **position number** is often **`index + 1`**.

This matches the integrated assignment flow: **sort in its own function**, **search in its own function**, then report **index or -1**.

---

## 9. Quick comparison table

| Algorithm        | Needs sorted data? | Typical “not found” |
|-----------------|--------------------|---------------------|
| Linear search   | No                 | Often `-1`          |
| Binary search   | Yes                | Often `-1`          |
| Bubble / selection sort | No (creates order) | N/A (in-place reorder) |

---

## 10. Big O: why some algorithms are more efficient

**Big O** describes how the **amount of work** grows as the problem size **$n$** (number of elements) grows. Constants and small details are dropped; we care about the **dominant trend** (linear vs logarithmic vs quadratic).

### Search

| Algorithm       | Typical worst-case time | Why |
|----------------|-------------------------|-----|
| Linear search  | **$O(n)$**            | In the worst case you may compare against **every** element (e.g. value missing or at the end). Each step is $O(1)$, but there can be **$n$** steps. |
| Binary search  | **$O(\log n)$**       | Each probe discards **about half** of the remaining index range. The number of steps grows like “how many times can you halve $n$?” — **logarithmic**, not proportional to $n$. |

For large $n$, **$\log n$** is much smaller than **$n$** (e.g. $n = 1{,}000{,}000$: $\log_2 n \approx 20$ vs a million steps). Binary search only applies when the array is **consistently ordered**; building that order has its own cost (see sorts below).

### Sort (bubble and selection as in this unit)

| Algorithm        | Typical time (usual analysis) | Notes |
|-----------------|-------------------------------|--------|
| Bubble sort     | **$O(n^2)$** (worst case, basic version) | Nested passes and inner work: roughly **$n$** rounds of **$O(n)$** comparisons/swaps in the worst case. Values move **one slot per swap** in the naive version — matches the “slow on large arrays” intuition above. |
| Selection sort  | **$O(n^2)$** comparisons   | About **$n(n-1)/2$** comparisons — **$\Theta(n^2)$**. **Swaps** are only **$O(n)$** (at most about **$n-1$** in many presentations), so selection sort can be preferable when **writes** are expensive, but **comparisons** still dominate for large $n$. |

### Putting it together

- **One search:** A single **$O(n)$** linear scan can beat **sort ($O(n^2)$) + binary search ($O(\log n)$)** if you only need to find something once in unsorted data.
- **Many searches** on the same data, or **order required** for other reasons: **sort once**, then **$O(\log n)$** binary searches can win overall; your notes’ **sort, then binary search** pattern fits that idea.

---

## 11. File map in this folder (for practice)

| File / folder              | What to study                          |
|---------------------------|----------------------------------------|
| `Unit6-Lab07_Instructions.pdf` | Lesson 8 pre-lab reading, Labs 8.1–8.4, writing assignment |
| `01-search-algo.cpp`     | Linear + binary search, commentary     |
| `02-sort-algo.cpp`       | Bubble + selection, `swap` variant     |
| `Unit6_Assignment_Dan/*` | Lab-style implementations            |
| `student_generated_code.cpp` | File I/O + vector + `data()` reuse |

---

*These notes synthesize the provided course files; always follow your instructor’s exact submission requirements for prototypes, output wording, and file names.*
