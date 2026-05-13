#include <iostream>

using namespace std;

class Number {
private:
    int* value;
public:
    Number(int v) {
        value = new int(v);
    }
    Number(const Number& obj) { // Copy constructor
        value = new int(*obj.value);
    }
    ~Number() { delete value; }
    void setValue(int v) { *value = v; }
    int getValue() const { return *value; }
};


int main(){
    Number num1(10);
    Number num2 = num1;

    num2.setValue(20);

    cout << "num1 is " << num1.getValue() << endl; // should be 10
    cout << "num2 is " << num2.getValue() << endl; // should be 20
    return 0;
}