# Appointment Scheduler — Project Summary

**Appointment Scheduling System** — Manages scheduled appointments,
prevents conflicts, and stores appointment data persistently in a file.

---

## 1. Program Overview

The project is split into three translation units plus a data file:

```
appointment-scheduler/
├── Appointment.h      // Appointment class declaration
├── Appointment.cpp    // Appointment class implementation
├── Calendar.h         // Calendar class declaration
├── Calendar.cpp       // Calendar class implementation
├── main.cpp           // Driver / user interaction
└── appointments.txt   // Persistent schedule data
```

There are two classes — `Appointment` and `Calendar` — plus a
`main.cpp` driver that ties them together.

---

## 2. Appointment

An appointment is defined as a period with a **start time**, an
**end time**, and a **description**.

- The user enters the start and end time.
- Each one contains hours, minutes, and a period (AM or PM).
- Internally, the time is converted into one integer, for example
  `202204211314`.
- This `long long` integer is in the `YYYYMMDDHHMM` format and is
  composed of year, month, day, hour, and minute. It can be converted
  back to a human-readable form in most outputs, for example
  `2022/04/21 - 01:14 PM`.

A valid appointment should consist of these criteria (enforced by the
driver in `main.cpp` via `isValidInput()` before the values are ever
handed to an `Appointment` object):

- The month has to be between 1 and 12.
- The minute has to be between 0 and 59.
- The hour has to be between 1 and 12, regardless of AM or PM.
- The period has to be either AM or PM; the program standardizes the
  case for this input.
- The program also evaluates the validity of the day, since some months
  have 30 days and others have 31. Leap-year logic is included as well
  (divisible by 4, unless divisible by 100 but not by 400).
- As a final cross-field check, the **end time must be strictly after
  the start time**; otherwise the entry is discarded.

### Class responsibilities

- **Private data** — month/day/year, hour/minute, AM-PM period for
  both start and end, a `description` string, and cached timestamps.
- **Constructor** — a member-initializer list sets every field to a
  safe default.
- **Overloaded setters**
  - `setStart(int m, int d, int y, int h, int mn, string period)` takes
    human-readable values (used when the user types them in).
  - `setStart(long long ts)` takes the compact `YYYYMMDDHHMM` form read
    from the file and decomposes it back into the individual fields.
  - The same overloading pattern is used for `setEnd`.
- **`const` getters** — `getStart()` and `getEnd()` return a
  normalized 24-hour-based timestamp so two appointments can be
  compared with a single integer comparison. `getDescription()` returns
  the text.
- **`printSingleApp() const`** — formats one appointment using
  `<iomanip>` (`setw`, `setfill`) for aligned, zero-padded output.

---

## 3. Calendar

A calendar consists of multiple appointments.

- These appointments should not have any conflict with each other.
- A text file is used to store all the appointments. The text file
  does **not** need to have the appointments in the right order —
  the program sorts them on load.

**Example `appointments.txt` file:**

```
Start|End|Description
202604151200|202604151300|Lunch Meeting (Wednesday)
202604141800|202604142000|Dinner with Parents (Tuesday)
202604150900|202604151000|Morning Standup (Wednesday)
202604140830|202604140930|Coffee Catch-up (Tuesday)
202604161400|202604161530|Project Deep Dive (Thursday)
202604142330|202604150030|Late Night Coding (Tue/Wed)
202604151430|202604151530|Design Review (Wednesday)
202604160800|202604160900|Gym Session (Thursday)
```

### Class responsibilities

- **Private data**
  - `vector<Appointment> appointments` — the container of stored
    appointments.
  - `parseLine()` — helper that splits one `|`-delimited line into
    start, end, and description, converts the numeric fields with
    `stoll`, and writes the result into an `Appointment` passed by
    reference. Wrapped in `try/catch` so a malformed line is skipped
    cleanly.
  - `sortAppointment()` — an in-class **selection sort** over the
    vector, using `getStart()` as the key.
- **Public interface**
  - `loadAppointments(const string &filename)` — opens the file with
    `ifstream`, reads it line-by-line with `getline`, uses `parseLine`
    to populate each `Appointment`, `push_back`s it into the vector,
    and finally sorts. Returns the populated vector.
  - `checkConflict(const Appointment &a)` — walks the (now sorted)
    vector and applies the overlap test
    `newStart < existingEnd && existingStart < newEnd`. Because the
    list is sorted by start time, the loop can exit early once it
    passes the new appointment's end time.
  - `addAppointments(const Appointment &a, const string &filename)` —
    the "commit" operation. It first calls `checkConflict`; if there's
    no conflict, it opens the file in **append mode**
    (`ofstream(filename, ios::app)`), writes the new appointment as
    `start|end|description`, `push_back`s it into the in-memory
    vector, re-runs `sortAppointment()` so the vector stays ordered,
    and reprints the updated schedule. Returns `true` on success,
    `false` on conflict.
  - `printAppointments() const` — a range-`for` loop that calls
    `printSingleApp()` on each element, with a divider line printed
    between entries for readability.

---

## 4. Main Program

The program shows the existing appointments and then enters an
**interactive loop**: the user can enter one appointment after
another, and the program checks each for conflicts before adding it
to both the in-memory calendar and the data file. The existing
appointments are stored in a **vector**. A vector is chosen over a
plain array because a vector's size can be dynamically changed;
therefore, it is more suitable for loading and writing operations.

### Helper functions in `main.cpp`

- `bool isValidInput(int y, int m, int d, int h, int mn, string &p)` —
  runs the full per-field validation: month range, minute range, hour
  range, AM/PM (uppercased in-place through the reference parameter),
  and day-of-month with a lookup array plus leap-year adjustment for
  February.
- `bool getValidDateTime(int &y, int &m, int &d, int &h, int &mn,`
  `string &p, string label)` — prompts the user for each field,
  calls `isValidInput` in a `while (true)` loop, and only returns
  when the user types a valid date/time. Writes its results back
  through **reference parameters** (out-parameters). Returns `false`
  if the user enters `-99` for the year, which is the sentinel used
  to quit the program.

### High-level flow

1. Create a `Calendar` object and call
   `loadAppointments("appointments.txt")`, which reads each line,
   parses it into an `Appointment`, stores it in the vector, and
   sorts the list. `printAppointments()` then displays the existing
   schedule.
2. Enter the main `while (true)` loop.
3. Call `getValidDateTime(..., "START TIME")`. If it returns `false`
   (user typed `-99`), `break` out of the loop and exit cleanly.
4. Build a new `Appointment` and set its start with the
   human-readable overload `setStart(m, d, y, h, mn, period)`.
5. Call `getValidDateTime(..., "END TIME")` and set the end the same
   way.
6. `cin.ignore(1000, '\n')` to discard the leftover newline, then
   `getline(cin, desc)` to read the free-text description.
7. Sanity check: if `newAppt.getEnd() <= newAppt.getStart()`, print
   an error and `continue` to the top of the loop — the entry is
   discarded.
8. Call `myCalendar.addAppointments(newAppt, inputFile)`. This single
   method handles the conflict check, the file append, the vector
   update, and the re-sort. `main` just reports success or failure.

### Conflict Detection

Once the new start and new end values are known, `checkConflict`
compares them against the existing appointments in the (sorted)
vector:

- **The Overlap Math** — for every existing appointment, it runs a
  single check:
  *Is the New Start < Existing End* **AND** *Is the Existing Start < New End?*
- **Early exit** — because the vector is sorted by start time, the
  loop breaks as soon as it finds an existing appointment whose start
  is `>= newEnd`. Nothing after that point can overlap.
- **Outcome** — if the condition is true for even one appointment,
  `checkConflict` returns `true`, `addAppointments` refuses to add
  the entry, and `main` reports the conflict and lets the user try
  again. If the entire list clears, the appointment is appended to
  `appointments.txt`, inserted into the in-memory vector, and the
  vector is re-sorted so subsequent conflict checks remain correct.

---

## 5. Concepts Used

The project pulls together essentially every major topic covered in
the course.

### Basic C++
- `#include <iostream>`, `<string>`, `using namespace std;`
- `main()` returning `int`, `return 0;`
- Primitive types `int`, `long long`, `bool`, and the `string` class.
- `cin` / `cout` for console I/O.
- Header guards (`#ifndef / #define / #endif`) so each header is
  included only once per translation unit.

### Conditional Statements
- `if / else if / else` chains for AM/PM conversion when decomposing
  a timestamp.
- Boolean expressions joined with `&&` in the overlap check
  `ns < ee && es < ne`.
- Early-`return true/false` pattern inside `checkConflict` so the
  function exits as soon as the answer is known.

### Loops and File I/O
- `ifstream` to read `appointments.txt`.
- `ofstream(filename, ios::app)` in `addAppointments` to **append**
  new entries without overwriting the existing data.
- `while (getline(file, line))` to process the file line-by-line.
- `stringstream` with `getline(ss, token, '|')` to split each line into
  fields.
- Classic indexed `for` loops for sorting, and range-`for`
  (`for (const auto &x : v)`) when the index isn't needed.
- `while (true) { ... break; }` in `main()` for the interactive
  session, exited only by the `-99` sentinel, and another
  `while (true)` inside `getValidDateTime` to re-prompt on bad input.
- `cin.ignore(1000, '\n')` before `getline(cin, desc)` so the newline
  left over from the previous `cin >>` does not eat the description.

### Functions
- Separation of declaration (in the `.h` file) and definition (in the
  `.cpp` file).
- **Parameter passing**
  - *Pass by value* for small types where appropriate.
  - *Pass by `const` reference* — `const string &filename`,
    `const Appointment &a` — to avoid copying without giving the
    callee permission to modify the original.
  - *Out-parameters* — `parseLine(const string &line, Appointment &out)`
    writes through a non-const reference and returns a `bool` to
    indicate success or failure. `getValidDateTime(int &y, int &m, ...)`
    uses the same pattern to return six primitive fields at once.
  - *Mutating reference parameters* — `isValidInput(..., string &p)`
    uppercases the period string in place so the caller sees the
    normalized value.
- **Function overloading** — two `setStart` overloads and two `setEnd`
  overloads share a name but take different parameter lists (six
  human-readable fields vs. one packed `long long`).
- **Return values** of many types: `bool`, `long long`, `string`, and
  `vector<Appointment>`.
- Helper/private functions (`parseLine`, `sortAppointment`) hidden
  behind the class's public interface.

### Arrays / Vectors
- `std::vector<Appointment>` as the dynamic container of appointments
  — chosen over a raw array because the number of appointments isn't
  known ahead of time.
- `push_back` both when loading the file **and** when
  `addAppointments` commits a new entry at runtime.
- `.size()` used as the loop bound inside `sortAppointment`.
- Indexed access `appointments[i]` / `appointments[j]` during sort.
- Range-`for` traversal in `printAppointments` and `checkConflict`.
- A plain C-style array inside `isValidInput`
  (`int daysInMonth[] = {0, 31, 28, 31, ...}`) used as a lookup
  table for day-of-month validation.

### Sorting and Searching
- **Selection sort** implemented by hand in `sortAppointment()`:
  track `minIndex` / `minValue`, scan the unsorted tail, then swap.
- Using the sorted order to make conflict detection faster — the
  `if (es >= ne) break;` inside `checkConflict` is an early exit that
  only works because the list is sorted by start time.
- Comparing records by a **key** (`appointment.getStart()`) rather than
  by the object as a whole.

### Classes and Objects (OOP)
- Two user-defined classes, each with its own `.h` / `.cpp` pair.
- **Encapsulation** — all data members are `private`; only
  carefully chosen methods are `public`.
- **Constructor with a member-initializer list** in `Appointment()`
  sets every field to a known default.
- **`const` member functions** (`getStart() const`,
  `printSingleApp() const`, `printAppointments() const`) promise not
  to modify the object, which is why they can be called on
  `const Appointment &` parameters.
- **Composition** — `Calendar` *contains* a `vector<Appointment>`;
  a `Calendar` "has-a" collection of `Appointment`s.
- **Function overloading inside a class** — the two `setStart`
  signatures live together on `Appointment`.
- Clear separation of concerns: `Appointment` knows nothing about
  files, and `Calendar` is the only class that touches `fstream`.

### Extra tools picked up along the way
- `<iomanip>`: `setw`, `setfill('0')` for zero-padded, aligned output.
- `<sstream>`: `stringstream` for parsing delimited strings.
- `<string>`: `stoll` for converting text to `long long`.
- `<cctype>`: `tolower` so the program accepts `"am"`, `"AM"`, `"pm"`,
  or `"PM"`.
- `static_cast<int>(...)` for explicit, safe type conversion.
- `try / catch (...)` for defensive parsing so one bad line doesn't
  crash the whole program.

---

## 6. Design Decisions Worth Highlighting

- **Integer timestamp (`YYYYMMDDHHMM`)** — encoding the full date/time
  as a single `long long` means "is A before B?" is just `A < B`. This
  is what makes both the selection sort and the conflict loop so
  simple.
- **Two representations, two setter overloads** — the program keeps
  the human-readable fields *and* a derivable timestamp, and uses
  overloading so the same name (`setStart` / `setEnd`) works whether
  the caller has six separate pieces (from the user) or one packed
  number (from the file).
- **Sorted storage enables an early exit** — `checkConflict` is O(n)
  in the worst case but in practice returns as soon as it passes the
  new appointment's end time. Because `addAppointments` re-sorts
  after every insert, that invariant survives the interactive loop.
- **`addAppointments` as a single "commit" operation** — bundling
  conflict check + file append + vector update + re-sort into one
  method keeps `main.cpp` simple: the driver just asks the question,
  and one boolean return value decides what to print.
- **Validation lives in the driver, domain objects stay clean** —
  `isValidInput` (in `main.cpp`) owns the calendar rules so that the
  `Appointment` class stores data without repeating itself with
  defensive checks on every setter.
- **Class boundaries match real-world nouns** — `Appointment` = one
  meeting, `Calendar` = the whole schedule. `main.cpp` stays short
  because each class does its own job.

---

## 7. What This Project Demonstrates

Taken together, the project exercises every major topic from the
course:

1. Basic I/O and variables.
2. Conditional logic and validation.
3. Loops and reading/writing files.
4. Functions, parameter passing, and overloading.
5. Vectors as dynamic containers.
6. A hand-written sort and sort-aware searching.
7. Designing and implementing classes with encapsulation, composition,
   `const` correctness, and constructors.

The end result is a small but complete OOP program: a driver
(`main.cpp`) that coordinates two collaborating classes
(`Appointment` and `Calendar`) backed by a plain-text data file.
