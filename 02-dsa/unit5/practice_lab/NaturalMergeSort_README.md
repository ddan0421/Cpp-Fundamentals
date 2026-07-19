# Natural Merge Sort — Practice Lab

A zyBooks lab implementing **natural merge sort**. The test harness and the
`Merge()` helper are provided; the task is to implement two member functions in
`NaturalMergeSorter.h`.

---

## What is natural merge sort?

Standard merge sort blindly splits the array in half down to single elements,
then merges back up. **Natural merge sort** instead exploits order that is
already present: it scans for **already-sorted runs** and merges adjacent runs
together, repeating until the whole array becomes a single sorted run. When the
data is already partly sorted, there is less work to do.

### Example

Unsorted array (11 integers):

```
[17, 58, 96, 24, 88, 70, 23, 64, 74, 81, 55]
```

The array contains five sorted runs:

| Run | Elements          |
|-----|-------------------|
| A   | 17, 58, 96        |
| B   | 24, 88            |
| C   | 70                |
| D   | 23, 64, 74, 81    |
| E   | 55                |

The algorithm merges adjacent run pairs, restarting from index 0 whenever only a
single trailing run remains:

```
Start:      [17, 58, 96 | 24, 88 | 70 | 23, 64, 74, 81 | 55]   runs A B C D E
Merge A+B:  [17, 24, 58, 88, 96 | 70 | 23, 64, 74, 81 | 55]    run F, then C D E
Merge C+D:  [17, 24, 58, 88, 96 | 23, 64, 70, 74, 81 | 55]     run F G, then E
Merge F+G:  [17, 23, 24, 58, 64, 70, 74, 81, 88, 96 | 55]      run H, then E
Merge H+E:  [17, 23, 24, 55, 58, 64, 70, 74, 81, 88, 96]       sorted
```

A final scan finds one run equal to the array length, so the algorithm
terminates.

---

## Project files

| File                    | Role |
|-------------------------|------|
| `NaturalMergeSorter.h`  | The class being implemented. Contains the provided `Merge()` plus the two functions to complete. |
| `RunLengthTestCase.h`   | A test-case class that calls `GetSortedRunLength()` and reports PASS/FAIL against an expected value. |
| `main.cpp`              | Driver: defines test vectors `v1`–`v8`, runs the run-length tests, then runs `NaturalMergeSort()` on each and verifies the result with `IsArraySorted()`. |

The provided `Merge(numbers, leftFirst, leftLast, rightLast)` merges two adjacent
sorted partitions `[leftFirst..leftLast]` and `[leftLast+1..rightLast]` using a
temporary buffer.

---

## Functions added

Both functions were added to `NaturalMergeSorter.h`.

### 1. `GetSortedRunLength(int* array, int arrayLength, int startIndex)`

Returns the number of elements, starting at `startIndex`, that are in ascending
order — stopping at the end of the run or the end of the array, whichever comes
first. Returns `0` if `startIndex` is out of bounds.

```cpp
int GetSortedRunLength(int* array, int arrayLength, int startIndex) {
   // Out-of-bounds starting index has no run
   if (startIndex < 0 || startIndex >= arrayLength) {
      return 0;
   }

   // Extend the run while each element is >= its predecessor
   int runLength = 1;
   for (int i = startIndex + 1; i < arrayLength; i++) {
      if (array[i] < array[i - 1]) {
         break;
      }
      runLength++;
   }
   return runLength;
}
```

**Key details:**

- A run ends only when the next element is **strictly smaller** (`array[i] <
  array[i-1]`), so **equal** adjacent values stay in the same run (e.g. eight
  equal values form one run of 8).
- Strictly-descending data therefore yields runs of length 1.
- An out-of-bounds `startIndex` (negative or `>= arrayLength`) returns `0`.

### 2. `NaturalMergeSort(int* array, int arrayLength)`

Repeatedly finds two adjacent sorted runs and merges them until the array is one
sorted run.

```cpp
void NaturalMergeSort(int* array, int arrayLength) {
   int i = 0;
   while (true) {
      // Length of the first sorted run, starting at i
      int firstRunLength = GetSortedRunLength(array, arrayLength, i);

      // Entire array is one sorted run: done
      if (firstRunLength == arrayLength) {
         return;
      }

      // First run reaches the array's end: restart from the beginning
      if (i + firstRunLength >= arrayLength) {
         i = 0;
         continue;
      }

      // Length of the second sorted run, immediately after the first
      int secondRunStart = i + firstRunLength;
      int secondRunLength =
         GetSortedRunLength(array, arrayLength, secondRunStart);

      // Merge the two adjacent runs
      int leftFirst = i;
      int leftLast = secondRunStart - 1;
      int rightLast = secondRunStart + secondRunLength - 1;
      Merge(array, leftFirst, leftLast, rightLast);

      // Continue after the second run, or restart if it hit the array's end
      if (rightLast >= arrayLength - 1) {
         i = 0;
      }
      else {
         i = rightLast + 1;
      }
   }
}
```

**Algorithm (as specified by the lab):**

1. Start at `i = 0`.
2. Get the length of the first sorted run starting at `i`.
3. If the first run's length equals the array length → **return** (sorted).
4. If the first run ends at the array's end → set `i = 0` and repeat step 2.
5. Get the length of the second run, starting immediately after the first.
6. Merge the two runs with the provided `Merge()`.
7. Set `i` to the first index after the second run, or `0` if the second run
   ends at the array's end.
8. Go to step 2.

---

## Building and running

```bash
g++ -std=c++17 -Wall -o test_nms main.cpp
./test_nms
```

### Test results

All tests pass:

```
GetSortedRunLength() tests summary:
   Passed: 23
   Failed: 0
NaturalMergeSort() tests summary:
   Passed: 8
   Failed: 0
```

The eight sort test vectors cover the important cases: already-sorted, a
two-run array, strictly-descending (runs of length 1 — the worst case),
all-equal elements, a single element, and multi-run arrays.
