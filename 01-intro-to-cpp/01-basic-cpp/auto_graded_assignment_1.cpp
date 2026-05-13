#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;

const double PI = 3.14;

int main(){
  double radius;
  double area;


  cout << setprecision(2) << fixed << showpoint;

  cout << "Enter the radius of the circle (m): ";
  cin >> radius;

  area = PI * pow(radius, 2);
  
  cout << "The area of the circle is: " << area << " square meters" << endl;

  return 0;
}



