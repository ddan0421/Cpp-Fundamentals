#include <iostream>
#include <string>

using namespace std;

/*
Function template: a pattern for a function that can work with many data types
When written, parameters are left for the data types
When called, compiler generates code for specific data types in function call 

template <typename T>
T times10(T num)
{
    return 10 * num;
}

- typename T is template prefix and typename is generic data type
- T is type parameter

*/

// Call a template function in the usual manner:
/*
In the background it essentially writes:
// For ival
int times10(int num) {
    return 10 * num;
}

// For dval
double times10(double num) {
    return 10 * num;
}
*/
int ival = 3;
double dval = 2.55;
template <typename T>
T times10(T num)
{
    return 10 * num;
}
int main(){
    cout << times10(ival) << endl; // displays 30 
    cout << times10(dval) << endl; // displays 25.5
    return 0;
}




