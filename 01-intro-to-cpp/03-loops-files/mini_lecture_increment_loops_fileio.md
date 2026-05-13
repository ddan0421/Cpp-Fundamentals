# C++ Mini Lecture: Loops, Increment/Decrement, and File I/O

---

## 1. Incremental & Decremental Operators

C++ provides `++` and `--` to change the value of a variable by 1.

### Types

| Operator | Type | Meaning |
|----------|------|---------|
| `++x`    | Pre-increment | Increment first, then use value |
| `x++`    | Post-increment | Use value first, then increment |
| `--x`    | Pre-decrement | Decrement first, then use value |
| `x--`    | Post-decrement | Use value first, then decrement |

### Examples

```cpp
int number = 6;
cout << number++ << endl;  // post-increment: prints 6, number becomes 7
cout << ++number << endl;  // pre-increment: number becomes 8, prints 8
cout << number-- << endl;  // post-decrement: prints 8, number becomes 7
cout << --number << endl;  // pre-decrement: number becomes 6, prints 6
```

**Key point:**
- Pre (`++x` / `--x`) → change first, then use
- Post (`x++` / `x--`) → use first, then change

### Usage in assignments

```cpp
int x = 0;
int y = x++;   // y = 0, x = 1
int z = ++x;   // x = 2, z = 2
```

---

## 2. Loops

Loops repeat a block of code until a condition is false.

### 2.1 `while` loop

- Concept: checks condition before executing
- Syntax:

```cpp
while (condition)
{
    // statements
}
```

- Example:

```cpp
int x = 0;
while (x < 5)
{
    cout << x << " ";
    x++;
}
// Output: 0 1 2 3 4
```

### 2.2 `do-while` loop

- Concept: executes at least once, condition checked after body
- Syntax:

```cpp
do
{
    // statements
} while (condition);
```

- Example:

```cpp
int n = 10;
do
{
    cout << n << " ";
    n++;
} while (n < 5);
// Output: 10
```

### 2.3 `for` loop

- Concept: best when number of iterations is known
- Syntax:

```cpp
for (initialization; condition; update)
{
    // statements
}
```

- Examples:

```cpp
int x = 0;
for (int count = 0; count < 3; count++)
    x += count;
cout << x << endl; // Output: 3

for (int i = 0; i <= 10; i += 2)
    cout << i << " "; // Output: 0 2 4 6 8 10
```

- Update can contain multiple expressions:

```cpp
int i = 0, total = 0;
for (; i < 5; i++, total += 2) {}
```

### 2.4 Break & Continue

- `break` → exits loop immediately
- `continue` → skips rest of iteration, continues to next

```cpp
for (int i = 1; i <= 5; i++)
{
    if (i == 3) continue; // skip 3
    cout << i << " ";     // Output: 1 2 4 5
}
```

---

## 3. File Input/Output

C++ uses fstream library: `ifstream` for input, `ofstream` for output.

```cpp
#include <fstream>
```

### 3.1 Reading from a file (`ifstream`)

- Syntax:

```cpp
ifstream inFile("data.txt");
if (!inFile)
{
    cout << "Error opening file" << endl;
    return 1;
}
```

- Reading numbers:

```cpp
int n;
inFile >> n; // reads one number
```

- Looping through file (example: 360 daily temperatures):

```cpp
float temp, total = 0;
for (int day = 1; day <= 360; day++)
{
    inFile >> temp;
    total += temp;
}
float avg = total / 360;
```

### 3.2 Writing to a file (`ofstream`)

- Syntax:

```cpp
ofstream outFile("results.txt");
outFile << "Average temperature: " << avg << endl;
```

- Formatting output:

```cpp
#include <iomanip>
outFile << fixed << setprecision(3) << showpoint;
outFile << avg << endl;
```

### 3.3 Full Example: Read temps and find average

```cpp
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    ifstream dataFile("WeatherData.txt");
    if (!dataFile) return 1;

    float temp, total = 0;
    for (int day = 1; day <= 360; day++)
    {
        dataFile >> temp;
        total += temp;
    }
    float avg = total / 360;
    cout << fixed << setprecision(3) << showpoint;
    cout << "Average temperature: " << avg << endl;
}
```

---

## 4. Key Tips from Quizzes

- **Increment/decrement:** pre vs post matters inside expressions, otherwise result same.
- **Loops:** braces `{}` determine the loop body — missing braces often cause errors.
- **`while` loop:** can increment counter any way, not just by 1.
- **`for` loop update:** can include multiple expressions, separated by commas.
- **File streams:** can open at declaration or using `.open()`.

---

## 5. Summary Table

| Concept | Syntax / Example | Notes |
|---------|----------------|------|
| `x++` / `++x` | `x++` post, `++x` pre | Pre vs post matters in expressions |
| `while` | `while (condition) { statements }` | condition checked before loop |
| `do-while` | `do { statements } while (condition);` | executes at least once |
| `for` | `for(init; condition; update){}` | update can be multiple expressions |
| `break` | exits loop | |
| `continue` | skip iteration | |
| `ifstream` | `ifstream file("file.txt"); file >> var;` | read file line by line |
| `ofstream` | `ofstream file("out.txt"); file << var;` | write to file |
| Formatting | `fixed << setprecision(3) << showpoint` | applies to `cout` & `ofstream` |

