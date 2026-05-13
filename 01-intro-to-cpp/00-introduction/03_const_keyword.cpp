#include <iostream>

int main() {
    // The const keyword specifies that a variable's value is constant
    // tells the compiler to prevent anything from modifying it
    // (read only)
    // tells the program to calculate the circumference of a circle
    const double PI = 3.1415926;
    const int LIGHT_SPEED = 299792458;
    double radius = 10;
    double circumfernce = 2 * PI * radius;
    std::cout << circumfernce << "cm";
    return 0;

}