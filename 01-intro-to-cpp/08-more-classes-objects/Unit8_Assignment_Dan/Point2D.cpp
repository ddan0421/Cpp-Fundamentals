#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Point2D {
private:
    int x, y;
public:
    Point2D(int xVal, int yVal) : x(xVal), y(yVal) {}
    double operator-(const Point2D& right) {
        return sqrt(pow((x - right.x), 2) + pow((y - right.y), 2));
    }
    Point2D operator+(const Point2D& right) {
        return Point2D(x + right.x,  y + right.y);
    }    

    string printPoint2D(){
        return "point is (" + to_string(x) + ", " + to_string(y) + ")"; 
    }
};

int main() {
    Point2D point1(2,2);
    Point2D point2(3,4);

    Point2D addition = point1 + point2;

    cout << "The subtraction result is " << point1 - point2 << endl;
    cout << "The addition result is " << addition.printPoint2D() << endl;
    return 0;
}