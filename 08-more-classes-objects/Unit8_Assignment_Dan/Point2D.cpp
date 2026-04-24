#include <iostream>
#include <cmath>

using namespace std;

class Point2D {
private:
    int x, y;
public:
    Point2D(int xVal, int yVal) : x(xVal), y(yVal) {}
    double operator-(const Point2D& right) {
        return sqrt(pow((x - right.x), 2) + pow((y - right.y), 2));
    }
    double operator+(const Point2D& right) {
        return sqrt(pow((x + right.x), 2) + pow((y + right.y), 2));
    }    
};

int main() {
    Point2D point1(2,2);
    Point2D point2(3,4);

    cout << "The subtraction result is " << point1 - point2 << endl;
    cout << "The addition result is " << point1 + point2 << endl;

}