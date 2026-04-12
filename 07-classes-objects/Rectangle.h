// Lines starting with # are preprocessor directives: the preprocessor runs
// before compilation and replaces or selects text. It does not "execute" like
// normal C++ code.

// Include guard: prevents this header's contents from being processed more
// than once if multiple files #include "Rectangle.h" (directly or indirectly).
// #ifndef = "if this macro is not yet defined..."
#ifndef RECTANGLE_H
// #define creates a macro name the preprocessor remembers for later #ifdef / #ifndef.
#define RECTANGLE_H

// Class declaration (header / interface) — aligns with 01-intro-oop notes:
// ADT, public interface vs private data, data hiding.

class Rectangle {
public:
  Rectangle(float side_l, float side_w);
  Rectangle();
  ~Rectangle();

  void setLength(float side_l);
  void setWidth(float side_w);

  // Accessors: do not change object state — marked const (01-intro-oop).
  float getLength() const;
  float getWidth() const;
  double findArea() const;
  double findPerimeter() const;

private:
  float length;
  float width;
};

// #endif closes the matching #ifndef (or #if / #ifdef) block above.
#endif
