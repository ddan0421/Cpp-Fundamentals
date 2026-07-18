# Chapter 12 — Sorting (Comprehensive Lecture Notes)

> Notes compiled from the Chapter 12 lecture slides, with corresponding code
> examples pulled from the textbook (*A Laboratory Course in C++ Data
> Structures* / Dale). Each algorithm pairs the conceptual explanation with the
> actual implementation used in the book.

---

## Table of Contents

1. [Sorting Revisited](#1-sorting-revisited)
2. [Straight Selection Sort](#2-straight-selection-sort)
3. [Bubble Sort](#3-bubble-sort)
4. [Insertion Sort](#4-insertion-sort)
5. [O(N log₂N) Sorts](#5-on-log₂n-sorts)
6. [Merge Sort](#6-merge-sort)
7. [Quick Sort](#7-quick-sort)
8. [Heap Sort](#8-heap-sort)
9. [Efficiency & Other Considerations](#9-efficiency--other-considerations)
10. [Keys, Stability, Pointers, and Caching](#10-keys-stability-pointers-and-caching)
11. [Radix Sort](#11-radix-sort)
12. [Parallel Merge Sort](#12-parallel-merge-sort)
13. [Summary Comparison Table](#13-summary-comparison-table)

---

## 1. Sorting Revisited

Sorting — putting an unsorted list of elements into order — is one of the most
common and useful operations in computing. Efficient sorts can yield large
savings for many applications. Because sorting large data sets can be very
time-consuming, a good sorting algorithm is highly desirable; this is one area
where programmers sometimes sacrifice clarity in favor of speed.

**How we evaluate sorting algorithms:**

- The number of **comparisons** made (the central operation: comparing two
  values to see which is smaller).
- The number of times **data is moved**.
- The amount of **additional memory** used.

**Sorting efficiency cases:**

- **Worst Case:** The data is in reverse order.
- **Average Case:** Random data, may be somewhat sorted already.
- **Best Case:** The array is already sorted.

Typically, average and worst case performance are similar, if not identical. For
many algorithms, the best case is also the same as the other cases.

Throughout the chapter, we assume we are sorting an **array** named `values`
whose elements are of type `ItemType` (a built-in type or a class that overloads
the relational and assignment operators). The number of elements is `numValues`
(referred to as `N` in analysis).

A helper used by nearly every algorithm is `Swap`. It is declared `inline` so the
compiler can insert the body directly at each call site, avoiding function-call
overhead (important because `Swap` is called so frequently):

```cpp
template<class ItemType>
inline void Swap(ItemType& item1, ItemType& item2)
// Post: Contents of item1 and item2 have been swapped.
{
    ItemType tempItem;
    tempItem = item1;
    item1 = item2;
    item2 = tempItem;
}
```

---

## 2. Straight Selection Sort

**Algorithm:**

1. Set `current` to the first index of the array.
2. Find the smallest value in the unsorted part of the array.
3. Swap the smallest value with the value in `current`.
4. Increment `current` and repeat steps 2–4 until the end of the array is reached.

The identifying feature of a selection sort is that, on each pass, one element
(the smallest) is put into its proper place.

**Finding the minimum (`MinIndex`):**

```cpp
template<class ItemType>
int MinIndex(ItemType values[], int startIndex, int endIndex)
// Post: Returns the index of the smallest value in
//        values[startIndex]..values[endIndex].
{
    int indexOfMin = startIndex;
    for (int index = startIndex + 1; index <= endIndex; index++)
        if (values[index] < values[indexOfMin])
            indexOfMin = index;
    return indexOfMin;
}
```

**The sort itself:**

```cpp
template<class ItemType>
void SelectionSort(ItemType values[], int numValues)
// Post: The elements in the array values are sorted by key.
{
    int endIndex = numValues - 1;
    for (int current = 0; current < endIndex; current++)
        Swap(values[current],
             values[MinIndex(values, current, endIndex)]);
}
```

**Analyzing Selection Sort:**

- A very simple, easy-to-understand algorithm.
- `N` iterations are performed; iteration `I` checks `N − I` items to find the
  next smallest value.
- Total comparisons: `(N−1) + (N−2) + … + 1 = N(N−1)/2`.
- Therefore selection sort is **O(N²)** — and even in the best case it is still
  O(N²), because the arrangement of values does not affect the work done.

| Number of Items | Number of Comparisons |
|-----------------|-----------------------|
| 10              | 45                    |
| 20              | 190                   |
| 100             | 4,950                 |
| 1,000           | 499,500               |
| 10,000          | 49,995,000            |

Doubling the array size roughly quadruples the number of comparisons.

### zyBooks variant — inline "find smallest, then swap"

zyBooks presents the same algorithm with a slightly different structure: instead
of a separate `MinIndex` helper, the search for the smallest remaining element is
inlined into the sort as a nested loop that tracks `indexSmallest`. A single swap
is then performed per outer pass. This makes the "one element placed per pass"
property of selection sort very explicit.

**The selection sort:**

```cpp
void SelectionSort(int* numbers, int numbersSize, SortTracker& tracker) {
   for (int i = 0; i < numbersSize - 1; i++) {
      // Find index of smallest remaining element
      int indexSmallest = i;
      for (int j = i + 1; j < numbersSize; j++) {
         if (tracker.IsFirstLTSecond(numbers, j, indexSmallest)) {
            indexSmallest = j;
         }
      }

      // Swap numbers[i] and numbers[indexSmallest]
      tracker.Swap(numbers, i, indexSmallest);
   }
}
```

- Outer loop index `i` marks the boundary of the sorted portion; on pass `i` the
  correct value for position `i` is found and swapped in.
- Inner loop scans `numbers[i+1..numbersSize-1]`, updating `indexSmallest`
  whenever a smaller element is found.
- Exactly **one swap per outer pass** → `N − 1` swaps total, regardless of the
  input order. (Note: it swaps even when `i == indexSmallest`, i.e., a "no-op"
  swap when the element is already in place.)

**Instrumenting with `SortTracker`:**

zyBooks wraps the comparison and swap operations in a `SortTracker` object so the
demo can report exactly how much work each sort performs. The tracker counts
comparisons and swaps and encapsulates the raw operations:

```cpp
class SortTracker {
private:
   int comparisonCount;
   int swapCount;

public:
   SortTracker() {
      comparisonCount = 0;
      swapCount = 0;
   }

   int GetComparisonCount() const { return comparisonCount; }
   int GetSwapCount() const { return swapCount; }

   // Returns true if array[index1] < array[index2]. Increments comparison count.
   bool IsFirstLTSecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] < array[index2];
   }

   // Returns true if array[index1] <= array[index2]. Increments comparison count.
   bool IsFirstLTESecond(const int* array, int index1, int index2) {
      comparisonCount++;
      return array[index1] <= array[index2];
   }

   // Swaps array[index1] and array[index2]. Increments swap count.
   void Swap(int* array, int index1, int index2) {
      swapCount++;
      int temp = array[index1];
      array[index1] = array[index2];
      array[index2] = temp;
   }
};
```

**Demo driver:**

```cpp
void SelectionSortDemo(int* numbersArray, int arrayLength) {
   cout << "Before sorting:    " << ArrayToString(numbersArray, arrayLength);
   cout << endl;

   SortTracker tracker;
   SelectionSort(numbersArray, arrayLength, tracker);

   cout << "After sorting:     " << ArrayToString(numbersArray, arrayLength);
   cout << endl;
   cout << "Total comparisons: " << tracker.GetComparisonCount() << endl;
   cout << "Total swaps:       " << tracker.GetSwapCount() << endl;
}
```

**What the tracker reveals — order-independence of selection sort:**

Running the demo on three 9-element arrays (unsorted, ascending, descending)
shows the defining trait of selection sort: the amount of work is the **same
regardless of the input's initial order**.

- Comparisons are always `N(N−1)/2 = 9·8/2 = 36` — the nested loop always scans
  every remaining element, so there is **no early exit and no best case**.
- Swaps are always `N − 1 = 8`, one per outer pass (including no-op swaps when an
  element is already in place).

| Input array (N = 9) | Comparisons | Swaps |
|---------------------|-------------|-------|
| Unsorted            | 36          | 8     |
| Sorted ascending    | 36          | 8     |
| Sorted descending   | 36          | 8     |

> This confirms the earlier analysis: selection sort is **O(N²) in every case**,
> because the arrangement of the values does not affect the number of comparisons
> performed. Contrast this with `ShortBubble`/`InsertionSort`, which reach O(N) on
> already-sorted data.

---

## 3. Bubble Sort

The bubble sort is a selection sort that uses a different scheme for finding the
minimum value. Smaller elements "bubble up" to the top of the array. Each
iteration puts the smallest unsorted element into its correct place, but it also
changes the locations of other elements along the way.

**Algorithm:**

1. Set `current` to the first index of the array.
2. For every index from the end of the list down to `current + 1`, swap adjacent
   pairs of elements that are out of order ("bubble up" the smallest).
3. Increment `current` and repeat.
4. Stop when `current` is at the end of the array.

**Bubbling up (`BubbleUp`):**

```cpp
template<class ItemType>
void BubbleUp(ItemType values[], int startIndex, int endIndex)
// Post: Adjacent pairs that are out of order have been switched
//       between values[startIndex]..values[endIndex] beginning at
//       values[endIndex].
{
    for (int index = endIndex; index > startIndex; index--)
        if (values[index] < values[index-1])
            Swap(values[index], values[index-1]);
}
```

**The sort itself:**

```cpp
template<class ItemType>
void BubbleSort(ItemType values[], int numValues)
// Post: The elements in the array values are sorted by key.
{
    int current = 0;
    while (current < numValues - 1)
    {
        BubbleUp(values, current, numValues-1);
        current++;
    }
}
```

**Analyzing Bubble Sort:**

- Takes `N−1` iterations; each iteration `I` performs `N−I` comparisons.
- Same comparison count as selection sort → **O(N²)**.
- However, it may perform several swaps per iteration (making `inline Swap` even
  more valuable).

### ShortBubble — stopping early

The basic `BubbleSort` keeps calling `BubbleUp` even after the array is sorted.
`ShortBubble` uses a `sorted` flag to stop as soon as a pass makes no swaps. This
makes the **best case O(N)** (an already-sorted array needs only one pass), which
is why `ShortBubble` is a good choice for data known to be almost in order.

```cpp
template<class ItemType>
void BubbleUp2(ItemType values[], int startIndex, int endIndex,
               bool& sorted)
// Post: Adjacent pairs that are out of order have been switched
//       between values[startIndex]..values[endIndex] beginning at
//       values[endIndex].
//       sorted is false if a swap was made and true otherwise.
{
    sorted = true;
    for (int index = endIndex; index > startIndex; index--)
        if (values[index] < values[index-1])
        {
            Swap(values[index], values[index-1]);
            sorted = false;
        }
}

template<class ItemType>
void ShortBubble(ItemType values[], int numValues)
// Post: The elements in the array values are sorted by key.
//       The process stops as soon as values is sorted.
{
    int current = 0;
    bool sorted = false;
    while (current < numValues - 1 && !sorted)
    {
        BubbleUp2(values, current, numValues-1, sorted);
        current++;
    }
}
```

- Best case (already sorted): **O(N)**.
- Worst case (reverse sorted): **O(N²)** plus extra swap/flag overhead.

---

## 4. Insertion Sort

Insertion sort acts like inserting each successive element into its proper place
within the already-sorted part of the array, moving elements down as necessary.
Like bubble sort, it uses swapping to find the correct position of the next item.

Starting at the end of the sorted part, we compare `values[current]` to the item
before it and swap if it is smaller — repeating until the values are in order or
we reach the front of the array.

**Inserting one item (`InsertItem`):**

```cpp
template<class ItemType>
void InsertItem(ItemType values[], int startIndex, int endIndex)
// Post: values[0]..values[endIndex] are now sorted.
{
    bool finished = false;
    int current = endIndex;
    bool moreToSearch = (current != startIndex);

    while (moreToSearch && !finished)
    {
        if (values[current] < values[current-1])
        {
            Swap(values[current], values[current-1]);
            current--;
            moreToSearch = (current != startIndex);
        }
        else
            finished = true;
    }
}
```

**The sort itself:**

```cpp
template<class ItemType>
void InsertionSort(ItemType values[], int numValues)
// Post: The elements in the array values are sorted by key.
{
    for (int count = 0; count < numValues; count++)
        InsertItem(values, 0, count);
}
```

**Analyzing Insertion Sort:**

- General case: **O(N²)**, like the previous sorts.
- **Best Case: O(N)** — when the data are already in ascending order, only one
  comparison is needed per item and no data is moved.
- Reading items from a file and inserting into a sorted list is a variation on
  insertion sort.

### zyBooks variant — swap-based insertion

zyBooks presents insertion sort as a swap-driven algorithm rather than the
"shift-then-drop" version. The outer loop walks `i` from `1` to the end; the inner
`while` loop walks `numbers[i]` **backward** through the sorted portion, swapping
it with its left neighbor as long as it is smaller. This mirrors the textbook's
`InsertItem` but expresses the descent as an inline loop with the same
`SortTracker` instrumentation used for the selection-sort demo.

**The insertion sort:**

```cpp
void InsertionSort(int* numbers, int numbersSize, SortTracker& tracker) {
   for (int i = 1; i < numbersSize; i++) {
      int j = i;
      while (j > 0 && tracker.IsFirstLTSecond(numbers, j, j - 1)) {
         // Swap numbers[j] and numbers[j - 1]
         tracker.Swap(numbers, j, j - 1);

         // Decrement j in preparation for next comparison
         j--;
      }
   }
}
```

- The `j > 0` guard is checked **before** the comparison, so reaching the front of
  the array short-circuits and costs no extra comparison.
- Each backward step performs exactly one comparison **and** one swap, so for this
  variant the swap count equals the number of "out of order" comparisons.
- Unlike selection sort, the work depends heavily on the input order: an element
  already in place ends the inner loop after a single comparison.

**Demo driver** (same `SortTracker` and `ArrayToString` helpers as the
selection-sort demo):

```cpp
void InsertionSortDemo(int* numbersArray, int arrayLength) {
   cout << "Before sorting:    " << ArrayToString(numbersArray, arrayLength);
   cout << endl;

   SortTracker tracker;
   InsertionSort(numbersArray, arrayLength, tracker);

   cout << "After sorting:     " << ArrayToString(numbersArray, arrayLength);
   cout << endl;
   cout << "Total comparisons: " << tracker.GetComparisonCount() << endl;
   cout << "Total swaps:       " << tracker.GetSwapCount() << endl;
}
```

**What the tracker reveals — order sensitivity of insertion sort:**

Running the demo on the same three 9-element arrays makes the best/average/worst
cases visible in the counts:

| Input array (N = 9) | Comparisons | Swaps |
|---------------------|-------------|-------|
| Unsorted            | 28          | 22    |
| Sorted ascending    | 8           | 0     |
| Sorted descending   | 36          | 36    |

- **Sorted ascending (best case):** only `N − 1 = 8` comparisons and **zero
  swaps** — each element is already ≥ its predecessor, so every inner loop exits
  after one comparison. This is the **O(N)** best case.
- **Sorted descending (worst case):** every element must travel all the way to the
  front, giving `1 + 2 + … + (N−1) = N(N−1)/2 = 36` comparisons and 36 swaps —
  the **O(N²)** worst case.
- **Unsorted (average case):** falls between the two extremes.

> Compare this with the selection-sort demo, where all three inputs produced 36
> comparisons and 8 swaps. Insertion sort does **less work on nearly-sorted data**,
> which is exactly why it (and `ShortBubble`) beat selection sort when the input is
> already close to order.

> `SelectionSort`, `ShortBubble`, and `InsertionSort` are all O(N²) — too
> time-consuming for large arrays. We need better methods when N is large.

---

## 5. O(N log₂N) Sorts

Sorting a whole array with the previous methods is O(N²). Note that N² is much
larger than `(N/2)² + (N/2)²`. If we could cut the array into two pieces, sort
each, and merge them, we would do a lot less work.

This "divide-and-conquer" idea, applied recursively, produces an entire category
of **O(N log₂N)** sorting algorithms. Chapter 7 introduced one (Quick Sort); this
chapter adds **Merge Sort** and **Heap Sort**.

| N    | log₂N | N²         | N log₂N |
|------|-------|------------|---------|
| 32   | 5     | 1,024      | 160     |
| 64   | 6     | 4,096      | 384     |
| 128  | 7     | 16,384     | 896     |
| 256  | 8     | 65,536     | 2,048   |
| 512  | 9     | 262,144    | 4,608   |
| 1024 | 10    | 1,048,576  | 10,240  |
| 2048 | 11    | 4,194,304  | 22,528  |
| 4096 | 12    | 16,777,216 | 49,152  |

---

## 6. Merge Sort

**Algorithm:**

1. Split the array in half.
2. Recursively MergeSort the two halves.
3. Merge the two sorted halves.
4. **Base Case:** Arrays of fewer than 2 elements are already sorted.

### Merging two sorted arrays

- Simultaneously walk through both halves.
- If `itemA < itemB`, copy `itemA` into the temp array and advance A.
- If `itemB < itemA`, copy `itemB` into the temp array and advance B.
- Stop when one half is empty; copy any remaining elements from the other half.
- Copy the temp array back into the original array.

```cpp
template<class ItemType>
void Merge(ItemType values[], int leftFirst, int leftLast,
           int rightFirst, int rightLast, ItemType tempArray[])
// Post: values[leftFirst]..values[leftLast] and
//       values[rightFirst]..values[rightLast] have been merged.
//       values[leftFirst]..values[rightLast] are now sorted.
{
    int index = leftFirst;
    int saveFirst = leftFirst;
    while ((leftFirst <= leftLast) && (rightFirst <= rightLast))
    {
        if (values[leftFirst] < values[rightFirst])
        {
            tempArray[index] = values[leftFirst];
            leftFirst++;
        }
        else
        {
            tempArray[index] = values[rightFirst];
            rightFirst++;
        }
        index++;
    }

    while (leftFirst <= leftLast)   // Copy remaining items from left half.
    {
        tempArray[index] = values[leftFirst];
        leftFirst++;
        index++;
    }
    while (rightFirst <= rightLast) // Copy remaining items from right half.
    {
        tempArray[index] = values[rightFirst];
        rightFirst++;
        index++;
    }
    for (index = saveFirst; index <= rightLast; index++)
        values[index] = tempArray[index];
}
```

> During execution, only one of the two "copy remaining items" loops ever runs
> — the other half has already been fully consumed by the main merge loop.

### The MergeSort function

The `tempArray` is passed as a parameter (rather than declared locally) so each
recursive call does not create its own copy on the run-time stack. The template
functions are explicitly instantiated with `<ItemType>` — this becomes important
in the parallel version (Section 12).

```cpp
template<class ItemType>
void MergeSort(ItemType values[], int first, int last, ItemType tempArray[])
// Post: The elements in values are sorted by key.
{
    if (first < last)
    {
        int middle = (first + last) / 2;
        MergeSort<ItemType>(values, first, middle, tempArray);
        MergeSort<ItemType>(values, middle + 1, last, tempArray);
        Merge<ItemType>(values, first, middle, middle + 1, last, tempArray);
    }
}
```

The initial call is `MergeSort(values, 0, numValues - 1, tempArray)`.

**Analyzing Merge Sort:**

- The array is split until it becomes 1- or 0-element subarrays (O(N) splitting).
- Merging all subarrays at each level is O(N), and there are log₂N levels
  → **O(N log₂N)** overall.
- **Disadvantage:** requires **O(N) additional memory** for the auxiliary array.

---

## 7. Quick Sort

Quick Sort (first seen in Chapter 7) is another recursive divide-and-conquer
sort:

- Choose a **split value** from the array.
- Partition the array into: values ≤ split value, and values > split value.
- Recursively quick sort the two subarrays.
- **Base Case:** a segment with fewer than two items.

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
        QuickSort(values, first, splitPoint-1);
        QuickSort(values, splitPoint+1, last);
    }
}
```

### The Split function

`first` and `last` move toward the middle, looking for items on the wrong side of
the split value. When they cross, `splitVal` (originally saved from
`values[first]`) is swapped into its correct place at `splitPoint`.

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
        while (onCorrectSide)              // Move first toward last.
            if (values[first] > splitVal)
                onCorrectSide = false;
            else
            {
                first++;
                onCorrectSide = (first <= last);
            }
        onCorrectSide = (first <= last);
        while (onCorrectSide)              // Move last toward first.
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

**Analyzing Quick Sort:**

- If the array splits evenly, log₂N splits are used → **O(N log₂N)**.
- If the array does not split evenly, it approaches **O(N²)**.
- Quick Sort can be inefficient if the data is already (nearly) sorted, because
  using `values[first]` as the split value then produces lopsided splits (one
  element vs. all the rest). A better split value for nearly-sorted data is the
  **middle value** `values[(first + last) / 2]`.
- Additional memory: **O(log₂N)** on average (recursion stack), up to **O(N)** in
  the worst case.

---

## 8. Heap Sort

Heap Sort (first seen in Chapter 9) turns the array into a **heap**, then
repeatedly places the root (the largest value) at the last unsorted slot of the
array, shrinking the heap until it is depleted. It uses the `ReheapDown`
operation to restore the heap's order property.

### ReheapDown

```cpp
template<class ItemType>
void HeapType<ItemType>::ReheapDown(int root, int bottom)
// Post: Heap property is restored.
{
    int maxChild;
    int rightChild;
    int leftChild;
    leftChild = root*2+1;
    rightChild = root*2+2;
    if (leftChild <= bottom)
    {
        if (leftChild == bottom)
            maxChild = leftChild;
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

### HeapSort

```cpp
template<class ItemType>
void HeapSort(ItemType values[], int numValues)
// Assumption: Function ReheapDown is available.
// Post: The elements in the array values are sorted by key.
{
    int index;
    // Convert the array of values into a heap.
    for (index = numValues/2 - 1; index >= 0; index--)
        ReheapDown(values, index, numValues-1);
    // Sort the array.
    for (index = numValues-1; index >= 1; index--)
    {
        Swap(values[0], values[index]);
        ReheapDown(values, 0, index-1);
    }
}
```

> Note: `HeapSort` does not use a retained `HeapType` structure — the heap is a
> temporary structure that exists only inside the function and is diminished
> element by element as the sorted part grows. Using `HeapType` directly would
> require twice the memory.

**Analyzing Heap Sort:**

- Building the heap is a significant **O(N)** overhead, so heap sort should be
  avoided for small arrays.
- `ReheapDown` is **O(log₂N)** and is called N times → overall **O(N log₂N)**.
- The initial order of the elements does **not** matter (unlike Quick Sort).
- **No additional space** is needed — sorts in place.

---

## 9. Efficiency & Other Considerations

Efficiency is not the only thing to consider when choosing a sort. Big-O ignores
constants and lower-order terms, and in some situations O(N²) may grow slower
than O(N log₂N).

> **O(N log₂N) is the theoretical limit** for comparison-based sorting — it can't
> get better than that. But we can still improve the coefficients.

**When N is small:**

- O(N²) sorts often have low overhead and few actions besides comparison.
- O(N log₂N) sorts usually have more overhead and more actions (such as merging).
- When N is small enough, an O(N²) sort might actually be faster.

**Eliminating calls to functions:**

- Every function call adds overhead, but replacing calls with the function body
  makes code less clear.
- The `inline` keyword suggests the compiler replace a call with the body —
  useful for short, frequently used functions like `Swap`.
- Recursive sorts (`MergeSort`, `QuickSort`) carry recursion overhead; a
  nonrecursive version avoids it at the cost of complexity.

**Programmer time:**

- Someone must design, implement, and test the algorithms. More complex
  algorithms are more error-prone.
- Fortunately, we can often rely on standard libraries (e.g., the C++ STL) with
  highly optimized, well-debugged implementations.

**Space considerations:**

- `MergeSort` requires an additional N memory.
- `QuickSort` may use O(N) memory (worst case) for the recursion stack.
- `HeapSort` is more algorithmically complex but uses **no additional memory**.

---

## 10. Keys, Stability, Pointers, and Caching

### Keys and stability

A record may contain multiple keys (e.g., a student's name, ID number, and
major), some of which may not be unique.

```cpp
struct AddressType
{
    // ...
    StrType city;
    long zip;
};
struct NameType
{
    StrType firstName;
    StrType lastName;
};
struct PersonType
{
    long studentNumber;
    NameType name;
    AddressType address;
};
```

To list by major with names alphabetized within each major, we can **sort
twice**: first by name, then by major. This only works if the sort is **stable**.

> A **stable sort** preserves the original order of records with duplicate keys.
> Of the sorts covered, **Heap Sort is the only one that is inherently
> unstable**. Others may be stable or unstable depending on implementation.

**Stable sort example** — students `(ID, Major, Last name)`:

```
Start:                 Sort by Last Name:      Then Sort by Major (stable):
(01, CHM, Davis)       (04, CSC, Albaf)        (05, BIO, Hart)
(02, CSC, Fernandez)   (01, CHM, Davis)        (01, CHM, Davis)
(03, CHM, Patil)       (02, CSC, Fernandez)    (03, CHM, Patil)
(04, CSC, Albaf)       (05, BIO, Hart)         (04, CSC, Albaf)
(05, BIO, Hart)        (03, CHM, Patil)        (02, CSC, Fernandez)
```

An **unstable** sort would keep majors correct but scramble the alphabetical
ordering within each major.

### Sorting with pointers

Moving large objects is inefficient. Instead, keep an array of **pointers** to the
objects and have the sort rearrange the pointers. The objects don't move but can
still be accessed in sorted order. This scheme also lets us keep the same data
sorted on multiple keys via multiple auxiliary pointer arrays.

### Caching

- Not all memory is equal: accessing a memory cell can take as long as executing
  ~100 instructions.
- The processor uses a small, fast **cache** for recently used data, and predicts
  upcoming sequential accesses.
- **Bubble Sort** has predictable access patterns and only compares adjacent
  elements — this complements the cache. It can outperform `HeapSort` on larger
  data sets than theory predicts.
- **Selection Sort** must search the whole list for the next smallest element,
  which works poorly with the cache.
- An **array of pointers** to scattered objects (or a linked list) defeats the
  cache, since the next access can't be predicted.

---

## 11. Radix Sort

Radix sort is **not** a comparison sort — it does not compare items against each
other. Instead, it considers each position in the key and groups keys by their
radix.

- **Radix:** the number of possibilities for each position (the digits in a
  number system). Lowercase letters have a radix of 26; base-10 digits, a radix
  of 10.

**Algorithm (three-digit positive integers):**

- Use 10 queues, one per digit (0–9).
- All items with a 0 in the ones position go into `queues[0]`, etc.
- Once all numbers are distributed, **collect** the queues in order.
- Repeat with the tens and hundreds positions.

```cpp
template<class ItemType>
void RadixSort(ItemType values[], int numValues, int numPositions, int radix)
// Post: Elements in values are in order by key.
{
    QueType<ItemType> queues[radix];
    // With default constructor, each queue size is 500.
    int whichQueue;
    for (int position = 1; position <= numPositions; position++)
    {
        for (int counter = 0; counter < numValues; counter++)
        {
            whichQueue = values[counter].SubKey(position);
            queues[whichQueue].Enqueue(values[counter]);
        }
        CollectQueues(values, queues, radix);
    }
}

template<class ItemType>
void CollectQueues(ItemType values[], QueType<ItemType> queues[], int radix)
// Post: queues are concatenated with queue[0]'s on top and
//       queue[9]'s on the bottom and copied into values.
{
    int index = 0;
    ItemType item;
    for (int counter = 0; counter < radix; counter++)
    {
        while (!queues[counter].IsEmpty())
        {
            queues[counter].Dequeue(item);
            values[index] = item;
            index++;
        }
    }
}
```

### Radix Sort's ItemType

Radix sort must extract a number for each position in the key. This varies by
type, so it is handled by client code via a `SubKey` member function on
`ItemType`. For an integer key, the digit at a given position is:

```
Result = (itemKey / 10^(position - 1)) % 10
```

For example, with `itemKey = 8749`:

| Position | Expression                | Digit |
|----------|---------------------------|-------|
| 1        | `itemKey % 10`            | 9     |
| 2        | `(itemKey / 10) % 10`     | 4     |
| 3        | `(itemKey / 100) % 10`    | 7     |
| 4        | `(itemKey / 1000) % 10`   | 8     |

For alphabetic keys, `SubKey` converts each character to 0–25 (case-insensitive)
or 0–51 (case-sensitive).

**Analyzing Radix Sort:**

- Each item (N) is processed once per key position (P) → **O(N·P)**, but since P
  is usually small relative to N, it's effectively **O(N)**.
- Extra memory is needed for the queues. With **array-based** queues the space is
  prohibitive (each queue needs room for every element). With **linked** queues
  and a **linked list**, values can be moved by changing pointers, so no extra
  copy is needed — improving both time and space.

---

## 12. Parallel Merge Sort

Sometimes O(N log₂N) just isn't fast enough. **Parallel processing** performs
multiple operations simultaneously (unlike serial/sequential processing). Merge
sort divides work into **independent** parts, making it an ideal candidate for
splitting across threads.

### Timing with `<chrono>`

```cpp
#include <chrono>

chrono::time_point<chrono::system_clock> start;
chrono::time_point<chrono::system_clock> end;

start = chrono::system_clock::now();
MergeSort<int>(numbers, 0, MAX_ITEMS-1, temp);
end = chrono::system_clock::now();

chrono::duration<float> elapsed = end - start;
cout << "Execution time in seconds = " << elapsed.count() << "\n";
```

### A thread for every merge (naive — don't do this)

Creating a new thread for every recursive call causes incredible slowdowns and
crashes on large inputs because each thread has significant overhead. At the
lowest recursion level, sorting a single value costs far less than spawning a
thread — the overhead dominates.

```cpp
#include <thread>

template<class ItemType>
void MergeSort(ItemType values[], int first, int last, ItemType tempArray[])
// Post: The elements in values are sorted by key.
{
    if (first < last)
    {
        int middle = (first + last) / 2;
        thread left  (MergeSort<ItemType>, values, first, middle, tempArray);
        thread right (MergeSort<ItemType>, values, middle + 1, last, tempArray);
        left.join();
        right.join();
        Merge<ItemType>(values, first, middle, middle + 1, last, tempArray);
    }
}
```

> On a 1,000-element array, this parallel version ran ~7,700× **slower** than the
> serial version, and crashed beyond ~1,000 threads.

### Chunks — the fix

At a certain array size, threads cost more than they can save. Only spawn new
threads when the segment is larger than a `chunkSize`; otherwise fall back to
serial merge sort. `chunkSize` is passed as a parameter.

```cpp
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>
using namespace std;

const int MAX_ITEMS = 20000000;
int numbers[MAX_ITEMS];
int temp[MAX_ITEMS];
int chunk;
// Merge function would appear here, but is omitted to save space

template<class ItemType>
void SerialMergeSort(ItemType values[], int first,
                     int last, ItemType tempArray[])
// Post: The elements in values are sorted by key.
{
    if (first < last)
    {
        int middle = (first + last) / 2;
        SerialMergeSort<ItemType>(values, first, middle, tempArray);
        SerialMergeSort<ItemType>(values, middle + 1, last, tempArray);
        Merge<ItemType>(values, first, middle, middle + 1, last, tempArray);
    }
}

template<class ItemType>
void ParallelMergeSort(ItemType values[], int first,
                       int last, ItemType tempArray[], int chunkSize)
// Post: The elements in values are sorted by key.
{
    if (first < last)
    {
        int middle = (first + last) / 2;
        if (last-first > chunkSize) // If enough work left, launch more threads
        {
            thread left  (ParallelMergeSort<ItemType>, values, first,
                          middle, tempArray, chunkSize);
            thread right (ParallelMergeSort<ItemType>, values, middle + 1,
                          last, tempArray, chunkSize);
            left.join();
            right.join();
        }
        else                        // Otherwise finish sorting locally
        {
            SerialMergeSort<ItemType>(values, first, middle, tempArray);
            SerialMergeSort<ItemType>(values, middle + 1, last, tempArray);
        }
        Merge<ItemType>(values, first, middle, middle + 1, last, tempArray);
    }
}

int main(int argc, const char * argv[])
{
    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    // Initialize the array with random integers
    for (int index = 0; index < MAX_ITEMS; index++)
        numbers[index] = rand() % 1000000000;

    cout << "Enter chunk size (<= " << MAX_ITEMS << "): ";
    cin >> chunk;
    start = chrono::system_clock::now();                 // Record start time
    ParallelMergeSort<int>(numbers, 0, MAX_ITEMS-1, temp, chunk); // Run sort
    end = chrono::system_clock::now();                   // Record end time
    chrono::duration<float> elapsed = end - start;       // Report time
    cout << "Execution time in seconds = " << elapsed.count() << "\n";
    return 0;
}
```

> The template functions must be **explicitly instantiated** (`<int>`) because
> the `thread` constructor makes it impossible for the compiler to infer the
> template type from the arguments.

### Different chunk sizes (quad-core, ≤ 8 threads), 20M values

| Chunk Size  | Number of Threads | Time (Seconds) |
|-------------|-------------------|----------------|
| 20,000,000  | 1                 | 8.2            |
| 10,000,000  | 2                 | 4.2            |
| 5,000,000   | 4                 | 2.4            |
| 2,500,000   | 8                 | 1.5            |
| 1,250,000   | 16                | 1.5            |
| 625,000     | 32                | 1.5            |
| 312,500     | 64                | 1.5            |
| 100,000     | 200               | 1.5            |
| 25,000      | 800               | 1.6            |

**Parallel gains:** spawning eight threads greatly increased performance, but the
time did **not** drop to 1/8 — because **merging is still serial**.

**Parallel merging** is possible (split the arrays at a value and merge below/above
independently), but like quick sort it can cause very uneven splits, and is very
complex with little gain.

**Avoiding parallel access:** Merge sort works well in parallel because each
divided part is independent — no thread touches a part of the array another
thread is using. Unsynchronized shared access (e.g., naively parallelizing radix
sort's enqueue) can lose data and produce incorrect, unpredictable results.
Coordinating access requires a **mutex** (mutual exclusion).

**Is parallelism worth it?** In this example, parallel merge sort was 5.5× faster
than the serial version (on hardware where 8× is the theoretical max). Larger data
sets and more parallel-capable machines yield even better gains. Parallel code is
complex and has complex bugs — but overall, parallelism is worth it if
implemented correctly.

---

## 13. Summary Comparison Table

| Algorithm       | Best Case  | Average / Worst Case | Extra Space | Stable?           | Notes |
|-----------------|------------|----------------------|-------------|-------------------|-------|
| Selection Sort  | O(N²)      | O(N²)                | O(1)        | Impl. dependent   | Simple; one swap per pass; cache-unfriendly |
| Bubble Sort     | O(N²)      | O(N²)                | O(1)        | Impl. dependent   | Many swaps; cache-friendly (adjacent) |
| ShortBubble     | **O(N)**   | O(N²)                | O(1)        | Impl. dependent   | Stops early if already sorted |
| Insertion Sort  | **O(N)**   | O(N²)                | O(1)        | Impl. dependent   | Good for nearly-sorted data |
| Merge Sort      | O(N log₂N) | O(N log₂N)           | **O(N)**    | Yes (as coded)    | Predictable; needs aux array |
| Quick Sort      | O(N log₂N) | O(N log₂N) / **O(N²)** | O(log₂N)–O(N) | Impl. dependent | Fast in practice; bad on sorted data w/ first-element pivot |
| Heap Sort       | O(N log₂N) | O(N log₂N)           | O(1)        | **No (unstable)** | In place; order-independent; high small-N overhead |
| Radix Sort      | O(N·P)≈O(N)| O(N·P)≈O(N)          | O(N) queues | Yes               | Not comparison-based; needs `SubKey` |

**Key takeaways:**

- No single sort is best for all applications.
- Simple O(N²) sorts can be as good or better for small N and take less
  programmer time.
- The order of the original data matters: `ShortBubble` is O(N) on sorted data,
  while a naive `QuickSort` can degrade to O(N²).
- O(N log₂N) is the theoretical lower bound for comparison-based sorting.
