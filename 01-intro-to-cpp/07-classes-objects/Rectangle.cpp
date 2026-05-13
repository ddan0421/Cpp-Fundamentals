#include "Rectangle.h"

// Implementation file — member definitions use the scope operator (Class::name)
// as in 01-intro-oop and 02-constructor-destructor.

Rectangle::Rectangle(float side_l, float side_w) {
  length = side_l;
  width = side_w;
}

Rectangle::Rectangle() {
  length = 1.0F;
  width = 1.0F;
}

Rectangle::~Rectangle() {
  // Primary role: release resources when the object leaves scope (02 / 03).
  // No dynamic memory here, so the body is empty — same idea as 03-arrays-of-objects.
}

void Rectangle::setLength(float side_l) { length = side_l; }

void Rectangle::setWidth(float side_w) { width = side_w; }

float Rectangle::getLength() const { return length; }

float Rectangle::getWidth() const { return width; }

double Rectangle::findArea() const {
  return static_cast<double>(length) * static_cast<double>(width);
}

double Rectangle::findPerimeter() const {
  return (2.0 * static_cast<double>(length)) + (2.0 * static_cast<double>(width));
}
