#include <iomanip>
#include <iostream>

// Dan Dan
// Option 2

using namespace std;

void calculateSpeed(int, int, float &);

int main() {
  int milesTraveled, hoursTraveled;
  float speedTraveled;

  cout << fixed << setprecision(2) << showpoint;

  cout << "Please input the miles traveled" << endl;
  cin >> milesTraveled;
  cout << "Please input the hours traveled" << endl;
  cin >> hoursTraveled;

  calculateSpeed(milesTraveled, hoursTraveled, speedTraveled);

  cout << "Your speed is " << speedTraveled << " miles per hour" << endl;

  return 0;
}

void calculateSpeed(int miles, int hours, float &speed) {
  if (hours == 0) {
    speed = 0;
  } else {
    speed = static_cast<float>(miles) / (hours);
  }
}
