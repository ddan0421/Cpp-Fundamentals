#include <iostream>
#include <iomanip>

using namespace std;

int main(){
  int q1, q2, q3, q4;
  double average;

  cout << "Please input your water bill for quarter 1:" << endl;
  cin >> q1;

  cout << "Please input your water bill for quarter 2:" << endl;
  cin >> q2;

  cout << "Please input your water bill for quarter 3:" << endl;
  cin >> q3;

  cout << "Please input your water bill for quarter 4:" << endl;
  cin >> q4;

  cout << fixed << setprecision(2);
  average = (q1+q2+q3+q4) / 12.0;

  if (average > 75.0)
  {
    cout << "Your average monthly bill is " << average 
      <<". Your are using excessive ammounts of water" << endl;
  }
  else if (average >= 25.0)
  {
    cout << "Your average monthly bill is " << average
      <<". You are using a typical amount of water" << endl;
  }
  else 
  {
    cout << "Your average monthly bill is " << average
      <<". You are using very little water! Very sustainable!" << endl;
  }

  return 0;
}

