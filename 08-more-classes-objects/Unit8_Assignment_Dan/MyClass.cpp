#include <iostream>

using namespace std;

class MyClass {
private:
  int value;

public:
  MyClass(int v) : value(v) {}
  friend void showValue(MyClass &obj);
};

void showValue(MyClass &obj) {
  obj.value = 2; // update the private variable
  cout << "Value: " << obj.value << endl;
}

int main() {
  MyClass class1(1);
  showValue(class1);

  return 0;
}
