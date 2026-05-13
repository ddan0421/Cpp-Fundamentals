#include <iostream>

using namespace std;

const int TOTALYEARS = 100;

typedef int AgeType[TOTALYEARS];

void printStats(const AgeType);

int main(){
    AgeType ageFrequency = {0};
    int inputNum;

    cout << "Please input an age from one to 100, put -99 to stop" << endl;
    cin >> inputNum;

    while (inputNum != -99){
        ageFrequency[inputNum-1]+=1;
        cout << "Please input an age from one to 100, put -99 to stop" << endl;
        cin >> inputNum;
    }

    printStats(ageFrequency);

    return 0;
}


void printStats(const AgeType array){
    for (int i = 0; i < TOTALYEARS; i++){
        if (array[i] != 0)
            cout << "The numbner of people " << i+1 << "years old is " << array[i] << endl;
    }
}
