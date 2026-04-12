// Client file — uses objects through the public interface only (01-intro-oop).
// Demonstrates constructors / destructor (02) and an array of objects (03).
//
// =============================================================================
// HOW TO BUILD THIS PROGRAM (from the directory that contains these files)
// =============================================================================
//
// Recommended command (one step: compile + link):
//
//   g++ -Wall -Wextra -std=c++17 -o oop_three_file_example main.cpp Rectangle.cpp
//
// Then run:
//
//   ./oop_three_file_example
//
// -----------------------------------------------------------------------------
// What that command means (left to right)
// -----------------------------------------------------------------------------
//
//   g++
//     The GNU C++ compiler "driver". It runs the preprocessor, compiler, and
//     linker for you. When you give it .cpp files, it compiles each one into
//     object code, then links them into one executable.
//
//   -Wall
//     Enables a large set of common warnings (the name is historical: "all"
//     common warnings, not literally every possible warning). Helps catch
//     suspicious code early (unused variables, wrong conversions, etc.).
//
//   -Wextra
//     Enables extra warnings that are not turned on by -Wall alone. Using
//     -Wall together with -Wextra is a typical habit for clearer, safer code.
//
//   -std=c++17
//     Tells the compiler which C++ *language standard* to use (here, C++17).
//     Without this flag, g++ uses its default standard (depends on g++ version).
//     You could use -std=c++14 or -std=c++20 if your course or project requires
//     a different version.
//
//   -o oop_three_file_example
//     Names the output *executable* file "oop_three_file_example".
//     Without -o, g++ on Linux usually creates a file named "a.out" instead.
//     The "-o" flag means "output file name"; the name must follow immediately.
//
//   main.cpp Rectangle.cpp
//     The *source files* to build. Each .cpp is a separate "translation unit":
//     the compiler compiles main.cpp and Rectangle.cpp independently, then the
//     linker combines them (along with the C++ standard library) so calls from
//     main to Rectangle's member functions resolve to the code in Rectangle.cpp.
//     Header files (.h) are pulled in via #include; you do not pass Rectangle.h
//     on the command line unless you use special modes — the #include chain is
//     enough for normal builds.
//
// In short: g++ turns your C++ sources into machine code and links them into
// one runnable program; the flags tune warnings and the language rules; -o
// names the program; the .cpp files list what to compile.
//
// -----------------------------------------------------------------------------
// Simple alternatives
// -----------------------------------------------------------------------------
//
// Minimal (fewer warnings, default standard — fine for tiny tests, less ideal
// for learning quality):
//
//   g++ main.cpp Rectangle.cpp -o oop_three_file_example
//
// Same as above but accept the default executable name "a.out":
//
//   g++ -Wall -Wextra -std=c++17 main.cpp Rectangle.cpp
//   ./a.out
//
// Use the generic compiler name (on many systems this is still g++ or clang):
//
//   c++ -Wall -Wextra -std=c++17 -o oop_three_file_example main.cpp Rectangle.cpp
//
// Clang instead of GCC (same general idea; flags are largely compatible):
//
//   clang++ -Wall -Wextra -std=c++17 -o oop_three_file_example main.cpp Rectangle.cpp
//
// Two-step compile then link (same result; useful when projects get large):
//
//   g++ -Wall -Wextra -std=c++17 -c Rectangle.cpp -o Rectangle.o
//   g++ -Wall -Wextra -std=c++17 -c main.cpp      -o main.o
//   g++ -Wall -Wextra -std=c++17 -o oop_three_file_example main.o Rectangle.o
//
//   Here -c means "compile only, do not link yet". The .o files are object
//   files. The last line links them into the final executable. Recompiling only
//   the .cpp you changed can save time on big projects (build tools like make
//   or CMake automate that).
//
// =============================================================================

#include <iostream>
#include "Rectangle.h"

using namespace std;

namespace {
const int kNumberOfBoxes = 4;
}

int main() {
  Rectangle box1;
  Rectangle box2(9.5F, 8.5F);
  Rectangle room(10.0F, 12.0F);

  box1.setLength(20.0F);
  box1.setWidth(5.0F);

  cout << "--- Two separate objects (dot operator) ---\n";
  cout << "box1 length: " << box1.getLength() << ", width: " << box1.getWidth()
       << ", area: " << box1.findArea()
       << ", perimeter: " << box1.findPerimeter() << "\n";
  cout << "box2 length: " << box2.getLength() << ", width: " << box2.getWidth()
       << ", area: " << box2.findArea()
       << ", perimeter: " << box2.findPerimeter() << "\n";
  cout << "room (parameterized ctor): area " << room.findArea() << "\n\n";

  cout << "--- Array of objects; default ctor runs per element (03) ---\n";
  Rectangle boxes[kNumberOfBoxes];
  for (int i = 0; i < kNumberOfBoxes; i++) {
    cout << "Box " << (i + 1) << " — length: " << boxes[i].getLength()
         << ", width: " << boxes[i].getWidth()
         << ", area: " << boxes[i].findArea() << "\n";
  }

  return 0;
}
