#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double g = 9.8;

float calculateDistance(int);

int main(){
    int time;
    double heights;

    cout << "Please input the time of fall in seconds:" << endl;
    cin >> time;

    cout << "Please input the height of the bridge in meters:" << endl;
    cin >> heights;

    double final_distance = calculateDistance(time);

    if (final_distance > heights)
        cout << "Warning-Bad Data: The distance fallen exceeds the height of the bridge" << endl;

    return 0;

}


float calculateDistance(int inputTime){
    cout << "Time Falling (seconds) Distance Fallen (meters)" << endl;
    cout << "***********************************************" << endl;

    double distance;
    for (int i = 0; i <= inputTime; i++){
        distance = 0.5 * g * pow(i, 2);
        cout << i << setw(25) << distance << endl;
    }
    return distance;
}
