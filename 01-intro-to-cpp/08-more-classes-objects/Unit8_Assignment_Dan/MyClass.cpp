#include <iostream>

using namespace std;

class MyClass {
private:
  int value;

public:
  MyClass(int v) : value(v) {}
  void getValue() {cout << "The value is " << value << endl;}
  friend void showValue(MyClass &obj);
};

void showValue(MyClass &obj) {
  obj.value = 2; // update the private variable
  cout << "After updating, the value is now: " << obj.value << endl;
}

int main() {
  MyClass class1(1);
  class1.getValue();
  showValue(class1);

  return 0;
}
