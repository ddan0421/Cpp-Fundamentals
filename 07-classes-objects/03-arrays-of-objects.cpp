#include <iostream>
using namespace std;

// Arrays of Objects
// Arrays can also contain objects of a class. For example, we could have an
// array of Rectangle objects. Example: Rectangle box[4]; // box is defined as
// an array of Rectangle objects This statement makes an array of 4 elements,
// each consisting of an object of the Rectangle class. Since this class has a
// default constructor, the default values are assigned to each element (object)
// of the array. The length and width for each of the objects in the box array
// are equal to 1 since these are the default values assigned by the default
// constructor.

class Rectangle {
public:
  // Constructor allowing a user to input the length and width
  Rectangle(float side_l, float side_w);
  Rectangle();  // Default constructor
  ~Rectangle(); // Destructor
  void setLength(float side_l);
  void setWidth(float side_w);
  float getLength();
  float getWidth();
  double findArea();
  double findPerimeter();

private:
  float length;
  float width;
};
const int NUMBEROFOBJECTS = 4;
int main() {
  Rectangle box[NUMBEROFOBJECTS]; // Box is defined as an array of
  // Rectangle objects
  for (int pos = 0; pos < NUMBEROFOBJECTS; pos++) {
    cout << "Information for box number " << pos + 1 << endl << endl;
    cout << "The length of the box is " << box[pos].getLength() << endl;
    cout << "The width of the box is " << box[pos].getWidth() << endl;
    cout << "The area of the box is " << box[pos].findArea() << endl;
    cout << "The perimeter of the box is " << box[pos].findPerimeter() << endl
         << endl;
  }
  return 0;
}
void Rectangle::setLength(float side_l) { length = side_l; }
void Rectangle::setWidth(float side_w) { width = side_w; }
float Rectangle::getLength() { return length; }
float Rectangle::getWidth() { return width; }
double Rectangle::findArea() { return length * width; }
double Rectangle::findPerimeter() { return ((2 * length) + (2 * width)); }
Rectangle::Rectangle(float side_l, float side_w) {
  length = side_l;
  width = side_w;
}
Rectangle::Rectangle() {
  length = 1;
  width = 1;
}
Rectangle::~Rectangle() {}
