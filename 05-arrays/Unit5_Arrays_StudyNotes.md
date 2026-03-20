# Unit 5: Arrays in C++ — Comprehensive Study Notes & Mini Lecture

---

## Table of Contents

1. [Key Concepts at a Glance](#1-key-concepts-at-a-glance)
2. [One-Dimensional (1D) Arrays](#2-one-dimensional-1d-arrays)
   - 2.1 [Declaration & Initialization](#21-declaration--initialization)
   - 2.2 [Partial Initialization & Implicit Sizing](#22-partial-initialization--implicit-sizing)
   - 2.3 [No Bounds Checking](#23-no-bounds-checking)
   - 2.4 [Accessing Elements](#24-accessing-elements)
   - 2.5 [Arrays as Function Arguments (Pass by Pointer)](#25-arrays-as-function-arguments-pass-by-pointer)
   - 2.6 [The Range-Based `for` Loop](#26-the-range-based-for-loop)
   - 2.7 [Common Array Operations](#27-common-array-operations)
   - 2.8 [Comparing Arrays](#28-comparing-arrays)
   - 2.9 [Structured Binding Declarations (C++17)](#29-structured-binding-declarations-c17)
   - 2.10 [Parallel Arrays](#210-parallel-arrays)
3. [The `typedef` Statement for Arrays](#3-the-typedef-statement-for-arrays)
4. [Two-Dimensional (2D) Arrays](#4-two-dimensional-2d-arrays)
   - 4.1 [Declaration & Initialization](#41-declaration--initialization)
   - 4.2 [Processing with Nested Loops](#42-processing-with-nested-loops)
   - 4.3 [Passing 2D Arrays to Functions](#43-passing-2d-arrays-to-functions)
   - 4.4 [Finding Highest/Lowest in a 2D Array](#44-finding-highestlowest-in-a-2d-array)
5. [Vectors as an Alternative](#5-vectors-as-an-alternative)
6. [Reading Array Data from Files](#6-reading-array-data-from-files)
7. [Complete Code Templates](#7-complete-code-templates)
   - Template A: 1D Array with Functions
   - Template B: 2D Array with `typedef` and Functions
   - Template C: File Input into Array
   - Template D: Letter Grade Counter (char array)
   - Template E: Student Grades with Average & Letter Grade
   - Template F: Quarterly Sales (2D Array Table)
8. [Critical Facts for the Test](#8-critical-facts-for-the-test)
9. [Common Pitfalls & Mistakes](#9-common-pitfalls--mistakes)

---

## 1. Key Concepts at a Glance

| Concept | Summary |
|---|---|
| **Array** | A collection of memory locations, all with the same data type, accessed by name + subscript |
| **Subscript** | Index starting at **0**; last valid index is `size - 1` |
| **Size** | Memory = `number_of_elements × size_of_each_element` |
| **No bounds checking** | C++ does NOT verify subscripts are in range — you must be careful |
| **Pass by pointer** | Arrays are always passed by pointer to functions (similar to pass by reference, but no `&`) |
| **`typedef`** | Creates a named array type to avoid brackets in prototypes/headings |
| **2D array** | Like a table — uses two subscripts: `array[row][col]` |
| **`const` keyword** | Use in function parameters to prevent modification of the array |
| **Range-based `for`** | `for (auto &val : array)` — iterates every element automatically |
| **Parallel arrays** | Two or more arrays where elements at the same index are related |
| **Structured binding** | C++17: `auto [a, b, c] = array;` unpacks array into individual variables |

---

## 2. One-Dimensional (1D) Arrays

### 2.1 Declaration & Initialization

An array is a collection of memory locations that share the same data type. Each element is accessed by its **subscript** (index).

```cpp
// General syntax
dataType arrayName[SIZE];

// Declaration with initialization list
const int SIZE = 5;
int tests[SIZE] = {90, 120, 20, 300, 91};
```

**Memory layout of `tests`:**

| Index | 0 | 1 | 2 | 3 | 4 |
|---|---|---|---|---|---|
| Value | 90 | 120 | 20 | 300 | 91 |

### 2.2 Partial Initialization & Implicit Sizing

**Partial initialization** — remaining elements are automatically set to **0**:

```cpp
int numbers[7] = {1, 2, 4, 8};
// Result: {1, 2, 4, 8, 0, 0, 0}
```

**Implicit sizing** — compiler determines size from the initialization list:

```cpp
int quizzes[] = {12, 14, 23, 10};
// Compiler sets size to 4
```

### 2.3 No Bounds Checking

C++ does **NOT** check if a subscript is valid. Using an out-of-bounds subscript can:

- Corrupt other memory locations
- Crash the program
- Lock up the computer
- Cause hard-to-find bugs

```cpp
int arr[5];
arr[10] = 99;  // DANGEROUS! No compiler error, but undefined behavior
```

### 2.4 Accessing Elements

```cpp
int tests[5] = {90, 120, 20, 300, 91};

tests[0];   // First element: 90
tests[4];   // Last element: 91
tests[2]++; // Adds 1 to the element at index 2 (20 → 21)
tests[i++]; // Accesses tests[i], THEN increments i (does NOT change tests)
```

> **Watch out:** `tests[i]++` adds 1 to the **element**. `tests[i++]` increments the **subscript** — very different!

### 2.5 Arrays as Function Arguments (Pass by Pointer)

Arrays are **always** passed by pointer (similar to pass by reference). This means:

- The function receives the **address** of the array, not a copy
- The function **can modify** the original array
- There is **no `&` symbol** in the parameter (unlike regular pass-by-reference)
- Use `const` to **prevent** the function from modifying the array

```cpp
// Function prototypes
void getData(int array[], int &sizeOfArray);               // can modify array
float findAverage(const int array[], int sizeOfArray);     // cannot modify array (const)
```

**Important:** When passing an array, you typically also pass the number of elements being used, since the function has no way to know the array's size.

**Full example:**

```cpp
const int TOTALGRADES = 50;

void getData(int array[], int &sizeOfArray) {
    int pos = 0;
    int grade;
    cout << "Input a grade or -99 to stop: ";
    cin >> grade;
    while (grade != -99) {
        array[pos] = grade;
        pos++;
        cout << "Input a grade or -99 to stop: ";
        cin >> grade;
    }
    sizeOfArray = pos;  // pos now holds the count of grades entered
}

float findAverage(const int array[], int sizeOfArray) {
    int sum = 0;
    for (int pos = 0; pos < sizeOfArray; pos++) {
        sum += array[pos];
    }
    return float(sum) / sizeOfArray;
}

int main() {
    int grades[TOTALGRADES];
    int numberOfGrades = 0;
    getData(grades, numberOfGrades);
    float avg = findAverage(grades, numberOfGrades);
    cout << "Average: " << avg << endl;
    return 0;
}
```

### 2.6 The Range-Based `for` Loop

Introduced to simplify iterating over **every** element in an array. You do **not** need a counter variable, and you **cannot** go out of bounds.

```cpp
// Syntax
for (dataType rangeVariable : array)
    statement;
```

**Example:**

```cpp
int testsNums[] = {10, 20, 45, 29};

for (const auto &val : testsNums) {
    cout << val << endl;
}
```

| Keyword | Purpose |
|---|---|
| `auto` | Automatically deduces the data type |
| `&` | Makes `val` a reference (avoids copying each element) |
| `const` | Prevents modification of the element |

### 2.7 Common Array Operations

#### Summing & Averaging

```cpp
int testsNums[] = {10, 20, 45, 29};
double sum = 0;

for (int i = 0; i < 4; i++) {
    sum += testsNums[i];
}
double average = sum / 4;  // average = 26.0
```

#### Finding Highest & Lowest

**Key technique:** Start by assuming the first element is both the highest and lowest, then compare the rest.

```cpp
int highest = testsNums[0];
int lowest  = testsNums[0];

for (int i = 1; i < 4; i++) {       // start at index 1
    if (testsNums[i] > highest)
        highest = testsNums[i];
    else if (testsNums[i] < lowest)
        lowest = testsNums[i];
}
// highest = 45, lowest = 10
```

**As reusable functions:**

```cpp
int findHighest(const int array[], int size) {
    int highest = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > highest)
            highest = array[i];
    }
    return highest;
}

int findLowest(const int array[], int size) {
    int lowest = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] < lowest)
            lowest = array[i];
    }
    return lowest;
}
```

### 2.8 Comparing Arrays

You **cannot** compare arrays directly with `==`. You must compare **element by element**:

```cpp
const int SIZE = 5;
int firstArray[SIZE]  = {5, 10, 15, 20, 25};
int secondArray[SIZE] = {5, 10, 15, 20, 25};
bool arraysEqual = true;
int count = 0;

while (arraysEqual && count < SIZE) {
    if (firstArray[count] != secondArray[count])
        arraysEqual = false;
    count++;
}

if (arraysEqual)
    cout << "The arrays are equal." << endl;
else
    cout << "The arrays are not equal." << endl;
```

### 2.9 Structured Binding Declarations (C++17)

Unpacks an array into individual named variables in one line:

```cpp
int testScores[] = {80, 90, 100};
auto [score1, score2, score3] = testScores;
// score1 = 80, score2 = 90, score3 = 100
```

**Limitation:** Cannot be used inside a function that received the array as a parameter (the compiler wouldn't know the size).

### 2.10 Parallel Arrays

Two or more arrays where elements at the **same subscript** are related. The arrays may be of **different types**.

```cpp
const int NUM_EMPLOYEES = 5;
int hours[NUM_EMPLOYEES];
double payRate[NUM_EMPLOYEES];

for (int i = 0; i < NUM_EMPLOYEES; i++) {
    cout << "Hours for employee #" << (i + 1) << ": ";
    cin >> hours[i];
    cout << "Pay rate for employee #" << (i + 1) << ": ";
    cin >> payRate[i];
}

for (int i = 0; i < NUM_EMPLOYEES; i++) {
    double grossPay = hours[i] * payRate[i];
    cout << "Employee #" << (i + 1) << ": $" << grossPay << endl;
}
```

Here, `hours[2]` and `payRate[2]` both refer to employee #3.

---

## 3. The `typedef` Statement for Arrays

`typedef` creates a **named data type** for an array. This eliminates brackets in function prototypes and headings — especially useful for multi-dimensional arrays.

```cpp
const int TOTALGRADES = 50;
typedef int GradeType[TOTALGRADES];  // GradeType is now a data type
```

**Without `typedef`:**

```cpp
void getData(int array[], int &sizeOfArray);
float findAverage(const int array[], int sizeOfArray);
```

**With `typedef`:**

```cpp
void getData(GradeType array, int &sizeOfArray);
float findAverage(const GradeType array, int sizeOfArray);
```

Both are functionally identical, but `typedef` makes the code cleaner. Convention: start type names with an **uppercase letter** (e.g., `GradeType`, `PriceType`).

**For character arrays (strings):**

```cpp
const int MAXCHAR = 30;
typedef char StringType30[MAXCHAR + 1];  // +1 for null terminator
StringType30 firstname, lastname;
```

---

## 4. Two-Dimensional (2D) Arrays

### 4.1 Declaration & Initialization

A 2D array is like a **table** with rows and columns.

```cpp
// General syntax
dataType arrayName[ROWS][COLS];

// Example
const int ROWS = 2, COLS = 2;
int exams[ROWS][COLS] = {
    {84, 78},
    {92, 97}
};
```

**Memory layout of `exams`:**

|  | Col 0 | Col 1 |
|---|---|---|
| **Row 0** | 84 | 78 |
| **Row 1** | 92 | 97 |

**With `typedef`:**

```cpp
const int NO_OF_ROWS = 3;
const int NO_OF_COLS = 4;
typedef float ProfitType[NO_OF_ROWS][NO_OF_COLS];

ProfitType profit;  // same as: float profit[3][4];
```

### 4.2 Processing with Nested Loops

An **n-dimensional** array requires **n nested loops** to access all elements.

**Reading input into a 2D array:**

```cpp
for (int row = 0; row < NO_OF_ROWS; row++) {
    for (int col = 0; col < NO_OF_COLS; col++) {
        cout << "Enter value: ";
        cin >> profit[row][col];
    }
}
```

**Printing a 2D array as a table:**

```cpp
for (int row = 0; row < NO_OF_ROWS; row++) {
    for (int col = 0; col < NO_OF_COLS; col++) {
        cout << setw(8) << profit[row][col] << " ";
    }
    cout << endl;  // new line after each row
}
```

### 4.3 Passing 2D Arrays to Functions

**Critical rule:** When passing a 2D array to a function, the **number of columns MUST be specified** in the parameter. The number of rows can be left unspecified and passed separately.

**Why?** The array decays into a pointer. The compiler needs the column count to calculate memory offsets for row navigation.

**Without `typedef`:**

```cpp
void showArray(float array[][NO_OF_COLS], int rows) {
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < NO_OF_COLS; y++) {
            cout << setw(4) << array[x][y] << " ";
        }
        cout << endl;
    }
}
```

**With `typedef`:**

```cpp
typedef float PriceType[MAXROWS][MAXCOLS];

void getPrices(PriceType table, int &numOfRows, int &numOfCols);
void printPrices(PriceType table, int numOfRows, int numOfCols);
```

> **Note:** `getPrices` takes rows/cols by **reference** (`&`) because it sets them. `printPrices` takes them by **value** because it only reads them.

### 4.4 Finding Highest/Lowest in a 2D Array

Same logic as 1D, but with **nested loops**:

```cpp
float findHighestPrice(PriceType table, int numOfRows, int numOfCols) {
    float highest = table[0][0];
    for (int row = 0; row < numOfRows; row++)
        for (int col = 0; col < numOfCols; col++)
            if (table[row][col] > highest)
                highest = table[row][col];
    return highest;
}

float findLowestPrice(PriceType table, int numOfRows, int numOfCols) {
    float lowest = table[0][0];
    for (int row = 0; row < numOfRows; row++)
        for (int col = 0; col < numOfCols; col++)
            if (table[row][col] < lowest)
                lowest = table[row][col];
    return lowest;
}
```

---

## 5. Vectors as an Alternative

`std::vector` is a dynamic array from the C++ Standard Library. Unlike raw arrays, vectors can **resize automatically**.

```cpp
#include <vector>

int rows = 3, cols = 4;
vector<vector<float>> profit(rows, vector<float>(cols));

// Input
for (int x = 0; x < rows; x++)
    for (int y = 0; y < cols; y++)
        cin >> profit[x][y];

// Output
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
        cout << setw(4) << profit[i][j] << " ";
    cout << endl;
}
```

| Feature | Raw Array | Vector |
|---|---|---|
| Size | Fixed at compile time | Dynamic (can grow/shrink) |
| Bounds checking | None | `.at()` method checks bounds |
| Memory | Stack | Heap |
| Passing to functions | Decays to pointer | Passed by value or reference |

---

## 6. Reading Array Data from Files

Instead of keyboard input, you can read data from a file using `ifstream`:

```cpp
#include <fstream>

ifstream dataFile;
dataFile.open("gradfile.txt");

int grades[100];
int pos = 0;
int grade;

while (dataFile >> grade) {
    grades[pos] = grade;
    pos++;
}
dataFile.close();

int numberOfGrades = pos;  // pos now holds how many values were read
```

**Example `gradfile.txt`:**

```
90
45
73
21
62
```

This technique replaces the sentinel-value loop (`-99` to stop) with automatic end-of-file detection.

---

## 7. Complete Code Templates

### Template A: 1D Array with Functions (Grades — Keyboard Input)

```cpp
#include <iostream>
using namespace std;

const int MAXSIZE = 50;
typedef int GradeType[MAXSIZE];

void getData(GradeType array, int &sizeOfArray);
float findAverage(const GradeType array, int sizeOfArray);
int findHighest(const GradeType array, int size);
int findLowest(const GradeType array, int size);

int main() {
    GradeType grades;
    int numberOfGrades = 0;

    getData(grades, numberOfGrades);

    cout << "Average: " << findAverage(grades, numberOfGrades) << endl;
    cout << "Highest: " << findHighest(grades, numberOfGrades) << endl;
    cout << "Lowest:  " << findLowest(grades, numberOfGrades) << endl;

    return 0;
}

void getData(GradeType array, int &sizeOfArray) {
    int pos = 0, grade;
    cout << "Enter grade (-99 to stop): ";
    cin >> grade;
    while (grade != -99) {
        array[pos] = grade;
        pos++;
        cout << "Enter grade (-99 to stop): ";
        cin >> grade;
    }
    sizeOfArray = pos;
}

float findAverage(const GradeType array, int sizeOfArray) {
    int sum = 0;
    for (int i = 0; i < sizeOfArray; i++)
        sum += array[i];
    return float(sum) / sizeOfArray;
}

int findHighest(const GradeType array, int size) {
    int highest = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > highest)
            highest = array[i];
    return highest;
}

int findLowest(const GradeType array, int size) {
    int lowest = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] < lowest)
            lowest = array[i];
    return lowest;
}
```

---

### Template B: 2D Array with `typedef` and Functions (Prices Table)

```cpp
#include <iomanip>
#include <iostream>
using namespace std;

const int MAXROWS = 10;
const int MAXCOLS = 10;
typedef float PriceType[MAXROWS][MAXCOLS];

void getPrices(PriceType table, int &numOfRows, int &numOfCols);
void printPrices(PriceType table, int numOfRows, int numOfCols);
float findHighest(PriceType table, int numOfRows, int numOfCols);
float findLowest(PriceType table, int numOfRows, int numOfCols);

int main() {
    int rowsUsed, colsUsed;
    PriceType priceTable;

    getPrices(priceTable, rowsUsed, colsUsed);
    printPrices(priceTable, rowsUsed, colsUsed);
    cout << "Highest: " << findHighest(priceTable, rowsUsed, colsUsed) << endl;
    cout << "Lowest:  " << findLowest(priceTable, rowsUsed, colsUsed) << endl;

    return 0;
}

void getPrices(PriceType table, int &numOfRows, int &numOfCols) {
    cout << "Number of rows (1-" << MAXROWS << "): ";
    cin >> numOfRows;
    cout << "Number of cols (1-" << MAXCOLS << "): ";
    cin >> numOfCols;

    for (int row = 0; row < numOfRows; row++)
        for (int col = 0; col < numOfCols; col++) {
            cout << "Enter price: ";
            cin >> table[row][col];
        }
}

void printPrices(PriceType table, int numOfRows, int numOfCols) {
    cout << fixed << showpoint << setprecision(2);
    for (int row = 0; row < numOfRows; row++) {
        for (int col = 0; col < numOfCols; col++)
            cout << setw(10) << table[row][col];
        cout << endl;
    }
}

float findHighest(PriceType table, int numOfRows, int numOfCols) {
    float highest = table[0][0];
    for (int row = 0; row < numOfRows; row++)
        for (int col = 0; col < numOfCols; col++)
            if (table[row][col] > highest)
                highest = table[row][col];
    return highest;
}

float findLowest(PriceType table, int numOfRows, int numOfCols) {
    float lowest = table[0][0];
    for (int row = 0; row < numOfRows; row++)
        for (int col = 0; col < numOfCols; col++)
            if (table[row][col] < lowest)
                lowest = table[row][col];
    return lowest;
}
```

---

### Template C: File Input into Array

```cpp
#include <fstream>
#include <iostream>
using namespace std;

typedef int GradeType[100];

float findAverage(const GradeType array, int size);
int findHighest(const GradeType array, int size);
int findLowest(const GradeType array, int size);

int main() {
    ifstream dataFile;
    dataFile.open("gradfile.txt");

    GradeType grades;
    int pos = 0, grade;

    while (dataFile >> grade) {
        grades[pos] = grade;
        pos++;
    }
    dataFile.close();

    int numberOfGrades = pos;

    cout << "Average: " << findAverage(grades, numberOfGrades) << endl;
    cout << "Highest: " << findHighest(grades, numberOfGrades) << endl;
    cout << "Lowest:  " << findLowest(grades, numberOfGrades) << endl;

    return 0;
}

float findAverage(const GradeType array, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++)
        sum += array[i];
    return sum / size;
}

int findHighest(const GradeType array, int size) {
    int highest = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] > highest) highest = array[i];
    return highest;
}

int findLowest(const GradeType array, int size) {
    int lowest = array[0];
    for (int i = 1; i < size; i++)
        if (array[i] < lowest) lowest = array[i];
    return lowest;
}
```

---

### Template D: Letter Grade Counter (char Array with `typedef`)

```cpp
#include <iostream>
using namespace std;

const int MAXGRADES = 50;
typedef char GradeType[MAXGRADES];

int getCount(const GradeType &array, char letter);

int main() {
    int numGrades;
    GradeType letterArr;

    cout << "How many grades? (1-50): ";
    cin >> numGrades;

    cout << "Enter uppercase grades (A B C D F):" << endl;
    for (int i = 0; i < numGrades; i++) {
        cout << "Grade: ";
        cin >> letterArr[i];
    }

    cout << "\nNumber of A = " << getCount(letterArr, 'A') << endl;
    cout << "Number of B = " << getCount(letterArr, 'B') << endl;
    cout << "Number of C = " << getCount(letterArr, 'C') << endl;
    cout << "Number of D = " << getCount(letterArr, 'D') << endl;
    cout << "Number of F = " << getCount(letterArr, 'F') << endl;

    return 0;
}

int getCount(const GradeType &array, char letter) {
    int count = 0;
    for (const auto &var : array) {
        if (var == letter)
            count++;
    }
    return count;
}
```

---

### Template E: Student Grades — Average & Letter Grade

```cpp
#include <iomanip>
#include <iostream>
using namespace std;

const int MAXGRADE = 25;
const int MAXCHAR = 30;

typedef char StringType30[MAXCHAR + 1];
typedef float GradeType[MAXGRADE];

float findGradeAvg(GradeType array, int numGrades);
char findLetterGrade(float numGrade);

int main() {
    StringType30 firstname, lastname;
    int numOfGrades;
    GradeType grades;
    char moreInput;

    cout << setprecision(2) << fixed << showpoint;

    cout << "Number of grades per student (1-" << MAXGRADE << "): ";
    cin >> numOfGrades;

    while (numOfGrades > MAXGRADE || numOfGrades < 1) {
        cout << "Invalid. Enter 1-" << MAXGRADE << ": ";
        cin >> numOfGrades;
    }

    cout << "More students? (y/n): ";
    cin >> moreInput;

    while (moreInput == 'y' || moreInput == 'Y') {
        cout << "First name: ";
        cin >> firstname;
        cout << "Last name: ";
        cin >> lastname;

        for (int i = 0; i < numOfGrades; i++) {
            cout << "Grade " << (i + 1) << ": ";
            cin >> grades[i];
        }

        float average = findGradeAvg(grades, numOfGrades);
        cout << firstname << " " << lastname
             << " average: " << average
             << " grade: " << findLetterGrade(average) << endl;

        cout << "More students? (y/n): ";
        cin >> moreInput;
    }
    return 0;
}

float findGradeAvg(GradeType array, int numGrades) {
    float sum = 0;
    for (int i = 0; i < numGrades; i++)
        sum += array[i];
    return sum / numGrades;
}

char findLetterGrade(float numGrade) {
    if (numGrade >= 90) return 'A';
    else if (numGrade >= 80) return 'B';
    else if (numGrade >= 70) return 'C';
    else if (numGrade >= 60) return 'D';
    else return 'F';
}
```

---

### Template F: Quarterly Sales (2D Array with Formatted Table)

```cpp
#include <iomanip>
#include <iostream>
using namespace std;

const int MAXYEAR = 10;
const int MAXCOL = 5;
typedef int SalesType[MAXYEAR][MAXCOL];

void getSales(SalesType table, int &numOfYears);
void printTableHeading();
void printSales(SalesType table, int numOfYears);

int main() {
    int yearsUsed;
    SalesType sales;

    getSales(sales, yearsUsed);
    printTableHeading();
    printSales(sales, yearsUsed);

    return 0;
}

void printTableHeading() {
    cout << setw(30) << "YEARLY QUARTERLY SALES" << endl << endl;
    cout << setw(10) << "YEAR"
         << setw(10) << "Q1"
         << setw(10) << "Q2"
         << setw(10) << "Q3"
         << setw(10) << "Q4" << endl;
}

void getSales(SalesType table, int &numOfYears) {
    cout << "Number of years (1-" << MAXYEAR << "): ";
    cin >> numOfYears;

    for (int i = 0; i < numOfYears; i++) {
        cout << "Enter year: ";
        cin >> table[i][0];
        for (int j = 1; j < MAXCOL; j++) {
            cout << "Sales for quarter " << j << ": ";
            cin >> table[i][j];
        }
    }
}

void printSales(SalesType table, int numOfYears) {
    for (int i = 0; i < numOfYears; i++) {
        for (int j = 0; j < MAXCOL; j++)
            cout << setw(10) << table[i][j];
        cout << endl;
    }
}
```

---

## 8. Critical Facts for the Test

These are the key takeaways from the pre-lab writing and course material:

1. The **first subscript** of every array in C++ is **0** and the last is **one less** than the total number of locations.
2. The amount of **memory allocated** to an array is based on the **type of data** and the **number of locations** (size).
3. Array initialization and processing is usually done inside a **loop**.
4. The **`typedef`** statement declares an array type and is often used for multidimensional arrays so that brackets don't have to appear in function prototypes.
5. Multi-dimensional arrays are usually processed within **nested `for` loops**.
6. Arrays used as arguments are **always passed by pointer**.
7. When passing an array to a function, it is often necessary to also pass a parameter holding the **actual number of elements used**.
8. A **string is an array of characters**.
9. Upon exiting a loop that reads values into an array, the **counter variable** will contain the size of that array.
10. An **n-dimensional array** requires **n nested loops** to access all members.

---

## 9. Common Pitfalls & Mistakes

| Mistake | Why It's Wrong | Fix |
|---|---|---|
| `if (array1 == array2)` | Cannot compare arrays directly | Compare element by element in a loop |
| Forgetting `const` on read-only array params | Function could accidentally modify data | Add `const` keyword: `const GradeType array` |
| Not initializing `sum = 0` before accumulating | Sum starts with garbage value | Always initialize: `float sum = 0;` |
| Using `&` with array parameters | Arrays already pass by pointer | Remove `&` — it's not needed for array params |
| Off-by-one error in loops | Accessing `array[size]` is out of bounds | Loop condition: `i < size`, not `i <= size` |
| Forgetting column size in 2D function params | Compiler can't calculate row offsets | Always specify: `void func(int arr[][COLS], int rows)` |
| Using `&` (bitwise AND) instead of `&&` (logical AND) | `&` performs bit operations, not boolean logic | Use `&&` for conditions: `if (x >= 90 && x <= 100)` |
| Forgetting to close file after reading | Resource leak | Always call `dataFile.close()` |
| Not passing array size to functions | Function has no way to know how many elements exist | Always pass size as a separate parameter |

---

## Quick Reference Card

```
┌─────────────────────────────────────────────────────────┐
│                  C++ ARRAYS CHEAT SHEET                 │
├─────────────────────────────────────────────────────────┤
│ DECLARE:    int arr[SIZE];                              │
│ INIT:       int arr[5] = {1,2,3,4,5};                   │
│ IMPLICIT:   int arr[] = {1,2,3};                        │
│ PARTIAL:    int arr[5] = {1,2};  // rest are 0          │
│ ACCESS:     arr[0], arr[1], ... arr[SIZE-1]             │
│                                                         │
│ TYPEDEF:    typedef int GradeType[50];                  │
│             GradeType grades;                           │
│                                                         │
│ 2D DECLARE: int table[ROWS][COLS];                      │
│ 2D TYPEDEF: typedef float PriceType[ROWS][COLS];        │
│ 2D ACCESS:  table[row][col]                             │
│                                                         │
│ RANGE FOR:  for (const auto &val : arr) { ... }         │
│ BINDING:    auto [a, b, c] = arr;  // C++17             │
│                                                         │
│ FUNC PROTO: void f(int arr[], int size);       // 1D    │
│             void f(int arr[][COLS], int rows); // 2D    │
│             void f(const GradeType arr, int n);// const │
│                                                         │
│ FILE READ:  ifstream f; f.open("file.txt");             │
│             while (f >> val) { arr[i++] = val; }        │
│             f.close();                                  │
└─────────────────────────────────────────────────────────┘
```

---

*Notes compiled from: `01-1d-arrays-basic-notes.cpp`, `02-typedef-notes.cpp`, `03-2d-arrays-notes.cpp`, `04-vector-basic-notes.cpp`, `auto_graded_assignment_1.cpp`, and all files in `Unit5_Assignment_Dan/` (student.cpp, testscore.cpp, price.cpp, quartsal.cpp, student_generated_code.cpp, pre-lab-writing.txt).*
