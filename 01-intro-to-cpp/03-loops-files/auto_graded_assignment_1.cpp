#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {

  ifstream dataFile;
  float YearAvg, hottest, coldest, total, temperature;
  int HottestDay, ColdestDay;
  const int CALENDARDAY = 360;

  cout << fixed << setprecision(3) << showpoint;

  dataFile.open("WeatherData.txt");

  for (int day = 1; day <= CALENDARDAY; day++) {
    // initialization
    if (day == 1) {
      dataFile >> temperature;
      hottest = temperature;
      coldest = temperature;
      ColdestDay = day;
      HottestDay = day;
      total = temperature;
    } else {
      dataFile >> temperature;
      if (temperature > hottest) {
        hottest = temperature;
        HottestDay = day;
      }
      if (temperature < coldest) {
        coldest = temperature;
        ColdestDay = day;
      }
      total += temperature;
    }
  }

  YearAvg = total / CALENDARDAY;

  cout << "Average yearly temperature: " << YearAvg << endl;
  cout << "Day " << HottestDay << " was the hottest, with a temperature of "
       << hottest << " degrees Celsius." << endl;
  cout << "Day " << ColdestDay << " was the coldest, with a temperature of "
       << coldest << " degrees Celsius." << endl;

  return 0;
}
